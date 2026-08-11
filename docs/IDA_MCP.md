# IDA-first analysis workflow

IDA Pro MCP is the preferred semantic-analysis backend when it is available
and is attached to the exact original Japanese TH10.5 v1.06a executable. The
existing Ghidra workflow remains the fallback and the current function-body
inventory authority.

```text
verify resources/th105.exe
        |
        v
check registered IDA MCP + exact IDB metadata
        |
        +-- valid ------> IDA-primary semantic analysis
        |                    |
        |                    +-- boundary agrees --> normal work unit
        |                    `-- boundary conflict -> ledger/Ghidra boundary
        |
        `-- unavailable --> strict Ghidra fallback
                             program="th105.exe"
```

IDA-primary means that Hex-Rays pseudocode, disassembly, xrefs, call graphs,
RTTI, structures, and type propagation are queried there first. It does not
make IDA names, types, function sizes, or visual similarity authoritative.

## Preflight

Open the original `th105c.exe` in IDA, start the IDA MCP plugin, and confirm
that Codex has a stdio bridge registered as `ida-pro-mcp`. The command and IDA
installation path are user-specific; the repository reads the active Codex
registration rather than hard-coding them.

```bash
python3 scripts/verify-target.py
codex mcp get ida-pro-mcp --json
python3 scripts/check-ida-mcp.py
python3 scripts/select-analysis-backend.py
```

The smoke test performs MCP `initialize`, `tools/list`, and real tool calls. It
fails closed unless SHA-256, MD5, image base, and file size match
`config/target.toml`. It also checks the known `0x0046A5B0` tail wrapper and
reports whether IDA currently assigns the separate body at `0x00463610` to the
same function.

Failure reasons are machine-readable:

| Reason | Action |
| --- | --- |
| `unavailable` | Start the IDA plugin or use the Ghidra fallback. |
| `target_mismatch` | Stop. Never analyze the localized or wrong executable. |
| `missing_tool` | Use Ghidra for the missing evidence operation. |
| `boundary_conflict` | Keep ledger/Ghidra boundaries; inspect target instructions manually. |

## Address-bounded work unit

1. Verify the target and inspect `config/functions.csv` and
   `config/claims.csv`.
2. Run `scripts/check-ida-mcp.py`. If it passes, use IDA for semantic analysis.
   If it is unavailable, run the Ghidra protocol smoke test in `docs/MCP.md`.
3. Start with function metadata, decompilation, disassembly, callers, callees,
   xrefs, relevant globals/strings, and RTTI or vtable evidence.
4. Compare the queried IDA entry and range with the ledger entry, `size`, and
   `span_end`. A query that resolves to another entry is an
   `ida_boundary_conflict`.
5. Keep facts, inferences, and hypotheses separate. Record durable names,
   contracts, and evidence in the repository rather than only in an IDB.
6. Compile and compare through the existing VC8/reccmp workflow. IDA output
   never promotes a row to `matching`.

For shells or sessions that cannot expose the registered native tools, use the
protocol-native helper. It revalidates the target before every session:

```bash
python3 scripts/ida-mcp-call.py \
  --call get_function_by_address '{"address":"0x00416A50"}' \
  --call decompile_function '{"address":"0x00416A50"}'
```

The helper rejects write tools unless the coordinator explicitly supplies
`--allow-write`. It always rejects `patch_address_assembles`.

## Function-boundary rule

IDA function chunks are useful for whole-flow decompilation but are not a safe
inventory boundary. The canonical regression case is:

| Address | Ledger meaning | Accepted size |
| --- | --- | ---: |
| `0x0046A5B0` | global-context tail wrapper | 11 |
| `0x00463610` | five-pass fighter/object callback body | 323 |

IDA currently decompiles both as one chunk owner. Both ledger rows independently
match 100%, so an IDA inventory must never merge or overwrite them. Similar
tail chunks, non-contiguous bodies, shared tails, and alignment gaps require
target disassembly plus the existing Ghidra inventory or a reviewed boundary
manifest.

## Durable truth and database writes

| Data | Authority |
| --- | --- |
| target identity | `config/target.toml`, `verify-target.py` |
| function status and accepted boundary | `config/functions.csv` |
| active ownership | `config/claims.csv` |
| supported names/globals | `known-symbols.csv`, `known-globals.csv` |
| gameplay scope/dependencies/types | `config/core-*.csv` |
| exact acceptance | `compare-function.py` and reccmp reports |
| semantic working cache | IDA IDB or Ghidra project |

Only the coordinator writes to IDA or Ghidra during parallel work. Never patch
the shipped executable or IDB bytes. Apply supported names, prototypes, types,
and comments in a short serial batch, read them back, and preserve the evidence
in tracked files. IDA and Ghidra databases are ignored caches, not the only
copy of a discovery.

## Importing prior Ghidra analysis

Ghidra project databases cannot be loaded directly into IDA. First export a
reviewable analysis bundle containing target identity and provenance plus
functions/body ranges, symbols, globals, types, prototypes, and comments. Then:

1. validate the bundle schema, digest, target hash, base, address ranges, and
   uniqueness without opening either database for writes;
2. dry-run boundary reconciliation against IDA and the function ledger;
3. import types in dependency order, then globals, names/prototypes, and
   comments;
4. never replace an existing non-default IDA name/type/comment automatically;
5. never delete or create functions for a boundary conflict; emit a conflict
   report for manual review;
6. record importer provenance so applying the same bundle is idempotent.

The `0x0046A5B0`/`0x00463610` pair is a mandatory regression fixture for any
future bulk importer.

The repository implements that path without launching the Ghidra GUI:

```bash
# Reads local/ghidra/th105 read-only and does not rerun analysis.
scripts/export-analysis-bundle.sh

# MCP-native dry-run; writes an ignored conflict report under .analysis/.
python3 scripts/sync-ghidra-to-ida.py

# Coordinator-only safe subset: supported names whose IDA boundary agrees.
python3 scripts/sync-ghidra-to-ida.py --apply --kinds names
```

`ExportAnalysisBundle.java` writes checksummed CSV payloads for functions,
symbols, comments, defined data, and data types plus Ghidra C declarations.
The bundle manifest binds every payload to the target hash and source-archive
hash. `sync-ghidra-to-ida.py` accepts only Ghidra `USER_DEFINED` function names
that also occur in the authoritative ledger, refuses `unclassified` rows,
preserves non-default IDA names, and refuses size conflicts. Every run writes a
machine-readable before/after report.

For a finer import inside IDA, run
`scripts/ida/import_ghidra_bundle.py`. It is dry-run by default and additionally
checks current user types and repeatable function comments before writing. Its
`--apply` mode can import supported globals, prototypes, and comments, but it
still never creates, deletes, merges, or resizes a function. Do not bulk-import
`data-types.h`: review it first, because Ghidra archives commonly contain large
Windows/CRT type sets and placeholder structures rather than gameplay layouts.

The downloaded project may retain the remote operating-system owner in
`local/ghidra/th105.rep/project.prp`. Change only that ignored local metadata to
the current user when `analyzeHeadless` reports `NotOwnerException`; never
rewrite or recommit the database payload.
