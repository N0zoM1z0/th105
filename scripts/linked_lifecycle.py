"""Strict VC8 source-owned zero globals and cleanup-only EH in real CRT images.

These witnesses grant no authored byte credit. Every code/data region is fully
compared after typed relocation replay; an unsupported form fails closed.
"""
from __future__ import annotations

import csv
import hashlib
from pathlib import Path
import re
import struct

import capstone
import linked_pe as core

ADDRESS = re.compile(r"0x[0-9A-Fa-f]{8}$")
OBJECT_FIELDS = {"symbol", "target", "size", "layout_source", "initializer", "initializer_table",
                 "atexit", "destructor_callback"}


def validate_contract(unit: dict, data_keys: set[str]) -> None:
    from workflow_manifest import repository_path, source_dependencies
    runtime = unit.get("link_runtime", "import")
    objects, runtime_data = unit.get("link_objects", []), unit.get("link_runtime_data", [])
    if not isinstance(runtime, str) or runtime not in {"import", "static"} or not isinstance(objects, list):
        raise ValueError("unsupported linked runtime/global contract")
    if runtime_data not in ([], ["___security_cookie"]):
        raise ValueError("only the native static CRT security cookie has a runtime-data contract")
    if runtime != "static" and (objects or runtime_data):
        raise ValueError("source-owned global lifecycles require the real static CRT")
    functions = unit.get("functions", [])
    if not isinstance(functions, list):
        raise ValueError("linked lifecycle functions must be a list")
    names = set()
    external = {str(m).split("=", 1)[0] for m in unit.get("link_data_targets", [])}
    external_keys = {str(m).partition("=")[2] for m in unit.get("link_data_targets", [])}
    if external_keys.intersection(runtime_data):
        raise ValueError("native runtime storage cannot also have an absolute external provider")
    for obj in objects:
        if not isinstance(obj, dict) or set(obj) != OBJECT_FIELDS:
            raise ValueError("global lifecycle requires exact layout/startup fields")
        symbol = obj["symbol"]
        if (not isinstance(symbol, str) or not core.SYMBOL.fullmatch(symbol)
                or symbol in names or symbol in external or not isinstance(obj["target"], str)
                or obj["target"] not in data_keys or obj["target"] in external_keys
                or type(obj["size"]) is not int or not 0 < obj["size"] <= 65536 or obj["size"] % 4):
            raise ValueError("invalid/duplicate source-owned global layout")
        if any(not isinstance(obj[k], str) or not ADDRESS.fullmatch(obj[k])
               for k in ("initializer", "initializer_table", "atexit", "destructor_callback")):
            raise ValueError("global startup needs exact target addresses")
        layout = obj["layout_source"]
        if (not isinstance(layout, str) or not layout.startswith("src/") or not layout.endswith(".cpp")
                or repository_path(layout) not in source_dependencies(unit)):
            raise ValueError("global native layout must come from the real included source")
        pair = [f for f in functions if isinstance(f, dict) and isinstance(f.get("private_global"), dict)
                and f["private_global"].get("object") == symbol]
        if len(pair) != 2 or {f["private_global"].get("role") for f in pair} != {"constructor", "destructor"}:
            raise ValueError("global lifecycle needs one constructor/destructor pair")
        ctor = next(f.get("symbol_base") for f in pair if f["private_global"]["role"] == "constructor")
        if not isinstance(ctor, str):
            raise ValueError("global constructor needs its exact native class symbol")
        match = re.fullmatch(r"\?\?0([A-Za-z_]\w*(?:@[A-Za-z_]\w*)*)@@QAE@XZ", ctor)
        same_type = bool(match and symbol.endswith("@@3U" + match[1] + "@@A"))
        if match and len(match[1].split("@")) == 2:
            cls, namespace = match[1].split("@")
            same_type |= symbol.endswith("@" + namespace + "@@3U" + cls + "@1@A")
        if (not same_type
                or next(f.get("symbol_base") for f in pair if f["private_global"]["role"] == "destructor")
                != "??1" + match[1] + "@@QAE@XZ"):
            raise ValueError("global symbol and natural lifecycle class identities disagree")
        names.add(symbol)
    for f in functions:
        if not isinstance(f, dict):
            continue  # The base contract diagnoses malformed function records.
        if "eh_cleanup" in f:
            eh = f["eh_cleanup"]
            symbol = str(f.get("symbol_base", ""))
            source_method = (re.fullmatch(r"\?\?[01][A-Za-z_]\w*(?:@[A-Za-z_]\w*)*@@[QU]AE@XZ", symbol)
                             or re.fullmatch(r"\?[A-Za-z_]\w*@[^?]+@@[QU][AB]E.+", symbol))
            source_stdcall = re.fullmatch(r"\?[A-Za-z_]\w*(?:@[A-Za-z_]\w*)*@@YG[A-Z].+@Z", symbol)
            private = f.get("private_from")
            ctor = re.fullmatch(r"\?\?0[A-Za-z_]\w*(?:@[A-Za-z_]\w*)*@@QAE@XZ", symbol)
            dtor = re.fullmatch(r"\?\?1[A-Za-z_]\w*(?:@[A-Za-z_]\w*)*@@QAE@XZ", symbol)
            source_only = isinstance(private, dict) and private.get("source_only_caller") is True
            private_ok = (private is None and source_method
                          or isinstance(private, dict) and
                          (private.get("through_exact_caller") is True or dtor
                           or source_only and (ctor or source_stdcall)))
            public_lifetime = (
                runtime == "static" and runtime_data == ["___security_cookie"]
                and (source_method or source_stdcall and source_only) and private_ok
                and not any(k in f for k in
                            ("export_name", "private_global", "private_static_leaf", "vtable_entry")))
            if (not isinstance(eh, dict) or set(eh) != {"handler", "info"}
                    or any(not isinstance(v, str) or not ADDRESS.fullmatch(v) for v in eh.values())
                    or (not objects and not public_lifetime)):
                raise ValueError("cleanup EH requires exact handler/FuncInfo fields and either "
                                 "a global witness or a source member with static CRT cookie and export/private-lifetime-caller proof")
        if "private_global" not in f:
            continue
        witness = f["private_global"]
        if (not isinstance(witness, dict) or set(witness) != {"object", "role"}
                or not isinstance(witness["object"], str) or witness["object"] not in names
                or not isinstance(witness["role"], str) or witness["role"] not in {"constructor", "destructor"}
                or any(k in f for k in ("export_name", "private_from")) or "eh_cleanup" not in f):
            raise ValueError("private global entry requires its unique startup role and complete EH")


