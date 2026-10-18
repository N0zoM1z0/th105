# Reimu CPU source candidate, 2026-10-19

This is the initial full-source checkpoint. The later
[counter-read checkpoint](REIMU_CPU_COUNTER_READS_2026_10_19.md) supersedes its
selected source/build pins and first mismatch; the finite results below
belong to this historical object.

This checkpoint recovers a complete C++ candidate for
`Reimu_update_cpu_action_policy @0x0048D390`. It is source-present and
**nonexact**. The strict comparator first differs at `+0x12E / 0x0048D4BE`,
inside the peer-life guard's conditional jump displacement. No bytes or
functions are added to the exact ledger.

## Target observations

Only the original Japanese 1.06a executable is used, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The existing [root packet](REIMU_CPU_ROOT_2026_10_19.md) establishes the
Reimu vtable entry, ECX receiver, no stack arguments, callable extent
`[48D390,49120F)`, all4126 reached instructions, four target switches,
157 calls to five helpers and52 balanced RETs. The callable SHA256 is
`3bd363994e140603ae0ec249ffd3a36b1ae0448e72a389e417c4cc7a6d113e2d`.

Direct Ghidra analysis re-attested the executable identity, entry, mapped
text and complete root bytes before decompiling the existing typed method.
It read back `void __thiscall`, ECX:4 receiver and15999-byte body. The typed
decompilation remains a hypothesis, not source or proof of its predicates.
This invocation was read-only; all nine primary database hashes remained
unchanged. Its report and pins are in `build/reimu-cpu-source/`; private
hypothesis and Java recipe are under `.analysis/reimu-cpu-source-20261019/`.
The temporary project alias was removed; no second Ghidra process/project
copy or IDA semantic analysis was used.

## Source and predicate recovery

`src/characters/ReimuCpuActionPolicy.cpp` implements the entire entry and
returning root using the existing770-byte CPU prefix view. It adds no class
fields, virtual methods, helper-result hooks, assembly or copied code bytes.
The Reimu action and common-attack trees are manually recovered; the retained
default source supplies only the shared policy selection/tails already
supported by target-to-target evidence. The rejected default-root copy's
1065/5000 differences are not treated as a Reimu implementation.

Observed accesses retain signed16-bit counters/resource thresholds, signed
facing and byte gates, full unsigned selector results, real checked front
sequence access, and the signed-short angle conversion after `atan2_degrees`.
The fields at609/60B are signed input bytes; their complete gameplay meaning
is not established by this root. Their fixture/source skill labels are
provisional. All selector/MT/atan2/checked-sequence/ftol calls execute original
PE code in the diagnostic, including the seeded generator's discarded draw.

Two threshold mistakes were exposed and corrected before this checkpoint:

- The grounded attack interval starts at90, not180. The first5000-case
  complete-return run found two differences at distance100; the corrected
  candidate passed all5000.
- The later grounded projectile fallback includes distance180. Raw
  `48EE7A..48EE8F` loads180, compares against the distance and tests AH41
  with JP; equality reaches the next selector call. A strict `>180` produced
  two failures in the45714-case matrix. Actor controls agreed, but the missing
  draw changed the RNG state. The source uses `>=180`, and focused36-case
  checks include the two failing seeds202/213 and neighboring179/181 inputs.

Control/counter resets are written in observed order. Together with the
observed signed action thresholds this makes the first302 canonical bytes
agree, ending inside the life-guard Jcc. This interval is a diagnostic only.

## Reproducible build and execution

The new `gpt-web-reimu-cpu-action-policy` unit is a `probe`, using VC8 SP1 O2,
GS disabled and ordinary C++ compilation. Existing CPU headers, layouts,
flags, selected sources and accepted units are unchanged. Two new relocation
keys attest exact double880/980 bytes at6C3F08/6C3EF8. Existing units do not
reference these new keys, so there are no affected accepted exact units.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-reimu-cpu-action-policy --compare --json
taskset -c 0 nice -n 10 python3 scripts/audit-cpu-policy-paths.py \
  build/match-units/GptWeb_ReimuCpuActionPolicy.obj --root reimu --cases 5000
taskset -c 0 nice -n 10 python3 scripts/audit-cpu-policy-paths.py \
  build/match-units/GptWeb_ReimuCpuActionPolicy.obj --root reimu --reimu-edge-cases
