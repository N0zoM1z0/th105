# Common Fighter sequence selection and VC8 block order

`CharacterEx::update_common_action_state` at `0x004740C0` is exact under
VC8 SP1. A single action switch produces both native selector instructions.
The switch exits and the explicit edge to the shared return keep the
original case entries and shared tails. The checkpoints below show how
those responsibilities affect one another.

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
frame advance. Before the shared-exit change, all three entries were
in action 162 in the rebuild.

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

The source names the two shared clamp entries and keeps the two steps
in cases 159–162 in scoped float locals. The native steps use the double
promotion of `0.6f` and round to float after each addition. That rewrite
kept the complete envelope and the 53 matching owners at the time.

After restoring the sequence tail, a scratch build gave the eight
clamp consumers their own rounded motion and frame-advance statements,
with `break` at their exits. Changing 50's exit to `break` as well
produced the same 11,049-byte envelope and 405 relocations. Both builds
keep the restored sequence cases, add no matching clamp owners, and
change 799's return branches. The selected clamp therefore still needs
the native entries between its x87 compare, speed store and advance.

### Two passes choose the clamp successors

In the 664-block graph with the detached clamp, the low switch visits
action 162 before the other clamp consumers. Its successful speed test
reaches the store block first. The DFS then discovers the boundary
publication and frame advance through that block, and `0x10B281E0`
places all three after 162.
The late copy emits another `FLDZ` and `FCOMPP` before the clamp.
The exact copy in 50 compares with the live zero via `FCOMP ST(1)`.
Using the same zero local in both source tests preserves the full
output. Reversing the comparison operands selects a memory operand
and adds two alignment bytes after 799's final return. The owner audit
assigns that padding to its final span.

Giving 53 and 54 their own frame advances and switch exits keeps both
calls through x87 lowering. With 51 and 52 still returning directly,
`0x10B2C950` merges the two calls into 52.
The splice at `0x10B30CE6` releases the redundant instructions. The
linked branches now go to `0x0047426D` in action 52. Omitting
52 in scratch moves the destination to 51. Omitting 51 and 52 together
restores the jump to 50 at `0x00474161`. A direct source jump to 50's
advance also changes the full graph. With both incoming cases, it
merges the distinct switch entries for 50 and 52 and routes 53 and 54
to 51.

The incoming list at the shared return label holds the unconditional
exits from 52, 51, 50, the detached clamp, 53 and 54 in that order among
the six traced copies. The conditional exits that skip the action reset
also appear on the list and are skipped by the scan at `0x10B3075B`.
At `0x10B30784`, VC8 offers 52 as the retained copy. The comparison
returns zero for 51, 50 and the detached clamp. It accepts 53 and 54
and removes their copies at `0x10B30CE6`, before 50 gets a turn as the
retained copy. The headless trace reproduces the complete relocated
`copied-advance-break` scratch object.

In the direct-jump control, folding the rounded speed assignment into
52's comparison keeps the three switch entries distinct. The 134-byte
spans in 51 and 52 still match. VC8 shortens 50 to 49 bytes and moves
its publication and advance into 52, which again owns the four jumps
from 53 and 54.

### A common switch exit restores 53 and 54

The early layout at `0x10B26CA8` and `0x10B26CAE` preserves two branch
lists. Actions 51 and 52 use the function return, while 50, 53, 54 and
the detached clamp use the switch exit. By `0x10C065F8`, the lowered
branches have one list. The two direct returns come first among these
actions, in the order 52 then 51. Changing only 51 to `break` leaves 52
as the winner. Changing only 52 gives the tail to 51. Changing both to
`break` gives it to 50. Using `return` for all the copies merges the
distinct switch entries of 50, 51 and 52.

The selected source keeps ordinary frame-advance statements in 53 and
54 and uses the switch exit in all six copies. In the lowered return
list, 50 now precedes the detached clamp, 51, 52, 53 and 54. Hardware
breakpoints at `0x10B30CE6` observe both splices into 50. The four
displacements at `0x00474326`, `0x0047433D`, `0x00474371` and `0x0047437B` lead
to `0x00474161`. These are the only sixteen bytes that change in the
complete 10,801-byte candidate. The 645 bytes from `0x004740FA` through
`0x0047437E` match the target, including the previously differing 243
bytes of 53 and 54. The owner diagnostic rises from 56 to 58 of 66.
All 396 relocation sites, types and resolved references are preserved.
The frame-advance tests also use the helper's declared `unsigned char`
return type directly. That cleanup alone reproduces the previous candidate.

### Rounded assignments restore 55 and 56

In the target, the speed guard leaves `FLDZ` live on both edges of each
case. The false edge enters `0x00474139` with only zero on the x87 stack.
The true edge stores and reloads the rounded float and enters `0x00474122`
with the adjusted speed above zero. Both paths consume the zero in 50.
The detached clamp in the rebuild carries that zero too, then loads
another one for `FCOMPP`.

Giving 55 and 56 their own rounded assignment inside the comparison and
their own switch exit restores both branch destinations in each case.
Splitting the assignment and test into separate statements can merge the
spill and reload into the shared tail, shortening both spans to 41 bytes.
The selected spelling preserves both 49-byte spans and changes only four
branch displacements in the 10,801-byte candidate. The contiguous target
range `0x004740FA` through `0x004743E0` now matches all 743 bytes. The owner
diagnostic rises from 58 to 60 of 66 without losing a span.

