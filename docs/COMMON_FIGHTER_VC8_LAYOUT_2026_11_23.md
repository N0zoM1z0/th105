# Common Fighter sequence selection and VC8 block order

The target places the sequence tail of common Fighter `0x004740C0` at
`0x00474992`, inside action 73. Actions 75 and 88 jump to it with an
x87 zero live. The selected source gives each case its own selection and
exits the switch with `break`. VC8 merges the lowered copies into 73
and reproduces all 802 bytes across the three physical spans.

## Discovery order with the shared source label

The trace uses the repository's VC8 SP1 14.00.50727.762, `/O2 /GS- /GR
/EHsc /MT`, and the same game-specific Wine prefix. Wine/GDB runs headless.
The on-disk `c2.dll` hash is pinned at
`497d1ffe57f75db8b458167bdea475f3962829e139b355a2672a4ef51c716413`.
The loaded image is at `0x10B00000`. A breakpoint at its wide compiler-pass
entry confirms that CL passes `-Og -Ob2 -Gy -EHs -MT`. The listing adds
`/FAcs`. Complete relocated equality against the ordinary build verifies
that the listing and breakpoints preserve the generated function and tables.

The node stamped with the source line of the horizontal-velocity test
keeps its identity across the following observations in each process.
Addresses in the table belong to this build of `c2.dll`.

| Observation | Where the horizontal-velocity test appears |
| --- | --- |
| `0x10C064F9`, after reading the function's intermediate language | In action 73, before the action 75 and 88 guards |
| `0x10C06C53`, before the call to `0x10B26CA0` | Still in action 73 |
| `0x10B26CA8`, before `0x10B281E0` | Still in action 73 |
| `0x10B26CAE`, immediately after `0x10B281E0` | After the action 88 guard |
| `0x10C065F8`, after the call to `0x10C07400` | Lowered to an x87 compare node in the new position |
| `0x10B2419F`, after native instruction encoding | `fcomp [esi+0xF4]` at function offset `+0xDD5`. The two earlier cases branch there from `+0x8D0` and `+0xAA7`. |

For the graph reads, follow the first instruction through
`dword(dword(dword(function + 8)) + 0x1C)`. Each instruction record starts
with its next pointer, has its opcode at `+4`, and stores a relative
source line as a word at `+0x14`. The original source lines 466, 468, 539
and 619 identify the 73 guard, the moved comparison, the 75 guard and the
88 guard. `0x10B281E0` walks a reverse block order rooted at `[graph+8]`,
following each block's `+0x10` pointer. It calls `0x10B28270` to write the
physical successor and splice the instruction list. The input order
already puts selection after action 88. The baseline has the selection
test at reverse index 439 and the final action-88 guard at 441. Omitting
action 88 in scratch puts the selection test at 451 and the final action-75
guard at 454. Reconstructing the baseline DFS from all 658 blocks and
their outgoing edge lists reproduces C2's complete postorder. The low
switch reaches 88 before 75 and 73. Action 88's successful final guard
discovers the shared block from the source label in 73.
The COFF encoder's return at `0x10B2419F` exposes the current
instruction record in EDI, the output offset at `[ESI+0x18]`, the encoded
length in EAX, and the bytes at `[ESP+0x48]`. The raw target and the fresh
owner audit supply the native and candidate offsets independently.

## Source and translation-unit controls

Making the exact `classify_fighter_x_boundary` definition visible in the
carrier left its standalone body exact at `0x00435910` (59/59 bytes).
The giant root retained 18 of its 30 calls, shrank to 9,145 bytes including
tables and no longer kept the same action-entry topology. This is a
measured effect of definition visibility under the same profile. Retain the
declaration-only boundary in this carrier while the native calls remain
present. The control uses the body from `StageGeometry.cpp`, which reads
the typed X coordinate and compares it to the stage thresholds.

The earlier shared-label source added explicit zero comparisons and an
unsigned-byte conversion at the landing predicate. Those edits preserved
the complete 10,801-byte candidate after replaying all 396 relocations.
Duplicating the selection tails with direct returns regresses the owner
diagnostic from 53 to 51 out of 66. Moving action 73's ordinary motion to
the guarded arm ahead of selection is byte-neutral. In action 88, splitting
the float guard from the integer guards or putting the motion return first
is also byte-neutral. Duplicating just its selection with a reversed
velocity test loses the previously matching action 799 owner.

## A shared switch exit restores action 73

The three cases retain separate comparisons in their own blocks before
and after `0x10B281E0`. All three still reach the late merge at
`c2.dll:0x10B2C950` after x87 lowering. At its return to
`0x10C077B6`, only 73's comparison remains. This keeps 73's fallthrough
into `0x00474992` and restores the backward jumps from 75 and 88.
Leaving any of the three selections as a direct return did not recover
all three spans. Several mixed-exit builds also changed action 799's
jumps to the epilogue.

The formal build and the headless traced build agree over all 10,801
bytes after replaying 396 relocations. The span lengths and offsets for
73, 75 and 88 agree with the target, and a direct byte comparison matches
344, 148 and 310 bytes respectively. The whole-root diagnostic improves
from 53 to 56 matching owners out of 66 and preserves all former matches.
The complete comparison against the 10,725-byte target falls from 4,979
to 3,698 differences. The first difference remains at `0x004740D4`.

## The shared horizontal-speed clamp

The native 55/56 and 159–162 paths enter action 50 at `0x00474122` to
store the rounded speed or at `0x00474139` to drop the x87 zero and
skip the store. The 53/54 paths enter later at `0x00474161` for the
frame advance. In the rebuilt function those entries are in action 162.

The clamp's speed store is instruction-list entry 82 before the call to
`0x10B281E0`. The same node is entry 3031 at the return, just after
action 162's branch. The boundary publication and frame advance move
with it. The headless trace reproduces the complete 10,801-byte candidate
after all 396 relocations.

Sharing the frame advance explicitly with action 50, or sharing both
boundary publication and advance, yields the same 10,741-byte candidate.
Both lose action 50 without recovering any of the incoming owners.
Putting the clamp store in that shared source path emits 10,717 bytes
and loses action 799 as well. The size change alone is misleading.

The retained source names the three shared entries and keeps the two steps
in cases 159–162 in scoped float locals. The native steps use the double
promotion of `0.6f` and round to float after each addition. That rewrite
kept the complete envelope and the 53 matching owners at the time.

## Complete comparison

The full target envelope is 10,725 bytes. It ends at `0x00476AA5`, after
both switch tables and before eleven inter-function INT3 bytes. The
contract covers 10,219 callable bytes, 66 jump words, 241 remap bytes and
one alignment byte.

The checker follows the two switches and terminates paths at thirteen
bound REL32 tail calls and eight register-indirect tail calls. The latter
must load the jump register through the receiver's vtable and restore the
Fighter frame. Branches may enter at the start of that setup. All sixteen
reviewed primary vtables, including CharacterEx and the fifteen roster
classes, bind slot `+0x14` to the exact 138-byte `next_sequence_block` at
`0x0045C220`. [Receiver and slot evidence](COMMON_FIGHTER_ROOT_2026_10_16.md#qualified-receiver-domain-and-source-interface)

The pinned target passes the structural check using its decoded relocation
sites. Changing the last index in either table, omitting a virtual tail
site, or removing a register restore or a direct-tail relocation is rejected.
The selected source emits 10,801 bytes and differs first at `+0x14`.
The remaining owner differences are the clamp's eight incoming cases
and the two switch selector instructions.

The focused build and owner commands are in the
[giant root review](GIANT_ROOT_REVIEW_2026_11_23.md#reproduce-the-selected-baselines).
The private driver and retained trace inputs are under `build/common-vc8/`.
