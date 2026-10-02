# Youmu facing branches and return paths, 2026-10-02

## Retained source and exact status

`Youmu_dispatch_action_state_vslot28 @ 0x00530200` remains **nonexact** over
37,692 target callable bytes. Action214 now expresses both facing decisions
with mirrored nested branches. Natural VC8 recovers all11 physical sequence
call sites in this owner, versus9 in the preceding source and11 in the target.
The five earlier zero/velocity comparisons and effect125 argument schedule
remain. One unused first-facing byte snapshot is removed byte-neutrally.

Fresh configured comparison first differs at `+0xCA / 0x005302CA`, target
`64`, candidate `3C`. Candidate metadata begins at `+0x9314`, versus target
`+0x933C`: the callable is40 bytes shorter. Its section tail is38,776 bytes.
All97 physical switch destinations/33 low entries remain distinct. Strict
instruction/edge diagnostics remain **27/98**, without gains or losses.
There is **zero new canonical exact credit**; regional shape agreement and
body-size proximity do not meet the whole-root acceptance gate.

Target callable SHA-256:
`19f2d4fba4f6ea626b69a28f4717d0fcfae06ea97e95ddb24e656e0ea518ed74`.
Retained CRLF source SHA-256:
`b6355fa965a49c4f05fe6978e3bf5ceee8e85c537c09df67254be6f5b8955296`.
Canonical compared candidate-window SHA-256:
`519ff678fcd039705f8cb667b45f9fb09380e72f8a282333153814fba32d3cc4`.
That compared window includes adjacent candidate metadata, not just its body.

## Observed target facing paths

All new target observations use the hash-attested original Japanese1.06a PE,
SHA-256 `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`,
entry point `0x0068B9D2`. IDA preflight exposes the different `10350095...`
executable and fails; that session is not used. This work uses no new Ghidra
process, database write or target patch.

**Observed:** first facing decisions apply to sequence states1/2. Facing1
reverses on ordered `peerX < selfX`; other facing values reverse on ordered
`peerX > selfX`. Reversal stores the direction byte, negates velocityX and
selects6. The default selects5. Second decisions apply to states3/4 with the
same ordered comparisons, but reversal selects5 and default selects6.
Unordered positions take the defaults and retain facing/velocity. Source
`LABEL_392` remains necessary for the state gate that skips the first region.

| Target first decision sites | Sequence / shared argument behavior |
| --- | --- |
| `531E42` | Select6 after facing1 reversal. |
| `531E4D` | Select5 on facing1 default. |
| `531E89` | One call after the other-facing6/5 argument join. |

| Target second decision sites | Sequence |
| --- | --- |
| `531EE6`, `531EF7` | Facing1 reversal5 / default6. |
| `531F35`, `531F48` | Other-facing reversal5 / default6. |

Those seven sites plus four preceding zero-guard sequence calls give11 in
action214. Replacing the former shared/default goto shape with ordinary
nested branches recovers that physical layout. Removing first-facing local
`v45` leaves the compared window unchanged: its signed byte load/negation
can use the real direction field. Second snapshot `v49` and the two real X
carriers remain; this does not prove unique original local types.

**Observed candidate diagnostic:** target `[531DFE,531F52)` and candidate
`[531D70,531EC4)` are both340 bytes/120 instructions. Normalize only internal
branch destinations to region offsets and the common external epilogue edge
to `root-return`; preserve registers, constants, operand widths and all other
instruction text.118 rows agree; two differ:

```text
target:    MOV ECX,[ESI+170]; FLD [ECX+EC]
candidate: MOV EAX,[ESI+170]; FLD [EAX+EC]
```

Absolute placement/epilogue branch displacements also differ. This diagnostic
does not establish340 exact bytes, an exact owner or full numerical/exception
equivalence. Original register lifetime and compiler/TU context remain open.

**Inferred source:** mirrored source branches explain the observed per-path
call layout while preserving all ordered and unordered outcomes. An earlier
nested-first probe lost low11 under the preceding typed-call phase. The
independently recovered zero lifetime/effect schedule changes that result;
the new complete nested shape retains all27 preceding owners. This is a
phase-scoped retry supported by new target evidence, not a general source
permutation search.

## Shared landing returns: positive edges, negative source controls

**Observed target:** action308 mode0 selects action10 then jumps to `530813`
for height/zero processing. Its positive mode1 predicate prepares sequence2
and jumps from `533619` into the shared indirect call at `5314AA`, physically
in action208. That call falls through `5314AC` to the height lookup/store,
velocity/acceleration zero helper and return.

Action414 enters with value4 and, after its positive predicate, prepares and
calls the sequence virtual at `534523..53452B`, clears byte`+47F` at `53452D`
and jumps from `534533` to `5314AC`. Action415 enters with value3; its positive
lower-sequence predicate branches from `53467A` to `534523`. Action416 enters
with value4 and branches from `534773` to that same414 selector/flag path.
The415 timer>=15 path independently updates accelerationX to0.6 and advances
the sequence block; it must remain separate.

