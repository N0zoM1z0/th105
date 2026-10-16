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
target byte `F0`, candidate `07`. After the height-guard follow-up below, the
comparison-window SHA-256 is
`4018df0d170704fa9e78800e3aaf9e096206f697ce7be1713b24141dd48c9326`.
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

## Follow-up: reset flow and complete native execution

The action-302 reset prefix now expresses zero mode as the first arm, then
conditionally regenerates an empty policy counter in modes other than 3.
This recovers the branch shape observed at target `5F240A`: `JNE`, a zero-word
store and a jump to the counter reload. The preceding source emitted the
opposite fallthrough layout.
Calls, values and field widths are unchanged. Only the action-302 diagnostic
difference report changes, from 31 edit groups to 29; all other owner reports
are unchanged. Whole-root exactness remains unproved, with the same 14/41
diagnostic owners, section length, metadata offset and first mismatch.

The new command executes each sampled path through its actual native RET:

```bash
python3 scripts/audit-cpu-policy-paths.py build/match-units/GptWeb_DefaultCpuActionPolicy.obj
```

Unlike the bounded outer-phase control, this command executes all five original
dependencies without replacing helper results. It runs the actual MT seed
function and discards one real draw before preserving a seeded input state.
Each case restores that state; eight seeds include 0, 1, 42, 5489 and FFFFFFFF.
The original selector uses ratio division, not modulo, so native execution also
preserves its real result distribution, registers and flags.

The checked-sequence input is a native eight-slot pointer ring with head zero
and one live 98-byte record. Actual `4399C0` bounds checks, pointer access and
RET4 execute. Original atan2 and float-to-integer code execute as well. The
emulator permits writes only to the actor, stack, MT array and MT index. A mapped
return marker allows RET to execute; the command requires the expected PC,
four-byte caller stack displacement and restored x87 TOP.

The **5,000 controls** vary all outer action groups and all named policy
destinations, opponent action, coordinates, velocities, facing, mode, resource,
signed counter/timer boundaries and seed. They compare the entire 7A4-byte
actor prefix, final MT state, call order/arguments and observed RNG/atan2
results, x87 inputs to conversion, stack cleanup and control word. The actor
prefix is an execution fixture, not a new complete class-size claim.

Fresh configured-object execution has **0/5,000 differences**. Both target and
candidate execute the following native helper entries; setup draws are excluded:

| Helper | Calls in each execution set |
| --- | ---: |
| atan2_degrees | 136 |
| mt19937_next_u32 | 10,167 |
| selector_random_roll | 9,840 |
| checked sequence | 270 |
| ftol2_sse | 10,136 |

The sampled paths visit **3,553 distinct target instruction addresses out of
4,069**, and 3,508 candidate instruction addresses. This is sampled execution,
not complete branch coverage or canonical byte credit. Coordinates are finite,
the peer is active, sequence-state55A is 1, and exceptions remain masked with
PC53. Inactive/other sequence states, all RNG streams, NaNs through the complete
function and exception behavior remain outside this matrix. The existing
16,600 outer-phase controls, including NaNs, still have zero differences after
the reset change. The final native input-set SHA-256 is
`2bd4b7c7883a74520652cf5d44007c08268a12768da2decf069c6fd91c9a37cf`;
the report also pins Python, Unicorn, its loaded library and the configured
object hashes.

A separate complete-return negative control rebuilds the preceding CPU source
from `9a38963`. The checked-in NaN fixture leaves target control6D0 at0, while
that historical object writes2; the current object matches. This confirms the
native oracle detects a known defect. Reproduce the current positive control
without rerunning the matrix:

```bash
python3 scripts/audit-cpu-policy-paths.py build/match-units/GptWeb_DefaultCpuActionPolicy.obj --case-file tests/fixtures/cpu-native-nan.json
```

An explicit case file is a nonempty JSON array with the matrix's input fields;
a `<field>_bits` hexadecimal string can supply the raw pattern for any float
input: `self_x`, `other_x`, `self_y`, `other_y`, `vx` or `vy`.

