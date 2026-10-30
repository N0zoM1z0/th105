# UDP packet-pool construction

The canonical Japanese1.06a target is unchanged. Packet-pool constructor413780
is exact145/145 in `exact-first-network-udp-lifetime`; destructor413820 remains
exact98/98 in the same freshly compiled image. Incremental authored progress
is1530 functions /434133 bytes. No parent or library helper earns credit.

## Source and ownership

`NetworkWinsockConstructorRuntime.cpp` now includes the actual packet-pool
implementation. Its real +17C member constructs the pool at412C3E. The compiler
naturally derives the pool's stack receiver, EAX result and RET4. No authored
COFF provider, forced ABI, copied machine instructions or fabricated caller is
used. Only the actual standard-library unsigned list and unsigned vector
explicit instantiations are compiled without /GL.

The +15C former manual-list hypothesis was wrong. Native allocation413E80
creates24 bytes with three links, a two-word payload, color+14 and sentinel+15.
Cleanup413D20 calls recursive414450, which visits links and deletes nodes with
no payload destructor. A `std::map<unsigned,unsigned>` is a lifetime-only view
of this tree. Original key/value meaning and map-versus-multimap semantics are
unknown; no lookup/insertion semantics are claimed. The +FC peer multimap is
independently established by endpoint lookup. Shared native CCriticalSection
RTTI supports one actual critical-section source type throughout the graph.

The owner's complete357-byte main constructor has matching instruction shapes
and relative offsets in the diagnostic. Its tree/deque cleanup registers still
differ; owner destructor341 differs from native333. Neither owner is accepted.
Thread wait has the actual priority15, STILL_ACTIVE loop, close and zero policy;
it supplies real source context and receives no additional exact credit.

## Complete pool proof

The full145-byte canonical body SHA-256 is
`ea62578de7107a6b99e73dde7424b1cde8bac39308ddeadac2f61507edbf914a`.
Its handler6BDFF1/27, funclets6BDFD0,6BDFDB,6BDFE6/11 each,
FuncInfo6E4680/36 and unwind map6E4668/24 all replay byte-exact.
Without unsigned-vector library context, cleanup state2 used ESI instead of
native ECX; ordinary library instantiation closes this difference naturally.
Both complete RTTI-backed pool/critical vtables and HIGHLOW fields are checked.

The previously absent405060 candidate is independently bounded38 bytes through
RET at405085, followed by CC padding. It deletes the vector allocation and
zeros its three pointers. It is compiler-generated and excluded, not authored
progress. There are4027 provisional candidates after adding this real helper.

The explicit `source_only_caller` constructor contract requires complete child
cleanup EH, one declared direct E8 in both closed caller CFGs, an exported real
source owner, ledger/source ownership, actual named callee, and all source
address-role/HIGHLOW witnesses. It grants no caller byte/EH equality. Existing
exact-parent and two-site contracts are unchanged. Unknown fields, false flags,
missing EH, malformed edges and unsupported member kinds fail closed.

## Reproduction

- `scripts/repo-python scripts/build.py --unit exact-first-network-udp-lifetime --json`
- `scripts/repo-python scripts/compare-linked-unit.py exact-first-network-udp-lifetime --address 0x00413780 --json`
- `scripts/repo-python scripts/compare-linked-unit.py exact-first-network-udp-lifetime --address 0x00413820 --json`

Fresh receipts are `build/frontier-udp-owner-tree-20261030/registered-ctor.json`
and `registered-dtor.json`. Private controls and owner/target disassembly are
under `.analysis/frontier-udp-owner-tree-20261030/` and the matching build scope.
The old pool-only unit is replaced; prior unaffected receipts remain valid.
