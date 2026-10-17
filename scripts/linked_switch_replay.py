"""Diagnostic relocation replay for the independently closed Iku linked CFG.

This does not relax linked_pe's accepted-unit comparator. Every byte remains
significant, including switch metadata and alignment; only proved address
fields are rewritten. The caller must first run the full linked CFG inspector.
"""

from __future__ import annotations

from collections import Counter
import hashlib
import struct

import capstone
from capstone import x86_const as x

from giant_owner_audit import decode
import linked_pe


def highlow_fields(pe, start, end):
    fields = set()
    for block in pe.DIRECTORY_ENTRY_BASERELOC:
        for entry in block.entries:
            address = pe.OPTIONAL_HEADER.ImageBase + entry.rva
            if entry.type == 0 or not start - 3 <= address < end:
                continue
            offset = address - start
            if entry.type != 3 or offset < 0 or offset + 4 > end - start:
                raise ValueError("unsupported/partial root base relocation")
            if any(abs(offset - prior) < 4 for prior in fields):
                raise ValueError("duplicate/overlapping root base relocation")
            fields.add(offset)
    return fields


def replay_root(pe, map_text, start, end, inspection, target, canonical,
                call_targets, bindings, literal_overrides, *, game_pe, functions=None):
    """Return the entire normalized envelope and a non-acceptance receipt."""
    base = pe.OPTIONAL_HEADER.ImageBase
    raw = pe.get_data(start - base, end - start)
    metadata = inspection["root_callable_and_padding_bytes"]
    if len(raw) != end - start or not 0 < metadata < len(raw):
        raise ValueError("invalid/truncated linked root envelope")
    rows = decode(raw[:metadata], start)
    by_address = {row.address: row for row in rows}
    fields = highlow_fields(pe, start, end)
    functions = functions if functions is not None else linked_pe.parse_map(map_text)
    symbols = linked_pe.parse_map_symbols(map_text)
    normalized = bytearray(raw)
    consumed, local_fields, areas = set(), {}, []
    counts, literal_identities = Counter(), {}

    for fact in inspection["switches"]:
        table = int(fact["table"], 0)
        jump = by_address[int(fact["dispatch"], 0)]
        if (jump.mnemonic != "jmp" or len(jump.operands) != 1
                or jump.operands[0].type != x.X86_OP_MEM):
            raise ValueError("switch dispatch no longer has its memory operand")
        operand = jump.operands[0]
        if (operand.mem.base or not operand.mem.index or operand.mem.scale != 4
                or operand.mem.disp & 0xFFFFFFFF != table):
            raise ValueError("switch dispatch/table disagrees")
        number = rows.index(jump)
        load = next((row for row in reversed(rows[max(0, number - 3):number])
                     if row.mnemonic == "movzx"
                     and row.operands[0].reg == operand.mem.index), None)
        if (load is None or len(load.operands) != 2
                or load.operands[1].type != x.X86_OP_MEM
                or load.operands[1].size != 1):
            raise ValueError("switch index load no longer agrees")
        index = load.operands[1].mem.disp & 0xFFFFFFFF
        for row, address in ((jump, table), (load, index)):
            field = row.address - start + row.disp_offset
            if row.disp_size != 4 or field in local_fields:
                raise ValueError("unsupported/repeated switch address field")
            local_fields[field] = address
        destination_count, index_count = fact["destination_count"], fact["index_count"]
        if not 0 < destination_count <= 256 or not 0 < index_count <= 256:
            raise ValueError("unsupported switch table size")
        for address, length, kind in ((table, 4 * destination_count, "destinations"),
                                      (index, index_count, "indices")):
            if not start + metadata <= address < address + length <= end:
                raise ValueError("switch table escapes root metadata")
            areas.append((address - start, address - start + length, kind))
        indices = raw[index - start:index - start + index_count]
        if (max(indices) >= destination_count or set(indices) != set(range(destination_count))
                or hashlib.sha256(indices).hexdigest() != fact["indices_sha256"]):
            raise ValueError("switch indices no longer agree")
        for field in range(table - start, table - start + 4 * destination_count, 4):
            value = struct.unpack_from("<I", raw, field)[0]
            if field not in fields or value not in by_address:
                raise ValueError("switch destination lacks relocation/instruction boundary")
            if field in consumed:
                raise ValueError("overlapping switch destination fields")
            struct.pack_into("<I", normalized, field, target + value - start)
            consumed.add(field)
            counts["switch_destinations"] += 1

    previous = metadata
    for first, last, kind in sorted(areas):
        if (first < previous or first - previous > 3
                or raw[previous:first] != b"\x90" * (first - previous)
                or (first != previous and (kind != "destinations" or first % 4))):
            raise ValueError("overlapping/unaccounted switch metadata bytes")
        previous = last
    trailing = raw[previous:]
    if len(trailing) > 15 or trailing != b"\xcc" * len(trailing) or end % 16:
        raise ValueError("unaccounted linked tail alignment")

    known = canonical.known_data_targets()
    permitted = {}
    for binding in bindings:
        address, literal, addends, validation = known[binding["key"]]
        if (binding["address"] != address or binding["data_hex"] != literal.hex()
                or set(binding["addends"]) != set(addends)):
            raise ValueError("game data binding differs from canonical contract")
        for addend in addends:
            value = address + (addend if addend < 2**31 else addend - 2**32)
            attest_game_data(game_pe, canonical, value, literal)
            permitted[value] = max(permitted.get(value, 0), len(literal))

    for row in rows:
        offset = row.address - start
        control = row.group(capstone.CS_GRP_CALL) or linked_pe.is_branch(row)
        if row.group(capstone.CS_GRP_CALL) and row.operands[0].type == x.X86_OP_IMM:
            names = functions.get(row.operands[0].imm, [])
            if len(names) != 1 or names[0][0] not in call_targets:
                raise ValueError("unmapped/ambiguous linked root call")
            if row.size != 5 or row.bytes[0] != 0xE8 or row.imm_offset != 1:
                raise ValueError("root direct call is not E8 REL32")
            destination = call_targets[names[0][0]]
            displacement = destination - (target + offset + 5)
            if not -(2**31) <= displacement < 2**31:
                raise ValueError("linked root call displacement overflows")
            struct.pack_into("<i", normalized, offset + 1, displacement)
            counts["direct_calls"] += 1
        elif linked_pe.is_branch(row) and row.operands[0].type == x.X86_OP_IMM:
            if row.operands[0].imm not in by_address:
                raise ValueError("unclosed linked internal branch")

        field = offset + row.disp_offset
        if row.disp_size and field in fields:
            memory = [operand for operand in row.operands if operand.type == x.X86_OP_MEM]
            if row.disp_size != 4 or len(memory) != 1:
                raise ValueError("base relocation is not a complete memory address field")
            value = memory[0].mem.disp & 0xFFFFFFFF
            if value != struct.unpack_from("<I", raw, field)[0]:
                raise ValueError("decoded memory field disagrees with linked bytes")
            if field in local_fields:
                if local_fields[field] != value:
                    raise ValueError("local switch reference changed")
                destination = target + value - start
                counts["switch_addresses"] += 1
            else:
                if memory[0].mem.base or memory[0].mem.index:
                    raise ValueError("unsupported indexed linked literal")
                names = [name for name, definitions in symbols.items()
                         if any(address == value for address, _ in definitions)]
                if len(names) != 1 or not names[0].startswith("__real@"):
                    raise ValueError("linked literal lacks unique exact map identity")
                name = names[0]
                key = canonical.dir32_target_key(name, literal_overrides, 0)
                bits = canonical.real_literal_bytes({"type": "DIR32", "symbol": name, "addend": 0})
                if key not in known or bits is None:
                    raise ValueError("linked literal lacks canonical contract")
                destination, declared, addends, validation = known[key]
                rva = value - base
                section = pe.get_section_by_rva(rva)
                if (section is None or section.Characteristics & (0x20000000 | 0x80000000 | 0x80)
                        or not section.Characteristics & 0x40
                        or not section.VirtualAddress <= rva <= rva + len(bits)
                        <= section.VirtualAddress + min(section.Misc_VirtualSize, section.SizeOfRawData)
                        or validation != "literal" or 0 not in addends or declared != bits
                        or memory[0].size > len(bits)
                        or pe.get_data(rva, len(bits)) != bits
                        or canonical.target_bytes(destination, len(bits)) != bits):
                    raise ValueError("linked/target literal bytes, width or section differ")
                literal_identities[name] = {"key": key, "bytes": bits.hex(), "target": hex(destination)}
                counts["literal_references"] += 1
            struct.pack_into("<I", normalized, field, destination)
            consumed.add(field)

        for operand in row.operands:
            if operand.type == x.X86_OP_MEM:
                if operand.mem.segment in (x.X86_REG_FS, x.X86_REG_GS) or field in consumed:
                    continue
                value = operand.mem.disp & 0xFFFFFFFF
                if value in permitted and not operand.mem.base and not operand.mem.index:
                    if operand.size > permitted[value]:
                        raise ValueError("game reference exceeds its attested data width")
                    counts["game_data_references"] += 1
                elif ((base <= value < base + pe.OPTIONAL_HEADER.SizeOfImage)
                      or (0x400000 <= value < 0x706000)
                      or (not operand.mem.base and not operand.mem.index and row.mnemonic != "lea")):
                    raise ValueError("unattested/unrelocated linked memory address")
            elif operand.type == x.X86_OP_IMM and not control:
                value = operand.imm & 0xFFFFFFFF
                if base <= value < base + pe.OPTIONAL_HEADER.SizeOfImage or 0x400000 <= value < 0x706000:
                    raise ValueError("unsupported pointer-shaped linked immediate")
    if consumed != fields or not set(local_fields) <= consumed:
        raise ValueError("unconsumed or missing linked root base relocation")
    return bytes(normalized), {
        "envelope_bytes": len(raw), "metadata_offset": metadata,
        "metadata_end_offset": previous, "trailing_link_alignment_hex": trailing.hex(),
        "highlow_fields": len(fields), "replayed": dict(counts),
        "literal_identities": literal_identities,
        "canonical_envelope_sha256": hashlib.sha256(normalized).hexdigest(),
        "scope": "complete diagnostic envelope replay; no accepted-unit or execution claim",
    }


def attest_game_data(pe, canonical, address, literal):
    rva = address - pe.OPTIONAL_HEADER.ImageBase
    section = pe.get_section_by_rva(rva)
    if (section is None or section.Characteristics & 0x20000000
            or not section.VirtualAddress <= rva <= rva + len(literal)
            <= section.VirtualAddress + section.Misc_VirtualSize
            or canonical.target_bytes(address, len(literal)) != literal):
        raise ValueError("game binding is not attested non-executable data")
