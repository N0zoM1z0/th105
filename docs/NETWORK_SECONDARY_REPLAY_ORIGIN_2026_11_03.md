# Network secondary replay dispatch origin, JP 1.06a

The target entry `0x44E460` spans 566 bytes, SHA-256 `1cf3d06ff026c5e6401efa673b64c3ab8eea34f7d0b664aa26ed61423b13952c`. Its complete decoded instruction span handles game-specific ACK_INFO and replay-packet lifetime/publication, using locked owner state and checked deque paths; see the prior semantic findings in `KNOWLEDGE_BASE.md`. The boundary audit shows no unvisited bytes, indirect jumps or outgoing direct jumps.

Fresh canonical comparisons replay client secondary dispatcher `0x44EA30` (68 bytes) and server secondary dispatcher `0x44FB40` (532 bytes). They call this entry at `0x44EA69` and `0x44FBB1`, respectively. Both caller edges and the complete target body hash are pinned in the origin rule. Receipts: `build/frontier-network-replay-origin-20261103/`.

`src/network/NetworkReplayRequestDispatch.cpp` now provides a typed candidate for both branches, using actual checked deques, scoped packet lifetimes, locks and the observed sender call. `exact-first-network-replay-request-dispatch` reproduces a complete 566-byte source body against native566, but the first difference is at `+0x49` and 177 canonical bytes differ, largely from ACK scalar publication scheduling and branch displacement. The target EH handler, packet vtables and deque callbacks are address-bound; their full emitted cleanup metadata has not been compared. Some local view names map to the established native helpers rather than demonstrated source-level linking. At that checkpoint neither complete body nor EH was established exact; the later checkpoint below supersedes it. Receipt: `build/frontier-network-replay-dispatch-20261103/formal.json`.

## Exact body and remote cleanup, 2026-11-03

The two independent ACK tail bytes are assigned before the tail word, a valid ordering under the held lock. With the actual shared packet base used at both serialization calls, the complete bounded body compares exactly: 566/566, SHA-256 `1cf3d06ff026c5e6401efa673b64c3ab8eea34f7d0b664aa26ed61423b13952c`. The two original exact callers and the pinned authored-origin proof remain the ownership evidence.

The emitted remote cleanup code at `0x6BA560` independently replays 59/59, including both destructor targets and the handler; the complete associated unwind and function metadata at `0x6DFF6C` replay 52/52. Run `scripts/repo-python scripts/audit-network-replay-dispatch-eh.py` after rebuilding the unit. These are bounded relocation replays, not an integrated-link or runtime exception-execution claim. Evidence: `build/frontier-replay-scalar-order-20261103/`.

## Replay ordering and actual insertion provider, 2026-11-09

The replay branch walks history from the requested index upward, but inserts
each short at the front of the packet's real deque. At 0x44E60F the dispatcher
indexes history; 0x44E619 then calls 0x42A4B0 with that short's address and the
packet deque as receiver. The complete 122-byte helper decrements the starting
offset, handles wraparound, stores the short, and publishes the new offset.
It is `push_front`, as the existing generated-origin anchor also records.

The source previously said `push_back` while its relocation forced the call
to this front-insertion address. Correcting the source and relocation name
preserves the entire 566-byte dispatcher. The actual emitted `push_front`
now compares 122/122 and its grow-map provider 344/344, with full relocations.
The independent remote cleanup audit again passes 59/59 code and 52/52 metadata.
The former append provider is a different 119-byte function.

Evidence is retained in
`build/frontier-replay-front-insertion-20261109/{compare,eh,verification}.json`;
the bounded provider check is
`.analysis/frontier-replay-front-insertion-20261109/verify.py`.
No shared layout, input migration, source pins or exact totals changed.
