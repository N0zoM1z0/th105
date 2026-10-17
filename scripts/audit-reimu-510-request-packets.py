#!/usr/bin/env python3
"""Audit local parameter definitions at all48 Reimu510-family request sites.

This is static basic-block dataflow, with unknown live-ins. It never runs or
returns an opaque callback and does not claim whole-volley/native equivalence.
"""
from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import sys
import tomllib

import capstone
from capstone import x86_const as x

ROOT = Path(__file__).resolve().parents[1]
SYMBOL = "?run_checked_action_dispatch@ReimuActionStatePreludeView@th105@@QAE_NXZ"
ANGLES = (30, 0, -30, 45, 15, -15, -45, 60, 30, 0, -30, -60)


def load(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / "scripts" / filename)
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


def block_packet(instructions, literal):
    # Only ESP and the attested ESI receiver have a known entry meaning.
    regs = {x.X86_REG_ESP: ("stack", 0), x.X86_REG_ESI: ("actor", 0)}
    memory, fp, reads = {}, [], set()

    def address(op):
        mem = op.mem
        base = regs.get(mem.base)
        if mem.index or not isinstance(base, tuple):
            return None
        return base[0], base[1]+mem.disp

    narrow_registers = {x.X86_REG_AL: x.X86_REG_EAX, x.X86_REG_AH: x.X86_REG_EAX,
                        x.X86_REG_AX: x.X86_REG_EAX, x.X86_REG_BL: x.X86_REG_EBX,
                        x.X86_REG_BH: x.X86_REG_EBX, x.X86_REG_BX: x.X86_REG_EBX,
                        x.X86_REG_CL: x.X86_REG_ECX, x.X86_REG_CH: x.X86_REG_ECX,
                        x.X86_REG_CX: x.X86_REG_ECX, x.X86_REG_DL: x.X86_REG_EDX,
                        x.X86_REG_DH: x.X86_REG_EDX, x.X86_REG_DX: x.X86_REG_EDX,
                        x.X86_REG_SI: x.X86_REG_ESI, x.X86_REG_DI: x.X86_REG_EDI,
                        x.X86_REG_BP: x.X86_REG_EBP, x.X86_REG_SP: x.X86_REG_ESP}

    def value(op):
        if op.type == x.X86_OP_IMM:
            return op.imm & 0xFFFFFFFF
        if op.type == x.X86_OP_REG:
            return regs.get(op.reg)
        if op.type == x.X86_OP_MEM:
            place = address(op)
            return memory.get(place[1]) if place and place[0] == "stack" and op.size == 4 else None
        return None

    def write(op, val):
        if op.type == x.X86_OP_REG:
            parent = narrow_registers.get(op.reg)
            if parent is not None:
                regs[parent] = None
            else:
                regs[op.reg] = val
        elif op.type == x.X86_OP_MEM:
            place = address(op)
            if place and place[0] == "stack":
                for offset in list(memory):
                    if offset < place[1]+op.size and place[1] < offset+4:
                        del memory[offset]
                if op.size == 4:
                    memory[place[1]] = val

    def fp_index(op):
        if op.type != x.X86_OP_REG or not x.X86_REG_ST0 <= op.reg <= x.X86_REG_ST7:
            raise ValueError("unreviewed x87 stack register")
        return op.reg-x.X86_REG_ST0

    def float_value(insn, op):
        if op.type == x.X86_OP_REG:
            index = fp_index(op)
            return fp[index] if index < len(fp) else None
        if op.type != x.X86_OP_MEM:
            return None
        place = address(op)
        if place and place[0] == "stack":
            bits = memory.get(place[1])
            if isinstance(bits, int) and op.size == 4:
                return struct.unpack("<f", struct.pack("<I", bits))[0]
            return None
        raw = literal(insn, op)
        return struct.unpack("<f" if op.size == 4 else "<d", raw)[0] if raw else None

    for insn in instructions[:-1]:
        ops, name = insn.operands, insn.mnemonic
        for op in ops:
            if op.type == x.X86_OP_MEM and op.access & capstone.CS_AC_READ and name != "lea":
                place = address(op)
                if place and place[0] == "actor":
                    reads.add(place[1])
        if name == "push":
            pushed = value(ops[0])
            sp = regs[x.X86_REG_ESP][1]-4
            regs[x.X86_REG_ESP] = ("stack", sp)
            memory[sp] = pushed
        elif name in ("mov", "movzx", "movsx"):
            write(ops[0], value(ops[1]) if name == "mov" else None)
        elif name == "lea":
            write(ops[0], address(ops[1]))
        elif name == "xor" and ops[0].type == ops[1].type == x.X86_OP_REG and ops[0].reg == ops[1].reg:
            write(ops[0], 0)
        elif name in ("add", "sub") and ops[0].type == x.X86_OP_REG and ops[0].reg == x.X86_REG_ESP:
            if ops[1].type != x.X86_OP_IMM:
                raise ValueError("nonconstant ESP adjustment in a request block")
            regs[x.X86_REG_ESP] = ("stack", regs[x.X86_REG_ESP][1]+(ops[1].imm if name == "add" else -ops[1].imm))
        elif name in ("fldz", "fld1"):
            fp.insert(0, 0.0 if name == "fldz" else 1.0)
        elif name == "fld":
            fp.insert(0, float_value(insn, ops[0]))
        elif name == "fild":
            fp.insert(0, None)
        elif name in ("fst", "fstp"):
            top = fp[0] if fp else None
            if ops[0].type == x.X86_OP_REG:
                index = fp_index(ops[0])
                while len(fp) <= index:
                    fp.append(None)
                fp[index] = top
            else:
                bits = struct.unpack("<I", struct.pack("<f", top))[0] if top is not None and ops[0].size == 4 else None
                write(ops[0], bits)
            if name == "fstp" and fp:
                fp.pop(0)
        elif name == "fxch":
            index = fp_index(ops[0]) if ops else 1
            while len(fp) <= index:
                fp.append(None)
            fp[0], fp[index] = fp[index], fp[0]
        elif name == "fchs":
            if fp and fp[0] is not None:
                fp[0] = -fp[0]
        elif name.startswith(("fadd", "fsub", "fmul", "fdiv")):
            # Coordinate arithmetic is intentionally unknown. Payload literals
            # must be locally defined without borrowing those values/live-ins.
            if fp:
                fp[0] = None
            if name.endswith("p") and len(fp) >= 2:
                fp.pop(0)
                fp[0] = None
        elif name.startswith("f"):
            raise ValueError(f"unreviewed x87 operation {name}")
        elif name in ("cmp", "test", "nop"):
            pass
        else:
            for op in ops:
                if op.access & capstone.CS_AC_WRITE:
                    write(op, None)
    sp = regs[x.X86_REG_ESP][1]
    pointer = memory.get(sp+20)
    payload = ([memory.get(pointer[1]+4*i) for i in range(3)]
               if isinstance(pointer, tuple) and pointer[0] == "stack" else None)
    return {"object_id": memory.get(sp), "count": memory.get(sp+24),
            "payload_bits": payload, "actor_reads": sorted(reads),
            "block_start": hex(instructions[0].address),
            "call_address": hex(instructions[-1].address)}


