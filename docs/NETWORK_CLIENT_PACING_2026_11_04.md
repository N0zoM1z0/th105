# Network client frame pacing

The `CNetworkClient` RTTI primary vtable owns `0x0044EAD0` at slot +0x24.
The complete 573-byte native body covers delay gating, synchronized queue
counts, state transition, queue advancement and periodic counters. All 169
instructions are reachable under the raw boundary audit. The partial owner
view uses the established endpoint and lock layouts; original source names
and complete nominal class layout are not established.

The new natural C++ source preserves the target's two separate locked peer
reads, signed delay/pacing comparisons, unsigned peer count and tick-load
order. The target calls the exact existing queue-advance member twice. A fresh
pinned VC8 build emits 573 bytes and matches the first 459, but differs from
+459 where the two counter operands are read in reverse order. This is not
an exact match, adds no exact bytes and does not establish concurrent runtime
equivalence. No live network or full-game execution was performed.
