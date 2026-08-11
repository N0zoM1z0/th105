# Character pilot map

This is the address-level onboarding map for the fifteen playable fighter
families.  It complements the subsystem tree in `RECONSTRUCTION_MAP.md`; the
function ledger remains authoritative for function status.

All addresses below come from RTTI-owned vtables in the exact Japanese 1.06a
target.  The constructor-installed vtable pointer is the `vtable` column.  The
other columns are target function pointers observed in that table, not
recovered original names.  Raw offsets exclude the preceding RTTI locator.

| Fighter | vtable | `+0x28` | `+0x3C` action change | `+0x44` | `+0x50` input/action | `+0x5C` | `+0x60` | State |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | --- |
| Reimu | `0x006B013C` | `0x004787B0` | `0x00491480` | `0x00491410` | `0x00494050` | `0x00490C60` | `0x004A2A50` | seed |
| Marisa | `0x006B0594` | `0x004A2F40` | `0x004B81F0` | `0x004B81B0` | `0x004B9A60` | `0x004B7AB0` | `0x004CA440` | seed |
| Sakuya | `0x006B0924` | `0x004CA870` | `0x004DDB20` | `0x004DDAF0` | `0x004DEF70` | `0x004DD2A0` | `0x004E9610` | mapped |
| Alice | `0x006B0BEC` | `0x004E9A20` | `0x004F9320` | `0x004F92D0` | `0x004FA5C0` | `0x004F88D0` | `0x0050E780` | seed |
| Patchouli | `0x006B0EBC` | `0x0050EC80` | `0x0051D140` | `0x0051D070` | `0x0051EA60` | `0x0051C5C0` | `0x0052F950` | seed |
| Youmu | `0x006B1154` | `0x0052FDA0` | `0x00539D70` | `0x00539D00` | `0x0053B040` | `0x005397E0` | `0x005448A0` | seed |
| Remilia | `0x006B13D4` | `0x00544D40` | `0x00554A00` | `0x00616680` | `0x00555D90` | `0x005544A0` | `0x0055CFD0` | seed |
| Yuyuko | `0x006B165C` | `0x0055D4A0` | `0x0056C490` | `0x0056C460` | `0x0056D8E0` | `0x0056BDC0` | `0x0057A5C0` | seed |
| Yukari | `0x006B18DC` | `0x0057AA60` | `0x00589F20` | `0x00589EA0` | `0x0058BBA0` | `0x00588DF0` | `0x00597B20` | seed |
| Suika | `0x006B1B9C` | `0x00598100` | `0x005ACC10` | `0x005ACBE0` | `0x005AE470` | `0x005ABDF0` | `0x005BEEE0` | seed |
| Udonge | `0x006B1E3C` | `0x005BF460` | `0x005D4610` | `0x005D45C0` | `0x005D63F0` | `0x005D3EA0` | `0x005E53D0` | seed |
| Komachi | `0x006B2074` | `0x005E5860` | `0x005F5DE0` | `0x005F5DB0` | `0x005F7190` | `0x005F5700` | `0x006013C0` | seed |
| Aya | `0x006B22DC` | `0x006018F0` | `0x006166A0` | `0x00616680` | `0x00617B20` | `0x00615EA0` | `0x0061F870` | seed |
| Iku | `0x006B2534` | `0x0061FDE0` | `0x0062F4B0` | `0x0062F480` | `0x00630800` | `0x0062E910` | `0x0063C1D0` | seed |
| Tenshi | `0x006B279C` | `0x0063C900` | `0x006495C0` | `0x00649520` | `0x0064AB80` | `0x00648850` | `0x00658830` | seed |

The meanings of `+0x3C` and `+0x50` are proven by the shared update path and
Sakuya behavior.  The other four columns deliberately retain neutral slot
labels until callers and fields establish their roles.

## Shared unlock inherited by every fighter

`0x004632D0` constructs one of fifteen derived fighters and then calls
`0x00462050`.  The shared initialization chain is now:

