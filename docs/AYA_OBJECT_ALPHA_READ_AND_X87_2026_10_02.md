# AyaObject transparent fade reads and natural x87 lowering

## Retained bounded result

**Observed:** `AyaObject_update_action_state_vslot28 @ 0x0061A290` retains
the reviewed callable `[61A290,61EED2)`, 19,522 bytes, in the original Japanese
1.06a executable SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Callable SHA-256 remains
`18c813a20cea427b2c3577e2612e3f2e949a191ee2496dc9204331758bebb895`.
This continues [the predicate and complete switch traversal checkpoint](AYA_OBJECT_UNORDERED_AND_SWITCH_CLOSURE_2026_10_02.md).

Only action817/822 sequence1/2 now capture the actual unsigned alpha value
before their floating updates, then use that value for the fade test and
subtraction. The target reads alpha before those updates; the previous source
read it afterwards. This is a value used by both the condition and stored
result, without volatile, inert storage, assembly or flag/register forcing.

The fresh configured whole-root request remains **nonexact at +0x22**,
target `0F` / candidate `19`. Candidate metadata starts at 19,020 versus target
19,524; candidate section tail is 19,488, 34 bytes shorter than the requested
callable. Strict owner diagnostics remain **3/34** (entry,980,physical
default802); 33 destinations/zero target-group splits remain. Source-present
and exact ledgers receive no new credit. Retained LF source SHA-256:
`3c7d67cc181c16671a6c9926dc74d369760f7143ae4c0c5f028133e7f78b733d`.
Available canonical candidate-window SHA-256:
`4da10fb33843801d5d58d0c036b5dfa9becd7310e20f9900320a4f68a7cd3eb2`.
That hash includes adjacent metadata and covers only 19,488 bytes; it is not
a body hash or a complete comparison extent.

## Alpha read and comparison timing

**Observed:** target sequence1 starts with `FLD [this+11C]`, then loads
unsigned alpha from +113 and compares it with15, before adding the scale,
storing the rounded scale into +11C/+120, and adding10 to angle +12C. Its
conditional jump consumes the integer comparison flags after those updates.
Sequence2 likewise loads/compares alpha with20 just after loading angle,
before angle/state370/scale updates; the flags survive to the fade branch.

| Target path | Float-update interval, excluding final branch | Candidate interval |
| --- | --- | --- |
| 817 sequence1 | `[61B33E,61B378)` | `[61B442,61B47C)` |
| 817 sequence2, also reached by822 | `[61B2DD,61B329)` | `[61B48C,61B4D8)` |
| 822 local sequence1 | `[61BD28,61BD62)` | shared817 sequence1 interval |

**Inferred and retained:** `unsigned char const current_alpha = alpha`
before each source update recovers the early load and comparison naturally.
VC8 produces the same 11/14 instruction sequences in the corresponding
update intervals after replacing only their scratch references +14/+18 with
a common semantic rounded-float role. No instructions are omitted from these
intervals. The early load is now followed by the actual `CMP AL,15/20`, with
no SETcc/test pair or additional instruction. The subtraction consumes that
same alpha value.

These are explicit interval diagnostics, **not byte acceptance**: stack
homes differ, 822 shares sequence1 in the candidate, and target/candidate
branch destinations and return placement differ. Target817 sequence2 branches
to801's common alpha subtraction/store suffix on success and returns locally
on failure; candidate uses the common failure return and a local successful
suffix. Target822 shares sequence2 via817 but keeps a separate sequence1
float-update body. Whole-root physical sharing remains unrecovered.

## Source controls and signed sequence dispatch

**Observed:** target817 at61B2BC and822 at61BD0F sign-extend the word +13E,
then use subtract0/1/1 dispatch. Baseline source's if/else chain produces
MOVZX and word tests. Replacing only those two chains with ordinary nested
switches, retaining all sequence bodies and common post-update behavior,
naturally produces MOVSX and subtract dispatch in VC8.

That control still shares822's entire nonzero dispatch into817, whereas
target822 has its own sequence1 body. It changes candidate metadata to19,024
and owner diagnostics3->2/34, losing physical default802 while preserving
entry/980. It is **not retained**. Capturing alpha on top of the switch
recovers its early MOV/CMP but preserves those same sharing/diagnostic
limitations, so that combination is also not retained.

A separate early `bool fade_finished = alpha < limit` control emits SETB
and TEST, with metadata19,032 and2/34 diagnostics. It is not retained.
The isolated alpha-value capture leaves metadata19,020, spans817600/822423
versus target505/501 and3/34 diagnostics unchanged, while recovering the
target's actual load/compare order. These controls distinguish dispatch,
predicate materialization and value-read timing; no case permutation or
compiler-flag search is inferred from them.

## x87 observations and limits

**Observed:** qword6CD1E0 contains bytes `000000a09999b93f`, exactly
0.10000000149011612. The retained `0.1f` scale addition already generates
that target qword FADD, so changing its literal is unnecessary. Other target
constants in these paths are qword6C0EC8=0.949999988079071,
6C2A60=0.8500000238418579 and6D6EC0=10.0.

Both target and baseline candidate round the shared scale through
FSTP32/FLD32 before writing both fields. In822 sequence0, both also round X
and Y through a stack float, store the member, keep the rounded values on
the x87 stack and consume them in the bounds comparisons. This behavior is
already generated from the ordinary source's member updates and bounds
union. Adding a scratch variable or assembly is not justified by this path.

The masked-guard scan remains124 target/124 candidate, with no per-owner
count differences. Its single902 ordinal lead remains the previously reviewed
role-order/path artifact. Full operand, precision, exception and value-lifetime
closure across this giant root remains unknown. TH08's specialized
FSINCOS/FRNDINT reference does not establish an assembly requirement for
these ordinary target FADD/FMUL/FSTP/FLD sequences.

## Reproduction and remaining work

```bash
python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
python3 scripts/audit-giant-action-owners.py aya-object-vslot28 \
  build/match-units/GptWeb_AyaObjectActionState.obj \
  --unit gpt-web-aya-object-vslot28-full-root --json
```

Fresh configured reports: `build/aya-sequence-final-20261002.json` and
`build/aya-sequence-final-owners-20261002.json`; object-bound raw and guard
reports: `build/aya-sequence-final-raw-20261002.json` and
`build/aya-sequence-final-guards-20261002.json`. Source controls/exported
packets live below `.analysis/aya-sequence-structure-20261002/` and
`build/aya-sequence-structure-20261002/`. Their existing-object comparisons
have no configured build provenance and award no exact credit. The controls
are the isolated source transformations described above; they are not an
acceptance recipe.

Complete raw traversal still reaches4,630 instructions/all19,522 target
bytes through seven validated switches, with no unresolved indirect exit or
unledgered direct target. IDA preflight still fails on the wrong attached
executable; new observations use the hash-verified PE. No shared ABI/header,
helper, compiler profile, relocation mapping, object partition or accepted
unit changes; no aggregate cold replay is claimed. Next evidence should
resolve physical successful/failure suffixes, +14/+18 stack homes and original
TU/LTCG context rather than repeat these negative dispatch spellings.
