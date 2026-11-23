# InfoEffectObject update at `0x0065CB40`

The [update source](../src/battle/InfoEffectUpdate.cpp) matches all 14,783
callable bytes and the entire 15,330-byte payload with 493 relocations.
The payload includes 84 jump destinations, 207 index bytes and four
alignment bytes. The configured VC8 SP1 unit is
`exact-first-info-effect-update`.

## Current-target evidence

Only original Japanese 1.06a SHA256
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e applies.
All 3565 decoded instructions are reachable, with 10 RET 0 exits. The complete
signed-short action dispatch closes 144 IDs: low 1..33, separate 100, high 101..274
and 900..922. Source case IDs are independently equal to the raw table/range set.

Code end is exclusive 6604FF, then one NOP. Low table 660500 has 12 entries/48
bytes; its 33-byte map begins 660530, followed by three alignment bytes. High
table 660554 has 72 entries/288 bytes; its 174-byte map starts 660674. Complete
payload ends 660722; fourteen INT3 bytes isolate 660730. All 547 non-code bytes
are compared, never added to authored-code credit.

Code SHA256:
e204892021b5c8ab702961a46f650c532e05f5ef4f095ba363e37fcc91638367.
Full target SHA256:
6b1ddd188d86f1ae825e31b0b7eea565eb482aece797305ffe733b391fe9f695.
Earlier typed candidate SHA256:
9ffe80ba2adc4d6abb5964d2a5a55a3182e880b2b0742d40c293a670bd694c4f.

InfoEffectObject primary vtable 6C37EC slot 28 cell 6C3814 owns this body.
COL 6D98B4 and descriptor 6E7C38 name .?AVInfoEffectObject@@. The origin rule
pins the whole body, RTTI and four calls; source presence alone is not evidence.
The source receiver is pointer-only, not an allocatable complete class.

All 72 physical calls remain: info emission 6609C0 fifty-seven, event 4359F0 two,
cosine 4063D0 two, info state 6609F0 one, animation 4351C0 four, game mode 43AC40
three and sine 406360 three. All 493 candidate relocations resolve:72 REL32 and
421 DIR32. This census is supporting evidence, not byte acceptance.

Factory-native IDA hash/metadata, entry 68B9D2, mapped bytes and function
inventory were freshly attested. The direct launcher lacks mcp/uv. Target PE
supplies instruction/boundary facts; decompiler output remains a hypothesis.
Supported void-thiscall name/prototype was updated and read back; no byte patch.

## Complete source coverage

- Low 1/2 grow scales or dispatch event 47, then advance animation.
-10..13 emit 20 on the first frame, cosine-grow until 15, then shrink both
  scales. At 90 they emit 15 and 21 and retire immediately without advancement.
-15..18 retain different initial emit/event/dispatch behavior, scale thresholds
  and ages30/60/120. Low-alpha retirement returns before animation.
-20 retires exactly at 90;21/22 expand/fade;30/31 cosine-modulate alpha and
  manually increment time without animation;32/33 only advance.
-100 and 110..250 emit family-owned label/conditional highlight/period60 pulse
  effects and use primary event state to enter fading. Mapping is not linear:
  action 200 corresponds to state 17,210 to 10,220..250 to 11..14.
-100/210/250 additionally require primary event state, mode!=16 and nonzero
  get_game_mode for their highlight emission. Other ordinary owners check
  the fighter-state global directly. These distinctions are not generalized.
-Grouped101/111..261 sine-modulate alpha and grow shared scale; age 60 retires.
 102/112..262 fade and clamp time 30 before sine-growing scale.
-Each ..3/..4 arm shrinks toward scale 1 and compares the independently selected
  primary/secondary event global; its float 174 retirement flag is preserved.
-Each ..5 arm has its own scale settling, float 174 age, late anisotropic growth
  and alpha control, followed by a second primary-event alpha decision.
-260 differs: it emits 263 and pulses261 using current primary event 15 directly,
  not a float 174 latch.263/264 similarly use current globals without the latch.
