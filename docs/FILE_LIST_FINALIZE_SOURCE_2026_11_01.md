# Complete FileList page finalization source

## Authored ownership and complete source

Original CFileList vtable6C15E0 slot8 points to43A590. Its primary COL6D7F98
and type descriptor6E656C name CFileList. Replay/Profile/Music/Result lists share
this same virtual body, not five distinct functions. All1106 bytes decode into
283 instructions ending in RET43A9E1. Complete target SHA256:
42c261d42ffb94ac18d1674da6993f8078f3555c4a12bec872c015b8ab9c8342.

FileListFinalize.cpp restores the complete policy: configure the real194-byte
font owner, release previous texture handles and clear tile storage, iterate
rows through virtual formatting, accumulate at most16 rows per page, append
line breaks, use maximum formatted width*7+4, create a256-high text texture,
append its handle, build a typed CTile with a16-row texture region, push a copy
into the render deque and reset the page string. Actual string/owner/tile
lifetimes remain normal C++. Narrow out-of-line push/assign declarations retain
the existing native member ABIs; no replacement STL algorithm is authored.

## New color ownership evidence and remaining boundary

The corrected shared Color4/CSpriteBase-owned texture now emits the entire
implicit CTile copy4396A0/164 from this real page owner, with SHA256:
6268fa650b0889102e2b98655a7ab27b9f228bee117669a2e1e8e61123cd1c66.
Both RTTI vtable relocations are resolved. This strengthens the existing
compiler-only copy proof; it does not add authored or new exclusion credit.
No artificial copy-only wrapper or explicit noexcept copy declaration is used
in this new source. The old copy unit remains separately reproducible.

The entire page root emits1155 versus native1106, first mismatch+16 at frame
allocation: source3A0 versus native398. Iterator/EH lifetime scheduling remains
unresolved. This is a complete nonexact source checkpoint, not a partial-byte
match. Earlier1080-size private candidates used different copy visibility;
that historical number is not the current implicit-owner result. No old source
spelling grid or artificial compiler barrier was reopened.

The actual root's handler6B8B91 has a16-byte address-ownership binding only;
full remote EH equality is not claimed. All normal named calls and data
relocations resolve in the formal comparison, whose failure is a genuine byte
mismatch, not a missing symbol or unsupported relocation.

## Validation and accounting

Unit exact-first-file-list-finalize formally reports nonexact1155/1106.
The existing cross-v106a-cfile-list unit freshly reproduces all14 configured
bodies, including its already-excluded deleting wrapper. Shared headers and
prior source are unchanged. Native RTTI/full-body/call witnesses pass the
new authored-origin rule.

Source1631, authored1651, mapped1816, review407, excluded1969, units770.
Exact authored remains1428 /443902 bytes. No prefix/copy double credit.

Receipts: build/frontier-file-list-color4-20261101/formal.json,
native.json, copy-canonical.json and file-list-peers.json. Raw native bytes
were reattested; older retained decompilation was not used as new authority.
No whole-corpus rebuild or push.
