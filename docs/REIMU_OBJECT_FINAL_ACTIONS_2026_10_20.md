# ReimuObject906/907/908/951/999 source evidence

This continues [903/904/905](REIMU_OBJECT_903_905_2026_10_20.md) inside authored
update root496540. The only target is original Japanese1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Fresh raw closure retains46128 owned bytes,10670 instructions,22 switches,
404 direct CALLs to25 targets and68 RETs. Local windows below are evidence
ranges inside that root, including branches to shared tails; they are not
standalone compiler boundaries.

| Action | Local start | Exclusive end | Owned bytes | Instructions |
| --- | --- | --- | ---: | ---: |
|906|49F275|49FB74|2303|519|
|907|49FB74|4A051D|2470|575|
|908|4A051D|4A13EF|3794|867|
|951|4A13EF|4A1612|547|147|
|999|4A1759|4A195B|514|120|

These9628 owned bytes contain2228 instructions.907 excludes the three alignment
bytes at4A00ED..4A00F0. SHA256 of each full local extent, including that gap:

| Action | SHA256 |
| --- | --- |
|906|`580c79e32de01ed31bc2a936777af1724575ee2eefe037ad85264a698860384a`|
|907|`018c5b3ac6a94a4eb5685e8a1fe9995ad6ea818b7853d2094a5aaf1a5fb87372`|
|908|`b3de3c57d0c2e9b4a5f547220ef2426ed73f79581ab99905acdd2cc63adccdf5`|
|951|`4f8aaf60c375e858de05f296d577d3b8efc9b10d877bc2b9bc73a5dae1ad97bf`|
|999|`2e5e3a67d51a8f8a927fef44c9d9302f1b5c1e156fe26814476d8dc1814d5761`|

The handwritten staging source now has hypotheses for all41 concrete actions
and defaults. It retains its coverage boolean, rather than the original void
ABI. No root implementation row, match unit, exact row or authored-byte credit
is added. The newly exposed170 pointer occupies existing bytes:174 and all
later offsets and the388-byte view size remain asserted. Only this staging TU
includes the header; accepted shared headers are unchanged.

## Target observations and source hypotheses

906/907/908 do not have a global phase5 retirement. Their sequence0 owner174
thresholds are respectively5000/2500/0. A crossed threshold sets state2 before
requesting the same action with {fresh heading,0,2}; the next request changes
word2 to3 and event38 follows. Raw ESP compensation proves the two requests
reuse one buffer: for906 both pointers normalize to the pre-request SP+134.
Direct Ghidra splits them into different inferred locals; that split is not
accepted. A world call may modify the passed buffer, so words0/1 of the second
request are unknown from caller instructions alone. Runtime execution stops
at the first real world entry and never fabricates that return.

The sequence0 pulse stores the actual sine result to374, rounds the two scales
through the same float, damps370 and can clear the counter/select state1 before
the independent emission check on the same update. State2 grows both scales
and fades alpha/111/110. Sequence2 uses111 to gate both111/112, allowing112 to
wrap; sequence3 rotates/grows/fades and retains the fresh post-animation
sequence3 retirement check.

906's selectors0..3 use periods225/195/165/135, sector counts2/4/4/8 and steps
180/90/90/45. Each type4 request rewrites all three words; the final type5
request rewrites heading and word2, then wave19 follows. The selector family is
selected before opaque calls. Sequence4 grows/clamps X scale only, damps speed
before its ordered minimum4 clamp and orientation, calls both counter helpers
with0, resets word366 before increment, and fades111/112 in state2. Its bounds
select state2 **after** that fade block, without immediate retirement: X>=1800,
X<-520, Y>1400 or Y<-800. Sequence5 has the separate growth/fade path.

907 reads the followed object through this+170, independently of owner348.
Selectors0..3 use periods225/210/200/170. The signed facing multiplies the X
difference, while Y adds100 before subtracting self Y. Selector1 executes the
real atan2 call but discards its result and uses fresh heading for its two
sectors. The other families use its negated result; selector2 applies -90 after
adding the sector term. All requests have speed6/type4. The unused result does
not authorize dropping the call or its floating/CRT behavior.

