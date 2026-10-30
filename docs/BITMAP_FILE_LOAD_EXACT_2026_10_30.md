# Exact raw bitmap file load

CBitmapData::load_from_file at 0041ACA0 is canonical exact448/448.
SHA-256: ab414e694b37039ffea85b2288ca7406c65df74387c102e79488c9263b215dc5.
Complete cleanup EH also matches: handler6BDBD8/27, funclet6BDBD0/8,
FuncInfo6E425C/36 and unwind map6E4254/8. Only448 authored function bytes
enter matches.csv. The incremental checkpoint is1523 exact/432448 bytes.

## Source and context

The existing ordinary C++ loader body is unchanged. It reads the one-byte
format and four header words, releases any old allocation, selects explicit
size or the native format/stride/height allocation, reads the payload and
destroys its owned reader. Real complete reader/package/CRC CIL context
recovers the target frame and scheduling without source-level byte shaping.

The actual CBitmapData/CBitmapSourceView declarations move to CBitmapData.hpp.
CBitmapFileLoad.cpp owns the shared loader definition. The original bitmap
runtime includes this definition so its other selected comparisons retain
their source context; the file/CSV/script graph also includes it. Class layout,
virtual order and the loader's source semantics do not change. No duplicate
authored or EH credit is assigned.

The strict full-cleanup verifier now admits an unrenamed exported public
virtual thiscall member as well as a public nonvirtual member. Both require
the actual static CRT cookie and the same complete handler/funclet/FuncInfo/
unwind replay. No new waiver, alias or private ABI is introduced. The existing
focused contract test now covers the public virtual spelling.

## Focused result and remaining boundaries

The five previously exact bitmap siblings and eight previously exact roots in
the shared file unit all replay exact. With the new loader,14 accepted
functions were checked across the two changed units. CI and whitespace gates
pass; unrelated native units were not rebuilt.

The complete BMP-only experiment now links every real reader/package provider
without unresolved symbols. It remains2197 bytes including metadata and a438h
frame, not exact against the native2230-byte callable plus45-byte metadata.
Read forwarding at its actual read sites does not close that residual.
The PNG loader also remains nonexact; neither receives partial credit.

Private receipts are under build/frontier-bitmap-reader-cil-20261030:
public-compare.json, the two affected-unit JSON files and ci.log.
The selected root stays in exact-first-csv-file-loading.

```bash
scripts/repo-python scripts/build.py --unit exact-first-csv-file-loading --json
scripts/repo-python scripts/compare-linked-unit.py exact-first-csv-file-loading --address 0x0041ACA0 --json
```
