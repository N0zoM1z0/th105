# Actual sprite and tile types in the design loader, 2026-11-02

Target SHA-256: 56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

DesignBaseLoad.cpp now uses actual CSprite and CTile instead of local vertex,
sprite-storage, sprite and tile classes. Its existing gauge view inherits the
actual sprite base and names the actual render_fvf4142 override; its number view
owns actual CTile. Gauge field accesses use the real texture dimensions and
handle value. The loader's gauge, number and design-object views remain local;
this does not claim actual CGage / CNumber ownership or unified outer classes.

The one affected unit preserves all three accepted 3-byte public methods at
0x40AE50 / 0x40AE60 / 0x40AE70. Gauge initialization remains nonexact at 360 bytes
with the same canonical candidate hash
52572feed070b2da682c1b4727319d2a6118f655d32d32d9630b197f5affb1bc.
The main loader remains blocked on its existing unqualified EH relocation.
No guessed handler address or relaxed comparator is added.

The emitted loader section has 2580 raw source bytes before and after, with
identical SHA-256 fe527be121cf925ff120f33f741054dbe3884581598a51ddb115f982e1cc4a19.
Its symbolic relocation sequence changes only the sprite table, tile table,
tile texture provider and a local switch-label spelling. That label retains its
2552 source-section offset. This is source-shape equality, not a canonical native
loader comparison; unresolved EH / private helper boundaries remain unresolved.

Actual sprite RTTI 249 bytes / nine slots and tile RTTI 247 bytes / four slots
pass. The existing generated-container origin rule passes all nine selected
bodies / 948 bytes, retaining its original thresholds and classifications.
No manifest, validator, origin ledger or authored counts are changed.

Private controls and receipts: .analysis/frontier-design-loader-real-sprites-20261102/
and build/frontier-design-loader-real-sprites-20261102/. Final CI passed all 962 tests in
113.522 seconds. Both diff checks gate the local checkpoint. Totals remain 1426 exact / 443399 bytes,
source 1636, authored 1655, mapped 1826, excluded 2076, review 296 and units 813.
