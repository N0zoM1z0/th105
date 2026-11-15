# Bitmap texture fallback and pixel upload source

Current update: the real library-backed graph now makes DDS 696 exact. Bitmap
parent 1126/native1106 and upload remain nonexact. The old standalone probe was
consolidated into exact-first-csv-file-loading; see
The initial reports below are historical.

Complete source now covers bitmap/mipmap loader 409080 and pixel upload 41AE60.
Both remain nonexact: loader 1161/native1106, upload 1037-byte emitted envelope
versus native 954 callable bytes plus 87 bytes of table/alignment metadata.
There is no new exact credit. Existing 1538 functions /435475 exact bytes remain.

## Target observations

The same fresh mapped-byte-attested Factory IDA session used for DDS supplied
provisional semantic output; raw PE independently establishes the final facts.
Loader 1106 contains 333 reachable instructions and no indirect jump table.
Upload 954 contains 313 instructions;311 are reachable. The two excluded CFG
operations are the native seven-byte LEA and one-byte NOP at 41B0F8/41B0FF.
They remain within the compared callable extent and are not masked.

The upload switches at 41AE8F and 41B0CB use actual four-destination tables at
41B21C/41B248 and 25-byte index maps at 41B22C/41B258. Every destination is a
verified instruction boundary. The full payload ends at 41B271, before 15 INT3
bytes and the next independently bounded function 41B280. The 87 bytes after
the callable comprise 82 table/index bytes plus 5 alignment bytes. Metadata
cannot inflate authored exact credit; source table equality is not claimed.

TitleResourceManager load 404C90 calls loader 409080 at 404CBC. The loader calls
DDS 4094E0 at 4090D8, then pixel upload 41AE60 at 40946D. Actual arguments fit normal
fastcall in both new entries: loader receives height output/path in ECX/EDX and
texture cell/width output on stack; uploader receives pitch/format in ECX/DL
and bitmap/destination on stack. Both pop 8. Source uses these ordinary typed
four-input declarations, not custom-register wrappers. Caller ignores upload
EAX; source does not fabricate a bitmap-pointer return from its incidental EAX.

## Loader semantics

DDS is tried first. Only 8876086C triggers bitmap fallback; any other HRESULT
returns unchanged. Three real CBitmapData objects own their buffers and array
construction/unwinding. No padded replacement bitmap object is introduced.
The source uses a friend declaration to access the existing exact 32-byte class;
layout, virtual order and existing methods are unchanged.

The loader strips four path characters for the base stem, starts from the
configured base variant and searches downward. Variant 0 uses the original
path, other variants use %s_%d.bmp. Encoded mode replaces the final four bytes
with .cv2 and calls load_from_file; ordinary mode calls load_bitmap. It can
load at most three mip images, and tries extra levels only if the requested
base variant was found. Global palette propagation, format reset, and dimension
outputs follow the target. The three 261-byte path buffers are used path data,
not inert alignment storage; the observed 260/261 strcpy_s bounds are preserved.

The backend square-capability policy is observed before format dispatch and
again within the actual creation helper. Format 8/16 creates format 25;24/32
creates 21. Unsupported formats preserve the prior HRESULT. Every successful
level lock uploads using the lock pitch and that bitmap's format. The native
UnlockRect argument remains 0 even for nonzero levels. This is recorded, not
silently corrected. Lock failure skips that level without replacing the creation
HRESULT. Array destruction runs on every return.

## Pixel semantics

Nonzero explicit_size selects run-length decoding. Eight-bit input uses byte
run lengths and palette-index colors;16-bit uses WORD runs/colors;24/32-bit
uses DWORD runs/colors. The indexed rollover assigns count=(run<count), which
is the observed unsigned comparison, rather than assuming zero-length runs
cannot occur. Other formats reset count to zero. Every arm avoids fetching a
new pair after the final pixel, and preserves live dimension/stride reads.

Uncompressed8-bit input expands palette colors to WORD output. Uncompressed
16-bit uses DWORD pairs and width/stride shifted right 1, preserving dropped odd
pixels.24/32-bit copies DWORD pixels. Destination pitch is divided by 2 or 4 as
observed, not substituted with image width. Unknown formats perform no copy.
No runtime guards or extra memory safety behavior absent from the target is
introduced. Original source spelling, nominal wrapper organization and full
exception-frame equivalence remain unknown.

## Validation and limits

The first complete loader compiled before tuning at 1153 bytes. Explicit pointer
use for the real bitmap receiver gives 1161 but retains nonexact virtual dispatch
and frame scheduling; same-size acceptance was never used. Upload's full source
build emits 1037 including switch data, differing at its frame allocation. A
shared destination-pointer control is byte-neutral. Neither gets partial credit.
The actual DDS/creation source is included, not replaced by mock functions.

New unit exact-first-bitmap-texture-loading resolves every code/data relocation
and reports both whole bodies as mismatches, with no unresolved-binding failures.
Only CBitmapData's friend access changes a shared header. Both affected accepted
units were rebuilt: all 16 previous exact functions remain exact. Other source
receipts are retained. No full-corpus rebuild or generic harness was added.

Raw proof, complete canonical reports and private controls are under
build/frontier-bitmap-texture-20261030 and the matching .analysis directory.
Semantic source evidence is retained with the DDS scope. Reproduce with
scripts/repo-python scripts/build.py --unit exact-first-bitmap-texture-loading
--compare --json; the expected nonzero exit reflects the documented mismatches.

## Pixel-cursor source control, 2026-11-09

The native RLE loops advance separate destination cursors at `0x41AF2A`,
`0x41AFE1` and `0x41B08D`, while retaining the X index for the final-pixel guard.
A private ordinary typed-cursor version preserves that structure and recovers
the native 0x10-byte local frame. It does not close the function: the complete
payload grows from 1,037 to 1,069 bytes against the native 1,041 bytes, with its
first mismatch at +13. Widening the two WORD-color locals to unsigned integers
is byte-neutral and does not explain the native DWORD spill slots.

Both the baseline and cursor version were compiled independently and through
the actual ScriptFileLoading/bitmap/reader/PNG LTCG context, with its unchanged
exports, compiler settings and pinned libraries. In each case, all 12 internal
absolute relocations and the complete payload replay identically between COFF
and linked PE. Thus this real caller context does not recover the remaining
cursor allocation and scheduling. No source change was retained; further work
needs new target evidence rather than increment-order or register controls.

Baseline payload SHA-256 is
`005a66826248ca973621b01a5fd5286a61e098b941210d6e73aba423a66e4d57`; the cursor
control is `140d7e87975aaaf2b7c289f843a2d1cc399dd6d0dc8d96fc00a7a2b4ec1c872e`.
