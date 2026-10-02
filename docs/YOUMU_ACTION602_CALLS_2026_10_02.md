# Youmu action-602 conversion, loop and shared-call recovery, 2026-10-02

## Retained result

**Observed:** `Youmu_dispatch_action_state_vslot28 @ 0x00530200` remains
nonexact over all 37,692 callable bytes. This checkpoint restores two
unsigned-to-float conversions in action 602, uses its one target-supported
float loop counter directly, and routes its sequence-advance exit through
the existing shared call/return path.

Fresh configured comparison still first differs at `+0xCA / 0x005302CA`,
target `64`, candidate `D8`. Metadata remains `+0x92B0` versus target
`+0x933C`. Strict instruction/edge diagnostics remain **26/98**, with no
gained or lost identical owner. Candidate still has 97 physical destinations
/ 33 low entries without merged target-distinct owners. No authored exact
function or byte credit is added.

Target callable SHA-256:
`19f2d4fba4f6ea626b69a28f4717d0fcfae06ea97e95ddb24e656e0ea518ed74`.
Retained CRLF source SHA-256:
`02a7552d8ba881b7cb1665e39fb930aaecaccaaeb5f0fc8a9f164c561ebb50b6`.
Canonical compared candidate-window SHA-256:
`90479dbb74a9f98df279c6d2da0c845a630be3c9442cc7a6a4d43c22a40e79cc`.
The candidate window includes its earlier metadata and is not a body hash.

## Unsigned conversion evidence

**Observed:** action 602 calls `selector_random_roll @ 0x4067D0` twice with
limit 360. Each caller performs a signed FILD of the returned word and adds
float `2^32` if EAX is negative, then writes the payload angle as a dword.
The float at `0x6D6EF8` has bits `0x4F800000`, value 4294967296.

| Roll | Call | Conversion | Payload store |
| --- | --- | --- | --- |
| First | `537017 CALL 4067D0` | `53701F TEST EAX,EAX; 537021 MOV [ESP+1C],EAX; 537025 FILD [ESP+1C]; 537029 JGE 537031; 53702B FADD [6D6EF8]` | `537031 FSTP [ESP+34]` |
| Second | `537080 CALL 4067D0` | `537088 TEST EAX,EAX; 53708A MOV [ESP+1C],EAX; 53708E FILD [ESP+1C]; 537092 JGE 53709A; 537094 FADD [6D6EF8]` | `53709A FSTP [ESP+34]` |

The retained source previously used `(float)selector_random_roll(360)`.
It now explicitly converts through unsigned int in both assignments.
Natural VC8 emits the target conditional `+2^32` conversion algorithm.
Source spelling is inferred; the instruction algorithm is observed.

The actual producer is independently reread as a 27-byte unsigned quotient:
`value / (UINT_MAX / limit)`. With limit 360, its range is **0 through 360**,
so its valid results do not exercise the high-bit correction. This is not
a claim of an observed gameplay-value bug, nor a reason to change the
already-exact producer's int return view or shared ABI. It recovers the
conversion visible in this caller. The upper endpoint is not inferred as
359 from an assumed modulo implementation.

## One float loop counter

**Observed:** `5370E2 FSTP [ESP+10]` initializes the index, and `5370E6 FLD`
feeds it directly to multiply-by-60 and add-30. Each iteration ends with
`537174 FLD [ESP+10]; 537178 FADD 1.0; 53717E FSTP [ESP+10]`. The counter
reload at `537188` then participates in `FCOM ST(1); FNSTSW AX;
FSTP ST(1); TEST AH,5; JNP 5370EA`. The live counter survives that taken
edge into the next angle expression; the exit discards it.

The old source maintained both float `v360` and double `v112`, copying the
former to the latter before the loop test. The retained source removes this
redundant carrier and uses `v360` in the payload expression. Fresh VC8 now
reproduces the target loop-end FCOM, discard, mask 5 and JNP template. The
counter home is still different: candidate `+0x18`, target `+0x10`.
This is target-supported value-flow recovery, not unique original local
declarations or full exception/precision closure. Ordinary indices 0..6 are
exactly representable in both retained scalar types.

## Shared virtual call and physical-site diagnostics

