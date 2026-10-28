# InfoEffectObject visual methods660730 /660780

Canonical exact80/80 transform and266/266 action initialization, adding346
authored bytes. The initializer's entire576-byte section, including two-byte
alignment,11-entry table and264-byte index map, also matches unmasked.
Receipt: build/frontier-660730-20261028/late-alpha-group.json.
Full-payload receipt: full-initializer.json in the same directory.

Hashes:
- transform:6323811da1d936a087846871ced6b6c498656453f923404cb5f4e2b4c039d2b7
- initializer:a6f44b53704393d1aa8e06c6ae6ea75ec5832005cdeaeff14c69abf951b689db
- full initializer:72c841b08b5c50b7fec3c72ad900341cc7f52c010a0d590585dc794b537fc2a3

Current InfoEffectObject RTTI table6C37EC owns slot34 at6C3820 (660730) and
slot3C at6C3828 (660780); the already-pinned COL6D98B4/type6E7C38 names the
class. Transform closes25 instructions. Explicitly following all11 native
jump-table destinations closes all63 initializer instructions /266 code bytes.
The generic boundary audit alone cannot resolve the initializer's indirect jump;
initializer-cfg.json records the complete table-aware traversal.

Transform first applies the common sprite transform435360, then translates by
(0, (1-cosine(3*InfoManager.transition494))*200*factor170, 0). A real float shift
local captures the target's rounding before argument construction. Directly
embedding the expression hoists the zero argument and gives79 bytes; the local
recovers80 naturally without a floating-point mode override.

Initialization preserves signed-short action ranges: >=900 factor0, >=100
factor-1, otherwise action<30 then >=10 factor0, else factor1. It sets absolute
positioning134 and applies independently enumerated scale/alpha/pivot/latch
policies. Scale assignments publish X before Y. The alpha-only30/31/270/273
case family belongs after the scale/latch families; placing it early moved the
shared default return and selected a short range branch. Natural source case
order recovers the complete native table and code, not just similar semantics.
Action274 is not in this initializer table, despite being handled by update.

The source reuses actual CEffectSprite storage, field-width/offset assertions,
and existing trig/transform interfaces. No new shared layout or compiler-profile
change. Metadata is compared but not counted as authored bytes. Pending update
65CB40 remains nonexact; these independent virtuals do not promote it.
