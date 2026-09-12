# Common Fighter: landing-owner recovery

## Scope and current result

This batch works only on shared `Fighter_update_common_action_state` at
`0x004740C0`, with its full 10,219-byte boundary. It is **still nonexact**.
No function or partial authored bytes are added to `matches.csv`.
The existing VC8 SP1 `/O2 /GS-` profile, headers, layouts, symbol ABI and
relocation bindings are unchanged.

Target identity is the original Japanese 1.06a executable, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Fresh preflight and IDA evidence are in
`build/common-fighter-current-preflight.json` and
`build/common-fighter-current-typed.json`. The prior documentation was used
as a hypothesis list; the baseline was independently compiled and audited.

| Measure | Fresh baseline | Retained change |
| --- | ---: | ---: |
| Instruction/edge-identical diagnostic owners | 51/66 | 52/66 |
| Previously identical owners lost | — | 0 |
| Absolute owner-span residual | 173 bytes | 165 bytes |
| Candidate metadata offset | +0x2840 | +0x2838 |
| COFF section tail, including metadata | 10809 bytes | 10801 bytes |
| Full canonical first mismatch | +0x14 | +0x14 |

Target compared-body hash:
`7def23cf4826d7511260e7d9ea8db18848c43a7b77939bb42724a29af117a0c6`.
Final nonexact comparison-window hash:
`bfa18b3551f6ac4f1c2782b40f5e63aa63ab195fd2765cb5c74146b648877caf`.
The section tail is not the callable boundary and is not an authored byte count.

## Observed action-74 control flow

After reducing vertical velocity and calling the descending-surface predicate,
the target at `0x00474AF2` branches on zero to `0x00474838`, the case-72
advance-frame body. Its nonzero path jumps at `0x00474AF8` to the shared
landing body at `0x00474743`. There is no additional tail-call epilogue here.

The retained source formerly used a negative early return:

```cpp
if (!has_crossed_stage_surface_while_descending()) {
    advance_frame_and_dispatch();
    return;
}
// landing statements, then break
```

The recovered source has the same calls, stores and conditional behavior,
but retains the complete structured branch:

```cpp
if (has_crossed_stage_surface_while_descending()) {
    // Existing landing statements, in their original order.
} else {
    advance_frame_and_dispatch();
}
break;
```

The real source preserves the predicate's existing unsigned-byte consumption.
This removes the candidate's eight extra bytes and reproduces the complete
170-byte physical action-74 owner, including both target-owner destinations.
It is a sufficient source/control-flow distinction, not unique original
formatting or a standalone exact-function claim.

Twenty function-scope variables occurring only in their declarations were
also removed. A second formal production build has the same comparison-window
hash as the successful branch-only probe; this cleanup is byte-neutral.
No used local was narrowed, hoisted or assigned fake liveness.

## Rejected probes in this batch

These experiments remain below `build/`; none is incorporated into production:

- Replacing the shared 73/75/88 sequence label with independent selection
  blocks fixes some local lengths but duplicates the action-75 terminal and
  relocates epilogues. A fully structured sequence cohort also fails its
  target-owner destinations. Neither is accepted based on same-size spans.
- Independent action-0 clamps with real float intermediates still expand
  159..162 from 61 to 146 bytes each and change the local rounding/reload
  sequence in 55/56. Local span changes alone do not establish lost rounding:
  a shared destination must also be traced. Promoting the rounded results
  to double changes comparison opcodes
  and produces 148-byte late owners. Neither numerical spelling closes the
  original shared clamp contract.
- A source-local action-790 positive `else if` chain is byte-neutral to the
  action-74 checkpoint and does not restore its target action-140 epilogue.
- Re-expressing 53/54's terminal and the 51/52 exits leaves the same misplaced
  shared action-0 destination. No arbitrary label/storage placement is retained.
- Strict FP with exception-sensitive scheduling disabled produces a visibly
  non-target aligned EBP frame. Formal comparison also stops at an unmapped
  `__real@3b23d70a` float literal, while the switch diagnostic cannot pair its
  candidate table. No double/float alias or new mapping was invented
  to bypass these failures; there is no completed canonical result for this
  rejected profile.
- Native `std::min<float>` remains an out-of-line call in this large caller.
  The comparator/audit reject the unmapped helper. The target has no such
  call; forced helper bindings would not be truthful reconstruction.

## Remaining source/code-generation questions

