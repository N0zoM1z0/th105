# Reimu740: both mode selectors and indeterminate locals

## Observed target and inferred source

Target is original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Parent `Reimu_dispatch_action_state_vslot28 @478FA0` remains81550 callable
bytes, SHA256 `dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
Candidate/origin/name/source rows remain authored, unclassified and
declaration-only. No implementation or exact credit changes.

The physical740 owner `[48C720,48C937)` has535 bytes/132 instructions,
SHA256 `b32f66936277d7426273bcd6d178f52e227779396d40fb399a267077fa525d56`.
All bytes/encodings and the two destination tables were rechecked against PE.

|Mode|Sequence1 cadence|Signed WORD730 limit|Duration|Sequence6 cutoff|
|---|---:|---:|---:|---:|
|0|10|6|80|60|
|1|8|8|80|60|
|2|6|11|80|50|
|3|5|14|80|30|

The first table48D36C lays out3,2,1,0; the second48D37C shares0/1. Out-of-range
sequence1 at48C772 reads one `[ESP+B4]` DWORD into divisor/limit/duration
registers. Sequence6 at48C8C4 reads the same slot into its cutoff. The prior
bounded record found no initialization on the reviewed entry/dispatch path.
The setup copy47095F..47096A loads a DWORD from MatchSetup and stores6FA894
without a range check at that copy. A global0..3 input-domain guarantee remains
unproved; these fallback instructions cannot simply be discarded.

`ReimuActionStateHighFinalCases.hpp` now uses two ordinary switches and
unassigned cadence/limit/duration/cutoff locals when no case matches. This
natural C++ hypothesis makes VC8 produce the target's three shared-slot MOVs,
per-arm duration LEAs and fourth cutoff MOV. The expanded candidate even
choosesESP+B4; compact staging choosesESP+18. No dummy locals, padding,
assembly, volatile forcing or artificial default values were introduced.
The previous740 bool-false guards are removed. The source still has the bool
staging ABI and pending actions>798; full original void/default behavior and
root compiler ownership remain pending. Uninitialized C++ use is not a
defined-behavior proof for arbitrary caller stacks or other compiler profiles.

## Focused build and native boundaries

```bash
scripts/compile-unit.sh src/characters/ReimuActionStateDispatch.cpp build/reimu-740-mode/ReimuActionStateDispatch.obj
python3 scripts/probe-reimu-action-source-shape.py --output-dir build/reimu-740-mode/expanded
python3 scripts/audit-reimu-740-mode-shape.py build/reimu-740-mode/ReimuActionStateDispatch.obj
python3 scripts/audit-reimu-740-mode-shape.py build/reimu-740-mode/expanded/ReimuActionStateDispatch.obj
```

VC8 SP1 `/O2 /GS- /GR /EHsc /MT`, default FP, produces:

- Compact: `400b45aadbfcda5180db30bc38a95fdc0a1aeaa2c738fde0ff33080ef7baa86e`.
- Expanded: `473df2cae507abbadadf39e8ec869bd36100571682ff002eb9f5cf903a05589e`.

Both pass **0/5494 native differences**, input SHA256
`f7a6eed35efc2ebd1bff55482c832bbb3a9fabf4e72d916e6c62d29f25eeb642`.
The matrix covers108 motion,288 nodes,4032 shot gates/payloads,56 cutoffs,
4 required branch cases,8 unknown boundaries and998 integration cases. Stops
are4606 genuine RETs,842 object requests,30 effects,6 common entries,1 set669
and9 pending (8 indeterminate reads plus the upper handoff). Actor bytes,
actual MT/helpers, ordered arguments/first pointed payload and genuine RET
stack/register/x87 state are compared. Returning world requests remain unproved.

`reimu_740_mode_facts.py` first verifies the target owner hash, then requires
one three-register same-DWORD read, its signed counter division, two unsigned
0..3 guards/indexed tables, exact mode constants and one cutoff read of the
same spill. MOV/LEA constant arms must end at their proved unconditional joins;
unrecognized forms fail closed. Reports pin target/object/tool hashes and
Capstone. The per-run native subclass stops the candidate before its derived
read addresses, requires action740/sequence1 or6/mode>3 there, and compares
the target's existing pre-read boundaries. It supplies no stack value, helper
return or target return, and mutates no other oracle module. Pending is an
analysis stop before a genuine read; its value remains unexecuted in this matrix.

The previous pending baseline is rejected by this structural guard. A compiled
control initializing only the cutoff to0 still passes **0/56** valid-mode
native cases, but is rejected for lacking the fourth same-slot read. Earlier
710/711/720 static loops and48 510 packets/12 level reloads all still pass.
No old full matrix or aggregate cold replay was run.

## One concrete exceptional-input experiment

A separate read-only probe omits the pre-read stops and uses the existing
fixture's zero-cleared initial stack, mode4/counter0. It observes the actual
memory reads without injecting values during execution. Target and expanded
candidate both read0. Sequence1 raises a real CPU exception at target48C78E
and candidate48CA59 (IDIV). Sequence6 executes real helpers and returns with
equal compared state. No helper result or callback return is fabricated.

This proves only that supplied zero-stack context. The actual stack addresses
differ (210FA2C versus210FA04), reflecting frame570h versus598h; arbitrary
initial bytes cannot be assumed equal. General unknown-input behavior/faults,
source-language undefined behavior and complete canonical equality remain
unproved. The probe/report remain below build/reimu-740-mode/.

## Structural result and next phase

Primary groups remain45/50/33,126 destinations and0 splits. Candidate740 is
540 bytes versus target535. Expanded prefix grows81288->81452 and total text
82628->82824. It now has **all11 target indirect switches**,1171 E8s versus1188
and150 RETs versus153. Frame598h versus570h remains the first diagnostic
mismatch at478FA8. The pre-table deficit is98 bytes; spans include alignment
and support neither compiler boundaries nor byte-equality credit. The reviewed
metadata ceiling and canonical comparator are unchanged.

Build/control/analysis receipts pin current sources/compiler/objects. The
earlier direct Ghidra identity is reused after PE checks and all9 unchanged
primary DB hashes; no new process/clone or IDA semantics. Superseded730,
intermediate pending/uninitialized and rejected-control products plus caches
are cleaned. Current two objects/source and bounded evidence remain. Next
recover the actual void/default entry, then returning world contexts, complete
relocation ownership and truthful VC8/LTCG provenance for root acceptance.
