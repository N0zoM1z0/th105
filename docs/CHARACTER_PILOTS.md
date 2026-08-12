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
| Reimu | `0x006B013C` | `0x004787B0` | `0x00491480` | `0x00491410` | `0x00494050` | `0x00490C60` | `0x004A2A50` | mapped |
| Marisa | `0x006B0594` | `0x004A2F40` | `0x004B81F0` | `0x004B81B0` | `0x004B9A60` | `0x004B7AB0` | `0x004CA440` | mapped |
| Sakuya | `0x006B0924` | `0x004CA870` | `0x004DDB20` | `0x004DDAF0` | `0x004DEF70` | `0x004DD2A0` | `0x004E9610` | mapped |
| Alice | `0x006B0BEC` | `0x004E9A20` | `0x004F9320` | `0x004F92D0` | `0x004FA5C0` | `0x004F88D0` | `0x0050E780` | mapped |
| Patchouli | `0x006B0EBC` | `0x0050EC80` | `0x0051D140` | `0x0051D070` | `0x0051EA60` | `0x0051C5C0` | `0x0052F950` | mapped |
| Youmu | `0x006B1154` | `0x0052FDA0` | `0x00539D70` | `0x00539D00` | `0x0053B040` | `0x005397E0` | `0x005448A0` | mapped |
| Remilia | `0x006B13D4` | `0x00544D40` | `0x00554A00` | `0x00616680` | `0x00555D90` | `0x005544A0` | `0x0055CFD0` | mapped |
| Yuyuko | `0x006B165C` | `0x0055D4A0` | `0x0056C490` | `0x0056C460` | `0x0056D8E0` | `0x0056BDC0` | `0x0057A5C0` | mapped |
| Yukari | `0x006B18DC` | `0x0057AA60` | `0x00589F20` | `0x00589EA0` | `0x0058BBA0` | `0x00588DF0` | `0x00597B20` | mapped |
| Suika | `0x006B1B9C` | `0x00598100` | `0x005ACC10` | `0x005ACBE0` | `0x005AE470` | `0x005ABDF0` | `0x005BEEE0` | mapped |
| Udonge | `0x006B1E3C` | `0x005BF460` | `0x005D4610` | `0x005D45C0` | `0x005D63F0` | `0x005D3EA0` | `0x005E53D0` | mapped |
| Komachi | `0x006B2074` | `0x005E5860` | `0x005F5DE0` | `0x005F5DB0` | `0x005F7190` | `0x005F5700` | `0x006013C0` | mapped |
| Aya | `0x006B22DC` | `0x006018F0` | `0x006166A0` | `0x00616680` | `0x00617B20` | `0x00615EA0` | `0x0061F870` | mapped |
| Iku | `0x006B2534` | `0x0061FDE0` | `0x0062F4B0` | `0x0062F480` | `0x00630800` | `0x0062E910` | `0x0063C1D0` | mapped |
| Tenshi | `0x006B279C` | `0x0063C900` | `0x006495C0` | `0x00649520` | `0x0064AB80` | `0x00648850` | `0x00658830` | mapped |

The meanings of `+0x3C` and `+0x50` are proven by the shared update path and
Sakuya behavior.  The other four columns deliberately retain neutral slot
labels until callers and fields establish their roles.

## Primary-vtable `+0x28` breadth

The fifteen `+0x28` roots now have a complete address-level structural census
in `config/character-vslot28-roots.csv`. The shared fighter phase at
`0x00463610` loads each fighter vtable, calls raw slot `+0x28`, and ignores the
incidental return. Every root dispatches from the 16-bit action field at
`Fighter+0x13C`; the manifest records the observed numeric table ranges and
dispatch sites without claiming original method or per-action names.

Together the roots account for 918,209 ledger bytes. All fifteen share a
twenty-callee action/frame/effect fingerprint. Character-specific callees
remain explicit so common low-action skeletons can fan out without erasing
high-action behavior. Alice, Youmu, and Yuyuko were the first structural pilots:
Alice has the shortest clean generic layout, Youmu is the smallest body but has
a distinct `0x0045D320` branch, and Yuyuko exposes a particularly clean
`301..418` versus `501..731` split. Tenshi is a 43-callee outlier.

The ledger remains the accepted boundary authority. Sakuya is the strongest
regression case: IDA reports only a `0xA227` primary chunk, while address
queries retain the same owner through the target `ret` at `0x004DCD91` and the
ledger span covers 74,937 function-body bytes. Reimu, Alice, Patchouli,
Remilia, Suika, Aya, and Tenshi likewise have IDA body-size differences caused
by non-contiguous chunks; none permits an automatic ledger resize.

