#!/usr/bin/env python3
"""Compare bounded pair-response entries with real target collision helpers.

The original collision phase seeds valid geometry. Priority words and source
bytes are data fixtures; no predicate, extent, reset or game result is supplied.
Native execution supplements the independent canonical byte comparison.
"""

from pathlib import Path
import argparse, collections, csv, hashlib, importlib.util, itertools, json, sys
import capstone, pefile, unicorn
from unicorn import x86_const as r

R = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location(
    "pair_phase_environment", R / "scripts/audit-battle-collision-phase.py"
)
env = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = env
spec.loader.exec_module(env)
c = env.c
ADDRESS, SIZE = 0x46CA80, 542
BODY_SHA = "ea54fb25e5ab2ac5e4b7c2dc17792e6073ef654b22b20a06fce6a9887c1257d6"
SYMBOL = "?resolve_group_b_object_clash@CollisionContext@th105@@QAEXPAUCollisionObject@2@0@Z"
REL32 = {
    "?test_group_b_against_group_b@CollisionContext@th105@@QAEHPAUCollisionObject@2@0@Z": 0x46BCA0,
    "?reset_collision_extents@CollisionContext@th105@@QAEXXZ": 0x46B6C0,
}


class Probe(env.Probe):
    def __init__(self, image, body=None):
        super().__init__(image, body)
        self.start = ADDRESS if body is None else env.SOURCE
        self.size = SIZE if body is None else len(body)

    def evaluate_pair(self, arena, resources, case):
        u = self.u
        u.context_restore(self.initial)
        u.mem_write(env.CTX, arena)
        u.mem_write(env.DATA, resources)
        u.mem_write(env.STACK, bytes(0x10000))
        self.put(0, "I", 0xFFFFFFFF)
        self.failure = None
        self.saw_return = False
        self.allocated = []
        self.alloc_trace = []
        self.old_nodes = set()
        self.call_order = []
        left, right = env.ACTORS[2], env.ACTORS[4]
        self.put(env.CTX + 0x1C, "iiii", 101, 102, 103, 104)
        for i, actor in enumerate([left, right]):
            record = env.DATA + 0x8000 + i * 0x40
            self.put(record + 0x10, "hh", *case["priorities"][i])
            self.put(actor + 0x1A8, "I", record)
            self.put(actor + 0x1A0, "B", case["sources"][i])
            self.put(actor + 0x180, "IB", 0x11223344 + i, 0xA0 + i)
            if case["overlap"]:
                self.put(actor + 0x1B4, "iiii", -10, -10, 10, 10)
        if case.get("alias"):
            right = left
        saved = {
            r.UC_X86_REG_EBX: 0x11111111,
            r.UC_X86_REG_EBP: 0x22222222,
            r.UC_X86_REG_ESI: 0x33333333,
            r.UC_X86_REG_EDI: 0x44444444,
        }
        for k, v in saved.items():
            u.reg_write(k, v)
        sp = env.STACK + 0xFF00
        self.put(sp, "III", env.RETURN, left, right)
        u.reg_write(r.UC_X86_REG_ESP, sp)
        u.reg_write(r.UC_X86_REG_ECX, env.CTX)
        u.reg_write(r.UC_X86_REG_FPCW, 0x27F)
        u.reg_write(r.UC_X86_REG_MXCSR, 0x1F80)
        u.emu_start(self.start, env.RETURN, count=200000)
        if self.failure:
            raise ValueError(self.failure)
        if (
            not self.saw_return
            or u.reg_read(r.UC_X86_REG_EIP) != env.RETURN
            or u.reg_read(r.UC_X86_REG_ESP) != sp + 12
            or any(u.reg_read(k) != v for k, v in saved.items())
        ):
            raise ValueError("native pair ABI failed")
        if (
            self.alloc_trace
            or self.word(0) != 0xFFFFFFFF
            or (u.reg_read(r.UC_X86_REG_FPSW) >> 11) & 7
            or u.reg_read(r.UC_X86_REG_FPCW) != 0x27F
        ):
            raise ValueError("unexpected allocation/SEH/x87 state")
        return dict(
            arena=bytes(u.mem_read(env.CTX, 0x20000)),
            calls=self.call_order,
            mxcsr=u.reg_read(r.UC_X86_REG_MXCSR),
        )


