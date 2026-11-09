# Protocol sends use the existing UDP provider

The primary protocol, peer-state publication, packet continuation and replay
paths now use the same `NetworkWinsockSendClientView` member as the ACK senders.
Five translation units no longer declare eight independent method-only sender
classes. Each caller uses the existing 0x200-byte send view at owner +0x3B4, followed by
its packet buffer at +0x5B4. The view models only that prefix; the separate
0x314-byte lifetime view still has unresolved tail ownership. The existing provider supplies the unsigned timeout
and result-pointer types; the delay sender passes a null result pointer without
a separate `void *` signature. State-query helper views remain separate.

## The server wrapper has no result contract

The complete 53-byte wrapper at 0x44F4E0 forwards to 0x416B60 and returns without
producing a result. The provider's inactive-peer edge at 0x416B9B reaches the
plain epilogue at 0x416D7A with the records pointer still in EAX. Its active edge
instead leaves the result of SetEvent. These are not one meaningful return
value. The wrapper and its known caller declaration now return `void`, matching
the existing provider. The source no longer promises an integer from that call.

The only direct incoming edge found in the game candidate inventory is
0x44FC1C in the server secondary dispatcher. It proceeds to critical-section
release at 0x44FD2E without consuming EAX. The wrapper's complete 53 bytes and
the caller's complete 532 callable bytes remain identical to the original.
This establishes the usable return contract, not the original type spelling.

## Focused comparison

Seven affected VC8 units retain all 26 accepted roots. The two existing
nonexact comparisons are unchanged: ACK-tail import is 78/native78 with its
first scheduling difference at +53; input-frame publication is 407/native409.
All comparison results, sizes and compared hashes equal the before-change
reports. No provider source, header, compiler setting or origin pin changed.

All 787 pre-existing non-debug sections across those builds preserve their
complete contents, symbol offsets, characteristics and relocation roles after
the six explicit symbol renames. This includes EH, RTTI, switch data and safe
handler references. The added header emits only two additional four-byte STL
deque constants in the six builds that include it, with no new callable body.

The server dispatcher's complete owned extents were also replayed directly:
- Main code plus its eight-entry switch table: 564 bytes at 0x44FB40.
- Cleanup actions and handler: 56 bytes at 0x6BA620.
- Two-state unwind map and FuncInfo: 52 bytes at 0x6E0008.
- Input packet cleanup: 8 bytes at 0x43BE90; ACK packet cleanup: 19 at 0x44DAF0.

Every byte and relocation agrees. All 142 main-body instructions are reachable
through the original switch; both unwind predecessors are -1, with separate
packet lifetimes at frame -0x50. This adds evidence, not new exact ledger credit.

Reports are under `build/frontier-protocol-send-provider-20261109/`.
The private `check-sections.py` and `check-dispatch-eh.py` recipes in the matching
`.analysis/` directory bind the comparisons to their actual executable inputs.
The seven unit names are recorded in `units.json`; each was rebuilt with
`scripts/repo-python scripts/build.py --unit UNIT --compare --json` before and
after the change. The unrelated input migration remains uncommitted.
