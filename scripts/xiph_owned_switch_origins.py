"""Whole original SDK code-plus-switch proof; no masked/prefix acceptance.

Separate from the old Xiph fingerprints: their no-relocations-after-code-boundary
rule remains unchanged. This path owns and compares every suffix-table byte.
"""
import hashlib
import json
from pathlib import Path
import struct
import tomllib
import capstone
from capstone.x86 import X86_OP_IMM, X86_OP_MEM, X86_OP_REG
import linked_pe as core

ROOT = Path(__file__).resolve().parents[1]
SYMBOL = "_vorbis_book_decodev_add"
HELPERS = {"_oggpack_look": 0x006B6B30, "_oggpack_adv": 0x006B6BE0,
           "_bitreverse": 0x00681640}


PROOFS = {
    SYMBOL: dict(address="0x00681C70", size=880, object="codebook.obj",
                 targets=HELPERS, layout=None, data={}),
    "_floor1_look": dict(address="0x00687790", size=514, object="floor1.obj",
        targets={"_calloc":0x0068D318, "_qsort":0x0068DD10},
        layout=dict(table_offset=516, table_count=4, prefix=b"\x8b\xff",
                    suffix=b"\x90"*12,
                    absolute_fields={121:(0x006879B0,"callback")}),
        data={"_icomp":(0x006879B0,21)}),
    "_floor1_encode": dict(address="0x00688620", size=1497, object="floor1.obj",
        targets={"_render_point":0x00687E90, "_oggpack_write":0x006B69B0,
                 "_ilog":0x00688C10, "_vorbis_book_encode":0x00681900,
                 "_render_line0":0x00688C20},
        layout=dict(table_offset=1500, table_count=4, prefix=b"\x8d\x49\x00",
                    suffix=b"\x90"*4,
                    absolute_fields={1396:(0x006FD3A0,"counter"),
                                     1404:(0x006FD3A0,"counter"),
                                     1474:(0x006FD3A0,"counter"),
                                     1482:(0x006FD3A0,"counter")}),
        data={"_?seq@?1??floor1_encode@@9@9":(0x006FD3A0,4)}),
}


