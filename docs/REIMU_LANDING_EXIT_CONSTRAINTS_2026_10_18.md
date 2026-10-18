# Reimu: coupled landing/advance exits and motion-reset visibility

The selected source remains unchanged. Explicitly factoring the correct low9
landing group splits a previously correct advance group, including when the
source spells that advance operation as one shared block. A single expanded
switch also regresses522/523 sharing. The true motion-reset definition changes
caller code while retaining all51 calls, but does not recover the outstanding landing
memberships. None of these controls is selected or executed natively.

## Identity and exact target observations

Target is original Japanese TH10.5 v1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Root478FA0 is `[478FA0,48CE2E)`,81,550 bytes, SHA-256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
It remains authored/unclassified/declaration-only. Baseline is the source from
`a2c8cb1`, ordinary object
`66fbf8ddf4504c8b9f5f26b4414cce387185bb588de20ae04906e053a2ddda1c`.
Its82,808 canonical bytes remain
`0622c8d3d8c86f4894f66dfa8425cd7e9f09900fd23e2bb1e6a8b582739813c9`,
nonexact at+541=4791BD.

Target6/7/8/9/306 share the entire action10/height/clear/RET tail, beginning
479713, with virtual call47971C, height479720 and clearing47972D. The four
explicit incoming branches are47952C/4795EE/47968C/47D520;9 falls through.
The other height/clear group is208/209/210/211/221/222/309. Current source
instead puts9 in that latter group.

The target advance/RET site47973E has the complete membership
0/2/9/71/72/74/145. Nine explicit branches enter its ECX setup at47973C;
branch multiplicity is not the number of actions. There is also a preceding
47973A `FSTP ST(0)` entry, reached from479290/4798F9/4799C0/47A5C9. The
selected source has corresponding cleanup/setup/call at4792D2/4792D4/4792D6.
These cleanup observations come from hash-attested raw disassembly; full
x87 depths and live-value identities have not yet been established.

The other unresolved target height/clear/sequence groups are197/658 at
48A701/48A70E/48A71B and198/608 at488FD5/488FE2/488FEF. The current source
instead pairs197/608 and198/658. Both target suffixes push EDI but use opposite
vtable scratch registers. This does not justify changing a prototype or adding
register-forcing constants.

197's branch47A67F enters the height **call** at48A701;198's47A7DB enters the
call at488FD5. Each caller has already executed `MOV ECX,ESI` immediately
before the conditional branch. The selected source has the same receiver
preparation. Jumping past a suffix's ECX setup is therefore not evidence that
the preceding predicate preserves ECX. No calling-convention change follows.

## Source-only exit controls

All controls use the unchanged VC8 flags, types, field widths and operations.
The private source has128 expanded nondefault keys; the one-switch control
does not revert to the compact retained case sharing.

| Control | Prefix / payload | Complete sharing result |
| --- | --- | --- |
|Factor the five-action landing block in9|81452 /82824|Landing group agrees; advance9 splits from0/2/71/72/74/145|
|Also give9 an explicit edge to145's advance block|81452 /82824|Entire canonical payload identical to the preceding control|
|Spell all seven advance edges into one source block|81452 /82824|Compiler still emits separate9 and six-action advance sites|
|Define the common landing block in6 instead of9|81452 /82824|Entire payload identical to the first control|
|Both common exits in one expanded switch|81356 /82728|9's advance group still splits;522/523 advancement, owned and wave tails merge|

The three byte-identical controls have canonical SHA-256
`0d9bdc8ac2924e2ed03b8391dac7745a71a530ee1a8ccac7cdfe99b2a3979615`.
Their result is stronger than a local instruction comparison: moving the
label or adding one explicit incoming edge changes no payload byte.

The full seven-edge control has a different payload, but still separates9's
advance from the other six actions. Its C++ shared block does not determine
the compiler's physical sharing. This is evidence about the current input and
compiler phase, not proof that a standalone match is impossible.