def native_zero_layout(data: bytes, symbol: str, size: int) -> dict:
    """Read a native COFF witness, never treating uninitialized raw_pointer=0 as bytes."""
    if len(data) < 20:
        raise ValueError("truncated native layout COFF")
    machine, count, _, symptr, nsym, optional, _ = struct.unpack_from("<HHIIIHH", data)
    strings = symptr + nsym * 18
    if (machine != 0x14c or optional or not count or 20 + count * 40 > symptr
            or strings + 4 > len(data)):
        raise ValueError("global layout needs a bounded native i386 COFF")
    string_size, = struct.unpack_from("<I", data, strings)
    if string_size < 4 or strings + string_size > len(data):
        raise ValueError("truncated native COFF string table")
    symbols = []
    i = 0
    while i < nsym:
        at = symptr + i * 18
        raw = data[at:at + 8]
        if raw[:4] == b"\0" * 4:
            offset, = struct.unpack_from("<I", raw, 4)
            end = data.find(b"\0", strings + offset, strings + string_size)
            if offset < 4 or end < 0:
                raise ValueError("invalid native COFF symbol string")
            name = data[strings + offset:end].decode("ascii")
        else:
            name = raw.rstrip(b"\0").decode("ascii")
        value, section, typ, storage, aux = struct.unpack_from("<IhHBB", data, at + 8)
        if i + 1 + aux > nsym:
            raise ValueError("invalid native COFF auxiliary count")
        symbols.append((name, value, section, typ, storage))
        i += 1 + aux
    found = [s for s in symbols if s[0] == symbol]
    if len(found) != 1 or not 0 < found[0][2] <= count or found[0][1:] != (0, found[0][2], 0, 2):
        raise ValueError("global layout symbol is not unique strong data at section offset zero")
    section = found[0][2]
    at = 20 + (section - 1) * 40
    raw_size, raw_pointer, reloc_pointer = struct.unpack_from("<III", data, at + 16)
    reloc_count, = struct.unpack_from("<H", data, at + 32)
    flags, = struct.unpack_from("<I", data, at + 36)
    peers = [s for s in symbols if s[2] == section and s[0] not in {symbol, ".bss"}]
    if (data[at:at + 8].rstrip(b"\0") != b".bss" or raw_size != size or raw_pointer
            or reloc_pointer or reloc_count or flags not in (0xc0300080, 0xc0400080)
            or size % (4 if flags == 0xc0300080 else 8) or peers):
        raise ValueError("global native witness must be its sole compiler-aligned zero .bss object")
    return {"symbol": symbol, "size": size, "alignment": 4 if flags == 0xc0300080 else 8, "section": ".bss", "flags": flags}


