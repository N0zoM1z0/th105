# KomachiObject action initializer: complete source, seven-byte residual

`0x00600390`, KomachiObject primary slot+3C, now has complete selected source in
`src/characters/KomachiObjectActionEntry.cpp/.hpp`. The pointer-only receiver
views must never be constructed or embedded. Numeric states and typed offset
accesses intentionally precede naming and abstraction work.

## Complete comparison

Formal and independent cold VC8 builds both emit **6540 bytes against 6540**,
canonical SHA256
`732ea4336323b83634f7669c6c8299ef3576f584dcdcf2970331514778ffa5b9`.
Exactly **seven unmasked bytes differ**, first **+0x93 /0x00600423**, target 86/
source 8E. All 324 bytes of destination tables/action remap compare equal; all
115 direct calls,24 virtual calls,25 RETs and the real 596370 tail are retained.
Source presence does not establish canonical acceptance. Exact totals and
`matches.csv` remain unchanged.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-komachi-object-entry --compare --json
python3 scripts/audit-komachi-object-entry.py
taskset -c 0 nice -n 10 python3 scripts/audit-komachi-object-entry-paths.py
```

The first two commands return 1 for the recorded mismatch; the last returns 0 for
eight scoped inputs. Both audits accept `--object`. Compile the selected source with
`scripts/compile-unit.sh` to a new path under `build/` for an independent cold
object. The full audit replays every relocation and compares the entire emitted
section, including metadata; no bytes are masked.

| Remaining target region | Observation |
| --- | --- |
|600422/600431|Target uses EAX for the input pointer, source ECX; two encoding bytes differ|
|6009B8..6009BD|Target loads rounded scale then adds H[0]; source loads H[0] then adds rounded scale; five encoding bytes differ|

The second difference is an x87 operand-order residual in 817, not a license to
ignore floating behavior. Native finite controls below pass, but exceptional
NaN payload/operand behavior and the original compiler context remain unknown.
No LTCG necessity is established by this residual.

## Observed target boundary and ABI

Only original Japanese 1.06a executable SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Existing RTTI/vtable origin anchors classify this root authored;
primary vtable cell `0x006C6018` contains 600390. It previously had no durable
name or selected source. Source selection does not change the frozen origin
selector or authored denominator.

| Region | Reviewed extent |
| --- | --- |
|Callable|600390..601BD7 inclusive /6216 bytes|
|Action destination table|601BD8..601C43 /27 DWORDs|
|Action remap 800..999|601C44..601D0B /200 BYTEs|
|Nested match-identifier table|601D0C..601D1B /4 DWORDs|
|Following separation|601D1C..601D1F /four INT3 bytes|
|Next independent callable|601D20, outside this payload|

Callable SHA256:
`fce78865faba3b457991099cca09fbacabdf75773c76b8cca74f842b5d470cb8`.
Complete 6540-byte payload SHA256:
`fe41b8cbdcd9e6c4a28c24ca2c5220f067fff3d0f144af1294188779d99526ca`.
Raw CFG traversal reaches all 1571 decoded instructions. Every direct/table edge
is accounted for; the only external tail is 601B93 ->596370. Root reserves 16
local bytes, saves EBX/ESI, and saves EDI only for in-range actions. All 25 RETs
are RET 0; the out-of-range shared epilogue does not pop an unsaved EDI.
The fall-through seven-byte LEA at 600AC9 aligns a real twelve-object loop; no
manual padding or EH region is introduced.

| Direct callee | Physical calls | Target contract |
| --- | ---: | --- |
|68A1A0|24|Native compiler FTOL, implicit x87 argument|
|496420|5|ECX owner, key/float half-width/three integer arguments, RET 20|
|435160|16|ECX=this+4, two float arguments, RET 8|
|4067D0|63|cdecl random limit, unsigned conversion at these float use sites|
|435D60|2|ECX receiver, no stack arguments, x87 height return|
|4066B0|1|cdecl direct unsigned MT result in 815|
|64CCB0|4|Seven four-byte stack arguments for an unparented object request|

Virtual sequence selection uses slot 0C. The local signed-WORD call carrier
preserves the observed pushes without changing the shared int-facing selector
implementation. Local stages use the observed ECX/stack/x87 ABI; original owner
class identities and complete layouts remain provisional. Existing declarations,
helper implementations, compiler flags and literal bindings are unchanged.

## Inferred source shape and finite experiments

The SakuyaObject/YukariObject sources are family references only. Komachi's
prefix interleaves its float zero stores and WORD384/386 stores differently.
All supported actions are independently reviewed, including 811's real fallthrough
to 800,815's direct MT modulo 360, physical positive/negative RNG tails and 902's
runtime match-identifier dispatch through the existing 6FA894 binding.

The first complete comparison exposed two missing source facts:902's second
object request updates **payload[2]**, not payload[1];930 must select a sequence,
write BYTE17C=2 and clear BYTE113 at sequence 0 and generate twelve objects only
at sequence 1. Raw stack/edge evidence corrects both. The second 902 payload is
statically verified from its real stack store; the native prefix does not claim
to execute past the first spawn.

Repeated float multiply/spill/reload/add/spill sequences establish a real
rounded intermediate in 810/812/850/853/854/856/901/902. Capturing the product as
float before adding reproduces both instruction widths and rounding. Numeric
random bounds, signed WORD guards and all target-retained physical helper calls
remain explicit. No inert locals, register forcing, fake returns, assembly or
copied target byte arrays are used.

| Private trial | One evidenced question | Complete payload |
| --- | --- | --- |
|00|First complete source, before the 902/930 coverage corrections|6484, SHA b5204fb3...|
|01|Correct 902 third component and 930 selector/guard from actual stores/edges|6540, SHA 9a5c4ee1...|
|02|Use native 817 unsigned <=49 guard rather than equivalent <50|6540, SHA 0ae4c031...; native immediate/branch recovered|
|03|Reverse 817 source addition operands|Byte-identical to 02|
|04|Order nested 902 cases 480/300/240 as their target physical blocks|6540, SHA 732ea433...; all 324 metadata bytes now equal|
|05|Express 817 through the consumed scale's compound assignment|Byte-identical to 04|

Keep 04. Both arithmetic-spelling controls are neutral, so park the operand/
register residual and switch to another complete representative. Do not repeat
these controls without new independent evidence.

## 2026-10-25: input-publication and complete same-owner context controls

The newly complete KomachiObject update 5F9420 provides a real same-owner
context, without making its nonexact source authoritative. A fresh bounded
preflight verifies the Japanese 1.06a PE and tracking; IDA still rejects the GUI
executable, so all new instruction reads use the hash-attested PE. Fresh formal
initializer replay reproduces full 6540/732ea433 and exactly the same seven
unmasked differences. No source/header/profile is changed in the selected unit.

Raw 600422 reads the input pointer before the 60042A BYTE184 publication, then
600431 loads input[2] for FTOL and the virtual selector. An isolated truthful
source control captures that actually consumed pointer before the flag store.
It emits the complete same 6540-byte canonical payload, first+0x93, seven
differences. The compiler already represents that source epoch without changing
the EAX/ECX choice; this is not a reason to force a register.

A second control compiles the complete existing update first and initializer
second, in their target address order, with one pointer-only primary interface.
Slot 28 and slot 3C remain fixed by the 6C6004/6C6018 witnesses. The common header
retains reviewed narrow selectors and all actually used update slots. The
shared spawn call view uses the initializer's existing unsigned-byte formal;
the update supplies its actual zero-extended BYTE104 value. Earlier native
provider evidence supports both low-byte/word carriers, without recovering the
original nominal parameter type. No object is instantiated, helper body copied,
opaque call replaced or calling convention changed.

The two definitions own distinct COFF text sections: update section 5 has 29060
bytes/1004 relocations, and initializer section 90 has 6540/284. The initializer
still canonically reproduces 732ea433 with the same seven differences. The
context update is unselected, and neither its bytes nor the whole TU receive
acceptance. This test supplies actual complete-body context; it does not prove
that the original methods shared a TU or that all compiler contexts are closed.

| New control | Initializer full bytes | Canonical SHA256 | Differences |
| --- | ---: | --- | ---: |
|Input pointer captured before BYTE184|6540|732ea4336323b83634f7669c6c8299ef3576f584dcdcf2970331514778ffa5b9|7|
|Complete same-owner update/initializer TU|6540|732ea4336323b83634f7669c6c8299ef3576f584dcdcf2970331514778ffa5b9|7|

The normal `scripts/audit-komachi-object-entry.py --object OBJECT` command replays
the initializer's complete section for either object. No bytes are masked. Accepted
units and aggregate counts do not change; no fresh native matrix is claimed. The
earlier eight-input witness retains its scope.

Both new questions yield identical complete initializer output. Close these
pointer-publication/common-owner controls unless independent evidence changes
the question. Keep the selected source unchanged and select another complete
large representative. IkuObject632C30 is a source-missing provisional 33617-byte
slot 28 candidate; its same-owner initializer 63B310 already has independently
accepted complete source. That is a reason to review this family next, not
permission to inherit its boundaries, fields or exactness.

## Eight scoped native controls

`scripts/audit-komachi-object-entry-paths.py` uses the original PE vtable,
checked one-node action tree, four linked sequence blocks and valid untextured
frames. Selector 45C390, map find 45C320, frame application/commit, FTOL, random
roll and MT helpers execute original instructions. Only resource/RNG **data**
is supplied; no target code, vtable entry, helper return or result is replaced.

A deterministic state fixture has MT index 0 and first state word 1013904223,
with words 1..623 set to their indices. The first real roll(15) yields 9 under
the target's quotient-based range policy. This is a selected state fixture,
not a claim about the game's startup seed. Captured RNG index, full receiver,
call trace, stack cleanup and x87 control/top/tags are compared.

| Question | Inputs | Stop / observed result |
| --- | --- | --- |
|930 generation guard|selected sequences 0,1,2,3|Only 1 reaches the first real spawn; others complete RET 0|
|902 initial request|sequence 0|Actual 64CCB0 entry with payload{0,0,2} and unchanged coordinates|
|810 product rounding|sequence 2 at x87 CW027F and 037F|Both scales have bits 3FF33334 after rounded 0.1f*9 then+1|
|817 consumed scale|sequence 0, finite heading 37.25|Native four-roll path completes RET 0 with matching receiver/RNG state|

All 8 pass: six real RETs and two pre-spawn prefixes. The real spawn body and
all later gameplay are outside those two prefixes. Vector SHA256:
`7e0fdd6afcf76467d514adf60451f7ce1063c378fa4d38237e40224e360546a8`.

The private unguarded930 negative fails 3/8 (sequences 0/2/3), canonical SHA
`269c208659964beccff740e7e4ff001259102266227ca946ae54ddb8accc3422`.
Removing the intermediate product rounding fails 2/8 (both 810 control words), SHA
`b1fe7c36363c589279d8ac796df3645cbb3539188251ade9289166d689018ef7`.
The latter yields 3FF33333 instead of target 3FF33334. These controls establish
the specific guard/rounding facts, not whole-function behavioral equivalence.

## Safety, durable state and remaining work

IDA preflight still fails on GUI SHA 10350095..., so that session supplies no
semantic or write evidence. One direct Ghidra run is limited to CPU 0/nice10 and
384MiB heap. File/import SHA, image base/entry, raw-backed mapped sections and
root SHA are independently checked. Temporary bounded root/helper metadata and
CALL_RETURN override for the actual 980 jump are read back and rolled back.
All nine primary database pins compare unchanged. Decompiler output remains a
hypothesis; raw target instructions determine every accepted storage width,
edge and float-rounding boundary.

Durable changes comprise the complete source/header, source/name/function
ledgers, one focused unit, full-payload/native audits and this evidence/handoff.
No new literal keys or shared accepted headers are changed. Original source
spelling, nominal owner layout, original TU/link context and the two residual
instruction choices remain unknown. Preserve this checkpoint and select a new
complete medium/large authored representative next.
