# AyaObject900 scratch and shared-exit audit, 2026-10-22

## Result and unchanged source

The [selected shared-tail source](AYA_OBJECT_900_SHARED_TAIL_2026_10_22.md)
remains unchanged: full20060 bytes/canonical2d034e48, metadata19592,
configured19522-byte comparison nonexact+0x22. No exact credit is added.
All observations use original Japanese1.06a SHA256
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e;
IDA rejects its current image and is not used.

Four complete-root source controls were compiled serially:

| Control | Full bytes | Canonical SHA256 prefix | Result |
| --- | ---: | --- | --- |
| Consumed integer facing local in sequence0 |20060|2d034e48|byte-neutral|
| Consumed chained scale assignment in sequence4 |20060|2d034e48|byte-neutral|
| One real loop-counter local across mode cases |20060|2d034e48|byte-neutral|
| Separate local three-float900 payload |20060|0b74f29b|unselected|

The local payload moves its address and all twelve element-store operands by
+8 while leaving the four original scratch operands unchanged. It therefore
breaks the already target-agreeing spawn argument layout. No inactive locals,
manual stack padding, assembly or fabricated register constraints were tried.
These negative controls are specific to this complete source/compiler context;
they do not prove that another independently justified context cannot change
allocation. There is no evidence here to change floating precision.

## Two exits are the same code at different positions

Raw target branches61DD34/61DD48 reach61BCF1. The candidate's corresponding
branches reach canonical61A507 (runtime800277). Both destinations have the
same17 bytes, SHA256
`9b42e8e49a496dd805b9b7aa8d40dcbbe9b802307fd2df72cda9d75fc76c927b`:
load the receiver vtable, select slot14, call with ECX=ESI, restore the saved
registers/frame, and RET. The new audit requires the two JNE/JLE sites inside
the qualified1773-byte/412-instruction900 region and checks the complete exit.

Thus those two owner-diagnostic differences represent physical sharing, not
different indirect-slot or return behavior. This does not establish the callee's
identity/effects or normalize either branch for exact acceptance. The canonical
comparator remains strict.

## Sequence4 prefix execution

`scripts/audit-aya-object-900-scale-prefix.py` executes target and current COFF
from actual root entry, stopping at the original435160 oriented-helper entry.
It supplies no helper result or return. Both immutable code images are mapped
separately; the candidate's relocations are replayed at800000. Unexpected code
entries are rejected.

All3456 prefixes agree in complete object/parameter fixture memory, ordered
writes, the actual two outgoing argument words, receiver=actor+4, stack depth,
x87 control/status/tag. Inputs cross twelve scale bit patterns, twelve speed
bit patterns, three phases and eight masked precision/rounding control words.
Patterns include signed zero, subnormals, values around the1.0 clamp, negative
values, infinities, quiet NaN and signaling NaN.

This exercises scale publication, speed decrement/clamp, and argument formation
around the sequence4 ESP+14(target)/ESP+18(candidate) temporary difference.
It is not execution of the orientation helper, callback paths, unmasked
exceptions or a complete function equivalence proof. It augments, rather than
relabels, the previously recorded10840 full root-entry/RET cases.

```bash
python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
python3 scripts/audit-aya-object-900-scale-prefix.py
```

The first command intentionally reports nonexact. Private complete-source
controls/recipe are in `.analysis/aya-900-scratch-20261022/`; reports/objects
are in `build/aya-900-scratch-20261022/`. The selected-source result is
`selected-formal.json`, the prefix/exit receipt is `prefix.json`, and the local
payload diagnostic is `local-payload-audit.json`. The audit deliberately pins
the currently qualified900 region and fails if later placement changes; rederive
its boundaries before updating those pins.

The remaining900 instruction-level differences are four scratch displacement
bytes plus relocation/physical-sharing placement. Do not infer whole-root
completion from that local census: other action families and linked context
remain nonexact. Further allocation attempts need new target/type/lifetime
or compiler-context evidence rather than repeating these controls.
