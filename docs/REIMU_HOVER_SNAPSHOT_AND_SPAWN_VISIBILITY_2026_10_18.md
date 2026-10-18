# Reimu: hover Y snapshot and real spawn-body visibility

Action616 now captures its double Y value before the height query, reproducing
the target's real load/spill/compare order. The selected giant root stays
within its candidate boundary, but remains nonexact at+541. Separate ordinary
and LTCG controls show that making the real spawn wrapper visible is
insufficient to change the preceding giant-root payload, even though a small
caller inlines that same wrapper.

## Target and selected source

Target is original Japanese TH10.5 v1.06a SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Root478FA0 owns `[478FA0,48CE2E)`,81550 bytes, SHA-256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
The root remains authored/unclassified/declaration-only in the live ledgers.
IDA preflight still rejects another image. This work uses the hash-attested
PE; it does not write any analysis database or target instruction.
All nine primary database files retain their preceding SHA-256 pins, checked
again with a1MiB streaming buffer.

In616 sequences4/5, the target executes:

```text
489DFA  FLD   DWORD PTR [ESI+F0]
489E00  MOV   ECX,ESI
489E02  FSTP  QWORD PTR [ESP+18]
489E06  CALL  435D60
489E0B  FADD  QWORD PTR [6C1B08]    ; 300.0
489E11  FCOMP QWORD PTR [ESP+18]
489E15  FNSTSW AX
```

The old source queried height before loading Y and compared two x87 stack
values. `ReimuActionStateHighMiddleCases.hpp` now declares the actually used
`const double current_y = y_f0` before that query. Braces delimit the existing
sequence4/5 arm. The candidate now performs the early load, m64 spill and
memory comparison. No interface, shared layout, compiler flag or dummy local
changes. The complete89-byte435D60 getter reads X/surface data, so the finite
output values alone cannot establish this Y-read order.

The physical616 instruction/edge diagnostic changes from1081 bytes/35
difference groups to1087/23, versus target1085. These counts include encoded
registers and original whole-root edges; they confer no partial exact credit.

Fresh genuine ordinary object SHA-256:
`3dd029c90c6f1578fc5526b4c4f2e1e19689b361b21648069cd086d41e9316e7`.
Canonical ordinary and genuine linked payloads agree over all82888 bytes:
`9b56f280023bdfda760e8372b692ee92101336f342a85f0cd8010a4cd92f8288`.
Prefix81516, frame570h and11 switches remain; source reachable instructions
are20285, target20243. All2472 fields replay:1184 calls,1104 numeric literals,
14 metadata addresses,163 code pointers and7 globals. All1281 HIGHLOWs and
all15 request/preparation contracts qualify. The linker envelope is82896:
82888 payload plus **8 INT3 bytes**. The preceding two notes mistakenly said12
for this phase; their prose is corrected. The reader always checked8. The
older82916-byte phase's12-byte gap is a different result.

The first strict difference is still+541=4791BD, the displacement of JNE4791BB:
target489D6A versus source489D41. Fresh complete-membership census preserves
the six recovered landing/height/slotC groups from
[the preceding checkpoint](REIMU_SHARED_LANDINGS_2026_10_18.md). Eight direct
callee partitions still differ, with zero per-action direct-count deltas.
Indirect physical totals220/220 still leave action deltas73(3/2),75(5/4),
88(3/2),200(3/2),410(4/3),416(5/4). Full action sets remain significant.

## Focused execution and wrong-order control

`audit-reimu-void-root.py --cohort hover_snapshots` reuses336 finite hover
inputs and six required-branch inputs from the existing high-middle family,
then adds12 NaN/infinity inputs over both sequences and x87 precisions.
All354 require the actual target489E06 and RET. A read-only memory observer
records the first root actor-Y read and first actual root height query,
including the raw Y word. It changes neither memory nor execution. Target
coverage requires the early read; the normal ordered-call comparison checks
the source observations too.

The selected root passes **0/1649**:354 hover,1010 integration and285 nonflat
surface cases. The compiled preceding candidate, whose complete canonical
payload is7816b79c… from the prior checkpoint, fails **354/354** hover inputs
under the same observer. Its recorded example has equal actor bytes and real
RET on both sides, but reads Y after the height call. This control establishes
that the new coverage detects the load-order error even with the real pure
getter. Both normal x87 precisions and unordered/nonfinite comparisons are
exercised. No unrelated historical matrix or all-unit replay was run.

