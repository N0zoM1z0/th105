# CGage render context: one multiplication pair remains

`CGage_render @41B3F0` remains **nonexact**. A live-height field reference now
restores the complete41B549/41B54F multiplication pair. The selected source is
still1010 bytes/323 instructions, but now321 instructions are identical to
the target. Only the fraction/height load-order pair remains different; the
first unequal byte moves from41B54A/+15A to41B580/+190. No exact or partial
match credit is added.

Only original Japanese TH10.5 v1.06a is used, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Fresh target/status/tracking checks pass. IDA still fails target attestation
with10350095... and supplies no semantic evidence. No analysis database or
target instruction is changed. The [previous source checkpoint](GAGE_RENDER_2026_10_20.md)
retains the full boundary, field and behavior recovery.

## Target facts and selected change

The complete target remains `[41B3F0,41B7E2)`, body SHA256
`67b9378f09e92621dad4bba0410f9aa4905bf24a8a73dd3e4440489bf860eedb`.
Its323 instructions close the local control-flow graph with two RET8 exits;
fourteen following INT3 bytes are excluded. RTTI-owned CGage vtable6D6A38
cell6D6A54/+1C owns this entry. No boundary, origin, field offset or call target
changes in this checkpoint.

Mode1 reads float height+7C twice, separated by vertex publications. The
selected source binds `const float &height = height_7c` at case entry and uses
that actual field in both products. It introduces no numeric copy, new object
storage, added stack home, forced register or fabricated operation. Width,
scale, vertex layout and the getter view remain unchanged. Original C++
reference spelling is a hypothesis; the accepted observation is the generated
instruction improvement and preservation of the complete remaining body.

The ordinary float-copy control from the prior checkpoint adds homes/code;
the new double-copy control similarly adds a qword home and changes the frame
from10h to14h. Those copied values are not selected. Pointer-to-height access
reproduces the selected reference body. Moving the reference to its first
arithmetic use instead reproduces the old body. This narrows the source
lifetime/context question without proving a unique original declaration.

| Target | Selected source |
| --- | --- |
|41B57F `fld st(3)`|41B57F `fld dword ptr [esi+7C]`|
|41B581 `fmul dword ptr [esi+7C]`|41B582 `fmul st(4)`|

These two instructions occupy the same five-byte range. Exactly four bytes,
at41B580..41B583, remain unequal. Every other instruction and address agrees,
including all branches, vertex/UV publications, rotation, real calls and the
complete graphics tail. This is a diagnostic comparison, not an alternative
acceptance boundary or a general floating-point equivalence proof.

## Bounded context controls

The fresh baseline reproduces the old1010-byte canonical1c7e7946... body.
The following complete-function controls are retained under
`build/gage-render-context-20261021/`; none changes an accepted shared input.

| Control | Complete source extent / first mismatch | Result |
| --- | --- | --- |
|Getter declaration returns double; caller still stores float|1010 /+15A|Both original vertical pairs remain; two additional mode0 pairs differ. Unselected.|
|Live height reference at case entry|1010 /+190|Selected; only two instructions differ.|
|Height pointer, swapped first factors, fraction reference|1010 /+190|Same whole selected body. No further improvement.|
|Height reference moved to first arithmetic use|1010 /+15A|Same whole old body.|
|Copied double height|1023 /+2|14h frame and extra homes; unselected.|
|Reference to typed width/height pair|1010 /+15A|Six instructions differ, including a new width pair; unselected.|
|Small float-return dimension helper|1032 /+16|Introduces wider rounding/code differences; unselected.|
|Signed negative extent expression|1012 /+16|Different operation stream; unselected.|
|Compound top subtraction, const render with mutable vertex cache, const coordinates|1010 /+190|Same whole selected body. No further improvement.|

The getter control re-examines an important distinction: independently exact
float-return provider source does not prove unique original API spelling.
The caller observes ST0 followed by FSTP m32. Changing its private declaration
to double does not solve the residual and is not selected; accepted providers
46FA50/46FA70 and their binding unit remain unchanged. The qualifier and
helper controls likewise do not establish original declarations or a compiler
limitation. The final operand selection and source/TU context remain open;
there is no standalone-object or LTCG impossibility claim.

## Fresh native prefix evidence

The unchanged public `audit-gage-render-prefix.py` is rerun on the selected
formal object:0 differences in4490 cases,1290 real RET8 completions and3200
stops at the actual texture-binding entry. Actual int/short providers,
orientation lookups and reached CRT instructions execute; no helper result is
substituted. Both sides visit304 of323 root instructions. Ordered writes,
full object bytes, helper arguments, endpoint arguments and the existing
x87/stack/register contract agree. Input pins are unchanged during execution.

