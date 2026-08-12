# TH105 libogg recovery notes

This directory currently contains the unmodified official libogg v1.1.3
headers and license used to compile the libvorbis probes. The exact libogg
release and nontrivial code-generation profile are still unresolved; the
directory name records the current header candidate, not a completed island
claim.

IDA target semantics nevertheless prove that the formerly unclassified
`0x006A2FB0..0x006A3DD7` range is a separated libogg framing/bitwise island:
33 functions and 3,343 bytes from `ogg_page_version` through selected
`oggpack_*` readers, including the `_packetout` core and its packetout/peek
wrappers. The `ov_*` graph calls these functions directly. They are therefore
tracked as third-party/library rows even though none is yet strict exact.

