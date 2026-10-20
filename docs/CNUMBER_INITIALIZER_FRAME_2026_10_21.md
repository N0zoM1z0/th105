# CNumber initializer frame and closed caller controls

CNumber_initialize at414E40 remains **102/104, nonexact at+0**. Five new
bounded controls reproduce the same entire102-byte canonical initializer;
none explains the target's entry word. No program source, header, ABI,
compiler profile or match is changed. These results supersede the older
unsupported assertion that the residual is merely standalone scheduling.

## Observed target and boundary

Only Japanese TH10.5 v1.06a is used, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Fresh target/status/tracking checks pass; IDA rejects10350095... and supplies
no semantics. No Ghidra process, metadata write or target patch is used.

The complete104-byte linear body is414E40..414EA8, ending in RET40 at414EA5.
Its sole direct call is414E9D to4098E0, whose actual266-byte target ends with
RET28. Exhaustive raw E8-target scanning finds only4442E3, within independently
canonical728-byte CMenuConnect construction. This is direct-call evidence,
not proof against unknown indirect callers. ECX receives the CNumber member;
void remains a source inference because this caller discards the result.
Target function SHA256:
`13610702388b9d375393b8111ba67cdca52de1239b7c724067846239761dd0d8`.

The ten incoming words are texture, left, top, right, bottom, columns,
float spacing, two reserved integers and a low-byte mode. Observed writes
are columns14, reserved18/1C, float(right-left)04, byte mode20, spacing08,
and1.0 at0C/10. The seven-word tile call receives member+28, texture,
left/top, right-left, bottom-top and two zeros. Whether some scalar words
originally belonged to a by-value aggregate is unproved.

Target starts PUSH ECX and ends POP ECX before RET40. Normal-return stack
analysis, using the actual callee RET28, finds no explicit ESP-relative
memory operand addressing entry-SP-4..-1. All such operands address incoming
words at entry-SP+4 or later; the width conversion reuses the right argument
slot at+16. PUSH/POP still save and restore ECX, so the word is not described
as having no machine effect. The reason for its presence remains unknown.
This proof replaces reliance on an unavailable IDA local-variable inventory.

## Complete compiler controls

| Control | Initialize | Render414F10 | Additional result |
| --- | --- | --- | --- |
| Fresh selected SP1 baseline | 102/104 | 312/312 exact | Standalone caller444190 is728/728 exact |
| Four coordinates in a real by-value rectangle | Identical102 bytes | 312/312 exact | Private interface hypothesis only |
| Low-byte unsigned-char mode parameter | Identical102 bytes | 312/312 exact | Private interface hypothesis only |
| Genuine IColor base/virtual signature view | Identical102 bytes | 312/312 exact | Layout is independently supported by the lifetime recovery |
| Actual runtime and CMenuConnect caller in one TU | Identical102 bytes | 312/312 exact | Constructor becomes792/728 nonexact, first+0x4C |
| VC8 RTM, ordinary O2/GS-off baseline | Identical102 bytes | 312/312 exact | SP1 versus RTM does not explain this residual |

Every102-byte result has canonical SHA256
`fcd06b657b11f935b2f8b7a8a9b275a5a1ccbc41c768c732468f633ec0e32f61`.
The private rectangle and byte-mode changes preserve the observed40-byte
stack cleanup; neither declaration is selected or uniquely proved.
The IColor control uses the independently recovered base and actual color
virtual signatures without changing fields or adding a local. All use real
source and ordinary compiler output, without padding, assembly or inert work.

The closed TU consists only of the existing CNumberRuntime.cpp and
MenuConnectConstructorRuntime.cpp. VC8 exposes/inlines more of the real
initializer into the constructor; this is a failed ownership/profile control,
not a replacement accepted constructor. Its initial comparator relocation
failure is resolved with the already-supported4098E0 tile-method binding;
the final complete792-byte constructor report has no unresolved relocation.
No public binding or accepted partition changes. The separate original
constructor's fresh728/728 receipt remains the accepted result.

RTM compiler SHA256 is
`3cbf4306526c06a07d09fd4785ac290c7ac7b52355944e7b377e08f5d8e7ece7`.
The baseline and all controls use the current canonical target, not historical
1.06 reports. The separate render result remains canonical
`81e97825bba4e4de5c56b2873015ddf9f600f9ef64b9498822873213251f2d66`.

## Retained state and unknowns

`build/cnumber-initialize-20261021/` keeps formal baseline/caller receipts,
private source/header/object controls and `facts-summary.json`. Private
recipes are in the same-named `.analysis/` directory. The facts packet pins
inputs, the complete stack-access trace and all five full-function controls.
No numerical native coverage is claimed for these byte-comparison experiments.

Original parameter spelling, local lifetimes, compiler/TU phase and the
unaddressed entry word remain open. The controls rule out their tested shapes;
they do not establish a standalone-compiler or LTCG impossibility. Public
CNumber source/headers, its render acceptance and the accepted caller remain
unchanged. Reimu496540 keeps the preceding811 source and remains nonexact+31.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-cnumber-runtime --compare --json
# Expected exit1:initialize102/104;render312/312 exact.
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-menu-connect-constructor-runtime --compare --json
# Expected exact728/728 on its unchanged isolated source.
```
