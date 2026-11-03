# Connect history selection source, 2026-11-03

The existing connect endpoint-history selection source is now tracked individually. Native `0x443030` has a 157-byte closed body, SHA-256 `d5ded1997bd697302ca937d005e37921d6d73f5879713483b875b3d268d4b7ea`, 52 decoded instructions and four return paths. The exact history-action wrapper calls it at `0x4430DA`; the three authored caller-unit roots and their existing compiler-header support freshly replayed.

The source updates the cursor, handles confirm/cancel input, parses the selected checked history entry and updates the profile message. `CONNECT_ENDPOINT_SELECTION_2026_10_28.md` records the original layout and prior bounded controls. The other method in the source unit, endpoint-edit initialization, remains exact 165/165.

The history-selection body compiles to 153 bytes versus native 157, with first mismatch at offset 105. VC8 merges return paths the target keeps separate. It remains nonexact, with no synthetic duplicate epilogue, partial-byte or exact credit. Fresh receipts: `build/frontier-connect-history-source-20261103/source.json` and `caller.json`.
