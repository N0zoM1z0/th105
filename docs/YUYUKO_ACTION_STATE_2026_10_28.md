# Yuyuko action-state root 55D850

## Evidence and status

Complete 116-action C++ candidate, unselected and nonexact. No implementation
or exact credit is added. The target is original Japanese TH105 1.06a with
SHA256 56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.
Factory IDA metadata was successfully checked October28; the direct repository
IDA launcher still lacks mcp1.26.0. This checkpoint's new refinements use the
hash-attested raw PE, not an assumed fully attested current IDA session.

Native callable55D850..56BD4B contains58619 bytes,14783 decoded/reachable
instructions,124 RETs and885 direct calls to27 targets. Raw control-flow
traversal closes all three action tables and both nested difficulty tables,
with no unreached instruction ranges or unresolved indirect exits. Full
payload through56C168 is59672 bytes, SHA256
f8a241c5d1d735d0c660f406b87a4cb00545d31a0ca66b67b129f3afefe5afd9.
The one byte before the first table is outside the callable boundary.

The low/mid/high tables have31/28/51 physical groups. Nested tables56C148 and
56C158 belong to actions710 and720. Their observed destinations, not a
compiler's inferred function extent, close the boundary. Declaration-only
helpers and a pointer-only receiver extension do not recover a complete
nominal Fighter layout or confer callee ownership.

## Focused result

Public source: src/characters/YuyukoActionState.cpp and .hpp.
Unit: exact-first-yuyuko-action-state. Both private and public builds emit
59264 full bytes versus59672; first mismatch is+8 (frame immediate4F0 versus
native4E8). Canonical candidate SHA256:
4ab59bce8db52388f2eae3f2eedb7b53fb28d08f85bd23f0d99e5b812835695f.
The full audit reports56597 unequal/missing positional bytes. This is a strict
mismatch diagnostic, not a semantic similarity score or accepted byte count.

Reproduce serially:

```
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-yuyuko-action-state --compare --json
scripts/repo-python scripts/audit-yuyuko-action-state.py
scripts/repo-python scripts/compare-giant-action-switches.py yuyuko-vslot28 build/match-units/ExactFirst_YuyukoActionState.obj --json
```

Expected comparison exit status is nonzero until exact. Receipts live under
build/frontier-55d850-20261027/: formal-first.json, formal-audit.json,
shotbranches-map.json and shotbranches-action-{calls,fp-ops}.json. Source and
focused intermediate trials remain in .analysis/frontier-55d850-20261027/.
No whole-corpus cold build is needed: new source/header, append-only unit and
literal bindings have no existing accepted consumers. Existing receipts remain
unchanged; the final local CI remains mandatory before commit.

## Target-backed corrections and remaining questions

- Action562 effect offset is integer23 times signed facing, followed by FP
  subtraction (567581/56759B onward), not a double23 multiply. The initially
  emitted double23 had no native literal witness and was removed, not bound.
- Actions10 and200 have separate native virtual-call exits. Explicit branches
  reproduce their call counts instead of folding action IDs into a ternary.
- Zero horizontal flash offsets use direct X, without an artificial FP+0.
- Spell-ring angle n*30 is retained as double for the later +15; mirrored X is
  captured in a double home before sine/cosine calls (56875B/5688AB). These
  lifetimes are observable raw storage facts, not padding to alter the frame.
- Action720's complete per-difficulty emission pair preserves four first-call
  sites and one shared second-call tail. Moving a boolean result outside the
  switch merged all first calls; a goto-only rewrite was byte-neutral. Keeping
  the real pair together restores five reachable spawn sites and FP-op counts.
- Action562 keeps independent live packets and per-branch base/coordinate
  evaluation before the shared spawn tail. The resulting call and FP-operation
  counts now agree. Counts alone do not prove instruction equality.
- Current per-action call-count diagnostic differs only for710: native4 versus
  candidate5 virtual sites. FP-operation counts differ for600/603: native8
  versus candidate7 FCHS sites. Their evaluation/alias lifetimes need further
  raw review. These diagnostics traverse reachable physical sites, not dynamic
  execution counts; they are not acceptance criteria.
- Preserve native725 fallthrough to726 except its entry4 return. Preserve the
  unusual ring820/900 sine(n-6) geometry and731's two cosine coordinates.
- General unordered FP predicates, external-callback alias effects, payload
  homes and physical tail sharing remain review topics. Source coverage and
  compilation do not establish complete semantics or exactness.

Eleven new float/double literals were bound by emitted bytes and unique native
operand addresses. No target patches, assembly, fake dependencies or forced
registers were used. Existing tracking totals remain1427 exact functions and
413799 authored bytes, incrementally validated rather than freshly rebuilt.
