# Reimu: middle projectile actions400..408

## Target observations and reconstruction

Target remains original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The parent is `Reimu_dispatch_action_state_vslot28 @478FA0`,81550 bytes,
ending48CE2E, SHA256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
It remains unclassified/declaration-only, with no implementation/exact credit.

`ReimuActionStateDispatch.cpp` now directly includes
`ReimuActionStateMidProjectileCases.hpp`: actions400,401,402,404,406,408.
It retains the shared entry/low/first-middle source, routes newly admitted
gap actions to real common4740C0 and leaves>408 pending. Its bool is a partial
source interface, not the complete original void-root ABI.

The six physical bodies occupy `[47DB64,47F4A9)`:6469 bytes/1570 instructions,
SHA256 `df0937acb38e1c6829478969afcd1c5eec3318c8a711df9edecc1bd2b06675cd`.
The primary table's current bytes independently confirm each entry:

|Action|Entry|Next physical entry|
|---|---|---|
|400|47DB64|47E0A7|
|401|47E0A7|47E5E1|
|402|47E5E1|47E7BF|
|404|47E7BF|47EDBE|
|406|47EDBE|47F343|
|408|47F343|47F4A9|

These regions are not independent callable boundaries.402's counter>10 exit
shares the next-block/RET at47D7BE, while406's second aim/advance/sequence8
suffix shares404's47ED44/47ED4D/47ED74 tails. The complete root remains the
canonical acceptance boundary.

Instruction-derived source choices preserve:

- Signed WORD+730 increment/wrap before remainder3, signed+732<5, exact
  zero-shot resource consumption and live BYTE+750 selection.
- 400/401 charge after the resource adjustment, versus404/406 charge before
  it.400 initializes its parameter array before charging;401 charges first.
- Ordinary object800 parameters(angle,15,0). Charged fire draws native
  range(0,30) for angle, then range(0,5) for speed, twice, with live positions
  and signed-facing coordinate offsets versus raw unsigned direction bytes.
- Two separate aim setups in sequences2/6. Directed X difference and Y
  difference each round through float call arguments; real atan2 returns
  float, converts to int, then negates the low WORD before signed clamping.
  Limits are[-30,30] for400/404,[-60,-40] for401 and[40,60] for406.
- 404/406 gravity and early landing to sequence8, flag+47F clear, native
  height/zero-motion and counter clear. Their sequence2/6 continuation also
  publishes0.35f gravity after the next-block call.
- 406 emits its charged-start effect before selecting sequence4;400/401/404
  select the sequence before the effect.408's observed launch constant is
  **3.5f** from6C3448, with0.75f gravity, not the rejected initial7.5f reading.

Private numeric views expose peer Y+F0, BYTE+47F, float+4D0, WORD+558,
signed BYTE+55A, DWORD+6C0 and WORD+738 with offset assertions. Names remain
descriptive views; neither the full class layout nor original TU is proved.
Typed declarations bind already accepted helpers406540(atan2),4351A0(range),
478DF0(scaled counter) and45C030(wave handle); their source/units are unchanged.

## Focused execution evidence

```bash
scripts/compile-unit.sh src/characters/ReimuActionStateDispatch.cpp build/reimu-mid-projectiles/ReimuActionStateDispatch.obj
python3 scripts/audit-reimu-mid-projectile-actions.py build/reimu-mid-projectiles/ReimuActionStateDispatch.obj
```

Pinned VC8 SP1 `/O2 /GS- /GR /EHsc /MT`, default FP, no injected environment,
produces17524 staged text bytes. Object SHA256 is
`f495235a74f80f74a5208af846a7008cef9f013c338771097257995cccd18a33`.
The manual compiler/source/header/object receipt is
`build/reimu-mid-projectiles/build-receipt.json`; the oracle separately pins
its object/support inputs and does not itself attest compilation.

Final result **0/2932 differences**, report
`build/reimu-mid-projectiles/native-final.json`, input SHA256
`d5a78a146a80b6860982d1d0a45f1480fcbc5d671148cd0b0773d8381da4f03e`.

|Cohort|Cases|
|---|---:|
|Nine sequences, node entry, landing, completion thresholds|648|
|Signed timer/shot counts, WORD wrap, ordinary/charged selection|960|
|Both aim nodes, three peer X/Y values and signed-facing extremes|608|
|Scaled-counter phases/scale/WORD wrap and real MT seeds|480|
|16 required original branch sites, both x87 precisions|32|
|104 old-middle smokes plus59 low/entry smokes and28 real common returns|191|
|New gap/default transfers|5|
|Later source handoffs|8|

