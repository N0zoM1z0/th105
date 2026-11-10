# Actual scene members and corrected lifetime extents, 2026-11-02

Pinned original Japanese v1.06a SHA-256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

## Source corrections

SceneConstructorWave.cpp now uses existing actual CSprite, CEffectSprite and
CTile classes, removing the three local polymorphic substitutes and their
nonpolymorphic four-byte initialization base. The observed initialization is
already represented by CSpriteBase's real four-byte handle value.

SceneLifetimeWave.cpp uses actual CSprite for Loading and LoadingWatch. More
importantly, its Logo model previously placed two CSpriteEx members at 0x08 and
0xF0. The complete exact constructor instead publishes CEffectSprite at 0x08 and
CTile at 0xF0, with its state dword at 0x194. The lifetime now has those actual
members and state, and asserts the complete extent 0x198. The distinction is
proved by the two different native RTTI tables, not just shared cleanup bytes.

Loading's lifetime previously stopped at the end of its deque at 0xB8. Its
observed word timer at 0xB8 is now represented, producing the correct aligned
extent 0xBC. Fresh exact scene-factory comparison independently preserves both
allocation sizes. No timer initialization absent from the target was added.
Other scene owner views remain separate; full-program linkage is not claimed.

## Native evidence

All 15 accepted roots in the two-file include closure remain complete exact.
The unchanged factory root is also freshly compared exact as an allocation
observer. All six scalar wrappers remain exact and pass their scoped origin
validation (181 bytes), with no accounting change.

Complete member RTTI/table proofs pass from the actual constructor unit:
- CSprite root hierarchy: 249 unique bytes and nine virtual slots.
- CEffectSprite root hierarchy: 339 unique bytes and four virtual slots.
- CTile root hierarchy: 247 unique bytes and four virtual slots.
The CSprite figure excludes the separate standalone IColor COL/table prefix
included in earlier 273-byte two-table reports; no bytes were omitted from its
own hierarchy traversal.

Six complete EH/code and metadata pairs are compared, totaling 676 bytes:
Loading ctor/dtor 60+60 each; Logo ctor/dtor 60+60 each; LoadingWatch ctor/dtor
46+52 each. Every handler and unwind action is included. The ordinary deque
cleanup provider is checked as a complete five-byte tail. Logo's actual effect
cleanup call targets 0x421D30, whose full seven-byte body matches the emitted
CEffectSprite destructor. Although 0x40AD50 has identical cleanup bytes, it is
not substituted for this observed call target. No exclusive nominal or ICF
identity is inferred from those equal bodies.

## Rejected independent rendering trial

A separate bounded control replaced the manual sprite dispatch in LoadingSV
and LoadingWatch rendering with actual CSprite and one ordinary nested color
call. Both candidates became 218 bytes versus native 217, first differing at
the entry register save. The original complete exact sources were restored.
No spelling grid, forced register or manual-vptr replacement was introduced.
Their private evidence remains under frontier-loading-real-sprites-20261102;
no render change is included in this checkpoint.

Final CI passed 962 tests (111.422 seconds), tracking, generated progress and
whitespace. The client wait timed out, but the persisted zero exit marker and full
terminal log confirmed success without rerunning the gate. Both diff checks passed.
No target bytes or generated binaries are committed.

Counts unchanged: 1427 exact / 443604 bytes, 1637 source-present, 1656 authored,
1826 mapped, 2074 excluded, 297 review and 813 units.
