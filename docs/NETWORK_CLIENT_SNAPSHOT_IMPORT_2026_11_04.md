# Network client snapshot import

The `CNetworkClient` RTTI primary vtable owns the 399-byte function at
`0x0044F200`. Its complete callable covers the locked incoming snapshot,
sequence change, two queue/peer publications or the alternate deck-copy
path, and pending flag. The target handler prefix and one scoped-lock unwind
state support the source's four-byte RAII guard. The pointer-only packet and
owner views capture observed offsets, not a claim about original nominal names.

Fresh VC8 emits 399 bytes, but the strict callable comparison first differs
at +106 in the register used for the sequence byte. The target handler prefix
is bound; complete exception metadata is not proven equal. No exact-byte
credit, live network behavior, concurrency equivalence or full-game execution
is claimed.
