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

## Reconstruction progress

The source keeps the large action bodies as natural C++ and is recovering the
original local packet lifetimes, shared exits, register lifetimes, and x87
ordering. Recent focused owner extents (candidate/target) are:

| Owner | Candidate | Target | Difference |
|---|---:|---:|---:|
| action 802 | 31 | 31 | exact owner extent |
| action 811 | 1,507 | 1,507 | exact owner extent; 18 diff groups |
| action 812 | 1,393 | 1,376 | +17 bytes |
| action 822 | 1,957 | 1,955 | +2 bytes |
| action 869 | 1,669 | 1,736 | -67 bytes |
| action 900 | 1,197 | 1,229 | -32 bytes |
| action 901 | 2,244 | 2,324 | -80 bytes |
| action 902 | 3,019 | 2,998 | +21 bytes |
| action 903 | 1,403 | 1,397 | +6 bytes |
| action 908 | 3,795 | 3,794 | +1 byte |

Action 811 now keeps sequence-3 and sequence-4 channel/alpha fades as separate
branches, matching the target's two control-flow paths rather than combining
them under one `sequence == 3 || sequence == 4` condition. Its final pure
state-field test is ordered sequence-first so Clang does not tail-merge the
811 epilogue into action 804. This restores a distinct 1,507-byte owner; the
owner extent now matches the target, while 18 instruction-difference groups
remain and the condition order itself is not yet byte-identical.

Action 900's sequence-0/1 retirement exits select their own packet and word
count, then converge on one local `spawn_unparented_related_object` call and
retirement return. The handler is currently 1,197/1,229 bytes by owner extent.
Its target-owned shared tail is still not fully recovered after removing the
dispatcher-wide emitter; the remaining 32-byte deficit is being treated as
real C++ control-flow ownership, not a padding target.

Action 901's sequence-1 burst paths converge on one direct C++ spawn call
inside the handler. The three-word packet is represented as three floats,
not a four-float zero-initialized array when only three words are passed.
Its owner is 2,241/2,324 bytes; the remaining differences are concentrated
in VC8 register lifetimes, loop control, and x87 packet preparation.

The dispatcher-wide `retiring_action`, `retiring_packet`, `retiring_words`,
and `emit_retiring_world` path have now been removed. Actions 822, 902, and
908 issue their packet-specific spawn/decrement/return calls in their own
natural C++ branches. This puts action 822 at 1,957/1,955 bytes and action
908 at 3,795/3,794 bytes; action 902 is 3,019/2,998. Action 903 is now 1,403/1,397 after moving its two terminal packet calls
into the health/burst branches; this reduced its instruction-difference groups
from 36 to 26 and the root total from 1,204 to 1,190 at that checkpoint. The improvement is not uniform: 811, 869, 900, and 901 are now
shorter because their target-owned shared tails still need explicit natural
reconstruction. Packet arrays for 822, 869, 900, 902, 903, and 908 are scoped
to their owning cases, allowing the compiler to reuse stack storage.

## Current root status and next work

The focused owner audit reports a 46,138-byte target callable extent,
45,680 candidate main bytes, a 46,548-byte candidate section tail, and 1,191
instruction-difference groups (down from 1,204 before restoring the distinct
811 epilogue). Action 802 remains one exact 31-byte owner, and action 811 now
matches its 1,507-byte owner extent. The complete root is still nonexact: the
root comparison's first mismatch remains at `0x0049655F` (offset `+0x1F`).
Actions 822 and 908 are within two and one bytes by owner extent. Action 869 is now 1,669/1,736 after restoring its two branch-local retirement calls. The larger
remaining deficits include 869/900/901 and 816/817/905/951; continue
recovering their original shared-tail and register lifetimes together with
the remote owner boundary. Do not substitute a full cold replay for focused
changed-owner builds.

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
57 to 46. The current root audit is 45,680 candidate main bytes against the
46,138-byte target callable extent, with 1,191 instruction-difference groups.
The target routes both branches to the shared `0x00499DF6` call tail; the
candidate still selects different shared call tails, so this is real semantic
and ownership progress, not an exactness claim. The full root remains
nonexact, and the separate action-901 and action-817 large-body gaps remain.
