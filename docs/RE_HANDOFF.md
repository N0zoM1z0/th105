# Current reconstruction handoff

The tracking ledgers and fresh target comparisons override prose. Historical
session notes are preserved in [the dated rolling log](RE_HANDOFF_HISTORY_2026_09_26.md)
and the focused evidence files; their old "current", "paused", and "next"
instructions are not the active queue.

## Target and active phase

- Target: original Japanese TH10.5 v1.06a, SHA-256
  `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
- User-directed phase: clean misleading documentation/code, then review the
  remaining origin and candidate-boundary queue. The initial census was
  **4,023 candidates, 1,476 authored, 1,308 excluded, 1,239 in review**.
  The first reviewed batch moves four complete game-owned bodies to authored;
  the second excludes ten five-byte E9 tail aliases; the third positively
  identifies VC8 runtime security-cookie check `0x00689D25`. The resulting
  census is **1,480 authored / 1,319 excluded / 1,224 review**. Source-present remains
  1,388; canonical exact remains 1,315 functions / 220,094 bytes. Recompute from
  `scripts/report-reconstruction-status.py --summary` after every promotion.
- The local target file passes hash verification. The attached IDA session
  currently exposes a different executable (SHA-256 beginning `10350095`),
  so do not use that session's output. Raw target PE disassembly is available.
  A Ghidra project would need independent target identity, entry point, and
  mapped-byte attestation before using its analysis. Do not launch multiple
  Ghidra processes or use the factory MCP adapter for this work.

## Origin and boundary review discipline

Review one evidence-linked batch at a time. `functions.csv` candidate spans are
provisional; establish a complete reachable body, RET/tail behavior, padding,
call and pointer edges, and any remote chunks before accepting a boundary.
Separate target observations from source hypotheses. An exact authored caller
alone does not prove that its callee is game-authored: STL, CRT, third-party,
and generated helpers are also called from exact game code. Use game-specific
behavior, RTTI/vtable ownership, or positive library/compiler provenance to
classify. Leave unresolved rows in review rather than assigning an origin to
make the count look complete.

`config/function-origin-rules.toml` generates the census. During the cleanup
pass, three stale rules were found to overlap functions already promoted to
canonical exact (`0x004064D0`, `0x004309F0`, `0x00496420`). Those rows belong to
the exact baseline; the stale nonexact rule text has been removed or narrowed.
Active origin-rule and anchor comments now refer to the full current inventory
instead of the historical 4,010-row snapshot. The 4,010 and 1,002 figures in
`docs/KNOWLEDGE_BASE.md` are labeled as dated checkpoints, not live totals.
Run `scripts/function-origins.py --check` after origin edits as well as the
normal tracking validator. Any new rule needs a fixed candidate count/byte sum
and target-backed provenance. Record reviewed boundary evidence in
`functions.csv` and a focused note; do not treat name mappings or source
presence as exact credit. `config/claims.csv` remains header-only.

The first [origin/boundary evidence batch](ORIGIN_BOUNDARY_REVIEW_2026_09_26.md)
reviews `0x00407AD0`, `0x004099F0`, `0x00420B90`, and `0x00462AB0` using
complete raw CFG spans, RET/padding, game-specific behavior, and replayed E8/E9
edges from exact callers. The new boundary auditor triaged all 1,239 initial
review rows: 935 had full provisional-span reachability with no visible exit;
159 had unreached bytes, 62 indirect jumps, and 137 outgoing direct edges
(overlapping groups). These are leads, not automatic origin promotions.
The same note also records ten five-byte tail aliases whose signed E9 target
and excluded destination origin are replayed in `function-origins.py`, plus
the 15-byte `0x00689D25` function matched against SHA-pinned VC8 SP1
`secchk.obj` with both COFF relocation targets resolved.

```bash
python3 scripts/verify-target.py
python3 scripts/check-ida-mcp.py
python3 scripts/report-reconstruction-status.py --summary
python3 scripts/validate-tracking.py --require-target
python3 scripts/function-origins.py --check
```

The previous bounded YoumuObject action-entry root at `0x00543670` is parked
while the review queue is active. Its target control flow reaches all
5,159/5,159 callable bytes, but the standalone candidate remains nonexact at
`+0x80` with 6/30 instruction-and-edge-identical diagnostic owners. The
820/850 tail-owner inversion and other physical differences are documented in
[the focused Youmu evidence](YOUMU_OBJECT_ENTRY_SWITCH_CLOSURE_2026_09_26.md).
The common Fighter `0x004740C0` root remains nonexact at `+0x14`; see
[its focused handoff](COMMON_FIGHTER_HANDOFF_2026_09_12.md).

## Commit gate

Run `python3 scripts/ci.py` and `git diff --check` in the finished local
worktree before every commit, then rerun after any further edit. Keep VC8 builds
single-process and pinned to one CPU. Shared accepted header/layout/compiler
changes require affected exact-unit replay; aggregate exact totals require a
cold `python3 scripts/verify-exact-units.py --all` run. Keep private reports in
`build/` or `.analysis/` and out of Git.
