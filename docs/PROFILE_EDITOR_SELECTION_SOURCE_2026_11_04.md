# Profile editor selection source

`ProfileEditor168::update_selection` at `0x00427C60` is game-authored through
its direct call from the independently exact profile-menu state-six handler
`0x0044CF70`. Its full 333-byte native body and target SHA are pinned in
`ORIGIN_RECOVERY_2026_11_03.md`.

The recovered source follows the real controller mode, pending reset and two
text accessors. When input mode is inactive it returns -1. Otherwise it advances
the editor state, releases both texture handles and exits input mode on reset,
or regenerates the two text textures and updates the corresponding actual
`CTile` members. The former locally declared controller view has been replaced
with a shared declaration extracted unchanged from its existing implementation.
The two texture services and tile calls use the existing target-backed APIs.

A fresh VC8 O2/GS- build yields 330 bytes versus the target's 333, with the
first mismatch in a branch displacement at +13. Its reset tests and coordinate
register scheduling differ from the target. This is source-present, **not
byte-exact**, and contributes no exact bytes or functions. No gameplay or
runtime execution has been claimed.

The independently exact caller, all 10 selected controller bodies, the editor
initializer, and its three selected lifetime/leaf bodies each replay exact
following the shared header extraction. Evidence is under
`build/frontier-profile-editor-selection-20261104/`. This is scoped checking,
not a full application link or whole-corpus replay.
Target-independent CI passed all 1,024 tests and progress/whitespace checks.
