# Iku steering clamps and payload-home correlation

Current checkpoint after [call sharing/result consumers](IKU_CALL_SHARING_2026_10_17.md).
Target remains original Japanese TH10.5 v1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Root620920 is59038 bytes, SHA-256
`abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea`.
Canonical comparison remains **nonexact+0x64 /620984**, after100 equal bytes.
No exact/partial authored credit or aggregate replay result is claimed.

## Target observations and selected source

Action730 sequences7/8 steer toward the peer, then clamp both velocity axes.
The mode is read at62DB64: mode3 selects +/-6, mode0 selects +/-4, and other
modes select +/-5. Each mode performs its **X upper-bound comparison inside
the branch**, before joining at62DBB2 for the X lower bound and both Y bounds.
All comparisons are ordered; unordered velocities do not become a bound.
The shared face-opponent CALL is62DC18. This185-byte/50-instruction interval
`[62DB64,62DC1D)` hashes to
`750b4c87eda9cdf65581666da076ebbc05f01ce93e0949b7ba9642ddbb90c41b`.
It is an internal CFG interval, not a new function boundary or exact unit.

The preceding source selected two float limit locals first, then clamped both
axes after the mode branches. The selected source now expresses clamp_x and
clamp_y with each mode's constants inside its branch. VC8 retains the target's
branch-local X test and shared lower-bound structure. Its final Y paths still
duplicate the face CALL: five physical action730 face calls versus target
four. Matching the source structure does not settle that later backend choice.

Direct Ghidra independently re-attested imported/PE hashes, entry, mapped
`.text`, root bytes,58 layout components,177 virtual-call records and ftol ABI.
A fresh typed decompilation corroborates the branch-local X test/common lower
and Y operations. It remains a hypothesis: its old `--fVar` rendering around
the cosine input must not replace the two observed FCHS operations. The
read-only768MiB/two-CPU clone was deleted; all nine primary database files are
hash-unchanged. Wrong-image IDA remained rejected.

## Compiler and identity diagnostics

Current source disk SHA-256 (CRLF):
`ff79e5743533c50c885a0139facff1febc726f2c2b5e5a84497fe2bd27b014ad`.
Normalized complete COFF section SHA-256:
`33f09d2ac49075ed6495a5b10a884fe18cf1f5b9e8556dcdec157eb58038549d`.
The final unit and native-tested object replay to identical whole-section
bytes. The59594-byte section contains a58439-byte callable span,15032 reachable
instructions/58433 instruction bytes, six internal compiler alignment bytes,
and1155 bytes of following metadata/alignment. There are128 RETs and no local
CALL relocations. All three33/42/35 tables remain.

Physical-owner diagnostics rise from5 to **7/109**:2/4/5/204/215/303/321.
The additional215/321 partitions are162/199 bytes; their encodings/edges agree
under the existing owner-coordinate comparison. They are not independent
callables, canonical matches or partial credit. Ordinary/register CALL counts
remain867/166 versus target865/177, including58 versus54 effect calls. Frame
400hex,84 real payload cells,41 surface and10 below-surface AL consumers stay.

Correlation by possible incoming action set and physical spawn-call ordinal
finds equal group lengths across all182 spawn sites and covers all84 target
payload homes. The public --payload-homes option intersects the candidate
home sets supplied by each paired call; it never pairs multi-home sets by
sorting them. Seventy-three homes have a single candidate correlation and
11 retain multiple possibilities. The545/546 pair resolves through its
independent calls; other shared sites lose action/pointer correlation in the
conservative union model. A bijection is not established. Three new tests
cover unsorted shared sets, unanchored ambiguity, unknown/missing/inconsistent
evidence. Under this conditional correlation, all first10 homes32..140 now
map to the same offsets; previously only five did. This is not a proof that
payload values or paths coincide. The hypothesis that compiler allocation
weights contribute to the permutation remains open; do not manually reorder
or fabricate stack storage from it.

Unselected controls further narrow the next work:

- `/O2 /Os`, passed as the private compiler's trailing `_CL_=/Os`, gives
  span52234/13914 instructions/one RET, a different prologue and six switches.
  Its43 effect/124 register calls strongly disagree with target54/177. The
  compiler's own `/?` help identifies `/Os` as favoring code space; no global
  profile is changed.
- Lifting the current inline status dispatcher into one direct void body is
  still whole-section neutral. Moving the face operation from the steering
  helper to its caller is also whole-section neutral.
- A hybrid source with explicit branch-local upper X tests and shared float
  limit locals produces span58476/15045 instructions, retaining the extra face
  site. It does not improve the selected branch structure.
- The genuine435240/465190 callees forward full DWORD direction slots. Their
  established interfaces/bindings are retained; narrowing a declaration to
  manipulate register allocation is not supported by this investigation.

## Native boundary checks

The new `--steering-clamps` fixture runs the actual whole entry for action730,
sequences7/8/9/10, modes-1/0/1/2/3/4, both facings and x87 PC53/64 with masked
exceptions. Both axes include inputs adjacent to +/-bound +/-0.5, signed zero,
subnormals, positive/negative Inf and quiet NaNs with explicit payload bits.
Finite horizontal/vertical peer geometry executes genuine atan/lookup math;
no dependency result is injected. Sequences9/10 retain their fixed +/-5 clamp
and ordered positive-X exit to sequence7.

Fresh final source passes **0/3840**:3312 RETs,528 genuine sequence-backend
entries,252 visited target-root instructions. Input SHA-256:
`f2c24710f5f4a32e1f1158bc3fe8c01d1f4de8ec9c7067df4239e6704106c031`;
target-output SHA-256:
`9ca446c550ee0c231299ece1447bb5466d61b6bfcfa0bddeffef87d8c3c5566c`.
A deliberately wrong mode0 bound of5 instead of4 produces **96/320 differences**
in the mode0/seq7,8 subset. Both sides RET in that control; only input cases
are filtered, with no target/backend return hooks.

Earlier812/16285/26783 matrices and unrelated accepted units are not replayed.
No shared header/layout/profile/partition or canonical relocation binding is
changed. Post-backend/exceptional execution, original C++/TU/inheritance and
LTCG's role remain unknown. Continue on shared call suffixes and constant/
scalar lifetimes in this root, including the remaining duplicated face call.

```bash
python3 scripts/build.py --unit gpt-web-iku-action-state --compare --json > build/iku-argtail-final-compare.json
# Expected exit1: canonical mismatch+0x64, not compilation failure.
python3 scripts/probe-iku-upper-actions.py --steering-clamps --output build/IkuArgTailSteeringNative.obj > build/iku-argtail-steering-native.json
python3 scripts/audit-iku-full-root.py --object build/match-units/GptWeb_IkuActionState.obj --native-object build/IkuArgTailSteeringNative.obj > build/iku-argtail-final-facts.json
python3 scripts/audit-iku-payload-homes.py --object build/match-units/GptWeb_IkuActionState.obj > build/iku-argtail-final-homes.json
python3 scripts/audit-iku-call-sharing.py --payload-homes --object build/match-units/GptWeb_IkuActionState.obj > build/iku-argtail-final-origins.json
python3 scripts/audit-giant-action-owners.py iku-vslot28 build/match-units/GptWeb_IkuActionState.obj --unit gpt-web-iku-action-state --json > build/iku-argtail-final-owners.json
python3 scripts/ci.py
git diff --check
```
