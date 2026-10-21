# TH10.5 reconstruction handoff

Current as of 2026-10-21. Reconstruction is **paused at the user's request**.
This checkpoint organizes documentation and local artifacts; it does not select
new reconstruction source or add exact credit. Last reconstruction commit:
`523d728` (`gpt-6.1-sol: recover native checked character access in font markup`).
There is no unfinished source edit or running build to carry over.

The previous 845-line operational record is preserved in the
[October 21 snapshot](RE_HANDOFF_HISTORY_2026_10_21.md). Dated evidence pages and
snapshots describe their own source/object epochs. The live ledgers and fresh
canonical comparisons override historical prose and old next-step lists.

## Target and startup checks

Use only original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Read [AGENTS.md](../AGENTS.md), [architecture](ARCHITECTURE.md),
[workflow](RE_WORKFLOW.md) and the relevant source before changing state.
Use one writable session, one bounded unit, serial VC8 builds and nice10/CPU0.
Do not delegate matching. Commits use English `gpt-6.1-sol: ...`; commit and push
stable checkpoints. Resume reconstruction only when the user asks.

```bash
git status --short
python3 scripts/verify-target.py
python3 scripts/check-ida-mcp.py
python3 scripts/report-reconstruction-status.py --summary
python3 scripts/validate-tracking.py --require-target
```

Target verification and tracking pass. IDA preflight rejects the open image:
SHA256 `10350095bcf95edb59e03bee9849a2dc8a7714b4927ad5909c569c550fce6822`.
Do not use that session's semantics or write metadata. Hash-attested raw PE
inspection remains available. Independently attest a Ghidra project before
semantic use; keep one process and read back metadata changes. Never patch
canonical target bytes. The private primary project and its nine-file pins
are described in [artifact retention](ARTIFACTS.md).

## Ledger snapshot

| Layer | Current value |
| --- | ---: |
| Provisional candidates | 4,024 |
| Authored / excluded / origin review | 1,591 / 1,418 / 1,015 |
| Durable mappings / source-present | 1,515 / 1,497 |
| Accepted authored exact | 1,374 functions / 233,060 bytes |
| Match units / configured functions | 538 / 1,507 |

These are ledger counts, not a new all-unit verification claim. No aggregate
cold replay was run for cleanup. The SVG visibly fills exact bytes against the
provisional authored denominator (233,060 / 2,135,634 = 10.91%) and shows origin
review separately (74.78% resolved). [Generated progress](PROGRESS.md) and the
SVG remain unchanged. `implemented.csv` means source-present; `matches.csv`
means accepted exact; `claims.csv` remains header-only.

## Current font source and comparison

| Source entry | Purpose |
| --- | --- |
| [TextFontOwner.hpp](../src/assets/TextFontOwner.hpp) | Native configuration and 0x194-byte owner layout |
| [TextFontRuntime.hpp](../src/assets/TextFontRuntime.hpp) | Shared owner alias and rendering data types |
| [TextFontOwner.cpp](../src/assets/TextFontOwner.cpp) | Constructor, destructor and configuration |
| [TextFontRender.cpp](../src/assets/TextFontRender.cpp) | Real rendering caller and file-local providers |

The fresh pre-cleanup build at `523d728` reproduces all 12 configured render
comparisons in `build/font-markup-lifetime-20261021/baseline-formal.json`,
including all canonical hashes from the selected
`build/font-markup-stack-20261021/formal.json`. Eight functions remain nonexact;
three accepted leaves and one uncredited helper are byte-equal.

| Address / operation | Source / target bytes | Current result |
| --- | ---: | --- |
| 411760 surface setter | 45 / 45 | Accepted exact |
| 4127C0 outline blend | 289 / 289 | Accepted exact |
| 4128F0 hex decoder | 45 / 45 | Accepted exact |
| 412920 checked character | 33 / 33 | Canonical byte equality; origin review, no authored credit |
| 411FA0 markup | 1728 / 1744 | Nonexact at 411FB0 / +16; frame reservation 788 / 796 |
| 411B80 glyph | 624 / 624 | Nonexact at +89; differences confined to +88..103 |
| 412670 render caller | 323 / 326 | Nonexact at entry; target aligned EBP frame differs |
| 4119A0 begin / 411AD0 end | 291 / 291; 168 / 168 | Nonexact at +7 |
| 411DF0 accent | 433 / 417 | Nonexact at +5; native ESI allocation unresolved |
| 411790 color / 4118F0 reset | 332 / 352; 161 / 162 | Nonexact at +2 / +7 |

Markup now naturally receives font in EDX, height output in ECX and two stack
arguments, with RET8. Its full canonical source hash is
`a3c2e09c65e0af2c63da0a20950896721a938a3299bc3cf12b4ed600f99296ff`.
The checked-character operation is a real `std::string::at` wrapper with six
actual EAX/EDI calls; authored wrapper versus specialized library ownership is
unresolved. Do not turn byte equality into an authored match or exclusion.
The local O2/Ob1 profile preserves actual helper calls; default O2's unused exact
copy with an inlined caller is insufficient caller evidence.

