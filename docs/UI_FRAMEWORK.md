# UI reconstruction framework

This document is the handoff map for the menu/UI reconstruction lane. It keeps
ABI facts, source candidates, and compiler-generated helpers separate so that a
declaration or skeleton is never mistaken for an implemented function.

The current vertical slice is scenario selection plus the shared guide and
cursor helpers. Addresses and status remain authoritative in
`config/functions.csv`; this document explains how those pieces fit together.

## Status rules

| Label | Meaning |
| --- | --- |
| `matching` | The listed source body is a 100% function-byte match. |
| `implemented` | A complete behavioral source candidate and standalone probe exist, but it is not yet included in the target build. |
| `compiles` | The source is included in the target build, but is not byte-identical. |
| `identified` | The role or ABI is known, but no complete source body is claimed. |
| `library` | VC8 runtime/template output, excluded from authored-game progress. |
| Opaque field | Size/offset is established, but the concrete type is intentionally not invented. |

Headers may therefore contain declarations for every edge needed to compile a
scene before all of their callees are reconstructed. Such declarations are ABI
scaffolding, not progress claims.

## Scene hierarchy and vtable

RTTI identifies the real inheritance chain as:

```text
IScene
└── CSceneBase
    └── CSelectScenario
```

`IScene` owns the six virtual slots. `CSceneBase` adds `scene_id` at `+0x04`,
and `CSelectScenario` begins its own fields at `+0x08`. The observed vtables
are `IScene` at `0x006AC454`, `CSceneBase` at `0x006AC77C`, and
`CSelectScenario` at `0x006ACC20`.

| Slot | Address | `CSelectScenario` method | Source status |
| ---: | ---: | --- | --- |
| 0 | `0x004247D0` | scalar deleting destructor | compiler-generated wrapper |
| 1 | `0x004237B0` | `int update()` | `implemented` |
| 2 | `0x00423B60` | `bool render()` | `implemented` |
| 3 | `0x004686B0` | `void unknown_scene_method()` | `matching` |
| 4 | `0x004238B0` | `void on_scene_enter(int)` | `implemented` |
| 5 | `0x0041DC90` | `void on_scene_exit(int)` | `matching` |
| 6 | `0x004239C0` | `int update_selection()` | `implemented`, class-specific extension |

The corrected base class is materially useful to matching: the constructor now
emits the observed `CSceneBase` construction vptr before installing the derived
vptr.

## Recovered layouts

### Shared UI primitives

| Type | Size | Established fields or contract |
| --- | ---: | --- |
| `UiSprite94` | `0x94` | vptr at `+0x00`; virtual color, texture, optioned-texture, and render calls |
| `UiTileA4` | `0xA4` | vptr at `+0x00`; tile-sheet texture, color, and indexed render calls |
| `UiDesignObject` | partial | vptr at `+0x00`, `x/y` at `+0x0C/+0x10`, enabled byte at `+0x14` |
| `GuideOverlay` | `0xA8` | texture `+0x04`, sprite `+0x08`, scroll `+0x9C`, width `+0xA0`, alpha `+0xA4` |

### `MenuCursorState`

The shared cursor is exactly `0x14` bytes:

| Offset | Type | Meaning |
| ---: | --- | --- |
| `+0x00` | `int` | item count |
| `+0x04` | `int` | visible page size; zero disables paging |
| `+0x08` | `int *` | signed held-input counter |
| `+0x0C` | `int` | selected item |
| `+0x10` | `int` | first visible item |

The earlier interpretation of `+0x04/+0x10` as repeat/previous state was
disproved by both page functions. The functions at `0x0043DB10` and
`0x0043DB80` exact-match as page backward/forward. `0x0041EE30` is the shared
single-step and held-repeat update; its source is behaviorally complete, while
standalone VC8 lowers `% 6` differently from the LTCG target.

### `CSelectScenario`

The class size is `0x3EC`. Important boundaries are:

