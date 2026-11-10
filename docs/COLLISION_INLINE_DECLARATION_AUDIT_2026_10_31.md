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

No aggregate count or source-spelling regression assertion was added to tests.

The final target-independent CI passes155 tests and the whitespace gate passes.
Exact totals remain1545 functions /438021 bytes. Source1740, authored1760 and
review847 are unchanged. This closes the two observed annotations only; it is
not a claim that every compiler attribute in the repository was audited.

## Follow-on SpellData declaration

Removed the declaration-only noinline attribute from
ShortDeque8::front_checked in src/battle/SpellData.hpp. Its normal separately
defined implementation and all layouts, signatures and bodies are unchanged.
No replacement optimizer constraint was introduced.

All 103 accepted functions in the 61 actual affected units were freshly compiled and
remain canonical exact. This set overlaps the earlier 452-function Collision replay;
these counts must not be summed as distinct coverage.

A literal tracked-source search finds no remaining __declspec(noinline)
outside src/library. This is not a general compiler-directive audit.
There is no new exact, source-present or origin credit.
