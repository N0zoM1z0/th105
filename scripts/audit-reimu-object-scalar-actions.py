#!/usr/bin/env python3
"""Execute scalar ReimuObject update source paths against the original root.

The staging boolean reports phase coverage, not the original void ABI. Actual
animation and math helpers run unchanged; object generation stops at real entry.
This does not establish whole-root semantics, original source or exact bytes.
"""

from pathlib import Path
from collections import Counter, defaultdict
import argparse, hashlib, importlib.util, itertools, json, struct, sys
import capstone, pefile, unicorn
from unicorn import x86_const as r

R = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(R / "scripts"))


def load(name, path):
    s = importlib.util.spec_from_file_location(name, R / path)
    m = importlib.util.module_from_spec(s)
    sys.modules[name] = m
    s.loader.exec_module(m)
    return m


entry = load("object_update_entry", "scripts/audit-reimu-object-entry-calls.py")
facts = load("object_update_facts", "scripts/audit-reimu-object-update-target.py")
c = entry.c
m = entry.m
A = 0x496540
S = 0x800000
OWNER = entry.OWNER
STACK = entry.STACK
RESOURCE = entry.RESOURCE
RETURN = entry.RETURN
FIGHTER = OWNER + 0x1000
SYMBOL = "?try_update_scalar_actions@ReimuObjectActionStateStagingView@th105@@QAE_NXZ"
HELPERS = dict(entry.animation.HELPERS)
HELPERS.update(
    {
        0x435160: (57, "oriented"),
        0x406360: (100, "sine"),
        0x4063D0: (94, "cosine"),
        0x53CBC0: (450, "pingpong"),
        0x68BAAE: (182, "fabs"),
        0x696387: (39, "control_word"),
    }
)
# The actual spawn body is a boundary, never a fabricated return.
SPAWN = 0x64CCB0


def export(path):
    facts.audit()
    obj = m.CoffObject(path, symbol_base=SYMBOL)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    values = defaultdict(set)
    for a, b in facts.RANGES:
        for i in md.disasm(c.target_bytes(a, b - a), a):
            for op in i.operands:
                if (
                    i.mnemonic.startswith("f")
                    and op.type == capstone.x86.X86_OP_MEM
                    and not op.mem.base
                    and not op.mem.index
                    and op.size in (4, 8)
                ):
                    v = c.target_bytes(op.mem.disp, op.size)
                    values[v[::-1].hex()].add(op.mem.disp)
    data = c.known_data_targets()
    for bits, addresses in values.items():
        if len(addresses) == 1:
            data["__real@" + bits] = (
                next(iter(addresses)),
                bytes.fromhex(bits)[::-1],
                frozenset({0}),
                "literal",
            )
    targets = c.known_targets()
    targets.update(
        {
            "?advance_frame_and_dispatch@CharacterObjectRuntime@th105@@QAEEXZ": 0x4351C0,
            "?lookup_orientation_sine_quantized_abs@th105@@YANM@Z": 0x406360,
            "?set_oriented_components_f0_f4@CharacterObjectRuntime@th105@@QAEXMM@Z": 0x435160,
            "?update_ping_pong_motion_and_periodic_spawn@CharacterObjectEffectEmitter@th105@@QAEXXZ": 0x53CBC0,
        }
    )
    b = c.coff_symbol_bytes(path, SYMBOL, S, len(obj.text), targets, data, {})
    return b


