#!/usr/bin/env python3
"""Compare bounded native collision-phase execution, separately from exactness.

Full-entry fixtures avoid same-side hit effects. Tail-entry fixtures explicitly
supply the attested 2Ch-frame state to test wide guards and signed low-word sums.
All game, geometry, checked-list and getter instructions run from the target PE.
Only malloc/free environment boundaries are callbacks; code is never patched.
"""

from pathlib import Path
import sys, importlib.util, struct, json, hashlib, math, collections, itertools, argparse, tomllib, csv
import pefile, unicorn
from unicorn import x86_const as r
from unicorn import unicorn as unicorn_api

R = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(R / "scripts"))
spec = importlib.util.spec_from_file_location(
    "phase_native_c", R / "scripts/compare-function.py"
)
c = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = c
spec.loader.exec_module(c)
ROOT = 0x46DFF0
SIZE = 1452
SOURCE = 0x800000
CTX = 0x2000000
STACK = 0x2100000
DATA = 0x3000000
RETURN = 0x710000
ACTORS = [CTX + 0x1000 * i for i in range(1, 7)]
MANAGERS = [CTX + 0x8000, CTX + 0x9000]
HEAP = CTX + 0x10000


class Probe:
    def __init__(self, image, body=None):
        u = self.u = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
        u.mem_map(0, 0x1000)
        u.mem_map(0x400000, 0x311000, unicorn.UC_PROT_READ | unicorn.UC_PROT_EXEC)
        u.mem_write(0x400000, image)
        u.mem_write(0x7039C4, struct.pack("<I", 1))
        u.mem_write(
            0x6FE8B0,
            b"".join(
                struct.pack("<f", math.cos(i * math.pi / 1800)) for i in range(3600)
            ),
        )
        self.start = ROOT if body is None else SOURCE
        self.size = SIZE if body is None else len(body)
        if body is not None:
            u.mem_map(SOURCE, 0x2000, unicorn.UC_PROT_READ | unicorn.UC_PROT_EXEC)
            u.mem_write(SOURCE, body)
        u.mem_map(CTX, 0x20000)
        u.mem_map(STACK, 0x10000)
        u.mem_map(DATA, 0x10000, unicorn.UC_PROT_READ)
        u.hook_add(unicorn.UC_HOOK_CODE, self.guarded_step)
        u.hook_add(unicorn.UC_HOOK_MEM_WRITE, self.guarded_write)
        self.initial = u.context_save()
        self.visited = set()
        self.calls = collections.Counter()
        self.executed = set()
        self.getter_calls = 0

    def guarded_step(self, *args):
        try:
            self.step(*args)
        except Exception as exc:
            self.failure = str(exc)
            self.u.emu_stop()

    def guarded_write(self, *args):
        try:
            self.write(*args)
        except Exception as exc:
            self.failure = str(exc)
            self.u.emu_stop()

    def put(self, a, fmt, *v):
        self.u.mem_write(a, struct.pack("<" + fmt, *v))

    def word(self, a):
        return struct.unpack("<I", self.u.mem_read(a, 4))[0]

    def write(self, u, access, address, size, value, unused):
        if not (
            address == 0
            and size == 4
            or CTX <= address < address + size <= CTX + 0x20000
            or STACK <= address < address + size <= STACK + 0x10000
        ):
            raise ValueError(f"unreviewed write {address:x} size{size}")

    def step(self, u, a, n, unused):
        if self.start <= a < self.start + self.size:
            self.visited.add(a - self.start)
        self.executed.add(a)
        if a == 0x4B9DA0:
            self.getter_calls += 1
        if self.start <= a < self.start + self.size and bytes(u.mem_read(a, 1)) in (
            b"\xc2",
            b"\xc3",
        ):
            if self.word(u.reg_read(r.UC_X86_REG_ESP)) == RETURN:
                self.saw_return = True
        if a in [0x68A143, 0x68A153]:
            raise ValueError(f"error path {a:x}")
        if a in [0x689DCB, 0x6898EA]:
            sp = u.reg_read(r.UC_X86_REG_ESP)
            arg = self.word(sp + 4)
            returned = self.word(sp)
            u.reg_write(r.UC_X86_REG_ECX, 0xA1A1A1A1)
            u.reg_write(r.UC_X86_REG_EDX, 0xB2B2B2B2)
            if a == 0x689DCB:
                if arg != 12 or returned != 0x421F37:
                    raise ValueError(f"unreviewed allocation {arg} from {returned:x}")
                result = HEAP + len(self.allocated) * 16
                self.allocated.append(result)
                self.alloc_trace.append(["new", 12, result])
                u.reg_write(r.UC_X86_REG_EAX, result)
            else:
                if (
                    arg not in self.old_nodes
                    or not self.start <= returned < self.start + self.size
                ):
                    raise ValueError(f"unreviewed free {arg:x}")
                self.old_nodes.remove(arg)
                self.alloc_trace.append(["free", arg])
                u.reg_write(r.UC_X86_REG_EAX, 0xF3F3F3F3)
            u.reg_write(r.UC_X86_REG_EIP, self.word(sp))
            u.reg_write(r.UC_X86_REG_ESP, sp + 4)
            return
        if not (0x400000 <= a < 0x6BF33A or SOURCE <= a < SOURCE + 0x2000):
            raise ValueError(f"unreviewed execution {a:x}")
        if bytes(u.mem_read(a, 1)) == b"\xe8":
            target = a + 5 + struct.unpack("<i", u.mem_read(a + 1, 4))[0]
            self.calls[target] += 1
            self.call_order.append(target)

    def head(self, a, values):
        sentinel = a + 0x80
        self.put(a, "III", 0, sentinel, len(values))
        self.put(sentinel, "III", sentinel, sentinel, 0)
        nodes = [a + 0x100 + 16 * i for i in range(len(values))]
        if nodes:
            self.put(sentinel, "II", nodes[0], nodes[-1])
        for i, (n, v) in enumerate(zip(nodes, values)):
            self.put(
                n,
                "III",
                nodes[i + 1] if i + 1 < len(nodes) else sentinel,
                nodes[i - 1] if i else sentinel,
                v,
            )

    def evaluate(self, case, tail=False):
        u = self.u
        u.context_restore(self.initial)
        u.mem_write(CTX, bytes(0x20000))
        u.mem_write(STACK, bytes(0x10000))
        u.mem_write(DATA, bytes(0x10000))
        self.put(0, "I", 0xFFFFFFFF)
        self.allocated = []
        self.alloc_trace = []
        self.failure = None
        self.saw_return = False
        self.old_nodes = set()
        self.call_order = []
        self.put(CTX + 0xC, "II", *ACTORS[:2])
        for off in [0x2C, 0x38, 0x44, 0x50, 0x5C, 0x68]:
            # Separate sentinels/nodes preserve each list's ownership.
            h = CTX + 0xA000 + (off - 0x2C) * 0x40
            self.put(CTX + off, "III", 0, h, case.get("old", 0))
            nodes = [h + 0x40 + 16 * i for i in range(case.get("old", 0))]
            self.put(h, "III", nodes[0] if nodes else h, nodes[-1] if nodes else h, 0)
            for i, n in enumerate(nodes):
                self.put(
                    n,
                    "III",
                    nodes[i + 1] if i + 1 < len(nodes) else h,
                    nodes[i - 1] if i else h,
                    0xDEAD0000 + i,
                )
                self.old_nodes.add(n)
        for side, m in enumerate(MANAGERS):
            self.put(m, "I", 0x6C40FC)
            values = [ACTORS[2 + side * 2 + i] for i in range(case.get("objects", 1))]
            self.head(m + 0x58, values)
        for i, a in enumerate(ACTORS):
            side = i if i < 2 else (i - 2) // 2
            frame = DATA + 0x1000 + i * 0x200
            box = frame + 0x100
            isfighter = i < 2
            na = case.get("a", 1)
            nb = case.get("b", 1)
            self.put(
                frame + 0x4C,
                "II",
                case.get("flags", 0),
                case.get("friendly", 0) * 0x100000,
            )
            for off, count, start in [(0x58, nb, box), (0x68, na, box + 0x40)]:
                self.put(
                    frame + off,
                    "IIII",
                    0,
                    start if count else 0,
                    start + count * 16 if count else 0,
                    start + count * 16 if count else 0,
                )
            self.put(
                frame + 0x78,
                "IIII",
                0,
                box + 0x80 if na else 0,
                box + 0x80 + na * 4 if na else 0,
                box + 0x80 + na * 4 if na else 0,
            )
            self.put(box, "iiii", -10, -10, 10, 10)
            self.put(box + 0x40, "iiii", -10, -10, 10, 10)
            self.put(a + 0xEC, "ff", float(side * 10000 + i * 1000), 0.0)
            self.put(a + 0x104, "b", 1)
            self.put(a + 0x12C, "f", 45.75)
            self.put(a + 0x13C, "h", 1)
            self.put(a + 0x158, "II", frame, DATA + 0x100)
            self.put(a + 0x16C, "IIhh", ACTORS[side], ACTORS[1 - side], 100, 200)
            self.put(
                a + 0x180,
                "Ib",
                case.get("result", 0) if not isfighter else 0,
                case.get("status", 1),
            )
            self.put(a + 0x1A4, "I", 0)
            if not isfighter and case.get("extension"):
                ext = DATA + 0x8000 + i * 0x40
                self.put(
                    ext,
                    "iiiihhh",
                    -10,
                    -10,
                    10,
                    10,
                    90 if case.get("extension") == 2 else 0,
                    0,
                    0,
                )
                self.put(a + 0x194, "I", ext)
            if isfighter:
                self.put(a + 0x334, "b", side)
                self.put(a + 0x4E9, "BB", 9 + side, 0)
                self.put(a + 0x658, "I", MANAGERS[side])
                self.put(a + 0x558, "h", 500)
        self.put(
            CTX + 0x74,
            "iiii",
            case.get("delta", 7),
            case.get("delta", 8),
            case.get("delta558", 9),
            case.get("delta558", 10),
        )
        if tail:
            for a in ACTORS[:2]:
                self.put(a + 0x174, "hh", case["current"], case["maximum"])
        sp = STACK + 0xFF00
        saved = {
            r.UC_X86_REG_EBX: 0x11111111,
            r.UC_X86_REG_EBP: 0x22222222,
            r.UC_X86_REG_ESI: 0x33333333,
            r.UC_X86_REG_EDI: 0x44444444,
        }
        for k, v in saved.items():
            u.reg_write(k, v)
        self.put(sp, "I", RETURN)
        u.reg_write(r.UC_X86_REG_ESP, sp)
        u.reg_write(r.UC_X86_REG_ECX, CTX)
        u.reg_write(r.UC_X86_REG_FPCW, 0x27F)
        u.reg_write(r.UC_X86_REG_MXCSR, 0x1F80)
        entry = self.start
        if tail:
            frame = sp - 0x3C
            self.put(
                frame,
                "IIII",
                saved[r.UC_X86_REG_EDI],
                saved[r.UC_X86_REG_ESI],
                saved[r.UC_X86_REG_EBP],
                saved[r.UC_X86_REG_EBX],
            )
            self.put(frame + 0x30, "I", CTX + 0x7C)
            u.reg_write(r.UC_X86_REG_ESP, frame)
            entry += 0x54B
        u.emu_start(entry, RETURN, count=300000)
        if self.failure:
            raise ValueError(self.failure)
        assert self.saw_return
        assert (
            u.reg_read(r.UC_X86_REG_EIP) == RETURN
            and u.reg_read(r.UC_X86_REG_ESP) == sp + 4
        )
        assert all(u.reg_read(k) == v for k, v in saved.items())
        assert self.word(0) == 0xFFFFFFFF
        if not tail and self.old_nodes:
            raise ValueError("old nodes not released")
        if (u.reg_read(r.UC_X86_REG_FPSW) >> 11) & 7 or u.reg_read(
            r.UC_X86_REG_FPCW
        ) != 0x27F:
            raise ValueError("x87 ABI changed")
        return dict(
            object=bytes(u.mem_read(CTX, 0x20000)),
            allocations=self.alloc_trace,
            calls=self.call_order,
            mxcsr=u.reg_read(r.UC_X86_REG_MXCSR),
        )


