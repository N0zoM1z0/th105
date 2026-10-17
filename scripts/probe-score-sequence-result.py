#!/usr/bin/env python3
"""Execute ScoreData42CF70 and its real compiled source with native getters.

Normal paths RET; malformed ranges stop at the genuine invalid-parameter
entry. No dependency return values are supplied by the fixture.
"""

from collections import Counter
from pathlib import Path
import argparse
import hashlib
import importlib.util
import itertools
import json
import struct
import sys

import pefile
import unicorn
import unicorn.x86_const as r

from giant_owner_audit import decode
from linked_pe import comparator, sha

ROOT = Path(__file__).resolve().parents[1]
START, SIZE = 0x42CF70, 159
BODY_SHA = "6c772b740b8d672b600fec4ddb0211bad97c315d5148309f710c2d12a46e8922"
SYMBOL = "?record_sequence_result_42c060@ScoreData@th105@@QAEXHHH@Z"
SOURCE = ROOT / "src/config/ScoreSequenceResult.cpp"
CALLS = {
    "?get_game_mode@th105@@YA?AW4GameMode@1@XZ": 0x43AC40,
    "?get_session_setup_option@th105@@YAIXZ": 0x43B070,
    "__invalid_parameter_noinfo": 0x68A143,
}
NATIVE, OWNER, RECORDS = 0x10000000, 0x20001000, 0x20008000
STACK, ENTRY_SP, RETURN = 0x30000000, 0x3000FE00, 0x31000000
NONVOLATILE = (r.UC_X86_REG_EBX, r.UC_X86_REG_EBP, r.UC_X86_REG_ESI, r.UC_X86_REG_EDI)
SENTINELS = (0x12345678, 0x23456789, 0x3456789A, 0x456789AB)


def input_cases():
    for mode, setup, selector, count, keys, counter in itertools.product(
        (0, 1, 3),
        (0, 2, 0xFFFFFFFF),
        (0, 1, 14),
        (0, 1, 3, 5),
        ((11, 22), (-5, 66), (77, -9), (999, 22), (11, 999), (999, 999)),
        (0, 7),
    ):
        yield dict(
            mode=mode,
            setup=setup,
            selector=selector,
            count=count,
            keys=keys,
            counter=counter,
            malformed=False,
        )
    for mode, setup, selector in itertools.product(
        (0, 1, 3), (0, 2, 0xFFFFFFFF), (0, 1, 14)
    ):
        yield dict(
            mode=mode,
            setup=setup,
            selector=selector,
            count=3,
            keys=(999, 999),
            counter=0,
            malformed=True,
        )


