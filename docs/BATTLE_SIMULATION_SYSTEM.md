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
BattleController [observed prefix +0x00..+0xA7]
├── 0x00470940 per-frame state dispatcher [exact]
│   ├── state 0 -> virtual +0x10
│   ├── state 1 -> virtual +0x14
│   ├── state 2 -> virtual +0x18
│   ├── state 3 -> virtual +0x1C
│   ├── state 4 -> virtual +0x20
│   ├── state 5 -> virtual +0x24
│   └── state 6 -> virtual +0x28
├── 0x0046FE80 setup/transition phase [exact]
├── 0x00470060 roster/setup phase [exact]
├── 0x004701C0 round-state initialization phase [exact]
├── 0x00470300 terminal fighter effect publication [exact]
├── 0x00470360 round/sequence resolution [exact]
│   └── 0x0045BC30 consume spell sequence entry [implemented]
├── 0x004704D0 active simulation wrapper [exact]
│   └── 0x0046B4F0 shared phase plus info callback [implemented]
├── 0x00470500 virtual scene/round transition phase [exact]
├── 0x00470780 round reset phase [implemented, 290/290]
└── 0x004708B0 synchronized input gate [implemented, 127/129]

Controller direct dependency layer [mixed breadth/exact]
├── 0x0042AAB0/0x0042ABF0 save/load fixed battle-setup slots [implemented]
│   └── 0x004275E0 checked 0x50-stride slot selector [exact]
├── 0x00427190 local/practice control setup [decompiled]
├── 0x00427AC0 synchronized control publication [decompiled, 258/240]
├── 0x0042A560 packed local control collection [exact]
├── 0x00458D10/0x00458F10/0x004591D0 scenario and story-row setup
├── 0x00458E80 member owned-string scenario dispatch [exact]
├── 0x0043F030 CMenuBattle mode-specific pause menu construction
├── 0x00462E20 fighter scripted-input state update
├── 0x00465F70 render/list reset plus event signal
└── 0x0046A490 fighter-pair and scene initialization [exact]

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

The canonical dispatcher match unit is exact for all 529 authoritative ledger
bytes. Its COFF section tail is 564 bytes because VC8 emits the remaining code
tail, one NOP, and a seven-entry local jump table in the same section; a
diagnostic comparison of that full tail is also exact. This strengthens the
switch/vslot evidence but does not override the ledger boundary or IDA's 535
byte grouping.

`0x004701C0` is exact across its authoritative 299-byte ledger span; its object
section tail is the same 306 bytes that IDA groups. It selects synchronized or
local input publication, advances scripted input for both fighters, opens the
scene-exit transition for either fighter's `+0x6B0` linked state, then chooses
the already exact narrow or broad two-fighter reset from controller phase.
Writing the final test as `phase != 1` preserves target fallthrough into the
narrow reset and branches to the broad reset; the semantically equivalent
positive test reverses code layout after 256 otherwise exact bytes.

The setup pair is exact as one audited source unit. `0x0046FE80` matches
479/479 with the target 260-byte path buffer and `/GS` frame; it selects local
or synchronized setup, initializes scenario/story rows, seeds the match,
initializes both fighter slots, and falls back to character-derived stage/BGM
selection when no scenario phase block exists. `0x00470060` matches 337/337;
it transfers the fixed setup slot, prepares the second fighter when inactive,
copies both fighters' `+0xEC/+0xF0` metadata, refreshes shared state, and
dispatches phase 0. Together they prove the complete 0x4C-byte `MatchSetup`
view and extend the controller's observed prefix through `+0xA4`.

`0x004708B0` now has truthful RAII source. Its input object pointer is at
`+0x104`, the 0x1C-byte `CriticalSectionWrapper` is at `+0x124`, and comparison
bytes are at `+0x140/+0x141`. VC8 emits 127 bytes against the 129-byte target;
the first mismatch at `+0x4B` is the helper result register (`BL` in target),
not missing lock or comparison behavior.
The availability leaf `0x00427680` is exact at 8/8 in a separate match unit.
Keeping it in its own translation unit is semantically important: putting its
body beside the RAII caller lets VC8 inline the zero test and delete the target
EH frame.

`0x0042A560` is exact at 224/224. It collects the low ten bits from each active
fighter-control record, maps menu inputs 59/60/61/63/64/65 into the six high
bits, and publishes each packed word through `0x0042A370`. This exact result
supports the `BattleInputGate` offsets for both control pointers, both low-bit
fields, the side-enable flags, and the queue/lock region. The network-session
gate bypasses local collection when synchronized play owns the input stream.

The paired synchronized publication path at `0x00427AC0` is semantically
complete in a temporary probe: it consumes the same 16-bit format under lock,
publishes low fighter bits and high menu-state bits for the enabled sides, and
resolves all external calls. VC8 currently emits 258 bytes against 240 with the
first mismatch at `+0x02`; the bounded blocker is entry register allocation,
not an unknown branch or unresolved relocation.

