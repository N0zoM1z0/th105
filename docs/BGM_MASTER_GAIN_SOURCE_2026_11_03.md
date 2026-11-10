# BGM master gain source, 2026-11-03

The native BGM master-gain policy at `0x403A30` spans 284 bytes, SHA-256 `9a96e51df5582338e56e081b3895ca413a8679357b0e3827a967f30b755bff2b`. The exact BGM configuration function calls it at `0x43B1E1`. The target's complete body clamps and publishes master gain, locks the active-stream list, updates each resolved stream's master gain, and applies effective gain to its DirectSound buffer only when active and present. The threshold retains the native unordered-to-gain-provider behavior.

The existing `BgmLoadServiceView` now expresses that policy using its actual checked
manager, active list, stream and audio providers. No fake lock, helper, register
ABI, padding or guessed original symbol is introduced.
`exact-first-bgm-load-service` was rebuilt after the source change and its existing
play 351, prepare 159 and PCM 252 roots all remained exact.

A separate public `exact-first-bgm-master-gain` unit emits a 357-byte CIL body. Its
strict linked comparison stops with an unaccounted unreachable source gap, so the
new function is explicitly nonexact; neither the gap nor any bytes are waived. The
original three-root unit remains usable and does not inherit this blocked
comparison. See `BGM_GAIN_THRESHOLD_2026_10_29.md` for earlier x87 and iterator
analysis.

A subsequent private CFG audit identified the sole unreachable source instruction as
a six-byte `lea ebx, [ebx]` at source offset `0x5A`, immediately before a
16-byte-aligned loop entry. The native loop uses different alignment and overall
layout. This observation does not qualify the existing three-byte alignment
contract, change the comparison, or make the bodies exact.
