# EffectObject update, 0x00659AA0: complete nonexact source

The entire8895-byte EffectObject update now has a reproducible source hypothesis
and focused unit. **It is not exact.** The selected candidate contains8899
callable bytes and9350 complete emitted bytes, versus native8895/9448. Canonical
comparison first differs at+8. No matches row or exact-byte credit is added.

Source: `src/battle/EffectObjectUpdate.cpp`.
Unit: `exact-first-effect-object-update`.
Only this new translation unit is compiled; the independently accepted entry
65BF90 remains unchanged. No shared header or compiler profile changes.

## Observed target and boundary

Canonical original Japanese1.06a SHA256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.
Primary EffectObject vtable6C14BC slot28 cell6C14E4 points here; COL6D7E98 names
`.?AVEffectObject@@`. A target-pinned origin rule independently verifies the
whole body hash, RTTI chain and four direct calls; source presence alone is
not used as authorship evidence. The source has a pointer-only receiver, never instantiated,
embedded or allocated as a complete owner.

Raw traversal decodes2170 instructions in the8895-byte main span, reaches2122,
and records48 unreachable alignment instructions. Those bytes remain compared;
none is silently dropped. All79 explicitly handled IDs are independently checked
against the300-byte index map. One63-entry destination table closes the switch.
Ten RET0s and one restored-frame tail65BD5A->4351C0 terminate the body. There are
no remote source chunks or unresolved indirect branches.

Callable end is exclusive65BD5F; one NOP precedes table65BD60 (252 bytes), then
index map65BE5C (300 bytes). Full payload ends65BF88, followed by eight INT3
bytes before the separately accepted initializer65BF90.
Callable SHA256:
2958ec9355ae1eaa8fae2562395c02b6dc7b3c1cbb233382e60b76b3f1122bd5.
Full SHA256:
8378f98ce4f95c89f459f3003491051f2653393446b75196d7695b361941bd6f.

All114 physical CALLs and the one tail are retained in the selected candidate:
MT19, selector RNG9, effect emission66, indexed events13, motion setup3,
animation advance2 plus its tail, sine1 and FTOL1. A matching census is only
supporting evidence; it is not a substitute for exact bytes.

The direct IDA launcher remains unavailable because mcp/uv is missing. Factory
metadata, entry68B9D2, exact mapped entry bytes e8ca9f0000e916feffff and inventory
401000/52 were checked before use. The complete decompiler artifact is retained
as a hypothesis, with raw CFG/operands authoritative. Supported name/prototype
metadata was updated/read back; no target byte writes occurred.

## Source behavior and repaired evidence

- Preserve independent first-frame families1..16/38, exact burst counts and
  paired102/103 emissions, plus the distinct7/8 shared-scale update.
- Preserve52..71 initial events, independent bursts and differing alpha/color
  thresholds; zero/low-alpha paths sometimes kill immediately and sometimes
  still advance animation. They are not collapsed into one generic lifecycle.
- Preserve100..155 motion, context-relative positions, sequence/health gates,
  shared versus independent scales, mixed byte-channel fading and native NaN
  comparison directions. Context+4A2 is a signed health-like word, not a named
  complete Fighter layout claim.
- Preserve160..165 signed time remainder, typed decay conversion and original
  bounce gates. Raw FCOMP/TEST41 confirms ordered sum<=0 and velocity<0, not the
  decompiler's unordered-negated shortcut. The decay is converted to int, then
  its low byte is sign-extended for comparison with unsigned alpha.
- Preserve200/201's independent random motion/spawn choices and signed WORD
  global publication: event16 adds40/5 with a999 cap; other events subtract40/5
  with a1 floor. Deletion dispatches26. No new saturation behavior is invented.
- Preserve202's color/motion order and300's unchecked animation-advance tail.
  Unhandled IDs return without advancing.

The full comparison exposes a real receiver error in the first source:
435160 motion setup receives **this+4**, not this. Itsthree raw LEA sites are
preserved through a declaration-only subobject view. This is a semantics repair,
not a register-forcing trick. Spawn and event receivers remain the full object.
Native repeated post-call reads and unsigned facing passed to emissions are kept.

## Finite complete-body trials

| Trial | Full candidate / finding |
| --- | --- |
|first|9654 bytes; all114 calls and79 handled IDs present. Countdown loops had an extra signed-positive TEST/JG and motion receiver was wrong. |
|countdown|9618; actual nonzero countdown condition reproduces native SUB/JNE loops. |
|motion subobject|9622; correct this+4 in allthree motion sites. Retained regardless of size. |
|selected live alpha|9350; direct live alpha field use in54/64..68 restores the native common post-burst scale/fade block instead of six duplicated local-snapshot tails. |
|normal completion|Changing300's return to normal break is byte-neutral. |
|upper-case owner|Moving the genuine300 arm to the start of the switch is byte-neutral. Stop that dispatch-spelling lane. |

Selected full canonical SHA256:
4fc56ccdb479afb9158a6dab1c58b22ac8471aa32080a87fe43addf21b52f254.
Remaining material differences include native one-table1..300 dispatch versus
source's separated300 and1..202 table, signed remainder lowering, source-owned
shared-return/layout choices and x87/register scheduling. The source main body
is four bytes longer while metadata is102 bytes shorter. Neither similar length
nor instruction/call counts gives exact credit. Original TU/lifetimes remain
unknown; this is not proof that LTCG is required.

Do not add fake cases, padding, volatile/register liveness, copied instructions
or artificial gotos. Reopen finite neutral controls only with new independent
context. The semantic source is retained, not tuned to a masked score.

## Reproduce and checkpoint

```
scripts/repo-python scripts/build.py --unit exact-first-effect-object-update --compare --json
scripts/repo-python scripts/audit-effect-object-update.py
```

Both comparisons currently return1 for a genuine mismatch; blocked/error results
are distinct and must not be relabeled as expected mismatches. The full audit
uses the canonical comparator on every emitted byte and relocation. Two added
literal bindings (double1.25 and the promoted0.94f value) are pinned by native
absolute FPU operands and exact COFF data, with no existing mapping changes.

`build/frontier-659aa0-20261027/` keeps complete target disassembly, CFG/index-map
facts, first/control objects, formal callable/full receipts and final local-CI
logs. Private source snapshots and the semantic artifact remain under the matching
analysis directory. Final CI is pending at writing; terminal log/exit is the
commit gate. Existing620 workflow tests are reused, not expanded into a runtime
matrix. No game/RNG/callback execution is claimed. Existing exact totals remain
unchanged and incrementally validated.
