# AyaObject900 coordinate and callback owner reads, 2026-10-22

## Observed and selected

This follows the [retirement-tail checkpoint](AYA_OBJECT_RETIREMENT_OWNER_READS_2026_10_22.md)
on update61A290. The independently attested Japanese1.06a target is unchanged;
IDA again rejects its open image and is not used. Fresh raw target reads show:

-61D85F tests owner action710 and branches before61D86E reads owner sequence.
-61D8BF writes owner X;61D8C5 reloads owner before the Y write at61D8D1.
-61D8F9 reloads owner and61D8FF reads its current sequence before slot0C.
-61DBC8 reloads owner after the spawn paths;61DBD0 reads sequence before slot14.

The source now preserves these boundaries rather than retaining the initial
owner/sequence across publications and calls. No shared type or virtual-call
signature is changed. Target slot0C's short-versus-int declaration remains a
separate ABI question; this checkpoint does not select a shared ABI change.

The complete root remains nonexact. Full canonical payload20044 SHA256:
`fe3b945a35860e7498f8075d87b18a3c6c0221343ff4ec926a3e5dc1faf93c7e`.
Metadata starts19576 versus target19524. Configured19522-byte window first
differs+0x22, target0F/source44; window SHA256:
`2e3a5abae68bb845a22bb37d3183bd16d991a8c76ff1702d5e5af60030e20120`.
No exact-ledger credit or aggregate cold replay is claimed.

## Source-lifetime controls

| Complete source control | Full bytes | Canonical SHA256 prefix |
| --- | ---: | --- |
| Previous retirement checkpoint |20028|b05357e6|
| Y/inside-stage owner reads only |20040|e73e891e|
| Plus postspawn owner read |20044|1029e623|
| Plus guarded initial sequence read, selected |20044|fe3b945a|

Removing the unnecessarily long-lived initial owner restores target EAX at
the initial owner load and EDI at the retirement decrement without register
forcing. The guarded initial sequence read moves MOVZX after the action-test
branch; it is no longer performed on rejected actions.

Three whole local intervals now match every byte under placement translation:

| Target interval | Bytes | Candidate start | Role |
| --- | ---: | --- | --- |
|61D8B9..61D915|92|61D925|X/Y publication and inside-stage selector gate/call|
|61DBC8..61DBEE|38|61DC34|postspawn owner sequence/slot14 and state publication|
|61DC18..61DC72|90|61DC84|retirement states, decrement and real epilogue|

These include internal relative branches and indirect-call instructions, but
not canonical function-address equality. The audit requires each complete
interval to occur uniquely in the relocated candidate. Earlier retirement76
is now extended through the actual RET. Root owner diagnostics remain3/34;
fresh raw target traversal still closes4630 instructions/all19522 callable bytes.
Movement scratch remains ESP+18 versus targetESP+14, and other900 control-flow,
physical tail sharing and remaining actions are not exact.

## Execution evidence and its limits

The existing `scripts/audit-aya-object-900-retirement.py` now additionally records
owner-pointer and initial-owner action/sequence read epochs relative to actual
object writes. It compares those reads separately from memory/write/x87 effects
when `--previous-object` is supplied.

Selected code agrees in all4792 actual root-entry/RET executions:

-2688 disjoint retirement cases from the preceding checkpoint;
-2048 disjoint movement cases: facing+/-1, heading -100.25/-0/+0/+100.25,
  two outside-stage X coordinates, owner sequences1/2, states0/2, four modes,
  eight masked x87 precision/rounding words;
-36 invalid-owner-action cases, proving no early sequence read on this matrix;
-20 previously documented artificial raw alias-stress cases.

All4772 normal and20 alias cases have identical final fixture memory, ordered
writes, x87 status/tag, and returned stack/callee-saved registers. Their owner
read traces also agree. Compared with the immediately preceding checkpoint,
ordinary effects remain equal but all4792 read traces differ. These are read
lifetime corrections, not evidence of4792 gameplay failures.

Movement values remain outside the stage and state364 skips spawning. No
opaque helper returns are supplied and no helper executes. The selector and
postspawn intervals therefore have static byte evidence, not full callback
execution or a proof that callbacks change ownership. Alias cases are raw
machine-memory stress fixtures, not legal C++ overlap/reachable game claims.
Unmasked exceptions, other action sequences and whole-game equivalence remain
unproven.

```bash
python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
python3 scripts/audit-aya-object-900-retirement.py
python3 scripts/audit-giant-action-owners.py aya-object-vslot28 \
  build/match-units/GptWeb_AyaObjectActionState.obj \
  --unit gpt-web-aya-object-vslot28-full-root --json
```

The first command intentionally reports a mismatch. Optional
`--previous-object PATH` supplies the old COFF for the scoped contrast. Private
control recipe/source inputs are under `.analysis/aya-900-read-epochs-20261022/`;
reports/objects are under `build/aya-900-read-epochs-20261022/`. Current configured
source uses `selected-formal.json`, `owner-audit.json`, and `execution.json`.
Local CI and whitespace gates are mandatory before commit/push.
