# Environment base ownership, JP1.06a

Environment is now the shared empty RTTI base. The observed24-byte animation
state belongs to AnimationObject. No object offset or exact-byte total changes.

## Cross-owner evidence

CScenarioData vtable6C2990/COL6D9474 uses Environment BCD6D7B70 at displacement4,
over the actual SystemEffectManager member constructed at+4. The Character
hierarchy uses the same type descriptor6E6430 via BCD6D7748 at displacement130,
over its animation state. A nonempty24-byte base cannot explain both layouts
without overlapping the real owners. An empty base explains both under MSVC.
Fresh source RTTI independently emits Environment offsets4/130; the compiler
accepts sizeof(Environment)==1 without adding storage to either owner.

AttackObject.hpp now places the old owner_field_000, flag_004/005 and unknown
state directly in AnimationObject at unchanged130/134/135 offsets. Historical
field names are retained. ReimuObjectOwnerView.hpp has the same owned state;
ScenarioDataLifetime.cpp uses the common tag instead of a local empty proxy.
AnimationObject/AttackObject/Reimu sizes remain158/330/388. Repository use
review found no container or standalone allocation of Environment, and no
external access to these fields through an Environment pointer.

## Focused preservation

Eleven affected units were rebuilt serially, not the corpus. All34 previously
accepted functions remain exact: AttackObject/AnimationObject construction2;
CharacterObject lifetime3; effect lifetime4; pool acquisition2; SystemEffect5;
roster/Sakuya spawns14+1; Character constructor1; ScenarioData destructor1;
Reimu counter helper1.

Known nonexact bodies are unchanged: Character destructor905 retains352716b4...;
ScenarioData constructor1528 retains6511c94f... for its compared prefix; the
full Reimu object candidate45696 retains4b565d71.... A fresh before/after COFF
comparison proves all136 Reimu section payloads and relocation tables identical.
Only the timestamp and one compiler local-symbol numeric suffix differ.
No partial body, metadata byte or nonexact giant gets new exact credit.

Receipts:build/frontier-environment-ownership-20261029/, including one JSON per
unit, source-rtti.json and reimu-section-equality.json. Default CI/diff checks
cover the final header correction. Original high-level static/helper methods
of the tag remain outside this layout recovery; no such methods are invented.
