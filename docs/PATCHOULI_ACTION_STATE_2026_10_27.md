# Patchouli action-state 0x0050F200

Complete unselected C++ candidate for 109 native action labels. All three
sparse regions plus direct 300/560 are present. Compilation and a full strict
comparison are available; no implementation or exact ledger credit is added.

## Exact-target observations

The JP1.06a target and Factory native IDA metadata, entry, mapped entry bytes
and inventory were attested at 16:40UTC on October 27. Direct IDA still lacks
mcp 1.26.0/uv. Full decompilation was read as a provisional guide, not copied
into source or trusted over raw instructions.

Native callable 50F200..51C6B4 exclusive is 54452 bytes, SHA-256:
41430c00c554e7dc169692c56b41fd43f5ef1204700cb092bab6420f327ed944.
All 14068 instructions decode;14067 are reachable. The sole unreachable
instruction is seven-byte compiler alignment at 50F8A9..50F8B0.
There are 133 RETs,807 direct call sites and 29 direct targets. All four
indirect jumps resolve: a pre-dispatch difficulty switch plus three sparse
action tables with 32/43/32 physical destinations. No indirect exit is unresolved.

Full code/table payload 55610 bytes ends 51CB3A, SHA-256:
d4d73f175e4f8b37667f04472df8c5db8cbec0ca20414d4107df08a007779043.
Alignment after that endpoint is not included.

## Source decisions and evidence limits

- Uses the accepted virtual slot order and a pointer-only receiver extension,
  not a recovered complete allocation or an instantiated Fighter.
- Buff7A4 reads owner 168 and peer170 health, not self health. Skill 606 is
  signed-byte arithmetic. Action 710 emits its orbit before the hitstop guard.
- All 40 native 5F9310 call sites test AL; the accepted int callee declaration is
  retained and caller values explicitly narrow. All 47 unsigned-conversion
  bias operands are float 2^32; candidate count/width agrees.
- Effects carry unsigned direction bytes while coordinate multiplication is
  signed. Ring 820's layer carries the low byte of word 730, including 255 for-1;
  it is not silently replaced by an int-1 argument.
- Trig and square helpers consume actual ST0 results, not decompiler aliases.
  Action 599 sign-extends DX at 519FE6 before subtracting from-20. The RNG has
  no phantom decompiler arguments.
- Action 214's alleged extra v571 virtual argument is absent in raw code.
  Release frame restoration uses the real slot 1C and preserves frame 730.
- Ground/air fan emissions keep distinct low/high payloads. Air fan seq0 and
  seq1 checks are independent across callbacks. Landing action/select/surface/
  zero-motion order is retained for each family rather than normalized.
- Action 603 request 853 adds 20 in world X, unlike its direction-scaled effect.
  Its request precedes sequence-window/resource calls. Action 602 has positive
  sine and negative cosine arguments. Actions 797/798 retain different landing
  event order and advance to 0 versus 700.
- Native 561 and 798 unordered comparisons were checked directly; unordered
  values skip emission/landing. Skill 581 has no defined cap for levels>4,
  unlike 580's default 4. That domain is still unproved; no fallback is invented.

Every action label has a complete candidate path, but this does not establish
all values, callback aliasing, NaN/overflow behavior or original TU ownership.
The source remains unselected while these semantics and physical ownership
are reviewed. No assembly, target arrays, fake returns, padding locals or
volatile register controls are used.

## First complete comparison

Candidate full 54342 versus native 55610; first mismatch+8 is frame 468 versus 460.
Full candidate SHA-256:
f21ffde47c144cf7fac7a4dc1e82d5ca06b63d37bae65bcfea7d767a69a4c783.
The full comparison has 52767 unequal/missing/extra positional bytes. This
number is not a semantic-completion percentage.

Candidate sparse groups 31/43/32 fold target-distinct210/222; no native group
splits. The diagnostic 31 allowance never relaxes target 32 or exact acceptance.
Native 209/212/221 and 585/586 genuinely share their respective target entries.

Per-action reachable-call counts differ at 214/409/500/501/502/503, where
source compilation folds virtual or request sites. Arithmetic-operation counts
differ at 214/500/501/502/503. These diagnostics identify remaining questions,
not proof that the other actions are equivalent. Global helper-count changes
also reflect common tails and the low-owner merge.

## Focused reproduction

taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-patchouli-action-state --compare --json
    scripts/repo-python scripts/map-giant-action-switches.py patchouli-vslot28 --json
    scripts/repo-python scripts/compare-giant-action-switches.py patchouli-vslot28 build/match-units/ExactFirst_PatchouliActionState.obj --json

The full audit replays every COFF relocation with the canonical comparator and
rechecks native CFG closure. Expected mismatch exits must not become acceptance.
Seventeen new literal bindings are supported by native operand addresses and COFF
values; all prior bindings and accepted consumer sources are unchanged. Only the new
unit is compiled.

## Branch and payload refinement

The next focused replay restores separate entry transitions for actions 409,
502 and 503. Native 5157AF/512FE7, 517151/51348B and 5174A1/512FE7
are distinct physical call sites, not one combined condition. Action 214 now
retains the shared turn-and-restore path at 5114CE and the four independently
returning sequence-8 restore paths at 5116A6, 5116C6, 511713 and 511735.
Its reachable virtual-call count is now 27, matching the native diagnostic;
its FCHS count also agrees. Neither count establishes byte equivalence.

Surface rings in actions 540/541/797/798 now spill the complete sine-derived
vertical offset (sine * 75 * 0.25) as a double before querying the surface,
not the unscaled sine result. Native 5180B2..5180D8 establishes this rounding
boundary. The emission argument order captures layer/direction before the
surface query and consumes the cosine afterward. The ground-810 initializer
ordering trial was byte-neutral and was not retained.

Prior surface-ring candidate: 54466 bytes versus 55610 target bytes, first mismatch
still +8 (frame 0x468 versus 0x460). SHA-256:
87055307b1883af792f0bc7cec13481185554ce128ec4728b05ae7f66844d921.
The strict full comparison reports 52911 unequal/missing/extra positional
bytes. Source remains unselected and no exact credit is added.

The private payload trace resolves all spawn pointers and finds 91 distinct
payload homes in both native and candidate code. Their spacing agrees,
including the one 16-byte step, but all candidate homes are displaced by
8 bytes (first home 44 versus 36). This isolates the residual frame question
to scratch/lifetime allocation rather than a missing payload. Native/candidate
physical virtual-call counts are 172/164 and epilogues 133/126; per-action
reachable-call differences now remain only at 500/501 (three native spawn
sites versus two compiled sites). Arithmetic census also differs at 502/503.
These are diagnostics, not acceptance or a proof of complete semantics.

The preceding focused receipts use the surface-ring prefix under the artifact
folder. No compiler flag, dependency ABI, existing relocation or accepted
consumer changed. Broader rebuilding is not warranted by this source edit.

## Argument lifetimes and native branch ownership, October 28

The current complete unselected candidate emits 55026/full55610 bytes, first+8 (468
frame versus 460), SHA256
0c76d2ef636a0ee3f83ad324a3209398f302deb286552cc56cb67a3114f96b54. The unmasked audit
reports 52741 unequal/missing positions, not a semantic percentage. Public replay
exactly reproduces the private ownerorder payload. No exact/source-selection ledger
changes.

- Nineteen atan sites retain rounded DX and evaluate DY in the outgoing
  argument. Native 513C82 through 51BC91 place DX before loading peer Y.
  All nineteen now have that instruction order; eight preceding 32-byte
  windows match verbatim, while other scratch offsets still differ.
  These bounded windows are not function acceptance.
- rising 820 captures current Y in QWORD before surface():51800F/518018 and
  51830E/518317 directly spill/subtract the native binary 64 temporary.
  The double local removes the prior unsupported DWORD round trip.
- Native 502 upgraded path 5171CA..51722F and ordinary path 517231..51728E
  each prepare their own complete request arguments before shared call 51729C.
  Source now keeps each packet and request inside its branch, rather than
  merging packet pointers and computing coordinates only afterward. The
  separate sequence 1 request remains unchanged. The 502/503 physical span
  residuals fall from 79/113 to 2/2 bytes, with two spawn sites still present.
- Native 500 request 516B31 and 516BDC each prepares effect 128 immediately
  afterward; the effect-call tail is shared at 516C20. A small source emission
  helper keeps each packet/request/effect group within the corresponding
  skill-level branch. The 501 peer independently has the same shape.
  Their three spawn sites and arithmetic-site counts are recovered; their
  physical spans are now one byte longer than native, not accepted exact.
- Flight 214 now appears between 211 and 215, following native physical owner
  order rather than after 226. Its physical span discrepancy drops from 237
  to 31 bytes. This changes placement, not gameplay condition order.

