# Bind Server flush to peer removal

`CNetworkServerPrimaryProtocolView::flush_send_state` now calls the existing
`NetworkWinsockPeerRemovalView::remove_peer` implementation, rather than an
undefined `NetworkSendStateView::process` alias. The peer address, record, map
and receiver declarations are shared through `NetworkWinsockPeerRemoval.hpp`;
the lookup and removal bodies are unchanged.

In the pinned Japanese 1.06a PE, the complete 37-byte caller at `0x44F520`
preserves owner +0x3B4 in ESI. It passes that same ECX receiver and slot zero
to the check at `0x44F52B -> 0x413390` and, on success, removal at
`0x44F538 -> 0x413170`. The recovered removal consumes an unsigned slot and
returns with RET4. No adapter or change of calling convention is needed.

Seven affected units retain all 21 previous comparisons: 17 authored exact
roots, two exact compiler wrappers, and the two pending peer functions.
Removal remains 440/native489; lookup remains 162/native167. Their larger
frame and private helper ABI differences still need original source context.
All 323 existing non-debug COFF sections preserve bytes and relocation roles
after the one call-symbol substitution, including emitted EH and RTTI.
There are no added sections.

The two linked allocator proofs consume the moved declaration through their
real source closures. Both were rebuilt and passed their complete 81-byte
allocator, exception-support, caller and inventory checks. Their configurations
change only the moved source pin and add the new header pin. The generated
aggregate requires the root-relative `network/NetworkWinsockPeerRemoval.hpp`
include; a source-local include failed to resolve in that aggregate and was
corrected before the successful replay.

The transport still has separate prefix views; joining its entire class requires the
unresolved member and input closure. No exact ledger or count changes, and no
pending input-migration file is included in this checkpoint.
