# One shared UDP event interface

Receive, acceptance and peer removal now use the same global
`INetworkUDPEventProc` declaration as the existing default implementations.
`NetworkUdpEvent.hpp` replaces three incomplete callback classes and the
independent default-policy class. Its six virtual methods have the established
argument widths and order, with no virtual destructor. The existing eight-byte
interface layout is preserved; method names remain descriptive.

The original name is directly recorded by RTTI: table 0x6C1630, COL 0x6D7FAC,
type descriptor 0x6E68C4, hierarchy 0x6D7FC0 and single base descriptor 0x6D7FD8.
The complete hierarchy describes `.?AVINetworkUDPEventProc@@`. Its slots and
fresh whole-method comparisons are:

| Offset | Method | Native body | Bytes |
| --- | --- | --- | --- |
| +0 | Acceptance | 0x43AA20 | 3 |
| +4 | Rejection | 0x44E8E0 | 3 |
| +8 | Primary data | 0x43AA10 | 3 |
| +12 | Peer data | 0x43AA20 | 3 |
| +16 | Route payload | 0x43AA30 | 8 |
| +20 | Peer removal | 0x44E8E0 | 3 |

The raw PE independently supplies every corresponding invocation:
0x415B61, 0x415BE4, 0x41DC59, 0x41DD0E, the route call following 0x41588B,
and 0x413318. Each loads the callback pointer from transport +0x80 and dispatches
through the stated slot. The two pairs of shared physical defaults remain
shared; they are not additional authored functions.

## Affected validation

All four direct units were rebuilt before and after the change. Five accepted
authored roots remain exact: the receive-thread entry, scoped-lock constructor
and three default-policy roots. The two existing auxiliary exact comparisons
and all nine nonexact results retain their complete compared hashes and sizes.
Across the four objects, all 382 non-debug sections retain their full bytes,
symbol offsets, characteristics and relocation roles after the six default
method symbol renames. No new code or data section is emitted.

The actual four-TU receive graph and seven-TU initialization graph were rebuilt.
Both 81-byte allocator origin proofs pass with their complete exception and
inventory checks. The four existing emitted-helper origin checks also pass.
Only the three changed caller hashes and new shared-header hash were updated
in the two linked allocator configurations. Their native anchors and all
validation settings remain unchanged.

The matching `.analysis/` directory retains the narrow replay recipes. Exact ledgers
are unchanged.

The separate constructor/lifetime and derived-event views are not yet joined
to this interface. That larger ownership change needs its own affected closure.
The send-provider notes also now distinguish the modeled 0x200-byte prefix from
the larger lifetime view; matching offsets do not establish a whole native class.