def packets(code, start, size, is_request, is_wave, literal):
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    instructions = list(decoder.disasm(code, start))
    if sum(insn.size for insn in instructions) != size:
        raise ValueError("request owner did not decode completely")
    leaders = {start}
    for insn in instructions:
        if insn.mnemonic.startswith("j") or insn.mnemonic in ("call", "ret"):
            leaders.add(insn.address+insn.size)
        if insn.mnemonic.startswith("j") and insn.operands[0].type == x.X86_OP_IMM:
            destination = insn.operands[0].imm
            if start <= destination < start+size:
                leaders.add(destination)
    by_address = {item.address: item for item in instructions}
    requests = [item for item in instructions if is_request(item)]
    waves = [item.address+item.size for item in instructions if is_wave(item)]

    def level_reload(point, limit):
        visited, lower = set(), point
        while lower <= point < limit and point in by_address and point not in visited:
            visited.add(point)
            item = by_address[point]
            for op in item.operands:
                if (op.type == x.X86_OP_MEM and op.size == 2 and op.mem.base == x.X86_REG_ESI
                        and not op.mem.index and op.mem.disp == 0x736 and op.access & capstone.CS_AC_READ
                        and item.mnemonic != "lea"):
                    return hex(point)
            if item.mnemonic == "jmp" and item.operands[0].type == x.X86_OP_IMM:
                point = item.operands[0].imm
            elif item.mnemonic.startswith("j") or item.mnemonic in ("call", "ret"):
                return None
            else:
                point += item.size
        return None

    result = []
    for index, insn in enumerate(requests):
        begin = max(point for point in leaders if point <= insn.address)
        block = [item for item in instructions if begin <= item.address <= insn.address]
        packet = block_packet(block, literal)
        if len(requests) == 12 and index in (0, 3, 7):
            point = max((point for point in waves if point <= insn.address), default=None) if index == 0 else requests[index-1].address+requests[index-1].size
            packet["level_reload"] = level_reload(point, insn.address) if point is not None else None
        result.append(packet)
    return result


