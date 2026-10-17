# Iku whole-root dispatch and physical action ownership

> Historical dispatch checkpoint. The current
> [payload lifetime checkpoint](IKU_PAYLOAD_LIFETIMES_2026_10_17.md) recovers
> the target stack frame and supersedes the source/codegen receipts below.

The selected source for `Iku_dispatch_action_state_vslot28 @ 620920` now uses
one ascending action switch with individual case bodies. It retains all 110
actions and the original void entry/prelude/default from the
[first complete-source checkpoint](IKU_FULL_ROOT_SOURCE_2026_10_17.md).
The actual root naturally recovers the target's three 33/42/35-entry tables
and all **108 physical table destinations**, with no split or merged target
owner. Whole-root canonical comparison remains **nonexact at +8**. No partial
or exact authored credit is added.

## Target observations and source inference

Target identity is unchanged: original Japanese TH10.5 v1.06a SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The root's 59,038 bytes retain SHA-256
`abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea`.
Its raw CFG closes 15,132 instructions and 131 RETs. The new `iku-vslot28`
entry in `config/giant-action-switches.toml` pins the three destination/index
arrays, their physical groups, 865 decoded direct CALLs to 32 targets and the
RET census. The raw E8 census independently agrees with the decoded calls.
This work uses hash-attested PE instructions; the wrong-image IDA session is
rejected by metadata preflight and no analysis database is modified.

The former source routed through several status methods and grouped actions
with runtime family flags. It produced six tables and only 36,703 callable
bytes. A private intermediate combining the switches, but retaining most
groups, produced four tables and 42,749 callable bytes. The selected source
then separates the target's physically independent actions and specializes
their entry-snapshot action/airborne/variant decisions. Later field reads
after real callbacks remain live. Constant predicates and unused snapshot
locals are removed; payloads, floating expressions, access widths, ordering
and ordinary helper interfaces remain. The unified status method and glide
method still express source sharing and are forced inline into the real void
entry; no original standalone boundaries are claimed.

This is a reorganization of the manually recovered C++, not decompiler
copying. A disposable Clang syntax/AST check assisted removal of constant
branches in the private draft; it supplies no target, VC8 or byte-equality
evidence. Only the pinned VC8 SP1 build is compared and executed. No padding,
assembly, inert locals, register forcing or fabricated callee addresses are
introduced. The shared header, profile, canonical bindings and unit partition
are unchanged.

## Actual COFF root and owner evidence

| Measure | Target | Selected VC8 root |
| --- | ---: | ---: |
| Callable bytes | 59,038 | 58,427 |
| Instructions | 15,132 | 15,037 |
| RETs | 131 | 129 |
| Sparse dispatch tables | 33 / 42 / 35 | 33 / 42 / 35 |
| Table destinations across all three regions | 108 | 108 |
| Entry stack frame | 0x400 | 0x4A8 |
| Ordinary / register CALLs | 865 / 177 | 867 / 167 |

The candidate has no local CALL relocation, no external tail and no unreached
byte in its callable CFG. Its 59,582-byte section comprises 58,427 callable
bytes, one leading metadata-alignment byte and 1,154 following bytes of
tables/index arrays with internal alignment. The target has two leading
alignment bytes before the same 1,154-byte metadata structure. The owner
mapper includes that candidate alignment byte in its 58,428-byte partition;
the full-root CFG audit correctly excludes it from callable bytes.

The physical-owner audit reports **5/109 instruction/edge-identical
diagnostics**, including the entry in its denominator: actions 2, 4, 5, 204
and 303. Internal edges are compared by physical owner plus byte offset;
opcodes, widths, external targets and short/near encodings remain significant.
These diagnostics are not canonical equality or independently owned functions.
Direct actions 300/560 are checked by the full-root selector/CFG audit; they
are not extra table destinations or separate owners in this partition.

The larger standalone status COMDAT is 60,326 bytes. The old largest-`.text`
heuristic selected it instead of the 59,582-byte void root; the owner auditor's
configured-symbol check rejected that selection. The COFF reader now accepts
an explicit exact root symbol and loads its section **and its own relocation
table**. The owner audit supplies its configured unit symbol; the span CLI
offers `--symbol`. Default inference for old callers is unchanged. Two new
tests cover a smaller root beside a larger COMDAT with different relocations,
plus missing, external-only, duplicate, nonzero-offset and data-section roots.

The Iku CFG audit also replays the actual candidate section tail, rather than
only the target callable size. Otherwise its final high table remains raw
when a candidate section exceeds 59,038 bytes. This is a diagnostic extent
fix; the canonical comparator and its accepted target extent are unchanged.

CALL-site sharing still differs. Relative to target, candidate direct sites
change by -2 at 4351C0, +4 at 435240, -1 at 4359F0, +1 at 435D60, -1 at
45C030 and +1 at 478E60; register sites change by -10. These are static
ownership differences, not yet evidence of missing behavior. Next work is
joint call/tail sharing and floating/payload temporary lifetimes. Fixing only
the first stack-size operand would not solve this root, and the present result
does not establish an LTCG barrier.