| Offset | Type | Role |
| ---: | --- | --- |
| `+0x08` | `MatchSetup *` | selected game type and scenario |
| `+0x0C` | `CInputManager *` | active menu input |
| `+0x14` | 24-byte SSO string | scenario-related temporary name |
| `+0x2C` | 16-byte int vector facade | unlocked scenario IDs |
| `+0x40`, `+0xD8`, `+0x170`, `+0x218` | texture handles | scene UI resources |
| `+0x44`, `+0xDC`, `+0x21C` | `UiSprite94` | color/preview sprites |
| `+0x174` | `UiTileA4` | scenario-label tile renderer |
| `+0x2BC`, `+0x2D0` | `MenuCursorState` | scenario and game-type cursors |
| `+0x2E4` | `TitleDesignResource` | design archive/tree facade |
| `+0x338`..`+0x340` | timer/floats | preview transition state |
| `+0x344` | `GuideOverlay` | shared scrolling guide strip |

Fields at `+0x2B0..+0x2B8` and some design-resource internals remain opaque on
purpose. Their offsets are stable, but assigning concrete class names would be
ahead of the evidence.

### `TitleDesignResource` object tree

The design resource is `0x34` bytes. Its checked object tree begins at `+0x20`
and is `0x14` bytes; the sentinel/root pointer is at tree `+0x04`. The recovered
node and iterator contracts are:

| Type/offset | Meaning |
| --- | --- |
| node `+0x00/+0x04/+0x08` | left, parent, and right links |
| node `+0x0C` | unsigned design object ID |
| node `+0x10` | `UiDesignObject *` value |
| node `+0x15` | nil/sentinel flag |
| iterator `+0x00/+0x04` | owning tree and current node |

`0x0040C7F0` searches the tree and returns this 8-byte iterator by value. The
bind helpers at `0x0040C6A0` and `0x0046F2A0` validate iterator ownership,
recognize the end sentinel, and extract the node value. This corrected ABI
restores the formerly missing validation block in the scenario constructor.

### `CMenuSelect`

RTTI and the vtable at `0x006AE108` establish a real `Menu`-derived class of
size `0x1C4`; it is no longer an opaque allocation. The four virtual slots are
the scalar deleting destructor, the shared no-op at `0x004686B0`, `update`,
and `render`.

| Offset | Type | Role |
| ---: | --- | --- |
| `+0x00` | `Menu` | vptr/base object |
| `+0x04` | `signed char` | primary/profile-assignment state |
| `+0x08` | `TitleDesignResource` | `data/menu/select/select.dat` design |
| `+0x3C` | `UiDesignObject *[8]` | menu entries 100 through 170 |
| `+0x5C` | `MenuCursorState` | eight-entry selector |
| `+0x70` | `signed char` | active player index |
| `+0x74` | `GuideOverlay[2]` | guide IDs 5 and 11 |

The constructor, destructor, update dispatcher, render method, and the full
player-assignment state are exact matches. The profile path also proves a
28-byte checked string facade: an allocator-state dword followed by the VC8
24-byte SSO string. Its pointer-first `c_str()` branch order is required for
the exact 400-byte result.

The primary state machine is behaviorally complete. It updates the cursor,
colors all eight entries, opens player-specific `0x288` and input-specific
`0x330` child menus, handles the network-server mode variant, and implements
confirm/cancel audio plus the scene-mode transition. Its standalone VC8 object
is currently 752 bytes versus the 669-byte target because four `new` paths
duplicate the null-result installation block instead of merging it with the
constructed-object path.

## Function and dependency map

```text
CSelectScenario::CSelectScenario
├── construct CSceneBase, UI primitives, vector, design resource, GuideOverlay
├── load four texture resources and bind their sprites/tiles
├── enumerate unlocked scenarios into the int vector
└── resolve design objects used by update/render

on_scene_enter(previous_scene)
├── acquire MatchSetup, GameConfig, and selected input
├── initialize both MenuCursorState instances
├── find the current scenario in the unlocked-ID vector
└── apply_scenario(scenario_id)

update()
├── handle global selection-state transition
├── optionally allocate/install CMenuSelect
└── update_selection()
    ├── GuideOverlay::update
    ├── MenuCursorState::update × 2
    ├── apply_scenario after scenario movement
    ├── dispatch menu events
    └── confirm/cancel or start the scene fade

render()
├── establish/finish the render frame
├── draw design objects, sprites, labels, score/unlock state, and preview
└── GuideOverlay::render

on_scene_exit(next_scene) ── clear_menu_objects
~CSelectScenario ── release handles, GuideOverlay/design/vector/string cleanup
```

