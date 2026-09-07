"""Instruction/edge diagnostics for giant roots; never exact-match acceptance.

Only relative control-flow operands and proved switch-table addresses are
normalized. Opcodes, operand widths, registers, external targets, and the
identity AND intra-owner offset of every internal edge remain significant.
"""
from __future__ import annotations

from bisect import bisect_right
from collections import deque
from difflib import SequenceMatcher
from typing import Any

from capstone import Cs, CS_ARCH_X86, CS_MODE_32, CS_GRP_CALL, CS_GRP_JUMP, CS_GRP_RET
from capstone.x86_const import X86_INS_JMP, X86_OP_IMM, X86_OP_MEM


def decode(code: bytes, address: int) -> list[Any]:
    if not code:
        raise ValueError("empty callable instruction span")
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    instructions = list(decoder.disasm(code, address))
    if sum(insn.size for insn in instructions) != len(code):
        consumed = sum(insn.size for insn in instructions)
        raise ValueError(f"incomplete instruction decode at {address + consumed:#x}")
    return instructions


def owner_at(offset: int, owners: dict[int, str]) -> tuple[str, int]:
    starts = sorted(owners)
    index = bisect_right(starts, offset) - 1
    if index < 0:
        raise ValueError(f"instruction/edge at {offset:#x} precedes all owners")
    start = starts[index]
    return owners[start], offset - start


def signature(
    insn: Any,
    base: int,
    code_size: int,
    owners: dict[int, str],
    boundaries: set[int],
    tables: list[tuple[int, int, str]],
) -> tuple[str, tuple[Any, ...] | None]:
    raw = bytearray(insn.bytes)
    identity: tuple[Any, ...] | None = None
    if (insn.group(CS_GRP_JUMP) or insn.group(CS_GRP_CALL)) and insn.operands[0].type == X86_OP_IMM:
        destination = insn.operands[0].imm & 0xFFFFFFFF
        if base <= destination < base + code_size:
            if destination not in boundaries:
                raise ValueError(f"edge {insn.address:#x} enters an instruction at {destination:#x}")
            identity = ("owner", *owner_at(destination - base, owners))
        else:
            identity = ("external", destination)
        if insn.imm_size not in (1, 2, 4):
            raise ValueError(f"unsupported relative operand width at {insn.address:#x}")
        raw[insn.imm_offset : insn.imm_offset + insn.imm_size] = bytes(insn.imm_size)
    elif insn.disp_size == 4:
        for operand in insn.operands:
            if operand.type != X86_OP_MEM:
                continue
            displacement = operand.mem.disp & 0xFFFFFFFF
            matches = [(start, name) for start, end, name in tables if start <= displacement < end]
            if len(matches) > 1:
                raise ValueError("overlapping switch-table identity ranges")
            if matches:
                start, name = matches[0]
                identity = ("switch_table", name, displacement - start)
                raw[insn.disp_offset : insn.disp_offset + 4] = bytes(4)
    return raw.hex(), identity


def paired_owners(rows: list[dict[str, Any]]) -> list[dict[str, Any]]:
    """Collapse cross-region default aliases, but reject splits and merges."""
    pairs: dict[int, dict[str, Any]] = {}
    reverse: dict[int, int] = {}
    for row in rows:
        if row["split"] or len(row["candidate_offsets"]) != 1:
            raise ValueError("instruction audit requires unsplit target owner groups")
        target = row["target_offset"]
        candidate = row["candidate_offsets"][0]
        if candidate in reverse and reverse[candidate] != target:
            raise ValueError("candidate merges distinct target physical owners")
        reverse[candidate] = target
        label = f"{row['region']}:{row['cases'][0]}"
        if target in pairs:
            prior = pairs[target]
            if (prior["candidate_offset"], prior["target_span"], prior["candidate_span"]) != (
                candidate, row["target_span"], row["candidate_span"]
            ):
                raise ValueError("inconsistent cross-region owner alias")
            prior["aliases"].append(label)
        else:
            pairs[target] = dict(
                name=label, aliases=[label], target_offset=target,
                candidate_offset=candidate, target_span=row["target_span"],
                candidate_span=row["candidate_span"],
            )
    if not pairs or min(pairs) <= 0 or min(reverse) <= 0:
        raise ValueError("expected a nonempty dispatcher before the switch owners")
    pairs[0] = dict(name="entry", aliases=["entry"], target_offset=0,
                    candidate_offset=0, target_span=min(pairs), candidate_span=min(reverse))
    return [pairs[offset] for offset in sorted(pairs)]


