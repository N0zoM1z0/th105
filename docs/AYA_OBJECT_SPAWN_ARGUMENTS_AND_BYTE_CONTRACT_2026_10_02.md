# AyaObject spawn arguments and byte call contract, 2026-10-02

## Bounded result

**Observed:** the AyaObject action-state root remains
`[0x0061A290,0x0061EED2)`,19,522 bytes, SHA-256
`18c813a20cea427b2c3577e2612e3f2e949a191ee2496dc9204331758bebb895`,
in the canonical Japanese1.06a PE
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
This follows [the sequence-gate/rate-store checkpoint](AYA_OBJECT_SEQUENCE_GATES_AND_RATE_STORE_2026_10_02.md).

852's three emission groups now express coordinates directly as call
arguments within each facing branch. A local `AyaObjectSpawnCallView`
models the effective low-byte facing/field33c contract, using the existing
64CCB0 body. Its ordinary x86 argument slots remain four bytes each; the
physical thiscall footprint remains28 bytes. This adds no helper body.
The unit records one explicit alias to that existing target. Shared headers,
wrapper/manager source and accepted units' relocation contracts are unchanged.
Original C++ wrapper parameter types are not uniquely established.

The fresh configured whole-root result remains **nonexact at+0x22**,
target0F/candidate56. Candidate metadata starts19,340 versus target19,524:
gap220->184. The19,808-byte section tail supplies the19,522-byte comparison
window; that window includes182 bytes after candidate metadata and is not
a candidate-body hash. Its SHA-256 is
`d9ea58e50c3335c4c89da7603f77c2f5fbc5f54971edeb24d171e2505dd277b9`.
Retained LF source SHA-256 is
`c0a8cea5fefaa43cb76fb68902db3fa5b4799c3054a10ca928ff87cd37c34baa`.
No exact-ledger credit is added.

## Argument evaluation and stack reuse

**Observed:** target first emission61C69C pushes copied-word count3 before
evaluating the coordinate RNG. Each facing path then pushes payload pointer,
field1 and facing, calls selector640, and stores converted Y directly into
the outgoing argument cell. The selector's cdecl limit cell becomes the Y
cell, without ADD ESP4 and a separate named-Y store/reload. Constant X is
then written to the next outgoing cell before spawn64CCB0. The second group
uses the same structure. Old source evaluated named x/y locals before
starting the outer call, which introduced those extra storage operations.

Target third group similarly computes Y from selector640 and unsigned
subtraction180, stores outgoing Y, then calls selector128 for X. Direct
argument expressions recover that Y-before-X call order under pinned VC8.
The explicit float X expression remains; removing only that cast is
byte-neutral and is not retained as a separate source change.

**Observed diagnostic:** first two emission groups occupy target
`[61C639,61C7F7)` and candidate `[61C60A,61C7C8)`,446 bytes/126 instructions.
All noncall encodings and translated internal edges agree. Ten external
CALL instructions have the same fixed targets, with different REL32
displacements because their placements differ by47 bytes. This is
placement-translated instruction/edge evidence, not canonical byte equality.
The preceding194-byte rate/sequence interval likewise keeps its43 instruction
forms at candidate `[61C99A,61CA5C)`, now42 bytes earlier than target; its
external CALL displacement changes. Do not carry its earlier same-address
raw-byte equality forward to this new object.

## Byte consumption through the real manager

**Observed:** target64CCB0 forwards four DWORD argument slots through
manager primary-vtable slot+4 and returns with RET28. Its78-byte body hash is
`9aedc5ceafe11e034397b151e7406e9495ac57c200514d560ac6b3a5b038048b`.
Copying a DWORD through this wrapper alone does not distinguish an original
int parameter from a byte parameter carried in an ordinary four-byte slot.

The actual Aya manager vtable is6C62A4; its slot+4 is618470, and its
preceding complete-object locator6DB7A8 refers to type descriptor6E8DF4,
`CharacterObjectManager<Aya,AyaObject>`. In that237-byte target manager,
618512 reads facing BYTE from saved ESP+20 and618516 reads field33c BYTE
from ESP+24.618530 and618548 store those bytes to object+104/+33C. RET36
closes the nine-argument manager call. Manager body hash:
`e29f767ab7c746db971de525ba7b1f694668b8e3b20e5bba09bc2c35e046e45b`.
These are independent raw width/vtable/RTTI observations, consistent with
the already accepted roster-spawn source's byte parameters.

