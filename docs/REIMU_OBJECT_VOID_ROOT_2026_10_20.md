# ReimuObject void update and complete-extent comparison

> Historical experiment record. Its pins, selected source and next steps apply
> to that checkpoint. Use [the current handoff](RE_HANDOFF.md) and
> [evidence index](REIMU_OBJECT_EVIDENCE.md) for current state and ABI limits.

The selected source and frame investigation have since advanced in the
[selector-family checkpoint](REIMU_OBJECT_SELECTOR_FAMILIES_2026_10_20.md).
The hashes and results below describe this earlier void-conversion checkpoint.

This supersedes the selected boolean method in [the final-action checkpoint](REIMU_OBJECT_FINAL_ACTIONS_2026_10_20.md).
The target remains original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The authored root is496540, with46128 owned instruction bytes and a46138-byte
physical envelope ending exclusively at4A197A. Its provisional39853-byte main
span in `functions.csv` is preserved. No alignment or remote chunk is promoted
into a fake standalone source function.

## ABI observations and source selection

**Observed:** ReimuObject's primary table6C40A4 has496540 at cell6C40CC/+28.
The accepted76-byte `CharacterObject_update_for_manager @4937D0` loads that
slot and calls it at49380A with the object in ECX. At49380C it loads the
secondary object, tests that pointer and returns or tail-jumps to4309F0; it
never consumes the update's EAX. The root uses ECX as its receiver, has no
stack arguments and its68 physical returns have RET0 cleanup. Raw complete
CFG closure still finds10670 instructions,22 switches and404 actual direct
CALLs to25 targets. The E8 inside49C35A's FLD1 is still not a call.

**Source inference:** the complete41-arm/default source now defines
`virtual void ReimuObjectActionStateStagingView::dispatch_action_state()`.
The historical filename/view name is retained. An opaque unused slot24
precedes the update, preserving all earlier slots and the388-byte field view.
Slot24 points at45C1F0 in the target; its unused source marker does not claim
that callee's signature or implementation. Every former true coverage return
is now a bare void return. The original update remains separate from the
already accepted helper implementations.

A genuine placement-construction probe, compiled separately from the selected
root, emits an11-entry source vtable. Its DIR32 at offset28 references the
actual `@@UAEXXZ` update symbol; preceding entries occupy00..24. This checks
compiler layout without adding an unused constructor, vtable or shaping code
to the root TU. Field offsets and sizeof388 remain compile-time assertions.

The public native auditor selects the void symbol and drops only its obsolete
boolean-EAX assertion. RET address/stack, callee-saved registers, x87 stack and
control word, object/owner/parameter bytes, helper traces and actual call-entry
arguments retain their checks. `implemented.csv` and the root's `source_file`/
status now select the complete source; `matches.csv` and `remote_exact` are
unchanged. This records source presence and a supported ABI, not exact bytes.

## Strict comparison of the complete physical envelope

The new `owned_extent = true` function contract forwards `--owned-extent` to
`compare-function.py`. It loads the existing byte-ownership ledger with
`require_bytes=True`, checks the current target and inventory, then compares
entry through the final remote byte. It does not concatenate chunks, mask
holes, shift edges, ignore alignment or inflate the provisional main span.
For496540 the comparison is46138 bytes:46128 owned plus10 known alignment
bytes. The generic report calls the latter `non_owned_bytes_compared` rather
than inferring ownership from the gap's contents.

An absent/unverified ownership record cannot fall back to the main span.
The new mode and `contiguous_span` are mutually exclusive. Linked-PE profiles
continue to reject this unsupported surface. Ordinary COFF comparisons retain
their previous boundaries and relocation rules. Owned-extent build provenance
also hashes `functions.csv`, `function-byte-ownership.toml` and its validator;
the comparison report separately pins the ownership manifest SHA256.

Nine focused tests exercise a remote REL32 beyond a four-byte main window,
remote-byte and intervening-alignment mismatches, absent ownership, incompatible
boundary modes, manifest type/range checks and provenance inputs. In the
counterexample the main-only comparison passes while the remote-byte mutation
fails at+14 under the complete mode. These synthetic tests grant no game-byte
credit. The linked-contract rejection test also covers the new flag.