The 14 nonidentical physical owners separate into four groups:

- Entry and the high dispatcher: SUB versus ADD-negative selector encodings.
- 53/54/55/56 and 159/160/161/162: target action-50 clamp/advance ownership
  versus the candidate's late action-162 copy, with associated rounding and
  alignment differences.
- 73/75/88: target action-73 sequence-selection owner versus candidate action
  88, plus the associated shared epilogue routes.
- High action 790: target action-140 terminal versus candidate action 150.

The action-74 success is evidence that remaining differences must not all be
labeled an unavoidable LTCG wall. Conversely, the negative probes do not
justify padding, copied bytes, forced registers, inert locals, artificial
return types or accepting normalized owner counts as canonical matches.

## Focused reproduction

```bash
python3 scripts/check-ida-mcp.py
python3 scripts/typed-re.py 0x004740C0 --max-bytes 10219 --json
python3 scripts/build.py --unit gpt-web-fighter-common-action-state --compare --json
python3 scripts/audit-giant-action-owners.py fighter-common-action \
  build/match-units/GptWeb_FighterCommonActionState.obj \
  --unit gpt-web-fighter-common-action-state --json
```

The build/comparison deliberately returns exit 1 for the nonexact body. The
audit returning zero only means the diagnostic succeeded. Final local reports:
`build/common-fighter-landing-final-formal.json`,
`build/common-fighter-landing-final-owners.json`, and
`build/common-fighter-landing-final-map.json`. Only this function was rebuilt;
there was no unrelated module replay or global cold build.

## Follow-up: action-790 terminal ownership (52 -> 53)

Fresh IDA attestation and the complete bounded instruction packet are
`build/common-fourteen-preflight.json` and
`build/common-fourteen-typed.json`. This follow-up changes only the same
function; the landing result above is the preceding checkpoint.

**Observed target:** after advance-frame dispatch, high action 790's
`JNZ` at `0x004765ED` reaches `0x00475440`, the action-140 `set_action(0)`
terminal. The terminal loads the vtable slot at +8, pushes action zero,
calls with ECX=this, then restores the frame and returns. The previous
candidate instead chose the identical terminal physically owned by action 150.

**Retained source inference:** preserve action 140's `return`, but express
ordinary completion in actions 143, 144, 150, 151, 152 and 153 with `break`.
The switch has no subsequent observable statements. Calls, stores, field
widths and ABI are unchanged. This coherent exit cohort makes VC8 choose
the target terminal and reproduces all instructions and edges of the
296-byte action-790 owner. It does not uniquely identify original syntax.

The production rebuild has **53/66** instruction/edge-identical owners,
with all previous 52 preserved. Metadata remains +0x2838 and section tail
10801 bytes. The canonical 10219-byte comparison remains nonexact at +0x14;
its comparison-window hash is
`99563500433bccf1f68e7c256b438595de9cdcf5b18aee4816f19e69e1cda835`.
No exact ledger, compiler profile, layout or relocation mapping is changed.
Reports: `build/common14-checkpoint-formal.json` and
`build/common14-checkpoint-owners.json`; use the focused commands above.

Additional negative controls, compiled only as private single-root probes:

- Moving the common action-0 advance label into action 50 moves its entire
  boundary/advance tail to action 162, losing action 50 despite a smaller body.
- Making action-51/52 and the generic action-0 completion use `break` does not
  repair the clamp/advance owner cohort.
- Duplicating a genuinely used sequence-selection terminal lets action 73
  match locally, but loses action 799 and leaves 75/88 routed to a second
  selection owner. No local improvement with that regression is retained.
  Giving the secondary terminal `return` instead is diagnostically neutral.
- Explicitly spelling `switch (v2 - 50)` and the corresponding high-switch
  subtraction, with algebraically shifted labels, produces the same canonical
  comparison-window hash. It does not fix SUB versus ADD-negative.

The remaining **13** diagnostic owners are entry, low 53/54/55/56,
73/75/88, 159/160/161/162 and low 180 (including the high dispatcher).
They remain three shared control-flow/code-generation questions, not 13
independent exact-function claims.

## Follow-up discriminators on the remaining 13 owners

IDA preflight was repeated successfully in `build/common13-preflight.json`.
The retained production checkpoint is still 53/66; none of the following
private single-function probes replaces it. Remote CI for `2dde1fd` passed
in run `34679459245`; the local commit gate passed all 101 tests.