class Probe:
    def __init__(self, image, candidate=None):
        self.uc = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
        self.uc.mem_map(0x400000, 0x311000, unicorn.UC_PROT_READ | unicorn.UC_PROT_EXEC)
        self.uc.mem_write(0x400000, image)
        self.start = A if candidate is None else S
        self.size = 0 if candidate is None else len(candidate)
        if candidate is not None:
            self.uc.mem_map(S, 0x4000, unicorn.UC_PROT_READ | unicorn.UC_PROT_EXEC)
            self.uc.mem_write(S, candidate)
        for a in [OWNER, STACK, RESOURCE]:
            self.uc.mem_map(a, 0x10000)
        self.initial = self.uc.context_save()
        self.counts = Counter()
        self.visited = set()
        self.uc.hook_add(unicorn.UC_HOOK_CODE, self.instruction)
        self.uc.hook_add(unicorn.UC_HOOK_MEM_WRITE, self.write)

    def write(self, uc, access, a, n, value, user):
        if not (
            OWNER <= a <= a + n <= OWNER + 0x388
            or FIGHTER <= a <= a + n <= FIGHTER + 0x800
            or STACK <= a <= a + n <= STACK + 0x10000
            or entry.PARAMETERS <= a <= a + n <= entry.PARAMETERS + 16
        ):
            self.failure = f"unreviewed write {a:#x}"
            uc.emu_stop()

    def instruction(self, uc, a, n, user):
        in_root = (
            any(lo <= a < hi for lo, hi in facts.RANGES)
            if self.start == A
            else S <= a < S + self.size
        )
        if in_root:
            self.visited.add(a)
        elif a == SPAWN:
            sp = uc.reg_read(r.UC_X86_REG_ESP)
            args = list(struct.unpack("<7I", uc.mem_read(sp + 4, 28)))
            self.endpoint = {
                "kind": "spawn",
                "receiver": uc.reg_read(r.UC_X86_REG_ECX),
                "arguments": args[:5]
                + [bytes(uc.mem_read(args[5], args[6] * 4)).hex(), args[6]],
            }
            uc.emu_stop()
            return
        elif not any(lo <= a < lo + size for lo, (size, _) in HELPERS.items()):
            self.failure = f"unreviewed instruction {a:#x}"
            uc.emu_stop()
            return
        if a in HELPERS:
            self.trace.append(a)
            self.counts[a] += 1
        if bytes(uc.mem_read(a, 1)) in [b"\xc2", b"\xc3"]:
            sp = uc.reg_read(r.UC_X86_REG_ESP)
            if struct.unpack("<I", uc.mem_read(sp, 4))[0] == RETURN:
                self.saw_ret = True

    def evaluate(self, case):
        uc = self.uc
        uc.context_restore(self.initial)
        uc.mem_write(OWNER, bytes([0xA5]) * 0x388)
        uc.mem_write(FIGHTER, bytes([0xA5]) * 0x800)
        uc.mem_write(STACK + 0xA000, bytes(0x6000))
        uc.mem_write(RESOURCE, entry.graph({"action": case["action"], "request": 0}))
        seq = case.get("seq", 0)
        seq_block = entry.BLOCK + seq * 0x20
        frame = entry.FRAME + seq * 0x100
        if case.get("terminal"):
            uc.mem_write(seq_block + 0x14, bytes(12))
        if case["action"] == 980:
            uc.mem_write(
                entry.PARAMETERS + 4, struct.pack("<f", case.get("duration", 100.0))
            )
        values = [
            (0, "I", 0x6C40A4),
            (0xEC, "f", case.get("x", 640.0)),
            (0xF0, "f", 100.0),
            (0xF4, "f", case.get("vx", 3.25)),
            (0xF8, "f", -1.5),
            (0x104, "b", case.get("facing", -1)),
            (0x113, "B", case.get("alpha", 200)),
            (0x11C, "f", 1.25),
            (0x120, "f", 0.75),
            (0x12C, "f", 37.25),
            (0x130, "I", entry.VECTOR),
            (0x134, "B", 0),
            (0x13C, "h", case["action"]),
            (0x13E, "h", seq),
            (0x140, "h", 0),
            (0x142, "h", case.get("timer", 0)),
            (0x144, "i", case.get("counter", 0)),
            (0x148, "h", 1),
            (0x14C, "h", 3),
            (0x150, "I", frame),
            (0x158, "I", frame),
            (0x15C, "I", seq_block),
            (0x160, "I", entry.TREE),
            (0x168, "I", 0),
            (0x16C, "I", 0),
            (0x170, "I", 0),
            (0x180, "i", case.get("phase", 0)),
            (0x184, "B", case.get("index", 2)),
            (0x330, "i", 3),
            (0x340, "I", entry.PARAMETERS),
            (0x348, "I", FIGHTER),
            (0x364, "h", case.get("state", 0)),
            (0x370, "f", 3.5),
            (0x374, "f", 0.25),
        ]
        for off, fmt, value in values:
            uc.mem_write(OWNER + off, struct.pack("<" + fmt, value))
        for off, fmt, value in [
            (0x13C, "h", case.get("owner_action", 150)),
            (0xEC, "f", 515.5),
            (0xF0, "f", 23.0),
        ]:
            uc.mem_write(FIGHTER + off, struct.pack("<" + fmt, value))
        sentinels = {
            r.UC_X86_REG_EBX: 0x11111111,
            r.UC_X86_REG_ESI: 0x22222222,
            r.UC_X86_REG_EDI: 0x33333333,
            r.UC_X86_REG_EBP: 0x44444444,
        }
        for reg, value in sentinels.items():
            uc.reg_write(reg, value)
        sp = STACK + 0xFF00
        uc.mem_write(sp, struct.pack("<I", RETURN))
        uc.reg_write(r.UC_X86_REG_ESP, sp)
        uc.reg_write(r.UC_X86_REG_ECX, OWNER)
        uc.reg_write(r.UC_X86_REG_FPCW, case.get("cw", 0x27F))
        uc.reg_write(r.UC_X86_REG_FPSW, 0)
        uc.reg_write(r.UC_X86_REG_FPTAG, 0xFFFF)
        self.failure = None
        self.trace = []
        self.saw_ret = False
        self.endpoint = None
        uc.emu_start(self.start, RETURN, count=50000)
        if self.failure:
            raise ValueError((case, self.failure))
        if self.endpoint is None:
            if (
                not self.saw_ret
                or uc.reg_read(r.UC_X86_REG_EIP) != RETURN
                or uc.reg_read(r.UC_X86_REG_ESP) != sp + 4
                or any(uc.reg_read(reg) != value for reg, value in sentinels.items())
            ):
                raise ValueError(
                    (case, "RET ABI failed", hex(uc.reg_read(r.UC_X86_REG_EIP)))
                )
            if self.start != A and uc.reg_read(r.UC_X86_REG_EAX) & 255 != 1:
                raise ValueError((case, "source phase did not handle action"))
            if (
                uc.reg_read(r.UC_X86_REG_FPTAG) != 0xFFFF
                or uc.reg_read(r.UC_X86_REG_FPSW) & 0x3800
            ):
                raise ValueError((case, "x87 stack unbalanced"))
            self.endpoint = {"kind": "ret"}
        if uc.reg_read(r.UC_X86_REG_FPCW) != case.get("cw", 0x27F):
            raise ValueError((case, "floating control word changed"))
        return {
            "object": bytes(uc.mem_read(OWNER, 0x388)).hex(),
            "owner": bytes(uc.mem_read(FIGHTER, 0x800)).hex(),
            "parameters": bytes(uc.mem_read(entry.PARAMETERS, 16)).hex(),
            "endpoint": self.endpoint,
            "trace": self.trace,
            "cw": uc.reg_read(r.UC_X86_REG_FPCW),
            "top": (uc.reg_read(r.UC_X86_REG_FPSW) >> 11) & 7,
            "tags": uc.reg_read(r.UC_X86_REG_FPTAG),
        }


