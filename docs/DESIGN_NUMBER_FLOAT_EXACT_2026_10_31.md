# Floating number renderer: complete canonical exactness

CNumber floating rendering at 0x00415050 is now canonical exact **581/581**.
The complete canonical SHA-256 is
11ddf568e6f2fd9607a1f317b4d11db4f8ec16756e76b59f1cb540003221d40a.
This adds one function and 581 bytes, reaching 1546 / 438602.
Source-present and authored counts do not increase.

## Evidence and source

The hash-attested original Japanese 1.06a PE remains the oracle. The retained
207-instruction body, RET24, five tile calls, 0.33f literal, vtable owners and
incoming dispatcher edge are independently recorded in
DESIGN_NUMBER_RENDER_2026_10_21.md. This checkpoint uses raw target bytes, not
an unverified analysis database.

The ordinary unexported helper definitions are visible with both real outer
callers. The integer-number and tile providers use their complete existing
bodies, with field names mapped onto the independently checked caller layouts.
DesignNumberRenderProviders.cpp contains those bodies. TextureHandleRuntime.cpp
and AngleLookup.cpp supply their real implementations; the pinned static CRT
supplies fmod and conversion routines. There are no fabricated callees,
executable absolute bindings, copied target bytes or authored COFF files
misclassified as libraries.

The genuine linked context naturally emits AND ESP,-64 and the native 0x38
allocation. No aligned data, dummy local or padding is added. The first complete
581-byte replay still differed at 0x41512F: quotient reassignment followed the
digit-count store rather than preceding it. Both native digit-loop tails
(0x41512F/0x415131 and 0x4151EA/0x4151EC) support quotient update before count
decrement. Expressing that order gives complete equality.

Precise/fenv source semantics and the existing exception-off and retained-EBP
settings remain explicit. These reproduce the target, not unique original
source spelling or translation-unit provenance.

The old file-local helper linkage generated CIL-library map ownership in the
diagnostic image. The public descriptor uses ordinary namespace functions,
unexported, whose complete bodies remain byte-identical. The compiler still
chooses EAX/RET8 and ESI/RET24 naturally. Existing strict caller contracts verify
the actual 40AFB0 -> 414EB0 and 414EE4 -> 415050 edges, with the latter checked
through the complete exact dispatcher. No comparator or validation rule changes.

The numeric 0.33f identity __real@3ea8f5c3 is added at the already attested
6D6EFC bytes. Its complete source/target IEEE value and readonly ownership are
validated by the existing numeric-literal gate.

## Verification scope

The existing gpt-web-design-number-render unit becomes a genuine linked unit.
The three existing accepted consumers in this unit remain exact: 40AF80 (55),
40AFC0 (63), and 414EB0 (95). No shared header or existing provider file changes,
so unrelated accepted receipts are retained. The new provider file has only
this consumer. No full-corpus cold replay or gameplay matrix is claimed.

Formal reproduction:

    scripts/repo-python scripts/build.py --unit gpt-web-design-number-render --compare --json

Full receipts, target disassembly and bounded diagnostic history are retained
under build/frontier-number-float-cil-20261031/ and its .analysis counterpart.
The initial static-path/static-runtime manifest combination was rejected;
the final ordinary unexported declarations pass the unchanged graph checks.
The interim authored AngleLookup COFF experiment is not the public graph:
the final context includes its actual source as CIL.

The former standalone authored-origin rule is superseded by canonical exact
ownership. Progress is regenerated. The single origin row is regenerated with the existing
baseline function after checking that only its old rule was removed and all
other rule/semantic inputs are unchanged. Full origin replays exceeded the
remote command limit; unchanged origin evidence is retained rather than
claimed freshly replayed. Final CI and whitespace checks gate the local
checkpoint; no remote push is performed.
