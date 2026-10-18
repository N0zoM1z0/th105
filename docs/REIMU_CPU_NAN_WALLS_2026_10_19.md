# Reimu CPU unordered wall predicates, 2026-10-19

Two policy0 wall guards in the15999-byte root at48D390 now negate ordered
wall predicates explicitly. The previous >=/<= rewrite chose different
policies and RNG bounds for NaN X positions. Both fixes are supported by raw
target instructions and actual-helper counterexamples. Whole-root strict
comparison remains nonexact at+12E/48D4BE; no exact credit is added.

## Identity and observed failures

Use only original Japanese1.06a, executable SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Callable `[48D390,49120F)` SHA256 is
`3bd363994e140603ae0ec249ffd3a36b1ae0448e72a389e417c4cc7a6d113e2d`.
The authored virtual identity, void ECX ABI, complete root boundary and four
metadata-table contracts are unchanged.

The previous selection matrices used finite X positions; the height/NaN suite
varied Y. Those passing reports did not establish unordered X behavior.
An8080-case exceptional-X subset using height pairs(0,0),(0,100),(100,0)
and(100,200) finds60 differences in the prior selected
`d3b9a023` payload. A real counterexample has seed35/selection roll30,
facing1, selfY100, peerY0, self X bits7FC00000 and peerX190:

| Actual execution | Policy766 | Timer768 | Selector limits |
| --- | --- | --- | --- |
| Target | 0 | 40 | 1000,100,60 |
| Previous source | 11 | 35 | 1000,100,30 |

The root's third real MT draw is2905646007. Its selector result is40 for bound60
and20 for bound30; source then adds15. Neither result is injected. Quiet and
signaling NaNs and both facings expose the same erroneous arm.

Fixing the first guard passes that8080-case subset, but expanding to all ten
selection-height pairs still finds200 differences in20200 cases. A second
counterexample has seed89/roll25, facing1, selfY0, peerY300, self X7FC00000
and peerX190. Target keeps policy0/timer6 with selector limits1000,100,10;
the one-guard candidate selects policy9/timer35 with limits1000,100,30.
This identifies the second close-distance wall guard independently.

## Instruction evidence and source correction

Actual target traces for the two counterexamples execute:

- Air/ground path: FCOMP at49076E, FNSTSW490774, TEST AH,5 at490776 and
  JNP490779. Unordered comparison leaves both tested bits set; the positive
  ordered-less wall branch is not taken. Target reaches the real bound60
  selector at491180 and RET491196.
- Ground/air path: FCOMP490273, FNSTSW490279, TEST AH,5 at49027B and
  JNP49027E. The same unordered rejection reaches the real bound10 selector
  at490703 and RET490719.

The old candidate instead tests only C0 for the facing1 leg, using
TEST DL,AH while DL is1. Its facing-1 leg also treats the opposite ordered
relation as a complement. That loses the unordered case. The selected source
uses `!((facing == 1 && x < 240) || (facing == -1 && x > 1040))` in those
two guards. It preserves bounds, memory widths, real calls and assignment
ordering. No compiler mode, volatile qualifier, helper result, ABI or target
byte is changed. Other wall predicates are not generalized without evidence.

An encoding-preserving source-to-source comparison covers all4008 functional
instruction ordinals. Only eight instructions differ: four TEST/Jcc pairs
for the two directional legs of the two guards. TEST DL,AH/JNE becomes
TEST AH,5/JNP; TEST AH,1/JE becomes TEST AH,5/JP. All other instruction
encodings and direct-edge destinations agree after mapping addresses to
instruction ordinals. External targets and literal identities are retained.

All eight code DIR32 operands still name the same metadata-relative tables;
all47 metadata code pointers still name the same instruction ordinals and
remaining metadata bytes agree. Before policy0, the only byte differences
are the eight local table addresses moving by4. Functional instruction lengths
grow by2 bytes, plus genuine compiler post-RET alignment8BFF; source adds no
padding. Prefix/payload change15916/16457 ->15920/16461. This normalization
qualifies unaffected source regions, not equality to target or partial credit.

