# Iku's unified upper-action source

> Current source: `src/characters/IkuActionState.cpp` with receiver
> `IkuActionStateView`. This checkpoint measured the preceding35-action file;
> its bodies are retained in the [middle/upper checkpoint](IKU_MIDDLE_SOURCE_2026_10_17.md).

`src/characters/IkuActionStateUpper.cpp` now contains35 complete staged action
bodies inside `Iku_dispatch_action_state_vslot28 @ 620920`: the entire34-ID
high compressed switch plus its direct action560. It replaces the three
separate object818/spell/late family files with one receiver view, one coherent
translation unit and a compiled status dispatcher. The original out-of-class
bodies for those26 IDs are preserved with only their receiver-class rename.

Nine new bodies are recovered in this checkpoint. Of the root's110 nondefault
IDs,75 plus its original prelude/default and full-root compiler integration
remain. These status methods are reconstruction scaffolding, not original
function boundaries or a replacement for the void target root. No source
selection, match unit, partial byte credit or exact count is added.

## Target observations

The only target is Japanese TH10.5 v1.06a SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The59038-byte root has SHA-256
`abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea`.
`scripts/audit-iku-upper-actions.py` rechecks that body, the complete high-switch
index/table mapping, and the direct560 comparison/edge at623724/62372F.

| New action | Entry | Recovered body |
| --- | --- | --- |
| 560 | 628EAD | Ground object813, symmetric aim clamp |
| 561 | 6290BA | Ground object813, negative aim interval |
| 562 | 62924D | Airborne object813, symmetric aim clamp |
| 563 | 6294CA | Airborne object813, positive aim interval |
| 570 | 62B784 | Ground object823, positive payload |
| 571 | 62B873 | Ground object823, negative payload |
| 572 | 62B930 | Airborne object823, positive payload |
| 573 | 62BAAD | Airborne object823, negative payload |
| 599 | 62BBEB | Signed emission gate, raw-MT object807/801 pair |

Direct normal-return traversal closes969 instructions/3770 unique bytes for
these nine entries. Their3633 physical bytes are all reached;70 remote
instructions contribute137 shared bytes. The union of all35 entries closes
6324 instructions/24997 unique root bytes. These are overlapping CFG unions,
not separately owned functions or additive authored progress. Calls are static
continuations in this audit; their backend behavior is not proved by traversal.

Raw instructions establish the source's finite aim intervals:560/562 use
[-10,10],561 uses[-60,-45],563 uses[45,60]. 561's lower comparison loads a
QWORD -60 constant, and563's upper comparison loads QWORD60; the stored bounds
are floats. Original atan2 receives separately rounded float coordinate
arguments and its negated float result is stored at+744 before clamping.
The source keeps those stores, widths and signed-facing coordinates.

Airborne562/563 compare signed sequence against2, subtract acceleration,
execute original crossing/zero/height helpers and select sequence2 on landing.
572/573 use signed sequence against1 and select sequence1. The original
animation completion and sequence-entry paths remain distinct, including
560/561's action0 and airborne action9. Acceleration becomes0.5 at the observed
frame gates. Frame advances are followed by fresh state reads.

Object813 uses payload17.5 and rounded X/Y coordinates before the spawn call.
Object823 uses signed payload +/-2; only airborne573 orders its wave before
the scaled-counter call. Action599 has no landing call: signed WORD+730 must
be positive and below12, and signed frame must be below7. The real unsigned
MT result feeds unsigned remainders35/5/360, with the observed WORD conversions
and separate coordinate reloads. Source retains both complete spawns and the
subsequent counter/update order; the native fixture stops at the first spawn.

One sequential direct Ghidra read-only clone re-attests imported executable
identity, entry, full mapped text, root bytes, receiver fields and prior callee/
virtual ABI metadata. All nine primary-project hashes remain unchanged and
the disposable clone is removed. Decompiler output is a hypothesis; source is
written from raw control/access/ABI evidence. No IDA analysis or target-byte
patch is used. Source contains no assembly, copied executable-byte body,
padding, fabricated return or invented original function boundary.

## Unified source and native fixture

The class inherits the unchanged verified animation prefix. Its accessors name
only observed state; the full Iku layout remains unresolved. The dispatcher
returns after the first handled family, so a callback changing the action does
not cause a second family to execute in the same invocation. The entire source
compiles with pinned VC8 `/O2 /GS- /GR /EHsc /MT`.

`scripts/iku_upper_actions.py` centralizes only local native-execution method
aliases and the existing non-executable `g_match_identifier` data key. No
canonical comparator relocation is added. The COFF loader maps the unified
TU's larger set of sections at10000000 plus a per-section stride; the former
800000 range would collide with its fixed stack/actor fixtures. This address
choice is private execution layout, not a target address or genuine link claim.

`scripts/probe-iku-upper-actions.py` invokes the actual compiled combined
dispatcher after both sides execute the original root prelude. It includes
previous family cases plus new aim/facing, signed sequence/frame/gate, landing,
frame/timer, flag, resource, seed and PC53/64 cases. Actual original seed/RNG,
lookup initialization, finite math/runtime, texture/deque, frame/landing,
zero-handle audio/event and shared-state helpers execute. No helper return or
backend result is injected.