def qualify(raw, canonical, native, base, code_size, relocations, targets, layout=None):
    if len(raw) != len(canonical) or canonical != native:
        raise ValueError("whole SDK payload differs")
    if layout is None:
        layout = dict(table_offset=code_size, table_count=8, prefix=b"", suffix=b"",
                      absolute_fields={})
    table_offset, count = layout["table_offset"], layout["table_count"]
    absolute = layout["absolute_fields"]
    if (code_size < 24 or count not in (4,8)
            or table_offset != code_size + len(layout["prefix"])
            or (base + table_offset) % 4
            or len(raw) != table_offset + count*4 + len(layout["suffix"])
            or layout["prefix"] not in (b"", b"\x8b\xff", b"\x8d\x49\x00")
            or any(b != 0x90 for b in layout["suffix"])
            or canonical[code_size:table_offset] != layout["prefix"]
            or canonical[table_offset+count*4:] != layout["suffix"]):
        raise ValueError("expected complete code followed by eight owned or four owned dwords and exact alignment")
    if len(relocations) != len(set(relocations)):
        raise ValueError("duplicate relocations")
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    ins = list(md.disasm(canonical[:code_size], base))
    if sum(i.size for i in ins) != code_size or ins[-1].mnemonic != "ret":
        raise ValueError("code extent does not close at RET")
    starts = {i.address: i for i in ins}
    tables = [i for i in ins if i.mnemonic == "jmp"
              and len(i.operands) == 1 and i.operands[0].type == X86_OP_MEM]
    if len(tables) != 1:
        raise ValueError("expected one owned switch dispatch")
    dispatch = tables[0]
    pos = ins.index(dispatch)
    if pos < 2:
        raise ValueError("missing switch guard")
    cmp, guard = ins[pos - 2:pos]
    mem = dispatch.operands[0].mem
    if (mem.base or not mem.index or mem.scale != 4
            or mem.disp != base + table_offset
            or dispatch.disp_size != 4
            or cmp.mnemonic != "cmp" or len(cmp.operands) != 2
            or cmp.operands[0].type != X86_OP_REG
            or cmp.operands[0].reg != mem.index
            or cmp.operands[1].type != X86_OP_IMM
            or cmp.operands[1].imm != count-1
            or guard.mnemonic != "ja"):
        raise ValueError("switch needs the adjacent unsigned eight-entry guard")
    entries = struct.unpack_from("<"+str(count)+"I", canonical, table_offset)
    if any(a not in starts for a in entries):
        raise ValueError("switch entry escapes code or enters an instruction")
    expected_dir32 = {dispatch.address - base + dispatch.disp_offset}
    expected_dir32.update(range(table_offset, table_offset+count*4, 4))
    expected_dir32.update(absolute)
    dir32 = {a for a, t in relocations if t == 6}
    rel32 = {a for a, t in relocations if t == 20}
    if any(t not in (6, 20) for _, t in relocations) or dir32 != expected_dir32:
        raise ValueError("unowned DIR32 or relocation kind")
    for offset, (target, kind) in absolute.items():
        owners = [i for i in ins if i.address-base <= offset < i.address-base+i.size]
        if len(owners) != 1 or struct.unpack_from("<I",canonical,offset)[0] != target:
            raise ValueError("absolute source role does not bind its declared target")
        i=owners[0]
        if kind == "callback":
            if (i.mnemonic != "push" or i.bytes[0] != 0x68 or i.size != 5
                    or offset != i.address-base+1):
                raise ValueError("callback is not the complete immediate pointer argument")
        elif kind == "counter":
            if (i.mnemonic != "mov" or i.disp_size != 4
                    or offset != i.address-base+i.disp_offset
                    or not any(op.type == X86_OP_MEM and op.mem.base == 0
                               and op.mem.index == 0 and op.size == 4 for op in i.operands)):
                raise ValueError("counter is not a complete absolute DWORD load/store")
        else:
            raise ValueError("unsupported absolute role")
    actual_calls = set()
    graph = {}
    for i in ins:
        nxt = i.address + i.size
        for operand in i.operands:
            if (operand.type == X86_OP_MEM and not operand.mem.base
                    and not (i.mnemonic == "lea" and operand.mem.index)):
                if (operand.mem.disp and i.address != dispatch.address
                        and i.address-base+i.disp_offset not in absolute):
                    raise ValueError("unexpected absolute memory reference")
        if i.mnemonic == "call":
            if (len(i.operands) != 1 or i.operands[0].type != X86_OP_IMM
                    or i.bytes[0] != 0xE8 or i.size != 5
                    or i.operands[0].imm not in set(targets.values())):
                raise ValueError("unproved external call")
            actual_calls.add(i.address - base + 1)
            successors = [nxt]
        elif i.mnemonic == "ret":
            if i.operands:
                raise ValueError("unexpected return cleanup")
            successors = []
        elif i.address == dispatch.address:
            successors = list(entries)
        elif i.group(capstone.CS_GRP_JUMP):
            if len(i.operands) != 1 or i.operands[0].type != X86_OP_IMM:
                raise ValueError("unowned indirect branch")
            successors = [i.operands[0].imm]
            if i.mnemonic != "jmp":
                successors.append(nxt)
        else:
            successors = [nxt]
        if any(a not in starts for a in successors):
            raise ValueError("branch escapes code or enters an instruction")
        graph[i.address] = successors
    if actual_calls != rel32:
        raise ValueError("REL32 fields differ from complete call inventory")
    for dest, predecessor in [(guard.address, cmp.address),
                              (dispatch.address, guard.address)]:
        if {a for a, edges in graph.items() if dest in edges} != {predecessor}:
            raise ValueError("switch guard can be bypassed")
    covered = set()
    for a, _ in relocations:
        if a < 0 or a + 4 > len(raw) or covered.intersection(range(a, a + 4)):
            raise ValueError("overlapping or out-of-bounds link fields")
        covered.update(range(a, a + 4))
    if any(raw[i] != canonical[i] for i in range(len(raw)) if i not in covered):
        raise ValueError("canonicalization modified non-link bytes")
    reached, pending = set(), [base]
    while pending:
        a = pending.pop()
        if a in reached:
            continue
        reached.add(a)
        pending.extend(graph[a])
    # Every byte is compared, including compiler alignment. Report unreachable
    # decoded instructions rather than silently deleting them from the extent.
    return dict(code_bytes=code_size, payload_bytes=len(raw),
                instructions=len(ins), reachable_instructions=len(reached),
                code_sha256=hashlib.sha256(canonical[:code_size]).hexdigest(),
                payload_sha256=hashlib.sha256(canonical).hexdigest(),
                call_sites=len(actual_calls), table_entries=list(entries), table_offset=table_offset,
                alignment_bytes=len(layout["prefix"])+len(layout["suffix"]),
                masked_bytes=0, unequal_bytes=0)


