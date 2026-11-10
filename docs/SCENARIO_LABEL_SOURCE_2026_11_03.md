# Scenario label selection source, 2026-11-03

The existing source for scenario label selection is now tracked individually. Native `0x455490` has a 276-byte closed callable body, SHA-256 `58a5ad2f28ad4f111408771ec435f7b34c3b1bf0bc77deb3185b7ce2f0498190`, 100 decoded instructions and `RET 0x1C`. The exact owned-string wrapper calls it at `0x45A4A1`; its 130-byte public replay was freshly verified.

The implementation resets the script iterator and searches command-zero labels against the owned string, with normal by-value cleanup. The recovered view and name are labels for the observed layout, not claims about original source spelling. `SCENARIO_LABEL_SELECTION_2026_10_28.md` records the target behavior, owned string, checked iterator and prior owner controls.

The existing `exact-first-scenario-label-selection` unit emits 275 bytes versus
native 276, with the first difference at offset 36. It remains source-present and
nonexact. The mapped exception-handler address in the ordinary object comparison is
not a full cleanup-EH equivalence proof, and no partial or exact-byte credit is
granted.

## Actual script and scenario ownership, 2026-11-04

Now that `CScript::next_command` has an ordinary source definition, the label
search uses the real `CScenarioData` owner, `CScript` member and checked deque
rather than separate partial receiver views. The exact 130-byte string-dispatch
wrapper calls the same actual `CScenarioData::select_label` symbol that the
source defines, and the label search calls the same `CScript::next_command`
symbol that its new source defines. This resolves the source-level names and
owner types, not an entire application link.

The complete label candidate remains 275/native276, first difference +36; its entire
canonical candidate SHA remains
`3eea55109cff650d5f922a2d9fad6ebdd64592846bb7569b67f87bedd5b09790`. Its cleanup EH
has not been promoted, and the script dereference helper's private ABI remains
unresolved. The exact wrapper and all 22 accepted roots across the 11 actual
source-dependent units replayed exact. No new function or byte is credited. The
focused origin rule and all 1,030 target-independent CI tests passed.
