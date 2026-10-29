# Encoded file-buffer cursor

Later same-day result: both file loaders are now exact234/267 with full cleanup
EH; see FILE_BUFFER_LOADING_EXACT_2026_10_29.md. The initial checkpoint and
controls below remain historical evidence.

Raw hash-attested Japanese1.06a code at419950 has a complete267-byte body,
through RET4 at419A58. Its decoder loads data_00 once at419A12, walks that
pointer at419A2A, and rereads size_04 for the loop bound at419A2D. The byte key
starts at8B, delta at71, and each iteration adds delta to key and95 to delta.

FileBufferEncodedRuntime.cpp now uses that real advancing payload cursor.
The previous data_00[index] expression allowed a fresh base-pointer read on
each iteration. This is a source memory-access correction, not an artificial
liveness change. The source keeps the actual unsigned owner-size bound and
unsigned-byte arithmetic. Allocation, terminal NUL, reader call, and native
CRT free remain unchanged.

The full fresh ordinary-COFF candidate is272 bytes versus native267, replacing
the previous275-byte candidate. Canonical replay still first differs at+0E:
source reserves one scratch DWORD, target two. Native also receives the owner
privately in ESI and retains the successful reader for unconditional cleanup;
the source keeps an ordinary member interface and actual FileReaderOwner RAII.
No ABI annotation, fake local, extra null guard or padding is added. There is
no new exact credit, and a shorter candidate is not acceptance.

The manifest formerly called wrappers408DB0/408E40 exact. That statement was
not backed by accepted units: both are still unclassified inventory entries.
Their raw140-byte bodies do establish the .cv0/.cv1 path-rewrite calls and
private receiver flow, but not a source match. The wording is corrected.

Focused command:

    scripts/repo-python scripts/build.py --unit gpt-web-file-buffer-encoded-runtime --compare --json

Receipt: build/frontier-file-buffer-context-20261029/formal.json. Target267
SHA2564586170018493a7ba134017243b15bd26f9eaa6265e014fafc6e9f289962b5f7.
The reported source hash43225b71c928e4ebf9145a0fcd052e4fdf08cda9b7c417cbdeec71d17249f2f9
covers the compared267-byte prefix, not the complete272-byte source body.
Only this source unit changed; existing exact receipts are unaffected.