The whole-root per-action direct/virtual-call and arithmetic-operation counts
now agree (ownerorder-action-calls.json and ownerorder-action-fp-ops.json are
empty diagnostic deltas). Global physical counts still differ because of
sharing: native/candidate virtual sites 172/165, epilogues 133/127, crossed
consumers 40/39 and on-surface8/7. All observed bool consumers test AL.
Payload dataflow resolves 91 homes with no unknown pointers; candidate homes
remain uniformly+8. The residual frame, physical sharing, register allocation
and complete semantics remain open. No compiler flags, ABI contracts, forced
registers, padding, target bytes or unrelated accepted units were changed.

## Orbit spawn-height grouping, 2026-11-04

The original pre-dispatch action-710 orbit sites include `0x0050F670` and
`0x0050F757`, and action-602 orbit sites include `0x0051A97A`, `0x0051AA0B`
and `0x0051AA9C`. These x87 sequences first add 100.0 to the fighter height,
then combine that value with the sine offset. The action-602 loop at
`0x0051AB3F..0x0051AB52` preserves the same grouping using a shared 100.0
stack value. The two shared source expressions now reflect that order; the
fresh VC8 object contains corresponding height/add/add-stack sequences.
This can matter for floating-point rounding and is not a full gameplay proof.

The complete callable remains nonexact from +8: its 54,452-byte native body
and 55,042-byte candidate section tail differ. This source remains unselected
and adds no exact credit.

### Direction reads in orbit emitters (2026-11-05)

Target ring-820 ground and orbit-825/852/900 paths read the unsigned direction before sine, and reload signed facing after cosine; representative target ranges are `0x5127AD..0x512838`, `0x51890E..0x518989`, `0x51A963..0x51A9D1`, and `0x50F651..0x50F6C9`. The candidate previously cached the signed value before sine. The source now sequences the two reads, preserving each path's original coordinate associations, the ring layer read, and its separate angle reloads. Rebuilt dispatcher sites show the late signed read for three ground-ring sites and four sites each for the three orbit families. The trig helpers do not ordinarily mutate the receiver, so this is a reconstruction-fidelity adjustment, not a demonstrated ordinary-play difference.

Strict root comparison remains nonmatching: target 54,452 bytes, candidate section tail 55,602 bytes, first difference at offset 139. No exact-match credit is claimed.

Actions 580 and 581's object-830 shots have the same direction-read ordering (`0x519A5E..0x519AEA`, `0x519C5D..0x519CE9`). They now capture direction before sine and reload signed facing after cosine, while re-reading the angle field for each call and preserving their distinct 200/450 horizontal offsets. Both rebuilt sites show the corresponding late read. The whole dispatcher remains nonmatching (candidate section tail 55,646, target 54,452, first difference +139); this is not exact credit or a demonstrated ordinary-play change.


## Leading difficulty table, 2026-11-26

The action-710 difficulty dispatch at `0x0050F4FC` owns the four DWORDs at
`[0x0051C6B4,0x0051C6C4)`, immediately before the first sparse action table.
Raw destinations are `0x0050F58E`, `0x0050F574`, `0x0050F55A` and `0x0050F503`.
The candidate mapper previously counted those sixteen metadata bytes as code,
which made the owner instruction decoder enter the first table.

The mapper now includes reviewed auxiliary tables that directly precede the
sparse tables in its metadata boundary. Each candidate word must have a local
DIR32 relocation to code before the table; missing/external relocations,
metadata destinations and gaps are rejected. Four focused tests and a real
Patchouli COFF mapping pass. Existing Tenshi, Alice, Marisa and Sakuya owner
comparisons remain 107/107, 104/104, 125/125 and 106/106 respectively.

The public sine/cosine declarations now return float, agreeing with the
existing relocation contract and the independently recovered lookup providers.
A fresh complete unit build now reaches byte comparison instead of failing
external-call replay. It remains nonexact: the first difference is at `+0x2F`
and the candidate section contains 55,622 bytes. Its frame is the native `0x460`;
native 210/222 still share one candidate entry. The report is
`build/patchouli-root-work-codex/public-float-contract.json`.

Private source trials also include a 65-member receiver with checked offsets.
Control flow, outgoing direction views and argument lifetimes remain under
review; no source selection or exact credit has been added.

## Typed receiver and ring argument flow, 2026-11-26

The current public candidate uses ordinary typed members with 65 checked offsets
and the eight observed virtual prefix slots. Direction arguments use the
low-byte views supported by the call sites; on-surface keeps its int return and
consumers explicitly test the low byte. These declarations describe this caller;
the complete original class and source-level parameter types remain unknown.

