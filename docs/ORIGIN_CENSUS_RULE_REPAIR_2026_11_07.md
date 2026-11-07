# Origin census rule repair

A full origin-census regeneration failed on six rules. This batch repairs three independent configuration inconsistencies without changing any origin disposition, function status, exact match, or byte total:

- The palette rule skips the already-matching raw-palette function; its expected name list now contains only the selected BMP function.
- The BGM stream rule's `0x402A00 → 0x418A10` call is an outgoing call from a selected body to an existing matching helper, so it is expressed as `required_selected_body_calls`, not as an incoming `required_direct_edges` witness whose target must itself be selected. The original call site and target remain checked.
- The menu-practice rule selected zero functions after its target became exact but still required a selected RTTI witness. The inactive rule is removed; the existing matching baseline and `MENU_PRACTICE_UPDATE_2026_11_04.md` retain the evidence.

The two active repaired rules were validated directly against the hash-attested target; a targeted test covers name lists after `skip_matching`. The full census is still blocked by separate profile generated-symbol, network caller-context and scalar-proof-cache issues. This batch does not claim to repair or bypass them.