All fifteen roots are now structurally `decompiled`. The
durable pilot manifest distinguishes
`ida_hexrays` from `exact_target_tables`: the former records pseudocode lines
and switches, while the latter records target-disassembly lines and decodes
the compiler's byte-index maps directly when a 54–67 KiB dispatcher defeats
Hex-Rays. Both forms require complete numeric table labels, direct and default
branches, field-width/read-write unions, callees, ABI/return topology, and
bounded slice points. The declaration-only ABI is in
`src/characters/Vslot28ActionStateRoots.hpp`.

The second wave proved why that distinction matters. Patchouli yielded 6,380
Hex-Rays lines and 107 top-level switch labels, while its accepted ledger span
still overrides IDA's seven-byte non-contiguous-body discrepancy. Marisa and
Udonge both passed IDA target, vtable, boundary, callee, and ABI checks but
Hex-Rays failed. Exact PE instructions and compressed byte maps recovered 125
and 105 table labels respectively, plus the direct `300/540/795/797/798` and
`300/520/795` singleton branches. Headless Ghidra was used as the strict
fallback; it recovered Udonge control flow but did not reconstruct switches,
so the byte maps—not guessed pseudocode—remain the case authority.

The third wave adds three boundary/outlier regressions. Reimu's 81,488 tracked
body bytes coexist with an instruction-supported 81,550-byte entry-to-ret span;
Hex-Rays and strict headless Ghidra both failed, so 126 compressed-table labels
plus direct 300/560 branches are instruction-backed. Remilia retains its
three-byte non-contiguous difference while contributing a 7,740-line Hex-Rays
view and 104 top-level labels. Tenshi retains a seven-byte body/span difference
and its character-local 43-callee, `+0x780..+0x7C0` extension outlier. A ledger
body-byte count is not silently replaced by a contiguous-span length.

The fourth wave closes the three highest-risk remaining shapes. Sakuya's exact
ledger span remains authoritative over an IDA primary chunk short by `0x8292`;
108 table labels and five direct branches were recovered from target bytes.
Yukari's contiguous 7,351-line view proves a character-local four-table layout
with three direct bridges. Suika's 79,426 tracked body bytes coexist with a
79,435-byte entry-to-ret span; its 113 labels and offset widths come from exact
maps and target instructions after Hex-Rays failure.

The final wave closes Aya, Iku, and Komachi. Iku and Komachi contributed
7,566- and 7,737-line IDA views with 108 and 103 table labels. Aya's IDA
decompile failed, but strict no-GUI Ghidra recovered 7,188 lines and 111
top-level labels. Its manifest uses `headless_ghidra` and retains the fallback's
type-propagation and default-location caveats; the `__thiscall` ABI comes from
the exact vtable/shared caller and ledger, not Ghidra's `__fastcall` guess.

Youmu action 200 uniquely reaches `0x0045D320`: after publishing byte `+0x47E`
as one, the helper writes `Fighter+0x670 = 3` and forwards constants `4` and
`0x00FFFF00` through the subobject at `+0x674`. The manifest retains this
neutral contract rather than assigning an effect/gameplay name. Yuyuko's
`301..418` and `501..731` compressed tables have no cross-band fallthrough,
making them independent source packets after their shared preamble. Alice's
accepted span splits into six address-bounded control-flow regions, including
separate low, middle, and high compressed tables.

The roster breadth gate is complete. Next split each root into bounded source
packets and fan shared low-action contracts only after normalized instruction
evidence; do not emit a monolithic placeholder body.

Refresh a bounded ignored work packet with the verified IDA backend instead of
requesting all fifteen giant decompiles at once:

```bash
python3 scripts/character-root-survey.py --kind vslot28 \
  --fighter Alice --output build/alice-vslot28-survey.json
```

Repeat `--fighter` for a small non-overlapping pilot set. The survey now emits
an explicit partial row and continues sibling roots when Hex-Rays fails; a
whole-roster decompile is still only a milestone operation. A partial row never
grants `decompiled`: route it to exact-target table decoding or headless
Ghidra, then satisfy the same manifest gate.

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

### Roster construction boundary

`0x004632D0` is now source-reconstructed as the 15-way fighter factory. It
selects `MatchSetup::Side+0x00`, allocates the observed family span, calls the
corresponding derived constructor with that `Side`, enters `0x00462050`, stores
the result at `BattleSlotState+0x28+4*slot`, and returns the slot. The exact
allocation table is retained in `src/battle/FighterFactory.cpp`; no common-size
or guessed derived hierarchy is used.

Every derived constructor calls `0x00461A90`, now real source in
`src/battle/FighterBaseInitialization.cpp`. That common base packet performs
the `AttackObject` construction, initializes three sprite-compatible headers,
initializes the spell-data and `+0x674` subobjects, creates three
allocation-backed members, and copies
`Side+0x00/+0x04/+0x05/+0x06/+0x08/+0x1C` to observed fighter fields. Both
source packets compile with VC8. Their first strict comparison fail-closes at
an unregistered local EH-handler `DIR32`; this is an exact-work boundary, not
a matching claim.

