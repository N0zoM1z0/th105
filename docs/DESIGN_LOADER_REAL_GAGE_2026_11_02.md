# Shared CGage in design loading, 2026-11-02

Target SHA-256: 56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

The design loader now uses actual CGage instead of DesignLoaderGage. Its existing
constructor definition is shared verbatim in GageConstructor.cpp, included by the
original lifetime context and the loader. This provides real source visibility
without invented helper bodies or forced inlining. Gauge initialization uses the
existing fill_mode_9c field; the ordinary helper pointer type and comparison
selector now name CGage. No compiler options or ABI controls change.

Both affected units preserve all six accepted roots. The two existing scalar
roots / 120 bytes keep their origin proof. The loader's own actual CGage scalar
wrapper also matches the complete 56-byte body at 0x40AD60. Its full four-level
CGage / CSprite / CSpriteBase / IColor RTTI graph is canonical, 329 bytes, and all
nine virtual slots match. Slot 8 remains the existing declared entry with a native
physical implementation shared with CSprite render; no additional body credit.

Gauge initialization remains nonexact at 360 bytes with the same candidate hash.
The main loader keeps its unqualified EH block and unchanged raw 2580-byte source
section (43a879f7fe4ebb0aa30c649c112ae59b734abecc7d06e7148cc62c64c210ff28).
Its only relocation-name changes are the actual gauge table and typed initializer
helper. This is source equality, not a canonical native loader comparison.
The existing generated loader-origin rule still passes all nine bodies / 948
bytes with unchanged thresholds. The outer design-object classes remain views.

Private controls and receipts: .analysis/frontier-design-loader-real-gage-20261102/
and build/frontier-design-loader-real-gage-20261102/. Final CI passed all 962 tests in
103.735 seconds. Both diff checks gate the local checkpoint. No origin/ledger counts change: 1426 exact / 443399
bytes, source 1636, authored 1655, mapped 1826, excluded 2076, review 296, units 813.