| Serial private VC8 control | Result | Disposition |
| --- | --- | --- |
| First facing decision nested | 27/98, metadata`+9304`; owner214 slotC10/target11. | Combined with target-supported second decision. |
| Both facing decisions nested | 27/98, metadata`+9314`; owner214 slotC11/11. | Retained. |
| Remove first-facing byte snapshot | Same compared window as the preceding row. | Retained cleanup. |
| Shared208 height/zero source label used by308 | 27/98, metadata`+9304`; compiler moves height tail into308. | Not retained. |
| Shared414 selector/flag source label used by415/416 | 26/98, metadata`+92E4`; loses mid416. | Not retained. |
| Selector/flag plus shared height tail | 26/98, metadata`+9304`; loses mid416. | Not retained. |
| Both308 and414/415/416 tail joins | 26/98, metadata`+9304`; loses mid416 and moves the common selector/flag/height tail into416. | Not retained. |
| Retained facing source plus308 height join | 27/98, metadata`+9334`, only8 bytes short; wrong physical height tail remains in308. | Not retained. |
| Isolated selector declaration `int -> short` on the preceding private control | Same compared window,27/98, metadata`+9334`. | No shared ABI change. |

The eight-byte-short candidate has a separate action208 indirect call at
`531495`, then jumps from `531497` to the308 height tail at `5335E5`. Action308
has another indirect call at `5335E3`, falling into that tail. The target
instead shares the single call at `5314AA` and places the height tail in208.
Matching size/site totals cannot establish that graph. No generic function
pointer, register forcing or assembly is introduced to fake the shared call.

The accepted selector body at `45C390` consumes the argument's low word.
The isolated declaration control is byte-neutral for these observed callers;
it establishes neither a unique original `int`/`short` prototype nor the
missing shared-call lifetime. The checked-in virtual header stays unchanged.

## Whole-root checks and TH08 x87 reference

Fresh explicit-object scans cover138 target/candidate floating guards and49
physical spawn payloads. The guard scanner has no unequal owner counts or
unordered-only leads under its ordinal hypotheses; all modeled payload
definitions resolve without conflicting ESP merges. These are bounded
diagnostics, not numerical/exception closure or exact acceptance.
Arithmetic counts remain349/348 with three multiset leads in601/696/710;
load/store leads remain12. The six normalized payload-address owners still
differ. These scans do not establish stack identity or dependency order.

Virtual physical-site counts at slots8/C/14/1C are target107/31/12/2 versus
candidate106/33/13/2. Action214's slotC count lead disappears; the remaining
slotC leads are duplicated sites in308/415. Static site counts are not runtime
call counts. Raw traversal still covers9,912 instructions/all37,692 bytes,
without unresolved indirect jumps. No shared header/helper/compiler flag,
relocation map or object partition changes; no aggregate cold-replay claim.

**External source corroboration:** local TH08 source uses real FSINCOS in
`src/ZunMath.hpp:38/:57/:145` and FRNDINT in `src/AnmManager.cpp:1146`.
The [TH08 reference audit](YOUMU_FLOAT_CARRIERS_2026_10_02.md) records its pinned
checkout and limitations. Those special instructions are absent from this
Youmu callable; its trigonometric helpers are separate callees. This does
not settle assembly needs for other roots/callees. The recovered zero FPU
lifetime and facing comparisons here are generated naturally by VC8 C++.

## Reproduction and remaining unknowns

```bash
python3 scripts/build.py --unit gpt-web-youmu-vslot28-full-root --compare --json
python3 scripts/audit-giant-action-owners.py youmu-vslot28 \
  build/match-units/GptWeb_YoumuActionState.obj \
  --unit gpt-web-youmu-vslot28-full-root --json
python3 scripts/ci.py
git diff --check
```

Fresh reports use `build/youmu-facing-return-final-20261002.json` and
`build/youmu-facing-return-final-owners-20261002.json`. Explicit-object guard,
stack, call, arithmetic and load/store diagnostics use that prefix/date.
The object-hash-bound regional diagnostic is
`build/youmu-facing-return-final-region-20261002.json`; its external jump is
normalized only after both destinations decode to the common seven-instruction
return epilogue. The private generator is
`.analysis/youmu-return-paths-20261002/facing-region.py OBJECT OWNER_AUDIT OUTPUT`.
Private controls are below `.analysis/youmu-return-paths-20261002/` and
`build/youmu-return-paths-20261002/`; their formal reports are existing-object
diagnostics without configured build provenance.

Original local types, physical shared tails, register allocation, argument
schedules, numerical/exception closure and original compiler/TU context remain
unknown. Whole-root zero-difference canonical replay is required for acceptance.
