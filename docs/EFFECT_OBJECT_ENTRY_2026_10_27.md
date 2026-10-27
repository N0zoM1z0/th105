# EffectObject action entry, 0x0065BF90

Complete source accepts **2676/2676 callable bytes** and **2980/2980 full
payload bytes**, including all304 switch-metadata bytes. No metadata is credited
as authored code. New source/unit: `src/battle/EffectObjectActionEntry.cpp` /
`exact-first-effect-object-entry`. Compiler remains pinned VC8 SP1 O2/GS-.

## Observed target, ABI and ownership

Original Japanese1.06a SHA256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.
All678 instructions are reachable, with32 RET0 exits,53 direct calls and no
remote chunks. Two indirect jumps are fully closed through29 low-range and9
high-range destinations. Callable end is exclusive65CA04. Metadata comprises
116-byte destination table65CA04,152-byte index map65CA78 and36-byte destination
table65CB10, ending exclusively65CB34. Twelve INT3 bytes separate65CB40.

Callable SHA256:
52d2ea2a2b0a7f3a741b6d8417a65a31d1695f11b544274ad36979ee029c3681.
Full payload SHA256:
d91263ec1492cec60f4a530583bb936f3f3f9fac639a88035c9dc1f0574d9304.
All176 COFF relocations replay:53 REL32 and123 DIR32, including switch metadata.
`scripts/audit-effect-object-entry.py` uses the existing strict comparator for
the full section tail; it is not a masked or structural score.

The primary vtable6C14BC slot3C cell6C14F8 points here. COL6D7E98 names
`.?AVEffectObject@@`. The already accepted EffectObject manager spawn437C00
calls this slot at437C6A with ECX=object, then replaces EAX with that object at
437C6D. Thus incidental EAX from this entry is ignored; a void implementation
matches naturally without fabricating the decompiler's mixed integer return.
The owner view is pointer-only and is never instantiated, embedded or allocated.

Factory-native IDA metadata, entry68B9D2, mapped bytes e8ca9f0000e916feffff and
inventory401000/52 were independently checked before this scope. Direct launcher
still lacks its mcp/uv runtime. Name/prototype metadata was updated/read back;
no target bytes were patched. Raw PE is the source for boundaries and constants.

## Complete source behavior

Numeric actions remain explicit, rather than inventing gameplay names.
The low switch covers51..202; the high switch301..309 and separate300 root
retain their original physical ownership. Unhandled IDs do nothing.

- Independent MT calls remain for actions53/54/64..69; repeated source arms
  are not combined into one random-producing case. Action101 shares one scale
  value then draws two velocities. Actions102/103 retain separate scale/angle/
  speed draws, cosine then sine, and negative angle publication.
- Action125 reads the context action/sequence and retains both independent214
  checks plus the native angle or angle+180 branches.
- Actions150/152/154 clear only float170;151/153/155 also clear byte113. The
  float publication comes first in source, preserving the target's separate
  zero-load/store path rather than letting VC8 collapse the two case families.
- Action160 retains seven explicit child-effect calls162,162,163,163,164,164,165
  with repeated self position/facing reads, then event58. No loop substitution.
- Actions162..164 retain all six ordered random draws and source scale sharing.
  Actions200/201/202 retain independent angle draws. Actions302/303 use distinct
 60/-60 and50/-50 cosine/sine velocities;304 uses its own RNG15+30 angle.
- Separate action300 and grouped301/306..309 share their native final angle10/
  byte113-clear machine tail, without grouping the source selector for300.

Unsigned RNG results are converted to float before arithmetic, as established
by native FILD plus single-precision2^32 correction. Literal0.01f/0.1f/0.7f
retain their promoted float bit patterns, not mathematically rounded decimal
substitutes. The new double-50.0 literal mapping at6C4D70 is independently pinned
by the FMUL operand65C9A4 and emitted COFF data. No existing mapping changes.

## Whole-source trials

First complete source emits2968 bytes. Correcting random-conversion width
changes the actual FADD operand width without changing size. Separating the
source action300 from the other angle10 cases recovers the native selector
split. Complete instruction comparison then isolates a13-byte body shortfall
at the zero-state families (payload alignment accounts for the12-byte total
shortfall). Putting the real float170 assignment before byte113 in151/153/155
preserves the target's two independent blocks and gives exact full2980 bytes.
No inert locals, padding, fake return, register forcing or assembly is used.

## Reproduce and scope

```
scripts/repo-python scripts/build.py --unit exact-first-effect-object-entry --compare --json
scripts/repo-python scripts/audit-effect-object-entry.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/check-match-literals.py --require-target
scripts/repo-python scripts/ci.py
```

Receipts: `build/frontier-65bf90-20261027/` has full target CFG/tables, first
and width/selector/publication controls, formal-first/full-first and final
focused/full/CI logs. Source controls remain under the corresponding private
analysis directory. Final CI is pending at writing; its terminal log/exit is
the commit gate. Only the new unit is compiled; unchanged acceptance receipts
are retained and totals are incremental. Actual game execution, RNG execution
and effect rendering are not part of this static comparison; no runtime matrix
is added. Callees and adjacent65CB40 receive no inherited exact/origin credit.

## Other bounded candidates retained this pass

No additional exact credit: CSelect character41FC90 remains619/25; entry421120
improves767/615 to783/42 via real input-value capture and shared cursor input;
render41FF00 improves1513/787 to1497/163 through direct live mix access. New
ProfileKeyConfig capture44B540 reaches785 bytes with780-byte exact prefix,
superseding the older389-prefix witness; its final SETNE versus target shared
false-return branch remains nonexact. Byte-result and positive outer-guard
controls do not close it. Complete sources/controls are retained privately under
`.analysis/frontier-ADDRESS-20261027/` and build counterparts, unselected.
