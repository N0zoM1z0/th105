# Tenshi action-state root `0x0063D3E0`

`exact-first-tenshi-action-state` reproduces the complete Japanese v1.06a root
under VC8 SP1 `/O2 /GS- /GR /EHsc /MT`. The final comparison on 2026-11-26 has
zero differences in all 47,784 physical code bytes and the complete 48,968-byte
payload `[0x0063D3E0,0x00649328)`.

## Complete target and compiler evidence

The target executable SHA-256 is
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
This matching pass used hash-attested raw PE bytes and Capstone. Earlier
Factory observations supplied hypotheses; the final boundary comes from raw
control flow and the full canonical comparison.

- Code SHA-256:
  `83af98e2673c40b5ca2f3caac87ab7a8e4114a758ac65dfeebdae1ad0a14e5b3`.
- Payload SHA-256:
  `a7e25e318b6ffcc43edbca3e9e3e34f311e5343c82c1a0b91d6a6d45a52d6d47`.
- All 1,562 relocations agree: 789 REL32 calls across 43 targets and 773 DIR32
  fields. The six switches contain 120 destination words and 702 index bytes.
  Two inter-table alignment bytes complete the 1,184-byte metadata extent.
- The owner audit is 107/107. Raw CFG reaches 12,489 instructions / 47,777
  authored bytes. The seven-byte LEA at `[0x00647C49,0x00647C50)` is unreachable
  loop alignment: it is compared, then excluded from authored progress.
- The three sparse regions have 35/36/37 destinations. Three four-word
  difficulty tables finish the payload. The following eight alignment bytes
  belong outside the root. All 125 RETs and the `0x320` frame agree.

The original VC8 `std::sin(float)` overload at `0x0063D3C0` is independently
18/18 exact in the same unit. Its compiler-generated origin stays excluded;
see [the sine evidence](TENSHI_ORIGINAL_FLOAT_SINE_2026_11_01.md). Degree lookup
providers `0x00406360` / `0x004063D0` also return float, but are separate calls.
The former double declarations gave the wrong call contract.

Reproduce with:

```bash
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit exact-first-tenshi-action-state --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py --unit exact-first-tenshi-action-state tenshi-vslot28 build/match-units/ExactFirst_TenshiActionState.obj --json
scripts/repo-python scripts/vc8_float_sine_origins.py
```

Private current results are `build/tenshi-root-work-codex/canonical.json` and
`owners.json`. The public receiver is character-scoped, with eight virtual
prefix slots and 82 checked member offsets. No shared layout changed.

## Source properties that closed the root

Use a signed facing member and explicit byte views for outgoing directions.
The four ring-801 sites, action 525 and action 730 capture outgoing direction
before lookup/RNG calls and reread signed facing afterwards. Direct argument
expressions and implicit float parameter conversion preserve this order;
extra coordinate carriers or explicit argument casts can move the reread.
The two post-ring wave requests in 412/416 use receiver `field_168`, while
750 publishes its transition through global `g_info_manager`.

Action 525's direct spawn coordinates remove an artificial eight-byte scratch
area and recover the native frame. Keep `-n*90.0` so VC8 emits FCHS and a
positive-90 multiplication. Negative integer offsets in 302/520/521 and 567
instead convert through float where native uses FISUB. Landing comparisons in
542/567 retain a double next-Y value; narrowing it early changes the branch
for sufficiently large heights. Action 730 uses the float unsigned correction
before widening to double, and 741/750 use signed timer division and bounds.

560/561 initialize only packet slots 1 and 2 before their burst loops. 565/566
really initialize slot 0 as well. Sharing one aggregate-initializing helper
added two native-absent stores and permuted twelve other packet homes. Split
those sites according to their actual writes. Ring storage remains four
floats with count three; shrinking it while still reading slot 3 is invalid
and did not improve the bytes.

567 keeps its observed `word_738 == 1` branch, even though both arms compute
numerically equal X coordinates. Put Y's expression in each call arm so VC8
shares its addition between CMP and JNE. 606 selects layer -1 for `sin(p[0]) > 0`
and layer +1 otherwise. The old `<= 0` ternary mishandled unordered results.
The other burst predicates retain ordered `>= 0 && <= 180` tests.

605's surface burst needs direct direction and coordinate arguments. A scalar
direction carrier changed register allocation and prevented 602 from sharing
605's select/zero-motion/surface tail. Expanding this callback-sensitive loop
removed exactly 32 bytes and the two surplus calls. Removing direction carriers
from every burst instead merged unrelated owners and was rejected.

224 returns immediately after advance-triggered action-zero cleanup, like 201.
Using an else/end-of-case return retained the same local behavior but reversed
the physical cleanup owner. In 604, place the sequence guard outside independent
frame tests; combining timer with that outer guard loses the native zero
register and its uses. 404/405/406 also retain independent entry tests.

Flatten the story prefix into two independent ordinary conditions. Its early
return helper produced the same entry instructions except reversed constant
initialization, while a synthetic single-iteration block disturbed unrelated
owners. The independent conditions reproduce the complete prefix. Keep the
compound action-dispatch skip `word_186 || related_170->word_48c`.

99 declares its integer loop index before its sample pointer. Indexing the
array directly also matched 99, but changed value numbering enough to reverse
740's FADD operands. In 740, convert the start index before the difficulty
switch, then initialize the mutable index before the sample pointer. These
lifetimes reproduce both the duplicated post-switch saves and pointer setup.
The difficulty case order is 3/2/1/0; integer `abs` emits CDQ/XOR/SUB.

## Validation and remaining limits

The switch verifier now recognizes native `MOV EBX,7` between CMP and JA in
720, preserving the selector and flags. Focused positive and selector/width/
flags/bypass negatives pass. Existing Alice, Marisa and Sakuya objects were
fully re-compared through the changed verifier and remain canonical exact.
These are comparator smokes, not fresh source builds for those three units.

Original nominal class/TU declarations and several field meanings remain
unknown. Difficulty locals outside 0..3 and 604's mode-1 packet slots 0/1 remain
unwritten as observed; no fallback values were introduced. Exact credit comes
from the complete code, switch data and relocation replay above.
