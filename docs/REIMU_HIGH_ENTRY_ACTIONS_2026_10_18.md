# Reimu: first nine high-table bodies

## Target observations and source hypothesis

Original Japanese TH10.5 v1.06a SHA256:
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
`Reimu_dispatch_action_state_vslot28 @478FA0` remains81550 bytes through
48CE2E, SHA256 `dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
Candidate/origin/name/source selection were rechecked: authored,
unclassified/declaration-only. No root implementation or exact entry is added.

Nine physical bodies occupy `[487A95,488F62)`:5325 bytes/1380 instructions,
SHA256 `bce4a18198ee6b8b65d0ef3f937d210a2b748447fb3610af2c4ea97cbb9f9145`.
Canonical high-table indices/destinations and every instruction are checked.

|Action|Entry|Next physical entry|
|---|---|---|
|561|487A95|487C01|
|565|487C01|48809F|
|566|48809F|488515|
|600|488515|4886E6|
|601|4886E6|488910|
|602|488910|488AD4|
|604|488AD4|488C3F|
|605|488C3F|488DFA|
|606|488DFA|488F62|

`ReimuActionStateHighEntryCases.hpp` extends the same monolithic source
through606. Gaps use real4740C0; later high source stays pending. Its bool
remains a staging interface, not the complete void-root ABI. Shared C++
branches remain source-shape hypotheses; physical target sharing/expansion,
original TU spelling and compiler provenance are unproved.

561 retains560's landing/gravity/crossing rules, first825 `[0,12,0]`, wave7
after the request and sequence1 node consumption/scaled50. Its node vertical
speed is22.5, versus560's14; horizontal4.5 and AY0.75 are unchanged.

565/566 publish17C=7. Landing runs at sequence0/frame<=1 or sequences1/2/3/6/8.
565 reads full DWORD6C0,566 full DWORD6C4; zero clears latch750. Both always
subtract AY. Crossing at signed sequence<1 sets height, clears AY/VY and
sets1, continuing. A separate prediction stores y+VY as double before a
second height query. Height>=prediction and VY<0 in sequences4/5/7 causes
height, zero motion and set6. Sequence1 counter>=10 with latch advances/RET;
otherwise counter>25 sets8/RET. Sequences4/5,7,8 subtract respectively
double0.25,widened0.1f,widened0.4f and clamp only negative horizontal results.

After advancement, sequence8 node sets5 through47BEB6/480CE4. Sequence0
frame2/timer0 sets VX12.5,VY4,AY0.9f, consumes200/floor120 and adds scaled50.
Sequence4/frame4/timer0 with latch and signed BYTE60B>=4 sets7, state0,
BYTE184=1,VY10,AY0.5 and RET. Sequence7/frame1/timer0 requests825
`[-75,12,1]` at x+signed-facing85,y+117, then wave10. Sequence4 node publishes
state0/BYTE184=1/VY10/AY0.5 and requests825 `[0,12,0]`, then wave7. Sequence7
node sets action0. The private signed byte is offset-asserted; prefix size
and existing offsets remain unchanged.

600/601/602 land and publish texture6/duration2 before their body. Sequence1
counter>30/60/45 advances/RET. Their shot caps are signed WORD730<5/10/14.
600/601 fire at counter%5==0 before advancement;602 requires the complete
counter0/timer0/frame0 node. Wave8 precedes850/853/854. Payloads are
`[(count-2)*45,0,count%3]`, `[count*-36,0,count%3]`, and
`[float(MT%70)-35,0,count%3]`. Coordinates are x+facing18,y+120, not112.
601 subsequently clears only floats0/1 and requests860, leaving float2 live;
count increments after all returning requests. Completion sets0, then only
600/601 publish texture6/duration30/60. Sequence0/frame2/timer0 after advancing
sets WORD48A=40, dispatches event23 and effect115 at x-facing2,y+120; sequence
window(0,2/5/2,60) and the secondary event cycle follow the returning effect.

604/605/606 also land and publish texture6/duration2. Their sequence1 cutoffs
are>30/>30/>90; sequence2 additionally uses>30/>70 for604/606. Sequence0
frame6/timer0 emits the event/effect setup before advancing, at x+facing7,
y+226; later window outcomes are2/3/4. Sequence0/frame8/timer0 after advancing
sends851/855/856 with one zero float, then wave9.605 sends a second855 at
x-facing75 after the first at x+facing75, negating only direction's low byte.
Subsequent objects, waves and window/cycle continuations have raw instruction
evidence; their returning world execution remains unproved.

## Focused build and native context

```bash
scripts/compile-unit.sh src/characters/ReimuActionStateDispatch.cpp build/reimu-high-entry/ReimuActionStateDispatch.obj
python3 scripts/audit-reimu-high-entry-actions.py build/reimu-high-entry/ReimuActionStateDispatch.obj
```

Fresh pre-edit550 smoke passes0/36. VC8 SP1 `/O2 /GS- /GR /EHsc /MT`, default
FP/no injected compiler environment, produces33226 staged text bytes, object
SHA256 `c0be6aaac5f749f5d32732dcf5238698f854a6f5fbca06719b55a474be16a021`.
`build-receipt.json` pins compiler/source/header/object hashes and the separate
previous-commit baseline. The oracle pins its own inputs, without itself
attesting compilation provenance.

The new oracle uses actual accepted `publish_texture_state @45F560`170 bytes,
native checked deque indexing42D1B0/100 bytes and WORD48A setter4776C0/15 bytes.
It supplies a real eight-entry VC8 deque layout, read-only distinct opaque
texture IDs, a manager pointer in runtime state and two mapped manager slots.
Only actual4-byte writes to D8/DC are admitted; both slots are compared.
Self/peer duration0/nonzero and both player indices cover both publisher paths.
Duration arguments are compared as eight raw stack bytes. This does not model
a rendering backend or substitute helper results. The source reuses existing
texture/window/event-cycle interfaces. Sequence-window45DEB0 is bound but is
not executed because the earlier real effect request stops first.

The private graph mapping is2 MiB because the expanded key domain with nine
sequences/fourteen frames exceeds1 MiB. Existing fixture layouts and oracle
classes are unchanged. Node/cadence/hold ground contexts use y=0: y=100 makes
the original landing helper switch to action9, bypassing the intended gates.
Required original sites exposed that unsuitable input; it was corrected
without changing source or the landing helper.

**0/6165 differences**, `build/reimu-high-entry/native.json`, input SHA256
`06b8a35de43ff390e606b1e5355cc41494b1f6aa3fc5aa3917bc7d5deaa006a3`:

|Cohort|Cases|
|---|---:|
|Motion/landing/completion/NaN|972|
|Full-width held inputs and counter/latch boundaries|144|
|Three friction rates, signed zero and NaN|128|
|Signed skill gate and latch/input combinations|64|
|600..602 shot cadence/caps/seeds|1980|
|Texture manager paths and completion|96|
|Nodes, frames and facing extremes|2160|
|30 required original sites at both x87 precisions|60|
|Earlier middle/low/entry/common paths|549|
|Gaps/defaults and later handoffs|12|

5578 cases reach genuine RET;514 stop at actual465190,52 at effect435240,
11 at common4740C0,1 at set669 and9 pending.7895 original-root and4636 staged
instruction addresses are sampled.4212 texture-publisher,8332 deque-index,
34 WORD48A setter,64 MT and396 wave calls execute actual native helpers.
4096 actor bytes, ordered calls/receivers/arguments, pointed payloads, world
scalar, manager slots, all2496 MT bytes/index and control word are compared.
Returns require stack delta4, saved registers and x87 TOP=0. One-/three-float
requests require aligned live stack storage, correct count/ID and all bytes.
No callback return is fabricated. Read-only animation/texture data, flat
surface, zero wave/event handles, inactive secondary cycle and masked PC53/64
bound this proof. Complete runtime/backend contexts and floating exceptions
remain unknown; no canonical-exact claim.

Compiled wrong-source controls detect64/144 for swapping held input fields,
96/96 for texture index6->5, and2/108 for825 angle-75->-60. Reports and private
build receipts are retained. Rejected sources/objects are removed.

## Preservation, analysis and next work

Six older adapters rebuild with identical non-debug code/data and relocation
offset/type/symbol/value/section identities, sizes530,771,1562,4017,4409,11271.
Smokes pass0/9,0/88,0/64,0/99,0/150,0/59. The549 integration cases include
earlier550/540/520/510/500 smokes. Full historical matrices are not repeated.
No accepted unit depends on this private header; accepted source/profile/
relocation ledgers and exact totals are unchanged. No cold aggregate replay.

One direct Ghidra read-only clone attests executable SHA, entry68B9D2,
base400000, Windows x86, mapped.text, root bytes and every bounded instruction,
then reads back nine entries/shared exits. Marker
`REIMU_HIGH_ENTRY_READBACK_PASSED` is in `ghidra.log`; `analysis-receipt.json`
pins log/script/table/body/primary hashes. All9 primary files are unchanged;
clone removed. One process used768 MiB/two CPUs. Wrong-target IDA supplies no
semantics. Superseded objects, private controls, baseline and caches are cleaned.

Next continue608 at488F62 and later high bodies. Returning world contexts,
complete void ABI, full CFG/relocations, truthful VC8/LTCG/TU provenance and
all81550 canonical bytes remain parent acceptance requirements.
