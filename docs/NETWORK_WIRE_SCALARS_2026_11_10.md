# Network packet scalar storage

REQUEST_REPLAY, INPUT and ACK_INFO place multi-byte values inside byte buffers
without guaranteeing scalar alignment. REQUEST_REPLAY and INPUT put their
32-bit sequence value at wire offset 1; INPUT's short payload begins at offset
7. The selected serializers and scalar field reads now use fixed-size memcpy
rather than dereferencing integer pointers into those byte buffers. The
little-endian VC8 target representation and all count checks remain unchanged.

ACK_INFO parsing also now constructs an actual short before appending it to
the real short deque. Previously it read an unsigned word into an int and
reinterpreted that int as a short reference. Native `0x44E0F0..0x44E0FE` still
matches: VC8 emits the same zero-extending word load, four-byte stack store and
push-back call for the real short local. That stack store does not require an
int object or an incompatible reference in the reconstructed C++.

Three affected units were rebuilt with their unchanged pinned profiles. All
15 configured roots remain locally canonical exact, including ACK_INFO
serialization292/parsing183, INPUT serialization104/parsing78 and the
REQUEST_REPLAY serialization27/parsing19 pair. All 527 non-debug sections and
885 relocation records are identical to fresh pre-change objects, including
EH support and the separately configured GS-off request pump. No shared header,
relocation mapping, accepted-byte ledger or pending input pin changed.

INPUT parsing still passes its incoming short pointer directly to push_back.
A temporary-copy control removed that alignment dependency but expanded the
root from 78 to 89 bytes, first mismatch +48. It was not retained. This source
boundary therefore remains unresolved; the other packet changes do not imply
that every packet access is alignment-independent.

These are local comparisons preserving existing matches, not new Factory acceptance.
