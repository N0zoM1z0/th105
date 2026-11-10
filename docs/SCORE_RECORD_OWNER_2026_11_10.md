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

## Story arrays: storage capacity is not the active roster size

`ScoreDataStoryProgressView` now declares twenty bytes in each event/primary/
secondary array, matching the existing defaults and persistence owner. The old
view split each into fifteen bytes plus five supposedly reserved bytes. Native
persistence `0x42D487..0x42D4DE` copies all five DWORDs from each of `+0x08`,
`+0x1C` and `+0x30`, including those last five bytes. Native initialization
and the established serialized schema corroborate the twenty-byte storage.

The policy loops still process fifteen characters, with thirteen initial
secondary unlocks. Those are observed policy bounds, not array cardinalities;
no unlock behavior or new event validation is introduced. The isolated source
layout change preserves complete COFF contents and relocations. Fresh
`gpt-web-score-story-progress` comparisons remain exact for both event
publication `0x42E750` (95 bytes) and refresh `0x42E3F0` (860 bytes).
Evidence and focused CI output: `build/frontier-score-story-arrays-20261110/`.

## Shared owned prefix and deck availability

The common `ScoreData` declaration now models the previously recovered prefix:
initialization byte, flags, three twenty-byte arrays, two unsigned sets, four
integer vectors, common count map, twenty character count maps, and twenty
record vectors. This carries the native constructor and persistence knowledge
into the actual accessor's type rather than leaving its first 0x198 bytes opaque.
Offsets +0x44, +0x9C, +0xA8 and +0x198 are compile-time checked. No new instance
or lifetime is introduced; the separate constructor/serialization definitions
remain unchanged.

Deck availability now accesses those maps directly, removing its duplicate
fifteen-map prefix. It still rereads the score accessor for each existing
operation, performs character-first/common-fallback lookup, and caps successful
counts at 99. Complete `0x448DF0` remains 358/358 exact. All fourteen affected
manifest units replay with their previous exact/nonexact outcomes. Twelve
complete section/relocation dumps are identical; deck availability and arcade
setup only reorder unchanged compiler support sections and their debug records.
Their full section-content and relocation multisets are identical, and each
selected root is independently compared rather than relying on that diagnostic.

Reports: `build/frontier-score-record-owner-20261110/full-prefix/`, compared
with `result-consumer/`. Focused CI and diff checks pass.
