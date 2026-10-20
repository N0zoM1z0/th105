# ReimuObject900 selected-value producer and store evidence

> Historical experiment record. Its pins, selected source and next steps apply
> to that checkpoint. Use [the current handoff](RE_HANDOFF.md) and
> [evidence index](REIMU_OBJECT_EVIDENCE.md) for current state and ABI limits.

This continues the [retiring-request checkpoint](REIMU_OBJECT_900_FLOW_2026_10_20.md)
inside authored root496540. Original Japanese TH10.5 v1.06a remains pinned to
SHA256 `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
No new implementation is selected in this batch. The73370b96 CPP, header,
compiler profile, bindings, ownership manifest and exact ledger are unchanged.

The complete46138-byte owned-extent comparison still fails at49655F/+31.
It includes46128 owned instruction bytes and10 alignment bytes through4A197A;
the39853-byte main-span candidate remains provisional. No action interval is
promoted to a compiler boundary. No root exact or authored-byte credit is added.

Current selected source/artifact pins are superseded by the [shared World checkpoint](REIMU_OBJECT_SHARED_WORLD_2026_10_20.md). Its independently supported cross-action lifetimes also close900 shared-store/direct-producer conditions. Local negative controls below remain phase-scoped evidence.

## Observed target requirement

Raw900 `[49C9F5,49CEC2)` remains1229 bytes/289 instructions, SHA256
`1755ac682f0c7af76eca0b7ef8d3a247efb855a85b94d53e7546f00378b2e28e`.
The four-sequence switch and three distinct retiring request buffers retain
the preceding observations. This batch focuses on the counter40 request's
fourth word. Let F be ESP after the fixed allocation and four saved registers.

| Selector | Value | Literal load |
| --- | --- | --- |
|3|50|49CAD8, float6C3D74|
|2|25|49CAE5, float6C3B3C|
|1|15|49CAF2, float6C3EA0|
|0|8|49CAFE, float6C2874|

All valid paths carry ST0 to one `FSTP dword [F+170]` at49CB04. They do not
store/reload a temporary before that packet store. Invalid selectors take
49CAFC ->49CB0B, skipping the fourth-word store. As before, source equality is
not asserted for an uninitialized fourth word outside the valid selector domain.

The selected predecessor emits four packet stores806182/8061A5/8061C8/8061E3
at F+110. Their preceding root floating operations are direct loads of the
correct float literals. Thus the earlier thirteen-node call graph and concrete
packet equality did not close this physical producer/store requirement.

## Actual write observations and stronger audit

`scripts/audit-reimu-object-900-flow.py` now reports schema v2. Its twelve
inputs are unchanged, SHA256
`1cdacb680ac94507940d054018043be6304f6ebc0a13c92c99fcb8a436dad1b0`:
ten target/source prefixes, including all four valid selectors, and two
target-only invalid selectors. It observes actual stack writes, preserving
the existing write-range guards, and identifies writes to the real packet's
fourth word from its pointer/count at the first World entry.

For each such write it records the preceding root floating operation. A root
CALL is a barrier, so a helper return cannot silently be classified as a direct
literal producer. The target must show one49CB04 write per valid case, direct
float literal producers at the four reviewed addresses, and no fourth-word
write in either invalid target case. Source checks separately report:

* Whether all valid cases use one physical packet FSTP.
* Whether its preceding root floating operation is a direct four-byte literal
  load matching the corresponding target producer.
* All previous prefix, packet, Sin/Cos order, four sequence call graphs and
  joint thirteen-node physical-sharing checks.

Only their conjunction accepts the scoped result. Branch predicates, other
input states, arbitrary aliases/resources, physical RET identity, returning
opaque effects and exact root bytes remain outside that conclusion.
Object-only reports retain `build_provenance_verified=false`; private source
hashes, COFF hashes and formal build receipts are distinct evidence.

The unchanged selected source now deliberately returns `rejected` under v2:
all ten prefixes and all four/joint graphs pass, but it has four packet-store
PCs. This is an exposed residual, not a new runtime failure. A stronger negative
control has one packet-store PC and also passes every earlier check, yet its
preceding load comes from a float temporary. A one-store counter alone would
incorrectly accept that different producer shape.

## Source and compiler controls

Eight controls test genuine scalar/request lifetimes or an explicit compiler
setting while preserving the declared ABI. No fake local, padding, assembly,
copied instructions or return is used.
Seven are fully relocation-qualified under the unchanged VC8 profile; the
function precision control below is explicitly unqualified.

| Shape | Canonical bytes / SHA256 prefix | Packet sites | Direct float producer | v2 |
| --- | --- | --- | --- | --- |
|Selected predecessor|45020 /4a3f8c39|4|yes|reject|
|Real float, invalid-path goto, common assignment|44956 /8b6f74f2|1|no|reject|
|Real float plus validity flag|44956 /8b6f74f2|1|no|reject|
|Guarded conditional expression|45020 /a2129a5c|4|yes|reject|
|Real double plus final float conversion|45020 /a49c69e7|4|no, qword loads|reject|
|Select real request pointer/count earlier|44988 /17162138|4|yes|reject|
|Earlier request selection plus float join|45020 /34b39d40|4|no|reject|
|Short-circuit scalar selection|44972 /47a89997|1|no|reject|
|Function precise-off control|unqualified|not claimed|not claimed|no canonical result|

All seven qualified experiments retain438h, first31 bytes,399 direct CALLs
to25 callees,59 RETs and0/43 identical owner diagnostics. Their ten concrete
prefixes, four mode graphs and joint13/13 graph pass. They all fail at least
one of the additional producer/store conditions. These are phase-scoped
counterexamples, not proof that another supported source/TU context is impossible.

The float/goto and validity-flag sources produce identical complete canonical
payloads. Their common packet FSTP8061A9 is preceded by:

```text
8061A1  FSTP dword [F+18]
8061A5  FLD  dword [F+18]
8061A9  FSTP dword [F+444]
```

Their packet also moves from F+104 to F+438. The target has no such intermediate
rounding copy or this packet placement. The discarded float source is
`001e1aafd47975c7345efafb7f9ab67033e36a38ec6f29afd88dd721de69bee6`,
canonical `8b6f74f2126972feb7d874354942b504d0b294f4ad5cd79e65850651957f29dc`,
native `db48ff8f5a9829149c8e87b2c099f374a8510adac1236127f9be285117b87801`.
It has275 physical900 instructions/1159 bytes and root metadata44088/868.
A smaller payload and shared final store do not justify selecting it.

The double experiment follows this new spill evidence. It removes that
particular float-copy shape but promotes literal loads to qword and restores
four packet stores, also contradicting the target. Early request selection
changes real pointer/count lifetimes without invented dependencies; both
controls still fail. Short-circuit selection writes the float temporary even
on intermediate rejected alternatives and reloads it before the final packet
store. These facts are observed in actual code and the write/producer traces.

The whole-function `float_control(precise,off,push)` experiment is limited to a
private source control. Compilation succeeds, but canonical replay rejects
new absolute literal `__real@3f266666` (float0.65). No binding is guessed or
added. Its canonical size, producer equivalence and native behavior are not
claimed. The [VC8 reference route](VC8_REFERENCE.md) remains external
corroboration; neither that documentation nor this control proves TH105's
original per-function profile or an LTCG stop condition.

## Validation and preserved source

The discarded float candidate passes0/5640 focused upper-state/900-gates/
emission/bounds/animation inputs, SHA256
`8f5ff73135872f79b5afe39207c3188773e6ad34412a3193e3f46256ebfb4494`:
4570 real RETs/1070 first World entries,852 target/786 source instructions
visited. This validates those prefixes, not the differing instruction shape.
Its preliminary901/804/selector/helper regressions pass. Once the temporary
spill is observed, its active full-matrix process is explicitly canceled and
observed terminal; **no completed full-input result is claimed for it**.
The cancellation is a deliberate candidate rejection, not an observation timeout.

The selected CPP is restored byte-for-byte to the preceding checkpoint:

| Artifact | SHA256 |
| --- | --- |
|Selected CRLF CPP|`73370b96caebc5f5b59d32412ef31ff6f364905930eadaeb389e21a0bf0ff6c4`|
|Unchanged header|`348794fa1087721b1444eacdc1d421355b6b8f76f656bd216b41261221876adc`|
|Canonical45020 at496540|`4a3f8c39fab18e7a3fa8dbbc71fa1d0f370312e11f949adb78e0c9b74a4789f9`|
|Native45020 at800000|`373934e1e3bcc34286151a06c27d44667e13fdc7767f72f9bfdb7f96a1f4f080`|
|Fresh final formal COFF|`52e1ed53cbd8f2a3e774222dac358a8e47e12aacc5a27394bab6ffea9ab460e8`|

Fresh final formal build and native export are byte-identical to the starting
payload; the final v2 report confirms the same admitted prefix/call equality
and rejects the remaining four-store shape. Root metadata44152/868,10248
instructions,399 CALLs/25 callees,59 RETs and0/43 owner diagnostics remain.
Target totals remain10670 instructions,404 CALLs/25 callees and68 RETs.
World99 target/104 source and animation22/12 remain the only callee-count gaps;
these do not quantify missing behavior or confer partial exact credit.

The preceding selected source's0/133192 and manager0/3744 receipts remain
historical evidence for the byte-identical payload. They are not presented as
new replays. No header/layout, profile, relocation, partition or other compiled
input changes invalidate another accepted object. No routine cold aggregate
replay or percentage is asserted.

## Analysis provenance and reproduction

Fresh target/ledger preflight, raw complete-root closure and callee census
qualify the work. IDA metadata identifies a different image and supplies no
semantics. One direct read-only/no-analysis Ghidra run attests identity, entry,
mapped text, root and vtable but times out decompiling the root. Its tool
return code alone is not accepted: missing sentinel/error rejects the receipt.
After terminal cleanup, a second run independently re-attests the same facts
and successfully exports only the bounded49CAAF..49CB3F instruction listing.
Neither failed pseudocode nor old local names are used as evidence. Both runs
preserve all nine primary database hashes and remove their temporary aliases.
Only one Ghidra process runs at a time under CPU0/nice10/128MiB heap.

Reports, COFFs and private source controls stay below
`build/reimu-object-900-selector-store-20261020`; private drivers stay below
`.analysis/reimu-object-900-selector-store-20261020`. Redundant canonical
copies and unselected full-root owner diffs can be removed while retaining
900-scoped facts and reproducible recipes. No generated reports, executables,
compiler installs, credentials or analysis databases are committed.

```bash
python3 scripts/verify-target.py
python3 scripts/check-ida-mcp.py
python3 scripts/report-reconstruction-status.py --summary
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-update-target.py --json
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-reimu-object-action-state --compare --json
# Expected canonical mismatch at49655F across all46138 physical bytes.
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-900-flow.py build/match-units/GptWeb_ReimuObjectActionState.obj --output build/reimu-object-900-selector-store-20261020/current-flow.json
# Expected v2 rejection: admitted prefixes/call graphs pass, four packet stores remain.
python3 scripts/check-match-literals.py --require-target
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Next seek independently supported producer/lifetime or compiler-context evidence,
or recover remaining cross-action World/animation/RET sharing. Do not continue
combinatorial source spelling or select an intermediate packet metric. Original
source/TU/profile/LTCG context, stack placement, returning opaque graphs,
arbitrary aliases/resources, nonnull rendering and unmasked exceptions remain
open. Terrain retains48 hardware-unqualified nonfinite contexts and its measured
SSE conversion gap. Preserve Fighter478FA0 and initializer4A1CE0 checkpoints.
