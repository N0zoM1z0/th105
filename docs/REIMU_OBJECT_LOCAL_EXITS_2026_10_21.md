# ReimuObject local retirement lifetimes

This page records sourcea2c44054 atde4ef13. The later
[905 packet-join checkpoint](REIMU_OBJECT_905_PACKET_JOIN_2026_10_21.md)
retains the seven exits while superseding the selected source/object and
call-sharing statistics. The original receipts below keep their own epoch.

Seven ordinary local exits now replace jumps to the generic retirement label
in `ReimuObject_dispatch_action_state_vslot28 @496540`. They recover observed
state330-write-before-x87-pop lifetimes and remove the source's early EBP=1 /
EBX=0 hoisting. The complete root remains **nonexact at49655F/+31**. No root
match, remote-exact flag or partial byte credit is added. The same-TU4963A0
helper freshly remains **66/66 canonical exact**.

## Target observations and source decision

Only original Japanese TH10.5 v1.06a is used, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Fresh preflight passes target/tracking checks; IDA has the wrong10350095...
image and is not used. All new target observations use the immutable raw PE.
No analysis database is opened or modified.

The existing complete raw audit reconfirms22 switches,10670 instructions,
46128 owned bytes,404 direct calls to25 targets,29 indirect calls and68 RETs.
The unchanged owned comparison covers46138 physical bytes through4A197A,
including10 known alignment bytes. The39853-byte main ledger span remains
provisional. Vslot28, ECX/RET0 and4937D0 discarding EAX remain observations;
the void source declaration remains an inference.

At4980E4 and49B8E7 the target writes `state_330 -= 1`, then pops a live x87
value and returns. The latter cleanup is reached from bounds in855/869/903/904.
The target855 sequence is particularly clear: rounded Y is published with FST,
the first three bounds tests retain it, and an early exit decrements330 before
FSTP. The final Y comparison consumes that value and reaches a different
ordinary retirement tail. The original compound bounds predicate can remain
intact in C++; machine cleanup specialization does not require two invented
source predicates or a manually preserved floating value.

The seven changes are:

| Action | Ordinary local decrement/return |
| --- | --- |
|812|Completed sector loop.|
|821|The existing compound owner-action/sequence termination gate.|
|822|Channel112 below15.|
|855/869/903/904|The existing four-clause bounds test, without splitting it.|

Every predicate, arithmetic expression, earlier store and actual helper call
is retained. The rest of the function, including850/853/854's recovered order,
902's typed owner publications and999's cleanup, stays in its existing source
form. There are no new locals, numeric operations, flags, ABI declarations,
shared headers, relocation bindings or ownership changes.

The earlier [retirement controls](REIMU_OBJECT_RETIREMENT_FPU_2026_10_20.md)
already distinguished final-memory equality from write-time floating state.
This selection uses ordinary unsplit local exits, rather than its split-bounds
control. Changed physical call sharing is still a compiler/source-context
residual; it is not by itself evidence of a changed runtime output. The new
selection is justified by the target-backed lifetimes and native evidence,
not by RET count or section length.

## Whole-function compiler diagnosis

| Diagnostic | Previous selected source | New selected source | Target |
| --- | ---: | ---: | ---: |
|Prefix before switch metadata|45144|45460|Table starts at46140|
|Whole source section payload, including868 metadata bytes|46012|46328|Callable physical envelope46138|
|Decoded source-prefix instructions|10461|10492|10670 owned instructions|
|Source CFG reachable instructions|10457|10491|10670|
|Physical RETs|65|71|68|
|Diagnostic RET-membership distance|25|29|0|
|Instruction/edge-identical owners, entry included|0/43|2/43|Not an acceptance metric|
|Reachable physical CALLs|433|432|433|

The new identical owners are the entry and main default group, labelled802
by the mapper. This diagnostic normalizes internal edge ownership; it does
not establish canonical byte equality for those windows or separate authored
functions. The first unequal byte at+31 is a jump displacement to the later
default path. The target entry has neither of the source's former constant
initializations; the new source removes both naturally.

Call-sharing differences remain explicit. The target has separate advance
calls for817 and860/861; the new source shares one across all three. Three
World/wave pairs have906-only static membership in the target and905-only
membership in the source. These are complete graph reachability sets assuming
normal returns, not predicate feasibility or execution through opaque calls.
`call-sharing-delta.json` records the actual differences. This change does not
claim that a larger source or LTCG context cannot recover them.

The formal root comparison hashes the first46138 source bytes as
`fb49c2c120a902b1b59b50a82f31cfe931e6fdc98720385ebf726b147861a1d1`.
The complete46328-byte source section, canonically relocated at496540, has
SHA256 `7842896240c69e2d920e76b4c39262f8d43257faba0574d5bfcf849e92b28e8c`.
These are different extents: the former must not be labelled the whole
source-payload hash. The868 metadata bytes are not callable-byte progress.

