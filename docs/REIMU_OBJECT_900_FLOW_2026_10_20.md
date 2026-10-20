# ReimuObject900 retiring requests and selector flow

This advances the [901 checkpoint](REIMU_OBJECT_901_FLOW_2026_10_20.md)
for authored root `ReimuObject_dispatch_action_state_vslot28 @496540`.
Only original Japanese TH10.5 v1.06a is used, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The void/ECX/RET0 ABI, vslot28, provisional39853-byte main-span ledger and
owned-extent unit are unchanged. The comparison covers all46138 physical
bytes through4A197A, including46128 owned instruction bytes and10 alignment
bytes. No root exact row, remote_exact flag or authored-byte credit is added.

## Observed target instructions

The physical900 interval `[49C9F5,49CEC2)` is1229 bytes/289 instructions,
SHA256 `1755ac682f0c7af76eca0b7ef8d3a247efb855a85b94d53e7546f00378b2e28e`.
It is one action interval inside the root, not a standalone compiler boundary.
A signed word13E load, CMP3 and unsigned JA49C9FF guard indexed dispatch
49CA05/table4A1BA0. The destinations are49CA0C,49CB3F,49CC4D,49CCA3;
default goes directly to movement49CE8A.

Let F be ESP after the fixed438h allocation and four saved-register pushes.
Push-adjusted raw addresses establish these distinct real request objects:

| Path | Buffer | Contents / count | Final target edge |
| --- | --- | --- | --- |
|Sequence0 owner174<=0|F+2DC|`0,0,2` /3|49CA6A ->499DF8|
|Sequence0 signed counter>=40|F+164|`parameter0,0,3,selector_value` /4|49CB3A ->499DF6|
|Sequence1 phase!=0 or owner174<=0|F+3E4|`0,0,2` /3|49CC48 ->499DF6|

499DF6 sets ECX;499DF8 is their common World CALL. That call also has users
outside900, which this four-sequence projection does not prove equivalent.
The selected C++ keeps three separate arrays alive in the case scope and
carries their actual pointer/count to one final call. These are used request
values with supported lifetimes, not inert compiler-shaping locals.

The counter40 packet uses a scalar comparison chain, reading6FA894 once:
selector3/2/1/0 assigns50/25/15/8. Only valid selectors reach the fourth-word
store49CB04. Invalid selectors leave it unwritten; unlike901's real fourth
zero, no zero initialization belongs here. The preceding source `switch`
compiled to a four-entry jump table. A const scalar snapshot and explicit
comparison chain restore the observed control shape without defining an
extra invalid-selector value.

Sequence3 stores the float radius `state370 * 40.0` at F+18 before testing
state370 for zero. Its central request jumps49CD26 ->49CE40 and shares World
CALL49CE4A with the second offset request. The first offset World is49CDB5.
Each offset evaluates Sin before Cos:49CD50/49CD83, then49CDE3/49CE18.
The second pair reloads packet0 and actor fields after the first World; radius
remains the saved float. State370 increments and Wave0 follows the last World.
The limit predicate then reloads parameter3. Existing source expressions
already compile to this two-site emission graph; the additional explicit
coordinate rewrite is unselected. Movement49CE8A jumps49CEBD ->497191 to
the root's existing animation/completion tail. No local900 animation clone is
introduced. Original x87 unordered behavior in sequence1 bounds is retained.

## Focused structural and execution evidence

The new `scripts/audit-reimu-object-900-flow.py` validates the signed-sequence
protocol, then compares four static normal-return call/RET projections and
their joint graph, retaining each physical call and its sequence membership.
The selected source passes all four and joint13/13 call nodes. The baseline
has13 target/15 source nodes and fails sequence0 plus the joint graph, even
though all ten compared concrete prefixes agree. Independent mode graphs
alone would not check the cross-sequence sharing of the final request.

Twelve inputs, SHA256
`1cdacb680ac94507940d054018043be6304f6ebc0a13c92c99fcb8a436dad1b0`,
comprise ten target/source prefixes and two target-only observations:

* One prefix per sequence0..3, with actual sequence dispatch checked.
* Four counter40 requests with selector0..3, actual helpers and A5 free-stack
  input initialization. Their fourth words are8,15,25,50 respectively.
* Target-only selectors-1/4 preserveA5A5A5A5 in the fourth word. The source's
  uninitialized fourth element is outside the defined input domain; no source
  equality or portable meaning is asserted for these two contexts.
