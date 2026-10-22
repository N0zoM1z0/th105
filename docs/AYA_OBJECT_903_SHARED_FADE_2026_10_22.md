# AyaObject903 shared fade-value recovery

## Selected change

This supersedes the selected-source epoch in the
[native-math audit](AYA_OBJECT_903_NATIVE_MATH_2026_10_22.md) for root61A290.
Only original Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Startup checks pass except the known wrong-image IDA rejection.
Raw target PE and complete native VC8 COFF supply the evidence.

The target's sequence2 computes the second fade product at61E827, reads alpha
at61E829, stores the product at61E82F, then compares alpha at61E835. Sequence3
computes its second product at61E91B and jumps into that same alpha/store path.
The preceding independent local-product controls read alpha too early. The
retained direct-store source read it too late.

The selected source carries the real second product in a shared `double
faded_scale`. Both fading branches assign it before jumping to
`aya903_store_fade`, where the alpha snapshot precedes the actual float field
store. The variable has a real use and every incoming edge assigns it. There
are no inert locals, padding, fake calls or ABI changes. The shared value's
lifetime across the branch merge, rather than its type alone, recovers the
observed scheduling. This is a supported source representation, not proof of
original source spelling or nominal local types.

## Complete-root controls

| Control | Full canonical bytes | SHA256 prefix | Decision |
| --- | ---: | --- | --- |
| Shared double product for2/3 |20036|623294c3|Selected|
| Also explicitly share color tail with8 |20036|623294c3|Identical; unnecessary source change omitted|
| Shared float product/color tail |20044|c37a584a|Unselected extra spill/reload|

The two double variants are identical across the complete canonical payload.
The float variant also passes all3168 dynamic cases, including read snapshots;
however its generated read/store interval is MOV AL, FSTP stack14, CMP AL,
FLD stack14, FSTP field120. The target instead has the contiguous14-byte
MOV AL/FSTP field120/CMP AL interval. The float result does not justify
accepting that extra storage path. The early runner incorrectly expected this
float control to fail dynamic checks; its actual success was retained and the
static distinction was investigated, not hidden or relabelled as a dynamic failure.

## Validation

All3168 original-helper executions now agree with target in final effects
**and alpha-read epochs**, including stored scale, preceding write count,
x87 status/tag and live register contents. This removes all1920 predecessor
read-epoch differences. The same actual native dependencies and masked matrix
from the preceding audit are retained; no helper returns are fabricated.

The native auditor now requires both read-epoch equality and the unique14-byte
target read/store interval within the mapped903 physical owner. The default
rejects the predecessor for its1920 read differences and absent interval, and
rejects the float control for the absent interval despite dynamic equality.
`--diagnostic` reports those differences without granting acceptance. It does
not override differing final effects. No local interval earns exact credit.

The normal-flow checker can now exclude only explicitly listed903 sequences.
It first verifies the primary903 ownership, signed WORD13E load, CMP9/JA and
actual dense ten-destination switch; aliased sequence entries are rejected.
With only2/3 excluded,4463 paired nodes agree under **strict instruction
labels**, including all other actions and the remaining903 sequences/default.
No dead-carrier allowance is used. Leaving sequence3 included correctly fails
on the actual old/new read-order change. The broader outside903 check also
passes4204 nodes. These checks assume normal opaque-call returns and do not
prove callback/exception behavior or full target equivalence.

## Canonical result and open differences

Action903 changes from1726 bytes/372 instructions to1696 bytes/361 instructions;
target is1697 bytes/364 instructions. Being one byte shorter does not establish
canonical matching. The physical shared alpha/store block is still after the
candidate's sequence3, whereas target places it after sequence2. The color tail
is still owned by candidate sequence8. Retirement and sequence7 next-block
return sharing also differ physically. Those gaps need evidence, not padding.

Root61A290 remains nonexact at offset34/hex22, target0F/candidate3B. Metadata
moves19596 to19568 versus target19524. Full canonical20036-byte SHA256:
`623294c32b653875c56df1232a75948b08525755d3e660d3afdce43ea481902d`.
Compared19522-byte window SHA256:
`5456dd932b8d71d0fcc7ffbc58c3bb4ce3495d6cc1ef2ddb95dd5aa1c73f27d0`.
The raw owner diagnostic count is3/34, down from4/34 because action802's
physical-sharing diagnostic changes; the strict normal graph still agrees.
Owner diagnostic counts are not acceptance metrics. Exact totals stay1381
functions/234914 bytes, with no aggregate replay claim.

Shared headers, layout, helpers, compiler profile, manifest and relocation
contracts remain unchanged. No previously accepted unit is affected.

## Reproduction and receipts

Recipes and all complete control CPPs:
`.analysis/aya-903-shared-fade-20261022/probe.py` and sibling files.
Reports/objects: `build/aya-903-shared-fade-20261022/`.
`selected-formal.json` is the configured selected build;
`selected-owner.json`, `selected-native.json`, `previous-native.json`,
`float-native.json`, and `selected-other-graphs.json` bind their respective scopes.
The preserved predecessor object is from commit5934dca's selected source.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
taskset -c 0 nice -n 10 python3 scripts/audit-aya-object-903-native.py
python3 scripts/audit-aya-object-normal-flow.py build/aya-903-shared-fade-20261022/previous.obj build/match-units/GptWeb_AyaObjectActionState.obj --exclude-903-sequence 2 --exclude-903-sequence 3
python3 scripts/audit-giant-action-owners.py aya-object-vslot28 build/match-units/GptWeb_AyaObjectActionState.obj --unit gpt-web-aya-object-vslot28-full-root --json
python3 scripts/ci.py
git diff --check
```

The configured canonical comparator still exits1. Native/graph audits pass
only their documented scopes. Remaining shared-tail placement, other903
behavior and whole-root ABI/numerical closure remain active work.
