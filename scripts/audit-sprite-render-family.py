#!/usr/bin/env python3
"""Replay canonical CSprite render boundaries and the two vslot bodies.

This is target evidence only. Equal target-relative instruction topology does
not grant source, library-origin, or canonical compiler-match credit.
"""
from __future__ import annotations

from collections import deque
import hashlib
import importlib.util
import json
from pathlib import Path
import struct

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]
ROOTS = (
    (0x406BE0, 0x6C0684, 0x144,
     "fa3b6f746fe5529b57abb6f24113ce3f6c33c54f781f975db13b7b89ccc829bf"),
    (0x406E50, 0x6C0688, 0x4142,
     "6c528e876bc6405bec90252d098e7964d2d3817159e098838b794500ffa8a5be"),
)


def require(condition: bool, message: str) -> None:
    if not condition:
        raise ValueError(message)


def main() -> None:
    spec = importlib.util.spec_from_file_location("sprite_typed", ROOT / "scripts/typed-re.py")
    require(spec is not None and spec.loader is not None, "missing local PE helpers")
    typed = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(typed)
    data, manifest = typed.verify_local_target()

    def mapped(address: int, size: int) -> bytes:
        return typed.target_bytes(data, address, size)

    def dword(address: int) -> int:
        return struct.unpack("<I", mapped(address, 4))[0]

    require(dword(0x40ADAB) == 0x6C0668, "CSprite ctor vptr publication changed")
    call = mapped(0x43F9FF, 5)
    require(call[0] == 0xE8 and 0x43FA04 + struct.unpack_from("<i", call, 1)[0] == 0x406BE0,
            "Menu::render_cursor direct edge changed")
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    roots, normalized = [], []
    for start, slot, fvf, expected_hash in ROOTS:
        body = mapped(start, 610)
        require(hashlib.sha256(body).hexdigest() == expected_hash, "render body hash changed")
        require(dword(slot) == start, "CSprite primary-vtable slot changed")
        require(mapped(start + 610, 14) == b"\xCC" * 14, "post-return padding changed")
        instructions = list(decoder.disasm(body, start))
        require(sum(i.size for i in instructions) == 610, "incomplete linear decode")
        by_address = {i.address: i for i in instructions}
        pending, seen = deque([start]), set()
        while pending:
            address = pending.popleft()
            if address in seen:
                continue
            require(address in by_address, "edge is not an instruction start")
            seen.add(address)
            insn = by_address[address]
            if insn.mnemonic.startswith("ret"):
                require(int(insn.op_str, 0) == 8, "unexpected return ABI")
                continue
            if insn.mnemonic.startswith("j"):
                destination = int(insn.op_str, 16)
                require(start <= destination < start + 610, "external direct jump")
                pending.append(destination)
                if insn.mnemonic == "jmp":
                    continue
            pending.append(address + insn.size)
        require(seen == set(by_address), "unreached callable instructions")
        topology = []
        for insn in instructions:
            operand = insn.op_str
            if insn.mnemonic.startswith("j"):
                operand = hex(int(operand, 16) - start)
            topology.append((insn.address - start, insn.mnemonic, operand))
        normalized.append(topology)
        roots.append({
            "address": f"0x{start:08X}", "bytes": 610, "sha256": expected_hash,
            "vtable_slot": f"0x{slot:08X}", "fvf": hex(fvf),
            "reachable_instructions": len(seen),
            "x87_instructions": sum(i.mnemonic.startswith("f") for i in instructions),
            "returns": [f"0x{i.address:08X}" for i in instructions if i.mnemonic.startswith("ret")],
            "calls": [{"site": f"0x{i.address:08X}", "operand": i.op_str}
                      for i in instructions if i.mnemonic == "call"],
        })
    require(len(normalized[0]) == len(normalized[1]), "target instruction counts differ")
    differences = [(a, b) for a, b in zip(*normalized) if a != b]
    require(differences == [((0x235, "push", "0x144"), (0x235, "push", "0x4142"))],
            "target pair differs beyond the FVF immediate")
    report = {
        "evidence": "hash-attested target CFG/vtable facts; no canonical source-match credit",
        "target_sha256": manifest["target"]["sha256"], "roots": roots,
        "normalized_target_pair_differences": differences,
    }
    output = ROOT / "build/sprite-render-family-facts.json"
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(report, indent=2) + "\n")
    print("CSprite render family: 2 x 610 reachable bytes / 210 instructions; only FVF differs")


if __name__ == "__main__":
    main()
