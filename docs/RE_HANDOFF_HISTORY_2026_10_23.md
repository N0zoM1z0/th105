# Historical snapshot before the October 23 handoff cleanup

The text below preserves the preceding session state and artifact paths.
Its active-phase statements, priorities and commit format are historical.
Use [the current handoff](RE_HANDOFF.md) and [artifact recovery](ARTIFACTS.md).

---

# TH10.5 reconstruction handoff

Resumed2026-10-23 at the user's request. Reconstruction is active again.
Use serial low-resource builds and focused affected-scope replays; preserve
stable commit/push checkpoints. Required commit format: `gpt-6.1-sol: ...`.
Earlier game-source checkpoint: `69c4e37`; cleanup checkpoint: `c1beb8b`.

The full preceding narrative is preserved in the
[October22 history](RE_HANDOFF_HISTORY_2026_10_22.md). Dated reports describe
specific source epochs; current ledgers and freshly verified objects take priority.

## Current selected work: AyaObject update0x61A290

Source: [AyaObjectActionState.cpp](../src/characters/AyaObjectActionState.cpp).
Configured unit: `gpt-web-aya-object-vslot28-full-root`.
Target callable ledger size19522; selected complete canonical payload20132,
metadata start19664. Full canonical SHA256:
`17585ff8bc4fadd5f63619d3d52d470440955256a820ac76ca97daa7ee31f88f`.
The configured19522-byte comparison remains **nonexact** at hex offset22,
target0F/source9B. No Aya root exact credit has been added.

Latest [801/852 context controls](AYA_OBJECT_801_CONTEXT_852_FACING_CONTROLS_2026_10_23.md)
retain selected game source unchanged.801's new-context snapshot still grows
136 bytes and fails outside801 strict comparison; private alignment diagnostics
also reach817/820/826 changes beyond the older852/853/861 audits. They are
incomplete and not acceptance evidence.852 is now pinned to a62-byte/14-instruction
window: one pre-branch MOVSX, two per-arm FILD conversions, no FIMUL. Int/double
locals each recover only part; neither is selected. The public facing-lifetime
packet lists exact bytes/widths/conversion regions for further context work.

Latest [807/854 read lifetimes](AYA_OBJECT_807_854_READ_LIFETIMES_2026_10_23.md):
807's post-spawn sequence snapshot now retains the live angle across alpha.
All3968 cases match every recorded observation, eliminating2044 read differences.
854 captures sequence and prior alpha before fading; all3840 cases agree,
eliminating3232 sequence-read and1776 alpha-snapshot differences. Both use strict
native mode without allow-read flags. Stepwise outside807/854 graphs preserve
4464/4481 nodes with no carrier allowances. Full payload shrinks4 bytes;
register choice, exclusive-branch optimization and frame-tail placement remain
nonexact.801's affected-auditor replay still reports3012 known read differences.

Prior [807 angle lifetime recovery](AYA_OBJECT_807_ANGLE_LIFETIME_2026_10_23.md):
a used double angle now spans the alpha write and recovers the exact26-byte
61A86D interval.3968 actual-code cases preserve effects and688 alpha-write x87
snapshots; all688 predecessor snapshot differences disappear.2044 sequence-read
differences remain, requiring the explicit scoped-audit option. Complete payload
changes only18 bytes inside that interval;4464 other-path strict graph nodes
agree. Source sequence snapshot and explicit frame-tail controls are unselected.
Neither resolves register/CSE or physical tail sharing; no root exact credit.

Prior [861 phase-scope correction](AYA_OBJECT_861_PHASE_SCOPE_2026_10_23.md):
phase/count advancement now stays inside initial sequence0. Target61D5F2 skips
it for nonzero sequence.3072 actual-code cases have0 selected final-state or
phase/count-write differences; predecessor differs in2304. The complete payload
changes only the displacement byte at33E8, skipping41 bytes. Outside8614466
strict graph nodes agree.768 existing alpha/X write-order differences remain
explicit, with their exact two-write shape checked. No exact credit.

