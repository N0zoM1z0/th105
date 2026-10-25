#!/usr/bin/env python3
"""Pin the Fighter PAT loader's complete CFG and optional whole COFF replay."""
import argparse
from collections import Counter
import hashlib
import importlib.util
import json
from pathlib import Path
import struct

import capstone
from capstone import x86
import pefile

import linked_noreturn as error
from workflow_manifest import load_manifest

ROOT = Path(__file__).resolve().parents[1]
ADDRESS, SIZE = 0x461B70, 3885
SHA = "8705c5b085b7e7c1977252b79929296687a251f1e22216c9521d02143f934d42"
UNIT = "exact-first-fighter-pat-resources"


def require(ok, message):
    if not ok:
        raise ValueError(message)


def range_error(read):
    """Reuse the existing target-pinned noncontinuable vector-error contract."""
    for address, size, digest in [
        (error.HELPER, error.HELPER_SIZE, error.HELPER_SHA),
        (error.THROW, error.THROW_SIZE, error.THROW_SHA),
        (error.RECORD, 32, error.RECORD_SHA),
    ]:
        require(hashlib.sha256(read(address, size)).hexdigest() == digest,
                "vector error/throw/exception record pin changed")
    require(struct.unpack("<I", read(error.RECORD + 4, 4))[0] == 1,
            "exception is no longer noncontinuable")
    rows = error.straight_throw(read(error.HELPER, error.HELPER_SIZE), error.HELPER, error.THROW)
    types = error.throw_types(read, 0x6E3BA4)
    require(read(0x6D694C, len(error.MESSAGE)) == error.MESSAGE, "range-error message changed")
    game = pefile.PE(str(ROOT / "resources/th105.exe"))
    imports = [(dll.dll.decode().lower(), entry.name)
               for dll in game.DIRECTORY_ENTRY_IMPORT for entry in dll.imports
               if entry.address == 0x6C015C]
    require(imports == [("kernel32.dll", b"RaiseException")], "throw import identity changed")
    return dict(helper=hex(error.HELPER), size=error.HELPER_SIZE,
                sha256=error.HELPER_SHA, terminal_call=hex(rows[-1].address),
                throw=hex(error.THROW), throw_size=error.THROW_SIZE,
                throw_sha256=error.THROW_SHA, exception_types=types,
                noncontinuable=True, helper_exact_or_origin_credit=False)


