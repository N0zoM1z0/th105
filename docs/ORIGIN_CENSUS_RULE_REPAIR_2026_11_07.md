# Origin census rule repair

A full origin-census regeneration failed on six rules. This batch repairs three independent configuration inconsistencies without changing any origin disposition, function status, exact match, or byte total:

- The palette rule skips the already-matching raw-palette function; its expected name list now contains only the selected BMP function.
- The BGM stream rule's `0x402A00 → 0x418A10` call is an outgoing call from a selected body to an existing matching helper, so it is expressed as `required_selected_body_calls`, not as an incoming `required_direct_edges` witness whose target must itself be selected. The original call site and target remain checked.
- The menu-practice rule selected zero functions after its target became exact but still required a selected RTTI witness. The inactive rule is removed; the existing matching baseline and `MENU_PRACTICE_UPDATE_2026_11_04.md` retain the evidence.

The two active repaired rules were validated directly against the hash-attested target; a targeted test covers name lists after `skip_matching`. The full census is still blocked by separate profile generated-symbol, network caller-context and scalar-proof-cache issues. This batch does not claim to repair or bypass them.

## Network caller context

The endpoint destructor rule previously put the 31-byte `0x44DBB5` constructor fragment into `required_body_hashes`, a field reserved for complete selected functions. It is now represented as a caller-context witness: the validator requires the enclosing `0x44DB10` constructor to retain its matching status, checks that the whole 31-byte span lies inside it, checks its SHA-256, and verifies that the span starts by pushing the selected `0x43BEA0` destructor address. The 19-byte destructor remains the selected full-body witness; the fragment is not added as a function. The real target witness and positive/negative unit controls pass. This repairs one more census failure without changing any classification. Profile generated-symbol and scalar-proof-cache failures remain unresolved.

## Checked deque witness

The `0x42D140` 100-byte generated checked `deque` indexing witness was historically regenerated from `ProfileMenuData.cpp`. That source was later corrected to use `.at()` for its own range-checked writer, so it no longer emits the anchored `operator[]`. Restoring the old writer would contradict its target evidence. The exact `NetworkInputSinkView::flush_to` owner instead naturally uses `std::deque<short>::operator[]`; a fresh VC8 build emits a complete 100-byte candidate whose relocation-masked fingerprint has the required unique inventory hit at `0x42D140`. Its actual owner remains exact 262/262. The existing origin rule now uses that current owner and its emitted symbol, retaining the same target, coverage requirements and compiler-generated classification. The rule ID remains a historical identifier. It does not prove that the target's original nominal element type must have been signed `short`.
