# Shared CNumber in design loading, 2026-11-02

Target SHA-256: 56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

The design loader now owns the shared CNumber instead of DesignLoaderNumber.
CDesignBase is a friend of CNumber so the loader can retain the observed direct
field initialization; this changes access visibility only. The real class's
existing size and private member-offset assertions replace the duplicate view.
Its constructor builds the actual tile before clearing the number-value pointer.

This corrects a concrete ordering error in the old local view. Native loader
0x40B81B..0x40B828 initializes object +0x44 (tile handle), then +0x40 (tile table),
then +0x3C (number-value pointer). The old view emitted +0x3C, +0x44, +0x40.
The shared constructor naturally emits the native +0x44, +0x40, +0x3C order.
No manual stores or initialization-order forcing are added to the loader.
The raw emitted loader section remains 2580 bytes; only ten raw byte positions
change, SHA-256 now
43a879f7fe4ebb0aa30c649c112ae59b734abecc7d06e7148cc62c64c210ff28.
This is an instruction-order correction, not ten new canonical native bytes:
the complete loader still has its unqualified EH / context block.

The loader's actual CNumber scalar wrapper matches all 60 bytes at 0x40AE10,
and its four-slot table agrees with native 0x6C1B60, including the source weak
scalar fallback. Existing color providers remain exact in their actual owner.
No new scalar credit or full namespaced RTTI identity is claimed. The outer
loader object and gauge views remain separate.

Actual quoted-include closure is 11 units. All 28 accepted roots in 10 units
pass adopted replays. Eight other comparison results in six units are unchanged:
seven compared hashes and the existing loader EH block. The raw loader change
above is retained separately rather than mislabeled as a canonical comparison.
The implicit-cleanup rule passes 3 / 28 after the header source-pin review;
generated loader origins pass 9 / 948 and scalar gates pass 1 / 30 plus 2 / 121.
No manifest, validator, origin classification or progress count changes.

Private controls and receipts: .analysis/frontier-design-loader-real-number-20261102/
and build/frontier-design-loader-real-number-20261102/. Final CI passed all 962 tests in
100.432 seconds. Both diff checks gate the local checkpoint. Totals remain 1426 exact / 443399 bytes,
source 1636, authored 1655, mapped 1826, excluded 2076, review 296 and units 813.
