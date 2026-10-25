# Private artifacts and recovery

Generated products belong under `build/`; private analysis and recipes belong
under `.analysis/`. Neither is included in a fresh clone. Start from the
[current handoff](RE_HANDOFF.md) and live ledgers: old reports retain their
source/object/tool epoch and cannot substitute for a fresh comparison.

## October 25 cleanup and handoff

The user requested cleanup and a new-agent handoff. Current state is summarized
in [RE_HANDOFF.md](RE_HANDOFF.md); its full preceding1582-line chronology is
preserved in [the dated archive](RE_HANDOFF_HISTORY_2026_10_25.md). The active
Tenshi partial draft and target observations remain in their original private
paths. No game source, ABI, compiler profile or acceptance ledger changed.

Four disposable cache/test-environment directories were removed:
`build/pycache`, `build/ci-public-checkout-20261024/checkout/.venv`, that checkout's
`build/pycache`, and `.tools/ci-public-python311`. Their157,085,867 logical bytes
(about149.8MiB) are recorded in per-file hashed inventories. The active `.venv`
and its external UV CPython3.11.14 installation remain intact. Recreate historical
test environments with the README's version/dependency pins when needed; normal
Python commands regenerate bytecode automatically.

Two download caches were also removed after comparison with installed tools:
Objdiff3.8.0 was byte-identical to `.tools/objdiff/objdiff-cli`; all
96 regular Maven3.9.16 archive members matched the installed tree. The installed tools
remain available. These cache byte figures are file-size totals, not a claim
about uniquely allocated hard-linked disk blocks.

Git was repacked serially with `--keep-unreachable`, without expiring reflogs or
pruning objects/worktrees. Its directory shrank from roughly76MiB to12MiB;
all16,988 object IDs, refs, six dirty worktree states and retained files were
verified afterward; `git fsck --full` passed. Git's automatic abbreviated-index
format changed after repack: all prior patches reproduce exactly with
`--abbrev=7`, and canonical full-index patch hashes are now recorded. This was
an output-format change, not a source mutation.

The manifest is `build/handoff-cleanup-20261025/manifest.json`; the private
one-use cleanup/finalization recipes are under `.analysis/handoff-cleanup-20261025/`.
All55,424 protected file hashes were unchanged, including both database locations,
compiler/analysis installations, accepted receipts, frozen controls and the active
Python environment. Existing historical reports/objects were retained directly.
No dirty worktree was removed and no reconstruction process was left running.

The31 active Tenshi files additionally have a verified262512-byte portable copy:
`build/handoff-cleanup-20261025/tenshi-resume.tar.gz`, SHA-256
`9e28ae84cac98d8b96a102901b29dbbd0250d0c32fee74119913eab674c3d6ff`.
`tenshi-resume-members.json` records every repository-relative member and hash.
List the bundle before restoring needed members with `tar -xzf ... -C .`;
do not overwrite newer work. This ignored local bundle is not supplied by a Git
clone and excludes executable, compiler and primary database files.

## October 23 handoff refresh

The [live handoff](RE_HANDOFF.md) now distinguishes current selection from
completed experiments. [AyaObject evidence](AYA_OBJECT_EVIDENCE.md) collects
the dated results; the completed [size-profile controls](AYA_OBJECT_SIZE_PROFILES_2026_10_23.md)
remain unselected. No game source, ABI, compiler profile or acceptance ledger
changes accompany this refresh.

Private cleanup inventory and recipe:
`build/handoff-refresh-20261023/manifest.json` and
`.analysis/handoff-refresh-20261023/cleanup.py`. Historical diagnostic logs and
assembly listings are gzip-compressed only after a verified lossless readback.
Frozen source/objects, link maps, formal receipts, current scopes, compiler
installs, target, databases and all six dirty worktrees remain directly available.
Git objects are repacked with pruning and reflog expiration disabled; all
preexisting object IDs, refs and worktree states are checked afterward.

322 historical exports shrink from 5,770,730 to 954,388 bytes, saving
4,816,342 bytes before cleanup metadata. Git's allocated directory shrinks
from roughly 113 MiB to 12 MiB; all 15,191 objects remain present. Its former
100.44 MiB of loose objects is packed, with total packs growing only from
9.32 to 9.89 MiB. These Git figures are rounded, not an exact combined byte total.
The manifest references `protected-inputs.json.gz`, a verified shared snapshot
of 41,017 hashes. Source-backed Python bytecode caches were also removed;
repeated receipt inventories share that snapshot to avoid new duplication.

