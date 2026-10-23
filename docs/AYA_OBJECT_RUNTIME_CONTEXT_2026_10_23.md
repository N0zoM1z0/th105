# AyaObject runtime owner context, October 23, 2026

The selected `AyaObject::update_action_state` runtime view at `0x0061A290`
is unchanged. Four isolated compiler controls produce the same complete
canonical root payload as the selected source. This closes those specific
experiments without establishing original C++ types or canonical target equality.

## Observed target facts

Only Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
was inspected. IDA preflight rejects the open database's different hash;
all facts below come from the hash-attested PE, not that database.

Primary vtable `0x006C624C` points back to locator `0x006DB6FC`, whose
type descriptor is `0x006E8D98`, named `.?AVAyaObject@@`. The hierarchy
at `0x006DB710` has signature 0, attributes 1 and eight flattened bases
through array `0x006DB720`. Their observed descriptor prefixes are:

| Base | Contained bases | PMD (member, vbtable, displacement) |
| --- | ---: | --- |
| AyaObject | 7 | `(0, -1, 0)` |
| CharacterObjectEx<Aya, AyaObject> | 6 | `(0, -1, 0)` |
| CharacterObject | 5 | `(0, -1, 0)` |
| CObjectBase | 0 | `(0x330, -1, 0)` |
| AttackObject | 3 | `(0, -1, 0)` |
| AnimationObject | 2 | `(0, -1, 0)` |
| AnimationObjectBase | 0 | `(4, -1, 0)` |
| Environment | 0 | `(0x130, -1, 0)` |

Each inspected base descriptor has attributes `0x40`. The packet reads and
hashes its six-dword/24-byte core; optional trailing fields and complete
descriptor boundaries are unknown. RTTI alone does not establish member types.
The configured 17-slot primary surface includes update at `+0x28 -> 0x61A290`
and initializer at `+0x3C -> 0x61F0B0`. The shared RET at `+0x40 -> 0x41F890`
does not establish exclusive class ownership.

`AyaObjectPool_acquire @ 0x617DF0` pushes size `0x388` at `0x617E65` and
writes this Aya vtable at `0x617EAC` and `0x617FB9`. Its 519 target bytes hash
to `956188e519e6012e46a281fb619a68fc70699798c4aa0a30cf4a84561c8f4025`.
Allocation size supports the runtime storage model; it is not independent
proof of the original class definition or constructor/destructor behavior.

## Compiler controls and limits

All controls start from the selected post-807/854 source epoch. They retain
real used fields and source behavior, with no assembly, inert shaping state,
ABI substitutions or shared manifest/header changes.

| Frozen control | Change | Full canonical payload |
| --- | --- | --- |
| `owner-view` | RTTI-shaped layered bases, real sprite/deque members; lower state overlay retained | Identical |
| `owner-direct` | Layered owner with direct consumed attack fields; removes the lower overlay | Identical |
| `typed-facing` | Use declared signed-byte `facing_104` in action 852 | Identical |
| `owner-virtual` | Declare update as a true virtual override in the layered owner | Identical |

The owner models pass 16 compile-time size/offset guards: root `0x388`,
animation `0x158`, attack `0x330`, character `0x348`, sprite `4`, environment
`0x130`, action `0x13C`, handle state `0x330`, packet `0x340`, owner `0x348`,
parent `0x34C`, deque `0x350`, short state `0x364`, floats `0x370`, counters
`0x384`; the direct model additionally guards absolute phase `0x180` instead
of the overlay size. These are isolated runtime models, not reconstructed
nominal class or lifecycle definitions.

Each root payload is 20,132 bytes, metadata begins at 19,664, and SHA256 is
`17585ff8bc4fadd5f63619d3d52d470440955256a820ac76ca97daa7ee31f88f`.
Equality covers canonical code and adjacent metadata, not entire COFF files.
The virtual control explicitly resolves `@@UAEXXZ`; nonvirtual controls use
`@@QAEXXZ`. No fallback symbol lookup or acceptance-ledger change is involved.

Inference: these concrete inheritance, field-access and virtual-member forms
do not explain the selected root's code-generation differences. The direct
model also shows that the neutral result is not solely due to the lower
overlay. Other original types, lifetimes, inline visibility and TU/link context
remain open. These failed controls do not prove an LTCG impossibility.

## Reproduction and handoff

Public read-only packet:

```sh
python3 scripts/audit-aya-object-runtime-context.py
```

It verifies the target and reports RTTI/allocation observations plus the
selected object's full canonical hash. It requires the configured object;
build it with the normal focused command if absent. To repeat the four local
controls without changing source:

```sh
python3 scripts/audit-aya-object-runtime-context.py \
  --object build/aya-owner-context-20261023/owner-view.obj \
  --object build/aya-owner-context-20261023/owner-direct.obj \
  --object build/aya-owner-context-20261023/typed-facing.obj \
  --virtual-object build/aya-owner-context-20261023/owner-virtual.obj \
  --output build/aya-owner-context-20261023/context-audit.json
```

Private scope `build/aya-owner-context-20261023/` retains corresponding
CPP/header/object snapshots, canonical packets and formal comparisons.
Owner CPPs include `.analysis/aya-owner-context-20261023/AyaObjectOwnerView.hpp`;
restore the matching frozen header before reproducing an older compiler control.
The selected source and object were restored, then formally rebuilt at
`2026-10-23T04:40:06.813869Z`; `restored-final-formal.json` records the expected
19,522-byte mismatch at `+0x22` (target `0F`, source `9B`).

`pool-anchor-replay.json`, built at `2026-10-23T04:36:16.747290Z`, records
all 15 functions exact in a fresh serial
`cross-v106a-roster-object-pool-acquire` build/comparison. This is a focused
accepted-unit replay, not a new aggregate cold replay. No new exact credit.
Latest local controls and receipts remain uncompressed for the next session.
