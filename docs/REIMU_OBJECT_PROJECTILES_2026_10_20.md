# ReimuObject800/801/804/807/808 source and caller evidence

This page records the b5855c6 checkpoint. The
[810/811/812 follow-up](REIMU_OBJECT_SEQUENCES_2026_10_20.md) records current
source pins and the expanded native/caller evidence.

This extends the [initial update checkpoint](REIMU_OBJECT_UPDATE_2026_10_20.md)
at88ac760. The bounded target remains authored `ReimuObject @496540`:46128
owned instruction bytes, not the provisional39853-byte main span. The complete
target CFG and its22 switches are unchanged. Exact target SHA256 remains
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.

## Source observations and hypotheses

The handwritten staging method now handles ten concrete actions plus the real
default. Another31 concrete actions remain explicitly unsupported. Its bool
still reports coverage; it is not the original void callable boundary.

| Action | Target-derived source behavior |
| --- | --- |
|800|Owner-effect/phase5 retirement, fresh993 secondary setup, signed-word acceleration, sequence1/2 scale and alpha handling, release/next-block/owned800 request, ordered bounds and shared animation retirement|
|801|Entry bounds with lower Y=-240, owner gate, growth/next-block, actual target steering and periodic801 request, phase/timer selector handling, sequence2/3 fade, movement and shared animation retirement|
|804|Separate target sequence0/1 paths expressed with shared source logic, secondary setup, state6 timer, short reset state, signed-byte index gate, two real MT draws after select2/release, sequence2 gravity/bounce/fade and lower Y=-120 bounds|
|807|Distinct sequence0/1 owner gates, state6 timer, signed-byte index acceleration/deceleration, alpha<=15 retirement without clearing alpha, X movement and animation completion|
|808|Owner gate, distinct sequence0/1 vertical speeds, conditional paired808 requests through one caller buffer, alpha<=15 retirement without clearing alpha, Y movement and animation completion|

The staging view exposes observed short fields368/36C/384 while preserving
size388 and existing offsets. No accepted unit uses this new staging header.
The source uses real virtual selectors and existing helper ABIs, including the
465190 owned-manager wrapper's seven argument words. No shared accepted header,
compiler profile, object partition or public relocation ledger changes.
Original class declarations, local types, source sharing and TU remain unknown.

Fresh VC8 `/O2 /GS- /GR /EHsc /MT` compilation succeeds. Current CRLF pins:

| Artifact | SHA256 |
| --- | --- |
|Staging CPP|`4fa8bfd27773f041af0e5c82a5c6b6586574ffc885c3efc31e4342b9dc9951f2`|
|Staging header|`362bf3c3d171e4f68119a45f6f7474ba90a4f15326850e940d41cc538271d9f2`|
|Observed fresh object|`7c3fe98011e077d9bf19c968649e8364e8a025c946f27dd0a430e893c8210152`|
|4200-byte staging replay at800000|`0cbfb224641bd15f9a032661b3fd843ddd18e1ead6527d0083b73a0e0c0ddcfb`|

The replay is an execution input, not a target-equal function. The object-only
auditor continues to report build provenance unverified; the separate fresh
build command/log provides the local compilation observation.

## Native execution evidence

The extended public scalar audit with `--projectiles` passes **0/6292**.
Input SHA256 is
`6d702701f7659f9787fc5b10d45199e9106daddac0f7eeea7c2da445123bac88`.
All1625 preceding scalar/default cases remain present, plus3780 projectile
state,210 bounds,216 alpha,192 steering,144 collapse,60 owner-gate,20 paired
request and45 frame/scale cases. Bounds include unordered X/Y and both x87
precisions; frame/scale cases include unordered scale. Collapse includes
signed-byte indices128/255 and actual MT seeds0/5489. Other fixtures also
retain original seed5489; the seeder checks seedFFFFFFFF independently.

| Actual endpoint | Inputs |
| --- | ---: |
|Real RET with stack/callee-saved/x87 checks|6074|
|64CCB0 unparented spawn entry|63|
|465190 owned spawn entry|75|
|435240 effect entry|26|
|496420 secondary-animation setup entry|54|

These inputs visit1026 target root instruction addresses and901 staging
addresses. They execute305 actual steering/atan2/CRT chains and268 actual MT
next calls. Target406670 generates the624-word MT state packets; target4065B0
generates the3600-entry orientation table. No host random/math return replaces
those routines. The finite CRT atan2 spans follow the already reviewed fighter
projectile audit; the initially missing68BB70 scope was an audit execution gap,
not evidence of a source mismatch.

Actor388 bytes, supplied owner800 bytes,16 parameter bytes, complete MT state
and index, helper ordering, endpoint receiver/arguments/copied payload, x87
control word/TOP/tags are compared. Writes stay within the supplied objects,
parameters, stack or the actual MT routine's aligned state/index destinations.
The secondary renderer pointer is null; fixtures supply one animation graph,
distinct actor/owner/parameter regions and an empty incoming x87 stack.
Returning world/renderer graphs, nonnull secondary destruction, arbitrary
alias/stack states, unmasked exceptions and whole-game behavior remain open.

