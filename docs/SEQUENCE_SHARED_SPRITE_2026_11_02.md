# Actual sequence-slot sprite and construction, 2026-11-02

Target SHA-256: 56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

FighterSequenceSlot now contains actual CSprite at +4 instead of the opaque
SpellSpriteWork storage. CoreContracts checks the real class and retains the
0x98 record size, field offsets and const enqueue parameter. The unused resource
method declaration is removed. The local prepare-record sprite and battle-info
render view likewise use actual CSprite, with ordinary scale fields and render
calls. Existing deque/controller layout views are unchanged.

Sequence enqueue now constructs the complete record in its allocated slot with
ordinary placement copy construction. It no longer assigns two fields and calls
a borrowed sprite-copy ABI through receiver casts. VC8 naturally preserves the
entire original 0x45DBA0 / 114-byte body, including its allocation/null branches.
The actual implicit CSprite copy emitted by this owner matches all 116 bytes at
0x455160. The existing compiler exclusion is not counted again. Its actual RTTI
graph covers 273 bytes and all nine virtual slots match the established table.
No manual vptr, instruction payload, fake local, exception annotation or forced
inlining barrier is introduced.

Actual include closure: 18 units. All 21 accepted roots in 14 units pass adopted
canonical comparisons. All eight other roots in seven units retain their fresh
before/after hashes. In particular prepare remains 257 / 259 bytes and the
pending sequence operations remain nonexact; this is not a new compiler-choice
trial. The directly affected display renderer remains 353-byte exact.
CoreContracts compiles, while wrong sprite offset and mutable enqueue parameter
controls are rejected. Compiler options and origin/ledger classifications do not
change; manifest call symbols now identify the real texture/copy providers.

Final CI passed all 962 tests in 125.660 seconds. Both diff checks gate the local
checkpoint. Totals remain 1426 exact / 443399 bytes, source 1636, authored 1655,
mapped 1826, excluded 2076, review 296 and units 813.
