# TH10.5 reconstruction handoff

Reconstruction resumed 2026-10-23. Current game source selects the float lookup
caller view after checkpoint `a04ba76`; 852's product operand-read and 826's
owner-Y corrections remain selected. Previous cleanup checkpoint: `1865c6a`.
Required commit format: `gpt-6.1-sol: ...`.

Latest user priority: whole-function exact first, gameplay naming later.
Read-only TH075 review supports typed offset source, minimal receiver views,
independently verified family reuse and short full-function compile/compare
loops. See the [workflow](RE_WORKFLOW.md#exact-first-priority-from-the-th075-review).
Do not spend another large matrix on an uncertainty that a strict build can
resolve. Preserve necessary ABI, storage widths, control flow and side effects.

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

These are ledger totals. This checkpoint makes no aggregate cold-replay claim.
Shared header/layout/profile/partition/relocation changes require affected
accepted-unit replay; new aggregate claims require `verify-exact-units.py --all`.

## AyaObject update 0x61A290

Selected [source](../src/characters/AyaObjectActionState.cpp), unit
`gpt-web-aya-object-vslot28-full-root`. Callable ledger size 19522;
complete canonical payload 20120, metadata starts at 19652, full SHA256:
`fad6fa5af2baa1d8b9013d3fe7279bcfea3f136474a0bb9f9a0a52ccd30caf2c`.
Fresh restored comparison remains **nonexact +0x22**, target `0F` / source `8E`.
No root exact credit. The adjacent metadata is not added to the callable boundary.

Source SHA256:
`da5c622d4808d6dd1516dee567923ede8f1a2c6c4ae0655730ba006505710f46`.
The first mismatch is the initial JA displacement. The
[evidence index](AYA_OBJECT_EVIDENCE.md) separates selected changes, scoped
behavioral checks and rejected context controls, with source-epoch limits.

Latest scope: `build/aya-852-sharing-context-20261023/`. Two root-local float
lookup declarations change only sixteen ordinary bytes in four FLD/FADD pairs
to target scale/rate read order. All 18,576 selected operand-read traces agree;
861 retains 3,096 known alpha/position ordered-write differences. All other
complete-payload bytes agree at A and S. See [the selected evidence](AYA_OBJECT_FLOAT_LOOKUP_SCALE_READS_2026_10_23.md).

The preceding 852 matrix's 9,728 actual-return inputs remain applicable because
reachable 852 code is unchanged; it was not rerun. Its 4,558 outside-product
graph pairs plus one qualified tail carrier were revalidated after fixing a
fabricated JMP fallthrough in the normal-flow utility. Four new CFG tests pass.

Current-source joint CIL replay equals native: seven switches, 362 HIGHLOW
fields and 123 direct calls are closed. Seventeen of nineteen requested
dependencies compare exact; restoring the already accepted 57-byte helper
leaves only the two lookup providers nonexact. No DLL execution or original TU
claim. The original global lookup return declaration remains unresolved.
Earlier controls retain their own source epochs in the evidence index.

Latest experiments: `build/aya-exact-first-source-20261023/`; public selection
is unchanged. [Seventeen whole-root source controls](AYA_OBJECT_EXACT_FIRST_SOURCE_CONTROLS_2026_10_23.md)
exclude the tested typed-offset/minimal-owner forms and forceinline member
tail, all byte-neutral. Raw target shares one frame/sequence2 tail across
801/807/811/817/822/854; baseline emits three sites. Explicit sharing can reduce
payload to20000 bytes but either hoists MOV EDI,2 before dispatch or reverses
all four recovered scale-read pairs. Neither smaller candidate is selected.
Local fenv and the tested sum forms do not fix that reversal. An ordinary
member helper retains five root calls in a genuine joint LTCG image and has
no supported target binding. No new exact credit.

Resume with one target-backed lead:

- Reproduce the six-action physical tail sharing at target61A5DB while keeping
  the original dispatcher and selected scale-read order. Compare the complete
  root first; current explicit-label/break and ordinary-helper controls do not
  establish the original source form. Preserve the selected source epoch when
  interpreting any return-view or operand-order result.
- Preserve 852's recovered live facing at the speed read. Target has two
  branch-local FILDs; current source hoists one before the branch. Tail EAX now
  agrees, but scratch remains ESP+0x18 rather than target +0x14.
- Preserve 807's second zero-sequence read before selecting shared 826/861 tails
  or 801 caching. Both shared-tail variants were rebased onto the selected float
  epoch and still lose that read in one actual-return witness.
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
taskset -c 0 nice -n 10 python3 scripts/audit-aya-object-852-native.py --product-read-lifetimes
taskset -c 0 nice -n 10 python3 scripts/audit-aya-object-scale-adds.py --actions 826 --position-lifetimes
taskset -c 0 nice -n 10 python3 scripts/audit-aya-object-scale-adds.py --actions 820 826 853 861 --scale-read-lifetimes --diagnostic
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
Latest focused public build, unchanged-input identity and final gate receipts
are `build/aya-exact-first-source-20261023/{baseline,final-state}.json` and
`build/aya-exact-first-source-20261023/ci.log`. Selected native observations
remain in `build/aya-852-sharing-context-20261023/scale-read-lifetimes.json`.
Root mismatch `+0x22` is
expected; the scale-read matrix uses explicit diagnostic mode and keeps the
3,096 known 861 write differences visible. Earlier 852 negative-control results
remain in `build/aya-852-expression-20261023/`.
Historical reports may end in `.gz`; restore with `gzip -dk PATH.gz` before
using old recipes. Current objects, frozen controls, receipts and provider inputs remain directly
available. Six dirty detached worktrees are retained.

After the final tracked edit, before every commit/push/PR:

```sh
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Mandatory local CI baseline: 466 tests. No private reports, executables, game
data, databases, compilers or credentials in commits. Verify remote HEAD after
an authorized push and leave the main worktree clean for the next session.