def compare_owner_instructions(
    target: bytes, candidate: bytes, address: int,
    pairs: list[dict[str, Any]],
    target_tables: list[tuple[int, int, str]],
    candidate_tables: list[tuple[int, int, str]],
) -> list[dict[str, Any]]:
    sides = []
    for code, side, tables in ((target, "target", target_tables), (candidate, "candidate", candidate_tables)):
        instructions = decode(code, address)
        cursor = 0
        for pair in sorted(pairs, key=lambda item: item[f"{side}_offset"]):
            if pair[f"{side}_offset"] != cursor or pair[f"{side}_span"] <= 0:
                raise ValueError(f"{side} owners do not partition the callable")
            cursor += pair[f"{side}_span"]
        if cursor != len(code):
            raise ValueError(f"{side} owners do not partition the callable")
        boundaries = {insn.address for insn in instructions}
        owners = {pair[f"{side}_offset"]: pair["name"] for pair in pairs}
        tokens = {insn.address: signature(insn, address, len(code), owners, boundaries, tables) for insn in instructions}
        sides.append((instructions, tokens))
    results = []
    for pair in pairs:
        spans = []
        for side, (instructions, tokens) in zip(("target", "candidate"), sides):
            start = address + pair[f"{side}_offset"]
            end = start + pair[f"{side}_span"]
            if end > address + len(target if side == "target" else candidate):
                raise ValueError(f"{side} owner {pair['name']} escapes callable bytes")
            selected = [insn for insn in instructions if start <= insn.address < end]
            if sum(insn.size for insn in selected) != end - start:
                raise ValueError(f"{side} owner {pair['name']} cuts an instruction")
            spans.append((selected, [tokens[insn.address] for insn in selected]))
        (ti, tt), (ci, ct) = spans
        differences = []
        for tag, a, b, c, d in SequenceMatcher(None, tt, ct, autojunk=False).get_opcodes():
            if tag != "equal":
                differences.append({
                    "kind": tag,
                    "target": [f"+0x{x.address-address:04X} {x.mnemonic} {x.op_str}" for x in ti[a:b]],
                    "candidate": [f"+0x{x.address-address:04X} {x.mnemonic} {x.op_str}" for x in ci[c:d]],
                })
        results.append({**pair, "target_instructions": len(ti), "candidate_instructions": len(ci),
                        "instruction_edge_identical": tt == ct, "differences": differences})
    return results


def reachable_boundary_audit(
    code: bytes, address: int, switch_destinations: dict[int, tuple[str, list[int]]],
) -> dict[str, Any]:
    """Traverse raw code from its entry, not IDA extents or a scan for E8 bytes.

Known byte-index switches are expanded from target-validated destination tables.
Register-indirect exits remain explicitly unresolved; no target is invented.
External calls are recorded but their bodies are outside this bounded audit.
"""
    instructions = decode(code, address)
    by_address = {insn.address: insn for insn in instructions}
    pending = deque([address])
    visited: set[int] = set()
    external: dict[int, list[dict[str, Any]]] = {}
    internal_calls: set[int] = set()
    indirect_exits = []
    switches = []
    end = address + len(code)

    def enqueue(destination: int) -> None:
        if destination not in by_address:
            raise ValueError(f"reachable edge/fallthrough is not a callable instruction: {destination:#x}")
        if destination not in visited:
            pending.append(destination)

    while pending:
        current = pending.popleft()
        if current in visited:
            continue
        insn = by_address[current]
        visited.add(current)
        jump = insn.group(CS_GRP_JUMP)
        call = insn.group(CS_GRP_CALL)
        if jump or call:
            operand = insn.operands[0]
            if operand.type == X86_OP_IMM:
                destination = operand.imm & 0xFFFFFFFF
                if address <= destination < end:
                    enqueue(destination)
                    if call:
                        internal_calls.add(destination)
                else:
                    external.setdefault(destination, []).append({"address": current, "kind": "call" if call else "jump"})
            elif jump:
                table = None
                if operand.type == X86_OP_MEM and operand.mem.base == 0 and operand.mem.index and operand.mem.scale == 4:
                    table = switch_destinations.get(operand.mem.disp & 0xFFFFFFFF)
                if table is not None:
                    name, destinations = table
                    for destination in destinations:
                        enqueue(destination)
                    switches.append({"address": current, "table": name, "destinations": len(set(destinations))})
                else:
                    indirect_exits.append({"address": current, "instruction": f"{insn.mnemonic} {insn.op_str}"})
        if not insn.group(CS_GRP_RET) and insn.id != X86_INS_JMP:
            enqueue(current + insn.size)
    unvisited = []
    for insn in instructions:
        if insn.address not in visited:
            if unvisited and unvisited[-1][1] == insn.address:
                unvisited[-1][1] += insn.size
            else:
                unvisited.append([insn.address, insn.address + insn.size])
    return {
        "decoded_instructions": len(instructions), "decoded_bytes": len(code),
        "reachable_instructions": len(visited),
        "reachable_bytes": sum(by_address[value].size for value in visited),
        "unreached_ranges": unvisited,
        "direct_external_targets": [{"address": target, "sites": sites} for target, sites in sorted(external.items())],
        "internal_call_targets": sorted(internal_calls),
        "switch_jumps": switches, "unresolved_indirect_exits": indirect_exits,
        "scope": "bounded root; indirect exits and external callee bodies are not classified by this traversal",
    }
