# Reimu:720..798 final high families

## Target observations and remaining boundary

Target is original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Parent `Reimu_dispatch_action_state_vslot28 @478FA0` remains81550 bytes
through48CE2E, SHA256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
Candidate/origin/name/source selection were rechecked: authored,
unclassified/declaration-only. No implementation or exact entry is added.

Eight physical bodies occupy `[48BC4D,48CE1F)`:4562 bytes/1149 instructions,
SHA256 `b9b527003838c4cb2fbd0fd24b052c052a80abab88f1055618f17c9be22447c2`.
Default48CE1F and the root end48CE2E remain unchanged.

|Action|Entry|Next physical entry|
|---|---|---|
|720|48BC4D|48C1F8|
|730|48C1F8|48C720|
|740|48C720|48C937|
|760|48C937|48CC88|
|770|48CC88|48CD20|
|795|48CD20|48CD79|
|797|48CD79|48CDCC|
|798|48CDCC|48CE1F|

`ReimuActionStateHighFinalCases.hpp` joins the same monolithic staging method
through798. A canonical table-to-source audit now reconciles all128 nondefault
keys: low44, mid50/high32, plus direct300/560. This proves label coverage only.
Compact loops/shared C++ branches remain source-shape hypotheses. Bool staging,
actions>798 and740's exceptional arms prevent a complete void-root claim.

740's mode>3 arms at48C772 (sequence1) and48C8C4 (sequence6) load root-stack
`[ESP+B4]`; sequence1 uses it as divisor/limit/cutoff. The entry/dispatch path
does not initialize that slot. The only literal-offset write in the decoded
root is482916 in an unrelated action body. Arbitrary stack contents, faults,
and original source/TU handling remain unknown. Source explicitly returns
pending for these two paths; the oracle stops the original before the first
read and compares that boundary with the candidate's genuine bool-false RET.
It supplies neither a guessed divisor nor a fabricated target return. Other
740 sequences, including out-of-range modes, retain their normal behavior.

## Recovered behavior

720 lands in sequence0/frame<=3 or sequence6. Sequence0/frame>3 changes scales
only while scale11C>0, using widened0.1f/0.2f, and subtracts25 from alpha only
when alpha>25. Sequence1 resets scales1/alpha0; sequence2 adds20 with saturation
at255. Sequence3's pre-advance counter==90 sets WORD730=1/wave8; ==120 advances
the block, sets AY0.25f and returns. Sequences4/5 crossing zero motion, sample
height and set6/RET. Completion sets700 and continues. A post-advance node2
uses two actual unsigned random-roll results for x=roll800+240,y=roll250+100.
Node3 wave13 precedes mode selection and a once-per-volley roll360. Modes0..3
send901 with respectively3/4/6/8 rays,120/90/60/45-degree spacing and payload
`[float(i*spacing+base),10,0,1/2/2/3]`. Each call uses four floats and current
x,y+100/raw direction. Out-of-range modes emit nothing. Later rays have raw
instruction evidence only.

730/760 advance first and continue after completion set700. A sequence1 node
sets VX=(640-x)/60*signed-facing,VY17.5,AY0.45f; gravity then applies immediately
in sequences1/2. A sequence3 node sets x640,wave9 and zero motion.730 sends902
`[0,0,0]`, direction1; modes2/3 append902 `[0,0,1]`, direction-1.760 sends four
objects905/906/907/908 with payloads `[0,1,0]`, `[0,-1.5,0]`, `[0,2,0]`,
`[0,-2.5,0]`, direction1. All use y+100 and re-read coordinates per request.

730's post-advance sequence4 >=60 advances/RET. Sequence5 modes0..3 use signed
counter cadence8/6/5/4.902 parameters begin with73C; mode3 instead uses
float((double(73C)+7)-unsigned(roll14)). Speed is4 in0/1, or
float(4-unsigned(roll5/10)*double(0.1f)) in2/3; the last float is2. Positions use
sin/cos(-angle), radius100, signed facing and `(sin*100+y)+100`. After returning
requests or skipped cadence,73C adds2. Mode>3 returns without that increment.

740's sequence1 mode table selects cadence/WORD limit10/6,8/8,6/11,5/14.
Signed counter modulo and signed730 gate wave8, then real roll200/roll30;
903 receives `[10-unsigned(roll200),unsigned(roll30)+15,730%3]`, x+facing18,
y+120.730 increments after the request and mode is re-read. Counter>80 then
advances/RET. Sequence6 advances/RET at >=60/60/50/30 for modes0..3, before
animation advancement. Completion sets700 and continues; a sequence6 node
calls wave2. The two undefined stack arms stay pending as described above.

760 clears WORD736 before sequence4 >=60 advances/RET. In sequence5, positive
signed736 decrements and sets4A8/4AC=3. Three independent signed-health gates
advance738 from0 to1 at<=7500,1 to2 at<=5000,2 to3 at<=2500, each setting736=120.
These can cascade within one call: phase0/health2500 becomes phase3 immediately.
Other sequences set736=3 unless the sequence4 cutoff already returned.

