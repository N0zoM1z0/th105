# ReimuObject action-state root — 2026-11-23

Target: Japanese TH10.5 1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.

## Authored origin and the actual function boundary

The ReimuObject primary vtable's `+0x28` slot is stored at
`0x006C40CC`; its target bytes are `40 65 49 00`, i.e. the absolute entry
`0x00496540`. The target-SHA-pinned
`config/roster-character-object-vtable-origin-anchors.toml` records this as
ReimuObject's `+0x28` root. The current function-origin census classifies
`0x00496540` as `authored_game / characters / authored / observed` through
`roster-character-object-vtable-authored-106a`. This establishes authored
class ownership, not the original translation-unit name or code exactness.

The target is one multi-chunk function, not a second function beginning at
the remote tail. The target-attested IDA lookup resolves `0x00496540`,
`0x004A00F0`, and `0x004A1970` to `sub_496540` (main IDA size `0x9BAD`).
The reviewed byte-ownership record expresses its physical layout as:

- Main span: `0x00496540..0x004A00EC` (39,853 bytes)
- Main-span exclusion: seven alignment bytes at `0x0049D169..0x0049D16F`
- Remote code chunk: `0x004A00F0..0x004A1979` (6,282 bytes)
- Three-byte gap between the main span and remote chunk
- Reviewed owned total: 46,128 bytes; callable extent ends at `0x004A1979`

The top-level action destination table begins at `0x004A197C`, immediately
after the callable extent. It is switch metadata, not another function body.
The ownership record deliberately keeps `remote_exact = false`; the boundary
review adds no exactness credit. The separate 81,550-byte Fighter root at
`0x00478FA0` is a different function and a different vtable ownership
boundary.

## Top-level action selector

The target has a 200-byte selector map at `0x004A1A24` and a 42-entry
32-bit destination table at `0x004A197C`. The current C++ switch emits the
same 200 selector bytes (200/200) in its COFF `.text` section at offset
`0xAFC4`; its 42-entry address table is represented by 42
`IMAGE_REL_I386_DIR32` COFF relocations beginning at `.text` offset `0xAF1C`.
Thus all 200 action values select the same 42 handler groups, including the
remote action families. This closes the top-level case grouping without
inventing cases, padding, or instruction overrides.

## Primary-vtable origin-boundary coverage

The target-SHA-pinned raw primary-vtable coverage audit reports all configured
class-specific virtual pointers as candidate-ledger starts: Fighter has 15
owners, 360 slots, and 99 unique pointers; Object has 15 owners, 255 slots,
and 59 unique pointers. Both surfaces have zero interior pointers and zero
unledgered pointers. In particular, ReimuObject's `+0x28` slot at
`0x006C40CC` resolves to the ledger start `0x00496540`.

This closes the primary-vtable pointer-coverage boundary, not the ReimuObject
codegen boundary. The three target executable chunks and seven-byte alignment
exclusion remain recorded in `config/function-byte-ownership.toml`, and
`remote_exact = false` remains intentional until the full root and remote
chunk compare exactly. The coverage audit does not promote any byte-exactness
or original source-translation-unit claim.


## Reconstruction progress

The source keeps the large action bodies as natural C++ and is recovering the
original local packet lifetimes, shared exits, register lifetimes, and x87
ordering. Recent focused owner extents (candidate/target) are:

| Owner | Candidate | Target | Difference |
|---|---:|---:|---:|
| action 802 | 33 | 31 | +2 bytes |
| action 807 | 272 | 300 | -28 bytes; shared advance tail is remote in candidate |
| action 811 | 1,509 | 1,507 | +2 bytes; 38 diff groups |
| action 812 | 1,361 | 1,376 | -15 bytes; 28 diff groups |
| action 817 | 3,026 | 3,066 | -40 bytes; 82 diff groups |
| action 822 | 1,886 | 1,955 | -69 bytes; 19 diff groups |
| action 869 | 1,691 | 1,736 | -45 bytes; 48 diff groups |
| action 900 | 1,209 | 1,229 | -20 bytes; 27 diff groups |
| action 901 | 2,239 | 2,324 | -85 bytes; 55 diff groups |
| action 902 | 2,998 | 2,998 | exact owner extent; 39 diff groups |
| action 903 | 1,403 | 1,397 | +6 bytes |
| action 908 | 3,793 | 3,794 | -1 byte; x87 accumulator order exact; 100 diff groups |
| action 951 | 547 | 547 | exact owner extent; 2 diff groups |

