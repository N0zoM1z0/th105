# Ghidra MCP for agents

## What is installed

The pinned versions and hashes are in `config/tools.lock.toml`. Local working
copies live below ignored `.tools/`; the analyzed Ghidra project lives below
ignored `local/ghidra/`.

The connection has two processes:

```text
Codex MCP client ──stdio──> GhidraMCP bridge ──HTTP loopback──> headless Ghidra
```

`.codex/config.toml` registers `scripts/mcp-ghidra.sh` as a project-local stdio
MCP server. The script verifies that port 8089 serves the TH10.5 project,
starts `scripts/ghidra-mcp-server.sh` when necessary, and never binds outside
`127.0.0.1`.

## Verify the real MCP path

```bash
codex mcp list
.tools/src/ghidra-mcp/.venv/bin/python scripts/check-mcp.py
```

The second command performs MCP `initialize`, `tools/list`, and
`tools/call(get_metadata)`. A direct HTTP health request alone does not count as
this verification.

Codex reads project MCP configuration at process startup. If the current Codex
session began before `.codex/config.toml` existed, start a new session from the
repository root; MCP servers are not hot-added to an already running tool list.

## Operating rules

- Include `program="th105.exe"` in program-scoped calls. The bridge enables
  strict program selectors to prevent accidental writes to another program.
- Prefer native MCP tools for decompile/xref/type/rename/comment operations.
- Script execution is deliberately left disabled because it is arbitrary code
  execution inside Ghidra. Reviewed batch scripts belong in `scripts/ghidra/`
  and run through headless Ghidra.
- Call `save_program` after intentional database changes.
- The original executable, Ghidra database, logs, and tool installs are ignored
  and must never be committed.

## Manual troubleshooting

```bash
scripts/ghidra-mcp-server.sh
curl --fail http://127.0.0.1:8089/check_connection
tail -f local/logs/ghidra-mcp.log
```

If port 8089 already serves a different program, the launcher refuses to
continue instead of switching that instance.
