# Patchouli control mode: complete source and parked stack-layout residual

## Result and reproduction

Patchouli Fighter primary slot `+0x5C @0x0051CB40` now has complete source in
`src/characters/PatchouliControlMode.cpp/.hpp`. Target and selected source both
have **2686 callable bytes /2736 complete emitted bytes**. Strict comparison
remains **nonexact** at `+8 /0x0051CB48`: native frame immediate4C versus
source44. There is no matches row and no additional exact credit.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-patchouli-control-mode --compare --json
python3 scripts/audit-patchouli-control-mode.py
```

Both commands correctly return1. The full audit checks every section-tail byte
and exact length, replaying all92 function relocations (24 REL32 /68 DIR32),
including metadata relocations beyond the callable boundary. Formal build
reproduces the selected private probe. All50 alignment/table bytes agree.

Target callable SHA256:
`bec7ad0d8afc74c17000a02b991a26a354cfba60928d2ffb72cdb49596e25cb9`.
Target full SHA256:
`7ae2d1d9ab9029452be7f05765855b81bad68d7acc76c525399e0231bf4aba58`.
Selected full canonical SHA256:
`1fbbee3ca927710d63d1b3a1ce9fce08fa81c3df67b289c2bce6cb54d8186885`.

A diagnostic independently decodes all710 callable instructions in both
candidates. Instruction addresses/sizes/mnemonics agree. Every differing byte
is classified: one frame immediate and40 one-byte ESP displacements. All other
instruction encodings and the complete50 metadata bytes agree. This is a
residual classification, **not** a masked match or semantic/exact acceptance.

## Observed target facts

Only original Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is inspected. Existing RTTI ownership classifies this root as authored; raw
primary slot5C cell6C4F08 points to51CB40. Slot08/0C bind45BFE0/45C390 and
slot58 binds the shared5F1F80 policy. Declaration-only callees earn no credit.

Raw traversal closes **710 instructions**, **10 RET0s**, **33 calls**, all
internal direct edges and ten destination entries. Direct calls comprise
4399C0 once,478E60 three times,4067D0 six times,465190 seven times,45C030 three
times and4063D0/406360 twice each. Virtual calls comprise eight action callbacks
and one CPU slot58 CALL followed by frame teardown, not a tail JMP. There is
no unresolved register jump, remote chunk or EH path in this bounded body.

Native prologue aligns ESP to eight bytes, reserves4Ch, saves EBX/ESI/EDI and
retains EBP for frame restoration. Callable end is exclusive51D5BE. Two-byte
MOV EDI,EDI alignment precedes the two-entry table51D5C0 and eight-byte index
map51D5C8. Four-entry tables at51D5D0 and51D5E0 dispatch identifiers0..3.
Full payload ends exclusively51D5F0, where the separately accepted89-byte
round-reset function begins. Six INT3 bytes precede this root. Neither adjacent
function is included or changed; metadata gives no authored-byte credit.

## Independently reviewed behavior

| Surface | Native operations retained in complete source |
| --- | --- |
| Prefix |Decrement WORD768, clear command words/dwords and five action-conditioned lanes, then the signed55A gate. |
| Records0..3 |State0/ready selects770 then1. State1/positive peer faces, selects710 then1; nonpositive peer also writes1. State2/positive peer/ready faces, uses unsigned RNG15 for horizontal motion, RNG4+double8.0 for vertical, scale.3f, then701/state1. The unusual state1 continuation remains. |
| Records4..7 initial spawn |Action720/sequence3 or action721 decrements positive WORD7A6. At zero, publish-1, spawn910 with three zero floats at self x/y+double100.0, then dispatch wave12. |
| Records4..7 ring timer |Decrement WORD7A8. At<=0, dispatch12 and capture unsigned RNG360 as float phase. Identifier3/2/1 reset300 and generate12/9/8 packets with double steps30/40/45; identifier0 resets360 and generates6 with step60. Each three-float packet contains phase+n*step,6f,3f. Independent physical loops remain. |
| Records4..7 state flow |Ready0 selects770 then1; ready1 faces/selects720 then2. State2/action720/sequence3 publishes3/delay60. Expired3 selects721 then4. State4 explicitly tests action720, then stores low-word RNG30+60 and state3; this guard is not normalized to721. |
| Records8..11 timing |Action730/sequence2 increments signed WORD7AA. Identifier3/2/1 choose float threshold120, ring limits4/3/2 and probabilities25/15/10; identifier0 chooses180/2/0. Ordered counter>=threshold plus signed modulo10 gates work. Exact equality captures x and y+100 anchors and resets7AE. |
| Main six-way ring |If signed7AE is below the float ring limit, dispatch61 and select unsigned RNG6. For six float indices, packet[0]=n*double60, packet[1]=(signed7AE+1)*double200, packet[2..3]=0; selected index sets flag3=1f. Explicit float x then y captures use cosine then sine, packet radius and stored anchors. Spawn920 receives byte facing, variant-1 and four parameters. |
| Nested placements |For positive7AE, float j loops to the current signed7AE. A real two-float temporary holds packet angle-double120 and (j+double1)*double200. RNG100<=float probability sets packet flag3 to1 without clearing it on failure; the flag stays sticky. Sine then cosine argument evaluation computes positions relative to the captured outer x/y. The original four packet words are passed; temporary angle/radius do not overwrite them. |
| Ring completion |Increment WORD7AE after six outer directions; reaching the ring limit clears7AE and7AA. Ready state0 selects730 then1. |
| Records248..255 |Conditional action0 followed by the genuine virtual CPU CALL and ordinary epilogue. |

The first identifier switch ignores other values after drawing its phase.
The second supplies no initialized defaults for its three real float locals.
Source preserves those observed omissions. Valid identifier domain and invalid
input behavior are not claimed recovered. All signed word consumers, unsigned
RNG conversions, float stores, double literals, repeated post-call reads and
real parameter counts remain explicit. Global6FA894 retains its conservative
`g_match_identifier` name.

## Focused full-source experiments

| Probe | One evidence-backed question / result |
| --- | --- |
|00|First complete source emits2740 bytes; all33 calls and instruction count agree. Differences include probability operand order and local storage. |
|01|Write RNG100<=chance in the native operand order. Full output becomes2736; comparison no longer preserves chance in a temporary promoted double across the RNG call. Frame is44h rather than4Ch. |
|02 selected|Express the two adjacent, genuinely consumed angle/radius float slots as a two-element temporary. All instruction forms/addresses now agree; only41 frame/stack bytes remain. This is a local source hypothesis, not proof of an original array declaration. |
|03 negative|A two-member structure for the same consumed pair produces the identical complete candidate as02. Do not repeat this spelling control. |
|04 rejected|Group all six consumed packet/temporary words into one array while keeping the four-word call count. Output regresses to2728 bytes and loses two instructions. This storage hypothesis is not selected. |

Keep02 and these receipts. Frame/array placement remains unknown; do not add
padding, inert storage, fake behavior or register constraints to fill the
native frame. Seek independent original lifetime/type/TU evidence before
reopening. No compiler-profile search, broad runtime matrix or proof that
LTCG is required is introduced.

## Inferences, validation and retention

The pointer-only receiver must never be constructed or embedded. Full owner
layout, unused virtual signatures and original TU identity remain unknown.
Sine/cosine double-return views are retained hypotheses: raw ST0 does not prove
their original nominal return types. Their caller operations follow the target;
these nonexact callees gain no new implementation or exact credit.

IDA preflight rejects the different executable open there; no semantics or
writes from that session are used. One read-only Ghidra process independently
checks file SHA, base, entry68B9D2, Windows x86 language/compiler and every raw
section against the PE. Temporary bounded entry/callee views are read back and
rolled back. All nine primary DB pins are unchanged. Decompiler output only
corroborates raw stack/edge interpretation and is not pasted as source. Heap
384MiB/one CPU; compilation remains serial CPU0/nice10, with memory monitored.

Private recipes/probes remain under
`.analysis/exact-first-patchouli-slot5c-20261024/`; its `build/` counterpart
retains full raw CFG/tables/literals, attested views/DB pins, probe comparisons,
formal object/provenance and byte-by-byte residual classification. No shared
header, flag, source partition or relocation mapping changes. Existing exact
units remain unchanged. Exact ledger totals stay1397 functions/327058 bytes;
no aggregate cold replay is claimed. Continue another complete same-slot peer
rather than repeating neutral layout controls.
