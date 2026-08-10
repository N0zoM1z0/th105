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

Four adjacent shared methods are identified without assigning gameplay terms.
`0x0045AA10` and `0x0045AA30` call one- or two-argument helpers and then the
same virtual slot `+0x3C`; their addresses occur across AttackObject-family
vtables. `0x0045AA60` tail-dispatches one of 64 entries from a table at
object `+0x164`, while `0x0045AA90` forwards four arguments plus object
`+0x170` to the handler at `0x0046BBA0` through the battle root. Their call
order and fields are observed, but helper, slot, and table semantics remain
unknown.

`0x0046D620` clears and fills six per-side collision lists from current fighter
and object frame data. It then dispatches in this order:

1. `0x0046D370` (`dispatch_family1_object_clashes`) enumerates active object
   pairs and calls `0x0046C070` for object-object clash handling.
2. `0x0046D160` (`dispatch_family2_against_family1`) resolves interactions
   between classified object lists through `0x0046BFD0`, falling back to
   `0x0046BF20` when not consumed.
3. `0x0046D040` evaluates every attack candidate against the opposing fighter.
   It performs shape overlap and state gates, then dispatches special outcomes
   or falls through to the general hit resolver at `0x0046B570`.

Terms such as graze, guard, spell, and armor must not be assigned to individual
branches until flags and live behavior prove them. At present, clash and general
hit roles are supported by the data flow; the finer result taxonomy is not.

### Collision scratch lists

The collision/list manager is `0xA8` bytes. Its six temporary lists are three
families for two player slots:

| Family / slot | List object | Sentinel pointer | Count |
| --- | ---: | ---: | ---: |
| 0 / 0 | `+0x2C` | `+0x30` | `+0x34` |
| 0 / 1 | `+0x38` | `+0x3C` | `+0x40` |
| 1 / 0 | `+0x44` | `+0x48` | `+0x4C` |
| 1 / 1 | `+0x50` | `+0x54` | `+0x58` |
| 2 / 0 | `+0x5C` | `+0x60` | `+0x64` |
| 2 / 1 | `+0x68` | `+0x6C` | `+0x70` |

Each list object is 12 bytes. `0x0046A7F0` allocates its persistent sentinel;
`0x0046D000` allocates transient 12-byte nodes laid out as `{next, prev,
CharacterObject *payload}`. `0x0046D620` frees all prior-frame nodes, relinks
the sentinel to itself, and resets the count without freeing payloads. Fields
`+0x74/+0x78` and `+0x7C/+0x80` hold deferred per-player results applied after
collision dispatch.

The target proves three geometry classifications but not their original game
terms, so documentation calls them families 0, 1, and 2. Family 1 feeds
object-object clash at `0x0046D370`; family 2 feeds object interactions at
`0x0046D160`; family 0 feeds attack-vs-fighter dispatch at `0x0046D040`.

Both object-list passes traverse sentinel links rather than their count fields.
`0x0046D370` performs a same-list pass for each player and then a slot-0 versus
slot-1 pass; the frame-flag filters are intentionally asymmetric between outer
and inner payloads. `0x0046D160` walks family-2 sources against family-1 and
tries `0x0046BFD0` before `0x0046BF20`. Neither pass touches the deferred-result
fields; `0x0046D620` applies those only after the family-0 fighter phase.

The three allocation/initialization leaves are now exact reconstructions:
`0x0041FEA0` creates a 12-byte self-linked sentinel, `0x0046A7F0` stores it
at list `+4` and zeros count `+8`, and `0x0046D000` creates a transient node.
The list field at `+0` is deliberately left unnamed because initialization
does not touch it.

### Frame-flag result leaf

`0x0046BE90` is an exact reconstructed leaf beneath `0x0046D040`. It checks
four ordered pairs between candidate-frame flags at `candidate+0x1A4->+0x50`
and fighter-frame flags at `fighter+0x158->+0x4C`. A matching pair writes
result code `3` to both objects at `+0x180`, resets collision extents, and
returns true. The target proves this mechanism but not its original gameplay
term, so the source uses the neutral name `try_frame_flag_pair_outcome`.

`0x0046D040` is the per-candidate attack-versus-fighter orchestrator. After
state and shape gates, it tries outcomes in strict order: `0x0046BE90`,
`0x0046BDE0`, `0x0046CE20`, then the ordinary resolver `0x0046B570`.
The latter performs scratch reset, threshold/result selection, candidate and
fighter output setup, owner/context accounting, depletion handling, virtual
callbacks, effects, and final extent reset. This phase map is observed; names
for individual result codes and flag bits remain deliberately unresolved.

