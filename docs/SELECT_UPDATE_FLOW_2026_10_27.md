# CSelect selection flow, 0x004208E0

The complete341-byte flow is canonical exact under unchanged VC8 SP1 O2/GS.
New source/unit: `src/ui/SelectUpdateFlow.cpp` / `exact-first-select-update-flow`.
Only this new unit is built. Shared layouts, literals and compiler flags are
unchanged; the already accepted stage-selection unit retains its prior receipt.

## Observed target and boundary

Canonical Japanese1.06a SHA256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.
All108 instructions are reachable. One RET0 at420A1A and restored-frame tail
jumps420A23->420560,420A30->41FC90 close the CFG. Eleven following INT3 bytes
isolate the next function. Neither tail target is absorbed into this boundary.
Whole-body SHA256:
e47e28285d58e29e1aa034a4a792996ef84f5a05a4a402665fa2fc8632eb3a88.

Positive authored ownership is CSelect-family virtual slot+18: CSelect at
6C0BDC/COL6D78D0, CSelectSV at6C04C4/COL6D6FD8, CSelectCL at6C051C/COL6D7178.
The two indirect calls42090F/420928 use callback slot+14 and the second callback
is skipped if null or identical to the first. Callback nominal identity remains
unknown; the source pointer-only interface declares only the observed order.

Raw PE is the byte/CFG authority. The direct IDA launcher remains unavailable
because of missing mcp/uv. Factory metadata, entry68B9D2, exact mapped entry
bytes e8ca9f0000e916feffff and inventory401000/52 were independently attested;
name/prototype metadata was updated/read back without patching target bytes.

## Source and first whole comparison

The partial owner is never instantiated, allocated or copied. It uses established
CSpriteEx/GuideOverlay members, exact offsets and ordinary virtual dispatch.

- Update both guides and distinct non-null callback objects.
- State0 shows the first guide and decreases the nonzero mix by15; other states
  show the second and increase mix while below255. Mix is an unsigned byte,
  not the retained constructor hypothesis's boolean label. Do not add saturation.
- Decrement a live transition timer and retain the original cosine/double-half
  interpolation into the float field.
- Advance the signed scroll counter modulo1024, update two opposite UV offsets,
  and tail-dispatch state0/1 to independently bounded character/stage routines.
  Any other state returns3.

The first source negated a double before multiplying by0.5, letting VC8 fold a
negative-half literal absent from this target's callsite. That mapping was not
forced. Integer-first negation emits349 bytes/86 differing positions. The native
FILD/FCHS/FMUL sequence instead requires conversion to float before negation;
that natural source emits the observed341 bytes. The other one-byte condition
residual is unsigned `>0` after TEST producing JBE rather than the target JE;
using the observed nonzero predicate resolves it without arithmetic tricks.
No special compiler flags, assembly, padding or fake returns are used.

## Independent nonexact character child

The complete41FC90 candidate remains unselected: first628 bytes/246 differences;
shared return3 and native random-first branch give619 bytes/25 differences.
The residual is cursor induction base+114 versus target+100 and corresponding
instruction displacements. A real local cursor-pair lifetime worsens634/524;
combined promoted-int polling gives601/554; byte narrowing and physical paired
members return unchanged619/25. The representation lane stops here, not an
unbounded spelling grid. Revisit with independent owner/TU/loop-lifetime evidence.

Its full source/controls are retained privately at
`.analysis/frontier-41fc90-20261027/`, with objects/previews under the matching
build directory. No source selection, match entry or extra exact credit is
inherited from this exact caller. Refresh helper41FB80 remains independently
unreviewed for source selection.

## Reproduce

```
scripts/repo-python scripts/build.py --unit exact-first-select-update-flow --compare --json
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/check-match-literals.py --require-target
scripts/repo-python scripts/ci.py
```

`build/frontier-4208e0-20261027/` retains first and narrowing trials, target raw
assembly/CFG facts, formal-first receipt and final focused/CI logs. Final CI is
pending at writing; terminal log/exit is the gate receipt. No new runtime test
matrix or actual UI/callback/gameplay execution is performed. Totals are
incremental, not a freshly rebuilt whole corpus.