2321 cases reach native RET;13 stop at real effect435240 entry,575 at real
object465190 entry,11 at real common4740C0 entry and1 at real set669 entry.
Another11 compare later-source state at original47CC5F against the candidate's
genuine false return.3132 original-root and1918 staging instruction addresses
are sampled. Returned cases preserve the real stack delta4 and callee-saved
registers; x87 TOP=0 and the input control word are required.

The inherited comparison checks4096 actor bytes, ordered helper/receiver/
argument traces, physical conversion inputs, world scalar and full MT state.
624 actual atan2 calls execute the unchanged target wrapper and native math
dispatcher/kernels through RET, with complete8-byte argument comparisons.
592 range calls execute4351A0,4067D0 and actual MT twist/temper; no draw is
substituted.572 scaled-counter calls execute the original107-byte method,
including all three signed phase branches and WORD accumulation.

Math code envelopes and internal entries are hash-pinned private execution
allowlists. The atan2 descriptor/table and all other code/data come from the
canonical mapped PE. This neither promotes their provisional function
boundaries nor assigns new compiler/library origin or authored progress.
Fixtures retain target startup math globals, masked PC53/PC64 and finite
aim inputs. Both-zero atan2/domain-error processing, other runtime modes,
full x87 tag/sticky-flag equivalence and unmasked exception delivery are unknown.

Objects800/807 and inherited848 validate the live supplied-stack pointer,
count3 and all12 pointed bytes alongside other arguments at the real wrapper
entry. No result is supplied. The two-shot loop's second request, wave call,
post-spawn shot increment,807's second request and other returning manager/
effect continuations therefore remain unproved. Wave45C030 is bound but has
zero executed entries in this matrix. Source includes these target-derived
continuations; the matrix supports only its stated endpoints.

The initial408 speed hypothesis failed2/2932 cases, both at its required
launch branch; target/candidate traces agreed and the stored velocity differed.
The corrected source above passes. Three compiled wrong-source controls are
retained as small reports, with source/objects removed after inspection:

- Original wrong7.5f launch:2/32 required-branch cases fail.
- Object800's third parameter changed from0 to1:8/60 smoke cases fail.
- Fire cadence tested against the pre-increment count:8/60 smoke cases fail.

Reports are `wrong-speed.json`, `wrong-payload.json`, `wrong-cadence.json` in
the same build directory. Controls use ordinary C++/VC8; the latter two add
only a private include directory. No helper-result or target-byte patch is used.

## Preservation, resource use and next work

All six older adapters are freshly rebuilt: non-debug code/data and every
relocation offset/type/symbol/value/section identity remain identical. Text
sizes remain530,771,1562,4017,4409,11271; receipt
`build/reimu-mid-projectiles/preserved-stages.json`. Focused replays pass0/9
entry,0/88 low,0/64 recovery,0/99 movement,0/150 late-low,0/59 low dispatch.
The changed monolithic method's earlier paths are covered by the191-case
integration cohort. Historical full matrices are not repeated. No accepted
unit uses this private header; accepted source/flags/relocation ledgers and
exact totals are unchanged. No aggregate cold replay is claimed.

The fixture adds optional nine-sequence graphs with computed block/frame
strides and image capacity. Each case supplies the current action and real
transition destinations rather than all unrelated animation keys. Default
six-frame/seven-sequence output is byte-equal for48 prior key/frame/profile
combinations.23 structural tests include64 keys,14 frames and9 sequences.
The supplied read-only graph, flat surface, zero wave/texture/event handles
and inactive secondary-event cycle bound the proof; they are not game assets.

One direct read-only Ghidra clone attests file identity, entry68B9D2,
base400000, Windows x86 language, complete mapped.text and full root hash.
It reads back the six current entries, prospective410..418 entries, helpers
and shared tails; marker `REIMU_MID_PROJECTILES_READBACK_PASSED` is in
`build/reimu-mid-projectiles/ghidra.log`. All9 primary DB files stay hash-equal,
and the clone is deleted. The wrong-target IDA session supplies no semantics.
Rejected/superseded products and Python caches are removed after final gates.

Next continue410..418, then the500 middle group and high actions, while
recovering real returning world contexts. Complete void ABI, full CFG/
relocations, truthful VC8/LTCG/TU provenance and an all81550-byte canonical
comparison remain prerequisites for accepting the parent as exact.
