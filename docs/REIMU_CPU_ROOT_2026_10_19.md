# Reimu CPU policy root: full boundary and a bounded sharing bridge

`Reimu_update_cpu_action_policy @ 0048D390` is now identified and mapped.
All15999 callable bytes and4126 instructions belong to a closed CFG, with
four qualified jump tables and52 balanced RETs. Its policy0 selection region
agrees with the default target on16000 complete-return inputs, while the full
default source differs on1065/5000 Reimu inputs. Reimu still has a declaration
only: no root implementation, exact match unit or authored-byte credit is added.

## Identity, ownership and ABI

Use original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Reimu primary-vtable cell6C4184, slot+58 from6C412C, contains48D390. Existing
RTTI-backed origin anchors independently establish authored ownership.

The reviewed callable is `[48D390,49120F)`, SHA256
`3bd363994e140603ae0ec249ffd3a36b1ae0448e72a389e417c4cc7a6d113e2d`.
Four INT3 bytes precede entry. Every decoded instruction is reachable; there
are no unowned internal alignment bytes or unresolved CPU transfers. NOP49120F
is post-RET alignment; the tables start491210 and end49144D, before three
alignment bytes and the next candidate491450. Tables do not extend the callable.

Entry consumes ECX as the receiver and allocates0C bytes. It saves EBX/ESI/EDI,
and only saves EBP after the peer-word174 guard succeeds. The early guard exits
through the three-register epilogue; later paths pop all four. An ESP worklist
finds one consistent depth at every instruction and depth0 at all52 RETs,
using the five helper cleanup contracts. No caller stack arguments are consumed.
The void output-policy interface is an inference supported by slot+58 use and
the existing source declaration; arbitrary EAX contents are not a return contract.

Observed entry work clears command fields724/728, converts absolute integer
opponent X/Y differences to float, decrements signed WORD768, clears controls
6BC..6D0 and applies action-dependent counter resets. This is CPU decision
work, not action initialization. The earlier action-root checkpoint remains
unchanged at478FA0.

| Direct helper | Decoded root calls | Stack cleanup |
| --- | ---: | ---: |
| __ftol2_sse68A1A0 | 6 | 0 |
| MT next4066B0 | 1 | 0 |
| selector_random_roll4067D0 | 121 | caller |
| checked sequence4399C0 | 25 | callee4 |
| atan2_degrees406540 | 4 | caller |

## Switch ownership

The target mapper now replays `reimu-cpu-action-policy` in
`config/giant-action-switches.toml`, with157 direct calls to five targets,
52 RETs and40 distinct primary destinations:

| Surface | Keys | Destination table / count | Byte index table |
| --- | --- | --- | --- |
| Current action | 200..416 | 491210 /19 | 49125C |
| Checked front record in action302 | 200..214 | 491338 /15 | none |
| Checked front record in action303 | 200..214 | 491374 /4 | 491384 |
| Signed policy WORD766 | 0..100 | 491394 /21 | 4913E8 |

The nested keys are codes read from the checked sequence controller, not the
animation sequence field13E. Primary action sharing is400/401,404/405/406 and
410/411. The other15 nondefault destinations must be recovered from their own
target instructions; default/Aya source is a hypothesis for their behavior.
The signed policy load is at48FBEE and policy0 enters48FC0C. Policy19..99 and
out-of-range words reach the actual shared return; no placeholder handler is
needed. Full character-specific source and numerical/branch closure remain open.

## Policy0 target-to-target execution

The raw default/Reimu policy0 traversals contain1486/1488 reachable instructions.
An ordered instruction-token comparison finds1442 identical forms after hiding
internal branch destinations. Some remaining differences are saved constant
register choices, register allocation and physical return-tail placement.
Token similarity alone is not an edge correspondence or equivalence proof.

Both original roots execute in separate Unicorn engines from the same existing
finite selection fixtures: action201, peer action100, policy0, resource1000,
mode1, two facings, ten height pairs, four positions/facings and four distances.
Actual MT seeds produce and independently confirm every policy roll0..99;
neither RNG results nor helper returns are substituted. The complete roots run
their real prefixes and return normally. Comparison includes actor bytes,
controls/commands/policy words, MT state, helper calls/conversion inputs, stack
and x87 control word.

