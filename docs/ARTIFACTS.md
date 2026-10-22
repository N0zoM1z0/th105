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

The retained October 21 font checkpoint is `build/font-markup-stack-20261021/`,
with recipes in `.analysis/font-markup-stack-20261021/`. Keep its selected
public/Cdecl objects, extracted native `vc8-string.obj`, target/canonical bodies,
formal comparisons, caller/stack/EH/library facts and execution receipts.
Its `retention.json` inventories the SHA-verified `completed-controls.tar.gz`.
The preceding `font-markup-local-20261021` and `font-setter-local-20261021`
scopes also retain selected objects, frozen inputs and per-file archive receipts.
`build/font-blend-20261021/local.bin` is an actual execution-harness input.

The retained October 21 ReimuObject source selection is documented by
`build/reimu-object-811-arguments-20261021/`; the earlier fade-order scope
retains its source epoch and controls. Nine primary database hashes remain in
`build/reimu-object-fade-order-20261020/primary-db-after.json` and were checked
again during this cleanup. The primary project is under
`.analysis/iku-vslot28-20261002/project/`; do not replace or delete it during
routine cleanup. The read-only interrupted `font-markup-lifetime-20261021`
scope retains a fresh baseline and constructor-call census, without a selected
source/layout change. At that October 21 checkpoint reconstruction was paused
and no build was pending. The live handoff supplies the current active phase.

## October 21 paused-session cleanup

The previous 845-line handoff is preserved verbatim in
[the October 21 snapshot](RE_HANDOFF_HISTORY_2026_10_21.md), with a historical
warning. [The live handoff](RE_HANDOFF.md) now lists current source entry points,
accepted versus diagnostic comparisons, blockers and focused reproduction.
No reconstruction source, header, profile, tracking or progress edit is made.

The cleanup compresses 287 completed October 20/21 JSON reports, text listings
and logs of at least 32 KiB, saving 28,610,196 bytes; it also removes 187,096
bytes of disposable Python cache. Every compressed file is read back and
SHA256-checked before unlinking its original. Formal comparisons, retention
receipts, source, frozen input ledgers, objects and binaries remain directly
available. Current markup-stack/local/lifetime and Reimu811 reports are kept
uncompressed. Target, selected source/objects and all nine primary DB hashes
are checked before and after; detached worktrees and tool installations are
untouched. Final CI caches can be removed again after verification.

The private inventory is `build/handoff-cleanup-20261021/manifest.json`; the
one-use recipe is `.analysis/handoff-cleanup-20261021/cleanup.py`. The fresh
font baseline reproduces all 12 selected comparison results and canonical
hashes, including the three accepted leaves and the uncredited 33-byte helper.
No additional VC8 build or aggregate replay is needed for documentation cleanup.

Restore a historical compressed report before an old recipe reads it:

```bash
gzip -dk build/PREVIOUS-SCOPE/REPORT.json.gz
```

For archived completed controls, restore only the needed members into the
same original scope, then verify their hashes against `retention.json`:

```bash
tar -tzf build/font-markup-stack-20261021/completed-controls.tar.gz
tar -xzf build/font-markup-stack-20261021/completed-controls.tar.gz \
  -C build/font-markup-stack-20261021 stdcall.obj
```

Keep both compressed/archive copies. Reports and private inputs are local;
a fresh clone requires the canonical target and pinned tools, then a fresh
configured build rather than an old receipt.

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
outputs and the then-current fade-order regression scope were kept uncompressed
at that checkpoint. Some historical reports in that scope were compressed in
the October 21 cleanup; its source, objects and evidence remain recoverable.

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
