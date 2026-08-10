# TH10.5 architecture baseline

This document separates confirmed properties of the shipped executable from
the source layout that the reconstruction project will use. Exact source-file
boundaries are not yet known.

## Binary identity and toolchain evidence

The analyzed target is the original Japanese 1.06a executable identified in
`config/target.toml`.

| Property | Observed value |
| --- | --- |
| Format | PE32, x86 Windows GUI |
| Image base | `0x00400000` (relocations stripped) |
| Entry point | `0x0067D112` |
| `.text` | `0x00401000..0x006ABFFF`, 2,797,568 raw bytes |
| Linker | Microsoft linker 8.0 |
| Rich-header tool build | 50727 for the dominant VC8 tools |
| Rich-header LTCG entries | 42 `Utc1400_LTCG_CPP` objects |
| Debug record | RSDS, PDB age 157 |
| Original PDB path | `c:\Nonotaro\works\東方緋想天\th105.pdb` |
| Ghidra inventory | 4,838 internal `.text` functions |
| Ghidra metadata | 5,009 total functions, 57,543 symbols |

The linker and Rich header establish the Visual C++ 2005 family. The 42
`Utc1400_LTCG_CPP` records are strong evidence that a meaningful C++ subset was
compiled with `/GL` and passed through link-time code generation. They do not
yet establish the exact service pack or all compiler/linker switches.

## Runtime structure

TH10.5 is structurally different from the earlier shooting games: it is a
large object-oriented fighting-game executable with polymorphic scenes,
network variants, battle-manager variants, per-character class families, and a
static C/C++ runtime.

```text
WinMain / platform bootstrap
└── engine services and main loop
    ├── input (DirectInput keyboard/mouse → logical player/menu input)
    ├── scene manager
    │   ├── logo/opening/title/menu/config/profile scenes
    │   ├── character/deck/stage select and loading scenes
    │   ├── local battle
    │   ├── server/client/watch battle variants
    │   └── ending/staff roll
    ├── renderer (D3D9/D3DX9, sprite, animation, pattern/frame data)
    ├── package/assets and audio
    └── network/replay services

battle scene
└── CBattleManagerBase
    ├── arcade/story/local manager variants
    ├── P1/P2 Character roots
    │   ├── shared Character/CharacterEx/AttackObject behavior
    │   └── one class and object-manager family per fighter
    ├── effect/object managers
    ├── collision and frame-data geometry
    └── weather, HUD/info, system effects
```

## Confirmed class families

MSVC RTTI supplies 280 type descriptors. Ghidra currently exposes 991
class/namespace entries after analysis. Important families include:

- Scenes: `IScene`, `CSceneBase`, `CBattle`, `CSelect`, `CLoading`,
  `CSceneManager`, and server/client/watch variants.
- Rendering/assets: `CRenderer`, `CSprite`, `AnimationObject`, `FrameData`,
  `PatternData`, `Environment`, `CPackageFileReader`.
- Battle: `CBattleManagerBase`, `CBattleManager`, `CBattleManagerArcade`,
  `CBattleManagerStory`, `Character`, `CharacterEx`, `CharacterObject`,
  `CharacterFrameData`, `AttackObject`.
- Objects/effects: `TObjectManagerBase`, `CHandleManagerEx`, `CEffectManager`,
  `EffectObject`, `WeatherEffectObject`, `SystemEffectObject`, `InfoEffectObject`.
- UI/profile: the `CMenu*`, `CProfile*`, and `CDesign*` families.
- Network: `CNetworkBase`, client/server/UDP/Winsock classes, `IPacket`, and
  `CDPP_*` packet classes.
- Scripting: `CScript::CCommandFactory`, `CCommandBase`, and typed `TCommand`
  templates.
- Fighters: Reimu, Marisa, Sakuya, Alice, Patchouli, Youmu, Remilia, Yuyuko,
  Yukari, Suika, Udonge, Komachi, Aya, Iku, and Tenshi, with object managers.

## Proposed source modules

`config/modules.toml` is the machine-readable module list. The initial source
tree will keep platform/engine/input/render/assets/audio/UI/script/network and
battle code separate, with character-specific code below `src/characters/`.
Address ranges will be added only after call-graph, RTTI/vtable, string-xref,
and compiler boundary evidence agree; code adjacency alone is insufficient.

## High-value confirmed roots

The seed addresses in `config/known-symbols.csv` and
`config/known-globals.csv` were validated against shipped instructions and live
state. They establish the first vertical slices:

- main loop and scene transition at `0x00407F80`/`0x004080E0`;
- DirectInput and logical input at `0x00409900..0x0040D250`;
- main-menu update/render at `0x00424AB0`/`0x00424860`;
- live battle-manager and fighter roots through `0x006E6244`;
- shared collision/frame geometry around `0x0046ACD0`;
- Sakuya action handling at `0x004DDB20` and `0x004DEF70`.

Gameplay reconstruction should start from the phase ordering and bounded work
lanes in [`docs/BATTLE.md`](BATTLE.md). UI, audio, and input plumbing remain
valid modules but are lower priority than the active battle pipeline.

These names describe observed roles; they do not imply that original source
names have been recovered.

## Open architecture gates

1. Recover translation-unit ownership from static init, RTTI/vftable clusters,
   strings, and link experiments while accounting for LTCG-erased boundaries.
2. Separate compiler/runtime/library functions from authored game code.
3. Recover class layouts and vtable slot ownership starting at scene and battle
   roots.
4. Identify the exact VC8 service level and optimization/link switches.
5. Produce original-object slices suitable for objdiff, then promote functions
   to reccmp-backed `matching` status.
