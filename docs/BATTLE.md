# Battle core map

This note is the entry point for agents working on gameplay rather than menus,
audio, or input plumbing. Addresses and phase ordering below are observed in the
original Japanese v1.06a target. Semantic names remain reconstruction names
unless explicitly supported by RTTI.

## Active-frame order

The active battle-state controller dispatches each frame through `0x00470940`.
Active round states execute the following stable sequence:

```text
manager virtual +0x40
  -> 0x0046A5B0  character action and owned-object update
  -> 0x0046D620  attack/projectile collision and hit resolution
  -> 0x0046C290  fighter body overlap and pushback
  -> 0x0046A5C0  position, status, and timer commit
  -> 0x0046A5D0  post-update phase
  -> manager virtual +0x30
```

State 1 uses the same surrounding update phases but omits `0x0046D620`; it is
therefore not yet an active damage phase. States 2 through 5 run the complete
pipeline when their state-specific gates allow simulation.

## Character update phase

`0x0046A5B0` enters `0x00463610`, which iterates active fighters and their
owned object managers. The Sakuya vtable provides concrete slot evidence:

- fighter vtable `+0x40` calls `0x004DDB20`, the action-change handler;
- the common update at `0x00459E50` reaches vtable `+0x50`, which is
  `0x004DEF70`, the input/action selector;
- fighter `+0x658` is the owned-object manager used during this phase.

The exact ordering inside `0x00463610` must be preserved: fighter callbacks,
owned-object callbacks, the common character update, then the object-manager
post-update callback.

## Attack and projectile collision phase

The `AttackObject` base has vtable `0x006AEB44`. Constructors at `0x00461A90`
and `0x004927D0` first call its constructor at `0x0045E3A0` before installing
the `Character` and `CharacterObject` vtables. This establishes a shared
collision-data base for fighters and their spawned objects.

`0x0046D620` clears and fills six per-side collision lists from current fighter
and object frame data. It then dispatches in this order:

1. `0x0046D370` enumerates active object pairs and calls `0x0046C070` for
   object-object clash handling.
2. `0x0046D160` resolves interactions between classified object lists through
   `0x0046BFD0`, falling back to `0x0046BF20` when not consumed.
3. `0x0046D040` evaluates every attack candidate against the opposing fighter.
   It performs shape overlap and state gates, then dispatches special outcomes
   or falls through to the general hit resolver at `0x0046B570`.

Terms such as graze, guard, spell, and armor must not be assigned to individual
branches until flags and live behavior prove them. At present, clash and general
hit roles are supported by the data flow; the finer result taxonomy is not.

## Body collision and geometry

Attack damage is resolved before fighter body separation.

- `0x0046ACB0` resets the collision context extents at `+0x1C..+0x28`.
- `0x0046ACD0` converts a local rectangle into a world AABB using actor
  position at `+0xEC/+0xF0` and facing at `+0x104`.
- `0x0046AD30` gates and accumulates AABB overlap.
- `0x0046C290` reads the two fighter roots at manager `+0x0C/+0x10`, consumes
  current-frame body geometry through fighter `+0x158`, and applies overlap
  correction and pushback.

## Physics and state commit

`0x0046A5C0` enters `0x00463760`. Its core callees include:

- `0x00459860`: position integration and stage-bound clamping for fighter
  coordinates `+0xEC/+0xF0`;
- `0x0045CDD0`: transient status processing;
- `0x0045CF00`: timer decrement and cleanup.

The names of the latter two remain broad until their complete field contracts
are mapped.

The collision/list manager constructed by `0x0046A810` installs
`CBattleManagerBase::vftable` at `0x006AF634` and constructs three pairs of
12-byte list-like elements. This object is distinct from the higher-level
battle-state controller that calls the frame phases above.

## Recommended reconstruction lanes

Keep claims address-bounded and prefer leaf functions before orchestrators:

1. Geometry: `0x0046ACB0`, `0x0046ACD0`, `0x0046AD30`, then `0x0046C290`.
2. Character action/object update: `0x0046A5B0`, `0x00463610`, `0x00459E50`.
3. Physics commit: `0x0046A5C0`, `0x00463760`, `0x00459860`,
   `0x0045CDD0`, `0x0045CF00`.
4. Hit pipeline: `0x0046D000`, `0x0046D040`, `0x0046D160`,
   `0x0046D370`, and finally `0x0046D620`.
5. Battle state machine: `0x0046FE80..0x00470500` and `0x00470940` after the
   phase contracts above are stable.

Do not begin with `0x0046D620` or `0x0046C290` as monolithic source ports. Use
their leaf callees to establish layouts, flag meanings, and comparison support
first, then reconstruct the orchestrators from those verified contracts.
