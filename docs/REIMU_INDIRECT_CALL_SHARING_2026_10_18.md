# Reimu: indirect call sharing and the 214 branch control

The complete root census now includes qualified indirect calls. The target has
220 physical sites and the current candidate211. Seven actions have different
reachable site counts. These are CFG facts, not missing dynamic calls or a
behavioral failure. Explicit facing branches recover214's14-site cardinality
in a private compiler control, but exceed the callable boundary58 bytes.
No game source, layout, binding, compiler profile or exact ledger changes.

## Identity and reproduction

Original Japanese TH10.5 v1.06a SHA-256:
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Root478FA0 owns `[478FA0,48CE2E)`,81550 bytes, SHA-256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
IDA preflight still rejects the other image. This unit uses raw attested PE
and qualified VC8 COFF, without analysis-database or target-byte writes.

Current ordinary object SHA-256:
`0a950c1fec476022ed45c663d529902c1b0393d679aa29d26d48a4f967d46c3c`.
The genuine linked/ordinary canonical payload remains82916 bytes, SHA-256
`9cdc589ffda90ef1828616df337228363291abe7e1487f781b7560d6c08e6766`.
Prefix81544/frame570h, all15 buffer/preparation contracts and11 switches
qualify. The strict first difference stays+541=4791BD, the JNE displacement
from4791BB into target489D6A versus candidate489D49. No normalization or
partial matching credit applies.

```sh
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-call-sharing.py build/reimu-ltcg/ordinary.obj
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-call-sharing.py build/reimu-direction-lifetimes/shared-speed/candidate.obj --diagnostic-oversize
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-linked-coff.py build/reimu-ltcg/receipt.json
```

Reports/receipts and private control recipes are below
`build/reimu-shared-sequence/`; they are disposable generated evidence.
The retained full-width direction control is the earlier positive witness
described in [the speed-lifetime checkpoint](REIMU_TRAJECTORY_SPEED_LIFETIME_2026_10_18.md).

## What the auditor establishes

The auditor reuses the existing relocation, stack and switch qualification,
then records complete reachable action sets for every indirect CALL alongside
the existing direct-call/RET census. Every reachable non-immediate CALL must
be a register call with qualified reaching slot-load definitions. Its physical
address appears exactly once. The slot candidates are load displacements,
**not identified methods or receivers**. In particular a site with possible
slots8/C remains one uncertain call, not two invented method calls.

Repeated memberships and sites outside all128 nondefault entries are retained.
The aggregate `indirect_calls` comparison removes slot-domain classification
before counting physical sites. A changed uncertainty domain can change the
per-domain counts without changing that aggregate. Six new tests guard mixed
domains, absent/phantom definitions, unknown slots, double counting and this
distinction; all10 focused tests pass.

| Slot-load candidates | Target sites | Current sites | Full-width control |
| --- | ---: | ---: | ---: |
|8|132|131|133|
|8 or C|2|1|1|
|C|51|48|49|
|14|35|31|33|
|All physical indirect calls|220|211|216|

All four candidate-domain partitions differ. Their per-action counts differ
for21 actions, but the aggregate physical-site counts differ for only seven:

| Action | Target reachable sites | Current reachable sites |
| --- | ---: | ---: |
|73|3|2|
|75|5|4|
|88|3|2|
|200|3|2|
|214|14|10|
|414|5|6|
|416|5|6|

The retained full-width control656acd1d... still has these same seven aggregate
deltas, despite restoring the complete owned243/wave77 partitions and reducing
direct-callee partition differences8->6. It remains read-only, prefix81688/
payload83060, oversize138/136. Thus the full-width lifetime result does not
close these indirect sharing questions.

All previous direct-call, RET, entry, graph and first-difference results for
the current object remain identical to the preceding report. There are still
eight differing direct-callee partitions and zero per-action direct-callee
count differences. CFG reachability does not establish path feasibility,
dynamic multiplicity, arguments, callback behavior or canonical equality.

## Focused source controls

The positive214 control expands its two ternary facing comparisons into
ordinary nested branches: first test facing, then the appropriate X comparison,
then keep the existing flip/setter or alternate setter. Each runtime path
retains its comparison and callback order at the source level. It adds no
resource gate, volatile read, forced register or duplicate inert condition.
This is a source-shape hypothesis, without a new native behavior proof.

| Control | Prefix / payload | Callable / metadata excess | Observation |
| --- | --- | --- | --- |
|Current source|81544 /82916|0 /0|214 has10 reachable indirect sites|
|214 explicit facing branches|81608 /82980|58 /56|214 has14, pure C-domain11/11|
|214 branches +414/416 post-advance sequence snapshot|81592 /82964|42 /40|414/416 still6 versus target5|
|214 branches +distinct414/416 frame guards|81608 /82980|58 /56|414/416 still6 versus target5|

The214 control object is
`f532efbe9f17d2b7ed02e529a06ba954c3b40d8c5e1850f298e8e57518c5e87f`;
generated source SHA-256
`5650d9bf90aa49164a384ae0badcb49fb406e64de72fcf46f01b8f636bab0b66`.
It has212 total physical indirect sites. Six aggregate action deltas remain;
214's cardinality agrees but its complete incoming partitions still differ.
The source still spells one ordinary resource condition. This is evidence
that branch shape can produce the target cardinality without fabricating a
second identical gate; it does not establish original source or visibility.

The target414/416 bytes retain two separate frame-start guard chains, for
sequence1 and sequence3, reaching one action9 setter. Current source combines
the sequence tests with OR. Target slot8 sites are47EDB4/47FA53 for414 and
47FE86/487495 for416. Current414 reaches47ED60/47F9E4/47FA27; current416
reaches47ED60/47FE0C/47FE4F. Restoring separate guards alone does not recover
the target sharing. The signed-WORD snapshot is taken after advancement and
any actual action setter, not before a callback. Neither control is selected.

Landing also differs beyond those counts: target416/522/523/614 share the
zero/height/setter tail beginning47FFA2;414 instead shares height47AD18 with
201/224/560/561. Target416 caches sequence3 in EDI; merely naming a real
constant consumed by its comparisons and landing setter leaves the retained
full-width canonical payload entirely unchanged. An ordinary static inline
helper for all26 zero/height/sequence triples remains an out-of-line call:
relocation qualification rejects the unmapped helper at+69FC. No fabricated
binding or forced inlining was introduced.

All oversized controls are read-only and never execute. The current genuine
candidate and its admission guards remain unchanged. No affected accepted
unit or native oracle changed, so no historical replay was repeated. Heavy
jobs run serially with CPU0 affinity/nice10; census peak RSS is298980KiB
(about292MiB). All nine primary database hashes are unchanged. Rejected
control objects and duplicate generated sources/headers are removed after
recording hashes; retain the useful214 and full-width positive witnesses.

Next recover compatible source/call-time lifetimes for the shared landing
exits and214 branches within the original envelope. Do not reinterpret static
site deficits as missing behavior, repeat unchanged controls, or weaken the
callable/metadata guard to execute an oversized candidate.