## Shared command layer

The functions at `0x00493300..0x00493580` are not Reimu-specific despite
their address placement. Target xrefs prove that they form a shared prelude
and lookup layer used by all fifteen input/action dispatchers:

| Address | Contract | Coverage | Source result |
| ---: | --- | --- | --- |
| `0x00493300` | signed gate selecting actions `208..210` | exactly 15 callers | exact 117/117 |
| `0x00493380` | flagged/ranged gate selecting `220`, `222..224` | exactly 15 callers | complete 258/258, epilogue placement differs |
| `0x00493490` | flagged state-158 gate selecting `225/226` | exactly 15 callers | exact 164/164 |
| `0x00493540` | set action; flag window `>=10`; finalize command | 160 calls in 15 dispatchers | exact 50/50 |
| `0x00493580` | signed lower-bound command table lookup | 783 direct xrefs | exact 78/78 |
| `0x004935D0` | ordered threshold gates for actions `208..210` | exactly 15 callers | exact 504/504 |
| `0x004937D0` | mirrored direction gates for actions `200/201` | 14 dispatcher callers | exact 333/333 |
| `0x00493920` | counted/repeated gate for action `202` | exactly 15 callers | complete 226/226, vslot prefetch differs |
| `0x00493A10` | mirrored counted/repeated gate for action `203` | exactly 15 callers | complete 226/226, vslot prefetch differs |
| `0x00493B00` | counted action `214` plus direction angle | exactly 15 callers | exact 393/393 |
| `0x00493C90` | front-record categories selecting `690..696` | exactly 15 callers | complete 950/950, instruction order differs |
| `0x0045BBB0` | front sequence availability and slot threshold gate | exactly 30 sites, two in each dispatcher | exact 118/118 |
| `0x004631E0` | pack shared input phase before action transition | 407 sites in 28 functions | exact 136/136 |

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

Alice's four-byte larger fresh allocation is the only observed pool deviation;
the spawn instructions themselves remain template-identical. Of the four
normalized calls, only acquire-and-link is character-specific; deque
`push_back`, array allocation, and `memcpy` share the same targets in every
member. Preserving the incoming parent in a stable alias before publishing it
to `object->parent_34c`, then passing the published lvalue to deque `push_back`,
reproduces the target scheduling without relying on C++03 evaluation order.
All fourteen non-Sakuya rows now compare exactly at 237/237 bytes from one
typed emitted body. Sakuya keeps its independently compiled same-size source
and remains `implemented` until its own strict comparison is exact.

The acquire-and-link column is independently stronger: all fifteen entries are
94-byte instruction-template twins after normalizing the three call operands at
`+0x18`, `+0x3F`, and `+0x4A`; the normalized SHA-256 is
`7cb85121ffe61ec2759825d7c64d10c2ceb25fc3281cee12510f562b449a5457`.
`RosterOwnedObjects.cpp` now emits the fourteen non-Sakuya functions from one
typed layout/body. VC8 produces 90 bytes for each, matching the prior Sakuya
probe and preserving the complete semantics; the common remaining four-byte
difference is register allocation and address-taken-local scheduling. These
rows are `implemented`, not `matching`.

The pool-acquire column is also one 519-byte fresh/reuse template. Normalizing
the fourteen `CALL rel32` operands at `+0x31`, `+0x7F`, `+0x98`, `+0xD8`,
`+0xF1`, `+0x108`, `+0x112`, `+0x14C`, `+0x15E`, `+0x17C`, `+0x18D`,
`+0x1A7`, `+0x1D8`, and `+0x1EB`, plus vtable immediates at `+0xBF` and
`+0x1CB`, gives SHA-256
`e32ec446ed55edd7ad233b42d9f892a2a81288e355bc0a2136864aac6fd55024`
for every non-Alice fighter. Alice becomes identical after additionally
parameterizing the allocation immediate at `+0x76`, `0x38C` instead of
`0x388`.