## Native evidence and replay scope

The first new control passes the existing3600-input/stride37 retirement
diagnostic with zero output, ordered-write and retirement-state differences.
Its helper-entry diagnostic independently has zero output/live-x87 event
differences on the same matrix, input SHA256
`e90a5943bb6d191b71e759265ca9a6fbceff9bc5317da6350aa49a70577b032b`.
The freshly built predecessor still has22 retirement-state differences on
those inputs, with zero output/write differences. This calibrates the actual
changed property rather than relying on final-memory equality.

`audit-reimu-object-retirement-fpu.py` now records the existing typed-store
obligations and coverage during that same execution: sixteen first-store
sites, eight902 owner publications, and the static822 parameter/heading pair.
It reuses the existing StoreProbe and packet inspectors. Source pattern
failures make the audit fail; subset/stride coverage is reported separately.
This permits a single full affected-root pass to check ordered stores and
retirement state together. It does not replay unrelated exact units.

The selected formal object passes **all133192 inputs** with zero output,
ordered-write and retirement-state differences, input SHA256
`f46a849ff57f64bb16e77fd0e28f7f51eee7238501c04049add99e7f77fc3b8b`.
All16 first-store sites execute; the eight902 owner publications each execute
144 times and retain their static float spill/reload patterns.822's post-opaque
heading pair retains static order and has zero executions. Inputs are pinned
before/after. `selected-full.json` is this combined receipt, not a second
execution of the older typed-store script. The run uses CPU0/nice10, taking
540.48 seconds with peak RSS244208KiB.

The earlier control and selected formal root export identical complete46328
native bytes at800000, SHA256
`24ce549b94bcd1dad882129735963028c2aedfd04c2f2452e36fee3975f5c2f9`.
`helper-entry-byte-bridge.json` pins both COFFs and the corresponding helper
comparisons. Thus its0/3600 helper-entry evidence applies by complete native
byte equality; it is not presented as a fresh run of the formal COFF or a
full133192-input helper-x87 check. That sample visits24 of25 direct callees;
4359F0 remains unvisited in it.

All native results are finite prefixes executing actual instructions/helpers,
ending at real RETs or opaque entries. No returning World/driver/CRT result is
substituted. Logical live x87 values/tags exclude physical TOP and exception
flags. Arbitrary aliases, resources, vtables, nonnull rendering, unmasked
exceptions, opaque continuations and original source/TU remain unknown.
The native audit does not independently certify build provenance; formal
compiler/input/object receipts supply that separate evidence.

Two final-auditor negative receipts calibrate its independent checks.
`baseline-final-audit.json` again detects22 retirement differences in3600
predecessor inputs, with zero output/write differences and passing static
patterns. `raw-owner-negative.json` uses the retained raw-owner object on71
upper-state inputs: output, write and retirement differences are all zero,
but the missing902 float spill/reload patterns correctly fail the audit.
Neither subset claims complete store-site coverage. The retained object's
own source/build epoch is separate; it is not presented as a fresh build.

## Pins and reproduction

| Selected artifact | SHA256 |
| --- | --- |
|CRLF CPP|a2c44054550380596f67b5aced05f301cab26cd711ac5c22b68f06e64f162ef1|
|Unchanged header|6f469e6886959fd41ee6976b3c784c3df0c2e753ad4729a536764a3c8cd28b4b|
|Formal COFF|4ddca4f4ff71c900385602bad74f1159bdebcc1c01b2db8ffd7cee9c1e0f8118|

Receipts and frozen baseline/control/selected inputs are under
`build/reimu-object-cleanup-20261021/`; private regeneration recipes are in
the corresponding `.analysis/` directory. `baseline-build.json` and
`selected-build.json` contain both complete root comparisons and the exact
helper. `selected-summary.json` and its owner/census reports describe the
whole-source diagnostics. Predecessor source555da070/canonical88bd9c9b and
earlier133192-input receipts retain their historical epoch.

Five completed bulk owner/census/excerpt reports are losslessly compressed
with `.gz` suffixes, saving1142239 bytes. `compression-manifest.json` records
per-file hashes and verified readback before removing loose copies. Restore a
report with `gzip -dk` before a private recipe that consumes its original path.
Sources, COFFs, current summaries and native/build receipts stay uncompressed.

```bash
# Expected exit1: complete-root mismatch+31; helper4963A0 must remain exact66/66.
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-reimu-object-action-state --compare --json
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-retirement-fpu.py \
  build/match-units/GptWeb_ReimuObjectActionState.obj --stride 1 \
  --output build/reimu-object-cleanup-20261021/reproduced-full.json
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Canonical root equality, return/call sharing and remaining source/TU context
are still required. No new exact function, cold aggregate replay or aggregate
percentage is claimed.
