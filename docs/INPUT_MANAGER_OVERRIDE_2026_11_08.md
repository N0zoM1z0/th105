# Restore the input-manager update override

`CInputManagerEx` overrides its base update slot. The shared header instead
introduced `build_player_logical_input_mask` as a third virtual function,
leaving the inherited base update in slot +4. This was a real dispatch mismatch,
even though the standalone 378-byte logical-update implementation already
matched the target.

## Original evidence

The pinned Japanese 1.06a executable has two callable entries at `0x6C1154`:
scalar deletion at `0x42CBC0`, followed by logical update at `0x409F70`.
The next bytes at `0x6C115C` are `score.dat` and its terminator, not another
function pointer. The preceding COL points to `0x6D7A50`; its hierarchy has
exactly the two descriptors for global `CInputManagerEx` and `CInputManager`.
The derived descriptor is at `0x6E6588`, the hierarchy at `0x6D7A64`, and the
base descriptor at `0x6FA43C`.

The real `NetworkBaseConstructorRuntime.cpp` owner constructs the nested input
endpoint and emits this table. Before the correction, its COFF section held a
COL plus three slots: the deleting destructor, base update, and added logical
update. Afterwards it holds a COL plus the two original callable roles.
The weak deleting symbol resolves to the actual scalar destructor; it is not
an invented callback binding.

## Source and validation

The derived declaration and definition now use
`update_player_input_counters_from_raw`, matching the base virtual signature.
The frame updater's direct call and the two match-unit symbol selectors follow
the rename. The logical implementation's qualified call to the base remains
unchanged. No field, base interface, destructor body or compiler flag changed.

The private proof checks complete unmasked bodies and closed control flow for
logical update `0x409F70`/378, derived destruction `0x42C950`/5 and scalar
deletion `0x42CBC0`/30. All three compare equal. Both full callable table slots
are verified against the original bytes and actual emitted relocation roles.

The header reaches 95 configured units, but only nine use the changed derived
type. A tracked source/reference search and transitive source-dependency review
identify those nine: logical input, the network base and constructor, primary
protocol/state/continuation, sprite lifetime, client pacing and frame update.
Their 21 before/after comparisons are unchanged: 17 zero-difference results,
including all 13 accepted roots. Every non-debug COFF section is identical in
bytes, symbols and relocation roles after normalizing the method rename,
except for the intended smaller derived table in the two constructor profiles.
This also covers the unchanged EH and data emitted by those owners.

Five affected compiler-origin checks pass: CSprite lifetime (including the
full network constructor EH), implicit input-packet cleanup, the network array
constructor helper, byte allocation and gamepad allocation. The latter two
consume the header without using the changed derived type; they were rebuilt
for their executable source pins. Only the changed header pins were renewed.
There is no new authored exact entry.

Private evidence and replay drivers are in
`.analysis/frontier-input-override-20261108/`; reports and preserved before/after
objects are in `build/frontier-input-override-20261108/`, notably
`interface.json`, `summary.json` and the five origin results. Target SHA-256 is
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`;
VC8 SP1 uses the existing unit profiles.

## Remaining type work

The shared source still emits namespaced struct RTTI
(`.?AUCInputManagerEx@th105@@`), whereas the original is a global class
(`.?AVCInputManagerEx@@`). The shared base and network endpoint constructors are now connected, as
described in [the endpoint note](NETWORK_INPUT_CONSTRUCTOR_2026_10_29.md).
The global lifetime definition and nominal RTTI identity remain separate; a
future merge must reconcile that boundary with complete lifetime evidence.
