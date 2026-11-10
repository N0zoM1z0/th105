# Practice menu actual weather tile, 2026-11-02

Original Japanese v1.06a target SHA-256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

MenuPractice.hpp uses actual global CTile for weather_tile_0b8. The already
shared owner keeps its extent 0x288 and all other fields unchanged.
MenuOverlayWave.cpp calls that named member directly and removes the separate
CTileRenderView declaration and its offset-based receiver cast. The constructor
and renderer unit bindings now select actual CTile methods. No compiler flags,
FP environment, added barriers or synthetic vptr writes are involved.

Fresh before/after controls preserve the complete constructor at 0x446170:
826 bytes, SHA-256
d6b96b6857e92da2490a7c6b4817725bbeffd518dda38b66be8a7d0436cc0d18.
Render 0x445BA0 remains 211 bytes, SHA-256
dbfd82fb4b2400e2ba6a1fdc6f5bb3ba45e7a20e31d92be94c72e7bbaceb14b0.

The actual include closure is four units; all 11 accepted roots were rebuilt
and compared exact. Three emitted scalar wrappers in two units retain fresh
HEAD hashes and are not new authored credit. The existing Connect dispatch
section contains its switch data beyond the accepted RET boundary; no boundary
or accounting changed here.

The complete constructor unwind/handler region at 0x6B98D0 is 98 bytes, and
FuncInfo plus five-state unwind table at 0x6DF6C0 is 76 bytes. Both fully match,
including the actual CTile cleanup call to shared physical address 0x40AD50.
That shared address does not uniquely identify a nominal cleanup class.
Actual CTile four-slot table 0x6C0718 and 247 unique RTTI bytes also match.

Default CI passed all 962 tests (90.674 seconds), tracking, generated progress and
whitespace checks. Both diff checks passed. No target binary or private report is
committed.

Totals unchanged: 1427 exact / 443604 bytes, 1637 source-present, 1656 authored,
1826 mapped, 2074 excluded, 297 review and 813 units.
