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

| Owner | Candidate | Target | Remaining |
|---|---:|---:|---:|
| action 802 | 31 | 31 | exact owner extent |
| action 811 | 1,465 | 1,507 | 42 bytes |
| action 822 | 1,879 | 1,955 | 76 bytes |
| action 869 | 1,675 | 1,736 | 61 bytes |
| action 900 | 1,213 | 1,229 | 16 bytes |
| action 901 | 2,255 | 2,324 | 69 bytes |
| action 902 | 2,972 | 2,998 | 26 bytes |
| action 903 | 1,390 | 1,397 | 7 bytes |
| action 908 | 3,786 | 3,794 | 8 bytes |

Action 811 now keeps sequence-3 and sequence-4 channel/alpha fades as separate
branches, matching the target's two control-flow paths rather than combining
them under one `sequence == 3 || sequence == 4` condition.

Action 900's sequence-0/1 retirement exits select their own packet and word
count, then converge on one local `spawn_unparented_related_object` call and
retirement return. The handler is 1,213/1,229 bytes by owner extent. The
shared `emit_retiring_world` tail now expresses the target's natural
spawn/decrement/return sequence directly instead of routing through a second
`retire` label.

Action 901's sequence-1 burst paths converge on one direct C++ spawn call
inside the handler. The three-word packet is represented as three floats,
not a four-float zero-initialized array when only three words are passed.
Its owner is 2,255/2,324 bytes; the remaining differences are concentrated
in VC8 register lifetimes, loop control, and x87 packet preparation.

Action-owned packets for 822, 869, 900, 902, 903, and 908 now have
case-local storage lifetimes. The 903 body is 1,390/1,397 bytes, and the
902/908 bodies are 2,972/2,998 and 3,786/3,794 bytes respectively. These
changes alter several neighboring owners because stack-slot reuse and
physical handler order are shared across this large function.

## Current root status and next work

The focused owner audit reports a 46,138-byte target callable extent, one
exact 31-byte owner (action 802), and a 45,400-byte candidate metadata
boundary; the candidate canonical section tail is 46,268 bytes. The complete
root is still nonexact. Its first entry mismatch remains at `0x0049655F`
(root offset `+0x1F`), and the larger remaining owner deficits include
822, 816, 905, 901, 951, 869, 851, 817, 811, and 821. Continue with the
large 822/869/901/817/816/905 bodies and their shared tail ownership; do not
substitute a full cold replay for focused changed-owner builds.

The exact 66-byte helper at `0x004963A0` remains independently exact.

## Focused reproduction

```sh
export DISPLAY= WAYLAND_DISPLAY=
scripts/repo-python scripts/build.py --unit gpt-web-reimu-object-action-state --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py reimu-object-vslot28 build/match-units/GptWeb_ReimuObjectActionState.obj --unit gpt-web-reimu-object-action-state --json
```

These focused results are not whole-root exactness claims.
