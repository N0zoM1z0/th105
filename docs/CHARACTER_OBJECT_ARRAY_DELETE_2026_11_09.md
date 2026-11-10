# CharacterObject copied-word array lifetime

The shared CharacterObject destructor now uses `delete[] copied_words_340`
instead of `free`, with the standard `<new>` declaration visible to VC8.
The previous comparator binding made `_free` resolve to the native array-delete
entry and hid the incorrect source contract. No class layout or lifetime order
changes.

## Observed ownership

In all fourteen configured roster spawn functions, native array new at
`0x665B8A` returns the pointer stored in CharacterObject+0x340. The real source
allocates `new unsigned[copied_word_count]`. Normal destruction loads that
base pointer at `0x492EFF`, tests it, and passes it to array delete `0x68AA26`
at `0x492F12`, then clears the field. The secondary renderer at +0x338 still
uses scalar delete.

The original Japanese 1.06a target hash and named VC8 SP1 runtime entries were
verified in [the package ownership correction](PACKAGE_INDEX_ARRAY_DELETE_2026_11_09.md).
Array delete's eventual jump through scalar delete to CRT free does not justify
using the wrong interface in source.

## Focused verification

Only `cross-v106a-character-object-ctor` consumes the changed implementation.
Fresh before/after builds preserve all three whole-body canonical comparisons:
constructor `0x492F90` at 78/78, normal destructor `0x492ED0` at 145/145, and
compiler-generated scalar wrapper `0x492F70` at 30/30.

All 42 non-debug COFF sections, totaling 1,118 bytes, retain their full contents,
symbol identities and relocation roles apart from the proven free-to-array-delete
correction. This includes the unchanged destructor EH code and metadata. The
selected scalar-wrapper origin replay also passes with its current source provenance
and native RTTI owners. No new authored exact credit is added.