def audit(obj=None):
    spec = importlib.util.spec_from_file_location(
        "fighter_pat_compare", ROOT / "scripts/compare-function.py")
    compare = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(compare)
    identity = compare.verify_target()
    code = compare.target_bytes(ADDRESS, SIZE)
    require(hashlib.sha256(code).hexdigest() == SHA, "complete main body pin changed")
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    instructions = list(decoder.disasm(code, ADDRESS))
    require(sum(i.size for i in instructions) == SIZE and len(instructions) == 1227,
            "full main instruction census changed")
    require(instructions[7].mnemonic == "sub" and instructions[7].op_str == "esp, 0x3a8",
            "native aligned frame changed")
    error_report = range_error(compare.target_bytes)
    by_address = {i.address: i for i in instructions}
    reached, pending, calls, indirect, returns, exits = set(), [ADDRESS], Counter(), Counter(), [], []
    while pending:
        address = pending.pop()
        if address in reached:
            continue
        require(address in by_address, f"escaping/noninstruction edge {address:#x}")
        reached.add(address)
        instruction = by_address[address]
        if instruction.mnemonic == "ret":
            require(bytes(instruction.bytes) == b"\xc3", "return cleanup changed")
            returns.append(address)
            continue
        if instruction.mnemonic == "call":
            operand = instruction.operands[0]
            if operand.type == x86.X86_OP_IMM:
                calls[operand.imm] += 1
            else:
                indirect[instruction.op_str] += 1
        if instruction.group(capstone.CS_GRP_JUMP):
            operand = instruction.operands[0]
            require(operand.type == x86.X86_OP_IMM, "unreviewed indirect jump")
            if not ADDRESS <= operand.imm < ADDRESS + SIZE:
                require(address == 0x461F30 and instruction.mnemonic == "jmp"
                        and operand.imm == error.HELPER, "unreviewed external exit")
                exits.append(address)
                continue
            pending.append(operand.imm)
            if instruction.mnemonic == "jmp":
                continue
        pending.append(address + instruction.size)
    unreachable = {hex(a): bytes(i.bytes).hex() for a, i in by_address.items() if a not in reached}
    require(len(reached) == 1226 and returns == [0x462A9C] and exits == [0x461F30],
            "CFG return/error-exit census changed")
    require(unreachable == {"0x4621dd": "8d4900"}, "internal alignment changed")
    require(compare.target_bytes(ADDRESS + SIZE, 3) == b"\xcc" * 3,
            "following independent thunk separation changed")
    require(compare.target_bytes(0x46308A, 5).hex() == "e8e1eaffff", "exact caller edge changed")
    require(calls[0x68A143] == 33 and calls[0x460C10] == 2
            and calls[0x461520] == 1 and calls[0x461590] == 2,
            "native guard/record/group provider census changed")
    require(indirect == Counter({"eax": 31, "edx": 29, "ebx": 2,
                                 "dword ptr [0x6c01d8]": 1}),
            "reader/format indirect call census changed")
    for address, value in [(0x6C2BC4, b"data/character/%s/%s.pat\0"),
                           (0x6C2BA0, b"data/character/%s/palette%03d.bmp\0"),
                           (0x6C2B88, b"data/character/%s/%s\0")]:
        require(compare.target_bytes(address, len(value)) == value, "format object changed")
    report = dict(
        result="target_cfg_closed", evidence_class="hash-attested target bytes/edges",
        target_sha256=identity, address=hex(ADDRESS), size=SIZE, code_sha256=SHA,
        end_exclusive=hex(ADDRESS + SIZE), instructions=len(instructions), reached=len(reached),
        ret0_sites=[hex(a) for a in returns], qualified_error_exits=[hex(a) for a in exits],
        unreviewed_escaping_edges=[], indirect_jumps=[], unreachable_instructions=unreachable,
        following_int3_bytes=3, frame="0x3a8",
        caller=dict(owner="0x00463070", site="0x0046308A", target=hex(ADDRESS)),
        direct_calls={hex(a): n for a, n in sorted(calls.items())},
        indirect_calls=dict(indirect), range_error=error_report, exact_claim=False,
    )
    if obj is not None:
        function = load_manifest()["units"][UNIT]["functions"][0]
        targets = compare.known_targets()
        targets.update({n: int(a, 0) for n, a in
                        (m.split("=", 1) for m in function["rel32_targets"])})
        candidate = compare.coff_symbol_bytes(
            obj, function["symbol_base"], ADDRESS, 0xFFFFFFFF,
            targets, compare.known_data_targets(), {})
        diagnostic = compare.target_bytes(ADDRESS, len(candidate))
        differences = [dict(offset=i, address=hex(ADDRESS + i), target=f"{a:02x}", candidate=f"{b:02x}")
                       for i, (a, b) in enumerate(zip(diagnostic, candidate)) if a != b]
        report["candidate"] = dict(
            object=str(obj), section_size=len(candidate), size_difference=len(candidate) - SIZE,
            full_section_canonical_sha256=hashlib.sha256(candidate).hexdigest(),
            full_relocation_replay=True,
            unequal_positions_in_main=sum(a != b for a, b in zip(code, candidate)),
            unequal_positions_in_section_sized_target_range=len(differences),
            section_sized_range_is_diagnostic_only=True, differences=differences,
        )
        report["result"] = "candidate_exact" if candidate == code else "candidate_nonexact"
    return report


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--object", type=Path)
    args = parser.parse_args()
    try:
        report = audit(args.object)
    except (OSError, ValueError, KeyError) as failure:
        print(json.dumps(dict(result="blocked", error=str(failure)), indent=2))
        return 1
    print(json.dumps(report, indent=2))
    return int(report["result"] == "candidate_nonexact")


if __name__ == "__main__":
    raise SystemExit(main())
