# UDP packet-pool lifetime and owner layout

## Exact target observations

Only original Japanese TH10.5 v1.06a was inspected, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Raw CFG review closes every main byte of these five return-terminated bodies,
without escaped direct branches, indirect jumps or uncovered tails.

| Address | Role | Bytes | Instructions | Body SHA-256 |
| --- | --- | ---: | ---: | --- |
| `412B10` | UDP owner constructor | 357 | 90 | `1f6718b9858d06144cf048ccb87a190f243e87c4d17f8bf77ca2b3e154d99c2b` |
| `412CC0` | UDP owner normal destructor | 333 | 89 | `5887adc2e6fb39505a144b4599c30f2da93fdf3a35dcab65e4e96142934f40b0` |
| `413780` | Packet manager constructor | 145 | 46 | `ea62578de7107a6b99e73dde7424b1cde8bac39308ddeadac2f61507edbf914a` |
| `413820` | Packet manager normal destructor | 98 | 34 | `cf5e0ec2b084cdb14ee98ab0640946e5e9fc43a511ec44da55fa2f6f92e1edb5` |
| `4138B0` | Generated packet manager deleting wrapper | 30 | 11 | `58e4f9f275e78197e7a9bc8fead74f8f3b33a2a4198562c0b6c5e73715b46782` |

The owner's primary vtable `6D6C5C`, COL `6DCE50` and type descriptor
`6FA60C` identify original `CNetworkUDP`. The packet member's vtable
`6D6C64`, COL `6DCE08` and type descriptor `6FA5B4` identify
`CHandleManager<NET_PACKET_UDP_BUFFER>`. Owner constructor site `412C3E`
constructs the member at+17C; destructor site `412D2E` destroys it.
Their policies and concrete game payload identify authored lifetimes;
automatically generated deleting wrappers remain compiler-owned.

The manager constructor physically consumes self at stack+4, returns it in
EAX and executes RET4. The ordinary normal destructor consumes ECX. These
are observed machine interfaces, not permission to declare an artificial
external stdcall constructor. Source keeps a real C++ class constructor.

## Native member and payload recovery

The earlier owner source treated its peer tree+FC as a manually initialized
list and put an opaque0x68-byte pool at+17C. Independent
[peer lookup/removal evidence](NETWORK_WINSOCK_PEER_REMOVAL_2026_10_16.md)
establishes the real `multimap<unsigned int, NetworkPeerRecord20*>` at+FC.
The pool itself is0x64 bytes; the event at owner+1E0 follows it as a separate
owner field. The outer critical section still begins+1E4 and the complete
owner remains0x314 bytes. No padding is added to reproduce code generation.

| Manager offset | Native source member | VC8 x86 bytes |
| --- | --- | ---: |
| `00` | Primary virtual pointer | 4 |
| `04` | `deque<NetworkUdpPacketBuffer41C>` | 20 |
| `18` | `vector<NetworkUdpPacketBuffer41C*>` | 16 |
| `28` | `vector<unsigned int>` generations | 16 |
| `38` | `list<unsigned int>` free indices | 12 |
| `44` | Current generation, initialized zero | 4 |
| `48` | Virtual critical-section wrapper | 28 |

Slot acquisition `417660` zeros0x41C bytes: size immediate at `4176D9`,
memset call at `4176F0`. Deque push `417A30` independently has that element
stride. Send paths including `416990` write protocol opcode at payload+1C
and caller content from+1D. The recovered packet is endpoint16, timestamp+10,
options+14, size+18 and1024 payload bytes at+1C. Free-slot consumption at
`417755` reads a full DWORD from list node+8, supporting unsigned-int indices.
Compile-time assertions pin packet size/payload and all pool member offsets.
Names expressing timestamp/options remain interpretations of their use;
the exact original field spellings are unknown.

`src/network/NetworkUdpPacketPool.cpp` uses an ordinary generation initializer
and an empty virtual destructor. Real member destruction releases the critical
section, free-index list, generation vector, stable pointer vector and packet
deque in reverse order. The generated calls and resets reproduce the observed
lifetime; no manual STL cleanup, vptr assignment or copied decompiler body is
used. Source is a method-focused view, without unsupported virtual methods.
The owner's separate tree+15C retains its existing opaque lifetime view:
concrete key/value types and multiplicity are still unknown.

## Strict canonical result and compiler context

The ordinary VC8 `/O2 /GS` pool candidate has ctor146/145 and dtor97/98.
The destructor's packet deque cleanup uses ordinary ECX, whereas the target
uses a private ESI helper. Pure `/GL /LTCG` gives a98-byte destructor but
also changes owner allocation and the shared list helper to the wrong private
ABI; equal size is not an exact result.

