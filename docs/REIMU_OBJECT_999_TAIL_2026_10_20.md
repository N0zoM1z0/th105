# ReimuObject999 independent guards and x87 cleanup

> Historical experiment record. Its pins, selected source and next steps apply
> to that checkpoint. Use [the current handoff](RE_HANDOFF.md) and
> [evidence index](REIMU_OBJECT_EVIDENCE.md) for current state and ABI limits.

Historical checkpoint atcc8eafd. Current source pins and the850/853/854
recovery are in [the fade-order checkpoint](REIMU_OBJECT_FADE_ORDER_2026_10_20.md).
The999 guards and windows below remain preserved.

## Selected recovery

Root496540 remains nonexact. The selected change replaces999's combined
sequence1-or8 guard with two ordinary independent guards and their real
field assignments. This follows two separately encoded target condition
chains. It naturally restores both constant lifetimes, both store groups,
a separate default RET and the final x87 cleanup. No locals, padding,
assembly, flags, bindings, layouts or helper bodies are added for shaping.

**Observed:** original999 checks144/142/140/13E twice after its actual4351C0
animation call. Sequence1 and sequence8 each have their own assignment group.
The15.0f and0.2f values stay on the x87 stack across those guards.792 admitted
original-code witnesses agree on actual animation entry/return fields,
executed comparison operands, logical x87 values/depths, writes and real RETs.
Both physical store groups execute. Four separate opcode windows agree
without byte masking; this is80 diagnostic bytes, not accepted authored credit.

**Inferred:** separate source statements explain the duplicated guards and
floating lifetimes. This does not establish the original source spelling or
TU. The original root C++ return type remains unproved; source void is still
an inference. Original lookup return types remain unproved as documented in
the preceding direction-return checkpoint.

**Unknown:** target zero comparisons use immediates while source uses the
observed-zero EBX/BX registers. Full guard/branch bytes still differ. Other
RET ownership, register placement, source/type/TU context and two first-World
buffer slots remain open. The full root receives no exact/remote_exact row.

## Exact target and edge facts

All observations use original Japanese1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The candidate39853-byte main span remains provisional. The strict comparison
still covers all46138 physical bytes through4A197A, with46128 owned bytes and
10 alignment bytes. No boundary or ownership change is made here.

The previous common-RET lead needs a narrower interpretation. FSTP ST(1) at
4A196B and FSTP ST(0) at4A196D have only999 membership. All other concrete
actions branch directly to4A196F, skipping those instructions. Their common
RET4A1979 has41 memberships; that does not mean41 actions use x87 cleanup.
The default has its own4351C0 call4A195B and RET4A196A.

Only five encoded incoming branches target4A196B:4A18DC,4A191C,4A1926,
4A1930 and4A193A. The second counter check is statically present; no claim
is made that every encoded edge is dynamically feasible without races or
aliasing. Incoming depths/fields are observations, not a race model.

A9533-input sample of the previous source/target prefix matrices has zero
output differences, input SHA256
`7762a5014dc84bfbaa836982031b3b7acd98fdda0d53f888e67a661927b9e667`.
It observes140 target visits to the x87 cleanup, depth2/TOP6 before the first
pop, depth1/TOP7 before the second, then empty/TOP0. Ordinary target entries
at4A196F already have empty stacks. The previous source shares plain80AF05
across all42 entries and has no counterpart to the999 cleanup. These sampled
prefixes and static edge reports explain the next source experiment; they
are not a full-input replay of the new source.

## Compiler control and selected windows

The immutable3d3486d source is the negative baseline. Its one OR guard has
five field comparisons and one three-store group. The selected two-if control
has eight field comparisons and two three-store groups. Both compile serially
on CPU0/nice10 under unchanged vc8-sp1-probe-o2, GS off/default FP.

|Property|3d3486d baseline|Selected independent guards|
|---|---|---|
|Canonical section tail|45676 /29bd8253|45744 /b3ba8c1a|
|Code prefix / metadata|44808 /868|44876 /868|
|Decoded / reachable source instructions|10379 /10374|10397 /10393|
|Direct / indirect calls|404 /29|404 /29|
|RET sites|61|62|
|RET membership multiset distance|31|28|
|Owner instruction/edge diagnostics|0/43|1/43, final physical region|
|Default / common return membership|one combined42-way RET|separate default and41-way RET|
|Same-object4963A0 helper|66/66 exact|66/66 exact|

