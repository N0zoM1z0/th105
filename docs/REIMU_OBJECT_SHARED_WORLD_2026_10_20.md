# ReimuObject shared World tail and903 selector loops

> Historical experiment record. Its pins, selected source and next steps apply
> to that checkpoint. Use [the current handoff](RE_HANDOFF.md) and
> [evidence index](REIMU_OBJECT_EVIDENCE.md) for current state and ABI limits.

This records checkpoint093d59b. Its source/payload pins and open812 residual
are superseded by [the812 checkpoint](REIMU_OBJECT_812_FLOW_2026_10_20.md);
the World/903 observations remain retained evidence.

Authored root496540 had six copies of one cross-action World tail, while903
merged two target-distinct selector loops. The selected source now keeps the
real request objects alive through one shared World call and preserves both
loops. All99 World sites have the target's action-entry membership partition.
This larger supported context also recovers900's shared direct-float packet
store, without a local scalar spill or a floating-point profile change.

Only original Japanese TH10.5 v1.06a is used, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The full46138-byte comparison through4A197A remains nonexact at49655F/+31.
Owned46128 bytes, ten alignment bytes, the39853-byte provisional main span,
ECX/RET0 ABI and primary vslot28 remain unchanged. The source void return
remains an inference. No root exact row, remote_exact flag or partial
authored-byte credit is added.

## Raw observations and source lifetime correction

The complete raw CFG has42 outer action destinations and22 reviewed indirect
switches. Conditional normal-return reachability from each destination gives
one World CALL499DF8 and one RET499E0E reached by exactly these actions:

`822, 869, 900, 901, 902, 903, 908`.

The selected predecessor has no cross-action World site. Its retiring request
sites are private to their actions, although some already share several paths
within an action. The target's common call is followed by state330 decrement,
saved-register restoration and RET0. This is a dedicated seven-action return,
not the root's unrelated general retirement/return partition.

Fourteen existing real arrays now remain alive at function scope through the
common call. Each branch initializes only the packet it uses and selects its
actual action ID, pointer and word count. The fields carry genuine World
arguments. Coordinates and unsigned API facing remain fresh reads at emission;
no actor field is cached across an earlier opaque World call.

| Action | Requests reaching the common tail | Real arrays retained |
| --- | --- | --- |
|822|Second request after owner-death/frame-phase burst|Two four-word packets, each reused after its first request|
|869|Owner669 sequence completion or other-owner exhaustion|Two three-word packets|
|900|Sequence0 death/counter40 or sequence1 death/phase|Three packets, counts3/4/3|
|901|Sequence1 health/exhaustion burst completion|Distinct health/exhaustion packets retained through all earlier requests|
|902|Sequence2 death/phase|One three-word packet|
|903|Owner death or completion of selected sector emissions|Distinct health and sector/final packets; sector packet reused for its final request|
|908|Sequence6/7 retirement|Distinct three-word packets with third values8/9|

Hoisting the actual objects avoids passing a pointer after its block lifetime
has ended. It does not add padding, inert arrays, fake returns, assembly or
instruction bytes. Fourteen objects are source identities; their original
lexical spelling and all stack placements are not proved by physical offsets.
The ordinary VC8 build naturally retains the target438h frame.

##903 selector distinction

Raw903 `[49E38C,49E901)` is1397 bytes/328 instructions, SHA256
`86d302610c8539f398102696d42604148cda64a5f94ffdd4ee0aaec82cb7278c`.
It is an action interval inside the root, not an independent compiler boundary.
Selector1 has its two-sector180-degree/axis loop at World49E76C. Selectors2
and3 have separate four-sector90-degree loops at49E6CC and49E642. All retain
the sector packet at F+2C, then overwrite it for the final903 request through
49E7D4 ->49E420 ->499DF6/499DF8. Owner-death uses distinct F+30C and also
reaches that common call. Float counters advance by one; raw bound literals
are2 and4. No opaque World return is fabricated to execute those loops.

The predecessor groups selectors2/3 into one C++ loop. Splitting those branches
while retaining the same real packet adds one source World site, correctly
exposing the two physical loop bodies. Joining the retiring requests then
removes six copies. Either change alone leaves the World partition wrong;
together they give99/99 and the correct seven-entry shared tail.

## A larger context closes the900 producer residual

The [preceding local experiments](REIMU_OBJECT_900_SELECTOR_STORE_2026_10_20.md)
remain phase-scoped negatives. Their scalar join gave one packet store but
added a float temporary store/reload. No such source scalar or FP setting is
selected here. The original scalar comparison chain, under the new request
lifetimes/shared consumer, now emits:

```text
80610E FLD  dword [6C3D74]   ; selector3 /50
80611B FLD  dword [6C3B3C]   ; selector2 /25
806127 FLD  dword [6C3EA0]   ; selector1 /15
806133 FLD  dword [6C2874]   ; selector0 /8
806139 FSTP dword [F+110]    ; common packet store
```

