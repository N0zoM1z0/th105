# Battle simulation reconstruction map

This is the breadth-first system map above the detailed algorithms in
`docs/BATTLE.md`. It covers the frame controller, character/object update,
collision preparation and dispatch, hit resolution, body separation, state
commit, and round transitions.

The shared lanes are reproducibly surveyed with:

```bash
python3 scripts/core-lane-survey.py \
  --lane battle-phase --lane collision-phase \
  --lane hit-resolution --lane geometry \
  --output build/battle-simulation-survey.json
```

That survey covers 70 pre-existing core nodes: 45 exact, 22 implemented, one
library, one identified, and one target initializer that IDA does not expose as
a function. This pass additionally promotes the ten-function controller island
`0x0046FE80..0x00470940` and its direct phase dependencies into the core graph.

## System tree

```text
BattleController [observed prefix +0x00..+0x9F]
├── 0x00470940 per-frame state dispatcher [decompiled]
│   ├── state 0 -> virtual +0x10
│   ├── state 1 -> virtual +0x14
│   ├── state 2 -> virtual +0x18
│   ├── state 3 -> virtual +0x1C
│   ├── state 4 -> virtual +0x20
│   ├── state 5 -> virtual +0x24
│   └── state 6 -> virtual +0x28
├── 0x0046FE80 setup/transition phase [decompiled]
├── 0x00470060 roster/setup phase [decompiled]
├── 0x004701C0 round-state initialization phase [decompiled]
├── 0x00470300 terminal fighter effect publication [decompiled]
├── 0x00470360 round/sequence resolution [decompiled]
│   └── 0x0045BC30 consume spell sequence entry [implemented]
├── 0x004704D0 active simulation wrapper [decompiled]
│   └── 0x0046B4F0 shared phase plus info callback [implemented]
├── 0x00470500 scene/round transition phase [decompiled]
├── 0x00470780 round reset phase [decompiled]
└── 0x004708B0 synchronized input gate [decompiled, separate input object]

Active simulation frame
├── manager virtual +0x40
├── character and owned-object update
│   ├── 0x0046A5B0 wrapper [exact]
│   └── 0x00463610 five-pass callback phase [exact]
├── attack/projectile collision
│   ├── 0x0045AEC0 frame geometry preparation [implemented]
│   ├── 0x0046D620 six-list orchestration [implemented]
│   ├── 0x0046D370 family-1 object clashes [implemented]
│   ├── 0x0046D160 family-2 against family-1 [implemented]
│   ├── 0x0046D040 candidate against fighter [exact]
│   └── 0x0046B570 general hit resolver [implemented]
├── fighter body overlap
│   └── 0x0046C290 separation/pushback [implemented]
├── position/status/timer commit
│   ├── 0x0046A5C0 wrapper [exact]
│   └── 0x00463760 commit orchestration [exact]
│       ├── 0x00459860 position integration [exact]
│       ├── 0x0045CDD0 transient status [implemented]
│       └── 0x0045CF00 timer cleanup [decompiled]
├── 0x0046A5D0 post-update/global state [exact]
└── manager virtual +0x30

Shared pre/post simulation sequence
└── 0x0046B420 sixteen-step phase [exact]
    ├── 0x00404980 and 0x00404A10 render/service mode transitions [decompiled]
    ├── 0x00463820/3970/3A00/3A60/3AB0 fighter-vector passes [decompiled]
    └── 0x00465B00/5B70 object-manager list passes [decompiled]
```

## Controller facts

`0x00470940` increments controller `+0x04` once per dispatched frame and reads
the phase at `+0x88`. Local/offline execution performs one virtual phase call.
Session option `2` instead polls `0x004708B0` and may advance multiple virtual
frames until synchronized input is available. Escape/scene-exit gates dispatch
event `0x29` and construct the observed transition object. These are direct
target facts; original class and method names remain unknown.

`0x00470360` joins the battle controller to the spell runtime. It consumes a
fighter sequence entry through `0x0045BC30`, selects virtual phase 3 or 4, and
updates the observed counters at controller `+0x94/+0x98/+0x9C`. This is why
Spell-card and Battle simulation cannot be reconstructed as isolated systems.

`0x00470300` sets fighter byte `+0x4E9` to `2` and emits effect 64, 66, or 67
from the fighter-facing byte at `+0x104`, selected by fighter `+0x72C` and
sequence state `+0x55A`. Finer gameplay terminology is intentionally not
assigned.

## Boundary and backend gate

The ledger remains authoritative for all comparisons:

| Address | Ledger bytes | IDA result | Treatment |
| --- | ---: | ---: | --- |
| `0x00406780` | ledger-defined | query error | retain ledger; use target bytes/headless fallback |
| `0x00463610` | 323 | 11 | IDA subchunk is rejected; exact 323-byte object is authoritative |
| `0x00463760` | 187 | 11 | IDA subchunk is rejected; exact 187-byte object is authoritative |
| `0x0046A610` | 127 | 130 | keep ledger span |
| `0x0046A6A0` | 219 | 222 | keep ledger span |
| `0x0046AF30` | 194 | 197 | keep ledger span |
| `0x0046D620` | 1405 | 1452 | keep ledger span |
| `0x004701C0` | 299 | 306 | keep ledger span |
| `0x00470940` | 529 | 535 | keep ledger span |

## Breadth-first implementation frontier

1. Declare and type the ten controller entries and their observed `0xA0`
   prefix; do not add empty bodies.
2. Preserve the already source-complete collision/hit algorithms while adding
   newly discovered direct phase dependencies to the core graph.
3. Split exact work by object boundary: controller island, shared sixteen-step
   phase, collision preparation/list orchestration, general hit/outcome paths.
4. Only after these shared paths are stable, fan out exact work into per-role
   character 600-series spell actions and other character-specific simulation.

The next exact work should favor a type or helper that unlocks several of these
branches, not a disconnected trivial leaf.
