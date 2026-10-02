# Youmu copied-input pointer and action601 arguments, 2026-10-02

## Retained result

`Youmu_dispatch_action_state_vslot28 @ 0x00530200` remains **nonexact** over
37,692 callable bytes. Its local spawn declaration now carries the observed
copied-input address as `const void *payload`, removing the56 original integer-
address casts. Action601 now computes and rounds its X argument in each real
range branch's call expression. One unsigned direction snapshot supports the
full direction argument and signed integer multiplication. Four unused scalar
hypotheses are removed; their removal is byte-neutral.

Fresh configured VC8 comparison first differs at `+0xCA / 0x005302CA`, target
`64`, candidate `38`. Candidate metadata begins at `+0x9310`, versus target
`+0x933C`: the callable is44 bytes shorter. Section tail is38,772 bytes.
All97 physical destinations/33 low entries remain distinct. Strict owner
diagnostics improve **27/98 -> 31/98**, gaining `mid:500`, `mid:501`, `mid:505`
and `mid:506`, without losses. There is **zero new canonical exact credit**.

Target callable SHA-256:
`19f2d4fba4f6ea626b69a28f4717d0fcfae06ea97e95ddb24e656e0ea518ed74`.
Retained CRLF source SHA-256:
`784e5356d0f80f09e6621213d73529aeb71f1602ba23a8f03a3cabc0f7141f7a`.
Canonical compared candidate-window SHA-256:
`cb91ae38d3c8fce149a8a0de8002dfc5a6ade8e4c196c9270b08bed2e68bad0d`.
That window includes adjacent metadata and is not a candidate body hash.

## Observed copy and forwarding contract

All new target observations use the hash-attested original Japanese1.06a PE,
SHA-256 `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`,
entry `0x0068B9D2`. Fresh IDA preflight fails against the other `10350095...`
executable; that session is not used. No new Ghidra process, database write
or target patch is involved.

**Observed:** forwarding helper `465190` loads the count and input pointer
from the caller stack, forwards them as unchanged dwords, loads the manager
from fighter`+658`, invokes its virtual slot4 and returns with `RET 1C`.
Its66-byte body SHA-256 is
`80aab8cb379377dc179c3e1311599ab890885fa92ffd5ecf075ff6c3df15a7fc`.

The Youmu consumer `53B1C0` loads count at `53B217`, skips allocation/copy for
nonpositive counts and allocates count*4 bytes otherwise. `53B237` loads the
source pointer, `53B23E` tests it, and `53B248..53B252` prepares count*4/source/
destination and invokes memcpy. The source pointer is used as copy input,
not stored in the child; the separately allocated destination is stored at
child`+340`. This closes the counted copy contract in this body without
establishing a unique C++ element type or original const declaration.
The237-byte consumer body SHA-256 is
`634f526c3634e39085d6544255bed23375652a9ec154049390662ed2fbbf5454`.

Raw aligned `.rdata` at `6C5118` points to this consumer. Complete123-byte
constructor `53B0A0` corroborates the primary table: `53B0F1` writes `6C5114`
to `[ESI]`, `53B0F7` writes secondary table `6C510C` to the base at`+4`, and
`53B0FD` publishes owner at`+64`. Thus primary slot4 is `53B1C0`; the source
and exact ledgers for the manager are corroboration, not a substitute for
these fresh raw pointer/instruction observations.

**Inferred local view:** an opaque copied-input pointer expresses the49
observed physical payload addresses without inventing float/unsigned/struct
element identity. The declaration and56 original cast removals are byte-
neutral against the preceding root. The56 old source calls become57 after
action601's one call becomes two source branch calls; VC8 shares the actual
machine call, so physical spawn sites remain49.

Only this root unit's relocation spelling changes from the integer-address
facade to `?spawn_owned_object_via_manager@YoumuActionStateView@th105@@QAEHHMMHEPBXH@Z`.
Its target remains `465190`. The accepted forwarding helper, manager bodies,
shared headers and global relocation maps stay unchanged. Compatible local
pointer views do not recover a unique original decorated prototype.

## Observed601 evaluation and rounding

The inclusive angle interval accepts ordered0..180. Outside and unordered
angles use multiplier175 and control byteFF; inside uses150 and control1.
The source preserves those outcomes, the signed direction multiplication,
the float payload, and `unsignedRoll + (index*45 + 22.5)` value association.

| Target path | Argument prefix | Signed product / Y store | X add / float home | Shared call |
| --- | --- | --- | --- | --- |
| Inside | `536E04..536E10` | `536E13 / 536E19` | `536E25 / 536E2B..536E2F` | `536E7E` |
| Outside | `536E44..536E51` | `536E54 / 536E5A` | `536E66 / 536E6C..536E70` | `536E7E` |

