# Spell card/resource CSV parser: complete 1646-byte exact representative

Target: original Japanese TH10.5 1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Address **0x004343A0**, complete callable/COFF section **1646 bytes**, end
exclusive434A0E. Two independent public builds reproduce every byte with all
relocations replayed. Canonical SHA-256:
`9227f8e00a66490d13ffc3ad8f992f0b6c997913acf9beeca2f128eb3a0f14fc`.

Source: `src/battle/SpellCardParser.cpp`.
Unit: `exact-first-spell-resource-csv`.
Mapping: `SpellDataOwner_parse_spell_csv_and_build_card_resources`.
The function is selected in implemented.csv and accepted in matches.csv.

## Independent target closure

`scripts/audit-spell-resource-csv-target.py` verifies executable identity, full
body hash,374 complete instructions and373 reached instructions. The sole
unreachable instruction is the six-byte alignment operation at43445A,
`8d9b00000000`. The single RET16 is at4348F2; an ownerless branch after that
return continues through434A0E. Two following INT3 bytes separate wrapper434A10.
No indirect jump or escaping edge is accepted. One indirect call at43452F uses
the native wsprintfA IAT cell6C01D8.

The independently accepted161-byte wrapper434A10 sets ECX from ESI immediately
before E8 at434A91 to this body. This verifies the unused-this member surface
independently of filtered parser433B30. The body does not consume its incoming
receiver; no free/stdcall facade replaces the member declaration.

The observed policy reads spell CSV rows, creates per-card BMP resources,
appends names separated by `<br>`, inserts spell records, and creates512x256
text textures in batches of16 rows or at end of input. Each inserted row stores
its16-pixel batch offset. A postfix reverse iterator publishes each composite
handle into the last batch of destination records. These game-specific choices
establish authored ownership separately from the STL providers.

## First complete comparison and evidence-backed changes

The retained complete source was compiled and compared before corrections. Its
first strict comparison stopped at the unmapped native EH handler. After that
handler and actual call/data operands were resolved, complete section replay
reported1986 bytes and1861 unequal positions. First canonical candidate SHA:
`bd158859020adf2dba3418aa2d154b532b874f3b1dc91054ed41c871ce255f77`.

Each subsequent trial addressed target instructions or a demonstrated ABI or
lifetime error. Jobs were serial, CPU0/nice10, with unchanged VC8 SP1/O2/GS.
No profile, toolchain header or shared game header was modified.

| Trial | Complete bytes | Unequal positions |
| --- | ---: | ---: |
| Retained first complete source |1986 |1861 |
| Correct existing Title texture API |2000 |1855 |
| Owning CSV constructor/single cleanup |2005 |1844 |
| Actual map value-conversion expression |1841 |1699 |
| Row constructor and missing batch offset |1855 |1721 |
| Actual postfix reverse iterator/signed loop |1868 |1601 |
| Actual checked unsigned deque access |1889 |1615 |
| Independent string-assign boundary |1756 |754 |
| Common row cleanup instead of early continue |1646 |2 |
| Checked-back field view with live bound reloads |1646 |0 |

Historical unequal counts compare the whole candidate-sized target address
range, including following bytes when a candidate is oversized. They are
diagnostic only. Final acceptance compares equal complete1646-byte sections.

Independent target observations supporting the corrections:

- CSV fields+04..+28 are ten zeroed DWORDs before load40F150. Allocator storage
  at+00 and parser flags+2C/+2D are not blanket-zeroed. A local owning constructor
  reproduces the actual initialization/EH timing; the base destructor supplies
  the single clear40FDB0. The retained extra explicit clear was removed.
- Native texture receiver702798 is the existing TitleResourceManager.
  load_texture404C90 takes two output-state pointers. create_text_texture404D00
  consumes a hidden small-object result pointer plus six explicit arguments,
  matching RET28. The retained five-word composite declaration was incorrect.
- Both resource fields are initialized when the row is constructed, before
  reading its columns. Native434644 writes `16 * batch_count` to record+48
  before increment and map insertion; retained source omitted that assignment.
