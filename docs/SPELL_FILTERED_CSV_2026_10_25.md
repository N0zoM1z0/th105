# Filtered spell CSV parser: complete source, four bytes pending

Target: original Japanese TH10.5 1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Address **0x00433B30**, full callable **1987 bytes**, end exclusive4342F3.
Source: `src/battle/SpellCsvFilteredParser.cpp`.
Unit: `exact-first-spell-filtered-csv`.

The complete ordinary C++ candidate has the same1987-byte extent and **four
unequal bytes** after full canonical relocation replay. It is identified but
unselected, absent from implemented.csv and matches.csv. No exact credit is
added. The source file existed before this investigation and was initially an
unverified hypothesis.

## Target observations

`scripts/audit-spell-filtered-csv-target.py` verifies the executable identity,
complete body hash
`7d09cf25edce166f13585697b544749512d2c6d8b968c555a97d75d1cdb19cb8`,
478/478 reachable instructions, no escaping edges or indirect jumps, and the
single RET20 at4341C6. The else branch lies after that return and reaches
4342F3. Thirteen following INT3 bytes separate the next wrapper434300; their
object/linker ownership is not claimed.

The independently accepted148-byte wrapper434300 executes `mov ecx,esi` at
434371 immediately before its E8 at434373 to this parser. The body does not use
its incoming receiver, but the caller proves a member-call surface. The old
free/stdcall interpretation is not adopted. The audit checks this native edge.

The native policy loads CSV rows, uses a short-key set to filter selected spell
IDs, builds `data/card/%s/card%03d.bmp`, stores resource handles in the image
owner, inserts spell records, and creates a512x256 text composite every16
selected rows or at end of file. A postfix reverse iterator publishes the
composite handle into the last batch of destination records. These application
choices establish authored ownership separately from the STL helpers.

Exact instructions establish these corrections to retained source:

- CSV ownership initializes ten DWORD fields at+04..+28 before load; allocator
  byte/word storage at+00 and parser flags+2C/+2D are not blanket-zeroed.
  A local owning constructor preserves initialization and EH timing. Its base
  destructor supplies the single native clear40FDB0. Explicit additional clear
  was removed.
- The selected-ID set is a genuine VC8 `std::set<short>`. Its constructor sets
  ECX to the owning set before nil allocation432B10; its destructor erases the
  range and releases the allocated node through operator delete6898EA. The old
  free function omitted ECX, and `_free` binds to a different native thunk.
- Both texture operations use the existing TitleResourceManager API and
  receiver702798. The composite call404D00 pushes a hidden small-struct result
  pointer plus six explicit arguments, matching RET28. The retained
  SpellTexturePool declaration supplied only five stack words.
- Parsed rows initialize their two resource fields during construction, before
  reading columns. Real map insertion converts `pair<int,SpellRecordView>` to
  the const-key value type, producing two record copy calls432ED0 per arm and
  both80-byte temporary lifetimes. The old separate76-byte record copy was not
  the observed value construction.
- The reverse iterator captures its old base before increment, then decrements
  the saved base to dereference. The retained manual version captured after
  increment and therefore skipped the newest destination record.
- Row advancement stays in each owner/ownerless arm. The native ownerless
  advancement is in the remote tail; an extra common image-owner test is absent.
- String reset calls independent assign-bytes4021C0. A typed pointer-only call
  view preserves its real thiscall arguments and reference return. The complete
  owning string type remains VC8 std::string; no bytes or inert storage are used.

The old shared headers, compiler profile and existing helper/global bindings
are unchanged. Added relocation rows belong only to the new probe: its native
EH-handler prefix, two texture-output globals and card-path literal. New
standard-method aliases resolve the actual operations at their observed native
destinations; they do not create additional helper-origin or exact credit.

## Whole-function comparisons

Every trial was compiled serially on CPU0 with nice10, GS enabled and pinned
VC8. Each listed candidate was replayed over its complete COFF section without
masks. Historical trial counts compare the entire candidate-sized target
address range; an oversized candidate extends into following padding/wrapper
bytes. These counts are diagnostic only, with candidate extent reported
separately. Final comparison uses equal complete1987-byte bodies.

