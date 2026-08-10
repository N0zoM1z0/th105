# Reverse-engineering workflow

## Sources of truth

- `config/target.toml`: immutable target identity.
- `local/ghidra/th105.gpr`: local analysis database; never committed.
- `config/functions.csv`: one row per internal Ghidra `.text` function.
- `config/known-symbols.csv` and `config/known-globals.csv`: concise supported names.
- `config/claims.csv`: active work ownership.
- reccmp reports: byte-match acceptance evidence.

## Inventory refresh

The Ghidra script `scripts/ghidra/ExportFunctionInventory.java` exports exact
function body sizes. The generator merges that inventory with existing manual
status fields and known names:

```bash
scripts/export-function-inventory.sh
python3 scripts/generate-tracking.py
python3 scripts/validate-tracking.py
python3 scripts/progress.py
```

Existing status/evidence/owner fields are preserved by address. A missing or
duplicate address fails validation.

## Function lifecycle

1. Claim a small function or tightly related group.
2. Establish role and interface using callers/callees, xrefs, RTTI/vtables,
   strings, globals, and neighboring functions.
3. Apply supported names/types to Ghidra and record evidence.
4. Reconstruct class layout and behavior before compiler-shaping work.
5. Implement in the appropriate source module.
6. Compile and iterate with object-level diff.
7. Run reccmp and record the exact percentage/report.
8. Mark `matching` only at 100%, update progress, and release the claim.

Do not use a decompiler listing as source by mechanical transcription. Its
types, signedness, control-flow structure, and expressions are hypotheses until
they agree with instructions and surrounding ABI evidence.

## Fast iteration loop

Normal function work should use a focused decompile/xref query and an
object/function-level diff. The CSV validator and progress check are the only
routine whole-project checks, and both are designed to finish in under a
second. Full Ghidra inventory exports and executable-wide reccmp reports are
milestone operations, not per-edit requirements.

## Parallel-agent safety

Agents should partition work by address/function and source module. Claims must
not overlap. Changes to shared ABI headers, class layouts, vtables, toolchain
configuration, or link order require coordination because they affect many
comparison units.

Generated reports stay below `build/`; durable facts and commands belong in
the ledger or docs so another agent can reproduce the conclusion without the
previous chat context.
