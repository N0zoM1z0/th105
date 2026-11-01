# Original Xiph table getters with complete data dependencies

Two original SDK getters now compare completely:

-684CF0/12: __vorbis_window_get from vorbis/window.obj.
-689820/12: vorbis_invsq2explook from vorbis/lsp.obj.

Each entire source/native16-byte code section matches, including four original
NOP alignment bytes. CFG closure and whole-callable inventory uniqueness are
checked independently. Only24 library code bytes are newly classified; no
padding or data bytes are credited as code or authored progress.

## Entire data sections, not partial array fingerprints

The window object's complete32672-byte initialized .data section matches
native6EF17C. All eight DIR32 table fields at source offsets32640..32668 point
to their actual same-section window-array symbols, with source offsets and
zero addends checked. Every nonpointer byte is identical too. The getter's
_vwin symbol is at source offset32640 and resolves to native6F70FC.

The lsp object's entire1176-byte initialized .data section matches native
6F75D4 without relocations. This includes all original lookup arrays, not just
the one returned value. INVSQ2EXP_LOOKUP is at source offset648/native6F785C;
the code's real +128 addend selects6F78DC. Its relocation literal witness is
therefore the bytes at the resolved address, not the different first element
at the symbol base. Full-section proof separately covers both.

These are writable, readable, non-executable initialized data sections in both
source and target. They are not claimed to be readonly or BSS. All float values
are compared bit-for-bit; no decimal conversion or approximate comparison is
used. Comparing the entire section avoids treating a symbol-to-section-end
tail as one incorrectly sized array.

## Original objects and validation

Official SDK archive SHA256:
fead50bbdf6a17e695b8b628f4ebe2c64a8f589ca6b983909484f4f361afbfcc.
window.obj SHA256:
b1906845039a193d3d0c7d1190e10aae87e159adf9bdbcf0eb60c98d1f2b6bab.
lsp.obj SHA256:
c89a27b23e2ea6e4fb3128912ba8e3cc4005207eef90342da07fa784dc2069ec.
The corresponding vorbisfile archive copies are hash-identical and receive
no duplicate credit. Two focused original-SDK units provide formal replay.

Ten tests protect original source/member/profile, whole extents, pointer versus
float identity, correct bindings and initialized writable storage. All94 real
corruption controls fail: every code/padding byte, all window pointer bytes,
all array boundaries and the selected float-table element. Full33848-byte data
comparison remains mandatory regardless of these selected mutation controls.
Generic short-function thresholds are unchanged.

Evidence: build/origin-anchors/xiph-table-getters.json and
build/frontier-sdk-table-leaves-20261101/. Private scripts are under
.analysis/frontier-sdk-table-leaves-20261101/.