The distance is a diagnostic count, not an exactness score. All25 direct
callee partitions and29 indirect memberships remain. The real4963A0 body
remains a separate natural COMDAT referenced27 times by the root. Its canonical
SHA256 stays `ad12b782ed5fc99007456fc66a9615951cee34178850a308316409c5245bb156`.

The identical diagnostic owner is actions:802, a31-byte physical region
`[4A195B,4A197A)` versus `[80AF2D,80AF4C)`. It contains the default call/RET
and the999 cleanup tail. Physical owner equality does not assign that cleanup
to the semantic default action, and normalized call/edge diagnostics are not
a canonical full-function match.

A further private control makes all of the consistently-float Runtime source
visible alongside these recovered guards. It preserves57/62/66/73 exact helper
bytes but emits a different45744-byte root, canonical7fc05b07/nativee2518f31.
It still has62 RETs, distance28, and the same EBX/BX zero comparisons. All25
direct and29 indirect memberships remain; it does not resolve the current
register/RET residual and is not promoted. Original source partition remains
open rather than inferred from helper equality.

|Window|Target|Selected native|Bytes|
|---|---|---|---|
|Two adjacent constant loads|[4A18D0,4A18DC)|[80AEA7,80AEB3)|12|
|Sequence1 stores with FXCH|[4A18FF,4A1915)|[80AED4,80AEEA)|22|
|Sequence8 stores and RET|[4A193C,4A195B)|[80AF0E,80AF2D)|31|
|x87 cleanup and common RET|[4A196B,4A197A)|[80AF3D,80AF4C)|15|

The source default now calls at80AF2D and returns80AF3C; its plain common
epilogue starts80AF41. Guard encodings and branch distances around these
windows remain different. The constant load operands use actual verified
target literal addresses6C3EA0/6C3CC0; no relocation field is masked.

## Public original-code audit

`scripts/audit-reimu-object-999-tail.py` finds the singleton999 animation call,
checks the two field/width guard chains and store groups, compares the four
windows, and executes actual original4351C0 plus its animation callbacks.
It observes the original callee entry/continuation and fields13E..147,
comparison operands, logical x87 register words, field writes, real RET,
callee-saved state, empty final x87 stack and unchanged control word.
Opaque entries stop without fabricated returns. World's inherited census
must also retain all25 direct partitions and29 indirect memberships.

The792 inputs combine11 sequences, counter/timer-1/0/1, frame0/1, both27F/37F
control words and normal/terminal animation fixtures. Counter and timer-1
are necessary witnesses: the actual animation helper increments both before
the guards. A preliminary352-case domain lacking these inputs visited no
stores; it is superseded and is not claimed as assignment coverage. The
finished audit requires both store groups to execute on both sides.

Final input SHA256 is
`65dac03da7ec4fd26326e3b1f28ba4ecd7ab7e322586ff0e4dddad5e38bd6963`.
Selected results have zero prefix/event differences,792 actual animation
entries/returns,1848 executed field comparisons and792 real root RETs.
There are24 observed stores per side:12 writes in each physical group, each
group exercised four times.788 paths use explicit x87 cleanup; four sequence8
successes pop their values through the stores. Both normal control words pass.

After the loads, TOP6/tags0FFF contain logical ST0=0.2f and ST1=15.0f. Their
observed extended words are `(CCCCCD0000000000,3FFC)` and
`(F000000000000000,4002)`. At the cleanup exit TOP0/tagsFFFF is empty.
No unordered/nonfinite or unmasked-exception hardware behavior is inferred.

The compiled previous full-root object is a negative control. It still has
zero final prefix differences on these792 inputs, but differs in all792
event sequences and fails the guard/window/coverage gates. It executes1144
guard comparisons, has constants-live events only eight times, and merges
all24 writes into one physical group. The new checks reject it/exit1.
Object-only reports retain build_provenance_verified=false and
original_source_shape_proven=false; formal build receipts are separate.

## Frozen selected checkpoint and regression

