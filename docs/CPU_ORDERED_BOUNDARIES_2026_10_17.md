# Default CPU decision root: ordered boundaries, October 17

The active target is `Fighter_update_default_cpu_action_policy @ 0x005F1F80`,
15,910 callable bytes. This pass fixes observable differences in its outer
action phase and closes all six switches in the target traversal. The complete
function remains nonexact; no function or partial authored bytes receive exact
credit.

## Target observations

Only the original Japanese 1.06a executable is used, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The callable is `[0x005F1F80, 0x005F5DA6)`, with body SHA-256
`fb26e85839101f4dc89506c9d51a14b76c729b6836d0efe2c063d18b22c10f77`.
IDA preflight rejects the attached session, which is not used.

The existing action and policy tables were insufficient for complete raw
traversal. Four nested sequence switches have signed-word selectors, subtract
200, compare against 12, and use a byte index followed by a DWORD destination
table. The source already contains these switches; they are not new functions.

| Outer action | Dispatch | Index table | Destination table | Entries |
| --- | --- | --- | --- | ---: |
| 302 | `5F2590` | `5F5EE8` | `5F5ED0` | 6 |
| 304 | `5F28B4` | `5F5F04` | `5F5EF8` | 3 |
| 322 | `5F3057` | `5F5F2C` | `5F5F14` | 6 |
| 410/412 | `5F3641` | `5F5F54` | `5F5F3C` | 6 |

Raw bounds, all 13 index bytes, destination DWORDs and instruction boundaries
were checked. The auxiliary-switch ledger now expands these edges. Traversal
increases from 3,963 instructions / 15,448 bytes to **all 4,069 instructions /
15,910 bytes**, with no unvisited range or unresolved indirect exit. The
previously unvisited 462 bytes already belonged to this root. This changes no
candidate, origin, source-present or exact count. The five direct external
targets remain unchanged, including `__ftol2_sse` and the checked-deque accessor
whose origin is still in review.

## Recovered source predicates

At `5F263F`, `5F306A` and the shared `5F3697`, `TEST AH,41` followed by
`JNE` rejects the unordered x87 result as well as less/equal. The complementary
lower-bound paths at `5F265B`, `5F3086` and `5F36B3` use `TEST AH,5` / `JP`
to reject unordered inputs from the ordered less-than arm.

The retained source had represented C0 and C3 as separate ordinary C++ `<`
and `==` Booleans. For NaN, both ordinary predicates are false, so their
negations incorrectly select the upper-bound arm. C0 itself also represents
unordered; it is not equivalent to an ordinary less-than Boolean.

The corrected source uses one genuinely consumed ordered comparison,
`above_boundary_threshold = x > limit`. Two repeated sequence-205 guards and
the shared lower-bound guard now express the negation of the target's ordered
predicate, such as `!(x < 400.0)`, instead of substituting `x >= 400.0`.
Call order, parameter/result widths, stores, field layout, numerical constants
and compiler settings are preserved. This is a behavioral correction, not a
claim of uniquely recovered original syntax.

One concrete counterexample is action 322, checked sequence 212, positive
facing, mode 1, policy counter 100 and a quiet-NaN x coordinate. At the shared
policy join, the target leaves control DWORD `+0x6D0` at zero; the preceding
compiled source writes 2. The corrected compiled source leaves it at zero.

## Bounded instruction-execution evidence

`scripts/audit-cpu-boundary-paths.py` loads the hash-attested target image and
separately executes the configured COFF body after normal relocation replay.
It stops at the unique counter-766 / policy-constant-7 instruction pair,
before the common policy phase. The probe checks the eight control DWORDs,
two command-flag DWORDs, six policy words, policy state, helper-call arguments
and order, and stack displacement. Every path must reach that join and restore
the initial x87 TOP; writes outside the actor and stack fail the probe.

The target's real float-to-integer runtime executes. Deterministic hooks return
RNG value zero within the observed 100/1000 bounds and provide one checked
sequence record, validating its receiver, index and stack cleanup. These are
execution controls, not compiler/link stubs or canonical acceptance inputs.

