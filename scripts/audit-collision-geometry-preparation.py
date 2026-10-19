"""Execute collision geometry preparation against the unchanged target helpers.

The finite ABI fixture supplies bounded read-only frame vectors, descriptor data,
a cosine resource table and an SSE2 CPU flag. Both cold and warm cache paths run;
there is no helper-result substitution or instruction patch. Error/throw paths,
legacy x87 ceil, original game startup tables and canonical equality are outside
this sampled execution claim. The strict compiler comparator remains separate.
"""

from pathlib import Path
from collections import Counter
import argparse, hashlib, importlib.util, itertools, json, math, struct, sys, tomllib
import pefile
import capstone
import unicorn
from unicorn import x86_const as reg
from unicorn import unicorn as unicorn_api

R = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(R / "scripts"))
spec = importlib.util.spec_from_file_location(
    "geometry_native_c", R / "scripts/compare-function.py"
)
c = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = c
spec.loader.exec_module(c)
ADDRESS, SIZE, CANDIDATE = 0x45C500, 2156, 0x800000
BODY_SHA = "79b6295ec257dabdb090b1e3ae8943ccbfd2468fc9d438785215c75ddfec4dff"
OWNER, STACK, RETURN, RESOURCE = 0x2000000, 0x2100000, 0x710000, 0x3000000
FRAME, PRIMARY, EXTENSION, BOX_A, BOX_B, SHAPE_VECTOR, SHAPES = [
    RESOURCE + x for x in (0x100, 0x400, 0x500, 0x1000, 0x2000, 0x3000, 0x4000)
]
COSINE, CPU_SSE2 = 0x6FE8B0, 0x7039C4
HELPERS = {
    0x45B760: 335,
    0x45B8B0: 445,
    0x45BA70: 1386,
    0x406480: 34,
    0x4064B0: 30,
    0x68A1A0: 171,
    0x68B510: 285,
}


