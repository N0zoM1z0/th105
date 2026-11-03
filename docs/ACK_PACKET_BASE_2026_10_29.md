# ACK_INFO packet base ownership, JP1.06a

Native ACK_INFO vtable6C2504 references COL6D8858, type descriptor6E6ED0
(.?AVCDPP_ACK_INFO@@), hierarchy6D886C and base array6D887C. Derived BCD6D8888
contains one base; BCD6D870C names IPacket through descriptor6E6E44 and gives
its nonvirtual displacement0. This is not the former source's non-polymorphic
four-byte result base, which is physically placed after a derived-owned vptr.

NetworkAckInfoSendersRuntime.cpp now represents the actual8-byte polymorphic
base: serializer slot0 plus result word+4. ACK_INFO inherits that vptr and
retains its exact40-byte extent, values+8, two14-byte deque members+C,
peer bytes+34 and remaining tail. The original base method spelling and pure
virtual status are not claimed; no virtual destructor is invented.

The constructor44DAC0 remains43/native41, first mismatch+13, source SHA256
57deb312456101365f99b5625edb1192d1fc3b3307a8853600defe2af3cef806.
Native uses XOR EAX/word publication before the array-construction arguments;
the source uses immediate-zero publication. No exact credit is added.
Initialization-bearing result-value probes, both with and without the correct
polymorphic base, also remain43/41 and are not selected.

The fresh changed-TU formal build retains both actual sender functions exact:
44F0F0 at269 bytes and44FE30 at341 bytes. No shared packet header, wire
serialization implementation or accepted byte count changes.

scripts/repo-python scripts/build.py --unit gpt-web-network-ack-info-senders-runtime --compare --json

Receipt:build/frontier-ack-result-value-20261029/formal.json.

## 2026-11-03 shared ACK packet type

The serializer/parser TU still used the superseded non-polymorphic-base view even though the native RTTI proved the offset-zero polymorphic base above. `NetworkAckInfoPacket.hpp` now provides the single shared `NetworkAckInfoPacket40` definition, including its existing result word, two deques and tail fields. The sender, serializer/parser and newly recovered replay-dispatch source use that same type; the replay dispatcher's ACK virtual call now has the actual serializer implementation available rather than a distinct undefined ACK type.

Fresh canonical comparisons preserve serializer `0x44DF20` 292/292, parser `0x44E0A0` 183/183 and senders `0x44F0F0` 269/269 and `0x44FE30` 341/341. The constructor remains nonexact 43/native41 with its previous object hash; the replay dispatcher remains nonexact 566/native566 with its previous object hash. The match-unit description now states the RTTI-backed hierarchy. Receipts: `build/frontier-ack-real-shared-type-20261103/`. This removes a source-type contradiction without adding exact bytes or claiming a complete integrated link.