def layout_inputs(unit: dict, image: Path) -> list[dict]:
    from workflow_manifest import repository_path
    result = []
    for i, obj in enumerate(unit.get("link_objects", [])):
        path = image.with_suffix(f".layout{i}.obj")
        result.append({"source": obj["layout_source"], "source_sha256": core.sha(repository_path(obj["layout_source"])),
                       "object": path.name, "object_sha256": core.sha(path),
                       "layout": native_zero_layout(path.read_bytes(), obj["symbol"], obj["size"])})
    return result


def unique_symbol(symbols: dict, name: str, owner: str) -> int:
    found = symbols.get(name, [])
    if len(found) != 1 or found[0][1].split()[-1:] != [owner]:
        raise ValueError("global/runtime data has no unique native linker owner: " + name)
    return found[0][0]


def private_entry(functions: dict, exports: dict, name: str, cil_owner: str, *, compiler=False) -> int:
    found = [(address, owner) for address, aliases in functions.items() for n, owner in aliases if n == name]
    if (len(found) != 1 or len(functions[found[0][0]]) != 1 or found[0][0] in exports.values()
            or not (found[0][1].split()[-1:] == [cil_owner]
                    or compiler and found[0][1] == "CIL library: CIL module")):
        raise ValueError("lifecycle/compiler entry is not unique private CIL code: " + name)
    return found[0][0]


def writable_zero(pe, address: int, size: int) -> None:
    rva = address - pe.OPTIONAL_HEADER.ImageBase
    section = pe.get_section_by_rva(rva)
    if (address % 4 or section is None or section.Characteristics & 0x20000000
            or section.Characteristics & 0xc0000000 != 0xc0000000
            or not section.VirtualAddress <= rva < rva + size <= section.VirtualAddress + section.Misc_VirtualSize):
        raise ValueError("global object escapes aligned writable nonexecutable mapped storage")
    # PE virtual zero fill is a loader property, not a copied data payload.
    offset = rva - section.VirtualAddress
    available = max(0, min(size, section.SizeOfRawData - offset))
    raw = pe.get_data(rva, available)
    if len(raw) != available or any(raw):
        raise ValueError("global mapped storage is not initially zero")


def require_equal(source: bytes, target: bytes, label: str) -> dict:
    if source != target:
        raise ValueError("full lifecycle/EH region differs: " + label)
    return {"kind": label, "size": len(source), "canonical_sha256": hashlib.sha256(source).hexdigest(),
            "target_sha256": hashlib.sha256(target).hexdigest()}


