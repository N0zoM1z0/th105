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

The IDA client entry points pin Python package `mcp==1.26.0`. If the selected
`python3` does not provide that version (as with the GPT-web systemd login
shell), they transparently re-exec through `uv run --no-project`; no global
Python installation or activated virtual environment is required. `uv` must
be on `PATH`.

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

- `scripts/function-origins.py --check`: target-backed replay of generated authored/excluded origin census rules (requires canonical target plus SHA-pinned VC8 and Xiph SDK archives). It also recompiles tracked VC8 generated-COMDAT anchors such as the checked PAT vector helpers and verifies relocation-masked inventory uniqueness.
- `scripts/build.py --check`: validate the VC8 unit graph.
- `scripts/build.py --unit NAME --compare`: focused build and strict compare.
- `scripts/compare-function.py`: canonical COFF/function comparator.
- `scripts/verify-exact-units.py --all`: cold replay of all accepted units.
- `scripts/report-reconstruction-status.py`: select work from current ledgers.
- `scripts/rank_retained_exact.py`: target-attested retained-1.06 source ranking for 1.06a; dual `/GS` profiles, normalized instruction shape, and relocation-masked raw mismatch counts are prioritization signals only. Repeatable `--historical-status` filters may widen the archaeology queue to old `implemented`/`compiles` rows without changing acceptance semantics.
- `scripts/ci.py`: target-independent public validation.

## Giant authored action-switch topology

For large Fighter vslot28 roots whose sparse switches use VC8 byte-index tables, use the fail-closed mapper instead of hand-decoding table bytes:

```bash
python3 scripts/map-giant-action-switches.py youmu-vslot28
python3 scripts/map-giant-action-switches.py youmu-vslot28 --json
```

Root/table witnesses live in `config/giant-action-switches.toml`.  The mapper reads `resources/th105.exe`, validates every byte index against the destination-table count, requires every decoded destination to stay inside the reviewed callable, checks retained call/RET/group census invariants, and annotates each physical action destination with direct callees from `config/functions.csv`.  Add new roster roots to the manifest only after independently attesting their callable and metadata boundaries.  The emitted spans are source-ownership evidence; they do not split the authored exact-byte ledger.
