# Environment base ownership, JP1.06a

Environment is now the shared empty RTTI base. The observed 24-byte animation
state belongs to AnimationObject. No object offset or exact-byte total changes.

## Cross-owner evidence

CScenarioData vtable 6C2990/COL6D9474 uses Environment BCD6D7B70 at displacement 4,
over the actual SystemEffectManager member constructed at+4. The Character
hierarchy uses the same type descriptor 6E6430 via BCD6D7748 at displacement 130,
over its animation state. A nonempty 24-byte base cannot explain both layouts
without overlapping the real owners. An empty base explains both under MSVC.
Fresh source RTTI independently emits Environment offsets 4/130; the compiler
accepts sizeof(Environment)==1 without adding storage to either owner.

AttackObject.hpp now places the old owner_field_000, flag_004/005 and unknown
state directly in AnimationObject at unchanged 130/134/135 offsets. Historical
field names are retained. ReimuObjectOwnerView.hpp has the same owned state;
ScenarioDataLifetime.cpp uses the common tag instead of a local empty proxy.
AnimationObject/AttackObject/Reimu sizes remain 158/330/388. Repository use
review found no container or standalone allocation of Environment, and no
external access to these fields through an Environment pointer.

## Focused preservation

Eleven affected units were rebuilt serially, not the corpus. All 34 previously
accepted functions remain exact: AttackObject/AnimationObject construction 2;
CharacterObject lifetime 3; effect lifetime 4; pool acquisition 2; SystemEffect5;
roster/Sakuya spawns 14+1; Character constructor 1; ScenarioData destructor 1;
Reimu counter helper 1.

Known nonexact bodies are unchanged: Character destructor 905 retains 352716b4...;
ScenarioData constructor 1528 retains 6511c94f... for its compared prefix; the
full Reimu object candidate 45696 retains 4b565d71.... A fresh before/after COFF
comparison proves all 136 Reimu section payloads and relocation tables identical.
Only the timestamp and one compiler local-symbol numeric suffix differ.
No partial body, metadata byte or nonexact giant gets new exact credit.

Default CI/diff checks cover the final header correction. Original high-level
static/helper methods of the tag remain outside this layout recovery; no such
methods are invented.
