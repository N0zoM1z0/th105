# Reimu primary slot 3C: complete action-entry source

`Reimu_initialize_action_entry @ 0x00491C40` has complete source in
`src/characters/ReimuActionInitialization.cpp/.hpp`. As of 2026-11-14 the
3785-byte body differs from the target only in two cross-jump decisions: the
404/414 shared-tail direction and case 322's branch into case 305's tail.
Three fixes got it there. The offset-macro accessor replaced an inline `at<T>`
template, the case 408/321 and 307/306 fallthroughs were added, and case 669
stores 0x734 first. Trials and the open lead are in the
[patterns note](VC8_SOURCE_SHAPE_PATTERNS.md). No exact credit.

## Observed target and boundary

Only original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Fresh target/status/target-required tracking checks pass. The new IDA
preflight again rejects GUI SHA `10350095...`; no IDA calls or writes follow.
All 964 main instructions were read from the hash-attested PE. No Ghidra
process or new database is used.

The RTTI-backed roster manifest pins Reimu primary vtable `6C412C`, cell
`6C4168`, slot `+3C`, to `491C40`. The main extent is `[491C40,492B09)`, 3785
bytes, SHA256
`ab70f8336d04a7698b0acaa29ca0ea8784f7a80b36bc7abb3e155d7a5ac7b04b`.
It preserves EBX/ESI/EDI, uses ECX as the receiver and a real four-byte
temporary, has 39 RET 0 exits and one default tail to `477830`. No GS/EH
registration is present. Void is the source return view; original spelling
and the original nominal class/TU boundary remain unknown.

Resolving all three indirect jumps closes 960 reachable instructions/3767 main
bytes. The remaining 18 main bytes are two branch-skipped loop-alignment ranges
(`491DD6..491DDF`, `4920C8..4920CF`). All reachable edges remain inside the
main span or the observed common-initializer tail `477830`.

| Destination table | DWORDs | Index table | Bytes | Input range |
| --- | ---: | --- | ---: | --- |
| `492B0C` | 14 | `492B44` | 211 | 4..214 |
| `492C18` | 31 | `492C94` | 251 | 301..551 |
| `492D90` | 18 | `492DD8` | 234 | 565..798 |

The complete payload is `[491C40,492EC2)`, 4738 bytes, SHA256
`ae72adaa4142577f69d3e97cf57e629c4bcce932a82457c8421dafdf9075f842`.
Five bytes align the main/tables. The remaining padding before the next
candidate `492ED0` is not added to the source comparison. Callable ownership
and adjacent switch metadata remain separate.

## Source and early comparison

The source is a complete numeric switch with typed offset accesses and
declaration-only callees. Its receiver view is never instantiated and makes no
claim about the full Reimu object size. It retains the actual signed action
word, narrow counters, flags, float fields, signed-facing coordinate arithmetic
and unsigned-facing transport. Effects/events, the 5-iteration effect loops,
owned-object request, motion resets and default common initializer are all
represented. Callee declarations confer no implementation credit.

The first full source was compiled and whole-compared immediately. It emits
4674 bytes (`fbd692e7...`), with the first mismatch at+0x0D because grouping
case 300 with 301 changes the switch pivot. Independent case 300 restores the
target 300/301 partition (`a24e5bc4...`). All direct-callee counts and all remaps
already agree in that first complete object; these are diagnostic facts,
not a substitute for canonical equality.

Target-backed changes preserve the observed state/velocity write order,
floating zero-assignment order and narrow-word clear groups. The corresponding
whole outputs are 4722 bytes (`d4afd81b...`, `b2d604b8...`, `aa5bc271...`).
Normalizing the facing read to one signed-byte view plus unsigned conversion
is byte-identical to `aa5bc271...`; do not repeat that spelling question.

## Independently supported direction interface

The real wrapper `435240` forwards a full stack slot through global `6FBCB0`.
That transport does not alone establish an int formal. The existing accepted
bootstrap constructs CEffectManager<EffectObject> at `4378F0`, publishing its
primary vptr `6C1490`; slot `+0C @6C149C` contains `437C00`. That accepted
115-byte provider reads direction with `MOV AL,BYTE[ESP+18] @437C3F` and copies
the byte into the spawned object. The corresponding flag read is `437C49`.

