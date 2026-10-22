#!/usr/bin/env python3
"""Audit the font parser's placement-construction cleanup ownership.

Read-only static evidence. This does not qualify exception execution, matching,
or compiler/library exclusion. Build both configured font units first.
"""
from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import sys

import capstone
import pefile

import linked_pe as lp
from workflow_manifest import load_manifest, unit_input_digest

ROOT = Path(__file__).resolve().parents[1]
PARSER = 0x411FA0
STUB = 0x402810
TARGET_BODY_SHA = "6343d2d6639459aaeadb9de2acd74ecbb0be02f8a908e4b84af385f1daeccebb"


def require(condition, message):
    if not condition:
        raise ValueError(message)


def rows(decoder, code, start):
    result = list(decoder.disasm(code, start))
    require(sum(x.size for x in result) == len(code), "incomplete instruction decode")
    return result


def instructions(decoded):
    return [dict(address=hex(x.address), bytes=x.bytes.hex(),
                 mnemonic=x.mnemonic, operands=x.op_str) for x in decoded]


def action(decoder, read, address):
    result = []
    for ins in decoder.disasm(read(address, 64), address):
        result.append(ins)
        if ins.mnemonic in ("jmp", "ret"):
            return instructions(result)
    raise ValueError("unterminated cleanup action")


def funcinfo(decoder, read, address):
    raw = read(address, 36)
    fields = struct.unpack("<9I", raw)
    require(fields[0] == 0x19930522 and fields[3:8] == (0, 0, 0, 0, 0),
            "unsupported FuncInfo")
    require(0 < fields[1] <= 4, "unexpected cleanup-state count")
    states = []
    for index in range(fields[1]):
        previous, dest = struct.unpack("<iI", read(fields[2] + index * 8, 8))
        require(-1 <= previous < index and dest != 0, "unsupported unwind map")
        states.append(dict(state=index, previous=previous, address=hex(dest),
                           instructions=action(decoder, read, dest)))
    return dict(address=hex(address), bytes=raw.hex(),
                fields=[hex(x) for x in fields], states=states)


def linked_info(decoder, pe, symbols, prefix):
    starts = [a for a, names in symbols.items()
              if any(n.startswith("__ehhandler$" + prefix) for n, _ in names)]
    require(len(starts) == 1, "ambiguous linked EH handler")
    base = pe.OPTIONAL_HEADER.ImageBase
    read = lambda a, n: pe.get_data(a - base, n)
    for ins in decoder.disasm(read(starts[0], 64), starts[0]):
        ops = ins.operands
        if (ins.mnemonic == "mov" and len(ops) == 2
                and ops[0].type == capstone.x86.X86_OP_REG
                and ops[0].reg == capstone.x86.X86_REG_EAX
                and ops[1].type == capstone.x86.X86_OP_IMM):
            return funcinfo(decoder, read, ops[1].imm)
        if ins.mnemonic == "jmp":
            break
    raise ValueError("linked handler lacks FuncInfo")


def native_info(decoder, obj):
    def unique(prefix):
        found = [s for s in obj.symbols.values() if s.name.startswith(prefix)]
        require(len(found) == 1, "ambiguous native EH symbol")
        return found[0]

    info = unique("__ehfuncinfo$?parse_text_markup")
    section = obj.sections[info.section_number - 1]
    raw = obj.data[section.raw_offset + info.value:section.raw_offset + info.value + 36]
    fields = struct.unpack("<9I", raw)
    require(fields[0] == 0x19930522 and fields[1] == 4, "native parser no longer has four states")
    table = unique("__unwindtable$?parse_text_markup")
    section = obj.sections[table.section_number - 1]
    refs = {a: (obj.symbols[s], t) for i in range(section.reloc_count)
            for a, s, t in [struct.unpack_from("<IIH", obj.data, section.reloc_offset + 10 * i)]}
    states = []
    for index in range(fields[1]):
        offset = table.value + index * 8
        previous = struct.unpack_from("<i", obj.data, section.raw_offset + offset)[0]
        symbol, kind = refs[offset + 4]
        require(kind == 6, "unsupported native action-address relocation")
        code_section = obj.sections[symbol.section_number - 1]
        following = [s.value for s in obj.symbols.values()
                     if s.section_number == symbol.section_number and s.value > symbol.value]
        end = min(following) if following else code_section.raw_size
        code = obj.data[code_section.raw_offset + symbol.value:code_section.raw_offset + end]
        code_refs = [dict(offset=a - symbol.value, symbol=obj.symbols[s].name, type=t)
                     for i in range(code_section.reloc_count)
                     for a, s, t in [struct.unpack_from("<IIH", obj.data, code_section.reloc_offset + 10 * i)]
                     if symbol.value <= a < end]
        states.append(dict(state=index, previous=previous, symbol=symbol.name,
                           instructions=instructions(rows(decoder, code, symbol.value)), references=code_refs))
    require([x["previous"] for x in states] == [-1, 0, 1, 0], "unexpected native cleanup graph")
    require([x["symbol"] for x in states[2]["references"]] == ["??3@YAXPAX0@Z"],
            "native construction cleanup is not two-argument placement delete")
    return dict(bytes=raw.hex(), fields=[hex(x) for x in fields], states=states)