```sh
nice -n 10 taskset -c 0 python3 -B scripts/probe-reimu-action-ltcg.py
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-call-sharing.py build/reimu-ltcg/ordinary.obj
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-void-root.py build/reimu-ltcg/ordinary.obj --cohort hover_snapshots --cohort integration --cohort surface_inputs
```

## Preceding-phase controls: remaining trajectory tails

The following private controls start from commit e0613d7, before the616 edit:
ordinary7fe0c1a8… and full canonical7816b79c…/82888 bytes. They are read-only
code-generation diagnostics; oversized candidates were never executed or
selected. The callable/envelope excesses retain the ordinary strict limits.

| Control | Callable/envelope excess | Remaining direct partitions | Observation |
| --- | --- | --- | --- |
| Capture Y before each final815 request in520..523 | 0/0 | 8 | Entire82888-byte canonical payload unchanged. |
| Existing int-direction view plus real int+20 captures | 202/200 | 6 | Complete owned-request and wave partitions recover; root exceeds both limits. |
|523 mutually exclusive sequence1 exit before sequence5 guard | 110/108 | 6 | Same two complete partitions recover; root exceeds both limits. |
|127 terminal outer returns become switch breaks | 0/0 | 8 | Owned/wave physical counts worsen to240/74 versus243/77. |
|523 exit ordering plus those terminal breaks | 62/60 | 8 | Still oversized; owned/wave241/75. |
| Private bool advancement view | 0/0 | 8 | Same graph, sharing, frame and first mismatch. |

The private bool view uses the reviewed Reimu vtable:4351C0 forwards its
completion path through slot14 to45C220, whose complete138 bytes return0/1.
That concrete receiver evidence does not establish every generic receiver or
the original formal type. No public binding or header was changed.

The target522 and523 each have a separate final815/wave/advance suffix:
48598F/485998/48599F and485D65/485D6E/485D75. The selected source still
shares them at4859A1/4859AA/4859B1. Their per-action call counts agree;
physical sharing remains wrong. Target520/521 sharing already agrees, and
their first four request spans retain the prior instruction/edge results.

## Real wrapper visibility: positive small caller, unchanged giant

The private `ReimuSpawnVisible.hpp` supplies the two actual existing member
definitions before callers. Each forwards the nine real request words through
manager+658/vslot4, using the receiver's observed byte direction/variant.
Both standalone overloads reproduce the complete target465190 wrapper:
66/66 bytes, no relocations, SHA-256
`80aab8cb379377dc179c3e1311599ab890885fa92ffd5ecf075ff6c3df15a7fc`.
There are no helper stubs, assembly bodies or replacement target calls.

A separate60-byte small caller inlines the real manager/slot4 body. This
positive control confirms that the definitions are usable for inlining.
The giant-root TU contains no extra small caller. Its ordinary section bytes
and every relocation identity remain equal to the preceding baseline; it
retains all242 spawn calls. The complete canonical82888 bytes remain7816b79c….

The genuine /GL control links the same pinned real source/CRT providers,
removes the two weak spawn aliases and exports the actual overloads. Both
full66-byte linked anchors match and are MAP-owned by root-gl.obj. Root at
100010A0 again replays all2472 fields/1281 HIGHLOWs and the separate8-byte
alignment gap; all82888 canonical bytes remain7816b79c…. The private DLL hash
is `f87438223ce1b930470106892cd09e581c9159b7973c8c5fd6b4c2725f4ead17`.
No diagnostic DLL is executed and no comparator acceptance rule is relaxed.

Receipts and recipes are under `build/reimu-trajectory-tails/`, with baseline
source hashes in `visible-spawn/*receipt.json`; regenerate at the stated phase
before relying on them. Real body visibility alone does not explain this
baseline giant's non-inlining. The original TU, inline budget and final source
shape remain unknown. Do not repeat this control as if visibility were still
untested, or generalize it to every future source phase.

Heavy jobs run serially on CPU0 at nice10. The genuine producer peaks at
320936KiB (about313MiB); the focused native run stays below190MiB. Disposable
control objects, superseded generated sources and Python caches were removed:
520 files/15.52MiB. Current genuine providers, the int+20 positive witness and
the real-visibility source/small caller remain useful and are retained, along
with phase receipts and recipes. Keep the current genuine provider cache. No exact ledger,
accepted unit, aggregate percentage or root credit changes.
