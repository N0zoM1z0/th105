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
│   ├── assets and parsers [contracted: remaining record/string blockers]
│   │   ├── 0x00416A50 VC8 deque<4-byte>::push_back [library, exact probe]
│   │   ├── 0x00404F30 pooled texture creation [decompiled]
│   │   ├── 0x0040EB20/EE50/EF50/F050/F780 CSV reader API [decompiled]
│   │   ├── 0x004325B0 first CSV parser [identified]
│   │   ├── 0x00432E20 record/resource parser [decompiled]
│   │   └── reader, image, small-string, and container contracts
│   ├── spell data [source-ready]
│   │   ├── 0x00430DE0 loader selector [exact]
│   │   ├── 0x00430C80 post-load transform [implemented]
│   │   └── 0x004317A0 local/common lookup [implemented]
│   ├── spell runtime [source-ready]
│   │   ├── 0x00430C30/0x00430D90 deque front/select [exact]
│   │   └── 0x0045BC30/0x0045C690 consume/prepare [implemented]
│   └── fighter integration [contracted]
│       ├── 0x0045F140 battle-state initialization [implemented]
│       └── 0x00462050 spell-resource initialization [decompiled, blocked]
└── Character-specific families [seed]
    ├── shared Character/CharacterEx/AttackObject contracts
    ├── per-character fighter and owned-object manager families
    └── Sakuya pilot [mapped]
        ├── raw vslot +0x3C: 0x004DDB20 action change [identified]
        └── common-update vslot +0x50: 0x004DEF70 input/action [identified]
```

Supporting systems remain necessary but lower priority unless they block a core
edge: engine/scene, render/assets, input, network/replay, UI/profile, audio, and
platform/runtime. Their module boundaries are listed in `docs/ARCHITECTURE.md`.

## Unlock-first frontier

1. **Spell record and ownership contracts.** The shared four-byte deque,
   pooled 512-by-256 card texture creation, and CSV reader API are now
   recovered. Continue with the remaining high-impact boundaries reported by
   `scripts/core-worklist.py --blockers`, especially `0x00408A40`,
   `0x00431430`, `0x00431950`, and `0x00432310`, then reconstruct the hard
   parser `0x00432E20` against these concrete contracts.
2. **Sakuya character pilot.** Use `0x004DDB20` and `0x004DEF70` to recover the
   derived vtable, action-code families, shared virtual contracts, and owned
   object-manager interactions. This lane should establish a repeatable
   onboarding method for the other fourteen fighters.
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

## Refresh commands

```bash
python3 scripts/core-worklist.py --ready
python3 scripts/core-worklist.py --blockers --limit 30
python3 scripts/progress.py --check
```

When those manifests unlock a new high-impact node, update this document in the
same handoff. Keep address-level status changes in `config/functions.csv` only.
