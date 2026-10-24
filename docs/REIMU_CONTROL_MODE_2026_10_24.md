# Reimu control mode: complete exact family peer

## Accepted result and reproduction

Reimu Fighter primary slot `+0x5C @0x00491450` accepts **1566 callable bytes**
and the entire **1844-byte emitted payload**, including alignment, both
destination and both byte-index tables. Formal and independent cold builds
replay all **48 relocations** (15 REL32 /33 DIR32) with zero differences.
Only callable bytes earn authored credit.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-reimu-control-mode --compare --json
python3 scripts/audit-reimu-control-mode.py
```

Run both commands. Full audit requires exact section-tail length and every
byte, replaying relocations beyond the callable boundary into both tables.
The existing probe unit is updated rather than duplicated. Formal object/
provenance is retained privately. Only this unit's active object and sidecar
were removed before an independent cold compile and both checks. The pinned
VC8 SP1 `/O2` profile remains unchanged.

Callable SHA256:
`d554495375968062b97cdec0cdcfd9968b4ee7494fa695ea145820aded2f5559`.
Full canonical SHA256:
`26d73763276489c86f7e0ce6498702d7edb940224a09217c0d1074cc3db419e5`.

Source/header are `src/characters/ReimuControlMode.cpp/.hpp`. These are
pointer-only call views; never construct or embed them. Existing slot08/0C
callees45BFE0/45C390 support int returns and short/int arguments. Declaration-
only callees gain no implementation/exact credit. Original complete layout,
unused virtual signatures and source/TU identity remain unknown. No assembly,
copied byte array, inert local, artificial padding, fake return, ABI/register
forcing, compiler-profile search or broad runtime matrix is used. Existing
accepted headers/sources and relocation bindings remain unchanged.

## Observed target facts

Only original Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is inspected. Existing RTTI evidence classifies the root as authored. Raw
primary vtable base6C412C has slot08=45BFE0, slot0C=45C390, slot58=48D390 and
slot5C cell6C4188=491450. These pointers do not prove original source names.

Complete raw traversal closes **390 instructions**, **8 RET0s**, **24 CALLs**,
all internal direct edges and six switch destination entries. Direct calls
are4399C0 once,478E60 six times and4067D0 eight times. Nine other CALLs use
virtual action slot08. The vptr/slot58 load at491A0E and restored receiver/
epilogue prove the one virtual CPU tail491A19. There is no unresolved external
direct tail, remote chunk or EH path in this bounded body.

Prologue reserves four bytes and saves EBX/ESI/EDI. EBX starts at-1, supplying
the timer decrement and the FF-facing write in records8; disjoint records0
later repurpose it to1. EDI has a zero lifetime. Last RET491A6D ends exclusively
491A6E. Two-byte MOV EDI,EDI alignment precedes the three-entry table491A70;
its12-byte index map starts491A7C. The other three-entry table starts491A88
and its240-byte index map491A94. Full payload ends exclusively491B84, followed
by twelve INT3 bytes. No neighboring code is included; alignment and276 table
bytes earn no authored credit.

All literal widths/bits are independently pinned. Native motion reads double
3/10/5/13/2/22 from6C3B78/6D6EC0/6C0648/6C3F38/6C21C0/6C3F30 and divides
by double56 at6C21B0. Scale.2 is float6C3CC0, scale.5 float6CD140 and vertical14
float6C3C64. Unsigned RNG correction uses float2^32 at6D6EF8. Existing
constant bindings suffice; no relocation-ledger or literal override is added.

## Independently reviewed behavior

| Surface | Native behavior retained |
| --- | --- |
| Prefix |Decrement WORD768; clear DWORD724/728 and6B4..6D0. Signed action50..149 clears WORD76C/76A/766/768/764. Action<=199 separately clears76C/764. Signed55A<1 returns before checked deque selection. |
| Records0..3 state0/1 |Ready state0 selects770 then1 and returns. Positive signed peer170/174 and ready state1 face, store unsigned RNG6+double3 and RNG3+double10, scale.2, select701, publish2 and return. State1 has no nonpositive-peer fallback. |
| State2 |Positive-peer ready path faces, stores double5-RNG10 and RNG4+double13 with scale.5, selects710, publishes3 and returns. Nonpositive peer publishes1. The later state3/4 checks remain separate reads. |
| State3 |Positive-peer ready path faces, stores double10-RNG20 and RNG4+double13 with scale.5, selects710, publishes4 and returns. Nonpositive peer publishes1. |
| State4 |Positive-peer ready path faces, stores double2-RNG4 and RNG4+double22 with scale.5, selects711, then publishes1. Nonpositive peer also publishes1; positive peer with nonready action leaves4 unchanged. The successful path does not remain in4. |
| Records4..7 |Initial770/1. Ready state1 faces/selects720 then1; no peer guard exists. Its callback/store tail shares the initial action tail. |
| Records8..11 |Initial770/1. Otherwise state1 writes facingFF **before** readiness. Ready action then publishes1 **before**730. Nonready action still receives the FF-facing store; there is no facing helper call here. |
| Records12..15 |Initial770/1. Ready state1 publishes2 **before**740 and returns. Positive-peer ready state2 faces; horizontal is `(peer170.x-self.x)/double56` times signed facing. Store vertical14f/scale.5, select701 then1. |
| Records248..255 |Conditional action0, then the actual slot58 virtual tail. |
| Records16..19 |Ready state0 selects760 then1 and returns. Ready state1 selects760 without a following state store. The initial callback's shared return is explicit; no callback-side mutation is assumed absent. |

Readiness means action700 or0. Signed narrow gates, independent peer/state
reads, unsigned32 RNG conversion, actual double arithmetic and callback-side
store ordering follow the target. No complete gameplay/class naming is needed
before canonical comparison.

## Fresh whole comparison and one focused correction

The retained source was an unselected probe. A fresh baseline emits1872
complete bytes and first differs+0x0C: the EBX-1 lifetime is absent. Independent
raw review identifies two semantic errors in that draft: records8 writes+1
instead of nativeFF, and the successful state4 path omits the native reset to1.
It also establishes actual double motion/divisor widths and pointer-only ABI
views. These target facts are corrected before source-present selection.

| Probe | Evidence-backed change / complete result |
| --- | --- |
|00|First newly reviewed complete source emits1840 versus1844. The real FF-facing use recovers the native EBX-1/decrement lifetime without register shaping. All24 physical CALLs and every motion/state operation agree. Only the initial callback/store shared tail moves from491550 to the final case, altering return displacements and table addresses; first+0xA1. |
|01 selected|Express the actual records16 state0/ready return immediately after760/state1, followed by the independent state1/ready check. This preserves the native exit while replacing the nested else shape; VC8 now chooses the native shared-return owner. Complete1844 becomes exact, including alignment and both destination/index tables. |

The early-return rewrite does not add behavior or a fake branch; it expresses
the reviewed ordinary exit. Exactness supports this bounded source/ABI/control
structure, not original source spelling or a general register-allocation rule.
No further spelling trials, compiler controls or large runtime matrix are needed.

A generated-object negative increments the first destination's addend in a
separate COFF file. Full audit rejects it at `+0x620 /0x00491A70`, target2D/
source2E, while the callable prefix still agrees. The original PE is untouched.
This verifies that metadata is actively compared.

## Validation, cohort state and retained evidence

IDA preflight rejects the different executable open in the GUI; no semantics
or writes from that session are used. One read-only Ghidra run independently
attests executable SHA/base/entry68B9D2, Windows x86 language/compiler and every
raw-backed section. Its temporary raw-bounded1566-byte entry closes390
instructions. Callee views/metadata are read back and rolled back; all nine
primary DB pins remain unchanged. Decompiled output corroborates raw facts
and is not pasted into source. Own process uses384MiB/one CPU. Compiles remain
serial CPU0/nice10, with available memory/swap monitored.

Private recipes, retained draft and both complete probes remain under
`.analysis/exact-first-reimu-slot5c-20261024/`; the matching `build/` scope
retains CFG/tables/literals, attestation/DB pins, baseline/formal/cold comparisons,
formal object/provenance and generated negative. Private reports/binaries/
databases are not committed.

Only Reimu's origin evidence label becomes canonical-exact-authored. The
nonmatching Fighter-vtable selector becomes45 roots/1027032 provisional bytes;
its immutable73-root witness and all dispositions/denominator stay unchanged.
Ledger totals become1400 exact functions/332073 callable bytes; source-present
becomes1529. Configured units/functions stay567/1535. No new aggregate cold
replay claim is made.

A raw primary-vtable lookup against the current source/match ledgers confirms
all15 slot5C owners now have complete selected source. Nine have exact ledger
records: Reimu/Sakuya/Alice/Youmu/Remilia/Yuyuko/Udonge/Komachi/Iku. Six retain
recorded nonexact residuals: Marisa/Patchouli/Yukari/Suika/Aya/Tenshi. This is
a coverage/status audit, not a cold replay of all15. Only Reimu receives a new
cold acceptance in this scope. The private cohort receipt records every target
pointer, candidate size, selected name/source and status.

This closes source selection across the slot5C cohort. Next select a new
complete medium/large authored representative using the target inventory;
keep the six parked residuals until new independent evidence changes their
questions. Do not repeat their neutral controls merely to finish the cohort's
exact column.