* Central and offset sequence3 prefixes check actual packet bytes and the
  Sin-before-Cos helper order at the first World entry.

Helpers execute original instructions, including lookup/RNG initialization.
Opaque entries stop execution; no World return is fabricated. Input-only
free-stack fill does not modify the return address, instructions or helpers.
The static graph assumes normal ABI returns and collapses RETs. It proves
neither branch predicates, physical RET ownership, opaque-return effects nor
canonical equivalence. Object-only reports retain
`build_provenance_verified=false`; formal build receipts are separate.

The shared graph walker now accepts only explicitly reviewed nested selector
switches. Recognition allows intervening x87 loads/stores that preserve the
integer register and comparison flags. Unknown indirect jumps still reject.
Three portable tests exercise flag-preserving packet stores, an integer
clobber rejection, and explicit nested-dispatch review/all-arm call edges;
seven prior graph order/loop/partial-sharing tests remain.

## Controlled VC8 experiments

All four controls start from the fresh901 baseline with the same VC8 SP1
profile, header and bindings. Each compares the full46138-byte target extent;
all remain nonexact at49655F/+31 with a natural438h frame.

| Shape | Canonical bytes / SHA256 prefix | Root CALL / RET | World sites | Joint900 graph |
| --- | --- | --- | --- | --- |
|Fresh baseline|45068 /d44dee15|401 /61|106|13/15 rejected|
|Scalar selector only|45068 /f34d2f4c|401 /61|106|13/15 rejected|
|Selected scalar selector + retiring join|45020 /4a3f8c39|399 /59|104|13/13 equal|
|Scalar selector + explicit emission coordinates|45052 /6cba25a9|401 /61|106|13/15 rejected|
|Both request joins|45004 /adae2ba8|399 /59|104|13/13 equal|

The explicit emission rewrite gives no call-sharing improvement: baseline
already has the target's two emission sites. Its shorter section does not
justify adoption. This corrects the initial hypothesis of a third excess900
site. Only the supported scalar selector and retiring-packet join are selected.
The scalar chain still has an instruction/lifetime residual: target49CB04
has one fourth-word FSTP at F+170, while selected native PCs806182/8061A5/
8061C8/8061E3 have four such stores at F+110. The scalar comparisons and
request sharing therefore do not prove the original x87 phi/store placement
or stack layout. A later used-scalar/finalization lifetime experiment must
retain the invalid selector's skipped store, rather than initialize it.

Whole-root World totals remain99 target/104 source and animation22/12; the
other23 callee totals agree. Root totals are404/399 direct CALLs to25 callees,
68/59 RETs and0/43 identical owner diagnostics. The source decodes10248
instructions, with metadata44152/868 bytes. Count gaps do not quantify missing
behavior or confer partial exact credit.

## Selected artifact and validation pins

| Artifact | SHA256 |
| --- | --- |
|Selected CRLF CPP|`73370b96caebc5f5b59d32412ef31ff6f364905930eadaeb389e21a0bf0ff6c4`|
|Unchanged header|`348794fa1087721b1444eacdc1d421355b6b8f76f656bd216b41261221876adc`|
|Canonical45020 at496540|`4a3f8c39fab18e7a3fa8dbbc71fa1d0f370312e11f949adb78e0c9b74a4789f9`|
|Native45020 at800000|`373934e1e3bcc34286151a06c27d44667e13fdc7767f72f9bfdb7f96a1f4f080`|
|Runtime proof COFF|`69e7d31154addc897bd1ed9e3180f29e70d1eafd31835c5557a4709604a4cd98`|
|Final formal COFF|`d2ba2f24a453d9f7ca30e12f1c8f012b6df236b685a7a082c88063b07f22da85`|

The final formal build refreshes the receipt after a ledger wording correction.
Both COFFs export byte-identical complete canonical/native payloads, verified
before interpreting the execution reports. The fresh starting formal COFF was
804d92e05b40868a13f443ad29516e62458496f79385a1d625a17e753f99ee10;
its canonical payload equals the preceding checkpoint.

Private focused native passes0/5640 upper-state/900 gates/emission/bounds/
animation inputs, SHA256
`8f5ff73135872f79b5afe39207c3188773e6ad34412a3193e3f46256ebfb4494`:
4570 real RETs and1070 first World entries,852 target/793 source instructions
visited. Existing object/owner/parameter, helper trace, stack, saved-register,
x87 state and frontier rules remain active.

