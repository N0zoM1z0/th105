# Practice battle policy source, 2026-11-03

The existing `PracticeBattlePolicyView::update_428260` implementation is now recorded individually. The native callable body is 553 bytes, SHA-256 `e111df68d1aa22d605f48a182591f33c9f62cf5b92f867c363d450b6d8d933b2`, followed by three alignment bytes and a five-entry switch table. The exact battle-presentation caller invokes it at `0x46B1A4`; a fresh public replay retains that caller's complete 105-byte match. The separate table is checked but is not counted as authored function bytes.

The existing source covers practice guard policy, two fighters' health and spirit restoration, mode selection and input binding, plus the observed non-practice branch. The earlier `PRACTICE_BATTLE_POLICY_2026_10_28.md` documents field evidence and bounded controls. No added null checks, synthetic registers, padding or guessed original names are claimed.

The fresh public source section is 576 bytes including its alignment and switch table; native code plus its table and alignment also span 576, but the code differs from offset 9. Equal section size is not equality, and neither partial bytes nor the table receive exact credit. Receipts are `build/frontier-practice-policy-source-20261103/source.json` and `caller.json`.
