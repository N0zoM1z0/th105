# Reimu: effect124 lifetimes and physical sharing

This continues [the effect123 checkpoint](REIMU_RANDOM_EFFECT_LIFETIMES_2026_10_18.md)
inside Reimu root478FA0, with the same hash-attested Japanese1.06a target
and81550-byte callable. Preflight again rejects the different IDA target;
all new target observations use canonical PE bytes. No Ghidra process,
shared ABI/layout/profile change, source selection or exact credit is involved.

## Target evidence and source

The four effect124 paths have the same live outgoing arguments across their
two real MT calls as the previously reviewed effect123 paths:

| Action | First MT call | Second MT call | Effect124 call | Direction |
| --- | --- | --- | --- | --- |
|223|47C427|47C459|47C48D|unsigned byte facing|
|224|47C666|47C698|47C6CC|unsigned byte after NEG DL|
|225|47C854|47C886|47C8BA|unsigned byte after NEG DL|
|226|47CA12|47CA44|47CA78|unsigned byte facing|

Before the first draw, X+double50 is saved to m64 and direction/arg5=1 are
pending. Rounded Y from unsigned modulo200 is pending before the second
draw; unsigned modulo100 is subtracted from the saved X base for rounded X.
The source retains its double snapshot and byte direction, and now expresses
the two rounded calculations inside each effect124 call. There are three
source expressions, expanded to four action bodies. The pinned VC8 build
evaluates Y before X; no general C++ evaluation-order guarantee is inferred.
Original source spelling and compiler visibility remain unknown.

## Native evidence and controls

The new320-input cohort crosses four actions, five raw facings, two MT seeds,
both x87 PC53/64 settings and X=-0/640/2**20/2**25.223 starts at frame count4
on the surface so its real advance reaches5;225/226 use sequence2. Target
checks require two real MT calls and an actual effect124 request. Existing
read-only snapshots compare direction/arg5 at draw1 and Y/direction/arg5 at
draw2.224/225's expected outgoing direction is negated modulo256. The oracle
does not write stack bytes, replace helper results or bypass actual MT code.

| Compiled candidate | Inputs | Mismatches |
| --- | ---: | ---: |
| Preceding expanded root, new observations |320|320|
| Selected staged late-low method |320|0|
| Staged method with wrong unnegated224/225 direction |320|96|
| Selected expanded root, both lifetime cohorts |720|0|
| Selected expanded root, integration/default/guarded740 |1528|0|

The baseline control is the preceding ordinary object SHA256
`2db6449a4c8f96d427765934f87309afc4cf80f60ceae5c45fc6448014859e77`;
its build input, object and replay receipt were retained before rebuilding.
Its world request values can agree despite the pending-argument differences.
The separate wrong-direction control detects actual outgoing direction errors.
The2248 expanded inputs stop at real RET/helper/world-request boundaries;
returning-world continuations and arbitrary stack contexts remain unproved.
No full historical matrix or aggregate cold replay ran.

## Whole-root results

The new81544-byte code prefix/82916-byte ordinary payload grows240 bytes;
frame570h remains. There are20333 reachable candidate instructions versus
20243 target. Both reviewed windows fit, with6/8 bytes spare. All11 switches,
nine buffer partitions and550/551/669 preparation contracts pass. Whole-root
sharing changes, so no unaffected suffix identity is claimed.

522/523 now have separate advance sites4858D8/485CB8, corresponding to target
48599F/485D75;209/221 still share47B5DD, corresponding to target47B51B. Source
advance sites rise from118 to119 versus target121. Remaining deficits are
300/320's completely merged bodies and310 joining215/797's advance. Other
call-site ownership differences remain. This is static topology evidence,
not per-input multiplicity, original compiler context or byte acceptance.

Genuine linked/ordinary replay agrees over all82916 payload bytes, SHA256
`2672556d0298e501e595aa4136b07195b9f55fea3d0b9a40a0d5d1ca9a6d66ed`.
It qualifies2468 fields(1180 calls,1104 numeric literals,14 metadata pointers,
163 code pointers,seven global addresses),1281 HIGHLOW entries and the
separate12-byte next-owner INT3 gap. First strict target difference remains
+17/478FB1. Root stays unclassified/declaration-only; no acceptance ledger changes.

Ordinary object SHA256:
`d7fc04128ef631dce0829a97d2d11773f8b541fda81f749ed4d7293bf97e3bfd`.
Linked image SHA256:
`48fbfa88ae159086c4f7ce4ff5ad45ca4b7af7c606b0e330009f940e52cb9c1f`.
Fragment CRLF SHA256:
`e967cd518c1c51fba31ad98d6ff8c8c669343b885c80b17c9b83ef8dadc0a4ed`.
The720-input SHA256 is
`ef23617286b58721ae04f28241e001adec20c7857eae429d538c04c71d7460c3`.
Receipts and controls occupy `build/reimu-sharing-review/`; current genuine
link products occupy `build/reimu-ltcg/`. Run heavy commands serially with
`nice -n 10 taskset -c 0`:

```bash
python3 scripts/probe-reimu-action-ltcg.py
python3 scripts/audit-reimu-linked-coff.py build/reimu-ltcg/receipt.json
python3 scripts/audit-reimu-root-stack.py build/reimu-ltcg/ordinary.obj --require-contracts
python3 scripts/audit-reimu-void-root.py build/reimu-ltcg/ordinary.obj --cohort random_lifetimes --cohort random124_lifetimes
python3 scripts/audit-reimu-void-root.py build/reimu-ltcg/ordinary.obj --cohort integration --cohort defaults --cohort unresolved740
python3 scripts/ci.py
git diff --check
```