def audit():
    c = lp.comparator()
    target_sha = c.verify_target()
    manifest = load_manifest()
    native_name = "gpt-web-text-font-render"
    linked_name = "gpt-web-text-font-color-linked"
    native = manifest["units"][native_name]
    linked = manifest["units"][linked_name]
    obj_path = ROOT / native["object"]
    provenance = json.loads(obj_path.with_suffix(".obj.provenance.json").read_text())
    require(provenance["unit"] == native_name
            and provenance["target_sha256"] == target_sha
            and provenance["object_sha256"] == lp.sha(obj_path)
            and provenance["source_sha256"] == lp.sha(ROOT / native["source"])
            and provenance["input_digest"] == unit_input_digest(native_name, native)[0],
            "stale native artifact; rebuild the configured unit")
    # This also attests the actual renderer -> parser -> color path and inputs.
    accepted = lp.compare_linked(linked_name, linked, {"0x00411790"})
    require(len(accepted) == 1 and accepted[0]["result"] == "exact", "linked context failed validation")
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    raw = c.target_bytes(PARSER, 1744)
    require(hashlib.sha256(raw).hexdigest() == TARGET_BODY_SHA, "unexpected target parser bytes")
    target_rows = rows(decoder, raw, PARSER)
    require([(x.address, x.op_str) for x in target_rows if x.mnemonic == "ret"] == [(0x41266D, "8")],
            "unexpected target return ABI")
    target_info = funcinfo(decoder, c.target_bytes, 0x6E49EC)
    require([x["previous"] for x in target_info["states"]] == [-1, 0, 1, 0], "unexpected target cleanup graph")
    require(target_info["states"][2]["instructions"][-3]["operands"] == hex(STUB),
            "target placement cleanup calls another address")
    require(c.target_bytes(STUB, 16) == b"\xc3" + b"\xcc" * 15, "cleanup is not a padded RET")

    spec = importlib.util.spec_from_file_location("font_cleanup_coff", ROOT / "scripts/compare-giant-action-switches.py")
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    native_eh = native_info(decoder, module.CoffObject(obj_path))
    contract = next(f for f in native["functions"] if f["address"] == "0x00411FA0")
    native_root = module.CoffObject(obj_path, symbol_base=contract["symbol_base"])
    native_code = c.coff_symbol_bytes(
        obj_path, contract["symbol_base"], PARSER, len(native_root.text),
        {s: int(a, 0) for s, a in (x.split("=", 1) for x in contract["rel32_targets"])},
        c.known_data_targets(), dict(x.split("=", 1) for x in contract["dir32_targets"]))
    native_rows = rows(decoder, native_code, PARSER)
    require([x.op_str for x in native_rows if x.mnemonic == "ret"] == ["8"],
            "native return ABI changed")
    image_path = ROOT / linked["object"]
    image = pefile.PE(str(image_path))
    symbols = lp.parse_map(image_path.with_suffix(".map").read_text())

    def start(prefix):
        addresses = [a for a, ns in symbols.items() if any(n.startswith(prefix) for n, _ in ns)]
        require(len(addresses) == 1, "ambiguous linked function")
        return addresses[0]

    parser_start = start("?parse_text_markup@")
    push_start = start("?push_back@?$deque@")
    parser_raw = lp.linked_body(image, symbols, parser_start)
    parser_rows = rows(decoder, parser_raw, parser_start)
    calls = [x for x in parser_rows if x.mnemonic == "call"
             and x.operands[0].type == capstone.x86.X86_OP_IMM and x.operands[0].imm == push_start]
    require(len(calls) == 1, "parser does not call the outlined push_back once")
    parser_eh = linked_info(decoder, image, symbols, "?parse_text_markup@")
    push_eh = linked_info(decoder, image, symbols, "?push_back@?$deque@")
    require([x["previous"] for x in parser_eh["states"]] == [-1, 0, 0], "unexpected CIL parser graph")
    require([x["previous"] for x in push_eh["states"]] == [-1], "unexpected CIL push_back graph")
    delete_start = start("??3@YAXPAX0@Z")
    push_action = push_eh["states"][0]["instructions"]
    require(len(push_action) == 1 and push_action[0]["mnemonic"] == "jmp"
            and push_action[0]["operands"] == hex(delete_start),
            "push_back cleanup does not tail-call placement delete")
    require(lp.linked_body(image, symbols, delete_start) == b"\xc3", "linked placement delete is not empty")

    target_pe = pefile.PE(str(c.TARGET))
    direct, pointers = [], []
    for section in target_pe.sections:
        data = section.get_data()
        base = target_pe.OPTIONAL_HEADER.ImageBase + section.VirtualAddress
        name = section.Name.rstrip(b"\0").decode("ascii")
        if name == ".text":
            for i in range(len(data) - 4):
                if data[i] in (0xE8, 0xE9) and base + i + 5 + struct.unpack_from("<i", data, i + 1)[0] == STUB:
                    address = base + i
                    require(data[i:i+1] == b"\xe8" and data[i+5:i+9] == b"\x83\xc4\x08\xc3", "unreviewed direct stub reference")
                    prefixes = []
                    for size in (8, 11, 14):
                        prefix = list(decoder.disasm(c.target_bytes(address - size, size), address - size))
                        if [(x.mnemonic, x.op_str.split(",")[0]) for x in prefix] == [
                                ("mov", "eax"), ("push", "eax"), ("mov", "ecx"), ("push", "ecx")]:
                            prefixes.append(prefix)
                    require(len(prefixes) == 1, "unreviewed two-argument cleanup prefix")
                    direct.append(dict(call=hex(address), instructions=instructions(prefixes[0]) + instructions(rows(decoder, data[i:i+9], address))))
        for i in range(len(data) - 3):
            if struct.unpack_from("<I", data, i)[0] == STUB:
                pointers.append(dict(section=name, address=hex(base+i)))
    require(pointers == [dict(section=".rdata", address="0x6d6a74")], "unreviewed absolute stub reference")
    col = struct.unpack("<I", c.target_bytes(0x6D6A5C, 4))[0]
    col_fields = struct.unpack("<5I", c.target_bytes(col, 20))
    type_name = c.target_bytes(col_fields[3] + 8, 64).split(b"\0", 1)[0].decode("ascii")
    require(type_name == ".?AVCDesignObjectBase@@", "shared virtual owner changed")
    return dict(target_sha256=target_sha, source_sha256=lp.sha(ROOT / native["source"]),
                target_parser=dict(address=hex(PARSER), size=len(raw), sha256=TARGET_BODY_SHA,
                    construction=instructions([x for x in target_rows if 0x412102 <= x.address < 0x41213A]),
                    handler=instructions(rows(decoder, c.target_bytes(0x6BE2A8, 46), 0x6BE2A8)), eh=target_info),
                native=dict(object=str(obj_path.relative_to(ROOT)), sha256=lp.sha(obj_path),
                    main_size=len(native_code), canonical_sha256=hashlib.sha256(native_code).hexdigest(),
                    first_mismatch=c.first_mismatch(raw, native_code, PARSER), eh=native_eh),
                cil=dict(image=str(image_path.relative_to(ROOT)), sha256=lp.sha(image_path),
                    parser_size=len(parser_raw), parser_eh=parser_eh, push_back_start=hex(push_start),
                    push_back_call=hex(calls[0].address), push_back_eh=push_eh, placement_delete=hex(delete_start),
                    accepted_color_context=accepted[0]),
                stub=dict(address=hex(STUB), direct_cleanups=direct, pointers=pointers,
                    shared_vtable=dict(start="0x6d6a60", slot=5, col=hex(col), type_name=type_name),
                    origin_decision="keep review; placement-delete and authored virtual share the same byte"),
                headers={name: lp.sha(ROOT / ".tools/msvc80-sp1/include" / name) for name in ("new", "xmemory", "deque")},
                scope="static construction/cleanup ownership only; no EH execution, byte equivalence, original TU, exclusion or new exact claim")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()
    try:
        result = audit()
    except (OSError, KeyError, TypeError, ValueError, struct.error) as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 1
    if args.json:
        print(json.dumps(result, indent=2))
    else:
        print("markup cleanup: target/native four states; CIL parser three + outlined push_back one")
        print(f"0x402810: {len(result['stub']['direct_cleanups'])} two-argument cleanups and CDesignObjectBase slot5; keep origin review")
        print(result["scope"])
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
