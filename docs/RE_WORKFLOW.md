# Reverse-engineering workflow

The workflow copies TH08's conservative state machine while adapting its
mechanics to TH105's VC8/LTCG executable.

## Sources of truth

- `config/target.toml`: immutable target identity and PE facts.
- verified IDA database: preferred semantic working state, never committed.
- `config/functions.csv`: provisional function candidates and reviewed state.
- `config/function-origins.csv`: generated authored/compiler/library disposition.
- `config/function-origin-rules.toml`: fail-closed current-target origin/exclusion rules.
- `config/reccmp-functions.csv`: durable address/name/category mappings.
- `config/implemented.csv`: mapped authored symbols whose source is present.
- `config/matches.csv`: accepted 100% exact functions only.
- `config/match-units.toml`: reproducible VC8 object/comparison graph.
- `config/known-symbols.csv`, `known-globals.csv`, and relocation ledgers:
  supported semantic and linker mappings.
- `docs/RE_HANDOFF.md`: current phase and blockers; ledgers override prose.

The analysis database is not the only durable record. Read back changes and
record accepted names, types, boundaries, and evidence in the repository.

## State layers

These transitions must remain separate:

1. **Candidate:** IDA sees a function-like region; boundary is provisional.
2. **Identified/decompiled:** role, ABI, and control flow have target evidence.
3. **Mapped:** a durable name/category exists in `reccmp-functions.csv`.
4. **Source-present:** the authored name appears in `implemented.csv`.
5. **Compiles:** a configured VC8 unit builds, but may differ.
6. **Exact:** the canonical comparator reports 100%, recorded in
   `matches.csv` and as `matching` in `functions.csv`.
7. **Excluded:** compiler/runtime/third-party ownership has positive evidence.

No earlier layer implies a later one. In particular, retained old source and
IDA auto-names do not imply mappings or implementations.

## Bounded function loop

1. Read the handoff, inspect Git state, verify target, attest IDA, and run the
   status/ledger checks from `AGENTS.md`.
2. Select one small address or a tightly coupled group. Keep claims header-only.
3. Inspect exact disassembly plus callers, callees, xrefs, strings, globals,
   RTTI/vtables, access widths, cleanup, saved registers, and EH behavior.
4. Reconcile the full target control flow with the candidate extent. Record
   observations, inferences, and unknowns separately.
5. Apply supported names/types in IDA; read them back and update durable ledgers.
6. Recover ABI, layout, ownership, and behavior before code-generation tuning.
7. Select or adapt the smallest natural source implementation. Add it to
   `implemented.csv` only when semantic coverage is supported.
8. Configure one reproducible unit, compile with the pinned VC8 environment,
   and compare the smallest extent first.
9. Add `matches.csv` only after strict zero-difference relocation replay against
   `resources/th105.exe`; update the candidate row at the same time.
10. Run validation/CI, update the handoff, and commit a stable checkpoint.

## Shared-change replay

Headers, class layouts, inline functions, compiler flags, translation-unit
partition, global mappings, and relocation allowlists can invalidate several
accepted objects. Re-run every affected unit immediately. Before reporting
aggregate exact totals, run a cold single-job replay:

```bash
python3 scripts/function-origins.py --check
python3 scripts/verify-exact-units.py --all
```

Reusing prior build products is diagnostic only and cannot support aggregate
claims.

## Analysis lifecycle

- `.analysis/` contains disposable exports, packets, and reports.
- `scripts/export-ida-inventory.py --write` deliberately replaces the entire
  candidate/origin baseline and never merges old status. Use it only for a
  target reset or an explicitly reviewed inventory refresh.
- IDA Pro is the only semantic backend. If it is unavailable or fails exact
  attestation, stop that reconstruction unit rather than substituting another
  analysis database.
- Never patch the original image or commit private databases/logs.

## Target changes

A target hash change invalidates every address, boundary, name, origin rule,
match unit, exact report, and architecture note unless explicitly re-proven.
This rule is why all former 1.06 progress was reset when 1.06a was established.
