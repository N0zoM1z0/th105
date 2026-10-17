# Reimu: middle shot actions410..418

## Target facts and source scope

Target: original Japanese TH10.5 v1.06a, executable SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Parent `Reimu_dispatch_action_state_vslot28 @478FA0` remains81550 bytes,
ending48CE2E, SHA256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
Its candidate/origin/name/source ledgers were rechecked: authored,
unclassified, declaration-only, with no new implementation or exact credit.

The five bodies are `[47F4A9,4802EA)`:3649 bytes/902 instructions, SHA256
`1427599e5334ca82105267a1408a7c1304fb63fde1ea83d0bac3715ef8dbb0fe`.
Canonical switch-index/destination bytes and each body hash were revalidated.

|Action|Entry|Next physical entry|
|---|---|---|
|410|47F4A9|47F878|
|412|47F878|47F9BB|
|414|47F9BB|47FE17|
|416|47FE17|4801D6|
|418|4801D6|4802EA|

`ReimuActionStateMidShotCases.hpp` is included directly by the existing
`ReimuActionStateDispatch.cpp` method. Earlier entry/low/middle cases stay
in the same method; newly admitted gaps use real common4740C0, and>418
remains pending. The staged bool is not the complete void-root ABI.

Raw instructions support these source choices:

- 410/414 aim at two distinct frame gates, clamp the negated low-WORD integer
  angle to[-10,10], dispatch wave2, consume200/floor60 and form object801's
  four floats(angle,10,1,mode). Mode is0 for the first shot and1 for the second.
  414 adds its scaled counter **before** atan2;410 adds it after wave/resource
  work and parameter initialization. Effect gates test any nonzero BYTE+750.
- 412 dispatches wave3 and creates object808 with three floats(0,0,0), then
  changes the third float to1 for its second request. Both use signed arg5=-1,
  inherited from the root's unconditional EBX=-1 definition. Its sequence3
  completion uses47BFBF, and sequence1 counter>20 uses47E5BD/47E5D7.
- 414 gravity starts at sequence0/frame>=8 or sequence2/frame>=4;416 starts
  at sequence0/frame>=4 or sequence2/frame>=1. Both publish0.6f and subtract
  its double representation, then zero motion, sample height and select3 on
  landing.414 uses47AD16;416 has the corresponding explicit tail.
- 416's two shot gates publish VX=-5,VY=6.5,AY=0.6 and float+744=45 before
  wave/resource/counter calls. Its801 parameters are(45,10,1,mode), with live
  facing/position reads after the calls. Completion uses48748C.
- 410/414/416 sequence1 counter>=25 immediately takes shared4852F6 next-block/
  RET.418 conditionally calls landing first, subtracts live AY, selects2 on
  crossing, applies sequence2 friction, and publishes VY=10/AY=0.85/event29 at
  its frame3 gate. Its landing transition continues to friction/advancement.

These are target-instruction inferences, not original source spelling or TU
claims. Only observed DWORD+6C4 and float+744 are added to the private prefix,
with offset assertions; its full class remains unknown.

## Focused native verification

```bash
scripts/compile-unit.sh src/characters/ReimuActionStateDispatch.cpp build/reimu-mid-shots/ReimuActionStateDispatch.obj
python3 scripts/audit-reimu-mid-shot-actions.py build/reimu-mid-shots/ReimuActionStateDispatch.obj
```

VC8 SP1 `/O2 /GS- /GR /EHsc /MT`, default FP/no injected compiler environment,
produces20258 staged text bytes. Object SHA256
`c445eaf0aa9fd5d5f88e3043153d3333428905b00a2da38dea92ba83c4336f7d`;
manual compiler/source/header/object receipt:
`build/reimu-mid-shots/build-receipt.json`. The oracle separately pins its
object/support inputs; it does not itself attest compilation provenance.

