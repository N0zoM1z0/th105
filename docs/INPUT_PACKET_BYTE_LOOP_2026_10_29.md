# Input packet byte-count loop, JP1.06a

InputPacket24::parse44E050 is now canonical exact78/78:
af88af971a739ff87245034a2f0def6a68ab67b3e136fa972baf7b9839ae8dd1.

The previous zero-gate JE versus native JBE residual is resolved by a normal
forward loop whose index has the same unsigned-byte width as the wire count.
VC8 naturally emits the native TEST BL/JBE before MOVZX EBX,BL and lowers the
admitted loop to its ordinary count-down form. No artificial carry dependency,
assembly, padding or compiler-profile change is used.

The parser still skips the packet type, reads sequence/tag/count, clears the
old deque, and ignores payload when count>=100. Count0 performs no append.
The byte index cannot wrap in any admitted count0..99. Existing signed-short
packet storage and checked push_back are preserved.

An unsigned-word isolated probe first exposed the remaining loop-width issue:
explicit zero guard stayed78/78 with one wrong branch; a32-bit forward index
kept JBE but moved the extension ahead of the test. The byte-indexed loop
matched. Moving only that loop back into the original signed-packet TU also
matches all78 bytes, so no packet type or public layout change is selected.

Fresh focused builds:
- gpt-web-network-packet-leaf-runtime: all12 selected functions exact, including
  the new78-byte parser and eleven previously accepted siblings.
- gpt-web-network-replay-request-pump: its separate GS-off build remains110/110.

The request pump was initially compared against the GS-on leaf object and
correctly mismatched. Its own configured GS-off formal build verifies the
unchanged result; profiles were not relaxed or conflated.

Commands:
scripts/repo-python scripts/build.py --unit gpt-web-network-packet-leaf-runtime --compare --json
scripts/repo-python scripts/build.py --unit gpt-web-network-replay-request-pump --compare --json

Source:src/network/NetworkPacketLeafRuntime.cpp.
Receipts:build/frontier-input-word-type-20261029/formal-packet-leaves.json and
formal-request-pump.json. Default CI and diff checks validate exact tracking.
