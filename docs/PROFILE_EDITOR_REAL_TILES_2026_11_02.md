# Profile editor shared tile owner, 2026-11-02

## Evidence and correction

Pinned Japanese v1.06a target SHA-256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

ProfileEditor168 at CProfileMenu +0x3B0 now uses the existing actual global CTile
at member offsets 0x0C and 0xB0 in ProfileMenu.hpp. ProfileEditorConstructor.cpp
includes that shared owner instead of redeclaring it and defining a separate,
incorrect eight-slot th105::CTile. The target CTile table at 0x6C0718 has four
inherited IColor slots, not eight. Its original +4 initialization is represented
by the shared CSpriteBase handle value, not a special color-base surrogate.

Full constructor 0x428000 remains 33 exact bytes, SHA-256
daa87ab1e566f82acb8b20e4618da167bbaac771ad11987509de89a22a9992d1.
The two member publications use a single actual CTile table relocation. All
247 unique RTTI bytes and the complete four-slot table match the target.
The obsolete namespace-table binding was removed from the constructor unit.
No compilation flags, fields, method behavior, explicit vptr stores or barriers
were added. ProfileEditor168 remains an inferred physical owner name, not a
claim of independently recovered nominal RTTI for that nonpolymorphic owner.

## Validation

Fresh before/after controls preserve five complete editor bodies: constructor
33, destructor 15, initialize 108, shutdown 32 and read_profile_name 42 bytes.
The actual quoted-include closure contains 21 units. All 42 accepted roots in
19 units rebuilt and compared exact, including the containing ProfileMenu ctor,
menu states and lifecycle consumers.

Six other roots in five units retain fresh HEAD hashes: ProfileMenu scalar
cleanup 30, data helper 45, data writer 785, music scalar cleanup 30, profile
base cleanup 28, and deck renderer 2521. Existing mismatches remain open; no
support-body or prefix bytes were added to authored exact credit.

Default CI passed all 962 tests (91.330 seconds), tracking, generated progress and
whitespace checks. Both working-tree and staged diff checks passed.

Totals unchanged: 1427 exact / 443604 bytes, 1637 source-present, 1656 authored,
1826 mapped, 2074 excluded, 297 review and 813 units.
