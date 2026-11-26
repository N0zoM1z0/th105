# Yuyuko action-state root 55D850

## Current typed checkpoint, 2026-11-26

Yuyuko `0x0055D850` now has a character-local receiver with checked member
offsets and a complete five-table comparison contract. It remains unselected
and nonexact. The evidence comes from the hash-attested original Japanese
TH105 1.06a PE, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`,
and serial VC8 SP1 `/O2 /GS- /GR /EHsc /MT` builds.

The callable `[0x0055D850,0x0056BD4B)` contains 58,619 bytes. Fresh raw traversal
reaches all 14,783 instructions, 124 RETs and 885 direct calls to 27 targets,
with no unresolved exits or unreached ranges. The complete payload ends at
`0x0056C168`: 59,672 bytes, 118 destination words, 576 index bytes and five
alignment bytes across three action switches and two difficulty switches.
Payload SHA-256:
`f8a241c5d1d735d0c660f406b87a4cb00545d31a0ca66b67b129f3afefe5afd9`.

### Observed source and ABI corrections

- The former sine/cosine declarations returned `double` although their target
  providers `0x00406360` / `0x004063D0` round their returns to binary32. They now
  return `float`, resolving the canonical comparator's unknown external target.
- The receiver replaces the raw `at<T>` accesses and shared animation-base
  dependency. Eight reviewed virtual slots and every named offset have compile
  checks. Effect direction is unsigned byte; spawn direction is signed byte.
  On-surface returns an integer and its callers explicitly consume AL.
- Native `0x0056B99B..0x0056B9B0` and `0x0056BB6A..0x0056BB7F` write separate
  16-bit fields: `76C=0`, `76A=1`, followed by `766=0`, `768=0` and `764=0`.
  The old candidate combined `76A`/`76C` into a dword store. Both halfwords are
  now represented and written separately.
- Direct spawn expressions preserve the outgoing direction argument before
  trig/RNG calls and the signed facing reread afterward. Mirrored orbit X keeps
  its pre-sine double snapshot. The native `0x4E8` frame is recovered.
- Negative integer offsets use float conversion before subtraction, recovering
  FISUB in 302/304/305, 562 and the negative petal offsets. The spell ring keeps
  its double angle and writes each rounded packet angle independently.
- Packet addresses place 651 immediately after 601 and 657 immediately after
  607. Moving the source cases into those positions restores their stack-home
  order and removes the two surplus surface/zero-motion calls in 657.
- Independent entry/frame guards, the repeated flight-release conditions and
  the post-switch advance follow the target control flow. Difficulty cases use
  the observed physical order 3/2/1/0. The original 725 fallthrough into 726,
  sine(n-6) ring geometry and two-cosine 731 coordinates remain present.

### Integer allocation and branch scopes, 2026-11-26

Native 725/726 clamp alpha through separate writes: subtract six when alpha is
at least six, otherwise write zero; add six when alpha is at most 249, otherwise
write 255. Replacing the local-alpha ternaries with these direct member
`if/else` branches restores both physical branch order and the high-switch
`BL=0xFF` definition. It also restores the root's EBP=90 / EBX=1 allocation and
removes all four previous direct-call count discrepancies. A late alpha source
shape can therefore change register allocation and physical tail merging across
this entire VC8 function.

The raw compiler trace explains the earlier allocation without requiring IDA:
C2 assigned the 90 interval to physical register 4 (EBX), then assigned a
372-reference one interval, with cost 188 and only register 6 available, to EBP.
The pinned C2 DLL hash is
`497d1ffe57f75db8b458167bdea475f3962829e139b355a2672a4ef51c716413`;
read-only hardware-breakpoint results are private in
`build/yuyuko-root-work-codex/color-log.json`. The source correction and complete
comparison, rather than the compiler trace alone, establish the improvement.

200/223 compare the incremented `word_730` member directly; the former short
snapshot introduced an extra MOVZX. 599 consumes the stored signed `word_734`
in its negative angle, recovering native MOVSX and store order. An uninitialized
function-local integer reused by the existing fan loops restores 404/406's
multiply operands and 657's FADD operands. It is initialized by every loop
before use. 408 needs independent timer/frame conditions, and 502/503/507/508
need separate crossed/return blocks for sequences zero and one. These source
scopes recover further native constant intervals and shared exits.

### Counted loops and declaration order

The 810 fan uses a count of six, five or four shots and computes each angle as
`base - n * 10`. VC8 strength-reduces that source to the native `add edi,10`
and scaled loop bound. Writing the already-reduced `n += 10` source instead
hoisted the integer-to-x87 scratch store above the level decision. The counted
source restores every physical 500/501/502/503 loop and its scratch stores.

820 and 900 initialize the sample index before declaring the angle induction
variable in the `for` statement. This restores 540/541's immediate-zero stack
initialization and 710's post-callback scratch stores. Declaring the angle first
had shared its zero with the sample index and moved those stores earlier.
These are reproducible source shapes, not uniquely recovered original spelling.

### Full comparison and remaining work

The fresh canonical build first differs at `+0x1B9` (`0x0055DA09`), in the relative
displacement of `ja 0x0056BBB6` at `0x0055DA07`. That default destination moves
with the remaining code-size discrepancy. The frame is `0x4E8`. The candidate
section contains 59,660 bytes, with switch data beginning at +58,608; the target
payload contains 59,672 bytes. The complete relocated candidate section SHA-256
is `4595106ff600ae8a0fe9e981d1dbb4bb3d207503490f1e561eba2359bbf997a2`.

The official instruction/edge diagnostic is 100/109 owners. All 885 direct calls
agree in count across all 27 targets, and every owner's floating instruction
sequence agrees. The remaining source-level differences are local one intervals:

- 502/503/507/508 load EBX=1 before their sequence-one crossed guard. The
  candidate compares against immediate one and omits the register definition.
- 512/513 load EDI=1 before their arc guard. The candidate retains three in EDI,
  uses immediate one in the arc/entry tests and differs in the later frame-three
  comparison and `word_730` store.
- 710/720's auxiliary table operands and the final owner's three alignment
  bytes depend on those six case layouts.

The first such definition is native `0x005649E6` (`+0x7196`). Review the split
constant intervals and their real source uses before changing local jumps or
alignment. No LTCG blocker has been established. The candidate remains unselected
and nonexact, with no exact credit.

Rejected controls include the ABI-compatible short selector and byte variant
views, helper expansion, do/while and negated-offset 810 forms, moving its common
callbacks into each branch, and sharing all loop indices. A short loop index
changes the induction code. A named double offset or caller-owned arc packet
can reverse 657's already-correct FADD operands. Alternate 402/815/820 counted
forms, scalar arc increment, facing equality casts, entry helpers and several
air timer scopes do not fix the six one intervals. Grouping the physically
shared 209/212/221 or 210/222 labels disturbs 607/720 without fixing them. The
last single-index 900 trial changed emitted bytes without establishing an
improvement and was reverted. Current source and focused results are retained; obsolete trial
objects, source copies and duplicate reports were removed.

Work is paused at the user's explicit request after this checkpoint. Resume
with the six one intervals above when instructed.

Reproduce serially:

```bash
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit exact-first-yuyuko-action-state --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py --unit exact-first-yuyuko-action-state yuyuko-vslot28 build/match-units/ExactFirst_YuyukoActionState.obj --json
```

Private current results are `build/yuyuko-root-work-codex/canonical.json` and
`owners.json`. The source/header have no accepted consumers. Existing exact
receipts are preserved; no whole-corpus comparison was run. The following notes
record earlier candidate work and its failed attempts.

## Physical-owner refinement

The low-case source now follows the observed physical owner order: the truly
shared 209/212/221 and 210/222 groups occur after 220;224/226 are no longer placed
next to 201/202 simply because their high-level logic is similar. Flight 214 is
between 211 and 215. This reduces the 214 span discrepancy from 340 to 37 bytes;
the comparison remains nonexact. Mirrored spell arguments retain the captured
double X but evaluate the outgoing Y/X expressions at the spawn call, consistent
with native packet/argument setup. An explicit idle 0/2 shared-label trial did
not recover native physical placement and was not retained.

Raw payload dataflow resolves all 100 native and candidate homes. Their size
pattern agrees (including four-float packets); every candidate home is 8 bytes
higher. Frames are 1256/1264 bytes. Native/candidate epilogues 124/126 and virtual
sites 180/178 differ. All 49 crossed and 8 on-surface consumers test AL in both.
These are whole-root diagnostics, not independent semantic acceptance.

The suspected airborne 812 unordered-predicate discrepancy was checked against
565851..565862 and 5659C3..5659D4: both predicates reject unordered values,
consistent with ordered less-than. No speculative NaN rewrite was made.
Remaining 710 virtual-site discrepancy is physical timeout-tail sharing, not an
observed extra dynamic call; native difficulties0/1 share the 56AC01 tail.

## Captured coordinate and aim-argument refinement

Action 726 captures the pre-RNG X field in a double local. Native 56B648 loads
the binary 32 field and 56B653 directly stores QWORD across RNG, then 56B67B
uses that QWORD in the subtraction. The former float local generated an
extra DWORD store/reload before its QWORD capture. The isolated capturex
trial removes that unsupported round trip, emitting 59420 bytes; the frame
remains 4F0. This does not narrow any arithmetic or assume RNG is pure.

The seven aim_fan sites and action 562 atan call now retain rounded DX while
computing DY in the first argument. Native 561858,561919,561CBD,561D7E,
562553,562ADF,562BBB and 5672D9 place DX in outgoing[esp+4] before loading
peer Y. No intervening helper or object write exists in these calculations.
All seven aim_fan call-preparation windows (32 bytes before call) match native
verbatim after this change. The eighth has the recovered instruction order
but still differs in scratch offsets. These bounded windows are diagnostics,
not whole-function acceptance or additional exact-byte credit.

The combined public replay is 59456/full59672, first+8, frame 4F0 versus 4E8,
SHA 256fae3443cfa58a7c2a829bfbab59e723ecfa12172e8a23914e37a7b610749988f. Payload
dataflow still resolves 100 homes, all+8, with no unknown payload pointers. One
skipped six-byte LEA EBX,[EBX] at candidate 56A7EA is compiler alignment, not
executable source or a masked acceptance range. All bytes remain in the canonical
audit. The extra scalar group and ring-operation scheduling remain unresolved.

## Action 720 surface predicate

Native 56B3B9..56B3CA captures Y directly in QWORD across surface(). The local
is now double, replacing the earlier DWORD comparison home. More importantly,
56B3D0 tests AH bit 0 alone: the gravity path at 56B3E5 is taken when surface is
less than Y **or unordered**. Action 700 is selected only for ordered surface>=Y.
The former source `if(surface<y) gravity; else action700;` incorrectly selected
700 on unordered input. The source now states the ordered >= branch first,
which reproduces TEST AH,1/JNE and both native continuation bodies. No finite-
only domain assumption, invented NaN handling, or defensive behavior is added.

The public full payload remains 59456/full59672, frame 4F0 and first+8, SHA256
893e55b4e6e1976682b96b24c1b5245becea1c35b6f0c40b5299741ddaff5323. The strict
positional difference count is 56540; there is still no exact acceptance.

## Arc and spell height grouping, 2026-11-04

Native action 510/511/512/513 arc sites at `0x00565526`, `0x005656CE`,
`0x005658F5` and `0x00565A67` add 120.0 to fighter height before combining
it with the sine offset. Action 731 at `0x0056B837..0x0056B84F` similarly
adds 100.0 to height before the cosine offset. The two corresponding source
expressions now preserve the native order. A fresh VC8 object contains the
same height/add/add-stack pattern. This can affect floating-point rounding;
it does not establish complete gameplay equivalence.

The full 58,619-byte callable remains nonexact from +8, with a 59,456-byte
candidate section tail. It is unselected and adds no exact credit.

## Action 562 ordered landing gate, 2026-11-04

The native gate at `0x005671C3..0x005671E2` compares surface against next Y,
then zero against vertical speed. Its status-word tests skip the landing path
for unordered comparisons as well as for surface below next Y, nonnegative
speed or sequence index at least five. The previous negated `<` / `>=`
expression accepted unordered values. The source now states the observed
ordered `surface >= next_y`, `speed < 0`, `sequence < 5` conditions directly,
preserving the native check order. Fresh VC8 output emits the same x87 status
masks (`AH & 1`, then `AH & 0x41`) and skip branches at the corresponding
gate. This is a bounded instruction/control-flow observation; it does not
claim complete gameplay or unmasked-exception equivalence.

The full 58,619-byte callable remains nonexact from +8; the candidate section
tail is 59,456 bytes. No exact-byte credit is added.

## Circle 801 facing lifetime, 2026-11-05

Native `0x56355F..0x5635D2` captures unsigned spawn facing before sine, then reloads signed facing after cosine for X. The former shared candidate helper captured signed facing before sine. Ordinary locals now preserve the two native read points; focused VC8 helper output captures direction at `0xB` and reloads signed facing at `0x40` after cosine. The native distinction between sine of `p[0]` and cosine of `-p[0]` remains intact. This establishes read order, not that the actual lookup changes facing or that ordinary gameplay differs. The 58619-byte root remains non-exact (candidate section tail 59524, first mismatch +8); no exact credit is claimed.

## Arc 812 facing lifetime, 2026-11-05

Native `0x565506..0x565594` captures the unsigned spawn-facing byte before the position sine lookup, then reloads signed facing after cosine for X. The shared candidate arc helper formerly captured both before sine. Ordinary locals now preserve the native read points; fresh VC8 helper output reloads signed facing at `0xAB` after cosine. The `sin*40 + (Y+120)` association remains intact. The X-expression association described at this checkpoint was corrected by the 2026-11-05 note below. This establishes read order, not that the actual lookup changes facing or that ordinary gameplay differs. The 58619-byte root remains non-exact (candidate section tail 59556, first mismatch +8); no exact credit is claimed.

## Orbit spell facing lifetimes, 2026-11-05

Native normal and reversed orbit spawns, including `0x5686B4..0x568726` and `0x56874C..0x5687C8`, capture unsigned spawn direction before sine and reload signed facing after cosine. Reversed paths also capture X before sine and subtract the cosine offset from that snapshot. The earlier shared candidate helper captured signed facing before both lookups. Ordinary locals now preserve the native read points in both branches; fresh VC8 output shows the signed post-cosine reload at all nine root sites, and retains the reversed branch's pre-sine X snapshot. The 58619-byte root remains non-exact (candidate section tail 59620, first mismatch +17); no exact credit or ordinary-gameplay difference is claimed.

### Ring 820 and difficulty 900 facing reads (2026-11-05)

The pinned target's ring-820 and difficulty-900 emitters capture the unsigned direction before the sine call and reload signed facing after cosine (for example, `0x566680..0x566719` and `0x56A8B5..0x56A94F`). The former candidate captured both interpretations before sine. The source now sequences the reads separately, preserving the target's `(sin * 300) + (Y + 170)` and `(cos * 300 + 50) * facing + X` associations. The rebuilt dispatcher shows the late signed load at both ring-820 sites and all four difficulty-900 sites. The lookup helpers do not ordinarily mutate the receiver, so this is a source and instruction-order fidelity correction rather than a demonstrated normal-play difference.

The full dispatcher remains nonmatching: target 58,619 bytes; candidate section tail 59,652 bytes, first difference at offset 17. This change does not claim exact-match credit.

Action 731's object-922 spawn uses cosine for both coordinates. Target `0x56B822..0x56B89E` captures unsigned direction before the Y cosine and reloads signed facing after the X cosine. The candidate now preserves those separate reads, both angle/radius reloads, and `cosine * radius + (Y + 100)` grouping. Its rebuilt site shows the target read ordering. This does not assert an ordinary-play difference from the nonmutating lookup. The dispatcher remains nonexact, with target 58,619 bytes, candidate section tail 59,676 bytes and first difference +17; no exact credit is added.

## Object 812 arc X association, 2026-11-05

Four native arc paths (`0x565551..0x56557E`, `0x5656F9..0x565726`,
`0x565920..0x56594B`, and `0x565A92..0x565ABD`) calculate
`cosine*100 + (state_740*5 - 85)` before multiplying by facing and adding X.
The earlier source grouped the first addition before subtracting 85; the
2026-10-28 description above did not distinguish the two associations. The
source now groups the state-derived offset as the native instructions do.
VC8 calculates the two independent products in a different order but keeps
the same subtraction/addition association. No normal-play numeric difference
is established.

The 58619-byte root remains nonexact at +17, with a 59676-byte candidate section
tail. This local fix does not add exact-function or byte credit.

## Action 720 ordered wave limit, 2026-11-09

The four native difficulty paths compare the float counter at +0x73C with
100.0 at `0x56AF34`, `0x56B022`, `0x56B10F` and `0x56B1FD`. Each uses
`test ah,41h; jp` to skip the wave for an above-limit or unordered result.
Only ordered counter <=100 reaches wave-handle 10, the two object-901
requests and the counter increment. The shared source helper previously
returned for `counter > 100` only, allowing unordered values through. Its
guard now rejects `!(counter <= 100)`. NaN reachability during ordinary play
has not been established.

Fresh pinned-VC8 comparisons cover the complete 58,619-byte callable and
59,672-byte original switch-bearing extent. The 59,676-byte candidate changes
only four `je` opcodes to `jp`, at root offsets `0xD70D`, `0xD7FA`, `0xD8E7`
and `0xD9D3`. The separately emitted source helper has the same one-opcode
change at +0x57. All other bytes across 181 non-debug sections and all 2,125
relocations remain unchanged. The four comparison outcomes are checked
against the original guards.

The full root remains nonexact at +17; candidate SHA-256 is
`45ce2e0fe7e3da0bfc754cfb19b189bd7438a21c48f93c4392a4c7958dceedd5`.