| Address | Contract | State |
| ---: | --- | --- |
| `0x004236F0` | `void __thiscall apply_scenario(int scenario_id)` | `matching`; releases old preview, formats `data/stand/%s.bmp`, loads and binds replacement |
| `0x004237B0` | `int __thiscall update()` | complete source candidate |
| `0x004238B0` | `void __thiscall on_scene_enter(int previous_scene)` | complete source candidate |
| `0x004239C0` | `int __thiscall update_selection()` | complete state-machine candidate |
| `0x00423B60` | `bool __thiscall render()` | complete render candidate |
| `0x00424350` | `void __thiscall ~CSelectScenario()` | `matching` |
| `0x00424470` | `void __thiscall CSelectScenario()` | complete constructor candidate; current VC8 probe is 854 bytes versus the 862-byte target |
| `0x0043D8E0` | `void __thiscall GuideOverlay::~GuideOverlay()` | complete source candidate |
| `0x0043D940` | `void __thiscall GuideOverlay::load(int)` | `matching` |
| `0x0043DA00` | `void __thiscall GuideOverlay::update()` | complete source candidate |
| `0x0043DA70` | `void __thiscall GuideOverlay::render()` | `matching` |
| `0x0043DAF0` | `void __thiscall GuideOverlay::GuideOverlay()` | `matching` |
| `0x004460A0` | `bool __thiscall CMenuSelect::update_primary_selection()` | complete source candidate; 752-byte probe versus 669-byte target |
| `0x00446360` | `void __thiscall CMenuSelect::render()` | `matching` |
| `0x004463E0` | `bool __thiscall CMenuSelect::update_player_assignment()` | `matching` |
| `0x00446580` | `bool __thiscall CMenuSelect::update()` | `matching` |
| `0x004465D0` | `void __thiscall CMenuSelect::~CMenuSelect()` | `matching` |
| `0x00446660` | `void __thiscall CMenuSelect::CMenuSelect()` | `matching` |

The guide destructor releases its texture handle and performs natural sprite
member destruction. Guide calls occur in several other menu scenes, but those
consumers should remain address-based until RTTI/vtable or constructor evidence
assigns reliable class identities.

## Compiler-generated int-vector cluster

`0x00423E60..0x004242C0` is a contiguous VC8 checked
`std::vector<int>`-style helper cluster, not a set of authored scenario
functions. It contains pointer-range copy/fill, overlap-safe movement,
construction, erase, growth/insertion, checked one-element insertion, and the
`push_back(const int&)` specialization. These entries are marked `library` in
the ledger.

The erase helper at `0x00423F40` is now ABI-complete. It is a checked
`erase(first, last)` specialization returning an 8-byte iterator through a
hidden result pointer. Each iterator is `{ owner, current }`, so the callee
receives five stack dwords after `this`: result, first owner/current, and last
owner/current. `CSelectScenario` implements `clear()` as checked
`erase(begin(), end())`, including both observed `_invalid_parameter_noinfo`
paths. The source facade keeps only the operations authored scene code needs
(`clear`, `size`, and `append`); recreating every template helper by hand would
inflate progress without recovering game logic.

The constructor's scenario counter is deliberately `long` even though both
`long` and `int` are 32-bit in this ABI. Passing it to `push_back(const int&)`
therefore creates the observed temporary `int`: VC8 can retain the counter in
EBP and pass the temporary by address. Making the counter itself `int` forces
its address to escape and spills the induction variable to the stack. This is
a source-type distinction, not an arbitrary register hint.

## Deliberate open edges

- The checked design tree ABI is recovered, but its remaining storage fields
  and the source reason for the two bind-helper code-generation copies are not
  yet proven.
- The `0x288` and `0x330` child-menu layouts reached from `CMenuSelect` remain
  opaque beyond their proven `Menu` base, allocation sizes, constructor ABIs,
  and player/mode arguments.
- `CMenuSelect::update_primary_selection` still needs the original source form
  that makes VC8 merge each constructor's null and non-null installation path.
- `MatchSetup` and `GameConfig` expose only fields proven by this slice.
- `UiSprite94`, `UiTileA4`, and `UiDesignObject` are shared ABI facades, not
  claims of original source names or complete layouts.
- GuideOverlay consumers outside this scene remain a good independent menu/UI
  lane once their owning vtables are mapped.
