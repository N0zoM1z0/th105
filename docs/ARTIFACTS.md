# Private artifacts and recovery

Generated products belong under `build/`; private analysis and regeneration
recipes belong under `.analysis/`. Neither directory is part of a fresh clone.
An old report records a particular source/object/tool epoch and never replaces
a fresh canonical comparison. Start with [the current handoff](RE_HANDOFF.md)
and the ledgers before choosing an artifact.

## Retained evidence

Preserve the canonical target, compiler installations, primary analysis
databases, regeneration recipes, and frozen positive/negative inputs. Keep
accepted comparison receipts and the currently selected source/object pins.
Retained old source is evidence of an experiment, not automatically selected
source or an original compiler boundary.

The current ReimuObject scope is `build/reimu-object-fade-order-20261020/`,
with recipes in `.analysis/reimu-object-fade-order-20261020/`. Its selected
and three negative-control objects, native reports and final checks remain
available. Nine primary database hashes are recorded in that scope's
`primary-db-after.json`. The primary project is under
`.analysis/iku-vslot28-20261002/project/`; do not replace or delete it during
routine cleanup.

## October 20 handoff cleanup

The detailed handoff was archived in
[the October 20 snapshot](RE_HANDOFF_HISTORY_2026_10_20.md). Dated experiment
pages retain their original hashes and results, with historical labels and
corrections to unsupported root-return claims. The live handoff supersedes
their priorities, selected pins and negative-control stop conditions.

Cleanup removes disposable Python/test caches and an invalid preliminary
fade-control summary/log. The corrected three-control summary, individual
comparison receipts, objects and recipes are retained. Historical bulk JSON,
assembly listings and logs are compressed with gzip; source, COFF objects,
linked images, compiler files and databases are preserved. Active build
outputs and the current fade-order regression scope are kept uncompressed.

The local inventory and SHA256 receipts are in
`build/handoff-cleanup-20261020/manifest.json`; the exact cleanup recipe is
`.analysis/handoff-cleanup-20261020/cleanup.py`. Every compressed file is
decompressed and checked against its original SHA256 before removal of the
uncompressed copy. This manifest distinguishes compression from cache and
invalid-report removal.

Historical documentation may name an uncompressed report whose local copy
now ends in `.gz`. Restore that file before running a recipe that reads it:

```bash
gzip -dk build/PREVIOUS-SCOPE/REPORT.json.gz
```

The compressed copy remains available. Compare the restored SHA256 with the
cleanup manifest or the dated evidence page. Earlier scopes may also have
their own `artifact-compression.json` receipts. Do not rewrite historical
source/object pins to describe a later source epoch.

## Cleanup boundaries

Remove caches and demonstrably invalid or redundant products first. Compress
large historical reports with integrity receipts instead of discarding their
evidence. Never remove a database, compiler, target image, frozen control or
private recipe merely because it is ignored by Git. Review old detached
worktrees separately; their presence does not authorize another writable
reconstruction session.
