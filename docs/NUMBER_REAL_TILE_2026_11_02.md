# Shared CTile in numeric rendering, 2026-11-02

## Scope and evidence

Target: original Japanese v1.06a, SHA-256
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

CNumberRuntime.hpp now uses actual global CTile at +0x28 and derives from the
actual IColor interface. Its three named color methods replace anonymous slots.
The target CNumber table at 0x6C1B60 contains 0x40AE10, 0x40ADE0, 0x40ADF0 and
0x40AE00. Source and native hierarchy both have two bases with a zero-offset,
nonvirtual IColor base. Outer namespace RTTI identity is not claimed.

CNumberTileTextureOptions.cpp defines CTile::set_texture_options using shared
field names. DesignNumberRender.cpp uses CTile, and its providers include the
existing UiTileRender.cpp rather than a duplicate implementation. Existing
linked preservation roles, compiler settings and FP-environment scope are
unchanged. Historical ledger name CNumberTileA4_set_texture_options remains a
stable address identifier, not a claim that the removed view is the native type.

## Owner control

A tile-only conversion made the MenuConnect constructor 735 bytes instead of
728. Correcting CNumber's IColor base alone did not change this result. Native
0x444190 stores the same CTile table (0x6C0718) at owner offsets 0x64, 0x130 and
0x300. Mixed manual and actual C++ table symbols prevented common-value reuse.
Changing both outer tile members to actual CTile naturally restored all 728
bytes, including the single table relocation at body offset 0x52. No explicit
vptr write, artificial dependency, register constraint or barrier was added.

The four-slot CTile table and 247 unique RTTI bytes match the target. Shared
physical cleanup addresses do not prove unique nominal class ownership.

## Validation

Actual quoted-include closure: 8 units, with 20 accepted roots in 7 units freshly
rebuilt and compared. Integer render 0x414F10 remains 312 bytes; tile texture
options 0x4098E0 remains 266; linked design-number roots remain 55/63/95/581.
MenuConnect 0x444190 remains 728 bytes, SHA-256
24eabb7746a05f06b724d86aad8273907d616ddad3d4aadd14c989f28d5b360d.

Four additional roots were compared with fresh HEAD controls and retained their
candidate hashes: InfoManager scalar cleanup (30), CNumber initialize (102),
InfoCombo load (427), and ProfileDeck constructor (2132). No new exact credit.
CNumber initialize's old scratch-word mismatch remains closed. CNumberLifetime
is still a separate cleanup view; the runtime scalar body and full linked owner
are not asserted exact.

Default CI ran all 962 tests successfully, but its first aggregate exit rejected a
trailing blank line. That formatting error was removed; the final aggregate gate
passed all 962 tests (90.918 seconds), tracking, generated progress and whitespace
checks. The texture-options unit was rebuilt and again compared exact after that
formatting correction.

Totals unchanged: 1427 exact functions / 443604 bytes, 1637 source-present,
1656 authored, 1826 mapped, 2074 excluded, 297 review, 813 units.
