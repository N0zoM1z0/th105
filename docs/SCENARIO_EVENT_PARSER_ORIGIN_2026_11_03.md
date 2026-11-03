# Scenario-event parser origin, JP 1.06a

The original `0x45A7A0` span has 543 bytes, SHA-256 `a6530f7089b75b611b3f33fdfb848e7d97940381460a66c9a3ac9774dda0e38f`. Boundary analysis reaches 541 instruction bytes and identifies the internal two-byte `8B FF` alignment at `0x45A8DE`; there are no indirect jumps or outgoing direct jumps. The body performs game-specific CSV row parsing, event lookup and list/short-deque publication, supporting authored ownership.

Fresh canonical comparisons pass for `0x434CE0` (45 bytes) and `0x470880` (479 bytes), which directly call this span at `0x434CF6` and `0x470911`. The body hash and both edges are pinned by the origin rule. Receipts: `build/frontier-scenario-parser-origin-20261103/`.

`src/battle/ScenarioEventParser.cpp` is now selected by `exact-first-scenario-event-parser`. The raw native prologue and 16-byte handler prefix establish an address-only EH relocation; they do not prove cleanup-EH equivalence. A fresh canonical comparison emits 518/native543 bytes, first differing at offset 16 in the stack-frame size. The source is registered as present, but neither the complete body nor EH is exact. The candidate span's two alignment bytes remain included in the provisional ledger byte count. Receipt: `build/frontier-scenario-parser-origin-20261103/formal.json`.

## Reuse of the selected-value local

The target-backed source lifetime noted in `KNOWLEDGE_BASE.md` was missing from the selected candidate: after publishing the selected short, the same integer local holds the next CSV value for the source list. Restoring that real reuse changes the generated `/GS` frame from `0x38` to the target's `0x34`, without changing the value, access order or introducing a synthetic local. The fresh complete candidate remains 518/native543 bytes and nonexact, now first differing at `+0x33` on destination-register allocation. Receipt: `build/frontier-scenario-parser-origin-20261103/reuse-selected.json`. No cleanup-EH or exact-byte claim is made.

## Native column-check and remaining-row lifetimes

The native loop checks the selected column before calling the CSV integer reader, with either branch consuming one value. Restoring that observable order and preserving distinct row-count and remaining-row lifetimes changes the first mismatch from `+0x33` to `+0x193` (403 bytes match from the start); the complete source body is 545/native543 bytes, still nonexact. The first residual concerns ordering of the source-list node pointer loads versus storing the read value. An ordinary nested `push_back(next_int())` control instead restores the larger `0x38` frame and is rejected. No exact or EH credit is claimed. Receipts: `final-read-order.json`, `remaining-inline-value.json` in the same build directory.

## Explicit list iterator lifetimes

Materializing the actual source-list begin and end iterators before assignment naturally yields 543/native543 bytes without fabricated storage. The first 403 bytes still match. The remaining differences are two instruction scheduling/register-allocation regions: source-list node preparation after the final CSV value, and iterator preparation for the list assignment. Same size is not equality; the whole body and cleanup EH remain unaccepted. Receipts: `explicit-list-iterators.json` and `explicit-list-iterators.asm` in the same build directory.

## Source-list reference and iterator scheduling

A real local reference to the source list, used for the self-assignment check and begin/end iterators, preserves behavior while reproducing the native final iterator-preparation sequence. Fresh whole-body comparison remains 543/native543 and nonexact: the first mismatch is still `+0x193` at source-list node preparation, but the complete canonical difference census falls from 25 bytes to 16. Both exact caller units and the existing generated-list origin rule replay successfully. No exact-byte or cleanup-EH claim is made. Evidence: `build/frontier-scenario-insert-order-20261103/`.
