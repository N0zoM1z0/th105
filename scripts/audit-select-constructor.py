#!/usr/bin/env python3
"""Compare CSelect's entire main section, remote EH code and EH metadata.

This diagnostic does not add exact credit. In particular, agreeing unwind
records cannot excuse even one different byte in the main constructor.
"""
from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import sys
import tomllib

import capstone
from workflow_manifest import load_manifest

ROOT = Path(__file__).resolve().parents[1]
UNIT = "exact-first-select-constructor"
SYMBOL = "??0CSelect@th105@@QAE@XZ"
ADDRESS, SIZE = 0x4231A0, 4247


def load_tool(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


canonical = load_tool("select_constructor_canonical", "compare-function.py")
coff_tool = load_tool("select_constructor_coff", "compare-giant-action-switches.py")


def replay_section(coff, section, base, targets, data_targets, target_reader):
    """Replay every EH-section operand; reject unsupported or overlapping fields."""
    if section.name not in {".text$x", ".xdata$x"}:
        raise ValueError("unexpected EH section kind")
    if section.characteristics & canonical.IMAGE_SCN_LNK_NRELOC_OVFL:
        raise ValueError("EH relocation overflow is unsupported")
    code = bytearray(coff._read_raw(section.raw_offset, section.raw_size))
    occupied = set()
    for index in range(section.reloc_count):
        raw = coff._read_raw(section.reloc_offset + 10 * index, 10)
        offset, symbol_index, kind = struct.unpack("<IIH", raw)
        if offset > len(code) - 4:
            raise ValueError("EH relocation escapes complete section")
        fields = set(range(offset, offset + 4))
        if fields & occupied:
            raise ValueError("overlapping EH relocation fields")
        occupied.update(fields)
        symbol = coff.symbols.get(symbol_index)
        if symbol is None:
            raise ValueError("EH relocation references missing symbol")
        name = symbol.name
        addend = struct.unpack_from("<i", code, offset)[0]
        if kind == canonical.IMAGE_REL_I386_REL32:
            if section.name != ".text$x" or canonical.rel32_operand_kind(code, offset) is None:
                raise ValueError("EH REL32 is not a code CALL/JMP/Jcc")
            key = canonical.relocation_target_key(name, targets)
            if key not in targets:
                raise ValueError("unknown EH code target: " + name)
            struct.pack_into("<i", code, offset, targets[key] + addend - (base + offset + 4))
        elif kind == canonical.IMAGE_REL_I386_DIR32:
            if name not in data_targets:
                raise ValueError("unknown EH absolute target: " + name)
            destination, literal, allowed, validation = data_targets[name]
            if validation != "address" or addend != 0 or 0 not in allowed:
                raise ValueError("unsupported EH absolute operand role/addend")
            if target_reader(destination, len(literal)) != literal:
                raise ValueError("EH absolute target pin changed")
            struct.pack_into("<I", code, offset, destination)
        else:
            raise ValueError(f"unsupported EH relocation {kind:#x}")
    return bytes(code)


def region_result(candidate, target, address):
    return dict(
        exact=candidate == target,
        target_size=len(target), candidate_size=len(candidate),
        candidate_sha256=hashlib.sha256(candidate).hexdigest(),
        target_sha256=hashlib.sha256(target).hexdigest(),
        first_mismatch=canonical.first_mismatch(target, candidate, address),
        unmasked_differing_bytes=sum(a != b for a, b in zip(candidate, target))
        + abs(len(candidate) - len(target)),
    )


def target_contract():
    rules = tomllib.loads((ROOT / "config/function-origin-rules.toml").read_text())["rules"]
    rule = next(r for r in rules if r["id"] == "select-base-constructor-authored-106a")
    eh = rule["required_vc8_eh_unwind"]
    pins = list(rule["required_body_hashes"]) + list(eh["actions"])
    for key, size in (("handler", eh["handler_size"]), ("func_info", 36), ("unwind_map", 152)):
        pins.append(dict(address=eh[key], size=size, sha256=eh[key + "_sha256"]))
    for row in pins:
        raw = canonical.target_bytes(int(row["address"], 0), row["size"])
        if hashlib.sha256(raw).hexdigest() != row["sha256"]:
            raise ValueError("reviewed target region changed: " + row["address"])
    return eh


def inventory(code):
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    instructions = list(decoder.disasm(code, ADDRESS))
    if sum(i.size for i in instructions) != len(code):
        raise ValueError("complete main decoding failed")
    calls = Counter(i.operands[0].imm for i in instructions
                    if i.mnemonic == "call" and i.operands[0].type == capstone.x86.X86_OP_IMM)
    return dict(
        instructions=len(instructions), returns=sum(i.mnemonic == "ret" for i in instructions),
        direct_calls={hex(a): n for a, n in sorted(calls.items())},
        indirect_calls=sum(i.mnemonic == "call" and i.operands[0].type != capstone.x86.X86_OP_IMM
                           for i in instructions),
    )


def audit(object_path=None):
    identity = canonical.verify_target()
    eh = target_contract()
    unit = load_manifest()["units"][UNIT]
    function = unit["functions"][0]
    if int(function["address"], 0) != ADDRESS or function["symbol_base"] != SYMBOL:
        raise ValueError("configured constructor changed")
    object_path = object_path or ROOT / unit["object"]
    targets, data = canonical.known_targets(), canonical.known_data_targets()
    for binding in function["rel32_targets"]:
        name, address = binding.rsplit("=", 1)
        targets[name] = int(address, 0)
    overrides = dict(binding.split("=", 1) for binding in function["dir32_targets"])
    main = canonical.coff_symbol_bytes(object_path, SYMBOL, ADDRESS, 0xFFFFFFFF, targets, data, overrides)
    obj = coff_tool.CoffObject(object_path, symbol_base=SYMBOL)
    counts = Counter(s.name for s in obj.symbols.values() if s.section_number > 0)
    if any(n > 1 for name, n in counts.items() if "$" + SYMBOL in name):
        raise ValueError("duplicate defined EH symbols")
    symbols = {s.name: s for s in obj.symbols.values() if s.section_number > 0}

    def defined(name):
        symbol = symbols.get(name)
        if symbol is None or not 1 <= symbol.section_number <= len(obj.sections):
            raise ValueError("missing defined EH symbol: " + name)
        return symbol

    first = defined("__unwindfunclet$" + SYMBOL + "$0")
    info = defined("__ehfuncinfo$" + SYMBOL)
    code_section = obj.sections[first.section_number - 1]
    meta_section = obj.sections[info.section_number - 1]
    if first.value != 0 or info.value != 0 or code_section.name != ".text$x" or meta_section.name != ".xdata$x":
        raise ValueError("EH source section ownership changed")
    code_base = int(eh["unwind_entries"][0]["action"], 0)
    meta_base = int(eh["func_info"], 0)
    owned = set()
    for index, row in enumerate(eh["unwind_entries"]):
        name = "__unwindfunclet$" + SYMBOL + "$" + str(index)
        symbol = defined(name)
        address = int(row["action"], 0)
        if symbol.section_number != first.section_number or code_base + symbol.value != address:
            raise ValueError("EH funclet source-to-target ownership changed")
        data[name] = (address, canonical.target_bytes(address, 1), frozenset([0]), "address")
        owned.add(name)
    actual = {n for n in symbols if n.startswith("__unwindfunclet$" + SYMBOL + "$")}
    if actual != owned:
        raise ValueError("extra or missing source unwind actions")
    for prefix, address, size, section_number, base in (
        ("__ehhandler$", int(eh["handler"], 0), eh["handler_size"], first.section_number, code_base),
        ("__ehfuncinfo$", meta_base, 36, info.section_number, meta_base),
        ("__unwindtable$", int(eh["unwind_map"], 0), 152, info.section_number, meta_base),
    ):
        name = prefix + SYMBOL
        symbol = defined(name)
        if symbol.section_number != section_number or base + symbol.value != address:
            raise ValueError("EH handler/metadata source ownership changed")
        data[name] = (address, canonical.target_bytes(address, size), frozenset([0]), "address")
    code = replay_section(obj, code_section, code_base, targets, data, canonical.target_bytes)
    metadata = replay_section(obj, meta_section, meta_base, targets, data, canonical.target_bytes)
    regions = dict(
        main=region_result(main, canonical.target_bytes(ADDRESS, SIZE), ADDRESS),
        eh_code=region_result(code, canonical.target_bytes(code_base, 461), code_base),
        eh_metadata=region_result(metadata, canonical.target_bytes(meta_base, 188), meta_base),
    )
    return dict(
        result="exact" if all(r["exact"] for r in regions.values()) else "mismatch",
        diagnostic_only=True, unit=UNIT, target_sha256=identity, regions=regions,
        all_section_relocations_replayed=True, unwind_actions=len(owned),
        target_inventory=inventory(canonical.target_bytes(ADDRESS, SIZE)),
        candidate_inventory=inventory(main),
    )


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path)
    args = parser.parse_args()
    try:
        result = audit(args.object)
    except (OSError, ValueError, RuntimeError, KeyError, StopIteration, struct.error) as error:
        print(json.dumps(dict(result="blocked", error=str(error)), indent=2))
        return 1
    print(json.dumps(result, indent=2))
    return 0 if result["result"] == "exact" else 1


if __name__ == "__main__":
    raise SystemExit(main())
