# Sprite pivot rotation source audit, 2026-10-02

## Identity, ownership and boundary

**Observed:** the original Japanese TH10.5 v1.06a executable has SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The complete callable at `0x00407680..0x00407AC6` is 1,095 bytes, with body
SHA-256 `313f3bb25a5e3c835faf60c91a2196b0a2d22d3507c01bcac149fe3debb69dde`.
The previous [origin/boundary review](ORIGIN_BOUNDARY_REVIEW_2026_09_26.md)
established full reachability, two RET 0x18 paths, six trig calls and six
calls from five canonical-exact renderers. Its `authored_game/render`
classification remains unchanged.

**Observed:** direct Ghidra 12.1 headless import was independently checked
against the executable SHA-256, PE image base `0x00400000`, entry point
`0x0068B9D2`, language `x86:LE:32:default`, Windows compiler specification,
and every mapped byte of `.text`. Mapped `.text` SHA-256 is
`f5cb09ff0a54362356d8c4cce853cbcb14552499cce12cf7390d0868db9ebe97`.
The bounded Ghidra function body contains all 1,095 addresses; the body hash
agrees with raw PE extraction. Its decompiler corroborates three optional
Z/Y/X rotations of four xyz points, but its flattened arithmetic is a
hypothesis, not evaluation-order evidence. No IDA or factory adapter output
was used. Keep scripts in an isolated directory: the initial broad
`.analysis` script path recursively scanned old worktree paths and was
explicitly terminated before the successful bounded run.

**Inferred:** `CSpriteEx_rotate_xyz` is the source identity supported by the
existing exact sprite layout and callers. ECX holds the receiver; six dword
arguments are angles X/Y/Z then pivots X/Y/Z. The working quad at `+0xB0`
has four 12-byte `{float x,y,z}` records. Original class spelling and TU
ownership remain unknown. The two lookup declarations now use their existing
`th105` namespace and recovered `double(float)` contracts; local cosine/sine
values retain the target's explicit single-precision stores.

## Correction to the old semantic-closure claim

**Observed:** fresh ordinary `/O2 /GS-` compilation reproduced the retained
probe's 1,089-byte length. It did not reproduce the target sum associations.
For vertex zero, target Z-rotation stores

```cpp
y0 * cosine + (x0 * sine + pivot_y)
```

where the old source stored

```cpp
(y0 * cosine + x0 * sine) + pivot_y
```

Target x87 `faddp` destinations establish the inner pivot addition before
the outer cosine addition. The corresponding output stores are
`0x00407705` (Z plane, Y output), `0x0040786C` (Y plane, X output), and
`0x004079D3` (X plane, Y output). The same grouping correction applies to
vertex zero at all three planes. Floating-point addition is not associative;
equal real-number formulas did not establish faithful behavior.

The private bounded x87 audit followed the all-three-active path, maintaining
the FPU stack, ESP-relative slots, float stores/reloads and updated object
fields. It reconstructed 54 ordered temporary/output store expressions.
The old probe disagreed at the three first-vertex sums and the subsequent
X-plane input derived from the first incorrect Z output. After the three
parenthesis fixes, all 54 expressions agree, without algebraic normalization.
Raw branch review separately covers skipped planes, unordered zero tests,
the shared exits and RET cleanup. This is bounded semantic evidence, not a
general machine-code equivalence proof or a replacement for exact replay.

## Focused comparison and residual

**Observed:** corrected source compiles to 1,095 bytes and 350 instructions;
the target also has 350 instructions. Canonical relocation replay reports
`mismatch`, first at `+0x01`, with 67 differing byte positions. Both target
and candidate now put subsequent branch/call and output-store sites at the
same offsets. The residual consists of three zero-test regions and differing
ESP-relative temporary operands. Outside the zero-test regions the reviewed
instruction mnemonic/size sequence agrees; the differing stack slots still
prevent acceptance.

Target zero-test regions start at `+0x000`, `+0x16D`, and `+0x2D4`. Target
duplicates the angle and uses `fldz; fucompp`; the candidate loads zero first,
uses `fucom`, and discards the extra FPU value. The first target angle load
also precedes frame allocation. Source spelling, scope and variable reuse
did not reproduce this topology. The corrected candidate compared hash is
`31d7bbd773b8952185cd64def6af896d3c0ac9c73a2c0daab098959ec7e2c63c`.

Reproduce the selected source and the full rotation comparison with:

```bash
python3 scripts/verify-target.py
python3 scripts/audit-candidate-boundaries.py 0x00407680 --json
python3 scripts/build.py --unit cross-v106a-effect-sprite-transforms --compare --json
python3 scripts/compare-function.py 0x00407680 \
  build/match-units/CrossV106a_EffectSpriteTransforms.obj \
  --symbol-base '?rotate_xyz@CSpriteEx@@QAEXMMMMMM@Z' \
  --rel32-target lookup_orientation_cosine_quantized_abs=0x004063D0 \
  --rel32-target lookup_orientation_sine_quantized_abs=0x00406360 --json
```

The last command currently exits 1 for the byte mismatch, with all six REL32
fields resolved. The focused unit's ten accepted transform functions remain
exact; it intentionally does not accept the rotation. Private reports are
`build/sprite-rotate-corrected-unit.json`,
`build/sprite-rotate-corrected-compare.json`,
`build/sprite-rotate-differences.json` and
`build/sprite-rotate-ghidra-bounded.log`.

## Tested hypotheses and remaining work

**Observed:** on the old source, VC8 RTM and SP1 both emitted 1,089 bytes.
Correcting the lookup return declarations alone was byte-neutral. Explicit
double/float zero types, double casts, negated equality, boolean/int value
contexts, early X-plane return, vertex scopes and independent source extraction
did not produce the target entry. Reusing axis-local coordinate temporaries
changes some stack slots but keeps the wrong zero-test topology. Fast
floating-point mode radically reassociates the arithmetic; strict/exception
modes change register/frame ownership. None establishes the target profile.
A bounded `/O2 /GL` exported/retained-only diagnostic kept the same wrong
entry shape; its unresolved inspection DLLs were not executed or accepted.
These negative experiments do not prove that every honest owning TU fails.

**External corroboration:** TH08's current rules require natural authored
C++ emission and its old `fsincos` macro is not an accepted general x87
solution. Its exact three-axis D3DX projection uses double zero constants
where VC7 distinguishes comparison width. That is a source hypothesis to
test on VC8, not transferable TH105 compiler evidence. This TH105 callable
contains lookup calls, not an inline `fsincos` instruction.

**Unknown:** the original TU/compiler ownership explaining comparison
selection and temporary reuse remains unresolved. The source is now selected
in `implemented.csv`, with a durable mapping in `reccmp-functions.csv` and
`implemented` status in `functions.csv`. `matches.csv` and the accepted unit
membership remain unchanged. Equal function length and the diagnostic byte
agreement earn no canonical exact credit.
