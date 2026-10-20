# ReimuObject850/853/854 ordered stores and local fade returns

## Selected recovery and evidence classes

Root496540 remains nonexact. This checkpoint restores the observed field
write order in850/853/854 and expresses each frame2 negative-scale retirement
as a real local decrement/return. Thirteen chained assignment groups become
ordinary ordered statements. The8531.5f clamp keeps both writes conditional
with braces. No flag, layout, return type, binding, ownership or helper-body
change is made, and no root exact/remote_exact row or authored credit is added.

**Observed:** target writes angles124/128/12C, scale11C/120 and zero velocity
F4/F8 in that order. Each frame2 fade has a private `--state330; RET` path.
Three complete72-byte arithmetic/comparison/local-return windows and three
12-byte zero-store pairs agree without masks:252 diagnostic bytes.300 finite
native witnesses agree on actual memory-write order, x87 values/status,
prefix outputs and real RET/opaque frontiers. All actual helpers are original
target code; no helper return is replaced.

**Inferred:** separate assignments and local retirement explain these
instruction shapes. Original source spelling and TU remain unknown. The
root's source void and the lookup return declarations retain their previous
inference limits. Numeric equality alone did not establish field write order
or the target's private return structure.

**Unknown:** the full root still differs at+31, and other RET ownership,
zero-register placement, source/type/TU context and two first-World buffer
slots remain open. Opaque returning graphs, arbitrary aliases/resources,
nonnull rendering and unmasked exceptions are outside the admitted scope.

## Target observations and source controls

The target is original Japanese1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The39853-byte candidate remains provisional. Strict comparison still covers
46138 physical bytes through4A197A:46128 owned and10 alignment bytes.
Ownership, adjacent switch metadata and the callable boundary are unchanged.

The prior chained source assignments execute their stores in reverse order.
The target's corresponding stores run left-to-right: angle X/Y/heading,
scale X/Y, and velocity X/Y. All recovered assignments have real effects;
none introduces a fake dependency, inert value or shaping-only operation.
The853 growth cases include the false clamp branch so scale Y must retain
its growth result when scale X does not exceed1.5f.

The target's three fade paths each retain zero on the x87 stack while updating
both scales, narrow alpha by10, compare zero with the stored scale X, and
locally decrement330 before returning when scale X is negative. The source
formerly jumped to a root-wide retirement label. Its equivalent final state
concealed the different physical return partition.

All controls compile serially on CPU0/nice10 under unchanged ordinary
vc8-sp1-probe-o2, GS off/default FP. The baseline is immutablecc8eafd.

|Control|Root canonical bytes / SHA prefix|RETs / distance|Outcome|
|---|---|---|---|
|cc8eafd baseline|45744 /b3ba8c1a|62 /28|reversed stores and shared fade returns|
|Ordered stores only|45744 /6627bf9f|62 /28|correct order, private kernels absent|
|Local fade returns only|45776 /9c93494b|65 /25|private kernels agree, store order differs|
|Ordered stores plus local returns, selected|45776 /343089b7|65 /25|all six windows and native events agree|

Distance is the RET-membership multiset diagnostic, not an acceptance score.
All controls preserve404 direct calls to25 targets,29 indirect memberships,
World sharing and the real4963A0 helper's canonical66/66 body. The source
adds no fabricated helper or return value. Correct conditional scope is
preserved when a single chained assignment becomes multiple statements.

## Complete local instruction windows

|Action|Target72-byte kernel|Native72-byte kernel|Target12-byte zero pair|Native12-byte zero pair|
|---|---|---|---|---|
|850|[49AB5B,49ABA3)|[80447B,8044C3)|[49AB48,49AB54)|[804468,804474)|
|853|[49B331,49B379)|[804C0E,804C56)|[49B31E,49B32A)|[804BFB,804C07)|
|854|[49B5DB,49B623)|[804EB8,804F00)|[49B5C8,49B5D4)|[804EA5,804EB1)|

All three arithmetic kernels have identical target bytes. They load scale X
and the actual qword literal6C0E80, update and store X/Y, add byte alpha F6,
FCOMP the stored scale X, FNSTSW AX, TEST AH41, branch to the continuation,
then decrement330 and restore the real438h frame before RET. Comparison reads
the actual stored float, rather than a synthetic or host-math value. Kernel
SHA256 for all three is
`48fc08c57a60052e146b644c3711e12da4fb9e01c29ac6ea05dfcb7f24fe0cc7`.
Zero-store pairs are two consecutive FST DWORD operations at F4 then F8.
No relocation or branch field is masked; continuation displacement is part
of the72-byte comparison. This is not a complete action/function acceptance.

## Original-code execution and negative sensitivity

`scripts/audit-reimu-object-fade-order.py` inherits the full World census,
finds the three original fade comparisons and local tails, and verifies each
72/12-byte pair. It records actual writes to F4/F8/11C/120/124/128/12C,
logical x87 state at fade entry and comparison, AX&4500, and actual RET.
The underlying probe checks final memory, real callees, callee-saved state,
stack/control-word balance and the existing opaque entry boundaries.

The300 inputs cover192 frame2 fade cases,72 growth/clamp cases and36 phase/
burst cases across all three actions. They include finite values adjacent to
0.2f, signed zero, alpha wrap boundaries0/9/10/255, below/above growth clamps,
speed-word0/250, sequences0/1/2, phase1/6, and27F/37F control words. The final
input SHA256 is
`1acb6ccff4fcba940a69ba8dc838b99dcbeb3ba906af14cb7f7bc1fe2e2a6d6c`.
Selected outputs/events have zero differences:248 real RETs,40 original
secondary-setup entries and12 original World frontiers. No unmasked or
nonfinite hardware behavior is claimed for these finite witnesses.
Each action observes64 fade comparisons per side, with AX&4500 states0000/
4000/0100 occurring40/8/16 times, covering negative, equal and positive stored
scale results.

