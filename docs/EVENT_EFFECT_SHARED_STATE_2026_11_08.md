# Event and weather effect state

The event/effect resource owner has one 0xE8-byte layout: event ID and stage,
resource-handle and sprite vectors, background-entry deque, stage-row map,
weather effect manager, then three float coordinates at `+0xDC/+0xE0/+0xE4`.
The constructor leaves the coordinates untouched; runtime reset clears them.
The background update moves those coordinates toward their targets.

Lifetime, runtime update and resource initialization now share the same
`EventEffectStateData` declaration. The complete constructor, destructor and
three runtime methods remain exact against Japanese TH10.5 1.06a with the pinned
VC8 profile. The resource initializer's existing nonexact candidate hash is
unchanged. The narrower caller interface was subsequently reconciled as described below.

The stage/music wrapper at `0x434DE0` now calls the shared state's actual
`void(signed char)` stage-publish interface. VC8 still emits the exact original
40-byte wrapper, including its full-width argument push. The event-ID setter has since been corrected as described below.

`0x469DF0` returns directly when the event ID is unchanged and tail-calls the
void stage publisher when it changes. The sole direct caller `0x434E90` passes
through its incidental EAX value, but its observed callers discard that value.
Both interfaces now return `void`; the publisher takes a signed-byte stage. The
old same-return-type forwarding explanation in `KNOWLEDGE_BASE.md` is superseded.
The two full bodies remain exact, as do the fourteen exact roster bridges, pair
mode and fighter system-command consumers. Yukari and the unselected Tenshi
action candidate retain their earlier nonexact candidate hashes.

The event-ID setter is now a member of the same resource-owning state as the
stage publisher. Its global-event caller uses that owner directly; the narrow
view no longer declares this method. Setter, caller, lifetime and runtime
comparisons all remain exact.

The global event-state pointer and background render/update paths now use the
same `EventEffectStateData` owner. Weather emission writes its three coordinate
fields directly, while background update reads them from that owner. Shutdown
and update call the real weather manager virtuals at `+0x08` and `+0x14` rather
than an emitter facade. The affected exact event, weather and render functions
remain exact; the existing nonexact weather initializer and background update
retain their previous candidate hashes.
