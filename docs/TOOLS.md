# Tool routing

Every route is pinned to `config/target.toml`. Semantic output is evidence;
only the canonical comparator can establish exactness.

## Direct local workflow

Use this when the coding agent can access the local shell and registered MCP:

```bash
python3 scripts/verify-target.py
python3 scripts/check-ida-mcp.py
python3 scripts/ida-mcp-call.py --call decompile_function '{"address":"0x..."}'
```

`ida-mcp-call.py` re-attests the target on every process and blocks writes by
default. `patch_address_assembles` is never allowed. Use `--allow-write` only
for reviewed names, types, comments, and other metadata; read back the result.

## GPT-web Bash + IDA adapter

`.tools/mcp_for_gptweb` is an ignored nested checkout adapted from the TH08
two-tool service. It exposes exactly:

- `run_command`: shell commands restricted to the TH105 workspace.
- `ida_call`: one allowlisted IDA MCP call after fresh target attestation.

The adapter checks the canonical local executable plus IDA metadata and mapped
bytes before every semantic call. Target patching is permanently blocked;
metadata writes are controlled by environment policy.

Local setup:

```bash
cd .tools/mcp_for_gptweb
cp .env.example .env
# Fill endpoint paths/tokens privately; never commit or print .env.
npm install
npm run typecheck
npm test
npm run build
```

The service/Funnel templates and operator commands are in that nested README
and `TH105_WORKFLOW.md`. Keep endpoints loopback-only unless the authenticated
Funnel route is intentionally enabled. Do not expose raw IDA MCP directly.

## Backend policy

IDA Pro is the sole semantic backend. If `scripts/check-ida-mcp.py` fails, stop
the bounded reconstruction unit and fix/report IDA; do not route to Ghidra.

## Matching tools

- `scripts/build.py --check`: validate the VC8 unit graph.
- `scripts/build.py --unit NAME --compare`: focused build and strict compare.
- `scripts/compare-function.py`: canonical COFF/function comparator.
- `scripts/verify-exact-units.py --all`: cold replay of all accepted units.
- `scripts/report-reconstruction-status.py`: select work from current ledgers.
- `scripts/ci.py`: target-independent public validation.
