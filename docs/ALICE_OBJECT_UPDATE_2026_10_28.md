# AliceObject complete update, 2026-10-28

AliceObject_update_action_state @ 004FCAB0 now has a complete manual source
hypothesis for 38 primary actions and the default. Whole canonical replay is
**nonexact**. Structural agreement does not earn exact-byte credit.

## Target observations

Canonical Japanese 1.06a SHA256 is
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Raw RTTI owns slot 28 through vtable 6C4B54, cell 6C4B7C, COL 6DA328 and
TD6E81F8 AliceObject. The adjacent accepted initializer 50C1C0 is unchanged.

Callable [4FCAB0,50BDF6) is 62278 bytes, SHA256
`363a5bbe7c9294389e5a6ddad319d2b0ffd628b5f821155b24516047476edf03`.
14945 instructions decode; 14944 instructions / 62271 bytes are reachable.
The sole seven-byte padding range is [4FE2E9,4FE2F0). Native has 120 RET 0s,
134 virtual calls and 424 direct calls to 28 distinct targets, without outgoing
tails. ESP alignment is 8 and the frame allocation is 0x348.

Complete payload [4FCAB0,50C1C0) is 63248 bytes, SHA256
`b293547ae355c58990d6bdb38fb5c1e26bb199556aa123a9dfb4a8b7dc0e00b0`.
18 table dimensions are 39,7,6,7,7,11,5,6,11,7,15,23,6,7,4,6,4,5.
Remaps at 50BE94/50C0A4/50C11C have 200/25/35 bytes. Two-byte8BFF callable
alignment, three-byte8D4900 at 50C0BD and NOP at 50C13F are independently covered.
No initializer or inter-function padding is claimed.

## Source and evidence limits

The local IDA preflight lacked its pinned MCP runtime; that session was not
used. Factory-native th105-ida was independently re-attested at 20:42 UTC with
canonical metadata, entry 68B9D2, mapped entry bytes, inventory and 46 exposed
operations. Decompilation supplied navigation hypotheses only. Raw instructions,
operand widths and whole target comparison decide the retained evidence.
No target bytes or database metadata were changed.

The receiver is a pointer-only view, not an allocation layout claim. Motion
uses this+4, wave uses owner 348, and all four indexed 4359F0 calls use owner 348.
The three early 4359D0 calls in 815/816 use this; distinct receiver declarations
preserve the established callee ABI. ST0 sine/cosine/square/atan2 results omitted
by decompilation are represented explicitly. Signed and unsigned fields,
callback-sensitive reloads, genuine packet arrays and observed guards are kept.
849 and 858 ignore the advance result before their frame-entry checks.902 uses
float dx/dy/radius and has no invented zero guard. Scalar lifetime and exceptional
floating-point equivalence remain unresolved, not asserted by a successful build.

The first complete source exposed an unsupported double 0.02 hypothesis. Raw
literal operands instead establish float 0.02 in 831/834/852/855/858. Correcting
those widths allowed complete relocation replay. That first candidate was 63052
bytes with one extra call each to 435D60,45C030 and 64CCB0. The selected source
represents 817 phase 1/10's actual shared ground-impact continuation, with two real
packet arrays and a pointer selected by the branch. This restores all direct-call
counts without inert storage, fake aliases, copied bytes or assembly.

## Selected complete replay

`scripts/repo-python scripts/build.py --unit exact-first-alice-object-update --compare --json`

Selected complete payload is 62960 bytes, SHA256
`64ed3752a3efde280ad84dbd8d242e7ee518e0df6501ba3a66c0162e04f0df8d`.
First mismatch is +37 /4FCAD5; 58935 unmasked positions differ including length.
Frame 348, all 28 direct-callee counts (424 calls), all 18 table dimensions and all
260 remap bytes agree. Candidate 126 returns/138 virtual calls differ from native
120/134. Stack homes, shared tails and floating-point scheduling remain open.
No normalized comparison, partial case or structural count receives exact credit.

Only source and mapping advance;
matches.csv is unchanged. Dedicated aliases do not alter existing consumers. No
shared ABI, compiler profile or accepted source changed, so unchanged accepted
receipts remain incremental and no corpus rebuild was required. The focused replay
and default repository CI gate this checkpoint.

## Actions 853 and 999 landing comparisons, 2026-11-04