**0/2217 differences**, report `build/reimu-mid-shots/native.json`, input SHA256
`e05e410b282c59ae34a982de343a3c4cc5132c2c1d6b3b7f54e7b546556a024a`:

|Cohort|Cases|
|---|---:|
|Nine sequences, real completion/landing, NaN velocity|540|
|Action-specific frames, four sequences, held/latch gates|864|
|Counter thresholds and live post-advance values|240|
|Both aim nodes, peer coordinates and signed-facing extremes|160|
|Signed scaled-counter phases and float scales|96|
|418 friction, +/-zero, threshold neighbors and NaN|16|
|19 required original branch sites, both x87 precisions|38|
|Earlier projectile/middle/low/entry paths and real common returns|251|
|New default transfers|5|
|Later source handoffs|7|

1806 cases reach native RET;366 stop at actual object465190 entry,23 at actual
effect435240 entry,11 at common4740C0 and1 at set669. Another10 compare the
original pending state at47CC5F with the candidate's genuine false return.
3930 original-root and2557 staging instruction addresses are sampled.

288 atan2 calls,363 scaled-counter calls and354 wave calls execute unchanged
native code. Wave calls tail into real401D50 using supplied zero handles;
no sound/API result is substituted. Math uses the previously reviewed target
dispatcher/kernels and complete float arguments. Return cases require stack
delta4, saved-register restoration, x87 TOP=0 and the original control word.
The comparison also covers4096 actor bytes, ordered helper/receiver/argument
traces, physical conversion inputs, world scalar and full MT state.

At actual801/808 wrapper entry, the new probe validates count4/3 respectively,
aligned live stack storage and all16/12 pointed bytes. It compares contents
and remaining arguments rather than requiring identical numeric stack
pointers. Inherited three-float800/807/848 requests retain their own guards.
No world-request return is fabricated; post-manager/effect continuations and
808's second request remain unproved even though source includes them.

Three compiled wrong-source controls fail as required:

- Move414's first scaled-counter call after aim/wave/resource work:2/38
  branch cases fail. Actor bytes agree in the first counterexample; ordered
  native calls expose the error.
- Change808's signed arg5 from-1 to1:1/50 smoke cases fail, on the real request
  argument despite equal actor bytes.
- Change>=25 to>25:3/50 smoke cases fail across410/414/416.

Reports are `wrong-order.json`, `wrong-sign.json`, `wrong-cutoff.json` in the
same build directory. Controls use ordinary modified C++/VC8 with a private
include directory. Rejected control source/objects are removed after review.

## Preservation, analysis and remaining work

The six prior adapters are rebuilt and preserve every non-debug code/data
byte and relocation offset/type/symbol/value/section identity; text sizes
remain530,771,1562,4017,4409,11271. Receipt:
`build/reimu-mid-shots/preserved-stages.json`. Old focused replays pass0/9,
0/88,0/64,0/99,0/150,0/59. The changed monolithic method's earlier paths use
the251-case integration cohort. Full historical matrices are not repeated.
No accepted unit uses this private header, and no accepted source, compiler
profile, relocation ledger or exact total changes. No cold aggregate claim.

The preceding direct Ghidra readback already attested all five entries and
complete target identity/entry/text/root. This phase rechecks its successful
log, nine unchanged primary DB file hashes, canonical body hashes and shared
exit instructions. Receipt `build/reimu-mid-shots/analysis-reuse.json`; no new
Ghidra process, database write or clone is needed. The wrong-target IDA
preflight is rejected and supplies no semantics.

Read-only animation, flat surface, zero wave/texture/event handles, inactive
secondary-event cycle and masked PC53/PC64 still limit the proof. Original
game assets, returning world backends, both-zero atan2/domain-error behavior,
other runtime modes and full floating-exception behavior remain unknown.

Next continue the500 middle family, then high actions and real returning
world contexts. Complete original void ABI, CFG/relocations, truthful VC8/
LTCG/TU provenance and all81550 canonical bytes remain acceptance requirements.
