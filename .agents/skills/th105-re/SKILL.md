---
name: th105-re
description: Reverse engineer and byte-match functions in the original Japanese TH10.5 v1.06a executable using verified IDA Pro MCP first, the repository Ghidra MCP fallback, and the authoritative function ledger.
---

# TH105 function reconstruction

Use this skill only inside this repository and only for the target hash in
`config/target.toml`.

## Select a bounded task

1. Read `AGENTS.md` in full.
2. Run `python3 scripts/verify-target.py` and
   `python3 scripts/validate-tracking.py`.
3. For gameplay-first work, run `python3 scripts/core-worklist.py --ready` and
   inspect `docs/CORE_FRAMEWORK.md`. Choose an unclaimed row from
   `config/functions.csv`, preferably a ready dependency frontier or a central
   hard function in the same lane.
4. Record the claim in `config/claims.csv` before editing shared source.

## Select the analysis backend

Run `python3 scripts/check-ida-mcp.py`. When it passes, use IDA Pro MCP first
for semantic analysis. Recheck metadata for every bounded work unit because
IDA is attached to the GUI's current file and has no program selector. If IDA
is unavailable or lacks a required read tool, use the Ghidra MCP fallback with
`program="th105.exe"` on every program-scoped call.

IDA function chunks and sizes are not inventory evidence. Reconcile the entry,
ledger `size`/`span_end`, and target instructions before using a decompile. The
`0x0046A5B0` tail wrapper and separate `0x00463610` body are the mandatory
regression case. Never call `patch_address_assembles` or patch target bytes.

Read [`../../../docs/IDA_MCP.md`](../../../docs/IDA_MCP.md) for routing,
protocol-native fallback calls, database-write safety, and analysis imports.
When importing a prior Ghidra project, export it with the repository's
headless `-readOnly -noanalysis` bundle path. Never launch the Ghidra GUI for
that transfer and never import unreviewed Windows/CRT placeholder types into
IDA as gameplay structures.

## Establish behavior

With the selected verified backend, start with:

1. `get_function_by_address`
2. `decompile_function`
3. incoming/outgoing xrefs and callers/callees
4. relevant strings, globals, vtable slots, RTTI, and neighboring functions

IDA uses `disassemble_function`, while Ghidra exposes corresponding
disassembly operations. Apply types and names only when supported. Record the evidence source and
confidence. Do not treat external layouts or later-game code as authoritative.
When a result changes a core call dependency or a complete/partial type
boundary, update `config/core-dependencies.csv` or `config/core-types.csv` in
the same handoff. Use declarations for not-yet-implemented functions; never add
fake behavioral stub bodies.

## Reconstruct and compare

1. Place code in the module indicated by `config/modules.toml`.
2. Preserve calling convention, object layout, side effects, and initialization
   order before attempting expression-level compiler tuning.
3. Before source shaping, read the relevant symptom section in
   [`references/exact-matching-patterns.md`](references/exact-matching-patterns.md).
   Start from its diagnosis table; do not repeat random variants when the
   mismatch is already a known ABI, relocation, x87, TU, or checked-STL pattern.
4. Compile the smallest unit supported by the current build.
5. Compare one function with `scripts/compare-function.py`; use objdiff for
   iteration and executable-level reccmp when that build stage exists.
6. Save generated reports under `build/` and put the reproducible command in
   the function row.

Status may become `matching` only at 100% under the accepted comparison. Use
`implemented` when source exists but is not in the target build, and `compiles`
only when it is included in that build but differs. For non-exact hard
functions, record target/object sizes, first mismatch, shaping class, and the
next bounded experiment rather than inventing a percentage. Update progress
and release the claim at handoff.

## Reuse learned patterns

When a new exact match reveals a reusable technique, update the pattern catalog
in the same change if it would save another agent meaningful retries. Include:

- the observable mismatch symptom;
- the source or build technique that fixed it;
- one repository address and reproducible command;
- limits and cases where the technique must not be used.

Keep one-off semantic discoveries in module notes or ledger evidence. Keep
general VC8/reccmp/source-shaping knowledge in the pattern catalog.

Only the coordinator writes IDA or Ghidra during parallel work. Read back IDA
names/types/comments after applying them; call `save_program` after Ghidra
writes. Preserve every durable discovery in tracked manifests, headers, docs,
or ledger evidence rather than only in a local database.

## Finish

Run:

```bash
python3 scripts/validate-tracking.py
python3 scripts/core-worklist.py --check
python3 scripts/progress.py --check
git diff --check
```

Report the addresses, old/new statuses, comparison percentage, and remaining
uncertainties.
