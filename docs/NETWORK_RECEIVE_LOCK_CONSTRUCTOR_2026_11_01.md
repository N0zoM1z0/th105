# Receive-loop scoped lock constructor

401850 is the complete25-byte authored NetworkReceiveLock constructor.
The existing definition in src/network/NetworkWinsockReceiveThread.cpp already
emits it naturally from the real receive translation unit. No source or compiler
flag changed, and no synthetic call, export, forced noinline or separate shim
was added to materialize a helper.

The actual game receive-loop call41D8F9 follows a16-byte setup at41D8EE:
form owner+E0, push that CriticalSectionWrapper pointer, form the real local
guard receiver, call401850. The already established CCriticalSection wrapper
has its Win32 critical section at+4. This explicit source constructor saves
the wrapper pointer in guard+0 and calls EnterCriticalSection on wrapper+4.
Its normal thiscall constructor result/RET4 arise from ordinary C++.

The complete native body ends401869 exclusive, SHA256
ef6ca3dce6bb3da165aeeb16d805c5cd2bce52514ce174931b27f81c58706197.
The emitted section is exactly25 bytes with one DIR32 relocation at15 to
__imp__EnterCriticalSection@4. Native IAT6C0108 resolves to Kernel32
EnterCriticalSection. The complete body has one inventory hit and a closed
RET4 CFG. This is explicit application synchronization logic, not an implicit
compiler-generated constructor or evidence that all scope guards are authored.
Nominal original class spelling remains nonunique.

Fresh private and public formal replays both compare all25 bytes exactly.
The existing thread callback41D7B0 remains14/14 exact. The complete current
receive unit was recompiled and all ten declared comparisons recorded. Peer
lookup/key support controls retain their prior ownership; receive_loop,
requests, endpoint processing and worker EH remain nonexact. No new caller,
destructor or EH credit follows from this small constructor.

Only this whole authored root is added: exact1432/443941 bytes,
source-present1637, authored1656, excluded2064, review307, units807.
Source raw SHA256 remains
5fc35db83596224f270281f55bac814bf1e45ff2b808c0540db93caef5a4a15f.
Evidence: build/frontier-receive-lock-20261101/constructor.json and formal.json.
Before acceptance, the existing strict origin framework verified the full
body hash and actual incoming call. That receipt is retained privately; the
accepted root now uses the canonical-exact-authored baseline, without a second
origin rule reclaiming it. Shared source and toolchain settings are unchanged.
