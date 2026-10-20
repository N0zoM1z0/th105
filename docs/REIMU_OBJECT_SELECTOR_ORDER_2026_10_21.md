# ReimuObject match-mode block order

The selected update root remains **nonexact at49655F/+31**. This checkpoint
recovers the target's descending match-mode block order in905..908 and all12
first-spawn packet stack offsets in906..908. These are source-shape diagnostics,
not partial exact credit. The same-TU4963A0 helper remains canonical66/66.

## Target observations

Only the hash-attested original Japanese1.06a executable is used, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
IDA attestation still rejects10350095...; no IDA semantics, Ghidra process or
metadata/target-byte write is used. Full raw root ownership remains46128 bytes
and10 alignment bytes in the46138-byte comparison; main candidate39853 stays
provisional. The full target has10670 instructions,22 switches and68 RETs.

Each table is indexed by modes0,1,2,3, but its destinations run backwards in
physical instruction order:

| Action | Table | Mode0 | Mode1 | Mode2 | Mode3 |
| --- | --- | --- | --- | --- | --- |
|905|4A1C24|49EF46|49EEC1|49EE3C|49ED7C|
|906|4A1C4C|49F76D|49F665|49F55D|49F451|
|907|4A1C74|4A0072|49FF68|49FE4E|49FD46|
|908|4A1CAC|4A0DC5|4A0C03|4A0A40|4A0847|

The previous source writes all four switches in ascending case order and VC8
emits those blocks in ascending order. Reordering the four complete case
bodies to3/2/1/0 preserves each period test, argument, operation and break.
Descending source order is a supported hypothesis; original spelling and
original TU/compiler context are not uniquely established by this result.

Actual native execution stops at each real first World64CCB0 entry. Let F be
the root stack pointer after its438h frame and saved registers, entrySP-448h.
The packet pointers are measured from actual calls, not inferred LEAs:

| Action | Target modes0/1/2/3, relative to F | Previous source | Selected source |
| --- | --- | --- | --- |
|905|174/11C/14C/104|168/120/150/138|138/150/120/168|
|906|C8/D4/B0/BC|BC/B0/D4/C8|C8/D4/B0/BC|
|907|270/258/240/228|228/240/258/270|270/258/240/228|
|908|348/318/2E8/2B8|2B8/2E8/318/348|348/318/2E8/2B8|

All entries are hexadecimal offsets. Each action still has four distinct
packet identities. All12 offsets for906..908 now agree;905 still differs.
The16 actual first-entry outputs and packet payloads agree before and after
the change. This covers neither subsequent opaque World returns nor all
loop iterations, aliases, object/resource states or x87 exceptions.

## The906 tail remains unresolved

Target906 has four private final-spawn/wave pairs:

| Mode | First World | Final World | Wave45C030 |
| --- | --- | --- | --- |
|3|49F4CD|49F546|49F553|
|2|49F5D9|49F64E|49F65B|
|1|49F6E1|49F756|49F763|
|0|49F7E9|49F862|49F86F|

All four target final-call setups push count3 before the packet updates.
For example,49F817 PUSH3 precedes49F819's heading load and49F826's packet
store. The selected standalone COFF still updates the packet before preparing
the shared final call. Scheduling alone does not prove an argument expression.

Four bounded, genuine source controls reproduce the predecessor's complete
46148-byte canonicalb12eab22... body unchanged:

* Put the existing heading/sequence updates in the actual packet argument's
  comma expression, preserving their order and values.
* Use a real12-byte typed heading/speed/sequence packet instead of float[3].
* Move the existing sector counter declaration into the enclosing period block.
* Make the actual78-byte64CCB0 source definition and its real manager-call
  typedef visible in the caller TU. The helper independently remains78/78;
  no forced inline/noinline or ABI substitute is used.

After selecting descending order, another control moves905's uninitialized
packet declarations into the switch cases and its shared consumer inside
that same switch scope. Every selected packet stays alive through its real
consumer; no dangling pointer, synthetic operation or extra call is added.
It reproduces the selected complete46152-byte body unchanged and is unselected.
None of these results establishes a universal source, profile or LTCG barrier.

## Selected source and comparison

Source is `src/characters/ReimuObjectActionStateStaging.cpp`, unit
`gpt-web-reimu-object-action-state`. Header, ABI, layouts, flags, globals,
relocation mappings and byte ownership remain unchanged.905's preceding
live-packet join and earlier local retirement/ordered-store recoveries remain.

| Artifact | SHA256 |
| --- | --- |
|CPP|`295be3bcbcb2b21cec2c0f09a3f56ae3dcd6fe268f1008b3ca80672598a99797`|
|Header|`6f469e6886959fd41ee6976b3c784c3df0c2e753ad4729a536764a3c8cd28b4b`|
|Formal COFF|`922a322ed8fd9c608c7a1144e63a13eb15a5bc394b3ad14199373028924d9f5c`|
|Whole46152-byte canonical source section|`7c16e018acfd53917697ba5d43c874868334adfa819526fc24fa09f71e22a714`|
|Fixed46138-byte compared prefix|`c49c7572b17f0baadaff6542d4a1a52b9b681f5cfeb55aaf02d0060d2f82a0d1`|

