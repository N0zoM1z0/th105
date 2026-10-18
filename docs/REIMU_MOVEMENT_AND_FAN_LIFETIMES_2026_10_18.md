# Reimu: movement and fan request lifetimes

This checkpoint remains inside root478FA0, the81550-byte callable in the
hash-attested original Japanese1.06a target. Target and callable hashes are
recorded in [the entry evidence](REIMU_ACTION_ENTRY_2026_10_17.md). IDA
preflight rejects the different attached executable. New target facts below
use canonical PE instructions; no Ghidra process or target-byte patch is used.

## Independent target observations

The movement200..203 effect124 preparations save X+double50 to m64 and retain
unsigned direction/arg5 before the first MT draw. Rounded Y from modulo200
is pending before the second draw supplies modulo100 for rounded X:

| Action | First MT | Second MT | Effect124 | Outgoing direction |
| --- | --- | --- | --- | --- |
|200|47AA11|47AA43|47AA77|unsigned facing byte|
|201|47AC89|47ACBB|47ACEF|unsigned byte after NEG DL|
|202|47AEAF|47AEE1|47AF15|unsigned facing byte|
|203|47B184|47B1B6|47B1EA|unsigned byte after NEG DL|

Source keeps the double and direction snapshots, expressing the rounded
coordinates inside the three calls expanded to four bodies. The new160-input
cohort crosses four actions, five facings, two MT seeds, both x87 precisions
and X=640/2**25.200 starts at count4 before real advancement; the others start
at5. Read-only MT-entry observations use the existing lifetime oracle and
require two actual draws plus effect124.201/203's direction wraps modulo256.

Separately,545/546's object821 requests retain count3, the three-float array
pointer, arg5=1 and unsigned direction **before** their sine lookups. Rounded
Y remains pending during cosine; signed facing times50 for X is read after
cosine. The integer multiplication and existing array identity are preserved.

| Action | Request | Sine | Cosine |
| --- | --- | --- | --- |
|545|486DE9|486D8B|486DBA|
|545|486E9A|486E3C|486E6B|
|546|487324|4872C6|4872F5|
|546|4873D5|487377|4873A6|

The two source loop sites now put their rounded coordinates inside the spawn
call. No helper, dummy local, layout change or compiler flag is introduced.
The CFG/ESP auditor explicitly reviews821/count3 and selects the two circular
sites from each arm's four physical requests. Existing822/count4 and869/count3
contracts retain their checks. Analyzer fixtures exercise all three contracts
against late pushes, wrong count/ID and reversed lookup order.

## Controls and final execution

| Compiled source / observation | Inputs or contracts | Differences |
| --- | ---: | ---: |
| Preceding expanded root, new movement lifetimes |160|160|
| Selected staged movement: lifetimes/input/coordinates |909|0|
| Movement-only root, old circular locals |2 action contracts|2|
| Final expanded root,545/546 matrix |2732|0|
| Final expanded root, movement lifetimes |160|0|
| Final expanded integration/default/guarded740 |1528|0|

The staged909 cases contain541 genuine RETs and368 real effect124 entries;
they include224 existing special-coordinate cases and525 input-boundary cases.
The expanded545/546 matrix has2260 RETs and472 actual object821 entries. Its
360 fan inputs cross signed skill levels, raw facing, phase and x87 precision.
The other expanded endpoints are the existing1230 RET/82 object/30 effect/
177 common/one setter/eight guarded740 endpoints, plus160 movement effects.
Thus4420 focused expanded inputs pass. Actual MT state/index and request
arguments are compared; world calls stop at real entry. Returning-world
continuations, later loop requests and arbitrary caller stacks remain unproved.
No full historical matrix or aggregate cold replay ran.

The preceding control object SHA256 is
`fc96ec6699e7672671db4996be5b517d75db3c22785e0c2470ff621ba03cdbb1`.
The160-input SHA256 is
`e2b6f9d92edaae556ed81875b60b71780cc63da60b1261e6226d3cd0c100b757`;
the2732-input SHA256 is
`14ce9a832ea6d38a0c9c8bd593e937c420e5b411a6b029a291be7c01322bf1c4`.

## Boundaries, full replay and remaining sharing

The movement-only intermediate has prefix81740/text83112 and first strict
difference+134/479026. It exceeds the callable/metadata windows190/188 bytes.
Only read-only diagnostics were allowed; that object was never executed.
The independently supported821 lifetime changes reduce the prefix256 bytes
to81544 and the payload to82916, restoring6/8 bytes of headroom. This is not
a boundary extension, truncation or padding workaround.

Final frame570h,20348 reachable source instructions(target20243), all11
switches, nine default buffer partitions and all five545/546/550/551/669
preparation contracts qualify. Genuine linked/ordinary replay agrees over
all82916 payload bytes, SHA256
`e14328a2455420de790de6089e123046fe083ce8f8b1a5f2f5265817df75d7e9`.
It checks2466 fields(1178 calls,1104 literals,14 metadata pointers,163 code
pointers,seven global addresses),1281 HIGHLOW entries and the separate12-byte
next-owner INT3 gap. The linked DLL is not executed.

Current first strict target difference is+17/478FB1: XOR EBX precedes PUSH EDI.
The intermediate's longer equal prefix is phase-scoped and does not describe
the selected source. Root remains unclassified/declaration-only, with no exact
or partial-byte credit. The six remaining direct-callee count differences are
advance121/119, effect57/56, wave77/73, owned object243/242, landing96/95 and
directional gate8/7(target/source). Cardinalities do not prove incoming sets:
source215 uses47BFC8 while310/797 share47D983; target shares215/797 instead.
Source522/523 share4859C6 where target separates them.209/221 correctly share
47B59E. Recheck300/320 and original visibility/profile before further tuning.

Ordinary object SHA256:
`0c189b55f5ab6c87914183183f5a1a3a03a64b5159546c9f1dac6566dfbc350d`.
Linked image SHA256:
`167cb81e6d300d785d6972f662a7378dbb364c5a606ef1facceac290009c12bf`.
Current receipts are under `build/reimu-movement-lifetimes/` and
`build/reimu-ltcg/`. Run heavy commands serially with `nice -n 10 taskset -c 0`:

```bash
python3 scripts/probe-reimu-action-ltcg.py
python3 scripts/audit-reimu-linked-coff.py build/reimu-ltcg/receipt.json
python3 scripts/audit-reimu-root-stack.py build/reimu-ltcg/ordinary.obj --require-contracts
python3 scripts/audit-reimu-root-stack.py build/reimu-ltcg/ordinary.obj --action 545 --action 546 --action 550 --action 551 --action 669 --require-contracts
python3 scripts/audit-reimu-root-stack.py build/reimu-ltcg/ordinary.obj --action 545 --action 546 --native --require-contracts
python3 scripts/audit-reimu-void-root.py build/reimu-ltcg/ordinary.obj --cohort movement_random_lifetimes
python3 scripts/audit-reimu-void-root.py build/reimu-ltcg/ordinary.obj --cohort integration --cohort defaults --cohort unresolved740
python3 scripts/ci.py
git diff --check
```
