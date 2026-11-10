# Scenario stand commands use the character resource name

The Stand command in `CScenarioData::update` now builds its resource path from
`it->second.text_098`, not `it->first`. A map key can name a story role rather
than a character directory. The previous source would request
`data/character/win/stand/...` for a winner record whose resource name is
`reimu`; the native code selects `reimu`.

## Original evidence

The pinned Japanese 1.06a interpreter dispatches command 3 to `0x459077`.
It finds the record using the command's first string, but its nonempty stand
branch passes **node + 0xC0** to the string concatenation at `0x45911A`.
The checked map node's pair starts at +0x0C and its mapped value at +0x28;
+0xC0 is therefore `ScenarioTextEntryDC::text_098`, not the key at +0x0C.
The later active-name publication at `0x459299` deliberately uses the key.
That publication, the empty-stand branch, texture dimensions/pivot, facing,
visibility and color updates are unchanged.

This distinction is used by ordinary battle transitions. The complete
`CBattleManager::run_transition_phase_5 @ 0x4724E0` freshly replays **991/991**.
Its calls at `0x47264D` and `0x4726EC` install keys `win` and `lose`, while the
other string argument comes from the corresponding character-name lookup.
The native installer at `0x456F05..0x456F1C` copies that second string into the
entry's +0x98 member. Thus the key/resource distinction is not an invented
malformed-state example.

## Focused verification

Both full interpreter builds were attempted with the existing unit
`exact-first-scenario-command-update`. Both strict comparisons stop at the
same unqualified local string copy constructor. The interpreter remains
unselected and gains no exact credit; its 5,368-byte source section is not
an exact match to the native 6,121-byte callable / 6,216-byte payload.

A complete before/after COFF differential accounts for all 300 non-debug
sections and 677 relocation records. The 299 non-root sections, including
EH code/data, are unchanged. The root adds `ADD EAX,0xB4` after its real map
iterator returns a pair pointer. Every other byte change follows the resulting
branch/label displacement or compiler alignment adjustment; all 182 direct
branches and all 266 root relocations are checked. The 23-case table retains
its targets, adjusted only for the shifted code positions.

A bounded instruction witness executes the native and compiled argument
selection up to, but not through, the first concatenation call. Winner/loser
aliases, an equal key/resource control and heap-backed strings all select the
native field after the fix. The old compiled source selects the wrong field
for each alias. This does not execute string concatenation, graphics or the
complete interpreter.

Evidence: `build/frontier-scenario-command-control-20261110/` contains both
objects/build reports, the complete native CFG audit, the exact phase-5 caller
report and `verification.json`. The reproducer is
`.analysis/frontier-scenario-command-control-20261110/verify.py`.
Only the interpreter TU consumes the edited source. No shared header,
manifest, source pin or acceptance ledger was changed.
