# InfoEffectObject update65CB40: complete nonexact source

Source src/battle/InfoEffectUpdate.cpp covers the complete14783-byte target.
It remains **nonexact**:14779 callable/full15326 candidate versus14783/full15330.
A four-byte length deficit is not four unequal bytes: displaced code/branches
produce many differing positions. Both canonical focused and full-tail audits
fail at+19. No matches row or exact credit is added.

## Current-target evidence

Only original Japanese1.06a SHA256
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e applies.
All3565 decoded instructions are reachable, with10 RET0 exits. The complete
signed-short action dispatch closes144 IDs: low1..33, separate100, high101..274
and900..922. Source case IDs are independently equal to the raw table/range set.

Code end is exclusive6604FF, then one NOP. Low table660500 has12 entries/48
bytes; its33-byte map begins660530, followed by three alignment bytes. High
table660554 has72 entries/288 bytes; its174-byte map starts660674. Complete
payload ends660722; fourteen INT3 bytes isolate660730. All547 non-code bytes
are compared, never added to authored-code credit.

Code SHA256:
e204892021b5c8ab702961a46f650c532e05f5ef4f095ba363e37fcc91638367.
Full target SHA256:
6b1ddd188d86f1ae825e31b0b7eea565eb482aece797305ffe733b391fe9f695.
Selected full candidate SHA256:
9ffe80ba2adc4d6abb5964d2a5a55a3182e880b2b0742d40c293a670bd694c4f.

InfoEffectObject primary vtable6C37EC slot28 cell6C3814 owns this body.
COL6D98B4 and descriptor6E7C38 name .?AVInfoEffectObject@@. The origin rule
pins the whole body, RTTI and four calls; source presence alone is not evidence.
The source receiver is pointer-only, not an allocatable complete class.

All72 physical calls remain: info emission6609C0 fifty-seven, event4359F0 two,
cosine4063D0 two, info state6609F0 one, animation4351C0 four, game mode43AC40
three and sine406360 three. All493 candidate relocations resolve:72 REL32 and
421 DIR32. This census is supporting evidence, not byte acceptance.

Factory-native IDA hash/metadata, entry68B9D2, mapped bytes and function
inventory were freshly attested. The direct launcher lacks mcp/uv. Target PE
supplies instruction/boundary facts; decompiler output remains a hypothesis.
Supported void-thiscall name/prototype was updated and read back; no byte patch.

## Complete source coverage

- Low1/2 grow scales or dispatch event47, then advance animation.
-10..13 emit20 on the first frame, cosine-grow until15, then shrink both
  scales. At90 they emit15 and21 and retire immediately without advancement.
-15..18 retain different initial emit/event/dispatch behavior, scale thresholds
  and ages30/60/120. Low-alpha retirement returns before animation.
-20 retires exactly at90;21/22 expand/fade;30/31 cosine-modulate alpha and
  manually increment time without animation;32/33 only advance.
-100 and110..250 emit family-owned label/conditional highlight/period60 pulse
  effects and use primary event state to enter fading. Mapping is not linear:
  action200 corresponds to state17,210 to10,220..250 to11..14.
-100/210/250 additionally require primary event state, mode!=16 and nonzero
  get_game_mode for their highlight emission. Other ordinary owners check
  the fighter-state global directly. These distinctions are not generalized.
-Grouped101/111..261 sine-modulate alpha and grow shared scale; age60 retires.
 102/112..262 fade and clamp time30 before sine-growing scale.
-Each ..3/..4 arm shrinks toward scale1 and compares the independently selected
  primary/secondary event global; its float174 retirement flag is preserved.
-Each ..5 arm has its own scale settling, float174 age, late anisotropic growth
  and alpha control, followed by a second primary-event alpha decision.
-260 differs: it emits263 and pulses261 using current primary event15 directly,
  not a float174 latch.263/264 similarly use current globals without the latch.
-270 emits273 and retires only on its first frame.273 requires both event
  globals16;274 shrinks and checks only secondary16.
-900..922 decrement alpha modulo256 after signed-short frame142>150 and retire
  only when subtraction reaches zero. Below frame30 they sine-position X; they
  still advance and may independently retire on animation completion.

All numeric states and offsets remain provisional names. No actual gameplay,
rendering, RNG or hardware execution is claimed.

## ABI and floating-point corrections

First complete source14782/full payload was compiled before broad tuning.
Putting each actual animation call in its owning case restores the native
partial EBX save: low/range paths do not save EBX, high dispatch saves it only
at65D12D. One common post-switch call did not preserve that physical context.

The first helper declarations incorrectly assumed cdecl based on decompilation.
Raw6609C0 ends RET20 and6609F0 ends RET4. Call sites also prepare ECX=self;
the callees overwrite ECX with their globals and do not consume incoming self.
Local declaration-only member-compatible facades preserve both caller ECX and
callee cleanup without inventing a helper implementation or changing shared ABI.
The weather helper665470 is separately cdecl and is not interchangeable.

Native low15..18 comparison is ordered <= threshold, with unordered taking the
slow-growth alternative. A > ternary would choose the wrong unordered branch.
Explicit real growth branches also remove unnecessary carried-double temporaries
and restore the target x87 operations. No forced rounding environment is added.

Trials: first14782; case-owned advancement15398; corrected member facades15294;
ordered growth15346; physical high case274 after270/273 gives15326. The selected
candidate has exactly14779 callable bytes. Independent low21/22 copies worsen
to15386; independent900..922 copies worsen to16976. Those controls are retained,
not selected, and the duplicate-case lane is closed absent fresh evidence.

Remaining differences are shared low retirement epilogues, placement of the
high saturated-alpha tail and frame142 load scheduling in900..922. They displace
otherwise similar sequences. Do not treat normalized per-case instruction
comparison, complete IDs or matching call counts as exactness. No register
forcing, inert values, copied bytes, padding, masked matching or LTCG claim.

## Reproduce and scope

- scripts/repo-python scripts/build.py --unit exact-first-info-effect-update --compare --json
- scripts/repo-python scripts/audit-info-effect-update.py
- scripts/repo-python scripts/validate-tracking.py --require-target
- scripts/repo-python scripts/ci.py

The first two commands currently exit1 with mismatch, not blocked.
Complete controls and full raw CFG/table/ID/call evidence are under
build/frontier-65cb40-20261027/ and corresponding private analysis directory.
The initial generator is not the selected later source.

Only this new unit is rebuilt. No shared header/flag/global/literal mapping
changes; prior receipts remain retained and totals are incremental. Final local
CI is pending at writing; its terminal exit/log is the commit gate.
