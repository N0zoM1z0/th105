# Effect manager virtual spawn

`CEffectManager<T>::spawn_effect` is virtual at primary vtable offset `+0x0C`.
The previous declaration omitted `virtual`, shifting every later slot in a
newly generated table. The declaration now matches the original dispatch
layout, and the InfoEffectObject implementation is the corresponding template
specialization rather than a separate manager facade.

The Japanese TH10.5 1.06a image has four matching nine-slot primary tables:
CSelectObject `0x6C08E0`, WeatherEffectObject `0x6C1418`, EffectObject
`0x6C1490`, and InfoEffectObject `0x6C37C0`. Their spawn slots point to
`0x422FB0`, `0x4377C0`, `0x437C00`, and `0x46F460`, respectively. The
fresh VC8 object emits the same slot roles in all four tables. Its primary and
secondary RTTI graphs, including the secondary-base adjustment, were checked
against the original image; the four secondary destructor thunks also replayed.

All four complete spawn bodies and the four manager constructor/destructor/
scalar-deleting-destructor families remain exact. Relevant manager virtuals,
tracked-object operations, event/effect users and Select's exact neighboring
functions were compared. The already nonexact event initializer, Select
constructor and update/prune helper retained their existing residuals. The 56
emitted manager EH symbols and their relocations were unchanged between builds
before and after restoring `virtual`; that is a before/after check, not an
independent comparison of every EH byte against the executable. No new exact
function is counted for this change.

The event/weather forwarding path now calls the actual virtual spawn on its
`CEffectManager<WeatherEffectObject>` member, rather than a second polymorphic
emitter facade. The returned value is a WeatherEffectObject pointer; the two
integer flags are passed to the spawn method as their low bytes. This preserves
values such as -2 as byte 0xFE. The complete event forwarder `0x4695B0`,
global forwarder `0x665470`, weather emission `0x660B30`, and the affected
event-state lifetime/runtime roots remain exact.

The layer forwarder `0x4695F0` now uses the same real weather manager's
`render_effects_for_layer` virtual at `+0x18`. The three battle-render phases
call it through the shared event state, with layers -2, -1 and +1. The complete
forwarder and all nine previously exact battle-object-manager peers remain
exact; its background-update peer retains its prior nonexact hash.

Battle info records also hold the InfoEffect manager at `+0x14`. Their group
emitter now calls the actual manager's virtual spawn instead of a generic
emitter facade. This exposes the correct owner and byte-sized flags, but does
not solve `0x46F9F0`: the revised candidate is 61 bytes against the 85-byte
original and remains nonexact. Its five directly affected normal/story binding
and forwarding functions remain exact.

The info-effect forwarding path similarly uses the real
`CEffectManager<InfoEffectObject>` at owner `+0x04`. Its `0x46E9D0` wrapper and
`0x6609C0` global forwarder now return the spawned object pointer and pass the
two flags as bytes. Both remain exact, as do their event and pair-mode callers.
The existing InfoEffect update candidate remains nonexact with its prior hash.

The InfoManager resource loader and release wrapper now use its actual
`CEffectManager<InfoEffectObject>` virtual methods at `+0x04` and `+0x08`.
The release wrapper is `void`: its sole direct target caller ignores EAX, and
the tail-called manager clear method is void. Both wrappers, normal/story
lifetimes, story initialization and record initialization retain complete
exact comparisons.

The InfoManager and its battle-info records now share the actual
`CEffectManager<InfoEffectObject>` type, including the embedded 0x94-byte
manager in the normal runtime view. This removes the three-slot facade and
padding that previously obscured their common owner. All 27 previously exact
functions in the affected resource, lifetime, initialization, render and gauge
units still compare exact. The two previously nonexact update candidates remain
nonexact: Story retains the same first mismatch, while normal update retains its
existing unresolved local deque relocation.

## Shared typed spawn state, 2026-11-10

The Select, Weather, ordinary Effect and InfoEffect spawn implementations now
share `EffectSpawnObjectView.hpp`. The observed virtual slots and seven state
fields are declared once, with offset assertions for position EC/F0, facing
104, manager anchors 130/160, context 164 and spawn flag 16C. The InfoEffect
nominal view remains a declaration-only derived view, preserving the existing
pool-return type without duplicating the virtual protocol or raw accessors.
No view is allocated, and unknown regions remain opaque.

The order of publication is unchanged: context and manager anchors precede the
virtual action setter; position, facing and spawn flag follow it; finalization
is the last virtual call. Context remains the spawn API's integer token here,
not a guessed complete object type. The object-specific update views retain
their independently observed interpretations.

Fresh serial builds preserve all five exact roots: Select 422FB0, Weather
4377C0, ordinary Effect 437C00 and InfoEffect 46F460 are each 115/115 bytes;
InfoEffect resource/preallocation forwarding 46F900 is 30/30. The three-family
COFF contents and relocations are identical. The InfoEffect object differs
only by removing seven obsolete 7-byte address-accessor COMDATs and their
compiler debug records; all remaining contents and relocations are identical.

Only these two units consume the changed inputs. This preserves local exactness and
adds no new Factory acceptance.