`src/library/UnsignedIntList.cpp` supplies the genuine standard explicit
instantiation `template class std::list<unsigned int>;`. Compiling it as
ordinary COFF and linking it before the pool CIL object preserves that shared
list helper's normal ECX entry while allowing the packet deque's private ESI
entry. The complete destructor becomes canonical **98/98**, with all four
REL32 fields, both native vptr stores and the DeleteCriticalSection IAT
reference verified. Canonical body SHA-256 is the full target hash above.
There are no dummy callers, register declarations, optimization attributes or
synthetic callee implementations. This reproducible link context does not
establish the original TU partition. The library instantiation receives no
authored progress or new target-helper exclusion credit.

The linked comparator now has a narrow typed primary-vtable contract. Both
native source vtables and their scalar deleting entries must belong uniquely
to the CIL input, with matching source-class RTTI and read-only primary COLs.
The hash-attested original PE independently checks each target RTTI spelling,
allowlisted four-byte entry and executable candidate destination. Replay
replaces only the full imm32 field of a native dword member-vptr MOV, requiring
exact one-to-one HIGHLOW relocation coverage. All unrelated base relocations,
internal literals, EH references, register loads and flat-vtable binding
bypasses fail closed. Additional COFF source/object hashes join normal build
provenance; modified artifacts fail before decoding. See
[the full linked comparison contract](LINKED_PE_MATCHING.md).

Both supported Capstone versions,4.0.2 and5.0.6, pass all15 linked-path tests
and independently rebuild/compare the selected98-byte destructor and30-byte
compiler wrapper. Build and comparison must use the same recorded parser
version. No existing COFF comparator permissions are changed.

The pool constructor remains source-present/nonexact. Its retained native
definition is exported as genuine lifecycle context, but its internal linked
EH address is unsupported by this comparator. Selecting the constructor or
requesting its whole linked unit fails closed; only the normal destructor
enters authored matches. There is no partial-constructor acceptance.

The corrected owner source is **354/357 ctor** and **398/333 dtor**. All
relocations resolve in the focused ordinary unit. EH ordering/register
allocation and native tree cleanup inline/private context remain different.
The old manually represented owner constructor was357/357 but nonexact at
+2D; replacing the incorrect type is semantic progress despite a different
candidate size. Keep these owner methods nonexact until stronger source/TU
evidence resolves them.

## Compiler ownership correction and replay

Fresh native owner source also reproduces scalar deleting wrapper `412C80`,
30/30, SHA-256
`b74b71b94d9b6d840d4a964ffc91b40859cc7d890d6a0b227c84beddf59be257`.
Its RTTI slot, normal-destructor call at `412C83`, flags branch and delete
call at `412C90` establish compiler ownership. There is no handwritten
definition of its `??_G` symbol. Remove its former authored match/source credit
while preserving the configured canonical compiler witness. Pool wrapper
`4138B0` reproduces30/30 and retains its existing compiler exclusion.
This batch adds98 authored exact bytes and removes30 incorrectly credited
compiler bytes, a net68; it is not a fresh aggregate replay claim.

```bash
python3 scripts/build.py --unit cross-v106a-network-udp-packet-pool --json
python3 scripts/compare-linked-unit.py cross-v106a-network-udp-packet-pool --address 0x00413820 --json
python3 scripts/compare-linked-unit.py cross-v106a-network-udp-packet-pool --address 0x004138B0 --json
python3 scripts/build.py --unit gpt-web-network-winsock-scalar-dtor --compare --json
```

Formal reports are `build/network-udp-packet-pool-dtor-formal.json`,
`build/network-udp-packet-pool-selected-formal.json` and
`build/network-udp-native-owner-formal.json`. The owner unit's expected full
comparison exit is1 because the two authored methods remain nonexact.
After the shared linked comparator change, a fresh build and accepted-function
dispatch reproduce scene retirement `408870` as281/281 and the pool destructor
as98/98. `build/network-udp-packet-pool-accepted-dispatch.json` records both
selected accepted results; no aggregate cold replay was performed. Local
`python3 scripts/ci.py` passes all147 tests and generated-progress checks.
`matches.csv` records only the new98-byte authored destructor.

## Analysis working state and remaining unknowns

The attached IDA preflight still reports a different executable; no IDA
analysis is used. Raw facts come from the hash-attested target PE. Direct
Ghidra independently checks executable/program SHA, base, entry marker,
x86 Windows identity and every mapped .text byte before work. The owner's
0x314 and pool's0x64 types, full four lifecycle extents, names and physical
parameter storage were saved, then read back in a fresh read-only invocation.
Logs are `build/network-udp-lifetime-ghidra-save.log` and
`build/network-udp-lifetime-ghidra-readback.log`; the latter ends
`NETWORK_UDP_LIFETIME_READBACK_COMPLETE`. Boundary evidence is
`build/network-udp-lifetime-boundaries.json`. Private drivers/database stay
below `.analysis/`; one Ghidra process uses768MiB and two active processors.

Remaining unknowns are the original source partition/inline decisions,
constructor private entry and EH context, second owner tree's concrete types,
and complete gameplay meanings of offset-named fields. No target bytes,
private ABI facades or extra progress exclusions are introduced to close them.
