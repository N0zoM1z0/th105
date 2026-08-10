# 東方緋想天 ～ Scarlet Weather Rhapsody

![Decompilation progress](resources/progress.svg)

This project aims to reconstruct the source code of the original Japanese
`東方緋想天 ～ Scarlet Weather Rhapsody` version 1.06a executable, with
reproducible binary comparison as the acceptance criterion.

The project is in its initial reverse-engineering stage. The target has been
fingerprinted and fully imported into Ghidra. The source/build partition is not
yet recovered; the first seventeen small routines have exact function-byte
matches.

## Target executable

Supply your own original executable as `resources/th105.exe`:

| Property | Required value |
| --- | --- |
| Original archive member | `th105c.exe` |
| Size | `3,039,232` bytes |
| SHA-256 | `49c23d9467b9927ba687ed2b873c4bc2d2f39ddadc9f55051ccf10172c0b7c11` |
| PE image base | `0x00400000` |

Localized executables are different binaries and are intentionally rejected.
The executable and game data are copyrighted assets and are not included.

```bash
scripts/import-target.sh /path/to/th105.rar
python3 scripts/verify-target.py
```

## Reverse-engineering environment

The repository uses Ghidra 12.1, GhidraMCP, reccmp, and objdiff-style object
comparison. The workflow borrows the proven mapping/build/report structure of
the GensokyoClub TH06 and TH08 projects, while adding a machine-readable
function ledger and a project-scoped MCP launcher for coding agents.

From the repository root, register the `th105-ghidra` MCP server once and verify
the complete MCP protocol path with:

```bash
scripts/bootstrap-tools.sh
scripts/bootstrap-ghidra-project.sh
scripts/register-codex-mcp.sh
codex mcp list
.tools/src/ghidra-mcp/.venv/bin/python scripts/check-mcp.py
```

The launcher starts the analyzed headless project on loopback when needed.
See [docs/MCP.md](docs/MCP.md) for setup and security details.

## Project map

- [Architecture](docs/ARCHITECTURE.md) — confirmed binary structure and module plan
- [Reverse-engineering workflow](docs/RE_WORKFLOW.md) — evidence and agent handoff rules
- [Matching workflow](docs/BUILD_MATCHING.md) — compiler, reccmp, and objdiff stages
- [Progress](docs/PROGRESS.md) — generated from `config/functions.csv`
- [AGENTS.md](AGENTS.md) — mandatory operating rules for coding agents
- [Parallel-agent skill](.agents/skills/th105-parallel/SKILL.md) — safe,
  high-throughput Ghidra/ledger delegation

Regenerate and validate the tracking data with:

```bash
python3 scripts/generate-tracking.py
python3 scripts/progress.py --check
python3 scripts/validate-tracking.py
```

## Build status

The PE Rich header and linker metadata point to Visual C++ 2005 (VC8), including
42 C++ LTCG records. VC8 SP1 already reproduces seventeen small routines exactly,
but the original service level, complete flags, translation-unit
partition, and link order are still being established. A matching full
executable is not yet advertised. See
[docs/BUILD_MATCHING.md](docs/BUILD_MATCHING.md).

## License

Repository-authored code and documentation are provided under the MIT License.
This does not grant rights to the original game or its assets.
