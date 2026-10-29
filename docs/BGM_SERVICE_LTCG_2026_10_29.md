# BGM fade and level control through genuine source context

The complete fade403940 and set-level403990 members are now **canonical exact
70/70 and69/69**. Canonical Japanese1.06a executable SHA256 remains
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Body hashes are respectively
`816da95d20e72e50c20d9b06412cb583251b37a19c0b79f37c8f2bc6c852d868` and
`7d08d83b2486bd9ea897e46b72d1c3bce52d86c8ffecac45679f6264495653dd`.
Raw CFG traversal reaches all70/69 bytes and RET16;10/11 following INT3 bytes
are outside the bodies. Exact facades43B140/43B170 call at43B158/43B199.

## Source recovery

`src/audio/BgmServiceRuntime.cpp` now supplies the real checked handle lookup,
stream transition and a natural logarithmic-gain provider alongside its four
existing service members. The pointer-only manager view has vectors at04/14,
free-slot list24, generation30 and CriticalSectionWrapper34, total50 bytes.
The raw lookup's low/high16-bit handle checks, scoped lock and vector::at are
preserved. The stream view exposes observed transition fields1350..1368 and
existing buffer28; this is not a full stream construction/layout claim.

The real transition body updates immediate gain/DirectSound volume or records
a delayed gain transition. Its native threshold at6D6EF4 is float0.002,
bytes6F12033B, now an isolated validated data alias. The natural gain provider
uses actual log10 and clamp logic; it does not copy the retained provider's
volatile staging or claim a new exact gain-helper result. The separately
accepted DirectSound unit is unchanged. All calls resolve to genuine source
or pinned CRT/SDK libraries; there are no manufactured code-address providers.

Whole-CIL optimization naturally chooses EAX for stream and EDI for duration,
while retaining an ordinary C++ method declaration. Preserving the actual public
lookup member keeps its observed ordinary entry; no dummy caller or forced
register is used. Set-level immediately becomes69/69. The helper itself remains
144/native153 on aligned-frame/FP preparation; neither it nor lookup gains
independent exact/source-ledger credit in this batch.

Fade also exposed an actual retained-source error. Native40395F loads the raw
flag argument, and402BF9/402BFC copy its low byte to stream1368. There is no
nonzero-to-one conversion. The previous bool/ternary source inserted one and
produced75/native70 even in genuine context. The source now forwards an int
flag unchanged, with only the callee's observed byte truncation. This faithful
stack-slot view does not prove the original nominal parameter type. The
existing global fade facade now declares the same forwarding interface and
still passes literal1. All three facade bodies replay unchanged17/40/47.

Scheduling403840 remains142/native143, first+2. Stop4038D0 remains96/native98,
first+32. No partial-function credit is assigned to these or to any provider.
Only the two complete accepted members add139 authored exact bytes.

## Real static runtime, no source-owned globals

The natural math provider pulls real CRT CPU/math initialization. Import-runtime
/NOENTRY linking reports LNK4210, which was rejected rather than suppressed.
The first real-static experiment was diagnostic only because the old public
lifecycle contract required a source-owned global. No artificial global was
introduced to satisfy that restriction.

The existing linked profile now also supports static CRT without source-owned
globals. It still verifies the pinned __DllMainCRTStartup entry. This mode
additionally requires bounded, read-only C/C++ initializer tables with genuine
crt0init.obj sentinels and exact HIGHLOW fields. The C++ table must have no
callbacks. C entries must have unique, specifically allowed libcmt symbol/owner
pairs: onexit, SSE2 math, SSE2 availability and multibyte initialization.
Unknown callbacks, duplicates, source CIL initializers and missing relocations
fail closed. Global lifecycle/EH contracts retain their existing requirements.
Two focused tests cover this new boundary and rejection paths; no broad runtime
matrix was added and the diagnostic DLL is never executed.

The selected gpt-web-bgm-service-runtime unit uses this real static profile.
Its four runtime callbacks are retained in each comparison receipt. Full code,
all data/REL32 operands and every relocation remain unmasked. There is no
initializer or helper byte credit merely for linking successfully.

## Verification

Current focused receipt:
`build/frontier-bgm-transition-context-20261029/formal-final-build.json`.
`boundary.json` records native CFG, hashes and caller/flag facts.
`caller-build.json` replays all three affected global facades.
`static-global-replay.json` preserves the two existing PackageArchiveStore
lifecycle matches163/228; `import-runtime-replay.json` preserves the existing
wave-clear85 match and its known245/native247 caller. These two older profiles
skip the new runtime-only table branch; the final additional callback allowlist
only tightens the new mode. Unchanged corpus receipts are retained, not cold
rebuilt. `tool-tests.log` and `ci.log` record the focused tooling and final gate.
Private construction/control recipes are under
`.analysis/frontier-bgm-transition-context-20261029/`.
