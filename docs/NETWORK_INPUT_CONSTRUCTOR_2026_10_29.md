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
corpus rebuild. The initial constructor checkpoint adds48 exact bytes.

## Paired endpoint destruction

43BEA0 is independently canonical19/19, SHA256
c1652a926d37f8857611bb27cdfa6f3fb4b5f0d7f6e3427c99d50a59c2531837.
The caller44DBB5 passes this address as the paired array destructor. Its whole
body clears the real short deque at68 and tail-enters input destruction409D50.
That same folded input destructor is used by the RTTI scalar entry42CBC0.
An ordinary endpoint destructor with an empty body generates this member
cleanup naturally. Input destruction remains an external declaration here;
no additional bytes are credited for that callee.

The focused formal-lifetime.json receipt replays both48-byte construction and
19-byte destruction exactly from the same source. This is compiler-generated member cleanup, not authored progress. The temporary
authored ledger credit is withdrawn; the configured exact witness is retained.
The authored increase remains48 bytes from the constructor, whose flag/mask/clear
body has independently observed application policy.

## Shared endpoint owner, November 8, 2026

The accepted constructor and cleanup now define the actual
`NetworkInputEndpoint7C` used by `NetworkBaseMembers.hpp`. The independent
`InputCore60View`, `NetworkInputConstructorView` and endpoint constructor view
have been removed. `CInputManager` also declares its existing constructor in
the shared header, and `InputManagerConstructor.cpp` defines that shared type
instead of another local class and duplicate bindings/counter layouts.

This fixes an initialization gap in the real network owner. Before the merge,
its object emitted a nine-byte implicit base constructor that only published
a vfptr, and a 23-byte implicit endpoint constructor that only published the
derived vfptr and zeroed the deque. Those definitions did not initialize the
bindings, counters or injected-input policy. Exact comparison of the parent's
callback addresses alone had not exposed their different emitted bodies.
The original 31-byte array-call site at `44DBB5` proves the constructor and
cleanup pair, two elements, stride `7C` and parent member offset `F8`.

The shared providers now reproduce complete base construction `409CF0`/60,
endpoint construction `44D8F0`/48 and endpoint cleanup `43BEA0`/19. The two
constructor declarations resolve to these actual definitions; the parent no
longer emits the incomplete implicit versions. The derived normal/scalar
support remains exact at 5/30 bytes, and both callable table roles are checked.
The resolved mask at offset `62` remains untouched, as in the original.

Eleven focused units preserve all 15 accepted roots and the four existing
nonexact results. The nine consumers retain every other non-debug section's
bytes and relocation roles; only the superseded implicit input lifetime/type
sections disappear from the real owners. SafeSEH symbol identities also remain
unchanged after COFF symbol-table renumbering. The complete network parent
still matches main411, EH197 and metadata116. Five affected origin proofs pass,
with only the two changed executable header pins renewed where consumed.
No exact ledger entry or count changes.

Private before/after objects, `section-diff.json`, `context.json` and the origin
results are in `build/frontier-input-endpoint-owner-20261108/`. The bounded
replay drivers are in `.analysis/frontier-input-endpoint-owner-20261108/`.
Target and VC8 profiles are unchanged. The source diff and changed TOML files
were checked; no broad corpus rebuild was needed.

Global nominal identity remains separate. The shared namespaced structs do not
yet match the native global-class RTTI. The base constructor TU also retains
its previous 30-byte scalar wrapper, while the existing global lifetime TU
provides the exact native31 witness. That visibility/identity boundary was
not changed to force a match.
