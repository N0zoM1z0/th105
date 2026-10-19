# Reimu300/320 declaration and value-flow controls

## Target facts and unchanged source checkpoint

This is bounded work inside `Reimu_dispatch_action_state_vslot28 @478FA0`,
not a new compiler boundary. Only the original Japanese v1.06a executable is
used, SHA256 `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The81550-byte callable has SHA256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
The root remains unclassified/declaration-only. No candidate from this batch
is selected, and no implemented/matches row or exact credit is added.

**Observed:**300 starts47CBBD and320 starts47D96A. Each has its own landing
CALL473DD0, directional gate CALL478EE0 and advance CALL4351C0. The first95
bytes/26 instructions have the same register, width, stack and callee roles
after expressing local relative branches as offsets and the common return
as a separate destination role. This normalization is diagnostic, not a
partial canonical match. Both prefixes use the float home `[esp+24h]`.

Their following virtual setter calls differ:300 calls EDX at47CC29;
320 calls EAX at47D9DA. Both join the predicate at47CC2B. The event CALL47CC4B
and RET47CC5E are shared by300/320/321. The300/320 event argument27 is pushed
at47CC47;321 pushes28 at47DA66 and jumps47DA68->47CC49, bypassing that push.
The current source instead folds300/320's prefix and advance/setter path.

A fresh build reproduces generated source
`7650c8d3b96683b69ef596d6eac0793ed8350ae24a7840c608a629e9929d43cf`
and complete canonical payload
`fbc0293d5e7ab9b39aca3d83c4d044ce7603d2e28d7961d2ff7736ef3f360177`.
This batch's baseline object is
`ab500d122771cea4eb49d2e066f05ef728c9115e9928c3d881ad5b784fb37e9d`.
It retains1236 equal complete membership/multiplicity checks and all153 RET
partitions. Payload/prefix/frame remain82808/81436/570h, with first strict
target difference+541/4791BD. Current genuine checkpoint pins in the
[616 evidence](REIMU_616_SHARED_COMPLETION_2026_10_20.md) remain unchanged.

## Twenty controls, none selected

All builds run serially with the existing VC8 profile at CPU0/nice10 and
qualify under both complete object auditors. All preserve the preceding1236
equal group checks and all RET partitions. There are11 byte-neutral controls
and nine changed controls producing six other complete payloads:

| Controls | Count | Payload SHA prefix | Bytes / code prefix | Instructions | New equal groups |
| --- | --- | --- | --- | --- | --- |
|Byte gate result, nested gate, assignment expression, byte completion, both arms through runtime interface, short timer/frame locals, narrowed int completion|7|`fbc0293d`|82808 /81436|20245|0|
|Inherited virtual prefix alone, setter through prefix in320, both setters through prefix, used inline prefix setter in320|4|`fbc0293d`|82808 /81436|20245|0|
|Wide gate result; wide carrier with narrowed byte-field comparison|2|`d0c5ad40`|82824 /81452|20251|4|
|Boolean gate result|1|`a5c2aa7f`|82824 /81452|20252|4|
|Wide carrier with narrowed branch test|1|`f83db3df`|82856 /81484|20256|4|
|Wide carrier with both uses narrowed|1|`6dbd9cbb`|82856 /81484|20256|4|
|Used velocity reference or pointer|2|`266ccb65`|82872 /81500|20259|4|
|Only300 or only320 through the existing runtime interface|2|`8bae74f3`|82920 /81548|20274|5|

The value-flow variants can separate landing and directional-gate sites, but
still merge advance and slot8. Reviewed changed prefixes also alter target
instruction roles or float homes: wide/bool/mixed320 uses `[esp+20h]`, while
the reference control introduces `[esp+14h]` and `[esp+20h]`. Equal or improved
site partitions do not establish local instruction equality.

**Corroboration:**raw target RTTI at COL6D9DB8, referenced by6C4128, places
Reimu, CharacterEx, Character, AttackObject and AnimationObject at mdisp0;
AnimationObjectBase is4 and Environment is130h. This supports testing a base
interface at offset0, without recovering the complete original class.
The private six-method polymorphic prefix preserves the existing virtual
signatures/order and derived field assertions. All four inherited-interface
controls are byte-neutral. No new base class or cast is adopted publicly.

## Existing provider identity exposes a misleading improvement

The runtime controls use the actual `CharacterObjectRuntime` declaration and
source, not a new external prototype. Fresh focused comparison of
`cross-v106a-character-object-runtime` passes all three existing functions
at4351C0/4963A0/64CD00. The62-byte4351C0 method is thiscall, no arguments,
unsigned-char return. Existing genuine closure aliases already associate the
prelude and CharacterEx declarations with this provider.

**Experiment:**using that declaration in only one arm prevents complete
folding; using it in both arms folds the code again. Both one-arm controls
produce the same full payload. The one-arm source retains all old group
checks and gains five, and moves the first strict mismatch to+578/4791E2.
However, action320 now reaches **two physical advance CALL sites**, versus
one in both target and baseline. The clamp arm calls4351C0 at47D9D1 and jumps
to47CC20; the other arm calls at47D9DF and joins the same block. These sites
are mutually exclusive. The slot8 call is still merged300/320. This candidate
therefore regresses a previously correct constraint and is rejected.

A private genuine source/CRT closure reproduces the same82920-byte
`8bae74f3e4f90a1538aa923b7672c4dd2c0dbb541c0ac0f4e6108ce3c65f7e18`
payload. All2478 replayed fields agree, with1282 HIGHLOWs,32 direct callee
identities,11 switches and15 request-buffer contracts. Eight linker alignment
bytes remain separate; the five existing nonexact provider diagnostics remain
nonexact. The image is not executed. Genuine receipt SHA256 is
`a677a501dff20c4eafdd6f3fbd77c40f596a63ebb54d38a0ed95f0c1694f32dd`.
Linking does not remove the unwanted advance-site cloning.

Native emulation of the qualified ordinary root passes0/989 cases, all989
return natively; target and candidate each execute971 actual advance entries.
Input SHA256 is
`cf8b769e3bcd17cc6c72ebcfb23c7166a65717e02be079bf1c65ba4d2f7e1fde`.
This explains why the extra mutually exclusive site is not a double execution.
It also demonstrates that these behavioral checks and a later first mismatch
do not justify source selection. Original declaration identities, source/IR
context and TU ownership remain unknown; no LTCG impossibility is established.

## Preserve counts as well as positive groups

`scripts/audit-reimu-call-sharing.py` now accepts `--baseline-object`.
It freshly qualifies both objects, requires the same target SHA/action/site
evidence, then compares previously equal positive target membership groups
and physical/per-action site counts. Counts include zero-target checks over
the finite union of observed domains. Empty membership sites remain in
physical totals. A regression prints its diagnostic report and exits1;
qualification failure exits2. Existing invocations without a baseline retain
their behavior. This guard makes no dynamic-count, feasibility or exact claim.

| Fresh integration control | Prior groups / counts | Lost groups / counts | New groups | Result |
| --- | --- | --- | --- | --- |
|Baseline versus itself|1236 /4897|0 /0|0|Preserved|
|Wide gate320 versus baseline|1236 /4897|0 /0|4|Preserved, still nonexact/unselected|
|One-arm runtime320 versus baseline|1236 /4897|0 /1|5|Rejected;4351C0 action320 count1->2|

Four focused regression tests cover this actual misleading-improvement shape,
a valid split, an extra site outside nondefault-action reach and changed
target identity/site evidence. The complete module passes14 tests.

## Direct300 source-context follow-up

A fresh current-source build repeats7650c8d3/fbc0293d before testing three
outer-control alternatives. This is still one81550-byte root, not a new
function at the action entry. Raw target4791DB compares the promoted action
against300, then uses JG4791E0 to the middle dispatcher and JE4791E6 to the
direct300 body. Its two independently decoded300/320 prefixes still have the
same95-byte/26-instruction roles and ESP+24 float home.

1. Moving300 outside the low `switch`, inside the existing `<=300` guard,
   preserves all1236 equal groups and4897 equal physical/per-action count
   checks, but adds none. The root remains82808/prefix81436/frame570h with
   20245 reachable source instructions. Canonical payload becomes
   `32c2026ed1cc1113c9d649d1959ba6750ae66618f3bd1b66939200ae9c74e051`.
   The common/default body moves before300, changing placement and relative
   operands.300 and320 still alias source47CBD0. Both first26-instruction
   prefix diagnostics remain equal; neither gains an independent physical
   copy. The changed hash is not a matching improvement.
2. Moving300 after a separate `<300` low region compiles, but the inspector
   rejects it with `direct action equality edge is absent or ambiguous`.
   COFF disassembly confirms an initial JGE, instead of the target JG/JE
   decision. No inspector rule is weakened, and no canonical, count,
   execution or exactness result is assigned to this unqualified object.
3. Reading a real short action selector for the middle switch, while retaining
   its existing outer guard, produces canonical
   `9ffb1d93230e1dc4be67988c58311f920316904f4515b8008b757aff54c49005`.
   It retains all1236/4897 old checks, adds none, and still aliases300/320.
   Code/payload/frame and reachable instruction count remain unchanged.

Both qualified changed controls still first differ at+541/4791BD. Neither is
selected or executed. These results exclude these tested dispatcher spellings
as fixes, without proving an original source partition, declaration identity
or LTCG requirement. No game source/header, profile, binding, ledger or
accepted unit input changes. Hash-attested raw PE observations require no
database write; the failed IDA preflight is not used for semantics.

Recipes/receipts are under `.analysis/reimu-300-source-context-20261020/` and
`build/reimu-300-source-context-20261020/`. The summary distinguishes the fresh
baseline, two qualified negatives and one compiled rejection. Six redundant
generated copies (1338567 bytes) are removed after their hashes are recorded;
baseline and the direct-in-low input remain for replay. The prior twenty
controls above retain their original input and validation scope.

## Database safety, reproduction and retained products

Direct read-only Ghidra re-attests raw/imported identity, base/entry,
x86/windows target, mapped text, whole callable hash and vtable6C4154->478FA0.
It decodes300/320/321 and4351C0 and verifies the two target advance calls,
distinct EDX/EAX virtual calls and321's shared-event edge. All nine primary
database files remain unchanged; the temporary alias is removed. RTTI above
is separately decoded from the hash-attested PE. IDA's failed preflight blocks
its use; no IDA semantics or factory adapter is used.

Private recipes are in `.analysis/reimu-300320-identity-20261020/`; reports
and retained inputs are in `build/reimu-300320-identity-20261020/`. The private
runtime binding is installed only while its serial wrapper runs, then restored
byte-for-byte. The public binding SHA remains
`d19770dd14b9e0e4fc6c8064d7d94cf05804ea4ab3d5a46a7e3e5af864df863c`.

```bash
taskset -c 0 nice -n 10 python3 -B .analysis/reimu-300320-identity-20261020/probe.py gatewide320 runtime320 runtime-both
taskset -c 0 nice -n 10 python3 -B scripts/audit-reimu-call-sharing.py build/reimu-300320-identity-20261020/gatewide320/candidate.obj --baseline-object build/reimu-300320-identity-20261020/baseline/candidate.obj
taskset -c 0 nice -n 10 python3 -B .analysis/reimu-300320-identity-20261020/linked.py replay
python3 -m unittest discover -s tests -p test_reimu_call_sharing.py
```

`summary.json` retains hashes/results for all21 builds. Redundant generated
sources/objects are removed after recording them; the recipe regenerates
controls. Baseline, wide-gate and runtime inputs remain for direct replay.
The current selected root, public genuine closure, source/layout/bindings and
progress ledgers remain unchanged. The remaining300/320 prefix ownership,
616 effect preparation,720 float homes and full-root/world semantics still
require evidence. No aggregate cold replay or percentage claim is made.
