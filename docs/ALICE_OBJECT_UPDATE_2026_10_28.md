# AliceObject complete update, 2026-10-28

AliceObject_update_action_state @ 004FCAB0 now has a complete manual source
hypothesis for 38 primary actions and the default. Whole canonical replay is
**nonexact**. Structural agreement does not earn exact-byte credit.

## Target observations

Canonical Japanese 1.06a SHA256 is
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Raw RTTI owns slot28 through vtable6C4B54, cell6C4B7C, COL6DA328 and
TD6E81F8 AliceObject. The adjacent accepted initializer50C1C0 is unchanged.

Callable [4FCAB0,50BDF6) is 62278 bytes, SHA256
`363a5bbe7c9294389e5a6ddad319d2b0ffd628b5f821155b24516047476edf03`.
14945 instructions decode; 14944 instructions / 62271 bytes are reachable.
The sole seven-byte padding range is [4FE2E9,4FE2F0). Native has 120 RET0s,
134 virtual calls and 424 direct calls to 28 distinct targets, without outgoing
tails. ESP alignment is 8 and the frame allocation is 0x348.

Complete payload [4FCAB0,50C1C0) is 63248 bytes, SHA256
`b293547ae355c58990d6bdb38fb5c1e26bb199556aa123a9dfb4a8b7dc0e00b0`.
18 table dimensions are 39,7,6,7,7,11,5,6,11,7,15,23,6,7,4,6,4,5.
Remaps at50BE94/50C0A4/50C11C have 200/25/35 bytes. Two-byte8BFF callable
alignment, three-byte8D4900 at50C0BD and NOP at50C13F are independently covered.
No initializer or inter-function padding is claimed.

## Source and evidence limits

The local IDA preflight lacked its pinned MCP runtime; that session was not
used. Factory-native th105-ida was independently re-attested at20:42 UTC with
canonical metadata, entry68B9D2, mapped entry bytes, inventory and46 exposed
operations. Decompilation supplied navigation hypotheses only. Raw instructions,
operand widths and whole target comparison decide the retained evidence.
No target bytes or database metadata were changed.

The receiver is a pointer-only view, not an allocation layout claim. Motion
uses this+4, wave uses owner348, and all four indexed4359F0 calls use owner348.
The three early4359D0 calls in815/816 use this; distinct receiver declarations
preserve the established callee ABI. ST0 sine/cosine/square/atan2 results omitted
by decompilation are represented explicitly. Signed and unsigned fields,
callback-sensitive reloads, genuine packet arrays and observed guards are kept.
849 and858 ignore the advance result before their frame-entry checks.902 uses
float dx/dy/radius and has no invented zero guard. Scalar lifetime and exceptional
floating-point equivalence remain unresolved, not asserted by a successful build.

The first complete source exposed an unsupported double0.02 hypothesis. Raw
literal operands instead establish float0.02 in831/834/852/855/858. Correcting
those widths allowed complete relocation replay. That first candidate was63052
bytes with one extra call each to435D60,45C030 and64CCB0. The selected source
represents817 phase1/10's actual shared ground-impact continuation, with two real
packet arrays and a pointer selected by the branch. This restores all direct-call
counts without inert storage, fake aliases, copied bytes or assembly.

## Selected complete replay

`scripts/repo-python scripts/build.py --unit exact-first-alice-object-update --compare --json`

Selected complete payload is62960 bytes, SHA256
`64ed3752a3efde280ad84dbd8d242e7ee518e0df6501ba3a66c0162e04f0df8d`.
First mismatch is +37 /4FCAD5; 58935 unmasked positions differ including length.
Frame348, all28 direct-callee counts (424 calls), all18 table dimensions and all
260 remap bytes agree. Candidate126 returns/138 virtual calls differ from native
120/134. Stack homes, shared tails and floating-point scheduling remain open.
No normalized comparison, partial case or structural count receives exact credit.

Audit: `scripts/audit-alice-object-update.py`.
Receipts: `build/frontier-4fcab0-20261028/{formal-build,full-audit,target-audit}.json`.
Private preparation: `.analysis/frontier-4fcab0-20261028/`.
Only source and mapping advance; matches.csv is unchanged. Dedicated aliases do
not alter existing consumers. No shared ABI, compiler profile or accepted source
changed, so unchanged accepted receipts remain incremental and no corpus rebuild
was required. The focused replay and default repository CI gate this checkpoint.

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
