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

- **Integer comparison constants are emitted as written** (`x < 1` is not
  `x <= 0` to VC8). A greedy respelling pass over the giant character
  functions removed hundreds of differing instructions; the target's `cmp`
  immediate gives the source literal. Float comparisons need the ordered form
  the target tests (`!(a > b)` is not `a <= b`).
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

For shared Fighter `0x004740C0`, the read-only VC8 trace identifies
`c2.dll:0x10B281E0` as the pass that places the 73/75/88 selection tail
after action 88, before x87 lowering. The next useful control is to compare
the input block ordering with a source variant that keeps all three
predecessors. The 53/66 owner baseline and its complete relocated bytes
survive the clearer sequence label and comparisons. The 10,725-byte
comparison contract now covers both switch tables and recognizes the
eight virtual tails alongside the bound direct tails. See the
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

With a shared switch exit in Youmu, the late C2 pass at 0x10B2C950 discards
the publication in 601 and retains it in 604. Sakuya's Object initializer
has 13 differing bytes in 803. Omitting either 800 or 801 in a scratch
build restores 803's native register choices. The 801 facing-byte load
advances the search position at `c2.dll:0x10D0F854`, so the full build's
803 virtual target search starts at ECX and skips the available EAX.
See the [Youmu](YOUMU_FIGHTER_ACTION_INITIALIZATION_2026_10_25.md) and
[Sakuya](SAKUYA_OBJECT_ENTRY_2026_10_24.md) case notes.

Sakuya's Object update `0x004E0D30` now retains both 803 alpha calls and
joins their continuation before sequence 2. The 920 match-ID switch
uses the original stub order, and the original signed cutoff in 816
restores the earlier 811 constant registers. Hardware watchpoints locate
that decision inside the whole-function pass at `c2.dll:0x10B0CF40`.
The original 816 cutoff delays splitting the whole-function group for 2.
The zero argument is allocated first and takes EDI.
Sequences 2 through 4 of action 815 now share the target's channel fade,
with checked byte-channel and signed time-counter fields. Action 930 now
agrees through its bounds checks. The late pass at
`c2.dll:0x10B2C950` still folds 816 and 930 into other frame calls.
Omitting 816 in a scratch build restores the 920 BP versus 930 BX
comparisons before that pass and both frame calls survive. Recover the
competing register live ranges with all of 816 present. Action 854
agrees through its shared saturation and return paths. The parameter,
owner and parent accesses now use checked members.
The complete candidate is 29,200 bytes with 737 relocations. The first
difference is at `0x004E0D55`. Actions 859 and 901 still need to recover
the target's four fade guards and two shared low-channel tails.
[Case note](SAKUYA_OBJECT_UPDATE_2026_10_25.md#actions-920-and-930-before-frame-advance)

Other open leads:
- Scenario character install 0x456EB0 (one EH-state store) and the info
  effect update 0x65CB40 (14,783 bytes, two regions).
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