`0x0046BDE0` is now an exact reconstruction of the second outcome leaf. It
checks three candidate flag bits plus fighter frame/short gates, optionally
uses `adjust_counter_482`, writes neutral result code `6`, emits effect `0x34`,
and resets extents. The source name stays flag-oriented because the original
gameplay term is not proven.

## Body collision and geometry

Attack damage is resolved before fighter body separation.

- `0x0046ACB0` resets the collision context extents at `+0x1C..+0x28`.
- `0x0046A9A0` accumulates those fields from two four-integer coordinate
  records and is reconstructed exactly.
- `0x0046AB80` and `0x0046ABD0` exactly project one or two AABBs vertically
  with descriptor words `+4/+0x0C`, then call the integer extent accumulator.
- `0x0046AA30` performs the corresponding float-coordinate accumulation after
  selecting and converting extrema.
- `0x0046ACD0` converts a local rectangle into a world AABB using actor
  position at `+0xEC/+0xF0` and facing at `+0x104`.
- `0x0046AD30` gates and accumulates float AABB overlap. Its behavior and ABI
  are identified, but pure VC8 C++ still schedules the bitwise reduction
  differently from the target.
- `0x0046AEA0` exactly reconstructs the four signed half-space expressions
  used to test a point against an AABB plus a four-word descriptor.
- `0x0046AC40` exactly reconstructs effect dispatch at the midpoint of the
  accumulated extents. Its VC8 double-`0.5` data relocation is verified
  against both the COFF literal and target bytes before comparison.
- `0x0046ADA0` tests one AABB against such a descriptor, while `0x0046B000`
  performs an ordered descriptor-pair broad phase and five point tests. Their
  predicates and helper order are identified, but their current source shapes
  are not yet byte-identical.
- `0x0046C290` reads the two fighter roots at manager `+0x0C/+0x10`, consumes
  current-frame body geometry through fighter `+0x158`, and applies overlap
  correction and pushback.

Collision objects expose two observed box groups without proven gameplay
names. Group A uses signed count `+0x1AF`, boxes at `+0x204`, and optional shape
pointers at `+0x304`; group B uses signed count `+0x1B0`, boxes at `+0x1B4`,
and shape pointers at `+0x318`. An optional primary box pointer is at `+0x32C`.
`0x0046AF30` tests group A against the primary box, `0x0046B100` tests group A
against group B, and `0x0046B290` tests group B against group B. Debug drawing
colors the groups differently, but that does not prove hitbox/hurtbox labels.

The group counts are signed bytes and every loop index is sign-extended before
box or pointer indexing. `0x0046B100` and `0x0046B290` select the descriptor-pair
helper, one-descriptor helper, or inline AABB predicate from the two descriptor
null states. They OR every pair result and do not return early after an overlap;
preserving that traversal is required even when only a boolean result is used.

`0x0046C070` handles one observed group-B object-pair overlap after
`0x0046B290` succeeds. It compares two 16-bit values from each current frame
record, writes neutral result codes at object `+0x180/+0x184`, and resets the
collision extents. The ordered table is fully mapped, including the unusual
branch where the left object's `+0x184` byte is derived from the right object's
`+0x1A0` byte. All comparisons are signed 16-bit. No graze, guard, cancel, or
priority terminology is assigned without live proof.

Inside the family-2 versus family-1 pass, `0x0046D160` first tries
`0x0046BFD0`, which transfers owner pointers and flips facing after group-B
geometry succeeds. Its fallback `0x0046BF20` performs group-A versus group-B
geometry, writes frame-derived outputs, subtracts from the other object's
`+0x174`, and dispatches frame event/effect values. `0x0046BFD0` now has an
exact 147-byte VC8 reconstruction in `ObjectResponses.cpp`. `0x0046BF20`
remains one instruction away: the target gratuitously zero-extends a 16-bit
load before immediately storing only its low 16 bits, while every otherwise
exact natural source shape uses a 16-bit load.

The larger nonzero outcome selector is also bounded. `0x0046CE20` obtains a
selector from `0x0045CB20`; selector zero returns false to the ordinary hit
resolver, selectors `1/3/5/6` use `0x0046C9E0`, and selectors `2/4` use
`0x0046CC00`. The two subpaths share scratch/resource accounting and a normal
result-code-2 response, but differ in their counter transition rules, terminal
gates, and effect codes (`0x32` versus `0x33`). Their names remain neutral until
live behavior establishes the original gameplay terminology.

