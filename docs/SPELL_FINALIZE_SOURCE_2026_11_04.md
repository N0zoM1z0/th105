# Spell selection finalization

The original `432200` body clears the 32-byte selected-value table, walks the
loaded short IDs and looks up each record through `432D20`. For a non-null
record with selector byte 1 it stores the ID's low byte at the record's
unsigned short index. The complete 260-byte native body has one three-byte
internal alignment instruction at `43223D`; the exact spell loader `432360`
calls it at `43239C`. The body hash and exact owner edge are pinned by the
focused `spell-finalize-selection-authored-106a` origin rule.

`SpellDataFinalize.cpp` replaces the previous unselected hand-expanded checked
iterator hypothesis with ordinary pinned-VC8 `std::deque<short>::iterator`
operations against the existing 20-byte deque layout. The source does not add bounds
checks or guards absent from the native root. Both mutable and const iterator
controls emit a 226-byte candidate against the 260-byte native body; the first
difference is the frame reservation at entry. Native VC8 retains a self-container
check and additional iterator/stack lifetime that this standalone build optimizes
away. Neither candidate is exact, and no matching-byte or exception-path equivalence
is claimed.

Reproduce the whole-body comparison with `scripts/repo-python scripts/build.py
--unit exact-first-spell-finalize-natural --compare --json`; a mismatch is
expected. The native target and the targeted origin rule were checked. Exact
source spelling and original TU/LTCG context remain unknown.

Two follow-up controls retain identical canonical output: explicitly naming and
comparing the actual end iterator each iteration, and temporarily using a real
`std::deque<short>` member of the same checked size in the owner rather than its
existing layout view. Both still emit the same 226-byte candidate and entry
mismatch; temporary source/header changes were restored. These controls do not
establish the original nominal member type or a whole-program compiler context.

## Direct checked-deque expressions, 2026-11-04

Using the observed deque member directly at each iterator endpoint, instead of
naming a reference to it, preserves the real checked iterator operations and
reproduces the native 0x10-byte frame and its container-owner check. Fresh VC8
emits 255 bytes against the native 260 and first differs at +3 in register-save
ordering; the preceding 226-byte result is superseded. The two section hashes
are `12b243917656930f48ba64f54ec71b7eb59262029064fb84d403ace56400b346`
and `ea2b335f8b0495fd7bce7ebb28bbfd221c5f685b465510c9dc0a5bfcad7078ce`,
respectively. The retained code is ordinary C++ and does not add manual iterator
checks. This is not an exact match or a claim of exception equivalence.

## Local complete comparison, 2026-11-04

The direct checked-deque endpoints are retained. Clearing the byte array with
`std::memset` and promoting the first read ID to the lookup's `int` argument
are ordinary operations with the observed target semantics; the later iterator
read remains separate after the lookup. Two separately compiled VC8 objects
now compare 260/260, including the original three-byte alignment instruction.
Both resolved sections have SHA-256
`ea2b335f8b0495fd7bce7ebb28bbfd221c5f685b465510c9dc0a5bfcad7078ce`.
The previous 255-byte candidate is superseded.

Independent Factory acceptance remains pending. This source-present method
receives no exact credit until that replay is accepted; no live execution or
broad exception-equivalence claim is made. The exact caller at `0x00432360`
was rebuilt and remains exact.

## November 9: use the native deque member directly

The November 8 queue migration made `loaded_spell_ids_20` an actual
`std::deque<short>`. Finalization now calls that member's `begin()` and `end()`
directly, removing two obsolete reinterpret casts and the comparison with the
old layout facade. The iterator lifetime and lookup/read sequence are unchanged.

Fresh complete comparisons before and after this cleanup both reproduce all 260
bytes with the same canonical hash recorded above. The loader caller at `0x00432360`
also remains 71/71. These are local replay results; acceptance status and the exact
ledger are unchanged.
