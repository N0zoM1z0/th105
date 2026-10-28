# BGM service initialization403460

Canonical JP1.06a SHA-256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

The exact CSceneManager initialization41E070 explicitly calls403460 with the
BGM owner7026E0. The function sets running18, creates two auto-reset events at
10/14, starts workers403B50/403B70 through real8-byte thread owners at00/08,
sets only the first worker's priority to15, and initializes both gainsAC/B0 to1.
This is an explicit runtime initializer, not a compiler-generated constructor.

src/audio/BgmServiceInitialize.cpp uses the existing BattleThreadHandle class
from AudioSchedulerRuntime.hpp. The already established start and priority
bodies are TU-visible, permitting their natural inlining; wait_for_exit retains
its native out-of-line call. No private ABI, forced inline attribute or manual
thread-handle offset access is used. This does not assert the original TU split.

First complete build:133/133 zero-difference canonical bytes, SHA256
c73fc8678642132b2692a27280f5bf8f68a6d2d26043c1de71573028e279770e.
Unit exact-first-bgm-service-initialize; receipts under
build/frontier-403460-20261028/{formal-build,boundary}.json.
The complete body ends at4034E4 RET; its CreateThread callback addresses reuse
the existing target-verified callback relocations. No shared header or existing
unit changed. Only133 authored initializer bytes receive new credit, not the
already accepted thread methods or worker wrappers.
