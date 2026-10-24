# Aya control mode: complete source and parked shared-tail residual

## Result and reproduction

Aya Fighter primary slot `+0x5C @0x00616800` has complete reviewed source in
`src/characters/AyaControlMode.cpp/.hpp`. The target owns **1726 callable
bytes /2004 complete emitted bytes**. Selected source emits2020 complete bytes
and remains **nonexact** at `+0xA1 /0x006168A1`, an early return displacement
caused by downstream layout. Source-present credit is added; no exact/match
credit is added.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-aya-control-mode --compare --json
python3 scripts/audit-aya-control-mode.py
```

Both commands correctly return1. The existing probe unit is updated rather
than duplicated. Full audit checks section-tail length and every byte while
replaying all60 relocations (19 REL32 /41 DIR32), including both destination
tables beyond the callable body. Formal build/audit reproduce selected private
probe00. The formal object/provenance is retained privately. The pinned VC8
SP1 `/O2` profile remains unchanged.

Target callable SHA256:
`4057e185934195fa9ad11e7b4f28c71211539e099100c581f60c8f445bbc2be4`.
Target full SHA256:
`4c4dae9b6da375119d179c6b8a6525e569e5e8cf5787bee74cc1eb2efd2a86cd`.
Selected full canonical SHA256:
`81bede8d9b0e07a86bcc97ed981e8b5248f60aeaa0bf9ca15c943bdb7f380839`.

Declarations are pointer-only call views: never construct or embed them.
Existing slot08/0C callees45BFE0/45C390 support int returns and short/int
parameters. Declaration-only callees gain no implementation/exact credit.
Original complete owner layout, unused virtual signatures, source/TU identity
and the remaining local lifetime/partition context are unknown. No assembly,
copied byte arrays, inert locals, artificial padding, fake returns, ABI/register
forcing or compiler-profile search is used. Existing accepted sources/headers
and relocation bindings remain unchanged.

## Observed target boundary and ABI

Only original Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is inspected. Existing RTTI evidence classifies this root as authored. Raw
primary vtable base6C62D4 has slot08=45BFE0, slot0C=45C390, slot58=6126E0 and
slot5C cell6C6330=616800. No new callee credit follows from these pointers.

Complete raw traversal closes **457 instructions**, **11 RET0s**, **30 CALLs**,
all internal direct edges and all six table destinations. Direct calls are
4399C0 once,478E60 four times and4067D0 fourteen times. Eleven more CALLs use
virtual action slot08. The slot58 load at616E94 and restored receiver/epilogue
prove the one virtual CPU tail at616E9F. No other unresolved external tail,
remote chunk or EH path remains in this bounded body.

Prologue reserves four bytes and saves EBX/ESI/EDI. EBX starts at-1 and is
repurposed to1 in records0/4; EDI holds0. EBP is saved conditionally at616B67,
after the records8 initial-ready return, and holds1 through that movement
family. The common return is physically inside the mode0 region at616C8C/
616C8D. Last RET616EBD ends exclusively616EBE; two-byte MOV EDI,EDI alignment
occupies616EBE..616EBF. The three-entry table starts616EC0, its12-byte index
map616ECC; the other three-entry table starts616ED8 and its240-byte map616EE4.
Full payload ends exclusively616FD4, followed by twelve INT3 bytes. No neighbor
bytes are included. Alignment and276 metadata bytes earn no authored credit.

All constant widths/bits are independently pinned. Motion uses double10 at
6D6EC0 and double8 at6C09A8, division by double80 at6C0850, float16 at6C3CE8,
float.4 at6C4480, float.5 at6CD140 and float640 at6C0574. Unsigned RNG
conversion uses float2^32 at6D6EF8. Existing literal bindings suffice;
no relocation-ledger change or new literal override is necessary.

## Independently reviewed behavior

| Surface | Native behavior retained |
| --- | --- |
| Prefix |Decrement WORD768; clear DWORD724/728 and6B4..6D0. Signed action50..149 clears WORD76C/76A/766/768/764; action<=199 separately clears76C/764. Signed55A<1 returns before checked deque selection. |
| Records0..3 |Ready state0 selects770 then1. Positive-peer ready state1 faces, stores negative unsigned RNG20 horizontally and RNG4+double10 vertically, scale.5, selects701 then2 and returns. State2 with nonpositive signed peer170/174 writes1; positive peer/ready selects710 then1 **without** a facing call. |
| Records4..7 gate |Initial770/1. Ready state1 or3 faces, consumes unsigned RNG100, then re-reads state1. RNG<=50 with state1 selects721 then3. Other outcomes publish motion701 then2. Ready state2 independently selects720 then1. |
| Records4..7 motion |Horizontal is `(peer170.x-self.x)/double80` multiplied by signed facing. Vertical16f and scale.4f precede701. No positive-peer gate or random motion magnitude is invented for this family. |
| Records8..11 entry |Initial770/1 returns. Ready state1 faces, publishes2 **before**730 and returns. Ready state2 faces and stores only the low word of RNG3 at76C, then tests modes0/1/2. |
| Mode0 backward |Ordered self x>=640/facing+1 or ordered x<=640/facingFF selects backward motion: negative unsigned RNG8 minus double10; vertical RNG4+double8; scale.5/action703 then1. Unordered position falls through to the forward path. |
| Mode0 forward /mode1 |Store vertical RNG4+double8 and scale.5 **before** calling RNG8. Horizontal uses RNG8+double10, action702 then1. Both physical selector pairs are retained. |
| Mode2 |Ordered x<=640 writes facing+1, elseFF. Each branch independently executes RNG12+double8 horizontally and RNG4+double8 vertically. Both vertical selector sites exist in the target. Scale.5/action702 then1 follows; horizontal is not multiplied by facing. |
| Records12..15 |Initial770/1. Ready state1 publishes2 **before**740. There is no peer guard. |
| Records248..255 |Conditional action0, then the actual slot58 virtual tail. |
| Records16..19 |Action750 suppresses the store; otherwise DWORD728=750. This path does not call set_action. |

Readiness is action700-or0. Target-observed signed gates, unsigned32 motion
conversion, signed facing, actual post-callback reads and double arithmetic
are retained. Physical code differences remain subject to complete canonical
comparison. There is no gameplay naming prerequisite or broad runtime matrix.

## Fresh full comparison and finite experiments

The retained source was an unselected probe. A fresh baseline emits1988 bytes
and reproduces first+0xA1. Its source combines the mode2 vertical random
expression after both facing branches, while raw target has two physical sites.
Full target review also establishes the actual double literal widths and
pointer-only call surfaces. That new evidence justifies a fresh complete body;
it does not justify repeating old guard/case-order controls unchanged.

| Probe | Evidence-backed question / complete result |
| --- | --- |
|00 selected|First newly reviewed complete source emits2020 versus2004. All30 physical CALLs now agree:14 selectors/4 facing/1 deque/11 virtual. Frame/register saves, earlier motion and mode2 operations agree; remaining differences are forward RNG conversion scheduling/sharing and the common callback/return's physical placement. |
|01 neutral|Capture each forward horizontal RNG as a consumed unsigned scalar before float conversion, reflecting native integer-result ownership. The full payload is byte-for-byte identical to00. This does not establish an original scalar declaration. |
|02 rejected|Make both native forward-conversion and action702 endpoints explicit, sharing a real unsigned result. VC8 merges a target-retained RNG4/callback copy:13 selectors/10 virtual sites, full1916. Fewer bytes do not mean improved matching. |
|03 rejected|Isolate just the action702 shared endpoint, preserving14 selector sites. It still merges that callback with the initial action tail, loses the conditional EBP lifetime and emits10 virtual sites/full1996. The actual call topology is worse; the nearer size is not acceptance. |
|04 neutral|Split the state2 gate into an early state return followed by the readiness branch, following the native guarded-region exit. It reproduces00's entire2020-byte payload. |

Keep source00's ordinary structured body. The two neutral controls and rejected
shared-exit witnesses are retained; stop the bounded investigation and select
another complete family peer. Reopen only with new independent lifetime/TU/
partition evidence. There is no conclusion that LTCG is required, and no
partial-window match score or exact credit is assigned.

The target converts each forward RNG8 result with FILD before the shared
stack cleanup/test at616C61, then reaches action702/common epilogue at616C77/
616C7C. Selected source places that common callback after mode2 and duplicates
part of mode1's unsigned conversion. This explains the changed early return
displacement; it does not prove how to force original source ownership.

## Validation and retained evidence

IDA preflight rejects the different executable open in its GUI; no semantics
or writes from that session are used. One read-only Ghidra run independently
attests executable SHA/base/entry68B9D2, Windows x86 language/compiler and every
raw-backed section. A temporary raw-bounded1726-byte entry closes457
instructions. Callee views/metadata are read back and rolled back; all nine
primary DB pins remain unchanged. Decompiled output corroborates raw facts
and is not pasted into source. Own Ghidra uses384MiB/one CPU; compiles remain
serial CPU0/nice10 with available memory/swap monitored.

Private recipes, retained draft and all five complete probes remain under
`.analysis/exact-first-aya-slot5c-20261024/`; the matching `build/` scope retains
raw CFG/tables/literals, attestation/DB pins, baseline/probe/formal comparisons,
full audit and formal object/provenance. Private reports/binaries/databases are
not committed. Existing accepted headers/sources/flags/bindings stay unchanged.
Source-present total becomes1528; configured graph remains567 units/1535
functions. Exact ledger totals stay1399 functions/330507 callable bytes, with
no aggregate cold replay claim. Origin dispositions/denominator and selector
46/1028598 remain unchanged. Continue remaining independently reviewed peers;
previous parked controls stay parked.
