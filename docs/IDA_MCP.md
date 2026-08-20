# IDA Pro MCP routing and attestation

IDA MCP has no `program=` selector: it operates on the database open in the
GUI. All TH105 semantic queries therefore fail closed until the active image is
attested as the canonical 1.06a target.

## Preflight

Open the selected `th105.exe`, start the IDA MCP plugin, then run:

```bash
python3 scripts/verify-target.py
python3 scripts/check-ida-mcp.py
```

These commands keep the plain `python3` interface but self-bootstrap the
pinned `mcp==1.26.0` dependency with `uv run --no-project` when the active
interpreter lacks it. This is intentional for headless GPT-web shells, whose
login `PATH` may select `/usr/bin/python3` instead of an interactive Conda
environment.

The second command verifies:

1. required read-tool capability and MCP connection;
2. SHA-256, MD5, file size, image base, and module metadata;
3. entry point `0x0068B9D2`;
4. exact mapped bytes at `.text` start, entry point, and three separated
   `.text` locations against `resources/th105.exe`;
5. a function-inventory query.

Any mismatch blocks IDA use. Never override the check because a database title
looks correct.

## Safe calls

Use `scripts/ida-mcp-call.py` for repeatable calls:

```bash
python3 scripts/ida-mcp-call.py --schema decompile_function
python3 scripts/ida-mcp-call.py --call get_function_by_address \
  '{"address":"0x00401000"}'
```

The wrapper revalidates metadata, defaults to read-only behavior, and
permanently rejects `patch_address_assembles`. Reviewed metadata writes require
`--allow-write`; query the affected item afterwards and record durable evidence
in the ledgers.

Treat IDA tail chunks, EH regions, auto-names, decompiler types, and function
sizes as evidence only. Comparison extents require complete target control-flow
and object-symbol evidence.

## Fresh inventory

For an intentional baseline replacement only:

```bash
python3 scripts/export-ida-inventory.py --write
```

This command re-attests IDA and replaces the candidate/origin ledgers without
merging prior status. It writes its raw snapshot below ignored `.analysis/`.

## Web adapter

The ignored `.tools/mcp_for_gptweb` adapter exposes one `ida_call` tool and
performs its own canonical-file, metadata, and multi-point byte attestation
before every call. It blocks target patching even if upstream IDA advertises a
patch tool. See `docs/TOOLS.md`.

## Failure policy

If any preflight stage fails, stop using semantic-analysis output and report
the IDA blocker. This repository does not route to Ghidra or another fallback.
