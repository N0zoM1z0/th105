# Default CPU policy0: native instruction coverage

This checkpoint concerns only the original Japanese1.06a CPU decision root
`Fighter_update_default_cpu_action_policy @ 005F1F80`,15910 callable bytes.
It extends the [ordered-boundary evidence](CPU_ORDERED_BOUNDARIES_2026_10_17.md).
The reconstruction source and its build/ABI/relocation contracts are unchanged.
No exact or partial byte credit is recorded.

## Observed target region

The validated policy index/destination tables select `005F47B0` for policy0.
Direct control-flow traversal from that internal entry reaches **1486
instructions /4879 bytes**, including shared return tails. Every branch stays
inside the enclosing callable; the only external transfers are native calls to
`selector_random_roll @ 004067D0`. There is no unresolved indirect exit or
internal call. This is an internal reachable region, not another function or
an exclusive byte-ownership claim.

The first14400 finite controls visited1455 of these instructions. The remaining
31 were the ladder at `005F5731` and its return: close airborne fighters with
self height500, peer height100 and distance90 reach the missing roll25..39
paths. Adding that height pair closes the instruction gap.

## Reproducible complete-return execution

```bash
python3 scripts/build.py --unit gpt-web-default-cpu-action-policy --compare --json
python3 scripts/audit-cpu-policy-paths.py build/match-units/GptWeb_DefaultCpuActionPolicy.obj --selection-cases
```

The first command still exits1 for the nonexact root. The second executes
**16000 controls with zero differences** and requires complete target-region
instruction coverage plus observed policy rolls0..99. It compares the full
7A4-byte actor prefix, MT state, native calls/results, conversion inputs, stack
and x87 control word through the actual native RET.

The matrix uses100 distinct real MT seeds, ten ground/air height pairs, four
distances and both facings at both stage edges. Action201, peer action100,
policy0, timer0 and refresh1 isolate policy selection. The two persistent
control DWORDs start at1 and-1, rather than relying on zero input to detect
preserved values. Other initialized actor/container states retain the native
probe's documented scope.

`tests/fixtures/cpu-policy-selection-seeds.json` contains input seeds ordered
by their predicted selection roll. The original MT seed, discarded warm draw,
entry RNG1000 call and selection RNG100 call all execute. The target must
confirm every predicted roll; fixture numbers never replace a helper result.
The selector retains its actual ratio division, not modulo.

| Observation | Target | Candidate |
| --- | ---: | ---: |
| Distinct selection rolls | 100 (0..99) | 100 (0..99) |
| Native selector / MT entries, each | 45940 | 45940 |
| Native conversions | 32000 | 32000 |
| Distinct root instruction addresses visited | 1578 | 1554 |
| Reachable policy0 target instructions visited | 1486/1486 | no candidate-address identity claim |

The matrix executes no atan2 or checked-sequence path. Those dependencies are
covered by the separate5000 finite whole-root controls, not this region claim.
The matrix input SHA-256 is
`77bfa4510ee00ca1cf9bce3cbe20fdad06db5d64fdc0bab74d704be00aa60ad2`.
Reports under `build/cpu-tail-` pin executable/body, object and emulator hashes.

The coverage gate derives the internal entry from the attested target tables,
uses the existing raw CFG auditor and fails on an unreviewed transfer. A wrong
predicted roll is rejected against actual target execution. A one-case negative
control has matching output but visits only36/1486 region instructions and is
reported incomplete. Missing instruction coverage or observed rolls makes the
selection CLI exit1; failed input/target/execution validation exits2.

## Limits and next action

Instruction coverage does not prove every branch edge, numerical input, RNG
stream or exception behavior. The rare selector result100 from rawFFFFFFFF is
outside the roll0..99 matrix. The peer remains active and sequence-state55A
is1; unmasked exceptions and other gameplay states remain open. Another3840
finite/nonfinite controls with the common attack phase bypassed have zero
differences, without extending the coverage claim above to all nonfinite cases.
The existing368 height controls and checked-in NaN fixture still pass after
the probe changes.

The fresh configured whole-root comparison remains nonexact at **+12E /
005F20AE**, targetF0 / candidate07. Metadata stays at+3E18 and the COFF section
tail is16521 bytes; all14/41 previously identical diagnostic owners survive.
The compared15910-byte candidate window still hashes to
`4018df0d170704fa9e78800e3aaf9e096206f697ce7be1713b24141dd48c9326`.
The new finite execution coverage narrows the next investigation to compiler
source shape, range lowering and physical shared-tail ownership; it is not an
acceptance substitute.

Rejected private controls are retained only as evidence: reading every stored
roll directly adds one identical diagnostic owner but grows the main selection
body from1402 to1443 candidate instructions, versus1414 target instructions;
a stored-field snapshot does not improve the owner count. Local
`fenv_access(on)` regresses14 to13 owners. Ordinary `/O2 /Os` changes to an
EBP frame and fails at the first byte. `/fp:fast` introduces a new float-zero
dependency and different operand forms; no compiler profile or relocation
ledger change is retained. Further spelling/flag matrices are not the next step.

Direct Ghidra re-attests executable identity, entry, mapped text and body hash.
Two saved comments identify the policy0 reachable region and the formerly
unvisited height branch; a fresh read-only process verifies them. Target bytes,
the ECX/no-stack ABI and the27-field physical view remain unchanged. The
verified private project replaces its working predecessor only after Java exits;
temporary copies and probe objects are removed.
