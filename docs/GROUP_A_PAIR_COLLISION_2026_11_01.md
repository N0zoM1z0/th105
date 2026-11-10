# Group-A/B collision traversal: restored descriptor read lifetime

46BB10 is now complete authored/source-present, not exact. This is a real
read-lifetime correction to the older unselected GeometryGroups.cpp hypothesis,
not another register-allocation spelling experiment.

## Complete target and independent ownership

The complete [46BB10,46BC9E) body has398 bytes, all112 instructions reachable,
and a RET8 at46BC9B. Native SHA256:
d588b612c1745b00bfaed71261f0175426f2219bb9dd26558a796ad94da9fefc.
Fresh exact attack-candidate resolver46DA10/285 calls it at46DAD7.
Fresh exact geometry preparation45C500/2156 independently establishes:
signed counts1AF/1B0, five group-B boxes1B4, five group-A boxes204,
five descriptor storage records254/2A4, primary box2F4, and five pointer
entries304/318. The new pointer-only view asserts its consumed offsets;
it is not allocated or presented as the complete game class.

The routine traverses signed-byte nested indices without count clamps or
early-success exits. It ORs every pair result. Two descriptors call46BA10,
one descriptor calls46B7B0 with the shaped box first, and two plain boxes
AND four separation differences, test bit31 and accumulate extents46B3B0.

## Actual correction and bounded comparison

The initial first-descriptor test at46BB43 determines the outer branch.
Inside that branch, native46BB83 and46BB9E load the first descriptor anew at
each helper call. The old source retained first_descriptor across the complete
inner loop. The new source keeps the outer test but rereads the actual slot
for each argument, computes box pointers within their real branch, and uses
the independently established typed arrays and bit31 condition.

The retained original compiles to321 bytes, SHA256
cc19df5aa0e32a54c36ba6a178574c2201c033d9c1ba763e72fc196119298fb5.
The corrected complete source is398 bytes, SHA256
b4972b1602894e8a3054c1edd07c33217ea6b4bee59483277785d26872b2e75b.
It still differs at44 byte positions, first+20/46BB24. Source delays saving
and obtaining the second receiver until the outer count passes; native saves
it before that guard. Broad-phase operand scheduling and corresponding
restore order also differ. These are the same bounded residual classes as
the separately reviewed group-B traversal. No new control grid is opened.

## Explicitly limited observer

Five bounded executions run the complete native, old-source and restored-source
traversals with helper calls deliberately substituted. The observer records
arguments and optionally changes the first descriptor slot after call one.
For one first box and two second boxes, native and restored source pass
descriptor A then B; old source passes A twice. With no mutation they agree.
Zero/negative first count and zero second count all produce no calls/result0.

This proves the traversal's read lifetime under a declared helper-boundary
substitution. It does not execute the real geometry helpers or claim those
helpers actually mutate descriptor slots in gameplay. It is not exactness
evidence and does not replace full byte comparison.

## Integration and validation

Selected source:src/battle/GroupAPairCollision.cpp.
The old A/B method in GeometryGroups.cpp remains unselected; primary197 and
the separate group-B candidate are unchanged. No shared header, ABI, compiler
flags or provider definition changes.

taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-group-a-pair-collision --compare --json
    taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit cross-v106a-candidate-fighter-resolver --compare --json
    taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit gpt-web-collision-geometry-preparation --compare --json

Scoped origin validation uses the complete native hash and fresh exact owner.

Source1787/authored1807/mapped1814/excluded1801/review419/units766.
Exact1585/449721 authored bytes stays unchanged. No prefix or equal-length credit.
