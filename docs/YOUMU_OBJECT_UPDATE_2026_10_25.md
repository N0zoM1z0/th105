# YoumuObject complete update `0x0053CEA0`

## Observed target facts

This packet covers the original Japanese 1.06a executable only, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Run the read-only raw audit:

```sh
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-youmu-object-update-target.py
```

RTTI-owned YoumuObject primary vtable `0x006C50BC`, slot28 cell `0x006C50E4`,
points to this entry. The next slot3C initializer cell `0x006C50F8` points to
`0x00543670`, immediately after the complete update payload. It is a separate
previously parked scope.

The callable range is `0x0053CEA0..0x005433F7`, 25944 bytes, SHA256
`c3334cf4f772931661dfddf7ffd6adb702b99aedf369809f11e8ec1d0171492e`.
The complete range through its switch metadata ends exclusively at `0x00543670`,
26576 bytes, SHA256
`4cc99136a6fc0fc7238c89bde5509d3504be026086b5f35a97cf219973a5911b`.
The raw traversal closes 6233 reachable instructions out of 6236 decoded,
49 RET0 sites, 224 direct calls to 20 entries and 30 primary-vtable calls.
Every direct branch and switch destination stays inside the callable range;
there is no external direct tail jump. The three unreachable instructions
are alignment LEAs at `53EE2A`, `5420DA` and `542F29`, totaling 19 bytes.
They remain part of the physical comparison extent.

The prologue aligns ESP to eight bytes and allocates `0x48` bytes, saving
EBX/EBP/ESI/EDI below that frame. It keeps the ECX receiver in ESI. Do not copy
Remilia's smaller frame or assume its four-float parameter packets: Youmu's
first action already passes five floats. The working no-argument member view
has RET0; the original source return type and full owner layout are unknown.

The metadata has no intervening gap or separator. Its 632 bytes partition as:

| Address | Contents |
| --- | --- |
| `5433F8` | 29 DWORD destinations |
| `54346C` | 200-byte remap for actions800..999 |
| `543534` | 5 DWORD destinations |
| `543548` | 6 DWORD destinations |
| `543560` | 5 DWORD destinations |
| `543574` | 13 DWORD destinations |
| `5435A8` | 4 DWORD destinations |
| `5435B8` | 4 DWORD destinations |
| `5435C8` | 6 DWORD destinations |
| `5435E0` | 9 DWORD destinations |
| `543604` | 11 DWORD destinations |
| `543630` | 8 DWORD destinations |
| `543650` | 8 DWORD destinations |

Primary cases are800,801,810,811,812,813,815,817,818,820,821,823,
848,850..857,899,900,901,902,930,980,999. All other remap entries
select the default continuation `5433EB`. Case848 is physically after899.
There is no903 case. The audit emits all remap destinations, the exact call
sites and the independently inspected virtual slots0C/14/1C/20.

## Callee interfaces under review

These are declaration-only working call views, not new helper implementation
or exact credit. The current ledgers already accept17 of the20 direct callees;
the two quantized trig lookups remain source-present, and `68A1A0` is compiler
conversion support. Call counts constrain the complete source review.

| Entry | Calls | Working view / evidence |
| --- | ---: | --- |
| `435160` | 18 | receiver+4, two floats, RET8 |
| `45C030` | 13 | owner dispatch, unsigned index, RET4 |
| `64CCB0` | 58 | unparented spawn, seven stack words, RET28 |
| `5575C0` | 8 | repeated emitter, three ints, AL result, RET12 |
| `4063D0` | 10 | cosine lookup, float input, ST0 result |
| `4351C0` | 16 | frame continuation, AL result, RET0 |
| `68A1A0` | 8 | compiler float-to-integer support |
| `4FC710` | 3 | bounds descriptor, four ints/three shorts, RET28 |
| `435240` | 1 | effect code/two floats/direction/trailing, RET20 |
| `5B0400` | 4 | relative-position helper, two ints, RET8 |
| `4963A0` | 10 | six-counter conditional continuation, limit, RET4 |
| `4067D0` | 49 | RNG limit, integer cdecl result |
| `64CD00` | 4 | phase continuation, limit, RET4 |
| `406360` | 11 | sine lookup, float input, ST0 result |
| `406540` | 3 | atan2, two floats, ST0 result |
| `53CDF0` | 1 | owner-history record application, unsigned index, RET4 |
| `4E0BF0` | 1 | heading turn, three floats, RET12 |
| `406580` | 3 | square float, float cdecl/ST0 result |
| `53CBC0` | 1 | ping-pong motion and periodic spawn, RET0 |
| `435D60` | 2 | ECX receiver, no stack input, ST0 height, RET0 |

Do not infer a bool domain for `4351C0`: it returns AL from a virtual callback
on its nonzero exit. Likewise, `64CCB0` forwards its complete direction DWORD
through a virtual manager call. A byte load at one call site does not prove
that changing all directions to byte parameters is safe. Each caller's
signed or unsigned extension must be preserved.

## Optional analysis hypothesis

IDA preflight still rejects the GUI's different executable SHA256
`10350095bcf95edb59e03bee9849a2dc8a7714b4927ad5909c569c550fce6822`.
No IDA data or writes are used.

A single direct Ghidra headless process ran readonly/noanalysis, CPU0/nice10,
one CPU and384MiB heap. Before decompilation it independently attested the
imported SHA256, PE image/entry/language/compiler and all four mapped sections,
then the complete raw callable hash above. Temporary entry/body and ABI views
were read back; root metadata was removed/restored in a rolled-back transaction.
All nine primary project-file hashes agree before and after. The initial pass
stopped because the working DB lacked the already accepted `406580` entry;
its transaction rolled back and project hashes remained unchanged. The second
pass added that target-bounded temporary view and completed. No new import or
analysis process was launched concurrently.

Private receipts live under
`build/exact-first-youmu-object-update-20261025/`: `raw-facts.json`,
`target-audit.json`, `ghidra-receipt.json`, `ghidra.log`,
`primary-db-before.json`, `primary-db-after.json`, and `decompile.txt`.
Decompiler output is only a hypothesis. It does not establish signedness,
rounding, callback read epochs or source lifetimes without instruction review.

## Current boundary of this checkpoint

The complete raw control flow and metadata are closed. Source recovery is next,
followed immediately by the first complete VC8 object/whole-payload comparison.
There is no selected update source, new mapping, match unit or exact claim yet.
Original source identity, full owner layout, original TU/compiler ownership and
the recoverable standalone source shape remain unknown. Remilia557690 stays
parked with its documented finite controls; this packet does not reopen it.