Native `0x0050619A..0x005061B8` and `0x0050BCAC..0x0050BCCE` retain
next Y in a QWORD across the surface query, then skip the landing path when
`AH & 1` is nonzero. That excludes unordered comparisons. Both source gates
now express ordered `surface >= nextY`; action 999 also retains the sum as a
double instead of rounding it to float before the query. The fresh VC8 object
uses QWORD temporaries and the corresponding x87 mask and skip branches at
0x9660 and 0xF0F4. These are local observations, not a claim about unmasked
exceptions or the entire callable.

The 62,278-byte callable remains nonexact from +37 (candidate section tail
62,960 bytes), and this checkpoint adds no exact credit.

## Action 805 surface clamp, 2026-11-04

Native `0x004FE6BA..0x004FE6C8` clamps Y only when the surface is ordered
and greater than the saved current Y (`AH & 0x41` skips the clamp). The prior
negated `surface <= currentY` also clamped on an unordered comparison. The
source now uses ordered `surface > currentY`; fresh VC8 emits the same local
status mask and skip branch at `0x1BBD..0x1BC6`. This observation does not
assert whole-root or unmasked-exception equivalence.

The 62,278-byte callable remains nonexact from +37; the candidate section
tail is 62,960 bytes. No exact credit is added.

## Actions 831 and 834 effect X grouping, 2026-11-05

Native `0x00502AF7..0x00502B1C` and `0x00503363..0x0050338A`
compute the integer index/facing offset, add current X, then add the random
offset. The prior source associated random with the integer offset first.
Both paths now express `random + (index_offset + X)`, preserving the native
x87 order and possible rounding difference. Fresh VC8 emits the corresponding
`fild`, `fadd X`, `faddp` sequences at `0x5FE2` and `0x6863`. Random call
order and the existing QWORD Y captures are unchanged. This does not establish
whole-root or unmasked-exception equivalence.

The 62,278-byte callable remains nonexact from +37; the candidate section
tail is 62,960 bytes. No exact credit is added.

## Actions 806, 815, 827 and 900 bounds, 2026-11-05

Five movement-bound checks now use the target's ordered outside comparisons: actions 806 (`0x4FEEE2..0x4FEF38`), 815 (`0x4FFBDE..0x4FFC34`), both action 827 paths (`0x501DE4..0x501E24`, `0x5021DC..0x502228`), and action 900 (`0x50A6F1..0x50A730`). Their former negated in-range or lower-bound conditions also retired unordered coordinates, unlike the native x87 branches. A focused build confirms the target-style branch forms. The full root remains non-exact: target 62278 bytes, candidate section tail 62960, first mismatch +37. No exact credit is claimed.

## Action 800 phase 33 scale, 2026-11-05

At `0x509BA8..0x509BB9`, the target retires only when the decayed scale is ordered and less than 0.02. The previous negated `>=` also retired an unordered value. The focused candidate now emits the same `test ah, 0x41; jne` continuation at `0xCFD1..0xCFE2`. The complete 62278-byte root is still non-exact (candidate section tail 62960, first mismatch +37); no exact credit is claimed.

## Action 801 fade gates, 2026-11-05

The target phase 10 and 11 checks at `0x4FD5ED..0x4FD5FE` and `0x4FD66F..0x4FD67A` retire only for ordered scales at or below 0.01. The previous negated greater-than checks also retired unordered values. Both source conditions now use ordered `<=`, and focused compilation reproduces the native local branch forms at `0xB04..0xB15` and `0xBBA..0xBC5`. The full 62278-byte root remains non-exact (candidate section tail 62960, first mismatch +37); no exact credit is claimed.

## Action 817 surface-impact Y captures, 2026-11-05

In phases 1, 10 and 8, the native surface-impact checks retain current Y in a QWORD before calling the surface-height helper at `0x50056B..0x50057C`, `0x500E4E..0x500E5F` and `0x500A64..0x500A75`. The earlier source read Y after that helper. Each path now captures Y only when its preceding distance or landing checks have failed, preserving the original short-circuit call order. Focused VC8 output shows the corresponding pre-call QWORD stores and comparisons at `0x3B00`, `0x3DBE` and `0x42FE`. The ordered greater-than test is unchanged. The full 62278-byte callable remains non-exact; no exact credit is claimed.

## Action 854 orbit selector (2026-11-06)

Native `0x50654F..0x506569` compares 359.0 against the fourth motion
parameter. A value greater than 359 or an unordered comparison selects the
negative-angle, radius-200 orbit; otherwise it selects the positive-angle,
radius-100 orbit. The earlier ordered `> 359.0f` source chose the latter for
an unordered parameter. The condition now reads `!(parameter <= 359.0f)`.
Finite values retain their existing branch; whether an unordered parameter
occurs in normal play and downstream conversion behavior are not established.

