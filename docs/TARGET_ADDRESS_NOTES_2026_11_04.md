# Current-target address notes

The `TitleResourceManager` declaration now states its pinned Japanese 1.06a
address `0x00702798`, consistent with `config/reccmp-relocations.csv`, the
exact-backed resource manager, and current call sites. Its former `0x006ECD40`
comment was stale; this was a comment correction only.

`BattleRoundReset.cpp` is an unselected historical cross-version hypothesis
containing fixed addresses and manual virtual-call spelling that are not
qualified for the current target. It is now marked accordingly instead of
silently appearing current. The current target's distinct 290-byte round-reset
candidate is `0x00471180`; its ownership and nonexact status are documented in
`ORIGIN_RECOVERY_2026_11_03.md`. No implementation or exact count changed.

The profile-editor leaves and render primitives freshly replayed exact; the
profile-editor selection candidate remains nonexact as before. This is scoped
validation, not a full corpus rebuild.
Target-independent CI passed all 1,024 tests and progress checks.
