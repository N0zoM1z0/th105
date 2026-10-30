# Exact palette dispatch and raw loading

PaletteDecodeMode::load_palette at408F70 is canonical exact163/163.
SHA-256: d91ecf6ba92724037da0360a7a42912377e75232a0a7756245091bcdbcbc779b.
PaletteDataView::load_raw_palette at419E80 is canonical exact243/243.
SHA-256: 76797ebe148db19487edd9f7f78a3548f50f985336e4f18457d01e49ebcbb125.
The new authored exact credit is406 bytes, bringing the incremental total to
1525 functions and432854 bytes. BMP palette conversion is not credited.

## Actual source contract

The dispatcher reads the receiver's mode byte, not an invented global flag.
It receives a path, an actual8-byte palette owner and the output-format byte.
Encoded mode rewrites the final extension to .pal and calls raw loading;
the other branch calls the BMP palette loader with the requested format.
PaletteDecodeMode is an inferred source name, not an original PDB claim.

The real caller naturally gives the raw loader its EDI receiver. No private
register declaration is used. Its call at408FCD is verified through a fresh,
complete exact replay of the public dispatcher in the same linked image.

Both native palette loaders release old storage through operator delete
at6898EA, not free at68AA26. The source now expresses the actual allocator
entry. Raw loading retains two typed paths:256 unsigned-short entries for
format16, and256 unsigned-int entries for format24/32, followed by the native
512/1024-byte reads. Invalid formats and the original pointer-reset policy
are unchanged; no defensive behavior is invented.

Raw loading also matches complete cleanup EH: handler6BDC68/27, cleanup
funclet6BDC60/8, FuncInfo6E42E0/36 and its unwind map. These are checked but
not separately added to the authored byte total.

## BMP palette conversion remains nonexact

The genuine reader/package graph recovers the native aligned448h frame.
The observed word-width masks are expressed as ~7, rather than byte-width
0xF8. The native explicit24/32 gate is retained. Ordinary one-entry loops
let VC8 generate the observed four-entry unrolling and recover the native
SIB operand choices; hand-expanded four-entry source did not.

The resulting source and native callable are both1047 bytes, but entry
receiver/format loads remain ordered differently. Signed-format and switch
validation controls did not close that difference and were not selected.
Two unreachable six-byte loop-alignment LEAs at offsets14A and2EA are also
outside the current strict linked CFG contract. No padding is ignored and
the verifier was not weakened to accept this body. Equal length is not exactness.

## Scope and verification

PaletteDataRuntime.cpp contains the actual palette implementation;
PaletteFileDispatch.cpp supplies the real caller context. The existing
file/CSV/script CIL graph includes both. The old unaccepted standalone palette
unit is replaced by these descriptors without duplicate credit.

All nine previously exact roots in the sole affected unit replay unchanged;
with the new dispatcher and raw loader,11 accepted roots were verified.
Local CI and whitespace checks pass. No cold full-corpus build or broad
runtime/test matrix was added.

Private receipts are under build/frontier-palette-reader-cil-20261030,
including public-wrapper.json, public-raw.json and accepted-final.json.

```bash
scripts/repo-python scripts/build.py --unit exact-first-csv-file-loading --json
scripts/repo-python scripts/compare-linked-unit.py exact-first-csv-file-loading --address 0x00408F70 --address 0x00419E80 --json
```
