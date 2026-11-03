# Scenario label selection source, 2026-11-03

The existing source for scenario label selection is now tracked individually. Native `0x455490` has a 276-byte closed callable body, SHA-256 `58a5ad2f28ad4f111408771ec435f7b34c3b1bf0bc77deb3185b7ce2f0498190`, 100 decoded instructions and `RET 0x1C`. The exact owned-string wrapper calls it at `0x45A4A1`; its 130-byte public replay was freshly verified.

The implementation resets the script iterator and searches command-zero labels against the owned string, with normal by-value cleanup. The recovered view and name are labels for the observed layout, not claims about original source spelling. `SCENARIO_LABEL_SELECTION_2026_10_28.md` records the target behavior, owned string, checked iterator and prior owner controls.

The existing `exact-first-scenario-label-selection` unit emits 275 bytes versus native 276, with the first difference at offset 36. It remains source-present and nonexact. The mapped exception-handler address in the ordinary object comparison is not a full cleanup-EH equivalence proof, and no partial or exact-byte credit is granted. Fresh receipts: `build/frontier-scenario-label-source-20261103/source.json` and `caller.json`.
