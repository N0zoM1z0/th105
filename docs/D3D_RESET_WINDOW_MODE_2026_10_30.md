# Direct3D reset and window-mode policy

Both complete authored roots now match the canonical Japanese 1.06a target:

- reset_application_d3d_device, 414A10: 281/281 bytes; SHA256
  5af60a593dd8c3df5150098c652e4c00a60f51dadf963ee98598b7d7865cebbe.
- toggle_application_window_mode, 414B30: 286/286 bytes; SHA256
  2f2303f51221b20cd0cd449d4d987d04098c8fa760ae2586d9c38ec9c6acffaa.

The new credit is 567 bytes: incremental total 1533 exact functions / 434831
bytes. This is focused validation, not a new whole-corpus replay.

## Reset behavior

The native 82-instruction root has two RETs and no missing tails or internal
padding. It rejects a null Direct3D interface, null device, or cooperative
result 88760868. Windowed presentation uses the saved display format; fullscreen
uses format 22. Under the existing backend critical section, each listener is
notified through virtual slot zero, then the old swap chain is released.

A negative device Reset result unlocks and returns false without restoring the
released swap chain or notifying reset completion. Success reacquires swap
chain zero, calls listener slot four, unlocks and returns true. The GetSwapChain
result is intentionally ignored. Locks are manual; no exception cleanup or
additional error recovery was added.

The actual message pump calls reset at 4081B2. Its old source declared a void
result, but native toggle calls 414B40 and consumes AL; the declaration now
correctly returns bool. The existing application loop remains exact 177/177.

## Window-mode behavior

The native application helper at 4087AE calls the toggler. The toggler flips
windowed state before reset and flips it back if reset returns false. It does
not perform a second reset on failure. The successful branch selects windowed
versus fullscreen before any metric API call.

Windowed mode computes signed outer width/height from the backend dimensions
and native metric indices, centers against screen dimensions, and calls
SetWindowPos with HWND_NOTOPMOST and flags 20h. Fullscreen mode uses negative
frame/caption offsets, zero width/height and flags 21h. Signed divisions retain
truncation toward zero; the exact API call and argument order is reproduced.

The fullscreen branch really calls GetSystemMetrics for indices
45, 7, 5, 46, 8, 6, 4 and discards those seven results before recomputing its
offsets. Source preserves these observed API calls directly, without inventing
unused locals or padding. Why the original source retained them is unknown.
A common source calculation before the branch did not preserve the native
branch timing; a cached flag preserved semantics but not code. Branch-local
source with the observed discarded calls reproduces the full body.

## Reproduction and evidence

D3DBackendReset.cpp uses the existing typed D3DBackend and listener contracts.
Ordinary COFF yields 277/281 reset and exact 286-byte toggle. The genuine
same-source CIL recovers the reset's aligned EBP frame naturally and matches
both complete functions. No forced alignment, custom ABI or copied helper was
introduced. The actual scalar fields and the PE-attested SetWindowPos IAT have
isolated data bindings; earlier backend addend allowlists remain unchanged.

Only the new unit and the changed application message-loop unit require native
replay. Both roots and the previous 177-byte caller pass. All unchanged origin
rules and unaffected rows are retained; the two freshly matched authored
baselines replace their previous unknown/review entries.

Private evidence is under build/frontier-d3d-reset-20261030, particularly
boundaries.json, formal-linked.json and caller.json. Reproduce with:

- scripts/repo-python scripts/build.py --unit exact-first-d3d-reset-window-mode --json
- scripts/repo-python scripts/compare-linked-unit.py exact-first-d3d-reset-window-mode --json
- scripts/repo-python scripts/build.py --unit cross-v106a-application-message-loop --compare --json