Root selectors/RETs remain118/48 versus target121/52. Reachable policy0 still
has1385 instructions,34 selectors and46 RETs, with no JA/JBE branches. Wrong
terminal sharing, FP scheduling and constant2/400 lifetimes remain open.

## Reproducible native controls

`audit-cpu-policy-paths.py --root reimu --x-position-cases` supplies20200
cases:101 actual policy-roll seeds, two facings, ten height pairs, self/peer X,
and quiet NaN, signaling NaN, positive/negative infinity and negative zero.
It runs the original PE helpers with empty masked-PC53 inputs. The two
counterexamples above are native target positive controls: target policy,
timer and real selector limits are independently checked before comparison.
The generator does not fabricate an outcome or substitute a helper.

The corrected private object passes0/20200 through the public mode. The fresh
selected source object has the same complete canonical payload, including
metadata, so repeated identical-code exceptional-X execution is unnecessary.
Fresh selected-object selection/general/height runs pass0/16160,0/5000 and
0/368, for0/41728 on the current canonical code overall. The general suite
executes all five original helpers. Normalizing source sites to instruction
ordinals makes all49 finite selector-pair records,63 coupled terminal records,
representative cases and publication/x87 records identical to the preceding
source; no previously correct finite sharing group is lost. All1488 target
policy0 instructions and actual rolls0..100 remain covered.
Full actor/RNG/call/ftol2-input/stack/control comparisons retain their existing
scope; complete numerical, exception-status and gameplay equivalence remain
unproved.

| Artifact | SHA256 |
| --- | --- |
| Selected source | `7102660c044b225578aeb52fb5379ef20925ed813f34e7ab6815e760384f01eb` |
| Fresh selected ordinary object | `4baa55369ce8eade9d817547d95617f4ddaed1de70a5b49edabfd9860786fe24` |
| Canonical16461-byte payload | `4a4cb565b9c023fb82e6f4fbb01e63df711d3b3f59ce15fef1c1f9c52b581792` |

Reports, native path/flags traces and normalization recipes are under
`build/reimu-cpu-geometry/`. Direct read-only Ghidra re-attests identity,
entry, mapped text, root bytes and metadata with384MiB/CPU0. Nine primary DB
file hashes remain unchanged; project alias removed. Its private recipe is
under `.analysis/reimu-cpu-geometry-20261019/`. Required IDA preflight still
rejects the wrong open target; no IDA semantic data or factory adapter is used.
Two materialized input arrays totaling about12MB were removed after execution;
the public generator regenerates the cases and the trace recipe reads it
directly. Reports, source controls and small recipes remain available.

Two initial controls remain unselected. Reading peerY directly instead of
through an integer pointer snapshot is completely payload-identical to the
old source. Removing five promoted-distance temporaries instead produces
`0f69c9d0`/16429 bytes and worsens reachable RET sharing46->45. This does not
establish their original declarations; neither experiment explains the mask
differences fixed here.

```bash
python3 scripts/build.py --unit gpt-web-reimu-cpu-action-policy --compare --json
python3 scripts/audit-cpu-policy-paths.py \
  build/match-units/GptWeb_ReimuCpuActionPolicy.obj --root reimu --x-position-cases
python3 scripts/audit-cpu-policy-paths.py \
  build/match-units/GptWeb_ReimuCpuActionPolicy.obj --root reimu \
  --selection-cases --selection-x87 --selection-terminals
python3 scripts/audit-cpu-policy-paths.py \
  build/match-units/GptWeb_ReimuCpuActionPolicy.obj --root reimu --cases 5000
python3 scripts/audit-cpu-policy-paths.py \
  build/match-units/GptWeb_ReimuCpuActionPolicy.obj --root reimu --height-cases
python3 scripts/ci.py
git diff --check
```

To reproduce the earlier-source negative control, export
`c574d43:src/characters/ReimuCpuActionPolicy.cpp` below build, compile it with
`TH105_EXTRA_INCLUDE_DIRS=src/characters scripts/compile-unit.sh`, and use the
current exceptional-X mode. The strict comparator intentionally still fails
on selected source. No shared header, flag, relocation or match ledger changes;
no unrelated accepted-unit or aggregate cold replay is claimed.
