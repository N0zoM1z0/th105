# Active result-menu source

The full `CMenuResult::update_active` source is now individually selected at
`4472A0` by `exact-first-result-menu-active`. Its actual owner is established
by the exact `447560` wrapper's native tail edge, and the whole native body is
pinned by `ui-input-result-policy-authored-106a`. The body contains 175 reachable
instructions and 27 direct calls across 619 bytes.

The source retains cursor updates, checked character and result selection,
replay setup, profile-menu transition, and cancel handling. A fresh pinned VC8
comparison emits a 620-byte candidate and differs from the original at +81;
the target uses a different receiver register during selection. This is not an
exact match, and no source-prefix credit is granted. The separately emitted
cleanup handler and metadata have not been proven exact. Prior source trials
also found different shared return topology; no fabricated return or ABI
changes are introduced. No actual replay loading or gameplay is claimed.

Reproduce with `scripts/repo-python scripts/build.py --unit
exact-first-result-menu-active --compare --json`, which is expected to report a
mismatch. The exact wrapper is in `cross-v106a-menu-result-update`, whose
separate constructor remains nonexact and makes the overall unit mismatch.
