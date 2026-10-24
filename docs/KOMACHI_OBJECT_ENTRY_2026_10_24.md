# KomachiObject action initializer: complete source, seven-byte residual

`0x00600390`, KomachiObject primary slot+3C, now has complete selected source in
`src/characters/KomachiObjectActionEntry.cpp/.hpp`. The pointer-only receiver
views must never be constructed or embedded. Numeric states and typed offset
accesses intentionally precede naming and abstraction work.

## Complete comparison

Formal and independent cold VC8 builds both emit **6540 bytes against6540**,
canonical SHA256
`732ea4336323b83634f7669c6c8299ef3576f584dcdcf2970331514778ffa5b9`.
Exactly **seven unmasked bytes differ**, first **+0x93 /0x00600423**, target86/
source8E. All324 bytes of destination tables/action remap compare equal; all
115 direct calls,24 virtual calls,25 RETs and the real596370 tail are retained.
Source presence does not establish canonical acceptance. Exact totals and
`matches.csv` remain unchanged.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-komachi-object-entry --compare --json
python3 scripts/audit-komachi-object-entry.py
taskset -c 0 nice -n 10 python3 scripts/audit-komachi-object-entry-paths.py
```

The first two commands return1 for the recorded mismatch; the last returns0 for
eight scoped inputs. Both audits accept `--object`. Compile the selected source
with `scripts/compile-unit.sh` to a new path under `build/` for an independent
cold object. The full audit replays every relocation and compares the entire
emitted section, including metadata; no bytes are masked. Generated receipts
live under `build/exact-first-komachi-object-entry-20261024/`.

| Remaining target region | Observation |
| --- | --- |
|600422/600431|Target uses EAX for the input pointer, source ECX; two encoding bytes differ|
|6009B8..6009BD|Target loads rounded scale then adds H[0]; source loads H[0] then adds rounded scale; five encoding bytes differ|

The second difference is an x87 operand-order residual in817, not a license to
ignore floating behavior. Native finite controls below pass, but exceptional
NaN payload/operand behavior and the original compiler context remain unknown.
No LTCG necessity is established by this residual.

## Observed target boundary and ABI

Only original Japanese1.06a executable SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Existing RTTI/vtable origin anchors classify this root authored;
primary vtable cell `0x006C6018` contains600390. It previously had no durable
name or selected source. Source selection does not change the frozen origin
selector or authored denominator.

| Region | Reviewed extent |
| --- | --- |
|Callable|600390..601BD7 inclusive /6216 bytes|
|Action destination table|601BD8..601C43 /27 DWORDs|
|Action remap800..999|601C44..601D0B /200 BYTEs|
|Nested match-identifier table|601D0C..601D1B /4 DWORDs|
|Following separation|601D1C..601D1F /four INT3 bytes|
|Next independent callable|601D20, outside this payload|

Callable SHA256:
`fce78865faba3b457991099cca09fbacabdf75773c76b8cca74f842b5d470cb8`.
Complete6540-byte payload SHA256:
`fe41b8cbdcd9e6c4a28c24ca2c5220f067fff3d0f144af1294188779d99526ca`.
Raw CFG traversal reaches all1571 decoded instructions. Every direct/table edge
is accounted for; the only external tail is601B93 ->596370. Root reserves16
local bytes, saves EBX/ESI, and saves EDI only for in-range actions. All25 RETs
are RET0; the out-of-range shared epilogue does not pop an unsaved EDI.
The fall-through seven-byte LEA at600AC9 aligns a real twelve-object loop; no
manual padding or EH region is introduced.

| Direct callee | Physical calls | Target contract |
| --- | ---: | --- |
|68A1A0|24|Native compiler FTOL, implicit x87 argument|
|496420|5|ECX owner, key/float half-width/three integer arguments, RET20|
|435160|16|ECX=this+4, two float arguments, RET8|
|4067D0|63|cdecl random limit, unsigned conversion at these float use sites|
|435D60|2|ECX receiver, no stack arguments, x87 height return|
|4066B0|1|cdecl direct unsigned MT result in815|
|64CCB0|4|Seven four-byte stack arguments for an unparented object request|

Virtual sequence selection uses slot0C. The local signed-WORD call carrier
preserves the observed pushes without changing the shared int-facing selector
implementation. Local stages use the observed ECX/stack/x87 ABI; original owner
class identities and complete layouts remain provisional. Existing declarations,
helper implementations, compiler flags and literal bindings are unchanged.

## Inferred source shape and finite experiments

The SakuyaObject/YukariObject sources are family references only. Komachi's
prefix interleaves its float zero stores and WORD384/386 stores differently.
All supported actions are independently reviewed, including811's real fallthrough
to800,815's direct MT modulo360, physical positive/negative RNG tails and902's
runtime match-identifier dispatch through the existing6FA894 binding.

The first complete comparison exposed two missing source facts:902's second
object request updates **payload[2]**, not payload[1];930 must select a sequence,
write BYTE17C=2 and clear BYTE113 at sequence0 and generate twelve objects only
at sequence1. Raw stack/edge evidence corrects both. The second902 payload is
statically verified from its real stack store; the native prefix does not claim
to execute past the first spawn.

Repeated float multiply/spill/reload/add/spill sequences establish a real
rounded intermediate in810/812/850/853/854/856/901/902. Capturing the product as
float before adding reproduces both instruction widths and rounding. Numeric
random bounds, signed WORD guards and all target-retained physical helper calls
remain explicit. No inert locals, register forcing, fake returns, assembly or
copied target byte arrays are used.

| Private trial | One evidenced question | Complete payload |
| --- | --- | --- |
|00|First complete source, before the902/930 coverage corrections|6484, SHA b5204fb3...|
|01|Correct902 third component and930 selector/guard from actual stores/edges|6540, SHA9a5c4ee1...|
|02|Use native817 unsigned <=49 guard rather than equivalent <50|6540, SHA0ae4c031...; native immediate/branch recovered|
|03|Reverse817 source addition operands|Byte-identical to02|
|04|Order nested902 cases480/300/240 as their target physical blocks|6540, SHA732ea433...; all324 metadata bytes now equal|
|05|Express817 through the consumed scale's compound assignment|Byte-identical to04|

Keep04. Both arithmetic-spelling controls are neutral, so park the operand/
register residual and switch to another complete representative. Do not repeat
these controls without new independent evidence.

## Eight scoped native controls

`scripts/audit-komachi-object-entry-paths.py` uses the original PE vtable,
checked one-node action tree, four linked sequence blocks and valid untextured
frames. Selector45C390, map find45C320, frame application/commit, FTOL, random
roll and MT helpers execute original instructions. Only resource/RNG **data**
is supplied; no target code, vtable entry, helper return or result is replaced.

A deterministic state fixture has MT index0 and first state word1013904223,
with words1..623 set to their indices. The first real roll(15) yields9 under
the target's quotient-based range policy. This is a selected state fixture,
not a claim about the game's startup seed. Captured RNG index, full receiver,
call trace, stack cleanup and x87 control/top/tags are compared.

| Question | Inputs | Stop / observed result |
| --- | --- | --- |
|930 generation guard|selected sequences0,1,2,3|Only1 reaches the first real spawn; others complete RET0|
|902 initial request|sequence0|Actual64CCB0 entry with payload{0,0,2} and unchanged coordinates|
|810 product rounding|sequence2 at x87 CW027F and037F|Both scales have bits3FF33334 after rounded0.1f*9 then+1|
|817 consumed scale|sequence0, finite heading37.25|Native four-roll path completes RET0 with matching receiver/RNG state|

All8 pass: six real RETs and two pre-spawn prefixes. The real spawn body and
all later gameplay are outside those two prefixes. Vector SHA256:
`7e0fdd6afcf76467d514adf60451f7ce1063c378fa4d38237e40224e360546a8`.

The private unguarded930 negative fails3/8 (sequences0/2/3), canonical SHA
`269c208659964beccff740e7e4ff001259102266227ca946ae54ddb8accc3422`.
Removing the intermediate product rounding fails2/8 (both810 control words), SHA
`b1fe7c36363c589279d8ac796df3645cbb3539188251ade9289166d689018ef7`.
The latter yields3FF33333 instead of target3FF33334. These controls establish
the specific guard/rounding facts, not whole-function behavioral equivalence.

## Safety, durable state and remaining work

IDA preflight still fails on GUI SHA10350095..., so that session supplies no
semantic or write evidence. One direct Ghidra run is limited to CPU0/nice10 and
384MiB heap. File/import SHA, image base/entry, raw-backed mapped sections and
root SHA are independently checked. Temporary bounded root/helper metadata and
CALL_RETURN override for the actual980 jump are read back and rolled back.
All nine primary database pins compare unchanged. Decompiler output remains a
hypothesis; raw target instructions determine every accepted storage width,
edge and float-rounding boundary.

Durable changes comprise the complete source/header, source/name/function
ledgers, one focused unit, full-payload/native audits and this evidence/handoff.
No new literal keys or shared accepted headers are changed. Original source
spelling, nominal owner layout, original TU/link context and the two residual
instruction choices remain unknown. Preserve this checkpoint and select a new
complete medium/large authored representative next.
