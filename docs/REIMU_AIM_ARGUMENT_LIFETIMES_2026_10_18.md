# Reimu: atan2 argument lifetimes

This checkpoint remains inside the81550-byte root478FA0 of the hash-attested
original Japanese1.06a target. Target/callable hashes remain those in
[the entry evidence](REIMU_ACTION_ENTRY_2026_10_17.md). IDA preflight rejects
the different attached executable. New observations below use canonical PE
instructions; no analysis database or target bytes were changed.

## Target and source

The clamped aiming paths prepare X on the outgoing stack **before** reading
peer Y. The target rounds X, writes ESP+4, loads peer Y, subtracts self Y,
rounds/writes Y at ESP, then calls atan2_degrees406540. Source formerly
computed two named float locals before preparing either argument. It now
keeps the rounded deltaX local and computes rounded deltaY inside the call.
Arithmetic, signed facing, clamps, ABI/layout and compiler flags are unchanged.

| Action | First target atan2 call | Second target atan2 call | Raw73-byte preparations equal |
| --- | --- | --- | --- |
|400|47DF03|47E039|second|
|401|47E44A|47E577|second|
|404|47EBCC|47ED11|second|
|406|47F1CE|47F307|both|
|410|47F60B|47F788|both|
|414|47FBA3|47FD29|both|

These are internal preparation intervals, not function boundaries. There are
four edited source expressions, expanded to12 physical sites. The shot pair
is410/414;412 does not use this source block.710/711's already-inline geometry
was inspected and left unchanged.

## Read-only native observation

The new600-input cohort crosses12 instruction-pinned target sites, five raw
facings, both x87 PC53/64 settings and five geometries, including X=2**25.
Geometry avoids the unmodeled returning CRT domain-error path. Ground and
airborne Y values preserve the actual landing/frame guards.

Only this cohort installs a memory-read observer, removed in a finally block.
At the root's actual peer-Y read it records ESP+4. At the real atan2 entry it
records both actual arguments above the return address. Target self-validation
requires exactly one peer-Y observation and one call, the advertised target
call site, and equality between pending X and actual X. No mirrored geometry
formula supplies that expected value. Helpers execute unchanged and the
observer writes no machine state or substituted result.

| Actual compiled candidate | Inputs | Differences |
| --- | ---: | ---: |
| Preceding ordinary root, new observations |600|600|
| Preview expanded ordinary root |600|0|
| Final genuine-build ordinary root |600|0|
| Final integration/default/guarded740 |1528|0|

The final600 comprise400 genuine RETs and200 actual object801 entries. The
other1528 retain1230 RET/82 object/30 effect/177 common/one setter/eight
guarded740 endpoints. Thus2128 final expanded inputs pass; no full historical
matrix or aggregate cold replay ran. Baseline examples have equal actor bytes
and actual atan2 arguments while the pending-X observation differs. Returning
world callbacks, arbitrary stacks and unmasked floating exceptions remain
unproved. The600-input SHA256 is
`129c2949d42e739ffde0c9093e2438f25e0a711aea2ccace2405d438b160dc87`.

## Full-payload locality and exactness limits

Complete typed A/B replay compares the preceding82916-byte canonical payload
`e14328a2455420de790de6089e123046fe083ce8f8b1a5f2f5265817df75d7e9`
with current
`826889ee7ec055e44def5cc1602de2fae75f58403e2332194ec3b20cd55dc0d3`.
Only240 bytes change,20 inside each73-byte argument preparation. Every byte
outside those12 intervals is identical, including subsequent CALL encodings,
branches and switch metadata. Prior physical call-sharing observations
therefore remain current; this edit does not resolve their unknowns.

Nine complete preparations equal target bytes without normalization. The
source bytes were independently checked against raw COFF text, so relocation
replay masks nothing in these intervals. The first400/401/404 preparations
differ only at offsets8/26: the signed-facing MOVSX and its temporary store
use ECX where target uses EDX. Native arguments agree; original register/
compiler context is unknown. This evidence assigns no exact or partial credit.

Prefix81544/text82916/frame570h and first strict+17/478FB1 remain. All11
switches, nine default buffer partitions and five545/546/550/551/669 circular
preparation contracts pass. Genuine linked/ordinary replay agrees over all
82916 payload bytes, qualifying2466 fields(1178 calls,1104 literals,14 metadata
pointers,163 code pointers,seven global addresses),1281 HIGHLOW entries and
the separate12-byte next-owner INT3 gap. The linked DLL is not executed.
Root remains unclassified/declaration-only; implementation/exact ledgers stay
unchanged.

Final ordinary object SHA256:
`41bf3b15ff2dbf6cf7c25e0c0191ab18d963782e0e7fab5d3b9af82c0ab245fd`.
Linked image SHA256:
`7c58cd311800f91d99225a0090582cbce489d6c23b14f66fa4ec089798a8a2b3`.
Receipts, the baseline control and locality/equality packets occupy
`build/reimu-aimed-lifetimes/`; current link products occupy `build/reimu-ltcg/`.
Run heavy commands serially with `nice -n 10 taskset -c 0`:

```bash
python3 scripts/probe-reimu-action-ltcg.py
python3 scripts/audit-reimu-linked-coff.py build/reimu-ltcg/receipt.json
python3 scripts/audit-reimu-root-stack.py build/reimu-ltcg/ordinary.obj --require-contracts
python3 scripts/audit-reimu-root-stack.py build/reimu-ltcg/ordinary.obj --action 545 --action 546 --action 550 --action 551 --action 669 --require-contracts
python3 scripts/audit-reimu-void-root.py build/reimu-ltcg/ordinary.obj --cohort aim_argument_lifetimes
python3 scripts/audit-reimu-void-root.py build/reimu-ltcg/ordinary.obj --cohort integration --cohort defaults --cohort unresolved740
python3 scripts/ci.py
git diff --check
```
