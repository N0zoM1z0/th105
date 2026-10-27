# CSelect stage-selection update, 0x00420560

The first complete source is **890/890 canonical exact** under unchanged
VC8 SP1 O2/GS. The new unit is `exact-first-select-stage-update` and the source
is `src/ui/SelectStageUpdate.cpp`. No shared header or existing unit changes.

## Observed boundary and ownership

Canonical original Japanese1.06a SHA256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.
All265 instructions in the890-byte extent are reachable. RET0 exits are420628,
42064C,4208AF and4208D9; six following INT3 bytes isolate the next body.
There are no indirect branches or remote chunks. The one indirect call42056F
is the input object's virtual slot+4, with receiver at scene+18.
Whole-body SHA256:
bcb7798938595176b877ddc6e464c428f006c4934834588f912cb55a6faa1231.

Caller420A23 tail-jumps here from4208E0 after restoring its frame when state+8
is1. That caller is virtual slot+18 in CSelect, CSelectSV and CSelectCL tables:
pointers6C0BDC/6C04C4/6C051C; COLs6D78D0/6D6FD8/6D7178 have the respective
RTTI names. This is positive authored ownership, not an adjacency guess.
The function returns int3 or6 in EAX. Eight invalid-parameter calls arise from
native checked vectors; five RNG callsites remain independent and ordered.

Factory-native IDA metadata, entry68B9D2, matching mapped entry bytes
(e8ca9f0000e916feffff) and inventory401000/52 were rechecked before semantic use.
The direct launcher still lacks mcp/uv; it is not used as an attested session.
Name/prototype were updated and read back without modifying target bytes.

## Source facts and preserved behavior

The bounded owner view is never constructed, allocated or copied. Member access
constraints match the existing CSelect constructor hypothesis, but do not promote
that constructor or infer all unknown bytes. The setup view uses the separately
established32-byte player stride and signed stage/music bytes.

- Refresh virtual input first. Enable music-variant selection only when the
  selected extra entry is nonnegative, then update the stage cursor.
- A stage change resets the music cursor, starts10 transition ticks and updates
  both float positions by native double1.0 with the observed float rounding.
- Confirm preserves random-stage indication and resolves each character15
  using13 or15 RNG choices according to the existing locked byte.
- Fixed stage copies the selected stage and selected normal/extra music entry.
  Random stage chooses one index in1..choice_count-1, reads normal music first,
  and only makes the extra coin flip when an extra entry exists.
- If either character is6 and the stage is neither14 nor16, preserve the final
  independent RNG choice between those stages. Music is not recomputed after
  that forced stage change. Do not silently correct this shipped behavior.
- Confirm dispatches40, invokes runtime preparation with an ignored zero stack
  argument, fades music over1000 and returns6. Cancel dispatches41, resets state
  and clears the second selection flag before the first, then returns3.

The already accepted43AC60 cdecl provider does not read stack arguments and
returns unsigned. This caller's PUSH0 is preserved through a declaration-only
cdecl call view with an ignored integer argument; its unsigned return is
explicitly discarded. This does not alter the provider or assert a recovered
original prototype. No fake return, assembly or inert data dependency is used.

## Verification

The first full object is890/890 without source-shape trials. Reconciling signed
stage/music storage and the provider's unsigned return is byte-neutral and keeps
all890 bytes exact. Existing literal mapping for double1.0 is reused; no global
relocation mappings or existing accepted consumers are changed.

```
scripts/repo-python scripts/build.py --unit exact-first-select-stage-update --compare --json
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/check-match-literals.py --require-target
scripts/repo-python scripts/ci.py
```

Artifacts are retained under `build/frontier-420560-20261027/`: first/typed
objects and canonical previews, full target disassembly/CFG facts, formal-first
receipt, second focused comparison and final gate logs. Final CI is pending at
writing; its terminal log/exit determines acceptance for the checkpoint.
No new runtime matrix, actual input/gameplay execution or full cold replay is
performed. Totals retain unchanged prior receipts and are incremental. Unknown
nominal TU and original names do not weaken full-byte acceptance.