An additional private edge matrix passes0/808, input SHA256
`d8550fac6ec607ae903036a607a676b47a19d07e759373f782e4e8876e8b01be`:
396 real RETs and412 first World entries. It combines signed counter extrema,
reviewed sequence/default inputs, signed facing extrema, zero/subnormal/large/
infinite radius states and both x87 precisions. An earlier attempt to supply
sequence-32768/32767 fails while constructing the fixture's animation-resource
addresses, before executing either function. That fixture limit is recorded
privately; no target/source failure or coverage for those sequence values is
claimed. The corrected edge matrix does not modify the shared native auditor.

The frozen selected public CPP also passes **0/133192** unchanged full inputs,
SHA256 `f46a849ff57f64bb16e77fd0e28f7f51eee7238501c04049add99e7f77fc3b8b`.
Visited instruction counts are9215 target/8823 source. Endpoints remain119356
actual RETs,10422 first World,915 setup,1151 owned-spawn,26 effect,114 wave,
472 parented-spawn,112 CRT errno and624 CRT qNaN entries. This is the admitted
input matrix, not coverage of every root instruction or returning opaque graph.
The source hash in its final receipt equals the frozen selected CPP above.

Fresh regressions pass9010/8 with joint23/23 calls,8040/3144, selector0/16,
both808/812 caller proofs, orientation0/400, alpha0/1170 and terrain288.
The target terrain result retains240 finite equal prefixes and48
hardware-unqualified nonfinite contexts; no additional hardware claim is made.
All25 typed REL32 targets,121 DIR32 bindings and20 scoped literal aliases are
unchanged. Floating audit remains349 ledger literals/775 explicit mappings/
1124 target references. No shared header/layout/compiler/profile/relocation
change invalidates another accepted object in this batch.

Original accepted manager4937D0's76-byte body also executes before the root
for0/3744 upper-state/900-gate inputs, SHA256
`fd2ee7fdf8dfaed18083b001c8148806c8031b7be09e4b1032d82301adfe0c03`:
3128 actual wrapper RETs and616 first World entries,743 target/684 source
instructions visited. The fixture clones the vtable into receiver input memory
and sets only the clone's28 entry; original code/vtable bytes stay unchanged.
Zero freeze/hold words and a null secondary delimit this integration scope.
The manager result uses the final formal COFF and the same native code hash.

The finished worktree must pass the mandatory local CI/diff gate before commit
and push. Ten portable graph tests are included in that gate.

## Provenance, reproduction and limits

Fresh target/ledger preflight, full raw root closure and shared-callee ranking
precede the work. IDA metadata identifies another image and supplies no
semantics. A single direct read-only/no-analysis Ghidra run independently
attests file/import identity, entry, mapped text, root and vtable under
CPU0/nice10/128MiB heap. All nine primary database hashes remain unchanged,
and the temporary alias is removed. Decompiler locals and array sizes remain
hypotheses; raw push-adjusted ESP proves the buffer addresses above. No
external engine analogy or retained source overrides these instructions.

Generated reports and controls stay in `build/reimu-object-900-flow-20261020`;
private drivers remain in `.analysis/reimu-object-900-flow-20261020`.
Redundant canonical byte copies and unselected full-root owner diagnostics
are removed, retaining their900 scope, source, COFF and regeneration recipes.
No executable, database, compiler installation or generated report is committed.

```bash
python3 scripts/verify-target.py
python3 scripts/check-ida-mcp.py
python3 scripts/report-reconstruction-status.py --summary
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-update-target.py --json
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-reimu-object-action-state --compare --json
# Expected mismatch across the complete46138 physical bytes.
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-900-flow.py build/match-units/GptWeb_ReimuObjectActionState.obj --output build/reimu-object-900-flow-20261020/flow.json
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-scalar-actions.py build/match-units/GptWeb_ReimuObjectActionState.obj --final-actions --output-dir build/reimu-object-900-flow-20261020/positive
python3 -m unittest discover -s tests -p test_reimu_selector_call_graph.py -v
python3 scripts/check-match-literals.py --require-target
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

**Unknown:** cross-action World/animation/RET sharing, constant/register/stack
lifetimes, original source spelling/TU/compiler context and any truthful LTCG
boundary. No LTCG impossibility is established. Returning opaque graphs,
arbitrary aliases/resources, nonnull rendering and unmasked exceptions remain
outside the execution scope. Terrain's48 hardware-unqualified nonfinite
contexts and measured SSE emulator gap remain open. Preserve Fighter478FA0
and initializer4A1CE0 checkpoints. No cold aggregate percentage is asserted.
