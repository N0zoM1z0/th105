# AyaObject unordered predicates, conditional reads and switch closure

## Retained bounded result, 2026-10-02

**Observed:** `AyaObject_update_action_state_vslot28 @ 0x0061A290` owns the
reviewed callable `[61A290,61EED2)`, 19,522 bytes. The original Japanese 1.06a
executable SHA-256 is
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`;
callable SHA-256 is
`18c813a20cea427b2c3577e2612e3f2e949a191ee2496dc9204331758bebb895`.

Two unordered predicates and action902's conditional owner-state reads are
corrected. The ordinary match-identifier switches in 900/902 now follow the
observed physical 3/2/1/0 order. Candidate main metadata starts at 19,020
(`+0x4A4C`), versus target 19,524 (`+0x4C44`); the 504-byte gap grows from the
baseline's 364 bytes. Candidate section tail is 19,488 bytes, 34 bytes shorter
than the reviewed target callable. The configured canonical request remains
19,522 bytes and fails at `+0x22`, target `0F` / candidate `19`. The available
candidate-window hash below includes adjacent metadata and has only 19,488
bytes; it is neither a candidate-body hash nor complete target-byte acceptance.

Strict instruction/edge diagnostics improve **2/34 -> 3/34**, gaining the
physical default owner `actions:802` without losing entry or action980. The
33 physical destinations remain distinct with zero target-group splits.
This adds no exact function or byte credit. Retained source SHA-256:
`d9ab796436db481b325c6493e59682ee9275f26927ff3b62752b199b33486a2d` (LF worktree bytes).
Available canonical candidate-window SHA-256:
`86b7dce49e6424617f290ab394a230db53054cc855113b0761b17ed6b8dc9d1f`.

## Complete nested-switch target traversal

**Observed:** fresh baseline audit reached only 3,446 instructions / 14,451
bytes, leaving 5,071 callable bytes unvisited. Its five unresolved indirect
exits hid a sixth, nested match-identifier dispatch in action900. Complete raw
linear decoding finds seven indexed jumps: the primary action switch and six
auxiliary switches. Their range checks and exact target DWORDs establish:

| Name | Dispatch | Destination table | Entries |
| --- | --- | --- | ---: |
| sequence856 | `61D3BA` | `61F020` | 6 |
| sequence900 | `61D852` | `61F038` | 6 |
| match900 | `61D96A` | `61F050` | 4 |
| sequence901 | `61DF4B` | `61F060` | 4 |
| match902 | `61E5AB` | `61F070` | 4 |
| sequence903 | `61E658` | `61F080` | 10 |

The sequence indices are sign-extended word +13E; unsigned JA bounds reject
negative indices as well as values above 5/3/9. Match indices come from the
full dword `6FA894`, bounded by 3. Every table destination is inside this
callable. Sequence856 has duplicate destinations for states2/3, and
sequence900 for states1/2; entry count is not unique-destination count.

`config/giant-action-switches.toml` now records each exact dispatch, ordered
destination list and table address. Readback verifies all six. The existing
fail-closed auditor verifies the table bytes and requires the dispatch edges
to be reached. Fresh traversal reaches **4,630 instructions / all 19,522
bytes**, with seven validated switch jumps, no unreached ranges, no unledgered
direct targets and no unresolved indirect exits. Adjacent switch metadata is
not added to authored callable ownership. Prior broad source-closure claims
do not prove numerical closure; the missing traversal and predicates below
required independent revalidation.

## Action900 ordered outside test

**Observed:** at `61DBF4`, target compares X against the qword 2000.0 at
`6C4688`; `TEST AH,1; JE 61DC18` enters owner-state update and lifetime
reduction for ordered X >= 2000. At `61DC07`, it compares float -720.0 at
`6C43E8` against X; `TEST AH,1; JNE 61DC9E` skips that update when X is above
-720 or unordered. Thus target outside behavior is the ordered union
`X >= 2000 || X <= -720`; NaN skips the owner update/lifetime reduction.

The retained source previously continued only when
`X < 2000 && X > -720`, then otherwise ran that update. Both ordered
comparisons are false for NaN, so that source took the wrong path.

**Inferred and retained:** the continuation guard is now
`!(X >= 2000 || X <= -720)`. VC8 naturally replaces two AH masks5 with masks1
and the corresponding parity branches with zero branches. These four
instruction changes restore the target predicates without changing owner
sizes. Ordered boundaries and infinities retain their existing behavior.

## Action902 unordered angle and conditional owner reads

**Observed:** target stores state370 into payload[0] at `61E49D`. Its lower
angle compare `61E4B7` tests C0 alone and rejects both negative and unordered
values. Its upper compare `61E4C2`, against float180 at `6D6EDC`, rejects values
above180 or unordered. Both rejected paths prepare the negative spawn side;
ordered [0,180], including both endpoints, prepares side+1.

The previous `(state370 < 0 || state370 > 180) ? -1 : 1` chose+1 for NaN.
**Inferred and retained:** `!(state370 >= 0 && state370 <= 180) ? -1 : 1`
restores the target outcome. Under the current source phase it changes only
the candidate lower-angle branch from JE to JP. The candidate upper guard
need not independently reject NaN: the preceding lower guard already rejects
it, and there are no intervening calls/state370 writes or external direct
entries into that upper-test region. This is path reconciliation, not a claim
that the isolated upper-guard truth table matches in all four x87 outcomes.

**Observed:** target match branches compare the time counter first, then
read `fighter_owner_348` and its signed word +174 only if needed. A match index
outside0..3 skips that read entirely. The old source cached `owner_state`
before the switch, causing an unconditional earlier dereference.

**Inferred and retained:** each actual short-circuit predicate now reads the
signed word within its time/owner condition; the cached local is removed.
Action902 shrinks **783 -> 644** bytes versus target652. This recovers the
conditional read timing, but the candidate merges all four matching branches
into one callback suffix. Target instead has two physical suffixes, sharing
3/1 and2/0: `61E607 JMP 61E5BC` and `61E5FB JMP 61E613` carry comparison flags.
These remaining physical tails are not recovered by the close span size.

## Physical match-body order

**Observed:** target match900 table indices0/1/2/3 point to
`61DB35/61DA9D/61DA05/61D971`, so physical bodies run3/2/1/0. Match902 indices
point to `61E609/61E5FD/61E5F1/61E5B2`, also3/2/1/0. Baseline candidate order
was0/1/2/3 in both tables. The source case order now follows this observed
layout, preserving every case's values and side effects.

For match900, physical bodies3/2/1/0 now have spans **148/152/152/147** bytes,
equal to the target's respective block spans. Their instructions, stack homes,
argument schedule and surrounding action remain nonexact. The order-only
control preserves2/34 diagnostics and increases difference-block counts
(90038->42,90229->30); that score is not a physical-order proof. The retained
order is supported by actual table/body positions and is combined with the
independently observed902 conditional read recovery, not accepted as exact.

## Floating guard coverage and limits

The initial scanner found124 target /123 candidate guards. The missing
candidate861 site is `TEST BL,AH`: EBX is set to1 on its entry path. No outside
direct branch enters the definition/test interval, and its direct callee
`435D60` has no EBX-family writes. That callee's only direct call is runtime
`68A1A0`; full raw decoding of that 171-byte region also has no EBX writes,
indirect calls or external tails. Thus BL remains1 at the guard. Their body
hashes are respectively
`4896deab933804203efe263ac8d771c5a471cc54e11b56fa25a6ed2134550895` and
`aeb7a87183a558dd228b968d6264bdeb993114992b7807d638c943a2adadd1a2`.
This proves EBX preservation for this call chain, not ECX preservation.

The extended private scan now covers **124/124 guards**, with no unequal
per-owner counts. Its single residual ordinal lead pairs target's right-facing
bound with candidate's velocity floor3: candidate lays the floor0 path before
floor3, whereas target puts floor0 later. Manual role pairing reconciles902's
seven guard roles; the upper-angle NaN filtering is handled compositionally
as above. Ordinal counts/finite-equivalence hypotheses do not establish all
operands, intermediate precision, association, exception behavior or value
lifetimes. Full numerical closure remains unknown.

Action997's112/76 target/candidate spans arise from physical sharing: target
keeps its FILD/FMUL/FADD X and FLD/FADD Y movement locally, whereas candidate
jumps into action800's shared movement body. Its integer scratch is already
at+18 in both. This observation does not justify adding a float scratch or
assembly. No extra997 source shaping is retained.

## Controls and reproduction

A separately compiled `g_match_identifier == 0 || == 1` spelling for900's
owner-state update shrinks its candidate1737->1715 versus target1773 and
moves metadata19160->19140, without diagnostic gains. It is not retained;
no global type or volatile qualification is inferred from this control.

Private source controls and exporters are in
`.analysis/aya-object-state-20261002/`; source/object/window hashes and focused
reports are in `build/aya-object-state-20261002/controls-summary.json`.
Target tables, raw instructions, guard packets and available instruction
changes are stored in that same build directory. These existing-object probes
have no configured build provenance and award no exact credit.

```bash
python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
python3 scripts/audit-giant-action-owners.py aya-object-vslot28 \
  build/match-units/GptWeb_AyaObjectActionState.obj \
  --unit gpt-web-aya-object-vslot28-full-root --json
```

Finished-worktree reports are `build/aya-object-state-final-20261002.json`
and `build/aya-object-state-final-owners-20261002.json`; the matching guard
report is `build/aya-object-state-final-guards-20261002.json`.
No shared header/ABI, compiler flag, helper body, relocation mapping or object
partition changes. Exact ledgers are unchanged; no cold aggregate replay is
claimed. IDA still fails preflight because the attached SHA begins10350095;
all new target observations are from the verified PE, without new database
output. Original source types, physical tails, virtual-call and argument
schedules, temporary homes, compiler/TU/LTCG context and full numerical/
exception closure remain open.