907 sequence4 checks horizontal bounce before vertical bounce and returns
immediately after the real next-block call. The signed state<=1 owner gate,
alpha<=245 ramp, state6 call and heading+8 remain distinct from sequence5's
heading-8 and ordered bounds. A bounce does not continue into motion/animation.

908 processes its ongoing bursts before selector dispatch: positive even366
requests type6, calls wave1, adjusts374 using the reread word and decrements;
positive odd368 requests type7, adjusts378 without that wave and decrements.
Invalid selectors still process these counters. The240-period type4 offsets
are60/80, plus100 for selectors1..3 and120 for3; type5 offsets are70/90, plus110
for2/3 and130 for3. Actual random draws are360 then7+3 or3+2. Reset periods
are240 for selector1 and150 for2/3; selector3 sets both counters60 before its
two angle draws. Counter reads after opaque calls remain fresh.

908 sequences4/5 orient at old speed, rotate +/-2, call state6 with10 and test
the **signed** byte index. Owner174<=0 or own174<=-800/-1200 selects state1,
which clears index, grows/fades and then checks ordered bounds including
X==1500. Sequences6/7 accelerate by0.25 before orientation, use limit3 and
request type8/9 on state1. Sequences8/9 rotate +/-10, grow by old speed, then
damp speed by0.9f and fade.

951 copies owner alpha. Sequences0/3 copy owner Y; other sequences query actual
terrain with the **owner receiver**, before copying owner X. The word7A4 flag
is set and conditionally cleared on retirement. Owner action70..88,181/180/145
or100..111 at sequence/frame0 retires. Own sequence0 with owner96/97 sequence3
advances the block and clears heading. Own sequence1 accepts199/198/197/796/771
at owner sequence0/frame3; own sequence3's sequence2 retirement excludes771.
Surviving0/3 subtract35 from heading. Own sequence1/frame4 skips animation;
the fixture supplies a coherent five-frame range for that input.

999's target table4A1CBC sends **sequences0..3** to the owner-X write/bounds
body, with gravity for1..3. A source draft omitted3; the state matrix rejected
64 cases and direct table decoding plus Ghidra corroboration corrected it.
Sequence4 rounds velocity after subtracting double(0.35f), forms the projected
Y in binary64, and queries terrain with the **actor receiver**. On landing it
writes owner78C=1 before a second actual height call, sets Y, clears both
velocities and acceleration, then selects short sequence5 and returns. The
second call and the double projection are required observations. Sequence6's
owner78E==1 advances the block, sets facing1 and returns. Sequence7/8's gravity
applies only to8. Normal completion uses fresh animation state before the
sequence1/8 velocity15/acceleration0.2f initialization.

## Bounded native evidence

The public scalar auditor adds170-followed-object, atan2 incoming-word and
999 landing-flag observations. They observe actual instructions and never
substitute math, animation, terrain, RNG or world returns. The followed
object, owner and actor use different positions; terrain uses the original
69-byte fill routine to build flat, raised and stepped inputs. Landing flags
are recorded at both real height entries, exposing write/call order even
when final object bytes would agree.

The prior115736 generated inputs are byte-for-byte unchanged, input SHA256
`6222508163ccf2c7752458be2d941fb76ef2decee67a1aa538578703ed7a61ca`.
The new17456 inputs cover states/sequences, signed owner thresholds, exact
alpha/channel gates, reset/increment order, modulo timing, followed coordinates,
both x87 precisions, signed byte indices, immediate bounce returns, one-ULP
bounds, actual MT seeds0/5489/FFFFFFFF, owner action gates, nonflat terrain,
landing rounding and real animation transitions. Exceptional arithmetic keeps
the existing emulator/hardware qualification limits.

Final emulated native comparison is0/133192, preserving all115736 previous
inputs and adding17456. Input SHA256:
`f46a849ff57f64bb16e77fd0e28f7f51eee7238501c04049add99e7f77fc3b8b`.
The actual endpoints are119356 RETs,10422 unparented/1151 owned/472 parented
world entries,915 secondary-setup,26 effect,114 wave,112 CRT errno and624 CRT
quiet-NaN handler entries. The matrix visits9215 target root instructions and
8226 source instructions. These are bounded prefix observations, not whole-root
semantic coverage or canonical equality.

Thirteen serially compiled wrong-source controls are rejected. Selected CPP
and header pins stay fixed; target bytes, public bindings and helper returns
are never patched. Repeat each public cohort with a private source mutation:

