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

Fresh comparisons preserve all twelve packet-leaf roots, replay request pump 110/110 and Client/Server secondary dispatch bodies 582/582 and 532/532. The later checkpoint below reconciles the network base's embedded INPUT view; no new exact bytes, cleanup-EH equivalence or complete-link claim.

## Network base INPUT member

The native network base constructor and destructor now use the same `InputPacket24` through a compatibility typedef, replacing the separate non-polymorphic-base view. The implicit destructor is the actual `InputPacket24` symbol, not an alternate class. Fresh ordinary comparisons preserve network constructor `0x44DB10` 411/411, implicit packet cleanup `0x43BE90` 8/8, base destructor `0x43C950` 259/259 and both UI-sprite lifetimes. Complete constructor and destructor remote EH code and metadata replay exactly; both `csprite-real-lifetimes-106a` and `implicit-input-packet-cleanup-106a` origin rules pass unchanged byte contracts after renewing the reviewed source pins. The shared INPUT and IPacket headers are included in those pins and have checkout-stable LF attributes. Receipts: `build/frontier-input-base-real-type-20261103/`. No exact-byte credit is added.

## Concrete packet vtable second slots

The original ACK, replay, replay-request and INPUT tables each contain two concrete slots: serialization followed by parsing. Earlier shared class definitions only declared the first slot virtual. Their concrete parse methods are now virtual, with their existing independently observed signatures; at that checkpoint the common base's original parse declaration/signature remained unresolved; the later inference below supersedes that source model. The checked source COFF tables each have exactly two slot relocations in native order, and target RTTI independently identifies the common offset-zero IPacket base. `scripts/audit-network-packet-vtables.py` validates fresh object provenance, source table extent/slot roles, native slot addresses and native base RTTI; its output is `build/frontier-packet-second-slots-20261103/vtables-final.json`. The accompanying negative test rejects missing or swapped slots.

Fresh comparisons preserve the previously exact packet serializers/parsers, secondary dispatchers, request pump and network base constructor/destructor. The constructor and replay handler remain nonexact with prior hashes. The input header pin was renewed, and both source-pinned origin rules plus complete network constructor/destructor EH and metadata replay successfully. No new exact bytes or claim that the common base's parse ABI is fully recovered.

### 2026-11-03: inferred common parse slot

The four packet classes now share an inferred `virtual void parse(const unsigned char*)` slot in `NetworkPacketBase8`. Removing artificial ACK returns preserves its complete 183-byte native body exactly, and the two inspected native ACK call sites do not consume its return value. All four concrete parser bodies and source vtable slot relocations remain exact against their respective native evidence. This supports a common void signature, but does not uniquely prove the original source return type or base declaration. Base abstractness and any standalone base-vtable implementation remain unresolved; no integrated link is claimed.

Fresh source/native vtable audit verified all four tables; both source-pinned lifetime origin rules and complete network constructor/destructor EH and metadata replay also passed after renewing the base-header pin. Previously exact affected roots remain exact; the ACK constructor and replay-request handler remain nonexact. No authored exact-byte gain is claimed. Evidence: `build/frontier-packet-common-parse-20261103/`.

### 2026-11-03: use the shared base at serialization call sites

The two ACK senders and replay-request pump now upcast their concrete packet objects to the shared `NetworkPacketBase8` instead of reinterpreting them as unrelated one-slot view classes. Canonical comparisons preserve both ACK senders (269/269 and 341/341), all twelve packet-leaf roots and the 110-byte request pump; the ACK constructor retains its prior 43/native41 mismatch and hash. The four packet vtable audit still verifies. This removes undefined cross-type casts without adding exact bytes or claiming new cleanup-EH or integrated-link equivalence. Evidence: `build/frontier-ack-sender-real-base-20261103/`.


## 2026-11-09: restore the small ACK and termination packet surfaces

The locally constructed SCENE_ACK and TERMINATE packets had only one virtual
slot and a non-polymorphic four-byte result base. Fresh pre-change objects
confirmed that omission, although the accepted dispatchers still matched:
their vptr relocation mapped the incomplete local table to the original table.

The original tables at `0x6C2568` and `0x6C2574` each contain two methods.
Their COLs at `0x6D893C` and `0x6D8988` identify `CDPP_SCENE_ACK` and
`CDPP_TERMINATE`. Both complete two-entry hierarchies use the same offset-zero
`IPacket` descriptor `0x6D870C`. The ACK payload byte is at +8; termination
has only the eight-byte base.

`NetworkSimplePackets.hpp` now supplies both concrete types to the Client
secondary dispatcher and the two Server callers. Each inherits the existing
shared packet base and supplies both virtual methods. The former stand-alone
type-2/type-8 serializers are now implementations of those actual classes,
connecting the emitted tables to real source providers. ACK parsing copies
input byte 1 to the payload; termination parsing is the observed no-op.

All four complete method bodies match: ACK serializer 21 bytes at `0x44E850`,
parser 13 at `0x44D7C0`, termination serializer 15 at `0x44E870`, and parser
3 at `0x44E8E0`. Four emitted table instances now have the complete eight-byte
slot arrays and the native inheritance geometry. Source RTTI names remain the
repository's descriptive names, and the common void parse signature remains
an inference from these implementations rather than recovered source spelling.

The actual include closure is four units. All eleven previously accepted roots
remain exact. Client dispatch also matches its full 624-byte code/table section,
70-byte EH code and 60-byte metadata; Server dispatch matches 564, 56 and 52
bytes respectively. All three emitted packet cleanup bodies remain exact.
No new authored exact credit is added: these physical methods were already
recorded. No source pins changed, and the pending input migration is untouched.

Evidence: `build/frontier-simple-packet-slots-20261109/` contains before/after
comparisons, `native-rtti.json`, `slots-proof.json`, and both full EH reports.
That evidence directory also retains the four pre-change objects; the small
verification scripts are in the corresponding private analysis scope. Ordinary code/table comparison alone is not enough
to establish a constructed object's complete virtual surface.
