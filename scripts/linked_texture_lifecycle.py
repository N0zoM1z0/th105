"""Exact startup witness for the actual 0x84 texture service aggregate only.

The first member is the polymorphic texture manager; its eight cached handles
are initialized by the real compiler-generated CRT initializer. This does not
relax the generic same-class global lifecycle contract.
"""
from __future__ import annotations

import csv
import hashlib
import struct

import linked_pe as core

FLAG = "link_texture_manager_lifetime"
SOURCE = "src/assets/TextureServiceLifetime.cpp"
GLOBAL = "?g_texture_service_lifetime@th105@@3UTextureServiceLifetime@1@A"
KEY = "texture_service_lifetime_object"
CLASS = "?$ResourceHandleManagerLifetime64@PAUTextureResource@th105@@@th105"
CTOR = "??0" + CLASS + "@@QAE@XZ"
DTOR = "??1" + CLASS + "@@UAE@XZ"
SCALAR = "??_G" + CLASS + "@@UAEPAXI@Z"
VTABLE = "??_7" + CLASS + "@@6B@"
SIZE, TARGET = 0x84, 0x702798
INIT, TABLE, CALLBACK, ATEXIT = 0x6BE730, 0x6C0364, 0x6BEDE0, 0x68AF1E
FIELDS = frozenset((0, 8, 12, 16, 20, 28, 32, 36, 44, 48, 52, 56, 60, 64, 68, 72, 76,
                    100, 104, 108, 112, 116, 120, 124, 128))
INIT_RELOCS = (8, 13, 18, 23, 28, 33, 38, 43, 48)


def validate(unit: dict, data_keys: set[str]) -> None:
    functions = unit.get("functions", [])
    if not isinstance(functions, list) or any(not isinstance(f, dict) for f in functions):
        if FLAG in unit:
            raise ValueError("texture lifecycle needs explicit function contracts")
        return  # The ordinary linked validator diagnoses an unrelated malformed unit.
    private = [f for f in functions if "private_texture_global" in f]
    if FLAG not in unit:
        if private:
            raise ValueError("private texture entry lacks its complete texture lifecycle")
        return
    if (unit[FLAG] is not True or type(unit[FLAG]) is not bool
            or unit.get("kind") != "linked_candidate" or unit.get("source") != SOURCE
            or unit.get("link_runtime") != "static"
            or unit.get("link_runtime_data") != ["___security_cookie"]
            or unit.get("enable_gs") is not True or unit.get("link_objects")
            or unit.get("preserve_public_members") or KEY not in data_keys
            or unit.get("linked_coff_sources") != ["src/library/UnsignedIntList.cpp", "src/library/UnsignedIntVector.cpp"]):
        raise ValueError("texture lifecycle requires the actual aggregate, original providers and static CRT")
    external = [str(m).rpartition("=") for m in unit.get("link_data_targets", [])]
    if any(name == GLOBAL or key == KEY for name, _, key in external):
        raise ValueError("texture-owned global cannot also be an absolute external provider")
    expected = {"0x00404F00": CTOR, "0x00404FD0": DTOR, "0x00405040": SCALAR}
    functions = unit.get("functions", [])
    if (len(functions) != 3 or {f.get("address"): f.get("symbol_base") for f in functions} != expected
            or len(private) != 1 or private[0].get("address") != "0x00404F00"
            or private[0].get("private_texture_global") is not True
            or type(private[0].get("private_texture_global")) is not bool
            or private[0].get("eh_cleanup") != {"handler": "0x006BE461", "info": "0x006E4C94"}):
        raise ValueError("texture lifecycle needs its exact constructor, normal destructor and scalar entry")
    for f in functions:
        if any(k in f for k in ("private_global", "private_from", "export_name", "private_static_leaf")):
            raise ValueError("texture lifecycle cannot substitute an export or another private caller")
        if f["address"] == "0x00405040":
            if f.get("vtable_entry") != VTABLE:
                raise ValueError("texture scalar entry lacks its actual vtable")
        elif "vtable_entry" in f:
            raise ValueError("texture constructor/normal destructor cannot use a scalar-entry contract")
    tables = unit.get("link_vtables", [])
    required = {
        VTABLE: ("??_7TextureResourceHandleManager64@th105@@6B@", SCALAR + "=0x00405040", ".?AV?$CHandleManager@PAUIDirect3DTexture9@@@@"),
        "??_7NetworkUdpPacketCriticalSectionView@th105@@6B@": (
            "??_7CriticalSectionWrapper@th105@@6B@",
            "??_GNetworkUdpPacketCriticalSectionView@th105@@UAEPAXI@Z=0x0040ABE0", ".?AVCCriticalSection@@"),
    }
    if (len(tables) != 2 or {t.get("symbol"): (t.get("target"), t.get("entry"), t.get("target_type_name")) for t in tables} != required):
        raise ValueError("texture lifecycle needs both concrete RTTI-owned member vtables")


