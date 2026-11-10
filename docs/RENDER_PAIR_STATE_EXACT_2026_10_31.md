# Renderer pair state: canonical 121 bytes

RenderModeManager::set_pair_state at404940 now matches all121 bytes, SHA-256
d5c4394234d0816a4c8e6855d79042419f8dd746b22d2b5dc16cecf9e6658cc5.
The native body is straight-line and ends in RET8; all five virtual calls and
both cached byte stores are compared, without relocation masking.

The source uses the existing actual RenderModeManager and D3DDevice9 interface.
It unconditionally sends render states27/15 from the two incoming bytes, then
24=1 and25=7, followed by texture-stage state(stage0,type4,value4). Only after
those calls does it publish the cached bytes at owner24/25. Device access is
reloaded naturally at each call; no failure branch or redundant cache guard is
invented. All HRESULTs are ignored, as in the native code.

## Recovering the result contract

The old declaration returned unsigned char, inferred before this body had
source. Both actual users, reset4014C0 at401527 and scene initialize41E070 at
41E09F, discard any result. Native AL at exit merely reflects the final byte
cache publication. A first source honoring the old declaration and explicitly
returning second emits123 bytes, retaining the second argument in BL and
adding an artificial result transfer.

The ordinary void interface removes that unsupported result computation and
naturally emits the exact121-byte body, including native first-argument BL
ownership. This is a source result-contract recovery supported by actual callers,
not a register constraint or an unused scratch lifetime. Original nominal
return spelling is not claimed to be uniquely proven from machine code.
The nonvirtual signature and both caller relocation names are updated together;
arguments and RET8 cleanup are unchanged.

D3DBackend.hpp replaces only the placeholder at existing virtual slot67 with
the three-unsigned-argument SetTextureStageState signature. The slot index,
interface size and all later method positions are unchanged. No source used
the old placeholder name. No manual vtable arithmetic or new device object is
introduced.

## Focused regression

Fresh renderer unit roots52/26/35/66/482/329 and scene unit162/25/5/5 all pass.
These cover both actual users of the changed result declaration. The remaining
shared-header change is a signature for a previously unused slot with unchanged
layout; no unrelated corpus rebuild is needed. Default CI also checks the
complete current manifest and ledgers.

No source or acceptance-tool forcing was used.

Totals: exact1581/449116, source1780, authored1800, mapped1807,
excluded1783/review444, units763. Only this121-byte game function is added.
