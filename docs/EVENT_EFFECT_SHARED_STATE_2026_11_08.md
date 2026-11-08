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
40-byte wrapper, including its full-width argument push. The separate event-ID
setter remains on its earlier return-bearing view pending caller-return analysis.