The accompanying6216-case scale audit matches scale-store live x87 snapshots
for selected and old801-control objects. Its phase controls exposed the counter
bug; direct853 addition-operand reversal is fully byte-neutral and unselected.
Frozen801 source predates this fix; rebase future controls instead of replacing
current source wholesale.

Prior [801 fade snapshot report](AYA_OBJECT_801_FADE_SNAPSHOTS_2026_10_22.md):
3840 cases preserve effects and corrected alpha-read snapshots;3012 sequence-read
differences remain explicit. Its old sequence-snapshot control was unselected
because it changed other paths. The [852 control audit](AYA_OBJECT_852_NATIVE_CONTROL_2026_10_23.md)
and scale audits bound some of those changes, not full-control acceptance.
Rebase any future801 trial onto current source: the frozen control predates
861's real counter fix and807's selected angle/sequence lifetimes. Color-byte
and early-Boolean controls were byte-neutral within their older source epoch.

Earlier selected corrections remain in source. Their old hashes are historical:

| Scope | Evidence / next-use reference |
| --- | --- |
|810 independent sequence reload|[4096 cases, prior2336 read-only differences](AYA_OBJECT_810_SEQUENCE_RELOAD_2026_10_22.md)|
|810/821 low-byte predicate use|[Actual full-EAX0/1 proofs; int ABI retained](AYA_OBJECT_PREDICATE_WIDTHS_2026_10_22.md)|
|804 post-gate reload|[3072 actual-code cases; false gate does not mutate sequence](AYA_OBJECT_804_SEQUENCE_RELOAD_2026_10_22.md)|
|821 growth counter|[Actual field correction36C to364;3300 cases](AYA_OBJECT_821_COUNTER_FIELD_2026_10_22.md)|
|903 shared fade value|[Double-product lifetime and3168 native cases](AYA_OBJECT_903_SHARED_FADE_2026_10_22.md)|
|900/901/902 control flow|[Detailed checkpoints and limits](RE_HANDOFF_HISTORY_2026_10_22.md)|

Next evidence leads:852 pre-branch promoted capture with per-arm conversion
under a supported source/context change;817/820/826 impact closure before adopting
801 caching; common frame-tail, register and scratch placement. Do not infer an LTCG impossibility from failed
local controls. Some old fixtures have placement assumptions; recheck them
against the current object before treating a fixture failure as game behavior.
The guarded native callback wrappers stop and rethrow Python hook exceptions;
older independent fixtures must be inspected for this protection before reuse.

## Other open large-function work

ReimuObject update496540 remains nonexact+31. Selected source is
[ReimuObjectActionStateStaging.cpp](../src/characters/ReimuObjectActionStateStaging.cpp),
with complete45696-byte canonical SHA256
`4b565d714737cf5ddfdaf8ae5d9944369071899fccb70223f86f572b55a65bf2`.
Same-TU counter4963A0 is66/66 exact. The [selected owner-view report](REIMU_OBJECT_OWNER_VIEW_SELECTED_2026_10_22.md)
records14464 scoped cases and9344 other-action graph nodes. Physical call/RET
sharing remains unresolved; use the [evidence index](REIMU_OBJECT_EVIDENCE.md).

AyaObject initializer61F0B0 remains nonexact with two register bytes different;
see its current ledger row and [801-era history](RE_HANDOFF_HISTORY_2026_10_22.md).
Other pending roots include Reimu Fighter478FA0, initializer4A1CE0,
YoumuObject543670, CGage41B3F0, loader40B000 and renderer415050.

Font sources: [owner](../src/assets/TextFontOwner.cpp),
[render](../src/assets/TextFontRender.cpp), [CIL input](../src/assets/TextFontLinked.cpp).
The physical owner is0x194, config0x128; markup frame gaps do not prove a larger
class. Current selected diagnostic results:

