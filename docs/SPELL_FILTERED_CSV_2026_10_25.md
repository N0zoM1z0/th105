# Filtered spell CSV parser: complete source, two bytes pending

## 2026-10-26: independent exact-peer follow-up

After resource parser4343A0 independently passed its complete1646-byte
comparison and cold acceptance, filtered433B30 was re-attested and its public
baseline independently rebuilt. That full1987-byte baseline still had exactly
the four differences documented below. Wrong-target GUI IDA was again rejected;
the public raw-PE audit still reaches all478 instructions through4342F3.

One evidence-backed source trial reuses the representative's actual
`DwordDeque4::back_checked()` field view, including all callbacks and fresh
bound reads. It reduces the complete filtered comparison to **two unequal
bytes**, at433E24 and433E27. The canonical1987-byte candidate SHA is now
`b742d1af1789c8fa42305c3f4d69b2a4155d09329c3f43500e38f3b4da9d2060`.
The public unit reproduces that result with full relocation replay and no
extent/byte waiver. It remains identified/unselected, absent from
implemented.csv and matches.csv.

The operation-to-instruction relationship is not local: this back-access change
closes the short-deque operand bytes433C3C/433C3F, while the back operands
433E24/433E27 stay reversed. The source compiler's operand choice depends on
the surrounding expression graph. Do not describe this as an independently
matched back operation in the filtered caller.

One genuine joint-TU control includes both complete real parsers, with their
identical inline back operation and string-call view defined once. No synthetic
caller or dead storage is added. Full comparison of both roots produces the
identical1987-byte/two-byte-residual filtered body and the exact1646-byte
resource body. This closes the tested shared-visibility question without
inferring original TU ownership, source spelling, nominal types, exception-path
equivalence or an LTCG impossibility. The joint control remains private.

| Independent whole-body control | Complete bytes | Unequal bytes |
| --- | ---: | ---: |
| Fresh filtered baseline |1987 |4 |
| Proven checked-back view in filtered caller |1987 |2 |
| Same filtered caller with both real parsers in one TU |1987 |2 |
| Resource representative in that same joint TU |1646 |0 |

Receipts are under `build/exact-first-spell-filtered-peer-20261026/`:
`baseline-build.json`, `baseline-census.json`, `proven-back-census.json`,
`joint-filtered-census.json`, `joint-resource-census.json`, `formal-final.json`
and `formal-census.json`. Trial sources and the untouched starting source are
retained in the corresponding private analysis directory. No shared header,
existing accepted source, profile or relocation binding changed. The inline
member definition is identical to the representative's definition.

This finite peer/visibility lane is closed. Preserve the new public two-byte
checkpoint and switch to a fresh complete medium/large authored candidate.
Do not repeat operand-order, spelling, constness or flag controls without a new
independent fact. No exact function or authored exact byte is added here.

After the conservative manifest input changed, a fresh serial cold replay in
that directory's `cold-all.log` passed all525 accepted units/all1413 functions.
The accepted resource parser remains1646/1646 exact. Aggregate source-present
and exact counts are unchanged; this filtered candidate remains unselected.

## Initial 2026-10-25 checkpoint

Target: original Japanese TH10.5 1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Address **0x00433B30**, full callable **1987 bytes**, end exclusive4342F3.
Source: `src/battle/SpellCsvFilteredParser.cpp`.
Unit: `exact-first-spell-filtered-csv`.

The initial complete ordinary C++ candidate has the same1987-byte extent and **four
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

Initial checkpoint canonical SHA:
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

Current expected exits: target audit0; build/compare1 with `result=mismatch` at
+2F4; object census1 with `candidate_nonexact`, section1987, two unequal bytes.
The original checkpoint instead reported first+10C and four unequal bytes. The
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
At that checkpoint the next candidate was independent full parser4343A0. Its
later complete exact result supplies the new evidence described above; it was
accepted through its own preflight, full closure and whole-function comparison.