```text
0x00462050 initialize_fighter_spell_resources [implemented, 333/333 bytes]
├── 0x00460B50 PAT + palette + parsed records [identified]
├── 0x0045E080 64 indexed character wave handles [exact]
├── 0x00430DE0 spell-data loader selector [exact]
├── face bitmap and embedded sprite setup
├── up to ten back/spell bitmaps in Fighter+0x68C
└── 0x00464320 cut-in resource at Fighter+0x3D0 [implemented, 197/199]
```

The `0x00460B50` contiguous body is `0x00460B50..0x00461A7C`, 3885
bytes.  Its previous ledger size was short by `0x68`; IDA and the target's
terminal `ret` agree on the corrected boundary.  Its local EH tails are not
part of that contiguous span.

## Shared command layer

The functions at `0x00493300..0x00493580` are not Reimu-specific despite
their address placement. Target xrefs prove that they form a shared prelude
and lookup layer used by all fifteen input/action dispatchers:

| Address | Contract | Coverage | Source result |
| ---: | --- | --- | --- |
| `0x00493300` | signed gate selecting actions `208..210` | exactly 15 callers | exact 117/117 |
| `0x00493380` | flagged/ranged gate selecting `220`, `222..224` | exactly 15 callers | complete 229/258 |
| `0x00493490` | flagged state-158 gate selecting `225/226` | exactly 15 callers | exact 164/164 |
| `0x00493540` | set action; flag window `>=10`; finalize command | 160 calls in 15 dispatchers | exact 50/50 |
| `0x00493580` | signed lower-bound command table lookup | 783 direct xrefs | complete 78/78, prologue order differs |
| `0x004935D0` | ordered threshold gates for actions `208..210` | exactly 15 callers | exact 504/504 |
| `0x004937D0` | mirrored direction gates for actions `200/201` | 14 dispatcher callers | exact 333/333 |
| `0x00493920` | counted/repeated gate for action `202` | exactly 15 callers | complete 226/226, vslot prefetch differs |
| `0x00493A10` | mirrored counted/repeated gate for action `203` | exactly 15 callers | complete 226/226, vslot prefetch differs |
| `0x00493B00` | counted action `214` plus direction angle | exactly 15 callers | exact 393/393 |
| `0x00493C90` | front-record categories selecting `690..696` | exactly 15 callers | complete 920/950 |

The gates test observed fields `+0x104`, `+0x13C`, `+0x484`, `+0x4B8`,
`+0x6B4`, `+0x6B8`, `+0x724`, and `+0x75A`, refresh the common snapshot at
`0x004631E0`, and use raw vslot `+0x08` to change action. The lookup treats
its key as signed 16-bit, performs lower-bound on the tree pointed to by
`Fighter+0x160`, checks only iterator validity/end, and returns a signed word
from the mapped entry at `+0x10`. It deliberately does not require exact key
equality.

These contracts move shared command parsing ahead of character-specific
branches: every pilot may now call the same source declarations instead of
reconstructing ten opaque helpers independently.  The action-214 gate writes
`-135/-90/-45/0/45/90/135/180` (with zero selected by two neutral cases) to
the derived-field position `+0x740`; this is an observed angle table, while
the gameplay label for the resulting motion remains deliberately unset.

## Roster owned-object spawn matrix

Every playable fighter owns the same manager/object lifecycle boundary. IDA
disassembly proves that all fifteen spawn entries are 237 bytes and end in
`ret 0x24`. After zeroing only the four direct `CALL rel32` displacements at
function offsets `+0x08`, `+0x53`, `+0x73`, and `+0x93`, every body has the
same SHA-256,
`1624928279d7f6257673ad5f943304704689115380798615d25055e71a40f8ad`.
This is instruction-template identity, not an exact source comparison.

