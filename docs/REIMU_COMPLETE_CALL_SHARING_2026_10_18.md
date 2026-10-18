# Reimu: complete call-sharing sets and controlled exclusions

The current root has equal per-callee reachable call counts for all128
nondefault actions, but **eight callees have different complete sharing
partitions**. A subset such as6/7/8/9 cannot establish a site's full incoming
set. This checkpoint makes that distinction reproducible and corrects the
preceding landing-tail ownership shorthand. No root source or exact credit
changes.

## Identity and qualification

Original Japanese TH10.5 v1.06a SHA-256 is
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Root478FA0 owns `[478FA0,48CE2E)`,81550 bytes, SHA-256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
IDA metadata preflight rejects the other image; this work uses raw attested PE
and qualified VC8 COFF graphs, without database or instruction writes.

The current ordinary object remains SHA-256
`710094fe7ca95169efd3e53b66a41a8ab1f6ef1f44e83a9f4caea14ac920eca7`,
prefix81544/payload82916/frame570h. Its complete canonical payload is still
`a6dc1ccf19322b8ab5c431671d0d204d7b26b29c2c3f8c47292a1d332d44a6bc`.

## Reproducible complete-set census

```sh
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-call-sharing.py build/reimu-ltcg/ordinary.obj
```

The auditor inherits strict root relocation, stack, all11 switch and request
contracts. It obtains primary action entries from the unchanged canonical
mapper and separately proves the300/560 equality edges: signed WORD13C load,
attested entry receiver, unchanged flags and reachable JE destination. Missing,
ambiguous or split entries fail closed. All128 entries must be present.

For every reachable direct call and RET, it records the **complete** set of
nondefault action entries that can reach that physical instruction. It compares
multisets of these sets, retaining repeated sites with identical memberships.
Sites outside nondefault-action reachability retain an explicit empty set;
they are not silently dropped. Placement remains separately visible through
addresses. Four target-independent tests distinguish equal per-action counts,
matching memberships at different locations, repeated sites and empty sets.

This is bounded CFG reachability, not path feasibility, dynamic multiplicity,
argument/behavior equality or byte matching. A matching partition is never
canonical credit. The current result is32 callees, eight partition differences
and zero actions with per-callee count differences:

| Callee | Target physical sites | Source physical sites |
| --- | ---: | ---: |
|4351C0 advance|121|119|
|435240 effect|57|55|
|435D60 height|56|54|
|45AF40 clear motion|51|49|
|45C030 wave|77|76|
|465190 owned request|243|242|
|473DD0 landing transition|96|95|
|478EE0 directional gate|8|7|

One source height site479544 serves19 actions. Within that set the target has
four distinct groups:

| Target height site | Complete action set |
| --- | --- |
|479720|6,7,8,9,306|
|47B28B|208,209,210,211,221,222,309|
|47B839|212,220,308,795,797,798|
|47D639|307|

The preceding checkpoint did make6/7/8/9 share their landing helpers, removing
duplicate source sites, but **did not recover their complete target incoming
set**. Other height sites also have different combinations, including197/198
with608/658 and414/416 with522/523/614. Aggregate deficits can mask compensating
merges and splits elsewhere; use the full report.

The common advancement site has the same full set
`{0,2,9,71,72,74,145}` at target47973E/source4792D6. The epilogues implicated
by the first strict difference also have the same118-action reachability set:
target RET489D71/source RET489D50. Their placement differs. The byte+541 JNE
displacement is still compared strictly, without normalization or partial
credit.

## Four focused compiler controls

All controls use the current receiver/return-flow source and ordinary compile
receipt. They are private probes under `build/reimu-exit-flow/`, not selected
implementations or original-source claims.

| Control | Prefix / payload | First difference | Result |
| --- | --- | --- | --- |
|0..3 direct completion branch instead of temporary|81544 /82916|+541|Entire canonical payload unchanged|
|All height queries as one consistent member interface|81544 /82916|+541|Entire canonical payload unchanged|
|Mutually exclusive regions, one final common default|81560 /82932|+541|Default moves to end; oversize10/8|
|RTM42 compiler core, same SP1 headers/flags|81604 /82976|+541|Oversize54/52; not selected|

The completion control uses the consumed advancement result only for1/3 and
plain advancement for0/2. The height control changes every generated call from
the global fastcall pointer interface to one actor member declaration; both
binary interfaces supply ECX, have no stack arguments and return ST0. Original
membership is not proved, and no public ABI/binding ledger is changed.

The shared-default control produces one call at48CE28, near target48CE21,
instead of the current early source call47CC7B. Its entire source call-sharing
multiset remains identical to the current candidate for **all32 callees**.
The RTM control likewise preserves all32 source partitions. Neither fixes the
four-way target landing partition, despite different code placement.

RTM and SP1 core files are individually SHA-pinned and versioned14.0.50727.42
and14.0.50727.762. Only the compiler path changes; SP1 headers stay identical
to isolate core code generation. This is not a complete RTM environment or
original patch-level identification. The old pre-receiver RTM negative did
not cover this corrected source, so this fresh control is phase-specific.
The oversized controls are never executed; all normal admission guards stay
unchanged. Byte-identical controls require no repeated native matrix.

Receipts, full-set reports and compact comparison summaries remain below
`build/reimu-exit-flow/`. Heavy work was single-core, nice10 and serial; measured
full-census peak RSS was298300KiB, approximately291MiB. Primary database hashes
remain unchanged. Duplicate controls and generated binaries are disposable
after recording their receipts. No full historical or aggregate replay runs.

Next recover source/visibility and call-time state for the complete differing
sets. Keep the existing bounded candidate; do not repeat these four controls
at unchanged inputs or treat one subset's shared site as an ownership match.