Latest evidence: [checked markup and stack facts](TEXT_FONT_MARKUP_CHECKED_2026_10_21.md),
[native markup ABI](TEXT_FONT_MARKUP_NATIVE_2026_10_21.md),
[surface exact](TEXT_FONT_SURFACE_EXACT_2026_10_21.md),
[glyph lifetime](TEXT_FONT_GLYPH_NATIVE_2026_10_21.md) and
[blend exact](TEXT_FONT_BLEND_EXACT_2026_10_21.md).
The owner unit retains accepted config constructor 67, owner constructor 138,
destructor 210 and configure 439 bytes; compiler cleanup witnesses confer no
authored credit. See [configuration exact](TEXT_FONT_OWNER_CONFIG_EXACT_2026_10_21.md).

Latest bounded execution receipts retain 92/92 checked-character cases and
2,400/2,400 affected parent cases, with 6,720 actual helper calls per side and
480 range-error-entry stops. Other providers remain observers; actual exception
unwinding, GDI, allocation failure and arbitrary aliasing are unqualified.
The preceding 8,640-parent/280-caller receipts have their own source epoch.
EH state graphs agree, but handler/funclet metadata and runtime unwinding remain
open. Current length/length+1 stack homes and delayed argument cleanup differ;
the 8-byte frame residual does not establish padding or a larger owner type.

The interrupted next scope, `font-markup-lifetime-20261021`, contains only
preflight, baseline and raw constructor-call census reports. No source/layout
change or new compiler conclusion was selected. Recipes for the latest accepted
checkpoint remain in `.analysis/font-markup-stack-20261021/`.

## Larger roots and resumption points

ReimuObject update `0x496540` is still **nonexact at 0x49655F / +31**. The
selected source remains
[ReimuObjectActionStateStaging.cpp](../src/characters/ReimuObjectActionStateStaging.cpp),
SHA256 `3b9e4896c3645bb1228db3b432a832154870c5639a80df6c02cb67ce2dba12cc`;
complete 45,700-byte canonical section SHA256
`d0ff3d3259c823cc56e322c5e0ec238456d8b490c78b4a5336a249b45a405a58`.
The 46,138-byte owned comparison includes 46,128 code bytes and 10 alignment
bytes. The selected source has 428 physical calls / 63 RETs versus 433 / 68;
call/RET membership distances remain 11 / 27. Same-TU counter `4963A0` is
accepted exact 66/66. Interior equal windows confer no partial exact credit.

811's 161-byte request window and 640 bounded prefixes agree, while 822's
request register/constant allocation, 908's post-wave x87 order, and remaining
call/RET ownership stay open. Opaque World/wave entries are execution stops;
no whole-root proof or fabricated return follows. ECX/RET0/caller ignoring EAX
are observations; `void` is an inferred source view, not a proven original
return type. See [Reimu evidence index](REIMU_OBJECT_EVIDENCE.md) and
[811 selected checkpoint](REIMU_OBJECT_811_COORDINATE_ARGUMENTS_2026_10_21.md).

Other open roots remain recorded in the October 21 snapshot: Reimu Fighter
478FA0, ReimuObject initializer 4A1CE0, YoumuObject initializer 543670, AyaObject
initializer 61F0B0, CGage 41B3F0, CDesignBase loader 40B000 and floating-number
renderer 415050. Do not infer an LTCG or standalone-object impossibility from
an unsuccessful control. Recheck old assumptions against target evidence.
When work resumes, choose one bounded address; preserve both the large-root
objective and smaller exact opportunities without routine all-history replay.

## Reproduction and final gate

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-text-font-render --compare --json
# Expected mixed result: 8 mismatches, 3 accepted exact leaves, 1 byte-equal review helper.
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-text-font-owner --compare --json
# Expected accepted owner/config roots exact; compiler witnesses are separate.
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-reimu-object-action-state --compare --json
# Expected mixed result: 496540 nonexact +31, 4963A0 exact 66/66.
```

Run only the relevant command for the chosen scope. Replay every affected
accepted unit after shared header/layout/profile/partition/binding edits.
A fresh aggregate claim requires `python3 scripts/verify-exact-units.py --all`.

[Artifact retention and recovery](ARTIFACTS.md) lists the cleanup inventory,
retained inputs and restoration commands. Reconstruction source, ABI/layout,
compiler profiles, ledgers and progress artifacts were left unchanged during
cleanup. Historical bulk reports are losslessly compressed; selected objects,
private recipes, target, toolchains, primary databases and detached worktrees
are preserved. The original 845-line handoff is retained verbatim in its dated
snapshot; use this page for current state.

Before every commit, push or pull request, run in the finished worktree:

```bash
python3 scripts/ci.py
git diff --check
```

The local gate is mandatory after the last tracked edit. Cleanup validation
passes all 430 workflow tests, target/tracking checks, local documentation links,
compressed-report/archive SHA256 recovery and `git diff --check`. The local CI
receipt is `build/handoff-cleanup-20261021/ci-final.log`.
Do not commit private reports, executable/game data, databases, toolchains or
credentials. Verify remote HEAD and a clean worktree after pushing.