def zero_initialized_counter(pe, address, size):
    if size != 4:
        raise ValueError("counter must be one DWORD")
    rva = address - pe.OPTIONAL_HEADER.ImageBase
    sections = [s for s in pe.sections
                if s.VirtualAddress + s.SizeOfRawData <= rva
                and rva + size <= s.VirtualAddress + s.Misc_VirtualSize]
    if (len(sections) != 1 or not sections[0].Characteristics & 0x80000000
            or sections[0].Characteristics & 0x20000000):
        raise ValueError("counter must occupy the non-executable writable zero-fill tail")
    return b"\0" * size


def validate(rule, selected, rows, read_pe, origins):
    try:
        spec = rule["xiph_owned_switch"]
        identity = PROOFS.get(spec.get("symbol"), {})
        if (set(spec) != {"component", "object", "symbol", "address", "size",
                         "payload_sha256"}
                or spec["component"] != "vorbis" or spec["object"] != identity.get("object")
                or spec["symbol"] not in PROOFS or spec["address"] != identity.get("address")
                or type(spec["size"]) is not int or spec["size"] != identity.get("size")
                or len(selected) != 1 or selected[0]["address"] != spec["address"]
                or int(selected[0]["size"], 0) != spec["size"]):
            raise ValueError("unsupported original SDK switch identity or extent")
        module = origins.load_xiph_sdk_module()
        sdk = (ROOT / ".tools/upstream/OggVorbis-win32sdk-1.0.1.zip").read_bytes()
        if hashlib.sha256(sdk).hexdigest() != module.ARCHIVE_SHA256:
            raise ValueError("original SDK archive hash differs")
        # Revalidate the independent, pre-existing origin anchors used for all
        # three callees. No arbitrary source-name-to-target overrides are read.
        rules = tomllib.loads(origins.RULES.read_text())["rules"]
        helper_origins = []
        for key, validator in [
            ("xiph_anchor_file", origins.validate_xiph_anchor_evidence),
            ("xiph_relocated_anchor_file", origins.validate_xiph_relocated_anchor_evidence),
        ]:
            deps = [r for r in rules if r.get(key)]
            if len(deps) != 1:
                raise ValueError("independent Xiph origin rule is missing/ambiguous")
            dep = deps[0]
            errors = validator(dep, origins.select(dep, rows), rows, read_pe)
            if errors:
                raise ValueError("independent Xiph origin replay failed: " + "; ".join(errors))
            helper_origins += tomllib.loads((ROOT / dep[key]).read_text())["anchors"]
        helpers = {name:address for name,address in identity["targets"].items()
                   if name not in ("_calloc","_qsort")}
        helpers.update({name:address for name,(address,size) in identity["data"].items()
                        if name == "_icomp"})
        for symbol, address in helpers.items():
            found = [a for a in helper_origins if a["symbol"] == symbol]
            if len(found) != 1 or int(found[0]["address"], 0) != address:
                raise ValueError("external callee identity differs")
        crt = {name:address for name,address in identity["targets"].items()
               if name in ("_calloc","_qsort")}
        if crt:
            defined = origins.load_msvc_archive_symbols()
            census = {r["address"]:r for r in origins.read_csv(origins.OUTPUT)}
            by_address = {r["address"]:r for r in rows}
            for name,address in crt.items():
                key = f"0x{address:08X}"
                if (name not in defined or by_address.get(key,{}).get("current_name") != name
                        or census.get(key,{}).get("evidence_id") != "vc8-pinned-archive-symbols-106a"):
                    raise ValueError("independent pinned CRT callee identity differs")
        obj = module.extract_object(sdk, spec["component"], spec["object"])
        raw, relocs = origins.xiph_relocated_text(obj, spec["symbol"])
        out = ROOT / "build/origin-anchors/xiph-owned-switch" / spec["symbol"].lstrip("_")
        out.mkdir(parents=True, exist_ok=True)
        path = out / spec["object"]
        path.write_bytes(obj)
        c = core.comparator()
        c.verify_target()
        address = int(spec["address"], 0)
        data = {}
        for name,(target,size) in identity["data"].items():
            if name == "_icomp":
                literal = read_pe(target,size)
            else:
                import pefile
                pe = pefile.PE(data=c.TARGET.read_bytes(), fast_load=True)
                literal = zero_initialized_counter(pe,target,size)
                if c.target_bytes(target,size) != literal:
                    raise ValueError("loaded static counter differs from proved zero-fill")
            if name != "_icomp" and literal != b"\0"*4:
                raise ValueError("original static counter initial image differs")
            # Literal validation also checks the original defined SDK section,
            # including the entire relocation-free callback, never a name alone.
            data[name] = (target,literal,frozenset({0}),"literal")
        canonical = c.coff_symbol_bytes(path, spec["symbol"], address, 0xffffffff,
                                        identity["targets"], data)
        proof = qualify(raw, canonical, read_pe(address, len(raw)), address,
                        spec["size"], relocs, identity["targets"], identity["layout"])
        if proof["payload_sha256"] != spec["payload_sha256"]:
            raise ValueError("complete payload hash differs")
        matches = []
        for row in rows:
            if int(row["size"], 0) != spec["size"]:
                continue
            other = int(row["address"], 0)
            rebound = c.coff_symbol_bytes(path, spec["symbol"], other, 0xffffffff, identity["targets"], data)
            if rebound == read_pe(other, len(rebound)):
                matches.append(row["address"])
        if matches != [spec["address"]]:
            raise ValueError("SDK complete-payload inventory uniqueness differs")
        proof.update(sdk_sha256=module.ARCHIVE_SHA256,
                     object_sha256=hashlib.sha256(obj).hexdigest(),
                     validator_sha256=hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
                     inventory_matches=matches, helper_targets=identity["targets"],
                     data_targets={k:v[:2] for k,v in identity["data"].items()},
                     target_sha256=str(origins.target_manifest()["target"]["sha256"]))
        (out / "proof.json").write_text(json.dumps(proof, indent=2) + "\n")
        return []
    except (OSError, ValueError, KeyError, TypeError, IndexError, struct.error) as exc:
        return [str(rule["id"]) + ": " + str(exc)]


def main():
    import importlib.util
    spec = importlib.util.spec_from_file_location("origin_rules", ROOT / "scripts/function-origins.py")
    origins = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(origins)
    document = tomllib.loads(origins.RULES.read_text())
    import argparse
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("rule", nargs="?", default="xiph-sdk-owned-switch-106a")
    args = parser.parse_args()
    rule = next(r for r in document["rules"] if r["id"] == args.rule)
    rows = origins.read_csv(origins.FUNCTIONS)
    target = origins.attest_target(document)
    errors = validate(rule, origins.select(rule, rows), rows, origins.pe_reader(target), origins)
    print(json.dumps(dict(rule=rule["id"], errors=errors), indent=2))
    return int(bool(errors))


if __name__ == "__main__":
    raise SystemExit(main())
