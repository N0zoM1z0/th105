# TH105 reconstruction agent rules

This repository reconstructs one exact binary: the original Japanese TH10.5
version 1.06a executable whose SHA-256 is
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Do not analyze or substitute 1.06, a localized executable, or another patch.

## Before changing reconstruction state

1. Read `docs/RE_HANDOFF.md`, `docs/ARCHITECTURE.md`,
   `docs/RE_WORKFLOW.md`, and the relevant source.
2. Inspect `git status`, then run:

   ```bash
   python3 scripts/verify-target.py
   python3 scripts/check-ida-mcp.py
   python3 scripts/report-reconstruction-status.py --summary
   python3 scripts/validate-tracking.py --require-target
   ```

3. Confirm the address in `config/functions.csv`. Its IDA size is provisional;
   reconcile the complete control flow before accepting a compiler boundary.
4. Confirm any durable name in `config/reccmp-functions.csv` and any source
   selection in `config/implemented.csv`. Neither is an exact-match claim.
5. Build and compare the smallest affected object/function before broad edits.

## Evidence and state

- Keep exact target observations, inferences, external corroboration, and
  unknowns distinct. Never mechanically paste decompiler output as source.
- The source tree predates the corrected target. Treat every retained source
  file as an unverified hypothesis until 1.06a instructions and ABI support it.
- `config/functions.csv` is the candidate/boundary ledger.
  `config/function-origins.csv` separately classifies authored, compiler, or
  library ownership. IDA auto-analysis proves neither.
- `config/implemented.csv` means source-present only.
- `config/matches.csv` means a canonical 100% result against the exact target.
  A mapping, build success, visual similarity, or stale 1.06 report is not
  matching evidence.
- Record exact results only with a unit in `config/match-units.toml` and a
  reproducible command/report reference.

## Analysis database safety

IDA MCP is attached to the file open in the GUI and has no program selector.
Re-run `scripts/check-ida-mcp.py` at the start of every bounded work unit. It
must attest target metadata, entry point, mapped bytes, required tools, and a
function-inventory probe. Never call `patch_address_assembles` or patch target
bytes.

IDA Pro is the only semantic-analysis backend for this repository. If its
preflight cannot pass, stop semantic reconstruction and report the blocker;
do not substitute Ghidra or another database. The IDB is working state, not the
durable record: mirror accepted names, types, boundaries, and evidence into the
repository ledgers. Read back IDA writes before relying on them.

## TH105 ABI and architecture

- Preserve the Visual C++ 2005 x86 ABI: calling conventions, field widths,
  class layout, vtable order, RTTI/EH behavior, static initialization, and
  object ownership.
- Rich-header evidence includes 42 VC8 C++ LTCG records. Do not assume every
  function has a recoverable standalone COFF/TU boundary or that TH08's VC7
  compiler behavior transfers.
- TH105 is a networked fighting game with extensive polymorphic C++ and
  character/object families. Use the TH08 control-plane discipline, not its
  gameplay architecture, source partition, addresses, or pattern conclusions.
- Do not use assembly, copied byte arrays, inert locals, fake returns, ABI
  lies, or padding to force a comparison.
- Keep generated files below `build/` and private analysis below `.analysis/`.

## Single-agent sessions

- Use one writable reconstruction session at a time. Do not delegate
  reconstruction/matching to subagents or run concurrent VC8 builds.
- `config/claims.csv` is schema-compatible and must remain header-only.
- Keep one bounded address or one coherent workflow-maintenance batch in
  flight. Commit stable checkpoints before a browser/session handoff.
- Re-run all affected accepted units after any shared header, type/layout,
  compiler-flag, object partition, or relocation-ledger change. Aggregate exact
  totals require a cold `python3 scripts/verify-exact-units.py --all` run.

## Handoff

Run the focused build/comparison, then:

```bash
python3 scripts/ci.py
git diff --check
```

Update `docs/RE_HANDOFF.md` when the phase or blocker changes. Report target
addresses, evidence class, changed files, exact result, and remaining unknowns.
Do not commit executables, game data, analysis databases, compiler installs,
generated reports, credentials, private keys, or `.tools/mcp_for_gptweb/.env`.
