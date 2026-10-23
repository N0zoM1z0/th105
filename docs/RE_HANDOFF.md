# TH10.5 reconstruction handoff

Reconstruction resumed 2026-10-23. Current source selects a partial807/817 frame
tail,817/822 angle captures and local double lookup views at `4adc63c`.
852's product-read and826's owner-Y corrections remain selected.
The latest Youmu initializer checkpoint restores its physical tail copies and
all metadata;21 callable register/preparation bytes remain. Reimu's local owner
selector retains the signed-word correction. Exact ledgers are unchanged.
Current bounded continuation: Youmu543670's five remaining call/register regions.
Previous cleanup checkpoint: `1865c6a`.
Required commit format: `gpt-6.1-sol: ...`.

Latest user priority: whole-function exact first, gameplay naming later.
Read-only TH075 review supports typed offset source, minimal receiver views,
independently verified family reuse and short full-function compile/compare
loops. See the [workflow](RE_WORKFLOW.md#exact-first-priority-from-the-th075-review).
The refreshed peer snapshot `4aeea7a` includes a 31352-byte exact callable.
A private Youmu pointer-only/offset-field control keeps the entire 5492-byte
canonical payload identical to `206b30d`, including the 21 remaining differences;
it is a bounded negative, with no public source or exact-ledger change.
Further conversion/receiver/forwarding and numeric-case-order controls keep
the same complete payload. A real member-pointer CIL link retains an extra
generated thunk and is rejected; see the [dispatch controls](YOUMU_ENTRY_PHYSICAL_TAIL_2026_10_23.md#dispatch-source-controls).
On October 24, sequence selector `0x45C390` now uses real checked `std::map::find`;
all 10 functions in its accepted native object and the separate short ABI
witness replay exact. Its emitted 105-byte find equals the existing excluded
compiler island `0x45C320`. Same-class short/int selector CIL visibility still keeps
Youmu's 21 differences; full map CIL changes selector frame/private-call shape
and is rejected. See the [visibility result](YOUMU_ENTRY_PHYSICAL_TAIL_2026_10_23.md#selector-visibility-and-native-map-implementation-2026-10-24).
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
complete canonical payload 20000, metadata starts at19532, full SHA256:
`5f2966cb6b34c844d210ac54e52894b5d510c17362c3fe2424c1d2de6b89c4ec`.
Fresh comparison remains **nonexact +0x22**, target `0F` / source `16`.
No root exact credit. The adjacent metadata is not added to the callable boundary.

Source SHA256:
`59bcfc3149acb4cfe422451e0198ae92c49639894e0812206a578924b6cec928`.
The first mismatch is the initial JA displacement. The
[evidence index](AYA_OBJECT_EVIDENCE.md) separates selected changes, scoped
behavioral checks and rejected context controls, with source-epoch limits.

Latest scope: `build/aya-tail-callviews-20261023/`. The selected partial exit
join removes120 payload bytes and one frame-helper site (13 to12; target11).
Both local double lookup views restore the four scale read orders in this
context. Used float angle snapshots retain target817/822 rotation before alpha.
See [the selected evidence](AYA_OBJECT_PARTIAL_FRAME_TAIL_2026_10_23.md).

A complete source graph proof pairs4569 nodes, excluding no actions/windows.
It checks one delayed MOV ECX,ESI across seven identical floating instructions
and a contracted internal JMP, before the same normal thiscall. Target807 also
loads the receiver at the common tail. All field/x87 observations are preserved
under that contract; callback/unmasked-exception register observers are outside
the proof. The807 native witness retains three reads. The preceding852 matrix
(9,728 cases) and scale matrix (18,576 cases) were not rerun; their scoped observations transfer
through this proof. The known861 alpha-before-X write-order issue remains.

Current joint CIL replay equals native: seven switches,362 HIGHLOW fields,
122 calls,287 literal references and three game-data references. The consistent
double-view provider context retains earlier16/19 results with input hashes
rechecked: two lookups and its private oriented body remain nonexact. The public
accepted float-view435160 unit remains57/57. No DLL execution, original TU or
unique original lookup declaration claim. Earlier float-context17/19 results
retain their own source epoch.

Hard 826/861 sharing still loses807's second zero-sequence read on this epoch.
Natural owner-Y captures preserve that read but move861 alpha after Y/scale-X;
even19992-byte/+0x1C7 candidates are rejected. Fresh RTM controls also remain
nonexact. The preceding offset/minimal-owner, forceinline and sum controls keep
their specific limits in the evidence index. The function-internal fenv pragmas
emit C4177 and are not a valid local fenv test. No new exact credit.

Resume with one target-backed lead:

- Reproduce the six-action physical tail sharing at target61A5DB while keeping
  the dispatcher and recovered read lifetimes. Source now has two sites for
  that six-action tail instead of three; one extra physical call remains.
  Preserve the selected source epoch when interpreting return-view effects.
- Recover861's X/alpha/Y store order together with807's repeated read. Tested
  hard joins fix861 but lose the read; natural Y captures keep the read but
  put alpha too late. Do not select a candidate only for its shorter prefix.
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
The [word-selector/joint-context refresh](REIMU_OBJECT_WORD_OWNER_JOINT_CONTEXT_2026_10_23.md)
selects short in both local owner declarations, preserving all native bytes.
Header SHA256 is `a8603fd542e9c19dcfef3009e50283b3aef42acde72768ae1a735192b01911fa`.
One consistent update/init TU reproduces both native payloads. Genuine joint
LTCG with20 real providers still leaves initializer4A1CE0's14 differences;
all247 fields/181 HIGHLOW entries close and metadata stays equal. Its fresh
596370 provider is323/323. Linked update differs at entry; no complete linked
update comparison is claimed. Original partition and906/999 allocation stay open.
Physical call/RET sharing remains open. Aya initializer `0x61F0B0` retains two
register-byte differences, +BF7/+BFF, in its4531-byte callable/4859-byte envelope.
The [fresh source and /Zi controls](AYA_ENTRY_SEQUENCE_WORD_ABI_2026_10_19.md#exact-first-refresh-2026-10-23)
leave selected source5ca0fb42 and canonical6f70b6f3 unchanged. `/Zi` now genuinely
compiles after private PDB/NTLM setup; it does not fix the register choice.
Typed payload APIs, full856 inlining and real lifetime controls were also
unsuccessful. Do not repeat them or count register-equivalent code as exact.
Youmu initializer `0x543670` now has a complete5159-byte callable with1294
instructions,78 calls/21 conversions and23 RETs; its natural NOP and all332
metadata bytes agree. Full5492-byte canonical SHA256 is
`d00f4fc4ceca80c8fc4510ff03dcf064e3188fa5dc33afc8e25815d880da413a`;
source SHA256 `66d01e60ca540b11515ebe4a58dc87f913ab340dd4845bcb1e992d9000c9be2d`.
It remains nonexact with21 body bytes, first+0x74F/543DBF, across850/851/848/855/856.
Captured821 parameters and explicit812/854 entries restore the848 handoff;
850 uses the same verified int facade as851. Public592-case actual-return
audit passes, including851's four ABI stress inputs. Genuine23-provider
LTCG fully replays229 fields/149 HIGHLOW and equals the native result.
See [the selected evidence](YOUMU_ENTRY_PHYSICAL_TAIL_2026_10_23.md).
Remaining work is call preparation and register allocation; keep the recovered
copy count, read order and metadata. Earlier owner scores are diagnostics only.

Other pending roots: Reimu Fighter `0x478FA0`,
initializer `0x4A1CE0`, CGage `0x41B3F0`,
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
are `build/aya-tail-callviews-20261023/{final-formal,final-identity,oriented-anchor}.json`
and `build/aya-tail-callviews-20261023/ci.log`. Earlier native observations
remain in `build/aya-852-sharing-context-20261023/scale-read-lifetimes.json`;
their source-graph transfer has the limits described above.
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
