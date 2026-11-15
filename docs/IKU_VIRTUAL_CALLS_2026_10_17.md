# Iku action root: complete virtual-call ABI qualification

This follows the [unsigned conversion/native checkpoint](IKU_RANDOM_FLOAT_TYPES_2026_10_17.md)
for `Iku_dispatch_action_state_vslot28 @ 620920`. The complete 59038-byte root
remains identified without complete C++ source, a match unit or exact credit.

## Target observations and receiver inference

`scripts/audit-iku-virtual-calls.py` re-attests Japanese TH10.5 v1.06a SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`,
root SHA-256 `abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea`,
all 15132 instructions and three validated switches. RTTI identifies primary
vtable 6C652C, whose+28 entry is 620920. No root store changes the receiver vptr.

The opt-in receiver analysis records register CALL state before volatile
registers are killed. A join preserves a finite union only when every incoming
value is a known vslot; any unknown path invalidates the set. Under ordinary
x86 callee-save rules and a valid Iku primary receiver, all 177 register CALLs
retain entry ECX and resolve the following observed interfaces:

| Vslot | Target | Explicit argument / return | Sites |
| --- | --- | --- | ---: |
| +08 | 45BFE0, set action and finalize | short / int; purge 4 | 112 |
| +0C | 45C390, select sequence | int / int; purge 4 | 40 |
| +14 | 45C220, next sequence block | none / uchar; purge 0 | 19 |
| +1C | 45C180, set sequence frame | short / int; purge 4 | 5 |
| +08 or +0C | both targets above | one physical DWORD, discarded int | 1 |

The shared CALL621040 is the last row. Its lexical predecessor loads slot 08,
but 622C07 also arrives with slot 08, while 62513F and 6265D2 arrive through
62103E with slot 0C. Choosing the lexical target would lose real paths.
Branches directly to 621042 skip this CALL. A common local int/DWORD prototype
describes the mixed site's physical ABI; it does not replace either callee's
global short/int declaration. Future C++ must preserve virtual dispatch.

These target sets are receiver-domain inferences, not proof that the original
compiler emitted direct calls or that the inferred C++ spelling is unique.

## Compiler conversion entry

The existing excluded VC8 runtime island `[68A1A0,68A24B)` has SHA-256
`aeb7a87183a558dd228b968d6264bdeb993114992b7807d638c943a2adadd1a2`.
Its entry 68A1A0 consumes ST0 and returns 32-bit EAX with no stack arguments or
stack purge. The checked fast path uses `FSTP QWORD[ESP]`, then
`CVTTSD2SI EAX,QWORD[ESP]` at 68A1B5 and plain RET 68A1BB. It never writes EDX.
The shared x87 fallback also computes EDX, which cannot establish a64-bit
return for this entry. This is a custom compiler runtime ABI, not an ordinary
C++ helper declaration. Natural C++ conversion expressions remain the source
hypothesis. The island extent is not a newly proved standalone boundary.

## Saved analysis and validation

One direct Ghidra process at a time works on a clone and first independently attests
PE identity, entry 68B9D2, x86 Windows language/compiler, full mapped `.text` and
root bytes. It saves four virtual interfaces,177 call target sets and effective
callsite prototypes, plus custom conversion storage ST 0:10 to EAX:4. A fresh
read-only process verifies the actual references and override types, register/stack
storage, returns, purges and unchanged instructions; it also rechecks the prior 58
receiver components and 30 ordinary helper ABIs. Only the verified clone is
transferred after primary-project hashes are confirmed unchanged. Clone/backup files
are removed.

The 248621-byte decompiler hypothesis still reports the spacebase/jumptable
warning, the same 17 range-proved infeasible remainder corrections and global
overlap. Filling these ABI holes did not remove the stack warning. No
decompiler output is accepted as source.

Reproducible checks:

```bash
python3 scripts/audit-iku-virtual-calls.py > build/iku-virtual-calls.json
python3 -m unittest discover -s tests -p test_typed_indirect_tails.py
python3 scripts/audit-common-fighter-indirect-tails.py --json
python3 scripts/build.py --unit cross-v106a-animation-sequence-virtuals --compare --json
python3 scripts/build.py --unit cross-v106a-animation-sequence-finalize --compare --json
```

The focused dataflow tests pass 16/16, including finite/unknown joins and
volatile receiver invalidation. The existing common-root diagnostic retains
eight qualified tails across 16 domains. The two affected callee units pass
10/10 and 2/2 canonical matches. No shared C++ header, object selection, ABI
profile, relocation binding, source-present/exact ledger or aggregate replay
is changed or claimed.