Ring 820 writes its layer member inside each `if/else` branch. A ternary
assignment instead selected an integer temporary before a common member store.
The separate assignments reproduce the target stores, including the native
nonvolatile register holding one. Surface-ring emission also evaluates facing
and layer directly in the outgoing arguments, preserving the double vertical
offset across the surface query. Cached direction/layer locals had changed
physical cleanup sharing between 540 and 541. The current complete code now has
the target surface-query and zero-motion call counts.

The unit now specifies the entire 55,610-byte envelope: the leading difficulty
table, three sparse tables, all 111 destination words, 711 index bytes and three
alignment bytes. The ordinary strict build still fails at code offset +8:
frame 0x468 versus 0x460. Its section is 55,174 bytes. Native 210/222 still merge
in the candidate; four direct-call targets are each short by one. The configured
payload contract runs after code equality and has not passed. Reproduce with the
unit command above; current private comparison is
`build/patchouli-root-work-codex/public-typed-ring.json`. Source selection and
exact ledgers remain unchanged.

## Native frame and flight ownership, 2026-11-26

Direct 830 request arguments recover the native 0x460 frame without changing
compiler flags or the direction parameter views. The prior 580/581 source
spilled a direction byte across sine and cosine. Native 519A5E reads the
unsigned direction for the outgoing argument before sine, then 519ABB reloads
signed facing after cosine.
Writing the complete coordinate expressions in `spawn(...)` removes those
spills. Direct surface-query arguments similarly remove the extra float
store/reload pairs in 520/521.

Flight 214 now reads input and sequence members directly. Cached direction
products and a short sequence local had changed computation placement and
introduced an extra zero extension. The ordinary input decision tree, default
weather branch first, self-X as the comparison's left operand, and callbacks
inside each turn/no-turn branch recover native sharing. Sequence 3 keeps its
callback/frame restoration within those branches. The candidate's 2,211-byte
owner differs from the 2,213-byte target only by the missing entry x87 pop at
510F3E in the instruction/edge diagnostic. The whole-root comparison remains
the acceptance gate.

Ground fans process sequence zero first and test the incremented counter member
directly. Small integer coordinate offsets use float conversion where the
native code uses `fiadd` or `fisub`. The reviewed integer bounds and branch
order also recover the local shapes in 304, 321, 520/521 and 585.

The fresh public unit report is
`build/patchouli-root-work-codex/public-argument-flight.json`: first mismatch
+0x9B, frame 0x460, candidate code 53,876 bytes and section 55,030 bytes. Native
210/222 still merge, with four direct-call targets each short by one. The
prefix still discards its x87 zero instead of carrying it into the switch;
other owner differences also remain. No source-selection or exact ledger
changed, and the payload contract has not passed.

## Timer scopes, counters and skill limits, 2026-11-26

Native 308, 401 and 406 load the frame timer into AX and test it separately
before their charge and firing frame checks. An outer timer guard instead
caused VC8 to cache the frame index. Keeping the sequence guard outside and
the timer test on each frame condition restores those reads and 401/406's
EDI value of five. Air fans and paired 801 emissions similarly need the
incremented counter member in each test. Paired emissions process sequence
zero before sequence one.

The burst loops in 407/409 initialize their float induction variable before
publishing `field_180 = 1` within each sequence branch. Moving the publication
out of the branches had moved it ahead of the loop temporary's store/reload.
Native 560/561 assign their limit through four independent level checks, in
the order `<= 3`, `<= 2`, `<= 0`, `>= 4`. Those tests cover every signed byte
value. The subsequent float comparison is `field_744 <= limit`; the former
double promotion reversed its x87 operands. These changes leave only the
missing entry pop in 561's local instruction/edge diagnostic.

Float conversion of the small integer offset also recovers the native `fisub`
in manual effects 301/302 and spell flashes 600/604/605. The `>= 1` sequence
bound in 225 restores EBX reuse. In 720/730, the sequence-one exit condition
belongs inside the sequence-one-or-two branch.

The full public build remains nonexact at +0x9B, with native frame 0x460,
53,912 code bytes and a 55,066-byte section. Its report is
`build/patchouli-root-work-codex/public-local-owner-repairs.json`; the public
object replays identically to private `local_owner_repairs`. The unresolved
210/222 merge, x87 zero lifetime and other local differences remain. This
checkpoint changes no source-selection or exact ledger entries.

