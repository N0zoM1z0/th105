# Original checked-string matcher leaves

6A0AA0/12 (match_jump) and 6A0AF0/18 (match_toggle_case) are complete,
relocation-free, inventory-unique bodies from the unchanged original Boost
release instances.cpp context. Only these 30 third-party bytes are newly
classified. Authored exact remains unchanged.

The actual specialization is perl_matcher over VC8 checked std::string const
iterators, its matching sub_match allocator and the original w32 regex traits.
The separately emitted raw-pointer specialization has different offsets and is
not substituted. The source probe is pinned after LF/CRLF normalization; all
184 original headers and original instances.cpp remain verified. No original
source, compiler flags, TU boundary or export changes were made.

## Ownership independent of short byte fingerprints

The actual original source emits a 120-byte static s_match_vtable with 30
zero-addend DIR32 member pointers. Its complete symbolic order is checked.
Source slots 16 and 28 name precisely the two selected specializations.

Native readonly table 6D60C0 is located uniquely by two independently exact,
non-tiny members: slot 2 is match_literal at 6A1AE0 and slot 15 is match_set
at 6A24E0. Both complete source bodies are replayed independently. The native
slots 16/28 then point to 6A0AA0/6A0AF0. This is four-slot ownership evidence,
not a claim that all table entries or all 30 method bodies have been proved.

Each selected leaf has no relocation, call, exception metadata or unaccounted
control-flow bytes. Full COFF extent, native extent, closed CFG, SHA256 and
whole candidate-inventory uniqueness are required. No masking, prefix matching
or generic threshold relaxation is used. The existing generic minimum remains
unchanged; this typed gate is limited to these two original methods.

## Fresh validation and limits

The existing release-instance unit now contains 12 formal comparisons; all
pass. Its earlier compact-switch payload checks remain intact. The unchanged
public-search unit's five comparisons also pass, including the checked matcher
constructor 443B30/243 and destructor 443AA0/129. The retained eight-TU CIL
public-search root remains nonexact; no claim changes that negative result.

Eight focused tests reject wrong specialization, shortened or masked anchors,
changed sources/flags/context, altered formal bindings and unrelated tiny
stubs. All 36 real corruption controls fail: every byte of both leaves, four
selected table fields and each independent witness body. The full narrow
origin rule passes before the two review rows are reclassified.

Universal false-return or similar three/five-byte stubs remain unaccepted.
