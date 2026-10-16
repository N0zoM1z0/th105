#!/usr/bin/env python3
"""Attest the complete default-to-Aya CPU target bridge, without exact credit.

Compare encoded instructions after explicit control/data address translation.
Only two target-pinned 61-byte additions are outside the correspondence.
This compares two original PE regions, never generated reconstruction code.
"""
from __future__ import annotations

import hashlib
import importlib.util
import json
from pathlib import Path
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32, CS_GRP_CALL, CS_GRP_JUMP
from capstone.x86 import X86_OP_IMM, X86_OP_MEM

ROOT = Path(__file__).resolve().parents[1]
OLD, NEW = 0x5F1F80, 0x6126E0
OLD_SIZE, NEW_SIZE = 15910, 16032
OLD_HASH = "fb26e85839101f4dc89506c9d51a14b76c729b6836d0efe2c063d18b22c10f77"
NEW_HASH = "7efa001552238230ac86c77f48f36a217cc486e847f85cb924527c64e2dc6e09"
OLD_META, NEW_META, META_SIZE = 0x5F5DA8, 0x616580, 632
ADDITIONS = ((0x6142C0, 61), (0x61447C, 61))
TABLES = ((0x5F5DA8, 19), (0x5F5ED0, 6), (0x5F5EF8, 3),
          (0x5F5F14, 6), (0x5F5F3C, 6), (0x5F5F64, 21))


def mapped_instruction(address):
    return address + NEW - OLD + (61 if address >= 0x5F3B60 else 0) + (61 if address >= 0x5F3CDF else 0)


def mapped_entry(address):
    # Existing fallback edges enter the additions before the old continuation.
    return {0x5F3B60: 0x6142C0, 0x5F3CDF: 0x61447C}.get(address, mapped_instruction(address))


def audit():
    spec = importlib.util.spec_from_file_location("cpu_bridge_canonical", ROOT / "scripts/compare-function.py")
    canonical = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(canonical)
    target_hash = canonical.verify_target()
    old = canonical.target_bytes(OLD, OLD_SIZE)
    new = canonical.target_bytes(NEW, NEW_SIZE)
    if hashlib.sha256(old).hexdigest() != OLD_HASH or hashlib.sha256(new).hexdigest() != NEW_HASH:
        raise ValueError("CPU target callable boundary/hash differs")
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    before, after = list(decoder.disasm(old, OLD)), list(decoder.disasm(new, NEW))
    if (len(before) != 4069 or sum(i.size for i in before) != OLD_SIZE
            or len(after) != 4097 or sum(i.size for i in after) != NEW_SIZE):
        raise ValueError("CPU callable does not decode completely")
    by_address = {i.address: i for i in after}
    paired, control_operands, calls, table_operands = set(), 0, 0, 0
    for original in before:
        address = mapped_instruction(original.address)
        actual = by_address.get(address)
        if actual is None or actual.size != original.size:
            raise ValueError(f"CPU instruction boundary differs at {original.address:#x}")
        paired.add(address)
        expected = bytearray(original.bytes)
        if ((original.group(CS_GRP_JUMP) or original.group(CS_GRP_CALL))
                and original.operands[0].type == X86_OP_IMM):
            target = original.operands[0].imm
            destination = mapped_entry(target) if OLD <= target < OLD + OLD_SIZE else target
            displacement = destination - (address + actual.size)
            start, size = original.imm_offset, original.imm_size
            expected[start:start + size] = displacement.to_bytes(size, "little", signed=True)
            control_operands += 1
            calls += int(original.group(CS_GRP_CALL))
        for operand in original.operands:
            if operand.type == X86_OP_MEM and OLD_META <= operand.mem.disp < OLD_META + META_SIZE:
                start, size = original.disp_offset, original.disp_size
                expected[start:start + size] = (operand.mem.disp + NEW_META - OLD_META).to_bytes(size, "little")
                table_operands += 1
        if expected != actual.bytes:
            raise ValueError(f"CPU encoded instruction/edge differs at {original.address:#x} -> {address:#x}")
    additions = [i for i in after if i.address not in paired]
    expected_additions = {i.address for start, size in ADDITIONS
                          for i in decoder.disasm(canonical.target_bytes(start, size), start)}
    if (len(additions) != 28 or sum(i.size for i in additions) != 122
            or {i.address for i in additions} != expected_additions):
        raise ValueError("unexpected instructions outside the CPU bridge")
    metadata = bytearray(canonical.target_bytes(OLD_META, META_SIZE))
    for table, count in TABLES:
        for index in range(count):
            offset = table - OLD_META + index * 4
            destination = int.from_bytes(metadata[offset:offset + 4], "little")
            if not OLD <= destination < OLD + OLD_SIZE:
                raise ValueError("old switch destination escapes its callable")
            metadata[offset:offset + 4] = mapped_entry(destination).to_bytes(4, "little")
    if metadata != canonical.target_bytes(NEW_META, META_SIZE):
        raise ValueError("CPU switch metadata differs after destination translation")
    if (control_operands, calls, table_operands) != (1111, 150, 12):
        raise ValueError("CPU bridge operand census differs")
    return {"schema": "th105-cpu-target-bridge-v1", "evidence": "original target correspondence; no exact credit",
            "target_sha256": target_hash, "default_body_sha256": OLD_HASH, "aya_body_sha256": NEW_HASH,
            "paired_instructions": len(before), "paired_bytes": len(old),
            "control_operands": control_operands, "paired_calls": calls,
            "switch_data_operands": table_operands, "metadata_bytes": META_SIZE,
            "extra_instructions": len(additions), "extra_bytes": 122,
            "additions": [{"address": f"0x{i.address:08X}", "mnemonic": i.mnemonic, "operands": i.op_str}
                          for i in additions]}


if __name__ == "__main__":
    try:
        print(json.dumps(audit(), indent=2))
    except Exception as error:
        print(f"CPU target bridge failed: {error}", file=sys.stderr)
        raise SystemExit(2)
