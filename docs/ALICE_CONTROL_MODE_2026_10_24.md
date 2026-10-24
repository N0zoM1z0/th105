# Alice control mode: complete exact family peer

## Accepted result

Alice Fighter primary slot `+0x5C @0x004F8E00` accepts **2284 callable bytes**
and the complete **2560-byte emitted payload**, including both destination
and both index tables. Formal and independent cold builds replay all **87
relocations** (34 REL32 /53 DIR32) with zero differences. Only callable bytes
earn authored credit.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-alice-control-mode --compare --json
python3 scripts/audit-alice-control-mode.py
```

Run both commands. The full audit requires every byte and the exact section-tail
length; relocation replay extends beyond the callable body into both tables.
The first formal object/provenance is retained. Only this new unit's active
object/sidecar were removed before an independent cold compile and both checks.
The pinned VC8 SP1 `/O2` profile remains unchanged.

Callable SHA256:
`5edce827e0e781ef5e5d80de2dbcb5d1dd4c54311f2eeace907c5da3bed6e656`.
Complete canonical SHA256:
`717b6ef1923f65dfa21adeac6764c10c9d511c5dce656c4f47f19e97a5678625`.

Source/header are `src/characters/AliceControlMode.cpp/.hpp`. The declarations
are pointer-only views: never instantiate or embed them. Original full layout,
nominal type names, unused virtual signatures and source/TU identity remain
unknown. Declaration-only callees gain no new implementation/exact credit.
No assembly, copied byte array, artificial padding, inert local, fake return,
ABI/register forcing, compiler-profile search or broad runtime matrix is used.
Existing accepted source/header pairs and relocation bindings remain unchanged.

## Observed target facts

Only original Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is inspected. Existing RTTI evidence classifies this root as authored. The raw
primary slot5C cell6C4C38 points to4F8E00; slot08/0C bind45BFE0/45C390, while
slot58 binds Alice's4F4B80 CPU root. That callee remains at its previous state.

Complete raw traversal closes **581 instructions**, **10 RET0s**, **44 calls**,
all internal direct edges and all six destination entries. Direct calls are
checked deque4399C0 once, facing478E60 nine times and selector4067D0 twenty-four
times. Ten further calls use virtual action slot08. An independent receiver /
vptr /slot58 load chain at4F96C4..4F96D1 proves the one virtual CPU tail.
There is no unresolved register jump, external direct tail or remote chunk.

The prologue reserves four bytes and saves EBP/ESI/EDI. EBP holds a real zero
lifetime; EDI starts at1 and becomes3 while processing the first motion cycle.
The callable ends exclusively4F96EC. There is **no alignment gap** before the
first destination table at4F96EC..4F96F7. Its12-byte index table occupies
4F96F8..4F9703. The second three-entry destination table occupies4F9704..4F970F,
followed by240 index bytes at4F9710..4F97FF. Full payload ends exclusively
4F9800, exactly where the separately accepted71-byte round-reset function
begins. No byte of that neighbor is included or changed.

The float constants are independently pinned: double10.0 at6D6EC0,
double8.0 at6C09A8, float.5 at6CD140, float640.0 at6C0574 and the float2^32
unsigned-conversion correction at6D6EF8. Unsigned selector consumption, narrow
state comparisons, signed peer174 and signed55A gates follow their actual
instructions. No new constant/global mapping is needed.

## Independently reviewed family behavior

The complete source uses proven pointer-call surfaces from the family, but
Alice's actual branches and store timing are checked independently.

| Surface | Native behavior retained |
| --- | --- |
| Prefix |Decrement WORD768, clear DWORD724/728 and6B4..6D0; signed action50..149 clears five word lanes; action<=199 separately clears76C/764. Signed55A<1 returns. |
| Records0..3 |State0/ready selects770 then1. State1 uses a signed positive peer gate; success faces, selects710 then2; nonpositive peer writes2. State2/positive peer/ready faces, uses10.0-RNG20 and RNG4+10.0 with scale.5, selects701 then3. State3 similarly selects711 then4, with a nonpositive-peer fallback to2. State4 repeats motion701 then1. |
| Records4..7 |State0/ready selects770 then1. Positive-peer state1/2 faces and selects720/721 then2/3; nonpositive peer writes1. Positive-peer state3/ready faces, executes the10.0 motion and701 then1. Repeated peer reads remain separate. |
| Records8..11 |State0 selects770 then1. State1 faces and publishes2 **before**730. State2/ready stores the low-word RNG3 result at76C; each valid mode selects its actual movement action and then **state3**. State3 faces and publishes4 **before**730. State4 repeats mode selection and returns to1. |
| Motion mode0 |Unsigned RNG8 is converted, negated, then subtracts double10.0; RNG4+double8.0 supplies vertical motion. Scale.5 and action703 follow. |
| Motion mode1 |Vertical RNG4+8.0 and scale.5 are stored **before** the RNG8 horizontal call; horizontal uses+10.0 and action702. RNG order is not normalized. |
| Motion mode2 |Ordered x<=640 sets facing byte+1, otherwiseFF, including unordered inputs. Both branches independently call RNG12 for horizontal+8.0 and RNG4 for vertical+8.0. Scale.5/action702 follow. Neither branch multiplies horizontal motion by facing. |
| Records12..15 |Initial770 then1; state1/ready publishes2 **before**740. There is no peer guard. |
| Records248..255 |Conditional action0 followed by the real slot58 virtual tail. |
| Records16..19 |Action750 suppresses the command store; otherwise publish DWORD728=750. This path does not call set_action. |

Readiness is the native action700-or0 test. State fields are read at their
actual post-call points; numeric state/motion meanings are not elevated to
unverified gameplay names. Mode selection comparisons consume only the returned
low word; motion RNG conversion consumes unsigned32. Signed facing storage is
a local view of byteFF, not proof of the original declaration.

## Early whole comparison and correction

Private probe00 is the first complete source. All44 call sites and the virtual
CPU tail are present, but the full payload is2652 bytes versus2560 native and
first differs at+1. Its instruction/register/shared-return differences are
not treated as an acceptance score.

Native4F92A3 sets EDI=3 before the state2 motion modes; the shared callback tail
at4F9115 stores DI. The first source mistakenly writes1 after all three mode
branches. Probe01 changes **only those three state2 continuation stores to3**.
This single target-backed semantic correction recovers the actual second
cycle, constant lifetimes, return sharing, register allocation and every table
byte. The complete2560-byte payload becomes exact immediately. No standalone
register-shaping or source-spelling trials are necessary.

A generated-object negative increments the first table destination addend in
a separate file. Full audit rejects it at`+0x8EC /0x004F96EC`, targetE0/sourceE1;
the target stays untouched. This verifies that metadata comparison is active.
Full equality proves this bounded emitted unit, not original source spelling
or a recovered complete class. No LTCG requirement is inferred.

## Validation and retained evidence

IDA preflight rejects the different executable currently open there; no
semantics or writes from that session are used. One read-only Ghidra process
independently attests file SHA, image base, entry68B9D2, Windows x86 language/
compiler and every raw-backed section against the PE. A temporary raw-bounded
2284-byte entry and callee call views are read back and rolled back. All nine
pinned primary DB hashes remain unchanged. Decompiled output only corroborates
raw branches/operands and is not pasted into source. Heap384MiB/one CPU;
builds run serially at CPU0/nice10, with memory/swap monitored.

Private recipes/frozen first source and corrected probe remain under
`.analysis/exact-first-alice-slot5c-20261024/`; the corresponding `build/` scope
retains raw CFG/tables/literals, attested views/DB pins, formal/cold comparisons,
formal object/provenance and generated table negative. Source/exact ledgers and
the nonmatching Fighter-vtable subset are synchronized:48 roots/1032047 bytes
remain in that selector; its immutable73-root pointer witness is unchanged.
Only Alice's origin evidence label becomes canonical-exact-authored; authored,
excluded and review dispositions and the denominator stay unchanged. Ledger
exact totals become1397 functions/327058 callable bytes, without a new aggregate
cold replay claim. Continue independently reviewed same-slot peers; keep the
recorded Tenshi and Marisa neutral controls parked.