## Earlier October 23 handoff cleanup

The live handoff now lists selected source, current hashes, open questions and
resume commands. The [preceding handoff](RE_HANDOFF_HISTORY_2026_10_23.md) and
[preceding artifact notes](ARTIFACTS_HISTORY_2026_10_23.md) retain earlier detail.
The earlier Aya owner-context experiment is recorded in a
[dated evidence report](AYA_OBJECT_RUNTIME_CONTEXT_2026_10_23.md); all four
controls are byte-neutral and selected game source is restored. No source,
ABI, compiler profile or acceptance-ledger change accompanies cleanup.

108 historical diagnostic reports were losslessly compressed from 21,508,505
to 1,775,207 bytes. Each gzip was read back and SHA256-checked before the
original was removed. Formal/selected receipts, frozen source/objects, current
Aya runtime-context and regression scopes, references and match-unit outputs
remain directly available. Older private diagnostic exports can now also have
`.gz` suffixes; database storage and frozen input ledgers were excluded.

The redundant 567,828,511-byte Ghidra download ZIP was removed after all 5,215
archive members were individually SHA256-compared to the installed files.
The installation is intact. Its inventory, archive SHA256 and verification are
in `build/handoff-cleanup-20261023/ghidra-install-check.json`.
Compression and duplicate-download removal save 587,561,809 bytes before cache
cleanup. Disposable Python/ruff caches are removed after final verification;
the separate `cache-cleanup.json` records those bytes and protected hash checks.

The private recipe is `.analysis/handoff-cleanup-20261023/cleanup.py`;
`build/handoff-cleanup-20261023/manifest.json` records every compressed path,
original hash, byte totals and 2,230 protected input hashes. Target, source,
scripts, tests, ledgers, match-unit files, VC8 references and both primary DB
locations passed before/after checks. All six dirty detached worktrees were
left intact. No target, compiler installation, database or frozen control was
discarded. Historical cleanup counts are not cumulative totals for this pass.

## Restore a historical report

```sh
gzip -dk build/PREVIOUS-SCOPE/REPORT.json.gz
# The same operation applies under .analysis/.
```

Compare the restored SHA256 to the relevant cleanup manifest. The compressed
copy remains available. Restore only the reports needed by the old recipe;
current canonical comparisons always use fresh configured builds.

Some completed controls have per-scope tar archives rather than individual
gzip files. List the archive and consult its `retention.json` for member paths
and hashes before restoring into the documented directory:

```sh
tar -tzf build/font-markup-stack-20261021/completed-controls.tar.gz
tar -xzf build/font-markup-stack-20261021/completed-controls.tar.gz \
  -C build/font-markup-stack-20261021 stdcall.obj
```

`build/aya-801-sequence-20261023/completed-controls.tar.gz` uses repository-relative
paths; restore its needed members with `-C .`. The latest
`aya-owner-context-20261023` controls remain loose. Their CPPs require their
matching frozen owner header when recompiling; see the dated report.

## Preserve these inputs

Keep the canonical target, compiler installations, primary databases, recipes,
frozen positive/negative controls, accepted comparison receipts and current
source/object pins. Ignored files can still be essential evidence.

The primary Ghidra project is
`.analysis/iku-vslot28-20261002/project/`; the retained pre-analysis snapshot is
`.analysis/archive-loader-shape-20261019/primary-before/`. Do not replace or
remove either during routine cleanup. A database remains usable only after
independent target attestation.

Keep current linked owner inputs/images under
`build/reimu-object-owner-closure-20261022/` and their provider scopes.
Its completed-controls archive contains unused earlier inputs, not the active
48-object image. Keep accepted animation/render receipts and selected objects.
The October 21 font checkpoint remains under `build/font-markup-stack-20261021/`;
its native library witness, selected objects, target/canonical bodies, EH facts
and execution receipts are retained. `build/font-blend-20261021/local.bin` is
an execution-harness input, not disposable output.

Six older detached worktrees contain uncommitted work. Their presence does not
authorize parallel writable reconstruction, and they need separate review
before removal. See the historical artifact notes for October 20–22 scopes,
archive-specific restoration and earlier per-file manifests.