Action 811 keeps sequence-3 and sequence-4 channel/alpha fades as separate
branches, matching the target's two control-flow paths rather than combining
them under one `sequence == 3 || sequence == 4` condition. Its final pure
state-field test is ordered sequence-first so Clang does not tail-merge the
811 epilogue into action 804. The current owner is 1,509/1,507 bytes with 38
instruction-difference groups; the condition order and final two-byte extent
are still not exact.

Action 900's three terminal sequence-0/1 branches now construct and emit
their packets in the owning branches through one case-local emitter pointer.
The current handler is 1,209/1,229 bytes with 27 owner-difference groups. Clang folds
the three calls to one candidate call tail at `0x00499CF8`; the target enters
its shared tails at `0x00499DF6` and `0x00499DF8`. This is a source-level
shared-call reconstruction, not yet the same physical boundary.

Action 901's sequence-1 burst paths converge on one direct C++ spawn call
inside the handler. The three-word packet is represented as three floats,
not a four-float zero-initialized array when only three words are passed.
Its owner is 2,239/2,324 bytes with 55 difference groups; the remaining
differences are concentrated in VC8 register lifetimes, loop control, and
x87 packet preparation.

The dispatcher-wide `retiring_action`, `retiring_packet`, `retiring_words`,
and `emit_retiring_world` path have been removed. Actions 822, 902, and 908
issue packet-specific spawn/decrement/return calls in their owning C++
branches. Their current extents are 1,886/1,955, 2,998/2,998, and 3,793/3,794
respectively. Action 903 remains 1,403/1,397 with 26 instruction-difference
groups after moving its two terminal packet calls into the health/burst
branches. Packet arrays for 822, 869, 900, 902, 903, and 908 are scoped to
their owning cases, allowing the compiler to reuse stack storage.

## Current root status and next work

The latest focused owner audit reports a 46,138-byte target callable extent,
45,636 candidate main bytes, a 46,504-byte candidate section tail, and 1,100
instruction-difference groups. The candidate main remains 502 bytes short and
the whole root is nonexact: the first raw-byte mismatch remains at
0x0049655F (offset +0x1F, target byte 0xF8, candidate byte 0x00).
Action 902 has an exact 2,998-byte owner extent; action 811 is +2 bytes,
action 812 is -15 bytes with 28 difference groups, and action 908 is -5 bytes.
Action 951 is now 547/547 bytes with two instruction-difference groups;
its shared advance tail still has a different physical address from target
action 807, despite the exact owner extent. The largest remaining
deficits include 816, 817, 821, 822, 869, 900, 901, 905, and 906. Continue
recovering their shared-tail, register, and x87 lifetimes together with the
remote owner boundary. Do not substitute a full cold replay for focused
changed-owner builds.

The exact 66-byte helper at 0x004963A0 remains independently exact.

## Focused reproduction

```sh
export DISPLAY= WAYLAND_DISPLAY=
scripts/repo-python scripts/build.py --unit gpt-web-reimu-object-action-state --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py reimu-object-vslot28 build/match-units/GptWeb_ReimuObjectActionState.obj --unit gpt-web-reimu-object-action-state --json
```

These focused results are not whole-root exactness claims.


## Action 903 terminal-call ownership

The action-903 health and special-burst terminal paths now issue their
packet-specific `spawn_unparented_related_object` calls directly in the
owning sequence branches, rather than carrying a packet pointer/word count
through a post-switch dispatcher tail. This restores the two distinct
argument-preparation paths visible in the target and reduces the action-903
instruction-difference groups from 36 to 26. Its candidate extent is now
1,403/1,397 bytes (+6), while the whole-root instruction-difference count
falls from 1,204 to 1,190. The root remains nonexact; the health-death branch
still reaches a candidate shared call tail at a different physical address
than the target's `0x00499DF6` tail. No padding or instruction overrides are
used.


## Action 869 branch-local retirement

The two sequence-0 retirement branches now build and emit their own three-word
packets directly in the owning C++ branches. This removes the post-switch
`retiring_packet_869`/`retiring_words_869` handoff and grows the owner from
1,656 to 1,669 bytes while reducing its instruction-difference groups from
57 to 46. The latest root audit is 45,488 candidate main bytes against the
46,138-byte target callable extent, with 1,127 instruction-difference groups.
The target routes both branches to the shared `0x00499DF6` call tail; the
candidate still selects different shared call tails, so this is real semantic
and ownership progress, not an exactness claim. The full root remains
nonexact, and the separate action-901 and action-817 large-body gaps remain.


## Shared advance-and-retire boundary at `0x00497191`

