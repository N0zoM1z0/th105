# Scenario-event parser origin, JP 1.06a

The original `0x45A7A0` span has 543 bytes, SHA-256 `a6530f7089b75b611b3f33fdfb848e7d97940381460a66c9a3ac9774dda0e38f`. Boundary analysis reaches 541 instruction bytes and identifies the internal two-byte `8B FF` alignment at `0x45A8DE`; there are no indirect jumps or outgoing direct jumps. The body performs game-specific CSV row parsing, event lookup and list/short-deque publication, supporting authored ownership.

Fresh canonical comparisons pass for `0x434CE0` (45 bytes) and `0x470880` (479 bytes), which directly call this span at `0x434CF6` and `0x470911`. The body hash and both edges are pinned by the origin rule. Receipts: `build/frontier-scenario-parser-origin-20261103/`.

`src/battle/ScenarioEventParser.cpp` is now selected by `exact-first-scenario-event-parser`. The raw native prologue and 16-byte handler prefix establish an address-only EH relocation; they do not prove cleanup-EH equivalence. A fresh canonical comparison emits 518/native543 bytes, first differing at offset 16 in the stack-frame size. The source is registered as present, but neither the complete body nor EH is exact. The candidate span's two alignment bytes remain included in the provisional ledger byte count. Receipt: `build/frontier-scenario-parser-origin-20261103/formal.json`.