The new `gpt-web-reimu-object-action-state` probe uses the original VC8 SP1 O2
profile and GS setting,25 explicit typed external-call bindings and121 external
DIR32 bindings. Twenty previously absent real literals receive function-scoped
allowlist keys. Their widths/values, initialized COFF bytes, unique target-root
operands and canonical PE bytes are checked; existing keys/addresses are not
changed. Floating relocation audit passes349 ledger literals/775 explicit
mappings and1124 target references. Adding the scoped keys leaves the native
replay byte-for-byte unchanged.

The fresh full comparison is **mismatch**, with no unresolved relocation or
waiver:

| Property | Result |
| --- | --- |
|Target physical extent|46138 bytes /`399e56d3f1373e76381cafb17e4984845fdb1f680dc0737f864229b52f84e31d`|
|Source section tail, including switch metadata|41480 bytes|
|Canonical replay at496540|`29adf4576063df15714a7f7594fd034479060e45730e1a2e5a99a918ed77aa4d`|
|First strict difference|+0 /496540, target81/source55|
|Target entry|`SUB ESP,438h; PUSH EBX; PUSH EBP`|
|Source entry|`PUSH EBP; MOV EBP,ESP; AND ESP,-8; SUB ESP,388h`|
|Source final RET end /metadata start|40610 /40612, with two alignment bytes between|
|Source metadata length|868 bytes|
|Target/source direct CALLs|404 /347, both25 targets|
|Target/source physical RETs|68 /61|
|Physical owner diagnostics|0/43 instruction/edge-identical owners|

Source counts come from the decoded prefix through metadata_start and include
its two-byte compiler alignment instruction. They are not a source CFG or
reachability proof. The mapper's historical405 E8/26-target counts remain raw
byte diagnostics. Source presence, matching callee sets, metadata length and
owner counts provide no partial exact credit.

Two natural private source-shape controls remain unselected. Replacing999's
named double projection with the same binary64 expression shortens the void
replay to41472/a0aa8547 but leaves the aligned-frame prologue. Expanding142
`goto retire` edges into in-place decrement/return blocks shortens the section
tail to41348/3aa20db5 and still gives0/43 owner diagnostics and a+0 mismatch.
Neither a size change nor an equivalent expression identifies the original
frame, return partition or TU/LTCG behavior. No inert locals, assembly, copied
target bytes, register forcing or artificial ABI is introduced.

## Native prefixes and manager-entry integration

The void source passes0/133192 unchanged public inputs, input SHA256
`f46a849ff57f64bb16e77fd0e28f7f51eee7238501c04049add99e7f77fc3b8b`.
Actual endpoints remain119356 RETs,10422 unparented/1151 owned/472 parented
entries,915 secondary-setup,26 effect,114 wave,112 CRT errno and624 CRT
quiet-NaN entries.9215 target and8225 source instructions are visited. The
source replay at800000 is41480/45780960, exactly reproducing the preceding
private void preparation despite its new genuine virtual declaration.

A separate4200-input integration probe starts at the original4937D0 wrapper,
not directly at the update. Controlled receiver data sets this+16C to the owner,
this+186 and owner+48C to0, and this+338 to null. It supplies an input vtable
clone at resource+E800, copying the original eleven cells and binding cell28
to the target or compiled entry. Both actors store the same clone address;
no target code or original vtable byte is patched. The actual wrapper, update
and helpers execute, including the wrapper's real post-update/RET path.

This passes0/4200 high-animation/final-state inputs:4156 real wrapper RETs and44
first world entries; input SHA256
`fff4c44d1164561a14ae08befbaea5c268bef7c4e8d41b62c8c491c636ab6d7b`.
The wrapper is present4200 times in each helper trace. These controlled flags,
null-secondary paths and cloned input table do not establish arbitrary manager
state or secondary rendering behavior. No returning world result is fabricated.
The private probe recipe and separate constructor emission remain under the
checkpoint's analysis/build directories.

