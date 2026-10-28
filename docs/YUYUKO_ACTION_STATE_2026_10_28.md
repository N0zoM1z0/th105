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
59456 full bytes versus59672; first mismatch is+8 (frame immediate4F0 versus
native4E8). Canonical candidate SHA256:
fae3443cfa58a7c2a829bfbab59e723ecfa12172e8a23914e37a7b610749988f.
The full audit reports56560 unequal/missing positional bytes. This is a strict
mismatch diagnostic, not a semantic similarity score or accepted byte count.

Reproduce serially:

```
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-yuyuko-action-state --compare --json
scripts/repo-python scripts/audit-yuyuko-action-state.py
scripts/repo-python scripts/compare-giant-action-switches.py yuyuko-vslot28 build/match-units/ExactFirst_YuyukoActionState.obj --json
```

Expected comparison exit status is nonzero until exact. Receipts live under
build/frontier-55d850-20261027/: formal-ownerorder.json, formal-ownerorder-audit.json,
ownerorder-map.json and ownerorder-action-{calls,fp-ops}.json. Source and
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

## Physical-owner refinement

The low-case source now follows the observed physical owner order: the truly
shared209/212/221 and210/222 groups occur after220;224/226 are no longer placed
next to201/202 simply because their high-level logic is similar. Flight214 is
between211 and215. This reduces the214 span discrepancy from340 to37 bytes;
the comparison remains nonexact. Mirrored spell arguments retain the captured
double X but evaluate the outgoing Y/X expressions at the spawn call, consistent
with native packet/argument setup. An explicit idle0/2 shared-label trial did
not recover native physical placement and was not retained.

Raw payload dataflow resolves all100 native and candidate homes. Their size
pattern agrees (including four-float packets); every candidate home is8 bytes
higher. Frames are1256/1264 bytes. Native/candidate epilogues124/126 and virtual
sites180/178 differ. All49 crossed and8 on-surface consumers test AL in both.
These are whole-root diagnostics, not independent semantic acceptance.

The suspected airborne812 unordered-predicate discrepancy was checked against
565851..565862 and5659C3..5659D4: both predicates reject unordered values,
consistent with ordered less-than. No speculative NaN rewrite was made.
Remaining710 virtual-site discrepancy is physical timeout-tail sharing, not an
observed extra dynamic call; native difficulties0/1 share the56AC01 tail.


## Captured coordinate and aim-argument refinement

Action726 captures the pre-RNG X field in a double local. Native56B648 loads
the binary32 field and56B653 directly stores QWORD across RNG, then56B67B
uses that QWORD in the subtraction. The former float local generated an
extra DWORD store/reload before its QWORD capture. The isolated capturex
trial removes that unsupported round trip, emitting59420 bytes; the frame
remains4F0. This does not narrow any arithmetic or assume RNG is pure.

The seven aim_fan sites and action561 atan call now retain rounded DX while
computing DY in the first argument. Native561858,561919,561CBD,561D7E,
562553,562ADF,562BBB and5672D9 place DX in outgoing[esp+4] before loading
peer Y. No intervening helper or object write exists in these calculations.
All seven aim_fan call-preparation windows (32 bytes before call) match native
verbatim after this change. The eighth has the recovered instruction order
but still differs in scratch offsets. These bounded windows are diagnostics,
not whole-function acceptance or additional exact-byte credit.

The combined public replay is59456/full59672, first+8, frame4F0 versus4E8,
SHA256fae3443cfa58a7c2a829bfbab59e723ecfa12172e8a23914e37a7b610749988f.
Receipts: build/frontier-55d850-20261027/formal-lifetimes.json and
formal-lifetimes-audit.json. allaimargs-action-{calls,fp-ops}.json retain the
710 virtual-site and600/603 FCHS differences noted above. Payload dataflow
still resolves100 homes, all+8, with no unknown payload pointers. One skipped
six-byte LEA EBX,[EBX] at candidate56A7EA is compiler alignment, not executable
source or a masked acceptance range. All bytes remain in the canonical audit.
The extra scalar group and ring-operation scheduling remain unresolved.