-270 emits 273 and retires only on its first frame.273 requires both event
  globals 16;274 shrinks and checks only secondary 16.
-900..922 decrement alpha modulo 256 after signed-short frame 142>150 and retire
  only when subtraction reaches zero. Below frame 30 they sine-position X; they
  still advance and may independently retire on animation completion.

All numeric states and offsets remain provisional names. No actual gameplay,
rendering, RNG or hardware execution is claimed.

## ABI and floating-point corrections

First complete source 14782/full payload was compiled before broad tuning.
Putting each actual animation call in its owning case restores the native
partial EBX save: low/range paths do not save EBX, high dispatch saves it only
at 65D12D. One common post-switch call did not preserve that physical context.

The first helper declarations incorrectly assumed cdecl based on decompilation.
Raw 6609C0 ends RET 20 and 6609F0 ends RET4. Call sites also prepare ECX=self;
the callees overwrite ECX with their globals and do not consume incoming self.
Local declaration-only member-compatible facades preserve both caller ECX and
callee cleanup without inventing a helper implementation or changing shared ABI.
The weather helper 665470 is separately cdecl and is not interchangeable.

Native low 15..18 comparison is ordered <= threshold, with unordered taking the
slow-growth alternative. A > ternary would choose the wrong unordered branch.
Explicit real growth branches also remove unnecessary carried-double temporaries
and restore the target x87 operations. No forced rounding environment is added.

Trials: first 14782; case-owned advancement 15398; corrected member facades 15294;
ordered growth 15346; physical high case 274 after 270/273 gives 15326. The selected
candidate has exactly 14779 callable bytes. Independent low 21/22 copies worsen
to 15386; independent 900..922 copies worsen to 16976. Those controls are retained,
not selected, and the duplicate-case lane is closed absent fresh evidence.

That trial still differed in the low retirement epilogues, the high
saturated-alpha tail and frame load scheduling in 900 through 922.

## Typed update state, 2026-11-10

The complete update now uses a nonconstructing `InfoEffectState` view instead
of the FIELD/F/I/S/B byte-offset macros. All 1,403 accesses name their actual
coordinate, scale, alpha, action, frame, time, lifecycle-state or fade-latch
field. Compile-time assertions fix the accessed offsets and 0x178-byte view.
Unused sprite and animation storage remains opaque; no object is constructed
and no virtual interface is fabricated.

The target's signed-short action/frame and signed DWORD time observations are
retained. Alpha is an unsigned byte, preserving its modulo-256 subtraction.
The lifecycle DWORD uses the existing `CObjectBase::state_000` unsigned width
at completed-object +0x158; this routine only decrements it. Coordinates/scales
and float 174 agree with the separately exact visual initializer's storage.
All 144 case labels retain their original order and every statement retains
its source position within the branches.

The final entire COFF section contents and relocations are identical to the
fresh baseline. The full 15,326-byte canonical candidate still has SHA-256
`9ffe80ba2adc4d6abb5964d2a5a55a3182e880b2b0742d40c293a670bd694c4f`,
including all switch metadata and all 493 resolved relocations. It remains
nonexact against 15,330 target bytes, with the same first mismatch at +19.
No source-spelling or epilogue search is reopened.

An initial attempt to reuse the visual method's full animation-sprite type
exposed its transitive GameMode getter declaration, which conflicts with the
update's existing int-return facade. Reusing that full type would require a
separate shared-ABI/binding change. The final bounded update view avoids that
unrelated change. The visual source was restored and its two complete roots
replayed at 80/80 and 266/266 exact.

## Shared exits and frame reads before the match

The match unit now runs the existing compact-switch check once the
callable comparison passes. The raw target passes the structural check
with its two decoded dispatch sites, 84 destinations, 207 index bytes
and both alignment spans. Single-byte changes to either index table,
a destination or the alignment fail comparison. The target check uses
the relocation sites implied by the raw instructions and tables. A
candidate must supply those bindings from its actual COFF relocations.

