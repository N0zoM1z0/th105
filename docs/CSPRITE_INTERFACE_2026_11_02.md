# Actual CSprite interface and rendering ownership

The global CSprite declaration now models all nine native virtual slots and
its five observed float fields, rather than an opaque20-byte tail. Three
existing complete render definitions now belong directly to CSprite, not an
unrelated raw-vptr render view or a base-only rectangle view. No operation,
helper boundary, float setting, vptr write or artificial storage is added.
This improves source ownership; it does not solve the remaining scheduler gaps.

## Independent native evidence

The RTTI-owned table6C0668 has these nine slots:40AE80,40AC50,40AC70,40AC90,
406A90,406A60,4070C0,406BE0,406E50. The next bytes are literal string data,
not a tenth slot. The actual COFF table has its four-byte COL prefix and36
bytes of method pointers. Every source relocation, zero addend, native slot
and the actual deleting weak fallback are checked in csprite_lifetime_origins.
The complete273-unique-byte RTTI graph remains unchanged.

Native texture setup406A90 converts signed width/height and pivots with FILD
from four input dwords, stores them at78/7C/80/84, and writes1.0/1.0/0.0 to
88/8C/90. The two complete610-byte renderers independently consume these same
pivot/scale/angle cells. The seven-argument source declaration therefore uses
an unsigned handle and six signed ints; the five-argument wrapper forwards
rectangle values to that method. Field offsets and0x94 extent are compile-time
asserted. These observations establish physical roles, not unique original
source names or proof that all method implementations match.

## Whole focused results

- Natural ctor40ADA0/16 and cleanup40AD50/7 remain canonical.
- Network constructor411/packet8, destructor259/scalar30/reset175 remain exact;
  complete constructor EH197/meta116 and destructor EH169/meta100 also pass.
- The two real rendering methods remain610-byte nonexact candidates, first
  difference+541. Their entire canonical candidate hashes equal the previous
  selected raw-view source:5de28d71b63d5f182f1dcd5d7053a6fb50248a99c71949ce3a53a2ec20e62cdc
  and985ab2bd4e681b8a490a9875ffda86c57364a39348b42c00cdeb7103b80a6e65.
- Rectangle4070C0 remains153/native153, first+16, canonical candidate hash
  2fdc67bed5910008d2d927da51444e6aed2d49df307fb9853063e1b8fa331a1c.
- A reproducible candidate unit now owns the two primary render comparisons;
  neither receives matching credit. Ordinary source/ABI metadata is updated.

The actual quoted-include closure is126 units. All101 units containing244
accepted authored roots were freshly rebuilt serially and all244 remain exact.
This is a bounded affected-header replay, not a whole-corpus cold rebuild.
The CSprite, implicit CSpriteEx, packet and record-cleanup source hashes were
renewed only after the whole affected proofs. All four focused guards pass.
The existing network scalar30 receipt is refreshed separately.

Seven new tests cover the whole table, slot order, source relocation roles,
zero addends and signed rectangle declaration. The actual source/RTTI/array
proof rejects all410 distinct single-byte mutations. Overlap with older
mutation scopes is not new code coverage. Exact table slots do not grant
exactness to the pending rendering/texture implementations.

No authored count or byte gain:1429 /443911, source1634, authored1653,
excluded2072, review302, mapped1821. Units increase808 to809 solely to retain
both complete renderer comparisons. Other legacy UiSprite94 call views and
unselected type declarations remain separate future source work; this is not
a claim that every sprite facade in the repository has been removed.

Reproduce with scripts/repo-python, CPU0/nice10: csprite_lifetime_origins.py,
sprite_default_origins.py, the two implicit-lifetime guards, both network EH
audits, build.py --unit exact-first-sprite-primary-render --compare --json,
and the analogous rectangle unit. The renderer comparisons intentionally
report mismatches.
