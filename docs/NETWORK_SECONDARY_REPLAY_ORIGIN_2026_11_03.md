# Network secondary replay dispatch origin, JP 1.06a

The target entry `0x44E460` spans 566 bytes, SHA-256 `1cf3d06ff026c5e6401efa673b64c3ab8eea34f7d0b664aa26ed61423b13952c`. Its complete decoded instruction span handles game-specific ACK_INFO and replay-packet lifetime/publication, using locked owner state and checked deque paths; see the prior semantic findings in `KNOWLEDGE_BASE.md`. The boundary audit shows no unvisited bytes, indirect jumps or outgoing direct jumps.

Fresh canonical comparisons replay client secondary dispatcher `0x44EA30` (68 bytes) and server secondary dispatcher `0x44FB40` (532 bytes). They call this entry at `0x44EA69` and `0x44FBB1`, respectively. Both caller edges and the complete target body hash are pinned in the origin rule. Receipts: `build/frontier-network-replay-origin-20261103/`.

Earlier natural-source analysis reached 566/native566 but differed in register allocation and remains a non-acceptance. No selected current source unit or full EH comparison is established for this entry. This checkpoint classifies authored ownership only; it adds no source-present or exact bytes.