def layout_specs(unit: dict) -> list[dict]:
    if unit.get(FLAG) is not True:
        return []
    return [{"symbol": GLOBAL, "size": SIZE, "layout_source": SOURCE}]


def initializer_bytes(at: int, ctor: int, callback: int, atexit: int, base: int) -> bytes:
    body = b"\xe8" + struct.pack("<i", ctor - at - 5) + b"\x33\xc0\x68" + struct.pack("<I", callback)
    for offset in range(0x64, 0x84, 4):
        body += b"\xa3" + struct.pack("<I", base + offset)
    return body + b"\xe8" + struct.pack("<i", atexit - at - len(body) - 5) + b"\x59\xc3"


def callback_bytes(at: int, dtor: int, base: int) -> bytes:
    return b"\xb9" + struct.pack("<I", base) + b"\xe9" + struct.pack("<i", dtor - at - 10)


def require_bytes(actual: bytes, expected: bytes, label: str) -> None:
    if actual != expected:
        raise ValueError("texture " + label + " differs from its complete native form")


def table_slot(raw: bytes, base: int, entry: int) -> int:
    if (base % 4 or len(raw) < 12 or len(raw) % 4 or len(raw) > 65536
            or raw[:4] != bytes(4) or raw[-4:] != bytes(4)):
        raise ValueError("texture initializer lacks real bounded CRT sentinels")
    values = [(base + i, struct.unpack_from("<I", raw, i)[0]) for i in range(4, len(raw) - 4, 4)]
    live = [(at, value) for at, value in values if value]
    if len(live) != 1 or live[0][1] != entry:
        raise ValueError("texture source image has a missing, repeated or additional C++ initializer")
    return live[0][0]


def field_binding(known: dict) -> int:
    record = known.get(KEY)
    if not isinstance(record, tuple) or len(record) != 4:
        raise ValueError("texture global lacks its typed field ledger")
    dst, raw, addends, validation = record
    if dst != TARGET or raw != bytes(4) or addends != FIELDS or validation != "address":
        raise ValueError("texture global field ledger differs from the actual manager/cache layout")
    return dst


