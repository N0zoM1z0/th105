# YoumuObject action-entry nested switch closure

## Scope

The bounded root is `YoumuObject::initialize_action_entry @ 0x00543670`,
whose reviewed callable is `[0x00543670, 0x00544A97)` (5,159 bytes). All
target observations here come from raw bytes of the original Japanese 1.06a
executable, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The active IDA MCP image has a different hash; no IDA or Ghidra semantic fact
is claimed in this checkpoint.

## Observed target control flow

The existing owner audit knew the 29-destination action switch but reported
5,083/5,159 reachable bytes, one unresolved indirect exit at `0x0054464F`,
and an unreached range `[0x00544656, 0x005446A2)`. The source path is action
901, sequence 6. Raw target instructions at `0x00544638..0x0054464F` test
sequence 6, load the match identifier from `0x006FA894`, reject values above
3, and execute `jmp dword ptr [eax*4 + 0x00544BD4]`.

The four consecutive target DWORDs at `0x00544BD4` are, in index order:

| Index | Destination | State words written |
| --- | --- | --- |
| 0 | `0x00544692` | `+0x366 = 30`, `+0x368 = 4` |
| 1 | `0x0054467E` | `+0x366 = 25`, `+0x368 = 7` |
| 2 | `0x0054466A` | `+0x366 = 20`, `+0x368 = 10` |
| 3 | `0x00544656` | `+0x366 = 15`, `+0x368 = 12` |

All four bodies rejoin at `0x005446A2`, inside the reviewed callable. The
case-0 store uses `DI`; the enclosing action path loads `EDI = 4` at
`0x005445C6` before reaching this switch. The
table occupies `[0x00544BD4, 0x00544BE4)` after the callable and primary
switch metadata; it is structural compiler data, not another 16 authored
callable bytes.

`config/giant-action-switches.toml` now records this auxiliary table, exact
entry order, and dispatch address. `scripts/audit-giant-action-owners.py`
checks the actual target DWORDs, requires destinations inside the callable,
and requires the configured dispatch to be traversed. A fresh focused audit
reaches **5,159/5,159 bytes**, with no unreached range, unledgered direct
target, or unresolved indirect exit. It reports two validated switch jumps:
the 29-destination action table and this four-destination state table.
This closes raw target branch reachability; it does not prove original TU
ownership or exact candidate bytes.

## Action 820/850 source and comparison

Raw target action 820 writes `phase_index_184 = 1` at `0x00543C0F`, then
unconditionally jumps from `0x00543C16` to `0x00543DA7`. Action 850 starts at
`0x00543D95`, stores two 2.0f scales, then reaches that common tail. The tail
reads `heading_340`, stores its first float to `+0x12C`, converts its third
float, and calls the vtable `+0xC` slot. The ordinary virtual
`select_sequence(int)` call produces the same canonical candidate window as
the former hand-written vtable function pointer, so the source now uses the
virtual call directly. Removing the short-lived local heading pointer is also
byte-neutral.

The target owner spans are action 820 **12** and action 850 **57** bytes;
the candidate still has **26** and **37**. A separate, reverted ordinary-C++
probe writing the common tail independently in both action arms grew action
820 to 46 bytes and moved metadata from +5,156 to +5,176; it did not recover
the target ownership. The retained natural virtual-call source is byte-neutral
against the starting candidate.

Focused reproduction:

```bash
taskset -c 2 python3 scripts/build.py --unit gpt-web-youmu-object-action-entry --compare --json
python3 scripts/audit-giant-action-owners.py youmu-object-action-entry \
  build/match-units/GptWeb_YoumuObjectActionEntry.obj \
  --unit gpt-web-youmu-object-action-entry --json
```

At this checkpoint the complete canonical comparison was **nonexact** at
`+0x80` (`0x005436F0`), with candidate window SHA-256
`b800b08d6f4fe213079dfccf0653a652d9095350ab76985b63237b0b1f1ca6da`.
The subsequent action-901 arm-order improvement has its own comparison below.
The original source/TU condition that places the shared 820/850 tail in
action 850 remains unknown.

## Subsequent action-901 arm-order checkpoint

Raw target table order is case 0, 1, 2, 3, but the physical target bodies are
laid out case 3, 2, 1, 0 at `0x00544656`, `0x0054466A`, `0x0054467E`,
`0x00544692`. The retained source now lists those four ordinary `case` arms in
physical order while preserving each case's state writes. A fresh pinned
single-core VC8 build keeps the action-901 span at 597 bytes and the whole
candidate metadata start at +5,156. The action-901 diagnostic difference
blocks drop from four to three; the four branch bodies now align, while its
virtual-call push scheduling and table address still differ. The owner audit
remains **6/30** instruction-and-edge-identical; action 820/850 remains
**26/37 candidate versus 12/57 target**.

Strict comparison of the full 5,159-byte callable still fails at `+0x80`.
The new compared-window SHA-256 is
`0b174356a268e762184a61f94774ae9af698df7af1ae230a548e055594de1acb`.
No partial or whole exact credit was added. An RTM `/O2` probe reproduced the
previous SP1 candidate window, and two linked `/GL` visibility controls began
with an EBP/aligned frame absent from the target. These probes only exclude
those tested contexts.

An additional bounded action-848 probe gave its `heading_340[2]` conversion
a real local `double` lifetime. The scoped arm preserved action 821's goto
entry. VC8 generated the same candidate window hash and 820/850 owner spans
as the retained source. The probe was reverted: this call-site spelling did
not change the tail placement.

## Current owner-difference inventory

The fresh post-revert SP1 object was rebuilt with one compiler process. Its
full callable still differs at +0x80, and the owner audit compares 30 physical
regions including entry:

| Diagnostic group | Count | Owners / observed difference |
| --- | ---: | --- |
| Instruction and internal edge identical | 6 | entry, 810, 812, 817, 854, 980 |
| One instruction moves within the same-sized owner | 16 | 800, 801, 811, 813, 815, 818, 852, 853, 848, 855, 856, 857, 899, 900, 930, 999; each audit delta is one `push eax` or `mov ecx, esi` deletion plus insertion |
| Other physical differences | 8 | 820, 821, 823, 850, 851, 901, 902, 802 |

The last eight need separate treatment. The 820/850 pair has the tail-owner
inversion described above. Action 821's jump lands at a different intra-owner
offset. Action 823 changes virtual-call register/scheduling and effect-spawn
argument registers. Action 851 changes the heading-pointer register and x87
load position. Action 901 has one `push eax` move plus the shifted auxiliary
table operand. Action 902 moves the phase-byte store across the signed-RNG
correction branch. Action 802 has a candidate-only three-byte alignment NOP.
These are raw diagnostic distinctions; the table does not establish semantic
equivalence or award partial exact credit.

Two further ordinary-C++ probes tested the local lifetime hypothesis. Giving
action 850's sequence conversion a scoped `double` local was byte-identical
to the retained source, including the 26/37 candidate spans for 820/850.
Replacing action 851's retained early `double` value with an early heading
pointer and later conversion made VC8 merge distinct target owners 851/854;
the owner audit rejected it. Both probes were reverted. This supports keeping
the currently distinct 851 lifetime but does not prove its exact source form.

A separate control moved the shared 820/850 tail to ordinary code after the
`switch`, with both action arms leaving by `break` and all other arms still
returning. VC8 generated the same canonical candidate window and the same
26/37 owner spans as the retained labeled form. It was reverted. The observed
tail inversion is therefore not explained by choosing a source label versus
an ordinary post-switch join in this standalone TU.