Result: **0/16000 differences**, visiting all1488 Reimu and1486 default policy0
instructions. Both sides execute45940 selector calls with45940 real MT draws
and32000 actual floating conversions. Atan2 and checked-sequence paths are not
part of this fixture. Input SHA256:
`77bfa4510ee00ca1cf9bce3cbe20fdad06db5d64fdc0bab74d704be00aa60ad2`.
The preceding160-case pilot is separately scoped and not added to that count.

This supports sharing the selection algorithm as a source hypothesis. It does
not prove all branches, roll100, arbitrary floats/FP environments, later policy
execution, or equivalence of the two entire CPU functions.

## A source reference that must not be promoted

A private reference adapts only the existing default source method ownership
to `ReimuCpuActionPolicyView`. Its full16553 canonical bytes agree with a fresh
ordinary default object when replayed at the same address, SHA256
`1a83e3e4d7ba79d799f088fdfc3871e07b9675aa3cda40ffd2058c1080921e96`.
This confirms the ABI adaptation itself changes no payload byte. It is still
default behavior, not a recovered Reimu implementation.

The reference fits the Reimu callable/metadata caps: prefix15928 and payload
16553. All five helpers execute normally. Complete finite execution has
**1065/5000 differences**, across30 action values. Differences include command
WORD/DWORD728 outputs and conditional RNG consumption; even common-action
inputs can differ before policy selection. Input SHA256:
`2bd4b7c7883a74520652cf5d44007c08268a12768da2decf069c6fd91c9a37cf`.
The100-case pilot has23 differences and is not the final result. No guard is
relaxed, callback result fabricated or wrong source selected.

The related default unit is rebuilt with its existing flags and still has its
known nonexact first difference+12E/5F20AE and canonical comparison-window hash
`af511b4feecaa98f3b601749f9e3456a299a2fa22b720105c284833a7ee49566`.
That expected nonexact comparison is distinct from the final CI gate. No
unchanged historical matrix or aggregate exact-unit replay is performed.

## Ghidra and repository state

Direct Ghidra independently checks the imported executable hash, entry point,
Windows/x86 language/compiler, mapped .text and full callable hash. Its initial
database has no function object at48D390. The complete function, supported
ECX/no-stack ABI, inferred void signature, signed policy fields and method-only
770-byte prefix view are saved in a private project copy, then reopened for
independent metadata readback. Only after readback does that project replace
its predecessor. The view is not a full Reimu class-size claim. A2074-line
decompilation remains a private hypothesis and is not pasted into source.
The canonical PE and mapped bytes remain unchanged. The temporary project
copy, predecessor and aliases are removed; the primary DB now intentionally
contains the accepted function metadata.

`functions.csv` changes the candidate to identified and points at the existing
declaration in `CpuActionPolicies.hpp`; `reccmp-functions.csv` records the name.
The origin classification was already authored. Neither `implemented.csv` nor
`matches.csv` changes. Source presence, matching units and exact totals do not
increase. Next recover Reimu's primary-action and common-attack decision tree
from raw target facts, then compose the shared selection algorithm with those
character-specific branches before configuring a complete source comparison.

Private packets, native adapters, source reference, hashes and metadata receipts
are under `build/reimu-cpu-root/`; Ghidra scripts/hypothesis are under
`.analysis/reimu-cpu-root-20261019/`. Public target reproduction is:

```bash
python3 scripts/map-giant-action-switches.py reimu-cpu-action-policy --json
python3 scripts/validate-tracking.py --require-target
```

`packet.py` pins all four switch surfaces and stack depths;
`native-policy0.py` reproduces the16000-case bridge, and `audit-reference.py`
records the unselected source counterexample. These are diagnostics, not
acceptance units. Heavy jobs remain serial on CPU0/nice10. The bounded Ghidra
decompilation peaks369MiB; the16000-case execution takes88.72s and peaks74MiB.
Current genuine providers, resources, toolchains and the verified primary
project are preserved. Final local CI and whitespace gates remain mandatory.
