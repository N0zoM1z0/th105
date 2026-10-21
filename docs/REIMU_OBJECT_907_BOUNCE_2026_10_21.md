# ReimuObject907: actual bounce callbacks and remaining call sharing

The selected496540 source remains unchanged, CRLF CPP SHA256
`3b9e4896c3645bb1228db3b432a832154870c5639a80df6c02cb67ce2dba12cc`,
header `6f469e6886959fd41ee6976b3c784c3df0c2e753ad4729a536764a3c8cd28b4b`.
Its complete45700-byte canonical section is stilld0ff3d32, nonexact at
49655F/+31. No authored function, exact byte, source selection or ABI/layout
change is added. The new evidence closes a bounded actual-return question
behind the remaining physical call-count difference.

## Observed target

Only original Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Target/status/tracking preflights pass; IDA rejects its wrong open
10350095... executable and supplies no semantics. No database is modified.

Fresh raw decoding/census independently reproduces10670 reachable owned
instructions,433 calls and68 RETs. Its complete call/return memberships agree
with the preceding frozen target census, after normalizing JSON dictionary
keys. The reviewed39853-byte main candidate and46138-byte physical comparison
ownership remain unchanged; the first31 bytes match and the first differing
field is the later default-branch displacement.

In907 sequence4, state1 calls the real counter helper4963A0 with limit0.
The target first tests signed-facing X velocity against X bounds0/1280.
An X bounce negates velocity+F4, publishes phase-index+184 =1 and phase+180 =0,
calls actual primary vslot14 at4A0362, then returns at4A036E. If X does not
bounce, Y velocity is tested against Y bounds0/900. A Y bounce negates+F8,
publishes the same state, calls vslot14 at4A03CB, then returns at4A03D7.
The tests are strict; equality at the boundary does not bounce. Ordered NaN
comparisons do not enter these bounce paths. Target FPU cleanup differs
between the comparison paths, but each callback begins with an empty x87 stack.

The current source has the same two ordinary conditional bodies, while VC8
shares their final state stores/callback/return. Its one physical CALL809B2F
handles both axes. Static counts alone cannot diagnose an omitted runtime call.

## Finite actual execution and negative controls

`scripts/audit-reimu-object-907-bounce.py` executes the actual target/source
root instructions, actual66-byte counter, original138-byte next-block helper
45C220 and its real animation continuations. The object's original primary
vtable and slot14 are read back at callback entry. Neither target bytes,
vtable entries nor helper results are replaced, and the callback actually
returns before the root's ordinary RET. Final stack/register and x87 balance
checks remain active.

The2048 inputs combine four X/Y coordinates each, four X/Y velocities each
(including signed zero and quiet NaN), both facings, two masked x87 control
words and phases0/6. State1 and owner+174 =3000 admit the bounce gate. The
fixture's `owner_value174` field is the later initializer actually consumed;
the older generic `owner_health` input is overwritten for this action and
must not be used to claim bounce coverage. The admitted data is the existing
checked animation tree/linked blocks with valid untextured frames.

Input SHA256 is
`30a518c0283c89dfde8662b0db07298bcebdaf18039a12e7ef4e71825b4eb153`.
There are256 X-bounce inputs,224 Y-bounce inputs and1568 without a bounce.

| Actual compiled source | Output differences | Ordered-write differences | Write-time logical-x87/value differences | Callback differences |
| --- | ---: | ---: | ---: | ---: |
| Selected source |0|0|0|0|
| Real counter in a separate source TU |0|0|0|0|
| Wrong X bounce negates Y velocity |256|256|256|0|
| Wrong X upper gate uses `>=1280` |128|128|128|112|

Both negative controls are genuine private C++ builds, rather than patched
instructions. Each still preserves the same-TU4963A0 canonical66/66 helper.
The source callback count is480 for both the selected source and wrong-axis
control. The wrong-boundary control instead calls592 times. These distinguish
correct runtime policy from equal call counts. Target physical sites execute
256/224 times; the correct source's single site executes480 times.

The audit compares complete fixture outputs and ordered root/helper writes.
It additionally records logical live x87 values/tags at velocity/phase stores
and callback entry. Its finite scope excludes arbitrary aliases/resources,
other vtables, intermediate physical TOP/exception flags, unmasked exceptions,
other907 sequences, opaque request continuations and full-root semantics.
Build provenance is a separate formal receipt, not certified by this emulator.

## Real counter visibility control

The selected root omits a redundant ECX reload before its907 virtual call;
the target reloads ECX. This motivates a fresh visibility test at this source
epoch, without assuming the older counter-context result transfers.
The exact real4963A0 definition was compiled in a separate TU and removed
only from the private caller TU. The normal declaration, body, fields and
calling convention are unchanged. Its provider independently remains66/66,
canonical SHA256
`ad12b782ed5fc99007456fc66a9615951cee34178850a308316409c5245bb156`.
No replacement return or external private-ABI facade is introduced.

The separate-TU caller remains44832 code+868 metadata bytes, with10395 decoded
instructions and63 RETs, compared with selected10393/63. Its whole45700-byte
canonical SHA is
`4051a1a639077e1a94812fe4bbff8f1f5e8dbd2ed6ce99d9c6adb7c02b5cd01a`.
It remains nonexact+31, with the same call-membership distance11 and
RET-membership distance27.907 still uses one physical virtual call809B32.
This source-epoch control changes allocation/scheduling but does not solve
the remaining sharing. It is unselected, and the accepted helper stays in
its current public TU.

Other target/source call-membership differences remain the animation groups
800/811/821/825 and815/822, plus indirect810/812/852 sharing. This audit does
not prove those predicates or establish an impossible standalone boundary.
The next work remains genuine source/TU and lifetime recovery; duplicating
callbacks merely to raise the physical count would contradict the new proof.

## Reproduction and retention

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-reimu-object-action-state --compare --json
# Expected exit1:496540 remains nonexact;4963A0 remains66/66 exact.
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-907-bounce.py \
  build/match-units/GptWeb_ReimuObjectActionState.obj \
  --output build/reimu-object-907-bounce.json
```

Receipts are under `build/reimu-object-call-ret-context-20261021/`, including
the formal baseline, fresh target census, facts-and-controls, provider66/66
comparison and four final audit runs. Recipes are in the matching `.analysis/`
directory. All four final matrices ran serially on CPU0/nice10 in33.65 seconds,
peak RSS137516 KiB. Three unselected source/object/native/large-report sets
were archived with per-file SHA256 round-trip checks:2417222 ->305663 bytes.
The baseline, summaries, native execution and provider receipts stay loose.

Only this audit and evidence documents change. No shared header, compiler
profile, game source, relocation/match/origin ledger or ownership record is
edited, so no unrelated accepted-unit or aggregate replay is required.