Each selected load reaches that one packet FSTP directly. Invalid selectors
skip it. The v2 audit now passes both the shared-store and direct-producer
conditions, all ten actual prefixes, two target-only unwritten-word contexts,
and the four/joint thirteen-call projections. Its input hash remains1cdacb68.
The source packet slot remainsF+110 versus targetF+170; a register1 comparison
also differs from the target immediate. This is not a local byte-match claim.
The independent shared-tail evidence, rather than a repeated spelling search,
justifies retesting the earlier compiler phase.

## Complete call census and scoped World audit

The raw root has **404 direct plus29 indirect CALLs**, not404 total CALLs.
Earlier summaries that called404 the total omit register-indirect calls.
The predecessor has399 direct/27 indirect; selected source has394 direct/28
indirect. Its additional907 indirect site appears under the new compiler
context. One private812 site remains missing from the physical partition.
Indirect callee identity/ABI is not inferred from an EAX or EDX operand.

The new `scripts/audit-reimu-object-world-sharing.py` validates every source
indexed jump against an unsigned bound and metadata-owned destination/index
tables, then closes reachability over all42 action entries. Partial-register
writes and unknown CALL/control transfers cannot silently invalidate a checked
index. Five portable tests cover a valid dispatch, AL clobbers before/after the
guard, an intervening CALL, and a lower-bound guard that cannot protect the
upper index.

The audit compares World site counts by the complete set of entries reaching
each physical call. Selected99/99 partitions agree, as do24/25 direct-callee
partitions. Animation22 target/12 source is the remaining direct-call partition
difference. The shared target499DF8/499E0E and source80A6B4/80A6CA each have
exactly the seven-action membership. The conditional post-World slice has one
RET and no further calls. Its18 decrement/epilogue instruction bytes agree at
499DFD and80A6B9. This bounded observation is neither a separate callable unit
nor partial exact-root credit. Other RET partitions remain unequal:68 target/54
source. Source static reachability is10173 instructions, versus10177 decoded
instructions including unreachable alignment; target10670 are all reachable.
Neither same counts nor these partitions confer exact credit.

A second audit component runs540 actual903 first-entry prefixes spanning
sequence0..2, selectors-1..4, three actual MT seeds, five facings and two x87
precisions. Object/owner/parameters, packet data, helper traces, RNG and ABI/x87
checks agree, input SHA256
`151faeffa2c99e2632ca891d036f82be8fb1b21e2af3d74b7ad49c09e5131d8c`.
The observed first World sites anchor four static normal-return projections
for selectors0..3 and a joint graph. All four and joint4/4 calls agree. The
three separate loop nodes and common final node survive the joint comparison.

A further180 coupled retirement-preparation prefixes pass, input SHA256
`8882bd571ed1e0b1ea8019ff673d700a403b5fc227c1c0b2fb494dd8508b472b`.
They cover both822 burst starts, both869 retirement conditions,900 death/phase
and all four valid counter40 selectors,901 health/exhaustion starts,902 phase,
all three903 owner-death sequences, and908 sequence6/7. Five facings and two
x87 precisions vary each of eighteen contexts. Actual packet/field/helper
outputs and first-frontier roles agree. For822/901 the final retiring request
lies after earlier opaque Worlds: only the real first burst request executes;
its final tail remains static conditional-return evidence. No return is faked.
These projections do not prove loop bounds, predicates, actual returns from
World, arbitrary aliases/resources or full game behavior. Raw bound recovery
and the first-entry execution remain distinct evidence.

## Controlled full-root builds

All controls use the same VC8 profile, header and relocation keys, retain438h
and first31 target bytes, and compare the complete46138-byte physical extent.
All remain nonexact with0/43 identical owner diagnostics.

| Shape | Canonical bytes / SHA256 prefix | Direct CALL / RET | World sites | World partition |903 joint graph|
| --- | --- | --- | --- | --- | --- |
|Predecessor|45020 /4a3f8c39|399 /59|104|reject|4/3 reject|
|Separate903 modes only|45152 /72fa2cfd|400 /59|105|reject|4/4 equal|
|Shared World only|44640 /db7f9f6e|393 /54|98|reject|4/3 reject|
|Selected split + shared World|44764 /3c410024|394 /54|99|equal|4/4 equal|
|Split/shared plus explicit local decrement/return|44764 /3c410024|394 /54|99|equal|byte-identical|

The first three compiled counterexamples each pass the same540 sector and180
retirement-preparation data prefixes. Baseline and split-only still fail140
frontier-role observations because the shared seven-action site is absent. Joined-only has the correct shared seven-action tail but lacks one
903 loop site. Split-only closes those loops but leaves the cross-action
partition wrong. The whole property is tested, not a preferred count alone.
Explicit local decrement/return and goto-retire emit identical complete code;
original source spelling is not claimed. No shared header/layout/profile,
object partition or binding is changed; other accepted objects are unaffected.