def cases(smoke):
    counts = ((0, 0), (2, 1)) if smoke else ((0, 0), (2, 1), (4, 4))
    flags = (
        (0, 0x400000, 0x800000, 0x1C00000)
        if smoke
        else tuple(i * 0x400000 for i in range(8))
    )
    faces = (-1, 1) if smoke else (-1, 0, 1, 2)
    controls = (0x27F,) if smoke else (0x27F, 0x37F)
    for (a, b), bits, face, extension, cw in itertools.product(
        counts, flags, faces, (0, 1, 2), controls
    ):
        patterns = (0,) if a == 0 else (0, 1, 2)
        for pattern in patterns:
            yield dict(
                a=a,
                b=b,
                flags=bits,
                face=face,
                extension=extension,
                cw=cw,
                pattern=pattern,
                angle=(30.75, -45.5, 135.25, 225.875)[
                    (bits // 0x400000 + pattern + extension) % 4
                ],
                primary=bool((bits // 0x400000 + pattern + extension) % 2),
            )


def graph(case):
    image = bytearray(0x10000)

    def put(address, fmt, *values):
        struct.pack_into("<" + fmt, image, address - RESOURCE, *values)

    put(FRAME + 0x4C, "I", case["flags"])
    put(FRAME + 0x54, "I", PRIMARY if case["primary"] else 0)
    for off, address, count, stride in (
        (0x58, BOX_B, case["b"], 16),
        (0x68, BOX_A, case["a"], 16),
        (0x78, SHAPE_VECTOR, case["a"], 4),
    ):
        begin = address if count else 0
        put(
            FRAME + off,
            "IIII",
            0,
            begin,
            begin + count * stride,
            begin + count * stride,
        )
    put(PRIMARY, "iiii", -13, -17, 23, 31)
    put(
        EXTENSION,
        "iiiihhh",
        -21,
        -9,
        19,
        27,
        0 if case["extension"] == 1 else 135,
        7,
        -11,
    )
    for i in range(4):
        put(BOX_A + i * 16, "iiii", -20 - i, -30 + i, 40 + i, 50 + i)
        put(BOX_B + i * 16, "iiii", -35 + i, -45 - i, 55 + i, 65 - i)
        put(SHAPES + i * 16, "iiii", 4 + i, 7 + i, 11 + i, 13 + i)
        present = case["pattern"] == 1 or (case["pattern"] == 2 and i % 2 == 0)
        put(SHAPE_VECTOR + i * 4, "I", SHAPES + i * 16 if present else 0)
    return bytes(image)


class Probe:
    def __init__(self, image, table, candidate=None):
        self.uc = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
        self.uc.mem_map(0x400000, 0x311000, unicorn.UC_PROT_READ | unicorn.UC_PROT_EXEC)
        self.uc.mem_write(0x400000, image)
        # Data-only environment inputs: an SSE2-capable CRT and a finite cosine table.
        self.uc.mem_write(CPU_SSE2, struct.pack("<I", 1))
        self.uc.mem_write(COSINE, table)
        self.start = ADDRESS if candidate is None else CANDIDATE
        self.size = SIZE if candidate is None else len(candidate)
        if candidate is not None:
            self.uc.mem_map(
                CANDIDATE, 0x2000, unicorn.UC_PROT_READ | unicorn.UC_PROT_EXEC
            )
            self.uc.mem_write(CANDIDATE, candidate)
        for address in (OWNER, STACK):
            self.uc.mem_map(address, 0x10000)
        self.uc.mem_map(RESOURCE, 0x10000, unicorn.UC_PROT_READ)
        self.initial = self.uc.context_save()
        self.counts = Counter()
        self.visited = set()
        self.uc.hook_add(unicorn.UC_HOOK_CODE, self.step)
        self.uc.hook_add(unicorn.UC_HOOK_MEM_WRITE, self.write)

    def write(self, uc, access, address, size, value, unused):
        if not (
            OWNER <= address <= address + size <= OWNER + 0x330
            or STACK <= address <= address + size <= STACK + 0x10000
        ):
            self.failure = f"unreviewed write {address:#x}"
            uc.emu_stop()

    def pointer(self, address):
        if RESOURCE <= address < RESOURCE + 0x10000:
            return [
                "resource",
                address - RESOURCE,
                bytes(self.uc.mem_read(address, 16)).hex(),
            ]
        if OWNER <= address < OWNER + 0x330:
            return [
                "owner",
                address - OWNER,
                bytes(self.uc.mem_read(address, 16)).hex(),
            ]
        if STACK <= address < STACK + 0x10000:
            return ["local", bytes(self.uc.mem_read(address, 16)).hex()]
        raise ValueError(f"unreviewed pointer {address:#x}")

    def step(self, uc, address, size, unused):
        if self.start <= address < self.start + self.size:
            self.visited.add(address - self.start)
        elif not any(a <= address < a + n for a, n in HELPERS.items()):
            self.failure = f"unreviewed execution {address:#x}"
            uc.emu_stop()
            return
        if address in HELPERS:
            self.counts[address] += 1
            if address in (0x45B760, 0x45B8B0, 0x45BA70):
                if uc.reg_read(reg.UC_X86_REG_ECX) != OWNER:
                    self.failure = "wrong geometry receiver"
                    uc.emu_stop()
                    return
                sp = uc.reg_read(reg.UC_X86_REG_ESP)
                if address == 0x45BA70:
                    args = struct.unpack("<IIIIII", uc.mem_read(sp + 4, 24))

                    def lowword(value):
                        return struct.unpack("<h", struct.pack("<H", value & 65535))[0]

                    left, right = args[4:]
                    if not (
                        STACK <= left <= left + 16 <= STACK + 0x10000
                        and STACK <= right <= right + 16 <= STACK + 0x10000
                        and abs(left - right) >= 16
                    ):
                        self.failure = "invalid oriented output slots"
                        uc.emu_stop()
                        return
                    self.trace.append(
                        [
                            hex(address),
                            self.pointer(args[0]),
                            *[lowword(x) for x in args[1:4]],
                        ]
                    )
                else:
                    source, dest = struct.unpack("<II", uc.mem_read(sp + 4, 8))
                    if not OWNER <= dest <= dest + 16 <= OWNER + 0x330:
                        self.failure = "invalid world-box output"
                        uc.emu_stop()
                        return
                    self.trace.append(
                        [hex(address), self.pointer(source), dest - OWNER]
                    )
        raw = bytes(uc.mem_read(address, size))
        if raw[0] in (0xC2, 0xC3):
            sp = uc.reg_read(reg.UC_X86_REG_ESP)
            if struct.unpack("<I", uc.mem_read(sp, 4))[0] == RETURN:
                self.saw_ret = True

    def put(self, offset, fmt, value):
        self.uc.mem_write(OWNER + offset, struct.pack("<" + fmt, value))

    def phase(self, case, warm):
        uc = self.uc
        self.put(0xEC, "f", 37.25 + (0.375 if warm else 0))
        self.put(0xF0, "f", -12.5 + (0.625 if warm else 0))
        self.put(0x104, "b", -case["face"] if warm and case["face"] else case["face"])
        self.put(0x174, "H", 0x8123 + (1 if warm else 0))
        self.put(0x13C, "H", 0x9001 + (1 if warm else 0))
        self.put(0x180, "I", 0x12345678 + (1 if warm else 0))
        self.put(0x184, "B", 0x81 + (1 if warm else 0))
        saved = {
            reg.UC_X86_REG_EBX: 0x11111111,
            reg.UC_X86_REG_ESI: 0x22222222,
            reg.UC_X86_REG_EDI: 0x33333333,
            reg.UC_X86_REG_EBP: 0x44444444,
        }
        for r, v in saved.items():
            uc.reg_write(r, v)
        sp = STACK + 0xFF00
        uc.mem_write(sp, struct.pack("<I", RETURN))
        uc.reg_write(reg.UC_X86_REG_ESP, sp)
        uc.reg_write(reg.UC_X86_REG_ECX, OWNER)
        self.trace = []
        self.saw_ret = False
        self.failure = None
        uc.emu_start(self.start, RETURN, count=50000)
        if self.failure:
            raise ValueError(f"{case} warm={warm}: {self.failure}")
        if (
            not self.saw_ret
            or uc.reg_read(reg.UC_X86_REG_EIP) != RETURN
            or uc.reg_read(reg.UC_X86_REG_ESP) != sp + 4
            or any(uc.reg_read(r) != v for r, v in saved.items())
        ):
            raise ValueError("native RET/nonvolatile ABI failed")
        if (uc.reg_read(reg.UC_X86_REG_FPSW) >> 11) & 7:
            raise ValueError("unbalanced x87 stack")
        if uc.reg_read(reg.UC_X86_REG_FPCW) != case["cw"]:
            raise ValueError("control word changed")
        return dict(
            object=bytes(uc.mem_read(OWNER, 0x330)).hex(),
            trace=self.trace,
            mxcsr=uc.reg_read(reg.UC_X86_REG_MXCSR),
        )

    def evaluate(self, case):
        uc = self.uc
        uc.context_restore(self.initial)
        uc.mem_write(OWNER, bytes([0xA5]) * 0x330)
        uc.mem_write(STACK + 0xC000, bytes(0x4000))
        uc.mem_write(RESOURCE, graph(case))
        for off, fmt, value in [
            (0x108, "f", 25.5),
            (0x10C, "f", -15.75),
            (0x12C, "f", case["angle"]),
            (0x158, "I", FRAME),
            (0x15C, "I", RESOURCE + 0x600),
            (0x194, "I", EXTENSION if case["extension"] else 0),
            (0x1A4, "I", 0),
        ]:
            self.put(off, fmt, value)
        uc.reg_write(reg.UC_X86_REG_FPCW, case["cw"])
        uc.reg_write(reg.UC_X86_REG_MXCSR, 0x1F80)
        return [self.phase(case, False), self.phase(case, True)]


def audit(path, smoke):
    object_hash = hashlib.sha256(path.read_bytes()).hexdigest()
    target_hash = c.verify_target()
    raw = c.target_bytes(ADDRESS, SIZE)
    if hashlib.sha256(raw).hexdigest() != BODY_SHA:
        raise ValueError("target changed")
    unit = tomllib.loads((R / "config/match-units.toml").read_text())["units"][
        "gpt-web-collision-geometry-preparation"
    ]
    function = unit["functions"][0]
    if int(function["address"], 0) != ADDRESS:
        raise ValueError("configured root address changed")
    rel = c.known_targets()
    rel.update(
        {
            name: int(address, 0)
            for name, address in (
                row.split("=", 1) for row in function["rel32_targets"]
            )
        }
    )
    candidate = c.coff_symbol_bytes(
        path, function["symbol_base"], CANDIDATE, 10000, rel, c.known_data_targets(), {}
    )
    canonical = c.coff_symbol_bytes(
        path, function["symbol_base"], ADDRESS, 10000, rel, c.known_data_targets(), {}
    )
    image = pefile.PE(str(R / "resources/th105.exe")).get_memory_mapped_image()
    table = b"".join(
        struct.pack("<f", math.cos(i * math.pi / 1800.0)) for i in range(3600)
    )
    probes = [Probe(image, table), Probe(image, table, candidate)]
    inputs = list(cases(smoke))
    mismatches = 0
    examples = []
    digest = hashlib.sha256()
    if len(inputs) != (96 if smoke else 1344):
        raise ValueError("incomplete input matrix")
    for n, case in enumerate(inputs):
        digest.update(json.dumps(case, sort_keys=True).encode())
        expected, actual = [p.evaluate(case) for p in probes]
        if expected != actual:
            mismatches += 1
            if len(examples) < 4:
                examples.append(
                    dict(
                        case=case,
                        object_diff=[
                            [
                                hex(i)
                                for i, (a, b) in enumerate(
                                    zip(
                                        bytes.fromhex(x["object"]),
                                        bytes.fromhex(y["object"]),
                                    )
                                )
                                if a != b
                            ]
                            for x, y in zip(expected, actual)
                        ],
                        trace_equal=[
                            x["trace"] == y["trace"] for x, y in zip(expected, actual)
                        ],
                    )
                )
        if n % 200 == 0:
            print(
                f"native {n}/{len(inputs)} mismatches={mismatches}",
                file=sys.stderr,
                flush=True,
            )
    if object_hash != hashlib.sha256(path.read_bytes()).hexdigest():
        raise ValueError("object changed during audit")
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    rows = list(decoder.disasm(raw, ADDRESS))
    failure_only = {
        i.address - ADDRESS
        for i in rows
        if i.mnemonic == "call" and i.op_str == "0x68a143"
    } | {0xF1, 0x4E8}
    if set(i.address - ADDRESS for i in rows) - probes[0].visited != failure_only:
        raise ValueError("normal-path target coverage incomplete")
    unvisited = [
        hex(i.address - ADDRESS)
        for i in decoder.disasm(raw, ADDRESS)
        if i.address - ADDRESS not in probes[0].visited
    ]
    return dict(
        schema="th105-collision-geometry-native-v1",
        target_sha256=target_hash,
        body_sha256=BODY_SHA,
        object_sha256=object_hash,
        candidate_size=len(candidate),
        canonical_payload_sha256=hashlib.sha256(canonical).hexdigest(),
        cases=len(inputs),
        native_calls_per_side=len(inputs) * 2,
        mismatch_count=mismatches,
        examples=examples,
        input_sha256=digest.hexdigest(),
        cosine_fixture_sha256=hashlib.sha256(table).hexdigest(),
        audit_source_sha256=hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
        unicorn_version=unicorn.__version__,
        unicorn_library_sha256=hashlib.sha256(
            Path(unicorn_api._uc._name).read_bytes()
        ).hexdigest(),
        python_version=sys.version.split()[0],
        helper_sha256={
            hex(a): hashlib.sha256(c.target_bytes(a, n)).hexdigest()
            for a, n in HELPERS.items()
        },
        helper_counts=[{hex(k): v for k, v in p.counts.items()} for p in probes],
        visited=[len(p.visited) for p in probes],
        unvisited_target_offsets=unvisited,
        scope="finite bounded vectors with cold/warm caches; actual geometry, angle, conversion and SSE2 ceil code; data-only cosine/CPU fixtures; no invalid containers, throw execution, original startup-table or canonical equality claim",
        build_provenance_verified=False,
    )


if __name__ == "__main__":
    p = argparse.ArgumentParser()
    p.add_argument("object", type=Path)
    p.add_argument("--smoke", action="store_true")
    a = p.parse_args()
    j = audit(a.object, a.smoke)
    print(json.dumps(j, indent=2))
    sys.exit(bool(j["mismatch_count"]))
