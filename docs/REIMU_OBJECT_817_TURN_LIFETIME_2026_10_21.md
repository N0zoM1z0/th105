# ReimuObject817 turn destination before RNG

The selected496540 source now preserves817 sequence3's observed parameter
pointer lifetime: capture before the first RNG, write that destination, then
reload after the second RNG. This is a source correction, **not a whole-root
exact match**. Full46138-byte comparison still first differs49655F/+31.
The complete46160-byte source section remains target-size+22, with426 physical
calls/71 RETs versus target433/68. Same-TU4963A0 remains66/66 exact.

## Observed target

Only original Japanese TH10.5 v1.06a is used, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Fresh target/tracking checks pass. IDA still rejects10350095...; no IDA
semantics, Ghidra process, database write or target modification is used.
The root's candidate/boundary/origin/ABI ledgers remain unchanged.

The raw sequence3 entry is4990CE, selected by the817 switch at4A1B30.
Its optional secondary-animation replacement ends at49910D. Then:

| Target instruction | Observation |
| --- | --- |
|49910D|Read object340 into EDI.|
|499118|Call actual selector RNG4067D0 with limit360.|
|49911D..499134|Unsigned subtract180, convert to float and add the old destination's float.|
|499137|Store the turn through the captured EDI pointer.|
|499139|Call the same RNG with limit60.|
|499153|Read object340 again into EAX, after adding40 and converting the second result.|
|499164..499170|Store speed through the reloaded pointer, prepare its heading/speed arguments and call435160.|

The frozen c79f3975 predecessor computes a named `turn` first and reads340
only after the first RNG. Moving the actual unsigned RNG expression into the
compound-assignment RHS lets the pinned VC8 build retain the target's captured
pointer. The second assignment and subsequent pointer reload remain. This
is a statement about emitted VC8 instructions, not a portable C++ evaluation-
order guarantee or proof of unique original source spelling. No extra read,
fake dependency, helper shim, custom ABI, forced register or assembly is added.

The target also establishes EBX=0/EDI=1 at498CE6/498CEB before the817 switch.
Its separate817 advance at4993AB and860/861 advance at49BF37 remain two real
sites. The selected source still shares one4351C0 call across817/860/861.
The pointer correction does not solve that separate constant/physical-sharing
problem; RET-distance27 and call-membership distance9 remain diagnostics.

## New native observer and negative control

`scripts/audit-reimu-object-817-turn-lifetime.py` observes actual parameter-
pointer reads, real RNG entries and parameter stores. Its read hook is limited
to object340..343. There are320 sequence3 cases: five real MT seeds, two x87
control words, two facings, two frame timers and eight amplitude values including
the5 boundary, large byte-conversion values and NaN. The fixture's actual
parameter pointer is checked at root entry. Both RNG calls execute original
code; all320 cases finish at real root RETs, with balanced native return checks.

Expected observed order is:

```text
pointer_read, rng360, turn_store, rng60, pointer_read, speed_store
```

All320 selected cases agree in final outputs, ordered writes and this observed
order. The predecessor has zero numerical/write differences but fails the
order check in **320/320**, reading the pointer after rng360. This makes the
read lifetime observable without inventing a callback, pointer mutation or
opaque return. Input SHA256:
`cc46775ac043cad9eedea6d412973da5c1212d60bcb3440107127b8cdea13299`.
Arbitrary aliases, original global API types, unmasked exceptions and whole-root
semantics remain outside this finite result.

A fresh stride37 retirement sample passes3600 cases, input e90a5943, with zero
output, ordered-write and logical retirement-x87 differences. Logical x87
excludes physical TOP/exception flags. The existing scoped905/907/908 selector
check also passes12 actual first-request prefixes and conditional normal-return
call graphs; it does not execute returning opaque World/wave continuations.
No old133192/26342 receipt is reissued.

## Complete comparison, impact and retained scope

| Selected artifact | SHA256 |
| --- | --- |
|CRLF CPP|`5210f5ab1662283e0b6f2ca5654cdb1fae5c07d2cfb4debb0609eeb064a35131`|
|Unchanged header|`6f469e6886959fd41ee6976b3c784c3df0c2e753ad4729a536764a3c8cd28b4b`|
|Tested formal COFF|`ab2088e8120fc786691e036e637668fc4191ec658b615ae86071b295b85af754`|
|Whole46160-byte canonical source|`f22ad394497f0f8731652c9cd1e2bf052763ed9d06b0a60877d3d64aeddd16ff`|
|Fixed46138-byte compared prefix|`33223535f5a455a67d6374e0e9ccbfcac1076606fb6343e071a82ac3641ba14f`|

The unchanged ordinary SP1 O2 profile retains frame438h, prefix45292 plus868
metadata bytes and10449 decoded instructions. Source-to-source instruction/edge
comparison, excluding recorded NOP forms, leaves40/43 physical owners identical.817's pointer/register lifetime
changes;851 and908 change constant-register allocation. No switch table changes.
For every instruction in each complete action closure, the private bridge also
checks actual byte identity. Only817/851/908 closures differ. The initial49
bytes and all metadata are identical. In particular821 and866's complete
root-owned closures are byte-identical to c79f3975, preserving the code behind
their earlier6720/256 scoped receipts without claiming a fresh execution run.
External helper implementations/bindings remain unchanged.

The tested private candidate and formal COFF export identical complete native
bodies. A final metadata-only rebuild is bridged by the same full-body equality;
`final-inputs.json` pins both formal containers and the current input digest.
No header, layout, compiler flag, relocation binding, ownership, match row or
aggregate exact count changes. Only the affected mixed root/helper unit is built.

## Unselected controls and retention

A complete RTM build of frozen c79f3975 also emits46160 bytes, canonical
0b290bf9, remains nonexact+31 and keeps426 calls/71 RETs. Its817 shared advance
and908 FILD/FADD-memory load form remain. RTM differs from SP1 in six physical
owner graphs, including constant materialization and alignment. The compiler
SHA256 pins and complete source/report inputs are retained. This single source
control does not prove a universal compiler-version or LTCG barrier.

An actual three-use first-frame predicate is outlined under both ordinary and
`inline` spellings. Both full-root comparisons are blocked by the extra unmapped
local callable; no target address is invented. A private inlining-hint control
completes comparison but emits46164 bytes/canonical4aac37b0 and still shares the
advance. It remains unselected; the selected source uses no such helper/hint.

Frozen inputs/reports are under `build/reimu-object-817-tail-20261021/`; recipes
are in the corresponding `.analysis/` scope and read frozen baseline inputs.
29 completed unselected products are compressed2309585->303850 bytes after
per-file SHA256 readback. Restore the archive before inspecting those controls.
Selected/baseline inputs, tools, canonical target and primary databases remain.
All heavy work is serial at CPU0/nice10.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-reimu-object-action-state --compare --json
# Expected exit1: root nonexact+31, helper66/66 exact.
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-817-turn-lifetime.py \
  build/match-units/GptWeb_ReimuObjectActionState.obj --output build/817-turn.json
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-retirement-fpu.py \
  build/match-units/GptWeb_ReimuObjectActionState.obj --stride 37 --output build/817-retirement.json
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```