**Inferred call view:** signed-char facing and unsigned-char field33c
express the meaningful consumed bytes while preserving the stack footprint.
VC8 then omits three MOVZX instructions that the old int-facing declaration
introduced in852's alternate facing paths. This projection of the actual
call chain does not identify the original decorated class/method or prove
that64CCB0's original declaration itself used these byte types. The shared
int-declared wrapper remains unchanged. Unit-local alias
`AyaObjectSpawnCallView_spawn_unparented_related_object=0x0064CCB0`
binds this synthetic view to the same ordinary target body; it supplies no
new implementation or exact acceptance.

An additional control routes the other18 source call expressions in this
root through the same view. The complete comparison window is byte-neutral.
That scope expansion is not retained and does not resolve other actions.

## Scoped argument model and owner effects

A fail-closed decoder-driven model executes the emission prefix for450
cases: nine signed/large time values, five facing bytes, five bounded RNG
return schedules and optional callback changes of time/facing. Both sides
agree in RNG limit order, action, coordinate/payload bits, copied count and
consumed facing/field bytes. Recorded unused facing high bits also agree
in these cases. RNG and spawn are mocked; FSTP32 explicitly uses nearest-even
rounding. This is neither whole-game execution nor a proof of global x87
control/exception behavior. The separate two641-value Y interval checks
retain unsigned wrap, including rare selector upper640.

852's target span is1,201 bytes/310 instructions; retained candidate is
1,206/312, down from1,248/318. Its remaining extra MOVCL plus two branch-local
MOVSX operations replace target's single MOVSX, accounting for the five-byte
size difference. Negative FILD/FLD order and scratch homes still differ.
The earlier int-facing promotion's FIMUL remains rejected.

Raw root diagnostics rise2/34->3/34: entry,800 and980.800's375-byte/107-
instruction owner now agrees under the owner audit; this is not function
acceptance. The same source changes also alter other physical owners:
855 candidate321->337 versus target332,861358->427 versus target358,
and9001737->1729 versus target1773. There is no uniform owner improvement.
Default802 still includes post-RET MOVEDI,EDI alignment in its diagnostic
span and remains unaccepted.33 destinations/zero splits persist.

| Sequential control | Metadata | Raw diagnostics |852 span |
| --- | ---: | ---: | ---: |
| Fresh baseline |19304|2/34|1248|
| First direct emission |19288|2/34|1232|
| First two direct emissions |19272|2/34|1216|
| All three direct emissions |19348|3/34|1215|
| Implicit X cast control |19348|3/34|1215|
|852 byte contract, retained |19340|3/34|1206|
| Other18 calls through view, byte-neutral |19340|3/34|1206|

## Verification and remaining work

```bash
python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
python3 scripts/audit-giant-action-owners.py aya-object-vslot28 \
  build/match-units/GptWeb_AyaObjectActionState.obj \
  --unit gpt-web-aya-object-vslot28-full-root --json
```

Final configured reports share prefix `build/aya-spawn-arguments-final-`.
Controls, byte-contract binding probes, emission model and width/interval
checker are under `.analysis/aya-spawn-arguments-20261002/`; control objects
and source/object/window-hashed `controls-summary.json` are under
`build/aya-spawn-arguments-20261002/`. Existing-object private controls do
not have configured build provenance. The adopted alias is now in the
normal configured root contract; final audits use the standard scripts.
The existing workflow test's obsolete `direction = 1` source-spelling
assertion is replaced by a check that the local call view binds64CCB0.
Its source-present/nonexact separation checks remain. This does not promote
any interval diagnostic or mocked execution result to exact acceptance.

Full raw target traversal closes all4,630 instructions/all19,522 bytes
through seven switches. Guards remain124/124, with the established853
twelve-role pairing and902 path lead. Prior853 select7 return/owner reload,
unsigned Y and quarter-motion observations remain. IDA still fails on the
wrong executable; no IDA output, factory adapter or target patch is used.
No aggregate cold replay is claimed. Run the mandatory CI/whitespace gate
before commit.

Remaining work includes facing conversion/FILD placement, float scratch
homes and X rounding carrier, movement/decrement register ownership,855/861
physical sharing, other actions' values/lifetimes and original TU/LTCG
context. Full numerical/exception closure remains unknown. Do not repeat
the neutral X-cast or other18-call scope control as a search strategy.