Input matrix SHA256 remains
`a9335c55c58e5c3525df3fee417fd9ff03bae2f8c8513e49e280bd1aa2779bb5`.
`selected-native.json` records this source/object/script epoch, fresh target
closure and the canonical+190 diagnostic. Its build-provenance flag remains
false; source-to-object provenance is provided separately by the formal build
receipt. The previous wrong-NaN/wrong-UV negative controls remain historical
calibration of the unchanged audit and are not presented as fresh builds of
this source.

The finite masked-x87 fixtures and native entry stops keep the
[previous audit's scope](GAGE_RENDER_2026_10_20.md#native-prefix-audit-and-negative-controls):
no COM/binder continuation, unmasked exception delivery, arbitrary alias/input
coverage or whole-root equality is proved. The nineteen post-binding
instructions are compared statically, not executed by this audit.

## Pins and focused reproduction

The selected unit remains `gpt-web-gage-render`, VC8 SP1 O2 strict FP, GS off,
with its existing local exception-control pragma. No shared header, compiler
profile, relocation ledger or accepted function changes. The origin rule's
only change is its descriptive evidence text; the existing target witnesses
are replayed with `validate_rule_evidence`. All other rule entries are
unchanged, and no library-anchor or aggregate cold replay is claimed.

| Artifact | SHA256 |
| --- | --- |
|Selected CRLF source|60ce4f3be6c53a7b7bfa6c74b5b1a024fe0764b65ff6b5f6d1c32aa319132356|
|Formal COFF|074cdb38ed189278386927aff1f7d6955c94c35c95ed85fdf6af7261569f5d18|
|Complete canonical source|fa2cc075b86578cc4f121c28aa54d9746ee0dd89701a1a821d8701dee80bea6a|

`baseline-build.json` and `selected-build.json` record the fresh before/after
formal comparisons. `selected-instructions.json` records the whole instruction
diagnostic. Frozen baseline/selected sources and the selected COFF remain in
the build scope; private control recipes are in
`.analysis/gage-render-context-20261021/`.
The thirteen unselected controls are compressed in `unselected-trials.tar.gz`,
with per-file hashes in `unselected-trials-manifest.json`. All59 files are
verified after compression before removing loose copies. Restore that archive
before replaying private generators that consume an earlier control's source.
Frozen baseline/selected sources and the selected COFF stay uncompressed.

```bash
# Expected exit1: first mismatch41B580/+190, complete1010-byte comparison.
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-gage-render --compare --json
taskset -c 0 nice -n 10 python3 scripts/audit-gage-render-prefix.py \
  build/match-units/GptWeb_GageRender.obj \
  --output build/gage-render-context-20261021/reproduced-native.json
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

## Additional product and inheritance controls

The subsequent `build/gage-product-20261021/baseline-build.json` formally
rebuilds the unchanged selected source and confirms the same complete1010-byte
canonicalfa2cc075... body, still nonexact at+190. The selected source and
object are frozen in that scope. Its fresh IDA preflight again fails target
identity, so these controls use only the canonical PE and pinned compiler.

The remaining fraction/height pair is examined through actual product
lifetimes, without introducing inert storage or changing a public input:

| Private source control | Complete source extent / instructions | Result |
| --- | --- | --- |
|Float product local before the final scale/subtraction|1018 /325|Introduces an intermediate float home; unselected.|
|Double product local with explicit promotion|1018 /325|Introduces an intermediate double home; unselected.|
|Double accumulator across the two real products|1034 /329|Adds rounding/homes beyond the target stream; unselected.|
|Full observed zero-offset sprite inheritance, retaining live height reference|1010 /323|Same wholefa2cc075... body and two-instruction residual.|
|Same inheritance with direct height accesses|1010 /323|Same earlier1c7e7946... body and four-instruction residual.|
|Ordinary static double-return product helper|1032 /320|Different complete code; unselected.|

The inherited/direct pair also checks the live-height interaction rather
than treating the old direct-field inheritance result as a timeless claim.
These results establish no unique original source spelling or compiler/TU
limitation. The public implementation, selected profile, bindings and accepted
providers remain unchanged, so the earlier source-pinned native receipt is
retained without another unrelated fixture replay. No new exact credit.

Private regeneration recipes are in `.analysis/gage-product-20261021/`.
All24 trial source/object/log/diagnostic files are losslessly compressed in
`unselected-trials.tar.gz`, with a per-file SHA256 manifest and verified readback
before removing loose copies. Restore that archive before inspecting or
rerunning a control. The formal baseline receipt and frozen inputs stay loose.

## Floating environment and a genuine larger CIL context

The subsequent `build/gage-fenv-context-20261021/baseline.json` freshly rebuilds
the unchanged selected source:1010 bytes, canonicalfa2cc075..., nonexact+190.
Whole-function `fenv_access(on)` and three direct expression promotions
(fraction to double, height to double, subtraction to double) each produce
that same complete canonical body. These are distinct from the preceding
product-local controls: no intermediate variable/home is introduced. None
recovers the remaining pair. No new numeric/exception coverage is claimed.

VC8 rejects statement-local fenv pragmas with C4177: global or namespace scope
is required. That trial is rejected rather than counted as an effective
environment change. The remaining controls compile without warnings.

A genuine larger CIL trial includes the actual GageRender and
TextureStageBinding definitions, the retained TextureHandleRuntime lookup/
recycling/release definitions, and the real AngleLookup functions. The cosine
table uses an external declaration and its existing attested data binding;
original TU partition is not claimed. The actual public helper entries are
exported in this diagnostic artifact to preserve their observed normal ABIs.
No source register facade, synthetic game callee or executable absolute
binding is used. Precise/fenv source pragmas and the renderer's existing
exception pragma supply the source environment; this does not establish
equivalence to a new formally configured strict-LTCG profile.

Binding compiler-owned real literals as external absolute symbols fails with
LNK2005 duplicate definitions, and is rejected. Leaving those genuine native
constants in the image links cleanly. The resulting source-owned root closes
through both RET8 exits at **1012 bytes/328 instructions**; this is raw linked
structure, not a canonical1012/1010 comparison. Strict comparison stops on
the first unqualified internal floating-literal memory reference. Existing
linked comparison does not yet authorize that literal surface. Neither a
forced link nor an operand mask is introduced. The different complete extent
also means literal support alone would not establish exactness.

Public source, profiles, headers, bindings and accepted units remain unchanged.
Consequently the previous native source-epoch receipt is retained without
another unrelated fixture or accepted-unit replay. Fresh preflight again
rejects the wrong IDA image; all target observations use the canonical PE.
Recipes, source/object hashes, the successful link, rejected literal binding
and raw-root CFG receipt are in the new build scope and its `.analysis/`
counterpart. Unselected ordinary controls are stored losslessly in the new
scope's archive; the baseline and larger linked context stay loose. Builds
remain serial on CPU0 at nice10. No new exact is added in this audit.

## Field-lifetime and getter interaction audit

`build/gage-field-lifetimes-20261021/` freshly pins the complete1010-byte/
323-instruction target, both RET8 exits and CGage vtable6D6A38 slot1C. The
selected source still produces canonicalfa2cc075... and first differs+190.
Six complete source controls leave all public source and shared inputs intact:

| Control | Complete extent/instructions | Unequal instructions |
| --- | --- | --- |
|Live reference to vertical scale in mode1|1010/323|2; same selected body|
|Live references to both scales in mode1|1010/323|2; same selected body|
|Reference to a physical two-float scale member|1010/323|2; same selected body|
|Height reference spanning the whole function|1010/323|10; first+DC|
|Double-return getter with the selected live-height context|1010/323|6; first+190|
|Non-pure float getter declaration|1010/323|2; same selected body|

The double getter trial specifically combines the current height context with
the alternate return declaration, rather than assuming the earlier direct-
height control covered that interaction. ST0 followed by FSTP m32 does not
uniquely determine the original getter spelling. No alternative type or field
layout is selected. Complete comparisons, source/object hashes and the target
CFG/RTTI receipt are in the scope; private recipes use the same named directory
under `.analysis/`. Controls are archived with verified lossless readback;
the selected baseline stays loose. No new exact or native-coverage claim.

## Getter clamp lifetime controls

`build/gage-clamp-context-20261021/` freshly rebuilds the unchanged selected
source60ce4f3b: complete1010-byte canonicalfa2cc075, still nonexact+190.
Five additional source controls test whether the getter/clamp lifetime rather
than the final product expression explains the remaining operand choice.

| Complete source control | Bytes/instructions | Result |
| --- | --- | --- |
|Const getter value, separate const clamped fraction|1058/341|Nonexact+10; additional strict-FP homes|
|Const getter value, separate mutable clamped fraction|1058/341|Same whole candidate as the const-fraction control|
|Native `std::min(value,1.0f)` after the existing ordered-zero gate|1047/326|Nonexact+10; unselected|
|Ternary clamp assigned to the original fraction variable|1010/323|Same whole selectedfa2cc075 body|
|Original assignment with commuted `1.0f <= fraction` guard|1010/323|Same whole selectedfa2cc075 body|

These forms retain a single getter call and NaN-preserving clamp policy.
The separately initialized fraction adds the strict-FP assignment lifetime;
neither its const qualification nor its native minimum helper solves the
target form. There is no reason to select those larger candidates or claim
that the remaining two instructions require a particular original clamp API.
No volatile/register shaping, game source, shared input, profile, binding or
accepted unit changes. The existing source-epoch native evidence is retained;
no new native/aggregate replay or exact byte is claimed. IDA again rejects the
wrong image; target facts come only from the hash-attested1.06a PE. Baseline
inputs remain loose. Five unselected controls are archived with per-file
SHA256 round-trip checks:166210 ->29879 bytes; recipes use the matching
`.analysis/` scope. Next: genuine source/TU context, rather than repeating
these byte-neutral clamp forms.
