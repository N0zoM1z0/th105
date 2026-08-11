# Reverse-engineering workflow

## Sources of truth

- `config/target.toml`: immutable target identity.
- the verified IDA IDB: preferred semantic working database; never committed.
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

Use the read-only headless bundle route in `docs/IDA_MCP.md` when transferring
an existing Ghidra project into IDA. Do not launch the Ghidra GUI merely to
export it, and do not translate Ghidra's private database files directly.

## Function lifecycle

1. Claim a small function or tightly related group.
2. Select the analysis backend through `docs/IDA_MCP.md`: IDA first after an
   exact metadata preflight, otherwise strict Ghidra fallback.
3. Establish role and interface using callers/callees, xrefs, RTTI/vtables,
   strings, globals, and neighboring functions.
4. Reconcile the selected tool's function boundary with the ledger and target
   instructions. IDA tail chunks and Ghidra non-contiguous bodies are not
   automatically accepted comparison spans.
5. Apply supported names/types to the selected analysis database and record
   durable repository evidence.
6. Reconstruct class layout and behavior before compiler-shaping work.
7. Implement in the appropriate source module.
8. Compile and iterate with object-level diff.
9. Run reccmp and record the exact percentage/report.
10. Mark `matching` only at 100%, update progress, and release the claim.

Do not use a decompiler listing as source by mechanical transcription. Its
types, signedness, control-flow structure, and expressions are hypotheses until
they agree with instructions and surrounding ABI evidence.

## Fast iteration loop

The accepted tooling rollout and its evidence boundaries are recorded in
[`WORKFLOW_EVOLUTION.md`](WORKFLOW_EVOLUTION.md). For a fresh, hash-attested
IDA-first packet at one ledger entry, use:

```bash
python3 scripts/work-packet.py 0x00421310 --refresh
```

Only the coordinator or a single-agent lane refreshes semantic evidence.
Parallel evidence workers use `--cached`; cached packets are advisory and never
justify a status transition by themselves. Use `--backend ghidra` for the
explicit headless fallback. The packet preserves backend-native payloads and
reports a boundary conflict instead of replacing the ledger boundary.

Normal function work should use a focused decompile/xref query and an
object/function-level diff. The CSV validator and progress check are the only
routine whole-project checks, and both are designed to finish in under a
second. Full Ghidra inventory exports and executable-wide reccmp reports are
milestone operations, not per-edit requirements.

When Ghidra's function body is a non-contiguous address set that omits bytes
inside the entry-to-`span_end` range, use `compare-function.py
--contiguous-span` only after disassembly proves that the whole contiguous span
belongs to the function. The comparison then covers those omitted bytes as
well as the tracked body rather than accepting a truncated prefix.

The comparator resolves external `CALL rel32` targets through
`known-symbols.csv`; the same strict mapping supports external `JMP rel32`
tail calls. Absolute data relocations remain fail-closed unless the
exact COFF symbol, target address, and literal bytes are recorded in
`config/reccmp-relocations.csv`; both the object literal and target bytes are
revalidated on every comparison. Any nonzero relocation addend must also be
explicitly allowlisted and is verified at that exact offset in both images.
PE virtual tails are materialized using their specified zero-fill semantics
when an allowlisted target lies beyond the section's raw file bytes.
Undefined DIR32 symbols remain rejected except for explicitly allowlisted
`__imp__*` imports. An import mapping must name its exact four-byte IAT slot
and on-disk thunk literal; the target bytes and relocation addend are
revalidated on every comparison.

`scripts/compare-function.py --json` is the machine-facing interface. It
distinguishes `exact`, `mismatch`, `blocked`, and `error`, reports the first
differing byte, and classifies relocation blockers. Human-readable output is
retained for direct iteration.

## Parallel-agent safety

Agents should partition work by address/function and source module. Claims must
not overlap. Changes to shared ABI headers, class layouts, vtables, toolchain
configuration, or link order require coordination because they affect many
comparison units.

Generated reports stay below `build/`; durable facts and commands belong in
the ledger or docs so another agent can reproduce the conclusion without the
previous chat context.

## Gameplay contract-first workflow

For core gameplay work, query `scripts/core-worklist.py` before claiming a
function. Its scope and dependency manifests complement rather than replace
`config/functions.csv`:

```bash
python3 scripts/core-worklist.py --check
python3 scripts/core-worklist.py --ready --lane spell-runtime
```

It is valid to add a proven ABI declaration, partial type view, or dependency
edge before source exists. Doing so does not justify a ledger status change.
Never use an empty function body as a placeholder; use the contract framework
described in [`CORE_FRAMEWORK.md`](CORE_FRAMEWORK.md).