IDA xrefs identify `0x00497191` as a second major shared tail in the same
46,138-byte ReimuObject root. It has 23 incoming code references across
13 owner families: 807, 850, 851, 855, 856, 859, 866, 869, 900, 903, 951,
980 and 998. The tail calls `advance_frame_and_dispatch`, tests the result,
returns without retirement on false, and decrements `state_330` before the
common epilogue on true. It is physically placed immediately after action
807, not at the remote end of the dispatcher.

The C++ `advance_and_retire_on_completion` label has been moved to the
post-807 boundary so those large action families share the same source-level
control-flow owner. This changed the focused audit from 1,192 to 1,132 instruction-difference
groups and moved 902 to an exact 2,998-byte owner extent. Reordering the
`register one` and `register zero` declarations in action 817 then reduced the
root to 1,127 instruction-difference groups and the candidate main to 45,488
bytes. Current focused extents are: 807 272/300, 808 415/410, 811 1,509/1,507,
812 1,361/1,376, 817 3,026/3,066, 821 1,083/1,119, 822 1,886/1,955,
869 1,691/1,736, 900 1,209/1,229, 901 2,239/2,324, 902 2,998/2,998,
903 1,403/1,397, 908 3,793/3,794, and 951 547/547. The complete root remains
nonexact. The root entry branch at `0x0049655F` is still the first raw-byte
mismatch. These results are focused owner evidence only, not a cold replay.

Action 901's two sequence-1 terminal burst branches now each own their
packet-specific spawn and retirement directly. This removes the extra local
`emit_901_burst_tail` join and reduces action-901 instruction-difference
groups from 75 to 70 while preserving the three-word packet semantics.


## Action 817 register lifetime ordering

Action 817 keeps one then zero as root-scoped register locals, while the two
14-particle collision bursts retain literal-one spawn arguments. At the
previous checkpoint this lowered the root to 1,108 difference groups and the
owner to 3,024/3,066 bytes with 80 groups. The subsequent action-822 branch
rewrite changes register allocation and physical layout across the large
switch; current action 817 is 3,026/3,066 bytes with 82 groups and the root is
at 1,100 groups after the action-980/998 remote-order move.
The target still begins the owner with
`xor ebx, ebx; mov edi, 1`, while the candidate emits `mov ebx, 1`;
the particle loop also remains `sub edi, ebx` rather than
`sub edi, 1`. This is a measurable source-level code-generation
experiment, not an exact register-lifetime match.

## Action 900 terminal packet branches

Action 900's three terminal sequence-0/sequence-1 branches now construct and
emit their own packet at the branch that owns the retirement, rather than
carrying a packet pointer and word count through one post-switch call. The
VC8 compiler naturally folds their common call/return tail into a shared
candidate tail. This moves action 900 from 1,185/1,229 to 1,207/1,229 bytes and increases
its owner-local difference groups from 32 to 39. The whole-root audit now
improves from 1,132 to 1,127 instruction-difference groups after keeping the
emitter pointer live across the three retirement branches and reordering the
action-817 register locals; candidate main code grows from 45,456 to 45,488
bytes. The shared candidate
call tail is still physically at a different address (`0x00499CF8`) from the
target's `0x00499DF6`/`0x00499DF8` entries, so action 900 is not exact.

The target has three action-900 branches entering those two target tail
addresses: one jumps to `0x00499DF8`, while two jump to `0x00499DF6`. The
candidate currently folds the three natural C++ calls to one common call
site. This is an explicit next boundary to refine; no padding or instruction
overrides were introduced.


## Action 951 owner-state retirement ordering

Action 951 no longer snapshots the owner's sequence, frame, and action fields
at handler entry. It keeps the owner pointer and reads those fields in the
target's short-circuit order. The two owner-action retirement families
(70–88 plus 181/180/145, and 100–111) remain separate, and each exit resets
the owner flag before returning. This reduces the action-951 owner audit from
12 to 2 instruction-difference groups. The current extent is now exactly
547/547 bytes; the remaining two groups are branch destinations to the shared
advance tail. The target tail is at `0x00497191` after action 807; Clang places the
same advance/retire sequence at `0x004A1505` inside the candidate action-951
owner. The latest focused root audit reports 1,100 instruction-difference groups,
with 45,636 candidate main bytes and 46,504 candidate section-tail bytes.
This is a local control-flow improvement with an open physical ownership boundary, not a whole-root
exactness claim.


## Action 817 collision-burst loop and register scopes

