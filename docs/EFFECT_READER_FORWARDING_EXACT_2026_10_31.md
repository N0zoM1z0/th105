# Effect resource loader: complete exact replay

Target: original Japanese TH105 v1.06a, pinned executable SHA-256
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

## Accepted result

The complete authored EffectResourceManagerView::load_effect_resource at
0x00437EC0 now compares exact over all 2528 bytes. Target and relocated source
SHA-256 are e0d31abb77468f60189ea2e9473f5896f0a08155057d03d81e74bfc40ce94566.
The previously reconciled 794-instruction boundary, real RET4, path handling,
group ownership, alias resolution and frame payload parsing are unchanged.

The remaining 79 differing byte positions were resolved by reusing the existing
ordinary read_file_buffer helper from the accepted file-buffer loaders. The
helper captures destination and length as real call arguments before dispatching
CFileReader::read; it naturally inlines. All 27 effect-loader reads use this same
helper. No forced inlining, private-register declaration, inert local, assembly,
handwritten byte sequence or fabricated helper target was added.

FileReaderOperations.hpp now owns that unchanged helper; CsvFileLoading.cpp and
EffectResourceLoading.cpp include it. This is an exact-backed source reconstruction,
not a claim to know the original helper's spelling or header location. The actual
shared FrameData layout and lifetime recovered in preceding work remain necessary
source context.

## Verification and scope

Public manifest unit: exact-first-effect-resources.

Fresh public canonical replay passed the new 2528-byte function and all 15
previously accepted functions in the two other actual changed-source consumers:
13 in exact-first-csv-file-loading and two in exact-first-bgm-stream-runtime.
Linked comparisons retain their ordinary private-call and complete EH checks.
No unrelated cold rebuild or whole-origin-census claim is made.

Private and public receipts:
build/frontier-reader-forwarding-20261031/*-public.json.
The authored match ledger gains one whole function and 2528 bytes:
1556 functions / 444236 bytes. No helper or compiler-library credit is added.
The old source-only origin rule is replaced by canonical-exact-authored.

## Separate, still unaccepted PAT control

Applying the same existing helper privately to all 60 PAT-loader reads reduces
the complete 0x00461B70 candidate from 3898 to the native 3885 bytes.
It remains nonexact, first difference +866 at0x00461ED2, canonical source SHA
9e978b66bcfec49e27e802dc9ac4285608a43ba327ab15822a99afde07b38baa.
This control is not published or counted. Equal length is not acceptance.