taskset -c 0 nice -n 10 python3 scripts/audit-cpu-policy-paths.py \
  build/match-units/GptWeb_ReimuCpuActionPolicy.obj --root reimu --selection-cases
taskset -c 0 nice -n 10 python3 scripts/audit-cpu-policy-paths.py \
  build/match-units/GptWeb_ReimuCpuActionPolicy.obj --root reimu --height-cases
```

The strict build/comparison command intentionally returns comparison failure.
Native reports use complete entry-to-RET execution, comparing the entire7A4
actor prefix, control words, RNG state, helper order/arguments/results,
ftol x87 inputs and stack cleanup. `reimu_cpu_cases.py` retains a finite
action/resource/sequence/geometry matrix, including signed counter extremes,
boundary values, both facings, signed byte gates and masked nonfinite inputs.
Its common-attack samples reuse256 actual seeds to limit initialization cost.
An earlier disposable matrix with a fresh seed for every geometry was stopped
after32000 cases to avoid unnecessary repeated MT initialization; no complete
result is claimed for it.

The diagnostic's Reimu join is a unique decoded counter/JNE boundary. Its
ordinary candidate may insert a flag-preserving MOV EDI,6 between them. The
default/Aya join rule remains unchanged. Regression tests reject duplicate,
wrong-counter, unreviewed constant, flag-changing and truncated shapes. This
boundary does not terminate complete-return execution or replace helpers.

Finished-source build pins (`build/reimu-cpu-source/unit.json`):

| Artifact | SHA256 |
| --- | --- |
| Source | `51cfa79957d88b7e443b65d5136a59a6e157f03cf375b554a9a2ca39ac39d85b` |
| VC8 object | `3f959e44c273f2bf1e97b625ef8d447cef58f9f0d4ab07a031f43f681e41cf70` |
| Canonical15785-byte payload | `fe974ea52a9c60011287f966997396f45b9ab30033da1c26879b56ddbfbbdf7b` |

All four finished-object replays passed, **0/67242** differences in total:

| Matrix | Cases | Differences | Input SHA256 |
| --- | ---: | ---: | --- |
| General complete calls | 5000 | 0 | `2bd4b7c7883a74520652cf5d44007c08268a12768da2decf069c6fd91c9a37cf` |
| Reimu boundaries/common attacks | 45714 | 0 | `2f3a5b11e61b3d6252222e3d4fa3351c95e4454966d7727978a8787febb4aae8` |
| Policy0 selection | 16160 | 0 | `bb6b26c3b92de692ab6d927f74df3f1f6e8754b4d5b2e024cee49f955e769fd0` |
| Finite/NaN heights | 368 | 0 | `6fef66471aadc3cf4361022df18acd143002731e0aa1bf25b34f375194a16ebf` |

All reports pin the object and canonical payload above. Selection confirms
actual rolls0..100 on both sides and visits all1488 target policy0 instructions
(4892 bytes including shared return tails), with no missing instruction
addresses. This is instruction coverage of that region, not complete branch
coverage of the whole root. General execution visits3467 target instructions;
the edge matrix visits2179. The general/edge reports each execute all five
original helpers. The36 additional focused regressions also pass.

The final gate is local `python3 scripts/ci.py` plus `git diff --check`,
including343 workflow tests. Census expectations now record1437 source-present
functions and517 units; exact expectations remain1333 functions/225099 bytes.
No all-unit cold replay or aggregate exact percentage is claimed.

## Remaining work

The target is15999 callable bytes; the candidate callable prefix is15244 and
its full COFF payload is15785. The two primary tables retain19 action and21
policy destinations with no split primary target groups. Recovered
302-sequence predicates simplify some target comparisons; the source does
not yet reproduce all auxiliary table/code-sharing shapes. Policy tails,
counter paths, conditional return placement and code generation remain open.
The first differing Jcc displacement is a symptom of the later layout and
return-sharing differences, not a reason to alter bytes or add padding.

Finite execution agreement does not establish all branch outcomes, floating
exceptions/precision modes, invalid object graphs, complete gameplay meaning,
original TU boundaries or canonical equality. Next work should use the new
whole-root source and call/CFG evidence to recover source shape. The81KB
Reimu action root remains open and unchanged by this checkpoint.
