# Number and connection shared cleanup members, 2026-11-02

Target is original Japanese v1.06a, SHA-256
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

CNumberLifetime.hpp now includes Tile.hpp and uses actual CTile at +0x28.
The payload-only CNumberTileLifetime and UiSpriteLifetime94 classes are removed.
MenuConnectLifetime.cpp uses actual CTile at +0x64/+0x300 and CSprite at
+0x1D4/+0x268. The existing shared IColor alias is retained. No storage extent,
member order, flag, ABI, manual vptr write or artificial dependency is added.
CNumberLifetime itself remains separate from the runtime CNumber class; no
claim is made that all owner methods or full-program linkage are unified.

Fresh before/after controls preserve CNumber normal destruction 40 bytes,
three color forwarders 11 bytes each, scalar cleanup 60, and DesignNumber
scalar cleanup 61. Full connection-menu destruction 0x443C30 remains 315 bytes,
SHA-256 0c109ea165c105dfe9c01a4768c4fa6c5a6f07d4880cc415107d849ce60225d2.
The 5-unit actual include closure preserves all 8 accepted roots in 4 units.
Nine other roots in four units keep their fresh HEAD hashes, including original
sequence library and implicit record cleanups. No support bytes are promoted.

## Cleanup evidence

The Connect destructor now also has a whole EH comparison: 168 bytes at
0x6B9450, including its full handler at 0x6B94DD, and 116 bytes of FuncInfo plus
ten-state unwind table reached by that handler. Every relocation is resolved
through an existing semantic binding or independently compared whole provider.
The deque cleanup at 0x40F8E0 is a complete 5-byte tail to 0x40FF90; the string
cleanup at 0x401E00 is a complete 38-byte body. Both match. CTile and CSprite
cleanup calls share physical address 0x40AD50, without a unique nominal-class
or exclusive ICF identity claim. EH metadata remains support, not authored credit.

Actual CTile RTTI (247 unique bytes) and all four slots pass in the CNumber
owner unit. The two scalar origins (121 bytes) and two implicit record origins
(23 bytes) pass scoped validation. The latter source pins now include Tile.hpp
and the reviewed CNumberLifetime.hpp hash. No exclusion decision changes.

Default CI passed 962 tests (90.973 seconds), tracking, generated progress and
whitespace. The client timed out while waiting, but the persisted exit marker is
zero and the full final log confirms completion; the gate was not rerun. Both diff
checks passed. No target or private evidence file is committed.

Counts remain 1427 exact / 443604 bytes; 1637 source-present, 1656 authored,
1826 mapped, 2074 excluded, 297 review, 813 units.
