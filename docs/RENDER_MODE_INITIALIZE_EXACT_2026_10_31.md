# Complete renderer initialization401430

Original Japanese TH105 v1.06a SHA-256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

initialize_render_mode_manager401430 is canonical exact142/142, SHA-256
763f8ab488bbcfc7cf97b31507dae8ca93f3e2dd028878617e50377aea36d9fc.
All instructions through its true return and final RET are compared. No
prefix, scheduling equivalence or extra helper bytes are credited.

## Observed policy and actual source

The function copies backend device7036C0 into the existing renderer's device04
at6FA220, registers its actual DeviceResetListener base6FA21C, and clears only
clear color30, reset flag2A and state2C. It then calls the backend device's
Clear with flags3, zero color/stencil and depth1, sets renderer device render
state58 to255, then clears stencil with flags4 and zero stencil/depth1.
COM results are ignored and true is returned, as in the native function.
It does not initialize any other renderer state or invent error handling.

Source RenderModeInitialize.cpp uses the existing complete RenderModeManager
header and actual backend-listener/critical-section implementation. Its second
listener caller is the already reconstructed BattleBaseEffect initializer,
not a dummy call: that real source is included and its actual public entry
retained. The single-caller control specialized away the listener argument
and produced137 bytes. Both real callers naturally retain the native argument
and private EAX backend receiver, without a calling-convention annotation.

A separate tail-only source view initially produced142 bytes with different
field-store scheduling. It was not selected. Returning to the existing actual
RenderModeManager type recovers all142 bytes. No field-store recipe, manual
vptr assignment, padding or forced compiler barrier is used.

## External data evidence

The existing listener-base alias retains its actual initialized vtable bytes
30696D00. A separate scoped data witness records the real zero-initialized
fields starting at6FA220, offsets0/38/40/44, corresponding to device04 and
renderer fields2A/2C/30. These are checked target data addresses used during
canonical replay, not additional source-owned storage or a synthetic provider.
The source continues to access the original declared renderer global directly.
The absolute data-binding object allocates no replacement renderer. No old
base-only alias is widened, no object lifetime is claimed, and every field
reference and linked relocation is still validated. No verifier changes occur.

## Validation and accounting

The public exact-first-render-mode-initialize unit passes the new142-byte root.
A separately built strict context replay passes both it and the existing effect
initializer17FF0. The original selected effect unit also freshly passes its
initializer and private listener registration414CB0. Existing source selections
remain unchanged; the public manifest does not duplicate their function rows.
No helper or second-caller credit is added.

scripts/repo-python scripts/build.py --unit exact-first-render-mode-initialize --compare --json

Focused evidence: build/frontier-render-mode-initialize-20261031/.
Default CI210 and whitespace checks pass. No whole-corpus cold rebuild.
One authored function adds142 bytes:1576 exact /448613 bytes;
source1771, authored1791, mapped1798, excluded1658, review578, units756.
