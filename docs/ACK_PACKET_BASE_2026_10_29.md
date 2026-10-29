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
