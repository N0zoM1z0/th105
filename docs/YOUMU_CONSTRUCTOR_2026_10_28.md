# Youmu constructor 0x0053B330

Canonical JP1.06a SHA-256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

## Independent member evidence

The older roster-constructor note correctly left Youmu separate because its
member at7D0 was then unresolved. The subsequently recovered history override
539B70 stores the actual44-byte YoumuObjectRecord at7A4 and pushes it into a
checked std::deque at7D0, limiting the history to60 frames. Existing source
YoumuHistoryVirtual.cpp and YoumuObjectRecords.hpp establish that member without
using the new constructor's match as type evidence.

Native53B330 calls Character462AB0, publishes the RTTI-owned Youmu table6C5144,
zero-constructs the deque's four owned state dwords7D4..7E0, and allocates the
0x68 YoumuObjectManager through53B0A0 before publishing it at658. The exception
handler6BC011 owns cleanup of the constructed deque; the448DE0 destructor
forwards to the existing checked-deque tidy420A80. The history record itself
remains uninitialized, as in the target. No manual vptr stores are used.

## Result

src/characters/YoumuConstructor.cpp uses the existing record type and ordinary
std::deque lifetime. The new isolated unit exact-first-youmu-constructor gives
159/159 zero-difference canonical bytes under the existing VC8 /O2 /GS profile.
The target boundary closes46 reachable instructions through RET4 at53B3CC;
there are no remote exits or unresolved indirect jumps. Both byte hashes are:
b62f24fc5c5b06c1cb9040a64f1dd80c6371305946ce87fd43918cc923fc9d83.

Receipts: build/frontier-53b330-20261028/mapped-build.json and boundary.json.
The new EH relocation is pinned to native6BC011 bytes8b542408. Existing history,
object-manager and roster constructor source/header/layouts are unchanged.
Only this authored constructor receives159 exact bytes; its STL/EH helpers
receive no additional authored credit. Physical unknown ranges are retained as
layout views, not claimed recovered member declarations.
