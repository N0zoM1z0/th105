# Common Fighter sequence join at actions 73, 75, and 88

## Scope and target

This bounded review concerns `CharacterEx::update_common_action_state @
0x004740C0`, specifically the shared sequence-selection entry at `0x00474992`.
The input is the original Japanese TH10.5 v1.06a executable with SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The tracked source and exact-match ledgers are unchanged. The callable remains
10,219 bytes and canonical-nonexact at `0x004740D4` (+0x14).

## Observed in exact target bytes

The raw PE disassembly and `scripts/audit-giant-action-owners.py` agree on
these physical edges:

| Action | Zero load and comparison | Selection edge | Other edge |
| --- | --- | --- | --- |
| 73 | `fldz` at `0x0047495C`; frame/sequence guards; `fcom [esi+0xF8]` at `0x00474985` | Fallthrough to `0x00474992` | Guards/zero test jump to `0x004749B8`, whose `fstp st(0)` at `0x004749C0` drops the zero |
| 75 | `fldz` at `0x00474B7C`; `fcom [esi+0xF8]` at `0x00474B7E` | `jp 0x00474992` at `0x00474B89` | `fstp st(0)` at `0x00474B8F`, then the normal epilogue at `0x00474B91` |
| 88 | `fldz` at `0x00474E81`; `fcom [esi+0xF8]` at `0x00474EAA` | `jp 0x00474992` at `0x00474EB5` | Counter/friction path at `0x00474EBB`, with `fstp st(0)` at `0x00474EC3` |

At the shared entry, `fcomp [esi+0xF4]` at `0x00474992` consumes the live
zero. The virtual slot `+0xC` is called with sequence 3 on the fallthrough
path (`0x004749A6`) and 2 on the other path (`0x004749AF`); both return through
the ordinary four-pop epilogue. These observations support the current
source's selected sequence and x87 stack balance. They do not establish the
original C++ branch spelling or compiler phase.

The raw-control-flow boundary audit reports 2,799 reachable instructions and
10,219 reachable bytes, with no unreachable bytes in this callable. The
candidate boundary and authored classification remain provisional in the
ordinary ledger sense; this review did not promote an exact match.

## Focused source-shape controls

Each row compiled only `gpt-web-fighter-common-action-state` with pinned VC8,
one compiler process on one CPU core. The complete canonical comparator and
owner audit ran after each build. All probes were reverted. The ignored local
reports are `build/common-73-*.json`, `build/common-75-combined-guard*.json`,
and `build/common-current-*.json`.

| Control | Candidate window SHA-256 | Identical owners / 66 | Selection ownership |
| --- | --- | --- | --- |
| Production baseline | `99563500433bccf1f68e7c256b438595de9cdcf5b18aee4816f19e69e1cda835` | 53 | Selection emitted in action 88 |
| Explicit action-73 slide continuation | same as baseline | 53 | Still in action 88 |
| Reverse the source condition around the two sequence calls | `84fd0e1db82fe0d85c1c98cb08003a2dc872e12d9614904a9913e9c4cf5a3cea` | 53 | Still in action 88; local encoding changes |
| Combine action-75 completion guards | same as baseline | 53 | Still in action 88 |
| Make action 73 explicitly jump into the common selection label | same as baseline | 53 | Still in action 88 |

The target owns 344 bytes in action 73, 148 in action 75, and 310 in action
88. The production candidate owns 310, 148, and 344 respectively. The moved
34-byte selection tail accounts for this paired span difference; action 75's
local body has the target length but jumps to the candidate's action-88 copy.
Neither same-size action 75 nor 53 matching diagnostic owners is partial
canonical exactness. All five comparisons remain nonexact at +0x14; no match
row is added.

## Analysis backend and next discriminator

The local `scripts/check-ida-mcp.py` preflight rejected the active IDA image:
its reported SHA-256 was
`10350095bcf95edb59e03bee9849a2dc8a7714b4927ad5909c569c550fce6822`.
A single local Ghidra 12.1 headless import of the SHA-checked target was
limited to two cores, then stopped after more than six minutes of incomplete
whole-program auto-analysis. It produced no decompilation or semantic fact used
here. This review relies on raw target bytes and the strict VC8 comparison.

The observed shared x87 path and the compiler output rule out these four
source spellings as a placement discriminator in the present standalone unit.
What causes the target to own the tail in action 73 remains unknown. A future
probe needs an independent source, type, or translation-unit visibility fact;
repeating equivalent condition or `goto` syntax has no evidence-based value.
