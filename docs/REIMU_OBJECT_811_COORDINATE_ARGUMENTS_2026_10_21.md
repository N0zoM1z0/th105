# ReimuObject 811 coordinate arguments

811 sequence0 now reads facing and prepares its outgoing metadata before the
two original RNG32 coordinate calls.640 initialized-lookup/RNG prefixes agree;
the predecessor fails640 facing/pending cases despite equal outputs. The
161-byte interior request window agrees after replaying its three known direct
calls. Whole496540 remains **nonexact49655F/+31**; this window receives no
function or partial exact credit.

## Target observations and source inference

Only original Japanese TH10.5 v1.06a is used, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Fresh target/status/tracking checks pass. IDA rejects10350095... and supplies
no semantics. No Ghidra process, metadata write or target patch is used.
The main39853-byte candidate, ECX/RET0 observations, void inference and
46138-byte target comparison ownership remain unchanged.

Raw4978BE..49795F prepares `{heading,5,5}`, count3, packet pointer, variant1
and facing byte104 before the first RNG32 at4978F5. The real Y argument is
already on the stack at the second RNG32 at497925. The actual request is
64CCB0 at49795A. The source previously computed two float locals before
reading facing. Keeping the actual X/Y expressions inside the call arguments
recovers this VC8 order, preserving unsigned-to-float conversion, float-field
addition, double16 subtraction and final float round trips. It does not prove
unique original source spelling or portable C++ argument evaluation order.

The complete161-byte candidate window at native801271..801312 agrees with
4978BE..49795F after replaying only direct calls at offsets55/103/156 to
4067D0/4067D0/64CCB0. All other bytes, including stack offsets and branches,
are equal. Target window SHA256:
`a838780617e9cb62a9da39cd0f3dc048a00589e2822a3cf8c473c816b5606175`.
This is an interior diagnostic, not a separately accepted function boundary.

The initial call-sharing investigation also rechecks4351C0's complete62-byte
body: it tail-jumps to virtual slot5 and forwards that AL result without
normalization. The current evidence does not justify replacing its byte
return contract with bool; no return declaration or helper body is changed.

## New native observer and affected replay

`scripts/audit-reimu-object-811-coordinate-arguments.py` observes actual facing
reads, original RNG entries/results, prepared stack arguments and logical x87
state. The expected order is `facing,rng32,rng32`. At the first RNG, facing,
variant, pointer and count must already occupy their actual outgoing slots;
at the second RNG, the real Y argument must precede them. Both packets must
match the eventual actual request. The packet offset is-112 from root-entry
SP on both target and source.

640 cases cover eight periodic counters including negative values, two
facings, five real MT seeds, two x87 control words and four coordinate pairs
including NaN. The original4065B0 initializer supplies the real lookup table;
original seeding, lookup helpers and RNG execute. The observer stops at the
actual unparented request entry and fabricates no return. Input SHA256:
`a3eb23a8ceb6a0e10e232568de5d9e05fcf8547d101e8e374c16a47180705216`.

All640 selected cases agree in outputs, ordered writes, facing order,
pending arguments, RNG results and logical x87 state. Frozen predecessor
4166880c agrees in outputs/writes/RNG/x87 but fails640 facing and pending
cases. Physical TOP, exception flags, unmasked exceptions, arbitrary aliases
and returning-request behavior remain outside this finite evidence.

Only811 and817 instruction graphs change. The817 change is an added JMP over
`LEA EBX,[EBX]` alignment following an opaque parented request. Static edge
inspection proves the jump reaches the original next instruction and skips
the register-preserving bytes; this is not returning-request execution.
The affected817 coordinate640 and turn320 checks freshly pass. The complete
formal native export equals the tested private candidate, connecting these
receipts to the selected source without an unnecessary broad replay.

## Formal comparison and preserved unknowns

| Artifact | SHA256 |
| --- | --- |
| CRLF CPP | `3b9e4896c3645bb1228db3b432a832154870c5639a80df6c02cb67ce2dba12cc` |
| Unchanged header | `6f469e6886959fd41ee6976b3c784c3df0c2e753ad4729a536764a3c8cd28b4b` |
| Formal COFF | `a6fc0066ade9190fa2aaae5996943598c280f26519ce9cdd0fda13095720a5b7` |
| Whole45700-byte canonical source section | `d0ff3d3259c823cc56e322c5e0ec238456d8b490c78b4a5336a249b45a405a58` |

Ordinary SP1 O2/GS-off retains438h frame,44832 code+868 metadata bytes,
10393 decoded instructions,428 calls and63 RETs. Same-TU4963A0 remains66/66
canonicalad12b782. The target still owns46128 code bytes/10670 instructions/
433 calls/68 RETs; the comparator requests46138 bytes and hashes the available
45700 source bytes. The first difference remains the+31 default jump.

41/43 source instruction graphs and all reviewed switch tables remain
identical after recorded address/edge normalization. All call/RET membership
multisets remain unchanged, distances11/27. These diagnostics do not normalize
the strict comparator.822/821/World/selector/packet checks retain their
preceding epochs; their owners' instruction graphs remain unchanged. In
particular, the preceding99 World memberships and16 packet-slot observations
are not reported as fresh executions.

Other4351C0/indirect-call sharing, return sharing,822 direction register
allocation and908's post-wave FILD/FADD-memory form remain open. No compiler
or LTCG impossibility, new exact function or aggregate cold result is claimed.
Header, ABI, layout, flags, bindings, ownership, origin and matches are unchanged.

## Local receipts

`build/reimu-object-811-arguments-20261021/` retains frozen baseline, private
candidate, formaltested.obj, positive/negative execution receipts and
`facts-summary.json`. Private recipes live in the same-named `.analysis/`
directory. Five preceding822 diagnostic graphs are SHA-checked/gzip-compressed
with per-file readback in `historical-diagnostics-compression.json`; frozen
source/COFF/native inputs and all comparison/execution receipts remain. Restore
those `.gz` reports before rerunning older private recipes. The current811
graphs stay loose. The graph diagnostic additionally recognizes the exact trailing
register-preserving `8D4900` alignment form; it is not an acceptance rule.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-reimu-object-action-state --compare --json
# Expected exit1:496540 nonexact+31;4963A0 exact66/66.
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-811-coordinate-arguments.py build/match-units/GptWeb_ReimuObjectActionState.obj --output build/reimu-811-arguments.json
```

See the [preceding822 checkpoint](REIMU_OBJECT_822_ARGUMENT_LIFETIMES_2026_10_21.md)
for its frozen source/control pins and compressed completed compiler graphs.