Of the 144 action IDs, 120 pair through all reachable instructions
after rebasing branches, including the original branch widths. Some
of those actions reach a different physical copy of the same
retirement instructions. The remaining shape differences cluster in
100 and the single body for 900 through 922. Both index maps agree
and all 493 relocations resolve in the complete replay.

The alpha tests for 15, 17, 16/18, 21/22 and 100 reach the retirement
at `0x0065CC9E` in the target. Their five candidate branches all
reach `0x0065D0F1`, the retirement after animation advance. The 100
branch also shrinks from six to two bytes. The first explicit goto control
yields the same 15,322 bytes. In both early builds the successful alpha
update is the conditional destination
before the late `0x10B2C950` pass. Under `0x10B2E0D0`,
`0x10BF2C00` replaces the branch operand as the pass moves
the subtraction onto the fallthrough and points the branch at the
nearer retirement. Sharing the low animation advance in source
also combines the previous growth branches of 15 through 18.

For 900 through 922, the target compares `[ESI+0x142]` with 150
at `0x00660482`, then reads it into EAX at `0x0066049C`.
The rebuilt code reads it into EAX before both comparisons.
VC8 enters with two separate definitions at `0x10C064F9`.
The first `0x10BAF600` call folds each definition into its own
memory operand. They remain separate on entry to `0x10B49300`
at `0x10C06D03`, with identical memory type and different address
temporaries. By the return at `0x10C06D08`, both comparisons
reference the same 16-bit value, before physical register assignment.
Capturing a short after the fade keeps the earlier load and adds
`MOVZX EAX, AX`. An unsigned short capture and a read through the
effect animation view emit that same output. Selecting the real
`CObjectBase` member in the fade leaves the original complete replay
intact. RTM 14.00.50727.42 and SP1 14.00.50727.762 reproduce the same
selected payload and relocated values at all 493 sites.

The shorter selected body uses the existing `GameMode` declaration
for the exact getter at `0x0043AC40` and preserves all 72 calls.
The clearer alpha branch and named sine angle preserve the full
canonical candidate with SHA-256
`8b8a8449490a12b4f60fc9949d7938e65831bc43f55a644a0940d492f873d5c0`.
The compiler traces replay the ordinary objects in full.

## The retirement order and frame references that match

The positive-first alpha guard already points to its own pre-animation
decrement at `0x10C077B1` in SP1's `c2.dll`. The late tail comparison at
`0x10B30784` offers the post-animation decrement in case 100 first. The
splice at `0x10B30CE6` removes the earlier copy. The guard's label now
precedes the retained post-animation decrement.

Moving only the case 10 retirement return below case 100 changes
the order of the competing returns. The same trace offers case 10
first and splices the alpha-retirement copies into it. The two emission
calls and the retirement stay in their original machine-code positions.
All five alpha guards reach `0x0065CC9E` and the animation tail stays
at `0x0065D0E6`. The trial that moved all of case 10 also gave it the
retirement and displaced the low switch entries. Routing all five guards
directly to the new source label sent them back to the late retirement copy.

For 900 through 922, the inline fade helper takes the frame, alpha and
lifecycle state by reference. It emits the signed memory comparison at
`0x00660482` and leaves the second read at `0x0066049C` in the caller.
The [battle setup token check](VC8_SOURCE_SHAPE_PATTERNS.md#patterns-that-produced-exact-matches)
uses the same source shape. The position update and animation advance
still run on their original paths.

The full replay and strict unit both match the pinned payload hash.
Changing the pre-table NOP or one valid low map index in a copy of the
COFF object leaves callable bytes equal and fails the complete comparison
at `0x006604FF` or `0x00660533`, respectively. The owner diagnostic
uses the callable boundary when the complete code and pre-table alignment
agree, so that the NOP stays outside the final owner. To reproduce
the focused check and diagnostic, run

```sh
scripts/repo-python scripts/build.py --unit exact-first-info-effect-update --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py info-effect-update \
  build/match-units/ExactFirst_InfoEffectUpdate.obj --unit exact-first-info-effect-update
```
