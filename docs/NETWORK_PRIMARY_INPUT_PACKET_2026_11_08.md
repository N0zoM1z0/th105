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
