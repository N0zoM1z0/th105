---
name: th105-re
description: Reverse engineer and byte-match functions in the original Japanese TH10.5 v1.06a executable using the repository Ghidra MCP and function ledger.
---

# TH105 function reconstruction

Use this skill only inside this repository and only for the target hash in
`config/target.toml`.

## Select a bounded task

1. Read `AGENTS.md` in full.
2. Run `python3 scripts/verify-target.py` and
   `python3 scripts/validate-tracking.py`.
3. Choose an unclaimed row from `config/functions.csv`, preferably adjacent to
   an already identified function in the same module.
4. Record the claim in `config/claims.csv` before editing shared source.

## Establish behavior

Use the `ghidra` MCP server with `program="th105.exe"` on every program-scoped
call. Start with:

1. `get_function_by_address`
2. `decompile_function`
3. incoming/outgoing xrefs and callers/callees
4. relevant strings, globals, vtable slots, RTTI, and neighboring functions

Apply types and names only when supported. Record the evidence source and
confidence. Do not treat external layouts or later-game code as authoritative.

## Reconstruct and compare

1. Place code in the module indicated by `config/modules.toml`.
2. Preserve calling convention, object layout, side effects, and initialization
   order before attempting expression-level compiler tuning.
3. Compile the smallest unit supported by the current build.
4. Compare with objdiff for iteration and reccmp for the accepted result.
5. Save the report under `build/` and put its path/command in the function row.

Status may become `matching` only at 100%. Otherwise use `compiles` and record
the measured percentage. Update progress and release the claim at handoff.

## Finish

Run:

```bash
python3 scripts/validate-tracking.py
python3 scripts/progress.py
git diff --check
```

Report the addresses, old/new statuses, comparison percentage, and remaining
uncertainties.
