# Reimu root: explicit probe bindings and unsigned conversion widths

## Target observations

Target is original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Parent `Reimu_dispatch_action_state_vslot28 @478FA0` remains81550 bytes,
SHA256 `dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
Candidate/origin/name/source selection remain authored,
unclassified/declaration-only. No implementation/exact credit changes.

The preceding void object has2449 relocation records:1167 external calls,
1098 numeric operands,14 addresses of local switch metadata,163 metadata
pointers into code and7 reads of6FA894. Its33 source call symbols refer to32
target callees; the two reviewed spawn declarations share465190's ABI.

Root disassembly independently identifies160 width/bit-pattern numeric values
in immutable `.rdata`, each at one address within this root. The earlier
candidate uses159 of these plus the qword2^32 anchor6D6ED0 already recorded for
Ogg conversions in reccmp-relocations.csv. Its9 qword-bias sites occur in
550/551,602,720,730 and740. Target counterparts use dword2^32 at6D6EF8.
The target also compares a sine result with dword zero at48A18A; the candidate
does not reference that zero literal. Address equality of numeric values is
not sufficient to establish the original root's literal placement.

## Source type recovery

`ReimuActionStateMid550Cases.hpp`, `ReimuActionStateHighEntryCases.hpp` and
`ReimuActionStateHighFinalCases.hpp` now explicitly pass the bounded unsigned
draw/remainder through float before the surrounding double arithmetic. This
is an inferred source-type hypothesis, supported by the emitted instructions;
original spelling remains unknown. Under pinned VC8 SP1/default FP, it changes
only9 raw `.text` opcode bytes, **DC->D8** (FADD qword->dword), plus the
corresponding relocation symbol/operand-width binding. Section size, instruction
positions, all other raw code/table bytes and frame allocation are unchanged.
No new rounding stores, dummy locals, assembly or padding appear. The explicit
casts occur in real calculations, with no fabricated helper result.

The previous and corrected operand constants both represent exact2^32. The
observed compiler output introduces no extra precision boundary; this is not
a portability claim about other compiler/FP environments. Source search shows
these fragments are included only by the main staging dispatcher. No accepted
source/header/layout/flag change or aggregate replay was needed.

Two isolated negative profile probes used the preceding source: SP1 with
`_CL_=/fp:fast` and VC8 RTM/default FP. Both keep all9 qword sites and frame598h.
Their prefixes are75604 and81140 versus baseline81128. Neither explains the
operand-width property, so no compiler/flag change is adopted. This does not
identify or exclude every possible original compiler/TU profile.

## Complete relocation audit, without acceptance

```bash
python3 scripts/probe-reimu-action-source-shape.py --void-root --output-dir build/reimu-root-relocations/expanded
python3 scripts/audit-reimu-root-relocations.py build/reimu-root-relocations/expanded/ReimuActionStateDispatch.obj
python3 scripts/audit-reimu-void-root.py build/reimu-root-relocations/expanded/ReimuActionStateDispatch.obj
```

`config/reimu-root-probe-bindings.toml` is explicitly probe-only. It records
exact mangled call aliases, the160 observed root numeric addresses, one
existing pool-only diagnostic anchor and the known global address. It does
not alter global or accepted-unit relocation mappings.

`audit-reimu-root-relocations.py` verifies the exact target/root hash and the
unchanged official table map. Calls must be genuine zero-addend E8 fields
whose destinations are both observed root calls and tracked candidates.
Numeric widths/bits must match their initialized COFF bytes and the immutable
target data; root addresses must equal independently recovered x87 reads.
The pool-only exception requires its existing canonical anchor. Global reads
require the known address mapping and actual root use. Local code operands
must select owned metadata; table pointers must select decoded code starts.

Every record is then replayed by the unchanged standard `coff_symbol_bytes`
and independently checked against its classified resolved value. Nothing is
masked or remapped to target label positions. All **2449** records resolve,
with the14/163 local-address directions kept separate. Source-only numeric
sites fall9->0; the corrected source uses159 root-observed numeric symbols.
The unused zero constant remains an explicit target/source-shape difference.

Two modified-binding controls are rejected: removing `__ftol2_sse`, and
mapping float2 to another aligned `.rdata` location with identical four bytes.
The latter demonstrates the distinction between value equality and observed
root placement. Four target-independent tests protect ledger scope, numeric
widths and disjoint root/pool ownership.

Complete relocation resolution is not full semantic ownership or an exact
result. The script writes no match unit or progress state. The candidate has
active code after its last physical RET; neither that RET nor the first table
alone proves a callable compiler boundary. Its strict replay still first
differs at478FA8, frame598h versus570h. Prefix81128/text82500,1167 E8s and148
RETs remain nonexact versus target81550/1188/153. All11 switches and126 primary
destinations remain. No percentage/partial-byte credit is inferred.

## Focused verification and next work

Current void object SHA256 is
`53833a15cd101721ae2223da0a1424dfd6de52784c4020375c6ad76c29da1be1`.
Native **0/1544** passes with unchanged input SHA256
`c61982a9ccc694e3b6667371b5a4882e896da92d11320dd4aa3784f464787b80`:
1010 integration,510 defaults,16 actual common returns and8 indeterminate-read
boundaries. Stops remain1246 real RETs,82 objects,30 effects,177 common entries,
1 set669 and8 pending. Returning world calls and arbitrary stack contents
remain unproved. Fresh compact bool build passes0/12 smoke and0/8 unknown
boundaries. The710/711/720 static loops and48 510 packets/12 level reloads pass.

Receipts, profile/control reports, opcode delta and strict replay are below
build/reimu-root-relocations/. Current inputs/compiler/objects are pinned;
all9 primary Ghidra DB hashes stay unchanged under the reused direct identity.
No new process/clone or IDA semantics. Rejected profile/initial cast products,
superseded objects/source copies and caches are cleaned; current artifacts
and small evidence records remain. Next address the source/compiler ordering,
remaining call sharing, exact callable ownership and returning-world evidence
before canonical acceptance of the whole root.
