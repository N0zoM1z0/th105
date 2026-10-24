# Yuyuko control mode: complete exact family peer

## Accepted result and reproduction

Yuyuko Fighter primary slot `+0x5C @0x0056C170` accepts **1653 callable bytes**
and the entire **1688-byte emitted payload**, including alignment, both
destination tables and the byte-index map. Formal and independent cold builds
replay all **62 relocations** (20 REL32 /42 DIR32) with zero differences.
Only callable bytes earn authored credit.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-yuyuko-control-mode --compare --json
python3 scripts/audit-yuyuko-control-mode.py
```

Run both commands. Full audit requires exact section-tail length and every
byte; it replays all relocations beyond the callable body into the tables.
Formal object/provenance is retained privately. Only this new unit's active
object and sidecar were removed before an independent cold compile and both
checks. The pinned VC8 SP1 `/O2` profile remains unchanged.

Callable SHA256:
`48340b269075e79540b836047aee0a9e87f1304f0a91c3d631db3654328e3c2b`.
Full canonical SHA256:
`16a2e95625b1ac1f978f9615242d9e67472885c5e631a7254d0a4046a8f886bf`.

Source/header are `src/characters/YuyukoControlMode.cpp/.hpp`. They use
pointer-only call views; never construct or embed them. Original complete
layout, nominal field types, unused virtual signatures and source/TU identity
remain unknown. Declaration-only callees gain no implementation/exact credit.
No assembly, copied bytes, inert local, artificial padding, fake return,
ABI/register forcing, compiler-profile search or broad runtime matrix is used.
Existing accepted source/header pairs and relocation bindings remain unchanged.

## Observed target facts

Only original Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is inspected. Existing RTTI evidence classifies the root as authored. Raw
primary vtable base6C564C has slot08=45BFE0, slot0C=45C390, slot58=5F1F80 and
slot5C cell6C56A8=56C170. Existing action/sequence callees support int returns
and short/int arguments. These facts do not establish original nominal names.

Complete raw traversal closes **435 instructions**, **7 RET0s**, **27 CALLs**,
all internal direct edges and all six destination entries. Direct calls are
4399C0 once,478E60 three times,4067D0 fourteen times,465190 once and45C030
once. Seven further calls use virtual action slot08. The slot58 load at56C7D7
and restored receiver/epilogue prove the one virtual CPU tail at56C7E3.
There is no unresolved external direct tail, remote chunk or EH path.

Prologue reserves18h and saves EBX/EBP/ESI/EDI. EBP starts at-1 for decrements
and becomes2 only in the first record family; EBX holds1 and EDI holds0.
The last instruction is56C7E3 JMP EAX, ending exclusively56C7E5. A three-byte
LEA ECX,[ECX] alignment sequence occupies56C7E5..56C7E7. The two-entry table
starts56C7E8, followed by eight index bytes at56C7F0 and a four-entry capacity
table at56C7F8. Full payload ends exclusively56C808, followed by eight INT3
bytes before the next function. Alignment and32 table bytes earn no authored
credit; no neighbor bytes are included.

Literal widths/bits are independently pinned: float320 at6C13B8, double960
at6C0E98, double5/-5 at6C0648/6C5548, double12/10 at6C35D0/6D6EC0 and
float.3 at6C3298. Unsigned RNG correction uses float2^32 at6D6EF8.
Capacity cases use float6/4/3/1; spawn position/burst parameters use double
240/100/650/30/1 and a float12 loop bound. Identifier DWORD is6FA894.
All existing constant/global bindings suffice; no relocation-ledger change
or new literal override is needed.

## Independently reviewed behavior

| Surface | Native behavior retained |
| --- | --- |
| Prefix |Decrement WORD768; clear DWORD724/728 and6B4..6D0. Signed action50..149 clears WORD76C/76A/766/768/764. Action<=199 separately clears76C/764. Signed55A<1 returns before checked deque selection. |
| Records0..3 initial |Ready state0 selects770 then1 and returns. State1 requires positive signed peer170/174 and readiness, then faces before choosing motion. |
| Edge motion |For ordered x<320, facing+1 uses RNG5+double5, other facing uses double-5-RNG5. For ordered x>double960 those directions swap. Vertical motion uses RNG4+double12. Store scale.3, select701, publish2, then **continue into state2 checks**. |
| Central motion |Default/central position uses double5-RNG10 and RNG4+double10. Store scale.3, select701, publish2, then **return immediately**. Ordered comparisons preserve unordered fallthrough. |
| State2 continuation |Positive peer and readiness face/select710 then1. Nonpositive peer writes1 without that action. State1 itself has no nonpositive-peer fallback store. Callback-side action/peer changes are not assumed absent. |
| Records4..7 |Initial770/1. Ready state1 selects720 then2 without facing or peer gate. Ready positive-peer state2 faces, then chooses725/726 and returns to1. Low position/facing+1 chooses725, otherwise726; high position/facing+1 chooses726, otherwise725. Center/default RNG100<=50 chooses725, else726. |
| Records8..11 initial |Ready state0 selects730 then1 and returns. There is no initial770 or unconditional state1 action transition copied from another fighter. |
| Burst timers |Action731/sequence2 decrements signed DWORD7A4 and7A8. Only7A4<=0 proceeds; signed7A4%30 must be0. Identifier3/2/1/0 selects float capacity6/4/3/1. The other timer still decrements on every gated tick. |
| Burst limit |If capacity is ordered greater than converted signed DWORD7AC, generate the batch. Otherwise set7AC=0 and7A4=180; the already-decremented7A8 remains unchanged. No additional state/peer gate exists here. |
| Captured spawn data |Capture unsigned RNG800+double240 as float x, then RNG400+double100 as float y. The genuinely consumed three-float array receives parameter1=RNG100+double650 before the loop. |
| Twelve-spawn loop |Float index starts0, advances by double1 and remains ordered<12. Each iteration writes parameter0=index*double30 and parameter2=0, then calls spawn920 at captured x/y, re-read unsigned direction byte104, variant1 and count3. Parameter1 remains in the same escaping array across calls. After the loop increment7AC and dispatch wave13. |
| Records248..255 |Conditional action0, then the actual slot58 virtual tail. |

Readiness is the native action700-or0 test. Narrow signed gates, unsigned32 RNG
conversion, double arithmetic, signed counters/remainder, float captures and
callback/store order follow the target. All three packet words are consumed;
no storage is introduced for register shaping.

Capacity has no default assignment in the target. Source deliberately invents
no fallback for an invalid identifier; normal0..3 selection is preserved.
Original invalid-identifier behavior and source declaration remain unknown.
This limitation is not resolved by a byte match or by assuming a decompiler's
invented initialization. No large behavior matrix was needed for this scope.

## Early full comparison and two focused corrections

| Probe | Evidence-backed change and complete result |
| --- | --- |
|00|First complete reviewed body emits1708 versus1688 target bytes. All20 direct CALL sites, the CPU tail, movement/timer/packet operations and frame slots agree. It duplicates the central action726 callback, giving8 physical virtual CALLs versus7. Capacity comparison also loads its operands in reverse order. First+0xBC is a downstream branch displacement. |
|01|Express the center selection as RNG100<=50 ->725, else726, in the same branch order as the native shared endpoints. VC8 now reuses the actual two callback tails. Full1688 and every other instruction agree; only the capacity operand loads and x87 test/branch remain, first+0x51D. |
|02 selected|Express the native capacity-left ordered comparison as count>float(counter). FLD capacity precedes FILD counter and the native TEST AH,5/JP gate is recovered. Complete1688 becomes exact, including alignment, both destination tables and the index map. |

These corrections explain native callback sharing and x87 operand ownership.
They do not change compiler settings or substitute a local-window score for
full equality. The source retains its ordinary structured branches and actual
consumed locals; source spelling/full-class recovery is not asserted.

A generated-object negative increments the first switch destination's addend
in a separate COFF file. Full audit rejects it at `+0x678 /0x0056C7E8`,
target4C/source4D. The callable body still agrees; target PE bytes are untouched.
This demonstrates that metadata is actively compared.

## Validation and retained evidence

IDA preflight rejects the different executable open in the GUI; no semantics
or writes from that session are used. One read-only Ghidra run independently
attests executable SHA/base/entry68B9D2, Windows x86 language/compiler and all
raw-backed sections. Its temporary raw-bounded1653-byte entry closes435
instructions; callee views/metadata are read back and rolled back. All nine
primary DB pins remain unchanged. Decompiler output corroborates raw facts
and is not pasted into source; in particular, raw operands establish the
spawn's float arguments. Own process uses384MiB/one CPU. All compiles remain
serial CPU0/nice10, with memory/swap monitored.

Private recipes and all three complete probes remain under
`.analysis/exact-first-yuyuko-slot5c-20261024/`; the matching `build/` scope
retains CFG/tables/literals, attestation/DB pins, formal/cold comparisons,
formal object/provenance and generated negative. Private reports/binaries/
databases are not committed.

Only Yuyuko's origin evidence label becomes canonical-exact-authored. The
nonmatching Fighter-vtable selector becomes46 roots/1028598 provisional bytes;
its immutable73-root witness and all dispositions/denominator remain unchanged.
Ledger totals become1399 exact functions/330507 callable bytes, without a new
aggregate cold replay claim. Source-present becomes1527 and configured graph
567 units/1535 functions. Continue independently reviewed same-slot peers;
previously recorded nonexact layout residuals stay parked.