| Fighter | Spawn | Acquire and link | Pool acquire | Fresh span | Object vtable |
| --- | ---: | ---: | ---: | ---: | ---: |
| Reimu | `0x00493110` | `0x00492E20` | `0x00492BA0` | `0x388` | `0x006B00B4` |
| Marisa | `0x004B9860` | `0x004B94E0` | `0x004B9240` | `0x388` | `0x006B050C` |
| Sakuya | `0x004DED80` | `0x004DEB80` | `0x004DE8E0` | `0x388` | `0x006B089C` |
| Alice | `0x004FA3C0` | `0x004FA1C0` | `0x004F9F40` | `0x38C` | `0x006B0B64` |
| Patchouli | `0x0051E870` | `0x0051E660` | `0x0051E3C0` | `0x388` | `0x006B0E34` |
| Youmu | `0x0053ADF0` | `0x0053AB60` | `0x0053A8C0` | `0x388` | `0x006B10CC` |
| Remilia | `0x00555BA0` | `0x00555930` | `0x00555690` | `0x388` | `0x006B134C` |
| Yuyuko | `0x0056D6F0` | `0x0056D4F0` | `0x0056D250` | `0x388` | `0x006B15D4` |
| Yukari | `0x0058B840` | `0x0058B640` | `0x0058B3A0` | `0x388` | `0x006B1854` |
| Suika | `0x005AE280` | `0x005AE080` | `0x005ADDE0` | `0x388` | `0x006B1B14` |
| Udonge | `0x005D6200` | `0x005D5FE0` | `0x005D5D60` | `0x388` | `0x006B1DB4` |
| Komachi | `0x005F6FA0` | `0x005F6DA0` | `0x005F6B20` | `0x388` | `0x006B1FEC` |
| Aya | `0x00617930` | `0x006176C0` | `0x00617420` | `0x388` | `0x006B2254` |
| Iku | `0x00630600` | `0x00630400` | `0x00630180` | `0x388` | `0x006B24AC` |
| Tenshi | `0x0064A990` | `0x0064A790` | `0x0064A510` | `0x388` | `0x006B2714` |

The shared ABI takes parent and related-object pointers, action, X/Y, two byte
arguments, and an optional dword payload. It returns a new object, publishes
the owner at `+0x168/+0x348`, copies owner state from `+0x130/+0x160`, writes
the parent at `+0x34C`, appends the child through the exact deque specialization
at parent `+0x350`, and calls object vslot `+0x08` with the action. The related
pointer is dereferenced at `+0x170` without a null guard. The outer manager
layout is likewise shared: secondary manager-base view at `+0x04`, tracked
list at outer `+0x58`, and fighter owner at `+0x64`.

Alice's four-byte larger fresh allocation is the only observed roster
deviation; the spawn instructions themselves remain template-identical. The
fourteen newly named rows are therefore `decompiled`, while only Sakuya has a
source body. A reusable emitted template must preserve separate character pool
calls and the Alice tail before those rows can advance to `implemented`.

## Sakuya pilot

Sakuya's constructor at `0x004DEEF0` has one explicit base argument, calls the
shared fighter constructor `0x00461A90`, installs vtable `0x006B0924`, allocates
`0x68` bytes, and creates the owned-object manager stored at `Fighter+0x658`.
Its sole caller is the fifteen-way fighter factory at `0x004632D0`.

The manager constructor at `0x004DECF0` first installs the shared
`ICharacterObjectManager` vtable, constructs a secondary manager base at
`+0x04`, then installs the two Sakuya manager vtables `0x006B08F4` and
`0x006B08EC`. The target's two EH cleanup states destroy the secondary base
and restore/clean the primary interface, proving a C++ multiple-inheritance
boundary rather than merely two unrelated raw pointers. It stores
the owning Sakuya pointer at `+0x64` and calls `0x004DEC70` with target count
`256`. That function acquires and tracks objects until the unsigned target is
reached, then `0x004B9540` returns every handle token to the pool and frees only
the tracking nodes. It is therefore a reusable-pool preallocation pass, not a
permanent 256-entry active list. The manager-base view is 0x60 bytes: pool at
`+0x04`, tracking list at `+0x54`; the outer owner remains at `+0x64`.

