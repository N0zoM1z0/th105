#!/usr/bin/env python3
"""Execute family1 traversal against original game/container helpers.

The original parent prepares one valid geometry snapshot. Bounded list, filter,
priority and overlap data then drive standalone target/source dispatcher entries.
This supplements, and does not replace, the strict canonical byte comparator.
"""

from pathlib import Path
import argparse, collections, csv, hashlib, importlib.util, itertools, json, sys, tomllib
import pefile, unicorn
import capstone
from unicorn import x86_const as r

R = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location(
    "family1_phase_environment", R / "scripts/audit-battle-collision-phase.py"
)
env = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = env
spec.loader.exec_module(env)
c = env.c
ADDRESS, SIZE = 0x46DD40, 686
BODY_SHA = "aa250ed95904cbc1b0d78f04b2f4a09ef1bcd53f844cc298140474e89f2ea8ec"


class Probe(env.Probe):
    def __init__(self, image, body=None):
        super().__init__(image, body)
        self.start = ADDRESS if body is None else env.SOURCE
        self.size = SIZE if body is None else len(body)

    def evaluate_clashes(self, arena, resources, case):
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
        for side, count in enumerate(case["counts"]):
            head = env.CTX + 0xA000 + side * 0x400
            header = env.CTX + 0x44 + side * 12
            actors = env.ACTORS[2 + side * 2 : 4 + side * 2]
            if case.get("alias") and side == 0:
                actors = [actors[0], actors[0]]
            self.put(header, "III", 0, head, count)
            nodes = [head + 0x40 + i * 16 for i in range(count)]
            self.put(
                head,
                "III",
                nodes[0] if nodes else head,
                nodes[-1] if nodes else head,
                0,
            )
            for i, n in enumerate(nodes):
                self.put(
                    n,
                    "III",
                    nodes[i + 1] if i + 1 < count else head,
                    nodes[i - 1] if i else head,
                    actors[i],
                )
        for i, a in enumerate(env.ACTORS[2:]):
            frame = self.word(a + 0x1A4)
            same = case["same"] == 1 or (case["same"] == 2 and i % 2 == 0)
            flags = (
                0x40
                if case["filter"] == 1 and i % 2 == 0
                else 0x80000
                if case["filter"] == 2 and i % 2
                else 0
            )
            self.put(frame + 0x4C, "II", flags, 0x100000 if same else 0)
            self.put(a + 0x1A0, "B", 0 if case["filter"] == 3 and i % 2 == 0 else 1)
            record = env.DATA + 0x8000 + i * 0x40
            self.put(
                record + 0x10,
                "hh",
                (i + case["priority"]) % 5 - 2,
                (2 * i + case["priority"]) % 4 - 1,
            )
            self.put(a + 0x1A8, "I", record)
            if case["overlap"]:
                self.put(a + 0x1B4, "iiii", -10, -10, 10, 10)
        saved = {
            r.UC_X86_REG_EBX: 0x11111111,
            r.UC_X86_REG_EBP: 0x22222222,
            r.UC_X86_REG_ESI: 0x33333333,
            r.UC_X86_REG_EDI: 0x44444444,
        }
        for k, v in saved.items():
            u.reg_write(k, v)
        sp = env.STACK + 0xFF00
        self.put(sp, "I", env.RETURN)
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
            or u.reg_read(r.UC_X86_REG_ESP) != sp + 4
            or any(u.reg_read(k) != v for k, v in saved.items())
        ):
            raise ValueError("native dispatcher ABI failed")
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
    function = tomllib.loads((R / "config/match-units.toml").read_text())["units"][
        "gpt-web-family1-object-clashes"
    ]["functions"][0]
    if int(function["address"], 0) != ADDRESS:
        raise ValueError("configured root changed")
    rel = c.known_targets()
    rel.update(
        {
            name: int(value, 0)
            for name, value in (
                item.split("=", 1) for item in function["rel32_targets"]
            )
        }
    )
    body = c.coff_symbol_bytes(
        obj, function["symbol_base"], env.SOURCE, 10000, rel, c.known_data_targets(), {}
    )
    canonical = c.coff_symbol_bytes(
        obj, function["symbol_base"], ADDRESS, 10000, rel, c.known_data_targets(), {}
    )
    image = pefile.PE(str(R / "resources/th105.exe")).get_memory_mapped_image()
    seed = env.Probe(image)
    snapshot = seed.evaluate(
        dict(
            a=0,
            b=1,
            objects=2,
            status=1,
            result=0,
            flags=0,
            extension=0,
            old=0,
            friendly=0,
        )
    )
    arena = snapshot["object"]
    resources = bytes(seed.u.mem_read(env.DATA, 0x10000))
    del seed
    probes = [Probe(image), Probe(image, body)]
    cases = []
    for n, (counts, same, filter, overlap) in enumerate(
        itertools.product(
            itertools.product(range(3), repeat=2), range(3), range(4), range(2)
        )
    ):
        cases.append(
            dict(
                counts=list(counts),
                same=same,
                filter=filter,
                overlap=overlap,
                priority=n % 5,
            )
        )
    cases.extend(
        dict(
            counts=[2, 2], same=1, filter=0, overlap=hit, priority=priority, alias=True
        )
        for hit, priority in itertools.product(range(2), range(5))
    )
    if smoke:
        cases = cases[::16]
    mismatches = 0
    examples = []
    digest = hashlib.sha256()
    for n, case in enumerate(cases):
        digest.update(json.dumps(case, sort_keys=True).encode())
        results = [p.evaluate_clashes(arena, resources, case) for p in probes]
        if results[0] != results[1]:
            mismatches += 1
            if len(examples) < 4:
                examples.append(
                    dict(
                        case=case,
                        calls_equal=results[0]["calls"] == results[1]["calls"],
                        arena_differences=[
                            hex(i)
                            for i, (a, b) in enumerate(
                                zip(results[0]["arena"], results[1]["arena"])
                            )
                            if a != b
                        ][:64],
                    )
                )
        if n % 64 == 0:
            print(
                f"native {n}/{len(cases)} mismatches={mismatches}",
                file=sys.stderr,
                flush=True,
            )
    if object_hash != hashlib.sha256(obj.read_bytes()).hexdigest():
        raise ValueError("object changed")
    rows = list(
        capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32).disasm(raw, ADDRESS)
    )
    unvisited = {i.address - ADDRESS for i in rows} - probes[0].visited
    invalid_calls = {
        i.address - ADDRESS
        for i in rows
        if i.mnemonic == "call" and i.op_str == "0x68a143"
    }
    if not smoke and unvisited != invalid_calls:
        raise ValueError("normal dispatcher coverage incomplete")
    sizes = {
        int(row["address"], 0): int(row["size"])
        for row in csv.DictReader((R / "config/functions.csv").open())
    }
    return dict(
        schema="th105-family1-object-clashes-native-v1",
        target_sha256=target_hash,
        body_sha256=BODY_SHA,
        object_sha256=object_hash,
        canonical_payload_sha256=hashlib.sha256(canonical).hexdigest(),
        candidate_size=len(body),
        cases=len(cases),
        mismatch_count=mismatches,
        examples=examples,
        input_sha256=digest.hexdigest(),
        audit_source_sha256=hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
        environment_source_sha256=hashlib.sha256(
            (R / "scripts/audit-battle-collision-phase.py").read_bytes()
        ).hexdigest(),
        unicorn_version=unicorn.__version__,
        unicorn_library_sha256=hashlib.sha256(
            Path(env.unicorn_api._uc._name).read_bytes()
        ).hexdigest(),
        visited=[len(p.visited) for p in probes],
        unvisited_target_offsets=[hex(i) for i in sorted(unvisited)],
        pair_return_sites=[
            [
                hex(i.address)
                for i in capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32).disasm(
                    c.target_bytes(0x46CA80, 542), 0x46CA80
                )
                if i.mnemonic.startswith("ret") and i.address in p.executed
            ]
            for p in probes
        ],
        helper_counts=[{hex(k): v for k, v in sorted(p.calls.items())} for p in probes],
        helper_sha256={
            hex(a): hashlib.sha256(c.target_bytes(a, sizes[a])).hexdigest()
            for a in sorted(probes[0].calls)
        },
        scope="bounded valid list topology/filter/priority/overlap fixtures, seeded by actual parent target; all dispatcher/pair/geometry instructions native, no helper-result substitution or code patch; no invalid/throw/startup/all-game-state claim",
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
