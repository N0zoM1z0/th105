# Battle outcome path B source, 2026-11-03

The existing `CollisionContext::try_outcome_path_b` source is now tracked individually. The native callable at `0x46D610` is 542 bytes, SHA-256 `450e7afc48c3a42457f273e7d649db337ddc8595af95fc1a44e2bd6071b5d898`, with 153 decoded instructions and three `RET 8` exits. The exact dispatcher calls it at `0x46D94E` and `0x46D976`; that dispatcher and the exact sibling path A both freshly replayed.

The source covers the target's conditional scratch reset, nonlethal quantity adjustment, terminal gates, counters, result publication, facing, event and effect updates. Its dataflow is preserved independently of the exact sibling; a shared caller does not establish equality. Prior target-backed work and bounded allocator controls are summarized in `KNOWLEDGE_BASE.md`.

A separate `exact-first-outcome-path-b` probe compiles the existing source to 530
bytes versus native 542. The first canonical mismatch is offset 180 and involves a
register choice; the function remains nonexact. The separate unit leaves the
existing two-function exact unit usable. No source rewrite, forced register,
partial-byte or exact-byte credit was added.

## Counter amount promotion, 2026-11-06

Native `0x46D6E5` zero-extends the frame's 16-bit amount, doubles the resulting register when bit `0x400000` is set at `0x46D700`, and only truncates when the counter is stored at `0x46D704`. The source now keeps the amount as an unsigned integer through this arithmetic instead of truncating after doubling. Both produce the same stored low 16 bits; this change expresses the observed native intermediate rather than a claimed gameplay correction. VC8 removes its extra 16-bit truncation after doubling. The complete candidate is 526 bytes versus 542 native, first mismatch +180; its register allocation and branch layout still differ, so no exact credit is claimed.
