# Complete original Xiph floor1 payload provenance

Two remaining audio-library candidates now have complete, zero-difference
original-SDK payload proofs. This supersedes the preceding note's statement
that 687790 and 688620 lacked full witnesses. No game function or authored
exact byte is added.

The fresh discovery enumerated every member of the original SDK libraries,
rather than relying on old build-object provenance files, which are no longer
present. Each body matched its original floor1.obj code in full; the strict old
fingerprint had stopped because the remaining bytes include owned switch data
and multi-byte alignment instructions. That old no-suffix gate stays unchanged.

## Full extents

- 687790 _floor1_look: 514 code bytes, all155 instructions reachable, then
  MOV EDI,EDI alignment2, four switch entries16 and twelve NOP bytes.
  All544 bytes are equal after legitimate source relocation.
  Code SHA256:85919581ac91b5a36a2224f6e61894159603923f65b62d4093b03779787330c8.
  Payload SHA256:39893aecd6a4ccaf2ac80cb110f0daa3dc1379048ecd8f9870ec05c8018af210.
- 688620 _floor1_encode: 1497 code bytes, all449 instructions reachable, then
  LEA ECX,[ECX] alignment3, four switch entries16 and four NOP bytes.
  All1520 bytes are equal after legitimate source relocation.
  Code SHA256:a610d2c613e46dec9162066110be51cd1238a255ed090b267cdc7426e06d20e6.
  Payload SHA256:a7c28e35115a6296b79c13df87a8d52c4d1fba75912fbff6f6c882d408a60121.

The re-extracted floor1.obj hash is
733287e303326152a0b10192f1d1a5105dc625d292d1683bc9bf135ca6240dcc.
The SDK pin remains fead50bbdf6a17e695b8b628f4ebe2c64a8f589ca6b983909484f4f361afbfcc.
The two exclusions count only2011 inventory code bytes, not table/alignment.

## Independent pointer and global ownership

The two look calls are the already named _calloc68D318 and _qsort68DD10.
Their current target identities, existing runtime-origin rows and definition
in freshly hash-checked original VC8 static archives are verified. This is
independent symbol provenance, not a new whole-byte proof of both CRT callees.

The qsort callback _icomp6879B0 has an independently replayed SDK anchor.
The absolute immediate argument additionally validates all21 original callback
bytes against its defined SDK section and target, not merely an address.

The encode calls use five independently replayed SDK anchors: _render_point,
_oggpack_write, _ilog, _vorbis_book_encode and _render_line0. Its original
static seq counter has four consistent absolute DWORD load/store fields,
all targeting6FD3A0. The original COFF literal check proves zero initialization;
the SHA-pinned PE places these four bytes in its non-executable writable
zero-fill tail. The ordinary origin reader intentionally cannot read raw bytes
there; a separate explicit virtual-section proof establishes the loaded zeros.
No arbitrary global binding or invented initialized file bytes are used.
LEA EDI,[EDI*8+50] is arithmetic, not an absolute memory read.

The narrowed validator admits only these fixed reviewed identities and data
roles, plus the original681C70 decoder. All link fields are owned, every
non-link byte is retained, no guard bypass is allowed, and all table entries
are instruction starts within their own body. Complete payloads are unique
in the current inventory. Neither coverage thresholds nor the old origin
validators were loosened.

## Validation

    taskset -c 0 nice -n 10 scripts/repo-python scripts/xiph_owned_switch_origins.py
    taskset -c 0 nice -n 10 scripts/repo-python scripts/xiph_owned_switch_origins.py xiph-sdk-floor-look-owned-switch-106a
    taskset -c 0 nice -n 10 scripts/repo-python scripts/xiph_owned_switch_origins.py xiph-sdk-floor-encode-owned-switch-106a

All three fresh proofs pass. Receipts are now in per-symbol directories under
build/origin-anchors/xiph-owned-switch: vorbis_book_decodev_add, floor1_look,
floor1_encode. Each proof.json records complete hashes, CFG counts, bindings,
owned tables, alignment and inventory uniqueness.

Twenty focused tests cover the original gate and the added exact alignment,
callback/counter instruction roles and writable zero-fill constraints.
Default CI now runs294 tests. No source or compiler/TU settings changed and
no broad native rebuild was performed.

Excluded1801/review420; authored1806/source1786/mapped1813/units765 and
exact1585/449721 authored bytes stay unchanged.