def rebase_data(pe, start: int, raw: bytes, replacements: dict[int, tuple[int, int]]) -> bytes:
    refs, out = [], bytearray(raw)
    for offset, (expected, target) in replacements.items():
        if offset % 4 or offset < 0 or offset + 4 > len(raw) or struct.unpack_from("<I", raw, offset)[0] != expected:
            raise ValueError("invalid typed lifecycle metadata pointer field")
        struct.pack_into("<I", out, offset, target)
        refs.append({"field_offset": offset})
    core.validate_body_relocations(pe, start, len(raw), refs)
    return bytes(out)


def validate_static_entry(pe, functions: dict) -> None:
    start = pe.OPTIONAL_HEADER.ImageBase + pe.OPTIONAL_HEADER.AddressOfEntryPoint
    if functions.get(start) != [("__DllMainCRTStartup@12", "libcmt:dllcrt0.obj")]:
        raise ValueError("static lifecycle image needs the real pinned DLL CRT entry")


def validate_static_runtime_initializers(pe, functions: dict, symbols: dict, *,
                                         allow_pinned_stdio: bool = False) -> list[dict]:
    """No source globals: require real CRT tables and only pinned CRT C callbacks.

    C++ initialization remains unsupported in this mode. Source-owned lifecycle
    units retain their separate complete constructor/destructor witnesses.
    """
    allowed = {
        "___onexitinit": "libcmt:onexit.obj",
        "__sse2_mathfcns_init": "libcmt:mathfcns.obj",
        "___sse2_available_init": "libcmt:cpu_disp.obj",
        "___initmbctable": "libcmt:mbctype.obj",
    }
    if allow_pinned_stdio:
        allowed["___initstdio"] = "libcmt:_file.obj"
    reports, seen = [], set()
    for family, lower, upper in (("C", "___xi_a", "___xi_z"),
                                 ("C++", "___xc_a", "___xc_z")):
        lo = unique_symbol(symbols, lower, "libcmt:crt0init.obj")
        hi = unique_symbol(symbols, upper, "libcmt:crt0init.obj")
        if lo % 4 or hi <= lo or (hi - lo) % 4 or hi - lo > 4096:
            raise ValueError("invalid real CRT runtime initializer table bounds")
        raw = core.readonly_data(pe, lo, hi - lo + 4)
        if raw[:4] != bytes(4) or raw[-4:] != bytes(4):
            raise ValueError("CRT runtime initializer sentinels are not zero")
        fields = []
        for offset in range(4, len(raw) - 4, 4):
            entry, = struct.unpack_from("<I", raw, offset)
            if not entry:
                continue
            aliases = functions.get(entry, [])
            section = pe.get_section_by_rva(entry - pe.OPTIONAL_HEADER.ImageBase)
            if (family == "C++" or len(aliases) != 1
                    or allowed.get(aliases[0][0]) != aliases[0][1]
                    or aliases[0][0] in seen
                    or section is None or not section.Characteristics & 0x20000000):
                raise ValueError("runtime-only static image has an unqualified source initializer")
            seen.add(aliases[0][0])
            fields.append({"field_offset": offset})
            reports.append({"table": family, "slot": lo + offset, "entry": entry,
                            "symbol": aliases[0][0], "owner": aliases[0][1]})
        core.validate_body_relocations(pe, lo, len(raw), fields)
    return reports


