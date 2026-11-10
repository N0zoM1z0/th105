# Shared UDP provider for ACK_INFO senders

The Client and Server ACK_INFO senders now call the existing
`NetworkWinsockSendClientView` implementation through its shared declaration.
Their former `NetworkClientSend4View` and `NetworkServerSend5View` methods had
no source definitions. The Server alias also returned `int`, whereas the
implemented provider returns `void`; neither native ACK sender consumes a
send result.

## Native member and call contract

The Japanese 1.06a Client call at `0x44F1B7` targets `0x416990`; the Server
call at `0x44FF3F` targets `0x416B60`. Both form the transport receiver from
owner+0x3B4 and the serialized packet buffer from owner+0x5B4. The provider's
existing fields extend through the queue lock at +0x1E4, ending at +0x200.

`NetworkWinsockSendClient.hpp` moves that existing definition unchanged from
its implementation file. Both ACK sender views now use the same 0x200-byte
prefix instead of a method-only byte followed by 0x1FF reserved bytes. This is
the send provider's modeled prefix, not a proved complete native class size.
The separate lifetime view reserves 0x314 bytes; its tail ownership remains
unresolved. Size and offset assertions preserve the transport and buffer offsets. Calls use
the provider's existing unsigned timeout argument and actual return types.
No shared packet, input class, wire format or sending policy changes.

## Complete affected comparisons

Fresh before/after builds preserve both authored ACK sender bodies:
`0x44F0F0` is 269/269 and `0x44FE30` is 341/341. Their cleanup support also
compares completely, with all relocations resolved:

- Both target entries reference the same 48-byte cleanup/handler region at
  `0x6BA660`; the handler starts at `0x6BA668`.
- Both use the 44-byte unwind/FuncInfo region at `0x6E003C`, with one state
  whose predecessor is -1. Its action destroys the packet at frame -0x50.
- The actual packet destructor at `0x44DAF0` matches all 19 bytes, including
  both short-deque destructions through the vector-destructor iterator.

The provider's linked unit retains its accepted 167-byte token release and
all four nonexact client/server/worker/entry hashes. The separate packet acquire
unit and ACK constructor also retain their previous nonexact results. The two
sender bodies, packet constructor/destructor and owned EH sections are unchanged
apart from the two named call relocations. Header inclusion additionally emits
two four-byte STL constants, not new callable bodies.

The two source-dependent origin proofs, `linked-packet-deque-back-106a` and
`vc8-linked-peer-allocator-106a`, were rebuilt and passed in full. Only their
changed implementation pin and new shared-header pin were updated. The header
has LF checkout attributes to keep those executable-input identities stable.
The separate blocked input migration was not included.

Reproduction uses `build.py --compare --json` with
`gpt-web-network-ack-info-senders-runtime`,
`cross-v106a-network-winsock-send-client` and
`cross-v106a-network-udp-packet-acquire`. No new authored exact count or complete
application link is claimed.
