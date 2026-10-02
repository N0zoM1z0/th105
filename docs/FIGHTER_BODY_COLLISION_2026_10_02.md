# Fighter body collision exact recovery, 2026-10-02

## Accepted result and target identity

`CollisionContext_resolve_fighter_body_collision @ 0x0046CCA0` is canonical
**1862/1862 exact** under the unchanged pinned VC8 SP1 `/O2 /GS-` profile.
The fresh target and relocation-replayed candidate body hashes are both
`c6ef9cab92b2106d93cd532e0074493d3ed0b3d53abaa3ae3ad16f06f0a10cd2`.

```bash
taskset -c 0 python3 scripts/build.py --unit cross-v106a-body-collision --compare --json
```

`build/body-collision-formal-exact-20261002.json` reports `result=ok`, one
exact comparison, a 1862-byte COFF function extent and no first mismatch.
The unit replays all ten REL32 call fields and 24 DIR32 fields. Five decorated
helper mappings cover boundary classification, world-box transform, overlap,
extent reset and stage-height proposal. The two byte globals are pinned to
`0x006E7B6C/6D` with target initial bytes `FF`; the double literals are `1.0`
at `0x006CD160` and `0.5` at `0x006CD138`. All use existing relocation keys;
no shared header, compiler profile or relocation ledger changed.

**Observed:** the raw PE SHA-256 is
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
A fresh `audit-candidate-boundaries.py 0x0046CCA0 --json` reaches all 1862
bytes / 528 instructions, with no undecoded overlaps, indirect jumps,
unreached ranges or outgoing direct branches. Five RETs end at
`0x0046D0DB`, `0x0046D285`, `0x0046D3CF`, `0x0046D3DB`, `0x0046D3E5`;
eight INT3 bytes follow. Entry ECX is the receiver; no stack arguments or
EH funclets occur in this callable. Only ESI/EBX are saved and the frame is
0x40 bytes. The independently established authored battle origin and nine
exact BattleManager/Story callers remain pinned in the archived origin
witness. That witness is replayed by the existing workflow test, including
a deliberately incorrect outgoing helper destination.

The attached IDA session failed identity attestation and was not used.
This unit needed raw PE instruction/CFG evidence, not a new Ghidra import.
Private source probes and disassembly are in `.analysis/body-collision-20261002/`.

## Correcting two retained semantic assumptions

The old retained source was **1853 bytes / 524 instructions**, not merely an
exact implementation with different stack coloring. Its prior "edge/AABB
semantics closed" description was too strong.

**Observed, center tie:** at `0x0046D110..D127`, the target loads the first
box bottom+top sum, loads the second bottom+top sum, compares the second
against the first, then uses `test ah,0x41; je` to select the alternate
resolution path only for ordered `second_y_sum > first_y_sum`. An unordered
result does not take that path. The left-resolution gate therefore needs:

```cpp
!(first_x_sum > second_x_sum) &&
(first_x_sum != second_x_sum || !(first_y_sum < second_y_sum))
```

The retained source's `first_y_sum <= second_y_sum` inverted the finite tie
ordering. Replacing it with `>=` corrected finite inputs but still emitted
`JP` rather than target `JE`: the unordered case also needed the negated
strict comparison. The accepted source preserves the observed sum operand
order and generates the complete comparison bytes naturally.

**Observed, directional velocity rounding:** in both ordinary separation
paths, the target rounds the mean to float, multiplies that mean by each
fighter's signed direction, stores **both directional velocities as floats**,
and only then subtracts the previous motion. The first path additionally
rounds its differences through the independent motion locals. The relevant
stores/loads occur at `0x0046D246..D278` and `0x0046D390..D3BB`.
The retained combined multiplication/subtraction expressions omitted these
intermediate single-precision assignments. Explicit real velocity and
response assignments recover the target x87 stores; these are numerical
semantics, not redundant compiler shaping.

Do not normalize the two subtraction paths. The first subtracts the saved
scaled motions, whereas the alternate path reads the fighters' unscaled
`+0xF4` components. The target distinguishes them and the accepted source
keeps that asymmetry.

## Natural source and lifetime closure

**Inferred source shape, validated code generation:** the four edge-owner
priority updates are ordinary ordered `if/else if` chains. Replacing all
retained labels/gotos with those chains emits the same target branch layout.
Two genuine phases use the existing local scratch union: the early phase
writes/reads its signed boundary byte, and the later phase writes/reads its
float separation. Target stores both at frame `+0x08`; no inactive union
member is read and no artificial storage, padding or alias dependency is
introduced. Separate scalar locals were also tested and emit a larger 0x44
frame under this profile. Original source union spelling versus compiler
slot coalescing remains unknown; the reconstruction expresses the observed
mutually exclusive storage lifetime explicitly.

After the tie and rounding corrections, a clean structured candidate was
1862 bytes / 528 instructions and differed only at two byte positions:
`0x0046D393/D397`, the operand of the alternate mean's store/load. A new
branch-local mean still used a different slot. One actual `float
average_motion` shared by the two ordinary separation paths closes both
positions without altering any calculation, condition, input evaluation
order or global profile. All 1862 bytes then agree after canonical replay.
No assembly, volatile/register forcing, inert locals or fake returns were
used.

**Unknown:** original class spelling, TU partition, variable names and
whether the original scratch reuse came from explicit union source or
compiler lifetime allocation. `CollisionContext` is an ABI facade whose
receiver fields and call contracts are independently supported by existing
exact collision helpers and exact callers. Exact acceptance proves this
reproducible source/object result, not recovery of the author's text.

## State and verification scope

`functions.csv`, `reccmp-functions.csv`, `implemented.csv`, `matches.csv`
and `match-units.toml` now record the selected implementation and exact
result. Its old active origin rule moves to `accepted_evidence`; the canonical
matching baseline owns its unchanged `authored_game/battle` census row.
The change adds **one exact function / 1862 exact bytes** and one source-present
function. Only the affected object needs a focused replay; no aggregate cold
replay is claimed. Final local CI and whitespace gates are required before
committing this checkpoint.
