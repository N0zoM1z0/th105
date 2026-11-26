# Komachi action-state root (`0x005E20E0`), JP 1.06a

## Status and scope

`exact-first-komachi-action-state` is **canonical exact** from the
character-scoped [source](../src/characters/KomachiActionState.cpp) and
[checked receiver](../src/characters/KomachiActionState.hpp), under VC8 SP1
`/O2 /GS- /GR /EHsc /MT`.

- All 63,993 callable code bytes (`[0x005E20E0, 0x005F1AD9)`) and the complete
  65,176-byte seven-table switch payload (`[0x005E20E0, 0x005F1F78)`) match
  with zero byte differences.
- All 1,864 COFF relocations agree: 915 `REL32` calls across 30 targets and
  949 `DIR32` fields. The 1,183 metadata bytes contain 7 switch tables, 120
  destination words, 692 index bytes and 11 alignment bytes.
- The owner audit is `107/107` (`106` unique switch destinations plus `entry`).
  Raw CFG reaches all 16,310 instructions / 63,993 authored bytes with zero
  internal alignment holes.
- Code SHA-256: `bb737abb720d627a985ae38f3b3f11f0cabf31b7ad0b7f89ab7a6f809ea9b8bd`.
- Payload SHA-256: `20d83eff7214346536177a1391fa993ccf62081c1b9ebc5aa048edc005094204`.

Reproduce with:

```bash
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit exact-first-komachi-action-state --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py --unit exact-first-komachi-action-state komachi-vslot28 build/match-units/ExactFirst_KomachiActionState.obj --json
```

### Key source-shape fixes for canonical equality

- **Byte direction parameter on `effect` (`0x00435240`)**: declaring the 4th
  argument as `unsigned char` removes redundant `movsx` casts in `201`/`203`/
  `224`/`225` and matches the `movzx` argument preparation used by `spawn`.
- **Preventing `facing_104` hoisting across trig calls**: reading `facing_104`
  directly (instead of through an `int` getter) in `emit801`, `swap820`, `730`
  and `214`, plus keeping `float dx` in `aim()`/`aim_short()`, restores
  `fild; fmulp` and exact per-call `movsx`/`movzx` reloads across `400..416`,
  `541..543`, `560..567`, `602` and `214`.
- **Inlining early-return helpers and post-switch `advance()`**: moving the
  shared `advance()` tail after `switch (action_id_13c)` for `0, 2, 4, 5, 9`
  and inlining `high_jump` (`208..212`), `air_normal_land` (`306..309`),
  `air_shot_landing` (`414..416`), `air811` (`507..508`), `swap820`
  (`540..543`) and `ring902` (`730`) restores all 106 unique switch
  destinations and every native tail-merge.
- **`case 730` (`ring902`) frame size and LIFO stack-slot packing**: writing
  `coord = static_cast<float>(n * 45.0 + base_angle); packet[0] = static_cast<float>(n * 45.0 + base_angle + jitter + 180.0);`
  without an intermediate `double angle` local prevents VC8 LICM from spilling
  `jitter + 180.0` to a `qword` temporary (restoring the `0x490` frame) while
  avoiding `fstp; fld` rounding. Hoisting `float coord;` before `switch
  (g_match_identifier)` with per-loop `for (float n = 0.0f; ...)` restores
  VC8's descending-weight LIFO slot packing (`esp+0x10` vs `esp+0x28`) across
  all 15 affected owners.
- **`case 405` nested air-landing guard**: writing `if (sequence_index_13e < 2)
  { if (static_cast<unsigned char>(crossed())) { ... return; } }` reorders the
  merge-block predecessors in VC8's `InsertAdditionalSplits`, restoring the
  local `mov ebx, 1` hoist at `+0x47FB` and eliminating the final 2-byte diff.

The dated notes below retain the earlier discovery and code-generation trials.

## Current-target evidence

Factory-native IDA metadata hashes/size, entry 0x68B9D2, inventory probe
0x401000/52 bytes, and five mapped 16-byte samples matched the original
Japanese 1.06a target at 04:14–04:15 UTC on October 28. The full decompiler
artifact returned at 04:17; it is a semantic hypothesis, not source proof.
The legacy local check-ida-mcp.py still lacks mcp==1.26.0. No package
installation was used and that legacy command is not recorded as passing.

