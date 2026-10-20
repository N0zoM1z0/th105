# CGage renderer: complete source, two remaining instruction pairs

Work started October20 and recorded October21,2026. `CGage_render @41B3F0`
is now source-present, **not exact**. The complete target and selected source
both contain1010 bytes/323 instructions. Four instructions in two vertical-fill
multiplication pairs differ; the first unequal byte is41B54A, offset346/15Ahex.
No `matches.csv` entry or partial exact credit is added.

Only original Japanese TH10.5 v1.06a is used, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Fresh target/tracking checks pass. IDA still fails target attestation with
10350095... and supplies no semantic evidence. No Ghidra process, database
mutation or target instruction patch is used.

## Observed boundary, ownership and ABI

The hash-attested PE body is `[41B3F0,41B7E2)`, SHA256
`67b9378f09e92621dad4bba0410f9aa4905bf24a8a73dd3e4440489bf860eedb`.
All323 decoded instructions are reachable in its local control-flow graph;
there is no indirect jump or unresolved local edge. RET8 at41B7D4/41B7DF
and fourteen following INT3 bytes establish the exclusive end. The candidate
ledger's1010-byte extent is retained after this independent reconciliation.

The independently exact CGage destructor40AD60 publishes RTTI-owned vtable
6D6A38. Its+1C cell6D6A54 points here. ECX supplies the receiver; two float
stack words supply screen coordinates. The body preserves ESI and uses a10h
local frame. A source `void` return view is consistent with the observed
call contract; the unique original C++ return declaration is not proved.

There are six physical CALLs: the owned provider's vslot0 at41B408, cosine
4063D0 at41B661, sine406360 at41B673, texture binding404DF0 at41B79C, and
two D3D virtual calls at41B7B4/41B7CE. Those graphics calls use device-vtable
offsets164/14C for SetFVF/DrawPrimitiveUP. Submission is FVF144, triangle
strip5, primitive count2, four vertices at receiver+8, stride28.

The existing CGage lifetime/factory evidence bounds the object toA4 bytes.
New typed observations are float UV spans+94/+98 and a32-bit fill selector+9C;
the owned getter pointer remains+A0. Vertex layout is28 bytes, with float
x/y/z/rhw, DWORD color and float u/v. Width/height78/7C, pivot80/84,
scale88/8C and orientation90 agree with the sprite layout. Source-local
assertions preserve these offsets without editing shared headers.

## Recovered behavior

The source calls the actual value provider, rounds its x87 result to float,
returns for ordered `fraction <= 0`, and assigns1 for `fraction >= 1`.
An unordered result continues. A null provider returns before any call.
The following three cases preserve the target's assignment order and float
assignment homes:

| Mode | Geometry | UV writes |
| --- | --- | --- |
|0|Right edge fixed; left edge becomes right minus fraction-scaled width.|Read vertex1.u; subtract fraction times span94; write vertex0.u then vertex2.u.|
|1|Bottom edge fixed; top edge becomes bottom minus fraction-scaled height.|Read vertex2.v; subtract fraction times span98; write vertex0.v then vertex1.v.|
|2|Left edge fixed; right edge becomes left plus fraction-scaled width.|Same vertex0.u/vertex2.u update as mode0, including its vertex1.u anchor.|

An unknown mode retains cached geometry/UV, then still proceeds to rotation
and submission. Nonzero orientation rotates all four vertices around the
input screen coordinates through the original quantized lookup functions.
The source retains each observed addition/subtraction association. Half-pixel
correction and all float round trips precede the original texture binder and
COM submission. The mode names, narrow class view and source spelling are
inferences from these instructions, not recovered original declarations.

## Canonical comparison and remaining context

The selected unit is `gpt-web-gage-render`, private ordinary VC8 SP1 O2 strict
FP, GS off, with local `float_control(except,off)`. It uses existing verified
code/global/literal bindings; no relocation ledger or shared profile changes.
Formal comparison covers all1010 bytes with relocation replay, without masks.

| Target instructions | Selected source instructions |
| --- | --- |
|41B549 `fld [esi+8C]`;41B54F `fmul [esi+7C]`|41B549 `fld [esi+7C]`;41B54C `fmul [esi+8C]`|
|41B57F `fld st(3)`;41B581 `fmul [esi+7C]`|41B57F `fld [esi+7C]`;41B582 `fmul st(4)`|

The paired encodings occupy the same respective9/5-byte ranges. All other319
instructions, including their addresses, are identical: branch layout, vertex
and UV writes, rotation, all calls and the complete graphics tail. This is a
diagnostic observation, not an acceptance rule or a floating-point equivalence
proof for arbitrary operands/environments.

Changing the source product order, using published vertex anchors, grouping
dimensions into pairs and putting cases in physical target order each retain
the same whole canonical body. The installed RTM control and the full
RTTI-observed zero-offset inheritance/nine-slot virtual view also retain the
same body. A height
local, double fraction, double half-pixel literal and exception-sensitive
strict control change wider code and are unselected. Ordinary non-strict FP
produces959 bytes and first differs at+16. These bounded trials establish
neither a compiler limitation nor an LTCG impossibility. Original declaration
ownership, optimization context and the source property explaining both
operand-order pairs remain unknown. No assembly, padding, fake behavior,
forced register or volatile shaping is selected.

