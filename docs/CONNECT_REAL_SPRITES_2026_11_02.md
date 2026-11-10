# Actual Connect sprite and list tile members, 2026-11-02

Original Japanese v1.06a target SHA-256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

MenuConnectConstructorRuntime.cpp now uses actual global CSprite at +0x1D4
and +0x268, agreeing with the already recovered cleanup owner. Its two virtual
texture calls now use that real interface rather than UiSprite94's manual
vtable dispatch. MenuConnectAddressList.cpp and MenuConnectHistoryList.cpp use
actual CTile for +0x300 and its existing set_texture method; their two manifest
call targets are updated accordingly. No shared class header or flags changed.

The full 728-byte constructor and both 6-byte number getters retain their fresh
before/after hashes and compare exact. Constructor SHA-256:
24eabb7746a05f06b724d86aad8273907d616ddad3d4aadd14c989f28d5b360d.
Actual sprite RTTI (273 unique bytes) and all nine virtual slots match. Complete
constructor EH remains 168 bytes plus 116 metadata bytes, also exact.

The actual include closure is only these three units. The two source-only list
loaders remain nonexact with unchanged complete candidate hashes:
- Address list 0x443130: source 870 versus native 881,
  260312f11647a54d5ce6a732170fa2592d00a6b21f556ac4ec1dc424f593696a.
- History list 0x4434B0: source 715 versus native 714,
  49c13aafe5dccea267821b0a9125212f5e23adeafdefe9e294be1640b9f478c3.

No new authored exact bytes, helper credit, full-program linkage or complete Connect
owner unification is claimed. Other partial Connect views remain. Full CI passed 962
tests (98.824 seconds), tracking, generated progress and whitespace checks. Both
working-tree and staged diff checks passed.

Totals remain 1427 exact / 443604 bytes, 1637 source-present, 1656 authored,
1826 mapped, 2074 excluded, 297 review and 813 units.