Fresh and reuse paths both increment the dword at pool `+0x30` with wrap to
one after `0xFFFF`, publish a token as low-16 slot/high-16 generation, call the
shared object constructor at `0x004927D0`, zero object
`+0x34C/+0x354/+0x358/+0x35C/+0x360`, and install the character vtable. The
pool view also exposes storage at `+0x04`, a generation range at `+0x18`, a
reusable-node container at `+0x24`, and a synchronization member at `+0x34`.
The complete common `0x50`-byte storage view is now represented by
`CharacterObjectPoolStorage`: checked pointer slots at `+0x04`, checked
generation words at `+0x14`, checked free-slot list at `+0x24`, counter at
`+0x30`, and a `CriticalSectionWrapper` at `+0x34`. The wrapper's enter and
leave methods at `0x0040A710/20` are exact 11-byte matches; the four checked
container helpers are fully decompiled but remain VC8 STL probe candidates.
The Reimu canonical source now uses the real checked STL containers and a
non-primary tail base.  Its 514-byte standalone VC8 probe is exact through the
entire fresh path; the target's remaining five bytes come from keeping the
handle in `EBX` while spilling the checked-list iterator in the reuse path.
That register/spill choice is deferred to the linked-LTCG island.  The exact
target clone manifest supports an audited fan-out, so the fourteen non-Sakuya
pool rows are now `implemented`.  Sakuya retains its older independent object
view and remains a separate integration task.

The shared constructor is now bounded at `0x004927D0` (78 bytes) with exactly
thirty roster-pool call sites, once from each fresh path and once from each
reuse path. It calls base constructor `0x0045E3A0`, initializes dwords
`+0x330/+0x334/+0x338/+0x340`, words `+0x174/+0x176/+0x344/+0x346`, and
installs `CharacterObject` vtable `0x006B001C`. The base constructor is the
193-byte `AttackObject` constructor at `0x0045E3A0`: it installs vtable
`0x006AEB44`, initializes the observed collision prefix through `+0x32C`, and
calls `0x00421310` on `this+4`. That `CEffectSprite` constructor and its
RTTI chain through `CSpriteEx`, `CSpriteBase`, and global `IColor` is now
represented in source. The base destructor and
derived scalar deleting destructor compare exactly; the 79-byte constructor is
same-size and differs only in VC8 vptr/EH-state store order. This removes the
ownership/layout uncertainty from the shared pool source path while leaving a
linked-LTCG comparison as the constructor's final byte blocker.

AttackObject RTTI further places `AnimationObjectBase` at `+0x04` and
`Environment` at `+0x130`; exact source establishes an `AnimationObject` size
of `0x158` and reproduces the complete AttackObject constructor 193/193 bytes.
CharacterObject RTTI places a non-primary `CObjectBase` at `+0x330` before the
primary `AttackObject` in declaration/construction order. Its two-field
constructor explains why `+0x334/+0x330` are initialized before the call to
`AttackObject_ctor`. The recovered multiple-inheritance source matches all
78/78 bytes, so the fifteen 519-byte pool-acquire functions are now the shared
frontier rather than a constructor-layout blocker.

## Roster manager lifecycle expansion

Exact target normalization extends the owned-object lifecycle from three to
eight fifteen-member families. The five newly audited families below preserve
every instruction and normalize only proven four-byte EH, vtable, or direct
call operands. Each family has one normalized SHA-256 across all fifteen
members. This proves shared structure and authorizes controlled semantic
fan-out; it does not by itself make any function byte-matching source.

| Fighter | Pool ctor `130` | Base ctor `103` | Base dtor `100` | Preallocate `117` | Manager ctor `123` |
| --- | ---: | ---: | ---: | ---: | ---: |
| Reimu | `0x00492B10` | `0x00492DB0` | `0x00492E80` | `0x00492F10` | `0x00492F90` |
| Marisa | `0x004B91B0` | `0x004B9470` | `0x004B95C0` | `0x004B9650` | `0x004B96D0` |
| Sakuya | `0x004DE850` | `0x004DEB10` | `0x004DEBE0` | `0x004DEC70` | `0x004DECF0` |
| Alice | `0x004F9EB0` | `0x004FA150` | `0x004FA220` | `0x004FA2B0` | `0x004FA330` |
| Patchouli | `0x0051E330` | `0x0051E5F0` | `0x0051E6C0` | `0x0051E750` | `0x0051E7D0` |
| Youmu | `0x0053A830` | `0x0053AAF0` | `0x0053ABC0` | `0x0053AC50` | `0x0053ACD0` |
| Remilia | `0x00555600` | `0x005558C0` | `0x00555990` | `0x00555A20` | `0x00555AA0` |
| Yuyuko | `0x0056D1C0` | `0x0056D480` | `0x0056D550` | `0x0056D5E0` | `0x0056D660` |
| Yukari | `0x0058B310` | `0x0058B5D0` | `0x0058B6A0` | `0x0058B730` | `0x0058B7B0` |
| Suika | `0x005ADD50` | `0x005AE010` | `0x005AE0E0` | `0x005AE170` | `0x005AE1F0` |
| Udonge | `0x005D5CD0` | `0x005D5F70` | `0x005D6040` | `0x005D60D0` | `0x005D6150` |
| Komachi | `0x005F6A90` | `0x005F6D30` | `0x005F6E00` | `0x005F6E90` | `0x005F6F10` |
| Aya | `0x00617390` | `0x00617650` | `0x00617720` | `0x006177B0` | `0x00617830` |
| Iku | `0x006300F0` | `0x00630390` | `0x00630460` | `0x006304F0` | `0x00630570` |
| Tenshi | `0x0064A480` | `0x0064A720` | `0x0064A7F0` | `0x0064A880` | `0x0064A900` |

