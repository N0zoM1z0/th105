# Iku incoming-action and payload relation

Historical f11d36b checkpoint. The subsequent
[glide exit recovery](IKU_GLIDE_EXIT_OWNERSHIP_2026_10_17.md) changes source and
instruction counts while retaining the84-home/59-identity correlation below.

The selected Iku620920 source remains unchanged. Preserving incoming action
and pointer provenance together removes the11 ambiguities in the earlier
home-set correlation: under the same action-group/physical-call-ordinal
pairing, all84 target homes now have one candidate home,59 at the same offset.
This is a conditional static bijection, not payload-value, path-feasibility,
original-variable or canonical-match proof. Whole59038 comparison remains
**nonexact+0x64 /620984**. No authored exact credit changes.

## Target observations and analysis

Target is original Japanese TH10.5 v1.06a, executable SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Root `[620920,62EFBE)` hashes to
`abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea`.
Wrong-image IDA was rejected; this work uses hash-attested raw target bytes.

`audit-iku-payload-homes.py` can now retain separate states for each
`(instruction, incoming action)`. Every state starts at the actual root
prologue. An action label is assigned only on the first reviewed action entry;
it persists through other arms' shared tails. The209/221 shared entry forks
labels while preserving its real incoming stack/register state. No arm is
treated as a standalone callable or seeded with invented register values.
Stack depth must agree at every instruction even across different actions.
Unknown and null pointer possibilities remain explicit within their action;
multiple pointer paths within one action remain sets.

The v2 `audit-iku-call-sharing.py --partition-payloads` checks the action sets
at all182 physical spawn sites against independent CFG-origin propagation.
Both images yield190 action/site records with no unknown payload origins.
Unique-PC coverage stays14870 target /14776 candidate before the independently
qualified epilogue restore. State counts are16959/16828. Frame400hex, all84
homes, aggregated site/home sets and unknown-site lists agree with the
unpartitioned audit. The final serial run took about6 seconds and231MiB peak RSS.

## Conditional cross-image correlation

Pairing still uses equal incoming-action groups and physical CALL ordinal
within each group. For each pair, constraints now use the same individual
action's pointer origins. No sorted zip of home sets or assumed bijection is
used to create constraints. A bijection is reported only after independent
constraints are all singleton, consistent and cover both complete84-home sets.
Missing, unknown, different null possibilities or inconsistent evidence blocks
that conclusion. The old union mode remains available and still reports
73 singleton constraints /49 identities /11 ambiguities.

The25 nonidentity correlations are below; the other59 preserve their offsets.
Offsets are relative to the ordinary body stack base after frame allocation
and four callee-save pushes. The action column is target provenance, not a
claim about original C++ variable declarations.

| Target home | Candidate home | Incoming action |
| ---: | ---: | ---: |
| 152 | 164 | 540 |
| 164 | 176 | 541 |
| 176 | 152 | 415 |
| 200 | 212 | 411 |
| 212 | 308 | 720 |
| 224 | 272 | 412 |
| 272 | 224 | 506 |
| 308 | 200 | 415 |
| 320 | 392 | 416 |
| 332 | 368 | 610 |
| 344 | 428 | 417 |
| 356 | 344 | 660 |
| 368 | 380 | 610 |
| 380 | 356 | 660 |
| 392 | 320 | 599 |
| 404 | 332 | 780 |
| 416 | 452 | 797 |
| 428 | 416 | 546 |
| 440 | 512 | 302 |
| 452 | 476 | 601 |
| 476 | 440 | 609 |
| 512 | 404 | 545 |
| 536 | 992 | 414 |
| 752 | 536 | 416 |
| 992 | 752 | 300 |

These are evidence for recovering genuine lifetimes and statement ownership.
Do not manually permute storage, add padding or remap stack bytes to obtain
acceptance. The normal canonical comparator remains unchanged.

## Shared effect tail and unselected source controls

The six416/417/565/566/567/568 paths enter the shared tail with X in ST0.
The565..568 heads finish with FLD actorX;416/417 reload the rounded subtraction
result. Pending Y/direction/flag arguments are already prepared. The21 bytes
`[626C34,626C49)` store X to the pending argument, push effect62, set ECX=this,
call435240 and then call vslot0x14. SHA-256:
`3786f23f4dcf1ea897e5a906e934191fc9549ec9345b9188ec1749f18aa6be03`.
Incoming jumps are626FC3/629DF8/62A5CA/62AE2B/62B6D3, plus416 fallthrough.
Candidate565..568 prepare ECX earlier and retain four separate effect calls.
This is a joint argument/suffix scheduling difference, not four missing effects.

Two bounded natural C++ controls remain unselected:

- Inlining416/417's X subtraction into the effect argument instead of its
  float local is byte-neutral over all59594 normalized bytes, SHA-256
  `33f09d2ac49075ed6495a5b10a884fe18cf1f5b9e8556dcdec157eb58038549d`.
- Replacing565..568's outer timer test with independent existing middle_frame
  predicates for frames5/6 recovers a timer carrier and the second timer test,
  corroborated by raw629DAC/629DFD. It still leaves the four extra effects,
  expands the section to60046 bytes and changes unrelated lowering. SHA-256
  `90f9147103f44f8689c027808e3a022ba02dc0195c15dc3b438150695faedae3`.
  This phase-scoped negative result does not settle original source spelling.

Both strict comparisons first differ+64hex; neither control is promoted from
a local resemblance or call count. Their unused objects/full source copies
were deleted; small private diffs retain the hypotheses.

## Reproduction and remaining work

```sh
python3 scripts/build.py --unit gpt-web-iku-action-state --compare --json > build/iku-effect-tail-baseline.json
python3 scripts/audit-iku-call-sharing.py --object build/match-units/GptWeb_IkuActionState.obj --partition-payloads > build/iku-action-payload-partition.json
python3 scripts/audit-iku-call-sharing.py --object build/match-units/GptWeb_IkuActionState.obj --payload-homes > build/iku-action-payload-unpartitioned.json
python3 scripts/ci.py
git diff --check
```

The focused build intentionally exits1 for nonexact+64hex. Reports bind the
root/object hashes, action-entry inventories and analysis/support script hashes.
Nine new tests cover shared and crossed entries, real prologue state, null and
unknown isolation, within-action ambiguity, global stack disagreement,
reversed shared correlations and missing/duplicate evidence.

Source CRLF SHA-256 remains
`ff79e5743533c50c885a0139facff1febc726f2c2b5e5a84497fe2bd27b014ad`.
No accepted shared header/layout/profile/partition/relocation changed; no old
native matrix or unrelated accepted-unit replay is needed for these diagnostics.
The [full linked replay](IKU_LINKED_REPLAY_2026_10_17.md) remains applicable.
Continue genuine call-argument/scalar lifetime recovery using the now-separated
action/pointer relation. Original TU/inheritance/compiler phase, payload-value
equivalence and post-backend/exception behavior remain unknown.
