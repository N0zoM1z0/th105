# PatGroup deque cleanup: resolved call-site provenance

461AF0/125 is now compiler-generated, with a full canonical125-byte witness
from the unchanged actual CharacterDestructor.cpp translation unit. It is not
an additional authored match and does not accept the Character destructor.

The fresh retained-object discovery examined716 ordinary COFF objects and10085
eligible function symbols. Two source symbols hit this reviewed address:
a nested CsvReader deque and the actual deque<PatGroup> cleanup. Retained
objects alone were not accepted. Fresh CharacterDestructor compilation emits
the complete real PatGroup specialization.

## Why the unqualified fingerprint was insufficient

All113 non-relocation bytes match, but ignoring three call fields gives two
native inventory hits: authored CsvReader_clear_rows40FDB0 and461AF0.
The CsvReader method is a real authored wrapper, still nonexact in its own
selected source context; it must not be reclassified or credited merely
because an emitted STL helper has the same instruction shape.

The actual PatGroup specialization has exactly three calls:
- source offset46: PatGroup::~PatGroup at461590.
- source offset88: operator delete at6898EA.
- source offset108: operator delete at6898EA.

PatGroup constructor and destructor are freshly canonical in their independent
lifetime unit, including the full128-byte destructor. Resolving every call
operand leaves only461AF0 across the full inventory. Independently rebinding
the fresh emitted COMDAT produces all125 canonical bytes with no differences:
05e84d6855ac248ecc7923c20036a167b525cbfe6ed2906cacbad672ac7896d4.
No data relocation, remote EH body or trailing bytes are present.

## Explicit repeated-site contract

The generated-origin validator already supported exact named REL32 targets
but required each symbol to occur once. The new optional rel32_site_counts
declares two sites for operator delete. Omitted counts still require one.
Counts must be positive integers for declared targets only; all source
relocation symbols, exact counts, non-overlapping fields and each native
destination are checked. Every site also participates in full-inventory
uniqueness. No ignored call, arbitrary mask, threshold change or first-hit
selection is introduced. Existing0.70/24/no-tail gates remain.

Six regression cases cover explicit repeats, unchanged default singleton
behavior, unknown/nonpositive counts, wrong repeated targets, omitted or
overlapping sites, and a count without a binding. All three existing origin
rules using named REL32 targets freshly pass: Character object-manager
adjustors, effect-manager adjustors and string count append.

## Preserved scope

Fresh Character destructor462CE0 remains905 bytes with its known single SIB
difference at+280; spell owner4619C0 stays exact101. PatGroup lifetime's two
accepted functions also remain exact. No game C++, header, profile or match-unit
contract changes.

Anchor:config/vc8-generated-pat-deque-tidy-origin-anchors.toml.
Rule:vc8-generated-pat-deque-tidy-106a.

Excluded1802/review418; authored1807/source1787/mapped1814/units766 and
exact1585/449721 authored bytes are unchanged. Default CI300 passes.
