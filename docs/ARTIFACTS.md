# Local inputs and disposable outputs

Keep the canonical `resources/th105.exe`, installed pinned toolchains, this
game's Wine prefix and analyzer projects. Shared runtimes are selected through
`.tools/shared-runtimes.json`; see [SHARED_TOOLS.md](SHARED_TOOLS.md).
Keep `.venv` for the pinned repository Python environment.

Current source and exact ledgers live in Git. `config/match-units.toml` and the
repository build/comparison scripts reproduce configured comparisons. Exactness
requires a complete fresh comparison of the affected scope, including owned
extents and relocations. Historical objects or receipts do not replace it.

## Private inputs still in use

- Primary Ghidra project: `.analysis/iku-vslot28-20261002/project/`.
  Preserve other analyzer projects and the pre-analysis project at
  `.analysis/archive-loader-shape-20261019/primary-before/`.
- Six detached worktrees under `.analysis/gptweb_*_wt` contain uncommitted work.
  The old CI checkout at `build/ci-public-checkout-20261024/checkout/` also has
  local edits. Preserve them until their work is reconciled.
- Reimu's linked owner closure under
  `build/reimu-object-owner-closure-20261022/` and its provider inputs retain a
  qualified 48-object compiler context. Related private recipes remain under
  `.analysis/`.
- The unresolved design loader, title acquisition and sprite-options contexts
  remain under `build/frontier-design-real-context-20261102/`,
  `build/frontier-title-acquire-real-graph-20261101/` and
  `build/frontier-sprite-options-source-20261102/`, with matching `.analysis/`
  recipes. Preserve their actual source/provider inputs while the TU/ABI
  questions remain open; see the [current handoff](RE_HANDOFF.md).
- Font native witnesses and execution inputs remain under
  `build/font-markup-stack-20261021/` and `build/font-blend-20261021/`.
  In particular, `local.bin` in the latter is a harness input.

## Routine cleanup

Generated products belong under `build/`; private analysis belongs under
`.analysis/`. Current `build/match-units/` and `build/origin-anchors/` caches are
convenient working outputs. Rebuild the affected units when fresh proof is
needed. Keep reference SDK/library inputs required by the configured tools.

Delete obsolete archives, duplicate evidence, superseded trial outputs and
cleanup reports when they no longer serve a concrete open question. Remove
their documentation references too. A citation alone is not a retention reason.
Record useful conclusions and failed approaches briefly in the relevant topic
note. Do not create another archive, per-file inventory or cleanup report to
justify deleting old output. Preserve a special compiler context only when an
unresolved question actually depends on inputs that are difficult to recreate.
