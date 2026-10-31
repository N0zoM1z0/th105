# Wave resource dispatch and array ownership

Scope: original Japanese TH105 v1.06a, executable SHA-256
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.
No new authored exact bytes are claimed.

## Target observations

Wave resource dispatch408ED0 is a complete151-byte body,48 decoded instructions,
two RET0 exits and internal conditional branches. Its SHA-256 is
f9f8f0ad2194ff0883e1f670e505df2337605b2ecd80a6440067d16a6e646e2c.
The already-exact DirectSound resource loader4184B0 calls it at4184FF with the
output in ECX and path in EDX. This is the existing ordinary two-argument
fastcall interface, not an invented private register declaration.

The mode byte7028D8 chooses the path. Encoded mode measures the source path,
copies it into a260-byte local buffer with strcpy_s, replaces its final four
bytes with .cv3, and calls the ordinary stdcall CV3 loader419590. There is no
new short-filename guard. Plain mode calls419690 with the real format, data and
size outputs. Its private compiled interface does not establish whether the
original C++ used aggregate or separate output parameters.

Factory-native IDA metadata, entry point and five16-byte mapped samples were
rechecked against the pinned raw executable before using its decompilation.
All passed; no database or target bytes were changed. Raw instruction listings
and responses are retained in build/frontier-wave-resource-20261031.

## Actual source and ownership

WaveData.hpp now shares the physical20-byte format plus data pointer14 and
size18 between the existing readers and the already-exact DirectSound owner.
The owner still initializes only data and size. Both replacement paths and its
destructor now use genuine delete[] for allocations produced by new unsigned
char[]. Including the real <new> declaration before the inline destructor is
essential with VC8. Scoped function bindings now identify array delete68AA26
rather than incorrectly naming free. Full304-byte DirectSound caller replay
remains canonical exact, including its normal cleanup behavior.

WaveResourceDispatch.cpp supplies the complete application policy, in the real
existing reader/package/CRC source context. It invokes the natural WaveData API;
the unchanged genuine compiler may specialize its private RIFF callee. No
assembly, fabricated call target, special register ABI or exception barrier is
introduced.

## Complete comparison results

- Existing DirectSound owner4184B0:304/304 canonical exact after the shared type
  and array-ownership correction.
- New public dispatcher408ED0:145/native151, first mismatch+27. Full canonical
  source SHA935cc3e54793e4e123cb40d4f6ddd29b298591bf214ec9c450fc86fa00990767.
- CV3 ordinary stdcall entry419590:248/native247 in the same actual CIL graph.
  Focused canonical comparison is blocked on an unresolved internal EH address;
  the free-function EH contract was not bypassed. This is not an exact result.
- Existing standalone RIFF419690 remains a nonexact ordinary aggregate-API
  control. Native private output splitting is not manually declared.

Private controls are bounded: leaving CV3 private gives235 and dispatcher143,
which do not represent its actual ordinary stdcall entry. Preserving that real
entry gives248 and dispatcher145. A normal four-output C++ RIFF interface, chosen
from the observed output addresses rather than forced registers, gives444-byte
RIFF and163-byte dispatcher; it is rejected and not published. Array-ownership
correction is byte-neutral in the selected CIL graph. No spelling grid followed.

The new unit is exact-first-wave-resource-dispatch; the CV3 entry moved from
the old standalone unit to this real caller graph. The old unit still retains
the RIFF aggregate-API control. Compare the dispatcher specifically when
reviewing its result: CV3's missing EH contract can block an aggregate report.

## Accounting and validation

The new151-byte root is authored/source-present only. Its raw hash and direct
edge from the freshly exact304-byte caller pass the new focused origin rule.
Existing unchanged ownership evidence is retained, not cold-regenerated.

Totals:1556 exact /444236 authored bytes,1753 source-present,1773 authored,
1780 mapped,1655 excluded,599 review,749 units. Compiler helpers receive no
new exact or provenance credit.
