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
├── Battle simulation -> docs/BATTLE_SIMULATION_SYSTEM.md
│   ├── frame-state controller [decompiled breadth]
│   │   ├── 0x0046FE80..0x00470940 ten-function controller island
│   │   ├── 0x0046FE80 setup/story/BGM phase [exact]
│   │   ├── 0x00470060 roster preparation [exact]
│   │   ├── thirteen direct dependencies [mixed breadth/exact]
│   │   ├── 0x004704D0 active simulation wrapper [exact]
│   │   ├── 0x004701C0 round initialization [exact]
│   │   ├── 0x00470300 terminal effect publication [exact]
│   │   ├── 0x00470360 spell-linked round resolution [exact]
│   │   ├── 0x004708B0 synchronized input gate [implemented, 127/129]
│   │   ├── 0x00427680 input availability leaf [exact]
│   │   ├── 0x0042A560 packed local control collection [exact]
│   │   ├── 0x00427AC0 synchronized publication [decompiled, 258/240]
│   │   └── 0x00470940 seven-state frame dispatcher [exact]
│   ├── fighter update [semantics-ready]
│   │   ├── action + owned-object callbacks [exact]
│   │   │   └── 0x0046A5B0 -> 0x00463610
│   │   ├── position/status/timers [semantics-ready]
│   │   │   ├── 0x0046A5C0 -> 0x00463760 outer phase [exact]
│   │   │   ├── 0x00459860 position phase [exact]
│   │   │   ├── 0x0045CDD0 transient status [implemented]
│   │   │   ├── 0x0045CF00 timer cleanup [implemented]
│   │   │   └── 0x00459D30 counter thresholds [exact]
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
├── Spell-card system -> docs/SPELL_CARD_SYSTEM.md
│   ├── assets and parsers [implemented: compiler-shaping remains]
│   │   ├── 0x00416A50 VC8 deque<4-byte>::push_back [library, exact probe]
│   │   ├── 0x00408A40 VC8 string append [library, exact probe]
│   │   ├── 0x00404F30 pooled texture creation [decompiled]
│   │   ├── 0x0040EB20/EE50/EF50/F050/F780 CSV reader API [decompiled]
│   │   ├── 0x00431430/0x00432310 VC8 map traversal/insert [library, exact]
│   │   ├── 0x00431950 SpellRecord deep copy [exact]
│   │   ├── short-key temporary tree and int-key record tree helpers [decompiled]
│   │   ├── 0x004325B0 first CSV parser [decompiled]
│   │   └── 0x00432E20 record/resource parser [implemented]
│   ├── spell data [source-ready]
│   │   ├── 0x00430DE0 loader selector [exact]
│   │   ├── 0x00430C80 post-load transform [implemented]
│   │   └── 0x004317A0 local/common lookup [implemented]
│   ├── spell runtime [source-ready]
│   │   ├── 0x00430C30/0x00430D90 deque front/select [exact]
│   │   ├── 0x98-byte two-short plus sprite sequence slot [contracted]
│   │   ├── 0x0045C440 VC8 deque grow [library exact]
│   │   ├── 0x0045C5A0 enqueue [exact]
│   │   ├── 0x00431860 indexed display callback [compiles, 234/234]
│   │   └── 0x0045BC30/0x0045C690 consume/prepare [implemented]
│   └── fighter integration [source-ready]
│       ├── 0x0045F140 battle-state initialization [implemented]
│       └── 0x00462050 spell-resource initialization [implemented]
│           ├── 0x0045E080 indexed wave resources [exact]
│           ├── 0x00460B50 PAT/palette records [decompiled]
│           └── 0x00464320 cut-in resource [implemented]
└── Character-specific families [mapped roots]
    ├── shared Character/CharacterEx/AttackObject contracts
    ├── shared command gates 0x00493300..0x00493580 [source-ready]
    │   ├── 0x00493300/0x00493490/0x00493540/0x00493580 [exact]
    │   └── 0x00493380 [implemented]
    ├── fifteen RTTI/vtable pilot rows -> docs/CHARACTER_PILOTS.md
    ├── fifteen vslot +0x3C action-change roots [decompiled breadth]
    │   ├── 36,677 bytes and 1,211 switch cases in the durable case manifest
    │   ├── 70 direct dependencies and twelve newly classified helpers
    │   ├── 0x00459970 motion reset shared by every roster member [exact]
    │   └── 0x004642D0 owned-object spawn adapter used by seven fighters [exact]
    ├── fifteen vslot +0x50 input/skill/spell roots [decompiled breadth]
    │   ├── 94,915 bytes and 172 switch cases in the durable case manifest
    │   ├── 227 direct-call cells across the roster
    │   └── fifteen raw tail-jump edges to 0x0045C7A0 [source-ready]
    ├── vslot +0x58 CPU action-policy family [decompiled breadth]
    │   ├── four overrides plus one default body shared by eleven fighters
    │   └── 80,524 bytes, 12,090 IDA lines, and 340 case occurrences
    ├── remaining sequence-lifecycle/event roots [decompiled breadth]
    │   ├── 22 bounded entries, 35,673 bytes, and 5,375 IDA lines
    │   ├── eleven vslot +0x5C sequence callbacks
    │   ├── ten vslot +0x60 bool event-code bridges
    │   └── Alice 0x004FA530 constructor boundary
    ├── fifteen owned-object spawn families [contracted]
    │   ├── one normalized 237-byte ABI/template
    │   ├── fifteen normalized acquire-and-link entries [source-ready]
    │   ├── fifteen normalized pool fresh/reuse entries [semantics-ready]
    │   ├── fourteen roster spawn entries [exact]
    │   └── Sakuya spawn source [source-ready]
    └── Sakuya fighter pilot [mapped]
        ├── 0x004DEEF0 fighter constructor [decompiled]
        ├── 0x004DECF0 manager constructor [decompiled]
        ├── 0x004DED80 owned-object spawn [implemented]
        ├── raw vslot +0x3C: 0x004DDB20 action change [decompiled]
        └── common-update vslot +0x50: 0x004DEF70 input/action [decompiled]
