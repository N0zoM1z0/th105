# Remove unnecessary collision-header inlining barriers

The shared Collision.hpp no longer marks these methods `__declspec(noinline)`:

- HitExchangeIndexedEntry::reset_info_manager_indexed_entry
- FighterActionScratch::reset_fighter_action_scratch

Both already have normal, separately compiled definitions in HitScratchEntry.cpp
and FighterActionScratch.cpp. No production source includes those definition
files into another translation unit. The annotations were unnecessary for the
current accepted graph and are removed rather than retained as optimizer
constraints. No replacement attribute, fake caller, source padding or register
constraint was introduced. Layout, signatures and all function bodies are
unchanged.

Actual quoted-include dependency traversal identifies197 manifest consumers of
Collision.hpp;164 of them contain accepted functions. All452 accepted functions
in those164 units were freshly compiled and compared completely against the
pinned original Japanese1.06a executable. Every one remains canonical exact.
This includes the67-byte Fighter scratch reset and26-byte indexed-entry reset.
Other accepted receipts were preserved. This was a header-scoped replay, not
`verify-exact-units --all` and not a claim of a fresh whole-corpus run.

The private reproducible batch recipe is
.analysis/collision-inline-declaration-audit-20261031/check.py; its explicit
index-to-unit/address selection, per-unit full comparison reports and summary
are under build/collision-inline-declaration-audit-20261031/. No aggregate
count or source-spelling regression assertion was added to tests.

The final target-independent CI passes155 tests and the whitespace gate passes.
Exact totals remain1545 functions /438021 bytes. Source1740, authored1760 and
review847 are unchanged. This closes the two observed annotations only; it is
not a claim that every compiler attribute in the repository was audited.
