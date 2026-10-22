# AyaObject902 payload snapshot and spawn-prefix recovery

## Scope and evidence

Observed against original Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Bounded root61A290 remains19522 callable bytes/4630 instructions/seven switches.
IDA preflight still rejects the other open image; all new observations use the
hash-attested PE and relocated VC8 COFF. This supersedes the current-source
selection in [phase reset](AYA_OBJECT_902_PHASE_RESET_2026_10_22.md), retaining
that correction. No shared header, ABI, helper, profile or relocation changes.

At61E497..61E511 the target stores angle/15/1 into the actual payload, then
reads payload[0] for its two direction comparisons. The two outgoing argument
prefixes differ in side+1/-1 before joining their coordinate/call suffix.
The low-sequence speed branch physically precedes the high-sequence branch.
The source now expresses that order, snapshot and two actual spawn calls.
This is a supported source shape, not proof of original C++ spelling.

Serial complete-root controls (canonical full payload):

| Control | Bytes | SHA256 prefix |
| --- | ---: | --- |
| Payload read only |20056|ef90c284|
| Separate calls |20068|62f4923b|
| Low-sequence branch first, selected |20064|d08781e4|

Recipes/sources remain in `.analysis/aya-902-spawn-20261022/`; receipts and
objects in `build/aya-902-spawn-20261022/`. The predecessor is committed7b5d2cf
and its object SHA256 is
`3acfaf6c9f02463855acfc9b928915b863bbb5f012a723670b06a06ca7e03536`.

## Executed validation

`audit-aya-object-902-spawn-prefix.py` executes the actual root entry until
original spawn64CCB0 entry, recording all seven outgoing words, twelve payload
bytes, receiver, stack depth, actor writes/memory and x87 status/tag. It does
not execute that helper or fabricate a return. All3744 prefixes agree with
target. The predecessor differs in2592 **x87 status only** observations;
arguments, memory, writes and tags already agreed. These are not2592 gameplay
bugs. Inputs cover sequences-1/0/1, thirteen angle bit patterns including signed
zero/subnormal/infinities/NaNs, three X positions, two facings/speeds and eight
masked precision/rounding controls. Negative sequence is an ABI boundary
fixture, not a claim of reachable gameplay state.

`audit-aya-object-902-phase.py` now adds960 no-spawn speed/sequence cases to
its3328 actual-animation cases. All4288 complete-return cases agree, including
1440 original next-block calls. The77-byte target phase window is selected
within the independently mapped action902 owner, avoiding an identical window
in another action. Speed cases include signed zero, finite limits, infinities
and NaN. Neither finite input enumeration establishes arbitrary resources,
unmasked exceptions or full spawn/callback behavior.

The default strict outside902 instruction-labelled graph check **fails**:
21 operand changes occur in action903. Optional `--dead-carriers` separately
qualifies nine short windows: four owner-pointer MOV/CMP pairs, four facing
MOVSX/spill pairs, and one LEA/three ADD/spill interval. It requires precise
register substitution in these templates, excludes alternate entries, and
checks both changed registers in both graphs until each byte is overwritten
or the void root returns. It continues past normal calls; a generic ABI
clobber is not treated as a defined value. Only4351C0's known AL return
defines that byte. Branch successors and
partial-register reads are checked; live ECX at a thiscall is rejected.
The only permitted call contracts are the recovered, separately exact57-byte
435160 and62-byte4351C0 thiscall helpers. Their target hashes are recorded.
No generic volatile-register wildcard was added; default strict mode remains.
Nine regression controls include partial writes, taken-branch reads, unknown
calls, reads after a call clobber, live this arguments and changed memory addresses.

With this explicit qualification,4418 paired normal-return nodes outside902
agree. This is conditional normal-ABI equivalence, not equality of all raw
register observations, arbitrary callbacks, exceptions or canonical bytes.

## Selected comparison and remaining work

Action902 now has target652 bytes/159 instructions. Spawn argument instruction
differences disappear in owner diagnostics. Remaining differences are four
scratch operands (ESP+18 instead of+14), switch-table placement, and match-mode
comparison/shared movement-exit placement. Owner diagnostics are4/34 and confer
no exact credit. Action903's register changes are qualified as above.

Configured root comparison remains **nonexact at offset34 (hex22)**,
target0F versus candidate59. Metadata begins19596 versus target19524.
Full canonical20064-byte SHA256:
`d08781e483c6d906dfce2de93a56b5df0bca35d541564ad28f5d9655addc53c3`.
Compared19522-byte window SHA256:
`e51da96720d42d51649f5df692080214f82b3d3fa3004e889c64b59b812c63ad`.
Selected COFF SHA256:
`9f6c9296ff5579a14c8ecc99566d3fb8aa43a965d408e7644356c7ce360f9968`.
Exact ledgers remain1381 functions/234914 bytes; no aggregate replay claim.

## Reproduction

Run serially with CPU0/nice10. The configured comparator exits1 for the pending
root. Use a separately rebuilt predecessor object for the optional regression
comparison; do not silently substitute another source epoch.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
taskset -c 0 nice -n 10 python3 scripts/audit-aya-object-902-spawn-prefix.py
taskset -c 0 nice -n 10 python3 scripts/audit-aya-object-902-phase.py
python3 scripts/audit-aya-object-normal-flow.py build/aya-902-spawn-20261022/previous.obj build/match-units/GptWeb_AyaObjectActionState.obj --exclude-action 902 --dead-carriers
python3 scripts/audit-giant-action-owners.py aya-object-vslot28 build/match-units/GptWeb_AyaObjectActionState.obj --unit gpt-web-aya-object-vslot28-full-root --json
python3 scripts/ci.py
git diff --check
```

Selected receipts: `selected-formal.json`, `selected-prefix.json`,
`phase-execution.json`, `other-graphs-qualified.json`, `selected-owner.json`
under the build directory above. Remaining scratch homes/physical tail sharing,
complete903 numerical behavior and native/LTCG context still need target-led
work. This result does not establish a standalone-object impossibility.
