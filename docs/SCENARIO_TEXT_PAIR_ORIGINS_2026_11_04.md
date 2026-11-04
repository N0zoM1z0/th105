# Scenario text-entry pair origins

For Japanese TH105 1.06a (SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`),
Scenario character installation `0x00456EB0` calls `0x00455DD0` and
`0x00455C50` at `0x00456FD0` and `0x00456FE2`. Their 114- and 115-byte
bodies implement the two standard-library pair constructions used to insert a
string-keyed `ScenarioTextEntryDC` value.

A small tracked witness builds the actual C++ standard-library pair types
with the pinned VC8 compiler. Each generated body has a relocation-masked
fingerprint with a unique hit in the complete current 4,027-candidate
inventory. The two native callable-body hashes and both call sites are pinned
by the origin rule. This establishes compiler-generated classification, not
full relocation or exception-metadata equality; no authored exact bytes are
awarded. The 598-byte character-installation caller now has a selected, nonexact
599-byte source candidate. Its original argument grouping and exception
context remain under review.

The same installation path calls `0x00456A30` at `0x00456FFF`. A separate
tracked witness instantiates the real checked `std::map<string,
ScenarioTextEntryDC>::insert` member; its 317-byte generated body also has a
unique relocation-masked hit across the current inventory. The native callable
hash and direct call are pinned. It is classified as compiler-generated, with
no authored exact or complete exception-metadata claim.

The insert member directly calls the internal tree `_Insert` at `0x00456550`.
The same witness independently regenerates that 523-byte COMDAT with a unique
relocation-masked inventory fingerprint. Its native body and call site are
pinned as compiler-generated evidence, without claiming complete EH equality.

The internal tree insert calls `_Buynode` at `0x004564A0`. The same witness
regenerates its 167-byte provisional body with a unique relocation-masked
fingerprint, including separately verified allocation, pair-construction,
free and exception-throw call destinations. The generated COMDAT has one
additional `CC` alignment byte, and the corresponding byte immediately after
the target candidate is also `CC`; neither is counted as an authored body.
The candidate's out-of-line throw path is retained in its body hash. This
classification does not claim complete exception metadata equivalence.

## Text-entry copy layout, 2026-11-04

The native `0x00455A80` entry copy constructs its sprite and string, then
copies four color bytes, seven integers and six state bytes individually. It
does not copy the trailing two alignment bytes. A scalar-field layout in the
shared `ScenarioTextEntryDC` preserves the 0xDC size and offsets and causes a
fresh pinned-VC8 implicit copy constructor to reproduce the complete 337-byte
native callable body after resolving the real sprite-copy and string-assign
calls. Its body SHA-256 is
`f69994866a9ed097e2dfff4b6e7a369942f46d869efadd6160c75058021d0a6b`.

The separate pinned witness has a unique full-inventory relocation-masked
fingerprint and the native pair constructors both call this body. It is an
implicit compiler-generated copy constructor and is excluded from authored
progress. The EH handler entry was resolved for the diagnostic body comparison;
complete exception metadata equality is not established. The layout is a
source hypothesis supported by the copy sequence, not proof of original field
names. Twenty-seven affected accepted Scenario roots replay exact; the current
character-install and render candidates retain their previous nonexact hashes.
