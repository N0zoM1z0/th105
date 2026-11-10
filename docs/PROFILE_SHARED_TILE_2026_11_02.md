# Shared actual profile tile, 2026-11-02

Target SHA-256: 56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

ProfileUiInfrastructure.hpp now declares the shared global g_profile_tile as
actual CTile. The render-only ProfileTileView and the separate MenuEnd
UiTileA4 global alias are removed. Both the profile renderer and result-menu
initializer use the same declaration. The canonical global at 0x6E6A88 starts
with the established CTile vptr 0x6C0718. The existing relocation allowlist key
is retained as evidence; consumer symbols now name the actual CTile type.
This is an external declaration, not a new global allocation or initializer.

Actual include closure: seven units. All 21 accepted roots in six units remain
exact in serial before/after and adopted replays, including profile tile renderer
0x43FB60 / 142 bytes and MenuEnd initializer 0x4404F0 / 512 bytes. The pending
profile-deck renderer remains 2521 bytes with its unchanged candidate hash.
Only source symbol names for the existing 0x4099F0 render and 0x4098B0 texture
providers change; their destination addresses and all caller hashes are unchanged.
No compiler flags, lifetime implementation, storage size or ledger changes.

Final CI passed all 962 tests in 111.630 seconds. Both diff checks gate the local
checkpoint. Counts remain 1426 exact / 443399 bytes, source 1636, authored 1655,
mapped 1826, excluded 2075, review 297 and units 813.