**Observed:** each path loads the unsigned direction once, loads Y, prepares
count/payload/control/direction arguments, computes the signed integer
product, writes outgoing Y and performs FILD/self-X addition. It then rounds
X through a dword store/reload before joining the common outgoing-X store and
spawn call. The prior candidate instead joined before the X addition and
prepared the trailing arguments afterward; it owned only one physical self-X
FADD where the target owns two.

**Inferred source:** real branch calls with an explicit float X expression
recover both additions, intermediate dword rounding and the argument-prefix/
outgoing-Y schedule naturally. Retaining one real unsigned direction snapshot
per branch recovers the observed unsigned load reused for signed arithmetic;
reading the signed/unsigned field twice produced a different byte-load/widening
schedule. No fake local, custom ABI or assembly is required for this recovery.

Register/temporary homes and narrow control argument upper bits still differ.
The target outside path pushes dword`FFFFFFFF` using a sign-extended byte
immediate, while the candidate's unsigned-byte view materializes
dword`000000FF`. The consumer uses the low
byte at `53B266` and stores it at child`+33C`. This establishes compatible
consumed values, not canonical equality or a unique original signedness.
The fifth argument view remains unchanged; byte consumption alone cannot
prove a signed-char or int source declaration.

## Serial controls and scoped diagnostics

| Private VC8 control | Observation | Disposition |
| --- | --- | --- |
| Opaque pointer/cast removal only | Same compared window as the preceding checkpoint;27/98, metadata`+9314`. | Retained type recovery. |
|601 branch argument expressions, direct signed/unsigned field reads |31/98; gains500/501/505/506, no losses; metadata`+9320`. | Refined with the observed shared direction load. |
|601 expressions with one real direction snapshot |31/98, same gains/no losses; metadata`+9310`. | Retained. |
| Remove four unused scalar declarations | Same compared window as preceding row. | Retained cleanup. |
|710 branch argument expressions alone |26/98, loses low11; metadata`+932C`. | Not retained. |
|601 and710 expressions together |12/98, loses15 previous owners despite metadata`+9338`, only4 bytes short. | Not retained. |

The earlier601 branch-call probe, before the independent float/zero/effect/
facing recoveries and without this explicit float argument expression, lost
twelve owners. That negative is phase-scoped and is superseded for the
retained current combination. This does not justify exhaustive source/type/
flag permutations or predict a positive710 result.

Fresh explicit-object stack/definition packets resolve all49 physical spawn
inputs without unknown payload definitions or conflicting modeled ESP merges.
Normalized payload-address leads decrease **6 -> 2**, closing500/505/601/604;
605/710 remain. In particular500's two sources are normalized`+136/+140`,
505's are`+144/+156`, and601's loop payload is`+100` in both target/candidate.
These are source-address/owner diagnostics, not proof of every value lifetime.

All138 masked floating guards have equal per-owner counts and zero unordered-
only leads under ordinal hypotheses. Arithmetic counts become349/349 with two
remaining multiset leads696/710. Load/store leads remain12. Physical virtual
counts at slots8/C/14/1C remain target107/31/12/2 versus candidate106/33/13/2.
The frame remains`230`; raw target traversal still reaches9,912 instructions/
all37,692 bytes without unresolved indirect jumps. None of these limited scans
establishes complete numerical/exception closure or exact bytes.

## Reproduction and remaining unknowns

```bash
python3 scripts/build.py --unit gpt-web-youmu-vslot28-full-root --compare --json
python3 scripts/audit-giant-action-owners.py youmu-vslot28 \
  build/match-units/GptWeb_YoumuActionState.obj \
  --unit gpt-web-youmu-vslot28-full-root --json
python3 scripts/ci.py
git diff --check
```

Fresh reports are `build/youmu-copied-input-601-final-20261002.json` and
`build/youmu-copied-input-601-final-owners-20261002.json`. Explicit-object call,
guard, stack, arithmetic and load/store packets use that prefix/date. Private
controls and raw helper/manager packets are below
`.analysis/youmu-pointer-contract-20261002/` and
`build/youmu-pointer-contract-20261002/`; existing-object control comparisons
have diagnostic provenance, not configured build attestation.

Original source types, remaining register/temporary homes,710 argument
schedule, shared physical tails, compiler/TU context and numerical/exception
closure remain unknown. No accepted helper/shared-header/compiler/global-
relocation/partition change or aggregate cold-replay claim is made. Whole-root
zero-difference canonical replay remains required for exact acceptance.