```

Supporting systems remain necessary but lower priority unless they block a core
edge: engine/scene, render/assets, input, network/replay, UI/profile, audio, and
platform/runtime. Their module boundaries are listed in `docs/ARCHITECTURE.md`.

## Unlock-first frontier

1. **Battle controller exact fan-out.** Setup, roster preparation, round
   initialization, terminal publication, round/spell resolution, active
   simulation, and the central dispatcher are exact. Finish the bounded
   transition/reset pair and shared fighter-pair initializer; keep the truthful
   127/129 RAII and 258/240 synchronized-publication blockers visible.
2. **PAT parser implementation.** `0x00462050` has target-sized complete source,
   `0x0045E080` is exact, and `0x00464320` is 197/199 bytes. The EH-bearing
   `0x20` group, `0x88` record, nested vectors, transient lists, and funclets in
   `0x00460B50` are now contracted. Before emitting its truthful body, recover
   the record lifecycle (`0x0045FF70`/`0x0045EF10`), group lifecycle
   (`0x00460500`/`0x00460570`/`0x00460920`/`0x00460A10`), deque growth
   (`0x0045F670`), and neutral checked-tree mutation bridges (`0x0045E6D0`,
   `0x0042C9F0`). Do not replace them with a guessed STL container.
3. **Fighter continuity codegen.** `0x00459D30` is exact and `0x0045CF00` now
   has complete source while preserving its authoritative boundary against
   IDA's merged tail chunk. Shape the bounded `+0x11E` mask schedule in
   `0x0045CDD0` and `+0x8B` store-order gap in `0x0045CF00`, then expand the
   state controller outward from the now-continuous exact outer phase.
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
├── 0x004631E0 shared action-transition input phase [exact]
│   └── 0x00463120 VC8 deque<short>::_Assign_n [library exact]
└── 0x00493C90 front-record actions 690..696 [source, 950/950]
    ├── Reimu 0x00494050 spell/skill groups [mapped]
    ├── Marisa 0x004B9A60 spell/skill groups [mapped]
    ├── Sakuya 0x004DEF70 spell/skill groups [mapped]
    ├── Alice 0x004FA5C0 spell/skill groups [mapped]
    │   └── 0x004FC0B0 object target-vector/state gate [exact, 14 calls]
    ├── Patchouli 0x0051EA60 spell/skill groups [mapped]
    ├── Youmu 0x0053B040 spell/skill groups [mapped]
    │   ├── 0x0053CA40 checked 44-byte record deque access [library exact]
    │   └── 0x0053CAA0 owner-record/action-state adapter [exact]
    ├── Remilia 0x00555D90 spell/skill groups [mapped]
    ├── Yuyuko 0x0056D8E0 spell/skill groups [mapped]
    ├── Yukari 0x0058BBA0 spell/skill groups [mapped]
    ├── Suika 0x005AE470 spell/skill groups [mapped]
    ├── Udonge 0x005D63F0 spell/skill groups [mapped]
    ├── Komachi 0x005F7190 spell/skill groups [mapped]
    ├── Aya 0x00617B20 spell/skill groups [mapped]
    ├── Iku 0x00630800 spell/skill groups [mapped]
    └── Tenshi 0x0064AB80 spell/skill groups [mapped]

shared owned-object lifecycle [contracted]
├── 0x00402A50 checked list erase [library exact, all 15 pool reuse paths]
├── 0x004454E0 four-byte VC8 deque push_back [library, exact]
├── 0x00406530/0x004065A0 shared float sine/cosine table lookups [source, compiler-shaping edge]
├── 0x00406710 atan2 radians-to-degrees helper [exact, 339 calls]
├── 0x00433BE0 oriented component setter [exact, 721 roster calls]
├── 0x00433C40 shared frame/time advance and vslot dispatch [exact]
├── 0x004FC3A0 related-object heading tracker [exact, 44 roster calls]
├── 0x004FC350 unparented related-object spawn adapter [exact, 1,026 roster calls]
├── 0x004FC4E0 state-6 phase counter transition [exact, 261 calls across 13 rosters]
├── 0x00520360 parented related-object spawn adapter [exact, 237 calls across 13 rosters]
├── 0x005203B0 state-4/8 phase counter transition [exact, 101 calls across 14 rosters]
├── 0x0053C7F0 ping-pong motion + periodic action-980 spawn [implemented, all 15 rosters]
├── 0x0064C090 owner-gated repeated effects 200/201 [exact, 228 roster calls]
├── 0x004B9540 return tracked objects to pool [implemented, 120/122]
├── fifteen 237-byte spawn entries [14 exact, Sakuya implemented]
│   ├── Sakuya 0x004DED80 [independent same-size source]
│   └── fourteen normalized twins [exact typed shared source]
├── fifteen 94-byte acquire-and-link entries [source-ready]
│   ├── normalized token/list contract
│   └── fourteen roster functions emitted from one shared source body
├── eight exact-template lifecycle families [120 target functions audited]
│   ├── fifteen 130-byte typed handle-pool constructors [decompiled]
│   ├── fifteen 103-byte manager-base constructors [exact]
│   ├── fifteen 100-byte manager-base destructors [decompiled]
│   ├── fifteen 117-byte preallocate/release passes [implemented]
│   └── fifteen 123-byte outer manager constructors [decompiled]
├── fifteen 519-byte pool fresh/reuse entries [implemented]
│   ├── low16 slot / high16 generation token contract
│   ├── Alice 0x38C allocation trait; all others 0x388
│   ├── Reimu and Sakuya canonical probes 514/519 [fresh path exact]
│   ├── all fifteen functions emitted from one audited source template
│   └── shared pool-container/lock/constructor helpers [contracted]
│       ├── 0x50-byte checked-container pool layout [source]
│       ├── 0x0040A710/20 lock wrapper [exact]
│       ├── four VC8 checked-container helpers [decompiled]
│       └── 0x004927D0 CharacterObject ctor [exact]
│           └── 0x0045E3A0 AttackObject ctor [exact]
│               └── 0x00421310 CEffectSprite ctor [source; linked-LTCG byte blocker]
└── Sakuya fighter pilot [source-ready]
    ├── 0x004DE8E0 pool acquire [implemented, canonical shared source]
    ├── 0x004DEB10 manager-base constructor [exact]
    ├── 0x004DEB80 acquire and link [source-ready]
    ├── 0x004DEC70 preallocate 256 then release [source-ready]
    ├── 0x004DECF0 outer manager constructor [decompiled]
    └── 0x004DEF70 spell/skill/normal dispatcher [semantics-ready]
```

The parent-reference append block occurs once in every fighter spawn family,
and the release/reset helper has paired callers across all fifteen manager
families. These are the reusable onboarding contracts for the next ten-plus
character pilots; character-specific work should start at each vtable's spawn
and dispatcher roots rather than rediscovering container ownership. The full
action-change/input-dispatch breadth survey is in
`docs/CHARACTER_ACTION_ROOTS.md`.

## Refresh commands

```bash
python3 scripts/core-worklist.py --ready
python3 scripts/core-worklist.py --blockers --limit 30
python3 scripts/progress.py --check
```

When those manifests unlock a new high-impact node, update this document in the
same handoff. Keep address-level status changes in `config/functions.csv` only.
