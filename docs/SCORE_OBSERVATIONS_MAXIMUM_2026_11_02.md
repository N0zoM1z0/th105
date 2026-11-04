# ScoreData observed maximum: operand-order verification

The existing source at `ScoreData::update_observed_record_statistics`,
`0x0042D010`, was already semantically correct. No source, type, ledger or
origin-anchor change is accepted in this checkpoint.

The native late comparison is `CMP EBX,[ESI+14h]; JLE` where EBX is the new
observation. It skips the store when the new value is less than or equal to
the stored value. The source emits `CMP [ESI+14h],EBX; JGE`, also retaining the
signed maximum. Comparing branch mnemonics without operand order produced an
incorrect minimum hypothesis. A temporary inversion and field rename were
fully restored from saved bytes; the native execution contradicted that
hypothesis. Those temporary replay receipts are not acceptance evidence.

## Evidence

- Canonical raw target hash verified; no IDA semantics used.
- Whole native extent191, SHA256
  `3d19b4fc049aa452ca13b25eaf72163499f21c3beed18590ec71637249951d75`.
- Fresh original source unit `gpt-web-score-observations`:182 bytes, SHA256
  `cd35ee25b63dcfe225de0cf77b19344a1f263e152f153850d5b5a33622f3fe1e`.
- Native has the nine-byte checked-iterator self-compatibility sequence at
  `42D05D`; ordinary current source omits it. No redundant synthetic check
  was inserted. This is the same unresolved compiler-context issue as the
  adjacent sequence-result method, not a new source-spelling search lane.
- `scripts/audit-score-observations.py` executes full original/source bodies
  with the two actual six-byte game/session getters. Thirteen bounded cases
  cover lower/equal/higher values, negatives and signed extremes, gating,
  empty/unmatched ranges, selector14 and duplicate-key early exit.
- All cases agree, preserve RET16/callee saves and leave the second duplicate
  record unchanged. The deliberately inverted minimum branch disagrees.
- Unknown instructions/helpers and unexpected writes fail closed using
  `native_callbacks.guarded_callback`, with errors checked immediately after
  emulation. Six target-independent tests cover these rejection paths,
  partial instructions, stack cleanup and nonvolatile preservation.
- No malformed-vector continuation, native OS calls, broad gameplay testing,
  universal equivalence, or exactness gain is claimed.

Reproduce after a fresh normal build:

```
scripts/repo-python scripts/build.py --unit gpt-web-score-observations --compare --json
scripts/repo-python scripts/audit-score-observations.py
scripts/repo-python -m unittest discover -s tests -p test_score_observations_audit.py
```

The first command deliberately returns comparison failure (182/191).
Diagnostic success does not override it. Private evidence is in
`build/frontier-score-minimum-20261102/`; `restored.json` and
`observations.json` describe the final source, while `corrected.json` and
`replays/` describe the rejected temporary minimum hypothesis.

## Direct vector endpoints, 2026-11-04

The source now expresses both iterator endpoints directly from the observed
vector member. It retains the real checked-container self-compatibility check,
without adding one by hand. Writing the same signed maximum predicate as
`observed_value > record->maximum_observed_14` preserves its meaning and
matches the native operand order. A fresh configured VC8 build and a second
separately compiled object each compare 191/191 against the native body, with
SHA-256 `3d19b4fc049aa452ca13b25eaf72163499f21c3beed18590ec71637249951d75`.

The independent Factory exactness replay could not be started for this
unregistered match; a request to register it before that replay was denied.
Therefore the function remains source-present and no exact credit is added.
The 182-byte result above is historical. Neither local comparison establishes
gameplay or broad exception behavior.
