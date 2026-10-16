# Common Fighter native animation paths, October 17

`Fighter_update_common_action_state @ 0x004740C0` remains the active major
root: 10,219 callable bytes shared by all 15 roster action roots. This batch
executes the previously unmodeled animation dependencies of actions 73, 75
and 88. It adds no exact or partial byte credit and changes no C++ source,
compiler profile, layout, relocation mapping or accepted unit.

## Canonical result

The fresh configured build remains nonexact at `+0x14 / 0x004740D4`, target
`48`, candidate `95`. Its canonical 10,219-byte window still hashes to
`99563500433bccf1f68e7c256b438595de9cdcf5b18aee4816f19e69e1cda835`.
The owner diagnostic remains **53/66**, metadata `+0x2838`, section tail
10,801 bytes. These diagnostics are not separate function matches.

The original Japanese 1.06a executable SHA-256 is
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`;
the root body hash is
`7def23cf4826d7511260e7d9ea8db18848c43a7b77939bb42724a29af117a0c6`.
IDA preflight again rejects the attached, different executable. No IDA
analysis or database mutation is used in this batch. The earlier attested
Ghidra receiver/types and [native motion evidence](COMMON_FIGHTER_NATIVE_MOTION_2026_10_17.md)
retain their own scope.

## Native animation controls

```bash
python3 scripts/build.py --unit gpt-web-fighter-common-action-state --compare --json
python3 scripts/audit-giant-action-owners.py fighter-common-action build/match-units/GptWeb_FighterCommonActionState.obj --unit gpt-web-fighter-common-action-state --json
python3 scripts/audit-common-fighter-animation-paths.py build/match-units/GptWeb_FighterCommonActionState.obj
```

The build returns 1 for the ordinary mismatch. The execution command returns
0 for **6,048 sampled cases with zero differences**, visiting **159/2,799**
target root instructions and 159 candidate instructions. This is a different
scope from the previous 403-instruction motion matrix; the counts are not
added as unique coverage, and the old matrix is not claimed as freshly rerun.

The new oracle executes original native instructions for the virtual calls,
action-tree lookup, frame selection, texture-vector access, untextured sprite
setup and transform copies. It neither supplies helper returns nor replaces
vtable entries or instructions. Original `CharacterEx` vtable `0x006C3F94`
slots `+0x0C/+0x14/+0x1C/+0x20` are attested against the PE. This proves the
fixture's exercised animation dispatch, without extending the earlier
receiver-domain claim to every possible dynamic class.

The explicit input graph contains one action-tree node plus its sentinel,
four properly linked 0x20-byte sequence blocks, one or two 0x88-byte frames
per block, and a checked one-entry texture vector holding handle zero.
Frame duration is 3; rectangle coordinates/sizes are distinct and valid;
render mode -1 follows the native non-transform branch. Handle zero follows
the native untextured branch, avoiding a graphics backend without inventing
one. The graph is read-only to native code. Its supplied data is an analysis
fixture, not extracted game assets or evidence of a complete resource class.

All cases use Y=100 and the original zero-initialized stage surface. They
cover three transitions independently checked against the target call trace:

| Input | Original path |
| --- | --- |
| Unexpired timer 0, limit 3 | Increment counters; no frame dispatch |
| Expired timer 2, two frames | Advance to frame 1 and apply its sprite data |
| Expired timer 2, one frame | Wrap, advance to block 1, reset timer/counter, then select sequence 2 or 3 when vertical velocity is nonzero |

The full matrix varies 12 raw bit patterns for each velocity: signed zeros,
minimum subnormals, +/-3, infinities, quiet NaNs and signaling NaNs. It uses
masked x87 PC53/PC64. Actions 73/88 include both stage edges and center;
action 75 stays at center because its wall-action setter needs additional
context. No floating-point exception equivalence is claimed.

Every execution reaches the genuine RET with caller stack delta 4, restored
x87 TOP and restored EBX/ESI/EDI/EBP sentinels. The comparison includes all
0x7A4 actor bytes, helper entries/receivers, selected sequence/frame arguments,
physical x87 conversion inputs, stack, callee-saved registers and control
word. Writes outside actor/stack, unreviewed code execution and virtual calls
outside the admitted slots fail. Full gameplay, branch and numerical
equivalence remain unproved.

| Original dependency | Calls per target/candidate matrix |
| --- | ---: |
| crossed-surface 5F9310 / surface 435D60 / conversion 68A1A0 / advance 4351C0 | 6,048 each |
| boundary 435910 | 5,472 |
| next frame 45C1A0 | 4,032 |
| next block 45C220 | 2,016 |
| set frame 45C180 | 3,696 |
| select sequence 45C390 / tree lookup 45C320 | 1,680 each |
| apply frame 45C110 / sprite frame 436760 / texture vector 40C100 / texture 407160 / rectangle 407230 / reset 4073A0 / commit 4073C0 | 7,728 each |

Both implementations select sequence 3 in 280 cases and sequence 2 in 1,400.
Input SHA-256:
`d25ca2a68cc33c2875413130b0ec3fdac5ffc86c132fbdc3a3cfe5b00758f303`.
The report also records executable/body/object and emulator library hashes;
its object hash agrees with the separate fresh configured build receipt.
The oracle itself does not attest compiler provenance.

## Negative controls and source-partition hypothesis

A private real C++ control changes the common `!velocity_x_f4` test into
`!(velocity_x_f4 < 0.0f || velocity_x_f4 > 0.0f)`. The 72-case smoke matrix
detects **three differences** and exits 1: for each action's shared selection,
quiet NaN horizontal velocity plus vertical velocity 3 selects sequence 2 in
the target and sequence 3 in the control. Real tree lookup and frame/sprite
application execute on both sides; the resulting actor/frame pointers differ.
The control is not retained as reconstruction source.

An action-75 edge input with negative-infinite horizontal velocity reaches
virtual action setter `45BFE0`; the tool rejects this unmodeled context before
executing it. No callback or helper result is fabricated to admit the path.

Complete state-specific inline handlers were also tested as a possible phase
boundary for native switch lowering. Extracting the entire real 50/51/52
bodies under the existing nested dispatcher is byte-neutral, retaining the
same window hash and 53/66 diagnostic owners. Flattening that dispatcher
fails the required low-table topology; also extracting complete 62/63/64
bodies still merges target-distinct owners. No score is assigned to those
invalid topologies. These controls reject this partition explanation; they
do not establish that all source/TU alternatives are exhausted or that LTCG
is the cause.

Final local evidence: `build/common-animation-final-build.json`,
`common-animation-final-owners.json`, `common-animation-final-native.json`,
`common-animation-final-negative-zero.json` and
`common-animation-scope-negative.json`. Private source recipes remain under
`.analysis/common-handler-20261017/`; generated objects are disposable.
The remaining whole-root blocker is simultaneous clamp/sequence physical
ownership and SUB lowering while preserving rounding and unordered behavior.