def cases():
    for action in [
        802,
        803,
        818,
        849,
        899,
        909,
        979,
        981,
        997,
        1000,
        -1,
        -32768,
        32767,
    ]:
        for timer in [0, 2]:
            yield {"action": action, "timer": timer}
    for x, phase, state, index, seq in itertools.product(
        [-401.0, -400.0, 640.0, 1680.0, 1681.0, float("nan")],
        [0, 1, 6],
        [0, 4, 5, 6],
        [2, 255],
        [0, 1, 2],
    ):
        yield {
            "action": 859,
            "x": x,
            "phase": phase,
            "state": state,
            "index": index,
            "seq": seq,
        }
    for action, alpha, seq, counter, timer, cw in itertools.product(
        [860, 861],
        [0, 9, 10, 24, 25, 26, 255],
        [0, 1, 2],
        [-1, 0, 7],
        [-1, 0, 2],
        [0x27F, 0x37F],
    ):
        yield {
            "action": action,
            "alpha": alpha,
            "seq": seq,
            "counter": counter,
            "timer": timer,
            "cw": cw,
        }
    for seq, state, alpha, counter, duration in itertools.product(
        [0, 1, 2], [0, 1], [0, 3, 4, 250, 251, 255], [0, 1, 9], [-1.0, 100.0]
    ):
        yield {
            "action": 980,
            "seq": seq,
            "state": state,
            "alpha": alpha,
            "counter": counter,
            "duration": duration,
        }
    for owner, seq, alpha, facing in itertools.product(
        [149, 150, 153, 154, 157, 158, 159], [0, 1, 2], [9, 10, 200], [-1, 0, 1]
    ):
        yield {
            "action": 998,
            "owner_action": owner,
            "seq": seq,
            "alpha": alpha,
            "facing": facing,
        }
    for action in [802, 859, 860, 861, 980, 998]:
        yield {
            "action": action,
            "terminal": True,
            "timer": 2,
            "seq": 0,
            "owner_action": 149,
        }


