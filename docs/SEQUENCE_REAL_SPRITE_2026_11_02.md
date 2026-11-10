# Actual sprite in sequence rotation, 2026-11-02

Target SHA-256: 56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

FighterSequenceRotate.cpp now uses actual CSprite in its 0x98-byte card.
The duplicate SequenceRotateSpriteBase80 / SequenceRotateSprite94 hierarchy
and its CNumberLifetime include are removed. The existing genuine deque,
card lifetime and byte-width final count publication remain unchanged.

Serial before/after and adopted comparisons preserve the full authored rotation
0x45DDA0 / 265 bytes. The actual implicit CSprite copy 0x455160 / 116 bytes and
card cleanup 0x45CF50 / 8 bytes remain canonical. The existing compiler-origin
range-erase witness now emits actual CSprite assignment: all 143 assignment
bytes and 515 deque erase bytes remain exact. No new artificial caller is added.
The related accepted enqueue 0x45DBA0 / 114 bytes is freshly exact.

The copy and assignment anchor symbol names now identify actual CSprite.
The reviewed record-cleanup source hash is renewed. All three scoped origin
rules pass: copy 1 / 116, implicit records 2 / 23 and card lifetime 2 / 658.
Fingerprint thresholds, selected addresses and exclusions do not change.
The original complete parent EH regions remain 44 code + 44 metadata bytes;
together with the 8-byte cleanup they preserve the same 96 support bytes.
Actual sprite RTTI 273 bytes and all nine virtual slots pass from this real owner.
None of these compiler or metadata bytes confer authored credit.

Final CI passed all 962 tests in 127.255 seconds. Both diff checks gate the local
checkpoint. Counts remain 1426 exact / 443399 bytes, source 1636, authored 1655,
mapped 1826, excluded 2075, review 297 and units 813.