| Deliberate error | Cohort | Differences /inputs |
| --- | --- | ---: |
|999 omits sequence3|`final-state`|64/3840|
|907 drops unused atan2|`final-907-aim`|90/360|
|907 follows owner rather than170|`final-907-aim`|360/360|
|951 queries actor terrain|`final-951-terrain`|432/720|
|999 reuses one height result|`final-999-land`|420/840|
|999 rounds projected Y to float|`final-999-land`|12/840|
|999 sets owner flag after second height|`final-999-land`|420/840|
|906 excludes X==1800|`final-bounds`|2/192|
|906 also grows Y scale|`final-906-phase`|672/672|
|908 treats index as unsigned|`final-908-gate`|216/720|
|908 emits366 on odd counts|`final-908-burst`|288/480|
|908 uses240 for selectors2/3 reset|`final-908-period`|60/1368|
|908 selector1 accepts offset110|`final-908-period`|6/1368|

The41336-byte replay also retains both808/812 conditional caller proofs.
VC8 now hoists variant1 into EBP at800030 and zero into EBX. The808 auditor
accepts this explicitly checked MOV-EBP/XOR-EBX dispatch permutation as well as
the predecessor MOV-EBX/XOR-EBP form, verifies24 case-to-window instructions
and all register aliases, and still rejects a separately compiled variant2.
The real RET1C supplies only a conditional normal-return stack effect; the
second request's first two words remain unknown after the opaque call.

Existing orientation0/400 and alpha0/1170 observers pass on this replay.
Terrain288 retains240 finite equal prefixes and48 hardware-unqualified
nonfinite contexts. The isolated original CVTTSD2SI still returns7FFFFFFF/
unchanged MXCSR under Unicorn1.0.2, versus the hardware contract80000000/
invalid flag. `matches_hardware_nan_contract` stays false; equal emulated
prefixes are not hardware acceptance. The adjacent runtime selector word at
6FA894 still supplies the mapped-dispatch0 NaN index-1 height load.

Eighteen accepted functions across stage-geometry4, animation-sequence-virtuals10,
character-object-runtime3 and atan2-natural1 replay exact. Accepted sources,
headers, flags, partitions and bindings are unchanged.

| Artifact | SHA256 |
| --- | --- |
|CRLF staging CPP|`20dc9d0d82236e941d8fba4bf64c2b380ce4c52adb28dbcc8ed12727a5a0a59e`|
|CRLF staging header|`a977bbed8cdd740e8721f7359a9d1ae4506daa8a9df471760ddbd653434b2089`|
|Observed fresh object|`def776eb09352aad3e1792b3edb023a0b0619c20c90478b7f1067184d5789aa3`|
|41336-byte replay at800000|`b6ef0db2594092104b39f78d604d7d172d31a6fc024f7457210ec986d8e29448`|
|Scalar native auditor|`ed8dcac0931bfc7b5e792ec69f8c950503692564e008635118078ce233a56a2a`|
|808 caller auditor|`129fef10b4b99a6fc194ba5d4e7ad731f4569e72372ba99cd76d288737fa9136`|

Object-only reports retain build-provenance-unverified status. The observed
serial fresh build command/log and pinned source are separate evidence.

The wrong907 owner-target control differs in360/360 inputs. Forty differ only
in the incoming atan2 words: later payload and snapshots conceal the error.
Dropping selector1's apparently unused atan2 call fails90/360, comprising68
argument/trace-only differences and22 that also change the actual CRT endpoint.
Wrong951 actor-height fails432/720, with144 changing the object and288 exposed
only by receiver/trace observation.

The wrong999 single-height optimization fails420/840 even though final object
bytes agree. Moving its owner flag past the second query also fails420/840.
Narrowing projected Y to float fails12/840. For example, raised terrain12.5,
Y12.5 and incoming VY0.3500000238418579 leave rounded VY2^-25. The target's
binary64 projection exceeds12.5, while the wrong float intermediate rounds to
12.5 and lands. Ghidra's narrowed decompiler expression is therefore rejected
by raw FSTP-qword evidence and this compiled control.


## Private void-ABI preparation

