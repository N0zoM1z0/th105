#!/usr/bin/env python3
"""Compare the four510-family bodies inside the integrated Reimu source."""
from __future__ import annotations

import argparse
import importlib.util
import itertools
import json
from pathlib import Path
import struct
import sys

import unicorn

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location("reimu_510_charge", ROOT / "scripts/audit-reimu-mid-500-actions.py")
charge = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = charge
spec.loader.exec_module(charge)
low = charge.low
SYMBOL = charge.SYMBOL
ACTIONS = (510, 511, 512, 513)
KEYS = (*charge.KEYS, *ACTIONS)
HELPERS, CALL_TARGETS = charge.HELPERS, charge.CALL_TARGETS
SUPPORT_PATHS = (Path(charge.__file__), *charge.SUPPORT_PATHS)
LITERAL_BINDINGS = {**charge.LITERAL_BINDINGS, "41f00000": 0x6C3DD4,
                    "c1f00000": 0x6C3DD0, "c2340000": 0x6C3DCC,
                    "42700000": 0x6D6EE0, "c2700000": 0x6C3DC8}
SCHEMA = "th105-reimu-mid-510-native-v1"
SCOPE = ("integrated entry/low/middle through513; actual native helpers and RET ABI; "
         "first812 request/payload per volley; later source pending; supplied "
         "read-only animation/flat/zero-handle context; no returning world "
         "request, full-volley execution, full-root or canonical-exact claim")


def cases(smoke=False):
    # Reuse input profiles, never alter the imported module's case domain.
    admitted = {500: 510, 501: 511, 502: 512, 503: 513}
    if smoke:
        for case in charge.cases(True):
            if case["action"] in admitted:
                yield {**case, "action": admitted[case["action"]]}
        return
    for case in charge.cases():
        if case["cohort"] in ("motion", "volley", "charge", "tail") and case["action"] in admitted:
            yield {**case, "action": admitted[case["action"]]}
    base = next(charge.cases(True))
    branches = (
        (510, 0x483479, {"sequence": 2, "frame": 2, "timer": 0, "level736": 0}),
        (510, 0x4835F4, {"sequence": 2, "frame": 2, "timer": 0, "level736": 1}),
        (510, 0x4837E5, {"sequence": 2, "frame": 2, "timer": 0, "level736": 2}),
        (511, 0x483B4E, {"sequence": 2, "frame": 2, "timer": 0}),
        (512, 0x484252, {"sequence": 2, "frame": 1, "timer": 0}),
        (513, 0x484986, {"sequence": 2, "frame": 1, "timer": 0}),
        (512, 0x4824FA, {"vy": 0xC0400000}),
        (513, 0x4824FA, {"vy": 0xC0400000}),
        (510, 0x481D73, {"sequence": 1, "counter": 20}),
        (510, 0x481D98, {"sequence": 1, "counter": 60, "level736": 1}),
        (512, 0x48748C, {"sequence": 5, "counter": -1, "timer": -1}),
        (513, 0x48748C, {"sequence": 5, "counter": -1, "timer": -1}),
    )
    for (action, site, change), cw in itertools.product(branches, (0x27F, 0x37F)):
        yield {**base, "cohort": "branches", "action": action,
               "required_site": site, "control_word": cw, **change}
    for case in charge.cases(True):
        yield {**case, "cohort": "integration"}
    for case in charge.cases():
        if case["cohort"] == "integration":
            yield case
    yield {**base, "cohort": "default", "action": 509}
    for action in (514, 520, 551, 560, 561, 798, 32767):
        yield {**base, "cohort": "handoff", "action": action}


class Probe(charge.Probe):
    resource_keys = KEYS
    handled_action_max = 513

    def step(self, uc, address, size):
        super().step(uc, address, size)
        if address == 0x465190 and self.spawn_request[1] == 812:
            request = self.spawn_request
            pointer, count = request[6:8]
            sp = uc.reg_read(low.r.UC_X86_REG_ESP)
            if count != 3 or pointer & 3 or not sp <= pointer <= pointer+12 <= low.STACK+0x10000:
                raise ValueError("812 parameters escaped the active supplied stack")
            self.spawn_request = (*request[:6], struct.unpack("<III", uc.mem_read(pointer, 12)), count)


def check_target_case(case, result, sites):
    charge.shot.check_target_case(case, result, sites)
    if case["cohort"] == "volley" and case["level736"] in (0, 1, 2):
        if result["spawn_request"] is None or result["spawn_request"][:2] != (0x465190, 812):
            raise ValueError("volley fixture bypassed the actual812 request")
        if result["actor"][0x17C] != 8:
            raise ValueError("812 request bypassed the observed17C=8 store")


COHORT_COUNTS = {"motion": 336, "volley": 600, "charge": 864, "tail": 288,
                 "branches": 24, "integration": 373, "default": 1, "handoff": 7}
SMOKE_COUNT = 36


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    selection = parser.add_mutually_exclusive_group()
    selection.add_argument("--smoke", action="store_true")
    selection.add_argument("--cohort", action="append", choices=tuple(COHORT_COUNTS))
    args = parser.parse_args()
    try:
        result = low.audit(args.object, args.smoke, args.cohort, contract=sys.modules[__name__])
    except (KeyError, OSError, ValueError, unicorn.UcError) as error:
        parser.exit(2, f"Reimu mid-510 audit failed: {error}\n")
    print(json.dumps(result, indent=2))
    raise SystemExit(1 if result["mismatch_count"] else 0)
