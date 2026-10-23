# TH10.5 reconstruction handoff

Prepared for handoff on 2026-10-23. No reconstruction trial or VC8 build is
in flight. Latest game-source checkpoint: `e24fb73`; latest evidence checkpoint:
`b11c6e3`. Action 826's owner-Y correction remains selected; subsequent sharing,
compiler and CIL controls are unselected. Required commit format:
`gpt-6-astra-medium: xxx ~`.

Use this page for current selection and next steps, the
[AyaObject evidence index](AYA_OBJECT_EVIDENCE.md) for scoped results, and the
[preceding session narrative](RE_HANDOFF_HISTORY_2026_10_23.md) for older history.
Current ledgers and fresh objects override dated prose.

## Start here

Only original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Read [AGENTS.md](../AGENTS.md), [architecture](ARCHITECTURE.md),
[workflow](RE_WORKFLOW.md), relevant source and dated evidence before edits.
Use one writable session, one bounded scope, no subagents/concurrent VC8 builds;
claims.csv stays header-only. Heavy commands use CPU0/nice10.

```sh
git status --short
python3 scripts/verify-target.py
python3 scripts/check-ida-mcp.py
python3 scripts/report-reconstruction-status.py --summary
python3 scripts/validate-tracking.py --require-target
```

IDA rejects the currently open database SHA256
`10350095bcf95edb59e03bee9849a2dc8a7714b4927ad5909c569c550fce6822`.
Use raw hash-attested PE inspection; do not use that session's semantics or
writes. Independently attest any Ghidra database and run at most one process.

| Ledger layer | Current value |
| --- | ---: |
| Provisional candidates | 4024 |
| Authored / excluded / origin review | 1595 / 1418 / 1011 |
| Mapped / source-present | 1519 / 1501 |
| Accepted authored exact | 1381 functions / 234914 bytes |
| Provisional authored byte denominator | 2136806 |
| Match units / configured functions | 543 / 1511 |

These are ledger totals. This cleanup makes no aggregate cold-replay claim.
Shared header/layout/profile/partition/relocation changes require affected
accepted-unit replay; new aggregate claims require `verify-exact-units.py --all`.

## AyaObject update 0x61A290

Selected [source](../src/characters/AyaObjectActionState.cpp), unit
`gpt-web-aya-object-vslot28-full-root`. Callable ledger size 19522;
complete canonical payload 20132, metadata starts at 19664, full SHA256:
`a5dc22f5c6f0e93a3fc81592510327c5708c8c4d41938f2bd96eaf7947523ede`.
Fresh restored comparison remains **nonexact +0x22**, target `0F` / source `9B`.
No root exact credit. The adjacent metadata is not added to the callable boundary.

Source SHA256:
`4272f7f5d30499822931f9a70f7b52e179e6d99732e7d21962f58a6cfdef0472`.
The first mismatch is the initial JA displacement. The
[evidence index](AYA_OBJECT_EVIDENCE.md) separates selected changes, scoped
behavioral checks and rejected context controls, with source-epoch limits.

Latest completed scope: `build/aya-size-profile-20261023/`. Both `/O2 /Os` and
`/O1` give the same 18,180-byte canonical payload, but lose the target entry's
8-byte stack alignment and first differ at `+0x4`. They remain unselected.
The preceding `build/aya-joint-cil-20261023/` closes caller address replay:
current selected and shared CIL payloads equal their native counterparts.
The older eight-byte CIL difference is historical, not a current blocker.

Resume with one target-backed lead:

- Recover visibility/lifetime context for 852's early promotion and branch-local
  conversions. Tested RTM, local fenv and explicit if/else did not recover it.
- Preserve 807's second zero-sequence read before selecting shared 826/861 tails
  or 801 caching. Existing candidates fail that observation.
- Investigate common frame tails and scratch placement with evidence beyond
  local size or equal final outputs. 903's 13,596-case check covers non-spawning
  paths and read epochs; it does not establish complete root equivalence.

Rebase trials onto current source. Negative results apply to their tested
context, not every possible LTCG partition. Private flow-alignment diagnostics
are incomplete and are not acceptance evidence. Native fixtures have scoped
limits; inspect placement assumptions and callback exception guards before reuse.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
python3 scripts/audit-aya-object-runtime-context.py
python3 scripts/audit-aya-object-predicate-widths.py
taskset -c 0 nice -n 10 python3 scripts/audit-aya-object-scale-adds.py --actions 826 --position-lifetimes
taskset -c 0 nice -n 10 python3 scripts/audit-aya-object-903-paths.py
```

The root comparison is expected to exit nonzero for nonexactness. The runtime
packet needs the configured object; its default run needs no frozen control.
The selected object contains the 37-byte interval for 826, but 861 does not execute
it; use explicit diagnostic mode for 861 position-lifetime reports.

## Other open roots

ReimuObject `0x496540` remains nonexact +0x1F (`0x49655F`). Selected
[source](../src/characters/ReimuObjectActionStateStaging.cpp) has full canonical
45696-byte SHA256 `4b565d714737cf5ddfdaf8ae5d9944369071899fccb70223f86f572b55a65bf2`;
same-TU counter `0x4963A0` is 66/66 exact. See the
[evidence index](REIMU_OBJECT_EVIDENCE.md) and
[selected owner model](REIMU_OBJECT_OWNER_VIEW_SELECTED_2026_10_22.md).
Physical call/RET sharing remains open. Aya initializer `0x61F0B0` retains two
register-byte differences. Other pending roots: Reimu Fighter `0x478FA0`,
initializer `0x4A1CE0`, YoumuObject `0x543670`, CGage `0x41B3F0`,
loader `0x40B000`, renderer `0x415050`.

Font entry points: [owner](../src/assets/TextFontOwner.cpp),
[render](../src/assets/TextFontRender.cpp), [CIL input](../src/assets/TextFontLinked.cpp).
Physical owner/config sizes remain `0x194` / `0x128`; frame gaps do not prove
larger classes. Begin `0x4119A0` is 291/291 nonexact +0x3B; Glyph `0x411B80`
624/624 +0x59; Accent `0x411DF0` 417/417 +0x6; Markup `0x411FA0` 1728/1744
+0x10; Renderer `0x412670` 335/326 +0x13. Begin/renderer are genuine CIL probes.
Offsets here use explicit hexadecimal notation; older reports often use decimal.
See [accent](TEXT_FONT_ACCENT_LIFETIMES_2026_10_22.md),
[glyph](FONT_GLYPH_WINDOW_PROOF_2026_10_22.md),
[markup cleanup](FONT_MARKUP_CONSTRUCTION_CLEANUP_2026_10_22.md),
[begin context](TEXT_FONT_BEGIN_CONTEXT_2026_10_22.md).
Prior accepted font leaves are unchanged, not newly replayed here.

## Artifacts and final gate

[Artifact retention and recovery](ARTIFACTS.md) describes this cleanup and
restoration. Latest inventory: `build/handoff-refresh-20261023/manifest.json`.
The same scope's `aya-final-comparison.json` records the fresh focused build;
`ci.log` records the final local gate. Root mismatch `+0x22` is expected.
Historical reports may end in `.gz`; restore with `gzip -dk PATH.gz` before
using old recipes. Current objects, frozen controls, receipts and provider inputs remain directly
available. Six dirty detached worktrees are retained.

After the final tracked edit, before every commit/push/PR:

```sh
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Mandatory local CI baseline: 462 tests. No private reports, executables, game
data, databases, compilers or credentials in commits. Verify remote HEAD after
an authorized push and leave the main worktree clean for the next session.
