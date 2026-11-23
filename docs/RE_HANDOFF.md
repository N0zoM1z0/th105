# TH10.5 reconstruction handoff

Follow [AGENTS.md](../AGENTS.md). Reconstruct only the original Japanese
TH10.5 v1.06a executable with SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.

Read live status from the ledgers rather than from this note:

```bash
git status --short
scripts/repo-python scripts/report-reconstruction-status.py --summary
```

## How the recent gains were made

Read [VC8 source-shape patterns](VC8_SOURCE_SHAPE_PATTERNS.md) before retrying
any near-miss. It lists the source shapes that produced exact matches and every
parked residual with what was tried. The most productive rules:

- **VC8 can preserve the written integer cutoff** (`x < 1` and `x <= 0`
  often emit different comparisons). A greedy respelling pass over the giant
  character functions removed hundreds of differing instructions. Check
  whether the target `cmp` reads an immediate or a register before choosing
  a source shape. Float comparisons need the ordered form the target tests.
- **Duplicate a shared tail in source** when one branch jumps into another
  branch's tail. VC8 then cross-jumps the copies the way the target does. This
  closed the scenario list fade 0x455850, the battle menu update 0x4407E0 and
  Komachi's initializer 0x5F6700.
- **Texture handles are the 4-byte class `DesignTextureHandle`**
  (`engine/TextureHandleValue.hpp`), taken by value by the binder 0x404DF0 and
  the release 0x404D70. Fields that callers pass to them are class-typed;
  vectors proven `vector<unsigned>` by native helpers keep `unsigned`.
