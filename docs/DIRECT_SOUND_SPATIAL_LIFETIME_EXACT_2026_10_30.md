# Exact DirectSound spatial-buffer destruction

Normal derived destructor4180F0 is canonical exact139/139, SHA-256
8f3d9a872923a79faa1ee3516b93ac370d61e5059a09ca603fc948400ae3a08a.
The incremental ledger is1529 exact functions /433988 authored bytes.
The historical139-byte COFF candidate differed at+2F; equal size alone was not
acceptance. The unchanged ordinary C++ body now closes that scheduling
boundary in the real shared allocation/lifetime CIL graph.

## Source and complete ownership

DirectSoundResourceLifetime remains a0x10-byte derived object with spatial
interface+C and buffer+4, over the0x0C-byte base. Its destructor releases and
zeros the spatial interface, releases and zeros the buffer, then performs the
ordinary base destructor. The target's repeated base release check and vptr
publication are retained. No body, zero-store ordering, field type, register,
inline directive or stack-storage change was needed.

The private trial and public unit both use src/audio/BgmStreamAllocation.cpp,
which includes the real DirectSoundResourceLifetime.cpp and actual buffer
creation provider. Existing pinned CRT/Xiph and standard-list context stays
unchanged. The normal destructor is exported under its real source symbol.

The derived target table6D6D20 is verified as the complete two-slot table:
initialize418180 and deleting destructor4180D0. Primary RTTI independently
names .?AVCDS3DBuffer@@ through COL6DCF1C and type descriptor6FA65C. The base
CDSBuffer table6D6D44 is independently checked too. Source methods, RTTI,
relocations, table extents and identities all remain mandatory.

Full cleanup replay includes handler6BD658/27 bytes, funclet6BD650/8 bytes,
FuncInfo6E3C30/36 bytes and unwind map6E3C28/8 bytes. The entire function,
all cleanup regions and all rebased metadata compare without a byte waiver.
No metadata, table, library or previously accepted body is counted again.

## Focused verification

The descriptor moves from the mixed COFF resource unit to the existing
exact-first-bgm-stream-lifetime linked unit. The source file and seven accepted
COFF peer bodies are unchanged; their recent focused receipts remain valid.
Only the changed linked context is freshly built. Both the new spatial139 and
existing stream220 destructor, with all of its three cleanup states, remain
canonical exact in that image.

    scripts/repo-python scripts/build.py --unit exact-first-bgm-stream-lifetime --json
    scripts/repo-python scripts/compare-linked-unit.py exact-first-bgm-stream-lifetime --address 0x00402880 --address 0x004180F0 --json

Receipts: build/frontier-spatial-buffer-lifetime-20261030/public-build.json
and public-compare.json. Target-independent CI passes142 tests; no all-unit
cold rebuild or end-to-end audio claim is made.
