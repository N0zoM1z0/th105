# Sakuya control mode: complete exact family peer

## Accepted result and reproduction

Sakuya Fighter primary slot `+0x5C @0x004DD7E0` accepts **1796 callable bytes**
and the entire **2116-byte emitted payload**, including all five destination
and both index tables. Formal and independent cold builds replay all **61
relocations** (17 REL32 /44 DIR32) with zero differences. Only callable bytes
earn authored credit.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-sakuya-control-mode --compare --json
python3 scripts/audit-sakuya-control-mode.py
```

Run both commands. Full audit requires the exact section-tail length and every
byte, replaying relocations beyond the callable boundary into all tables.
The formal object/provenance is retained. Only this unit's active object and
provenance sidecar were removed before an independent cold compile; both
checks pass again. The pinned VC8 SP1 `/O2` profile remains unchanged.

Callable SHA256:
`c6d8ac88a2c26b348e846b5bfa75b66096b28fac296eb6ba26061cc5c025eaa4`.
Full canonical SHA256:
`7e064ea6ed9ee825d5e4bd7f2ae47810e9acf3446d8f44d12f43fa0ce865ce9f`.

Source/header are `src/characters/SakuyaControlMode.cpp/.hpp`; the existing
probe unit is updated rather than duplicated. The declarations are pointer-only
call views: never construct or embed them. Slot08/0C bind existing45BFE0/
45C390, with actual int returns and short/int parameters. Original complete
layout, nominal field types, unused virtual signatures and source/TU identity
remain unknown. Declaration-only callees gain no implementation/exact credit.
No assembly, copied byte array, inert local, artificial padding, fake return,
ABI/register forcing, compiler-profile search or broad runtime matrix is used.

## Observed target facts

Only original Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is inspected. Existing RTTI evidence classifies this root as authored. The raw
primary vtable base6C4914 has slot08=45BFE0, slot0C=45C390, slot58=5F1F80 and
slot5C cell6C4970=4DD7E0. These observations do not prove original source names.

Complete traversal closes **451 instructions**, **8 RET0s**, **26 CALLs**,
all internal direct edges and17 switch destination entries. Direct CALLs
are checked deque4399C0 once, facing478E60 three times and selector4067D0 nine
times; thirteen further CALLs use virtual action slot08. Four other facing
operations are real external tails at4DDBD9/4DDC71/4DDD64/4DDE47, with restored
ECX receiver and no arguments. A separate vptr/slot58 load at4DDDDF proves
the virtual CPU tail4DDDE9. There is no other unresolved exit or remote chunk.

Prologue reserves four bytes and saves EBP/ESI; EBP has a real zero lifetime.
Last RET4DDEE3 ends the callable exclusively4DDEE4. There is no alignment gap
before the two-entry destination table at4DDEE4. Its8-byte index map starts
4DDEEC. Four-entry timer tables start4DDEF4 and4DDF04. The three-entry record
table starts4DDF14 and its244-byte index map starts4DDF20. Another four-entry
timer table starts4DE014. All320 metadata bytes end exclusively4DE024, followed
by twelve INT3 bytes. The next function and prior function metadata are excluded.

Literal access widths are independently pinned: double3.0 at6C3B78, double12.0
at6C35D0, double60.0 at6C1888, float.5 at6CD140, float180.0 at6D6EDC,
float6.0 at6CD1D8, float-6.0 at6C3C60, float1100.0 at6C41F0 and float1220.0
at6C4800. Unsigned RNG conversion uses float2^32 at6D6EF8. The identifier
DWORD is6FA894. Existing constant/global bindings suffice; no relocation-ledger
entry or compiler setting is changed.

## Independently reviewed behavior

| Surface | Native behavior retained |
| --- | --- |
| Prefix |Decrement WORD768; clear DWORD724/728 and6B4..6D0. Signed action50..149 clears WORD76C/76A/766/768/764; action<=199 separately clears76C/764. Signed55A<1 returns before checked deque selection. |
| Records0..3 entry |Ready state0 selects770 then1. State1 with signed positive peer170/174 faces; unsigned RNG100<=50 selects710 then2. Otherwise select711, store unsigned RNG6-double3 as horizontal and RNG3+double12 as vertical, state2 and scale.5. Both outcomes return. |
| State2 mobility |Positive peer/ready faces first. Facing+1 with ordered x<180, or other facing with ordered x>1100, selects705, horizontal motion6 and timer=RNG60+60. Otherwise unsigned RNG100>50 selects705/horizontal6; remaining values select706/vertical-6. These random routes use RNG60+90. Original two facing branches are retained independently. |
| Active mobility |Action705/706 separately checks facing+1, ordered x>1220 and velocityX>0 before writingFF; then independently checks facingFF, ordered x<double60 and velocityX>0 before writing+1. Expired timer publishes state1 **before** action700. NaN does not satisfy an ordered comparison. |
| Records4..7 action |Initial770/1. Ready state1 selects720, writes2 and really tail-calls facing. Ready state2 selects721, generates the RNG6-3/RNG3+12 packet, scale.5/state3, then really tail-calls facing. There is no peer gate. |
| Records4..7 delay |Ready state3 uses identifier3/2/1/0 to store timer10/15/20/30 and publishes4. Invalid identifier leaves the old timer but still publishes4. Then state4/expired/ready selects722, calls facing and writes1. The state4 continuation uses the shared terminal condition with records8/12. |
| Records8..11 |Initial770/1. Ready state1 selects730, writes2 and tail-calls facing, returning without another state check. Ready state2 selects the same identifier delay and publishes3, including for invalid identifiers. State3/expired/ready selects722, calls facing and writes1. |
| Records248..255 |Conditional action0, followed by the actual virtual CPU tail. |
| Records12..15 |Initial770/1. Ready state1 selects740, writes2 and tail-calls facing. Ready state2 selects identifier delay then3. State3/expired/ready selects722, calls facing and writes1. **No4A8/4AC store exists in this target body.** |

Readiness is the native action700-or0 test. State/peer reads remain at their
actual post-callback points. Motion RNG consumes unsigned32 before float
conversion and the observed double arithmetic. WORD state/timer gates and
signed peer174/sequence55A checks follow their instructions. Gameplay naming
is deferred; no assumption about callback immutability is introduced.

## Early whole comparison and focused corrections

The retained source was not selected in implemented.csv and remained an
unverified hypothesis. A fresh baseline compile emits2192 complete bytes and
first differs at+1: EBP's zero lifetime is absent. Independent raw review finds
unobserved4A8/4AC writes, float3/12/60 where the target reads doubles, and
unnecessary complete-owner storage/ABI hypotheses. These are corrected before
source-present selection. Read-only decompilation corroborates the complete
edge/operand review; it is not pasted as source.

| Probe | Complete result and target-backed change |
| --- | --- |
|00|First newly reviewed complete pointer-only body emits2104 bytes versus2116, retaining all26 CALLs/five tails. Zero-register/prologue, RNG correction widths, callback scheduling and packet arithmetic now agree. First+0x9E is a downstream return displacement; remaining differences are facing-arm placement, timer-case order and final alignment. |
|01|Reverse the three timer switches to physical order3/2/1/0, following the target's10/15/20/30 blocks and shared exits. Complete2104 remains nonexact; all timer block instruction sequences now agree. |
|02 selected|Retain each actual facing arm's edge check and random fallback independently, rather than source00's single combined fallback after the facing gate. VC8 shares the real callbacks/RNG bodies itself and places the other-facing check after the random returns. Complete2116 becomes exact, including the final alignment and every metadata byte. |

The redundant `CMP DX,DX` in the delay family is emitted naturally by the
ordinary state stores/continuation; it is not manually represented or forced.
The exact result supports this bounded source/ABI/expression structure, not
original source spelling, complete class recovery or a general compiler recipe.
No separate spelling controls or large behavior matrix are necessary.

A generated-object negative increments the first switch destination's addend
in a separate COFF file. Full audit rejects it at `+0x704 /0x004DDEE4`,
targetBA/sourceBB, while the callable prefix still agrees. This verifies that
comparison includes metadata. The executable remains untouched.

## Validation and retained evidence

IDA preflight rejects the different executable open in the GUI; no semantics
or writes from that session are used. One read-only Ghidra run independently
attests executable SHA/base/entry68B9D2, Windows x86 language/compiler and every
raw-backed section against the PE. The temporary raw-bounded1796-byte entry
closes451 instructions; callee views/metadata are read back and rolled back.
All nine primary DB pins remain unchanged. Ghidra's presentation may inline a
tail callee; acceptance uses the independently reviewed raw root boundary.
Own process uses384MiB/one CPU. Compiles are serial CPU0/nice10, with memory/
swap monitored. Formal/cold full audits and the generated negative behave as
expected before ledger promotion.

Private recipes, retained draft and all three complete probes remain under
`.analysis/exact-first-sakuya-slot5c-20261024/`; its matching `build/` scope
retains raw CFG/tables/literals, attestation/DB pins, baseline/formal/cold
comparisons, formal object/provenance and generated table negative. No private
binary/report/database is committed.

Only Sakuya's origin evidence label becomes canonical-exact-authored. The
nonmatching Fighter-vtable selector becomes47 roots/1030251 provisional bytes;
its immutable73-root witness and all authored/excluded/review dispositions
remain unchanged. Ledger totals become1398 exact functions/328854 callable
bytes, without a new aggregate cold replay claim. Configured units/functions
stay566/1534; source-present becomes1526. Continue independently reviewed
same-slot peers while keeping Suika/Yukari/Patchouli/Tenshi/Marisa residuals
parked.