def witnesses(unit: dict, pe, target, functions: dict, symbols: dict, exports: dict,
              cil_owner: str, imports: dict, bindings: list, vtables: list,
              internal_refs: list, sdk_imports: list, known: dict, read_target,
              layouts: list) -> tuple[list, dict | None]:
    validate(unit, set(known))
    if unit.get(FLAG) is not True:
        return [], None
    from linked_lifecycle import unique_symbol, private_entry, writable_zero, rebase_data
    if (len(layouts) != 1 or layouts[0]["source"] != SOURCE
            or layouts[0]["layout"]["symbol"] != GLOBAL
            or layouts[0]["layout"]["size"] != SIZE
            or layouts[0]["layout"]["alignment"] != 8):
        raise ValueError("texture aggregate lacks its sole native 0x84-byte layout witness")
    field_binding(known)
    base = unique_symbol(symbols, GLOBAL, cil_owner)
    if base % 8 or TARGET % 8:
        raise ValueError("texture aggregate violates compiler storage alignment")
    writable_zero(pe, base, SIZE)
    writable_zero(target, TARGET, SIZE)
    if any(base <= at < base + SIZE for name, items in symbols.items() if name != GLOBAL for at, _ in items):
        raise ValueError("texture aggregate aliases another mapped symbol")
    refs = [{"kind": "object", "source_address": base + off, "address": TARGET + off,
             "size": 4, "symbol": GLOBAL, "addend": off} for off in sorted(FIELDS)]
    ctor = private_entry(functions, exports, CTOR, cil_owner)
    stem = GLOBAL[1:].split("@@", 1)[0] + "@@YAXXZ"
    init = private_entry(functions, exports, "??__E" + stem, cil_owner, compiler=True)
    callback = private_entry(functions, exports, "??__F" + stem, cil_owner, compiler=True)
    atexit = unique_symbol(symbols, "_atexit", "libcmt:onexit.obj")
    with (core.ROOT / "config/functions.csv").open(newline="") as stream:
        ledger = {int(r["address"], 0): r for r in csv.DictReader(stream)}
    with (core.ROOT / "config/function-origins.csv").open(newline="") as stream:
        origins = {int(r["address"], 0): r for r in csv.DictReader(stream)}
    if (ledger.get(ATEXIT, {}).get("current_name") != "_atexit"
            or (origins.get(ATEXIT, {}).get("origin"), origins.get(ATEXIT, {}).get("disposition")) != ("vc8_runtime", "exclude")
            or ledger.get(0x404FD0, {}).get("status") != "matching"
            or origins.get(0x404FD0, {}).get("disposition") != "authored"):
        raise ValueError("texture startup lacks positive CRT/normal-owner identity")
    core.decode_closed_body(read_target(ATEXIT, int(ledger[ATEXIT]["size"])), ATEXIT)
    game_range = (target.OPTIONAL_HEADER.ImageBase,
                  target.OPTIONAL_HEADER.ImageBase + target.OPTIONAL_HEADER.SizeOfImage)
    regions = []
    dtor = None
    # Both complete existing cleanup entries must freshly compare before the
    # initializer's private constructor receives any object-address bindings.
    for address, size in ((0x404FD0, 98), (0x405040, 30)):
        f = next(f for f in unit["functions"] if int(f["address"], 0) == address)
        start = core.source_function_start(f, functions, exports, cil_owner, vtables)
        if address == 0x404FD0:
            dtor = start
        body = core.linked_body(pe, functions, start)
        calls = {name: int(dst, 0) for name, dst in (m.rsplit("=", 1) for m in f.get("rel32_targets", []))}
        resolve = lambda dest: core.resolve_linked_call(dest, pe, functions, imports, calls, sdk_imports)
        code, replayed, data_refs = core.canonicalize(body, start, address, bindings, resolve,
            (core.IMAGE_BASE, core.IMAGE_BASE + pe.OPTIONAL_HEADER.SizeOfImage), game_range,
            vtables, internal_refs=internal_refs + refs)
        core.validate_body_relocations(pe, start, len(body), data_refs)
        require_bytes(code, read_target(address, size), "support body")
        regions.append({"kind": "texture support", "source_address": start, "target_address": address,
                        "size": size, "canonical_sha256": hashlib.sha256(code).hexdigest(),
                        "target_sha256": hashlib.sha256(read_target(address, size)).hexdigest(),
                        "replayed_rel32": replayed, "data_references": data_refs})
    source_init = core.linked_body(pe, functions, init)
    require_bytes(source_init, initializer_bytes(init, ctor, callback, atexit, base), "source initializer")
    core.decode_closed_body(source_init, init)
    core.validate_body_relocations(pe, init, 59, [{"field_offset": off} for off in INIT_RELOCS])
    canonical_init = initializer_bytes(INIT, 0x404F00, CALLBACK, ATEXIT, TARGET)
    require_bytes(read_target(INIT, 59), canonical_init, "target initializer")
    source_callback = core.linked_body(pe, functions, callback)
    require_bytes(source_callback, callback_bytes(callback, dtor, base), "source callback")
    core.decode_closed_body(source_callback, callback, tail=True)
    core.validate_body_relocations(pe, callback, 10, [{"field_offset": 1}])
    canonical_callback = callback_bytes(CALLBACK, 0x404FD0, TARGET)
    require_bytes(read_target(CALLBACK, 10), canonical_callback, "target callback")
    lo = unique_symbol(symbols, "___xc_a", "libcmt:crt0init.obj")
    hi = unique_symbol(symbols, "___xc_z", "libcmt:crt0init.obj")
    if hi <= lo or hi - lo > 65536:
        raise ValueError("texture CRT table bounds are invalid")
    source_slot = table_slot(core.readonly_data(pe, lo, hi - lo + 4), lo, init)
    require_bytes(rebase_data(pe, source_slot, struct.pack("<I", init), {0: (init, INIT)}),
                  core.readonly_data(target, TABLE, 4), "initializer table slot")
    for kind, at, target_at, code in (("texture initializer", init, INIT, canonical_init),
                                     ("texture callback", callback, CALLBACK, canonical_callback)):
        regions.append({"kind": kind, "source_address": at, "target_address": target_at,
                        "size": len(code), "canonical_sha256": hashlib.sha256(code).hexdigest(),
                        "target_sha256": hashlib.sha256(read_target(target_at, len(code))).hexdigest()})
    return refs, {"kind": "texture_manager_and_cache", "symbol": GLOBAL, "source_address": base,
        "target_address": TARGET, "size": SIZE, "alignment": 8, "source_constructor": ctor,
        "target_constructor": 0x404F00, "source_initializer": init, "target_initializer": INIT,
        "source_initializer_slot": source_slot, "target_initializer_slot": TABLE,
        "source_callback": callback, "target_callback": CALLBACK, "regions": regions}