def object_witnesses(unit: dict, pe, target, functions: dict, symbols: dict, exports: dict,
                     cil_owner: str, known: dict, read_target, *, layout_alignments: dict | None = None) -> tuple[list[dict], dict]:
    """Attest complete source storage and real initializer/table/atexit reachability."""
    refs, witnesses = [], {}
    with (core.ROOT / "config/functions.csv").open(newline="") as f:
        ledger = {int(r["address"], 0): r for r in csv.DictReader(f)}
    with (core.ROOT / "config/function-origins.csv").open(newline="") as f:
        origins = {int(r["address"], 0): r for r in csv.DictReader(f)}
    occupied = []
    for obj in unit.get("link_objects", []):
        symbol, size = obj["symbol"], obj["size"]
        base = unique_symbol(symbols, symbol, cil_owner)
        dst, raw, addends, validation = known[obj["target"]]
        if validation != "address" or raw != bytes(4) or any(a < 0 or a % 4 or a + 4 > size for a in addends):
            raise ValueError("global object field ledger exceeds its native zero layout")
        alignment = 4 if layout_alignments is None else layout_alignments.get(symbol)
        if alignment not in (4, 8) or base % alignment or dst % alignment:
            raise ValueError("source/target global storage violates its native COFF alignment")
        writable_zero(pe, base, size)
        writable_zero(target, dst, size)
        for start, end, target_start, target_end in occupied:
            if max(base, start) < min(base + size, end) or max(dst, target_start) < min(dst + size, target_end):
                raise ValueError("source-owned global ranges overlap")
        occupied.append((base, base + size, dst, dst + size))
        if any(base <= at < base + size for name, items in symbols.items() if name != symbol
               for at, _ in items):
            raise ValueError("source-owned global aliases another mapped symbol")
        for off in addends:
            refs.append({"kind": "object", "source_address": base + off, "address": dst + off,
                         "size": 4, "symbol": symbol, "addend": off})
        pair = {f["private_global"]["role"]: f for f in unit["functions"]
                if f.get("private_global", {}).get("object") == symbol}
        ctor = private_entry(functions, exports, pair["constructor"]["symbol_base"], cil_owner)
        dtor = private_entry(functions, exports, pair["destructor"]["symbol_base"], cil_owner)
        stem = symbol[1:].split("@@", 1)[0] + "@@YAXXZ"
        init = private_entry(functions, exports, "??__E" + stem, cil_owner, compiler=True)
        callback = private_entry(functions, exports, "??__F" + stem, cil_owner, compiler=True)
        atexit = unique_symbol(symbols, "_atexit", "libcmt:onexit.obj")
        target_atexit = int(obj["atexit"], 0)
        if (ledger.get(target_atexit, {}).get("current_name") != "_atexit"
                or (origins.get(target_atexit, {}).get("origin"), origins.get(target_atexit, {}).get("disposition"))
                != ("vc8_runtime", "exclude")):
            raise ValueError("atexit target lacks positive runtime ownership evidence")
        core.decode_closed_body(read_target(target_atexit, int(ledger[target_atexit]["size"])), target_atexit)
        # Exact compiler-generated helper forms, not manufactured caller stubs.
        def initializer(at, ctor_at, callback_at, atexit_at):
            return (b"\xe8" + struct.pack("<i", ctor_at - at - 5) + b"\x68" + struct.pack("<I", callback_at)
                    + b"\xe8" + struct.pack("<i", atexit_at - at - 15) + b"\x59\xc3")
        source_init = core.linked_body(pe, functions, init)
        if source_init != initializer(init, ctor, callback, atexit):
            raise ValueError("source global initializer is not its complete native ctor/atexit body")
        core.decode_closed_body(source_init, init)
        core.validate_body_relocations(pe, init, len(source_init), [{"field_offset": 6}])
        target_init = int(obj["initializer"], 0)
        target_callback = int(obj["destructor_callback"], 0)
        init_report = require_equal(initializer(target_init, int(pair["constructor"]["address"], 0),
                                               target_callback, target_atexit), read_target(target_init, 17), "initializer")
        source_callback = core.linked_body(pe, functions, callback)
        if source_callback != b"\xe9" + struct.pack("<i", dtor - callback - 5):
            raise ValueError("source atexit callback is not its full native destructor tail")
        core.decode_closed_body(source_callback, callback, tail=True)
        core.validate_body_relocations(pe, callback, len(source_callback), [])
        callback_report = require_equal(b"\xe9" + struct.pack("<i", int(pair["destructor"]["address"], 0) - target_callback - 5),
                                        read_target(target_callback, 5), "atexit callback")
        lo = unique_symbol(symbols, "___xc_a", "libcmt:crt0init.obj")
        hi = unique_symbol(symbols, "___xc_z", "libcmt:crt0init.obj")
        if lo % 4 or hi <= lo or (hi - lo) % 4 or hi - lo > 65536:
            raise ValueError("invalid real CRT C++ initialization table bounds")
        table = core.readonly_data(pe, lo, hi - lo + 4)
        slots = [lo + i for i in range(0, len(table), 4) if struct.unpack_from("<I", table, i)[0] == init]
        if table[:4] != bytes(4) or table[-4:] != bytes(4) or len(slots) != 1:
            raise ValueError("global initializer is not uniquely retained between real CRT sentinels")
        source_slot = slots[0]
        target_slot = int(obj["initializer_table"], 0)
        require_equal(rebase_data(pe, source_slot, struct.pack("<I", init), {0: (init, target_init)}),
                      core.readonly_data(target, target_slot, 4), "C++ initializer table slot")
        witnesses[symbol] = {"symbol": symbol, "source_address": base, "target_address": dst, "size": size,
            "source_initializer": init, "target_initializer": target_init,
            "source_initializer_slot": source_slot, "target_initializer_slot": target_slot,
            "source_callback": callback, "target_callback": target_callback,
            "regions": [init_report, callback_report]}
    for symbol in unit.get("link_runtime_data", []):
        base = unique_symbol(symbols, symbol, "libcmt:gs_cookie.obj")
        dst, raw, addends, validation = known[symbol]
        if raw != b"\x4e\xe6\x40\xbb" or addends != frozenset({0}) or validation != "address":
            raise ValueError("target runtime cookie ledger identity differs")
        for image, address in ((pe, base), (target, dst)):
            if core.pe_data(image, address, 4) != raw:
                raise ValueError("native runtime cookie initial value differs")
            section = image.get_section_by_rva(address - image.OPTIONAL_HEADER.ImageBase)
            if address % 4 or not section.Characteristics & 0x80000000:
                raise ValueError("native runtime cookie is not aligned writable data")
        refs.append({"kind": "runtime", "source_address": base, "address": dst, "size": 4, "symbol": symbol})
    return refs, witnesses


