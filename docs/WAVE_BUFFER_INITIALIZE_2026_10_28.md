# Wave buffer initialization and providers, 2026-10-28

Complete source now covers401990 (234 bytes),4183B0 (247) and418610 (85).
All remain nonexact. The Japanese TH1051.06a executable is SHA256
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

## Native ownership and behavior

Exact CSceneManager initialize41E070 calls401990 at41E0FF. The initializer
creates a real262144-byte zeroed local buffer and18-byte PCM format: mono,
44100Hz,16-bit samples,2-byte block alignment,88200 bytes/second, no extension.
It loads32 ordinary12-byte resource prefixes from owner+C8 and32 spatial16-byte
prefixes from+248, then initializes gains+450/+454 to1 and indices+448/+44C to0.
The two direct calls at401A20/401A31 reach4183B0. Return is true in AL; the scene
caller ignores it. The real buffer explains the stack probe and GS cookie.

4183B0 releases an existing COM buffer, calls the actual virtual initializer,
and either locks/copies/unlocks both returned regions or calls418610 when the
source is null. Initialization failure clears the pointer; lock failure emits
the current DSound-Error message and returns false. Successful paths publish the
buffer size. Its clear provider deliberately preserves the observed zero-length
memset call after Lock and forwards the returned pointer/length to Unlock;
no guessed bug fix or new lock-error guard is introduced.

All234/247/85 bytes are reached by closed CFG traversal. Return boundaries and
hashes are retained in build/frontier-401990-20261028/boundary.json. A focused
origin rule validates the three hashes and four actual direct edges. No library
helper or compiler alignment receives new authored credit.

## Ordinary source and genuine linked context

`src/audio/WaveBufferInitialize.cpp` uses ordinary C++ member contracts and the
existing typed DirectSound interface. It preserves real source buffers, format
and split-copy lifetimes. The native private conventions remain explicit:
4183B0 takes its receiver in EAX/source in EDI and pops8 stack bytes;418610 keeps
its receiver in ESI. No custom calling convention or forced register is written.

Focused unit `exact-first-wave-buffer-initialize` compiles all three complete
bodies with GS enabled where needed. Selected ordinary output is227/234 at+1,
247/247 at+0 and90/85 at+3 respectively. None receives exact credit. Real pointer
walking instead of indexed arrays does not close the ordinary native ABI gap.

A separate private one-CIL LTCG context includes all three actual method bodies.
Every code dependency resolves through pinned compiler/runtime libraries; only
attested game error strings and IAT cells are bound externally. It is a comparison
artifact, never an executable substitute or runtime test. With internal provider
visibility, VC8 naturally recovers EAX/EDI and ESI receiver conventions, but it
also specializes the only two call sites' constant size. The full initializer
becomes224/234 with a103-byte exact prefix; array-base preparation and the
specialized calls differ. Preserving the real public load member produces227/
234 and ordinary ABI again. Neither diagnostic is selected as exact.

The normal public linked profile rejects the import-runtime cookie's internal
address; a separate read-only diagnostic verifies its unique msvcrt:gs_cookie.obj
map owner, writable four-byte storage and exact initial0xBB40E64E before ordinary
DIR32 replay. No bytes are masked or changed. An attempted absolute-cookie
binding correctly fails duplicate-definition linking and is discarded; no
/FORCE, unresolved-code allowance or tool-contract relaxation is used. This
private cookie diagnostic is not a public acceptance profile.

Receipts: build/frontier-401990-20261028/formal-build.json, boundary.json,
first-comparison.json, linked-internal-comparison.json, linked-comparison.json,
private-linked-unit.json and link-driver.log. Reproduction sources/commands stay
under .analysis/frontier-401990-20261028. The original TU/public visibility and
remaining lifetime/code scheduling are unresolved. Only affected source was
built; no corpus cold replay or extra gameplay/test matrix was added.
