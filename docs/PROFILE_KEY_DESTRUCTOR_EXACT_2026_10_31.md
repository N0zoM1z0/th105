# Profile key configuration destructor: complete188-byte exact match

Target: original Japanese TH105 v1.06a, SHA-256
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

The complete CProfileKeyConfig normal destructor44B9D0 now compares188/188
canonically. The former exact-sized candidate's first mismatch at+0x85 was
a member-destruction scheduling difference, not an acceptable near match.

The application body remains unchanged: release handles3C andE4, invoke the
design08's actual virtual cleanup, then let member and Menu base destruction
run. The two A4 tiles now have the ordinary polymorphic CNumberTileLifetime
rather than manually represented vptr stores. This naturally reproduces the
native ordering without volatile fields, fake aliasing, assembly or constraints.

The matching character-selection submenu now also uses the real94-byte
polymorphic sprite lifetime, preserving its164-byte normal destructor exactly.
Both existing30-byte scalar wrappers remain exact without new credit.

## Shared real source and bounded changes

CNumberLifetime.hpp now provides the one common UiSpriteLifetime94 declaration,
alongside the independently exact-backed four-byte IColor/tile/number lifetimes.
Connect-menu, select-scene and profile-submenu lifetime views share it instead
of duplicating their sprite declarations. No stored field offset changes.

ProfileSubmenuLifetime.hpp is a destructor-facing view of the existing288/330
layouts. Constructor/render/update headers remain unchanged. The existing
ProfileSubmenuLifetime.cpp supplies the same application destructor bodies
against the actual polymorphic members.

All twelve affected public whole-function comparisons pass:

- New key configuration destructor188.
- Old profile character destructor164 and both30-byte scalar wrappers.
- Old CSelect destructor845 and connect-menu destructor315.
- Old CNumber destructor40, three11-byte color forwarders, scalar60 and
  design-number scalar61.

Thus eleven old functions remain exact, with no helper or duplicate credit. This is
focused replay, not a cold whole build.

Only one new188-byte authored match is added:1565 functions /446423 bytes.
Source1761/authored1781/mapped1788, excluded1658/review588 and units753 remain
unchanged. The old source-only key-destructor origin rule is replaced by the
canonical-exact-authored evidence.
