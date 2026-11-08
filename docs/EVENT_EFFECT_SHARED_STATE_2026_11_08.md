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
unchanged. The narrower caller interface remains separate: its stage-publish
return/signature and emitter call need independent ABI reconciliation before
it can be merged safely.

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