The comparison includes the complete7B8 actor view, native helper arguments/
order and intermediate+180 publication, ST0 converter inputs, full RNG digest,
texture/global service/pair state, empty x87/CW and genuine RET stack/callee-
saved registers. The prior NaN-X case still stops at the genuine abs entry
before unsupported imported CRT/OS error processing. Object/effect/animation/
finalize calls stop at their real first backend entry.

The combined dispatcher passes0/4591 smoke cases and0/29955 expanded cases.
The latter execute21719 genuine RETs,5819 first-spawn,203 effect,621 action,
395 next-block,1196 sequence,1 finalize and1 NaN-X abs entry stop. Execution
visits4071 distinct root instructions; this does not cover every static CFG
instruction or prove paths after the stopped calls.

The unchanged-family probes also pass0/452 (object818),0/741 (spell) and0/2144
(late). Their target-output digests exactly equal the pre-consolidation smoke
receipts. Original out-of-class body text is independently checked against
Git HEAD after the receiver-class rename. Existing control-source generators
still identify their intended unique expressions.

Expanded receipt:

- source SHA-256, CRLF on disk:
  `9bf7c8754d0cf32ce95d42485979909cf8e6f125f2f38bf4a789e239c2e37b8d`;
- input SHA-256:
  `3f04e08ed7072bc75b73448d6fb9d036609e55f8044499f34fd3a9a1d3103de2`;
- target-output SHA-256:
  `faf1fd23e403965f1e51360af787d46db48e7997e12480a1a3c3d8f84055253f`;
- Unicorn1.0.2; report includes object, compiler, header, probe/fixture hashes,
  dependency aliases and original lookup-initialization/runtime receipts.

The first aim-limit control exposed a fixture gap rather than a source
mismatch: the broad aim matrix supplied timer0, so genuine4351C0 advanced it
to1 and bypassed its post-advance zero gate. The source is unchanged. New
`--new-only` gate cases supply timer/time -1 when the target must observe0,
valid airborne height/velocity states, and the finite aim geometries on both
sides of each clamp. This mode runs only the nine new actions instead of
replaying the older families. Its smoke cases are a subset of the expanded
focused matrix. This focused mode passes0/8374 cases:4624 genuine RETs,
3236 first-spawn,466 action and48 next-block entry stops;789 root instructions
are observed in this separate run. It does not re-run the prior26 families.
Its input SHA-256 is
`c32ac20b0a4936a4403a744c9ecbc83a5affccafe05088d33fd68b4e3e4cc414`;
target-output SHA-256 is
`f57fd07b02f0f4c6508c732e47ff5893878172b6da9d38f2f3d3a9c098120193`.

With the corrected preconditions, the deliberately wrong563 upper aim bound
differs14/650 focused smoke cases, and the deliberately unsigned599 positive
gate differs64/650. Both controls preserve identical target inputs/outputs.
No C++ implementation changes were needed after the fixture gap was found.

## Reproduction and remaining work

```bash
python3 scripts/audit-iku-upper-actions.py > build/iku-upper-action-facts.json
python3 scripts/probe-iku-upper-actions.py --smoke > build/iku-upper-source-smoke.json
python3 scripts/probe-iku-upper-actions.py > build/iku-upper-source-native.json
python3 scripts/probe-iku-upper-actions.py --new-only > build/iku-upper-gates-native.json
python3 scripts/probe-iku-upper-actions.py --new-only --smoke --control aim-limit > build/iku-upper-aim-control.json
python3 scripts/probe-iku-upper-actions.py --new-only --smoke --control unsigned-gate > build/iku-upper-gate-control.json
python3 scripts/probe-iku-object818-actions.py --smoke > build/iku-upper-regression-object818.json
python3 scripts/probe-iku-spell-actions.py --smoke > build/iku-upper-regression-spell.json
python3 scripts/probe-iku-late-actions.py --smoke > build/iku-upper-regression-late.json
python3 scripts/ci.py
git diff --check
```

Control commands intentionally exit nonzero when they detect differences.
Reports and objects stay below `build/`; private analysis stays below
`.analysis/`. Earlier family evidence remains in the
[object818](IKU_OBJECT818_SOURCE_2026_10_17.md),
[spell](IKU_SPELL_SOURCE_2026_10_17.md) and
[late](IKU_LATE_SOURCE_2026_10_17.md) checkpoints, whose source hashes describe
the pre-consolidation files.

Only affected staged source and diagnostics are rebuilt. No accepted unit
selects these files; shared accepted headers, flags, profiles, relocation
ledgers and object partitions are unchanged. The514 accepted units are not
routinely replayed and no cold aggregate is claimed. Continue recovering the
remaining42 middle IDs300--547, followed by33 opening IDs, in the same root.
Post-backend execution,
later ring members, exception behavior, full receiver layout, original TU/LTCG
ownership, full-root compilation and canonical byte equality remain unknown.
