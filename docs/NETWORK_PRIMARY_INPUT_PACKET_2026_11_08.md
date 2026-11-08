# Primary network input packet ownership

The network base constructor places an `InputPacket24` at owner +0x90, with
its tag at +0x9c and its deque at +0xa0. The client and server primary runtime
views now use that same packet type rather than splitting it into an unrelated
serializer facade, state bytes and queue. Input publication calls the packet
through its actual `NetworkPacketBase8` base; its sender result is still the
base field at +0x94. Compile-time checks retain the +0x90 packet and +0xdc
following lock offsets in both views.

Fresh full-function comparisons of client sync `0x44E8F0`, client publication
`0x44ED10`, and server sync `0x44F730` all remain exact against JP 1.06a,
including their relocations. This is semantic consolidation, not new exact
credit.

The server input publisher now also uses the packet's real `sequence_008` and
`values_010` members, connecting its increment and history maintenance to the
same object subsequently serialized. The two previously exact peers in that
translation unit remain exact; the ACK tail and server publisher remain
nonexact with their pre-change object hashes, including 404 versus 409 bytes
for the publisher. No new exact credit is claimed.

The primary protocol send paths on both sides now use the same embedded input
packet and its real base as well. The server's sequence comparison is tied to
`sequence_008`; the clients' pending-send path serializes that same packet.
All seven selected client/server protocol functions remain exact, including
complete relocations. No additional exact functions are claimed.

The adjacent owner +0x64 and +0x70 scene packets likewise use the actual
`ScenePacket0C` objects constructed by the network base, with the peer-state
bytes expressed as their first payload bytes. Client and server sync plus
client publication remain exact with complete relocation comparisons.
The client protocol view now uses those same two scene packet members rather
than separate opaque bytes. Its four selected protocol functions remain exact.
