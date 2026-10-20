# ReimuObject original lookup returns and direction consumers

Historical checkpoint at3d3486d. Current source pins and the999-only x87
cleanup ownership are in [the999-tail checkpoint](REIMU_OBJECT_999_TAIL_2026_10_20.md).
The two direction consumers below remain preserved.

## Result and limits

Root496540 remains nonexact over its complete46138-byte physical extent.
This checkpoint recovers two complete32-byte post-lookup consumers in869
and901. Both byte strings agree without relocation masking.128 finite
witnesses execute the original406360 lookup, observe its actual table read
and return, and agree on x87 comparison status, direction byte and admitted
prefix outputs. This is bounded diagnostic evidence, not root acceptance or
new authored-byte credit.

**Observed:** original406360 returns through x87 after `FLD DWORD PTR
[EDX*4+6FE8B0]` at4063B9. Both root consumers compare that result with zero
and write byte33C through ESI. Selected caller-side float declarations plus
ordinary explicit if/else assignments reproduce both entire consumers.

**Inferred:** float is a supported caller-side return model. An x87 return
and a32-bit table load alone do not establish the original C++ return type.
The existing exact57-byte435160 caller also uses the float model. Neither
consumer equality nor that helper proves original lookup/TU ownership.

**Unknown:** original406360/4063D0 source declarations and standalone compiler
boundaries remain unresolved. AngleLookup.cpp retains its unverified double
definitions, and neither lookup has an exact acceptance. This checkpoint
does not claim a globally consistent recovered C++ API. Root void, remaining
RET sharing, two buffer slots and source/register/TU context remain open.

## Exact target observations

All observations use original Japanese1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The main39853-byte candidate remains provisional. Owned ranges are unchanged:
`[496540,49D169)`, `[49D170,4A00ED)`, `[4A00F0,4A197A)`.
Strict comparison covers46128 owned bytes and10 alignment bytes. Its target
SHA256 is `399e56d3f1373e76381cafb17e4984845fdb1f680dc0737f864229b52f84e31d`.

|Action|Target lookup CALL|Target consumer|Selected native consumer|
|---|---|---|---|
|869|49C581|[49C586,49C5A6)|[805A1E,805A3E)|
|901|49CF12|[49CF17,49CF37)|[80641C,80643C)|

The consumers execute FLDZ, caller stack cleanup, FCOM ST(1), FNSTSW AX,
FSTP ST(1), TEST AH and local conditional branches followed by separate
immediate byte stores of255 and1.869 uses mask41/JNE;901 uses mask05/JP.
Each window is32 bytes; no external branch or relocation field is masked.
Their SHA256 values are respectively
`3e83dea5944bc242c032ece0ed1a6dcf87ccde5c087c66540e3dd78b70d056bc`
and `add0fbb693e0195dd54bfe1a4f446f00c58789f31a0c7133aadf583b42629e8a`.

The root retains the real4963A0 phase-counter definition in a distinct
natural COMDAT:27 root REL32 references resolve to that actual same-object
definition. Its unchanged66 bytes remain canonical
`ad12b782ed5fc99007456fc66a9615951cee34178850a308316409c5245bb156`.
The preceding801/852 selector separation and actual45C390 return witnesses
remain valid at target496AC1/49B02A and source8004B0/8048F1.

## Source controls

All builds run serially on CPU0/nice10 with ordinary vc8-sp1-probe-o2,
default FP and GS off. No flag, layout, helper body or target patch changes.

|Control|Root canonical bytes / SHA prefix|Consumer result|
|---|---|---|
|1cce7b1 double/ternary baseline|45672 /1fa159af|two29-byte consumers, different FP status|
|Actual4963F0 release body before/after root|45672 /1fa159af|root byte-identical; release43/43, counter66/66|
|Float declarations only|45676 /55e87913|FP status agrees,29-byte register/store merge differs|
|Double declarations plus explicit stores|45672 /0884a576|32-byte extents, FP instructions/status differ|
|Double declarations plus explicit consumer casts|45688 /29f5380f|extra float spill/reload,37-byte extents|
|Float declarations plus explicit stores, selected|45676 /29bd8253|both32-byte consumers agree|
|Consistently-float complete Runtime source inclusion|45676 /0f896ace|different root;57/62/66/73 helpers exact|

The real4963F0 release control reads338, destroys via430080, deletes via6898EA
and clears338. Visibility in either order has no observed root effect; it is
not added to the selected TU. The actual release body remains43 bytes, not48.

