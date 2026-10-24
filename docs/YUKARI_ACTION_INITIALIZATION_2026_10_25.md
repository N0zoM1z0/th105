# Yukari action initialization: 2026-10-25

`Yukari_initialize_action_entry @ 0x0058A4F0` accepts3455 callable bytes and
the complete4381-byte emitted payload. Formal and independent cold VC8 builds
reproduce SHA256
`e0a7822f65f99607719fd6354ba4d14e4e182439d1aebae2ef0d2a1888135334`
with all151 section relocations replayed and no masked differences. The whole
comparison found a real action214 state-write error before acceptance.

## Observed boundary, ownership and ABI

Target is Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The current IDA session still fails target attestation; it is not used. No
Ghidra/decompiler session is used. All869 linear main instructions were read
from the hash-attested PE; retained source supplies no independent target fact.

The candidate `[58A4F0,58B26F)` is3455 bytes, SHA256
`765e801111cac9931a478958e39115b0f4a0128f6379d6a9657486aa688824d3`.
The complete resolved CFG closes866 reachable instructions/3441 bytes/36 RET0s.
Unreachable internal alignment occupies14 bytes at58A848..58A84F and
58A97A..58A97F. These bytes remain in the canonical comparison. Four external
tail sites enter actual zero-motion45AF40 and the default tail enters477830.
Three preceding INT3s isolate the entry; next candidate58B610 follows the
reviewed payload and three bytes of trailing padding. No EH/GS frame is present.
The real16-byte temporary frame coexists with EBX/ESI/EDI saves and ECX receiver.

The existing RTTI-backed Fighter origin anchor pins primary cell6C5908 at
offset3C of Yukari vtable6C58CC to58A4F0. This establishes authored ownership;
it did not establish source or exactness before this work. Exact promotion
removes only this3455-byte root from the rule's `skip_matching` census. Neither
authored denominator nor candidate size changes.

Full `[58A4F0,58B60D)` includes all main bytes, two alignment bytes,57
destination DWORDs/228 bytes and696 remap bytes:

| Destination table | DWORDs | Input range | Remap start/bytes |
| --- | ---: | --- | --- |
| 58B270 | 14 | 4..214 | 58B2A8 /211 |
| 58B37C | 26 | 301..548 | 58B3E4 /248 |
| 58B4DC | 17 | 562..798 | 58B520 /237 |

The third switch uses ECX for its remapped byte index. Actions300 and560/561
have direct dispatch branches outside these table ranges. Adjacent metadata
is compared in full and receives no extra callable/authored-byte credit.

The source uses a pointer-only virtual view with observed slot8 action setter
and slot3C initializer. It never instantiates/embeds a complete Fighter. The
scratch reset receives this+4 and has a separate pointer-only declaration.
Normal thiscall declarations bind all ten actual external symbols. Physical
CALL counts are473F90 secondary-cycle3,435240 effect8,4359D0 layout-scalar2,
4359F0 event3,465190 spawn2,435110 scratch1,45AF40 zero-motion24,4351C0 frame1
and45C030 wave1. One virtual action call remains. Four45AF40 JMPs and the
477830 default JMP survive. No declaration-only callee receives new credit.

Short effect action/byte-facing transport follows the actual435200 word setter
and437C00 byte direction read, independently witnessed by the prior exact52-byte
forwarder in `COMMON_ACTION_INITIALIZATION_2026_10_25.md`. The spawn direction
is transported as a zero-extended byte; the original manager formal spelling
remains unproved. Its real pointer/count packet is represented as three floats,
not integer pointer fabrication. The return value is unused at both spawn sites.

## Whole-source comparisons and corrections

Private receipts are below `build/exact-first-yukari-action-entry-20261025/`;
trial sources/scripts remain in
`.analysis/exact-first-yukari-action-entry-20261025/`.

| Complete source/control | Full bytes | Canonical SHA256 | Result |
| --- | ---: | --- | --- |
| First complete source | 4326 | cefc5a5dd4310e31345476ee61c393d8ff78b815b8cd1e3eeb72f2d4d30dc2aa | nonexact+8 |
| Independent505/510 and565/566 arms | 4330 | 42b57a72e94f198ce145bbd122fee2a06add307cc400f1fb9f75eee2d3613289 | nonexact+2A |
| Case-local797/798 payload lifetime | 4322 | 458b58d9ec4188fa0bd1a905091e1b4fade9966ff81a065d083b16871533690a | nonexact+2A |
| Independent560/561 versus562/563 entries | 4333 | 3a380c83b4d631c04311cf66a259e78f12be68e01378b8d94207f1e806e6ae20 | nonexact+2A |
| Explicit target-order scalar publications | 4381 | b39eec6726cb5b435f6e92c18632479881481b7a525859ae5496def82bd3dae5 | two unequal bytes |
| Correct action214's74C zero | 4381 | e0a7822f65f99607719fd6354ba4d14e4e182439d1aebae2ef0d2a1888135334 | exact |

