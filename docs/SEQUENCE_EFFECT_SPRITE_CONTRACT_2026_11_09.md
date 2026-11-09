# Sequence-effect reset uses the real sprite member

The sequence-effect reset at `0x4652B0` now accesses a real `CSprite` at +4
through a shared `FighterSequenceEffectView`. It no longer embeds an unrelated
four-byte color class followed by opaque storage. Its two callers use the
same implemented method instead of separate undefined aliases. The method is
void, matching the existing sprite color interface and the callers' use.

The native Character constructor provides the member identity independently
of the reset body. At `0x462AF0` it loads CSprite table `0x6C0668`; at
`0x462B11` it publishes that table to Character+0x3D4. The table's RTTI records
CSprite, CSpriteBase and IColor with zero base adjustments. Slot +4 points to
`CSpriteBase::set_color` at `0x40AC50`.

Both physical callers of the reset helper pass Character+0x3D0. The helper
loads the vptr at +4, calls its color slot with `0x80FFFFFF`, and returns.
Before that call it clears counters +0x9C/+0xA0, writes -640.0f at +0xA4 and
sets alpha +0xA8 to 0x80. Both callers discard the call's register result.
The former local `int set_color` declaration and returned int did not express
the shared provider's source contract, even though the same call/RET sequence
could compile. No return-dependent behavior is removed from either caller.

The shared declaration remains an accessed prefix, not a recovered complete
Character member class. No view instance is constructed, no lifetime is
changed, and the four bytes at +0x98 remain unknown. Field offsets are checked
at compile time. The implemented reset method has a stable namespace-qualified
symbol rather than an anonymous-namespace identity.

## Validation

The three source consumers remain completely exact:

- Reset/color `0x4652B0`: 50 bytes.
- Sequence finalization `0x45D110`: 154 bytes.
- Indexed sequence window `0x45DEB0`: 446 bytes.

All 170 non-debug COFF sections are unchanged after symbolic relocation
normalization; include order moves an existing small section but does not
change its contents or references. There are no owned EH regions in these
three functions. The real color provider and its two siblings also replay
exact at 19, 30 and 190 bytes. The native caller scan finds exactly the two
source-connected calls, at `0x45D170` and `0x45DFA2`.

Evidence is retained in `build/frontier-sequence-effect-sprite-20261109/`,
including fresh before/after objects, native constructor/RTTI/caller evidence,
all six full body comparisons and `proof.json`. This restores type and provider
consistency without adding authored exact credit or touching source pins.
