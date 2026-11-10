# Two complete implicit record cleanups

Two previously proved support bodies are now formally classified as compiler-
generated: SequenceRotateCard destructor45CF50/8 and InfoRecord154Lifecycle
destructor46E950/15. Both actual source records declare no destructor. Their
ordinary member lifetimes generate the complete cleanup bodies; no source
implementation, assembly, byte payload or hand-written vptr stores are added.

The source remains the real FighterSequenceRotate.cpp and
InfoManagerBaseLifetime.cpp owner TUs. The first record contains one94-byte
sprite at+4. The second contains sprites at+4 and+98. Their known nontrivial
color-base lifetimes account for all emitted stores and RETs. The source-local
CNumberColorLifetime view maps only its independently identified native IColor
vtable. These local view names do not claim the original record type spelling.

The rotation's real implicit copy and complete parent/EH ownership were already
established by FIGHTER_SEQUENCE_ROTATE_EXACT_2026_10_31.md. The info manager's
actual constructor/destructor array callbacks and record-member layout were
established by INFO_RECORD_LIFETIME_2026_11_01.md. This checkpoint does not
recount those parent, copy, constructor, metadata or support bytes.

Both new formal selections use the existing strict implicit-lifetime gate:
reviewed source/header hashes, pinned compiler, actual owner unit, complete
emitted destructor symbol/section extent, whole native hash and full canonical
comparison. No generic masked-fingerprint threshold is relaxed. A fresh raw
CFG check closes each RET boundary, and each entire byte body is unique in the
full4027-candidate inventory.

Current source/native hashes:
-45CF50/8:51d7355ce2c8a297ef113328b2d6405d45a652055a0453c724c6d930cf512109.
-46E950/15:13c246d3bcc6065db09caa3462cda670cb28700f35ea08b13ad1be865e9506e7.

The two complete public owner replays pass all eight configured bodies:
rotation265, sprite copy116, record cleanup8, info constructor195, normal
owner destructor185, deleting destructor30, record constructor28 and cleanup15.
These are fresh actual native comparisons, not cached claims. Existing implicit-
lifetime tooling tests remain applicable; no new validator behavior is added.

Only23 compiler bytes and two exclusions are added. Authored exact/source counts do
not change. The earlier IColor declaration correction is unchanged.