Additional private controls are not retained: making the real MT/selector
definitions visible regresses to 11/41 owners; rewriting all five remaining
nonzero-first reset prefixes displaces other physical suffixes; reorganizing
the grounded/airborne source blocks, typed physical-field substitutions and
float zero literals provide no identical-owner gain. No compiler flags,
headers, TU partition or relocation contracts change. Direct Ghidra was
re-attested/read back for this work; its target bytes and saved ABI/view remain
unchanged. Reports for the retained checkpoint use
`build/cpu-root-20261017-reset-`.

## Follow-up: ordered heights and RNG consumption

The common airborne decision phase had three more unordered-input errors.
The exact target compares peer height against self height, then rejects the
unordered case before calling RNG:

| Target predicate | Observed flags and rejection | Source rejection guard |
| --- | --- | --- |
| `5F41C4 FCOMPP` | `5F41C8 TEST AH,5`; `5F41CB JP` | `!(peer_y < self_y)` |
| `5F4503 FCOMPP` | `5F4507 TEST AH,5`; `5F450A JP` | `!(peer_y < self_y)` |
| `5F458F FCOMPP` | `5F4593 TEST AH,0x41`; `5F4596 JNE` | `!(peer_y > self_y)` |

For unordered comparison, AH contains `0x45`: parity rejects both `TEST AH,5`
guards, and nonzero rejects the `TEST AH,0x41` guard. The retained `>=` and `<=`
source expressions were false for NaN, allowing an extra RNG call instead.
The source now uses the negated ordered predicates. This recovers observed
branch semantics without asserting original source spelling or full exception
behavior. No ABI, type/layout, compiler, partition or relocation contract changes.

A concrete full-return counterexample uses action201, sequence200, self X100,
peer X250, self Y quiet NaN, peer Y0, zero velocity, positive facing, mode1,
resource1000, policy0, counter100, timer10, refresh1 and seed0. Target RNG1000
results are592 and715; the preceding object additionally consumes844. The
immediate actor bytes happen to agree, but helper order and final MT state
differ. The corrected object consumes exactly the target stream.

The reproducible **368-case** height matrix includes224 controls over seven
finite/NaN height pairs, distances150/200, sequences200/212 and eight real MT
seeds. The remaining144 bypass common attacks with peer action100 and select
policy0 with timer0. Float bit strings preserve NaN inputs without nonstandard JSON.

| Native complete-return execution | Differences |
| --- | ---: |
| Fresh preceding configured object | **112 / 368** |
| Corrected configured object | **0 / 368** |

Reproduce the current positive control with:

```bash
python3 scripts/audit-cpu-policy-paths.py build/match-units/GptWeb_DefaultCpuActionPolicy.obj --height-cases
```

Both reports pin input SHA-256
`6fef66471aadc3cf4361022df18acd143002731e0aa1bf25b34f375194a16ebf`.
Each target selector/MT entry executes1061 times; the preceding candidate
has1173 calls to each and the corrected candidate1061. Each side also executes736 native conversions and
two checked-sequence calls. This matrix executes no atan2 path; the separate
5000 finite controls exercise all five helpers. After the final source change,
those5000 finite controls and the16600 outer-phase controls still have zero
differences. Complete nonfinite, exceptional and gameplay coverage remains open.

The focused configured build and canonical comparator still report nonexact
at+12E, metadata+3E18 and16521-byte section tail. All14/41 identical diagnostic
owners survive. Only the common airborne body, physically grouped under
`actions:414` by the owner diagnostic, changes; no partial exact credit is
recorded. Raw target facts above are mirrored in three direct Ghidra comments,
saved and checked in a fresh read-only process after re-attesting the target,
entry, mapped text and body hash. Target bytes and the27-field ABI view remain
unchanged. Reports for this checkpoint use `build/cpu-height-`.