def main():
    global O
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument(
        "--output-dir", type=Path, default=R / "build/reimu-object-scalar-native"
    )
    args = parser.parse_args()
    O = args.output_dir
    O.mkdir(parents=True, exist_ok=True)
    path = args.object
    candidate = export(path)
    (O / "scalar-stage.bin").write_bytes(candidate)
    pe = pefile.PE(str(R / "resources/th105.exe"))
    image = bytearray(pe.get_memory_mapped_image())
    math = load("object_update_native_math", "scripts/iku_native_math.py")
    table, receipt = math.lookup_fixture(c)
    image[0x2FE8B0 : 0x2FE8B0 + len(table)] = table
    (O / "lookup-initialization.json").write_text(json.dumps(receipt, indent=2) + "\n")
    target = Probe(bytes(image))
    source = Probe(bytes(image), candidate)
    all_cases = list(cases())
    h = hashlib.sha256(json.dumps(all_cases, sort_keys=True).encode()).hexdigest()
    differences = []
    endpoints = Counter()
    for i, case in enumerate(all_cases):
        try:
            a = target.evaluate(case)
            b = source.evaluate(case)
        except Exception as e:
            print("FAILED CASE", i, case, repr(e), flush=True)
            raise
        endpoints[a["endpoint"]["kind"]] += 1
        if a != b:
            differing = [k for k in a if a[k] != b[k]]
            differences.append({"index": i, "case": case, "different": differing})
            if len(differences) < 5:
                print("DIFFERENCE", i, case, differing, flush=True)
    report = {
        "case_count": len(all_cases),
        "input_sha256": h,
        "differences": differences,
        "endpoints": dict(endpoints),
        "calls": dict(target.counts),
        "source_calls": dict(source.counts),
        "visited_target": len(target.visited),
        "visited_source": len(source.visited),
        "object_sha256": hashlib.sha256(path.read_bytes()).hexdigest(),
        "candidate_sha256": hashlib.sha256(candidate).hexdigest(),
        "build_provenance_verified": False,
        "lookup_initialization": receipt,
        "support_sha256": {
            str(p.relative_to(R)): hashlib.sha256(p.read_bytes()).hexdigest()
            for p in [
                Path(__file__),
                R / "scripts/audit-reimu-object-entry-calls.py",
                R / "scripts/audit-common-fighter-animation-paths.py",
                R / "scripts/iku_native_math.py",
                R / "scripts/compare-function.py",
                R / "scripts/audit-reimu-object-update-target.py",
                R / "src/characters/ReimuObjectActionStateStaging.cpp",
                R / "src/characters/ReimuObjectActionStateStaging.hpp",
            ]
        },
        "scope": "five supported actions/defaults; actual target helpers, no replacement returns; world spawn entry stops; no full-root or exact claim",
    }
    (O / "scalar-native.json").write_text(json.dumps(report, indent=2) + "\n")
    print(
        {
            k: report[k]
            for k in (
                "case_count",
                "input_sha256",
                "endpoints",
                "visited_target",
                "visited_source",
                "object_sha256",
                "candidate_sha256",
                "scope",
            )
        },
        "differences",
        len(differences),
        flush=True,
    )
    return int(bool(differences))


if __name__ == "__main__":
    raise SystemExit(main())
