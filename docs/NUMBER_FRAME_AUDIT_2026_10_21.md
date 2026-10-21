# CNumber frame audit after the render matches

No new exact is accepted in this audit. The selected DesignNumberRender.cpp
remains unchanged at SHA256
`49d44f0e7bb236da792120d1d50347a4ab4be9d69a54270b5b1adf26ee5d0f04`.
A fresh `gpt-web-design-number-render --compare --json` again reports complete
55/63/95 exact and floating547/581 nonexact at415053/+3.

Only the canonical Japanese 1.06a PE is used, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
IDA attestation rejects the attached database; no database semantics or writes
are used. This is a single-core, serial compiler investigation.

## A natural counterexample to an explicit-alignment assumption

The OggPcmRuntime.cpp at commit c5a59ef has no explicit alignment declaration. Fresh
ordinary VC8 SP1 O2/GS-off compilation emits255 bytes beginning
`push ebp; mov ebp,esp; and esp,-64; sub esp,34h`. Strict FP also naturally
retains the64-byte frame, at263 bytes. Its real double current_time, loop
comparisons, library calls and addressed bitstream slot are source context,
not unused alignment scaffolding.

Adding only `#pragma optimize("y", off)` to a private copy of that exact
source removes the AND and yields a normal EBP frame at240 bytes. Thus the
frame-pointer setting can also suppress automatic double alignment in a
genuine game-side example. The preceding CNumber setting recovers its private
stack-argument protocol, but that success does not establish the provenance
of its target's64-byte frame. A retained EBP frame and automatic stack
alignment are distinct questions. This observation does not prove that
CNumber originally had a particular double local, attribute or command line.

The comparison control is reproducible without changing the selected Ogg file:

```bash
git show c5a59ef:src/audio/OggPcmRuntime.cpp > build/ogg-frame-control.cpp
TH105_EXTRA_INCLUDE_DIRS="$PWD/src/audio" taskset -c 0 nice -n 10 scripts/compile-unit.sh build/ogg-frame-control.cpp build/ogg-frame-control.obj
TH105_EXTRA_INCLUDE_DIRS="$PWD/src/audio" TH105_FP_MODE=strict taskset -c 0 nice -n 10 scripts/compile-unit.sh build/ogg-frame-control.cpp build/ogg-strict-frame-control.obj
```

The FPO control prepends the pragma to a private copy and supplies
`src/audio` as its include directory. No Ogg source selection or match changes
are made by this audit.

## Rejected CNumber type and visibility controls

All trials retain complete caller/helper definitions. None contains an aligned
dummy, fake return, byte array, assembly or register directive.

| Private change | Floating bytes | Observation |
| --- | ---: | --- |
|Real double magnitude shared by conversion and fmod, retained EBP|565|Adds qword materialization; no64-byte frame|
|Same double magnitude, automatic frame selection|586|Still unaligned; fractional count promoted to EAX, RET20|
|Real double fmod result, regular call, local fenv access|565|Adds qword store/load; no64-byte frame|
|Same result without fenv access|543|Folds decimal factor to a double constant; fails target operand evidence|
|Double1.0 instead of float1.0 in decimal adjustment|583|Changes0.33 operand to a double literal; fails observed m32 reference|
|Automatic frame selection and /Oi-|583|No64-byte frame; does not restore target entry protocol|
|External floating helper visibility|584|No64-byte frame; seven stack words/RET28, incompatible with target private entry|
|Opaque ordinary-double-call control|583|No64-byte frame; rejects the suspected builtin-name explanation|

The latter uses a private standard-ABI declaration as a compiler-classification
control only; no alias is retained or accepted. These trials discriminate
specific hypotheses, not every possible original TU or LTCG context.

Private raw-COFF, source hashes, entry bytes, extents and return suffixes are
recorded in `build/number-frame-20261021/frame-controls.json`; the same scope
retains fresh baseline and disassembly receipts. Rejected source copies remain
below `.analysis/number-frame-20261021/`. Comparison extents and canonical
hashes of the three accepted callers remain unchanged. There is no unrelated
accepted-unit replay or cold aggregate claim.
