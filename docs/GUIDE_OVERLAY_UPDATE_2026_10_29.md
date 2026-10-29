# Guide overlay update, JP1.06a

43F450 is canonical exact112/112, SHA256
1a00542e8630792db845edd7744e24e311f277c7cb75aa9ef0393ef4ecbcd1d1.
The complete RET-ending section is equal, not just its scroll prefix.

## Recovery of the color call

The existing sprite is a94-byte CSprite with the independently known color
virtual at table+4. The old source used a manually extracted method pointer,
a temporary alpha byte and an assignment inside the final argument. A typed
color virtual alone restores the vtable loads before alpha publication, but
still differs in SUB versus ADD and receiver/shift scheduling:112 bytes with
eight unequal bytes.

Use the actual virtual call separately in the two visibility branches, with
alpha_a4+=15 or alpha_a4-=15 as the color argument's compound assignment.
VC8 naturally merges the call suffix and emits native SUB AL,15, followed by
virtual lookup, byte writeback, zero-extension, shift and receiver adjustment.
No method-pointer forcing, register/volatile state or assembly is used.
The unsigned byte retains wrapping behavior; no saturating clamp is added.
The scroll increment remains double0.5 with float32 publication and the native
strict-greater wrap comparison.

The accepted definition retains GuideOverlay::update and the existing shared
header. A local typed CSprite virtual view replaces manual dispatch; it creates
no sprite, publishes no vtable and changes no caller ABI. The obsolete method
body is removed from GuideOverlay.cpp rather than leaving two definitions.
The new focused unit selects GuideOverlayUpdate.cpp only.

## Focused sibling replay

The changed old TU is rebuilt once: load43F390179/179, render43F4C0124/124,
constructor43F54020/20 all remain exact. Destructor43F330 remains90/92 at+40,
its same handle-load CSE; it receives no new exact credit. Other callers and
shared layouts are unchanged. Only112 new authored exact bytes are counted.

scripts/repo-python scripts/build.py --unit exact-first-guide-overlay-update --compare --json
scripts/repo-python scripts/build.py --unit cross-v106a-guide-overlay --compare --json

Receipts:build/frontier-guide-virtual-color-20261029/formal-update.json and
formal-siblings.json. The latter intentionally reports the known nonexact
destructor alongside the three unchanged accepted siblings.