The canonical Sakuya evidence establishes the common layout: a polymorphic
typed handle manager occupies outer manager-base `+0x04..+0x53`, its tracked
list starts at `+0x54`, and the multiple-inheritance outer manager places that
base at `+0x04` with its fighter owner at `+0x64`. All fifteen preallocation
passes now have emitted shared source: acquire and track until count `256`,
then tail-call the shared handle-release path. The Reimu standalone body is
117 bytes against the 117-byte target; only the `EBX`/`EBP` allocation schedule
differs, so this family is ready for later per-function exact tuning without
blocking broader character recovery. The adjacent manager-base constructor is
fully recovered as a polymorphic `CHandleManagerEx<Object>` member at `+0x04`
followed by the tracked list at `+0x54`; all fifteen constructor instances now
compare exactly at 103/103 bytes.

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
the tracking nodes. Its stale Ghidra size was corrected from 112 to the IDA-
verified contiguous 122 bytes ending at `retn 0x004B95B9`. A genuine checked
`std::list<CharacterObject *>` source reproduces 120/122 bytes; only the token
load/push register differs (`EAX/50` target versus `EDX/52` standalone). It is
therefore a reusable-pool preallocation pass, not a permanent 256-entry active
list. The manager-base view is 0x60 bytes: pool at `+0x04`, tracking list at
`+0x54`; the outer owner remains at `+0x64`.

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

The same bounded split is now grounded for the first three pilot roots rather
than only for Sakuya. Reimu `0x00494050` is 6952 bytes and Marisa `0x004B9A60`
is 7664 bytes; both occupy fighter vtable slot `+0x50`. Their spell/front-record
paths call the exact `0x0045BBB0` readiness gate and shared `0x00493C90`
selector before committing 600-series actions. Their 5xx skill paths converge
on `0x004631E0` immediately before raw action vslot `+0x08`. Observed examples
include Reimu `600/601/606/608/609/610/614/619`, Marisa `600..619` with an
alternate `658` branch, and Sakuya `600..609/656`. These action IDs and call
orders are facts; spell/skill labels remain inferred from the surrounding
record and command data flow.

The next three vtable `+0x50` roots are now bounded as well:

| Fighter | Dispatcher size | Front-record spell mapping | 500-series shared phase calls | Next character-specific roots |
| --- | ---: | --- | ---: | --- |
| Alice | 6677 | records `200..209` -> actions `600..609` | 31 calls plus one tail edge | `0x004FA2B0`, `0x004FA530`, `0x004FC0B0` |
| Patchouli | 6351 | `200..207/210` -> `600..607/610`; `201` also -> `651` | 25 calls | `0x0051C5C0`, `0x0051D140`, `0x0052F950` |
| Youmu | 6017 | records `200..207` -> actions `600..607` | 23 calls plus two tail edges | `0x005397E0`, `0x00539D70`, `0x005448A0` |

Each dispatcher has exactly two `0x0045BBB0` sites and one `0x00493C90`
site. Their skill trees use command word `+0x728`, derived gates in the
`+0x605..+0x611` range, and per-family latches beginning at `+0x754`, but the
action priorities differ. The tables above therefore support one shared
control skeleton with character traits; they do not support copying one
fighter's action map into another.

The following wave establishes the same boundary for three more fighters:

| Fighter | Dispatcher size | Front-record spell mapping | `0x004631E0` edges | Next character-specific roots |
| --- | ---: | --- | ---: | --- |
| Remilia | 5415 | `200..207` -> `600..607` | 19 calls plus one tail edge | `0x005544A0`, `0x00554A00`, `0x0055CFD0` |
| Yuyuko | 6180 | `200..208` -> `600..608`; later `201/207` -> `651/657` | 25 calls | `0x0056BDC0`, `0x0056C490`, `0x0057A5C0` |
| Yukari | 6233 | `200..207/215` -> `600..607/615`; later `206` -> `656` | 23 calls plus one tail edge | `0x00588DF0`, `0x00589F20`, `0x0058BA30` |

These three also each have two `0x0045BBB0` sites and one `0x00493C90`
site. Remilia uses six grounded command families including high-bit
`0x40000000/0x20000000` variants; Yuyuko has primary and secondary 500-series
clusters; Yukari has both positive-derived and zero-gated trees. The observed
fields remain neutral `command_bits_728`, derived gates, and family latches
until action implementations or runtime evidence justify gameplay names.

