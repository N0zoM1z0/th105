# Selection policy methods on the declared CSelect owner

The previously established seventh virtual declaration now has its actual
source implementation: `CSelect::update_selection` owns the existing complete
341-byte flow body. Stage and character policy similarly become
`CSelect::update_stage_420560` and `CSelect::update_characters_41fc90`.
The three large partial-owner declarations are removed. Their fields resolve
to the independently checked CSelect members, not replacement storage.

The shared `SelectSetupState.hpp` retains the already-reviewed setup field
view from the entry TU: identifier, signed stage/music bytes, two existing
MatchSetup::Side records, seed and three random flags at4C..4E. This is still
a pointer-only view, not a claim about original nominal setup type or heap
allocation. Both full layout headers include it. Entry, character and stage
policy now use one definition instead of three differently named records.

Character refresh calls the existing actual CSelect::bind_character. Flow
calls the two actual CSelect policy declarations. The selected-effect callback
interface remains a narrow slot14 view; casts are performed on each existing
load rather than caching across callbacks, preserving possible mutation by
those callbacks. Input fields use the existing constructor-owner hold array;
no separate input-manager type unification is claimed in this scope.

## Whole-body verification

Private seven-unit adoption controls passed before publication. Final fresh
include closure is9 units, with all four accepted authored consumers freshly
replayed: stage890, flow341, binding258 and destructor845. The five nonexact
consumers retain their complete previous candidate bytes:

- Character619 /25 differences:
  `537459e26772b9fb7aa85db0339011557c774ec435680fcd158fe12bd838f7c3`.
- Entry783:
  `c5a5b8b1dc50bbd2e16c13d84f36263ed6bead06faa0536c0547a9fed2474ef3`.
- Frame685/native697:
  `718a936b35f387880f875d139c2293cb95d8e06498a4a319645d06a4e6560f5d`.
- Render1497 /163 differences:
  `b98b646c43d177d02864f2a8e848314792657bbfe3c238393e1bac20f9102420`.
- Constructor4247 /13 differences:
  `76c04f844fb8c2d9d30293de2e1831edc3eeb9ab2acc442138825ddf43e64d33`.

Full constructor EH461 and metadata188 remain exact. The implicit CSpriteEx
owner gate adds the shared setup header to its reviewed source pins and passes
without relaxing the gate. All12 guarded character state/call cases and4
render cases rerun, including existing corrupted-cursor and random-table
negative controls. These are finite diagnostics, not universal equivalence.

The seven-slot owner audit now also checks complete stage/character bodies.
Decorated method selectors and call identities change, not destinations,
ABI, compiler flags or algorithms. No source spelling/register grid was
reopened. `matches.csv` and origin accounting remain unchanged. Exact1429 /
443911 bytes, source1636, authored1655, mapped1823, review300, excluded2072,
units812. This is owner/source consolidation, not an exactness increase.

The namespace-qualified CSelect declarations, separate destructor-facing
owner, remaining UI/input facades and full executable linkage are not claimed
fully recovered. Evidence: `.analysis/frontier-select-methods-20261102/` and
`build/frontier-select-methods-20261102/`. Native jobs serial CPU0/nice10;
original hash-attested target only, no IDA semantic reuse, no push.