| Address | Operation | Selected / target bytes | Status |
| --- | --- | ---: | --- |
|4119A0|Begin|291 /291|Genuine CIL nonexact+59|
|411B80|Glyph|624 /624|Native nonexact+89|
|411DF0|Accent|417 /417|Native nonexact+6|
|411FA0|Markup|1728 /1744|Native nonexact+16|
|412670|Renderer|335 /326|Genuine CIL nonexact+19|

[Accent lifetimes](TEXT_FONT_ACCENT_LIFETIMES_2026_10_22.md),
[glyph window](FONT_GLYPH_WINDOW_PROOF_2026_10_22.md),
[markup cleanup](FONT_MARKUP_CONSTRUCTION_CLEANUP_2026_10_22.md), and
[begin context](TEXT_FONT_BEGIN_CONTEXT_2026_10_22.md) retain qualified proofs.
Markup native has four cleanup roles; CIL's outlined push_back owns the fourth
role, so three parser states do not prove missing cleanup. RTM GL/Zi still fails
C1902; it supplies no code-generation comparison. Previous accepted font
end/reset/color and owner/config functions remain accepted, not newly replayed
by this documentation cleanup.

## Target, ledger and startup rules

Only Japanese TH10.5 v1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Read [AGENTS.md](../AGENTS.md), [architecture](ARCHITECTURE.md),
[workflow](RE_WORKFLOW.md), dated evidence and relevant source before changes.
One writable session, one bounded scope, no subagents/concurrent VC8 builds;
claims.csv stays header-only. Use CPU0/nice10 for heavy work.

```sh
git status --short
python3 scripts/verify-target.py
python3 scripts/check-ida-mcp.py
python3 scripts/report-reconstruction-status.py --summary
python3 scripts/validate-tracking.py --require-target
```

IDA currently rejects SHA256
`10350095bcf95edb59e03bee9849a2dc8a7714b4927ad5909c569c550fce6822`.
Do not use its semantics/writes/patches. Raw hash-attested PE inspection is valid;
independently attest any Ghidra database and run at most one process.

| Ledger layer | Value |
| --- | ---: |
|Provisional candidates|4024|
|Authored / excluded / origin review|1595 /1418 /1011|
|Mapped / source-present|1519 /1501|
|Accepted authored exact|1381 functions /234914 bytes|
|Provisional authored byte denominator|2136806|
|Ledger byte percentage|10.99%|
|Match units / configured functions|543 /1511|

These are ledger totals, not a fresh aggregate replay. A new aggregate claim
requires cold `verify-exact-units.py --all`. Replay affected accepted units after
shared header/layout/profile/partition/relocation changes. Source-present,
owner diagnostics and scoped native cases never mean canonical exactness.

## Resume commands and cleanup recovery

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
taskset -c 0 nice -n 10 python3 scripts/audit-aya-object-801-fade.py --allow-sequence-read-differences --output build/aya-801-fade-20261022/resume-native.json
python3 scripts/audit-aya-object-predicate-widths.py
```

The root comparison is expected to exit nonzero for nonexactness. Selected
objects and latest801/810/predicate reports remain directly available. Older
large diagnostic reports may now end in `.gz`; restore before using an old
recipe with `gzip -dk PATH.gz`. See [artifact retention](ARTIFACTS.md) and the
private `build/handoff-cleanup-20261022/manifest.json` for per-file hashes.
Six old detached worktrees contain uncommitted work and were preserved.
Target, toolchains, primary databases, frozen controls and current objects were
not deleted. Disposable Python caches can be regenerated automatically.

After the last tracked edit, before every commit/push/PR:

```sh
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Local CI is mandatory; baseline459 tests. No private reports, executables,
game data, databases, toolchains or credentials belong in commits. Push stable
checkpoints and verify remote HEAD and a clean main worktree.
