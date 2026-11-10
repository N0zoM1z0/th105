# Exact/source-present ledger consistency

A status audit found exactly one canonical-exact row absent from the selected
source-present list: EffectResourceManager_load_effect_resource_437ec0.
Its2528-byte acceptance was already recorded on October31; the current source
and formal exact-first-effect-resources unit still replay the entire body
exactly. The missing name is restored to implemented.csv.

This corrects source-present1635 to1636. It adds no new exact function or exact
byte; exact1431/443916 remains unchanged. No authored source, mapping, byte
boundary, function-origin assignment or comparison contract is modified.

Tracking validation now requires every exact row to name an implemented/source-
present entry. Three focused tests cover the valid case, a missing entry and
an unrelated name. The stale parked effect-loader79-difference note is also
corrected to point to its existing later acceptance; the separate PAT load-order
negative remains explicit.

Prior source and acceptance explanation:
[EFFECT_READER_FORWARDING_EXACT_2026_10_31.md](EFFECT_READER_FORWARDING_EXACT_2026_10_31.md).
