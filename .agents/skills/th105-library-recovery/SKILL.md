---
name: th105-library-recovery
description: Recover verified compiler/runtime or third-party library islands in the original Japanese TH10.5 v1.06a executable efficiently. Use when classifying a suspected library range, identifying an exact upstream release, compiling public sources with VC8, mapping COFF relocations, strictly comparing library functions, or reporting reproducible library bytes without contaminating authored-game progress.
---

# TH105 Library Recovery

Use a fail-closed, breadth-first pipeline for code that is proven to come from a
compiler runtime or public third-party library. Recover provenance and build
configuration once, then fan the result out across the whole library island.

Read `.agents/skills/th105-re/SKILL.md` first. Also read
`.agents/skills/th105-matching/SKILL.md` before any strict comparison or ledger
status update. Repository `AGENTS.md` and `config/functions.csv` remain
authoritative.

## Safety and accounting invariants

- Analyze only the target accepted by `python3 scripts/verify-target.py`.
- Run `python3 scripts/check-ida-mcp.py` before using IDA; fall back according to
  `docs/MCP.md` when the preflight fails.
- Treat a version string, function size, decompiler resemblance, or upstream
  source match as candidate evidence, never as an exact result.
- Keep verified external functions at `status=library`. Do not reclassify them
  as `matching` to raise authored-game progress.
- Set a library row's `match_percent` to `100.00` only after the accepted strict
  comparator reports an exact whole-function match. Record the exact command or
  durable report in `evidence` together with `source_file` and `owner`.
- Keep authored exact bytes and reproducible library bytes as separate metrics.
- Never commit target binaries, analysis databases, compiler installations, or
  disposable upstream build trees.

## Workflow

### 1. Preflight and bound the island

Run:

```bash
python3 scripts/verify-target.py
python3 scripts/function-origins.py --check
python3 .agents/skills/th105-library-recovery/scripts/audit-library-island.py \
  --evidence-id zlib-1.2.3 --top 15
```

Inspect `config/functions.csv`, `config/function-origins.csv`,
`config/function-origin-rules.toml`, and `config/claims.csv`. Claim a small,
address-bounded unit before changing functions, source, or ledger rows. Do not
claim the full island merely to run read-only probes.

The origin rule must be fail-closed: exact address set or range, expected row
count, expected byte total, provenance, confidence, and an evidence pointer.

### 2. Establish the upstream release

Prefer, in order:

1. embedded release/version strings;
2. public API and diagnostic strings;
3. exact constants, tables, and function-size fingerprints;
4. call-graph shape and compiler idioms;
5. external projects only as supporting evidence.

Build a small version matrix using public entry points before compiling the
whole library. Keep facts, inferences, and hypotheses visibly distinct. If the
release is unresolved, leave it unresolved and test multiple official tags.

### 3. Compile one upstream translation unit with VC8

Clone or unpack official upstream source under `/tmp`. Preserve the exact tag
and commit identifier in the evidence notes. Compile the smallest translation
unit first:

```bash
.agents/skills/th105-library-recovery/scripts/compile-upstream-vc8.sh \
  /tmp/upstream/zlib/inflate.c /tmp/th105-lib/inflate.obj \
  --include /tmp/upstream/zlib
```

The helper uses the repository VC8 SP1 toolchain and the fast non-LTCG probe
configuration `/O2 /GS- /MT`. Vary one build option at a time when target
evidence requires it. Do not vendor upstream code until its exact release,
license, and repository placement are decided.

### 4. Form candidates breadth-first

Use COFF section sizes, symbols, target ledger sizes, and call relationships to
form a candidate matrix. Start with distinctive public wrappers and lifecycle
functions, then recover internal helpers and static data. Exact size is a
strong filter, not proof.

Prioritize:

1. configuration and version anchors;
2. small wrappers that reveal REL32 target mappings;
3. initialization/destruction functions that reveal object layout;
4. large same-sized functions gated only by relocations;
5. near-size functions requiring source/configuration archaeology.

### 5. Compare strictly and resolve relocations fail-closed

Run the repository comparator against one COFF symbol and one target address:

```bash
python3 scripts/compare-function.py 0x00664FA0 /tmp/th105-lib/inflate.obj \
  --symbol-base _inflateReset
```

- Map calls with `--rel32-target NAME=ADDRESS` only after the callee identity is
  independently supported.
- Map static data with `--dir32-target COFF_SYMBOL=ALLOWLIST_KEY` only after the
  target bytes/address are audited in `config/reccmp-relocations.csv`.
- Treat local helper, jump-table, string, and constant relocations as distinct
  evidence tasks.
- Stop on the first unexplained relocation or byte mismatch. Never wildcard a
  relocation or patch target bytes.

Read `references/library-recovery-patterns.md` for the validated zlib pilot,
failure taxonomy, Xiph version-fingerprint plan, and handoff template.

### 6. Fan out only after an audited anchor

After at least one strict exact anchor proves release and compiler settings,
compile the neighboring translation units and distribute non-overlapping
function probes. The coordinator alone updates claims, ledgers, analysis
databases, generated inventories, and Git during parallel work.

For each result, record one of:

- exact: strict 100%, reproducible command/report;
- relocation-gated: code shape and size agree, named mapping still unverified;
- configuration-gated: likely upstream source, compile options/macros differ;
- release-gated: exact upstream version is unresolved;
- source-divergent: evidence shows a patch or materially different source;
- identity-unresolved: target address or function boundary is uncertain.

### 7. Validate and hand off

Before handoff run:

```bash
python3 scripts/validate-tracking.py
python3 scripts/function-origins.py --check
python3 scripts/core-worklist.py --check
python3 scripts/progress.py --check
```

State the island/range, upstream tag and commit, compiler flags, exact functions
and bytes, unresolved categories, files changed, comparator commands/reports,
and released or updated claims.

## Bundled resources

- `scripts/audit-library-island.py`: join origin and function ledgers, verify
  order, measure an island, list largest byte targets, and report exact-library
  bytes separately from authored matching.
- `scripts/compile-upstream-vc8.sh`: compile an external C/C++ source file with
  the repository VC8 SP1 toolchain and explicit include directories.
- `references/library-recovery-patterns.md`: empirical TH105 zlib results,
  candidate/failure patterns, Xiph strategy, and evidence templates.
