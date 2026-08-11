# TH10.5 reconstruction map

This is the navigation and unlock map for important game behavior. It does not
replace the function ledger or gameplay manifests. Update the tree when a new
contract changes what can be worked on next; do not add isolated trivial
functions merely to make the tree look complete.

## State vocabulary

| State | Meaning |
| --- | --- |
| `seed` | a supported root exists, but the family is not mapped |
| `mapped` | major call/vtable/data boundaries are supported |
| `contracted` | the minimum ABI/type/dependency boundary is recorded |
| `semantics-ready` | behavior is sufficiently understood for faithful source |
| `source-ready` | source exists; individual ledger rows may still differ |
| `exact` | every row explicitly named by that node is byte-identical |
| `blocked` | a concrete missing dependency or toolchain boundary is recorded |

These are subsystem states, not `config/functions.csv` statuses. Exact function
status remains ledger-driven. `core-functions.csv` selects gameplay scope,
`core-dependencies.csv` supplies machine-checked unlock edges, and
`core-types.csv` supplies partial or complete ABI contracts.

## Core tree

```text
TH10.5
├── Battle simulation
│   ├── frame-state controller [mapped]
│   │   └── 0x0046FE80..0x00470940 active-state dispatch
│   ├── fighter update [semantics-ready]
│   │   ├── action + owned-object callbacks [exact]
│   │   │   └── 0x0046A5B0 -> 0x00463610
│   │   ├── position/status/timers [semantics-ready]
│   │   │   ├── 0x0046A5C0 -> 0x00463760 outer phase [exact]
│   │   │   ├── 0x00459860 position phase [exact]
│   │   │   ├── 0x0045CDD0 transient status [implemented]
│   │   │   └── 0x0045CF00 timer cleanup [decompiled]
│   │   └── 0x0046A5D0 post-update [exact]
│   ├── attack/projectile collision [source-ready]
│   │   ├── 0x0045AEC0 geometry preparation [implemented]
│   │   ├── 0x0046D620 six-list orchestration [implemented]
│   │   │   ├── 0x0046D370 family-1 clash pass [implemented]
│   │   │   ├── 0x0046D160 family-2/family-1 pass [implemented]
│   │   │   └── 0x0046D040 candidate/fighter cascade [exact]
│   │   ├── 0x0046B570 general hit resolution [implemented]
│   │   └── 0x0046C290 fighter body separation [implemented]
│   └── 0x0046B420 shared battle phase [exact]
├── Spell-card system
│   ├── assets and parsers [implemented: compiler-shaping remains]
│   │   ├── 0x00416A50 VC8 deque<4-byte>::push_back [library, exact probe]
│   │   ├── 0x00408A40 VC8 string append [library, exact probe]
│   │   ├── 0x00404F30 pooled texture creation [decompiled]
│   │   ├── 0x0040EB20/EE50/EF50/F050/F780 CSV reader API [decompiled]
│   │   ├── 0x00431430/0x00432310 VC8 map traversal/insert [library, exact]
│   │   ├── 0x00431950 SpellRecord deep copy [exact]
│   │   ├── 0x004325B0 first CSV parser [identified]
│   │   └── 0x00432E20 record/resource parser [implemented]
│   ├── spell data [source-ready]
│   │   ├── 0x00430DE0 loader selector [exact]
│   │   ├── 0x00430C80 post-load transform [implemented]
│   │   └── 0x004317A0 local/common lookup [implemented]
│   ├── spell runtime [source-ready]
│   │   ├── 0x00430C30/0x00430D90 deque front/select [exact]
│   │   └── 0x0045BC30/0x0045C690 consume/prepare [implemented]
│   └── fighter integration [source-ready]
│       ├── 0x0045F140 battle-state initialization [implemented]
│       └── 0x00462050 spell-resource initialization [implemented]
│           ├── 0x0045E080 indexed wave resources [exact]
│           ├── 0x00460B50 PAT/palette records [identified]
│           └── 0x00464320 cut-in resource [implemented]
└── Character-specific families [mapped roots]
    ├── shared Character/CharacterEx/AttackObject contracts
    ├── shared command gates 0x00493300..0x00493580 [source-ready]
    │   ├── 0x00493300/0x00493490/0x00493540 [exact]
    │   └── 0x00493380/0x00493580 [implemented]
    ├── fifteen RTTI/vtable pilot rows -> docs/CHARACTER_PILOTS.md
    ├── fifteen owned-object spawn families [contracted]
    │   ├── one normalized 237-byte ABI/template
    │   ├── fifteen normalized acquire-and-link entries [source-ready]
    │   ├── fifteen normalized pool fresh/reuse entries [semantics-ready]
    │   ├── fourteen roster spawn entries [decompiled]
    │   └── Sakuya spawn source [source-ready]
    └── Sakuya fighter pilot [mapped]
        ├── 0x004DEEF0 fighter constructor [decompiled]
        ├── 0x004DECF0 manager constructor [decompiled]
        ├── 0x004DED80 owned-object spawn [decompiled]
        ├── raw vslot +0x3C: 0x004DDB20 action change [decompiled]
        └── common-update vslot +0x50: 0x004DEF70 input/action [identified]
```