- Prefer checked typed members for target-observed storage, as in the
  [Sakuya initializer](RE_WORKFLOW.md#sakuya-action-initializer). The exact
  roster initializers now verify their dispatch tables, and the macro-heavy
  Fighter initializers use checked members for fixed scalar offsets. Keep
  composite access provisional where the full subobject layout is uncertain.
  An offset macro can preserve VC8 scheduling that changes with an inline
  `at<T>` accessor.
- For giant switches, [locate differences by action and shared tail](RE_WORKFLOW.md#giant-root-owner-diagnostics)
  before tuning a case. Finish each trial with the full comparison.
- A "remote chunk" reached by `jmp` after an epilogue is usually a tail call
  to a separate function (the scene frame update 0x43B4A0 tail-calls 0x4400D0).

For equal-size residuals, inspect statement order, branch direction, scopes
and literals together with the shared tails and visible definitions that
can change instruction selection elsewhere. Earlier RTM, LTCG, `/Z7`, `/fp`
and `/Os` trials left several such residuals unchanged.

## Giant action root follow-up

Shared Fighter `0x004740C0` now differs by seven bytes across the complete
10,725-byte envelope. Local rounded assignments restore 55/56. Giving 50
the direct return and 62 the switch exit lets 50 merge 159–162 before 62
consumes their return edges. All clamp and sequence paths now match, as
do both switch tables and the alignment byte. The remaining two
instructions are `ADD EAX,-50` and `ADD EAX,-691` at `0x004740DE` and
`0x00475E20`, where the target has `SUB` with positive immediates. The
first byte difference is `0x004740DF`. At `0x10C0B1FE`, VC8 sees distinct
input and result symbols in the split shape and one symbol in the flat
shape. This decides the instruction before both builds allocate EAX.
A flat control now puts 690 back in low case 54, with merged slots and a
moved default return. See the
[compiler trace](COMMON_FIGHTER_VC8_LAYOUT_2026_11_23.md) and the
[engine and Oracle review](GIANT_ROOT_REVIEW_2026_11_23.md).

## Open work

Smallest remaining character residuals, after the literal pass:
- Alice CPU policy 0x4F4B80 (about 40 differing instructions);
- the control-mode functions: Aya 0x616800, Patchouli 0x51CB40 (+8 bytes of
  frame), Suika, Yukari, Tenshi;
- the object-entry functions of Sakuya, Marisa, Patchouli and Yuyuko, and the
  Marisa CPU dispatch tails 0x4B4070;
- the Youmu initializer 0x53A1D0.

Reimu's initializer at 0x491C40 is exact. Cases 404/406 and 414/416 reach
one flag reset after the switch. VC8 shares their already-lowered x87
multiplication forward into 414. See the [case note](REIMU_ACTION_INITIALIZATION_2026_10_25.md#shared-reset-after-the-switch).

Udonge's initializer at 0x5D0E60 matches all 5,070 bytes with its three
switches. In 404/406, moving the horizontal multiply before the final flag
write also restores the separate native scaling tail in 650.
See the [Udonge case note](UDONGE_ACTION_ENTRY_2026_10_24.md).

Youmu `0x0053A1D0` now expresses the 602 reset as a fallthrough and still
differs at 44 bytes in the complete 1,874-byte envelope. For independent
phase arms, C2 first places the 602 entry in 601. It finds five matching
601/604 instructions but rejects the pair because its size estimate
stops at 20 bytes before the call, and the merge requires more than 20
at `0x10B30B74`. A shared switch exit leaves 604 falling through, so the
late splice keeps its copy. Komachi's exact 550/551 uses the same splice
with the native fallthrough already in place. A resolved LTCG build of
the relevant Youmu actions reaches the same cutoff, even when the compiler
sees the exact motion-reset definition and keeps its calls. Follow the
block layout before changing store order or receiver scheduling.
See the [Youmu case note](YOUMU_FIGHTER_ACTION_INITIALIZATION_2026_10_25.md#vc8-rejects-the-independent-tails-at-a-20-byte-cutoff).

Sakuya's Object initializer
has 13 differing bytes in 803. Omitting either 800 or 801 in a scratch
build restores 803's native register choices. The 801 facing-byte load
advances the search position at `c2.dll:0x10D0F854`, so the full build's
803 virtual target search starts at ECX and skips the available EAX.
See the [Sakuya case note](SAKUYA_OBJECT_ENTRY_2026_10_24.md).

Sakuya's Object update `0x004E0D30` now reproduces all 387 reachable
instructions in 803 after rebasing, including both alpha calls and the
sequence 2 branch to the frame retirement. The signed phase byte at
`+0x184` restores all 17 native frame-call owner groups. It keeps
all uses of 30 in 920 in one EBX group and leaves EBP for the 920
zero. The 930 comparison still uses BX and its call survives. Both
actions agree through their complete reachable paths after rebasing.
Action 816 still merges two byte-identical retirement tails. The 811
constant registers have swapped again. The 815 fade and 854 saturation
paths survive these changes. The selected source has all four fade
guards and both shared saturation destinations. The reachable paths
of 859 sequences 5/6 and 901 sequences 4 and 7 agree after rebasing.
Action 998 sequence 1 enters the first native tail after the channel
clears. VC8's early `0x10B281E0` pass puts the clear block in 901.
The rebuilt clear block jumps to the alpha test in 998. All three 901
parent updates now jump to their native partners in 859 with the new
angle still on the x87 stack. All three paths agree through the shared
ECX reload and frame call. The comparison forms in 810 restore constants
in 818, 857, 859 and 901. Actions 800, 801, 812, 813, 818, 850, 857 and
sequence 0 of 859 and 901 agree after rebasing. Action 815 now has
the native frame cutoff. Its two x87 operand orders and alpha tail
still differ. Action 900 pairs after rebasing except for its two x87
landing-sum instructions. The entry Y bounds change the address
definition used by the early C2 pass. Compare how that definition
reaches the landing sum. Six 853 branches now use the native local
retirement. Only sequence 6's alpha exit still uses the 805 copy.
The 853 frame decrement and its layer argument still have EBP and EDI
eligible in the all-jump control. The two-use -1 group scores zero and
joins the layer group's split batch at `0x10B0D7F5`. It becomes immediate
-1 before `0x10B2C950` merges the frame call. The selected three-use
group gets EDI. The remaining lead is to restore the separate 805
retirement register so that 853 can keep all three uses.
The early pass at `0x10C26030` substitutes a symbolic operand for the
805 immediate cutoff. `0x10B130F6` links it to the five-use group for
2, and `0x10B17A46` installs BP after allocation. The `<= 1` control
uses BX for the cutoff and gives EBX to the separate -1 group. The
804 sequence test starts in the same group for 2 as the 805 cutoff.
`0x10B599B0` restores the 804 immediate after splitting removes `0x39A`
from the lookup sets. The 805 block retains the group for 2. Its three
comparisons each add one point against one definition. Removing just
the frame use leaves the four-use group at score 1, still in EBP.
`0x10B15562` removes the last eligible register from the first
805 spawn's -1 fragment after assigning a different group. The second
spawn and the retirement retain a separate register. Trace the first
fragment and its competing group together before retrying a cutoff.
Combining the 805 inclusive cutoff with the 804 positive-first phase
branch reproduces 804 and 853 after rebasing and reverses the x87
loads in 813, 815, 859 and 901. In `0x10BAF600`, the last two bits of
813's address-temporary ordinals break the tie between the two
scale reads. The 804 branch edit increases both ordinals by one,
flipping their order. The 802 cutoff edit advances both again and
restores the x87 order. Trace the creation and reuse of those
temporaries before retrying the phase branches. The selected
29,480-byte candidate shares the six scale updates in 815, 859
and 901. It preserves all 742 relocations and 17 frame-call sites.
The first difference is still at `0x004E0D55`.
[Fade tails](SAKUYA_OBJECT_UPDATE_2026_10_25.md#fade-tail-folding-in-actions-859-and-901)
and [retirement sharing](SAKUYA_OBJECT_UPDATE_2026_10_25.md#action-853-retirement-is-shared-with-action-805-in-the-rebuild).

Other open leads:
- Info effect update `0x0065CB40` now checks both jump tables through
  all 15,330 target bytes. The current 15,322-byte replay first differs
  at `0x0065CB53`. The two compact regions retain all 84 physical
  destinations. Five alpha guards choose the late retirement copy.
  The first `0x10BAF600` call preserves the two memory reads for
  900–922 until `0x10B49300` combines them. Inspect the memory
  definitions and intervening stores entering that pass.
  [Info effect update](INFO_EFFECT_UPDATE_2026_10_27.md#shared-exits-and-frame-reads-2026-11-23)
- Scenario character install 0x456EB0 (one EH-state store).
- LTCG context: `MenuCursorState::update` 0x41FA20 takes a propagated
  `int period` from its 35 callers, which explains its `idiv` by 6. The angle
  lookups 0x406360/0x4063D0 (`idiv` by 3600) and the menu callers' residuals may
  come from the same whole-program context.
- LTCG-private ABIs need linked units: `this` in ESI or EAX, 0x41B7F0, the PAT
  loader 0x461B70, and the shared `list::erase` 0x414DE0 behind 0x414D50 and
  0x419400.
- The text-texture pair 0x404D00/0x4097A0 differs only in LTCG promoting
  `width` into ECX. The gain conversion 0x418990 keeps two redundant float
  round-trips.
- The ACK-constructor CIL context lacks the IPacket base serialize/parse
  providers; recover them rather than inventing bodies.
- The CDesignBase loader links but differs in size (2666 against 2708) and
  frame (0x3E8 against 0x3F8); see
  [real gauge context](DESIGN_LOADER_REAL_GAGE_2026_11_02.md).
- The giant action roots have no exact entries. Komachi 0x5E20E0 has a
  complete unselected candidate (unit `exact-first-komachi-action-state`,
  108 actions). Its [checked motion fields](KOMACHI_ACTION_STATE_2026_10_28.md#checked-motion-fields-2026-11-23)
  preserve the compiled envelope. Its strict contract covers all seven
  tables. The ring-902 angle update restores frame `0x490`. The callable
  check now first differs at `+0x2A`, where native loads EBX before the
  card gate. The owner
  diagnostic follows all seven native dispatches with the split 209/212
  scratch variant. The VC8 graph reaches the shared flight block through
  212 first. The native 212 jumps back to that block inside 209. Reimu
  0x478FA0 has staged partial sources (`src/characters/ReimuActionState*`)
  and still needs a selected whole-root unit.

## Checking shared type changes

Follow [the affected-consumer replay rules](RE_WORKFLOW.md#shared-change-replay).
Inspect include closures and compare the affected accepted units after a shared
layout or header change. Check origin anchors when the change touches their
evidence. The short and unsigned deque pop-back, input cleanup, and VC8 float
sine proofs validate fresh emitted code and its call or type evidence. Their
build records capture the source hash automatically. The roster pointer
manifests cover their physical slots across exact-status changes.

## Session rules

Keep one writable reconstruction scope and run VC8/Ghidra serially. Attest an
analysis session before using its semantics. Source presence, semantic probes
and a successful link confer no exact credit. Run the focused comparisons and
`python3 scripts/ci.py` before each commit.
