---
name: th105-parallel
description: Coordinate parallel TH10.5 reverse-engineering agents without corrupting the shared Ghidra project, ledger, or Git history.
---

# TH105 parallel reconstruction

Use this skill together with `th105-re` when a coordinator delegates two or
more bounded TH10.5 reconstruction tasks. It is for this repository and the
target hash in `config/target.toml` only.

## Coordinator ownership

The coordinator is the sole writer for shared state:

- `config/claims.csv`, `config/functions.csv`, known-symbol/global CSVs, and
  generated progress;
- Ghidra rename/type/comment/save operations;
- shared ABI headers, module maps, toolchain configuration, and build scripts;
- Ghidra inventory exports, commits, and pushes.

Workers may inspect all files and the target, but default to analysis-only.
Give a worker a dedicated source subtree only when it is explicitly asked to
implement and no other worker owns that subtree. Workers never commit or push.

## Fast, safe scheduling

1. The coordinator reads `AGENTS.md` and `th105-re`, verifies the target and
   ledger, then partitions by non-overlapping function address ranges.
2. Reserve every selected range in `config/claims.csv` before any mutation.
   One claim can cover a tightly coupled accessor group; never claim a broad
   subsystem without concrete addresses.
3. Start at most one persistent loopback GhidraMCP server for the shared
   project. Workers use the existing `th105-ghidra` server through MCP; they do
   not start alternative servers against the same project or run inventory
   export while it is live.
4. Use parallel workers first for evidence gathering. Each should batch its MCP
   calls in one `scripts/mcp-call.py` session to avoid startup overhead.
5. The coordinator selects only evidence-backed candidates, applies Ghidra
   mutations in a short serial batch, calls `save_program`, then stops the
   server before `scripts/export-function-inventory.sh`.
6. Compile and compare each selected function independently. Update the ledger,
   regenerate progress, run lightweight checks, release claims, then commit.

Four concurrent evidence workers is normally enough: Ghidra decompilation is
server-serialized enough that more workers usually add queueing rather than
throughput. Add an implementation worker only after a clear interface and
source ownership are known.

For the current Codex setup, a productive default is one coordinating agent
plus four `gpt-5.6-terra` workers at `high` reasoning. The workers gather and
challenge evidence; the coordinator performs source integration, Ghidra
writes, comparisons, ledger updates, and Git operations. Prefer reusing a
completed worker for the next address-bounded lane because it retains the
relevant class/layout context.

## Gameplay-first scheduling

Unless the user requests otherwise, prioritize the core gameplay map in
`docs/BATTLE.md` ahead of UI, audio, menu, and input plumbing:

1. collision geometry and small no-relocation leaves;
2. attack/hurtbox intersection primitives;
3. projectile/object clash and attack-vs-fighter dispatch;
4. character action, physics, and timer phases;
5. collision-list orchestrators and the battle state machine after their leaf
   contracts are stable.

A high-throughput four-lane wave is:

- **A / exact probe**: one or two small leaves and their immediate callee;
- **B / layout**: the shared `AttackObject`/`CharacterObject` fields used by a
  tightly bounded hitbox cluster;
- **C / semantics**: defensive and hit-result dispatch, with game terms kept
  inferred until flags or runtime behavior prove them;
- **D / hard path**: recover or shape one central orchestrator, large geometry
  builder, or response cascade using the current complete leaf/layout evidence.

This produces source matches and the layouts needed for the next wave at the
same time. Every wave should include at least one hard-path lane; do not spend
all workers scanning arbitrary short functions. Short leaves are preferred
when they unblock a core ABI, relocation, or call path rather than only
increasing the counter.

Before assigning source-shaping work, route the worker through the diagnosis
table in `../th105-re/references/exact-matching-patterns.md`. The handoff should
name the applicable pattern IDs (for example P3/P6/P11) and the first mismatch,
so the next worker does not repeat already classified experiments.

## Shared MCP lifecycle

When workers need a stable shared server, the coordinator starts exactly one
in a coordinator-owned foreground execution session:

```bash
env TH105_JAVA_HOME=/usr/lib/jvm/java-21-openjdk-amd64 \
  scripts/ghidra-mcp-server.sh
```

Keep that execution session open, verify `/get_metadata` names `th105.exe`, and
give workers read-only MCP briefs. A detached `nohup` process is not reliable in
all agent runtimes and can race worker launchers for the project lock. Before
headless inventory export, wait for every worker, call `save_program`, send
Ctrl-C to the coordinator-owned session, verify port 8089 is closed, then run
`scripts/export-function-inventory.sh`. Never use a broad `pkill` pattern and
never export while the server owns the project.

## Recommended lanes

- **Reconnaissance**: caller/callee/xref/RTTI/string/global evidence for an
  address range. No writes.
- **Accessor cluster**: small neighboring routines returning or setting known
  globals. Return exact instructions and candidate VC8 bodies.
- **Class/layout**: one RTTI/vtable family and its constructor/update roots.
  Return field-offset evidence; do not make layout headers yet.
- **Verifier**: independently challenge a proposed name/signature using target
  instructions and callers. No writes.

Keep direct dependencies in the same lane. Do not split a constructor and its
vtable/layout recovery across workers without an explicit handoff.

## Worker brief

Every delegated brief must contain:

1. exact addresses and an exclusion range owned by another worker;
2. whether the worker is analysis-only or its allowed source subtree;
3. mandatory `program="th105.exe"` MCP selector;
4. a prohibition on ledger/Ghidra/Git mutation unless explicitly delegated;
5. expected output: instructions, callers/xrefs, globals/offsets, confidence,
   candidate signature/body, byte-match feasibility, and unresolved points.

Workers label every conclusion **Observed**, **Inferred**, or **Hypothesized**.
They must not convert a decompiler label into an original-source claim.

## Handoff format

Return one compact record per address:

```text
0x00400000 | proposed_name | Observed/Inferred/Hypothesized
Instructions: ...
Evidence: callers/xrefs/globals/RTTI/strings ...
Candidate ABI/body: ...
Match path: object command or why not yet feasible
Unknowns: ...
```

The coordinator independently reproduces the code-generation result before
marking `matching`. Object-level byte equality is a fast local acceptance
signal; retain the limitation that the final reconstructed executable needs
reccmp confirmation when an executable build exists.

## Finish

Before handoff, the coordinator stops or waits for workers using Ghidra, then
runs the normal tracking/progress checks. A commit must identify the address
range, evidence, exact comparison result, and remaining uncertainty. Verify
the local Git author before pushing.