The fresh branch of `0x004DE8E0` allocates `0x388` bytes, installs SakuyaObject
vtable `0x006B089C`, and initializes the observed parent/reference fields. The
complete allocation span is represented in `src/characters/Sakuya.hpp`; bytes
that remain semantically unknown stay explicitly opaque. The Sakuya fighter
extension begins at `+0x730` and currently reaches `+0x757`.

`0x004DDB20` is a no-argument `__thiscall` action-change handler.  It switches
on the 16-bit action at `+0x13C`, uses the common velocity reset at
`0x00459970`, and falls back to the shared common-action initializer for
unhandled actions.  Observed families include ordinary ground/air actions in
`300..418`, skill actions in the `500` series, spell actions beginning at
`600`, and terminal/special actions `797` and `798`.  Sakuya fields written by
the complete switch include shorts `+0x730..+0x738`, floats `+0x73C`, `+0x740`,
and `+0x74C`, and bytes `+0x750` and `+0x754`.

`0x004DEF70` is likewise a no-argument `__thiscall`; `0x00459E50` tail-jumps
to raw vslot `+0x50` and ignores its incidental register return.  The function
selects actions from command bits and current ground/air state.  Proven groups
are:

| Group | Default actions | Alternate actions | Level byte | one-use/cancel byte |
| --- | --- | --- | ---: | ---: |
| command group 236 | `500/501` | `505/506` | `+0x608` | `+0x754` |
| command group 214 | `520/521` | `525/526` | `+0x609` | `+0x755` |
| command group 623 | `540/541`, air `542/543` | `545/546`, air `547/548` | `+0x60A` | `+0x756` |
| high-bit command group | `560/561` | `565/566` | `+0x60B` | observed adjacent cancel byte |
| spell records `200..209` | actions `600..609` | record `206` also reaches `656` | n/a | n/a |

The complete IDA control-flow recovery also enumerates normal actions
`300..309`, `320..322`, and `400..418`, split by ground/air state, facing-
relative direction fields, and signed command-table thresholds. The shared
front-record helper tries actions in the exact priority
`690, 691, 695, 696, 692, 693, 694`; records `0..5` select all but `690`, while
`690` accepts the observed record range `100..199`.

Successful selections call the shared phase at `0x004631E0`, may set bit
`0x08` at `+0x491` when the observed window is at least ten, and invoke raw
vslot `+0x08` to change action. The target has no stack arguments and returns
the selected path's low byte. All branches are now covered by the 850-line IDA
decompile, so the ledger records `decompiled`; source remains split into
bounded command groups to avoid a monolithic guessed transcription.

The Sakuya manager's raw primary-vtable slot `+0x04` is `0x004DED80`, a complete object-spawn
boundary. It obtains a new Sakuya object from the manager base at `+0x04`,
copies owner state into object fields `+0x130`, `+0x160`, `+0x168`, and
`+0x348`, optionally links a parent at `+0x34C`, optionally allocates and
copies a dword payload at `+0x340`, publishes position at `+0xEC/+0xF0`, and
sets facing/action through byte `+0x104` and raw vslot `+0x08`. Parent objects
hold a VC8 `std::deque<SakuyaObject *>` at `+0x350`; its exact 117-byte
push-back specialization owns its map and four-pointer blocks but not the child
pointees. The complete spawn source compiles to the target size, 237/237 bytes;
remaining differences are parent-reference argument scheduling and the final
field-load/register order.

## Next waves

1. Promote the fourteen acquire-and-link helpers in the roster matrix. They are
   normalized 94-byte twins of Sakuya's complete contract and are the direct
   blockers for a shared emitted spawn template.
2. Split Sakuya's complete `0x004DEF70` matrix into source-backed spell, skill,
   and normal-action blocks, beginning with the spell-record `600..609/656`
   selector because it links parser data directly to character behavior.
3. Apply that dispatcher split to Reimu and Marisa, then fan out through the
   remaining roster while preserving one bounded character/action family per
   claim.
