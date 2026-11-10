# Actual shared CGage owner, 2026-11-02

Original Japanese v1.06a target SHA-256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

## Source

New ui/Gage.hpp declares actual global CGage deriving from existing CSprite,
CSpriteBase and IColor. Its A4 extent, UV spans at94/98, mode at9C and owned
value pointer atA0 are retained. The existing float-returning GageValueView
interface moves unchanged into this header. Its nominal name remains a view.
The existing release policy is ordinary conditional operator delete, not a
virtual deletion. GageLifetime.cpp supplies the existing constructor and outer
design lifetime; GageRender.cpp defines actual CGage::render without changing
its arithmetic or strict-FP profile.

GageDesignRender.cpp uses actual CGage and CSprite members, and actual IColor
instead of another four-slot interface. Separate outer design owner views are
not unified here. Removed declarations include the payload-only lifetime
sprite, manual-vptr render gauge and duplicate design sprite/base/vertex types.
No storage padding, dependencies, barriers, ABI or register constraints added.

## Native type evidence

The entire CGage RTTI graph contains 329 unique bytes. It matches the target's
CGage -> CSprite -> CSpriteBase -> IColor nonvirtual zero-offset hierarchy.
Table 0x6D6A38 has nine slots: 40AD60, 40AC50, 40AC70, 40AC90, 406A90, 406A60,
4070C0, 41B3F0, 406BE0. All source slot roles and the full table extent match.
Slot8 uses the inherited interface spelling render_fvf4142, but its native
implementation is physically shared with CSprite::render at406BE0. It remains
a declaration only: neither a new implementation nor unique original method
spelling is asserted. Native sharing is not an exclusive nominal identity.

## Comparisons

Fresh before/after controls preserve the complete scalar bodies 56 and64 bytes,
three color forwarders of11 bytes, design render60/68 and sprite scale19.
All six accepted roots in two units rebuilt exact; the full include closure is
three units. Scoped scalar origin validation passes two roots /120 bytes; only
the symbol spelling changes in its anchor, with no disposition/count change.

CGage render 0x41B3F0 remains 1010 bytes and nonexact. Its full candidate SHA-256
is unchanged: fa2cc075b86578cc4f121c28aa54d9746ee0dd89701a1a821d8701dee80bea6a.
First difference remains +0x190 at0x41B580, the previously documented pair of
multiplication load-order instructions. No new attempt to force that schedule
was made. Exact design callers do not make the indirect renderer exact.
Constructor bytes, full-program linkage and unresolved slot bodies receive no
new acceptance. No authored exact bytes are added by the type graph proof.

Final default CI passed 962 tests (101.468 seconds), tracking, generated progress
and whitespace checks. Both working-tree and staged diff checks passed.

Totals stay 1427 exact /443604 bytes, 1637 source-present, 1656 authored,
1826 mapped, 2074 excluded, 297 review and813 units.
