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
`0xE50` instead. These facts identify the release but do not by themselves
promote all 151 libvorbis and vorbisfile rows to exact.

The decisive follow-up was the archived official `OggVorbis-win32sdk-1.0.1.zip`
(SHA-256
`fead50bbdf6a17e695b8b628f4ebe2c64a8f589ca6b983909484f4f361afbfcc`).
Its 2003 prebuilt `info.obj` and `vorbisfile.obj` reproduce the target's
nontrivial code generation exactly. The repository fetcher validates that
archive and extracts individual COFF members without committing the SDK
binary. Strict relocation replay now proves all 25 `vorbisfile.obj` functions
retained by TH105, plus four functions from `info.obj`: 29 functions and 8,858
bytes in total. This includes the 1,516-byte `ov_pcm_seek_page`, 860-byte
`ov_read`, and four verified floating-point DIR32 literals. The final call in
target `0x0066DD00` resolves to `ov_pcm_seek`, proving the function is
`ov_time_seek` rather than the otherwise byte-identical `ov_time_seek_page`
candidate. The next dependency wave completed every TH105 function selected
from `info.obj`, `block.obj`, and `synthesis.obj`. The accepted total is now 49
functions and 14,857 bytes, including the 1,615-byte
`vorbis_synthesis_blockin` and the 919-byte shared DSP initializer.

Reproduce the accepted bytes with:

```bash
python3 scripts/build.py --unit xiph-vorbis-info-anchors --compare --json
python3 scripts/build.py --unit xiph-vorbisfile-host-endian-anchor --compare --json
python3 scripts/build.py --unit xiph-sdk-vorbis-block --compare --json
python3 scripts/build.py --unit xiph-sdk-vorbis-synthesis --compare --json
```