770's post-advance sequence0/frame7/timer0 sets BYTE655=1, calls actual
`Fighter_finalize_sequence_entry @45D110` with-1, publishes texture6/duration-1,
then calls actual `Fighter_copy_action_word_176_to_174 @45B250`. WORD stores are
76C=0,76A=1,766=0,768=0,764=0, then event23. The private prefix exposes those
offset-asserted fields; it retains all prior offsets/size. The native fixture
uses inactive phase55A=0 and does not claim active score/event publication.

795 subtracts widened0.3f only in sequence0;797/798 use current AY. Crossing
sets sequence1;797/798 also dispatch event30 and place x480/x800. Shared47B837
then samples height, zeroes motion and returns.795 uses47B835 to call the
virtual sequence setter first. Without crossing, completion selects700 for
795/798 and0 for797 via shared47BFB0. Live entry registers are DX=0,BP=7,
BX=-1,CX=1;770's frame test is7, not another caller's shared-tail constant.

## Focused verification

```bash
scripts/compile-unit.sh src/characters/ReimuActionStateDispatch.cpp build/reimu-high-final/ReimuActionStateDispatch.obj
python3 scripts/audit-reimu-high-final-actions.py build/reimu-high-final/ReimuActionStateDispatch.obj
```

VC8 SP1 `/O2 /GS- /GR /EHsc /MT`, default FP/no injected environment,
produces46640 staged text bytes. Object SHA256
`93a74ca696437f3a2dec66e51185c95a3d195b88927f3942a9eece6dd0461a2f`.
`build-receipt.json` pins compiler/source/header/object hashes and a fresh
pre-edit5f30ef4 baseline. That baseline passes the old0/104 smoke. Under the
new852-case integration domain it differs once:798 now executes its real body
where the old source returned pending. The other851 cases agree.

**0/11820 differences**, `build/reimu-high-final/native.json`, input SHA256
`ebd6a7861452a4065ee96cd88d3e0a8bd059adb78e73e946a8089266d0c039c5`.
There are10364 genuine RETs,1400 actual465190 stops,30 effects,12 common entries,
1 set669 and13 pending (including the eight740 cases).10381 target/6732 staged
root instruction addresses are sampled. Real MT-next/random-roll helpers each
execute2267 times; texture publication270, inactive finalization/WORD copy64 each.

|Cohort|Cases|
|---|---:|
|Motion/landing/completion/NaN|864|
|Sequence/counter/timer/frame nodes|2304|
|720 scales/alpha and real random-position/mode branches|720|
|730 signed cadence/modes/angles/facing|2160|
|740 signed modulo, WORD limits, three MT seeds and cutoffs|4088|
|760 signed phase/timer/health cascade|720|
|770 real finalization/texture/WORD-copy contexts|60|
|17 required original sites, both x87 precisions|34|
|740 unresolved stack-read boundaries|8|
|Earlier high/middle/low/entry/common paths|852|
|Gaps/defaults and upper handoffs|10|

The oracle compares4096 actor bytes, ordered actual calls/receivers/arguments,
complete live-stack payload/count/content, texture-manager slots, world scalar,
MT state/index and x87 control word. RET requires stack delta4, preserved
registers and x87 TOP=0. It pins both new helper byte envelopes and checks that
finalization's active score path is outside this fixture.901 requires four
floats;902/903/905..908 require three. Mode/cadence/finalization and unresolved
fixtures require their original branches/requests. No callback result or target
instruction is patched. Flat surface, read-only animation/texture IDs, inactive
indexed/secondary/score paths, zero sound handles and masked PC53/PC64 bound
this evidence. Returning world calls and full floating exceptions are unknown.

Compiled negatives detect18/216 for720's mode0 variant1->2,84/720 for making
760's second health gate an else-if, and8/56 for740's >= cutoff becoming>.
Reports/private build receipts remain; rejected source/objects are removed.
Six old adapters rebuild with identical non-debug code/data/relocations,
sizes530,771,1562,4017,4409,11271; smokes pass0/9,0/88,0/64,0/99,0/150,0/59.
No old full matrix or cold aggregate replay was run. Accepted units, profiles,
relocation ledgers and exact totals remain unchanged.

The prior direct Ghidra receipt covers these eight final bodies. Current
canonical body/instruction/auxiliary-table bytes and all9 unchanged primary
hashes are rechecked; no new process/clone. Wrong-target IDA is recorded and
unused. Prior objects, baseline, rejected controls and caches are cleaned.
Next reconcile the740 undefined paths, complete the original void ABI/default
surface and establish truthful full-function compilation/comparison. Returning
world contexts and VC8/LTCG/TU provenance remain parent acceptance requirements.
