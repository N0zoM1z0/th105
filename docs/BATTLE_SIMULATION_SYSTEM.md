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
├── 0x004704D0 active simulation wrapper [exact]
│   └── 0x0046B4F0 shared phase plus info callback [implemented]
├── 0x00470500 scene/round transition phase [decompiled]
├── 0x00470780 round reset phase [decompiled]
└── 0x004708B0 synchronized input gate [implemented, 127/129]

Controller direct dependency layer [decompiled breadth]
├── 0x0042AAB0/0x0042ABF0 save/load fixed battle-setup slots
├── 0x00427190/0x00427AC0/0x0042A560 control collection/publication
├── 0x00458D10/0x00458F10/0x004591D0 scenario and story-row setup
├── 0x0043F030 CMenuBattle mode-specific pause menu construction
├── 0x00462E20 fighter scripted-input state update
├── 0x00465F70 render/list reset plus event signal
└── 0x0046A490 fighter-pair and scene initialization

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

The dispatcher deliberately retries an unsupported phase once: it increments
the frame counter twice before returning zero. Session option 2 polls the
separate `BattleInputGate`; when input is unavailable it loops additional
frames only for phases 0 and 5, then republishes the synchronized return value.
These branches must remain explicit in eventual source rather than being
collapsed into a generic vtable array.

`0x004708B0` now has truthful RAII source. Its input object pointer is at
`+0x104`, the 0x1C-byte `CriticalSectionWrapper` is at `+0x124`, and comparison
bytes are at `+0x140/+0x141`. VC8 emits 127 bytes against the 129-byte target;
the first mismatch at `+0x4B` is the helper result register (`BL` in target),
not missing lock or comparison behavior.

`0x00470360` joins the battle controller to the spell runtime. It consumes a
fighter sequence entry through `0x0045BC30`, selects virtual phase 3 or 4, and
updates the observed counters at controller `+0x94/+0x98/+0x9C`. This is why
Spell-card and Battle simulation cannot be reconstructed as isolated systems.

`0x00470300` sets fighter byte `+0x4E9` to `2` and emits effect 64, 66, or 67
from the fighter-facing byte at `+0x104`, selected by fighter `+0x72C` and
sequence state `+0x55A`. Finer gameplay terminology is intentionally not
assigned.

The first one-hop expansion from the controller island promoted thirteen
formerly unclassified direct dependencies. The two 0x0042AAxx functions are
inverse fixed-slot setup transfers; the 0x00427xxx/0x0042A560 group bridges
local or synchronized controls into packed fighter inputs; and the 0x00458xxx
group loads character story CSV/pages and event rows. `0x004704D0` now has a
canonical 42/42 match unit, proving its shared phase call and phase-0/5/6 tail
dispatch without guessing the tail object's gameplay name.
Their declaration-only handoff is
`src/battle/BattleControllerDependencies.hpp`; it intentionally records
receiver and argument contracts without placeholder behavior or unsupported
original class ownership.

## Boundary and backend gate

The ledger remains authoritative for all comparisons:

| Address | Ledger bytes | IDA result | Treatment |
| --- | ---: | ---: | --- |
| `0x00406780` | ledger-defined | query error | retain ledger; use target bytes/headless fallback |
| `0x00427190` | 474 | 482 | keep ledger span |
| `0x0043F030` | 797 | 800 | keep ledger span |
| `0x00458E80` | 127 | 130 | keep ledger span |
| `0x00458F10` | 306 | 312 | keep ledger span |
| `0x004591D0` | 516 | 543 | keep ledger span |
| `0x00463610` | 323 | 11 | IDA subchunk is rejected; exact 323-byte object is authoritative |
| `0x00463760` | 187 | 11 | IDA subchunk is rejected; exact 187-byte object is authoritative |
| `0x0046A610` | 127 | 130 | keep ledger span |
| `0x0046A6A0` | 219 | 222 | keep ledger span |
| `0x0046AF30` | 194 | 197 | keep ledger span |
| `0x0046D620` | 1405 | 1452 | keep ledger span |
| `0x00465F70` | 325 | 332 | keep ledger span |
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
