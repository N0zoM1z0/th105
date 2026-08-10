# TH105 reconstruction agent rules

This repository reconstructs one exact binary: the original Japanese TH10.5
version 1.06a executable whose SHA-256 is recorded in `config/target.toml`.
Do not analyze or substitute a localized executable.

## Before changing code

1. Read `docs/ARCHITECTURE.md`, `docs/RE_WORKFLOW.md`, and the relevant module
   notes.
2. Run `python3 scripts/verify-target.py`.
3. Inspect `config/functions.csv` and `config/claims.csv`. Do not duplicate an
   active claim; use a small address-bounded work unit.
4. Confirm `th105-ghidra` with `codex mcp list`. If necessary, run the protocol
   smoke test documented in `docs/MCP.md`.

## Evidence rules

- Keep facts, inferences, and hypotheses distinct. A plausible decompiler name
  is not a fact.
- Prefer exact target instructions, cross-references, RTTI, vtables, live
  observations, and comparison reports. External projects are supporting
  evidence only.
- Record meaningful names in `config/known-symbols.csv` or directly in the
  function ledger with an evidence pointer. Save corresponding Ghidra changes.
- Never mark a function `matching` from visual similarity. It requires a 100%
  reccmp/object comparison and a reproducible report path or command in the
  `evidence` column.

## Function status model

`config/functions.csv` is the source of truth:

- `unclassified`: inventory only
- `identified`: role/name supported by evidence
- `decompiled`: control flow and types documented, no source implementation
- `implemented`: source exists but does not yet compile in the target build
- `compiles`: included in the target build, not byte-identical
- `matching`: byte-identical under the accepted comparison
- `library`: verified compiler/runtime/third-party code excluded from authored progress
- `blocked`: a concrete blocker is documented

Do not skip directly to `matching`. Update `source_file`, `owner`,
`match_percent`, and `evidence` together with status changes.

## MCP usage

Codex loads the registered `th105-ghidra` server from its user configuration.
Use MCP native tools for decompilation, xrefs, functions, types, comments, and
renames. Always provide `program="th105.exe"`; strict program routing is on.
If an already-running agent session cannot hot-load that registration, use
`.tools/src/ghidra-mcp/.venv/bin/python scripts/mcp-call.py`; it still uses MCP
initialize/list/call over stdio.
The server binds only to loopback. Arbitrary Ghidra script execution remains
disabled in the MCP server; use reviewed scripts under `scripts/ghidra/` via
headless Ghidra when batch behavior is needed.

After changing the Ghidra database, call `save_program`, export the relevant
inventory, and commit the source-side evidence in the same change.

## Parallel work

For two or more concurrent reconstruction lanes, read
`.agents/skills/th105-parallel/SKILL.md` together with the normal `th105-re`
skill. The coordinator owns Ghidra writes, claims, ledgers, inventory exports,
and Git; evidence workers receive non-overlapping address ranges.

## Implementation and verification

- Preserve the expected VC8-era ABI: x86 data sizes, calling conventions,
  class layout, vtable order, exception behavior, and static initialization.
- Keep functions in the module directories described by
  `docs/ARCHITECTURE.md`. Do not create a monolithic catch-all translation unit.
- Build and compare the smallest affected object/function first, then run the
  project-level comparison when the build skeleton supports it.
- Run before handoff:

  ```bash
  python3 scripts/validate-tracking.py
  python3 scripts/progress.py --check
  ```

- Do not commit the original executable, game data, Ghidra project database,
  MCP logs, generated reports, compiler installations, or credentials.

## Handoff

Leave the ledger more precise than you found it. State the address range,
evidence used, files changed, exact comparison result, and remaining blocker.
Release or update the corresponding row in `config/claims.csv`.