def audit(obj, smoke=False):
    target_hash = c.verify_target()
    object_hash = hashlib.sha256(obj.read_bytes()).hexdigest()
    raw = c.target_bytes(ROOT, SIZE)
    if (
        hashlib.sha256(raw).hexdigest()
        != "ca24d275c213508fd8a634e8712736c20297637739051f98147bebbd8f8bca53"
    ):
        raise ValueError("target root changed")
    if c.target_bytes(0x4B9DA0, 4) != bytes.fromhex("8d4158c3") or c.target_bytes(
        0x6C40FC + 0x24, 4
    ) != struct.pack("<I", 0x4B9DA0):
        raise ValueError("getter/vtable changed")
    function = tomllib.loads((R / "config/match-units.toml").read_text())["units"][
        "gpt-web-battle-collision-phase"
    ]["functions"][0]
    if int(function["address"], 0) != ROOT:
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
        obj, function["symbol_base"], SOURCE, 10000, rel, c.known_data_targets(), {}
    )
    canonical = c.coff_symbol_bytes(
        obj, function["symbol_base"], ROOT, 10000, rel, c.known_data_targets(), {}
    )
    # The tail fixture uses only storage justified by these common entry instructions.
    if raw[:16] != canonical[:16] or raw[0x54B:0x554] != canonical[0x54B:0x554]:
        raise ValueError("tail-entry frame precondition changed")
    image = pefile.PE(str(R / "resources/th105.exe")).get_memory_mapped_image()
    p = [Probe(image), Probe(image, body)]
    cases = []
    for n, ((a, b), flags, extension) in enumerate(
        itertools.product(((0, 0), (1, 0), (0, 1), (1, 1)), range(8), range(3))
    ):
        cases.append(
            dict(
                a=a,
                b=b,
                flags=flags * 0x400000,
                extension=extension,
                objects=(flags + extension) % 3,
                status=(-1, 0, 1)[(a + b + flags + extension) % 3],
                result=2 if n % 5 == 0 else 0,
                old=2 if n % 2 else 0,
                friendly=0,
            )
        )
    for status, result, objects in itertools.product((-1, 0, 1), (0, 2), (0, 1, 2)):
        cases.append(
            dict(
                a=1,
                b=1,
                status=status,
                result=result,
                objects=objects,
                old=2,
                friendly=0,
            )
        )
    tails = [
        dict(
            current=cur,
            maximum=maximum,
            delta=delta,
            delta558=(0, 7, -9)[n % 3],
            objects=0,
            a=0,
            b=0,
        )
        for n, (cur, maximum, delta) in enumerate(
            itertools.product(
                (-32768, -1, 0, 1, 100, 32767),
                (-32768, -1, 0, 99, 200, 32767),
                (
                    -65536,
                    -32769,
                    -32768,
                    -1,
                    0,
                    1,
                    32767,
                    32768,
                    65535,
                    65536,
                    0x12345678,
                ),
            )
        )
    ]
    if smoke:
        cases = cases[::8]
        tails = tails[::17]
    mismatches = {"full": 0, "tail": 0}
    examples = []
    digest = hashlib.sha256()
    for lane, inputs in [("full", cases), ("tail", tails)]:
        for n, case in enumerate(inputs):
            digest.update(json.dumps([lane, case], sort_keys=True).encode())
            out = [x.evaluate(case, lane == "tail") for x in p]
            if out[0] != out[1]:
                mismatches[lane] += 1
                if len(examples) < 4:
                    examples.append(
                        dict(
                            lane=lane,
                            case=case,
                            object_differences=[
                                hex(i)
                                for i, (a, b) in enumerate(
                                    zip(out[0]["object"], out[1]["object"])
                                )
                                if a != b
                            ][:64],
                            calls_equal=out[0]["calls"] == out[1]["calls"],
                            allocations_equal=out[0]["allocations"]
                            == out[1]["allocations"],
                        )
                    )
            if n % 32 == 0:
                print(
                    f"native {lane} {n}/{len(inputs)} mismatches={mismatches[lane]}",
                    file=sys.stderr,
                    flush=True,
                )
    if object_hash != hashlib.sha256(obj.read_bytes()).hexdigest():
        raise ValueError("object changed")
    if p[0].calls != p[1].calls or p[0].getter_calls != p[1].getter_calls:
        raise ValueError("helper counts differ")
    inventory = {
        int(row["address"], 0): int(row["size"])
        for row in csv.DictReader((R / "config/functions.csv").open())
    }
    helpers = set(p[0].calls) | {0x4B9DA0}
    import capstone

    rows = list(
        capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32).disasm(raw, ROOT)
    )
    unvisited = {i.address - ROOT for i in rows} - p[0].visited
    invalid_calls = {
        i.address - ROOT
        for i in rows
        if i.mnemonic == "call" and i.op_str == "0x68a143"
    }
    padding = {0x8D, 0x3F8, 0x3FF, 0x4B9}
    same_side_hit = {0x514, 0x516, 0x51D, 0x51F, 0x522, 0x526, 0x527, 0x528}
    coverage_complete = unvisited == invalid_calls | padding | same_side_hit
    if not smoke and not coverage_complete:
        raise ValueError("bounded target execution coverage changed")
    return dict(
        schema="th105-battle-collision-phase-native-v1",
        target_sha256=target_hash,
        body_sha256=hashlib.sha256(raw).hexdigest(),
        object_sha256=object_hash,
        canonical_payload_sha256=hashlib.sha256(canonical).hexdigest(),
        candidate_size=len(body),
        full_cases=len(cases),
        tail_entry_cases=len(tails),
        mismatches=mismatches,
        examples=examples,
        input_sha256=digest.hexdigest(),
        audit_source_sha256=hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
        python_version=sys.version.split()[0],
        unicorn_version=unicorn.__version__,
        unicorn_library_sha256=hashlib.sha256(
            Path(unicorn_api._uc._name).read_bytes()
        ).hexdigest(),
        cosine_fixture_sha256=hashlib.sha256(
            b"".join(
                struct.pack("<f", math.cos(i * math.pi / 1800)) for i in range(3600)
            )
        ).hexdigest(),
        allocator_volatile_registers={
            "ECX": "0xA1A1A1A1",
            "EDX": "0xB2B2B2B2",
            "free_EAX": "0xF3F3F3F3",
        },
        helper_counts={hex(k): v for k, v in sorted(p[0].calls.items())},
        getter_calls_per_side=p[0].getter_calls,
        helper_sha256={
            hex(a): hashlib.sha256(c.target_bytes(a, inventory[a])).hexdigest()
            for a in sorted(helpers)
        },
        visited=[len(x.visited) for x in p],
        bounded_target_coverage_complete=coverage_complete,
        unvisited_target_offsets=[
            hex(i.address - ROOT) for i in rows if i.address - ROOT not in p[0].visited
        ],
        allocator_boundary="Only51-byte native Buynode's12-byte allocation and root clear's validated original-node frees; volatile registers clobbered, checked-list instructions execute unchanged",
        scope="114 bounded full-entry no-self-hit fixtures and396 separate2Ch-frame tail entries; actual game/getter/geometry/container code; data-only SSE2/cosine fixtures; no invalid containers, throw path, same-side hit effect/callback environment, full game startup or canonical-equality claim",
        build_provenance_verified=False,
    )


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument("--smoke", action="store_true")
    args = parser.parse_args()
    result = audit(args.object, args.smoke)
    print(json.dumps(result, indent=2))
    sys.exit(bool(sum(result["mismatches"].values())))
