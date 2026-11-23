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

## Action 811 sequence-specific fade reconstruction

The 811 handler's sequence-3 and sequence-4 channel/alpha fade paths are
separate in the target. The source previously combined them under one
`sequence == 3 || sequence == 4` condition, allowing VC8 to share one block.
The source now keeps the two branches separate and in target order. In the
focused object, action 811 grows from 1,288 to 1,328 bytes; action 804's
reconstructed extent also grows from 1,093 to 1,111 bytes after removing the
shared bounded-projectile tail label. The neighboring action 812 remains
1,376/1,376 bytes by extent.

The root is still not exact. The current focused owner audit totals 45,084
candidate callable bytes against 46,138 target bytes. Action 811 remains
179 bytes short because VC8 reuses the action-804 bounds/frame-advance tail
at the candidate's `0x496FC9` destination, while the target emits a separate
811 tail at `0x497D11`. This is a real control-flow/layout difference, not
missing action-selector entries or padding. The next source work is to
recover the target's distinct live-register lifetimes around the 811 tail
and continue with the larger 900/869/901 action families.

## Action 900 retirement dispatch reconstruction

Action 900's three sequence-0/1 retirement cases now converge at one local
C++ spawn site, with the packet and word count selected by the sequence
switch. This replaces three repeated spawn/epilogue call sites while keeping
the actual packet construction and normal movement path in the case body.
The focused owner extent is now 1,217 bytes against 1,229 target bytes
(previously 1,103 bytes with the function-wide retirement label). The
remaining 12-byte deficit is not padding: the target branches into the
shared emitter/epilogue body placed with the earlier 822 family, whereas
this compiler currently keeps the local call/return in 900. The next boundary
experiment moves the shared natural C++ label toward its 822 owner, then
rechecks the adjacent 869/900/901/902 owners.

## Action 900 retirement dispatch reconstruction

Action 900's sequence-0 dead/complete and sequence-1 dead exits now select a
packet and word count locally, then flow through one natural
`spawn_unparented_related_object` call and the ordinary retirement return.
This replaces the function-wide generic `emit_retiring_world` path for this
handler. The focused owner grows from 1,103 to 1,217 bytes against the
1,229-byte target (12 bytes short); the 66-byte `0x004963A0` helper remains
exact. The owner audit now places action 900 within 12 bytes by extent,
without padding or instruction overrides.

The remaining action-900 differences include the target's shared spawn-call
tail at `0x00499DF8` (entered from action 900 and owned physically by the
preceding action-822 region), plus stack-slot and register-order differences
in the packet preparation. The focused root still has 45,212 candidate
callable bytes against 46,138 target bytes and is not exact. Continue with
the 869/901/902 large handlers and the shared action-822 spawn tail.

## Action 869 owner-retirement reconstruction

Action 869's two sequence-0 owner exits now retain their packet pointer and
word count in the handler and use one natural spawn/retire call site after
the sequence switch. This removes the function-wide `emit_retiring_world`
path from this handler. The focused owner grows from 1,636 to 1,676 bytes
against the 1,736-byte target (60 bytes short). Action 900 remains at
1,217/1,229 bytes after its analogous sequence-specific retirement
reconstruction. The root's candidate callable bytes are now 45,292/46,138;
all changes remain ordinary C++ and the root is still nonexact.

The remaining 869 differences are primarily register lifetimes and x87
operand/stack ordering in the two orbit-position paths, plus the target's
shared spawn tail at `0x00499DF6`. Continue with the 901/902 large handlers
and the shared tail ownership around action 822.
