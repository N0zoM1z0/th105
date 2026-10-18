# Reimu policy0 result cache and x87 evidence, 2026-10-19

This checkpoint preserves the full selector result before explicitly consuming
its signed low word in policy0 predicates. It reproduces the target's
`MOV ECX,EAX` cache operation. The15999-byte root at48D390 is still nonexact
at+97/48D427;121 target/117 source selector sites and52/50 RETs remain.
No exact bytes or functions are added.

## Target and interpretation

Only original Japanese 1.06a is used, executable SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Root `[48D390,49120F)` SHA256 is
`3bd363994e140603ae0ec249ffd3a36b1ae0448e72a389e417c4cc7a6d113e2d`.
The existing vtable, void ECX/no-stack-argument and complete root CFG evidence
is unchanged. Direct read-only Ghidra re-attested file/entry/text/root bytes
and typed method metadata; nine primary DB file hashes remained unchanged.
The384MiB heap/CPU0 run is under
`.analysis/reimu-cpu-policy0-20261019/`; no factory adapter, IDA semantic data,
copied project or target patch was used. The project alias is removed.

Observed target48FC28 saves full EAX into ECX, then48FC2D stores CX at76A.
Later conditions consume signed16-bit CX. The former short local made VC8
emit `MOVZX ECX,AX` instead. The selected source uses an int call-result
cache and `POLICY_ROLL_WORD` for explicit signed-short consumption. This
expresses the observed producer/consumer widths without changing the helper
signature, actor layout, arithmetic, call order or branch decisions. It is
not proof of the unique original C++ variable declaration.

An encoding-preserving comparison between both compiled roots finds exactly
one changed functional instruction, ordinal2470: `0fb7c8 -> 8bc8`. It maps
direct branch/call destinations by instruction ordinal while retaining their
encodings and external targets. All3964 functional instruction positions and
47 function-local DIR32 metadata pointer destinations otherwise agree; index
metadata bytes agree. Genuine compiler post-RET alignment changes from90 to
8BFF because the cache instruction is one byte shorter. No padding was added
to source. Both callable prefixes/payloads remain15860/16401 bytes.

## Empty x87 inputs and actual helper observations

The first16160-case private observation explicitly cleared the x87 tags at
root entry. All46420 paired selector entries per side were empty/TOP0 and
preserved that state/control word across their real RETs. A1152-case
publication subset was also empty, but did not cover all non-duration paths;
it must not be generalized to every policy store.

Making this observation reproducible exposed a fixture issue: the installed
Unicorn1.0.2 fresh context reports eight occupied zero-tagged slots (5555),
even with TOP0. The old CPU probe set TOP/control indirectly without clearing
the tag word. `CpuProbe.run` now explicitly supplies FPSW0/FPTAGFFFF and
checks both TOP and the full tag word at the stop. This configures test
input; it never patches target instructions or helper behavior. Regression
tests cover a dirty saved context and rejection of an occupied slot at TOP0.
Older CPU reports remain historical observations of their prior emulator
input; they do not prove empty-entry liveness. JSON actor-case hashes are
unchanged, but the newly explicit emulator environment is a separate input
contract.

`--selection-x87` is available only with Reimu selection cases. It observes
actual selector entry/genuine return and policy/timer writes. It verifies
empty masked-PC53 entry, decodes real caller sites, and retains tag/TOP/live
80-bit/control snapshots. Missing genuine returns are rejected. No helper
results, actor outcomes or return edges are substituted.

Fresh full selection recording on the selected object confirms:

- 16160 cases, actual rolls0..100, all1488 target policy0 instructions visited;
  no output differences or missing target instructions.
- 46420 paired selector observations. Target38/source34 physical sites include
  the initial draw. Source has36 argument/state records because one physical
  CALL serves bounds15/20/30. All are empty/TOP0 before and after; no changed
  helper-return snapshots. This rules out different live call-entry values
  as the explanation for the four missing physical copies on these paths.
- Target nonempty publications occur only at48FCF2, the policy3 store, with
  one live value in66 observations (1040 or240). Candidate48FD72 carries
  those values in38 observations, and also retains one value at DI-based49026F and literal7
  store4903F3. Timer publications are empty on both sides. These are actual
  scheduling differences, not proof that a cleanup can be inserted arbitrarily.

The source-visible real selector is also tested in the same TU with ordinary
`/Ob1` to retain the target's non-inlined call surface. The selector remains
canonical27/27, and the entire caller payload is identical to the selected
external-declaration form. This rejects visibility of that one helper as a
sufficient explanation under this control; it does not rule out other honest
TU/LTCG contexts. The27-byte result was already accepted and adds no credit.

## Finished-source results and reproduction

| Artifact | SHA256 |
| --- | --- |
| Source | `556098b785ef77ed7b8a49b55fa4c72cd4cf6e60f29dfc7dd88fca12baa3754a` |
| Reimu object used in native replay | `32b68b8f36a6e23f0917affdede1dd96e674de51d44a64b3b16f74524bb162c7` |
| Canonical16401-byte payload | `70905d5a0663e6c41cbdc5dfd94a9ee56b8ed3a197011432c5270e87b2990ae4` |

The prior payload was
`8baf522260e54665fb7bf441a6ff4db19863b1483387b86f082f4c1792d36547`.
Native reports and normalization/control recipes remain below
`build/reimu-cpu-policy0/`. Shared headers, flags, TU selection and relocation
bindings are unchanged; the real-selector TU is an unselected control.

```bash
python3 scripts/build.py --unit gpt-web-reimu-cpu-action-policy --compare --json
python3 scripts/audit-cpu-policy-paths.py \
  build/match-units/GptWeb_ReimuCpuActionPolicy.obj --root reimu --cases 5000
python3 scripts/audit-cpu-policy-paths.py \
  build/match-units/GptWeb_ReimuCpuActionPolicy.obj --root reimu \
  --selection-cases --selection-x87
python3 scripts/audit-cpu-policy-paths.py \
  build/match-units/GptWeb_ReimuCpuActionPolicy.obj --root reimu --height-cases
```

Strict comparison intentionally returns a mismatch. With explicit empty x87
inputs/stop checks, Reimu passes0/21528 (5000 general,16160 selection,368
height). The shared fixture change is independently replayed on fresh default
and Aya CPU objects: both pass the same21528 controls, for0/64584 related
cases overall. Their known strict nonexact results remain unchanged. These
are focused related-root diagnostics, not a corpus cold replay or aggregate
exact percentage. The source edit's whole-root normalization also qualifies
the unmodified primary/common instruction graph; no unrelated source unit
or accepted match ledger changes.

Complete numerical/exception/concurrency equivalence, original C++ source,
remaining constant-register lifetimes and CALL/RET sharing remain unknown.
Investigate the terminal selection paths and genuine compiler/TU context;
do not repeat a missing-live-value-at-selector hypothesis without new evidence.
Final gates are local `python3 scripts/ci.py` and `git diff --check`.
