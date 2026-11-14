# Exact functions left unaccepted

A survey that rebuilt every unit holding a nonexact authored function found three
that already compare exact, with full relocation replay, in their existing units:

| Address | Function | Bytes | Unit |
| --- | --- | ---: | --- |
| `0x42CF70` | `ScoreData::record_sequence_result_42c060` | 159 | `gpt-web-score-sequence-result` |
| `0x42D010` | `ScoreData_update_observed_record_statistics` | 191 | `gpt-web-score-observations` |
| `0x432200` | `SpellDataOwner_finalize_loaded_spell_data` | 260 | `exact-first-spell-finalize-natural` |

Earlier sessions recorded them as exact locally but held them for "Factory
acceptance". That step is no longer part of acceptance; a zero-difference
comparison in a reproducible unit is. All three are now in `matches.csv`.

The old note on `0x42CF70` claimed that ordinary VC8 omits the target's
`cmp edi, edi` same-container check; the current build keeps it.

    scripts/repo-python scripts/build.py --unit gpt-web-score-sequence-result --compare --json
    scripts/repo-python scripts/build.py --unit gpt-web-score-observations --compare --json
    scripts/repo-python scripts/build.py --unit exact-first-spell-finalize-natural --compare --json

Re-run the survey after shared header changes: a nonexact unit can become exact
without its own source changing.