Two final vertical-only precision controls narrow that question: promoting
both problematic products to double retains the selected1010-byte canonical
body; changing only mode1's half-pixel literal to double produces1008 bytes
and moves the first mismatch to+16. Neither is selected or treated as evidence
of the original source's precision declarations.

Selected CRLF source SHA256:
`dbea79c88a2d48bef5c330ac402c19a6974724af2772b6a603502664265e5895`.
Frozen formal COFF SHA256:
`b64422f319a310136567ffc7dff81cd2432f926ed3e76e1c5a14a9f8cf443b7d`.
Complete canonical source SHA256:
`1c7e7946fd4c3145495046e7176c9c624bada6a4719757675291f35cc25763db`.

## Native prefix audit and negative controls

`scripts/audit-gage-render-prefix.py` exports the actual COFF, attests the PE
and complete target closure, then executes target/source under Unicorn. The
actual exact int/short providers46FA50/46FA70, cosine/sine helpers and reached
CRT instructions run unchanged. The orientation table uses the existing
native initialization fixture from `iku_native_math.py`. Every executed code
range is checked against its immutable target or relocated source input.
Allowed writes are confined to the A4-byte object and fixture stack. The
getter/value pages remain read-only during native execution.

The4490 cases comprise two provider kinds, fourteen requested fraction words,
five mode values, four finite angles, masked x87 control words27F/37F and four
height/scale pairs, plus ten null-provider cases. Fraction fixtures include
signed zero, subnormal, below/equal/above-one, infinities and quiet/signaling
NaN inputs; geometry includes rounding-sensitive, dual-NaN and tiny pairs.
The real providers perform their actual integer-to-float/subtract/divide path.
These are distinct arbitrary native object/getter inputs; constructor/game
reachability of every fixture is not asserted.

All4490 prefixes agree:1290 reach real RET8 and3200 stop at the actual
texture-binding entry. Comparison includes full object bytes, ordered writes,
actual getter/lookup calls and lookup arguments, binding receiver/arguments,
x87 status/control word/empty stack, plus return stack and preserved registers
for completed returns. Both sides visit304 of323 root instructions. The19
post-binding COM/submission/return instructions are statically compared but
not executed by this audit. The binder and graphics implementation are opaque;
unmasked exception delivery, arbitrary aliases, arbitrary inputs, full-game
behavior and whole-root exactness remain unproved.

Input matrix SHA256:
`a9335c55c58e5c3525df3fee417fd9ff03bae2f8c8513e49e280bd1aa2779bb5`.
The audit pins its source/object, PE, manifest, target/symbol/relocation inputs
and loaded local analysis modules before and after. It deliberately reports
`build_provenance_verified=false`: build provenance comes from the separate
formal receipt, not from an emulator inferring a source/object relationship.

Two real C++ negative controls are separately compiled under the same flags:
changing the gate to `!(fraction > 0)` causes640/4490 differences, and changing
mode2's U destinations to vertices1/3 causes640/4490 differences. The original
native-prefix audit and both negatives were rerun with the final pinned script;
successful rejection is exit1. Their source/COFF hashes and build commands
are retained in `negative-checks.json`, with final replay commands/receipts
in `final-prefix-replays.json` and `*-final-native.json`.

## Affected accepted unit and reproduction

`GageLifetime.cpp` now names spans94/98 and selector9C instead of the twelve
unmodeled bytes. Its existing slot18 marker is refined to rectangle4070C0's
four float edges/RET16; the outer empty40AE60 slot records three words/RET12
without claiming their semantic types. Only this private translation unit is
affected. All five functions in `gpt-web-gage-lifetime` freshly compare exact
with their previously accepted full hashes. Current lifetime source SHA256:
`8de1130fc9cb19d1bd4237ef3f84dfe274c9fe2a7872f2fc4912a2b400c52f60`.
The original [lifetime receipt](GAGE_LIFETIME_2026_10_20.md) remains historical.

```bash
# Expected exit1: complete root remains nonexact.
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-gage-render --compare --json
# Expected exit0:4490 equal scoped prefixes; no graphics continuation.
taskset -c 0 nice -n 10 python3 scripts/audit-gage-render-prefix.py \
  build/match-units/GptWeb_GageRender.obj \
  --output build/gage-render-20261020/reproduced-native.json
# Expected exit0: all five affected accepted functions are exact.
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-gage-lifetime --compare --json
taskset -c 0 nice -n 10 python3 scripts/function-origins.py --write --check
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Receipts and frozen selected source/COFF are in `build/gage-render-20261020/`;
raw target packets/private source trials and negative generation recipes are
under `.analysis/gage-render-20261020/`. No generated object/report is committed.
Completed unselected trial files are compressed in `unselected-trials.tar.gz`
inside the build scope, with per-file hashes in `unselected-trials-manifest.json`;
archive contents were verified before removing their loose copies.
The function moves from review to authored/source-present with a complete
target-pinned origin rule. Exact totals do not change. ReimuObject496540 stays
open and untouched; no cold aggregate or broad historical replay is claimed.
