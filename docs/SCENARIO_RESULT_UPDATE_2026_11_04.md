# Scenario result phase update

Japanese TH105 1.06a `0x00454A50` is a complete 403-byte Scenario result
phase update, SHA-256
`f4e0aad65c899f67572a833c036a139fafafedd36dd8e360a6ea0809e0d6a871`.
The Scenario command interpreter calls it at `0x00458972` on its real result
member. The body implements phase-dependent alpha, timed panel movement,
entry-level updates, and phase/counter progression. Its calls to sine, cosine,
result reset and level-setting target independently exact existing providers.

The selected `ScenarioResultResource::update` source uses the shared actual
result layout and those real function symbols. Fresh ordinary VC8 comparison
emits 403 bytes but is nonexact at +3 because of ESI/EDI allocation; its full
candidate SHA-256 is
`1dfd4213426885ee44f1db6b2f00d489ac8fd3c74809966621f2025a0a74dd32`.
The function is authored/source-present and contributes no exact bytes.

A bounded x86 observer runs 28 native/source cases spanning inactive state,
phases 0/1/2/3 and selected counter boundaries, with two controlled finite
wave results. It compares call order/arguments, returned byte, stack cleanup,
phase/counter/alpha and four position pairs. All traces agree; a test that
inverts the active-state branch is detected. Wave lookups, reset and level
updates are controlled mocks: actual orientation-table values, external effects,
exception handling and whole-game execution are outside this evidence.