Both808/812 conditional caller proofs and the orientation0/400, alpha0/1170 and
terrain288 observers pass on the new replay. Terrain retains240 finite equal
prefixes and48 hardware-unqualified nonfinite contexts. The measured Unicorn
SSE NaN conversion gap and runtime6FA894 adjacent-word behavior remain explicit.
No exceptional hardware or unmasked-floating closure is claimed.

Thirty-one previously accepted functions replay exact:18 in stage geometry,
animation virtuals, object runtime and atan2, plus13 accepted members of the
manager-runtime probe. That mixed manager unit intentionally returns1 because
its already nonexact58BE10 parent still differs at+165 in erase registers;
two unaccepted compiler thunk comparisons are kept separate. The accepted
4937D0 wrapper is76/76. No accepted function regresses and no thunk/library
result enters authored progress.

## Identity, provenance and remaining work

Fresh target/status/tracking, full raw CFG and shared-callee checks precede the
conversion. A fresh boolean baseline reproduces41336/b6ef0db2 and passes0/360
high-animation inputs. IDA metadata still identifies another image and supplies
no semantic evidence. Direct read-only/no-analysis Ghidra independently attests
file/import hash, entry, full mapped text, root and all eleven vtable cells
under a128MiB heap cap, CPU0 and nice10. All nine primary DB hashes remain
unchanged and the temporary alias is removed.

Ghidra's private caller hypothesis guesses a fastcall spelling and expands the
4309F0 tail beyond the76-byte wrapper, with type-propagation warnings. Neither
that expansion nor inferred types are accepted boundaries/ABI facts. Raw
instructions, the accepted wrapper source/comparison and independent source
vtable emission establish the bounded ABI contract used here.

| Artifact | SHA256 |
| --- | --- |
|Selected CRLF CPP|`810381743cecde1813441b7ae2c2d32339530697aa239e450ed28d48d6aa10bb`|
|Selected CRLF header|`348794fa1087721b1444eacdc1d421355b6b8f76f656bd216b41261221876adc`|
|Native auditor|`6d3dfbdf984db55dd29bae2648c383df071bdd1f29efced1f3d790fd368b8d70`|
|Native replay at800000|`45780960252921793c5b4574f7c1cd1dd31395dbb819a989d5571a854f853816`|
|Ownership ledger|`e6e9d4e0321a468f7e38e2abf7cc8e0f224132f0230c5d4814e3757792be8d08`|

The formal unit writes a fresh compiler/input/object provenance receipt. Native
object-only audits retain `build_provenance_verified=false`; file pins and
observed fresh builds are separate evidence. Reports/objects/constructor and
shape controls stay under `build/reimu-object-void-root-20261020`; private
recipes and Ghidra scripts stay under `.analysis/reimu-object-void-root-20261020`.
No executable, database, compiler install or generated report is committed.

```bash
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-update-target.py --json
python3 scripts/build.py --check
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-reimu-object-action-state --compare --json
# Expected nonexact result; compare all46138 bytes, not only the main span.
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-scalar-actions.py build/match-units/GptWeb_ReimuObjectActionState.obj --final-actions --output-dir build/reimu-object-void-root-20261020/positive
python3 -m unittest discover -s tests -p test_owned_extent_comparison.py -v
python3 scripts/check-match-literals.py --require-target
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Next investigate target/source physical case/return sharing, the explicit
selector-family emission sites and the aligned-frame cause using raw owned
instructions and whole-extent comparisons. The remaining57 direct call-site
and seven RET differences are physical partition evidence, not missing-runtime
behavior counts or an LTCG impossibility proof. Returning world/setup/wave/
event/CRT graphs, arbitrary aliases/resources, nonnull rendering, unmasked
exceptions, original source spelling/hierarchy/TU and exact root bytes remain
open. Preserve Fighter478FA0 and initializer4A1CE0 checkpoints. No new exact
credit, cold aggregate replay or aggregate percentage is asserted.
