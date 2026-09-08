# Reverse-engineering workflow

The workflow copies TH08's conservative state machine while adapting its
mechanics to TH105's VC8/LTCG executable.

## Sources of truth

- `config/target.toml`: immutable target identity and PE facts.
- verified IDA database: preferred semantic working state, never committed.
- `config/functions.csv`: provisional function candidates and reviewed state.
- `config/function-origins.csv`: generated authored/compiler/library disposition.
- `config/function-origin-rules.toml`: fail-closed current-target origin/exclusion rules.
- `config/xiph-origin-anchors.toml`: relocation-free current 1.06a witnesses against the SHA-pinned official Xiph Win32 SDK; every anchor is revalidated for full-inventory uniqueness before exclusion.
- `config/xiph-relocated-origin-anchors.toml`: strict link-agnostic Xiph witnesses whose supported COFF relocation fields are masked only after boundary/form checks, minimum exact-byte coverage, alignment-tail checks, and full-inventory uniqueness.
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
   compare the smallest extent first, and audit floating relocations with
   `python3 scripts/check-match-literals.py --require-target`.
9. Add `matches.csv` only after strict zero-difference relocation replay against
   `resources/th105.exe`; update the candidate row at the same time.
10. Update the handoff, then run the mandatory final local `python3 scripts/ci.py`
    and `git diff --check` gate. Commit, push, or open a pull request only after
    both commands pass in the finished worktree.

GitHub Actions is a second check, not a substitute for the local gate. Any edit
after the final pass invalidates that pass and requires another local run.

## Giant-root owner diagnostics

For roots covered by `config/giant-action-switches.toml`, pair the target and
candidate span mapper with `scripts/audit-giant-action-owners.py ROOT OBJECT
--unit UNIT`. The latter preserves instruction encodings and compares internal
edges by physical owner plus intra-owner offset; it also traverses raw target
control flow to identify unledgered direct targets and visible indirect-exit
unknowns. A same-sized arm or a higher diagnostic count is never exact credit.
Run the strict full-function comparator independently. See
[GIANT_OWNER_AUDIT.md](GIANT_OWNER_AUDIT.md) for the common Fighter counterexample
and reproducible commands. Public CI dependencies are pinned in
`scripts/requirements-ci.txt`; install them before `scripts/ci.py` on a fresh
Python environment.

For roster Object giant roots, run `scripts/rank-roster-object-shared-callees.py` before decompiling another action family. It discovers direct external callees from raw canonical root bytes and only then annotates candidate/origin state, so missing IDA functions or stale classifications remain visible. Use the result as candidate/primitive evidence only; canonical exact acceptance still requires the normal match unit/comparator.

Candidate-boundary review must also cover indirect/data-driven call surfaces. Run `scripts/audit-roster-primary-vtable-coverage.py` to close the current Fighter/Object primary vtables against candidate starts, and use `scripts/rank-unledgered-rdata-text-pointers.py` to rank aligned canonical `.rdata` pointers that land outside all tracked main spans and reviewed remote chunks. Neither report assigns authored or exact credit. A raw pointer can name a compiler startup thunk, EH helper, deleting destructor, jump-table byte sequence or a real authored virtual/callback. Promote only after raw boundary isolation plus ownership/RTTI/caller evidence; then require the ordinary canonical comparator before exact acceptance. `CSceneManager::initialize @ 0x0041E070` is the current positive example: IDA had no containing function, but RTTI/vtable ownership plus a separately padded 162-byte body established the candidate and ordinary VC8 source subsequently matched 162/162.

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

- Audit direct branch targets that IDA represents only as remote tail chunks. If raw PE shows an independently isolated callable (for example INT3/alignment boundary plus its own return), do not inherit IDA ownership automatically. Split/add a candidate only after control-flow/xref review and an independently reproducible source/object comparison; a tail jump alone proves neither chunk nor separate-function ownership. Conversely, when IDA and target switch edges prove that a source function owns discontiguous executable chunks, record those chunks in `function-byte-ownership.toml` and hash any alignment excluded from the provisional main span. `functions.csv` span length is not authored-byte ownership.
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

### Writable callback-table boundary audit

Direct CALL/JMP closure and RTTI vtables do not cover mutable function-pointer tables. Periodically run `scripts/rank-unledgered-rdata-text-pointers.py --section .data` and inspect uncovered `.text` targets against raw padding, complete return closure, callers/consumers, and library/runtime provenance. Do not auto-promote a pointer target: compiler startup tables and runtime callbacks share the same surface. Conversely, when a writable table is copied into a known callback ABI and raw PE isolates the pointed body, treat that as first-class missed-candidate evidence even when IDA has no function object at the target.
