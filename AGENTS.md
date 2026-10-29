# TH105 reconstruction agent rules

Reconstruct only the original Japanese TH10.5 v1.06a executable, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Use `scripts/repo-python` for repository Python commands; README.md describes
setup, `.python-version` and `scripts/requirements-ci.txt` pin the environment.

## Work loop

Read `docs/RE_HANDOFF.md` and the relevant source. Consult
`docs/ARCHITECTURE.md` and `docs/RE_WORKFLOW.md` for unfamiliar boundaries/ABI.
Inspect `git status` before editing; preserve other sessions' changes.
For reconstruction or ledger changes, run:

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/validate-tracking.py --require-target
```

Confirm the address in `config/functions.csv`, any durable name in
`config/reccmp-functions.csv`, and source selection in `config/implemented.csv`.
Candidate sizes are provisional: reconcile complete control flow before
accepting a compiler boundary. Compile and strictly compare the complete
bounded function early, then change one target-backed source property per trial.
Documentation/test-workflow maintenance needs no target/IDA preflight or native
build.

## Exact-first validation

- Acceptance is zero byte differences against the canonical target, with a
  reproducible unit in `config/match-units.toml` and command/report evidence.
- Do not require allocation-failure, null-pointer, fuzz, broad runtime or
  gameplay matrices. Preserve the target's actual guards/EH paths; do not add
  defensive behavior absent from the target.
- Use bounded diagnostics only for a concrete uncertainty blocking comparison.
  Analysis/probe tests are optional; run relevant tests when their tools change.
- Do not pin progress totals, historical checkpoint status or source spelling
  in tests. Ledgers and canonical receipts record those facts.
- Compare the new unit and directly affected accepted consumers. Review consumers
  after shared header/layout/flag/TU/global/relocation changes. Preserve unchanged
  receipts and report totals as incremental validation.
- Full `scripts/repo-python scripts/verify-exact-units.py --all` requires an
  explicit user request or demonstrated repository-wide invalidation that cannot
  be narrowed. State the reason first; zero-difference acceptance stays unchanged.

## Evidence and ABI

Keep target observations, inferences, external corroboration and unknowns
separate. Decompiler output and unreviewed retained 1.06 source are hypotheses.
`functions.csv` records candidates/boundaries; `function-origins.csv` separately
records authored/compiler/library ownership. Auto-analysis proves neither.
`implemented.csv` means source-present; only `matches.csv` records exactness.
Mapping, compilation, similar output or stale 1.06 reports confer no exact credit.

Preserve VC8 x86 calling conventions, field widths, class/vtable layout,
RTTI/EH, static initialization and ownership. The target has 42 C++ LTCG Rich
records; standalone COFF/TU boundaries may be unrecoverable. TH08's gameplay
structures, addresses and VC7 compiler behavior do not transfer automatically.
Never force comparison with assembly, copied bytes, inert locals, fake returns,
ABI lies or padding.

## Analysis sessions

Use one bounded writable reconstruction scope or coherent maintenance batch.
Do not delegate reconstruction/matching or run concurrent VC8/Ghidra jobs.
`config/claims.csv` remains header-only. Preserve other worktrees and private
analysis state; generated files belong under `build/`, private analysis under
`.analysis/`.

Prefer the registered Factory-native IDA provider. Before using its semantics
in a bounded scope, discover its allowlisted operations and verify the active
metadata hash/size/base, entry point, the five mapped-byte samples defined in
`scripts/check-ida-mcp.py`, and a function inventory/disassembly/decompiler/
callers/callees probe. Compare sampled bytes with the pinned raw PE and retain
the Factory responses privately. Factory's metadata-only attestation alone is
not a mapped-byte check. See `docs/FACTORY_IDA_2026_10_29.md`.

`scripts/check-ida-mcp.py` remains the preflight for the legacy repository
bridge. Its failed session is blocked; it is not a requirement to install that
bridge's Python runtime when the independent Factory-native session passes the
same checks. A failed active-target/byte check blocks the affected analysis
session; hash-attested raw PE analysis remains available.
Ghidra requires independent imported-file, entry-point and mapped-byte checks
against `resources/th105.exe`. Never patch target bytes or call
`patch_address_assembles`. Mirror accepted database names/types/boundaries into
repository evidence and read back metadata writes.

## Handoff and commit

Use `gpt-dots: <summary>` for new commit subjects (user instruction,
2026-10-29). Older prefixes in archived notes are historical, not current
submission rules. Do not rewrite existing commits merely to change their prefix.

For reconstruction changes, run focused affected comparisons, then:

```bash
scripts/repo-python scripts/ci.py
git diff --check
```

The finished local gate is required before commit/push/PR; rerun after changes
to source, ledgers, scripts, tests or generated progress. Default CI validates
ledgers, match units and exact-comparison tooling; it does not rebuild native
units or run all analysis tests. `scripts/ci.py --all-tests` is optional for
broader tooling changes. Regenerate progress explicitly when inputs change;
CI only checks it.

Update `docs/RE_HANDOFF.md` when phase/blocker changes. Report addresses,
evidence class, changed files, exact result and remaining unknowns. Commit
stable checkpoints before session handoff. Never commit executables, game data,
analysis databases, compiler installs, generated reports, credentials/private
keys or `.tools/mcp_for_gptweb/.env`.