- Real `map<int,SpellRecordView>::insert(pair<int,SpellRecordView>(key,parsed))`
  creates an80-byte temporary and const-key conversion temporary, calling the
  record copy provider432ED0 twice per arm. Both temporary records are destroyed
  before advance_row40F680. The retained named76-byte record copy and named map
  value extended these lifetimes across row advancement.
- The native reverse loop saves the old iterator base, increments the reverse
  iterator, then decrements the saved base to dereference. `(current++)->second`
  reproduces it; the retained manual sequence skipped the newest record.
- The string reset invokes independent assign-bytes4021C0. A typed pointer-only
  reference-returning call view preserves that real API boundary while actual
  owning strings remain VC8 std::string.
- Native row cleanup is shared after the optional batch action. Expressing the
  condition as `if (batch_count == 16 || !has_next_row)` reproduces that merge.
  The retained early continue duplicated cleanup paths and added110 bytes after
  the preceding fixes.

## Final two bytes: actual bound reads, preserved checks

The complete genuine-deque candidate already matched1644 of1646 bytes, but its
load/add displacement bytes at43458F and434592 were10/0C instead of0C/10.
Both are part of the upper bound of checked back dereference. This difference
was not waived as commutative arithmetic.

The existing `DwordDeque4::back_checked()` source-facing interface now expresses
the observed operations directly: capture end, validate it, decrement, validate
against freshly read head/count, compute the block/slot, validate dereference
against fresh bounds, wrap the block once, then load through the current map.
All three failure call sites in this access remain; the full root retains all
five invalid-parameter calls including reverse-iterator checks.

This preserves behavior if an installed invalid-parameter callback returns and
changes container state: later bounds are reread. The old retained definition
cached bounds across those callbacks. The explicit field view naturally emits
the two native operand bytes and leaves every other root byte unchanged. It
uses ordinary C++ fields/arithmetic and the existing member declaration, with
no new iterator representation, assembly, copied bytes, inert storage, padding,
fake return or changed calling convention. This establishes a sufficient source
view, not the original nominal spelling or TU boundary.

The record/map/deque representations remain provisional nominal views pinned
by the existing shared declarations and observed ABI. No shared header or
existing accepted binding changed. The only new data relocation row is the
native16-byte GS/EH-handler prefix at6B8358 for this unit. Existing data rows
already qualify the card path, texture outputs, composite config, manager,
empty string and separator. No helper-origin or extra library exact credit is
introduced.

## Reproduction and handoff

```bash
scripts/repo-python scripts/audit-spell-resource-csv-target.py
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py \
  --unit exact-first-spell-resource-csv --compare --json
scripts/repo-python scripts/audit-spell-resource-csv-target.py \
  --object build/match-units/ExactFirst_SpellCardParser.obj
```

All three commands return0. The object census reports `candidate_exact`,
section1646, zero size difference and zero unequal bytes, using the public
unit's aliases and complete canonical relocation replay. It is a diagnostic;
formal acceptance remains the normal build/comparator plus tracking gates.

Receipts under `build/exact-first-spell-resource-csv-20261025/`:
`first-compare.json`, `first-replay.json`, `formal-first.json`,
`formal-second.json`, `target-audit.json` and `formal-census.json`. Independent
first/second public builds both report complete1646/1646 exact; the first object
is retained separately. Private first source and every trial source/object/full
replay are preserved under the matching .analysis/build directories. No
generated report, compiler, executable or database is committed.

Wrong-target GUI IDA was rejected by fresh preflight. Observations came from
the hash-attested raw PE; no target patching or Ghidra process was used.
Available memory stayed above10GiB and swap use119MiB during focused builds.
No broad behavioral matrix was needed to resolve the concrete mismatches.

The fresh serial cold replay in `cold-all.log` passes all525 accepted units and
all1413 functions, including an independent rebuild of this complete1646-byte
root. The authored exact total is382816 bytes. Prior accepted source, shared
headers, compiler profiles and bindings remain intact.

Filtered peer433B30 still has its own unselected1987-byte/four-byte-residual
checkpoint. This representative's success supplies new evidence for its checked
back access, but does not accept that peer. Next work should independently
replay the peer with that one operation and audit any remaining difference;
the short-ID selection loop and nil-tree ownership are separate questions.
