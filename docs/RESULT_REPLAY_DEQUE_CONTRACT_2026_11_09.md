# Result and network replay deque contracts

The short-value accessor at 0x0042D140 is VC8's checked
`std::deque<short>::operator[]`, not `at()`. Its full 100-byte body has three
invalid-parameter calls and returns the address of a two-byte element in an
eight-element block. The old const `at()` provider is 95 bytes and calls
`_Xran`; binding its caller to 0x0042D140 concealed a different provider.

Four network sources now select the actual indexing operator. Result-menu
selection uses the same operator through the existing replay-storage view.
Its match-setup append at 0x0042AA90 is `deque<short>::push_back`, not a string
assignment. The source now appends the selected short by reference. This
does not change the existing result-list storage layout.

## Bounded verification

The canonical Japanese 1.06a executable was hash-verified. Five affected
source units were rebuilt with the pinned VC8 profile:

- Server state import/export and ACK consumption: 162, 284 and 99 bytes exact.
- Client replay consumption: 199 bytes exact.
- Network primary state: 166, 152 and 175 bytes exact.
- Replay-request dispatch: 566 bytes exact.
- Result-menu active update: unchanged 620-byte candidate against 619 target
  bytes, with the first mismatch at +81. Its cleanup EH remains unaccepted.

All nine complete canonicalized root bodies equal their pre-change versions.
Thirteen complete root/EH sections also retain their bytes, owned extents and
symbolic relocations after the deliberate accessor-name substitution.

Five emitted const/nonconst short indexing providers each compare 100/100
bytes, including all three relocations. The menu's actual push-back provider
compares 119/119, with the complete 344-byte grow-map provider also matching.
These are compiler-generated support bodies already classified as such;
authored exact totals do not change.

Private reproducible evidence:
- `.analysis/frontier-result-replay-deque-20261109/build_units.py`
- `.analysis/frontier-result-replay-deque-20261109/verify.py`
- `build/frontier-result-replay-deque-20261109/verification.json`

The pending input-class migration and its source pins are a separate change.

## Remaining packet getters, November 9

Two declaration-only `at()` views still named the wrong provider: INPUT packet
serialization at `0x44D920` and replay consumption at `0x44E210`. Both now index
their existing `std::deque<short>` member directly. No packet layout, count
guard, reverse-consumption order, lock scope or unsigned input-word conversion
changes. Their real nonconst `operator[]` instantiations each emit the complete
100-byte native provider, including all three invalid-parameter calls.

The two affected units retain all 13 full local canonical matches, including
104-byte INPUT serialization and 170-byte replay consumption. Seventeen complete
root/EH sections retain their bytes and relocations after the provider-symbol
substitution. Evidence is in `build/frontier-packet-subscript-providers-20261109/`,
with the bounded verification script in the corresponding `.analysis/` directory.
These are repository-local comparisons, not a new Factory acceptance claim.
The separate Factory invocation/environment freshness issue remains unresolved.

The earlier result-menu 620-byte status above is historical. Its subsequent
619-byte local match and full EH proof are documented in
`RESULT_MENU_ACTIVE_SOURCE_2026_11_03.md`; current authoritative registry
acceptance must still be checked independently.
