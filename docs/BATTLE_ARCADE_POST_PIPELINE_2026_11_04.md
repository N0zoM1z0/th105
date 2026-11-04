# Arcade battle post-pipeline override

The 198-byte native body at `0x00472F80` is the `+0x30` virtual of the
RTTI-identified `CBattleManagerArcade` table at `0x006C154C`. All 198 bytes
are reachable and its SHA-256 is
`7bd9a3677d422ac3ea268666d008962cbe98e547bdb4a781dac8c5d4395143fe`.
It checks both fighters' terminal flags, advances the opposite fighter's
counter, updates the byte at owner offset `0x5B0` and dispatches transitions
3 or 4. The selected source uses the established base and a narrow derived
view, without asserting the original full derived layout.

The ordinary pinned VC8 build emits 198 bytes, canonical SHA-256
`a194fd236d33d3094f29894db9af4efd7177b239619b37927799ab0b1514221d`.
It differs first at +181: target loads the vptr before incrementing the state
byte, while the candidate increments first. It remains nonexact. The native
and source class's original nominal names and translation-unit context remain
unknown. No manual vtable, fake operation, forced register, or runtime
behavioral equivalence is claimed. Receipts and boundary audit are under
`build/frontier-arcade-post-source-20261104/` and
`build/arcade-472f80-boundary.json`.

Reproduce with `scripts/repo-python scripts/build.py --unit
exact-first-arcade-post-pipeline --compare --json` (expected mismatch exit 1).
The focused origin rule independently validates the original RTTI slot and
full body hash. Source selection adds no exact bytes.
