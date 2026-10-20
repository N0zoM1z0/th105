# ReimuObject helper visibility and live x87 controls

This is the source555da070 epoch. The later
[local-exit selection](REIMU_OBJECT_LOCAL_EXITS_2026_10_21.md) supersedes its
selected pins. The negative visibility/context results below remain scoped
to their actual sources and do not prohibit new evidence-backed controls.

This checkpoint leaves the selected source unchanged from
[typed stores](REIMU_OBJECT_TYPED_STORES_2026_10_20.md). Complete496540
canonical equality is still unachieved. Target SHA256 remains
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.
Fresh preflight passes target/tracking checks; the attached IDA still has the
wrong target and is not used.

## Observed caller state

Concatenating the real `CharacterObjectRuntime.cpp` definitions before the
selected root changes its canonical payload from88bd9c9b tofc204711. Both
have46012 bytes and first mismatch49655F/+31. All three additional helpers
independently compare exact in that experimental object:

| Target | Helper | Canonical bytes | SHA256 |
| --- | --- | ---: | --- |
|435160|set_oriented_components_f0_f4|57|015590dfda96aee7e8038f5938e4fcb83d18d471f7d36b91a4b4a7863329e361|
|4351C0|advance_frame_and_dispatch|62|23d8fbc1b248a756adca80522ec8fc693b5f00bb4052cd7460199c5413ccffa7|
|64CD00|advance_phase_counter_conditional|73|5a925eba1df3d72343c51e12bf8c78497ac236d485d0a202cf46dd9399ec3712|

The existing4963A0 remains66/66. These are rechecks of accepted helpers,
not new authored credit. Callee exactness does not establish original TU
ownership or exactness of its callers.

The new `scripts/audit-reimu-object-helper-entry.py` compares logical live
x87 values/tags at direct helper entry, restricting recorded calls to returns
inside the root. It executes original helpers; opaque operations remain
entry stops. Empty physical registers, physical TOP and exception flags are
excluded from this diagnostic. It does not assert a universal empty-x87 ABI.

Default stride37 selects3600 inputs from the existing133192 finite fixtures,
with input SHA256
e90a5943bb6d191b71e759265ca9a6fbceff9bc5317da6350aa49a70577b032b.
Selected source has zero final-output and zero helper-entry differences.
The combined-runtime control has zero final-output differences but73
helper-entry differences, all action816. Its calls to4963A0 and64CD00 retain
a live zero where the original and selected source have no live x87 value.
Target816 call sites are498800/498846 and498AE6/498B2C. The sample visits24
of25 direct callees;4359F0 is unvisited. This is neither complete path
coverage nor a full133192-input replay.

Three separate visibility controls identify the responsible definition:

| Additional definition visible | Root payload SHA256 |
| --- | --- |
|435160 only|88bd9c9bc88d9fc7643a2a162de2aa1cee026fb7d744bb8feb559bb86d54474e|
|4351C0 only|88bd9c9bc88d9fc7643a2a162de2aa1cee026fb7d744bb8feb559bb86d54474e|
|64CD00 only|fc20471102d2f26496b3f68a0fd54c5fdb48618375ebf9ddda7479bea760a38b|

**Inference:** making64CD00 visible under this source/profile permits a
different floating lifetime in816. These controls reject that particular
source grouping; they do not prove that every original caller used an
external definition or that LTCG cannot reproduce the target. No speculative
visibility change is selected.

## Other bounded controls

The hosted `/GL` experiment links the real selected root and4963A0 with both
contracts exported, plus a zero-section absolute-symbol provider for actual
external destinations. It is not the recovered game link graph.

Both speed and size builds begin with `push ebp; mov ebp,esp; and esp,-8`,
unlike the target's initial `sub esp,438h`, hence fail at+0. Speed keeps the
counter's66-byte body exact; size emits59 bytes. Size also calls `__ftol2`
instead of `__ftol2_sse`. Fresh extraction of VC8 SP1 libcmt's2316-byte
ftol2.obj verifies its distinct public entry at68A1D6, not68A1A0. The complete
171-byte relocated member matches uniquely; no shared binding or authored
credit changes. The library member SHA256 is
571c5539497ab6ae752435d5a3c96bc7f186f96ab2fc6dedf37a12c2169fb5d3.

Expanding generic source tails into natural local returns emits46476 bytes,
70 RETs and altered call membership partitions, still nonexact+31. Enabling
`fenv_access(on)` only around the root compiles but comparison is **blocked**
by an unmapped double1380 literal; this is not a completed canonical negative.
No guessed relocation was added. Neither experiment is selected.

## Reproduction and remaining work

```bash
python3 scripts/build.py --unit gpt-web-reimu-object-action-state --compare --json
python3 scripts/audit-reimu-object-helper-entry.py \
  build/match-units/GptWeb_ReimuObjectActionState.obj \
  --output build/reimu-object-exact-20261020/helper-entry/selected.json
```

The root build's nonzero result is expected for the unresolved root; its
separate4963A0 result must remain exact. To reproduce the negative, concatenate
`src/characters/CharacterObjectRuntime.cpp` and
`src/characters/ReimuObjectActionStateStaging.cpp` into a private generated
CPP, compile with the selected profile and `src/characters` include directory,
then run the same audit. Expected audit exit1 must accompany exactly73 event
differences and zero output differences for this pinned source and stride.
The audit pins inputs before/after but does not independently certify build
provenance.

The fresh formal rebuild has raw COFF SHA256
9d0cf6aba4ed041369bfb47d092ad4033b959a36758baa020b419acac188609e,
with root canonical88bd9c9b and helper canonicalad12b782 unchanged.
The3600-input check is repeated as `helper-entry/selected-rebuilt.json`;
the preceding `selected.json` retains the previousda35fa38 COFF pin.
Do not equate raw object-file identity with canonical payload identity.

Receipts reside in `build/reimu-object-exact-20261020/`: `helper-entry/`,
`visible-runtime-callees.json`, individual `visible-*-summary.json`, and
`linked-context/results.json`/`ftol-provenance.json`. Private regeneration
recipes are `visible-single.py`, `linked-context.py`, and
`natural-returns-current.py` in the corresponding `.analysis/` directory.
Preserve their actual command lines, sources and objects. No full aggregate
exact replay is claimed.

Routine cleanup compresses27 superseded owner/census reports, saving11059583
bytes. Each gzip is decompressed and checked before removing its original;
`helper-entry/compression-manifest.json` records paths, sizes and SHA256.
Sources, COFF objects, recipes and current receipts remain. Restore an older
report with `gzip -dk PATH.json.gz` before running a recipe that consumes it.

Return sharing, register lifetimes, physical tail placement and original
source/TU context remain unresolved. This checkpoint adds a more discriminating
diagnostic; it does not move the canonical first mismatch or accept496540.
