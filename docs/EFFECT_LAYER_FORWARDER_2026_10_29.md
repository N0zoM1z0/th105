# Effect render-layer forwarding, JP1.06a

4695F0 is canonical exact11/11, SHA256
10511f679a2f7fed358f1328a022d27e2647458f3bcf5c4a62b3c176e1f2afb3.
The previous10/11 receiver-scheduling stop was based on an incorrect
int-returning/int-parameter virtual contract.

## Independent ABI evidence

Exact EventEffectState lifetime places CEffectManager<WeatherEffectObject>
at owner+48. Its primary table6C1418, already pinned by the exact manager
constructor, contains46F350 at slot18/table cell6C1430. That independently
exact27-byte method is void render_effects_for_layer(signed char). It forwards
the signed layer through the exact checked-list callback64B510 and its
layer-gated object renderer421AE0. This is not a prototype chosen solely to
improve the wrapper bytes.

The three exact callers are BattleObjectManager phases466980,4669F0,466A50.
Their call sites466999/466A3A/466A9A pass layers-2,-1,+1 and consume no return
value. The wrapper tail preserves that stack argument and transfers to the
primary render virtual. Its existing dispatch_emitter_state public name is
retained for compatibility, but the source signature is now void(signed char).
The corresponding EffectEmitterSubobject slot declaration is corrected too.
No field size, virtual slot position or class allocation is changed.

Normal C++ now loads the vptr and slot before adjusting the receiver, exactly
as the target. There is no manual vtable load, register directive or trampoline.

## Focused validation

- Event unit:29-byte id setter,49-byte emitter, new11-byte layer forwarder and
  511-byte background render all exact.
- Actual caller TU: all nine selected roots remain exact, including the three
  phase callers99/83/83.
- Shared emitter facade46E9D0 remains49/49 exact.
- The existing nonexact group emitter46F9F0 remains66/85; no credit or claimed
  fix. A separate private narrow-spawn interface probe is61/85 and unselected.

scripts/repo-python scripts/build.py --unit cross-v106a-event-effect-state --compare --json
scripts/repo-python scripts/build.py --unit cross-v106a-battle-object-manager-runtime --compare --json
scripts/repo-python scripts/build.py --unit cross-v106a-info-effect-emitter --compare --json

Receipts are in build/frontier-effect-emitter-abi-20261029. Only11 new authored
exact bytes are counted. Other wider legacy emitter/spawn contracts are not
silently changed by this bounded signed-layer correction.

A2026-10-30 full exception-sensitive FP control on the existing narrow group
emitter candidate gives63/native85. It does not recover the native x/y local
frame and is not selected. Evidence: build/frontier-effect-fp-exceptions-20261030/.