## Physics and state commit

`0x0046A5C0` enters `0x00463760`. Its core callees include:

- `0x00459860`: position integration and stage-bound clamping for fighter
  coordinates `+0xEC/+0xF0`;
- `0x0045CDD0`: transient status processing;
- `0x0045CF00`: timer decrement and cleanup.

The names of the latter two remain broad until their complete field contracts
are mapped.

Two exact per-frame reset leaves at `0x0046A610` and `0x0046A6A0` clear
different observed subsets of fighter fields `+0x6B4..+0x728` for both player
slots. These are intentionally named by field range until callers prove phase
or gameplay terminology. `0x0046B520` is also exact: it subtracts and clamps
fighter short `+0x482`, applies a state-5 gate from `+0x4B8`, and raises short
`+0x486` to the resulting floor value.

Two additional exact fighter gates now bound the general hit path:
`0x0045CAE0` tests signed short `+0x13C` against `0x32..0x95`, while
`0x0045CD90` additionally requires positive y at `+0xF0` and zero short
`+0x49E`. `0x00434860` compares the same y coordinate against an x-dependent
stage-height helper. Both the wrapper and helper `0x00434800` are exact: the
helper rounds positive x with double `0.5`, clamps at table index `0x4FF`, and
reads the 0x500-float height table at `0x006E4E38`.

`0x0046A940` resets the shared exchange scratch used by five hit-resolution
paths: it copies target `+0x174` to `+0x47C`, clears target `+0x4A2`, initializes
owner `+0x491/+0x494/+0x498..+0x49C`, and resets an indexed 0x34-byte manager
entry. Its VC8 source shape is recovered; durable matching remains blocked on
the indexed manager global and `0x00469E40` relocation mappings.

The hit pipeline obtains frame-derived quantities through exact sibling
wrappers `0x0045AAE0` and `0x0045AB10`. They multiply a candidate scale by the
signed descriptor short at `+0x1C` or `+0x20`, respectively, then tail-dispatch
the VC8 float-to-int truncation helper. `0x0045B870` adjusts an observed
signed-short counter at `+0x558`, with near-limit scaling and an upper cap of
500. Its faithful C++ is not yet register-scheduled exactly.

The scale provider `0x0045A030` is identified as the product of several
candidate/owner/fighter scalars and conditional modifiers. `0x0045AAE0` now has
an exact natural-C++ match, including its tail jump to verified VC8 runtime
`_ftol2_sse`; that runtime is tracked as library code rather than authored
progress.

The adjacent no-relocation leaf `0x0045AAC0` is also exact. It returns zero
when pointer `+4` is null and otherwise divides the byte difference between
pointers `+8` and `+4` by `0x88`. Its structural contract is proven; the
element type and original gameplay name are not.

The collision/list manager constructed by `0x0046A810` installs
`CBattleManagerBase::vftable` at `0x006AF634` and constructs three pairs of
12-byte list-like elements. This object is distinct from the higher-level
battle-state controller that calls the frame phases above.

`0x0046B420` is an identified 16-step cross-manager phase sequence over the
object manager, fighter container, static service, and effect manager; it does
not directly manipulate hit fields. The vtable `+0x38` wrapper `0x0046B4F0`
calls that sequence and then an Info-manager-family virtual slot `+0x14`.
Their exact compiler shapes are known, but durable project comparison still
needs broader global/tail-dispatch relocation support.

## Recommended reconstruction lanes

Keep claims address-bounded and prefer leaf functions before orchestrators:

1. Geometry source shaping: `0x0046AD30`, `0x0046ADA0`, and `0x0046B000`,
   using the exact extent and point-test leaves already in source.
2. Hit/object responses: `0x0046BF20`, `0x0046BFD0`, `0x0046C070`, then the
   larger `0x0046CE20` outcome branch.
3. Character action/object update: `0x0046A5B0`, `0x00463610`, `0x00459E50`.
4. Physics commit: `0x0046A5C0`, `0x00463760`, `0x00459860`,
   `0x0045CDD0`, `0x0045CF00`.
5. Collision-list orchestrator `0x0046D620` only after the response contracts
   and the two documented list passes are stable.
6. Battle state machine: `0x0046FE80..0x00470500` and `0x00470940` after the
   phase contracts above are stable.

Do not begin with `0x0046D620` or `0x0046C290` as monolithic source ports. Use
their leaf callees to establish layouts, flag meanings, and comparison support
first, then reconstruct the orchestrators from those verified contracts.
