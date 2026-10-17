# Reimu730: separate cadence/request modes

## Target facts and source change

Target remains original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Parent `Reimu_dispatch_action_state_vslot28 @478FA0` remains81550 bytes,
SHA256 `dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
The candidate/origin/name/source ledgers remain authored,
unclassified/declaration-only. No source-present or exact credit is added.

Action730's physical owner `[48C1F8,48C720)` contains1320 bytes/332
instructions, SHA256
`7aece8b846adce70c2d48d02b647ebd506145ecea8e8a649081ff1c3af1e1773`.
All retained encodings/body bytes were rechecked against the canonical PE.
Its table48D35C selects four mode arms, physically ordered0,1,2,3:

|Mode|Signed counter cadence|Angle float|Speed float|
|---|---:|---|---|
|0|8|current73C|4|
|1|6|current73C|4|
|2|5|current73C|float32(4-unsigned roll5 * double(0.1f))|
|3|4|float32(saved double(73C+7)-unsigned roll14)|float32(4-unsigned roll10 * double(0.1f))|

Mode3 saves the double angle before its first draw. All modes set the third
float to2, then use real sine/cosine and current coordinates/facing for902.
One shared spawn tail is at48C6F7..48C701. After return,48C706 reloads the
current73C and adds double2 before storing float32. The same increment occurs
on valid non-firing frames; modes above3 bypass it. Negative counters use
signed remainder. These are instruction observations, not decompiler types.

`ReimuActionStateHighFinalCases.hpp` now spells out these four cadence bodies,
with one real float[3] across mutually exclusive arms and inline coordinate
arguments. Snapshot/random order and the common fresh post-request phase
increment are preserved. Shared730/760 entry, movement, initial objects,
sequence4 exit and760 health phases are unchanged. Original source spelling
and compiler/TU ownership remain hypotheses; no accepted header/layout/profile
or relocation changes were made.

## Focused build and execution

```bash
scripts/compile-unit.sh src/characters/ReimuActionStateDispatch.cpp build/reimu-730-mode/ReimuActionStateDispatch.obj
python3 scripts/probe-reimu-action-source-shape.py --output-dir build/reimu-730-mode/expanded
python3 scripts/audit-reimu-730-mode-shape.py build/reimu-730-mode/ReimuActionStateDispatch.obj
python3 scripts/audit-reimu-730-mode-shape.py build/reimu-730-mode/expanded/ReimuActionStateDispatch.obj
```

The a534de3 baseline passes0/12 smoke and0/128 new extreme-counter cases.
VC8 SP1 `/O2 /GS- /GR /EHsc /MT`, default FP, produces:

- Compact object: `20b59762a7950f6e5677e9c69e0027c3b2ecb5226c690a76200e7b5ec838e87e`.
- Three-region probe: `82e2a8510ea89e7ddc684a8d425a65b0bcf726d2cd609f492646ba234d94ba34`.

Both pass **0/3676 native differences**, input SHA256
`085365f14b11cf1a563447aaf443d95bfad04f7ec0895880115ba5daada31045`.
The matrix has108 motion,288 nodes,2160 cadence/angle/facing cases,6 required
branches,128 extreme signed-counter cases and986 earlier/current integration
cases. The new extremes includeINT_MIN/INT_MAX and genuine native counter wrap
fromINT_MAX. At both x87 precisions, target guards require the real902 entry
exactly when the post-advance signed counter is divisible by8/6/5/4.
The extreme cohort has40 object stops and88 genuine RETs. A compiled mode2
cadence5->6 mutation is detected in **16/128** of these cases.

Full-matrix stops are3029 genuine RETs,609 object requests,30 effects,6 common
entries,1 set669 and1 pending. Actor bytes, real MT state/draws, helper order,
arguments/first pointed payload and RET stack/register/x87 state are checked.
The oracle stops before returning world requests; it does not execute the
emitted path's subsequent phase increment. Static byte inspection separately
confirms a fresh73C load, double2 addition/store and RET after the candidate's
shared last spawn at COFF+1364E. Its literal is checked as
`__real@4000000000000000`. This is a continuation fact, not fabricated callback
execution or a whole-function proof.

All8 earlier710/711 static mode contracts,4 720 contracts and48 510 packets/
12 level reloads still pass on the new expanded object. No old full matrices
or aggregate cold replay was run.

## Structural result and remaining work

The unchanged mapper retains45/50/33 primary groups,126 destinations and0
splits. Candidate730 grows862->1322 bytes versus target1320. Its four modes
now contain separate sine/cosine paths feeding one shared902 call, with
signed power-of-two masks and two IDIVs as observed in the target. No compiler
flag change or artificial dependency was needed.

Expanded text grows82088->82628; its first table moves80764->81288. Decoded
E8s grow1164->1171 versus target1188. RETs remain149 versus153; indirect
switches grow8->9 versus11. Frame598h versus570h remains the first diagnostic
mismatch at478FA8. The pre-table deficit is262 bytes. These are alignment-
inclusive diagnostic spans, not accepted compiler boundaries or equality.
The existing reviewed metadata ceiling is unchanged.

Reports, current PE packet and build/control receipts are below
`build/reimu-730-mode/`. The earlier direct Ghidra receipt is reused after
current byte checks and all9 unchanged primary hashes. No new process/clone
or IDA semantics. Superseded720 objects/source copies, the rejected control
and caches are removed; current objects/source and bounded evidence remain.
Next reconcile740's two mode switches and undefined paths, then the original
void/default ABI, returning world contexts and full relocation/VC8/LTCG
provenance before canonical acceptance of the81550-byte root.