Giving 159–162 the same local clamp and switch exits emits `FCOMP ST(1)`
and the target's two float roundings. Each copy survives in its own
146-byte span. In this full duplication control, 55/56 and the action-2
group 67/163–166 all keep their clamp and frame-advance calls through
x87 lowering. At `0x10B30A1F` the late matcher counts twelve equivalent IR
instructions for 50 with 55/56 and for 62 with 67/163–166. It accepts all
seven pairs. The same comparator trace sees no pair between 50 and
159–162. Moving the float temporaries to function scope or using a
compound update preserves the duplicated result.

### Action 50 must merge before action 62

All of these exits initially enter the same late return list. In the
full duplication control, 62 reaches `0x10B30766` while the original
return edges of 159–166 still belong to that list. At `0x10BF2CD0`, the
four edges from 159–162 are unlinked during splices whose retained branch
belongs to 62. A separate snapshot at 50's turn finds all four already
absent. The emitted 159–162 copies still contain their own clamp and
publication. The shorter shared return consumes the edge the longer
action-0 merge needed.

Keep the local rounded assignments and give 50 the direct return and
62 the switch exit. Changing only 50's exit reproduces the duplicated
result. With both changes, the breakpoint first observes the splices
of 159–162 into 50. A later round shares the intermediate suffix with
55 before final branch cleanup. The native object restores all four
61-byte spans in 159–162, the six clamp paths into 50 and the existing
action-2 paths through 62.
Changing 62's assignment to a separate local in this arrangement loses
the original rounding spill sites in some of the action-2 callers.
The selected source uses the original rounded assignment for 62.

## Selector lowering after block placement

Both the selected split switch and the flat switch with action 690
in its case list use `0x2A6` with positive 50 and 691 in the IR read at
`0x10C064F9`. The original nodes still hold those operands after block
placement at `0x10B26CAE`. The split build keeps the operation nodes
through expression lowering. At `0x10C0B291` VC8 changes them to `0x12`
and passes the negated immediates to the operand builder. The writes at
`0x10C28BB7` select `0x2D`, which is encoded as `ADD` with those same
immediates.

In the flat build, at `0x10BB2C43` each of the two expressions has a
single remaining operand, the negative constant. VC8 returns it and
releases the old operation through `0x10BB6A80`.

At `0x10C0B1C5`, both builds present kind-1 operands without pending
definitions. In the split build, the source and destination refer to
different symbols at operand offset `+0x18`. The comparison at
`0x10C0B1FE` sends both operations to the `ADD` fallback. In the flat
build, each new operation uses the same symbol on both sides. The same
check accepts it, and `0x10C0B24D` negates the constant and selects
`0x32` for the final `SUB`. Both builds eventually allocate EAX for the
operation. The encoding choice has already been made by then.

The traced objects reproduce the complete ordinary builds. Subtracting
the base in place before each split switch, reading the field as the
switch operand, and using separate branch locals all reproduce the
selected 10,725-byte candidate. Giving both split switches a shared
normalized index puts two `LEA` instructions ahead of the original
conditional branches and changes the physical layout.

The original flat control places the shared 54/690 entry near the high
dispatcher. Giving 54 the direct return and 690 its own switch exit
keeps both `SUB` instructions and moves their joint entry back among the
low cases, between 53 and 55. This control has 48 low destinations.
It aliases 51/52 and 62/63/64 and places the common return at the end
of the high cases. A direct return in 690 instead separates 62/63/64
and moves the joint pivot back near the high dispatcher. Moving the
lexical `default` label in the early-pivot trial preserves its complete
output. A source change needs the in-place operand identities at
`0x10C0B1FE` and the physical case entries of the selected build.

## Distinct entries in the single switch

In the flat control with a direct return in 54, the calls at the
entries of 51, 52 and 62–64 survive through x87 lowering at
`0x10C077B1`. The late splice at `0x10B30CE6` releases the original
entry calls of 51, 63, 64 and 690. Making 690 the direct return instead
reverses the 54/690 pairing. In that build the late comparator finds
eight equivalent instructions in each of the 62/63/64 pairs and leaves
their entries distinct.

Branching from `default` to the return in 75 restores all 51 low slots.
With direct returns in both 54 and 690 and the switch exit in 50, the
shared landing entry is back at `0x00474375` and the common return at
`0x00474B91`. The already matching 50–67 cases survive this change.
In the exact build, the trace after `0x10C077B6` still shows the
separate entries of 51, 52 and 62–64. The entry for 54 survives and
the duplicate landing in 690 is released.

Using the switch exit for the landed path in 71, the two transitions
in 74 and the rebound in 76 restores the landing and sequence owners.
The same exit choice in 145 and 158 puts their shared tails back in the
original cases. The remaining difference is one byte in 790's branch
displacement. Giving 140 the switch exit sends the branch to
`0x00475440` inside 140, matching the last byte.

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
`scripts/repo-python scripts/build.py --unit gpt-web-fighter-common-action-state --compare --json`
reports zero differences after all 393 relocations. The complete
10,725-byte envelope includes the one-byte alignment at `0x004768AB`.
The exact ledger records 10,219 callable bytes. The owner diagnostic
reports one extra trailing NOP in candidate action 799 because it ends
the candidate span at the first table. The complete byte comparison
verifies that NOP as the metadata alignment on both sides.

The focused build and owner commands are in the
[giant root review](GIANT_ROOT_REVIEW_2026_11_23.md#reproduce-the-selected-baselines).
The private driver and retained trace inputs are under `build/common-vc8/`.