Yukari's `0x0058BA30` is now an exact 367-byte character-specific source
unit. It preserves the shared mirrored action-`200/201` gates, then after
committing action `201` compares the exact stage-boundary classifier result
with facing and conditionally calls raw vslot `+0x0C` with value `4`. This is
the first extracted role-specific branch from the mapped roster dispatchers;
the common `0x004937D0` version remains the implementation used by the other
fourteen fighters.

The third wave takes the pilot map beyond the requested ten-character mark:

| Fighter | Dispatcher size | Front-record spell mapping | `0x004631E0` edges | Next character-specific roots |
| --- | ---: | --- | ---: | --- |
| Suika | 5849 | `200..208` -> `600..608`; later `200` -> `650` | 21 calls plus one tail edge | `0x005ABDF0`, `0x005ACC10`, `0x005BEEE0` |
| Udonge | 6684 | `200/202/203/205..209` -> `600/602/603/605..609`; later `200/202/205` -> `650/652/655` | 28 calls | `0x005D3EA0`, `0x005D4610`, `0x005E53D0` |
| Komachi | 6181 | `200..206/211` -> `600..606/611` | 26 calls plus one tail edge | `0x005F5700`, `0x005F5DE0`, `0x006013C0` |

Suika, Udonge, and Komachi again share the two sequence-ready sites, the one
front-record selector site, command word `+0x728`, derived gates, and four
family latches. Their sparse spell tables and secondary paths differ enough
that the per-character traits must preserve explicit record/action pairs.

The final wave completes all fifteen roster pilot boundaries:

| Fighter | Dispatcher size | Front-record spell mapping | `0x004631E0` edges | Next character-specific roots |
| --- | ---: | --- | ---: | --- |
| Aya | 7161 | primary `200/201/202/205/206/211/212` -> `600/601/602/605/606/611/612`; later `203/211/212` -> `603/661/662` | 29 calls plus one tail edge | `0x00611D80`, `0x00615EA0`, `0x006166A0`, `0x0061F870` |
| Iku | 6302 | primary `200..203/205..210` -> `600..603/605..610`; later `200/210` -> `650/660` | 24 calls | `0x0062E910`, `0x0062F4B0`, `0x0063C1D0` |
| Tenshi | 5352 | `200..207` -> `600..607`; later `207` -> `657` | 17 calls plus one tail edge | `0x00648850`, `0x006495C0`, `0x0064C090`, `0x00658830` |

Aya and Iku use sparse record tables and later-priority spell branches; Tenshi
uses a contiguous eight-record primary table but a distinct later `657` path.
All three retain the roster-wide two sequence-ready sites, one front-record
selector, command word, derived gates, and four family latches. No small
Aya-only or Iku-only dispatcher callee analogous to Yukari `0x0058BA30` was
observed; Tenshi `0x0064C090` is instead a bounded owned-object effect-emission
helper. It is now exact at 200 bytes and is not Tenshi-only: target xrefs prove
228 direct calls distributed across all fifteen roster object-action roots.
Its two modes accept owner actions `50..149` or `71..149`, then emit effect
codes `200` and `201` the requested positive number of times from the object's
current position and facing.

## Roster action-change family

The fighter primary-vtable slot `+0x3C` is now breadth-mapped for all fifteen
roster members.  Unlike the CPU policy slot, every fighter owns a distinct
body.  IDA completed every switch and direct-callee inventory; the
machine-readable case order and callee addresses are preserved in
`config/character-action-change-cases.csv`.

| Fighter | Body | Bytes | Cases | <300 | 300s | 400s | 500s | 600s | 700+ | Direct callees |
| --- | --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| Reimu | `0x00491480` | 3,767 | 96 | 15 | 13 | 11 | 28 | 19 | 10 | 10 |
| Marisa | `0x004B81F0` | 2,446 | 91 | 0 | 14 | 20 | 31 | 15 | 11 | 5 |
| Sakuya | `0x004DDB20` | 2,106 | 78 | 0 | 14 | 15 | 24 | 16 | 9 | 1 |
| Alice | `0x004F9320` | 1,551 | 71 | 2 | 14 | 14 | 26 | 10 | 5 | 3 |
| Patchouli | `0x0051D140` | 3,132 | 80 | 2 | 14 | 15 | 21 | 14 | 14 | 10 |
| Youmu | `0x00539D70` | 1,424 | 60 | 0 | 16 | 12 | 21 | 8 | 3 | 3 |
| Remilia | `0x00554A00` | 1,802 | 73 | 0 | 15 | 14 | 20 | 14 | 10 | 1 |
| Yuyuko | `0x0056C490` | 2,083 | 88 | 0 | 14 | 14 | 28 | 16 | 16 | 2 |
| Yukari | `0x00589F20` | 3,441 | 89 | 15 | 13 | 13 | 26 | 10 | 12 | 9 |
| Suika | `0x005ACC10` | 2,577 | 85 | 0 | 16 | 15 | 23 | 15 | 16 | 4 |
| Udonge | `0x005D4610` | 4,033 | 118 | 40 | 12 | 14 | 25 | 11 | 16 | 9 |
| Komachi | `0x005F5DE0` | 1,971 | 68 | 0 | 14 | 15 | 23 | 11 | 5 | 3 |
| Aya | `0x006166A0` | 2,049 | 75 | 0 | 14 | 14 | 31 | 11 | 5 | 4 |
| Iku | `0x0062F4B0` | 1,842 | 74 | 0 | 14 | 15 | 25 | 16 | 4 | 2 |
| Tenshi | `0x006495C0` | 2,453 | 65 | 0 | 14 | 14 | 17 | 9 | 11 | 4 |