Supporting systems remain necessary but lower priority unless they block a core
edge: engine/scene, render/assets, input, network/replay, UI/profile, audio, and
platform/runtime. Their module boundaries are listed in `docs/ARCHITECTURE.md`.

## Unlock-first frontier

1. **Roster character pilots.** All fifteen owned-object spawn entries now have
   one proven ABI and normalized instruction template; Sakuya supplies the
   source body, all fifteen acquire-and-link helpers have one source-ready
   body, and all pool fresh/reuse paths are semantics-ready. Recover their
   shared container/lock/constructor dependencies without hiding Alice's
   `0x38C` allocation exception, then emit the shared spawn pattern and split
   spell/skill decision leaves under each fighter dispatcher.
2. **PAT record semantics.** `0x00462050` now has target-sized complete source,
   `0x0045E080` is exact, and `0x00464320` is 197/199 bytes. Recover the
   EH-bearing record types inside `0x00460B50`; this is the remaining shared
   resource semantic boundary inherited by all fifteen fighters.
3. **Fighter state continuity.** Shape the one-byte remaining loop difference
   in `0x0045CDD0`, reconstruct the separate tail helper `0x00459D30`, then
   implement `0x0045CF00` without accepting IDA's merged tail chunk. This
   connects action, position, hit results, transient flags, and countdowns
   through the already exact outer phase before expanding the state controller.
4. **Central matching lanes.** Continue shaping `0x0045AEC0`, `0x0046B570`,
   `0x0046C290`, `0x0046D160`, `0x0046D370`, and `0x0046D620`, but treat this
   as exact-codegen work rather than the main source of new semantic unlocks.

## Character-family promotion rule

A fighter moves from `seed` to `mapped` only after its node records:

- RTTI/vtable ownership and shared virtual-slot mapping;
- at least one action-change or input/action root;
- at least two nontrivial action, projectile, spell, or owned-object xrefs;
- the derived type delta from the narrow shared `Character` contract;
- evidence links and unresolved fields without guessed gameplay terminology.

This keeps character work connected to the shared battle pipeline and prevents
progress from being dominated by isolated small functions.

## Character-pilot unlocks

```text
shared command layer [source-ready]
├── 0x00493300..0x00493B00 common gates [mixed exact/source-ready]
├── 0x0045BBB0 front-sequence readiness [exact]
├── 0x004631E0 shared action-transition input phase [source, 134/136]
└── 0x00493C90 front-record actions 690..696 [source, 950/950]
    ├── Reimu 0x00494050 spell/skill groups [mapped]
    ├── Marisa 0x004B9A60 spell/skill groups [mapped]
    ├── Sakuya 0x004DEF70 spell/skill groups [mapped]
    ├── Alice 0x004FA5C0 spell/skill groups [mapped]
    ├── Patchouli 0x0051EA60 spell/skill groups [mapped]
    └── Youmu 0x0053B040 spell/skill groups [mapped]

shared owned-object lifecycle [contracted]
├── 0x004454E0 four-byte VC8 deque push_back [library, exact]
├── 0x004B9540 return tracked objects to pool [semantics-ready]
├── fifteen 237-byte spawn entries [contracted]
│   ├── Sakuya 0x004DED80 [source-ready]
│   └── fourteen normalized twins [decompiled]
├── fifteen 94-byte acquire-and-link entries [source-ready]
│   ├── normalized token/list contract
│   └── fourteen roster functions emitted from one shared source body
├── fifteen 519-byte pool fresh/reuse entries [semantics-ready]
│   ├── low16 slot / high16 generation token contract
│   ├── Alice 0x38C allocation trait; all others 0x388
│   └── shared pool-container/lock/constructor helpers [contracted]
│       ├── 0x50-byte checked-container pool layout [source]
│       ├── 0x0040A710/20 lock wrapper [exact]
│       ├── four VC8 checked-container helpers [decompiled]
│       └── 0x004927D0 CharacterObject ctor [decompiled]
│           └── 0x0045E3A0 AttackObject ctor [decompiled]
│               └── 0x00421310 CEffectSprite ctor [next blocker]
└── Sakuya fighter pilot [source-ready]
    ├── 0x004DE8E0 pool acquire [contracted]
    ├── 0x004DEB80 acquire and link [source-ready]
    ├── 0x004DEC70 preallocate 256 then release [source-ready]
    └── 0x004DEF70 spell/skill/normal dispatcher [semantics-ready]
```

The parent-reference append block occurs once in every fighter spawn family,
and the release/reset helper has paired callers across all fifteen manager
families. These are the reusable onboarding contracts for the next ten-plus
character pilots; character-specific work should start at each vtable's spawn
and dispatcher roots rather than rediscovering container ownership.

## Refresh commands

```bash
python3 scripts/core-worklist.py --ready
python3 scripts/core-worklist.py --blockers --limit 30
python3 scripts/progress.py --check
```

When those manifests unlock a new high-impact node, update this document in the
same handoff. Keep address-level status changes in `config/functions.csv` only.
