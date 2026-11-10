# Score record array ownership

The statistics and sequence-result methods now index an actual member array,
`ScoreData::records_198`, instead of casting storage beyond a prefix-only
`ScoreData` declaration to a vector pointer. The array contains twenty checked
vectors of 24-byte observed records. No selector guard or constructor is added.

## Original executable evidence

In the canonical JP1.06a constructor `0x43E1A0`, instructions
`0x43E29C..0x43E2B6` pass the vector destructor `0x435F90`, constructor
`0x4460D0`, count 20, stride 16 and address `this+0x198` to the native array
construction helper. Defaults, loading and persistence independently use the
same twenty ranges. The earlier prefix-only declaration predated this lifetime
recovery. The remaining unknown prefix remains opaque; the declaration does
not assert that the original nominal class has no further members.

## Complete affected comparisons

Fresh builds before and after the change reproduce all 191 bytes of statistics
`0x42D010` and all 159 bytes of sequence recording `0x42CF70`. Historical notes
that reported 182/191 and 142/159 describe an older compiler/input state, not
these fresh builds. This change preserves the current exact bodies rather than
fixing those historical residuals. No accepted ledger or Factory receipt changes.

All fourteen manifest units whose transitive source dependencies include
`ScoreData.hpp` were rebuilt and compared serially. Thirteen retain identical
complete COFF section contents and relocations, covering the two record roots,
fighter callers, menu/result consumers, music and result lists, and arcade
setup. Existing mismatches in five other roots are unchanged. The score getter
remains exact at six bytes with the same global relocation. Its new vector
header inclusion also emits the ordinary SDK `bad allocation` literal, its
static pointer relocation, and the C++ runtime default-library directive; no
new executable code or initialization section is emitted.

Evidence is under `build/frontier-score-record-owner-20261110/{before,after}/`:
all fourteen full comparison reports and complete section/relocation dumps.
The small serial driver is `.analysis/frontier-score-record-owner-20261110/build.py`.
Focused CI passed. These are local exact comparisons, not new Factory acceptance.
