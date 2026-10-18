# Reimu214: effect lifetimes and repeated resource gate

This checkpoint concerns root478FA0 in the hash-attested original Japanese
TH1051.06a target. Target/callable hashes remain those in
[the entry record](REIMU_ACTION_ENTRY_2026_10_17.md). IDA preflight rejects
the different attached executable. All new target observations are raw PE
instructions; no analysis database was launched or changed.

## Positive target facts and selected source

214's effect125 call47BD23 keeps direction and arg5=1 pending before sine
47BCC6: MOVZX at47BCB3, pushes47BCC0/47BCC1, then its phase argument. Rounded
Y replaces that phase slot before cosine47BCF2. Signed facing for X is read
after cosine at47BCF7. Earlier velocity lookups are cosine47BB34/sine47BB4E;
both pairs execute actual target lookup/fabs/control-word/conversion code.

The source already retains the unsigned direction snapshot and the required
rounded coordinate expressions. Moving those expressions inside the effect
call recovers their outgoing lifetimes with the pinned VC8 compiler. It
does not add a helper, change field layout/ABI/flags or infer original source
spelling. Named-coordinate source remains a compiled negative control.

The adjacent resource gate at47BD28..47BD66 loads DWORD6C8 once, tests its
cached value twice, and repeats the signed WORD736/482 comparisons. There is
no intervening write or call. The complete reviewed root CFG supplies only
local incoming edges to the second gate; none of its11 switch tables enters
the gate interval. This closes the hidden shared-root-entry explanation,
without claiming all possible external incoming edges have been classified.

Raw corroboration within other same-target provisional roster-root spans
finds repeated ESI+736 comparisons at Yuyuko55F231/55F24C and
Komachi5E3C43/5E3C5F; Udonge5C1D8C has one observed comparison. Their nearby
6C8/482 tests support a related source/context question. These observations
do not establish shared source, original inline helpers, volatile fields or
compiler flags. The ordinary single source condition remains unchanged.

## Native evidence

The new240-input cohort crosses six phases, five raw facings, both steering
modes, both x87 PC53/64 settings and heights100/681. Initial sequence1/3 agrees
with post-steering horizontal velocity, avoiding a sequence callback that
would reset the frame counter before the advertised effect. Counter0 advances
to1 through the real frame helper. Target checks require real resource cost,
two sine/two cosine calls and the actual effect125 request.

At the second lookup of each kind, the void-root harness reads above its real
cdecl phase argument: eight bytes of direction/arg5 at sine entry, twelve
bytes of Y/direction/arg5 at cosine entry. Return-address qualification excludes
initialization calls outside the root. This observation writes no machine
state and neither replaces nor stops lookup execution.

| Compiled candidate / cohort | Inputs | Mismatches |
| --- | ---: | ---: |
| Preceding expanded object, new lifetime observations |240|240|
| Selected staged late-low method, effect cohort |240|0|
| Selected staged method, steering/flight exit |720|0|
| Selected expanded root, effect cohort |240|0|
| Selected expanded root, integration/default/guarded740 |1528|0|

All720 staged steering/exit cases reach genuine RET. The1768 expanded inputs
include1230 RETs; effect/object/common/setter cases stop at actual entries,
and eight740 inputs stop before indeterminate reads. Returning-world
continuations and arbitrary caller stacks remain unproved. No full historical
matrix or aggregate cold replay ran. The preceding control object is SHA256
`d7fc04128ef631dce0829a97d2d11773f8b541fda81f749ed4d7293bf97e3bfd`.
The240-input SHA256 is
`69c69022779a1a253bc04c18d876a5108229ab55fd44adeb7e41a5cd20bb33db`.

## Complete candidate result

Code prefix81416/text82788 shrinks128 bytes from the preceding checkpoint;
frame570h remains. Source has20265 reachable instructions versus target20243.
All11 switches, nine buffer partitions and550/551/669 preparation contracts
pass. Genuine linked/ordinary replay agrees over all82788 payload bytes,
SHA256 `63c73a0ec4f4f0acda5d8344faa2b2f2e30dacd6a8995bb1e59aeacff092ab02`.
It qualifies2467 fields(1179 calls,1104 literals,14 metadata pointers,
163 code pointers,seven global addresses),1281 HIGHLOW entries and the
separate12-byte next-owner INT3 gap. The linked DLL is not executed.

First strict target difference moves from+17 to+18/478FB2: PUSH EDI agrees,
but the candidate clears EDI and stores DI where target stores an immediate
WORD zero. This is diagnostic movement, not exact or partial-byte credit.
Root remains unclassified/declaration-only. Source advance sites remain119
versus target121.209/221 share47B5CD;522/523 stay separate485898/485C78;
310 joins215/797 at47BFCF, unlike target31047D94A versus215/79747BFB2.
300/320 remain completely merged. Original visibility/compiler context,
the duplicate resource predicate and whole-root exactness remain open.

Ordinary object SHA256:
`fc96ec6699e7672671db4996be5b517d75db3c22785e0c2470ff621ba03cdbb1`.
Linked image SHA256:
`035d55da7ecbe12e7eb0310ae999ecd803b32fabd29de8d8043c105981da860a`.
Fragment CRLF SHA256:
`e58093a603f7a1e042f1a1a9eb650f7ba6d29685de8f8e9e55364ada1f15e7b7`.
Current receipts are under `build/reimu-flight-gate/` and `build/reimu-ltcg/`.
Run heavy commands serially with `nice -n 10 taskset -c 0`:

```bash
python3 scripts/probe-reimu-action-ltcg.py
python3 scripts/audit-reimu-linked-coff.py build/reimu-ltcg/receipt.json
python3 scripts/audit-reimu-root-stack.py build/reimu-ltcg/ordinary.obj --require-contracts
python3 scripts/audit-reimu-void-root.py build/reimu-ltcg/ordinary.obj --cohort flight_effect_lifetimes
python3 scripts/audit-reimu-void-root.py build/reimu-ltcg/ordinary.obj --cohort integration --cohort defaults --cohort unresolved740
python3 scripts/ci.py
git diff --check
```