Raw hash-attested CFG:
- Callable: 0x5E20E0..0x5F1AD9, 63,993 bytes.
- All 16,310 instructions / 63,993 bytes reachable; no alignment holes.
- 136 RETs; 915 direct call sites to 30 targets.
- Seven resolved tables; no unresolved indirect exit.
- Three action tables: low 34, mid 41, high 31 physical destinations.
- A two-destination card gate with nine remap bytes.
- Three four-entry tables keyed by the match identifier (the first has three
  unique destinations). The [later audit](GIANT_ROOT_REVIEW_2026_11_23.md#what-the-byte-check-covers)
  ties these reads to the battle setup writer.
- Direct actions 300, 540, 795, 797, 798 are outside the sparse tables.
- Full payload ends 0x5F1F78, 65,176 bytes; next callable starts 0x5F1F80.

Callable SHA-256:
bb737abb720d627a985ae38f3b3f11f0cabf31b7ad0b7f89ab7a6f809ea9b8bd

Full target SHA-256:
20d83eff7214346536177a1391fa993ccf62081c1b9ebc5aa048edc005094204

## Source and data-flow findings

The pointer-only view is not a complete recovered Fighter class.

All forty native crossed-surface consumers test AL. All twenty-four native
on-surface consumers also test AL; one loads a vtable pointer before TEST,
which the generic immediate-consumer summary does not recognize.

The native and candidate each have 94 resolved spawn-payload homes and no
unknown payload-pointer sites. Their sorted offset sets are identical:
56..1172, step twelve. This is an offset-set observation, not proof that
each action owns the same home. Native/candidate frames now both equal 1168 bytes.
Candidate physical return sites are 137 versus 136; virtual call sites
191 versus 192.

Three native virtual calls belong to the peer at receiver+0x170, not self:
0x5EED38, 0x5EF5B3, 0x5EFD89. The private stack diagnostic admits those only
after proving the local peer load, vptr load and slot+8 target chain, with
the normal four-byte argument purge. It does not accept arbitrary unknown
virtual receivers.

Recovered distinctions include:
- 540 applies the skill-606 peer cooldown before surface rings; 542 applies
  skill-60A cooldown afterward. 541/543 have their own skill-606 extra ring.
- 550 advances before clearing field 180; 551 clears before advancing.
- Only 203 clears frame_timer_142 on the shared air-dash landing path.
- 600 returns after successful advance/reset; 603 continues its entry logic.
- 710 preserves the original check of the old field 740 before replacing Y.
- 604 preserves its two peer/self health conversions and separate packet
  lifetimes rather than replacing them with an integer swap.
- Twenty-four ring layer predicates use ordered [0,180] membership. Native
  unordered comparisons take the negative-layer arm. The decompiler's
  apparent '<0 || >180' loses that behavior; the candidate now uses the
  actual ordered condition and complete per-arm argument preparation.

## Bounded byte-direction interface view

The candidate spawn declaration uses unsigned-byte direction with the same
four-byte ABI slot. This is supported by the real Komachi manager, not by
instruction matching alone.

The complete canonical manager 0x5F78C0 is 237 bytes, SHA-256
5facf0036e53de10e5916c20f880aa1bdff879ffd6212996a6f311072921bb80.
It reads only BYTE direction at 0x5F7962 (ESP+20 after two saves) and BYTE
variant at 0x5F7966 (ESP+24), stores them at object+104/+33C, and returns
RET 24. The accepted roster spawn source uses byte formals.

The shared 66-byte forwarding wrapper 0x465190 forwards full DWORD slots,
which does not establish int formals. Independently exact int and byte
forwarding witnesses are already recorded in

Those accepted sources are not modified here. Original signedness/type
spelling remains ambiguous; this is a supported binary call view. The
variant remains int in this candidate. No register or manual-stack facade.

Runtime boundary globals 0x6FBD24 and 0x6FBD1C are address bindings with
loader-zero contents, not numeric constants.

## Comparisons and remaining differences

Whole candidates were compiled before refinement:
- First complete int-direction candidate: 64,596 bytes, first +8.
- Ordered ring arms and separate virtual argument branches: 65,428, first +8.
- Byte-direction view: 65,156, first +8.
- Explicit wind turn branches: same length; final SHA below.

All mapped per-action floating arithmetic counts agree except 567, whose
native first 824 shot has two identical argument arms guarded by field 738.
Raw 0x5EE24F branches to separate calls 0x5EE2AD/0x5EE2F6 using the same
packet; the candidate coalesces them. Do not insert an inert branch to force
the duplicate physical sites.

Other physical-call diagnostics: 603 has eight/seven RNG call sites;
720 has seven/four spawn sites and six/three wave sites. These are reachable
physical sites, not dynamic execution counts. Shared tails/argument epochs,
constant materialization and exact instruction ownership remain unresolved.
Low 209/212 merge to one candidate owner, leaving 33 rather than 34 low
destinations. Source behavior and complete execution equivalence are not
claimed verified solely by these structural diagnostics.

The native flight 214 repeats the same resource gate twice without an
intervening write/call. The candidate keeps its logical condition once;
no volatile or inert duplicate gate is added.

## Reproduction

taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-komachi-action-state --compare --json
    scripts/repo-python scripts/ci.py
    git diff --check

The ordinary build command compares the callable. The separate full-payload
audit also checks all seven tables, reachability, length and unmasked bytes.
Both reported a mismatch for this checkpoint. Candidate SHA-256:
5ac7b06797104542570da85ab2029169a844efbcfa0f6bba55c766af74cd5771

61,429 positional differences including missing tail bytes are diagnostic,
not a completion percentage.

Checked-in source is authoritative.

## Scalar frame and request preparation refinement

The private VC8 source listing identifies the extra eight-byte allocation:
tv26973 is a qword temporary following all 94 arrays, holding jitter+180
hoisted out of action 730's loop for match identifier 3. It is not an extra packet.
Changing packet sizes or adding padding would not explain it.

Native 0x5F0DEF writes the angle to a DWORD home while retaining the x87
value, then adds jitter and 180 before writing the packet at 0x5F0DFD.
A float trajectory source expresses the observed scalar copy and removes the
extra hoisted qword. Angle-only control emits 65,188 bytes with frame 0x490
and first difference +42. This isolates the frame change from the separate
request-preparation edits.

The inference is bounded: actual loop indices are 0..11, base is roll(360),
steps are 30/45/60 and the optional offset is 22.5. Jitter is roll(20)-10.
All angle values here are small integer/half-integer values exactly
representable in binary 32. This is not permission to narrow arbitrary x87
intermediates elsewhere. The compiler's extra store/reload around the angle
still differs from native's FST-retained-value sequence, so the original
expression is not claimed recovered byte-for-byte.

801 and 902 circular emissions now calculate X/Y in their ordinary call
arguments instead of materializing both named coordinates before preparing
the request. The native pushes count/pointer/layer/direction before sine,
prepares outgoing Y before cosine, then calls spawn. The selected expression
restores that lifetime shape. Standalone controls emit 64,932 and 64,852
bytes respectively while retaining frame 0x498; neither alone explains the
frame recovery. The combined selected candidate is 64,884 / frame 0x490.

The unrelated dust-base narrowing hypothesis was explicitly rejected:
0x5E2D08 stores the captured X+50 as QWORD before RNG. Its existing double
capture is retained. No artificial local, register assignment or byte patch
was used.

Final stack audit still resolves all 94 payload homes; its offset set remains
56..1172 step twelve, unchanged from native. Physical call and arithmetic
residuals remain those described above. The preceding checkpoint is retained
in Git; none of these structural improvements adds exact byte credit.

## Action 603 spawn-height grouping, 2026-11-04

In both direction branches the native code at `0x005EF2A5..0x005EF2B3`
and `0x005EF2FA..0x005EF308` adds the exact double constant 20.0 to the
fighter's float height before adding the converted random value. The previous
source grouped the additions as `(random + height) + 20.0`. The candidate now
expresses `random + (height + 20.0)` in both branches. The fresh VC8 object
emits the corresponding x87 `fld height; fadd 20; faddp` grouping in each
branch; the target and candidate both round once to float for the argument.
This preserves an observed floating-point distinction rather than assuming
addition is associative. The compiler still shares the random call physically;
no general callback, FPU-mode or runtime equivalence is claimed.

The complete 63,993-byte callable / 65,176-byte target payload remains
nonexact. The fresh candidate payload is 64,900 bytes, SHA-256
`b8a7f166299864852d5ed6de61fdcb7290ac7021c537e02a6884e7b1667d77f0`,
with first mismatch +42 and 61,441 unequal positions over the full payload.
The source remains unselected and earns no exact credit.

## Actions 720 and 732 angle grouping, 2026-11-04

The native loops for action 720 (`0x005F0988..0x005F09AE`) and both action
732 surface branches (`0x005F1593..0x005F15A9` and
`0x005F1663..0x005F1679`) convert the random value, separately add 30.0 to
the loop angle, then combine the two x87 values. The source now reflects that
observed grouping in all three places. The new object emits the corresponding
`fild angle; fadd 30.0; faddp` sequence in each loop. For the bounded integer
values in these loops the old and new groupings yield the same numeric result;
this is source-structure evidence, not a claimed gameplay change.

The whole function remains nonexact: the 63,993-byte comparison first differs
at +42, with a 64,904-byte candidate section tail. The source remains unselected
and no exact credit is claimed.

## Shared ring angle expressions, 2026-11-04

The shared ring helpers also contained the earlier left-associated spelling.
Raw target sites include `0x005E4DA8` (action 302), `0x005E50F0` (304),
`0x005E9AE2` (525), `0x005EAC11` (541), `0x005EC5A5` (550) and
`0x005F07C0` (711): each separately adds 30.0 to the integer loop angle
before combining it with the converted random value. The six shared helper
expressions now use that grouping. These bounded integer inputs remain exactly
representable, so this is source-structure fidelity rather than a claimed
numeric or gameplay change.

The fresh ordinary VC8 object contains the corresponding integer-load,
add-constant, add-stack-value sequences. The entire root remains nonexact,
first mismatch +42 against its 63,993-byte callable, with a 64,952-byte
candidate section tail. This unselected candidate contributes no exact credit.

## Swap attack spawn-height grouping, 2026-11-04

For the extra rings in actions 541 and 543, native instructions at
`0x005EADD4..0x005EADEB` and `0x005EB8D3..0x005EB8EA` form
`sin(angle) * 200.0 + (height + 100.0)`. The previous shared source instead
formed `(sin(angle) * 200.0 + height) + 100.0`. The source now preserves the
native grouping, and the fresh object emits the corresponding height load,
constant addition and x87 stack addition (for example candidate offset
`0x8D0E..0x8D1E`). Floating-point addition is not generally associative; this
is a target-backed ordering correction, not a claim of full gameplay
verification.

The complete callable remains nonexact at +42. The candidate section tail is
64,952 bytes; no source selection or exact-byte credit is added.

## Action 214 flight effect facing, 2026-11-05

Native `0x5E3BC4..0x5E3C34` captures the unsigned effect-facing byte before sine and reloads signed facing after cosine for X. The earlier candidate read signed facing between the two lookups. Ordinary locals now preserve the two native read points; fresh VC8 captures direction at `0x1B15` and reloads signed facing at `0x1B4D`, after cosine. This establishes read order, not that the actual lookup changes facing or that ordinary gameplay differs. The 63993-byte root remains non-exact (candidate section tail 64952, first mismatch +42); no exact credit is claimed.

## Swap 820 ring facing lifetime, 2026-11-05

The two native swap-ring paths `0x5EADBB..0x5EAE34` and `0x5EB8BA..0x5EB933` capture the unsigned spawn-facing byte before sine and reload signed facing after cosine for X. The earlier shared candidate helper loaded signed facing between the lookups. An ordinary local now preserves the native read point while retaining the existing `sin*200 + (Y+100)` association; focused VC8 helper output reloads signed facing at `0x403` after cosine. This establishes read order, not that the actual lookup changes facing or that ordinary gameplay differs. The 63993-byte root remains non-exact (candidate section tail 64952, first mismatch +42); no exact credit is claimed.

## Ring 902 facing and peer read lifetimes, 2026-11-05

Native ring paths including `0x5F0E1A..0x5F0E9E` and `0x5F0F1F..0x5F0FA3` capture unsigned spawn facing before sine, read the peer pointer for Y after sine, then reload signed facing and the peer pointer for X after cosine. The old shared helper captured signed facing and the peer pointer before the lookups. Separate ordinary locals preserve the observed lifetimes; fresh VC8 helper output captures direction before sine, reads Y's peer at `0xE7` after sine, and reloads signed facing and X's peer at `0x11B..0x122` after cosine. The sine-times-500 plus peer Y plus 100 association remains unchanged. This establishes read order, not that the actual lookups change those fields or that ordinary gameplay differs. The 63993-byte root remains non-exact (candidate section tail 65096, first mismatch +42); no exact credit is claimed.

## Fan 801 facing lifetimes, 2026-11-05

The native fan spawn sites, including `0x5E74BD..0x5E753B` with X offset and `0x5E809B..0x5E80FE` without it, capture unsigned spawn facing before sine and separately reload signed facing after cosine. The former candidate's shared `emit801` helper captured signed facing before sine. Both real offset branches now use ordinary locals for the native read points; focused VC8 output shows the post-cosine signed reload in the helper and all 18 emitted root sites. The existing `(cos*150 + xoff)*facing + X` versus `cos*150*facing + X` distinction and the Y association are retained. This establishes read order, not that the actual lookup changes facing or that ordinary gameplay differs. The 63993-byte root remains non-exact (candidate section tail 65448, first mismatch +42); no exact credit is claimed.

## Signed counters in actions 562, 602 and 605, 2026-11-05

Native action 562 `0x5ED66F..0x5ED6AB` tests the 16-bit counter at `0x730` with signed `jle` and sign-extends it for the modulo. The previous unsigned read let a negative value enter and increment. Native action 602 `0x5EEF76..0x5EEFB3` and action 605 `0x5EFDED..0x5EFE22` compare counter `0x734` with 5 or 6 using signed `jge` and sign-extend the same value for the emitted angle. The previous unsigned reads skipped negative values and would calculate the wrong angle. All three source sites now use the signed short field. Focused VC8 compilation confirms signed threshold branches and sign extension; ordinary-play reachability of negative counters is not established. The full root remains nonexact and receives no exact credit.

## Actions 520 and 521 signed level gates, 2026-11-05

The native stream-815 paths at `0x5E975A..0x5E9772` and `0x5E9857..0x5E986F` compare the byte at `0x605` against 2 and 4 using signed `jl`. The earlier helper read that byte as unsigned, selecting a limit of 8 for values `0x80..0xFF` where the native path selects 5. The helper now uses a signed byte; its focused VC8 output emits signed comparisons at both expanded call sites. Negative-level reachability during ordinary play has not been established. The full root remains nonexact and gains no exact credit.

## Action 710 peer read lifetimes, 2026-11-05

The native 900 spawn path calls cosine and sine before loading the peer pointer for each coordinate (`0x5F05D0..0x5F05E4` and `0x5F064D..0x5F0663`). The previous compound expressions caused the VC8 candidate to load that pointer before the random and trigonometric calls. Separate ordinary double offset locals preserve the observed evaluation points: the focused candidate now emits each multiply, then the peer-pointer load, then the coordinate addition, without a double spill. The native check of the existing Y value before overwriting it is deliberately retained. This establishes read order, not a demonstrated ordinary-play difference. The full 63,993-byte root remains nonexact at +42 (candidate section tail 65,448); no exact-byte credit is claimed.

## Fan 801 facing argument width, 2026-11-05

All 18 native fan-801 spawn paths capture the facing with `movzx` and pass the complete zero-extended word before the trigonometric calls; for example, `0x5E74BD..0x5E74D2`. The preceding byte-sized direction locals preserved the read point but compiled into a one-byte stack write followed by a full-word reload, leaving the high bytes dependent on prior stack contents. The two real offset branches now snapshot facing into an unsigned integer. Focused VC8 output zero-extends the byte before sine at all 18 expanded sites and carries the full value to the spawn argument; the signed-facing reload for the X calculation remains separate. The downstream gameplay effect of the old upper bytes is not established. The 63,993-byte root remains nonexact at +42 (candidate section tail 65,368); no exact credit is claimed.

## Action 730 ring-902 facing argument, 2026-11-05

The five native ring-902 paths similarly zero-extend the direction before the sine lookup, at `0x5F0E1E`, `0x5F0F1F`, `0x5F102A`, `0x5F1131`, and `0x5F1234`. The previous byte local compiled to a one-byte stack write and a later full-word reload. An unsigned integer snapshot restores the observed full argument value at all five expanded sites while retaining the separately timed peer and signed-facing reads. Focused VC8 comparison confirms the zero-extended capture. No normal-play consequence is established, and the complete root remains nonexact; no exact credit is claimed.

## Action 730 ring-902 angle precision, 2026-11-05

The native ring paths retain `n * step + base` on the x87 stack for the packet angle while separately storing a float coordinate used by the trigonometric lookups. For example, `0x5F0FE3..0x5F1009` computes the coordinate from the unrounded sum and then adds jitter to that retained sum. The previous source rounded the shared angle to float before both uses. A double angle local now allows VC8 to retain the sum for the packet, with the coordinate still explicitly converted to float; focused output shows no intermediate float spill before the packet addition. The actual base and jitter come from bounded integer random results, while steps and the optional 22.5-degree offset are exactly representable, so no ordinary-play numerical difference is established. The 63,993-byte root remains nonexact: the frame changes and the first mismatch is now +8, with a 65,304-byte candidate section tail. No exact credit is claimed.

## Unsigned random conversion constants, 2026-11-05

The complete native action root uses the float `2^32` correction for unsigned random conversions, including the RNG(150) conversion at `0x5F0590..0x5F05A2`. Fresh pre-change VC8 emitted the double correction at 56 expanded sites because 28 source expressions converted unsigned results straight to double. Those expressions now convert through float before promotion, retaining the surrounding double arithmetic. In the root disassembly the native and new candidate each contain 82 float corrections and no double corrections, versus 26 float and 56 double before this change. The next x87 arithmetic/store-category census is unchanged apart from the correction type: the 56 changed paths introduce no extra early float-store category. This count is a routing and code-generation observation, not a per-site proof or whole-function match. All affected random ranges are bounded to small integers, so no ordinary-play numeric difference is established. The 63,993-byte root remains nonexact at +8 with a 65,304-byte candidate section tail; no exact credit is claimed.

## Action 214 unordered flight exit, 2026-11-09

For sequences 3/4 with facing other than 1, native `0x5E3D97..0x5E3DDE`
compares peer X with self X. `test ah,41h; jne` selects sequence 6 without
changing facing or horizontal velocity for less, equal or unordered results.
Only ordered peer X greater than self X reverses both values and selects
sequence 5. The source's `peer_x <= self_x` condition sent unordered values
into the reversal arm. It now states `!(peer_x > self_x)`. Ordinary-play
reachability of NaN coordinates has not been established.

Fresh pinned-VC8 before/after builds change exactly one byte in the complete
65,304-byte candidate payload: at root offset `0x1CE4`, `jp` becomes `je`
for the compiler's opposite-layout reversal branch. All 2,269 relocations and
the other bytes of all 240 non-debug sections are unchanged. The four x87
comparison outcomes now select the native sequence and reversal behavior.

The complete 63,993-byte callable and its switch payload remain nonexact against the
65,176-byte original extent, first difference +8. The new full candidate SHA-256 is
`4c4bf8d203af7047cb15a442d62954ee1e28f873cd839264a9fe525cb4a0e88e`.

## Checked motion fields, 2026-11-23

`AnimationSequenceObjectView` now exposes five checked floats at `+0xEC`,
`+0xF0`, `+0xF4`, `+0xF8` and `+0x100`. These are the current target's
position, velocity and vertical acceleration fields, also present in the
checked receiver for the exact Komachi initializer at `0x005F6700`. The root
snapshots, peer reads, surface transitions and motion initializers use the
members directly. This replaces 447 float offset accesses between
`KomachiActionState.cpp` and its inline helpers. Cases 0–10 also expose the
call order and conditional transitions on separate lines.

Headless builds of the old and new sources replay all 1,857 selected COFF
relocations. The complete 65,304-byte candidate and its switch topology
are identical, including the merged 209/212 entry. All 170 accepted functions
that depend on the shared header still compare exactly across 47 units.

Ending action 212 with `break` emits the same candidate. A scratch build
with explicit shared paths for crossing and continued flight restores both
dispatch entries. VC8 places the continued-flight body after 212 instead of
209, exchanging the 48- and 102-byte owner spans. The scratch section grows
to 65,356 bytes. Registering the leading card-expiration table at `0x005F1ADC`
sets the candidate instruction boundary before the switch data. Registering
the three match-identifier tables closes the remaining raw target edges.
The scratch owner audit now completes across 107 owners and reaches all
63,993 native callable bytes through seven dispatches.

Negating only 209's source condition reproduces the split candidate. Negating
both conditions merges the entries again. The native 209/212 continuation also
joins 221 at `0x005E40A0` after the gravity update. Sharing that suffix in
source leaves the two spans exchanged and grows the candidate's 221 span by
12 bytes.

The headless VC8 SP1 trace at `c2.dll:0x10B26CA8` reproduces the split
candidate's 65,356 bytes and all 1,860 relocations. Applying the
[recovered depth-first walk](YOUMU_FIGHTER_ACTION_INITIALIZATION_2026_10_25.md#vc8-block-ordering-2026-11-23)
to its raw graph reproduces all 3,571 entries in the compiler's postorder
list. The low switch (block 34) visits entry 212 (459) before entry 209
(382). Its non-crossing edge through 462 discovers the shared flight block
(386) before 209 is visited. That block still follows 209 in the physical
list at the breakpoint, but the new order puts it after 212. The emitted
209 branch enters the shared flight code with `JE` and 212 falls through.
The target uses `JNE` from 209 to the landing path and `JE` from 212 back
to the flight code inside 209.

Putting 212 before 209 in source reverses their emitted entry order, while
the flight block still follows 212. Both owner spans, the section size and
the relocation count stay the same as in the first split candidate.

## Shared high-jump landing and ring frame, 2026-11-23

The native crossing paths in 208–211 all enter the virtual call to
`set_action(10)` inside 212 at `0x005E3837`. A scratch version with all five
landing paths using the same source label keeps two 209/212 dispatch entries
and emits 65,356 bytes. VC8 still assigns the flight to 212 and the landing
to 209, leaving their 48- and 102-byte spans exchanged. Joining 221's
sequence check simultaneously leaves those spans exchanged and moves the
physical landing owner again. Duplicating the flight with a shared late
launch effect merges the 209/212 entries. These variants remain unselected.

In action 730, the native first ring for match mode 3 stores its coordinate
angle at `0x005F0DEF` while keeping the x87 value live. It then adds the
jitter and the 180-degree turn inside the loop. VC8 previously hoisted
`jitter + 180` into a QWORD local and grew the whole dispatcher frame from
`0x490` to `0x498`. Separate double updates for the packet angle restore
both additions to the loop and remove the QWORD spill. The packet still
rounds to float once, after the additions. The coordinate store remains
later than the original.

The selected 65,288-byte rebuild replays 1,857 relocations. The seven
dispatches, compact remap bytes and external relocation counts agree with
the preceding candidate. The first difference moves from `+8` to `+0x2A`
(`0x005E210A`). The native hoists `EBX = 8` before the card gate, then
derives `EDI = 2` with LEA. The current build loads EDI directly and defines
EBX after the deque call or on the bypass edge.

The card gate's 0–4 and 5–8 entries each compute the expiry effect's
height. In the native build the first jumps into the second's shared
effect call at `0x005E22BA`. Factoring the call through one source label
collapses all nine remap indices to one destination. Naming the rounded
height or reversing the face-test operands gives the selected bytes.
Spelling separate facing arms emits two immediate direction writes
instead of the native shared `NEG CL` and leaves the prologue difference.

## The card bound is live across the dispatcher

The native load at `0x005E210A` feeds the card bound and subsequent action
paths. Following the raw CFG through all seven tables, and stopping at
writes to EBX or its subregisters, reaches the frame tests in 322, 404,
415, 418 and 770, the counter test in 402, the byte stores in 510/511, and
the uses in 520/521 and 603. In the current build both the card-path load
and bypass-path load reach the common action switch. The build still uses
BX in 322 and 402, but uses immediate byte stores for 510/511. The latter
two stores follow the real landing helper in both builds.

On the pinned VC8 SP1 compiler, the two separate constant-load records
already exist at `c2.dll:0x10C0661B`, before the final pass that splices
Youmu's publication tail. The first appears after the deque call and
signed record load. The argument records at both sites carry value 8
into the same register class. The final listing places the two writes
at `+0x58` and `+0x228`. The traced section replays to the same
65,288 canonical bytes and 1,857 relocations as the ordinary build.

An explicit switch default, separate range guard, signed or unsigned
record local, and explicit forward exits to the countdown each compile
to the same complete candidate. Further comparison can focus on the
earlier materialization and register allocation of constants shared
across actions.

The card-expiration code and skill-state writes now use six checked
members in the local receiver view. The hit accumulator at `+0x178`
is also written by the native hit policy at `0x0046C6D0`. The selected
layout and clearer card switch replay to the same complete candidate.

Typing the entry guards and countdown as a group changes code in other
actions. In 400, 402, 404 and 406, seven native memory adds from
`+0x744` become an earlier load followed by a stack add. The probe
also adds a jump in 525 and grows by 16 bytes overall. Those entry
fields keep their existing spelling pending a narrower explanation.