The whole payload and compared prefix have different extents. Fourteen extra
payload bytes do not imply near-exactness. Source prefix45284 plus868 metadata
bytes emits10446 decoded/10445 reachable instructions,71 RETs and426 physical
calls; target has433 calls. Call-membership distance9, RET-distance29 and
owner identity1/43 are diagnostics only. First difference remains the default
jump displacement at49655F. No new match or remote-exact flag is recorded.

Whole-root call memberships retain the same concrete residual: target817 and
860/861 use two4351C0 sites where source shares one; target906 has three extra
final World64CCB0 and three extra wave45C030 sites.905 has its intended four
private first spawns and shared second-spawn/wave consumer.

## Affected verification

A complete source-to-source instruction/edge audit compares the frozen
predecessor and selected candidate, including reviewed switch tables.
31/43 physical owners are identical after only control-edge/table-address
normalization. Six earlier owners (822/869/900/901/902/903) only retarget the
moved shared World tail.951 changes volatile temporary registers; the default
owner gains one compiler MOV EDI,EDI NOP. This diagnostic preserves actual
instruction widths/registers and is not a target matching claim.

The selected formal COFF passes these affected checks:

* 26342 inputs in24 high/final cohorts: zero output, ordered-write or
  retirement-live-x87 differences. The cohorts include the four changed
  match-mode families and951's changed temporary registers. Input SHA256 is
  `6031e9a6074f2e61c362a5b06127cc909641fdece30e55284a42f52d27113606`.
  CPU0/nice10 run:115.67 seconds wall time, peak RSS198232KiB.
* 3600 whole-root stride37 inputs: zero output/write/retirement differences;
  the same3600-input helper-entry sample has zero output/live-x87 differences.
  Input SHA256 is `e90a5943bb6d191b71e759265ca9a6fbceff9bc5317da6350aa49a70577b032b`.
  Helper4359F0 remains unvisited. These samples do not cover all typed stores;
  static902 spill/reload and822 heading-pair checks still agree.822's
  post-opaque pair has zero executions. Physical TOP/flags are excluded.
* The scoped905/907/908 audit passes12 actual first-entry prefixes and complete
  selector-owned conditional normal-return call graphs. Input SHA256 is
  `4de38b17a904cdb01c8fb124e92c5ba322869ccee884608a78368d6d08b7a0df`.
  The default four-family audit still rejects906's call-site partition.
* The World-sharing report remains rejected overall: target99 sites versus
  source96. Its18-byte shared seven-action post-call tail remains byte-equal;
  its540 actual903 prefixes, four/joint normal-return call graphs and180
  retiring-request prefixes still agree. No opaque result is fabricated.
* The formal COFF's16 first-prefix observations reproduce the12 restored
  packet offsets and905's remaining four mismatches. Stack placement and
  block order do not substitute for a whole-function canonical comparison.

The predecessor's full133192-input pass belongs to CPP1c9a12c4 and is not
reissued or byte-bridged to this changed root. No unrelated accepted unit,
aggregate replay or aggregate percentage is claimed.

Artifacts and frozen inputs are in `build/reimu-object-906-tail-20261021/`;
private recipes are in the corresponding `.analysis/` directory. The formal
build receipt separately proves source/compiler provenance; complete native
byte equality bridges the order-control COFF to the tested formal COFF.
A final rebuild after CSV line-ending normalization is bridged by complete
native equality to that tested COFF, preserving its scoped receipts without
replaying unchanged instructions. Recipes read the frozen predecessor when
that control requires it.

56 completed unselected-control files are losslessly compressed from5248235
to666168 bytes in `unselected-trials.tar.gz`, with per-file SHA256 readback
before loose removal. `compression-manifest.json` pins the archive and files.
Baseline, selected and descending-order control sources/COFFs stay loose;
primary databases, tools and canonical target are retained.

```bash
# Expected exit1: root mismatch+31; helper4963A0 must remain66/66.
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-reimu-object-action-state --compare --json
# Scoped complete call graphs; default still rejects906.
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-selector-families.py \
  build/match-units/GptWeb_ReimuObjectActionState.obj \
  --action 905 --action 907 --action 908 --output build/reimu-selector-graphs.json
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-retirement-fpu.py \
  build/match-units/GptWeb_ReimuObjectActionState.obj --stride 37 \
  --output build/reimu-selector-sample.json
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Remaining work:905 packet placement,906/817 physical sharing, return layout
and original source/TU context. Canonical whole-root equality and behavior
beyond the finite native/normal-return static scopes remain unproved.