| Evidence-backed trial | Complete bytes | Unequal positions |
| --- | ---: | ---: |
| First complete retained source |1999 |1890 |
| Correct texture ABI |2003 |1895 |
| CSV initialization/single clear |2023 |1889 |
| Real selected-ID set |2010 |1871 |
| Real map values/reverse iterator |2063 |1872 |
| Real checked deques |2139 |1947 |
| Independent string assign boundary |2024 |1813 |
| Owning constructor timing |2024 |1766 |
| Signed batch counter |2032 |1710 |
| Separate owner/ownerless branch lifetimes |2023 |1713 |
| Direct image-owner uses and forward batch loop |1987 |4 |
| Const deque reads |1987 |4 |
| VC8 RTM control |1987 |4 |
| Explicit reloaded deque bounds, negative control |1987 |179 |
| Direct begin/end iterator expressions |1987 |4 |

The first complete source was built and compared before source corrections.
Its strict CLI first stopped at the unmapped EH handler; a subsequent complete
replay resolved the actual handler and native operands rather than masking
them. First canonical SHA:
`3c0e20668456427c2575f0009a83e0a0b4abd6c26ad7578f0e389d93881debc0`.

Final source canonical SHA:
`bf34bc86412914882ffc8f3ca3f480a2430f9820c88aa7de7a7888eb4d3c2f36`.
The public formal build and full difference census agree with the private trial.

| Native byte address | Target | Candidate |
| --- | --- | --- |
|00433C3C |10 |0C |
|00433C3F |0C |10 |
|00433E24 |0C |10 |
|00433E27 |10 |0C |

These are displacement bytes in two checked-deque upper-bound sums. Native
433C3A loads count+10 then adds head+0C; candidate reverses those reads. Native
433E22 loads head+0C then adds count+10; candidate reverses them. Both fields
are32-bit unsigned. This observation does not waive strict instruction equality
or establish exception-path equivalence. The zero-difference criterion remains.

RTM and SP1 deque headers compare identically, and both compiler controls emit
the identical canonical root. Const access and direct iterator expressions are
also byte-neutral. The explicit reloaded-bounds source is a rejected negative
control. This bounded operand-order lane is parked; do not repeat a compiler,
flag, constness or spelling grid without independent new evidence. Original
nominal source types, optimizer/TU context and exact source spelling remain
unknown. No LTCG impossibility claim follows.

## Reproduction and handoff

```bash
scripts/repo-python scripts/audit-spell-filtered-csv-target.py
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py \
  --unit exact-first-spell-filtered-csv --compare --json
scripts/repo-python scripts/audit-spell-filtered-csv-target.py \
  --object build/match-units/ExactFirst_SpellCsvFilteredParser.obj
```

Expected exits: target audit0; build/compare1 with `result=mismatch` at+10C;
object census1 with `candidate_nonexact`, section1987, four unequal bytes. The
census uses the public unit's exact aliases and replays every relocation across
the full section; it is a diagnostic, not an alternative acceptance procedure.

Receipts: `build/exact-first-spell-filtered-csv-20261025/target-audit.json`,
`formal-final.json`, `formal-census.json` and the final local CI log.
First source, each trial source/object, all full replay JSON/bin files and
negative controls remain under the matching private analysis/build directories.
Generated outputs and compiler binaries are not committed.

IDA preflight rejected the wrong GUI executable. All accepted observations here
come from the hash-attested raw PE; no IDA patches, Ghidra sessions or concurrent
compiler processes were used. Available RAM stayed above10GiB, swap use119MiB.
No broad behavioral matrix is justified by the four known operand differences.
After these ledger additions, a fresh serial cold replay passed all524 accepted
units/all1412 functions. Receipt: the same build directory's `cold-all.log`.
Next bounded candidate is the independent full parser4343A0, starting with fresh
preflight and its own first whole-function comparison. Nothing about that peer
is inferred as exact from this root.
