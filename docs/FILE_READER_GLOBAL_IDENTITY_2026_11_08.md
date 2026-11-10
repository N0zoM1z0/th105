# Global file-reader identities

The canonical executable identifies `CFileReader` and `CPackageFileReader`
as global classes. Their RTTI strings are `.?AVCFileReader@@` and
`.?AVCPackageFileReader@@`; the package reader has the plain reader as its
single base at offset zero. The corresponding vtables are `0x006C0F34` and
`0x006D6E28`, with complete-object locators at `0x006DCDC0` and `0x006DCFF8`.

Both declarations and their implementations now use those global identities.
Using declarations in `th105` preserve existing caller source names without
creating different classes. The owner helper and file-handle typedefs retain
their existing namespace. Field widths, layouts, signatures and virtual slots
are unchanged.

## Complete RTTI and consumer comparisons

The emitted COFF now matches all twelve distinct records in the two RTTI
graphs, totaling 207 bytes. Comparison covers type names, complete-object
locators, hierarchy descriptors, base-class arrays, base descriptors and the
two vtable COL pointers, with every relocation resolved. The former namespace
mismatch is gone; no type-name field is masked or substituted.

Profile load `0x00431AC0` retains its previous 728-byte canonical candidate,
with only the two known differences at +540 and +543. Its 64-byte remote EH
code, 60-byte metadata, 21-byte reader cleanup and five complete reader method
bodies still compare equal. Global type identity was not the cause of that
remaining checked-deque load ordering.

The affected source/include and relocation closure contains 32 units. All 47
previously accepted roots in that closure replay exact, including the fourteen
CSV linked roots compared separately from the unit's nonexact members. Every
comparable candidate retains its prior canonical hash; existing blocked
comparisons remain blocked. No new authored exact function is recorded.

The narrow reader-vtable verifier now requires the same global type names for
source and target. Its 68 existing tests pass, including a new negative case
for the obsolete namespaced type. The source-pinned BGM list-growth, CSV
copy-helper and wave deque-back proofs also replay successfully after updating
only their two changed executable source inputs.

## Reproduction and remaining work

`check-profile-identity.py` verifies current object/compiler provenance before
comparing the complete profile/EH/reader/RTTI regions.

Further work on profile loading still needs evidence for the two deque operand
loads. The identity change does not justify another spelling or register
allocation search. Shared reader consumers remain source-consistent with the
recovered global classes.
