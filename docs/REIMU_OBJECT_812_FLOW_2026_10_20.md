# ReimuObject812 sequence and animation call ownership

## Scope and observed target

This supersedes the812 indirect-site and animation-sharing residual at
checkpoint093d59b. The authored root remains496540, with all46138 physical
bytes compared through4A197A. The main39853-byte candidate, three reviewed
instruction ranges, ten alignment bytes and ownership manifest remain unchanged.
Action812's physical interval `[497DC8,498328)` is1376 bytes/334 instructions,
SHA256 `5e1cf656f1216fe824e538fad76d02c60a0f6261554a79c8d1814d8947de30f0`.
It is an action interval, not a standalone compiler function.

**Observed:** bounds/phase checks and two5575C0 gates precede the heading update.
MOVSX reads the signed sequence word, CMP4/JA protects switch497E9A/table4A1AFC.
Destinations are497EA1,497F40,498141,49828C,49828C. Negative/out-of-range
sequences bypass the five arms and reach local animation4982D1.

|Path|Target physical CALL|Observed original slot/callee|Membership|
|---|---|---|---|
|sequence0 scale at least1|497F06|14 /45C220|812|
|sequence1 after state-counter helper, phase nonzero|4976E3|0C /45C390, argument3|810/812|
|sequence2 after state-counter helper, phase nonzero|49826B|0C /45C390, argument3|812|
|ordinary animation continuation|4982D1|direct4351C0|812|

The first indirect load is vptr+14 with ECX=this and no stack arguments. Both
sequence-selection paths load vptr+0C, push3, set ECX=this and return after
the actual virtual call. Slot0C's existing source parameter is short; no ABI
or header change is made. The public runtime audit independently observes
callee, vtable, receiver and stack argument in original code. It does not
infer callee identity from CALL EAX/EDX or extrapolate to arbitrary vtables.

Target sequence1 retains its physical shared path with810. Sequence2's
return is private. On ordinary paths,4351C0 may decrement330, followed by a
separate counter144/timer142/frame140/sequence2 retirement test. Sequence3/4
alpha below15 clears alpha and decrements330 **before** this animation call;
it does not bypass the call. Target RET sharing with other actions remains
unresolved and is not proved by collapsing RETs in call projections.

## Source hypotheses and controlled builds

The preceding source sent both sequence1 and sequence2 to the same
`select_sequence_three` label, and sent812 to the cross-action
`advance_with_sequence_two_retirement` label. The selected source keeps
sequence1's label and gives sequence2 its own ordinary C++ call/return. It
also writes812's existing animation/retirement operations inside its case.
No operation, helper argument, field type, shared layout, profile, binding,
packet lifetime or opaque-return behavior changes.

**Inference:** these lexical scopes better explain the observed physical call
ownership. They do not establish original source spelling or the compiler's
full source/TU/LTCG context. All four controls use the same VC8 profile and
natural438h frame. No assembly, padding, dead locals or fabricated return is used.

|Control|Canonical bytes / SHA prefix|2438 prefix differences|812 indirect partition|812 animation partition|Five-mode joint graph|
|---|---|---|---|---|---|
|baseline093d59b|44764 /3c410024|0|reject|reject|reject|
|local sequence2 only|44784 /85a6ddb2|0|equal|reject|equal|
|local animation only|44856 /150d25d7|0|reject|equal|reject|
|both, selected|44872 /fdf7c248|0|equal|equal|equal|

The negative controls demonstrate why equal executed outputs alone cannot
accept physical sharing. Sequence-only's joint graph passes because graph
entries are already inside812; the separate42-action census rejects its
animation shared with other actions. Animation-only retains the merged
sequence1/2 indirect site and fails the joint graph. All controls compare the
complete root and first differ at49655F/+31, not just the812 interval.

## Reproducible scoped audit

`scripts/audit-reimu-object-812-flow.py` reuses the complete target fact packet,
bounded source switch guards,42-action census, graph closure and graph-bijection
utilities. It rejects unknown sequence dispatches, incomplete indirect-site
coverage, changed original vtables/receivers and changed select-sequence words.
The source observations are801742/slot14,80196F/shared slot0C and801ABF/private
slot0C. All three sites execute in actual812 prefixes;810 inputs separately
exercise the other member of the shared site.

The2438 inputs (2428 action812 and10 action810) have SHA256
`b2bcfe07d54779631c15c2e02b06afbd852f072bcae802ecec88156537e28e04`.
They include the existing812 sequence, speed, growth, orbit, bounds and timer
matrices; additional alpha14/15, terminal/nonterminal, counter0/1, five signed
facings and two masked x87 precision modes; and both sequence transitions.
Results are2312 actual root RETs and126 first World entries, with zero complete
object/owner/parameter/helper/ABI/x87/output or indirect-event differences.
Original animation, virtual, orientation and state-counter helpers execute;
World calls stop at their first entry. Returning World effects are not fabricated.