A consistently-double Runtime inclusion with an explicit cast at435160's sine
consumer still makes that helper65 bytes/nonexact at+39; the earlier no-cast
control differed at+38. The other62/66/73-byte helpers stay exact. These
controls do not justify changing accepted Runtime declarations globally.

The selected root changes only its two lookup declarations and the869/901
direction assignments. The root-specific manifest/exporter now admit the two
float YAMM aliases, already used by the exact435160 unit, at the same physical
406360/4063D0 targets. Legacy YANM double aliases remain for qualified negative
controls. Thus27 typed REL32 keys denote25 physical targets;121 DIR32 and20
scoped literal mappings are unchanged. Neither alias is a prototype proof.

## Actual original-code witnesses and sensitivity

`scripts/audit-reimu-object-direction-returns.py` independently locates one
physical sine consumer for each singleton869/901 owner. It validates the
actual32-bit table-read instruction, full consumer bytes and local branch
boundaries. The inherited World census must retain all25 direct-callee
partitions,29 indirect memberships,99/99 World sites and the shared tail.

For each side it observes actual original406360 entry, real argument word,
EDX table index and loaded table word, actual continuation, AX comparison
bits masked by4500, and final byte33C. No lookup return or table value is
injected at a call frontier. The existing deterministic lookup initialization
fixture is pinned separately; nonfinite/unordered hardware is not claimed.
Input angle and initial direction are legitimate object fields set before
the root's first instruction. Opaque calls stop without fabricated returns.

The128 cases cover869/901,16 finite heading parameters around signed zero,
negative angles and selected quantization/quarter/half-turn boundaries,
counter0/1, and actual RET versus first-World paths. Their input SHA256 is
`df91efb7372b370a2c8d777f13dde3a639380fcf340bf64f174f3b5f0fff6029`.
Selected results: zero prefix/event differences,64 RETs and64 World frontiers.

|Action|AX&4500|Direction33C|Count per side|
|---|---|---|---|
|869|0000|255|30|
|869|0100|1|20|
|869|4000|1|14|
|901|0000|1|28|
|901|0100|255|28|
|901|4000|1|8|

Four compiled full-root negatives run the identical128 inputs. All retain
zero final prefix differences, but all are rejected by complete consumer
bytes. Baseline and double/explicit-store controls also produce106 comparison
event differences; float-only and double/cast controls produce none. Therefore
final outputs alone would fail to detect important instruction/status errors.
Object-only audits explicitly retain build_provenance_verified=false and
original_lookup_cpp_return_type_proven=false. Formal source/COFF receipts are
separate evidence.

## Frozen selected checkpoint

|Artifact|SHA256|
|---|---|
|Root CPP|`fd0916feef53d8cd59d3b574d66c28ac658b29baae3b515a6ac02ee8372556d7`|
|Unchanged root header|`6f469e6886959fd41ee6976b3c784c3df0c2e753ad4729a536764a3c8cd28b4b`|
|Canonical45676 at496540|`29bd825349ad074a07564d5a7c62f7910ae11af7e5ba29e0af245737013da6a9`|
|Native45676 at800000|`b4a79843155434f480d6e5634305844523e3618c338a81eb17a8af0d6872bac5`|
|Frozen tested COFF|`ef533d004c52f10151b754855c8f978c9a859024cac736eb12eb58f768b168f3`|
|Direction audit|`1961c95ed1c900ce0b68e32b3e61324072b0a649cc2a2f7a9aba2bcc9b251b29`|

The root emits44808 code-prefix bytes plus868 metadata bytes,10379 decoded/
10374 reachable instructions,404 direct/29 indirect calls and61 RETs.
Target closure has10670 instructions,404/29 calls and68 RETs. The natural438h
frame and first31 bytes remain; strict mismatch stays49655F/+31 and owner
instruction/edge diagnostics0/43. No exact/remote_exact root row is created.
The existing801/811 join remains. World/RET is target499DF8/499E0E and now
source80AA44/80AA5A; the entire18-byte shared post-call tail is unchanged.

Actual first-World pointers over19 witnesses retain12/14 distinct buffer
slots.822 health remains targetF+190/sourceF+1A0 and900 completed sequence0
remains targetF+164/sourceF+104. Those pointers do not establish full buffer
lifetimes after an opaque World return.