`0x00470360` is exact at 358/358 and joins the battle controller to the spell
runtime. It finalizes or consumes fighter sequence entries through
`0x0045BB10/0x0045BC30`, publishes the outcome band and tallies, selects the
shared virtual slot `+0x34` with phase 3 or 4, and updates controller
`+0x94/+0x98/+0x9C`. This is why Spell-card and Battle simulation cannot be
reconstructed as isolated systems.

`0x0045BB10` is exact at 154/154. For a nonzero outcome it copies the pending
statistic candidate, records the peer/self/record tuple in `ScoreData`, and
resets the embedded sequence effect at fighter `+0x3D0`; every active sequence
then publishes its front record and outcome through the player-indexed display
context. Inlining both checked front-entry expressions is required for the
target VC8 right-to-left argument evaluation and register schedule.

`0x00470300` is exact at 90/90. It sets fighter byte `+0x4E9` to `2`, updates
the observed byte global at `0x006E4E2E` on one branch, and emits effect 64,
66, or 67 from the fighter-facing byte at `+0x104`, selected by fighter
`+0x72C` and sequence state `+0x55A`. Finer gameplay terminology is
intentionally not assigned.

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

The paired `0x0042AAB0/0x0042ABF0` setup transfers now have a complete payload
contract: each stored setup is 0x3C bytes inside a 0x50-stride envelope, with
two 0x14 `std::deque<short>` payloads. The envelope also owns a third deque at
`+0x3C`; the exact 297/297 native VC8 assignment at `0x0042A7B0` replaced the
earlier opaque side-payload hypothesis. Their authored save/load bodies
emit 288/305 and 292/332 bytes with clean relocations, while the shared checked
slot selector `0x004275E0` is exact at 60/60. Their remaining shared blocker is
the original fixed-slot container/TU register lifetime, so the layout is
durable while exact tuning remains bounded as a pair.

The scenario dispatch at `0x00458E80` is a receiver-bearing `__thiscall`, not
the earlier free `__stdcall` hypothesis. Its shared `ScenarioTransitionView`
source is exact for all 127 authoritative bytes; both `0x00470500` and
`0x00470780` now pass the phase block in ECX and retain their established
comparison results.

The adjacent event-row parser `0x004591D0` now has complete authored source.
It resolves an owning event-name string through `0x0043AC30`, clears the output
short deque and the two internal integer lists, selects one of four CSV columns,
and mirrors the newly read integer list. Its strict object is 538 bytes against
the 516-byte ledger span, with every relocation resolved; the first delta at
`+0x10` is the VC8 `/GS` frame size, while IDA's 543-byte grouping remains
non-authoritative.

This fan-out is the concrete validation for the breadth-first workflow: one
controller map produced eight authored exact functions (`0x0046FE80`,
`0x00470060`, `0x004701C0`, `0x00470300`, `0x00470360`, `0x00470940`,
`0x0042A560`, and `0x00427680`), preserved precise stop conditions for three
hard neighbors, and strengthened shared controller/input types before another
call-graph layer was expanded.

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

`0x0046A490` is exact at 279/279. It loads both fighter slots, performs paired
roster and vslot resets, publishes four position pointers, clears collision and
global scene state, resets renderer/post/input services, and dispatches phase
zero. The otherwise unused `BattleController+0x04` thiscall receiver for
`0x00434780` and COFF-global forms of `0x006E6238/0x006E4E38` are required for
the exact VC8 EBX/EDI schedule.

`0x00470500` is exact at 602/602 and corrects an earlier model: it is the
existing virtual `BattleController::dispatch_round_phase_34(int)` at vslot
`+0x34`, not a second nonvirtual transition method. Its seven cases cover
state clearing, fighter transition reset, effects, scenario selection, async
scene loading, owned `String28` Win/Lose dispatch, and Continue/End menu
allocation. Native string ownership and `/GS` EH metadata are part of the
accepted match.

`0x00470780` now has complete 290-byte source and a 290-byte VC8 object. The
strict first mismatch is `+0x3D`: target retains the phase block in EDI after
first deriving list `+0x598` through ECX, while the standalone object derives
destination `+0x5A4` first. This remains `implemented`, with checked-STL
register shaping explicitly isolated from semantic completeness.

1. Tune the round reset `0x00470780` only through truthful checked-list source
   shaping or later linked/LTCG evidence; its behavior and size are complete.
2. Tune the synchronized control pair `0x00427AC0/0x0042A370` after their queue
   container layout is shared; retain the explicit register-allocation blocker.
3. Preserve the already source-complete collision/hit algorithms while adding
   only direct dependencies that unlock a controller or spell-runtime edge.
4. Use the complete `0x004591D0` source and decompiled `0x0043AC30` resolver as
   the next scenario-loader exact packets; do not rediscover their behavior.
5. Fan out exact work by object boundary, then feed recovered types and exact
   helpers back into the next one-hop breadth wave.

The next exact work should favor a type or helper that unlocks several of these
branches, not a disconnected trivial leaf.