The ordinary C++ witness `scripts/native/reimu_effect_byte_forwarder.cpp`
uses the byte direction consistently in both wrapper and virtual declaration.
It freshly reproduces **all 52/52 bytes** of `435240`, SHA256
`766e73525d2dfc9742f5e6e054a58e61f65b5def458e9c42a3aff78b2c075fd8`,
using the already pinned effect-sink global. It adds no helper/exact credit.
Only this new receiver declaration changes; shared accepted headers and their
int transport views are untouched. This establishes a valid byte interface,
not uniqueness of the original declaration.

Applying the interface to the root yields 4702 bytes (`4893d60d...`). It removes
the artificial double extension of the same facing byte and restores the low
switch's physical partition sizes. The whole root remains nonexact.

## A concrete native counterexample and correction

The remaining shared-tail differences prompted a scoped scalar-state check.
It found 28 failures, all at **owner+750** in actions 502/507. Reading those
actual target edges back shows the complete issue: actions 500/501,502/503/
512/513,505/506,507/508,510/511 enter the cleanup tail at `492382`, which also
writes byte`+750=1` after the three word clears. The first source omitted that
write from all five source arms. The selected source corrects the entire group.

The extended check now passes **210/210 scoped native cases**. It covers the
affected family plus the distinct 306/307/321/797 entries, signed 607 threshold,
zero/scale paths and related clears. Finite, signed-zero, subnormal, maximal,
infinite, quiet-NaN and signaling-NaN velocities run under both masked x87
control words 27F/37F. Each side executes the complete selected root path and,
where called, the actual 27-byte `45AF40` zero-motion helper through real RET 0.
There are 84 genuine helper entries on each side. No opaque return, instruction
stub, fabricated provider result or substituted store is used. Full 0x900-byte
owner snapshots, caller stack cleanup and callee-saved registers are checked.
Effect/resource/default-helper paths are outside this bounded native cohort;
no whole-game or unmasked-trapping-environment claim is made.

The corrected whole payload is `e14c2c80...`, still 4702 bytes with 2489 unmasked
differences including 36 bytes of size difference. Different shared cleanup
positions shift the tables; candidate has 38 RETs versus 39. Complete native
state agreement does not excuse those differences.

## Finite controls and remaining unknowns

An accessed-prefix member-layout control emits 4714 (`d8d164dd...`) before the byte
interface, and 4694 (`f47665e4...`) with it. Neither is selected. Capturing case 76's
direction/Y inputs introduces a real extra temporary/frame and changes physical
helper/exit sharing (`5405b9af...`); it does not close the target. Capturing genuine
double velocity products emits 4694 (`75bb9e7d...`), also unselected. Preserve these
receipts instead of adding storage or register constraints.

Original helper visibility, caller/TU optimization context and the remaining
shared-tail/FP scheduling are unresolved. No standalone/LTCG impossibility is
proved. A next useful bounded representative is the actual common initializer
`477830`, candidate 4849 bytes: first establish its origin, complete boundary
and ABI from raw target/call/RTTI evidence. It currently remains unclassified
and source-missing; Reimu's default tail is evidence to investigate, not an
automatic promotion. This can supply real family context without fabricated
callers or a broad flag search.

## Reproduction

Run serially, CPU 0/nice10:

```sh
scripts/repo-python scripts/build.py --unit exact-first-reimu-action-initialization --compare --json
TH105_ENABLE_GS=0 TH105_FP_MODE=default TH105_INLINE_MODE=default \
  scripts/compile-unit.sh scripts/native/reimu_effect_byte_forwarder.cpp build/reimu-byte-wrapper.obj
TH105_ENABLE_GS=0 TH105_FP_MODE=default TH105_INLINE_MODE=default \
  scripts/compile-unit.sh src/characters/ReimuActionInitialization.cpp build/reimu-entry-cold.obj
```

Full comparisons deliberately return 1 until exact. Five target-free negative/
fixture tests guard all table extents, including malformed last-table indices,
metadata destinations, truncated remaps and unreviewed external tails.
No prior accepted source, header, compiler profile or relocation key changes.
Only new exclusive literal aliases and local function bindings are added.
Source-present1545/mapped1564, units 584; exact stays 1403/359740 bytes. No new
aggregate cold replay is claimed.

## Action 616 initialization tail

The original action 616 path at `0x49292A` calls zero-motion, clears `+0x73C`, and then has its own state-publication tail rather than joining action 612's tail. Reordering the independent `+0x184` and `+0x47E` writes after the call preserves behavior and causes the focused candidate to recover that distinct native instruction sequence and store order. The fields do not overlap and no call intervenes. The full candidate section is now 4,734 bytes versus the 4,738-byte original payload. Full relocation replay remains non-exact, with 2,296 differing byte positions and first difference +0x28; no exact credit is claimed.
