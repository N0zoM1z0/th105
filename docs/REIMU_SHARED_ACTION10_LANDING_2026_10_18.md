# Reimu: one real action10 landing tail for202/203/225/226

The staged source now expresses the target's common landing block directly.
The complete four-action memberships agree for motion clearing, height lookup
and the action10 virtual call. Two extra height calls, two extra clear-motion
calls and two extra indirect calls disappear. Previously equal complete groups
remain equal, including owned243/243, wave77/77 and the six earlier landing
groups. The whole root is still nonexact at+541; no exact credit is added.

## Observed control flow and source

Target is original Japanese TH10.5 v1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The root is `[478FA0,48CE2E)`,81,550 bytes, SHA-256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
It remains authored/unclassified/declaration-only in the ledgers.

Observed202 falls through from its successful crossing test into47AE4A.
The other three entries have explicit branches to that same block:

| Action | Incoming branch | Common block |
| --- | --- | --- |
|203|47B13E JNE|47AE4A|
|225|47C80E JNE|47AE4A|
|226|47C9CE JNE|47AE4A|

That block calls45AF40 to clear motion, calls435D60 for the actual surface
height, stores Y, calls vslot8 with action10 and returns. Source previously
emitted three independent copies:202,203 and the225/226 pair.

An initial private control changes only the four landing exits to outer-switch
breaks. It merges202/225/226 but leaves203 separate. It is not selected.
The next control factors the actual block with ordinary C++ incoming `goto`
edges. All four actions then share it, as independently observed in the target.
No register constraint, artificial helper, extra read or dummy operation is
introduced. The source spelling is an inference; the target edges are facts.

`ReimuActionStateMovementAttackCases.hpp` now spells202 and203 separately,
retaining their distinct initialization timing and direction expressions.
202 contains `ReimuActionStateLandingAction10.hpp`;203 and the225/226 group
in `ReimuActionStateLateLowCases.hpp` jump to its function-local label.
The stand-alone late-low staging method includes the same real tail after its
switch. Its unknown-action default still returns false, while these handled
landing paths return true. The original void-root candidate and the bool
staging interfaces remain distinct. Class layout, signatures, flags and binding
ledgers do not change, and the source generator needs no special case.

## Complete correspondence

Fresh genuine ordinary object SHA-256:
`66fbf8ddf4504c8b9f5f26b4414cce387185bb588de20ae04906e053a2ddda1c`.
The complete82,808-byte canonical ordinary/linked payload is
`0622c8d3d8c86f4894f66dfa8425cd7e9f09900fd23e2bb1e6a8b582739813c9`.
Every byte also agrees with the private shared-tail control and the separately
compiled checked source. This establishes the selected source reproduces the
tested control; it is not a target-root equality claim.

Prefix81,436/payload82,808/frame570h fit the81,550/82,924 limits. The linked
envelope82,816 includes its separately proved eight-byte INT3 alignment gap.
All2,471 fields qualify:1,183 calls,1,104 numeric operands,14 metadata addresses,
163 code pointers and7 globals. All1,281 HIGHLOWs,11 switches and15 stack/request
contracts remain required. Source reachable instructions fall20,289 to20,257;
the target has20,243. No internal branch displacement or alignment is masked.

The following are complete memberships, not selected subsets:

| Operation; complete action set202/203/225/226 | Target site | Source site |
| --- | --- | --- |
|Clear motion|47AE4C|47C9B8|
|Height lookup|47AE53|47C9BF|
|Action10 virtual call|47AE67|47C9D3|

Total physical height calls now agree56/56 and clearing calls51/51. Their full
callee partitions still differ at other action sets; equal totals are not full
ownership recovery. All32 direct and aggregate indirect inventories retain
complete action sets, multiplicity and empty memberships. No previously equal
complete group regresses. Six direct-callee partitions still differ:
advancement121/120, effect57/55, height56/56, clearing51/51, landing96/95 and
action-gate8/7. Per-action direct-call cardinalities still agree.

Indirect physical totals are now220/219. Only410(4/3) and416(5/4) retain
aggregate per-action deficits. The first strict difference remains+541=4791BD,
in JNE4791BB: target489D6A versus source489CF0. The new payload is the same
size as the earlier rejected visible-height control, but has a different hash,
retains frame570h and preserves the target-style Y snapshot. Do not confuse
these source phases or infer equality from size.

## Focused verification

| Fresh check | Result |
| --- | --- |
|Root integration/default/common/unresolved740/nonflat surface cohorts|0/1,829|
|Affected movement/attack staging smoke|0/99|
|Affected late-low staging smoke|0/150|
|Affected integrated-low staging smoke|0/59|
|Real effect62 creation/callback/RET/destruction smoke|0/12|

The root set contains1,010 integration cases,510 boundary-default inputs,
16 genuine common returns,8 retained indeterminate740 boundary stops and285
nonflat-surface inputs. World-request cases keep their existing entry-stop
and argument-comparison scope; they do not acquire fabricated callback results.
Each of202/203/225/226 reaches target47AE53 twice and source47C9BF twice in
the surface cohort. The real surface data remains unchanged. These observations
exercise the recovered shared block, rather than merely selecting its cases.
The effect62 smoke uses the genuine returning backend from the prior phase.
Arbitrary world/resource graphs, later object ticks and exceptions remain open.

Public reproduction commands include:

```bash
nice -n 10 taskset -c 0 python3 -B scripts/probe-reimu-action-ltcg.py
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-call-sharing.py build/reimu-ltcg/ordinary.obj
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-void-root.py build/reimu-ltcg/ordinary.obj \
  --cohort integration --cohort defaults --cohort common_return \
  --cohort unresolved740 --cohort surface_inputs
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-shot-effect-returns.py \
  --output-dir build/reimu-landing-exits/effect62-smoke --smoke
```

Compile the three staging sources with `scripts/compile-unit.sh`, then use
their existing `audit-reimu-movement-attack-actions.py`,
`audit-reimu-late-low-actions.py` and `audit-reimu-low-dispatch.py` adapters with
`--smoke`. Exact commands, input hashes and terminal statuses are retained in
`build/reimu-landing-exits/validation-receipt.json`. No full historical matrix
or aggregate exact-unit replay is run.

Direct read-only Ghidra re-attests executable identity, entry, language/compiler,
all mapped `.text` and the full root hash before reading the four bounded
instruction windows. It independently reports all three explicit edges above;
no decompilation or saved metadata write occurs. All9 primary DB hashes remain
unchanged, and the temporary project alias is removed.

Heavy work stays serial on CPU0/nice10. The genuine producer peaks320,632KiB
(313MiB); focused validation306,940KiB (300MiB); bounded Ghidra307,564KiB
(300MiB),11.45s, with128MiB Java heap. Cleanup removes22 obsolete generated,
object and native products/2.71MiB, preserving all164 current genuine-cache
files, receipts and private recipes. Private control receipts describe their
preceding `c39c49b` input phase; regenerate that phase before repeating those
old source transforms against the now-updated cache.

Next address the remaining low9 and197/198/608/658 height/clearing memberships,
the separate300/320 prefixes and the remaining effect/landing/action-gate and
virtual-next exits. Preserve the complete groups recovered so far. Whole-root
byte equality and original TU/visibility remain unproved.