A separate private copy renames only the coverage method to
`void ReimuObjectActionStateStagingView::update_action_state()` and changes
its true returns to bare returns, with the matching declaration. The native
copy uses that actual void symbol and removes only the boolean-EAX assertion;
RET0, callee-saved registers, x87 stack/control word, memory, helper calls and
real endpoints remain checked. No target/helper instruction or return is
replaced. The source compiles serially with the existing profile and character
include directory.

It passes0/5465 scalar/final-state inputs, with5420 real RETs and45 first world
entries; input SHA256
`146b13ab9296591bd18d8f9d2d34331a00b79ae0c80dc75d11476d8b59b96bf2`.
This is preparation for promotion, not a full matrix or canonical comparison.
The selected public source remains the pinned boolean checkpoint above.

| Private artifact | SHA256 |
| --- | --- |
|CRLF void CPP|`15ba5006cb2bd4592fd79fafad49cf4222835c2bbdc4f5e6a0d0ffcbefcbd095`|
|CRLF void header|`92b35b5ff8c7f0a2edd4a1739b2c15c530d00d41688928465d0b02089d910859`|
|Observed void object|`9649fd83daef7688b4d5d91fbc2d428332b69daf01907034f34e05bc924bc4ee`|
|41480-byte void replay|`45780960252921793c5b4574f7c1cd1dd31395dbb819a989d5571a854f853816`|

The private source, source-pins receipt and native report remain under
`build/reimu-object-final-actions-20261020/void-probe`; the copied auditor is
under the corresponding private analysis directory. Its object-only report's
public support hashes do not attest the transformed source; the separate
private source pins and observed build provide that distinction.

## Reproduction and remaining work

A fresh baseline reproduces34928 replay bytes/226800a1 before edits. Target,
status, tracking and shared-callee ranking checks precede recovery. IDA metadata
attests a different image and supplies no semantic evidence. Direct read-only,
no-analysis Ghidra checks file/import identity, entry, full mapped text, root
extent and primary vtable with a128MiB heap cap, CPU0 and nice10. All nine primary DB hashes
remain unchanged and the temporary alias is removed. Decompiled expressions,
locals and types remain hypotheses; raw bytes settle disagreements.

```bash
taskset -c 0 nice -n 10 scripts/compile-unit.sh src/characters/ReimuObjectActionStateStaging.cpp build/reimu-object-final-actions-20261020/candidate2.obj
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-scalar-actions.py build/reimu-object-final-actions-20261020/candidate2.obj --final-actions --output-dir build/reimu-object-final-actions-20261020/positive
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-808-buffer.py build/reimu-object-final-actions-20261020/candidate2.obj
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-812-loop.py build/reimu-object-final-actions-20261020/candidate2.obj
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-orientation-args.py build/reimu-object-final-actions-20261020/candidate2.obj --output build/reimu-object-final-actions-20261020/orientation-args.json
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-secondary-alpha-args.py build/reimu-object-final-actions-20261020/candidate2.obj --output build/reimu-object-final-actions-20261020/secondary-alpha-args.json
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-terrain-contexts.py build/reimu-object-final-actions-20261020/candidate2.obj --match-identifiers 0 1 2 3 --output build/reimu-object-final-actions-20261020/terrain-contexts.json
taskset -c 0 nice -n 10 python3 scripts/build.py --unit cross-v106a-stage-geometry --compare --json
taskset -c 0 nice -n 10 python3 scripts/build.py --unit cross-v106a-animation-sequence-virtuals --compare --json
taskset -c 0 nice -n 10 python3 scripts/build.py --unit cross-v106a-character-object-runtime --compare --json
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-angle-atan2-natural --compare --json
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Objects, reports, raw packets and compiled wrong-control copies stay below
`build/reimu-object-final-actions-20261020`; private recipes and Ghidra scripts
stay below `.analysis/reimu-object-final-actions-20261020`. No executable,
analysis DB or generated report is committed. No cold aggregate is claimed.

All41 arms having source hypotheses does not prove whole-root semantics.
Returning world/setup/wave/event/CRT graphs, opaque buffer mutation, arbitrary
aliases/resources, nonnull rendering and unmasked exceptions remain open.
Promotion to an honest original void callable and whole-root canonical byte
comparison remain the next phase; no standalone/LTCG impossibility is inferred.
Preserve Fighter478FA0 and initializer4A1CE0 checkpoints.