**Observed:** action 602's threshold edge `536ED6 JGE 534649` reaches the
action-415 physical tail: vtable load, slot `+0x14` call at `534650`, then
root teardown/RET. It skips action 415's preceding acceleration store.
Other direct incoming edges reach this same tail from actions 410, 411,
510 and 605. The source's existing `LABEL_898` already represents the
sequence-call/return path; action 602 now joins it rather than duplicating
the call and return locally. Physical placement remains a compiler result.

| Virtual slot | Target physical calls | Previous candidate | Retained candidate |
| --- | --- | --- | --- |
| `+0x08` | 107 | 105 | 105 |
| `+0x0C` | 31 | 31 | 31 |
| `+0x14` | 12 | 14 | 13 |
| `+0x1C` | 2 | 2 | 2 |

The local action-602 `+0x14` physical site is removed. Its retained join
still reaches a differently placed shared tail, and action 740 still has
an extra physical `+0x14` site: target `539273 JGE 535B0B` shares the
action-529 call at `535B12`, while candidate emits its own site. Relocating
the existing source label alone does not recover that placement.

These are static-site counts, not runtime call counts or proof of missing
behavior. For example, candidate action 203 reaches the shared zero-motion,
surface-height and action-10 sequence at `531021`; its physical slot-8 call
is classified under the preceding owner. Raw call order agrees with target
action 203 at `531232..53124F`. The owner-count difference does not justify
adding another executed setter. Other slot-8/slot-C sharing and placement
remain unresolved; this is not global semantic closure.

## Bounded probes and validation

| Probe | Observation | Disposition |
| --- | --- | --- |
| Move shared sequence tail into source action 415 and route 602 to it | 26/98, metadata `+0x92A0`, 13 physical slot-14 sites. | Extra label relocation not retained. |
| Move shared sequence tail into source action 529 | Entire compared window byte-neutral, 26/98. | Not retained. |
| Both relocations | 26/98, metadata `+0x92A0`; moves the remaining extra site to action 605. | Not retained as placement recovery. |
| Two unsigned conversions only | 25/98, loses low11; metadata `+0x92C8`. | Property tested together with the independent shared exit. |
| Route 602 only | 26/98, metadata `+0x92A0`, 13 slot-14 sites. | Target-supported shared exit retained. |
| Unsigned conversions plus shared exit | 26/98, metadata `+0x92B0`. | Retained with direct float index use. |
| Change duplicate index carrier to float | 25/98, loses low11; metadata `+0x92B8`. | Not retained. |
| Remove duplicate index carrier | 26/98, metadata `+0x92B0`; target loop-test template restored. | Retained through configured rebuild. |

Private probes are below `.analysis/youmu-call-topology-20261002/` and
`build/youmu-call-topology-20261002/`. Existing-object comparisons are
diagnostic with unverified build provenance. No shared type, accepted helper,
compiler flag, relocation mapping or object partition changes.

```bash
python3 scripts/build.py --unit gpt-web-youmu-vslot28-full-root --compare --json
python3 scripts/audit-giant-action-owners.py youmu-vslot28 \
  build/match-units/GptWeb_YoumuActionState.obj \
  --unit gpt-web-youmu-vslot28-full-root --json
```

Fresh configured reports: `build/youmu-action602-final-20261002.json` and
`build/youmu-action602-final-owners-20261002.json`. Private call classifier:
`.analysis/youmu-call-topology-20261002/call-packets.py`; report
`build/youmu-action602-final-calls-20261002.json`. Its linear predecessor
slot classification is a diagnostic; the accepted target edges and the
action-203 shared path are separately reconciled above.

The explicit-object guard and stack analyses described in
[the preceding float-carrier checkpoint](YOUMU_FLOAT_CARRIERS_2026_10_02.md)
are replayed to `build/youmu-action602-final-guards-20261002.json` and
`build/youmu-action602-final-stack-20261002.json`. They again report 138/138
masked guards with zero unordered-only leads, and 49 resolved spawn payload
sites without conflicting modeled ESP merges. The same six payload-address
owners remain different. Target traversal remains 9,912 instructions /
37,692 callable bytes without unresolved indirect jumps.

**Unknown:** exact shared-tail placement, remaining argument schedules,
float lifetimes, original local/TU/compiler context and full numerical
closure. Neither these discrepancies nor the TH08 special-instruction
examples prove an assembly or LTCG requirement. No new Ghidra or IDA output
is used. Whole-root canonical zero-difference replay is still required;
this focused result does not claim aggregate cold replay.
