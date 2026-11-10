# Real CSelect sprites and the shared IColor interface

CSelect's 38 ordinary sprite members now use the actual global CSprite type
in both constructor and destructor views. Construction, virtual texture calls
and field destruction use ordinary C++, replacing the local raw-vptr sprite
representation and the separate sprite-lifetime class in this owner. The
character-binding implementation is now CSelect::bind_character and uses the
actual CSprite setter and scale fields; scene entry calls it directly instead
of going through an unrelated receiver view.

## One real base identity, not register forcing

The first private control mixed actual CSprite/IColor with a second source
interface named CNumberColorLifetime. Select destruction grew845 to850 bytes:
the compiler could not reuse a constant belonging to a different source vtable
symbol even though both mappings named the same native IColor table.

Native RTTI independently establishes one four-byte IColor base. Making the
legacy CNumberColorLifetime spelling a typedef of ::IColor restores the full
845-byte destructor naturally. No register, volatile, alias barrier, artificial
storage or copied instruction sequence is used to remove the extra load.
The other existing narrow lifetime views are not all rewritten here.

IColor now lives in the minimal engine/ColorInterface.hpp. Importing the whole
battle sprite header into every number lifetime initially exposed an existing
C/C++ dispatch_indexed_event linkage conflict in MenuConnect. The minimal
shared interface removes that unnecessary dependency without changing either
function declaration's ABI. MenuConnect destruction315 remains exact.

## Actual lifetime emission

CSprite's empty constructor/destructor bodies are ordinary in-class definitions.
The redundant UiSpriteLifetime.cpp definitions are removed. The existing
lifetime match unit retains its identity but compiles the real
NetworkBaseConstructorRuntime.cpp with its actual /GS profile, so ctor16 and
cleanup7 are naturally emitted for the real member array. This is not a fake
caller or an emission-only TU; no forced inline/export/COFF boundary is added.
Both the lifetime selector unit and parent unit compile that same ordinary
source for their separate comparison selections. Final original TU partition
or whole-program linking is not claimed by these focused witnesses.

## Full results and regression scope

- Select destructor845 and real character binding258 remain canonical.
- Constructor4247 retains exactly its previous13-byte residual; complete remote
  EH461 and metadata188 remain exact. Main candidate hash stays76c04f844fb8c2d9d30293de2e1831edc3eeb9ab2acc442138825ddf43e64d33.
- Render1497/163, character update619/25, entry783 and frame update685 retain
  their entire previous canonical candidate hashes. Four render and twelve
  character observer cases, including their negative controls, pass again.
- Network construction411/packet8 and destruction259/scalar30/reset175 stay
  exact; complete EH197/meta116 and EH169/meta100 also pass.
- Natural CSprite16/7, scalar31, table36, full RTTI273 and actual array site40
  pass from the real owner source. All410 unique byte-corruption controls reject.
- The affected include closure is130 units. All104 units containing251 accepted
  authored roots were freshly rebuilt and remain exact. Initial receipts before
  the minimal-interface extraction were preserved but not reused afterward.
- Existing configured nonexact authored neighbors in those rebuilt units were
  also inspected; none becomes exact. No unrelated cold whole-corpus replay.

The four affected source-origin guards were renewed only after the full proofs,
including the new interface header. All pass; the network scalar30 receipt was
refreshed. The constructor EH audit now applies the same explicitly named,
pre-attested data aliases as its main comparison. Unknown destinations, raw
addresses and unreviewed alias chains fail; no comparison mask is introduced.
Five alias tests and three lifetime-source review tests protect these changes.

Reproduce serially on CPU0/nice10 with scripts/repo-python: the focused unit
builds, csprite_lifetime_origins.py, sprite_default_origins.py, both packet/record
implicit-lifetime gates, the two network EH audits and the CSelect constructor,
render and character audits. Nonexact candidate audits still report mismatch.

No count or exact-byte gain: exact1429 /443911; source1636, authored1655,
excluded2072, review300, mapped1823, units811. Remaining UiTile/other UI call
views are separate work; this is not an all-facade or full-game reconstruction
claim.
