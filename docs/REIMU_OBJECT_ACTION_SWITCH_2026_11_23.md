# ReimuObject action-state switch and remote ownership — 2026-11-23

Target: Japanese TH10.5 1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.

## One authored root, three physical code chunks

The primary ReimuObject vtable's `+0x28` slot enters `0x00496540`. Its
reviewed ownership remains one authored function, not a second function at
the remote chunk:

- Main extent: `0x00496540..0x004A00EC`, 39,853 bytes, including one
  separately excluded seven-byte alignment NOP
- Remote extent: `0x004A00F0..0x004A1979`, 6,282 bytes
- Reviewed owned total: 46,128 bytes
- Switch metadata starts after the callable at `0x004A197C`

The final remote chunk contains the tail action families (including 908,
951, 980, 998 and 999) and the default owner. The function-byte-ownership
record retains `remote_exact = false`; no extra source or exact credit is
implied by this boundary record.

## Top-level action selector recovered

The target has a 200-byte selector map at `0x004A1A24` and a 42-entry
32-bit destination table at `0x004A197C`. The current C++ switch in
`ReimuObjectActionStateStaging.cpp` emits the same 200 selector bytes
(200/200) in its COFF `.text` section at offset `0xAFC4`; its 42-entry
address table is represented by 42 `IMAGE_REL_I386_DIR32` COFF relocations
beginning at `.text` offset `0xAF1C`. Thus all 200 actions select the same
42 handler groups as the target. This closes the top-level case grouping, including the remote
handler groups, without inventing missing cases or padding.

The source still does not match the complete root. The focused
`gpt-web-reimu-object-action-state` comparison remains nonexact at the entry
branch (`0x0049655F`, offset `+0x1F` after the dispatch bound). The candidate
COFF `.text` section tail is 45,684 bytes against the 46,138-byte target
extent (444 bytes short of the 46,128 reviewed owned bytes, with 10 target
bytes separately excluded). The
remaining work is physical handler order, instruction/lifetime coupling,
shared tails, and the exact remote body layout—not the 200-entry selector
map. The exact 66-byte `0x004963A0` counter helper remains independently
exact.

## Focused reproduction

```sh
export DISPLAY= WAYLAND_DISPLAY=
scripts/repo-python scripts/build.py --unit gpt-web-reimu-object-action-state --compare --json
```

Do not treat this scoped switch-map result as whole-root exactness. The
separate 81,550-byte Fighter root at `0x00478FA0` is a different function
and a different vtable ownership boundary.
