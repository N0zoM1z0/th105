# Actual Config menu sprite arrays, 2026-11-02

Pinned original Japanese v1.06a SHA-256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

MenuConfigConstructor.cpp, MenuConfigUpdate.hpp and MenuOverlayWave.cpp now use
actual global CSprite for the two members beginning at0xB8. The existing source
methods call the real virtual interface rather than UiSprite94 manual dispatch.
The constructor and destructor array callback bindings use the actual method
symbols while retaining the same native addresses. No other owner fields,
compiler flags, clamps or runtime branches change. The separate Config owner
views themselves are not unified in this step.

Fresh before/after comparisons preserve all eight accepted roots in two units,
including config render197, destructor179 and update665 callable bytes. The
update section also contains switch data; its 688-byte section extent is not a
new function boundary. Two scalar support roots of30 bytes each are unchanged.
The include closure is only three units.

Constructor0x441520 remains source863 versus native868 with full candidate hash
f2cf2f4027b7b5dde68db19f58b9500d9468e7104fa9f2c2a47994f3dc8c7048.
The old final signed clamp difference remains closed. No prefix or constructor
exactness credit is claimed from these changes.

Both original array setup sites are fully compared: 40 bytes at0x44156B and
29 bytes at0x4414C7. They use count2, stride0x94 and member0xB8, with constructor
callback0x40ADA0 and destructor callback0x40AD50. The actual CSprite callbacks
are complete canonical16/7-byte bodies. The latter has physically shared
cleanup bytes, not an exclusive nominal-class identity. Actual sprite RTTI273
and all nine virtual slots also pass.

The entire constructor EH is87 bytes at0x6B91A0 (handler0x6B91DC); destructor
EH is87 bytes at0x6B9140 (handler0x6B917C). Each complete metadata section is68
bytes, with the unwind table preceding FuncInfo by32 bytes. All310 support bytes
match. These are evidence for cleanup ownership, not new authored exact bytes.

Private evidence is under .analysis/frontier-config-real-sprites-20261102/ and
build/frontier-config-real-sprites-20261102/. Final default CI passed962 tests
(98.220 seconds), tracking, generated progress and whitespace checks. Both diff
checks passed. No private report or target bytes are committed.

Counts remain1427 exact /443604 bytes,1637 source-present,1656 authored,
1826 mapped,2074 excluded,297 review and813 units.
