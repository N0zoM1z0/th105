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
PARENT = OWNER + 0x2000
PARENT_PARAMETERS = RESOURCE + 0xE000
RELATED = OWNER + 0x3000
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
        0x5575C0: (200, "owner_effect_gate"),
        0x4963A0: (66, "state_six_counter"),
        0x4963F0: (43, "release_secondary"),
        0x4E0BF0: (314, "turn_toward_related"),
        0x406540: (63, "atan2"),
        0x4066B0: (279, "mt_next"),
        0x4067D0: (27, "scaled_random_roll"),
        0x64CD00: (73, "phase_counter"),
        0x496370: (35, "secondary_alpha"),
        0x5B0400: (82, "relative_owner_position"),
        0x45C1A0: (67, "next_sequence_frame"),
        0x4359D0: (21, "publish_battle_layout_scalar"),
        0x427280: (10, "set_battle_layout_scalar"),
        0x435D60: (89, "stage_surface_height"),
        0x5F9310: (64, "crossed_stage_surface_while_descending"),
        # CRT atan2 paths, including the observed quiet-NaN exception record.
        # Execute the original instructions; no host-math replacement return.
        0x68BB70: (10, "crt_atan2_entry"),
        0x6965AB: (0x196, "crt_atan2_stack_entry_and_postprocessing"),
        0x6965F3: (0x14E, "crt_math_postprocessing"),
        0x696774: (60, "crt_math_load_argument"),
        0x690C07: (0x163, "crt_math_binary_dispatch_and_special_values"),
        0x69649C: (0x8C, "crt_atan2_table_kernels"),
        0x6964EC: (9, "crt_half_pi_kernel"),
        0x690D59: (17, "crt_math_special_status"),
        0x69C9E5: (252, "crt_87_exception_record"),
        0x696266: (91, "crt_special_value_classifier"),
    }
)
HELPER_ADDRESSES = frozenset(
    address
    for base, (size, _) in HELPERS.items()
    for address in range(base, base + size)
)
# The actual spawn body is a boundary, never a fabricated return.
SPAWN = 0x64CCB0
BOUNDARIES = {
    SPAWN: ("spawn", 7, True, True),
    0x465190: ("owned_spawn", 7, True, True),
    0x435240: ("effect", 5, False, False),
    0x496420: ("secondary_setup", 5, False, True),
    0x4FCA60: ("parented_spawn", 7, True, True),
    0x45C030: ("wave", 1, False, True),
    # Stop at the real errno side-effect entry. No thread-local CRT state or
    # returning NaN math result is fabricated for the steering fixture.
    0x695F11: ("crt_errno", 1, False, False),
    # fabs has changed to its working control word here. Record the real
    # operation, NaN and saved caller control word before TLS errno access.
    0x696004: ("crt_qnan", 4, False, False),
}
MT_INDEX, MT_STATE, MT_BYTES = 0x6FA1FC, 0x6FDEF0, 624 * 4
SURFACE, SURFACE_BYTES = 0x6FA898, 0x500 * 4


def surface_fixtures(image):
    """Build terrain inputs with the original69-byte range-fill routine."""
    fill, fill_size = 0x434EE0, 69
    allowed = ((fill, fill + fill_size), (0x68A1A0, 0x68A24B))
    uc = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
    uc.mem_map(0x400000, 0x311000, unicorn.UC_PROT_READ | unicorn.UC_PROT_EXEC)
    uc.mem_write(0x400000, image)
    uc.mem_protect(0x6FA000, 0x2000, unicorn.UC_PROT_READ | unicorn.UC_PROT_WRITE)
    uc.mem_map(STACK, 0x10000)
    initial = uc.context_save()
    failures, written = [], set()

    def instruction(engine, address, size, unused):
        if not any(lo <= address < address + size <= hi for lo, hi in allowed):
            failures.append(f"unreviewed surface initializer instruction {address:#x}")
            engine.emu_stop()
        elif (
            bytes(engine.mem_read(address, size))
            != image[address - 0x400000 : address - 0x400000 + size]
        ):
            failures.append("surface initializer code differs")
            engine.emu_stop()

    def write(engine, access, address, size, value, unused):
        pc = engine.reg_read(r.UC_X86_REG_EIP)
        if (
            fill <= pc < fill + fill_size
            and size == 4
            and address % 4 == 0
            and SURFACE <= address <= SURFACE + SURFACE_BYTES - 4
        ):
            written.add(address)
        elif not STACK <= address <= address + size <= STACK + 0x10000:
            failures.append(f"unreviewed surface initializer write {address:#x}")
            engine.emu_stop()

    uc.hook_add(unicorn.UC_HOOK_CODE, instruction)
    uc.hook_add(unicorn.UC_HOOK_MEM_WRITE, write)
    operations = {
        "flat": [(0.0, 1279.0, 0.0)],
        "raised": [(0.0, 1279.0, 12.5)],
        "step": [(0.0, 639.0, -8.0), (640.0, 1279.0, 32.0)],
    }
    packets = {}
    for name, calls in operations.items():
        written.clear()
        for begin, end, height in calls:
            uc.context_restore(initial)
            sentinels = {
                r.UC_X86_REG_EBX: 0x11111111,
                r.UC_X86_REG_ESI: 0x22222222,
                r.UC_X86_REG_EDI: 0x33333333,
                r.UC_X86_REG_EBP: 0x44444444,
            }
            for reg, value in sentinels.items():
                uc.reg_write(reg, value)
            sp = STACK + 0xFF00
            uc.mem_write(sp, struct.pack("<Ifff", RETURN, begin, end, height))
            uc.reg_write(r.UC_X86_REG_ESP, sp)
            uc.reg_write(r.UC_X86_REG_FPCW, 0x27F)
            uc.reg_write(r.UC_X86_REG_FPSW, 0)
            uc.reg_write(r.UC_X86_REG_FPTAG, 0xFFFF)
            uc.emu_start(fill, RETURN, count=100000)
            if (
                failures
                or uc.reg_read(r.UC_X86_REG_EIP) != RETURN
                or uc.reg_read(r.UC_X86_REG_ESP) != sp + 16
                or any(uc.reg_read(reg) != value for reg, value in sentinels.items())
                or uc.reg_read(r.UC_X86_REG_FPCW) != 0x27F
                or uc.reg_read(r.UC_X86_REG_FPTAG) != 0xFFFF
                or uc.reg_read(r.UC_X86_REG_FPSW) & 0x3800
            ):
                raise ValueError("actual surface fill ABI failed: " + str(failures))
        if len(written) != 0x500:
            raise ValueError("actual fill did not cover every terrain element")
        packets[name] = bytes(uc.mem_read(SURFACE, SURFACE_BYTES))
    return packets, {
        "entry": hex(fill),
        "size": fill_size,
        "code_sha256": hashlib.sha256(
            image[fill - 0x400000 : fill - 0x400000 + fill_size]
        ).hexdigest(),
        "array": hex(SURFACE),
        "array_bytes": SURFACE_BYTES,
        "calls": operations,
        "sha256": {
            name: hashlib.sha256(data).hexdigest() for name, data in packets.items()
        },
        "scope": "actual target fill and ftol2 instructions, RET0C/callee-saved/FPCW/x87 checks; immutable terrain inputs, no replaced height result",
    }


def seed_fixtures(image, seed_values=(0, 5489, 0xFFFFFFFF)):
    """Generate actual MT inputs through the pinned target seed routine."""
    uc = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
    uc.mem_map(0x400000, 0x311000)
    uc.mem_write(0x400000, image)
    uc.mem_map(STACK, 0x10000)
    packets = {}
    failures = []

    def instruction(engine, address, size, unused):
        if not 0x406670 <= address < address + size <= 0x4066AD:
            failures.append("unreviewed MT seed instruction")
            engine.emu_stop()
        elif (
            bytes(engine.mem_read(address, size))
            != image[address - 0x400000 : address - 0x400000 + size]
        ):
            failures.append("MT seed bytes differ")
            engine.emu_stop()

    def write(engine, access, address, size, value, unused):
        if not (
            STACK <= address <= address + size <= STACK + 0x10000
            or size == 4
            and address % 4 == 0
            and (address == MT_INDEX or MT_STATE <= address < MT_STATE + MT_BYTES)
        ):
            failures.append("unreviewed MT seed write")
            engine.emu_stop()

    uc.hook_add(unicorn.UC_HOOK_CODE, instruction)
    uc.hook_add(unicorn.UC_HOOK_MEM_WRITE, write)
    for seed in seed_values:
        sp = STACK + 0xFF00
        uc.mem_write(sp, struct.pack("<II", RETURN, seed))
        uc.reg_write(r.UC_X86_REG_ESP, sp)
        uc.emu_start(0x406670, RETURN, count=10000)
        if (
            failures
            or uc.reg_read(r.UC_X86_REG_EIP) != RETURN
            or uc.reg_read(r.UC_X86_REG_ESP) != sp + 4
        ):
            raise ValueError("actual MT seeding failed: " + str(failures))
        if struct.unpack("<I", uc.mem_read(MT_INDEX, 4))[0] != 624:
            raise ValueError("actual MT seed index differs")
        packets[seed] = bytes(uc.mem_read(MT_STATE, MT_BYTES))
    return packets


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
            "?emit_repeated_effects_for_owner_state@CharacterObjectEffectEmitter@th105@@QAEEHHH@Z": 0x5575C0,
            "?replace_secondary_animation@CharacterObjectEffectEmitter@th105@@QAEXHMHHH@Z": 0x496420,
            "?release_secondary_animation_renderer@CharacterObjectEffectEmitter@th105@@QAEXXZ": 0x4963F0,
            "?turn_heading_toward_related@CharacterObjectEffectEmitter@th105@@QAEXMMM@Z": 0x4E0BF0,
            "?spawn_unparented_related_object@CharacterObjectEffectEmitter@th105@@QAEPAXHMMHHPBIH@Z": 0x64CCB0,
            "?advance_state_six_counter_conditional@CharacterObjectRuntime@th105@@QAEEH@Z": 0x4963A0,
            "?mt19937_next_u32@th105@@YAIXZ": 0x4066B0,
            "?selector_random_roll@th105@@YAHH@Z": 0x4067D0,
            "?lookup_orientation_cosine_quantized_abs@th105@@YANM@Z": 0x4063D0,
            "?advance_phase_counter_conditional@CharacterObjectRuntime@th105@@QAEEH@Z": 0x64CD00,
            "?set_secondary_animation_alpha@CharacterObjectEffectEmitter@th105@@QAEXE@Z": 0x496370,
            "?spawn_parented_related_object@CharacterObjectEffectEmitter@th105@@QAEPAXHMMHHPBIH@Z": 0x4FCA60,
            "?dispatch_character_wave_handle@ReimuObjectOwnerSpawnView@th105@@QAEXI@Z": 0x45C030,
            "_ftol2_sse": 0x68A1A0,
            "?position_relative_to_owner_offsets@CharacterObjectEffectEmitter@th105@@QAEPAUFighter@2@HH@Z": 0x5B0400,
            "CharacterObjectEffectEmitter_position_relative_to_owner_offsets": 0x5B0400,
            "?publish_battle_layout_scalar@ReimuObjectActionStateStagingView@th105@@QAEXM@Z": 0x4359D0,
            "?has_crossed_stage_surface_while_descending@ReimuObjectActionStateStagingView@th105@@QAEHXZ": 0x5F9310,
            "ReimuObjectActionStateStagingView_has_crossed_stage_surface_while_descending": 0x5F9310,
            "stage_surface_height_at_x": 0x435D60,
            "atan2_degrees": 0x406540,
            "?dispatch_indexed_event_member@ReimuObjectOwnerSpawnView@th105@@QAEXI@Z": 0x4359F0,
            "ReimuObjectOwnerSpawnView_dispatch_indexed_event_member": 0x4359F0,
            "?spawn_owned_object_via_manager@ReimuObjectOwnerSpawnView@th105@@QAEHHMMHHHH@Z": 0x465190,
        }
    )
    b = c.coff_symbol_bytes(path, SYMBOL, S, len(obj.text), targets, data, {})
    return b


