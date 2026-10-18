# Reimu: distinct shot guards recover complete landing-tail memberships

Restoring the separate sequence1/3 frame-start triggers in414/416 recovers
two complete target landing/height groups. VC8 now retains sequence3 in EDI
and shares the existing tails naturally. No named constant, helper, register
constraint, layout, signature or compiler-profile change is needed.
The whole root remains nonexact at+541; these are static sharing observations,
not partial exact credit.

## Identity and source change

Target is original Japanese TH10.5 v1.06a SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Root478FA0 owns `[478FA0,48CE2E)`,81550 bytes, SHA-256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
It stays authored/unclassified/declaration-only. IDA metadata rejects another
image; this work uses hash-attested raw PE and qualified VC8 objects. No
analysis database or target instruction is written; all nine primary database
hashes remain unchanged.

Observed target414/416 each retain distinct frame-counter/timer/index guards
for sequence1 and sequence3. The prior source combined the sequence tests
inside one guard. `ReimuActionStateMidShotCases.hpp` now spells the two
different triggers separately, preserving each setter/return. The second
trigger stays conditional on aerial for the combined410/414 source arm.
Both checks occur after actual advancement and any action0 callback, so no
state is captured across a callback. No identical inert condition is added.

The earlier int-direction control did not recover these groups. This new
control uses the independently supported byte-direction phase from
[the preceding checkpoint](REIMU_SPAWN_DIRECTION_WIDTH_2026_10_18.md).
The phase change is material; the old negative result does not answer it.

## Complete membership result

Fresh `audit-reimu-call-sharing.py` keeps all128 entries, physical multiplicity
and empty memberships. The following **complete** action sets now agree:

| Operation / complete action set | Target site | Current site |
| --- | --- | --- |
|Clear motion:414,560,561|47FA25|47FA6A|
|Height:201,224,414,560,561|47AD18|47AD8E|
|Slot C:201,224,414,560,561|47AD2B|47ADA1|
|Clear motion:416,522,523,614|47FFA4|47FEAF|
|Height:416,522,523,614|47FFAB|47FEB6|
|Slot C:416,522,523,614|47FFBE|47FEC9|

Before this change414 and416 each had a private landing tail; only522/523/614
shared the latter tail. The new416 entry at47FE49 starts MOV EDI,3, matching
the target's constant lifetime without an explicit source capture. Source and
target tails both push EDI and retain their original helper/virtual-call order.
Placement and other saved constants/edges still differ.

The current ordinary object SHA-256 is
`7fe0c1a8af90daac6d283539ebb28408f35e3920bea4e5bc7d17669d570e5744`.
Prefix81516/payload82888/frame570h stay unchanged in size. Source reachable
instructions fall20304->20284 and four duplicated direct calls disappear.
All2472 fields replay:1184 calls,1104 numeric,14 metadata,163 code pointers
and7 globals. All1281 HIGHLOWs, the separate8-byte INT3 gap,11 switches and
15 request buffer/preparation contracts qualify. The complete genuine linked
and ordinary payloads agree, SHA-256
`7816b79cb99e41884c292154c629ebb3bbad2abd612d5e2163ea66fbd05dc1b7`.
The private guard control has the identical entire canonical payload, so its
520/521 instruction/edge diagnostics remain applicable to this genuine build.

First strict difference stays+541=4791BD: JNE4791BB targets489D6A versus
source489D41. Eight direct-callee complete partitions still differ, with
zero per-action direct-callee count differences. Indirect physical totals now
agree220/220, but the same six aggregate action deltas remain:
73(3/2),75(5/4),88(3/2),200(3/2),410(4/3),416(5/4).
Matching physical totals do not establish per-action or dynamic equivalence.
The shared advancement, wave/request and virtual-next-block sets remain open.

A separate byte-variant argument-view control is not selected. The complete
4938D0 receiver consumes only the low variant byte, and a clean byte/byte
wrapper already reproduced66/66; neither fact determines the original formal
width. In this source phase the variant control first differs at+388 instead
of+541 and establishes no further accepted ownership result. It stays
read-only; the public variant view and binding ledger remain unchanged.

## Focused execution

```sh
nice -n 10 taskset -c 0 python3 -B scripts/probe-reimu-action-ltcg.py
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-call-sharing.py build/reimu-ltcg/ordinary.obj
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-void-root.py build/reimu-ltcg/ordinary.obj --cohort shot_boundaries --cohort integration --cohort surface_inputs
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-root-stack.py build/reimu-ltcg/ordinary.obj --action 522 --action 523 --native --require-contracts
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-trajectory-returns.py --output-dir build/reimu-shared-landings/current-trajectory
```

The current root passes0/2675:1380 focused shot inputs,1010 integration and
285 nonflat surface inputs. The new `shot_boundaries` adapter reuses1376
original410/414/416 motion/frame/counter/aim/cost/branch cases, plus four
sequence3 inputs requiring the actual414/416 action9 call sites and RET at
both x87 precisions. The first attempted airborne fixture was rejected: real
473DD0 selected action9 before the guard. Using the proved flat-surface input
preserves sequence3 until the original guard; the coverage assertion remains.

Aerial522/523 checks pass0/948 through real helpers/RET or first world requests,
including unmasked arguments and buffer identity. Complete815 returns pass
0/320 with1600 objects per process through real manager/callback/destruction
and full unmasked snapshots. No complete arbitrary-world/resource or exception
claim follows from these supplied contexts.
Current returning-host smokes also pass: owned0/14 with50 objects, circular
0/5 with99 objects and effect0/40. No full historical matrix was replayed.

Phase-specific receipts, access packets and controls are under
`build/reimu-shared-landings/`. Heavy jobs run serially with CPU0 affinity and
nice10. Duplicate/rejected objects and unused native snapshots are discarded
after recording hashes; preserve the current genuine provider cache. No
accepted source unit, exact ledger, aggregate cold replay or root credit
changes.
The genuine producer peaks at320944KiB (about313MiB).

Next recover the remaining complete advancement/wave/request and virtual-next
memberships. Keep the recovered landing groups intact; their target placement,
original TU/visibility and full callable equality remain unproved.
