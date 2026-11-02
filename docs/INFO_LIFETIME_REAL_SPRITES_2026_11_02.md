# Actual info-record sprites and implicit combo cleanup, 2026-11-02

Target SHA-256: 56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

InfoManagerBaseLifetime.cpp now uses actual CSprite for both members of its
0x154-byte record. The duplicate sprite base/derived declarations and unused
CNumberLifetime include are removed. Actual record layout assertions still
establish sprites at +0x004 and +0x098. Before/after and adopted comparisons
preserve owner constructor 195, destructor 185, scalar wrapper 30, implicit
record constructor 28 and implicit record destructor 15 bytes. Only the first
two are authored matches; the three support bodies remain excluded.

Actual sprite RTTI 273 bytes and nine virtual slots pass. The complete constructor
and destructor EH bodies both map to the same physical 104-byte code region at
0x6BB880 and 76-byte metadata region at 0x6E1428. This is 180 unique support
bytes, not 360. The original array callbacks and member ownership remain exact.

That EH proof also closes the previously review-only 0x46EF30 / 5-byte helper.
The actual ComboResource34Lifecycle member derives from DesignResource34Lifecycle
and declares no destructor. Its ordinary implicit destructor is naturally emitted
by this real owner and tail-calls the qualified design cleanup at 0x421890.
The complete native EH region calls precisely this helper. The whole emitted
body matches; its raw SHA-256 is
297637762156706b1a1bdffa4e7de653ba49f562ed33570d30230a43fc3bd09b.
Among all 4027 inventory candidates, only 0x46EF30 has that complete 5-byte body.
This is an ownership proof, not a size heuristic or an artificial probe.

Add that one address to the existing strict implicit-cleanup rule: three bodies,
28 bytes in total. Renew the source pin and add the ordinary emitted selector.
Only the 0x46EF30 origin row changes from review to compiler-generated exclusion.
No authored function or byte is added or withdrawn. Invalid source hash, extent,
member kind and selector are all rejected; nine focused lifetime tests pass.
The existing record-constructor origin 1 / 28 and scalar origin 1 / 30 also pass.
No public validator or fingerprint threshold changes.

Private controls and receipts: .analysis/frontier-info-lifetime-real-sprites-20261102/
and build/frontier-info-lifetime-real-sprites-20261102/. Final CI passed all 962 tests in
109.298 seconds. Both diff checks gate the local checkpoint. Totals: 1426 exact / 443399 bytes, source 1636,
authored 1655, mapped 1826, excluded 2076, review 296 and units 813.