## Selected pins and execution

| Artifact | SHA256 |
| --- | --- |
|Selected CRLF CPP|`8f60f8fb265ae096cf0d604e319111988b10a175555cd2b4bd70ec47d40bb880`|
|Unchanged header|`348794fa1087721b1444eacdc1d421355b6b8f76f656bd216b41261221876adc`|
|Canonical44764 at496540|`3c4100249fbbc4da6a21e498e89823813761811e25444883c65af3b5c17a4694`|
|Native44764 at800000|`a7f74e1e89c23fbf5fb7becea2c07f0659dad69b54655a9f80a6576920c4576a`|
|Fresh formal COFF|`d743840ac64fddd15427e2d9dfa0bd04df0f7465d7f6274ebe15679b8c7b61da`|

Source metadata43896/868, direct394 CALLs to25 callees,28 indirect CALLs and54
RETs remain nonexact. The cleaned public CPP exports byte-identical complete
canonical/native payloads to the private selected control. Object-only audits
retain `build_provenance_verified=false`; formal compiler/input/COFF receipts
are separate.

The frozen selected public source passes **0/133192** unchanged full inputs,
SHA256 `f46a849ff57f64bb16e77fd0e28f7f51eee7238501c04049add99e7f77fc3b8b`.
Target/source visited counts are9215/8806. Endpoints remain119356 actual RETs,
10422 first World,915 setup,1151 owned-spawn,26 effect,114 wave,472 parented,
112 CRT errno and624 CRT qNaN entries. Existing object/owner/parameter, helper
trace/argument, stack, saved-register, x87 and frontier guards remain active.
The final receipt's CPP hash equals the frozen selected source above.

Original accepted4937D0's76-byte manager wrapper passes0/8556 upper-state,
upper-900-gates, high-903-owner and final-state inputs, SHA256
`1446323855a4cb22fd6b1a7f8a264687bb47b440df679b65aab9fe4964cd0bf5`:
7800 real wrapper RETs and756 first World entries,1802 target/1675 source
instructions visited. Only an input vtable clone receives the source28 entry;
original code/vtable bytes remain unchanged. Zero freeze/hold words and null
secondary delimit this integration fixture.

Fresh regressions pass900 v2's10 compared prefixes/two target-only contexts,
9010/8 with joint23/23 calls,8040/3144, selector0/16, both808/812 caller proofs,
orientation0/400, alpha0/1170 and terrain288. Terrain still separates240 finite
equal prefixes from48 hardware-unqualified nonfinite contexts. All25 typed
REL32 targets,121 DIR32 bindings and20 scoped literal aliases remain unchanged;
floating audit remains349 ledger literals/775 explicit mappings/1124 target
references. No aggregate cold replay is claimed.

## Provenance and reproduction

Fresh target/ledger preflight, raw complete-root closure and shared-callee
census precede the work. IDA metadata identifies another image and supplies
no semantic information. Two sequential direct read-only/no-analysis Ghidra
runs re-attest file/import identity, entry, mapped text, root and vtable, then
export bounded shared-tail and903 instruction listings. No decompiler output
is used. CPU0/nice10/128MiB heap and all nine primary database hashes are
preserved; temporary aliases are removed. No target byte is patched.

Generated reports/controls remain under `build/reimu-object-shared-tails-20261020`;
private drivers remain under `.analysis/reimu-object-shared-tails-20261020`.
No executable, compiler, database, generated report or credential is committed.

```bash
python3 scripts/verify-target.py
python3 scripts/check-ida-mcp.py
python3 scripts/report-reconstruction-status.py --summary
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-update-target.py --json
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-reimu-object-action-state --compare --json
# Expected nonexact result over all46138 physical bytes.
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-world-sharing.py build/match-units/GptWeb_ReimuObjectActionState.obj --output build/reimu-object-shared-tails-20261020/world-sharing.json
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-900-flow.py build/match-units/GptWeb_ReimuObjectActionState.obj --output build/reimu-object-shared-tails-20261020/900.json
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-scalar-actions.py build/match-units/GptWeb_ReimuObjectActionState.obj --final-actions --output-dir build/reimu-object-shared-tails-20261020/positive
python3 -m unittest discover -s tests -p test_reimu_world_switch_guards.py
python3 scripts/check-match-literals.py --require-target
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Next recover animation call ownership and the812 indirect-site/RET residuals
from bounded raw paths, retaining an honest source/TU/compiler context. Stack
placement, constant/register lifetimes and exact instructions remain unequal.
No LTCG impossibility is established. Returning World/setup/event/CRT graphs,
arbitrary aliases/resources, nonnull rendering and unmasked exceptions remain
outside execution scope. Terrain retains48 hardware-unqualified nonfinite
contexts and its measured SSE gap. Preserve Fighter478FA0 and initializer4A1CE0.
No cold aggregate percentage is asserted.
