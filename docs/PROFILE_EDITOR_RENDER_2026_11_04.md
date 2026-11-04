# Profile editor rendering

Japanese TH105 1.06a `ProfileEditor168::render` at `0x00427DB0` contains a
568-byte callable body (SHA-256
`44953d23a8806cd2c7695c1f377cbfe8e09c6a7434ccdef8c89c945a306a0740`)
and a following four-entry jump table. The complete 584-byte body/table
SHA-256 is `300516c5b6bd3b326f40c6ca56f1b5f9b8c062351b4a98d80d53a8d011b4a6d0`.
The canonical-exact ProfileMenu render calls it at `0x0044BEBA`.

The real-type source reads the shared profile controller text, composition
attributes and cursor, renders the primary/composition tiles when present,
selects highlight colors/underline geometry, and draws the blinking caret.
USER32 `SetRect` is bound to the verified `0x006C020C` IAT slot. The exact
integer-rectangle helper and the separate nonexact CTile render source retain
their actual identities. The ordinary candidate section including its local
switch table is 596 bytes, SHA-256
`6256d99a355e5c3130fa12be00af0d4e2e454b541c81f13136eabbde23dade1a`;
it is nonexact and receives no callable or table exact credit.

A bounded x86 observer runs 12 finite ASCII fixtures spanning inactive state,
primary and composition text, all four highlight attributes and two unknown
attributes, missing texture handles and caret timing. It executes the pinned
native floating conversion with the SSE path enabled, and compares the complete
ordered rectangle, draw and tile call traces against source and an independent
fixture model. `SetRect`, draw and tile calls are controlled mocks. A modified
highlight color is detected by a negative test. Actual IME input, D3D output,
other floating environments, unbounded strings and full-game execution are not
proved. Fresh comparison preserves the exact 223-byte ProfileMenu render and
six exact render-primitive roots.