##808 caller buffer: correcting a decompiler-local assumption

The direct read-only Ghidra hypothesis prints different array names for the two
requests and makes the second array's first two elements look uninitialized.
Those names do not establish distinct original locals. Physical stack reuse
also cannot distinguish one original C++ local from two locals with reused
storage. Target instructions
prove reuse after accounting for pushes and the actual callee's RET1C:

| Observation | Address / baseline-relative address |
| --- | --- |
|First pointer from LEA after PUSH3|497230 / B+128h|
|Three zero stores|497229:B+128h,497237:B+12Ch,49723F:B+130h|
|First actual call|49727B ->64CCB0|
|Real callee normal-return cleanup|64CCFB: RET1Ch|
|Caller writes float1 to third word|497282 / B+130h|
|Second pointer from LEA after PUSH3|49729E / B+128h|
|Second actual call|4972C8 ->64CCB0|

`scripts/audit-reimu-object-808-buffer.py` independently tracks these
straight-line ESP/pointer/x87 stores and the corresponding compiled caller.
Target pointer offset128h and source offset10h each designate one shared
three-word buffer. It checks seven argument words, count3, action808, variant1,
float store widths, empty local x87 state and normal-return stack balance.
Target window `[497225,4972CD)` SHA256 is
`0c3b216422bf657535ea340fba316762e0e058f3e0b667f46917dceaea37ce25`.

This is conditional caller analysis, not a synthesized world return. The audit
invalidates all passed payload words across the first call. Thus its second
snapshot is **unknown, unknown, float1**; caller instructions alone do not prove
that the callee preserved the first two zeros. This explicit unknown prevents
the handwritten one-buffer source from acquiring an unsupported returning-world
claim. The native matrix stops at the first request and does not execute the
second. Six tests cover wrong cleanup, wider stores, word pushes, stack-pointer
LEA, unknown instructions and target reuse with conservative invalidation.

## Wrong-source controls

Each control compiles independently and runs the same6292 native inputs. The
selected source stays unchanged; negative artifacts remain below build.

| Deliberate source error | Native differences /6292 |
| --- | ---: |
|801 `scale<1` changed to `!(scale>=1)`|1, unordered scale|
|804 signed-byte index `<1` changed to unsigned-byte `<1`|34, including RNG state|
|807 alpha `<=15` changed to `<15`|4|
|808 between-call assignment `copied[2]=1` changed to `copied[1]=1`|0; caller-buffer audit rejects|

The fourth control deliberately exposes the native matrix's first-call stop:
it still passes0/6292, while the caller audit exits1 for the wrong third-word
assignment. The positive caller audit exits0. This does not extend native
coverage to a returning world call. Controls' source SHA256 pins are:

| Control | Source SHA256 |
| --- | --- |
|801 unordered|`3db3d3c03ec6ed1f4dc7f4645afbc921aba819b51f4b14d3ff7043f81cf2907d`|
|804 unsigned|`aad73d80ab076a6d746129d666bf9337e217a0cb1ce668d19c563aa1cc8c3598`|
|807 alpha|`72924a3990d4659f1fbbeaa511f3329f44be27a54165bbe240768f5ca0943e14`|
|808 wrong word|`f784e2a5cae6834e6cf0526a93936aa9dfddc747d0420f650fb8d012873d49c9`|

## Database safety and reproduction

Fresh direct Ghidra independently checks import/executable identity, base/entry,
x86/windows target, mapped text, root extent and vtable slot. The read-only
128MiB/CPU0/nice10 export completes with all nine primary DB hashes unchanged;
the temporary alias is removed. Its C text remains a hypothesis below build.
The failed IDA preflight is not used for semantics; no factory adapter is used.

```bash
taskset -c 0 nice -n 10 scripts/compile-unit.sh src/characters/ReimuObjectActionStateStaging.cpp build/reimu-object-projectiles-20261020/candidate.obj
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-scalar-actions.py build/reimu-object-projectiles-20261020/candidate.obj --projectiles --output-dir build/reimu-object-projectiles-20261020/positive
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-808-buffer.py build/reimu-object-projectiles-20261020/candidate.obj
python3 -m unittest discover -s tests -p 'test_reimu_object*py'
```

Recipes remain below `.analysis/reimu-object-projectiles-20261020/`; fresh
target/positive/control/Ghidra outputs stay below its build counterpart. Builds
are serial and temporary products remain small. No implementation/matches row,
match unit or exact credit is added. Next recover810/811/812 and their shared
exits, then continue the other28 concrete actions. The separate Fighter478FA0
and Object-entry4A1CE0 checkpoints remain unchanged.
