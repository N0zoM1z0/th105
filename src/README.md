# Source layout

The planned modules are defined in `config/modules.toml`; character-specific
implementations belong below `src/characters/`. This taxonomy does not establish
the original translation units or binary ownership.

The tree includes retained hypotheses from the former 1.06 target. For the
original Japanese 1.06a target, `config/implemented.csv` records selected source
and `config/matches.csv` records accepted canonical exact functions. A file's
presence or successful compilation does not establish either status.

Obtain current counts with
`python3 scripts/report-reconstruction-status.py --summary`.
Start from the [current handoff](../docs/RE_HANDOFF.md), then consult
the [AyaObject](../docs/AYA_OBJECT_EVIDENCE.md) or
[ReimuObject](../docs/REIMU_OBJECT_EVIDENCE.md) evidence index before changing
those large roots. Dated reports retain their own source and object epochs.