Each change answers observed whole-function evidence. Conditional constant
selection had pooled two real zero-motion sites; independent arms recover them.
Function-scope payload lifetime made four real zero-motion tails and the common
default into ordinary calls. Restricting each actual packet to its797/798 case
recovers all five tails. Independently retaining560..563 source arms restores
the actual17-word third table and its562 lower bound. Chained zero assignments
published fields in reverse order and merged target-retained suffixes. Ordinary
explicit stores in target-observed order recover the complete4381-byte shape.
There is no compiler flag search, padding, assembly, inert storage or fake caller.

Only two bytes then differ, at58AA79 and58AA97, both x87 store/pop encodings in
action214. Stack tracing shows the zero loaded at58AA54 survives through108's
store and the115 load/store. The10 literal at58AA8A is popped into73C, leaving
the original zero for74C. The earlier source incorrectly assigned10 to both.
Changing only74C to0 reproduces the entire payload exactly. This is a semantic
correction revealed by complete comparison, not acceptance of a same-size body.

The optional one-case native reset witness executes the actual root and actual
67-byte435110 helper through RET0, preserving the return stack and nonvolatile
registers. It compares all0x900 receiver bytes. The corrected source agrees;
the old4381-byte source produces74C=10 instead of0 and differs at74E/74F.
Each side executes the original scratch helper once; no provider return or
substitute helper is supplied. Broader behavior matrices are unnecessary for
this closed ambiguity and are not run.

## Independent semantic review

Numeric states and field names stay provisional, but complete behavior is
instruction-reviewed before source selection:

- Movement70..89 preserves facing widths, the five-effect loops, existing
  7A0/7A2 conversions and actual999 spawn guard at7A4.214 has115 in10C,10 in73C
  and0 in74C after resetting the actual this+4 scratch object.
- Action300 checks142/140 before initialization; only then conditionally calls
  zero-motion and sets184/180. A nonzero47E gates rounded float subtraction by
  double0.5; only ordered negative speed clamps and clears47E. Actual frame
  advancement may invoke slot8 with0, then updated142/140 gate event27.
- Action402 clears740 without750;404/406 use the double-expanded values of
  float0.2/0.1 and retain their distinct740 reset.414..416 scale by0.25.
- Action520 alone can set4A8=2, using signed byte605>=4.565 and566 publish
  distinct184 values1/10 after real zero-motion; both retain750=1.
- 600..603 leave730/732 unchanged.606/656 clear73C/730/738 before the real
  zero tail;710 clears three shorts without changing180.797/798 spawn899 at
  x360/920,y100 with direction byte, variant-1, a real zero float[3] and count3,
  then dispatch wave1. Unhandled actions tail into477830.

Exact bytes do not prove original local names, full class layout or original
source/TU partition. No new inference about a parked peer's LTCG context follows.
The successful recipe is independently checked complete arms, actual packet
lifetimes and early full comparison; revalidate differences for each next peer.

## Reproduction and handoff

Run commands serially, CPU0/nice10, with the locked repository interpreter:

```sh
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-yukari-action-initialization --compare --json
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-yukari-action-initialization.py --scoped-reset
TH105_ENABLE_GS=0 TH105_FP_MODE=default TH105_INLINE_MODE=default \
  taskset -c 0 nice -n 10 scripts/compile-unit.sh src/characters/YukariActionInitialization.cpp build/yukari-entry-cold.obj
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-yukari-action-initialization.py --object build/yukari-entry-cold.obj
taskset -c 0 nice -n 10 scripts/repo-python scripts/function-origins.py --check
taskset -c 0 nice -n 10 scripts/repo-python scripts/verify-exact-units.py --all
```

Five target-free fixtures cover all three table ranges, the ECX index, corrupt
final indices, metadata destinations, remap truncation and unreviewed CFG tails.
Only new local source/interfaces/unit and25 exclusive literal aliases are added.
Prior accepted source, headers, compiler settings and bindings are unchanged.
The complete serial cold replay passes516 units/all1404 accepted functions:
`build/exact-first-yukari-action-entry-20261025/cold-all.log`. The exact ledger
now records363195 authored bytes; source-present1547/mapped1566, units586.

Next source-missing same-slot representative is Patchouli51D650, candidate3132
bytes in the RTTI-backed roster ledger. Re-attest target/slot and reconcile its
own complete CFG/ABI before carrying over any source. Reimu/Udonge/common
residuals remain parked without new independent evidence.
