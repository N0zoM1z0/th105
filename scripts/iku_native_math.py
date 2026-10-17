"""Generate Iku's native lookup fixture with the original target initializer.

The unledgered177-byte initialization region is used only as an observed
dependency entry. This does not classify ownership or accept a new function.
All math/runtime instructions execute from the hash-attested target PE.
"""
import hashlib
import struct

import capstone
import pefile
import unicorn
from unicorn import x86_const as r


def attest_instruction(mapped, engine, address, size, trace):
    if not 0x401000 <= address < address + size <= 0x6BF33A:
        raise ValueError(f"native math execution outside target text at {address:#x}")
    raw = bytes(engine.mem_read(address, size))
    if raw != mapped[address - 0x400000:address - 0x400000 + size]:
        raise ValueError("native math instruction differs from target")
    if address not in trace:
        rows = list(capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32).disasm(raw, address))
        if len(rows) != 1 or rows[0].size != size:
            raise ValueError("native math instruction does not decode completely")
        trace[address] = raw.hex()
    elif len(trace[address]) != size * 2:
        raise ValueError("native math entered a different instruction boundary")


def lookup_fixture(canonical):
    from pathlib import Path
    canonical.verify_target()
    target = Path(__file__).resolve().parents[1] / "resources/th105.exe"
    mapped = pefile.PE(str(target)).get_memory_mapped_image()
    engine = unicorn.Uc(unicorn.UC_ARCH_X86, unicorn.UC_MODE_32)
    engine.mem_map(0x400000, 0x311000)
    engine.mem_write(0x400000, mapped)
    engine.mem_map(0x1000000, 0x10000)
    engine.mem_map(0xF000000, 0x1000)
    trace, errors = {}, []

    def instruction(uc, address, size, unused):
        try:
            attest_instruction(mapped, uc, address, size, trace)
        except Exception as error:
            errors.append(str(error))
            uc.emu_stop()

    def write(uc, access, address, size, value, unused):
        if not any(first <= address and address + size <= last for first, last in (
                (0x1000000, 0x1010000), (0x6FE8B0, 0x7020F0),
                (0x6FDEF0, 0x6FE8B0), (0x6FA1FC, 0x6FA200))):
            errors.append(f"initializer write outside table/RNG/stack at {address:#x}")
            uc.emu_stop()

    engine.hook_add(unicorn.UC_HOOK_CODE, instruction)
    engine.hook_add(unicorn.UC_HOOK_MEM_WRITE, write)
    engine.mem_write(0x100FF00, struct.pack("<I", 0xF000000))
    engine.reg_write(r.UC_X86_REG_ESP, 0x100FF00)
    engine.reg_write(r.UC_X86_REG_FPCW, 0x27F)
    engine.emu_start(0x4065B0, 0xF000000, count=10000000)
    if (errors or engine.reg_read(r.UC_X86_REG_EIP) != 0xF000000
            or engine.reg_read(r.UC_X86_REG_ESP) != 0x100FF04
            or (engine.reg_read(r.UC_X86_REG_FPSW) >> 11) & 7
            or engine.reg_read(r.UC_X86_REG_FPCW) != 0x27F):
        raise ValueError("original table initialization failed its RET/stack/x87 contract: " + str(errors))
    table = bytes(engine.mem_read(0x6FE8B0, 14400))
    digest = hashlib.sha256(table).hexdigest()
    if digest != "c134fa85e7988574c2db386dc8e14de2113d6e465c18f4503bd265219c5ca898":
        raise ValueError("original PC53 orientation table differs")
    return table, {"entry": 0x4065B0, "observed_span_bytes": 177,
                   "observed_span_sha256": hashlib.sha256(canonical.target_bytes(0x4065B0, 177)).hexdigest(),
                   "table_sha256": digest, "control_word": 0x27F,
                   "instructions": len(trace), "trace": trace,
                   "scope": "original initialization through RET, actual3600 float entries and cardinal overrides; "
                            "not host-generated cosine values, helper-result hooks, boundary/origin/exact credit"}
