# Ghidra MCP for agents

## What is installed

The pinned versions and hashes are in `config/tools.lock.toml`. Local working
copies live below ignored `.tools/`; the analyzed Ghidra project lives below
ignored `local/ghidra/`.

The connection has two processes:

```text
Codex MCP client ──stdio──> GhidraMCP bridge ──HTTP loopback──> headless Ghidra
```

`scripts/register-codex-mcp.sh` registers the absolute launcher path with the
Codex user configuration under the collision-resistant name `th105-ghidra`.
The launcher verifies that port 8089 serves the TH10.5 project,
starts `scripts/ghidra-mcp-server.sh` when necessary, and never binds outside
`127.0.0.1`.

The headless server uses Java 21 from `/usr/lib/jvm/java-21-openjdk-amd64` by
default, independently of a host `JAVA_HOME` that may point at Java 17. Override
only for this project with `TH105_JAVA_HOME=/path/to/java21`.

## Verify the real MCP path

```bash
scripts/register-codex-mcp.sh
codex mcp list
.tools/src/ghidra-mcp/.venv/bin/python scripts/check-mcp.py
```

The second command performs MCP `initialize`, `tools/list`, and
`tools/call(get_metadata)`. A direct HTTP health request alone does not count as
this verification.

For shells or agent sessions that started before the MCP registration existed,
`scripts/mcp-call.py` is a small protocol-native client. It keeps several calls
in one initialized stdio session:

```bash
.tools/src/ghidra-mcp/.venv/bin/python scripts/mcp-call.py \
  --schema decompile_function
.tools/src/ghidra-mcp/.venv/bin/python scripts/mcp-call.py \
  --call get_function_by_address \
  '{"address":"0x00439870","program":"th105.exe"}'
```

Use repeated `--call TOOL JSON` arguments for an atomic-looking agent work unit,
then finish database edits with `save_program`. Use `--search REGEX` to discover
tool names without dumping the full catalog.

Codex reads MCP configuration at process startup. Start a new session after
registration; MCP servers are not hot-added to an already running tool list.

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