Frozen full-input execution passes0/133192, unchanged SHA256
`f46a849ff57f64bb16e77fd0e28f7f51eee7238501c04049add99e7f77fc3b8b`.
Target/source visit9215/8953 instructions. Endpoints remain119356 RETs,10422
World,915 secondary setup,1151 owned-spawn,26 effect,114 wave,472 parented
spawn,112 CRT errno and624 CRT quiet-NaN frontiers. Source/header, support,
frozen COFF and native pins agree before/after. No opaque return is invented.

All18 serial negative/owner/runtime commands finish with expected exits. The
3360-input animation matrix visits all22 sites and retains the two actual
selector2 witnesses.812, World540+180/four-joint,900,901,804,selector,808/812
caller, orientation400,alpha1170 andterrain288 checks pass. Terrain remains
240 finite equal plus48 hardware-unqualified nonfinite contexts. The oriented
435160 unit separately replays57/57; selected4963A0 remains66/66. Runtime
4351C0/64CD00 source and acceptance are unchanged. Floating relocation audit
retains349 ledger literals,775 mappings and1124 actual target references.

The final formal rebuild after ledger edits emits COFF SHA256
`7f25b86e7e6c9d11a3356e96beb5a17e487012e6a83d1772df1a027609980d83`.
Only bytes4/5 inside the COFF timestamp field differ from frozenef533d00;
all other object bytes are identical. Canonical root/helper hashes stay
29bd8253/ad12b782. Runtime reports deliberately pin the frozen tested container,
not the later timestamp. The mixed build has the expected nonzero comparison
exit because the root is nonexact; its accepted66-byte helper remains exact.

## TH075 read-only corroboration

The user-suggested `/home/pentester/coding/codex_ida/th075-reconstruction/th075`
repository was read without changes, builds or database use. Its HEAD was
`a57b43e32b9f30dd500c730c3f78a8d897be73c5`, and
`probes/VC7MathTablePolicies.cpp` SHA256 was
`e70996e475d9c2a328d99cdeeccb6927b44a7f468b71a2f10d29d05c33206fa4`.
That retained source model uses a float3600-entry table,10x scale and900 phase
shift. These are useful external source corroboration, not TH105 type,
compiler, boundary or exactness evidence. No TH075 executable is attested here.

TH075's retained policy truncates the scaled float before integer absolute
value. TH105's actual100/94-byte lookups instead use a64-byte-aligned frame,
float scaling/rounding, external fabs68BAAE, further float stores/reloads,
addition of0.5f before68A1A0 conversion and signed remainder3600. Transferring
TH075's truncation/absolute-value order would be wrong here. The original
reason for TH105's frame alignment and its C++ return declarations is unknown.

## Reproduction and next work

Receipts/controls stay below `build/reimu-object-cleanup-context-20261020`;
private regeneration recipes stay in its matching `.analysis` scope. Nine
primary Ghidra database hashes are unchanged; no Ghidra process or metadata
write is used in this unit. IDA's wrong executable contributes no semantics.
No aggregate cold replay or new percentage is claimed.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-reimu-object-action-state --compare --json
# Expected mixed result: root496540 mismatch+31, helper4963A0 exact66/66.
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-direction-returns.py build/match-units/GptWeb_ReimuObjectActionState.obj --output build/reimu-object-cleanup-context-20261020/direction-replay.json
taskset -c 0 nice -n 10 python3 scripts/build.py --unit cross-v106a-character-runtime-oriented --compare --json
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-animation-sites.py build/match-units/GptWeb_ReimuObjectActionState.obj --output build/reimu-object-cleanup-context-20261020/animation-replay.json
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-scalar-actions.py build/match-units/GptWeb_ReimuObjectActionState.obj --final-actions --output-dir build/reimu-object-cleanup-context-20261020/full-replay
python3 scripts/check-match-literals.py --require-target
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Continue remaining target RET ownership and the822/900 first-World buffer
slots while preserving the recovered selector/lookup consumers and accepted
helpers. One concrete next lead is the final epilogue: target4A196B/4A196D
contain FSTP ST(1)/FSTP ST(0) before RET4A1979, whereas the default uses
RET4A196A. The selected default shares plain RET80AF05 with all41 concrete
action memberships. Recover incoming x87 stack depths and edges before
further source join controls; RET membership alone does not prove equal
cleanup requirements. The remaining membership receipt is diagnostic only.
Returning opaque graphs, arbitrary aliases/resources/vtables,
nonnull rendering, unmasked exceptions and48 terrain nonfinite hardware
contexts remain open. Preserve Fighter478FA0 and initializer4A1CE0. No
standalone-root match or LTCG impossibility is asserted.