def audit(obj, smoke=False):
    target_hash = c.verify_target()
    raw = c.target_bytes(ADDRESS, SIZE)
    if hashlib.sha256(raw).hexdigest() != BODY_SHA:
        raise ValueError("target body changed")
    object_hash = hashlib.sha256(obj.read_bytes()).hexdigest()
    rel = c.known_targets()
    rel.update(REL32)
    body = c.coff_symbol_bytes(obj, SYMBOL, env.SOURCE, 10000, rel, c.known_data_targets(), {})
    canonical = c.coff_symbol_bytes(obj, SYMBOL, ADDRESS, 10000, rel, c.known_data_targets(), {})
    image = pefile.PE(str(R / "resources/th105.exe")).get_memory_mapped_image()
    seed = env.Probe(image)
    snapshot = seed.evaluate(dict(a=0, b=1, objects=2, status=1, result=0,
                                 flags=0, extension=0, old=0, friendly=0))
    arena = snapshot["object"]
    resources = bytes(seed.u.mem_read(env.DATA, 0x10000))
    del seed
    probes = [Probe(image), Probe(image, body)]
    values = [-32768, -2, -1, 0, 1, 2, 32767]
    cases = [dict(priorities=[list(p[:2]), list(p[2:])], sources=[1, 2], overlap=True)
             for p in itertools.product(values, repeat=4)]
    cases.extend(dict(priorities=[[2, a], [-1, b]], sources=[1, 2], overlap=False)
                 for a, b in itertools.product(values, repeat=2))
    branches = [([0, 1], [0, 1]), ([0, -1], [0, 1]),
                ([0, 2], [0, 1]), ([2, 1], [2, 0]),
                ([0, 2], [0, 0]), ([0, 0], [1, 1]),
                ([0, 0], [-1, 1]), ([2, 0], [1, 0]),
                ([0, 0], [1, 0]), ([0, 0], [0, 0])]
    cases.extend(dict(priorities=[a, b], sources=list(sources), overlap=True)
                 for a, b in branches
                 for sources in itertools.product([0, 1, 2, 255], repeat=2))
    cases.extend(dict(priorities=[[v, v], [v, v]], sources=[s, s],
                      overlap=True, alias=True)
                 for v, s in itertools.product(values, [0, 1, 2, 255]))
    if smoke:
        cases = cases[:2401:101] + cases[2401:2450:7] + cases[2450:]
    mismatches, examples = 0, []
    digest = hashlib.sha256()
    for n, case in enumerate(cases):
        digest.update(json.dumps(case, sort_keys=True).encode())
        results = [p.evaluate_pair(arena, resources, case) for p in probes]
        if results[0] != results[1]:
            mismatches += 1
            if len(examples) < 4:
                examples.append(dict(case=case,
                    calls_equal=results[0]["calls"] == results[1]["calls"],
                    arena_differences=[hex(i) for i, (a, b) in enumerate(zip(
                        results[0]["arena"], results[1]["arena"])) if a != b][:32]))
        if n % 256 == 0:
            print(f"native pair {n}/{len(cases)} mismatches={mismatches}",
                  file=sys.stderr, flush=True)
    if object_hash != hashlib.sha256(obj.read_bytes()).hexdigest():
        raise ValueError("object changed")
    rows = list(capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32).disasm(raw, ADDRESS))
    if sum(i.size for i in rows) != SIZE:
        raise ValueError("incomplete target decode")
    unvisited = {i.address - ADDRESS for i in rows} - probes[0].visited
    if not smoke and unvisited:
        raise ValueError(f"pair coverage incomplete: {sorted(unvisited)}")
    sizes = {int(row["address"], 0): int(row["size"])
             for row in csv.DictReader((R / "config/functions.csv").open())}
    return dict(
        schema="th105-family1-pair-response-native-v1", target_sha256=target_hash,
        body_sha256=BODY_SHA, object_sha256=object_hash,
        canonical_payload_sha256=hashlib.sha256(canonical).hexdigest(),
        candidate_size=len(body), cases=len(cases), mismatch_count=mismatches,
        examples=examples, input_sha256=digest.hexdigest(),
        audit_source_sha256=hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
        environment_source_sha256=hashlib.sha256(
            (R / "scripts/audit-battle-collision-phase.py").read_bytes()).hexdigest(),
        unicorn_version=unicorn.__version__,
        unicorn_library_sha256=hashlib.sha256(
            Path(env.unicorn_api._uc._name).read_bytes()).hexdigest(),
        visited=[len(p.visited) for p in probes],
        unvisited_target_offsets=[hex(i) for i in sorted(unvisited)],
        pair_return_sites=[
            [hex(i.address) for i in instructions
             if i.mnemonic.startswith("ret") and i.address in probe.executed]
            for probe, instructions in zip(probes, [rows, list(capstone.Cs(
                capstone.CS_ARCH_X86, capstone.CS_MODE_32).disasm(body, env.SOURCE))])
        ],
        helper_counts=[{hex(k): v for k, v in sorted(p.calls.items())} for p in probes],
        helper_sha256={hex(a): hashlib.sha256(c.target_bytes(a, sizes[a])).hexdigest()
                       for a in sorted(probes[0].calls)},
        scope="bounded signed priority extrema, independent source bytes, overlap/miss and aliased pointers; seeded by original parent; actual pair/predicate/extent/reset instructions, no game-result callback; no all-game-state or exact claim",
        build_provenance_verified=False,
    )


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("--smoke", action="store_true")
    args = parser.parse_args()
    result = audit(args.object, args.smoke)
    print(json.dumps(result, indent=2))
    sys.exit(bool(result["mismatch_count"]))