def audit(path):
    canonical = comparator()
    target_sha = canonical.verify_target()
    body = canonical.target_bytes(START, SIZE)
    if hashlib.sha256(body).hexdigest() != BODY_SHA:
        raise ValueError("score target body differs")
    spec = importlib.util.spec_from_file_location(
        "score_result_coff", ROOT / "scripts/compare-giant-action-switches.py"
    )
    coff = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = coff
    spec.loader.exec_module(coff)
    obj = coff.CoffObject(path, symbol_base=SYMBOL)
    code = canonical.coff_symbol_bytes(
        path, SYMBOL, NATIVE, len(obj.text), CALLS, canonical.known_data_targets(), {}
    )
    identities = {
        "source_sha256": sha(SOURCE),
        "header_sha256": sha(SOURCE.with_name("ScoreData.hpp")),
        "object_sha256": sha(path),
    }
    provenance_path = Path(str(path) + ".provenance.json")
    provenance = json.loads(provenance_path.read_text())
    if (
        provenance["unit"] != "gpt-web-score-sequence-result"
        or provenance["target_sha256"] != target_sha
        or provenance["source_sha256"] != identities["source_sha256"]
        or provenance["object_sha256"] != identities["object_sha256"]
    ):
        raise ValueError(
            "object provenance does not bind the selected ScoreData source"
        )
    pe = pefile.PE(str(ROOT / "resources/th105.exe"))
    engine = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
    image_base = pe.OPTIONAL_HEADER.ImageBase
    engine.mem_map(image_base, (pe.OPTIONAL_HEADER.SizeOfImage + 4095) & ~4095)
    engine.mem_write(image_base, pe.get_memory_mapped_image())
    engine.mem_map(NATIVE, (len(code) + 4095) & ~4095)
    engine.mem_write(NATIVE, code)
    engine.mem_map(0x20000000, 0x10000)
    engine.mem_map(STACK, 0x10000)
    engine.mem_map(RETURN, 0x1000)
    expected = {
        row.address: bytes(row.bytes)
        for blob, base in (
            (body, START),
            (code, NATIVE),
            (canonical.target_bytes(0x43AC40, 6), 0x43AC40),
            (canonical.target_bytes(0x43B070, 6), 0x43B070),
        )
        for row in decode(blob, base)
    }
    initial = engine.context_save()
    state, visited, outcomes = {}, set(), Counter()

    def instruction(uc, address, size, unused):
        if address == 0x68A143:
            state["stop"] = "invalid-parameter-entry"
            uc.emu_stop()
            return
        if (
            address not in expected
            or bytes(uc.mem_read(address, size)) != expected[address]
        ):
            state["error"] = f"unattested instruction {address:#x}"
            uc.emu_stop()
            return
        if START <= address < START + SIZE:
            visited.add(address)
        if address in (0x43AC40, 0x43B070):
            state["calls"].append(hex(address))

    def write(uc, access, address, size, value, unused):
        if STACK <= address and address + size <= STACK + 0x10000:
            return
        if size == 4 and address in state["allowed_counts"]:
            return
        state["error"] = f"unexpected write {address:#x}/{size}"
        uc.emu_stop()

    engine.hook_add(unicorn.UC_HOOK_CODE, instruction)
    engine.hook_add(unicorn.UC_HOOK_MEM_WRITE, write)

    def evaluate(case, source):
        engine.context_restore(initial)
        engine.mem_write(0x20000000, bytes(0x10000))
        engine.mem_write(STACK, bytes(0x10000))
        record_keys = ((11, 22), (-5, 66), (11, 22), (77, -9), (11, 999))
        for index, (first, second) in enumerate(record_keys):
            engine.mem_write(
                RECORDS + 24 * index,
                struct.pack(
                    "<iIiiii", first, 0xA55AA55A, second, case["counter"], -99, 123
                ),
            )
        begin = RECORDS + (24 * (case["count"] + 1) if case["malformed"] else 0)
        end = RECORDS + 24 * case["count"]
        engine.mem_write(
            OWNER + 0x198 + 16 * case["selector"],
            struct.pack("<4I", 0, begin, end, RECORDS + 24 * 5),
        )
        engine.mem_write(0x6FBD4C, struct.pack("<I", case["mode"]))
        engine.mem_write(0x6FBD44, struct.pack("<I", case["setup"]))
        engine.mem_write(
            ENTRY_SP,
            struct.pack(
                "<4I",
                RETURN,
                case["selector"],
                case["keys"][0] & 0xFFFFFFFF,
                case["keys"][1] & 0xFFFFFFFF,
            ),
        )
        for register, value in zip(NONVOLATILE, SENTINELS):
            engine.reg_write(register, value)
        engine.reg_write(r.UC_X86_REG_ESP, ENTRY_SP)
        engine.reg_write(r.UC_X86_REG_ECX, OWNER)
        state.clear()
        state.update(
            stop=None,
            error=None,
            calls=[],
            allowed_counts={RECORDS + 24 * i + 12 for i in range(case["count"])},
        )
        engine.emu_start(NATIVE if source else START, RETURN, count=10000)
        if state["error"]:
            raise ValueError(state["error"])
        if engine.reg_read(r.UC_X86_REG_EIP) == RETURN:
            state["stop"] = "ret"
            if engine.reg_read(r.UC_X86_REG_ESP) != ENTRY_SP + 16:
                raise ValueError("score RET12 cleanup differs")
            if (
                tuple(engine.reg_read(register) for register in NONVOLATILE)
                != SENTINELS
            ):
                raise ValueError("score callee-save contract differs")
        if state["stop"] is None:
            raise ValueError("score execution did not reach a qualified boundary")
        outcomes["source" if source else "target", state["stop"]] += 1
        return {
            "stop": state["stop"],
            "calls": list(state["calls"]),
            "score": bytes(engine.mem_read(OWNER, 0x300)).hex(),
            "records": bytes(engine.mem_read(RECORDS, 24 * 5)).hex(),
        }

    inputs, outputs = hashlib.sha256(), hashlib.sha256()
    mismatches, examples, cases = 0, [], list(input_cases())
    for case in cases:
        inputs.update(json.dumps(case, sort_keys=True).encode())
        target, source = evaluate(case, False), evaluate(case, True)
        outputs.update(json.dumps(target, sort_keys=True).encode())
        if target != source:
            mismatches += 1
            if len(examples) < 2:
                examples.append({"case": case, "target": target, "source": source})
    if identities != {
        "source_sha256": sha(SOURCE),
        "header_sha256": sha(SOURCE.with_name("ScoreData.hpp")),
        "object_sha256": sha(path),
    }:
        raise ValueError("score source/header/object changed during execution")
    return {
        "schema": "th105-score-sequence-result-native-v1",
        "target_sha256": target_sha,
        "target_body_sha256": BODY_SHA,
        "build_provenance_sha256": sha(provenance_path),
        **identities,
        "probe_sha256": sha(Path(__file__)),
        "cases": len(cases),
        "mismatch_count": mismatches,
        "examples": examples,
        "input_sha256": inputs.hexdigest(),
        "target_output_sha256": outputs.hexdigest(),
        "target_instructions_visited": len(visited),
        "unicorn_version": unicorn.__version__,
        "outcomes": [
            {"side": side, "stop": stop, "cases": count}
            for (side, stop), count in sorted(outcomes.items())
        ],
        "scope": "Real target and compiled method, native game/session getters, checked vector iteration; "
        "normal RET12 or genuine invalid-parameter entry only; no helper-return hooks, "
        "exception/handler continuation or canonical byte equality claim.",
    }


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    args = parser.parse_args()
    report = audit(args.object.resolve())
    print(json.dumps(report, indent=2))
    raise SystemExit(bool(report["mismatch_count"]))
