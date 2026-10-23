# TH10.5 reconstruction handoff

Resumed 2026-10-23 at the user's request. Reconstruction is active, with serial
low-resource builds and focused affected-scope verification. Latest game
source checkpoint: `e24fb73`; cleanup checkpoint: `730d942`. Latest 861 sharing
controls are unselected; action826's owner-Y correction remains in source.
Required commit format: `gpt-6.1-sol: ...`.
The [preceding session narrative](RE_HANDOFF_HISTORY_2026_10_23.md) preserves
older controls and references. Current ledgers and fresh objects override history.

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

| Current evidence | Result and practical limit |
| --- | --- |
| [826 owner-Y lifetime](AYA_OBJECT_826_OWNER_Y_LIFETIME_2026_10_23.md) | Captured double Y spans alpha; target37-byte interval restored.2584 strict native cases agree, eliminating2584 prior ordered-write/position-snapshot differences. Only13 bytes change inside19 bytes;4438 outside826 graph nodes agree. |
| [861 shared-tail controls](AYA_OBJECT_861_SHARED_TAIL_CONTROLS_2026_10_23.md) | Target861 joins826's phase/fade blocks. Shared-source candidates pass5168 position and3072 phase cases, but lose807's second zero-sequence read in2456 cases. All unselected. Interval audits now require actual per-action hits. |
| [852 RTM/fenv controls](AYA_OBJECT_852_RTM_AND_FENV_CONTROLS_2026_10_23.md) | RTM preserves SP1's unresolved conversion shapes. Both RTM objects pass 6528 scoped native cases; the profile changes other-action instructions. Local fenv keeps FIMUL and adds a double roundtrip; explicit if/else is byte-neutral to the int control. All unselected. |
| [903 paths/frame transitions](AYA_OBJECT_903_PATHS_AND_FRAME_TRANSITIONS_2026_10_23.md) | 13596 paired cases cover all ten sequences, real frame/next-block calls and twelve masked control words, including PC24. Effects and alpha/gate/timer read epochs agree. Old fade object is rejected despite equal effects; ordinary color helper is byte-neutral and unselected. |
| [Joint CIL replay](AYA_OBJECT_JOINT_CIL_REPLAY_2026_10_23.md) | Current update/init owner model links with twelve real native source providers. Full update replay consumes 362 HIGHLOW fields and seven switches, including six dense tables. Current and shared-control CIL payloads equal their native counterparts; shared807 still reads twice versus target three. Not an all-exact helper closure or DLL execution claim. |
| [807/854 read lifetimes](AYA_OBJECT_807_854_READ_LIFETIMES_2026_10_23.md) | 3968/3840 actual-code cases agree in strict mode; outside-action graphs preserve 4464/4481 nodes. |
| [807 angle lifetime](AYA_OBJECT_807_ANGLE_LIFETIME_2026_10_23.md) | Exact local 26-byte interval and live angle across alpha; historical sequence-read deficit is superseded by the row above. |
| [861 phase scope](AYA_OBJECT_861_PHASE_SCOPE_2026_10_23.md) | Phase/count advance only in initial sequence 0; 2304 predecessor state differences eliminated. Existing 768 alpha/X write-order differences remain explicit. |
| [801 fade snapshots](AYA_OBJECT_801_FADE_SNAPSHOTS_2026_10_22.md) | Alpha snapshot corrected; affected replay still has 3012 sequence-read differences. |
| [801/852 controls](AYA_OBJECT_801_CONTEXT_852_FACING_CONTROLS_2026_10_23.md) | Caching remains unselected. Latest826 report closes scoped817/822 sharing and820/826 execution gaps, but finds807's recovered26-byte interval is lost. The retry after826's fix still loses it.852 promotion/conversion placement remains open. |
| [Runtime owner context](AYA_OBJECT_RUNTIME_CONTEXT_2026_10_23.md) | Four layered/direct/typed/virtual controls were byte-neutral before826's correction; frozen payloads have the older17585ff8 hash. RTTI/allocation facts remain reproducible; nominal types and lifecycle remain open. |

Latest scope: `build/aya-joint-cil-20261023/`; preceding runtime scope:
`build/aya-903-read-epochs-20261023/`; preceding compiler controls:
`build/aya-852-rtm-20261023/`; preceding shared-tail controls:
`build/aya-861-owner-y-20261023/`. The preceding 801 impact scope
is `build/aya-801-impact-20261023/`. Earlier owner-context scope's
accepted pool replay is 15/15 exact, including Aya acquire `0x617DF0` (519 bytes).
Earlier selected 804/810 sequence, 821 counter and 903 fade corrections remain
in source; links and epoch-specific hashes are in the historical handoff.

Next leads: supported visibility/lifetime/ownership context for 852's early
promotion and branch-local conversion placement. Native RTM, local fenv access
and explicit if/else did not recover that shape in the tested context.
Preserve 807's second zero-sequence read
before selecting 861/826 shared source. `/Ob1` and tiny getters are byte-neutral
in the tested shared-phase context. Native RTM's payload is 4 bytes longer and
keeps the read deficit. Other leads are 807's facing-capture/scratch scheduling
before selecting 801 caching, common frame tails, register and scratch placement.
903 now has a broader non-spawning behavioral check, including frame dispatch;
its shared fade/color/retirement placement still needs distinct context evidence.
The current two-body CIL/native-provider context is byte-neutral after complete
caller replay; the old eight-byte CIL result belongs to the earlier source epoch.
Failed local controls do not prove an LTCG
impossibility. Rebase trials onto current source rather than frozen predecessors.
Native fixtures have scoped limits; inspect their placement assumptions and
Python callback exception guards before reuse. Private flow-alignment diagnostics
are incomplete and are not acceptance evidence.

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
restoration. Private inventory: `build/handoff-cleanup-20261023/manifest.json`.
Historical reports may end in `.gz`; restore with `gzip -dk PATH.gz` before
using old recipes. Latest owner-context objects/receipts and affected accepted
pool receipt remain directly available. Six dirty detached worktrees are retained.

After the final tracked edit, before every commit/push/PR:

```sh
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Mandatory local CI baseline: 462 tests. No private reports, executables, game
data, databases, compilers or credentials in commits. Verify remote HEAD after
an authorized push and leave the main worktree clean for the next session.