The numeric bands are structural facts, not gameplay names: they count the
recovered switch labels by action number.  The only direct callee shared by
all fifteen bodies is `0x00459970`, now exact at 27/27 bytes; it clears the
four motion floats at `+0xF4..+0x100`. The shared manager adapter
`0x004642D0`, reached by seven fighters, is also exact at 66/66 and proves
the fighter `+0x658` manager pointer plus vslot `+0x04` spawn ABI. The wave
adds 70 caller/callee edges and promotes twelve
previously unclassified shared or character-specific dependencies, including
the 4,830-byte `BaseFighter_initialize_common_action`, the checked
spell-sequence window dispatcher `0x0045C8B0`, and the roster-owned object
spawn adapter `0x004642D0`.

All fifteen input/action selector roots also share the same tail-jump to
`0x0045C7A0`. That 265-byte spell-sequence rotation now has complete source,
making its front-slot copy/pop/enqueue contract available to every character
pilot instead of rediscovering it per roster member. Its remaining 247/265
standalone delta is bounded to the original CSprite local copy/destructor and
linked EH folding; an EH-bearing probe recovered the target prologue through
`+0x94` but did not prove an exact source patch.

These bodies are now `decompiled`, not `implemented`: their complete case
topology and dependency graph are durable, but no placeholder source is
emitted.  The next source wave should factor the common 300/400/500 action
bands and add per-character 600/700 traits, using the CSV rows as independent
address-bounded implementation packets.

The companion vslot `+0x50` input/skill/spell family is now at the same breadth
gate. Its fifteen ledger-accepted bodies cover 94,915 bytes and 13,703 complete
IDA pseudocode lines. The 172 switch labels, 227 direct-call cells, and shared
`0x0045C7A0` tail edge are preserved row-by-row in
`config/character-input-dispatch-cases.csv`. All fifteen roots are
`decompiled`; source work can now split common `200` command handling from each
fighter's `300/320` skill/spell records without rediscovering monolithic
control flow.

## CPU action-policy vslot family

The fighter primary vtable slot `+0x58` is a second roster-wide command
boundary, separate from the normal skill/spell input dispatcher at `+0x50`.
IDA data xrefs prove four character overrides and one default body shared by
the other eleven fighters:

| Policy body | Target span | Vtable owners | IDA lines | Case occurrences / unique labels |
| --- | ---: | --- | ---: | ---: |
| `0x0048CBA0` | 15,999 | Reimu | 2,390 | 56 / 51 |
| `0x004B38A0` | 16,229 | Marisa | 2,362 | 71 / 51 |
| `0x004F4650` | 16,354 | Alice | 2,668 | 85 / 49 |
| `0x005CFE00` | 15,910 | Sakuya, Patchouli, Youmu, Remilia, Yuyuko, Yukari, Suika, Udonge, Komachi, Iku, Tenshi | 2,330 | 64 / 48 |
| `0x00611D80` | 16,032 | Aya | 2,340 | 64 / 48 |

The ownership matrix above is a target fact: each entry is read directly from
the fighter vtable whose `+0x3C` action-change and `+0x50` input-dispatch slots
are already mapped. The CPU-policy terminology is an inference supported by
the bodies, not original debug information. Every body reads the paired
fighter at `+0x170`, computes absolute X/Y separation from `+0xEC/+0xF0`,
switches on action `+0x13C`, repeatedly calls the exact random helpers, reads
the checked front sequence at `+0x55C`, and writes the control block
`+0x6B4..+0x6D0`, command flags `+0x724/+0x728`, and policy counters
`+0x764..+0x76E`.