Five separate sequence call projections and the combined15/15-physical-call
graph agree. These projections are conditional on normal ABI returns, preserve
call loops and physical sharing, and label indirect sites with the identities
observed under the admitted original-vtable fixture. They do not establish
predicates, loop bounds, arbitrary resources, aliases or vtables. The separate
existing812 caller proof still checks the unescaped float counter's eight
iterations and real World RET1C conditional on normal returns.

## Selected checkpoint

|Artifact|SHA256|
|---|---|
|Public CPP|`6ac4b36a94e2a994234d9b5a832bd08fb66e1edc59e56f4975657a93783214b1`|
|Unchanged header|`348794fa1087721b1444eacdc1d421355b6b8f76f656bd216b41261221876adc`|
|Canonical44872 at496540|`fdf7c248c8df3f6d4dee1e7f1f4da1913b68d3e56f12f1f5ed4af7f8eeb2f701`|
|Native44872 at800000|`bb0aacc16ef6070de1b78669b7726e29d84d52797789016e0fea65bde3567f6f`|
|Fresh formal/tested COFF|`4ddc83bee8b8e541686ea89061973397eeb7a47986eac45cc1238b9bc13d8e36`|

Source metadata44004/868, decoded10198 and reachable10195 instructions;
395 direct CALLs to25 callees,29 indirect CALLs and56 RETs. Target remains
10670 reachable instructions,404 direct CALLs to25 callees,29 indirect CALLs
and68 RETs. Equal indirect counts are not a proof of all29 identities.
Owner diagnostics remain0/43. The root remains nonexact over46138 bytes at
+31; no exact row, remote_exact flag or authored-byte credit is added.

The unchanged seven-action World partition remains99/99. Its shared source
CALL/RET move to80A721/80A737; the18-byte post-World decrement/epilogue still
agrees with499DFD..499E0E.900's one shared direct-float-produced fourth-word
FSTP is retained.24/25 direct-callee partitions still agree; animation improves
22/12 to22/13, with nine physical calls and other action memberships unresolved.
812's own indirect and animation memberships now agree, while RET membership,
register/stack placement, original source/TU/LTCG context and full-root bytes
remain open. Prior World/900/901/804/selector evidence is retained under fresh
selected-object regressions, qualified by its original scoped contracts.

Frozen selected full-input execution passes **0/133192**, unchanged input hash
`f46a849ff57f64bb16e77fd0e28f7f51eee7238501c04049add99e7f77fc3b8b`.
Target/source visited counts are9215/8819, with119356 actual RETs,10422 first
World entries,915 secondary setup,1151 owned-spawn,26 effect,114 wave,472
parented-spawn,112 CRT errno and624 CRT qNaN endpoints. All original input,
object/owner/parameter, helper, stack/saved-register, x87 and frontier guards
remain active. Final CPP/COFF/native hashes are checked against the frozen pins
above. ExistingWorld540+180,900v2,9010/8/joint23,8040/3144,selector0/16,
808/812 caller,orientation400,alpha1170 andterrain288 regressions pass. Terrain
retains240 finite equal and48 hardware-unqualified nonfinite contexts. The
25 typed REL32 targets,121 DIR32 bindings and20 scoped literal aliases are
unchanged;349 ledger literals/775 explicit mappings/1124 target references pass.
These are scoped execution and ownership results, without root exact credit.

## Provenance and commands

Preflight verifies only original Japanese1.06a SHA25656350024… . IDA reports a
different image and contributes no semantics. Direct Ghidra read-only/no-analysis
attests file/import identity, entry, mapped text, full root hash and vtable,
then exports the bounded812 instruction listing. CPU0/nice10/128MiB heap, one
Ghidra process and all nine primary database hashes are preserved. No target
bytes are patched; temporary project aliases are removed.

Generated controls/reports are under `build/reimu-object-812-20261020`, with
private drivers under `.analysis/reimu-object-812-20261020`. Object-only audits
retain `build_provenance_verified=false`; formal compiler/input/source/COFF
receipts are separate. No compiler, game binary, database or report is committed.

```bash
python3 scripts/verify-target.py
python3 scripts/check-ida-mcp.py
python3 scripts/report-reconstruction-status.py --summary
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-reimu-object-action-state --compare --json
# Expected nonexact result over all46138 physical bytes.
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-812-flow.py build/match-units/GptWeb_ReimuObjectActionState.obj --output build/reimu-object-812-20261020/812-flow.json
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-812-loop.py build/match-units/GptWeb_ReimuObjectActionState.obj
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-world-sharing.py build/match-units/GptWeb_ReimuObjectActionState.obj --output build/reimu-object-812-20261020/world-sharing.json
python3 scripts/check-match-literals.py --require-target
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

No shared header/layout/profile/object partition/typed relocation keys change,
so unrelated accepted units do not require replay. No cold aggregate percentage
is claimed. Returning opaque graphs, arbitrary aliases/resources/vtables,
nonnull rendering, unmasked exceptions and terrain's48 hardware-unqualified
nonfinite contexts remain open. Preserve Fighter478FA0 and initializer4A1CE0.
