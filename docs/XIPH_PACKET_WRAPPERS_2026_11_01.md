# Original Ogg packet wrappers

6B6800/21 (_ogg_stream_packetout) and 6B6950/21 (_ogg_stream_packetpeek) now
match the official SHA-pinned Ogg/Vorbis Win32 SDK 1.0.1 framing.obj. They pass
advance=1 and advance=0 respectively to the same actual __packetout provider
6B6820/302. Only the 42 new library code bytes are classified.

The archive SHA256 is
fead50bbdf6a17e695b8b628f4ebe2c64a8f589ca6b983909484f4f361afbfcc;
the extracted framing.obj SHA256 is
6ab66ea08a2e48f01c89e90b4d0b816b6774f267a4cdd08f34a499abf9a14026.
No source implementation, ABI facade or compiler workaround was introduced.
The formal prebuilt unit uses the existing extraction recipe as its provenance
input, not as replacement C++ source. The cached archive is verified before
extraction; no network retrieval is needed by the gate.

Both complete source sections are 32 bytes: actual 21-byte callable bodies
followed by 11 original NOP alignment bytes each. The provider section is
304 bytes: its full 302-byte callable and two NOP bytes. All 368 source/native
section bytes are canonically compared, not just a short prefix. CFG closure
is separately proved for each callable before padding, and every relocation
is the actual named REL32 provider call at +13. No padding gets function-byte
credit. The independently classified provider's original source symbol,
component, object, extent and ownership are checked and its full body replayed.

The advance argument, two incoming stack arguments, three outgoing argument
pushes, cleanup and RET all agree. Whole-callable inventory uniqueness is
checked after canonical relocation. The generic relocated-anchor 24-byte
minimum is unchanged; this narrow typed gate does not admit arbitrary short
wrappers.

Three formal SDK comparisons pass. Seven focused tests reject changed SDK,
member, symbol, provider, shortened/masked bodies and padding-as-code claims.
All 368 real byte-corruption controls fail, covering every byte of both full
wrapper sections and the provider section. The narrow origin rule passes
before the two review rows are reclassified. No authored credit is added.

Evidence: build/origin-anchors/xiph-packet-wrappers.json and
build/frontier-ogg-packet-wrappers-20261101/. Private scripts are under
.analysis/frontier-ogg-packet-wrappers-20261101/.