The SHA-attested breadth pass covers 80,524 target bytes and 12,090 complete
IDA pseudocode lines. Its 340 case-label occurrences, unique numeric labels,
five-callee sets, and non-overlapping vtable ownership are validated in
`config/character-cpu-policy-cases.csv`. All five rows are now `decompiled`;
this records complete structure without pretending that the large policy
bodies have source implementations.

All five bodies have the same complete direct-callee set:
`mt19937_next_u32`, `selector_random_roll`, `atan2_degrees`, the checked
sequence accessor `0x0045B9E0`, and VC8 `_ftol2_sse`. The shared prefix clears
`+0x724/+0x728` and `+0x6BC..+0x6D0`, decrements `+0x768`, refreshes the
random word at `+0x76E`, and returns immediately when the paired fighter's
short `+0x174` is non-positive. These facts are captured as declarations and
offset assertions in `src/characters/CpuActionPolicies.hpp`; no placeholder
function body is emitted.

The caller-side control-mode dispatcher at `0x00462E20` supplies the vslot
meaning boundary: control byte `+0x72C == 2` selects vslot `+0x5C`, value `3`
selects a separate shared path, and other values select this `+0x58` policy.
The exact human/CPU/replay labels for every numeric mode remain unresolved.
Later source work should first factor the common 64-case skeleton, then layer
Reimu/Marisa/Alice/Aya traits; attempting five unrelated 16-KB functions would
discard the strongest recovered structure.

## Sequence-lifecycle and event-bridge breadth

The final unclassified character-command roots in the core graph now have one
SHA-attested IDA inventory in
`config/character-lifecycle-event-roots.csv`. The 31 bounded entries cover
48,181 target bytes, 7,578 complete pseudocode lines, 683 case-label
occurrences, and 181 direct-call cells. Every IDA boundary agrees with the
ledger in the attested full-roster survey.

Fifteen vslot `+0x5C` roots are neutral `update_sequence_lifecycle` callbacks.
They reset per-frame command/output fields, inspect the checked front sequence,
advance character-specific `700`-series action state, and emit owned effects.
Fifteen vslot `+0x60` roots are `bool (event_code)` bridges. Their common event
families cover position/camera publication, action reset, spell/terminal
transitions, effect emission, and character-specific `120+` or `130+` codes.
The manifest records numeric labels without guessing gameplay terminology.

The remaining row, Alice `0x004FA530`, is not forced into either virtual
family: its complete body calls the base fighter constructor, publishes the
Alice vtable, initializes the float at `+0x138` to `-6.0`, allocates the owned
manager, and stores it at `+0x658`. It is retained as the constructor boundary
that completed the same address-selected breadth wave.

All 31 entries are `decompiled` and have declarations in
`src/characters/SequenceLifecycleEventRoots.hpp`; there are no placeholder
bodies. Every fighter now has both vslot families recorded, so the next
implementation wave can fan out by shared vslot role and numeric case family
instead of rediscovering monolithic per-character control flow.

The Sakuya manager's raw primary-vtable slot `+0x04` is `0x004DED80`, a complete object-spawn
boundary. It obtains a new Sakuya object from the manager base at `+0x04`,
copies owner state into object fields `+0x130`, `+0x160`, `+0x168`, and
`+0x348`, optionally links a parent at `+0x34C`, optionally allocates and
copies a dword payload at `+0x340`, publishes position at `+0xEC/+0xF0`, and
sets facing/action through byte `+0x104` and raw vslot `+0x08`. Parent objects
hold a VC8 `std::deque<SakuyaObject *>` at `+0x350`; its exact 117-byte
push-back specialization owns its map and four-pointer blocks but not the child
pointees. The complete Sakuya spawn source compiles to the target size,
237/237 bytes; its independent comparison still has parent-reference and final
register-order differences. The shared non-Sakuya specialization uses a stable
incoming-parent alias and all fourteen of those entries are exact.

The complete fifteen-character action-change and input-dispatch breadth map is
maintained in `docs/CHARACTER_ACTION_ROOTS.md`. It records accepted ledger
boundaries, switch families, the common command prelude, both machine-readable
case manifests, and the three action-root IDA boundary conflicts that must
remain fail-closed.

## Next waves

1. Use the recovered
   `CEffectSprite -> CSpriteEx -> CSpriteBase -> IColor` boundary to emit the
   normalized fifteen-way pool-acquire source using the complete `0x50`-byte
   storage and exact lock contracts; retain `0x00421310` as the first
   linked-LTCG island.
2. Split Sakuya's complete `0x004DEF70` matrix into source-backed spell, skill,
   and normal-action blocks, beginning with the spell-record `600..609/656`
   selector because it links parser data directly to character behavior.
3. Apply that dispatcher split to Reimu and Marisa, then fan out through the
   remaining roster while preserving one bounded character/action family per
   claim.
