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
  159..162 from 61 to 146 bytes each and lose required rounding reloads in
  55/56. Promoting the rounded results to double changes comparison opcodes
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
