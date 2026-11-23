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
| action 812 | 1,294 | 1,376 | -82 bytes |
| action 817 | 3,027 | 3,066 | -39 bytes; 83 diff groups |
| action 822 | 1,888 | 1,955 | -67 bytes |
| action 869 | 1,691 | 1,736 | -45 bytes |
| action 900 | 1,207 | 1,229 | -22 bytes |
| action 901 | 2,247 | 2,324 | -77 bytes |
| action 902 | 2,998 | 2,998 | exact owner extent |
| action 903 | 1,403 | 1,397 | +6 bytes |
| action 908 | 3,789 | 3,794 | -5 bytes |
| action 951 | 575 | 547 | +28 bytes; 2 diff groups |

Action 811 keeps sequence-3 and sequence-4 channel/alpha fades as separate
branches, matching the target's two control-flow paths rather than combining
them under one `sequence == 3 || sequence == 4` condition. Its final pure
state-field test is ordered sequence-first so Clang does not tail-merge the
811 epilogue into action 804. The current owner is 1,509/1,507 bytes with 38
instruction-difference groups; the condition order and final two-byte extent
are still not exact.

Action 900's three terminal sequence-0/1 branches now construct and emit
their packets in the owning branches through one case-local emitter pointer.
The handler is 1,207/1,229 bytes with 39 owner-difference groups. Clang folds
the three calls to one candidate call tail at `0x00499CF8`; the target enters
its shared tails at `0x00499DF6` and `0x00499DF8`. This is a source-level
shared-call reconstruction, not yet the same physical boundary.

Action 901's sequence-1 burst paths converge on one direct C++ spawn call
inside the handler. The three-word packet is represented as three floats,
not a four-float zero-initialized array when only three words are passed.
Its owner is 2,247/2,324 bytes; the remaining differences are concentrated
in VC8 register lifetimes, loop control, and x87 packet preparation.

The dispatcher-wide `retiring_action`, `retiring_packet`, `retiring_words`,
and `emit_retiring_world` path have been removed. Actions 822, 902, and 908
issue packet-specific spawn/decrement/return calls in their owning C++
branches. Their current extents are 1,888/1,955, 2,998/2,998, and 3,789/3,794
respectively. Action 903 remains 1,403/1,397 with 26 instruction-difference
groups after moving its two terminal packet calls into the health/burst
branches. Packet arrays for 822, 869, 900, 902, 903, and 908 are scoped to
their owning cases, allowing the compiler to reuse stack storage.

## Current root status and next work

The latest focused owner audit reports a 46,138-byte target callable extent,
45,576 candidate main bytes, a 46,444-byte candidate section tail, and 1,114
instruction-difference groups. The candidate main remains 562 bytes short and
the whole root is nonexact: the first raw-byte mismatch is still
`0x0049655F` (offset `+0x1F`, target byte `0xF8`, candidate byte `0xC5`).
Action 902 has an exact 2,998-byte owner extent; action 811 is +2 bytes and
action 908 is -5 bytes. Action 951 is 575/547 bytes with only two
instruction-difference groups; its remaining extent excess is the shared
advance tail being physically owned by the candidate's 951 region instead of
target action 807. The largest remaining deficits include 812, 816, 817, 821,
822, 869, 900, 901, 905, and 906. Continue recovering their shared-tail,
register, and x87 lifetimes together with the remote owner boundary. Do not
substitute a full cold replay for focused changed-owner builds.

The exact 66-byte helper at `0x004963A0` remains independently exact.

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
812 1,294/1,376, 817 3,027/3,066, 821 1,083/1,119, 822 1,888/1,955,
869 1,691/1,736, 900 1,207/1,229, 901 2,247/2,324, 902 2,998/2,998,
903 1,403/1,397, 908 3,789/3,794, and 951 575/547. The complete root remains
nonexact. The root entry branch at `0x0049655F` is still the first raw-byte
mismatch. These results are focused owner evidence only, not a cold replay.

Action 901's two sequence-1 terminal burst branches now each own their
packet-specific spawn and retirement directly. This removes the extra local
`emit_901_burst_tail` join and reduces action-901 instruction-difference
groups from 75 to 70 while preserving the three-word packet semantics.


## Action 817 register lifetime ordering

The action-817 local register declarations are now ordered `one` then `zero`.
This source-level lifetime ordering changes Clang's allocation across the
large switch: the focused root audit drops from 1,166 to 1,127 instruction-
difference groups, with candidate main bytes moving from 45,492 to 45,488.
Action 817 changes from 3,029 to 3,027 bytes, action 901 from 2,248 to 2,247,
and action 908 from 3,793 to 3,789. The target still begins the owner with
`xor ebx, ebx; mov edi, 1`, while the candidate retains a different register
assignment, so this is a measurable code-generation improvement rather than
an exact register-lifetime match.

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
12 to 2 instruction-difference groups. The current extent is 575/547 bytes
(+28): the remaining two groups are branch destinations to the shared advance
tail. The target tail is at `0x00497191` after action 807; Clang places the
same advance/retire sequence at `0x004A1505` inside the candidate action-951
owner. The focused root audit now reports 1,114 instruction-difference groups,
down from 1,115 in the preceding case-local-loop checkpoint, while candidate
main code grows from 45,468 to 45,576 bytes. This is a local control-flow
improvement with an open physical ownership boundary, not a whole-root
exactness claim.


## Action 817 collision-burst loop and register scopes

The sequence-0 and sequence-9 collision bursts now use natural post-decrement
`do/while` loops for their 14 particle emissions. Their `one` count is scoped
to the two manager-spawn branches; the repeated particle calls and sequence-3/
sequence-4 tests use literal one values. This removes the shared count from the
loop lifetime and reduces the focused owner audit to 82 instruction-difference
groups at 3,027/3,066 bytes. The target still keeps zero in `EBX` and one in
`EDI`, whereas the candidate uses a different register lifetime and retains
`sub edi, ebx` in the loop. That mismatch remains a source-level register
allocation problem, not a reason to add assembly or padding.
