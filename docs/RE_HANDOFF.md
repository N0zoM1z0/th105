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
  Eighteen evidence-linked origin/boundary batches are recorded in
  [the focused review](ORIGIN_BOUNDARY_REVIEW_2026_09_26.md). The current
  census is **1,486 authored / 1,387 excluded / 1,150 review**. Source-present
  remains 1,388; canonical exact remains 1,315 functions / 220,094 bytes.
  Recompute from `scripts/report-reconstruction-status.py --summary` after
  every promotion.
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
`secchk.obj` with both COFF relocation targets resolved. Eighteen ten-byte
global destructor adapters are tied to actual `_atexit` registration sites;
eight larger checked-container/string cleanup bodies are pinned by full hashes,
free-call edges, and the same registration mechanism. Ten smaller callback
bodies have direct `_atexit` registration and complete main spans. Three
simple aliases without that witness stay in review. The bounded proximity
screen's two other hits `0x0043BF50/60` feed the VC8 array constructor
before the nearby `_atexit` call and also remain in review. The KERNEL32
`0x006B55C0/0x006B5ECA` thunks have exact six-byte boundaries and IAT
name/slot witnesses. The 400-byte `__free_lc_time @ 0x0069CCD9` and 31-byte
`__allshl @ 0x006B6D00` have complete VC8 archive extents and full-inventory
fingerprints; all 43 `__free_lc_time` relocations resolve to CRT `_free`.
The 286-byte match-mode setup has complete raw CFG, game state writes and two
replayed E8 sites in exact `CTitle::update`; the nine observed E8 calls all
belong to that one exact caller. The 111-byte text-texture wrapper has complete
raw CFG, handle lifetime/error cleanup, and independent exact UI/network
callers; its retained class label remains a hypothesis. The 298-byte profile
message update has five complete return paths, game UI state writes, and direct
calls from seven separate exact menu functions; its retained source probe is
still nonexact. Twelve eight-byte Boost exception vtable entries subtract the
offset in their adjacent VC8 RTTI locator from ECX and tail-jump to a separate
candidate. Eight primary virtual deleting destructors in the same Boost RTTI
families have complete 30/57-byte bodies and a conditional call to the
excluded free alias. Four `clone_impl` virtuals end in the pinned VC8
`__CxxThrowException` call after copying an exception temporary. Their
underlying destructor/copy-helper origins remain open. Four clone/allocate
virtuals have complete 120-byte main spans; their common VC8 FuncInfo names
a single unwind action that frees the allocated object on copy failure. The
464-byte network sender `0x00416990` has complete raw CFG, type-0x0E packet
construction, Win32 queue/event behavior and nine distinct exact callers.
The old `ReimuObject*` deque fingerprint also matches code used by this
network sender, so its subsystem is now neutral runtime rather than characters.
The 334-byte profile-slot default initializer has a complete main span,
fixed game key codes, twenty deck slots and exact profile UI callers; the
called deck CSV loader `0x00431E80` now has a reviewed 463-byte main span
and six-state VC8 EH cleanup chain. Its class/ABI identity remains unknown.

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