def audit(path):
    canonical = load("reimu_510_packet_canonical", "compare-function.py")
    target_sha = canonical.verify_target()
    mapper = load("reimu_510_packet_mapper", "compare-giant-action-switches.py")
    target_mapper = mapper.load_target_mapper()
    root = target_mapper.select_root(tomllib.loads((ROOT / "config/giant-action-switches.toml").read_text()), "reimu-vslot28")
    target = target_mapper.map_root(target_mapper.PeImage(ROOT / "resources/th105.exe"),
                                    target_mapper.load_function_rows(ROOT / "config/functions.csv"), root)
    obj = mapper.CoffObject(path, symbol_base=SYMBOL)
    candidate = mapper.build_candidate_map(obj, root)
    comparison = mapper.compare_maps(target, candidate)
    base = int(root["address"], 0)

    def target_request(insn):
        return insn.mnemonic == "call" and insn.operands[0].type == x.X86_OP_IMM and insn.operands[0].imm == 0x465190

    def source_request(insn):
        pair = obj.relocations.get(insn.address+1)
        return insn.mnemonic == "call" and pair and pair[1] == 20 and pair[0].name.startswith("?spawn_owned_object_via_manager@")

    def target_wave(insn):
        return insn.mnemonic == "call" and insn.operands[0].type == x.X86_OP_IMM and insn.operands[0].imm == 0x45C030

    def source_wave(insn):
        pair = obj.relocations.get(insn.address+1)
        return insn.mnemonic == "call" and pair and pair[1] == 20 and pair[0].name.startswith("?dispatch_character_wave_handle@")

    def target_literal(insn, op):
        mem = op.mem
        return canonical.target_bytes(mem.disp, op.size) if not mem.base and not mem.index else None

    def source_literal(insn, op):
        if op.mem.base or op.mem.index:
            return None
        pair = obj.relocations.get(insn.address+insn.disp_offset)
        if not pair or pair[1] != 6 or not pair[0].name.startswith("__real@"):
            return None
        symbol = pair[0]
        section = obj.sections[symbol.section_number-1]
        off = section.raw_offset+symbol.value+op.mem.disp
        raw = obj.data[off:off+op.size]
        expected = bytes.fromhex(symbol.name.removeprefix("__real@"))[::-1]
        if len(raw) != op.size or raw != expected:
            raise ValueError("COFF literal bytes differ from their symbol")
        return raw

    rows, failures = [], []
    expected = [[struct.unpack("<I", struct.pack("<f", value))[0] for value in (angle, 15.0, 0.0)] for angle in ANGLES]
    for row in comparison["rows"]:
        if len(row["cases"]) != 1 or row["cases"][0] not in (510, 511, 512, 513):
            continue
        action = row["cases"][0]
        target_start = base+row["target_offset"]
        source_start = row["candidate_offsets"][0]
        wanted = packets(canonical.target_bytes(target_start, row["target_span"]), target_start, row["target_span"], target_request, target_wave, target_literal)
        actual = packets(obj.text[source_start:source_start+row["candidate_span"]], source_start, row["candidate_span"], source_request, source_wave, source_literal)
        for label, group in (("target", wanted), ("source", actual)):
            if len(group) != 12:
                failures.append({"action": action, "side": label, "request_count": len(group)})
            for index, packet in enumerate(group):
                if (index >= 12 or packet["payload_bits"] != expected[index] or packet["object_id"] != 812
                        or packet["count"] != 3 or (index in (0, 3, 7) and not packet.get("level_reload"))
                        or not {0xEC, 0xF0, 0x104} <= set(packet["actor_reads"])):
                    failures.append({"action": action, "side": label, "index": index, "packet": packet})
        rows.append({"action": action, "target": wanted, "source": actual})
    if len(rows) != 4:
        raise ValueError("four510-family owner rows are required")
    return {"schema": "th105-reimu-510-static-request-packets-v1", "target_sha256": target_sha,
            "object_sha256": hashlib.sha256(path.read_bytes()).hexdigest(), "failure_count": len(failures),
            "capstone_version": capstone.__version__,
            "support_sha256": {str(item.relative_to(ROOT)): hashlib.sha256(item.read_bytes()).hexdigest()
                               for item in (Path(__file__), ROOT / "scripts/compare-function.py",
                                            ROOT / "scripts/compare-giant-action-switches.py",
                                            ROOT / "config/giant-action-switches.toml")},
            "failures": failures, "rows": rows,
            "scope": "basic-block local payload/count definitions, fresh actor reads and inter-group level reloads only; unknown live-ins, no callback execution/return, native continuation or canonical-exact claim"}


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    args = parser.parse_args()
    try:
        result = audit(args.object)
    except (KeyError, OSError, ValueError) as error:
        parser.exit(2, f"Reimu510 static packet audit failed: {error}\n")
    print(json.dumps(result, indent=2))
    raise SystemExit(1 if result["failure_count"] else 0)
