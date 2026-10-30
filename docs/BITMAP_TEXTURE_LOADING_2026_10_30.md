# Bitmap texture fallback and pixel upload source

Current update: the real library-backed graph now makes DDS696 exact. Bitmap
parent1126/native1106 and upload remain nonexact. The old standalone probe was
consolidated into exact-first-csv-file-loading; see
DDS_TEXTURE_LINKED_EXACT_2026_10_30.md. The initial reports below are historical.

Complete source now covers bitmap/mipmap loader409080 and pixel upload41AE60.
Both remain nonexact: loader1161/native1106, upload1037-byte emitted envelope
versus native954 callable bytes plus87 bytes of table/alignment metadata.
There is no new exact credit. Existing1538 functions /435475 exact bytes remain.

## Target observations

The same fresh mapped-byte-attested Factory IDA session used for DDS supplied
provisional semantic output; raw PE independently establishes the final facts.
Loader1106 contains333 reachable instructions and no indirect jump table.
Upload954 contains313 instructions;311 are reachable. The two excluded CFG
operations are the native seven-byte LEA and one-byte NOP at41B0F8/41B0FF.
They remain within the compared callable extent and are not masked.

The upload switches at41AE8F and41B0CB use actual four-destination tables at
41B21C/41B248 and25-byte index maps at41B22C/41B258. Every destination is a
verified instruction boundary. The full payload ends at41B271, before15 INT3
bytes and the next independently bounded function41B280. The87 bytes after
the callable comprise82 table/index bytes plus5 alignment bytes. Metadata
cannot inflate authored exact credit; source table equality is not claimed.

TitleResourceManager load404C90 calls loader409080 at404CBC. The loader calls
DDS4094E0 at4090D8, then pixel upload41AE60 at40946D. Actual arguments fit normal
fastcall in both new entries: loader receives height output/path in ECX/EDX and
texture cell/width output on stack; uploader receives pitch/format in ECX/DL
and bitmap/destination on stack. Both pop8. Source uses these ordinary typed
four-input declarations, not custom-register wrappers. Caller ignores upload
EAX; source does not fabricate a bitmap-pointer return from its incidental EAX.

## Loader semantics

DDS is tried first. Only8876086C triggers bitmap fallback; any other HRESULT
returns unchanged. Three real CBitmapData objects own their buffers and array
construction/unwinding. No padded replacement bitmap object is introduced.
The source uses a friend declaration to access the existing exact32-byte class;
layout, virtual order and existing methods are unchanged.

The loader strips four path characters for the base stem, starts from the
configured base variant and searches downward. Variant0 uses the original
path, other variants use %s_%d.bmp. Encoded mode replaces the final four bytes
with .cv2 and calls load_from_file; ordinary mode calls load_bitmap. It can
load at most three mip images, and tries extra levels only if the requested
base variant was found. Global palette propagation, format reset, and dimension
outputs follow the target. The three261-byte path buffers are used path data,
not inert alignment storage; the observed260/261 strcpy_s bounds are preserved.

The backend square-capability policy is observed before format dispatch and
again within the actual creation helper. Format8/16 creates format25;24/32
creates21. Unsupported formats preserve the prior HRESULT. Every successful
level lock uploads using the lock pitch and that bitmap's format. The native
UnlockRect argument remains0 even for nonzero levels. This is recorded, not
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
16-bit uses DWORD pairs and width/stride shifted right1, preserving dropped odd
pixels.24/32-bit copies DWORD pixels. Destination pitch is divided by2 or4 as
observed, not substituted with image width. Unknown formats perform no copy.
No runtime guards or extra memory safety behavior absent from the target is
introduced. Original source spelling, nominal wrapper organization and full
exception-frame equivalence remain unknown.

## Validation and limits

The first complete loader compiled before tuning at1153 bytes. Explicit pointer
use for the real bitmap receiver gives1161 but retains nonexact virtual dispatch
and frame scheduling; same-size acceptance was never used. Upload's full source
build emits1037 including switch data, differing at its frame allocation. A
shared destination-pointer control is byte-neutral. Neither gets partial credit.
The actual DDS/creation source is included, not replaced by mock functions.

New unit exact-first-bitmap-texture-loading resolves every code/data relocation
and reports both whole bodies as mismatches, with no unresolved-binding failures.
Only CBitmapData's friend access changes a shared header. Both affected accepted
units were rebuilt: all16 previous exact functions remain exact. Other source
receipts are retained. No full-corpus rebuild or generic harness was added.

Raw proof, complete canonical reports and private controls are under
build/frontier-bitmap-texture-20261030 and the matching .analysis directory.
Semantic source evidence is retained with the DDS scope. Reproduce with
scripts/repo-python scripts/build.py --unit exact-first-bitmap-texture-loading
--compare --json; the expected nonzero exit reflects the documented mismatches.
