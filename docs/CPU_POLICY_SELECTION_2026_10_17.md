# Default CPU policy 0: native instruction coverage

Follow-up: the Aya policy-tail study
adds a genuine seed for roll 100. The live `--selection-cases` command now runs
16160 cases for rolls 0..100. The 16000-case measurements below describe the
earlier corpus.

This checkpoint concerns only the original Japanese 1.06a CPU decision root
`Fighter_update_default_cpu_action_policy @ 005F1F80`,15910 callable bytes.
It extends the [ordered-boundary evidence](CPU_ORDERED_BOUNDARIES_2026_10_17.md).
The initial coverage checkpoint left source and build/ABI/relocation contracts
unchanged. The [source-ownership follow-up](CPU_SOURCE_OWNERSHIP_2026_10_17.md)
now supplies the current source and canonical comparison.
No exact or partial byte credit is recorded.

## Observed target region

The validated policy index/destination tables select `005F47B0` for policy 0.
Direct control-flow traversal from that internal entry reaches **1486
instructions /4879 bytes**, including shared return tails. Every branch stays
inside the enclosing callable; the only external transfers are native calls to
`selector_random_roll @ 004067D0`. There is no unresolved indirect exit or
internal call. This is an internal reachable region, not another function or
an exclusive byte-ownership claim.

The first 14400 finite controls visited 1455 of these instructions. The remaining
31 were the ladder at `005F5731` and its return: close airborne fighters with
self height 500, peer height 100 and distance 90 reach the missing roll 25..39
paths. Adding that height pair closes the instruction gap.

## Reproducible complete-return execution

```bash
python3 scripts/build.py --unit gpt-web-default-cpu-action-policy --compare --json
```

The first command still exits 1 for the nonexact root. The second executes
**16000 controls with zero differences** and requires complete target-region
instruction coverage plus observed policy rolls 0..99. It compares the full
7A4-byte actor prefix, MT state, native calls/results, conversion inputs, stack
and x87 control word through the actual native RET.

The matrix uses 100 distinct real MT seeds, ten ground/air height pairs, four
distances and both facings at both stage edges. Action 201, peer action 100,
policy 0, timer 0 and refresh 1 isolate policy selection. The two persistent
control DWORDs start at 1 and-1, rather than relying on zero input to detect
preserved values. Other initialized actor/container states retain the native
probe's documented scope.

`tests/fixtures/cpu-policy-selection-seeds.json` contains input seeds ordered
by their predicted selection roll. The original MT seed, discarded warm draw,
entry RNG 1000 call and selection RNG 100 call all execute. The target must
confirm every predicted roll; fixture numbers never replace a helper result.
The selector retains its actual ratio division, not modulo.

| Observation | Target | Candidate |
| --- | ---: | ---: |
| Distinct selection rolls | 100 (0..99) | 100 (0..99) |
| Native selector / MT entries, each | 45940 | 45940 |
| Native conversions | 32000 | 32000 |
| Distinct root instruction addresses visited | 1578 | 1554 |
| Reachable policy 0 target instructions visited | 1486/1486 | no candidate-address identity claim |

The matrix executes no atan2 or checked-sequence path. Those dependencies are
covered by the separate 5000 finite whole-root controls, not this region claim.
The matrix input SHA-256 is
`77bfa4510ee00ca1cf9bce3cbe20fdad06db5d64fdc0bab74d704be00aa60ad2`.

The coverage gate derives the internal entry from the attested target tables,
uses the existing raw CFG auditor and fails on an unreviewed transfer. A wrong
predicted roll is rejected against actual target execution. A one-case negative
control has matching output but visits only 36/1486 region instructions and is
reported incomplete. Missing instruction coverage or observed rolls makes the
selection CLI exit 1; failed input/target/execution validation exits 2.

## Limits and next action

Instruction coverage does not prove every branch edge, numerical input, RNG
stream or exception behavior. The rare selector result 100 from rawFFFFFFFF is
outside the roll 0..99 matrix. The peer remains active and sequence-state55A
is 1; unmasked exceptions and other gameplay states remain open. Another 3840
finite/nonfinite controls with the common attack phase bypassed have zero
differences, without extending the coverage claim above to all nonfinite cases.
The existing 368 height controls and checked-in NaN fixture still pass after
the probe changes.

The fresh configured whole-root comparison remains nonexact at **+12E /
005F20AE**, targetF0 / candidate 29. After the source-ownership follow-up, metadata is at
+3E38 and the COFF section tail is 16553 bytes; all 14 previously identical
diagnostic owners survive, with 15/41 now identical.
The current compared 15910-byte candidate window hashes to
`af511b4feecaa98f3b601749f9e3456a299a2fa22b720105c284833a7ee49566`.
The new finite execution coverage narrows the next investigation to compiler
source shape, range lowering and physical shared-tail ownership; it is not an
acceptance substitute.

Rejected private controls are retained only as evidence: reading every stored
roll directly adds one identical diagnostic owner but grows the main selection
body from 1402 to 1443 candidate instructions, versus 1414 target instructions;
a stored-field snapshot does not improve the owner count. Local
`fenv_access(on)` regresses 14 to 13 owners. Ordinary `/O2 /Os` changes to an
EBP frame and fails at the first byte. `/fp:fast` introduces a new float-zero
dependency and different operand forms; no compiler profile or relocation
ledger change is retained. Further spelling/flag matrices are not the next step.

Direct Ghidra re-attests executable identity, entry, mapped text and body hash.
Two saved comments identify the policy 0 reachable region and the formerly
unvisited height branch; a fresh read-only process verifies them. Target bytes,
the ECX/no-stack ABI and the 27-field physical view remain unchanged. The
verified private project replaces its working predecessor only after Java exits;
temporary copies and probe objects are removed.
