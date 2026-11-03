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

The Client and Server secondary packet dispatchers now also construct and parse the shared RTTI-backed `NetworkAckInfoPacket40` instead of their own stale non-polymorphic-base aliases. The inline constructor is naturally kept as the original out-of-line call in both TUs; the actual parser symbol is shared as well. Fresh canonical comparisons remain exact: Client `0x44EE80` 582/582 and Server `0x44FB40` 532/532. Receipts: `build/frontier-ack-secondary-real-type-20261103/`. Their exception cleanup bodies are not newly claimed exact by these body comparisons; no exact bytes are added.

## Shared IPacket base for replay

The SHA-pinned target's replay vtable `0x6C24F8` points to COL `0x6D880C`, whose hierarchy `0x6D8820` identifies `CDPP_REPLAY` and the same offset-zero `IPacket` base descriptor `0x6D870C` used by ACK_INFO. `NetworkPacketBase.hpp` now shares that established polymorphic base, and `NetworkReplayPacket.hpp` supplies the same real replay type to its serializer/parser, client secondary dispatcher and replay-request handler. Native RTTI receipt: `build/frontier-replay-shared-ipacket-20261103/rtti.json`.

Fresh canonical comparisons preserve all twelve packet-leaf roots, including replay serialize `0x44D990` 285/285 and parse `0x44E160` 171/171; Client dispatch remains 582/582, both ACK serializer/parser roots and both exact ACK senders remain exact. The ACK constructor and replay-request dispatcher retain their prior nonexact results and hashes. No new authored exact bytes, cleanup-EH equivalence or complete-link claim.

## Shared IPacket base for replay requests

The target request-replay vtable `0x6C24E0` points to COL `0x6D8774` and hierarchy `0x6D8788`, which uses the same offset-zero `IPacket` base descriptor `0x6D870C`. `NetworkReplayRequestPacket.hpp` now supplies the real shared request type to Client/Server secondary dispatch, the request serializer/parser and the request handler. This also replaces the old Client-only `packet_type()` virtual declaration with the established serializer slot. RTTI receipt: `build/frontier-replay-request-shared-ipacket-20261103/rtti.json`.

Fresh canonical comparisons preserve all twelve packet-leaf roots (including request serialization 27/27 and parse 19/19), Client secondary roots 91/91, 13/13 and 68/68, and Server dispatcher 532/532. The request handler remains 566/native566 nonexact with the same canonical candidate hash; full cleanup EH and integrated link are not claimed. No new exact bytes are added.

## Shared IPacket base for INPUT

Native INPUT vtable `0x6C24EC` points to COL `0x6D87C0` and hierarchy `0x6D87D4`, whose offset-zero base descriptor is again `0x6D870C` (`IPacket`). `NetworkInputPacket.hpp` now provides the shared INPUT type for its serializer/parser and Client/Server secondary dispatchers. The prior replay-request checkpoint also received a fresh canonical replay of its separate 110-byte pump `0x44D880`; the request serializer/parser ledger signatures now use the current shared request type. RTTI receipt: `build/frontier-input-shared-ipacket-20261103/rtti.json`.

Fresh comparisons preserve all twelve packet-leaf roots, replay request pump 110/110 and Client/Server secondary dispatch bodies 582/582 and 532/532. The separate `InputPacket24ConstructorView` embedded in the network base remains to be reconciled independently; no new exact bytes, cleanup-EH equivalence or complete-link claim.
