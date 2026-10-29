# Network input endpoint constructor, JP1.06a

44D8F0 is canonical exact 48/48, complete through RET at44D91F.
SHA256:957bbca7276927eaf0de68ac6807c0905b94e5bc40c484533a356205e4ef9ca0.

## Ownership and layout

The CNetworkBase constructor at44DBBA supplies44D8F0 as the array constructor
for two7C-byte endpoints at owner+F8. Its paired destructor is43BEA0.
The endpoint composes a68-byte input object and a real std::deque<short> at68.
This is not a claim that the deque belongs to the RTTI input class itself.
Input base409CF0 initializes bindings at4 and ten counters at38..5C.
The input prefix has masks60/62 and a boolean64; resolved62 is deliberately
not initialized because the target does not write it here.

The published table6C1154 has COL6D7A50 and TD6E6588 naming CInputManagerEx.
Its two slots are42CBC0 and409F70. The next DWORD is ASCII data, not a third
virtual. Scalar destruction42CBC0 calls409D50, which only restores the input
base table; it does not own the endpoint deque. The isolated constructor view
therefore uses a two-slot override and composition. Existing partial shared
interfaces and accepted consumers are unchanged.

## Source and comparison

The natural constructor first assigns use_injected=true, then injected_mask=0,
then clears its default-constructed queue. This reproduces the native store
order without inert locals, manual vptr writes or forced register allocation.
The old store-order stop is superseded; no unique original source spelling or
original translation-unit boundary is inferred from this match.

scripts/repo-python scripts/build.py --unit exact-first-network-input-constructor --compare --json

Source:src/network/NetworkInputConstructor.cpp.
Receipt:build/frontier-network-input-constructor-20261029/formal-build.json.
Full private section comparison and formal section-tail size both cover48 bytes.
No shared source or compiler profile changed; validation is focused, not a cold
corpus rebuild. Only48 new exact bytes are counted.