The **16,600 controls** cover actions 302/304/322/410/412, 13 sequence values,
both facings, modes 0..3, signed policy-counter boundaries, and 25 float bit
patterns. These include adjacent float values around 300/400/860/960, signed
zero, subnormals, maximum finite values, infinities, and signed quiet/signaling
NaNs. The primary matrix uses masked exceptions, round-to-nearest and x87
precision controls 53 and 64; additional controls exercise counter gates.

| Compiled source | Output/call/stack differences |
| --- | ---: |
| Fresh preceding baseline | **132 / 16,600** |
| Corrected configured unit | **0 / 16,600** |

All baseline failures have NaN inputs and belong to six action/sequence
groups: 302/205, 302/212, 322/205, 322/212, 410/212 and 412/212. An earlier
2,970-control independent run also found 12 baseline output differences and
zero after correction. The expanded probe uses Unicorn 1.0.2; its loaded
library SHA-256 is
`19eb8d5f73daf33b7e3d41a851bc72f12b5b17fbf2c747eaefa5c5c137a9c4df`.
Reports record the actual engine and object hashes. The Python Unicorn binding
is needed only for this local target-dependent command, not public CI.

This proves the stated bounded controls. It does not establish full-function
equivalence, all RNG streams, unmasked exception behavior or complete numerical
closure. The source remains subject to the complete canonical comparator.

## Canonical comparison and remaining work

Fresh pinned VC8 builds use the existing unit and unchanged profile. The
preceding source has a 16,481-byte COFF section tail and metadata at `+3DF0`.
The corrected source has a 16,521-byte section tail and metadata at `+3E18`;
the target's first table is at `+3E28`. These lengths include metadata and
are not authored-byte credits. All previously identical diagnostic owners
remain identical: **14/41** before and after.

The whole 15,910-byte comparison remains nonexact at **+12E / 5F20AE**,
target byte `F0`, candidate `07`. The corrected comparison-window SHA-256 is
`beafd48300ee162e4583de8a8f00eaf2486e56dd9d4e673e1e18ac3338a12ba7`.
Branch/store ownership, range lowering, floating lifetimes and original TU
context remain open. The older 16,453-byte / `+3DD4` function-ledger prose
predated the September predicate correction and did not describe the fresh
baseline; it is replaced with current evidence.

Only this nonexact unit is rebuilt. No shared header, compiler flag, accepted
unit, relocation contract or exact ledger changes; no unrelated/full replay is
needed. Reproduce with:

```bash
python3 scripts/build.py --unit gpt-web-default-cpu-action-policy --json
python3 scripts/compare-unit-object.py gpt-web-default-cpu-action-policy build/match-units/GptWeb_DefaultCpuActionPolicy.obj --json
python3 scripts/audit-giant-action-owners.py default-cpu-action-policy build/match-units/GptWeb_DefaultCpuActionPolicy.obj --unit gpt-web-default-cpu-action-policy --json
python3 scripts/audit-cpu-boundary-paths.py build/match-units/GptWeb_DefaultCpuActionPolicy.obj
```

The comparator exits 1 for the nonexact root. The execution command exits 1
for a discovered difference and 2 for a failed probe, rather than treating an
incomplete run as a pass. Seven target-independent tests protect policy-join
selection against unrelated registers/offsets/constants, duplicate or separated
pairs and truncated decoding.

## Direct Ghidra working state

A single direct Ghidra process re-attested the imported executable identity,
actual entry point, Windows/x86 analysis target and every mapped `.text` byte.
It saved the complete root, ECX receiver/no stack arguments, a method-focused
`CpuActionPolicyPrefix770View` with **27 physical fields**, and six boundary
comments. The prefix is a view, not a claim about complete original class size.
A fresh read-only process verified the metadata and unchanged callable bytes.
The hypothesis has no PIC/unreachable warning; its globals-overlap warning is
not a source result. No decompiler text is pasted into reconstruction source.

The verified project was copied back to the primary private database only
after Java exited; the temporary project was removed. Private
recipes and hypotheses are under `.analysis/cpu-root-20261017/`; reports use
`build/cpu-root-20261017-`. The shared Fighter root `4740C0` remains at its
53/66 diagnostic checkpoint; this pass changes no common-action source.