## Facing operands and repeated frame checks, 2026-11-26

The prefix facing tests need the peer coordinate as their left source operand:
`peer.x > x` and `peer.x < x`. In the ground-facing helper, the self coordinate
instead goes on the left, with the peer explicitly promoted to double. These
ordinary comparison spellings recover the target's `fld` order and status-word
tests at 50F2F3..50F32E and in actions 197–199. Removing promotion alone had
been byte-neutral; reversing which coordinate appears first is material.

Actions 197/198 also need separate complete timer/frame guards around facing
and velocity reset. This recovers `EDI = 6` and immediate-zero timer tests.
Their former outer timer guard prevented that constant reuse. The private
`facing_timer_repairs` instruction/edge diagnostic now differs in 197, 198 and
199 only by each missing two-byte entry x87 pop. The complete root remains
nonexact, so these local shapes confer no exact credit.

The calibrated compiler trace identifies an earlier zero-cost register
interval in the `f04698c5` source, before x87 stack mapping. The final section
of [VC8 source patterns](VC8_SOURCE_SHAPE_PATTERNS.md#pinned-c2-x87-liveness-investigation-2026-11-26)
records the active general allocator and the exact Tenshi control. The remaining
source cause, the 210/222 merge and the complete switch comparison are open.
The fresh public build has 53,928 code bytes and a 55,082-byte section; its
first mismatch remains +0x9B. Current strict evidence is
`build/patchouli-root-work-codex/public-facing-timer-repairs.json`.

## Canonical exact match, 2026-11-26

`exact-first-patchouli-action-state` is canonically exact under VC8 SP1
`/O2 /GS- /GR /EHsc /MT`:

- All 54,452 physical code bytes (`0x0050F200..0x0051C6B4`, SHA-256
  `41430c00c554e7dc169692c56b41fd43f5ef1204700cb092bab6420f327ed944`) and the
  complete 55,610-byte switch payload (`0x0050F200..0x0051CB3A`, SHA-256
  `d4d73f175e4f8b37667f04472df8c5db8cbec0ca20414d4107df08a007779043`) match
  with zero byte differences.
- All 1,651 COFF relocations agree: 807 REL32 direct calls across 29 targets
  and 844 DIR32 fields. Four switch tables contain 111 destination words, 711
  index bytes and 3 alignment bytes.
- The official owner audit passes 106/106 (entry included). Raw CFG reaches
  14,067 instructions / 54,445 authored bytes; the seven unreachable loop
  alignment bytes at `0x0050F8A9..0x0050F8AF` are compared and excluded from
  authored progress.

Three source-shape recoveries closed the remaining differences:

1. **Carried x87 zero in `201`/`224`**: Separating the two
   `if (sequence_index_13e == 2)` guards (instead of nesting the velocity
   update inside the `landing()` guard) lets the prefix `0.0f` live range flow
   into both cases. Each adds one `Enterload` (`-2`) and two uses (`+4`),
   raising the general-allocator `Color` interval spill cost from `0` to `+4`
   so VC8 keeps `0.0f` in `st(0)` across the switch.
2. **Distinct `210`/`222` owners**: Writing `case 209:`, `case 212:` and
   `case 221:` as separate cases (matching the other fighters) lets VC8's
   `FgDoLateFlowOpts` (capped at 17 iterations) merge `209`/`212`/`221`
   automatically while leaving `210` and `222` distinct at their native
   255-byte spans (`0x510D4A` and `0x5119C2`).
3. **Local branch/operand shapes**: Reversing branch polarity in `10`, `200`,
   `500..503` (`byte_604 >= 3`), and `721` (`x_ec < 640.0f`, `x_ec > field_74c`),
   using `< 1` in `414`/`567`/`568`, unsigned `> 0` on `field_6bc`/`6c0`/`6c4`
   in `545`/`546`, float `field_744 <= limit` in `580`/`581`, direct
   `(field_6c8 == 0 && word_736 > 10) || word_482 <= 0` in `214`, and separate
   `entry(...)` guards in `214` and `415` recovered all remaining local diffs.

Reproduce with:

```bash
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit exact-first-patchouli-action-state --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py --unit exact-first-patchouli-action-state patchouli-vslot28 build/match-units/ExactFirst_PatchouliActionState.obj --json
```

Private reports: `build/patchouli-root-work-codex/{canonical,owners}.json`.
Original full class layout, TU ownership and several field meanings remain
unknown.
