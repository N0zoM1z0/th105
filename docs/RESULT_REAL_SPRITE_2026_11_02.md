# Actual result-menu portrait sprite, 2026-11-02

Target: original Japanese v1.06a, SHA-256
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

ResultMenu.hpp changes character_sprite_008 from the manual-vptr UiSprite94
facade to actual global CSprite. Existing portrait render, texture and color
calls now use the actual nine-slot interface. No source expression, field size,
compiler flag, callback preservation or runtime branch was changed.

All four accepted roots in three units freshly remain exact, including the
270-byte renderer, 256-byte normal destructor and 43-byte update guard. The
actual include closure is five units. The constructor remains 495 versus native
502 bytes, first mismatch at +45. Its full candidate hash changes from
6a32046f885a24cb656952a42cff95297b1367634c801e2d4c9273f0c6c18fa7 to
97390578d694d2859f2d48dde56dba3ebbc77917990acdf721357f612bb2ec93.

A full candidate-to-candidate comparison shows only six byte positions change:
the sprite handle-zero store now precedes the EH state-zero store. That order
agrees with the native constructor sequence. Earlier register selection and
instruction offsets still differ; this is not a new exact prefix/body claim.
No register, scratch-word or global-value lifetime constraint was introduced.
The other four nonaccepted roots retain fresh HEAD hashes: two implicit list
cleanups, the scalar wrapper and the pending 342-byte portrait refresh.

Actual sprite RTTI (273 bytes including standalone IColor COL) and all nine
slots pass. Full constructor and destructor EH are 115 code bytes plus 84
metadata bytes each, totaling 398 support bytes. The native vector cleanup at
0x435F90 matches its complete 42-byte source body. The existing independently
qualified ResultList callback at 0x447260 remains its observed destination;
this does not claim that all TUs emit the same helper body or link unchanged.
Generic implicit-lifetime validation passes all 17 roots / 1434 bytes after
refreshing only the reviewed ResultMenu.hpp source hash. No classification or
support bytes are promoted to authored exactness.

The baseline report explicitly records the known constructor change; other
comparisons are unchanged. Final CI passed 962 tests (131.404 seconds), tracking,
generated progress and whitespace. After the client timeout, the persisted exit
marker and terminal log confirmed success without a repeat run. Both working-tree
and staged diff checks passed.

Totals remain 1427 exact / 443604 bytes, 1637 source-present, 1656 authored,
1826 mapped, 2074 excluded, 297 review and 813 units.