The first four controls have121 physical advances, matching the target total
while still missing its separate300/320 sites. The extra9 site conceals that
deficit. The one-switch control returns to120 by wrongly merging522/523;
it does **not** restore9's complete advance membership. Its owned count is
243/242 and wave77/76, and eight direct partitions differ rather than six.
Those regressions preclude selection. Equal cardinalities, fewer instructions
or a smaller object are insufficient.

All controls fit the reviewed callable/metadata caps and pass the applicable
15 stack/request contracts in read-only diagnostics. Their behavior is not
replayed merely to re-establish unchanged operations after a known sharing
regression. No native sensitivity or target-root equality claim is made.

## True27-byte motion-reset definition

The accepted `FighterMotionReset.cpp` body is adapted only to the root's
existing member name and offset-proved view. All27 canonical helper bytes
agree with45AF40, SHA-256
`ced17212284f1e530398a6109db9a47ab83392761b9228b279bbd334f0c1950d`.
Its float stores remain F4/F8/FC/100 and its void thiscall interface is unchanged.
This is an existing exact anchor, not new matching credit.

With that definition visible before the otherwise unchanged root, all51 reset
calls remain. Prefix81364/payload82736/frame570h has canonical SHA-256
`2abc8e2e0dbcd81d5c227050807af706d8aa7b549d368f41598038672f513c50`.
All32 complete direct source partitions remain identical to the baseline,
including the outstanding low9 and197/198 pairings. The code change therefore
does not require inlining or a changed direct-call inventory.

Aggregate indirect sharing regresses: a source-only214/545/546 group replaces
one214 site and the previously correct545/546 group. Physical totals become
220/218 instead of220/219; per-action aggregate deficits still only report
410 and416. Again, unchanged per-action counts do not prove correct sharing.
An unreferenced identical27-byte body leaves all82,808 baseline bytes unchanged.
That control distinguishes mere extra body/function presence from making the
called definition available in this phase; it asserts no original unused helper.

The public opaque-provider gate remains intact. A private closed-unit
diagnostic first proves the unique defined helper's full27 bytes, section/value
and call origins, then permits only that provider while retaining the other
relocation/metadata/numeric/global checks. It is a separate diagnostic contract,
not root admission. No image or private control is executed.

## Reproduction and next work

Private recipes, receipts, full membership regressions and payload hashes are
under `build/reimu-landing-memberships/`. The representative object command is:

```bash
nice -n 10 taskset -c 0 python3 -B build/reimu-landing-memberships/two-common-exits.py
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-call-sharing.py \
  build/reimu-landing-memberships/two-common-exits/candidate.obj --diagnostic-oversize
```

`single-switch.py` consumes that generated source. The zero-visible and
unreferenced controls have their own recipes; `zero-closed-census.py` uses the
full27-qualified private provider. Regenerate removed object products before
reusing inspection commands. None of these recipes changes selected source,
an accepted unit, an ABI, a flag or the public admission rules.

Direct read-only Ghidra re-attests image/entry/language/compiler, all mapped
`.text` and the full root hash, then independently confirms15 explicit edges:
four landing entries, nine advance-setup entries and the two jump-to-call
entries above. There is no full-root decompilation or saved metadata write.
All9 primary DB hashes remain unchanged, and the temporary alias is removed.
The separate x87 cleanup-entry packet remains raw PE evidence.

Heavy jobs stay serial on CPU0/nice10. Peak RSS is319,496KiB (312MiB); the
bounded Ghidra run takes10.62s with128MiB Java heap. Cleanup removes23 obsolete
products and redundant byte-identical reports/5.02MiB, preserving all164 current
genuine-cache files and the small true-definition witnesses. No historical
native matrix or aggregate exact-unit replay is run.

Next recover x87 stack states and live-value identities around47973A/47973C
and their selected-source counterparts, using reviewed callee stack effects.
Whether those states explain physical sharing remains unknown. Do not repeat
these goto/switch/visibility variants without a material source-phase change,
or force a register/ABI to obtain a desired group. The full95% authored-byte
goal remains open.