The focused VC8 candidate uses the same C0 comparison bit at `0x9A25`, with an
inverted branch layout (`test bl,ah` where BL is 1). The full root remains
nonexact, section tail 62,972 bytes, compared SHA-256
`9014c56e98e0739732e7b139ea5dbc09e098ff79ef9fc49f5c97df81b55c59b3`.
No full-function or exact-byte credit is claimed.

## Action 854 packet selector (2026-11-06)

At `0x50682B..0x506847`, the native packet selects value 6 when the fourth
motion parameter is at least 360 or the comparison is unordered, and value 5
otherwise. The earlier ordered `>=` chose 5 on an unordered value. The source
now uses `!(parameter < 360.0f)`; finite results are unchanged. Candidate
`0x9D06..0x9D09` reproduces the same outcomes with an inverted branch. Whether
an unordered parameter occurs in play is unknown. The full root remains
nonexact, section tail 62,972, compared SHA-256
`5b4f6d53907b989ae2a9f9131c37dd2347e0f2927415ce40602c87894ad683fc`.

## Action 858 owner-state ranges (2026-11-06)

The thirteen checks of owner fields `0x6C0` and `0x6C4` in action 858 use unsigned bounds in the native body. For example, `0x508D6E..0x508D90` accepts only values 1 through 3, using unsigned `jbe`/`jae` branches. The former signed source accepted values with bit 31 set as well. All corresponding source checks now read the fields as unsigned, consistent with the fighter-side unsigned field view; the fresh candidate emits unsigned bounds at these sites. Ordinary values 0 through 3 retain their behavior. Whether high-bit values arise in normal play is not established. The complete focused candidate remains nonexact (62972-byte section tail against a 62278-byte main span, first mismatch +37); no exact credit is claimed.

The adjacent primary-state checks at `0x5085CB..0x5085DC` and `0x50895B..0x50896C` apply the same unsigned 1-through-3 bounds to owner field `0x6BC`. Those two source reads now use an unsigned primary value as well. The fresh candidate emits unsigned branches; the same high-bit reachability limitation applies and the complete function remains nonexact.

## Orbit target coordinate rounding, 2026-11-09

Phase 0 of action 834 rounds its desired X coordinate to float before using it
for distance, aim and the eventual position snap. Native `0x502D4E` stores m32
before the sine call, then `0x502D8F` reloads that value before subtracting the
object's X and squaring. Phase 0 of action 855 likewise stores desired Y to
m32 at `0x506CBD` and reloads it at `0x506CD3` before the Y difference and
square. The source incorrectly retained these two coordinates as double.
They are now explicit float values, preserving the observed state precision.

The difference occurs with finite coordinates, without an exceptional value.
For example, a float lookup return of `0x3F5DB3D7`, radius 20, owner-X-plus-facing
offset 715 and object X 720 give native squared X distance `0x4317CB6C`; the
previous wide target gives `0x4317CB7F`. A second finite fixture covers action
855's Y distance. These are arithmetic counterexamples, not gameplay traces.

Fresh pinned VC8 output stores/reloads both target coordinates as m32 at
candidate `0x502CD8`/`0x502D1D` and `0x506C65`/`0x506C7B`. Only the update
section changes; all 131 other non-debug sections are byte-identical.
The complete comparison replays all 1,454 relocations and preserves call
counts, the 18 switch-table dimensions and all 260 remap bytes. The candidate
payload grows from 62,972 to 62,976 bytes against the native 63,248-byte extent,
including its 62,278-byte callable body. It remains nonexact from +37.

After payload SHA-256:
`ae399452d72ecb330d62b1b543284c128a297cd746c014dcca82564919910e71`. Only
`exact-first-alice-object-update` consumes this source; no ledger or pending
input/source-pin changes are needed.

## Ordered-negative orbit facing, 2026-11-09

Actions 831, 834, 852 and 855 select facing -1 only for an ordered-negative
horizontal velocity. Native `0x502643`, `0x502E58`, `0x505A75` and `0x506D8A`
load zero, compare it with the velocity, and use `test ah,41h; jne` to select
+1 for nonnegative or unordered results. The previous `velocity >= 0 ? 1 : -1`
source incorrectly selected -1 for unordered values. All four expressions now
use `velocity < 0 ? -1 : 1`, and fresh VC8 output reproduces that branch policy.
Negative, zero and positive results are unchanged. Whether unordered velocity
occurs in normal play is not established.

