#!/usr/bin/env python3
"""Check genuine MT calls with the live x87 value seen in Iku LTCG output.

Executes the attested target and linked source helpers, never replacing a
callee result. This is a focused boundary diagnostic, not whole-Iku execution.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import sys

import pefile
import linked_pe

ROOT = Path(__file__).resolve().parents[1]
MT_UNIT = "cross-v106a-mt19937-next"
NAMES = {
    "next": "?mt19937_next_u32@th105@@YAIXZ",
    "state": "?g_mt19937_state@th105@@3PAIA",
    "index": "?g_mt19937_index@th105@@3HA",
    "twist": "?g_mt19937_twist_xor@th105@@3PAIA",
}
STACK, RETURN = 0x30000000, 0x40000000
ENTRY_SP = STACK + 0xF000
# One normal float80 value whose low mantissa bit would disappear in binary64.
SENTINEL = (0xC000000000000001, 0x3FFF)
STATE_BYTES = 624 * 4


def unique_address(symbols, name):
    addresses = {address for address, _ in symbols.get(name, [])}
    if len(addresses) != 1:
        raise ValueError("MT symbol has no unique MAP address: " + name)
    return next(iter(addresses))


def load_context(directory, canonical):
    directory = directory.resolve()
    receipt_path = directory / "receipt.json"
    receipt = json.loads(receipt_path.read_text())
    if receipt.get("schema") != "th105-iku-provider-visibility-entry-v1":
        raise ValueError("requires an Iku provider-visibility receipt")
    if receipt["target_sha256"] != canonical.verify_target():
        raise ValueError("visibility receipt target differs")
    if receipt["root_source_sha256"] != linked_pe.sha(ROOT / "src/characters/IkuActionState.cpp"):
        raise ValueError("visibility receipt uses another Iku source")
    if receipt["visible_provider_units"] not in ([], [MT_UNIT]):
        raise ValueError("MT boundary probe requires ordinary or MT-only visibility")
    for filename, key in (("IkuRoot.dll", "image_sha256"), ("IkuRoot.map", "map_sha256")):
        if linked_pe.sha(directory / filename) != receipt[key]:
            raise ValueError("stale linked MT artifact: " + filename)
    symbols = linked_pe.parse_map_symbols((directory / "IkuRoot.map").read_text())
    addresses = {key: unique_address(symbols, name) for key, name in NAMES.items()}
    return directory, receipt, addresses, linked_pe.sha(receipt_path)


class Engine:
    def __init__(self, target_addresses, context=None):
        import unicorn
        import unicorn.x86_const as registers

        self.registers = registers
        self.unicorn_version = unicorn.__version__
        self.uc = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
        image = pefile.PE(str(ROOT / "resources/th105.exe"))
        self.map_image(image)
        self.addresses = target_addresses
        if context is not None:
            directory, _, self.addresses, _ = context
            image = pefile.PE(str(directory / "IkuRoot.dll"))
            self.map_image(image)
        base = image.OPTIONAL_HEADER.ImageBase
        text = next(section for section in image.sections if section.Name.rstrip(b"\0") == b".text")
        self.code_range = (base + text.VirtualAddress, base + text.VirtualAddress + text.Misc_VirtualSize)
        self.uc.mem_map(STACK, 0x10000)
        self.uc.mem_map(RETURN, 0x1000)
        self.failure = None
        self.uc.hook_add(unicorn.UC_HOOK_MEM_WRITE, self.write)
        self.uc.hook_add(unicorn.UC_HOOK_CODE, self.instruction)

    def map_image(self, image):
        base = image.OPTIONAL_HEADER.ImageBase
        self.uc.mem_map(base, (image.OPTIONAL_HEADER.SizeOfImage + 4095) & ~4095)
        self.uc.mem_write(base, image.get_memory_mapped_image())

    def instruction(self, uc, address, size, unused):
        if not self.code_range[0] <= address < self.code_range[1]:
            self.failure = f"execution leaves the attested helper image at {address:#x}"
            uc.emu_stop()

    def write(self, uc, access, address, size, value, unused):
        fields = self.addresses
        if not (STACK <= address and address + size <= STACK + 0x10000
                or fields["state"] <= address and address + size <= fields["state"] + STATE_BYTES
                or fields["index"] <= address and address + size <= fields["index"] + 4):
            self.failure = f"write outside MT state/stack at {address:#x}"
            uc.emu_stop()

    def state(self):
        return (bytes(self.uc.mem_read(self.addresses["index"], 4))
                + bytes(self.uc.mem_read(self.addresses["state"], STATE_BYTES)))

    def set_state(self, state):
        if len(state) != STATE_BYTES + 4:
            raise ValueError("MT fixture state has the wrong width")
        self.uc.mem_write(self.addresses["index"], state[:4])
        self.uc.mem_write(self.addresses["state"], state[4:])

    def init_fp(self, cw):
        r = self.registers
        self.uc.reg_write(r.UC_X86_REG_FPCW, cw)
        self.uc.reg_write(r.UC_X86_REG_FPSW, 0)
        self.uc.reg_write(r.UC_X86_REG_FP0, SENTINEL)
        self.uc.reg_write(r.UC_X86_REG_FPTAG, 0xFFFC)

    def fp(self):
        r = self.registers
        return tuple(self.uc.reg_read(reg) for reg in
                     (r.UC_X86_REG_FP0, r.UC_X86_REG_FPCW, r.UC_X86_REG_FPSW, r.UC_X86_REG_FPTAG))

    def call(self, address, argument=None):
        r = self.registers
        uc = self.uc
        self.failure = None
        uc.mem_write(ENTRY_SP, struct.pack("<I", RETURN)
                     + (struct.pack("<I", argument) if argument is not None else b""))
        uc.reg_write(r.UC_X86_REG_ESP, ENTRY_SP)
        preserved = (r.UC_X86_REG_EBX, r.UC_X86_REG_ESI, r.UC_X86_REG_EDI, r.UC_X86_REG_EBP)
        values = [0x11110000 + n for n in range(len(preserved))]
        for reg, value in zip(preserved, values):
            uc.reg_write(reg, value)
        fp = self.fp()
        uc.emu_start(address, RETURN, count=100000)
        if self.failure:
            raise ValueError(self.failure)
        if uc.reg_read(r.UC_X86_REG_EIP) != RETURN or uc.reg_read(r.UC_X86_REG_ESP) != ENTRY_SP + 4:
            raise ValueError("MT RET/stack contract differs")
        if [uc.reg_read(reg) for reg in preserved] != values:
            raise ValueError("MT callee-saved registers differ")
        if self.fp() != fp:
            raise ValueError("MT call changes live float80/control/status/tag state")
        return uc.reg_read(r.UC_X86_REG_EAX)


def run(directories, draws=626, control=None):
    if draws < 1:
        raise ValueError("draw count must be positive")
    if control not in (None, "different-seed"):
        raise ValueError("unknown MT preservation control")
    canonical = linked_pe.comparator()
    target_sha = canonical.verify_target()
    globals_ = canonical.known_data_targets()
    target = {key: globals_[name][0] for key, name in NAMES.items() if key != "next"}
    target.update(next=0x4066B0, seed=0x406670)
    contexts = [load_context(path, canonical) for path in directories]
    expected = Engine(target)
    inputs, outputs = hashlib.sha256(), hashlib.sha256()
    cases, differences, examples = 0, 0, []
    for context in contexts:
        directory, receipt, _, _ = context
        actual = Engine(target, context)
        twist = bytes(actual.uc.mem_read(actual.addresses["twist"], 8))
        if twist != canonical.target_bytes(target["twist"], 8):
            raise ValueError("linked MT twist constants differ")
        label = ("noinline" if receipt.get("mt_noinline_control") else
                 "visible" if receipt["visible_provider_units"] else "ordinary")
        for seed in ((0,) if control else (None, 0, 1, 119)):
            for cw in ((0x27F,) if control else (0x27F, 0x37F)):
                expected.init_fp(cw)
                actual.init_fp(cw)
                if seed is None:
                    initial = struct.pack("<I", 625) + bytes(STATE_BYTES)
                else:
                    expected.call(target["seed"], seed)
                    initial = expected.state()
                expected.set_state(initial)
                if control:
                    # Different genuine seed state, with no code/result replacement.
                    expected.call(target["seed"], 1)
                    actual.set_state(expected.state())
                    expected.set_state(initial)
                else:
                    actual.set_state(initial)
                for draw in range(1 if control else draws):
                    a, b = expected.call(target["next"]), actual.call(actual.addresses["next"])
                    state = expected.state()
                    case = [label, seed, cw, draw, control]
                    inputs.update(json.dumps(case).encode())
                    outputs.update(struct.pack("<I", a) + state)
                    cases += 1
                    if a != b or state != actual.state():
                        differences += 1
                        if len(examples) < 2:
                            examples.append({"case": case, "target_return": a, "source_return": b})
        print(f"checked {directory.name}: {cases} cases / {differences} differences", file=sys.stderr)
    return {
        "schema": "th105-iku-mt-live-fp-boundary-v1", "target_sha256": target_sha,
        "probe_sha256": linked_pe.sha(Path(__file__)), "unicorn_version": expected.unicorn_version,
        "target_helpers": {name: {"address": hex(address), "size": size,
                                  "sha256": hashlib.sha256(canonical.target_bytes(address, size)).hexdigest()}
                           for name, address, size in (("seed", 0x406670, 64), ("next", 0x4066B0, 279))},
        "contexts": [{"directory": str(path), "receipt_sha256": digest,
                      "image_sha256": receipt["image_sha256"], "map_sha256": receipt["map_sha256"],
                      "mt_noinline_control": receipt.get("mt_noinline_control", False)}
                     for path, receipt, _, digest in contexts],
        "cases": cases, "mismatch_count": differences, "examples": examples,
        "input_sha256": inputs.hexdigest(), "target_output_sha256": outputs.hexdigest(),
        "float80_sentinel": list(SENTINEL), "diagnostic_control": control,
        "scope": "Real target seed/next and linked MT bodies with one live float80 value; RNG/stack/nonvolatile/x87 checks. No injected returns, original ABI inference or whole-Iku execution claim.",
    }


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("contexts", type=Path, nargs="+")
    parser.add_argument("--draws", type=int, default=626)
    parser.add_argument("--control", choices=("different-seed",))
    arguments = parser.parse_args()
    result = run(arguments.contexts, arguments.draws, arguments.control)
    print(json.dumps(result, indent=2))
    raise SystemExit(bool(result["mismatch_count"]))
