"""Hash-pinned raw PE facts for Iku actions 565--568.

Run after supplying the exact Japanese TH10.5 v1.06a target executable.
The output under build/ is a diagnostic report, not source or exact credit.
"""

import hashlib
import json
import re
import struct
from pathlib import Path

import capstone
import pefile


ROOT = Path(__file__).resolve().parent.parent
TARGET_SHA = "56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e"
BODY_SHA = "abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea"
raw = (ROOT / "resources/th105.exe").read_bytes()
assert hashlib.sha256(raw).hexdigest() == TARGET_SHA
pe = pefile.PE(data=raw, fast_load=True)
assert pe.OPTIONAL_HEADER.AddressOfEntryPoint + pe.OPTIONAL_HEADER.ImageBase == 0x68B9D2


def mapped(address, size):
    offset = pe.get_offset_from_rva(address - pe.OPTIONAL_HEADER.ImageBase)
    return raw[offset:offset + size]


assert hashlib.sha256(mapped(0x620920, 59038)).hexdigest() == BODY_SHA
decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
table = struct.unpack("<35I", mapped(0x62F2C8, 35 * 4))
lookup = mapped(0x62F354, 798 - 561 + 1)
assert len(set(table)) == 35 and set(lookup) == set(range(35))
entries = {action: table[index] for action, index in enumerate(lookup, 561)}
starts = [entries[action] for action in (565, 566, 567, 568)]
assert starts == [0x6296BE, 0x629E96, 0x62A668, 0x62AEF6]
assert entries[570] == 0x62B784
starts.append(entries[570])

cases = []
for action, start, end in zip((565, 566, 567, 568), starts, starts[1:]):
    body = mapped(start, end - start)
    rows = list(decoder.disasm(body, start))
    assert sum(row.size for row in rows) == end - start
    direct_calls = [(row.address, int(row.op_str, 16)) for row in rows
                    if row.mnemonic == "call" and row.op_str.startswith("0x")]
    spawn = [(site, dest) for site, dest in direct_calls if dest == 0x465190]
    assert len(spawn) == 14
    for site, _ in spawn:
        index = next(index for index, row in enumerate(rows) if row.address == site)
        assert rows[index - 1].mnemonic == "push" and rows[index - 1].op_str == "0x332"
    mul99 = [row.address for row in rows if row.mnemonic == "imul"
             and row.op_str.endswith(", 0x63")]
    assert len(mul99) == 14
    references = {}
    for row in rows:
        match = re.search(r"\b(dword|qword) ptr \[(0x[0-9a-f]+)\]", row.op_str)
        if match and row.mnemonic.startswith("f"):
            address, width = int(match.group(2), 16), match.group(1)
            literal = mapped(address, 4 if width == "dword" else 8)
            references[(address, width)] = {
                "address": hex(address), "width": width,
                "raw": literal.hex(),
                "value": struct.unpack("<f" if width == "dword" else "<d", literal)[0],
            }
    outward_edges = [
        {"site": hex(row.address), "destination": row.op_str}
        for row in rows if row.mnemonic.startswith("j") and row.op_str.startswith("0x")
        and not start <= int(row.op_str, 16) < end
    ]
    assert all(0x620920 <= int(edge["destination"], 16) < 0x62EFBE
               for edge in outward_edges)
    cases.append({
        "action": action, "start": hex(start), "end_exclusive": hex(end),
        "bytes": len(body), "sha256": hashlib.sha256(body).hexdigest(),
        "linear_instructions": len(rows),
        "x87_instructions": sum(row.mnemonic.startswith("f") for row in rows),
        "spawn_object_id": 0x332, "spawn_call_sites": [hex(site) for site, _ in spawn],
        "signed_facing_times_99_sites": [hex(site) for site in mul99],
        "direct_calls": [{"site": hex(site), "destination": hex(dest)}
                         for site, dest in direct_calls],
        "x87_absolute_literals": list(references.values()),
        "outside_case_direct_branches": outward_edges,
    })

assert [case["bytes"] for case in cases] == [2008, 2002, 2190, 2190]
result = {
    "evidence": "hash_attested_PE_physical_case_decode; not complete source or an exact match",
    "target_sha256": TARGET_SHA, "root_sha256": BODY_SHA,
    "action_family": [565, 566, 567, 568], "cases": cases,
}
output = ROOT / "build/iku-565-family-20261002.json"
output.parent.mkdir(parents=True, exist_ok=True)
output.write_text(json.dumps(result, indent=2) + "\n")
print("Iku 565--568:", sum(case["bytes"] for case in cases),
      "physical bytes;", sum(len(case["spawn_call_sites"]) for case in cases),
      "spawn sites;", sum(len(case["outside_case_direct_branches"]) for case in cases),
      "cross-case branches")
