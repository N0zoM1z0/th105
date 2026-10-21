# CDesignBase cleanup: complete 310-byte exact reconstruction

`CDesignBase_virtual_cleanup @0x0040BB40` is canonical **310/310 exact**,
SHA256 `5c8d5c4c66df8434fe8eeeb2277cac7a1960ce07de381c57e844b35bbc4502a3`.
The complete 119-instruction body includes its loop alignment and 40BC25 error
edge. Only this 310-byte game root receives new acceptance/byte credit.

Only original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. IDA rejects its wrong open image; new facts use the hash-attested PE
and real VC8 compilation. No database or target bytes are changed.

## Source and context

The recovered policy is unchanged: delete/pop objects from the list back,
release texture IDs in forward checked-vector order and clear the vector.
The map and persistent iterator stay untouched.

The native element is modeled as a four-byte `DesignTextureHandle` value,
with unsigned field at +0, ordinary value construction/conversion and implicit
copy/destruction. There is no custom copy loop or destructor. The vector
remains 16 bytes at +4; CDesignBase stays 34 bytes with all other offsets intact.
Complete equality and the affected lifetime consumers support this value
representation; unique original type/API spelling remains unknown.

`DesignBaseCleanup.cpp` uses native clear(). A genuine container reference
and explicit begin/end erase independently generate the same whole bytes.
Both remove a retained iterator self-compatibility check and naturally recover
loop alignment. The pinned vector header implements clear through erase;
its source lifetime still matters to code generation.

`DesignBaseCleanupLinked.cpp` includes actual cleanup and genuine C++ texture
lookup/release definitions, with the real native unsigned-list instantiation.
Explicit preservation of the two public member exports retains their normal
observed thiscall ABIs. Unique CIL ownership, native implementations and actual
exports are read back. These providers receive no new match or byte credit;
the existing 115-byte release acceptance is unchanged.

| Complete context | Bytes/instructions | Result |
| --- | --- | --- |
|Preceding ordinary unsigned vector|315|Nonexact frame and scalar memmove_s|
|Real provider CIL, unsigned vector|318/122|Aligned frame; scalar erase differs|
|CIL aggregate element, direct erase expression|315/121|Assignment loop; extra compatibility check|
|Aggregate with native clear or container reference|310/119|Whole body equal after named REL32 replay|
|Selected value/conversion class and clear|310/119|Strict configured canonical exact|

No compiler flag, assembly, padding, forced register, synthetic callee or
fabricated return is introduced. Original TU partition remains unknown.

## Qualified error exit

The linked comparator formerly rejected the mid-function E9 to 40C350.
`error_tails` now supports only the registered VC8 vector-out-of-range role,
its exact source symbol, target site and existing REL32 mapping. It requires:

- Pinned target 123-byte helper, 74-byte throw routine and 32-byte exception
  record; record flag 1 and original KERNEL32 RaiseException IAT identity.
- Complete straight-line helper decodes ending at the actual C++ throw call,
  without RET, branches, indirect calls or traps. Source map and IAT must
  identify the genuine pinned MSVCR80 `_CxxThrowException` import.
- One unexported CIL-owned source helper, its read-only vector-error message
  and actual second throw argument, with matching out_of_range/logic_error/
  exception types, PMDs and 40/40/12-byte layouts.
- One exact source E9 and the declared target E9; complete source/target caller
  CFG closure with every instruction owned, then normal full REL32 replay.

All 310 bytes, data references and relocation coverage still pass. Unqualified
exits and substituted edges, helpers, imports, metadata or provenance fail.
The source helper's 145 and target helper's 123 bytes are not matched or excluded;
40C350/68A153 stay in origin review with no credit. Their EH is outside the
caller, and the new contract does not authorize general noreturn/EH/literals.

`preserve_public_members` accepts normal public thiscall names only. It cannot
replace the actual comparison root, select private entries or create match
rows. Its source-owned exports/native hashes and the new validator module
participate in reproducible linked provenance.

## Verification

Sixteen configured header consumers and seven linked-validator consumers form
21 affected units. **All 59 predecessor accepted functions and the new cleanup
cold-build exact.** No unrelated unit or cold aggregate total is claimed.
The three loader empty virtuals stay exact; 40B000 still blocks on EH and
41B280 remains nonexact at +5.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-design-base-cleanup --compare --json
# 310/310 exact; validated_error_tails and preserved_public_members are recorded.
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Receipts are in `build/design-cleanup-context-20261021/`, including formal
builds, complete error witnesses, affected-scope and per-function replays.
Recipes and frozen predecessor inputs use the matching `.analysis/`/baseline
directories. Earlier manual 310-byte diagnostics motivated the new contract;
only the strict configured result supports matches.csv. Synthetic regression
tests reject returning/branching helpers, forged anchors/imports/throw
arguments/types, writable metadata, aliases and missing/nonnative exports.
