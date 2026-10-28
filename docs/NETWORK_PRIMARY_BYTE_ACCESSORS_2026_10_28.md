# Network primary byte accessors, 2026-10-28

Six complete Server/Client primary-vtable methods are canonical exact, adding
44 authored bytes. The target is Japanese TH1051.06a, SHA256
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

Fresh RTTI readback fixes CNetworkServer vtable6C16EC/COL6D803C and
CNetworkClient vtable6C1754/COL6D80BC, both primary base offset0. The existing
exact constructors/destructors independently publish those same vtables.
The reviewed cells are slots2C,30,38; unrelated slot34 remains independent.

- Server43CBA0 writes the low argument byte to+78, RET4, exact10.
- Server43CBB0 sign-extends byte+78 into EAX, RET0, exact5.
- Server43CBC0 reads byte+80 into AL, RET0, exact7.
- Client43CD10 writes the low argument byte to+6C, RET4, exact10.
- Client43CD20 sign-extends byte+6C into EAX, RET0, exact5.
- Client43CD30 reads byte+81 into AL, RET0, exact7.

All bodies are straight-line and completely decoded, with following INT3
padding through the next16-byte boundary. The old auto-analysis label naming
Concurrency at43CBC0 is not ownership evidence: the current target's typed
Server vtable owns this physical method. Original source symbols and potential
folding with unrelated identical code are not asserted.

`src/network/NetworkPrimaryByteAccessors.cpp` supplies ordinary pointer-only
field views and offset checks. The signed EAX getters are preserved explicitly;
AL-only byte getters do not invent high return bits. Signed-byte storage is a
compatible source representation, not proof of unique original field typing.
Setter return spelling is not uniquely recoverable from the incidental AL copy.
No complete allocation, lock, validation or new state behavior is introduced.
No shared networking header or existing caller ABI changes.

Focused unit `exact-first-network-primary-byte-accessors` replays all six roots
exact under VC8 SP1 O2. Receipts are
build/frontier-43cba0-20261028/{formal-build.json,boundary.json}. Existing accepted
native receipts remain incremental; no cold corpus replay was run.
