# TH105 libogg recovery notes

This directory contains the unmodified official libogg v1.1.3 source/header
candidate used to document the recovered translation-unit shapes. The exact
SDK source revision remains unresolved; the directory name is not a claim that
the archived SDK was built from this tag.

IDA target semantics nevertheless prove that the formerly unclassified
`0x006A2FB0..0x006A3DD7` range is a separated libogg framing/bitwise island:
33 functions and 3,343 bytes from `ogg_page_version` through selected
`oggpack_*` readers, including the `_packetout` core and its packetout/peek
wrappers. The `ov_*` graph calls these functions directly. They are therefore
tracked as third-party/library rows independently of exact-match status.

The archived official Ogg/Vorbis Win32 SDK 1.0.1 supplies the actual prebuilt
`framing.obj` and `bitwise.obj` code-generation profile used by the target.
Strict relocation replay now proves all 33 linked libogg functions and all
3,343 function bytes exact. This includes the CRC and bit-mask DIR32 tables,
the `OggS` literal, CRT/helper REL32 calls, and internal framing calls.
Reproduce the complete island with:

```bash
python3 scripts/build.py --unit xiph-sdk-ogg-framing-relocation-free --compare --json
python3 scripts/build.py --unit xiph-sdk-ogg-bitwise-relocation-free --compare --json
```

The vendored v1.1.3 sources remain source-shape/header candidates. Exact status
comes from the SHA-256-pinned SDK COFF objects, not from assuming those source
files are the SDK's exact libogg revision.