def target_handler(read_target, start: int) -> bytes:
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    raw = read_target(start, 128)
    for instruction in decoder.disasm(raw, start):
        if core.is_branch(instruction):
            if instruction.size != 5 or instruction.bytes[0] != 0xe9:
                raise ValueError("unsupported cleanup handler terminal")
            result = raw[:instruction.address + instruction.size - start]
            core.decode_closed_body(result, start, tail=True)
            return result
        if instruction.group(capstone.CS_GRP_RET):
            break
    raise ValueError("cleanup handler has no bounded full terminal jump")


def cleanup_eh(function: dict, pe, target, functions: dict, exports: dict, cil_owner: str,
               start: int, raw: bytes, target_raw: bytes, refs: list[dict], bindings: list,
               vtables: list, resolve, game_range: tuple, read_target) -> tuple[list[dict], list[dict]]:
    """Compare all cleanup funclets, the complete handler and both EH data records."""
    config, symbol = function["eh_cleanup"], function["symbol_base"]
    handler = private_entry(functions, exports, "__ehhandler$" + symbol, cil_owner, compiler=True)
    dst_handler, dst_info = int(config["handler"], 0), int(config["info"], 0)
    for body, at, expected in ((raw, start, handler), (target_raw, int(function["address"], 0), dst_handler)):
        hits = [i for i in core.decode_closed_body(body, at) if i.mnemonic == "push"
                and i.operands[0].type == capstone.x86.X86_OP_IMM and i.operands[0].imm == expected]
        if len(hits) != 1 or hits[0].size != 5:
            raise ValueError("parent does not install its unique cleanup handler")
    source_handler = core.linked_body(pe, functions, handler)
    target_code = target_handler(read_target, dst_handler)
    source_ins = core.decode_closed_body(source_handler, handler, tail=True)
    target_ins = core.decode_closed_body(target_code, dst_handler, tail=True)
    def info_pointer(instructions):
        hits = [i.operands[1].imm for i in instructions if i.mnemonic == "mov" and len(i.operands) == 2
                and i.operands[0].type == capstone.x86.X86_OP_REG
                and i.operands[0].reg == capstone.x86.X86_REG_EAX
                and i.operands[1].type == capstone.x86.X86_OP_IMM and i.imm_size == 4]
        if len(hits) != 1:
            raise ValueError("cleanup handler does not select one complete FuncInfo")
        return hits[0]
    info = info_pointer(source_ins)
    if info_pointer(target_ins) != dst_info:
        raise ValueError("target cleanup handler/FuncInfo identity disagrees")
    s_info = core.readonly_data(pe, info, 36)
    t_info = core.readonly_data(target, dst_info, 36)
    sv, tv = struct.unpack("<9I", s_info), struct.unpack("<9I", t_info)
    if (sv[0] != 0x19930522 or tv[0] != sv[0] or not 1 <= sv[1] <= 64 or tv[1] != sv[1]
            or sv[3:] != (0, 0, 0, 0, 0, 1) or tv[3:] != sv[3:]):
        raise ValueError("unsupported cleanup-only VC8 FuncInfo states/flags/catch metadata")
    states = sv[1]
    s_map = core.readonly_data(pe, sv[2], states * 8)
    t_map = core.readonly_data(target, tv[2], states * 8)
    source_funcs, target_funcs = [], []
    for i in range(states):
        state, fn = struct.unpack_from("<iI", s_map, i * 8)
        target_state, target_fn = struct.unpack_from("<iI", t_map, i * 8)
        if state != target_state or not -1 <= state < i:
            raise ValueError("cleanup unwind state transition differs or is cyclic")
        if fn != private_entry(functions, exports, "__unwindfunclet$" + symbol + "$" + str(i), cil_owner, compiler=True):
            raise ValueError("cleanup table does not reference its actual native funclet")
        source_funcs.append(fn)
        target_funcs.append(target_fn)
    if (source_funcs != sorted(set(source_funcs)) or target_funcs != sorted(set(target_funcs))
            or source_funcs[-1] >= handler or target_funcs[-1] >= dst_handler):
        raise ValueError("cleanup extents are not distinct bounded regions before their handler")
    image_range = (pe.OPTIONAL_HEADER.ImageBase, pe.OPTIONAL_HEADER.ImageBase + pe.OPTIONAL_HEADER.SizeOfImage)
    handler_ref = {"kind": "eh_handler", "source_address": handler, "address": dst_handler,
                   "symbol": "__ehhandler$" + symbol}
    info_ref = {"kind": "eh_info", "source_address": info, "address": dst_info, "symbol": "FuncInfo:" + symbol}
    all_refs = [*refs, info_ref]
    reports = []
    regions = [(handler, dst_handler, source_handler, target_code, "cleanup handler")]
    for i, (fn, dst) in enumerate(zip(source_funcs, target_funcs)):
        end = (target_funcs + [dst_handler])[i + 1]
        if not 0 < end - dst <= 256:
            raise ValueError("target cleanup exceeds its independently bounded extent")
        body = read_target(dst, end - dst).rstrip(b"\xcc")
        core.decode_closed_body(body, dst, tail=True)
        regions.append((fn, dst, core.linked_body(pe, functions, fn), body, "cleanup funclet " + str(i)))
    for at, dst, body, target_body, label in regions:
        canonical, calls, data = core.canonicalize(body, at, dst, bindings, resolve, image_range,
                                                 game_range, vtables, internal_refs=all_refs, tail=True)
        core.validate_body_relocations(pe, at, len(body), data)
        reports.append({**require_equal(canonical, target_body, label), "source_address": at,
                        "target_address": dst, "replayed_rel32": calls, "data_references": data})
    reports.append({**require_equal(rebase_data(pe, info, s_info, {8: (sv[2], tv[2])}), t_info, "FuncInfo"),
                    "source_address": info, "target_address": dst_info})
    replacements = {4 + i * 8: (source_funcs[i], target_funcs[i]) for i in range(states)}
    reports.append({**require_equal(rebase_data(pe, sv[2], s_map, replacements), t_map, "unwind map"),
                    "source_address": sv[2], "target_address": tv[2]})
    return [*refs, handler_ref], reports
