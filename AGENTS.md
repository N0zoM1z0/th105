# TH105 reconstruction agent rules

## Highest priority: lightweight exact reconstruction and useful knowledge

These are the user's current workflow requirements. They override older
instructions that mandate broad CI, repeated preflights, document/source-pin
refreshes, per-checkpoint audits or extra workflow machinery. Preserve the
actual exactness, target identity, natural-source and state-isolation rules.

- Prioritize exact reconstruction and reusable knowledge. Use the shortest
  useful loop: inspect relevant state, analyze/edit, compile and compare the
  affected scope, retain useful learning, and create a coherent checkpoint.
- Use existing repository scripts and composable Bash. Add only the smallest
  change needed for an observed problem. Do not introduce a framework, schema,
  registry, state machine, generalized validator, test family or reporting
  process merely to make a local reconstruction task look more engineered.
- Documentation, knowledge and handoff edits require no compiler, analyzer,
  full CI, cold replay or receipt refresh. Inspect the diff. Check syntax only
  for machine-readable inputs actually changed.
- Source changes need the complete affected exact comparison, including its
  owned extents and relocations. Recheck known consumers of changed shared
  inputs. Tool changes need relevant positive/negative cases and a bounded
  real smoke. Run a broad suite only for an explicit request or a demonstrated
  impact that cannot be narrowed; state that reason first.
- Do not add tests or live freshness gates for prose hashes, prompt wording,
  progress totals, handoff source-SHA tables or ordinary source spelling.
  Bind exact evidence to executable inputs and relevant verification settings.
  Keep Git metadata as provenance. A document genuinely consumed by a build
  remains a build input. Never edit historical receipts to manufacture a pass.
- Plain Markdown is sufficient for knowledge: record the finding, applicable
  target/compiler/scope, evidence links, useful failed attempts and open
  questions. No mandatory JSON conversion, promotion workflow or test per note.
  Search relevant sections; do not read an entire large knowledge journal.
- Write documentation and knowledge in natural, fluent English. Lead with the
  concrete finding and connect the evidence and next action clearly. Remove
  filler, circular restatements, repeated conclusions and unnecessary jargon.
  Do not add defensive-claim boilerplate. State a real uncertainty or scope
  limit once when it changes a decision; do not repeat disclaimers about what
  a note does not prove, certify or authorize. Prefer a small useful note over
  an exhaustive report that is difficult to read.
- Keep handoff focused on current work, evidence references, blockers and the
  next useful action. Generate progress from canonical ledgers; avoid manual
  duplicate counts, recurring full reports and unrelated documentation chores.
- Keep necessary inputs, reproducible current results and concise useful
  knowledge. A documentation citation alone is not a reason to retain a file.
  Delete obsolete archives, duplicate evidence, old trial outputs and cleanup
  reports together with their references. Preserve a special compiler context
  only when an open question depends on inputs that are difficult to recreate.
  Do not create new archives, inventories or cleanup reports to justify deletion.
- Preserve dirty/untracked work, targets, useful evidence, game-specific Wine
  prefixes and analyzer projects. Exactness still requires a complete strict
  comparison; knowledge and successful commands alone confer no exact credit.


Reconstruct only the original Japanese TH10.5 v1.06a executable, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Use `scripts/repo-python` for reconstruction and analysis Python commands;
README.md describes setup, `.python-version` and `scripts/requirements-ci.txt`
pin that environment. Basic CI is the exception: `python3 scripts/ci.py` needs
only Python 3.11+ and the standard library, without `.venv` or analysis packages.

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
python3 scripts/ci.py
```

The finished local gate is required before commit/push/PR; rerun after changes
to source, ledgers, scripts, tests or generated progress. Default CI checks
changed Python/JSON/TOML/shell syntax and staged/unstaged whitespace only.
GitHub Actions uses `--all` to check syntax across tracked files and checks
commit whitespace. Ledger validation, affected exact comparisons and relevant
tool tests run separately when the task requires them. Do not add a routine
test suite, progress freshness check or environment audit to basic CI.
Regenerate progress explicitly when its inputs change.

Update `docs/RE_HANDOFF.md` when phase/blocker changes. Report addresses,
evidence class, changed files, exact result and remaining unknowns. Commit
stable checkpoints before session handoff. Never commit executables, game data,
analysis databases, compiler installs, generated reports, credentials/private
keys or `.tools/mcp_for_gptweb/.env`.

## Shared Factory runtime

Follow [the shared tools instructions](docs/SHARED_TOOLS.md). Ghidra/JDK and
Wine executables are shared through Factory; repository scripts also work
without MCP. Use `scripts/shared_runtime.py` and the existing compiler/analysis
frontends. Keep this game's prefix, analyzer project, Java home/cache, target
and compiler profile isolated. Do not install duplicate tools or inherit
another game's `WINEPREFIX`. This shared-runtime procedure supersedes older
per-repository installation instructions; pinned versions/hashes still apply.