|Artifact|SHA256|
|---|---|
|Root CPP|`a784a2747eab6a64ea60e903da46a7b5542a3d0142b24efe01127b1233ac8a8e`|
|Unchanged header|`6f469e6886959fd41ee6976b3c784c3df0c2e753ad4729a536764a3c8cd28b4b`|
|Canonical45744 candidate|`b3ba8c1ac6674ddfbbb7cab994e5e28ff6fd73af7facb38b4d1ecd95410e2ff5`|
|Native45744 at800000|`08a27d2a427e85de416c8bb592a2cf226796f9d08d6086379e1f6c7ba5d1f5bf`|
|Frozen tested COFF|`7c15116ec3f08e68800dca8aa66968a4c5b665f4cb59dd9387869e8456e57ced`|
|999 audit|`97b666852befb8bda0cb45054aee4fd79c81f0ee96649b2370b9eac23a138618`|

The natural438h frame and first31 bytes remain. Strict full-root mismatch is
still49655F/+31. No selected helper/source-layout/compiler-profile/relocation
or ownership change is made. Frozen full-input execution
passes0/133192 with unchanged input SHA256
`f46a849ff57f64bb16e77fd0e28f7f51eee7238501c04049add99e7f77fc3b8b`.
It visits9215 target/8967 source instructions. Endpoints remain119356 RETs,
10422 World,915 secondary setup,1151 owned-spawn,26 effects,114 wave,
472 parented-spawn,112 CRT errno and624 quiet-NaN frontiers. Source/header,
COFF/native and full-emulator support pins agree before/after.

All17 initial selected/negative/owner/runtime commands end with expected
exits. The869/901128-input direction audit and3360-input animation/actual
selector witnesses remain green.812, World540+180/four-joint,900,901,804,
selector,808/812 caller,orientation400,alpha1170 andterrain288 pass. Terrain
retains240 finite equal and48 hardware-unqualified nonfinite contexts.
First-World pointers across19 witnesses still agree12/14 distinct buffers:
822 health targetF+190/sourceF+1A0 and900 completed sequence0 targetF+164/
sourceF+104 remain different. Those pointers do not establish full lifetimes.
Floating relocation checks retain349 literals/775 mappings/1124 references.

The17-command driver pins the initial999 audit8fd81f82. Subsequently its
standalone load check is strengthened to read the entire constant-load
address span, preserving any intervening bytes rather than concatenating
two encodings. Both792-input selected and rejected-previous-object checks
replay under the current97b66685 audit hash. The full native emulator, root
source, header and tested COFF are unchanged. Historical driver pins are
retained; final audit reports carry the current support hash.

The final formal rebuild after ledger edits has COFF SHA256
`649611b4938a0b4d4675209210a87f3006b2bd8b34fd86accebc41ba891f84ca`.
It differs from frozen7c15116e only at COFF timestamp offsets4,5;
all other bytes are identical. Root/helper canonical hashes remain
b3ba8c1a/ad12b782. Runtime receipts pin the frozen tested container rather
than the later timestamp. The mixed comparison has the expected nonzero
exit for the root mismatch; its accepted66-byte helper remains exact.

## Receipts and next work

Generated receipts and controls stay under
`build/reimu-object-x87-cleanup-20261020`, private recipes under the matching
`.analysis` scope. All nine primary database hashes remain unchanged;
no Ghidra process or metadata write is used. IDA's wrong executable supplies no
semantics. No unrelated or aggregate cold replay/percentage is claimed.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-reimu-object-action-state --compare --json
# Expected: root496540 mismatch+31; real helper4963A0 exact66/66.
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-999-tail.py build/match-units/GptWeb_ReimuObjectActionState.obj --output build/reimu-object-x87-cleanup-20261020/tail-replay.json
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-direction-returns.py build/match-units/GptWeb_ReimuObjectActionState.obj --output build/reimu-object-x87-cleanup-20261020/direction-replay.json
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-scalar-actions.py build/match-units/GptWeb_ReimuObjectActionState.obj --final-actions --output-dir build/reimu-object-x87-cleanup-20261020/full-replay
python3 scripts/check-match-literals.py --require-target
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Continue remaining RET ownership and real source/register/TU lifetimes while
preserving the999/869/901 consumers and801/852 selector identities. The822
health and900 completed-sequence0 buffer slots remain leads. Returning opaque
graphs, arbitrary aliases/resources/vtables, nonnull rendering, unmasked
exceptions and48 terrain nonfinite hardware contexts remain open. Preserve
Fighter478FA0 and initializer4A1CE0. No LTCG impossibility is claimed.
