# Patchouli control mode: complete source and parked stack-layout residual

## Result and reproduction

Patchouli Fighter primary slot `+0x5C @0x0051CB40` now has complete source in
`src/characters/PatchouliControlMode.cpp/.hpp`. Target and selected source both
have **2686 callable bytes /2736 complete emitted bytes**. Strict comparison
remains **nonexact** at `+8 /0x0051CB48`: native frame immediate 4C versus
source 44. There is no matches row and no additional exact credit.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-patchouli-control-mode --compare --json
```

Both commands correctly return 1. The full audit checks every section-tail byte
and exact length, replaying all 92 function relocations (24 REL32 /68 DIR32),
including metadata relocations beyond the callable boundary. Formal build
reproduces the selected private probe. All 50 alignment/table bytes agree.

Target callable SHA256:
`bec7ad0d8afc74c17000a02b991a26a354cfba60928d2ffb72cdb49596e25cb9`.
Target full SHA256:
`7ae2d1d9ab9029452be7f05765855b81bad68d7acc76c525399e0231bf4aba58`.
Selected full canonical SHA256:
`1fbbee3ca927710d63d1b3a1ce9fce08fa81c3df67b289c2bce6cb54d8186885`.

A diagnostic independently decodes all 710 callable instructions in both
candidates. Instruction addresses/sizes/mnemonics agree. Every differing byte
is classified: one frame immediate and 40 one-byte ESP displacements. All other
instruction encodings and the complete 50 metadata bytes agree. This is a
residual classification, **not** a masked match or semantic/exact acceptance.

## Observed target facts

Only original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is inspected. Existing RTTI ownership classifies this root as authored; raw
primary slot 5C cell 6C4F08 points to 51CB40. Slot 08/0C bind 45BFE0/45C390 and
slot 58 binds the shared 5F1F80 policy. Declaration-only callees earn no credit.

Raw traversal closes **710 instructions**, **10 RET 0s**, **33 calls**, all
internal direct edges and ten destination entries. Direct calls comprise
4399C0 once,478E60 three times,4067D0 six times,465190 seven times,45C030 three
times and 4063D0/406360 twice each. Virtual calls comprise eight action callbacks
and one CPU slot 58 CALL followed by frame teardown, not a tail JMP. There is
no unresolved register jump, remote chunk or EH path in this bounded body.

Native prologue aligns ESP to eight bytes, reserves 4Ch, saves EBX/ESI/EDI and
retains EBP for frame restoration. Callable end is exclusive 51D5BE. Two-byte
MOV EDI,EDI alignment precedes the two-entry table 51D5C0 and eight-byte index
map 51D5C8. Four-entry tables at 51D5D0 and 51D5E0 dispatch identifiers 0..3.
Full payload ends exclusively 51D5F0, where the separately accepted 89-byte
round-reset function begins. Six INT3 bytes precede this root. Neither adjacent
function is included or changed; metadata gives no authored-byte credit.

## Independently reviewed behavior

| Surface | Native operations retained in complete source |
| --- | --- |
| Prefix |Decrement WORD768, clear command words/dwords and five action-conditioned lanes, then the signed 55A gate. |
| Records 0..3 |State 0/ready selects 770 then 1. State 1/positive peer faces, selects 710 then 1; nonpositive peer also writes 1. State 2/positive peer/ready faces, uses unsigned RNG 15 for horizontal motion, RNG 4+double 8.0 for vertical, scale.3f, then 701/state1. The unusual state 1 continuation remains. |
| Records 4..7 initial spawn |Action 720/sequence3 or action 721 decrements positive WORD7A6. At zero, publish-1, spawn 910 with three zero floats at self x/y+double 100.0, then dispatch wave 12. |
| Records 4..7 ring timer |Decrement WORD7A8. At<=0, dispatch 12 and capture unsigned RNG 360 as float phase. Identifier 3/2/1 reset 300 and generate 12/9/8 packets with double steps 30/40/45; identifier 0 resets 360 and generates 6 with step 60. Each three-float packet contains phase+n*step,6f,3f. Independent physical loops remain. |
| Records 4..7 state flow |Ready 0 selects 770 then 1; ready 1 faces/selects720 then 2. State 2/action720/sequence3 publishes 3/delay60. Expired 3 selects 721 then 4. State 4 explicitly tests action 720, then stores low-word RNG 30+60 and state 3; this guard is not normalized to 721. |
| Records 8..11 timing |Action 730/sequence2 increments signed WORD7AA. Identifier 3/2/1 choose float threshold 120, ring limits 4/3/2 and probabilities25/15/10; identifier 0 chooses 180/2/0. Ordered counter>=threshold plus signed modulo 10 gates work. Exact equality captures x and y+100 anchors and resets 7AE. |
| Main six-way ring |If signed 7AE is below the float ring limit, dispatch 61 and select unsigned RNG 6. For six float indices, packet[0]=n*double 60, packet[1]=(signed 7AE+1)*double 200, packet[2..3]=0; selected index sets flag 3=1f. Explicit float x then y captures use cosine then sine, packet radius and stored anchors. Spawn 920 receives byte facing, variant-1 and four parameters. |
| Nested placements |For positive 7AE, float j loops to the current signed 7AE. A real two-float temporary holds packet angle-double120 and (j+double 1)*double 200. RNG 100<=float probability sets packet flag 3 to 1 without clearing it on failure; the flag stays sticky. Sine then cosine argument evaluation computes positions relative to the captured outer x/y. The original four packet words are passed; temporary angle/radius do not overwrite them. |
| Ring completion |Increment WORD7AE after six outer directions; reaching the ring limit clears 7AE and 7AA. Ready state 0 selects 730 then 1. |
| Records 248..255 |Conditional action0 followed by the genuine virtual CPU CALL and ordinary epilogue. |

The first identifier switch ignores other values after drawing its phase.
The second supplies no initialized defaults for its three real float locals.
Source preserves those observed omissions. Valid identifier domain and invalid
input behavior are not claimed recovered. All signed word consumers, unsigned
RNG conversions, float stores, double literals, repeated post-call reads and
real parameter counts remain explicit. Global 6FA894 retains its conservative
`g_match_identifier` name.

## Focused full-source experiments

| Probe | One evidence-backed question / result |
| --- | --- |
|00|First complete source emits 2740 bytes; all 33 calls and instruction count agree. Differences include probability operand order and local storage. |
|01|Write RNG 100<=chance in the native operand order. Full output becomes 2736; comparison no longer preserves chance in a temporary promoted double across the RNG call. Frame is 44h rather than 4Ch. |
|02 selected|Express the two adjacent, genuinely consumed angle/radius float slots as a two-element temporary. All instruction forms/addresses now agree; only 41 frame/stack bytes remain. This is a local source hypothesis, not proof of an original array declaration. |
|03 negative|A two-member structure for the same consumed pair produces the identical complete candidate as 02. Do not repeat this spelling control. |
|04 rejected|Group all six consumed packet/temporary words into one array while keeping the four-word call count. Output regresses to 2728 bytes and loses two instructions. This storage hypothesis is not selected. |

Keep 02 and these receipts. Frame/array placement remains unknown; do not add
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
checks file SHA, base, entry 68B9D2, Windows x86 language/compiler and every raw
section against the PE. Temporary bounded entry/callee views are read back and
rolled back. All nine primary DB pins are unchanged. Decompiler output only
corroborates raw stack/edge interpretation and is not pasted as source. Heap
384MiB/one CPU; compilation remains serial CPU 0/nice10, with memory monitored.

No shared header, flag, source partition or relocation mapping changes. Existing
exact units remain unchanged. Exact ledger totals stay 1397 functions/327058 bytes;
no aggregate cold replay is claimed. Continue another complete same-slot peer rather
than repeating neutral layout controls.
