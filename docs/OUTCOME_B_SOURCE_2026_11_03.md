# Battle outcome path B source, 2026-11-03

The existing `CollisionContext::try_outcome_path_b` source is now tracked individually. The native callable at `0x46D610` is 542 bytes, SHA-256 `450e7afc48c3a42457f273e7d649db337ddc8595af95fc1a44e2bd6071b5d898`, with 153 decoded instructions and three `RET 8` exits. The exact dispatcher calls it at `0x46D94E` and `0x46D976`; that dispatcher and the exact sibling path A both freshly replayed.

The source covers the target's conditional scratch reset, nonlethal quantity adjustment, terminal gates, counters, result publication, facing, event and effect updates. Its dataflow is preserved independently of the exact sibling; a shared caller does not establish equality. Prior target-backed work and bounded allocator controls are summarized in `KNOWLEDGE_BASE.md`.

A separate `exact-first-outcome-path-b` probe compiles the existing source to 530 bytes versus native 542. The first canonical mismatch is offset 180 and involves a register choice; the function remains nonexact. The separate unit leaves the existing two-function exact unit usable. No source rewrite, forced register, partial-byte or exact-byte credit was added. Receipts: `build/frontier-outcome-b-source-20261103/source.json` and `caller.json`.
