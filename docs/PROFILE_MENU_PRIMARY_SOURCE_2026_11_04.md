# Profile menu primary source

The existing profile-menu primary state source is now selected and registered
for the game-authored `0x0044BCF0` body. The independently exact virtual update
`0x0044D240` tail-jumps to it, and the complete original body and seven-entry
switch table are pinned in `ORIGIN_RECOVERY_2026_11_03.md`.

The ordinary structured source updates the guide and cursor, emits the observed
selection/cancel events, switches to the selected menu state, and starts text
input for the profile-name branch. Its prior goto-based shared epilogue has
been replaced with equivalent straightforward returns; no artificial control
flow or register shaping is introduced.

The fresh VC8 object contains 246 bytes of callable code, two alignment bytes,
and a 28-byte same-section switch table. The original callable is 256 bytes.
The compiler shares one return path differently, so the comparison is nonexact
(first mismatch +55) and gains no exact function or byte credit. The complete
native switch table remains independently pinned; source table equality and
runtime behavior have not been claimed. See `BUILD_MATCHING.md` for the earlier
bounded negative controls. The adjacent state-one body was subsequently selected as nonexact; see `PROFILE_MENU_STATE_ONE_SOURCE_2026_11_04.md`.

Receipts: `build/frontier-profile-primary-20261104/`; a scoped replay of the
exact dispatcher validates its caller edge, not a full application link.
Target-independent CI passed all 1,024 tests, including progress and whitespace
checks; the exact 227-byte dispatcher replay also passed.
