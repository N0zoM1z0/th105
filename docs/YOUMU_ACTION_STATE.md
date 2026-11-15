# Youmu action state 0x530200

`Youmu_dispatch_action_state_vslot28` spans [0x530200, 0x53953C), 37,692
bytes. Its source is `src/characters/YoumuActionState.cpp`, compared by unit
`gpt-web-youmu-vslot28-full-root`. It is nonexact; the last recorded first
difference was at +0xCA (target `64`).

Corrections already in the source, each backed by target bytes:
- the virtual-call ABI and typed virtual calls;
- shared effect tails and the shared zero return;
- ordered facing guards, unordered angle-range tests and the target's
  addition association (see the float-comparison rule in the
  [patterns note](VC8_SOURCE_SHAPE_PATTERNS.md));
- the full object-853 payload (three float fields);
- float X carriers for spawn arguments, and argument schedules computed inside
  the call expression for action 603's two offset spawns;
- action 602's conversions, loop index and shared call, and the value order of
  actions 603, 696 and 526;
- action 214's zero/effect lifetimes and its eleven sequence-call sites;
- action 720's signed comparison and nested switch.

Tried without effect: `int` and `short` selector views are byte-neutral, and a
uniform change to the spawn-control interface makes the root worse. The
target passes both `FFFFFFFF` and `000000FF` for the same consumed `FF` byte,
so caller widths stay as they are.

The related object initializer 0x543670 is covered by
[its physical-tail note](YOUMU_ENTRY_PHYSICAL_TAIL_2026_10_23.md), the fighter
initializer 0x53A1D0 by
[its own note](YOUMU_FIGHTER_ACTION_INITIALIZATION_2026_10_25.md), and the
object update 0x53CEA0 by [its note](YOUMU_OBJECT_UPDATE_2026_10_25.md).

The per-checkpoint notes from September 26 to October 19 were removed in the
commit that added this note; Git history keeps them.
