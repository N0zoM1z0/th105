# Yukari action-state root `0x0057B030`

## Canonical exact match (2026-11-27)

`Yukari_dispatch_action_state_vslot28` (`0x0057B030`) is canonically exact under
VC8 SP1 `/O2 /GS- /GR /EHsc /MT` (`exact-first-yukari-action-state`) against JP
TH10.5 v1.06a SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`. This
completes all 15 Fighter primary vtable `+0x28` action-state roots.

- Callable code `[0x0057B030, 0x00588F02)`: 57,042 / 57,042 bytes exact
  (14,501 reachable instructions, zero unreachable alignment bytes, 140 RETs,
  SHA-256 `7caa43b9c69087875de1d8db150434733ad7b8a0fbd0d7bd245ee288f3db5db3`).
- Complete nine-table switch payload `[0x0057B030, 0x005893B8)`: 58,248 / 58,248
  bytes exact (four sparse action tables `low`/`mid`/`high`/`special` with
  44/27/47/6 destinations plus five four-entry difficulty tables in `710`,
  `720`, `730`, `740`, `741`; 144 destination words, 623 index bytes, 7
  alignment bytes, SHA-256
  `8c76f4df41ea9627a161193cf132671508311cd6e04717a4314a7cb2390682af`).
- Relocations: all 1,769 agree (889 REL32 calls across 32 targets and 880 DIR32
  fields). Owner audit: 122/122 `instruction_edge_identical_owners`.

Reproduce:

```bash
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit exact-first-yukari-action-state --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py --unit exact-first-yukari-action-state yukari-vslot28 build/match-units/ExactFirst_YukariActionState.obj --json
```

### Key source-shape recoveries that closed the root

- **Typed checked receiver**: replaced `at<T>()` offset casts in
  `src/characters/YukariActionState.{hpp,cpp}` with checked typed members
  (`offsetof` static assertions), `signed char` facing on `spawn`, `unsigned char`
  facing on `effect`, and member `dispatch_character_wave_handle` + `+0x04`
  `YukariActionScratch::reset`.
- **Exact comparisons and arithmetic**: `--word_730 < 0` in `73`/`88`,
  `word_730 * 0.0025f` / `-word_732 * 0.0025f` in `89`, `field_6b8 < 0` in `200`,
  `sequence_index_13e < 3` in `203`, `frame_index_140 > 4` in `305`,
  `double a = field_740 * 5.0; ... a + (field_744 - 20.0) + n * 10.0 - 10.0` in
  `402`, duplicated `y_f0 = yukari_surface(this)` in both `facing_104 == 1`
  arms of `201`, restored `p[2] = 4.0f; p[1] = 0.25f;` in `launch826`/`launch910`,
  descending `case 3..0` order in `710`/`730`/`741`, `alpha <= 250` saturation
  in `750`, and `for (int i = 0; i < count; ++i)` in `burst910` (scheduling
  `word_738 = 1` before loop-counter setup).
- **VC8 `c2.dll` `CONST(0) -> EBP` / `CONST(1) -> EBX` coloring**: tracing
  `c2.dll:0x10B14E2A` showed `CONST(6) -> EBP` and `CONST(4) -> EBX` split both
  `CONST(0)` and `CONST(1)`. Writing `case 2:` and `case 1:` separately in
  `action 720`'s difficulty switch gave `CONST(70)` `score = 1` (`lea ebp,
  [eax + 0xa]`), cutting the post-split `CONST(0)` vs `CONST(1)` priority gap
  from 93 points to 6 (`-1458` vs `-1452`); unnesting the repeated
  `!frame_timer_142` frame guards into sequential `if (!frame_timer_142 && ...)`
  checks added +8 points with zero extra code bytes, flipping `CONST(0)` ahead
  of `CONST(1)` so `0` takes `EBP` and `1` takes `EBX`. Splitting `entry(1)` and
  `entry(2)` into two `if` guards in `action 404` restored its shared `0x57F6B5`
  `set_action_and_finalize(9)` tail.

---

## Historical investigation notes (2026-10-28..2026-11-07)

The notes below retain the earlier target-behavior observations and intermediate
refinements established before the 2026-11-27 exact match.

Factory native IDA was checked on October 28: target hashes/file size,
entry 68B9D2, initial function inventory 401000/52, and 16 mapped bytes at 401000,
68B9D2,420000,570000,6B0000 all agree with the independently hashed PE.
The direct repository launcher still lacks mcp 1.26.0. Decompiler output is a
hypothesis only; raw instruction evidence overrides its lost ST0 results and
misleading shared-tail calling-convention annotations.

Native callable 57B030..588F02 is 57042 bytes,14501 decoded/reachable instructions,
140 RETs,889 direct calls to 32 targets, no unreached ranges. Four action tables
and five nested difficulty tables close every indirect exit. Low/mid/high/
special tables contain 44/27/47/6 destinations; the default is 588EF3. Complete
payload through 5893B8 is 58248 bytes, including the two bytes before the first
table, SHA 2568c76f4df41ea9627a161193cf132671508311cd6e04717a4314a7cb2390682af.
Callable SHA 2567caa43b9c69087875de1d8db150434733ad7b8a0fbd0d7bd245ee288f3db5db3.

## Source and replay

Source: src/characters/YukariActionState.cpp and .hpp. The receiver is a
pointer-only extension, not a recovered complete nominal Fighter layout.
All direct helpers remain declaration-only; none inherits root ownership.
Unit: exact-first-yukari-action-state.

```
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-yukari-action-state --compare --json
scripts/repo-python scripts/compare-giant-action-switches.py yukari-vslot28 build/match-units/ExactFirst_YukariActionState.obj --json
```

Public replay emits 57792 full bytes versus 58248. First difference+8 is the frame
immediate 4E8 versus native 4E0. Candidate SHA256:
12d9549c7a1da78ef8e507fb170ddd006203e0ead7926d0fd9e4ad11e94a2360. Full audit
reports 54483 unequal/missing positional bytes, not a semantic percentage. Comparison
exit 1 is expected.

New source/header and append-only unit/literal entries have no existing accepted
consumers. Unchanged exact receipts are retained; no whole-corpus cold build is
claimed or required. Final scripts/ci.py and git diff --check remain mandatory.

## Preserved target distinctions

- Prelude 998 emits paired+10/-10 one-float packets, not the null packets used by
  other roster peers. Coordinates are(80,130),(60,80),(75,140), signed facing;
  7A2=100. Walk speed is 4.5; normal jump 12.5/.55; high jumps use.65 gravity.
- Native 71..78,88,89,145 recovery actions preserve integer-truncate-then100
  velocity captures, AL boundary tests, layout/event/reset order and one-time999.
  197..199 use independent 981 packet lifetimes;199 makes two checked deck calls
  at receiver+55C. 201/224 landing clears VY/gravity, not VX. 201's entry 4/5
  checks share the native outer time gate.
- Yukari 214 uses five/six release states, turn 1/3, acceleration.3, no copied
  peer angle wrapping, and direction-sensitive release selection. Native trig
  results are consumed from ST0 despite missing return assignments in IDA.
- 400/401/404 fan 800 has distinct low/high packets and timing;402/406 retain
  float induction and their different formulas. Counter/callback order is not
  replaced with a generalized peer pattern. 801 packets contain four floats.
- 522/523 preserve actual atan/sqrt calls and the native constants 37825,65025,
  128500,190800. Do not recompute those constants from presumed geometric
  coordinates: native 135/135 atan and 37825 sqrt coexist. Their shared speed
  temporaries are float, demonstrated by 583389 onward.
- 565/566 distinguish time-counter and frame-timer control. 566 can set frame
  timer 75 and then take its same-frame launch. 721 uses 10, not 75;720 reads
  owner+168 Y for its difficulty burst, not peer+170 Y.
- 710 packet fields 1/2 are initialized outside each loop; subsequent callback
  mutations are not overwritten per iteration. Difficulty 740 default at 588718
  reads an uninitialized stack local. The source leaves the local unset outside
  difficulties0..3; invalid-difficulty behavior is not recovered portable
  semantics and no made-up default was introduced. Further evidence is needed
  before selecting this source.
- 656 loads virtual slot+0C and argument 5, then jumps into shared call 57B867.
  Reading only instructions immediately before call 57B869 falsely suggests
  set_action(10). The incoming register/argument context must be preserved.

## Diagnostics and remaining work

Zero-offset spawn coordinates now read X directly, eliminating unsupported FP+0
in 520/521/525/526. Low cases follow raw physical-owner order. Random emission
arguments preserve target Y-before-X evaluation and captured bases while
avoiding unnecessary source temporaries. These are natural semantic/lifetime
changes, not padding or register forcing.

Current per-action direct-call and FP-operation counts agree. Physical virtual
site counts still differ in 201(3/2),214(14/13),656(3/4); these count reachable
sites, not dynamic executions or nominal vtable meanings. They do not prove
semantic equality. Native 44 low owners become 43, merging 210/222. The manifest
permits that candidate count only for diagnostics; target expectations remain 44.

Payload dataflow resolves 101 homes on each side, no unknown spawn pointers.
Native/candidate frames 1248/1256 and epilogues 140/144 differ. Packet ordering,
size-class positions and scratch lifetime are not yet exact. All 49 crossed
consumers test AL; native 9/candidate8 on-surface physical sites likewise test
AL. Candidate has 3 unreachable compiler alignment bytes. General unordered FP
predicates, callback aliasing and original TU/lifetime context remain open.

Seventeen new literals have unique native operand witnesses and matching COFF
values; no arbitrary unresolved literal binding was allowed. No target patches,
assembly, forced registers, inert locals or fake returns were introduced.
Exact tracking remains 1427 functions/413799 authored bytes.

## Direction/argument refinement

The latest focused replay is formal-directionbranches.json and
formal-directionbranches-audit.json. Explicitly capture the zero-extended
byte direction before deriving signed coordinate offsets, as the native 998
prelude demonstrates. Its first packet call now has the native length; exact
register allocation and the 4E8/4E0 frame remain different.

Native 710 has separate same-facing/reversed-facing argument-setup arms that
converge on each spawn instruction (e.g.587262..5872B3). Expressing those as
whole calls in if/else, instead of a ternary direction temporary, reduces the
710 physical span discrepancy from 224 to 9 bytes. This is a source-shape result,
not exact credit. Packet, call and arithmetic semantics remain the scope;
no assembly, target modifications or dummy dependencies were introduced.

## Aim argument lifetime refinement

The current source keeps the binary 32 DX local and evaluates the binary 32 DY
expression directly in the atan argument. Raw native sites 57FFC8, 5800AA,
58044C, 58052E, 580844, 580C84 and 580D6A first place rounded DX in outgoing
[esp+4], then load peer Y and prepare outgoing DY. The previous two-local
source captured DY before placing DX and kept a separate DY stack home.
No helper call or field write intervenes in either coordinate calculation;
all arithmetic widths and the ordered DX capture remain unchanged.

The isolated change affects 140 bytes in seven same-sized instruction ranges. At all
seven sites the 32 bytes immediately before the atan call now match native verbatim;
none did before. These are local diagnostic windows, not function acceptance.
Function size, action-owner map, metadata and 4E8 frame remain unchanged. The
complete unmasked canonical audit still mismatches at+8.

The frame investigation also rejected narrowing the action 730 Y capture:
588639..58864A explicitly stores and compares a QWORD across surface().
Native burst 910 likewise captures its X+100 base as QWORD before RNG at
587E0C, 587EEC and 587FCB. The extra frame space therefore does not justify
changing these scalar widths. The compiler listing still places their shared
QWORD group above the initial one-float packet; the cause remains unresolved.
This checkpoint changes neither selected-source nor exact ledgers.

## Action 310 ordered landing gate, 2026-11-04

Native instructions `0x0057F9D4..0x0057F9F1` compare surface to the
computed next Y, then zero to vertical speed. The status-word tests skip the
landing path on either unordered comparison. The previous source used
`!(surface < next_y)`, which can admit an unordered surface comparison. It now
uses ordered `surface >= next_y` followed by `speed < 0`. The fresh VC8 object
emits the target's corresponding x87 status masks (`AH & 1`, then `AH & 0x41`)
and skip branches. This establishes the local gate ordering, not general
runtime or unmasked-exception equivalence.

The 57,042-byte callable remains nonexact from +8; the candidate section tail
is 57,792 bytes. The source remains unselected and adds no exact credit.

## Actions 402 and 406 ordered shot gates, 2026-11-04

Native instructions `0x00580601..0x00580612` and
`0x00580F01..0x00580F12` compare 5.0 against the field at 0x740 and
skip the shot path when `AH & 0x41` is nonzero. Thus the path requires an
ordered field value below 5.0; the previous negated `>=` also admitted NaN.
Both conditions now use `< 5.0f`. The fresh VC8 object emits the same local
x87 status mask and skip branch at both sites. This is evidence for the local
gates, not an assertion of whole-function or unmasked-exception equivalence.

The 57,042-byte callable remains nonexact from +8; the candidate section tail
is 57,792 bytes. The source remains unselected and adds no exact credit.

## Action 214 flight effect facing, 2026-11-05

Native `0x57E111..0x57E181` captures the unsigned effect-facing byte before sine, computes and rounds Y, then separately reloads signed facing after cosine for the X offset. The earlier candidate reused signed facing captured before both lookups. Ordinary locals now preserve both native read points; fresh VC8 output captures the effect byte at `0x306A` and reloads signed facing at `0x30A1`, after cosine. This establishes read order, not that the actual lookup changes facing or that ordinary gameplay differs. The 57042-byte root remains non-exact (candidate section tail 57792, first mismatch +8); no exact credit is claimed.

### Object 856 shower read order (2026-11-05)

The target's two shower-856 expansions capture the unsigned direction and `(Y + 350)` qword before RNG(400), round the resulting Y argument before RNG(300), and reload signed facing after that second random call (for example `0x586717..0x5867A5`). The earlier candidate cached signed facing before either RNG call. Explicit local values now preserve the target call/read ordering and separate final X/Y float stores; both rebuilt root sites show the signed reload after RNG(300). The actual random helper does not ordinarily mutate the receiver, so no normal-play difference is asserted for the read-order correction.

Strict root comparison remains nonmatching: target 57,042 bytes, candidate section tail 57,824 bytes, first difference +18. This does not add exact-match credit.

## Action 201 object 849 signed position, 2026-11-05

At `0x57D207..0x57D24F`, the native frame-70 spawn reads the facing byte once, zero-extends and negates its low byte for the direction argument, but sign-extends the same byte before multiplying by 200 for X. The earlier source multiplied the unsigned byte instead. With facing `0xFF` and the action's X of 40, the native X is -160 while the old source gave 51040. The source now sign-extends the captured byte for the offset while preserving the byte-valued reversed direction. The focused VC8 build emits `movsx` followed by multiplication by 200 for this position; the entire root remains nonexact and receives no exact credit.

## Actions 606 and 656 shower conversions, 2026-11-05

The two native shower expansions convert RNG(400) and RNG(300) using the float `2^32` correction before their coordinate arithmetic (`0x58672B..0x58678D` and `0x586988..0x5869EA`). The previous helper converted both unsigned values directly to double, producing four double-correction instructions. Converting through float before promotion preserves the observed correction type without an added float-store category: the native root and fresh candidate each have 35 float corrections and no double corrections, versus 31 and 4 respectively before this edit. These count comparisons are diagnostic, not proof of whole-root equality. The bounded random values are exactly representable as floats, so no ordinary-play numeric change is established. The 57,042-byte root remains nonexact at +18 with a 57,824-byte candidate section tail; no exact credit is claimed.

## Object 800 fan-angle association, 2026-11-05

Six native fan paths, for example `0x57FCFC..0x57FD1D` and
`0x580185..0x5801A1`, subtract 20 from the float angle field before adding
the signed counter-derived integer, then add the loop integer and subtract
15 or 30. The old shared source grouped the counter and angle before
subtracting 20. Parenthesizing the angle-minus-20 expression restores the
native association in both fan loops; fresh VC8 emits the corresponding
field subtraction, floating add, integer add and final subtraction sequence.
No normal-play numeric difference is established.

The 57042-byte root remains nonexact at +18, with a candidate section tail of
57840. This local correction adds no exact-function or byte credit.

## Action 402 fan-angle association, 2026-11-05

At `0x580642..0x58066E`, the object-800 fan angle adds `state_740 * 5` to
`state_744 - 20`, then adds the loop term and subtracts 10. The prior source
added the two fields before subtracting 20. The corrected expression preserves
the target association; VC8 evaluates the independent field subtraction and
multiplication in a different order, but combines them in the observed order.
No normal-play numeric difference is established. The 57042-byte root remains
nonexact at +18 with a 57840-byte candidate section tail; no exact-function or
byte credit is claimed.

## Action 214 unordered peer-position comparison, 2026-11-07

For release sequences 3 and 4 with a facing byte other than 1, the native
comparison at `0x57E2E0..0x57E2F3` compares the peer's X with the fighter's X.
Only an ordered peer-X-greater result takes the facing/velocity reversal and
sequence-5 path. Less, equal, and unordered results select sequence 6 at
`0x57E31E` (EBP holds 6 from `0x57DDE0`). The earlier ordered `peerX <= selfX`
source sent unordered values to the reversal path instead.

The unselected source now uses `!(peerX > selfX)`, preserving all ordered outcomes
and the original unordered branch. The fresh candidate compares the operands in
reverse at `0x327D..0x3296`, with a parity branch that selects the same four
outcomes. Ordinary-play reachability of an unordered position is unknown. The
complete candidate remains nonexact: 57,840-byte section tail against the
57,042-byte native callable, first mismatch +18. No exact credit is claimed.
