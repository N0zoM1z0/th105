# Origin edge status reconciliation

A target-independent audit found stale status expectations on four existing
origin caller edges and four references to the same line-render provider. The
underlying native addresses, target hashes and CALL sites are unchanged:

- Line rendering `0x00401180` is source-present, rather than merely identified.
- FileReaderOwner open `0x0040CF40` is canonical exact, rather than only
  source-present.
- BGM transition `0x00402B70` is source-present, rather than unclassified.
- CharacterEx scalar deleting destructor `0x0064B770` is an independently
  canonical compiler-generated wrapper, now excluded from authored matches and
  marked identified in the candidate ledger. Its full 36-byte symbol and RTTI
  origin were freshly replayed using the dedicated scalar-wrapper validator.

Six directly affected origin rules were then checked against target bytes and
call sites without errors. A new target-independent regression test scans all
explicit caller statuses and body-call target statuses against the ledger and
rejects missing or stale rows. It does not replace a full origin evidence
replay. The rectangle renderer itself is now source-present, still nonexact;
its audit, three bounded observer cases and limits are documented in
`RECTANGLE_PRIMITIVE_2026_10_26.md`.
Eight accepted render/guide functions replayed exact, and target-independent
CI passed all 1,030 tests and generated-progress checks.
