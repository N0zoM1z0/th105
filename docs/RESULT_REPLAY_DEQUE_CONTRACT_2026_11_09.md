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
- `build/frontier-result-replay-deque-20261109/resumed.log`
- `build/frontier-result-replay-deque-20261109/verification.json`

The pending input-class migration and its source pins are a separate change.
