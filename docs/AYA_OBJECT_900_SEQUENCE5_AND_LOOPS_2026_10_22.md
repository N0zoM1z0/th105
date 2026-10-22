# AyaObject900 sequence5 owner reads and spawn loops, 2026-10-22

This continues the [owner-epoch checkpoint](AYA_OBJECT_900_OWNER_EPOCHS_2026_10_22.md)
on19522-byte update61A290. Target identity remains original Japanese1.06a,
SHA25656350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.
IDA preflight again rejects its current image; all observations below come
from the hash-attested PE and fresh native VC8 compilation.

## Selected source correction

Observed target sequence5 starts61DE75. It writes owner X at61DE81, reloads
owner at61DE87 for the Y write, and reloads again at61DF0E before publishing
WORD730=1 when time_counter144>=20. The source previously retained one owner
pointer through the whole sequence. Both reloads are now preserved using
current fighter_owner348 accesses. There is no shared ABI/header/flag change.

The complete candidate is20056 bytes, canonical SHA256
`8b221c5c7a61bf77a39370ad80c1a37f99db2c50e381cd35ad04e13073262545`.
Metadata starts19588 versus target19524. The configured19522-byte comparison
remains nonexact+0x22, target0F/source50, compared-window SHA256
`ff30b47a95c2a367cef523ef99365bae78f5d03a03a43523db0a94fa5cc190f3`.
Target traversal still closes4630 instructions/all19522 bytes; owner diagnostic
count remains3/34. No exact ledger or aggregate cold-replay claim is added.

Sequence5's147 bytes [61DE75,61DF08) and30 bytes [61DF0E,61DF2C) now each
occur uniquely and identically under translation in the candidate. The omitted
six-byte JL reaches the common animation tail, whose physical ownership differs.
The preceding92/38/90-byte sequence0 intervals remain unchanged and verified.

## Four complete spawn loops already agree

Fresh target [61D971,61DBC8),599 bytes, covers all four actual mode-specific
spawn loops, including loop-counter, payload and coordinate floating operations.
The candidate agrees throughout after independently decoding and replaying the
four CALL rel32 fields to their actual destination64CCB0. All other bytes must
match, including constant addresses, argument stores and internal branches.
The verifier locates a unique24-byte start, checks four real five-byte CALLs,
and compares the whole relocated interval. It does not mask arbitrary bytes.

This closes the proposed float-versus-double source-spelling lead for these
loops in the current compiler context: existing source already emits their
target operations. No precision edit was selected. This translated regional
comparison is not canonical whole-root equality or runtime callback proof.

## Execution scope

The reusable `scripts/audit-aya-object-900-retirement.py` now covers7960 complete
root-entry/RET executions: the previous4792 cases plus3168 sequence5 cases.
New cases combine two X values, eight masked x87 precision/rounding words,
facing+/-1, eleven velocity-X bit patterns, three velocity-Y patterns, and
counters20/21/INT_MAX. Velocity patterns include signed zero, subnormals,
clamp-boundary values, negative values, infinities, quiet and signaling NaNs.

All cases agree in final fixture memory, ordered writes, x87 status/tag,
callee-saved registers, stack cleanup and recorded owner-read epochs. The prior
checkpoint agrees in effects but differs in the3168 sequence5 read traces.
Those are read-lifetime differences, not3168 demonstrated gameplay failures.
Counter>=20 avoids the shared animation helper. No opaque helper is executed
or supplied a fabricated return; callback/lower-counter behavior remains outside
this execution proof. The previous20 artificial alias-stress cases retain their
explicit raw-memory, non-game-reachability qualification.

```bash
python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
python3 scripts/audit-aya-object-900-retirement.py
python3 scripts/audit-giant-action-owners.py aya-object-vslot28 \
  build/match-units/GptWeb_AyaObjectActionState.obj \
  --unit gpt-web-aya-object-vslot28-full-root --json
```

The comparator intentionally reports nonexact. Optional `--previous-object`
provides the scoped contrast. Reports are under
`build/aya-900-sequence5-20261022/`; private prior source is under
`.analysis/aya-900-sequence5-20261022/`. Local CI and whitespace gates apply.
Remaining leads are the common animation-tail placement, sequence0/4 scratch
homes, shared next-sequence exits and other action families; whole-root floating
exception/callback behavior remains unproven.
