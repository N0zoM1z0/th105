# TH10.5 reconstruction handoff

Exact-first reconstruction checkpoint: 2026-10-24. Remilia input policy
`0x556070` and independently reviewed Tenshi `0x64B7A0`, Sakuya `0x4DF4B0`,
Suika `0x5AED00`, Youmu `0x53B410`, Yuyuko `0x56DEB0`, Yukari `0x58C2E0`
Iku `0x631340`, Komachi `0x5F7AB0`, Aya `0x618660`, Alice `0x4FACD0`,
Reimu `0x494810`, Udonge `0x5D2C70` and Patchouli `0x51EF60` cold-replay exact.
The fourteen-function cohort adds87251 code bytes; latest peer adds6351 and
matches its first complete source. All fifteen roster slot50 policies now have
complete source. Marisa7664/full7768 remains nonexact and parked after neutral
controls. The next large representative is Marisa CPU slot58 `0x4B4070`: its
complete source now compiles and passes1134 scoped native-helper inputs; the
full16867-byte output remains nonexact at+12E. Native exits/ordered predicates
and a real h180 equality error are recovered. Residual physical tail merging
is recorded; select another complete representative unless new evidence appears.
Required commit format:
`gpt-6.1-sol: ...`.

Current priority remains complete large-function exactness before gameplay
naming. Keep necessary types, offsets, numeric states, control flow and side
effects, and compare the entire function early. The read-only TH075 review is
in [the workflow](RE_WORKFLOW.md#exact-first-priority-from-the-th075-review).
Its VC7.1 compiler settings do not transfer to this VC8 target.

The renewed user direction is to prioritize complete medium/large functions,
compare the first complete source early, test one evidence-backed hypothesis
per trial, and switch candidates after repeated neutral controls. Follow a
successful representative through independently reviewed family differences.
Keep large execution matrices scoped to concrete ambiguities and defer naming,
beautification and abstraction. Compile serially at CPU0/nice10 and monitor
available memory/swap. Commit and push stable checkpoints only after local CI.

## Start here

Read [AGENTS.md](../AGENTS.md), [architecture](ARCHITECTURE.md),
[workflow](RE_WORKFLOW.md), relevant source and the scoped evidence before edits.
Use one writable session, one bounded scope, no subagents/concurrent VC8 builds;
claims.csv stays header-only. Heavy commands use CPU0/nice10.

Only original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.

```sh
git status --short
python3 scripts/verify-target.py
python3 scripts/check-ida-mcp.py
python3 scripts/report-reconstruction-status.py --summary
python3 scripts/validate-tracking.py --require-target
```

IDA still opens database SHA256
`10350095bcf95edb59e03bee9849a2dc8a7714b4927ad5909c569c550fce6822`.
Its failed preflight blocks that session's semantics and writes. Raw inspection
of the hash-attested target PE remains available. Independently attest any
Ghidra import and use at most one process; preserve primary analysis databases.

| Ledger layer | Current value |
| --- | ---: |
| Provisional candidates | 4024 |
| Authored / excluded / origin review | 1595 / 1418 / 1011 |
| Mapped / source-present | 1536 / 1518 |
| Accepted authored exact | 1395 functions / 322165 bytes |
| Provisional authored byte denominator | 2136806 |
| Match units / configured functions | 560 / 1528 |

These are ledger totals, without a new aggregate cold replay. Replay affected
accepted units after shared changes; aggregate claims require a cold
`python3 scripts/verify-exact-units.py --all`.

## Current bounded representative: Marisa CPU policy 0x4B4070

[Complete source and residual](MARISA_CPU_TARGET_2026_10_24.md) retains16229
callable target bytes/4159 instructions/46 RETs/161 direct calls and16907 full
target bytes. Selected full16867-byte payload remains nonexact at+12E:
`b7872facbcbe0e9019026385d84694d52beb3e0d8eeecda5459b3411fda23127`.
All eight destination/four index tables remain; no exact credit.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit exact-first-marisa-cpu-policy --compare --json
python3 scripts/audit-marisa-cpu-policy.py
taskset -c 0 nice -n 10 python3 scripts/audit-marisa-cpu-policy-paths.py
```

Canonical commands correctly return1; scoped execution returns0 on1134 inputs.
The new h180 cases reject all four pre-fix inputs; actual gate is >=180. Native
seed54 positively pins grounded/airborne opponent tails to vertical1/0, rejecting
a mistaken zero-output ownership inference. That failed experiment was never
selected. Ordered velocity/height checks, angle producer/consumer widths,
integer thresholds, explicit action exits and policy214 sharing now follow raw
instructions. First-stage1291 and attack1254 instruction counts agree; this is
not canonical equality. Current source has119/121 selector sites and45/46 RETs;
policy0's17/16 duration calls still merge with18. Approach100 placement, one
shared facing tail and minor output scheduling remain. Original TU/compiler
context is unknown, with no proof that LTCG is required.

Receipts cover probe00..probe24 changes. Approach-label18 is byte-neutral;
repeated-assignment23 still does not recover block placement or missing calls;
independent-posture24 loses three more physical copies and is unselected.
Park unchanged controls and select another complete representative; reopen only
with independent source/lifetime evidence. Prior visibility/FP/profile trials
remain parked. No shared source/header/layout/flag or relocation changes.
This root is distinct from input4B9FA0. Recipes/reports remain under
`.analysis/exact-first-marisa-cpu-20261024/` and its `build/` counterpart.

## Exact family peer: Patchouli input policy 0x51EF60

[Accepted peer/evidence](PATCHOULI_INPUT_POLICY_2026_10_24.md) closes1810
instructions/35 RETs/six tails and all11 table entries. Callable6351 and full
6396 bytes/128 relocations match in the first complete source and independent
formal/cold builds:

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit exact-first-patchouli-input-policy --compare --json
python3 scripts/audit-patchouli-input-policy.py
```

Full canonical SHA256:
`9f517cea7b41772006c05e97ef82af42ef960a44bcc54a27c7ee250160b07e6a`.
Actual ground208/209 defaults, air201, fifth flag758, signed tier611, backward
407/409 paths, nested post-query vertical reread and double120.0 are independently
reviewed. Generated-table negative fails at+18D0. No source correction or compiler
controls; earlier accepted sources/mappings are unchanged. All15 complete slot50
policies have source,14 accepted exact. Select a fresh complete representative;
Marisa's unchanged OR/shared-label placement trials stay parked.

## Exact family peer: Udonge input policy 0x5D2C70

[Accepted peer/evidence](UDONGE_INPUT_POLICY_2026_10_24.md) closes1919
instructions/40 RETs/six tails and all10 table entries. Callable6684 and full
6724 bytes/135 relocations match in the first complete source and independent
formal/cold builds:

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit exact-first-udonge-input-policy --compare --json
python3 scripts/audit-udonge-input-policy.py
```

Full canonical SHA256:
`20fb17b9a6f95c25aff1e7810bbd682c60f140bef07ba14f5d5df1e66eb9d31d`.
Actual ground201/204 defaults, air200/202/205, tiers, repeated308, float90.0,
three-float848 spawn packets and post-reset word7A6 clear are independently
reviewed. Existing66-byte465190 spawn ABI is freshly checked and unchanged.
Generated-table negative fails at+1A1C. No source correction or compiler controls;
earlier accepted sources/mappings are unchanged. Continue Patchouli's complete
slot50 peer; Marisa stays parked at its recorded placement residual.

## Exact family peer: Reimu input policy 0x494810

[Accepted peer/evidence](REIMU_INPUT_POLICY_2026_10_24.md) closes1992
instructions/42 RETs/seven tails, nine destinations and all20 remapped edges.
Callable6952 and full7008 bytes/142 relocations match in the first complete
source and independent formal/cold builds:

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit exact-first-reimu-input-policy --compare --json
python3 scripts/audit-reimu-input-policy.py
```

Full canonical SHA256:
`ab3651e356c3b26be806d10352bd9c5af0ea8c8c8101e4addfba7c262926125a`.
Actual ground input initialization before the third deque read/default switch,
sparse records, query500/502 versus action501/503, double120.0 and different
window/resource order in groups6F8/6FC are independently reviewed. Generated
destination/remap negatives fail at+1B28/+1B4C. No source correction or compiler
controls; earlier accepted sources/mappings are unchanged. Continue remaining
complete peers; Marisa stays parked.

## Exact family peer: Alice input policy 0x4FACD0

[Accepted peer/evidence](ALICE_INPUT_POLICY_2026_10_24.md) closes1912
instructions/40 RETs/seven tails and all10 table entries. Callable6677 and full
6720 bytes/132 relocations match in the first complete source and independent
formal/cold builds:

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit exact-first-alice-input-policy --compare --json
python3 scripts/audit-alice-input-policy.py
```

Full canonical SHA256:
`3b430021d2cc28d0ce1810de20a55331bcc62ffe584828375424624301cba764`.
Actual eager input initialization, signed words7A4/7A6 after window calls,
query546/545 versus action543/542, surface==1, one air308/416 and float140.0
are independently reviewed. Generated-table negative fails at+1A18. No source
correction or compiler/source-shape controls. Earlier accepted sources/mappings
are unchanged. Continue remaining complete peers; Marisa stays parked.

## Exact family peer: Aya input policy 0x618660

[Accepted peer/evidence](AYA_INPUT_POLICY_2026_10_24.md) closes2021 instructions/
39 RETs/seven tails and all13 table entries. Callable7161 and full7216 bytes/
146 relocations match in formal and independent cold builds:

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit exact-first-aya-input-policy --compare --json
python3 scripts/audit-aya-input-policy.py
```

Full canonical SHA256:
`27ca5b6b8e56b4099e251f654b0f53b24ba4100eb13fe96a79df110ba65377da`.
The first complete comparison differs only at two height-condition bytes.
Native TEST AH,41 plus JP after FCOMP480.0 admits equal; correcting < to <=
makes the entire payload exact without compiler/source-shape controls. Sparse
ground/air records, actual shared action numbers, air2000's distinct override
flag, one normal-air308, resource skip and repeated416 paths are independently
reviewed. Generated-table negative fails at+1BFC. Earlier accepted sources and
mappings are unchanged. Continue complete remaining peers; Marisa stays parked.

## Exact family peer: Komachi input policy 0x5F7AB0

[Accepted peer/evidence](KOMACHI_INPUT_POLICY_2026_10_24.md) closes1762
instructions/34 RETs/six tails and all12 table entries. Callable6181 and full
6232 bytes/124 relocations match in the first complete source and independent
formal/cold builds:

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit exact-first-komachi-input-policy --compare --json
python3 scripts/audit-komachi-input-policy.py
```

Full canonical SHA256:
`8d53e8dd92bdea44be96ed4ef0ded1fae0fb68e336f8e07edd721bc735c5c012`.
Ground207..210 defaults, actual ignored-result air45D1B0 call without air deque
reads, changed tiers, state303 fallback, float140.0 and air406/405/404 order are
independently reviewed. Generated-table negative fails at+1828. No compiler or
source-shape controls; earlier accepted sources/mappings are unchanged. Continue
remaining complete peers while preserving Marisa's parked residual.

## Exact family peer: Iku input policy 0x631340

[Accepted peer/evidence](IKU_INPUT_POLICY_2026_10_24.md) closes1813
instructions/36 RETs/nine tails and all11 table entries. Callable6302 and full
6348 bytes/131 relocations match in the first complete source and independent
formal/cold builds:

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit exact-first-iku-input-policy --compare --json
python3 scripts/audit-iku-input-policy.py
```

Full canonical SHA256:
`5628641c925c65b24ce8feae7a7be22d6e680d8ffa83ee05de4dc5029931f7a3`.
Ground204 default, air200/210/default early return, distinct query/action numbers,
state300-to321, double120.0 and direction-negative417 are independently reviewed.
Generated-table negative fails at+18A0. No compiler/source-shape controls;
previous accepted source/header and mappings are unchanged. Continue the
remaining complete peers while preserving Marisa's parked residual.

## Exact family peer: Yukari input policy 0x58C2E0

[Accepted peer/evidence](YUKARI_INPUT_POLICY_2026_10_24.md) closes1734
instructions/26 RETs/seven tails and all16 table entries. Callable6233 and full
6300 bytes/129 relocations match in the first complete source and independent
formal/cold builds:

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit exact-first-yukari-input-policy --compare --json
python3 scripts/audit-yukari-input-policy.py
```

Full canonical SHA256:
`6ad4c81e95ea54236fdcd3de48e1a8fa897f8f1a1d4deb83173f335138a9ef7d`.
Existing58C170 gate, sparse215 selector, distinct query/action numbers, actual
pre-action12C clears, double120.0 and query/resource order are independently
reviewed. Generated-table negative fails at+185C. No compiler/source-shape
controls; earlier accepted input and gate sources are unchanged. Continue the
remaining complete peers while preserving Marisa's parked residual.

## Exact family peer: Yuyuko input policy 0x56DEB0

[Accepted peer/evidence](YUYUKO_INPUT_POLICY_2026_10_24.md) closes1773
instructions/36 RETs/seven tails and all9 table destinations. Callable6180 and
complete6216 bytes/125 relocations match after formal and independent cold builds:

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit exact-first-yuyuko-input-policy --compare --json
python3 scripts/audit-yuyuko-input-policy.py
```

Full canonical SHA256:
`7fd52536151126351f5ec2fd4d7f9464d2316f912e25607c89700a9f8d0efe87`.
The first full comparison caught only copied4941D0 minimum2 versus native1 at
56DFE8. Correcting it matches the whole body without code-generation controls.
Actual4000/2000 masks, signed zero gates, air201/207 records,180.0f and repeated
normal queries are independently reviewed. Generated-table negative fails at
+1824. Prior accepted sources/mappings remain unchanged. Continue complete
slot+50 peers while leaving Marisa's neutral placement controls parked.

## Parked complete peer: Marisa input policy 0x4B9FA0

[Complete source/evidence](MARISA_INPUT_POLICY_2026_10_24.md) closes2151
instructions/36 RETs/15 tails and both20+6-entry tables. Callable7664/full7768
source remains nonexact at+1AF5; no matches row or authored exact credit.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit exact-first-marisa-input-policy --compare --json
python3 scripts/audit-marisa-input-policy.py
```

Both comparisons currently return1. Selected full canonical SHA256:
`53acd36513eee03fe5ea95775c31ff5827e4ec01d903fb2abef9bbc71983fd1c`.
All104 metadata bytes match;104 callable bytes differ only within4BBA95..4BBB37.
The first comparison caught a misread second412 success edge; native4BBB36
enters the shared mode gate at4BBAD1. Corrected short-circuit OR and explicit
shared-label sources produce identical whole payloads. Keep the ordinary OR
source, park this physical-block placement residual and switch to another
complete peer. Mode reads after the first action in group6F8 remain distinct
from pre-action mode choices in group6FC. No compiler search/LTCG impossibility.

## Exact family peer: Youmu input policy 0x53B410

[Accepted peer/evidence](YOUMU_INPUT_POLICY_2026_10_24.md) closes1714
instructions/28 RETs/nine external tails and all8 table destinations. The first
complete compiled source matches6017 callable/full6052 payload bytes and121
relocations; formal and independent cold builds pass:

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit exact-first-youmu-input-policy --compare --json
python3 scripts/audit-youmu-input-policy.py
```

Full canonical SHA256:
`050e801122ba3cee6da69fb3abdcca297922e24d08913ef938c1b4e42a962fa1`.
Three real slot0C sequence calls,540 continuation, changed command tiers,
air queued pack-only exit,double100.0/float90.0 and actual query/resource order
are independently reviewed. The generated table negative fails at+1784. No
compiler/profile search; previous accepted headers/sources are unchanged. Keep
the unrelated nonexact YoumuObject initializer parked as documented below.

## Exact family peer: Suika input policy 0x5AED00

[Accepted peer/evidence](SUIKA_INPUT_POLICY_2026_10_24.md) independently closes
1667 instructions/31 RETs/six external tails and all9 table destinations. The
first complete source matches5849 callable/full5888 payload bytes and117
relocations; formal and independent cold builds pass both commands:

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit exact-first-suika-input-policy --compare --json
python3 scripts/audit-suika-input-policy.py
```

Full canonical SHA256:
`aad5c91e0526eabc05c81285aa78e1723f0adbccb30f92f8745ce47724f4940b`.
The generated-table negative fails at+16DC. +60D tier531/530, shared545 success,
air523/522 zero gates and508/507 tiers, record200-to650,160.0f and reordered
normal-air policy are independently reviewed. No source correction or compiler
search was needed. Earlier exact input sources remain unchanged. Continue the
other complete slot+0x50 peers with independent target review.

## Exact family peer: Sakuya input policy 0x4DF4B0

[Accepted peer/evidence](SAKUYA_INPUT_POLICY_2026_10_24.md) closes1687
instructions/33 RETs/six external tails and independently checks all10 table
entries. The first complete source matches5897 callable bytes and the full
5940-byte payload/120 relocations. Formal and independent cold builds pass:

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit exact-first-sakuya-input-policy --compare --json
python3 scripts/audit-sakuya-input-policy.py
```

Full canonical SHA256:
`57689f32d9ee39731ad0682f45652b77a0f9c6e26323c9e879fe61a9504812c3`.
The generated-table negative fails at+170C. Ten queued commands, changed tier
fields/action pairs, air+608/+60C zero gates, repeated308/400 queries and90.0f
are target-reviewed. No compiler/profile search or source correction was needed.
Prior accepted inputs are unchanged. Continue complete slot+0x50 peers under
independent review and both callable/full-payload comparisons.

## Exact family peer: Tenshi input policy 0x64B7A0

[Accepted peer/evidence](TENSHI_INPUT_POLICY_2026_10_24.md) independently closes
1515 instructions/26 RETs/seven external tails. The5352-byte callable and full
5384-byte payload/108 relocations match after separate canonical and cold builds.
Replay both commands:

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit exact-first-tenshi-input-policy --compare --json
python3 scripts/audit-tenshi-input-policy.py
```

Full canonical SHA256:
`20bb75cd53cebe9b7714eb97bc8fdd4160b2310e2599d38aaef74acbb2b064d5`.
A table-byte generated-object negative fails. Changed special-command tiers,
signed+82E gate, record207-to657, normal state200 transitions, absent Remilia
cleanup/shortcuts and140.0f distance are independently reviewed. Correcting
one copied541 fallback to the actual540 yields zero differences and the native
shared block; no flag/profile or register search. Prior exact inputs stay intact.

Next, continue another complete Fighter slot+0x50 peer from the two accepted
representatives, reviewing its actual changes before comparison. Keep views
pointer-only and do not normalize query/action-number differences or repeated
calls. RemiliaObject's initializer below remains nonexact and parked.

## Exact representative: Remilia input policy 0x556070

[Accepted source/evidence](REMILIA_INPUT_POLICY_2026_10_24.md) closes all1470
instructions/16 RETs/eight external tails. Both the5415-byte callable and the
complete5448-byte payload/112 relocations match after independent cold builds.
Replay both commands:

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit exact-first-remilia-input-policy --compare --json
python3 scripts/audit-remilia-input-policy.py
```

The complete canonical SHA256 is
`aa8fea23fd443bab1f58993e3f8d41f3ee7d262b70f2ea3d5ec74a6e75c3dcec`.
A generated-object table-byte negative fails the full-payload audit. Source
retains numeric commands, offset fields and real repeated queries. Two initial
query/action-number mistakes were corrected from native pushes; removing an
eager queued-field cache recovers the native range guard. No compiler/profile
or hierarchy search was needed. Only the representative earns credit; callees
remain at their previous states. Never instantiate/embed its pointer-only views.

Next, review another complete Fighter primary slot+0x50 peer against this
representative, independently checking changed gates, command/action pairs,
offsets, ABI and exits. Preserve RemiliaObject's nonexact checkpoint below;
do not resume neutral initializer-register trials without new evidence.

## RemiliaObject initializer 0x55BE70

[Complete source/evidence](REMILIA_OBJECT_ENTRY_2026_10_24.md) covers the
4997-byte callable and full5384-byte payload, including all three destination
tables and the199-byte remap. Unit `exact-first-remilia-object-entry` freshly
builds and remains nonexact at+0x80. The selected full canonical SHA256 is
`d114fd28eaefcbc4fb8f1c8ebe1ceb7512661cdabb05624179ec85bab5be2aac`.
All21 conversion/virtual calls,42 RNG calls, seven motion calls, two spawns and
both replacements are present. Explicit used casts retain product rounding;
a double captures851's input float across its byte write without an extra spill.

Residuals are selector-call registers,901's shared heading-block placement and
the980 CALL+RET versus target tail JMP. Named-field versus offset access is
byte-neutral, and terminal/default controls regress the remap range. Do not
repeat these controls unchanged. The selected receiver is declaration-only;
never construct/embed it. No exact credit, runtime matrix or LTCG impossibility.

The subsequent input-policy representative above is exact; this initializer's
source and retained controls remain a separate nonexact checkpoint.
Read-only Ghidra was independently attested; all pinned primary DB
files are unchanged. Receipts/recipes are under
`build/exact-first-remilia-entry-20261024/` and
`.analysis/exact-first-remilia-entry-20261024/`.

## AyaObject update 0x61A290

The initializer and update now share
[AyaObjectActionView.hpp](../src/characters/AyaObjectActionView.hpp), removing
duplicate receiver declarations. Its 15 offset assertions and 0x388 prefix-size
assertion express a partial call view; never construct or embed it. The actual
primary vtable `0x6C624C` owns update slot+0x28 and initializer slot+0x3C.
Slot+0x0C consistently takes short. Aya's vtable `0x6C62D4`, published by the
constructor at `0x61861C`, and AyaObject both bind that slot to `0x45C390`.
No original complete allocation or TU identity is claimed.

| Method / unit | Callable / complete payload | Current result |
| --- | --- | --- |
| `0x61A290`, `gpt-web-aya-object-vslot28-full-root` | 19522 / 20000 | Nonexact +0x22 |
| `0x61F0B0`, `gpt-web-aya-object-action-entry` | 4531 / 4859 | Two differences: +0xBF7 / +0xBFF |

Current raw CRLF source SHA256:

- [Update](../src/characters/AyaObjectActionState.cpp): `15a6f13a5ea5a751fa7f6cec6dbffed628bd373e0bb29e984788f8bbefbe0a72`.
- [Initializer](../src/characters/AyaObjectActionEntry.cpp): `fa06d792237a849bb70c2cc7dc1a38e92bb0b8bcce056bb26c7914e945cd4280`.
- Shared header: `2ed12ce922918d59726cc45f0fcc8c514a43b3c1cec0b13c1a0f8a64ad8728c5`.

Both complete canonical payloads equal the preceding separate views:
update `5f2966cb6b34c844d210ac54e52894b5d510c17362c3fe2424c1d2de6b89c4ec`,
initializer `6f70b6f354fdff459a628bdfbf0a7a3c12fe854a65f95f6cf33731b5d606b066`.
Only receiver declarations, member qualifications and their unit-local symbol
aliases changed. Earlier runtime matrices retain their recorded scope; this
checkpoint proves machine-payload equality and makes no fresh runtime claim.

The selected update still has the partial807/817 frame-tail join, used817/822
angle captures and local double quantized lookup views. It has12 physical frame
helper calls versus target11. See the [selected evidence](AYA_OBJECT_PARTIAL_FRAME_TAIL_2026_10_23.md)
and [epoch index](AYA_OBJECT_EVIDENCE.md) for behavioral contracts and limitations.

A new retained lead defines the real frame/phase methods under the common
receiver. Both source orders reproduce helper `0x4351C0` 62/62 and `0x64CD00`
73/73, and reduce update's frame-helper calls12 to11. However, the update grows
to20032 bytes, SHA256 `23925cd489b690a45c7c49f04f52dacac967c01896200853c4ef95069d5655e6`,
and stays nonexact at+0x22; the initializer still differs at two bytes. This TU
is unselected. A matching call count is a diagnostic, not acceptance. Receipts:
`build/aya-joint-owner-20261024/summary.json` and its archive/restore manifest.

For continuation, compare which frame call disappeared in that TU with the
target's physical tail/return graph. The initializer's856 pointer register
lifetime remains unknown. Six common-receiver/ABI controls preserve the selected
payloads; an int sequence declaration regresses the initializer. Prior source
order, getter/lifetime, /Zi, FP-profile, hierarchy and linked-context controls are
recorded in [the initializer evidence](AYA_ENTRY_SEQUENCE_WORD_ABI_2026_10_19.md).
Do not repeat those unchanged trials. Later C2 patches remain untested; the
archived download listings and inspected Vista package did not yield a backend.

## Other open roots

| Root | Retained result | Evidence |
| --- | --- | --- |
| ReimuObject `0x496540` | Full45696, nonexact +0x1F; adjacent counter `0x4963A0` 66/66 exact | [Current index](REIMU_OBJECT_EVIDENCE.md), [owner/joint context](REIMU_OBJECT_WORD_OWNER_JOINT_CONTEXT_2026_10_23.md) |
| Reimu initializer `0x4A1CE0` | 14 differences; genuine joint CIL still nonexact | [Joint context](REIMU_OBJECT_WORD_OWNER_JOINT_CONTEXT_2026_10_23.md) |
| Youmu initializer `0x543670` | Callable5159/full5492; 21 register/preparation bytes differ; metadata agrees | [Current evidence](YOUMU_ENTRY_PHYSICAL_TAIL_2026_10_23.md) |
| AyaObject initializer `0x61F0B0` | Callable4531/full4859; two register bytes differ | [Current evidence](AYA_ENTRY_SEQUENCE_WORD_ABI_2026_10_19.md) |

Youmu's retained canonical SHA256 is
`d00f4fc4ceca80c8fc4510ff03dcf064e3188fa5dc33afc8e25815d880da413a`;
source SHA256 `66d01e60ca540b11515ebe4a58dc87f913ab340dd4845bcb1e992d9000c9be2d`.
Its physical copy count, read order and all332 metadata bytes must be retained.
Sequence selector `0x45C390` uses real checked `std::map::find`; its accepted
10-function native unit and independent short witness passed at `de8037a`.
Its 105-byte generated find remains excluded library code. No new replay of
that unit or the 592-case Youmu matrix is claimed here.

Other pending roots include Reimu Fighter `0x478FA0`, CGage `0x41B3F0`, loader
`0x40B000` and renderer `0x415050`. Font evidence remains in
[begin](TEXT_FONT_BEGIN_CONTEXT_2026_10_22.md),
[glyph](FONT_GLYPH_WINDOW_PROOF_2026_10_22.md),
[accent](TEXT_FONT_ACCENT_LIFETIMES_2026_10_22.md) and
[markup](FONT_MARKUP_CONSTRUCTION_CLEANUP_2026_10_22.md).
Older handoff detail is available at Git `4dd8436` and in the
[October23 narrative](RE_HANDOFF_HISTORY_2026_10_23.md).

## Artifacts and final gate

Generated artifacts belong under `build/`; private recipes/analysis under
`.analysis/`. Preserve compiler installs, target resources, primary analysis
state and the native-provider inputs referenced by retained CIL receipts.
Completed controls are archived only after every member's length/hash is
checked; per-scope `retention.json` files provide exact restore commands.
The cleanup inventory is `build/handoff-cleanup-20261024/retention.json`.
Legacy `.analysis/gpt-web` exports were archived with a restore command there;
six historical worktrees with uncommitted source were left untouched.
Do not use indiscriminate `git clean` or delete unknown analysis state.

Focused commands, run serially; both Aya comparisons currently return1 because
their recorded mismatches remain:

```sh
python3 scripts/build.py --unit gpt-web-aya-object-action-entry --compare --json
python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
```

Before any commit, push or PR, run in the finished worktree:

```sh
python3 scripts/ci.py
git diff --check
```

The local gate is mandatory and must follow the final tracked edit. Target
observations, source hypotheses, runtime contracts and canonical acceptance
remain separate. No assembly, copied target arrays, inert locals, fake returns,
ABI lies or padding may be used to force a result.