The complete candidate remains 62,976 bytes against the native 63,248-byte
owned extent, with first mismatch +37. All 1,454 relocations replay, and the
complete call, return, frame, switch-table and remap inventories are unchanged.
All 131 other non-debug sections remain byte-identical. The root changes 126
bytes: the four facing selections and register/load scheduling in four adjacent
angle calculations. Those calculations retain their integer multiplier, float
parameter product, sum and stores; four constant relocation offsets move with
the loads, while every relocation symbol and kind remains unchanged.

After payload SHA-256:
`c10fff5cbcc3d85df89f3d23fb84c9f74e461faae46a74d985e5bdad5059e78f`. Only
`exact-first-alice-object-update` consumes this source. The root remains nonexact,
with no ledger credit or changes to the pending input work.

## Typed view promotion and 30-byte residual analysis (2026-11-28)

`src/characters/AliceObjectUpdate.hpp` and `src/characters/AliceObjectUpdate.cpp`
now use a checked typed view (`AliceObjectUpdateView`, `AliceUpdateOwnerView`,
`AliceUpdateMotionView` with compile-time `offsetof` checks) instead of raw
offset macros. Focused VC8 SP1 replay (`exact-first-alice-object-update`) now
reproduces the full 63,248-byte section tail, all 18 switch tables, all 3 remap
tables (260 bytes), all 424 direct calls across 28 targets, `sub esp, 0x348`,
120 RETs, and 134 virtual calls, advancing first mismatch from `+37` (`0x4FCAD5`)
to `+21,593` (`0x501F09`) and leaving 30 unmasked byte differences across 2
sites (63,218 / 63,248 bytes identical, 38/40 owners exact when accounting for
the 2-byte `8bff` table alignment at `+0xF346` before switch metadata).

Compared callable SHA-256:
`cc860d37816d7b8ee1cc206454438636d9aa2c3088aa04c0ace5cb29ef849c75`. The root
remains nonexact and earns no exact ledger credit.

Two compiler-level residuals remain open:

1. **Action 827 case 2 vs action 900 case 3 (4 bytes at `+0x5459..+0x545C`)**:
   Both cases emit 22 identical tail bytes (`sub al, 10; mov [esi+0x113], al;
   mov al, 0xf6; add [esi+0x111], al; add [esi+0x110], al`) followed by
   `jmp 0x50223A`. Under `/O2`, VC8 SP1 `c2.dll` `TryTailMerge` (`0x10B30B74`)
   merges any matching tail over 20 bytes (`ebp > 20`). When both cases `break;`
   to `0x50223A`, VC8 merges `900 c3` into `827 c2` (`-12` bytes); giving `827 c2`
   its own `FINISH()` keeps both unmerged at the exact 63,248-byte length with
   `jmp 0x4FCCB4` instead of `jmp 0x50223A` (4 bytes). Giving `byte_111` and
   `byte_110` a signed `I1` access in one of the two cases prevents `TailMerge`
   via `SingleOperandEqual` (`0x10BF7012` -> `0x10BF7B50`) and makes both `827 c2`
   and `900 c3` 100% byte-exact (39/40 owners, 26 diff bytes total), though that
   cast is not retained without independent source evidence.
2. **Action 849 cases `1..3` and `19..20` (26 bytes: `+0x6A6E..+0x6BEF` and
   `+0x7B3A..+0x7CF1`)**: `G_owner` (`[esi+0x348]`) and `G_act` (`[owner+0x13c]`)
   swap `ecx`/`edx`. Tracing `c2.dll` `Color` (`0x10B104B0..0x10B114EA`) shows
   `prio(G_owner) - prio(G_act) = 6*N_15 - 3*N_1 - 3*N_3 - sum(N_4..N_14)` equals
   `+2` in `c1..3` and `+3` in `c19..20`. Making `CONST(150)` live-in to `Block 1`
   (`cmp cx, 0x96`) raises `N_1` by 1 and drops the gap by `-3` in both arms
   simultaneously (flipping only those exact 26 bytes to target `edx`/`ecx`), but
   neither `0x4FCAB0` nor `0x5034ED` contains `150` in `resources/th105.exe`.
   VC8 RTM, `/GL` + `/LTCG`, `/fp:strict`, `/Oy-`, `/Oi-`, `/Ob0`, `/Ob1`, and
   40+ natural C++ shapes in `case 849` all leave the same swap.