class Probe:
    def __init__(self, image, candidate=None, seeds=None, surfaces=None):
        self.uc = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
        self.uc.mem_map(0x400000, 0x311000, unicorn.UC_PROT_READ | unicorn.UC_PROT_EXEC)
        self.uc.mem_write(0x400000, image)
        self.seeds = seeds
        self.surfaces = surfaces
        if seeds is not None:
            self.uc.mem_protect(
                0x6FA000, 0x1000, unicorn.UC_PROT_READ | unicorn.UC_PROT_WRITE
            )
            self.uc.mem_protect(
                0x6FB000, 0x1000, unicorn.UC_PROT_READ | unicorn.UC_PROT_WRITE
            )
            self.uc.mem_protect(
                0x6FD000, 0x2000, unicorn.UC_PROT_READ | unicorn.UC_PROT_WRITE
            )
        self.start = A if candidate is None else S
        self.size = 0 if candidate is None else len(candidate)
        # Code maps are immutable. Cache the same byte/range checks formerly
        # repeated through Python/Unicorn for every executed instruction.
        self.return_opcodes = {
            address
            for address in HELPER_ADDRESSES
            if image[address - 0x400000] in (0xC2, 0xC3)
        }
        if candidate is None:
            self.return_opcodes.update(
                address
                for lo, hi in facts.RANGES
                for address in range(lo, hi)
                if image[address - 0x400000] in (0xC2, 0xC3)
            )
        else:
            self.return_opcodes.update(
                S + n for n, byte in enumerate(candidate) if byte in (0xC2, 0xC3)
            )
        if candidate is not None:
            self.uc.mem_map(
                S,
                (len(candidate) + 0xFFF) & ~0xFFF,
                unicorn.UC_PROT_READ | unicorn.UC_PROT_EXEC,
            )
            self.uc.mem_write(S, candidate)
        for a in [OWNER, STACK, RESOURCE]:
            self.uc.mem_map(a, 0x10000)
        self.initial = self.uc.context_save()
        self.counts = Counter()
        self.visited = set()
        self.uc.hook_add(unicorn.UC_HOOK_CODE, self.instruction)
        self.uc.hook_add(unicorn.UC_HOOK_MEM_WRITE, self.write)

    def write(self, uc, access, a, n, value, user):
        pc = uc.reg_read(r.UC_X86_REG_EIP)
        if (
            self.seeds is not None
            and 0x4066B0 <= pc < 0x4067C7
            and n == 4
            and a % 4 == 0
            and (a == MT_INDEX or MT_STATE <= a < MT_STATE + MT_BYTES)
        ):
            return
        if (
            pc == 0x427284
            and a == 0x6FBD00
            and n == 4
            and struct.unpack("<h", uc.mem_read(OWNER + 0x13C, 2))[0] in (850, 853, 854)
        ):
            return
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
        elif a in BOUNDARIES:
            kind, count, copied, receiver = BOUNDARIES[a]
            sp = uc.reg_read(r.UC_X86_REG_ESP)
            args = list(
                struct.unpack("<" + "I" * count, uc.mem_read(sp + 4, count * 4))
            )
            if copied:
                packet_four = (
                    args[6] == 4
                    and (
                        (args[0] == 822 and a in (SPAWN, 0x4FCA60))
                        or (args[0] in (900, 901) and a == SPAWN)
                    )
                    and struct.unpack("<h", uc.mem_read(OWNER + 0x13C, 2))[0] == args[0]
                )
                packet_one = (
                    args[6] == 1
                    and args[0] in (851, 856)
                    and a == 0x465190
                    and struct.unpack("<h", uc.mem_read(OWNER + 0x13C, 2))[0] == args[0]
                )
                if args[6] != 3 and not packet_four and not packet_one:
                    self.failure = "unreviewed copied-word count"
                    uc.emu_stop()
                    return
                args = args[:5] + [
                    bytes(uc.mem_read(args[5], args[6] * 4)).hex(),
                    args[6],
                ]
            self.endpoint = {
                "kind": kind,
                "receiver": uc.reg_read(r.UC_X86_REG_ECX) if receiver else None,
                "arguments": args,
            }
            uc.emu_stop()
            return
        elif a not in HELPER_ADDRESSES:
            self.failure = f"unreviewed instruction {a:#x}"
            uc.emu_stop()
            return
        if a == 0x435D60:
            receiver = uc.reg_read(r.UC_X86_REG_ECX)
            self.surface_arguments.append(
                [receiver, bytes(uc.mem_read(receiver + 0xEC, 4)).hex()]
            )
        if a == 0x435160 and self.current_action in (903, 904, 905):
            sp = uc.reg_read(r.UC_X86_REG_ESP)
            self.orientation_arguments.append(
                {
                    "receiver": uc.reg_read(r.UC_X86_REG_ECX),
                    "words": list(struct.unpack("<II", uc.mem_read(sp + 4, 8))),
                }
            )
        if a in HELPERS:
            self.trace.append(a)
            self.counts[a] += 1
        if a in self.return_opcodes:
            sp = uc.reg_read(r.UC_X86_REG_ESP)
            if struct.unpack("<I", uc.mem_read(sp, 4))[0] == RETURN:
                self.saw_ret = True

    def evaluate(self, case):
        uc = self.uc
        uc.context_restore(self.initial)
        self.current_action = case["action"]
        self.orientation_arguments = []
        self.surface_arguments = []
        if case["action"] in (858, 866, 901):
            if self.surfaces is None:
                raise ValueError("terrain input fixture is required")
            uc.mem_write(SURFACE, self.surfaces[case.get("surface", "flat")])
        if self.seeds is not None:
            uc.mem_write(MT_INDEX, struct.pack("<I", 624))
            uc.mem_write(MT_STATE, self.seeds[case.get("seed", 5489)])
        uc.mem_write(OWNER, bytes([0xA5]) * 0x388)
        uc.mem_write(FIGHTER, bytes([0xA5]) * 0x800)
        uc.mem_write(STACK + 0xA000, bytes(0x6000))
        uc.mem_write(RESOURCE, entry.graph({"action": case["action"], "request": 0}))
        seq = case.get("seq", 0)
        seq_block = entry.BLOCK + seq * 0x20
        frame = entry.FRAME + seq * 0x100
        if case.get("terminal"):
            uc.mem_write(seq_block + 0x14, bytes(12))
        frame_count = 1
        if case["action"] in (
            850,
            853,
            854,
            855,
            856,
            858,
            866,
            869,
            900,
            901,
            902,
            903,
            904,
            905,
        ) or (case["action"] == 822 and seq == 0):
            # Coherent three-frame ranges for the admitted projectile families.
            # The earlier single frame cannot represent their later frames.
            first = RESOURCE + 0x6000
            template = bytes(uc.mem_read(entry.FRAME, 0x88))
            uc.mem_write(first, template * 3)
            uc.mem_write(seq_block + 4, struct.pack("<II", first, first + 3 * 0x88))
            frame = first + case.get("frame", 0) * 0x88
            frame_count = 3
        if case["action"] == 980:
            uc.mem_write(
                entry.PARAMETERS + 4, struct.pack("<f", case.get("duration", 100.0))
            )
        values = [
            (0, "I", 0x6C40A4),
            (0xEC, "f", case.get("x", 640.0)),
            (0xF0, "f", case.get("y", 100.0)),
            (0xF4, "f", case.get("vx", 3.25)),
            (0xF8, "f", case.get("vy", -1.5)),
            (0x104, "b", case.get("facing", -1)),
            (0x113, "B", case.get("alpha", 200)),
            (0x11C, "f", case.get("scale", 1.25)),
            (0x120, "f", case.get("scale_y", 0.75)),
            (0x12C, "f", 37.25),
            (0x130, "I", entry.VECTOR),
            (0x134, "B", 0),
            (0x13C, "h", case["action"]),
            (0x13E, "h", seq),
            (0x140, "h", case.get("frame", 0)),
            (0x142, "h", case.get("timer", 0)),
            (0x144, "i", case.get("counter", 0)),
            (0x148, "h", frame_count),
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
            (0x370, "f", case.get("amplitude", 3.5)),
            (0x374, "f", 0.25),
        ]
        for off, fmt, value in values:
            uc.mem_write(OWNER + off, struct.pack("<" + fmt, value))
        if case["action"] in (
            800,
            801,
            804,
            807,
            808,
            810,
            811,
            812,
            815,
            816,
            817,
            821,
            822,
            825,
            848,
            850,
            851,
            852,
            853,
            854,
            855,
            856,
            858,
            866,
            869,
            900,
            901,
            902,
            903,
            904,
            905,
        ):
            for off, fmt, value in (
                (0x170, "I", FIGHTER),
                (0x338, "I", 0),
                (0x368, "h", case.get("hold", 0)),
                (0x36C, "h", case.get("turn", 0)),
                (0x384, "h", case.get("six_counter", 0)),
            ):
                uc.mem_write(OWNER + off, struct.pack("<" + fmt, value))
            uc.mem_write(
                entry.PARAMETERS + 12, struct.pack("<f", case.get("mode", 0.0))
            )
        if case["action"] in (
            810,
            811,
            812,
            815,
            816,
            817,
            821,
            822,
            825,
            848,
            850,
            851,
            852,
            853,
            854,
            855,
            856,
            858,
            866,
            869,
            900,
            901,
            902,
            903,
            904,
            905,
        ):
            uc.mem_write(OWNER + 0x111, struct.pack("<B", case.get("channel", 200)))
            uc.mem_write(
                OWNER + 0x34C, struct.pack("<I", 0 if case.get("no_parent") else PARENT)
            )
            uc.mem_write(
                entry.PARAMETERS + 4, struct.pack("<f", case.get("speed", -12.5))
            )
            uc.mem_write(PARENT, bytes([0xA5]) * 0x388)
            for off, fmt, value in (
                (0xEC, "f", case.get("parent_x", 515.5)),
                (0xF0, "f", case.get("parent_y", 23.0)),
                (0x13E, "h", case.get("parent_seq", 0)),
                (0x340, "I", PARENT_PARAMETERS),
            ):
                uc.mem_write(PARENT + off, struct.pack("<" + fmt, value))
            uc.mem_write(PARENT_PARAMETERS, struct.pack("<ffff", -71.25, 8.5, 2.0, 0.0))
        if case["action"] in (
            815,
            816,
            817,
            821,
            822,
            825,
            848,
            850,
            851,
            852,
            853,
            854,
            855,
            856,
            858,
            866,
            869,
            900,
            901,
            902,
            903,
            904,
            905,
        ):
            for off, fmt, value in (
                (0x112, "B", case.get("channel2", 200)),
                (0x170, "I", RELATED),
                (0x386, "h", case.get("phase_counter", 0)),
            ):
                uc.mem_write(OWNER + off, struct.pack("<" + fmt, value))
            uc.mem_write(PARENT + 0x364, struct.pack("<h", case.get("parent_state", 0)))
            uc.mem_write(RELATED, bytes([0xA5]) * 0x388)
            uc.mem_write(
                RELATED + 0xEC,
                struct.pack(
                    "<ff", case.get("target_x", 515.5), case.get("target_y", 23.0)
                ),
            )
            uc.mem_write(FIGHTER + 0x13E, struct.pack("<h", case.get("owner_seq", 0)))
            uc.mem_write(FIGHTER + 0x60D, struct.pack("<b", case.get("skill", 0)))
        if case["action"] in (
            821,
            822,
            825,
            848,
            850,
            851,
            852,
            853,
            854,
            855,
            856,
            858,
            866,
            869,
            900,
            901,
            902,
            903,
            904,
            905,
        ):
            for off, fmt, value in (
                (0x104, "b", case.get("owner_facing", -1)),
                (0x140, "h", case.get("owner_frame", 1)),
                (0x174, "h", case.get("owner_health", 100)),
                (0x186, "h", case.get("owner_hold", 0)),
            ):
                uc.mem_write(FIGHTER + off, struct.pack("<" + fmt, value))
            uc.mem_write(
                PARENT + 0x12C, struct.pack("<f", case.get("parent_heading", -19.5))
            )
            if case["action"] == 822:
                uc.mem_write(
                    entry.PARAMETERS + 12, struct.pack("<f", case.get("mode", 1000.0))
                )
        if case["action"] in (
            850,
            851,
            852,
            853,
            854,
            855,
            856,
            858,
            866,
            869,
            900,
            901,
            902,
            903,
            904,
            905,
        ):
            for off, value in (
                (0x366, case.get("speed_word", 16)),
                (0x368, case.get("fade_word", 0)),
            ):
                uc.mem_write(OWNER + off, struct.pack("<h", value))
        if case["action"] in (850, 853, 854):
            uc.mem_write(0x6FBD00, struct.pack("<f", case.get("layout_scalar", -7.75)))
        if case["action"] == 855:
            uc.mem_write(OWNER + 0x36A, struct.pack("<h", case.get("spin_word", 0)))
        if case["action"] in (858, 866, 869, 900, 901, 902, 903, 904, 905):
            uc.mem_write(FIGHTER + 0x142, struct.pack("<h", case.get("owner_timer", 1)))
        if case["action"] in (900, 901, 902, 903, 904, 905):
            uc.mem_write(0x6FA894, struct.pack("<i", case.get("match_identifier", 0)))
            uc.mem_write(OWNER + 0x110, struct.pack("<B", case.get("channel0", 123)))
            uc.mem_write(OWNER + 0x174, struct.pack("<h", case.get("value174", 0)))
            uc.mem_write(
                FIGHTER + 0x174, struct.pack("<h", case.get("owner_value174", 100))
            )
            uc.mem_write(
                FIGHTER + 0x730, struct.pack("<h", case.get("owner_word730", 0))
            )
            uc.mem_write(
                entry.PARAMETERS,
                struct.pack("<f", case.get("heading_parameter", 37.25)),
            )
            for off, key, value in (
                (0x7A8, "left0", 400.0),
                (0x7AC, "left1", 300.0),
                (0x7B0, "right0", 600.0),
                (0x7B4, "right1", 700.0),
                (0x7B8, "top0", 200.0),
                (0x7BC, "top1", 300.0),
                (0x7C0, "bottom0", 0.0),
                (0x7C4, "bottom1", -100.0),
            ):
                uc.mem_write(FIGHTER + off, struct.pack("<f", case.get(key, value)))
        if case["action"] in (903, 904, 905):
            uc.mem_write(
                FIGHTER + 0x736, struct.pack("<h", case.get("owner_word736", 1))
            )
            uc.mem_write(
                FIGHTER + 0x738, struct.pack("<h", case.get("owner_word738", 1))
            )
        if case["action"] == 869:
            for off, fmt, value in (
                (0x374, "f", case.get("heading_amplitude", 0.25)),
                (0x378, "f", case.get("radial_acceleration", 1.25)),
                (0x37C, "f", case.get("angular_velocity", 0.75)),
            ):
                uc.mem_write(OWNER + off, struct.pack("<" + fmt, value))
            uc.mem_write(
                PARENT + 0x144, struct.pack("<i", case.get("parent_counter", 17))
            )
            uc.mem_write(
                FIGHTER + 0x7C8, struct.pack("<h", case.get("owner_word_7c8", 1))
            )
            uc.mem_write(
                FIGHTER + 0x7CA, struct.pack("<h", case.get("owner_word_7ca", 0))
            )
            uc.mem_write(
                entry.PARAMETERS,
                struct.pack("<f", case.get("heading_parameter", 37.25)),
            )
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
        expected_cw = case.get("cw", 0x27F)
        if self.endpoint["kind"] == "crt_qnan":
            if (
                self.endpoint["arguments"][0] != 21
                or self.endpoint["arguments"][3] != expected_cw
            ):
                raise ValueError(
                    (case, "fabs NaN operation/saved control word differs")
                )
            expected_cw = 0x133F
        if uc.reg_read(r.UC_X86_REG_FPCW) != expected_cw:
            raise ValueError((case, "floating control word changed"))
        return {
            "object": bytes(uc.mem_read(OWNER, 0x388)).hex(),
            "owner": bytes(uc.mem_read(FIGHTER, 0x800)).hex(),
            "parameters": bytes(uc.mem_read(entry.PARAMETERS, 16)).hex(),
            "parent": None
            if case["action"]
            not in (
                810,
                811,
                812,
                815,
                816,
                817,
                821,
                822,
                825,
                848,
                850,
                851,
                852,
                853,
                854,
                855,
                856,
            )
            else (
                bytes(uc.mem_read(PARENT, 0x388)).hex(),
                bytes(uc.mem_read(PARENT_PARAMETERS, 16)).hex(),
            ),
            "related": None
            if case["action"]
            not in (
                815,
                816,
                817,
                821,
                822,
                825,
                848,
                850,
                851,
                852,
                853,
                854,
                855,
                856,
            )
            else bytes(uc.mem_read(RELATED, 0x388)).hex(),
            "layout_scalar": bytes(uc.mem_read(0x6FBD00, 4)).hex()
            if case["action"] in (850, 853, 854)
            else None,
            "match_identifier": bytes(uc.mem_read(0x6FA894, 4)).hex()
            if case["action"] in (900, 901, 902, 903, 904, 905)
            else None,
            "surface_arguments": self.surface_arguments,
            "orientation_arguments": self.orientation_arguments,
            "endpoint": self.endpoint,
            "trace": self.trace,
            "cw": uc.reg_read(r.UC_X86_REG_FPCW),
            "top": (uc.reg_read(r.UC_X86_REG_FPSW) >> 11) & 7,
            "tags": uc.reg_read(r.UC_X86_REG_FPTAG),
            "rng": None
            if self.seeds is None
            else (
                bytes(uc.mem_read(MT_INDEX, 4)).hex(),
                bytes(uc.mem_read(MT_STATE, MT_BYTES)).hex(),
            ),
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


def projectile_cases():
    for action, seq, phase, index, counter in itertools.product(
        (800, 801, 804, 807, 808),
        (-1, 0, 1, 2, 3, 4),
        (0, 1, 2, 4, 5, 6, 9),
        (0, 1, 255),
        (0, 1, 5, 10, 11, 61),
    ):
        yield dict(
            action=action,
            seq=seq,
            phase=phase,
            index=index,
            counter=counter,
            cohort="projectile-state",
        )
    for action, xpos, ypos, cw in itertools.product(
        (800, 801, 804),
        (-101.0, -100.0, 1380.0, 1381.0, float("nan")),
        (-241.0, -240.0, -121.0, -120.0, 1000.0, 1001.0, float("nan")),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=action,
            seq=3,
            counter=1,
            x=xpos,
            y=ypos,
            cw=cw,
            cohort="projectile-bounds",
        )
    for pair, alpha, index in itertools.product(
        (
            (800, 1),
            (800, 2),
            (801, 2),
            (801, 3),
            (804, 2),
            (807, 0),
            (807, 1),
            (808, 0),
            (808, 1),
        ),
        (0, 4, 5, 9, 10, 14, 15, 16, 24, 25, 26, 255),
        (0, 255),
    ):
        yield dict(
            action=pair[0],
            seq=pair[1],
            counter=11,
            alpha=alpha,
            vx=1.5,
            index=index,
            cohort="projectile-alpha",
        )
    for mode, hold, turn, counter, phase, index in itertools.product(
        (0.0, 1.0), (0, 5), (0, 1), (1, 5, 60, 61), (0, 1, 6), (0, 255)
    ):
        yield dict(
            action=801,
            seq=1,
            mode=mode,
            hold=hold,
            turn=turn,
            counter=counter,
            phase=phase,
            index=index,
            cohort="projectile-steering",
        )
    for seq, state, index, six_counter, phase, seed in itertools.product(
        (0, 1), (0, 3), (0, 128, 255), (9, 10), (2, 4, 6), (0, 5489)
    ):
        yield dict(
            action=804,
            seq=seq,
            state=state,
            index=index,
            six_counter=six_counter,
            phase=phase,
            counter=1,
            seed=seed,
            cohort="projectile-collapse",
        )
    for action, seq, owner in itertools.product(
        (800, 801, 804, 807, 808), (0, 1), (49, 50, 70, 71, 149, 150)
    ):
        yield dict(
            action=action,
            seq=seq,
            counter=1,
            owner_action=owner,
            cohort="projectile-owner-gate",
        )
    for ypos, facing in itertools.product(
        (959.0, 960.0, 961.0, float("nan")), (-128, -1, 0, 1, 127)
    ):
        yield dict(
            action=808,
            seq=0,
            counter=5,
            y=ypos,
            facing=facing,
            cohort="projectile-two-request",
        )
    for action, seq, scale, timer in itertools.product(
        (800, 801, 804, 807, 808), (0, 1, 2), (0.5, 1.0, float("nan")), (2,)
    ):
        yield dict(
            action=action,
            seq=seq,
            counter=-1,
            scale=scale,
            timer=timer,
            cohort="projectile-frame",
        )


def sequence_cases():
    for action, seq, phase, index, counter in itertools.product(
        (810, 811, 812),
        range(-1, 8),
        (0, 1, 2, 4, 5, 6, 9),
        (0, 1, 128, 255),
        (-1, 0, 1, 5, 61),
    ):
        yield dict(
            action=action,
            seq=seq,
            phase=phase,
            index=index,
            counter=counter,
            cohort="sequence-state",
        )
    for action, speed, state, counter, cw in itertools.product(
        (810, 812),
        (-1.0, 0.0, 1.5, 1.5000001192092896, 3.0, float("nan")),
        (-1, 0, 3, 15, 32767),
        (-3, 1, 5),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=action,
            seq=1,
            speed=speed,
            state=state,
            counter=counter,
            cw=cw,
            cohort="sequence-zero-speed",
        )
    for action, scale, speed, cw in itertools.product(
        (810, 812),
        (0.5, 1.0, float("nan")),
        (-1.0, 3.0),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=action,
            seq=0,
            scale=scale,
            speed=speed,
            counter=1,
            cw=cw,
            cohort="sequence-growth",
        )
    for seq, channel, alpha, cw in itertools.product(
        (3, 4, 5),
        (0, 39, 40, 41, 255),
        (0, 9, 10, 11, 39, 40, 41, 255),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=811,
            seq=seq,
            channel=channel,
            alpha=alpha,
            counter=1,
            cw=cw,
            cohort="sequence-channel-alpha",
        )
    for no_parent, parent_seq, parent_x, parent_y, cw in itertools.product(
        (False, True),
        (-1, 0, 1, 2, 3),
        (-101.0, 515.5, float("nan")),
        (-121.0, 23.0, float("nan")),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=811,
            seq=1,
            no_parent=no_parent,
            parent_seq=parent_seq,
            parent_x=parent_x,
            parent_y=parent_y,
            cw=cw,
            counter=1,
            cohort="sequence-parent",
        )
    for speed, scale_y, cw in itertools.product(
        (1.5, 3.5, 5.0, float("nan")),
        (0.0, 0.02, 0.0235294122248888, 0.5, float("nan")),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=811,
            seq=2,
            speed=speed,
            scale_y=scale_y,
            counter=1,
            cw=cw,
            cohort="sequence-shrink",
        )
    for mode, amplitude, phase, six_counter, cw in itertools.product(
        (-91.25, 0.0, 37.25, 360.25),
        (-0.25, 0.0, 0.25, 3.5),
        (0, 1, 6),
        (2, 3),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=812,
            seq=2,
            mode=mode,
            amplitude=amplitude,
            phase=phase,
            six_counter=six_counter,
            counter=1,
            cw=cw,
            cohort="sequence-orbit",
        )
    for action, seq, xpos, ypos, cw in itertools.product(
        (810, 811, 812),
        (3, 6),
        (-101.0, -100.0, 1380.0, 1381.0, float("nan")),
        (-241.0, -240.0, -121.0, -120.0, 1000.0, 1001.0, float("nan")),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=action,
            seq=seq,
            x=xpos,
            y=ypos,
            counter=1,
            cw=cw,
            cohort="sequence-bounds",
        )
    for counter, seed, index, phase in itertools.product(
        (-4, -1, 0, 1, 4, 8),
        (0, 5489, 0xFFFFFFFF),
        (0, 1),
        (0, 6),
    ):
        yield dict(
            action=811,
            seq=0,
            counter=counter,
            timer=2,
            seed=seed,
            index=index,
            phase=phase,
            cohort="sequence-random",
        )
    for action, seq, phase, index, six_counter in itertools.product(
        (810, 811, 812),
        (0, 1, 2),
        (0, 1, 6),
        (0, 255),
        (2, 3, 14, 15, 19, 20, 29, 30),
    ):
        yield dict(
            action=action,
            seq=seq,
            phase=phase,
            index=index,
            six_counter=six_counter,
            hold=5,
            counter=1,
            cohort="sequence-timer",
        )


def late_projectile_cases():
    for action, seq in itertools.product((815, 816, 817), range(10)):
        yield dict(action=action, seq=seq, counter=0, cohort="late-fresh")
    for action, seq, xpos, ypos, cw in itertools.product(
        (815, 816, 817),
        (1, 4, 8),
        (-101.0, -100.0, 1380.0, 1381.0, float("nan")),
        (-121.0, -120.0, 1000.0, 1001.0, float("nan")),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=action,
            seq=seq,
            x=xpos,
            y=ypos,
            counter=1,
            parent_state=1,
            cw=cw,
            cohort="late-bounds",
        )
    for action, seq, phase, index, counter in itertools.product(
        (815, 816, 817),
        range(-1, 10),
        (0, 1, 4, 5, 6, 8),
        (0, 1, 128, 255),
        (-1, 1, 5, 15, 30, 121),
    ):
        yield dict(
            action=action,
            seq=seq,
            phase=phase,
            index=index,
            counter=counter,
            cohort="late-state",
        )
    for seq, state, speed, alpha, index, phase, cw in itertools.product(
        (0, 4),
        (-1, 0, 1, 2),
        (-5.0, -2.5, -1.0, -0.5, 0.0, 0.5, 1.0, 2.5, float("nan")),
        (235, 236, 255),
        (0, 1),
        (0, 4, 6, 8),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=816,
            seq=seq,
            state=state,
            vx=speed,
            vy=speed,
            alpha=alpha,
            index=index,
            phase=phase,
            cw=cw,
            owner_action=525,
            owner_seq=2,
            counter=1,
            cohort="late-physics",
        )
    for seq, index, phase, owner, owner_seq, cw in itertools.product(
        (0, 4),
        (0, 1, 255),
        (0, 1, 4, 6, 8),
        (524, 525, 526, 527),
        (-1, 0, 2, 3),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=816,
            seq=seq,
            state=1,
            index=index,
            phase=phase,
            owner_action=owner,
            owner_seq=owner_seq,
            cw=cw,
            counter=1,
            cohort="late-owner",
        )
    for pair, alpha, channel, cw in itertools.product(
        (
            (815, 1),
            (815, 3),
            (815, 4),
            (816, 2),
            (816, 3),
            (816, 6),
            (816, 7),
            (817, 1),
            (817, 4),
            (817, 6),
            (817, 7),
            (817, 8),
        ),
        (0, 9, 10, 14, 15, 19, 20, 39, 40, 235, 236, 255),
        (0, 9, 19, 20, 255),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=pair[0],
            seq=pair[1],
            counter=121 if pair == (815, 3) else 56,
            alpha=alpha,
            channel=channel,
            channel2=channel,
            parent_state=1,
            cw=cw,
            cohort="late-alpha",
        )
    for seq, counter, dx, dy, vx, cw in itertools.product(
        (0, 9),
        (29, 30, 31, 32, 34, 35, 60),
        (-120.0, 0.0, 120.0, 120.00001525878906, float("nan")),
        (-10.0, 10.0, 10.000000953674316, float("nan")),
        (0.0, 0.25),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=817,
            seq=seq,
            counter=counter,
            target_x=dx,
            target_y=dy,
            x=0.0,
            y=0.0,
            vx=vx,
            cw=cw,
            cohort="late-near",
        )
    for seq, skill, counter, owner, owner_seq in itertools.product(
        (0, 9),
        (-128, -4, -3, -2, 0, 1, 127),
        (-1, 0, 59, 60, 179, 180, 239, 240, 7799, 7800),
        (529, 530, 531, 532),
        (0, 1),
    ):
        yield dict(
            action=817,
            seq=seq,
            skill=skill,
            counter=counter,
            owner_action=owner,
            owner_seq=owner_seq,
            vx=1.0,
            target_x=2000.0,
            cohort="late-skill",
        )
    for seq, amplitude, channel, alpha, cw, seed in itertools.product(
        (3, 8),
        (
            -129.0,
            -128.0,
            -1.0,
            -0.25,
            0.0,
            4.999999523162842,
            5.0,
            5.5,
            127.9,
            128.0,
            255.0,
            256.0,
            float("nan"),
        ),
        (0, 4, 127, 128, 255),
        (0, 127, 255),
        (0x27F, 0x37F),
        (0, 5489, 0xFFFFFFFF),
    ):
        yield dict(
            action=817,
            seq=seq,
            amplitude=amplitude,
            channel=channel,
            channel2=channel,
            alpha=alpha,
            cw=cw,
            seed=seed,
            counter=1,
            cohort="late-casts",
        )
    for parent_seq, no_parent, seed, cw in itertools.product(
        (-1, 0, 9, 10), (False, True), (0, 5489, 0xFFFFFFFF), (0x27F, 0x37F)
    ):
        yield dict(
            action=817,
            seq=2,
            parent_seq=parent_seq,
            no_parent=no_parent,
            seed=seed,
            cw=cw,
            counter=1,
            cohort="late-links",
        )
    for parent_state, phase, state, index, alpha, seed, cw in itertools.product(
        (0, 1),
        (0, 6),
        (5, 32767),
        (0, 1, 255),
        (0, 9, 10),
        (0, 5489, 0xFFFFFFFF),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=817,
            seq=4,
            parent_state=parent_state,
            phase=phase,
            state=state,
            index=index,
            alpha=alpha,
            seed=seed,
            cw=cw,
            counter=1,
            cohort="late-links",
        )
    for action, seq, terminal in itertools.product(
        (815, 816, 817), range(10), (False, True)
    ):
        yield dict(
            action=action,
            seq=seq,
            terminal=terminal,
            counter=-1,
            timer=2,
            cohort="late-animation",
        )
    for seq, cw in itertools.product((0, 9), (0x27F, 0x37F)):
        yield dict(
            action=817,
            seq=seq,
            counter=31,
            x=-0.000001,
            y=-0.0000001,
            target_x=120.0,
            target_y=10.0,
            vx=0.0,
            cw=cw,
            cohort="late-near-rounding",
        )


def owner_projectile_cases():
    def owner(action, seq):
        if action == 825:
            return 565
        if action == 848:
            return 302 if seq == 1 else 308 if seq == 5 else 306
        return 530

    for action, seq, phase, index, counter, timer in itertools.product(
        (821, 822, 825, 848),
        range(-1, 8),
        (0, 1, 4, 5, 6, 8),
        (0, 1, 128, 255),
        (-1, 0, 1, 15, 30),
        (0, 1),
    ):
        yield dict(
            action=action,
            seq=seq,
            phase=phase,
            index=index,
            counter=counter,
            timer=timer,
            owner_action=owner(action, seq),
            owner_seq=1,
            cohort="owner-state",
        )
    for seq, action, hold, phase, cw in itertools.product(
        (-1, 0, 1, 2, 4),
        (-1, 559, 560, 561, 562, 564, 565, 566, 567, 613, 614, 615),
        (0, 1, 256, -1),
        (0, 5),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=825,
            seq=seq,
            owner_action=action,
            owner_hold=hold,
            phase=phase,
            cw=cw,
            timer=1,
            counter=1,
            cohort="owner-825-gate",
        )
    for seq, action, owner_seq, frame, hold, state in itertools.product(
        range(8),
        (301, 302, 303, 305, 306, 307, 308, 309),
        (0, 1, 2, 3),
        (0, 1, 4),
        (0, 256),
        (0, 1),
    ):
        yield dict(
            action=848,
            seq=seq,
            owner_action=action,
            owner_seq=owner_seq,
            owner_frame=frame,
            owner_hold=hold,
            state=state,
            counter=1,
            cohort="owner-848-gate",
        )
    for phase, index, ypos, six, cw in itertools.product(
        (0, 1, 6),
        (0, 1, 128, 255),
        (-0.000001, 0.0, 0.000001, float("nan")),
        (2, 3),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=821,
            seq=0,
            phase=phase,
            index=index,
            y=ypos,
            six_counter=six,
            counter=1,
            timer=1,
            cw=cw,
            cohort="owner-821-impact",
        )
    for seq, action, owner_seq, frame, hold, cw in itertools.product(
        (3, 4),
        (529, 530, 531, 532),
        (-1, 2, 3, 4),
        (3, 4),
        (0, 1),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=821,
            seq=seq,
            owner_action=action,
            owner_seq=owner_seq,
            owner_frame=frame,
            owner_hold=hold,
            counter=1,
            cw=cw,
            cohort="owner-821-follow",
        )
    for frame, timer, health, phase, mode, cw in itertools.product(
        (0, 1, 2),
        (0, 1, 2),
        (-32768, -1, 0, 1, 32767),
        (0, 1, 5),
        (-1.0, 0.0, 15.0, float("nan")),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=822,
            seq=0,
            frame=frame,
            timer=timer,
            owner_health=health,
            phase=phase,
            mode=mode,
            counter=15,
            cw=cw,
            cohort="owner-822-frame",
        )
    for amplitude, alpha, channel, cw in itertools.product(
        (
            -3.5,
            -0.10000000149011612,
            -0.05,
            0.0,
            0.05,
            0.10000000149011612,
            3.5,
            float("nan"),
        ),
        (0, 14, 15, 255),
        (0, 14, 15, 255),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=822,
            seq=4,
            timer=1,
            amplitude=amplitude,
            alpha=alpha,
            channel=channel,
            channel2=channel,
            cw=cw,
            counter=1,
            cohort="owner-822-spin",
        )
    for seq, vx, vy, alpha, channel, cw in itertools.product(
        (5, 6),
        (-1.0, 0.5, 1.0, 2.0, float("nan")),
        (-2.0, 0.0, 2.0, float("nan")),
        (0, 3, 4, 255),
        (0, 255),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=822,
            seq=seq,
            vx=vx,
            vy=vy,
            alpha=alpha,
            channel=channel,
            channel2=channel,
            cw=cw,
            counter=1,
            cohort="owner-822-cross-field",
        )
    for seq, seed, facing, cw in itertools.product(
        (0, 4),
        (0, 5489, 0xFFFFFFFF, 79, 137),
        (-128, -1, 0, 1, 127),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=822,
            seq=seq,
            timer=0,
            owner_health=0 if seq == 0 else 100,
            seed=seed,
            facing=facing,
            cw=cw,
            counter=1,
            cohort="owner-822-packet",
        )
    for seq, facing, hold, counter, cw in itertools.product(
        (3, 5),
        (-128, -1, 0, 1, 127),
        (0, 256),
        (1, 3),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=848,
            seq=seq,
            owner_action=306 if seq == 3 else 308,
            owner_seq=1,
            owner_frame=1,
            owner_facing=facing,
            owner_hold=hold,
            counter=counter,
            cw=cw,
            cohort="owner-relative-position",
        )
    for action, xpos, ypos, cw in itertools.product(
        (821, 822),
        (-101.0, -100.0, 1380.0, 1381.0, float("nan")),
        (-401.0, -400.0, -121.0, -120.0, 1000.0, 1080.0, 1081.0, float("nan")),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=action,
            seq=2 if action == 821 else 0,
            frame=0 if action == 821 else 1,
            timer=1,
            x=xpos,
            y=ypos,
            counter=1,
            cw=cw,
            cohort="owner-bounds",
        )
    for action, seq, terminal in itertools.product(
        (821, 822, 825, 848), range(8), (False, True)
    ):
        yield dict(
            action=action,
            seq=seq,
            terminal=terminal,
            owner_action=owner(action, seq),
            owner_seq=1,
            owner_frame=1,
            counter=-1,
            timer=2,
            cohort="owner-animation",
        )


def follow_projectile_cases():
    for action, seq, phase, index, state, counter, cw in itertools.product(
        (850, 851, 852),
        range(5),
        (0, 1, 5, 6),
        (0, 1, 255),
        (-1, 0, 2, 5),
        (0, 1, 60, 61),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=action,
            seq=seq,
            phase=phase,
            index=index,
            state=state,
            counter=counter,
            timer=1,
            owner_action=604 if action == 851 else 609,
            owner_seq=1,
            scale=0.5,
            cohort="follow-state",
            cw=cw,
        )
    for frame, phase, speed, scale, amplitude, cw in itertools.product(
        (0, 1, 2),
        (0, 1, 6),
        (-32768, -1, 0, 32700, 32767),
        (-0.1, 0.0, 0.2, 0.8, 0.9, 1.0, float("nan")),
        (-1.0, 2.45, 2.5, float("nan")),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=850,
            seq=1,
            frame=frame,
            phase=phase,
            speed_word=speed,
            scale=scale,
            amplitude=amplitude,
            alpha=5,
            counter=1,
            timer=1,
            cohort="follow-850-frames",
            cw=cw,
        )
    for seq, owner, counter, fade, state, cw in itertools.product(
        (0, 1, 2),
        (603, 604, 605),
        (59, 60, 61),
        (-32768, 86, 87, 90, 32767),
        (1, 2, 32767),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=851,
            seq=seq,
            owner_action=owner,
            counter=counter,
            fade_word=fade,
            state=state,
            phase=5,
            timer=1,
            cohort="follow-851-gates",
            cw=cw,
        )
    for seq, owner, owner_seq, index, phase, facing, cw in itertools.product(
        (0, 1, 2, 3),
        (608, 609, 610),
        (-1, 1, 2),
        (0, 1, 255),
        (0, 6),
        (-128, -1, 1, 127),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=852,
            seq=seq,
            owner_action=owner,
            owner_seq=owner_seq,
            index=index,
            phase=phase,
            facing=facing,
            counter=1,
            timer=1,
            cohort="follow-852-owner",
            cw=cw,
        )
    for action, seq, alpha, scale, cw in itertools.product(
        (851, 852),
        (2, 3),
        (0, 9, 10, 11, 14, 15, 19, 20, 255),
        (-0.1, 0.0, 1.0, float("nan")),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=action,
            seq=seq,
            alpha=alpha,
            scale=scale,
            counter=1,
            timer=1,
            cohort="follow-fade",
            cw=cw,
        )
    for xpos, ypos, cw in itertools.product(
        (-201.0, -200.0, 1480.0, 1481.0, float("nan")),
        (-641.0, -640.0, 1580.0, 1581.0, float("nan")),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=850,
            seq=1,
            frame=2,
            counter=1,
            timer=1,
            x=xpos,
            y=ypos,
            scale=1.0,
            cohort="follow-bounds",
            cw=cw,
        )
    for action, seq, terminal in itertools.product(
        (850, 851, 852), range(5), (False, True)
    ):
        yield dict(
            action=action,
            seq=seq,
            terminal=terminal,
            owner_action=604 if action == 851 else 609,
            owner_seq=1,
            phase=6,
            index=1,
            counter=-1,
            timer=2,
            scale=0.5,
            cohort="follow-animation",
        )


def sibling_projectile_cases():
    for action, seq, frame, phase, index, counter, timer, cw in itertools.product(
        (853, 854, 855, 856),
        range(4),
        range(3),
        (0, 1, 5, 6),
        (0, 1, 255),
        (0, 11, 121),
        (0, 1),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=action,
            seq=seq,
            frame=frame,
            phase=phase,
            index=index,
            counter=counter,
            timer=timer,
            cw=cw,
            owner_action=606,
            scale=0.5,
            cohort="sibling-state",
        )
    for action, frame, phase, speed, scale, cw in itertools.product(
        (853, 854),
        range(3),
        (0, 6),
        (-32768, -1, 0, 49, 50, 51, 32760, 32767),
        (-0.1, 0.0, 0.2, 0.9, 1.0, 1.4, 1.5, 1.6, float("nan")),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=action,
            seq=1,
            frame=frame,
            phase=phase,
            speed_word=speed,
            scale=scale,
            alpha=5,
            counter=1,
            timer=1,
            cw=cw,
            cohort="sibling-frames",
        )
    for state, spin, life, alpha, counter, phase, cw in itertools.product(
        (0, 1, 2, 3),
        (-32768, -5, 0, 85, 86, 90, 32767),
        (299, 300, 32767),
        (7, 8, 255),
        (10, 11),
        (0, 1, 6),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=855,
            seq=0,
            state=state,
            spin_word=spin,
            speed_word=life,
            fade_word=10,
            alpha=alpha,
            channel=0,
            channel2=7,
            counter=counter,
            phase=phase,
            timer=1,
            cw=cw,
            cohort="sibling-855-transitions",
        )
    for seq, owner, counter, fade, state, cw in itertools.product(
        (0, 1, 2),
        (605, 606, 607),
        (-1, 0, 119, 120, 121),
        (-32768, 86, 87, 90, 32767),
        (1, 2, 32767),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=856,
            seq=seq,
            owner_action=owner,
            counter=counter,
            fade_word=fade,
            state=state,
            phase=5,
            timer=1,
            cw=cw,
            cohort="sibling-856-gates",
        )
    for action, xpos, ypos, cw in itertools.product(
        (853, 854, 855),
        (-401.0, -400.0, -201.0, -200.0, 1480.0, 1481.0, 1680.0, 1681.0, float("nan")),
        (-521.0, -520.0, -321.0, -320.0, 1280.0, 1281.0, 1480.0, 1481.0, float("nan")),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=action,
            seq=1,
            frame=2,
            phase=0,
            state=2,
            spin_word=85,
            x=xpos,
            y=ypos,
            vx=0.0,
            vy=0.0,
            scale=1.0,
            counter=1,
            timer=1,
            cw=cw,
            cohort="sibling-bounds",
        )
    for action, seq, terminal in itertools.product(
        (853, 854, 855, 856), range(4), (False, True)
    ):
        yield dict(
            action=action,
            seq=seq,
            frame=2,
            phase=6,
            state=2,
            spin_word=85,
            scale=0.5,
            owner_action=606,
            counter=-1,
            timer=2,
            terminal=terminal,
            cohort="sibling-animation",
        )
    for frame, phase, speed, facing, cw in itertools.product(
        (0, 1),
        (0, 6),
        (-32768, -51, -50, -1, 0, 49, 50, 32767),
        (-128, -1, 0, 1, 127),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=854,
            seq=1,
            frame=frame,
            phase=phase,
            speed_word=speed,
            facing=facing,
            scale=0.5,
            counter=1,
            timer=1,
            cw=cw,
            cohort="sibling-orientation",
        )


def orbit_projectile_cases():
    def owner(action):
        return 616 if action == 866 else 669 if action == 869 else 600

    for action, seq, phase, index, counter, timer, cw in itertools.product(
        (858, 866, 869),
        (-1, 0, 1, 2, 3, 4, 5, 6),
        (0, 1, 4, 5, 6),
        (0, 1, 127, 128, 255),
        (0, 1, 15, 30),
        (0, 1),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=action,
            seq=seq,
            phase=phase,
            index=index,
            counter=counter,
            timer=timer,
            cw=cw,
            owner_action=owner(action),
            owner_seq=1,
            fade_word=1,
            cohort="orbit-state",
        )
    for frame, state, vy, ypos, surface, cw in itertools.product(
        (0, 1),
        (0, 1, 2, 32767),
        (-20.0, -1.0, 0.0, 1.0),
        (-9.0, 0.0, 12.5, 31.5, 32.0, 33.0),
        ("flat", "raised", "step"),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=858,
            seq=0,
            frame=frame,
            state=state,
            vy=vy,
            y=ypos,
            x=639.5,
            surface=surface,
            phase=0,
            index=1,
            counter=1,
            timer=1,
            cw=cw,
            cohort="orbit-impact",
        )
    for xpos, facing, phase, index, surface, cw in itertools.product(
        (
            -10.0,
            0.0,
            19.5,
            20.0,
            639.49,
            639.5,
            640.0,
            1260.0,
            1279.49,
            1280.0,
            float("nan"),
        ),
        (-128, -1, 0, 1, 127),
        (0, 4),
        (0, 128),
        ("flat", "raised", "step"),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=858,
            seq=0,
            x=xpos,
            y=200.0,
            vy=-1.0,
            facing=facing,
            phase=phase,
            index=index,
            surface=surface,
            counter=1,
            timer=1,
            cw=cw,
            cohort="orbit-terrain",
        )
    for frame, counter, index, alpha, scale, cw in itertools.product(
        (0, 1),
        (29, 30, 31),
        (1, 128),
        (0, 9, 10, 255),
        (-0.1, 0.0, 0.1, 1.0, float("nan")),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=858,
            seq=0,
            frame=frame,
            counter=counter,
            index=index,
            alpha=alpha,
            scale=scale,
            y=200.0,
            phase=0,
            timer=2,
            cw=cw,
            cohort="orbit-release",
        )
    for seq, state, action, owner_seq, frame, timer, cw in itertools.product(
        (-1, 0, 1, 2, 3),
        (0, 1, 2),
        (615, 616, 617),
        (-1, 2, 3, 4, 5, 6),
        (0, 1),
        (0, 1),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=866,
            seq=seq,
            state=state,
            owner_action=action,
            owner_seq=owner_seq,
            owner_frame=frame,
            owner_timer=timer,
            speed_word=14,
            fade_word=1,
            phase=5,
            counter=1,
            timer=1,
            cw=cw,
            cohort="orbit-owner",
        )
    for phase_word, alpha, speed, facing, cw in itertools.product(
        (-32768, 14, 15, 32767),
        (4, 5, 255),
        (0.0, 0.5, 1.5, 2.0, float("nan")),
        (-128, -1, 1, 127),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=866,
            seq=2,
            speed_word=phase_word,
            alpha=alpha,
            speed=speed,
            facing=facing,
            phase=1,
            x=2000.0,
            y=-1000.0,
            counter=1,
            timer=1,
            cw=cw,
            cohort="orbit-deceleration",
        )
    for xpos, word, surface, cw in itertools.product(
        (-1.0, 639.49, 639.5, 1279.5, float("nan")),
        (-30, -1, 0, 1, 29, 30, 32767),
        ("flat", "raised", "step"),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=866,
            seq=0,
            owner_action=616,
            owner_seq=5,
            state=0,
            fade_word=word,
            x=xpos,
            y=17.0,
            surface=surface,
            counter=1,
            timer=1,
            cw=cw,
            cohort="orbit-emission",
        )
    for action, owner_seq, remaining, threshold, mode, state, cw in itertools.product(
        (668, 669, 670),
        (1, 2),
        (-1, 0, 1, 32767),
        (-32768, -1, 0, 1, 32767),
        (-1.0, 0.0, 1.0, float("nan")),
        (0, 1),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=869,
            seq=0,
            owner_action=action,
            owner_seq=owner_seq,
            owner_word_7c8=remaining,
            owner_word_7ca=threshold,
            mode=mode,
            state=state,
            counter=1,
            timer=1,
            cw=cw,
            cohort="orbit-latch",
        )
    for action, angular, amplitude, acceleration, angle, cw in itertools.product(
        (668, 669),
        (-16.0, 0.75, float("nan")),
        (0.0, 0.95, 1.0, float("nan")),
        (-1.0, 0.4, 1.25, float("nan")),
        (-30.0, 0.0, 37.25, float("nan")),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=869,
            seq=0,
            owner_action=action,
            owner_seq=1,
            angular_velocity=angular,
            amplitude=amplitude,
            radial_acceleration=acceleration,
            heading_parameter=angle,
            counter=1,
            timer=1,
            cw=cw,
            cohort="orbit-motion",
        )
    for missing, parent_counter, counter, cw in itertools.product(
        (False, True),
        (-120, 0, 9, 10, 11, 20, 30, 60, 90, 119, 120, 255),
        (1, 31),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=869,
            seq=1,
            no_parent=missing,
            parent_counter=parent_counter,
            counter=counter,
            timer=1,
            cw=cw,
            cohort="orbit-pulse",
        )
    for seq, counter, alpha, amplitude, cw in itertools.product(
        (2, 3, 4, 5, 6),
        (14, 15, 16),
        (4, 9, 10, 14, 15, 255),
        (-3.0, 0.0, 1.0, float("nan")),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=869,
            seq=seq,
            counter=counter,
            alpha=alpha,
            amplitude=amplitude,
            phase=6,
            timer=1,
            cw=cw,
            cohort="orbit-fade",
        )
    for action, xpos, ypos, cw in itertools.product(
        (858, 869),
        (-201.0, -200.0, -101.0, -100.0, 1380.0, 1381.0, 1480.0, 1481.0, float("nan")),
        (-321.0, -320.0, -201.0, -200.0, 1000.0, 1001.0, 1280.0, 1281.0, float("nan")),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=action,
            seq=1 if action == 858 else 3,
            x=xpos,
            y=ypos,
            vx=0.0,
            vy=0.0,
            counter=1,
            timer=1,
            cw=cw,
            cohort="orbit-bounds",
        )
    for action, seq, terminal in itertools.product(
        (858, 866, 869), range(7), (False, True)
    ):
        yield dict(
            action=action,
            seq=seq,
            frame=0 if action == 858 else 2,
            counter=31 if action == 858 else 1,
            timer=2,
            index=1,
            y=200.0,
            owner_action=owner(action),
            owner_seq=1,
            fade_word=1,
            terminal=terminal,
            cohort="orbit-animation",
        )


def upper_projectile_cases():
    for action, seq, phase, state, owner_value, cw in itertools.product(
        (900, 901, 902),
        (-1, 0, 1, 2, 3, 4, 5, 6, 7),
        (0, 1, 5, 6),
        (0, 1, 2),
        (-1, 0, 1, 32767),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=action,
            seq=seq,
            phase=phase,
            state=state,
            owner_value174=owner_value,
            counter=1,
            timer=1,
            speed_word=0,
            amplitude=0.25,
            mode=1000.0,
            cw=cw,
            cohort="upper-state",
        )
    for seq, counter, phase, index, match, cw in itertools.product(
        (0, 1, 2, 3),
        (-6, -1, 0, 4, 5, 6, 39, 40, 41),
        (0, 6),
        (0, 255),
        (0, 1, 2, 3),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=900,
            seq=seq,
            counter=counter,
            phase=phase,
            index=index,
            match_identifier=match,
            mode=1000.0,
            amplitude=0.0 if seq == 3 else 3.5,
            cw=cw,
            cohort="upper-900-gates",
        )
    for counter, amplitude, mode, facing, cw in itertools.product(
        (-7, -6, -1, 1, 5, 6),
        (-1.0, -0.0, 0.25, float("nan")),
        (-1.0, 0.0, 0.25, 1000.0, float("nan")),
        (-128, -1, 0, 1, 127),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=900,
            seq=3,
            counter=counter,
            amplitude=amplitude,
            mode=mode,
            facing=facing,
            cw=cw,
            cohort="upper-900-emission",
        )
    for seq, value, owner, owner_word, phase, cw in itertools.product(
        (0, 1),
        (-32768, -1500, -1499, -1001, -1000, -999, -501, -500, -1, 0, 1000, 32767),
        (-1, 1),
        (0, 1, 2),
        (0, 1, 6),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=901,
            seq=seq,
            value174=value,
            owner_value174=owner,
            owner_word730=owner_word,
            phase=phase,
            speed_word=0,
            mode=2.0,
            y=200.0,
            vy=0.0,
            counter=1,
            timer=1,
            cw=cw,
            cohort="upper-901-values",
        )
    for value, phase, latch, index, cw in itertools.product(
        (-32768, -1001, -1000, -999, -521, -520, -501, -500, -499, -1, 0, 999, 32767),
        (0, 1, 6),
        (0, 1, -1),
        (0, 255),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=901,
            seq=1,
            value174=value,
            phase=phase,
            speed_word=latch,
            index=index,
            y=200.0,
            vy=0.0,
            counter=1,
            timer=1,
            cw=cw,
            cohort="upper-901-color",
        )
    for state, threshold, ypos, vy, value, surface, cw in itertools.product(
        (0, 1, 32767),
        (-1.0, 0.0, 1.0, 2.0, float("nan")),
        (79.5, 80.0, 80.5, float("nan")),
        (-1.0, 0.5, 1.0),
        (-749, 0),
        ("flat", "raised", "step"),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=901,
            seq=1,
            state=state,
            mode=threshold,
            y=ypos,
            vy=vy,
            value174=value,
            x=639.5,
            surface=surface,
            speed_word=1,
            phase=0,
            counter=1,
            timer=1,
            cw=cw,
            cohort="upper-901-impact",
        )
    for seq, counter, alpha, speed, cw in itertools.product(
        (2, 3, 4, 5, 6, 7),
        (-1, 0, 4, 5),
        (0, 9, 10, 255),
        (0.0, 0.75, float("nan")),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=901,
            seq=seq,
            counter=counter,
            alpha=alpha,
            speed=speed,
            timer=1,
            cw=cw,
            cohort="upper-901-fade",
        )
    for seq, state, owner_value, amplitude, counter, facing, cw in itertools.product(
        (0, 1),
        (0, 1, 2),
        (-1, 1),
        (-0.0, 0.25, 1.0, float("nan")),
        (-1, 0, 17, 123456789),
        (-128, -1, 1, 127),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=902,
            seq=seq,
            state=state,
            owner_value174=owner_value,
            amplitude=amplitude,
            counter=counter,
            facing=facing,
            timer=1,
            cw=cw,
            cohort="upper-902-rectangles",
        )
    for state, match, axis, edge, sign, facing, cw in itertools.product(
        (0, 1, 2),
        (0, 1, 2, 3, -1, 4),
        ("x", "y"),
        (-0.5, 0.0, 0.5, float("nan")),
        (-1, 0, 1),
        (-128, -1, 1, 127),
        (0x27F, 0x37F),
    ):
        # Keep the other coordinate and velocity inside both rectangles.
        case = dict(
            action=902,
            seq=2,
            state=state,
            match_identifier=match,
            x=500.0,
            y=100.0,
            vx=0.0,
            vy=0.0,
            facing=facing,
            counter=1,
            timer=1,
            cw=cw,
            cohort="upper-902-portals",
        )
        if axis == "x":
            case["x"] = (600.0 if sign >= 0 else 400.0) + edge
            case["vx"] = float(sign * facing) if abs(facing) == 1 else float(sign)
        else:
            case["y"] = (200.0 if sign >= 0 else 0.0) + edge
            case["vy"] = float(sign)
        yield case
    for state, axis, sign, cw in itertools.product(
        (1,), ("x", "y"), (-1, 1), (0x27F, 0x37F)
    ):
        for match in (0, 1, 2, 3, -1, 4):
            yield dict(
                action=902,
                seq=2,
                state=state,
                match_identifier=match,
                x=701.0
                if axis == "x" and sign > 0
                else 299.0
                if axis == "x"
                else 500.0,
                y=301.0
                if axis == "y" and sign > 0
                else -101.0
                if axis == "y"
                else 100.0,
                vx=float(sign) if axis == "x" else 0.0,
                vy=float(sign) if axis == "y" else 0.0,
                facing=1,
                counter=1,
                timer=1,
                cw=cw,
                cohort="upper-902-secondary",
            )
    for action, seq, xpos, ypos, cw in itertools.product(
        (900, 901, 902),
        (1, 2),
        (-101.0, -100.0, 39.5, 40.0, 1240.0, 1240.5, 1380.0, 1381.0, float("nan")),
        (-201.0, -200.0, 80.0, 900.0, 901.0, float("nan")),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=action,
            seq=seq,
            x=xpos,
            y=ypos,
            vx=0.0,
            vy=0.0,
            phase=0,
            state=2,
            counter=1,
            timer=1,
            mode=1000.0,
            cw=cw,
            cohort="upper-bounds",
        )
    for action, seq, terminal in itertools.product(
        (900, 901, 902), range(8), (False, True)
    ):
        yield dict(
            action=action,
            seq=seq,
            terminal=terminal,
            frame=2,
            owner_value174=1,
            state=2,
            counter=1,
            timer=2,
            y=200.0,
            mode=1000.0,
            cohort="upper-animation",
        )

    for xpos, vx, facing, cw in itertools.product(
        (39.5, 40.0, 1240.0, 1240.5, float("nan")),
        (-1.0, 0.0, 1.0, float("nan")),
        (-128, -1, 0, 1, 127),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=901,
            seq=1,
            x=xpos,
            y=200.0,
            vx=vx,
            vy=0.5,
            facing=facing,
            value174=0,
            speed_word=1,
            counter=1,
            timer=1,
            cw=cw,
            cohort="upper-901-steering",
        )
    for angle, speed, amplitude, facing, trigger, cw in itertools.product(
        (-0.0, 37.25, 180.0, float("nan")),
        (0.0, 0.0001, 17.25),
        (0.0, 0.25),
        (-128, -1, 1, 127),
        (0, 1),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=901,
            seq=0,
            heading_parameter=angle,
            speed=speed,
            amplitude=amplitude,
            facing=facing,
            owner_word730=trigger,
            value174=0,
            counter=1,
            timer=1,
            cw=cw,
            cohort="upper-901-orbit",
        )


def actions_903_905_cases():
    for action, seq, phase, index, state, cw in itertools.product(
        (903, 904, 905),
        range(-1, 10),
        (0, 1, 4, 5, 6),
        (0, 1, 127, 128, 255),
        (0, 1, 2),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=action,
            seq=seq,
            phase=phase,
            index=index,
            state=state,
            owner_value174=8000,
            counter=1,
            timer=1,
            cw=cw,
            cohort="high-state",
        )
    for seq, counter, phase, seed, cw in itertools.product(
        range(3),
        (-11, -10, -1, 0, 1, 9, 10, 39, 40, 41, 50),
        (0, 6),
        (0, 5489, 0xFFFFFFFF),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=903,
            seq=seq,
            counter=counter,
            phase=phase,
            state=0,
            owner_value174=8000,
            owner_action=740,
            owner_seq=6,
            match_identifier=1,
            seed=seed,
            timer=1,
            cw=cw,
            cohort="high-903-transition",
        )
    for seq, match, action, owner_seq, seed, cw in itertools.product(
        range(3),
        (-1, 0, 1, 2, 3, 4),
        (739, 740, 741),
        (5, 6, 7),
        (0, 5489, 0xFFFFFFFF),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=903,
            seq=seq,
            state=1,
            match_identifier=match,
            owner_action=action,
            owner_seq=owner_seq,
            owner_value174=8000,
            seed=seed,
            counter=1,
            timer=1,
            cw=cw,
            cohort="high-903-owner",
        )
    for seq, index, phase, value, seed, cw in itertools.product(
        range(3),
        (0, 1, 127, 128, 255),
        (0, 6),
        (-1, 1),
        (0, 5489, 0xFFFFFFFF),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=904,
            seq=seq,
            index=index,
            phase=phase,
            owner_value174=value,
            seed=seed,
            counter=1,
            timer=1,
            cw=cw,
            cohort="high-904-signed-index",
        )
    for action, speed, angle, facing, cw in itertools.product(
        (903, 904, 905),
        (-20.0, -0.0, 0.001, 0.75, float("nan")),
        (-180.0, 0.0, 37.25, float("nan")),
        (-128, -1, 1, 127),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=action,
            seq=4 if action == 905 else 3,
            speed=speed,
            heading_parameter=angle,
            facing=facing,
            owner_value174=8000,
            counter=1,
            timer=1,
            cw=cw,
            cohort="high-orientation",
        )
    for state, value, gate736, gate738, match, cw in itertools.product(
        (-1, 0, 1, 2),
        (-32768, 7499, 7500, 7501, 32767),
        (-1, 0, 1),
        (-1, 0, 1),
        (-1, 0, 1, 2, 3, 4),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=905,
            seq=0,
            state=state,
            owner_value174=value,
            owner_word736=gate736,
            owner_word738=gate738,
            match_identifier=match,
            counter=1,
            timer=1,
            cw=cw,
            cohort="high-905-gates",
        )
    for match, counter, cw in itertools.product(
        (-1, 0, 1, 2, 3, 4),
        (
            -270,
            -240,
            -210,
            -150,
            -1,
            0,
            1,
            149,
            150,
            151,
            209,
            210,
            211,
            239,
            240,
            241,
            269,
            270,
            271,
        ),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=905,
            seq=0,
            state=1,
            owner_value174=8000,
            owner_word738=0,
            match_identifier=match,
            counter=counter,
            timer=1,
            cw=cw,
            cohort="high-905-periods",
        )
    for counter, match, amplitude, cw in itertools.product(
        (-1, 1, 149, 240),
        (-1, 0, 1, 2, 3, 4),
        (-0.0, 0.25, 1.0, float("nan")),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=905,
            seq=0,
            state=0,
            owner_value174=8000,
            owner_word736=0,
            owner_word738=0,
            match_identifier=match,
            amplitude=amplitude,
            counter=counter,
            timer=1,
            cw=cw,
            cohort="high-905-same-frame",
        )
    for phase, word, state, value, alpha, cw in itertools.product(
        (0, 1, 5, 6),
        (-32768, 0, 9, 10, 32767),
        (0, 1),
        (7500, 7501),
        (0, 9, 10, 255),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=905,
            seq=4,
            phase=phase,
            speed_word=word,
            state=state,
            owner_value174=value,
            alpha=alpha,
            counter=1,
            timer=1,
            cw=cw,
            cohort="high-905-phase-counter",
        )
    for seq, channel, channel2, alpha, cw in itertools.product(
        (0, 2, 3, 5),
        (0, 4, 5, 6, 255),
        (0, 4, 5, 255),
        (0, 9, 10, 255),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=905,
            seq=seq,
            state=2,
            owner_value174=8000,
            channel=channel,
            channel2=channel2,
            alpha=alpha,
            counter=1,
            timer=1,
            cw=cw,
            cohort="high-905-channels",
        )
    for action, seq, xpos, ypos, cw in itertools.product(
        (903, 904, 905),
        (1, 4),
        (-521.0, -520.0, -401.0, -400.0, 1680.0, 1681.0, 1800.0, 1801.0, float("nan")),
        (-801.0, -800.0, -521.0, -520.0, 1400.0, 1401.0, 1480.0, 1481.0, float("nan")),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=action,
            seq=seq,
            x=xpos,
            y=ypos,
            state=2,
            owner_value174=8000,
            vx=0.0,
            vy=0.0,
            speed=0.0,
            counter=1,
            timer=1,
            cw=cw,
            cohort="high-bounds",
        )
    for action, seq, counter, terminal, cw in itertools.product(
        (903, 904, 905),
        range(10),
        (-1, 0, 1),
        (False, True),
        (0x27F, 0x37F),
    ):
        yield dict(
            action=action,
            seq=seq,
            counter=counter,
            terminal=terminal,
            frame=2,
            timer=2,
            state=2,
            owner_value174=8000,
            cw=cw,
            cohort="high-animation",
        )


def main():
    global O
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path)
    parser.add_argument(
        "--output-dir", type=Path, default=R / "build/reimu-object-scalar-native"
    )
    parser.add_argument(
        "--projectiles",
        action="store_true",
        help="include800/801/804/807/808 and actual MT fixtures",
    )
    parser.add_argument(
        "--sequences",
        action="store_true",
        help="include810/811/812 and the preceding projectile matrix",
    )
    parser.add_argument(
        "--late-projectiles",
        action="store_true",
        help="include815/816/817 and all preceding matrices",
    )
    parser.add_argument(
        "--cohort",
        action="append",
        help="run only named cohorts from the selected matrices",
    )
    parser.add_argument(
        "--owner-projectiles",
        action="store_true",
        help="include821/822/825/848 and preceding matrices",
    )
    parser.add_argument(
        "--follow-projectiles",
        action="store_true",
        help="include850/851/852 and all preceding matrices",
    )
    parser.add_argument(
        "--sibling-projectiles",
        action="store_true",
        help="include853/854/855/856 and all preceding matrices",
    )
    parser.add_argument(
        "--orbit-projectiles",
        action="store_true",
        help="include858/866/869 with terrain inputs and all preceding matrices",
    )
    parser.add_argument(
        "--actions-900-902",
        action="store_true",
        help="include900/901/902 and all preceding matrices",
    )
    parser.add_argument(
        "--actions-903-905",
        action="store_true",
        help="include903/904/905 and all preceding matrices",
    )
    args = parser.parse_args()
    if args.actions_903_905:
        args.actions_900_902 = True
    if args.actions_900_902:
        args.orbit_projectiles = True
    if args.orbit_projectiles:
        args.sibling_projectiles = True
    if args.sibling_projectiles:
        args.follow_projectiles = True
    if args.follow_projectiles:
        args.owner_projectiles = True
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
    seeds = (
        seed_fixtures(
            bytes(image),
            (0, 5489, 0xFFFFFFFF, 79, 137)
            if args.owner_projectiles
            else (0, 5489, 0xFFFFFFFF),
        )
        if args.projectiles
        or args.sequences
        or args.late_projectiles
        or args.owner_projectiles
        else None
    )
    surfaces, surface_receipt = (
        surface_fixtures(bytes(image)) if args.orbit_projectiles else (None, None)
    )
    if surface_receipt is not None:
        (O / "surface-initialization.json").write_text(
            json.dumps(surface_receipt, indent=2) + "\n"
        )
    target = Probe(bytes(image), seeds=seeds, surfaces=surfaces)
    source = Probe(bytes(image), candidate, seeds=seeds, surfaces=surfaces)
    all_cases = list(cases())
    if (
        args.projectiles
        or args.sequences
        or args.late_projectiles
        or args.owner_projectiles
    ):
        all_cases.extend(projectile_cases())
    if args.sequences or args.late_projectiles or args.owner_projectiles:
        all_cases.extend(sequence_cases())
    if args.late_projectiles or args.owner_projectiles:
        all_cases.extend(late_projectile_cases())
    if args.owner_projectiles:
        all_cases.extend(owner_projectile_cases())
    if args.follow_projectiles:
        all_cases.extend(follow_projectile_cases())
    if args.sibling_projectiles:
        all_cases.extend(sibling_projectile_cases())
    if args.orbit_projectiles:
        all_cases.extend(orbit_projectile_cases())
    if args.actions_900_902:
        all_cases.extend(upper_projectile_cases())
    if args.actions_903_905:
        all_cases.extend(actions_903_905_cases())
    if args.cohort:
        available = {case.get("cohort", "scalar") for case in all_cases}
        if set(args.cohort) - available:
            parser.error("cohort is absent from the selected matrices")
        all_cases = [
            case for case in all_cases if case.get("cohort", "scalar") in args.cohort
        ]
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
        "surface_initialization": surface_receipt,
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
        "cohorts": dict(Counter(case.get("cohort", "scalar") for case in all_cases)),
        "seed_fixture_sha256": {}
        if seeds is None
        else {
            str(seed): hashlib.sha256(packet).hexdigest()
            for seed, packet in seeds.items()
        },
        "scope": "admitted scalar/default/projectile source paths; actual target helpers, no replacement returns; world/effect/secondary-setup/wave/CRT-errno/CRT-qNaN entry stops; no full-root or exact claim",
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