Three compiled full-root negatives execute the identical inputs. All have
zero final-prefix differences but are rejected:

|Negative|Event differences|Static rejection|
|---|---|---|
|cc8eafd baseline|266|all three zero pairs and local kernels differ|
|Ordered stores only|0|all three local return kernels absent|
|Local fade returns only|266|all three zero pairs reversed|

Thus output equality, event equality and instruction-window equality each
test different requirements. Reports retain build_provenance_verified=false
and original_source_spelling_proven=false; formal source/COFF receipts are
separate. No partial byte credit is assigned from these diagnostics.

## Frozen selected checkpoint

|Artifact|SHA256|
|---|---|
|Root CPP|`08cc1a0f7815e8724ea5102369a42f522b21f4e5d360a07a9604fcb424293915`|
|Unchanged header|`6f469e6886959fd41ee6976b3c784c3df0c2e753ad4729a536764a3c8cd28b4b`|
|Canonical45776 candidate|`343089b74da3c9e70d871c25c15e84586cf380979c88e8339b72a46b8d45e015`|
|Native45776 at800000|`1686c3b77f29036ca9f7b0ebbcb02a93a6844f335ba1bdf0cfe93123c9a58933`|
|Frozen tested COFF|`82fee43c09f3c381f178a241ecb3b08a9e878cd94cd85fa1227defe11edf2dab`|
|Fade audit|`78ccf71e40fe03551b3a2ee083a9ce29e8f052ad3055dbf245b40575b1a6303a`|

The root emits44908 code-prefix bytes plus868 metadata bytes,10414 decoded/
10410 reachable source instructions and65 RETs versus the target's68.
The first31 bytes and natural438h frame remain. Owner instruction/edge diagnostics
remain1/43 in the final31-byte physical default-plus999-cleanup region.
The root remains strictly nonexact at49655F/+31. The same-object4963A0
definition still has27 root REL32 references and remains canonical66/ad12b782.
Other accepted Runtime-unit inputs, header/layout,27 typed REL32 keys for25
physical targets,121 DIR32 and20 scoped literal mappings are unchanged.

This phase also corrects the historical direction page's native address
transcription using its actual frozen reports:3d3486d/cc8eafd869/901 consumers
start805E1E/80681C, not the earlier prose values. Current consumers move to
805E3B/806839 and remain32 bytes equal. No historical source/COFF/kernel hash
or native result changes because of this documentation correction.

Frozen full-input execution passes0/133192 with unchanged input SHA256
`f46a849ff57f64bb16e77fd0e28f7f51eee7238501c04049add99e7f77fc3b8b`.
Target/source visit9215/8985 instructions. Endpoints remain119356 RETs,
10422 World,915 secondary setup,1151 owned-spawn,26 effects,114 wave,
472 parented-spawn,112 CRT errno and624 quiet-NaN frontiers. Source/header,
frozen COFF/native, Runtime source and audit support pins agree before/after.

All20 serial selected/negative/owner/runtime commands finish with expected
exits. Preserved checks include999792, direction128, animation3360 plus
actual selector witnesses,812, World540+180/four-joint,900,901,804,selector,
808/812 caller,orientation400,alpha1170 andterrain288. Terrain remains240
finite equal and48 hardware-unqualified nonfinite contexts. Literal audit
still checks349 ledger literals,775 mappings and1124 target references.

World sharing remains99/99 with an identical18-byte post-call tail at target
499DF8/499E0E and native80AA64/80AA7A. Actual first-World pointers across19
witnesses retain12/14 distinct slots:822 health targetF+190/sourceF+1A0 and
900 completed sequence0 targetF+164/sourceF+104 remain different. These
pointers do not prove effects after returning opaque World calls.

The final formal rebuild after ledger edits has COFF SHA256
`94e2457eed11fa03ead127117d4eada53d2e12b7a96a8f485e9f114532d35f28`.
Only timestamp offsets4,5 differ from frozen82fee43c; all other
object bytes are identical. Root/helper canonical hashes remain343089b7/
ad12b782. Native receipts pin the frozen tested container rather than this
later timestamp. The mixed comparison has the expected nonzero root result,
while the accepted66-byte helper remains exact.

## Receipts and next work

Receipts/controls remain under `build/reimu-object-fade-order-20261020`,
private recipes in the matching `.analysis` scope. All nine primary
database hashes remain unchanged; no Ghidra process or metadata write is used.
IDA's wrong executable supplies no semantics. No unrelated/aggregate cold
replay or new authored-byte percentage is claimed.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-reimu-object-action-state --compare --json
# Expected mixed comparison: root496540 mismatch+31; helper4963A0 exact66/66.
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-fade-order.py build/match-units/GptWeb_ReimuObjectActionState.obj --output build/reimu-object-fade-order-20261020/fade-replay.json
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-999-tail.py build/match-units/GptWeb_ReimuObjectActionState.obj --output build/reimu-object-fade-order-20261020/999-replay.json
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-scalar-actions.py build/match-units/GptWeb_ReimuObjectActionState.obj --final-actions --output-dir build/reimu-object-fade-order-20261020/full-replay
python3 scripts/check-match-literals.py --require-target
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Continue remaining RET ownership and source/register/TU lifetimes while
preserving the850/853/854,999,869/901 and801/852 proofs. Buffer slots822
health and900 completed sequence0 remain leads. Returning opaque graphs,
arbitrary aliases/resources/vtables, nonnull rendering, unmasked exceptions
and48 terrain nonfinite hardware contexts remain open. Preserve Fighter478FA0
and initializer4A1CE0. No standalone-root match or LTCG impossibility is claimed.
