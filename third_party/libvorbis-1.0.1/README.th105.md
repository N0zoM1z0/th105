# TH105 libvorbis v1.0.1 recovery notes

This directory contains the selected unmodified official libvorbis v1.0.1
source/header set needed by current and next-wave TH105 Xiph match units. The upstream tag
resolves to commit `b63c4d7189f861d51e4e22ff76ff8711753179b9`; `COPYING` is retained beside
the source.

The target initially had three strict exact anchors from a local VC8 compile:

- `0x0066E290` `host_is_big_endian` (3 bytes);
- `0x0066E2A0` `vorbis_comment_init` (18 bytes);
- `0x0066E330` `vorbis_info_blocksize` (23 bytes).

The release candidate is supported by two stronger non-name fingerprints.
The target `ov_time_seek` at `0x0066DD00` uses the old reverse link scan found
in v1.0.1 and rejected by the changed v1.2.0 implementation. The adjacent
`vorbis_info_init` at `0x0066E350` allocates a `0xE80`-byte
`codec_setup_info`; the official v1.1.0 through v1.2.3 candidates allocate
`0xE50` instead. Nontrivial bodies still have compiler-configuration or
source-shape deltas, so these facts do not yet promote all 151 libvorbis and
vorbisfile rows to exact.

The decisive follow-up was the archived official `OggVorbis-win32sdk-1.0.1.zip`
(SHA-256
`fead50bbdf6a17e695b8b628f4ebe2c64a8f589ca6b983909484f4f361afbfcc`).
Its 2003 prebuilt `info.obj` and `vorbisfile.obj` reproduce the target's
nontrivial code generation exactly. The repository fetcher validates that
archive and extracts individual COFF members without committing the SDK
binary. This raised the first accepted SDK wave to six exact libvorbis/file
functions, including 96-byte `vorbis_comment_clear`, 38-byte
`vorbis_info_init`, and 58-byte `ov_info`.

Reproduce the accepted bytes with:

```bash
python3 scripts/build.py --unit xiph-vorbis-info-anchors --compare --json
python3 scripts/build.py --unit xiph-vorbisfile-host-endian-anchor --compare --json
```
