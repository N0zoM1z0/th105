# BGM load dispatch and stream preparation: complete exact bodies

Original Japanese TH105 v1.06a SHA-256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

Two complete authored functions are newly canonical exact:

- Service play4036E0:351/351, SHA-256
  fea47955e33ed4ba53cd643c6917befee1f956ed8a926051598f6a580c6f24df.
- Stream prepare402960:159/159, SHA-256
  17e3cec7bdd668e5f6a4652292fab29a7968ec73afbb3b21a2ca0dfb8b004c75.

Preparation additionally passes all79 cleanup/EH bytes: handler6BDA98/27,
string cleanup6BDA90/8, FuncInfo6E40BC/36 and one-state unwind map8. The actual
single call40375E in the freshly exact351-byte service establishes its private
entry. Existing strict exact-parent and full EH verification is reused without
any verifier change. The entire parent and all typed relocations are replayed,
not inferred from a historical match or partial byte prefix.

## Recovered application policy

The service looks up its packed slot/generation handle. If a stream exists,
it passes a genuine by-value std::string and the product of service gainsAC/B0
plus requested gain to stream preparation. Queue mode inserts at the front
of pending94 and signals loading event14. Immediate mode starts the stream;
success appends to active88 under the actual critical section20. Failure
appends to retiredA0 and signals event14. All paths, including invalid-handle
and immediate-load failure, return true as the target does. No defensive
false return, filename guard or extra locking is added.

Preparation clears active20, assigns the by-value path to name00, resets
state1C to3, records current/master/start/target gains, clears transition1350,
duration1354, flag1368 and next136C. It deliberately does not clear previous1370
or scheduled134C, which are not written by this native function. Its parameter
string has normal C++ destruction and cleanup ownership, not an explicit
copied stack representation.

## Genuine provider context and source boundary

BgmServiceLoad.cpp includes the existing complete BgmStreamRuntime.cpp, with
its real Ogg/file/DirectSound/math providers, and reconstructs the checked
manager lookup alongside the service's observed fields. This service is a
pointer-only view, not a new global storage/lifetime claim. Thread bytes are
unaccessed; event14, critical1C, manager38, token queues88/94/A0 and gainsAC/B0
have independently observed offsets. Queue and argument values use the existing
four-byte BgmHandleResult. This is a meaningful token representation, not proof
of the original nominal class spelling.

Ordinary C++ context naturally selects ESI for private prepare and EAX for
stream start. Source keeps normal member declarations and has no forced
alignment, private ABI annotation, inert locals, dummy callers or native-byte
substitution. The actual ordinary public manager lookup entry is preserved,
as already independently established in previous BGM source work. Complete
source bodies, original Xiph libraries and pinned CRT/SDK imports resolve the
provider graph. No synthetic code-address stubs are linked.

The stream start provider is339/native358 here and remains unaccepted. Its
named caller binding does not claim whole-callee equality. Likewise no extra
lookup, container, math or codec provider is credited by these two matches.
The independently accepted old Ogg open291 and SFL loader484 are freshly
rebuilt in their existing selected context and remain exact, including their
required private-entry/EH proofs. The only old source change is the ordinary
prepare declaration added to BgmStreamRuntime; its definition lives in the
new service source, with no shared layout, compiler flag or data-alias change.

## Verification and accounting

scripts/repo-python scripts/build.py --unit exact-first-bgm-load-service --compare --json

Both public roots freshly pass. Focused existing source-consumer replay selects
418A10 and418D10 in exact-first-bgm-stream-runtime. Default CI210 and whitespace
checks pass. No cold whole-repository comparison is claimed.

Two authored functions add510 bytes:1575 exact /448471 bytes; source1770,
authored1790, mapped1797, excluded1658, review579, units755.

## Separate master-gain control remains private

A bounded follow-up reconstructed master-gain403A30/284 in the same actual
service/stream context. Straightforward parameter clamping plus ordinary gain
conversion initially emitted357 bytes with inlined math. Preserving the actual
public stdcall gain provider and using a direct value clamp emitted300 bytes; a
standard min/max clamp also emitted300. The native clamp's x87 value flow,
loop/register scheduling and full alignment remain different. No extra stores,
forced alignment, synthetic helper or permissive alignment matching was added. Both
accepted play/prepare roots still replayed exact in the private control. The
experimental method is not selected and the accepted source was restored. No new
counts or credit.

A separate wave per-handle gain401CE0/109 control reused the real gain and
resource-handle lookup definitions, preserving their independently observed public
entries. Its source body is101/native109 and lacks the aligned EBP frame; no native
caller byte is waived. Real Xiph dependencies were linked rather than faking their
providers. This unsuccessful private source is not selected. The earlier
float-overload/frame investigation in
DIRECT_SOUND_VOLUME_SOURCE_INTEGRITY_2026_10_29.md already bounds that shared
math-provider uncertainty; no overload/spill grid was repeated.