### Native action-0 assignment cohort

`build/common13-native-assignment.cpp` tests the same source form as the
already matching action-2 cohort: use a rounded assignment expression in
the clamp, retain action 50's `return`, and use ordinary `break` completion
in 51/52/53/54/55/56 and 159..162. Remove the explicit shared clamp labels.
For 159..162, retain the two genuinely consumed float intermediates before
assigning and testing the field. Unlike the earlier independent-clamp probe,
51/52 also join the switch exit and the clamp tests the field assignment:

```cpp
if (velocity_x_f4 < 0.0f) {
    first = velocity_x_f4 + 0.6000000238418579;
    second = first + 0.6000000238418579;
    if ((velocity_x_f4 = second) > 0.0f)
        velocity_x_f4 = 0.0f;
}
// Existing boundary/peer update, advance and set_action(0), then break.
```

The audit reaches **56/66**, gaining all of **53/54/55/56**, but loses
action 799 through an extra NOP. The late four owners each expand from
61 to 146 bytes; metadata grows to 10560. This is a rejected regression,
not four newly accepted blocks or evidence of a smaller canonical residual.

The fresh target at `0x00475B64..0x00475B80` loads velocity and the double
0.6000000238418579 constant, adds, exchanges, stores the first float stage,
adds that stage, and stores/reloads the second float stage. The native
candidate emits this same sequence at +0x1AA0..+0x1ABC. Its following
clamp/boundary/advance tail is duplicated locally, whereas the target jumps
to action 50 at `0x00474122`. The two-stage rounding sequence is therefore
reproducible; this experiment does not establish a fundamental rounding
limitation or an unavoidable LTCG cause.

Further controls:

| Private probe suffix (`build/common13-*.cpp`) | Diagnostic result | Rejection reason |
| --- | --- | --- |
| `adjacent-clone` | 56/66, metadata 10560 | Exact adjacent action-2 peer/call cast spelling does not repair late ownership. |
| `rounded-expression` | 56/66, metadata 10560 | Nesting both float casts in the assignment does not repair late ownership. |
| `native-early` | 52/66, metadata 10320 | Restoring explicit late shared labels also steals the early four owners again. |
| `late-returns` | 46/66, metadata 10924 | Late return completion additionally regresses action-2 owners 66/67/163..166 and action 799. |
| `direct-primary` | 51/66, metadata 10212 | Putting shared labels directly in action 50's real clamp still moves the tail to 162; action 50 shrinks to 49 bytes and no longer matches. |
| `sequence-exit` | 53/66, metadata 10296 | Action 88's ordinary completion as break does not move the selection owner. |
| `sequence-conditional` | 53/66, metadata 10296 | One ternary-argument set_sequence call does not move the selection owner. |

The `native-size` control adds source-local `#pragma optimize("s", on)` to
the native cohort. Its canonical comparison fails at entry +0x00: it starts
with an EBP frame rather than the target PUSH ECX. Section tail is 7791
bytes, and the owner audit cannot identify the expected low switch table.
There is **no completed owner count** for that profile; no compiler setting
is retained. Its empty failed-audit JSON must not be treated as a zero score.

All completed owner results above come from the full-root
`audit-giant-action-owners.py` command, with the corresponding
`build/common13-<suffix>-audit.json` report. They are not canonical byte
comparisons. For future work, preserve the distinction between reproducible
local instruction sequences and simultaneous whole-root owner placement;
do not retain NOP removal, padding or manufactured liveness to compensate
for these source regressions.

Finally, `build/common13-unsigned-selectors.cpp` preserves the signed outer
690 partition but casts both inner switch selectors to unsigned. All listed
case values are unchanged; negative low actions still select default.
The focused canonical comparison reproduces the retained hash
`99563500433bccf1f68e7c256b438595de9cdcf5b18aee4816f19e69e1cda835`,
and the full-root diagnostic remains 53/66 with metadata 10296. Together
with the explicitly normalized-selector control above, this rejects these
two simple selector-expression hypotheses for SUB versus ADD-negative.

The subsequent exit/ABI/visibility batch is recorded in
[COMMON_FIGHTER_EXIT_PHASE_EVIDENCE_2026_09_12.md](COMMON_FIGHTER_EXIT_PHASE_EVIDENCE_2026_09_12.md).
It preserves the 53/66 checkpoint and demonstrates that a single native
switch can emit the target SUB encoding, but still fails complete ownership.