The sequence-0 and sequence-9 collision bursts use natural post-decrement
do/while loops for their 14 particle emissions. The two manager-spawn branches
share the root-scoped one/zero register locals, while the collision-burst
calls pass literal 1 so the one lifetime does not come from those packet
arguments. The current owner is 3,026/3,066 bytes with 82 instruction-
difference groups after the subsequent action-822 layout change. Clang still
chooses EBX for one and reuses it for the loop decrement.

## Action 822 sequence entries and alpha saturation

The sequence-1 alpha saturation uses a natural C++ if/else rather than a
conditional expression. This reproduces the target instruction block exactly:
`cmp al, 0xcd; ja; add al, 0x32; mov [esi+0x113], al; jmp; mov byte [esi+0x113], 0xff`.
The target block is at `0x0049A185..0x0049A1A3`; the candidate block at object
offset `0x3B87..0x3BA5` has the same instruction sequence.

Sequences 2 and 3 are now separate C++ switch entries instead of a
sequence-equality ternary. Sequence 3 uses a mutable float local and compound
addition to recover the target x87 operand order:
`fld [esi+0x11c]; fadd qword [0x6c0e80]`.
The rounded result is then published to both float fields before the shared
alpha/channel fade. The remaining local mismatch is that the candidate
publishes the fields inline, whereas the target's sequence-3 path jumps to the
shared publish tail at `0x0049A1BC`; the temporary also occupies a different
stack slot.

Action 822 is now 1,886/1,955 bytes with 19 instruction-difference groups,
down from 45 groups. The focused root moves from 1,107 to 1,082 groups; the
candidate main and section-tail sizes are 45,640 and 46,508 bytes. The first
root mismatch remains at `0x0049655F`; these are focused local improvements,
not a whole-root match.

## Action 980/998 remote-owner source order

The source switch now places actions 980 and 998 after action 951 and before
999, matching the target's remote-chunk order. Their candidate starts moved
from object offsets `0x6364/0x636e` to `0xaebe/0xaec8`; target starts are
`0xb0d2/0xb0dc`. This moves both owners out of the earlier main
switch body and into the same late code region as the target remote chunk.
Action 980 is exact at 10/10 bytes; action 998 is 345/317 bytes with three
difference groups, mainly because the candidate still owns the shared
advance/retire tail inside its contiguous span. Action 999 starts at
`0xb021` versus target `0xb219`.

This is an origin-boundary/layout improvement, but not a root-match improvement:
the focused root count rises from 1,082 to 1,100 groups, while candidate main
and section-tail sizes move to 45,636 and 46,504 bytes. The remaining 502-byte
main deficit is now the dominant displacement between the late remote owners
and their target positions. No assembly or padding was introduced.

## Action 908 x87 accumulator evaluation order

The sequence-1 accumulator update now snapshots state_374 into a natural C++
local before adding the integer state_366. This forces the target x87 operand
order: load the existing float, load the signed integer with fild, then
faddp and store the result. The candidate emits that four-instruction
sequence exactly. In the latest root build, action 908 is 3,793/3,794 bytes
with 100 instruction-difference groups after the remote-owner source-order
move; remaining differences are concentrated in register assignment
(EBX/EDI), the -1 countdown lifetime, and downstream control-flow layout. The focused root is now 45,636 candidate main bytes,
46,504 candidate section-tail bytes, and 1,100 instruction-difference
groups. This is a verified local code-generation improvement, not a whole-root
exactness claim.

## Action 812 register lifetimes and shared movement tail

Action 812 has an explicit case scope for the three register values visible in
the target handler: five = 5, one = 1, and retire_delta = -1. The source uses
five for the phase-state and modulo-five tests, one for the state-364 increment
and related-object spawn arguments, and retire_delta for state-330 retirement
updates. This recovers the target's EDI=1 and EBP=-1 lifetimes and reduced the
owner from 1,294/1,376 to 1,393/1,376 bytes (+17), with 29 difference groups.

IDA xrefs confirm the target's movement tail at 0x00497F17 has three entries,
from action 812 sequences 0, 1, and 2. The source now routes those three
sequences through one natural C++ move_with_facing_velocity_812 label. The
target's advance/dispatch tail at 0x004982CF is also represented by a shared
advance_812 label, with sequence 3/4 retirement bypassing the movement block.
This reduces the action-812 owner to 1,361/1,376 bytes (-15) and 28
instruction-difference groups. The whole-root audit now reports 1,100 groups after the action-980/998
remote-order move; candidate main code is 45,636 bytes.

The target also keeps five in EBX for the phase-state comparison and modulo
operation; the current compiler still rematerializes the constant at those
sites, so action 812 is not exact. The root remains nonexact and its remote
ownership boundary remains provisional.