## Focused native and canonical results

The selected source passes **0/16,285 whole-entry smoke cases**, reaching
12,769 genuine RETs and 3,516 first backend/runtime entries. It visits 10,195
target-root instructions. Both roots execute their own prelude and actual
motion/frame/landing/RNG/event/audio/counter/math dependencies. Full actor,
calls/arguments/payloads, globals/RNG, conversion inputs, RET stack/callee
saves, empty x87 and control-word checks remain. First backend/runtime stops
and the explicit fixture limitations from the preceding checkpoint remain;
post-backend and exceptional continuations are unverified.

The smoke collection is checked as a subset of the earlier 26,783 passing
inputs. That expanded matrix is **not** replayed after this source change.
Current negative controls still detect the prelude-countdown error in 60/60
cases and unordered glide-facing error in 28/48. Both are subsets of the
passing current smoke collection. The projected-height control now finds its
case after the new explicit case scope; all eight control generators identify
their intended unique expressions.

Current receipts:

- Final C++ SHA-256, CRLF on disk:
  `1c92dbcc89be4e05b0f0ae76237d25e73b103af714ff793e5328f17c1534bc10`;
- smoke input SHA-256:
  `74b221b4ed574beb84cdfb324f2298645fd787ed48696486c05568598da3d1e6`;
- target-output SHA-256:
  `dd68c4cd32ae4a96d7cc2d0b5ffef5f9ce8dc1c58a43a91ef68416e1f1e7051e`;
- full canonical-replayed candidate section SHA-256:
  `2c8e3d6e0e5cb2e2ebb946452b438d60c8e0b57162cc3bd66901c771ab9af9cc`.

The 16,285-case run compiled the unfolded private draft, SHA-256
`b1eb193b87a9e88afdfdd0e8712203258cb21b08d708a7ebdc403af3e2e7bf60`.
Final source cleanup expresses actions 0/2 as ignoring the advance result,
removing their empty conditional bodies, plus redundant parentheses/spacing.
The freshly rebuilt configured unit replays to identical full-section bytes
as that native-tested draft; its evidence therefore still covers the actual
compiled root. A focused final-source run additionally passes **0/275** for
actions 0/2, with the final source hash in its receipt. That object also replays
to identical full-section bytes. No broad native replay follows the neutral
cleanup. `--actions` now selects explicit IDs and rejects absent IDs, allowing
subsequent focused work without repeating all action fixtures.
The formal 59,038-byte comparison resolves its relocations and fails at
620928/+8: target frame 0x400 versus candidate 0x4A8. No exact ledger changes,
aggregate replay or fresh aggregate percentage is claimed. All unrelated
accepted sources, headers, flags and relocation mappings are unchanged.

```bash
python3 scripts/build.py --unit gpt-web-iku-action-state --compare --json > build/iku-codegen-final-compare.json
python3 scripts/probe-iku-upper-actions.py --all-actions --smoke --output build/IkuCodegenUnfoldedNative.obj > build/iku-codegen-unfolded-native.json
python3 scripts/audit-iku-full-root.py --object build/match-units/GptWeb_IkuActionState.obj --native-object build/IkuCodegenUnfoldedNative.obj > build/iku-codegen-final-facts.json
python3 scripts/probe-iku-upper-actions.py --opening --whole --smoke --actions 0 2 --output build/IkuCodegenPolishedNative.obj > build/iku-codegen-polished-native.json
python3 scripts/audit-iku-full-root.py --object build/match-units/GptWeb_IkuActionState.obj --native-object build/IkuCodegenPolishedNative.obj > build/iku-codegen-polished-facts.json
python3 scripts/compare-giant-action-switches.py iku-vslot28 build/match-units/GptWeb_IkuActionState.obj --symbol '?dispatch_action_state_vslot28@IkuActionStateView@th105@@QAEXXZ' --json > build/iku-codegen-final-topology.json
python3 scripts/audit-giant-action-owners.py iku-vslot28 build/match-units/GptWeb_IkuActionState.obj --unit gpt-web-iku-action-state --json > build/iku-codegen-final-owners.json
python3 scripts/probe-iku-upper-actions.py --opening --whole --smoke --control prelude-countdown > build/iku-codegen-countdown-control.json
python3 scripts/probe-iku-upper-actions.py --opening --whole --smoke --control unordered-face > build/iku-codegen-face-control.json
python3 scripts/validate-tracking.py --require-target
python3 scripts/ci.py
git diff --check
```

The formal comparison and negative controls intentionally exit nonzero.
The final local CI gate passes all 202 workflow tests and its ledger, graph,
literal, generated-progress and whitespace checks.
Generated objects/reports stay below `build/`; private drafts stay below
`.analysis/`. The disposable 49 MiB AST dump is removed. Full receiver layout,
original source/TU ownership, exceptions and later backend behavior remain
unknown.
