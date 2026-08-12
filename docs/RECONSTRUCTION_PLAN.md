# Whole-program reconstruction plan

This is the durable direction for coordinators and reconstruction agents.  It
connects whole-executable classification, subsystem breadth, giant-function
slicing, and exact matching.  `RECONSTRUCTION_MAP.md` remains the gameplay
unlock tree; `EXECUTABLE_INVENTORY.md` remains the whole-program census.

## Objective and completion model

The objective is faithful source for the authored Japanese TH10.5 v1.06a
program plus reproducible integration of its compiler/runtime and third-party
dependencies.  Completion is not one percentage.  Track these independently:

1. origin classification coverage;
2. subsystem classification coverage;
3. semantic coverage (`identified` and `decompiled`);
4. source coverage (`implemented` or later);
5. exact function and byte coverage;
6. giant-root structural coverage;
7. partial-link, runtime, and full-executable validation.

Compiler/runtime/library code must be present at link time eventually, but it
does not require manual gameplay-source reconstruction and is excluded from
authored progress after provenance is proven.

## Program sequence

### Phase 1: ledger schema gate — active

Deliverables:

- one origin census row per ledger address;
- fail-closed rules with expected count and bytes;
- validators that reject missing, duplicate, reordered, overlapping, or stale
  rows;
- raw, confirmed-authored, excluded, and review progress populations.

Current state: implemented.  The first audited pass moved `library` from 49
to 1,861 without changing function boundaries.  The remaining 2,327 review
rows are explicit rather than silently treated as authored.

Exit gate: every origin/status mutation is reproducible from an evidence rule,
and all normal validation commands pass.

### Phase 2: structured strict comparator — established, continue expanding

Use canonical match units and `compare-function.py --json`.  Every exact
packet records target/object size, first mismatch, relocation resolution,
shaping class, and a reproducible command.  Library provenance does not grant
`matching`; library rows use provenance evidence, while authored exact rows
require 100% accepted comparison.

Exit gate: each active source family has a smallest affected-object command,
and ambiguous symbol/relocation aliases fail closed.

### Phase 3: match-unit object graph — established for core, expand by system

Connect source units, ABI/type contracts, dependencies, relocation anchors,
and accepted function spans.  Continue the existing gameplay manifests for
battle/spell/character work, and add system manifests for scene, render,
assets, UI, input/replay, network, audio, script, and platform.

Exit gate: a worker can select a bounded root and see its direct dependencies,
types, source unit, comparison path, and unresolved blocker without reading
the entire repository.

### Phase 4: lazy IDA-first work packets — operational

Run `check-ida-mcp.py` at each bounded unit.  Use IDA for semantics only when
the target hash/capabilities pass, reconcile every boundary with the ledger,
and use Ghidra headless fallback otherwise.  Parallel workers are read-only;
the coordinator owns IDA/Ghidra writes, ledgers, claims, manifests, Git, and
pushes.

Exit gate: work packets are hash-attested, boundary conflicts are explicit,
and no discovery exists only in an analysis database.

### Phase 5: known-roster family manifests and fan-out — active

The roster already has clone-family, action-change, input, CPU-policy, and
lifecycle/event manifests.  Add the two giant repeated pillars:

- fifteen fighter primary-vtable `+0x28` roots;
- fifteen per-character owned-object/action behavior roots.

For each pillar:

1. recover numeric dispatch/table structure for all fifteen;
2. fingerprint common direct callees and field accesses;
3. split into normal (`300/320/400`), skill (`500`), spell (`600`), and
   special (`700+`) packets only where paired evidence supports those bands;
4. recover one shortest clean pilot completely;
5. prove shared skeletons by normalized target instructions;
6. emit truthful shared source and character traits;
7. fan out exact packets without granting status from clone similarity.

Current `+0x28` state: all fifteen vtable owners, ledger spans, action-table
blocks, and call fingerprints are recorded. All fifteen roots now have complete
case/field/return slice manifests and are structurally `decompiled`. Marisa,
Reimu, and Udonge establish
the backend-neutral `exact_target_tables` path for giant roots that defeat
Hex-Rays. Sakuya has a severe IDA chunk conflict and must always use the ledger
span. Tenshi remains a 43-callee outlier.
Reimu and Tenshi also establish that tracked non-contiguous body-byte counts
and instruction-supported contiguous spans must remain separate evidence.

Exit gate: every giant root is at least structurally decompiled into bounded
packets, with no fake body and no unresolved accepted span.

### Phase 6: one audited synthetic COFF island and objdiff — established

Use synthetic PE-derived islands only for relocation-aware diagnosis.  They
must retain `synthetic_pe_derived_not_original_coff` provenance and can never
alone grant `matching` or original TU/LTCG claims.

Exit gate: hard linked/LTCG cases have a reproducible object-graph diagnostic
and a precise stop condition instead of repeated blind source perturbation.

### Phase 7: generic clone mining, WIP scheduler, and dashboard

After the known roster families are stable:

- mine exact normalized clones across the full ledger;
- classify small compiler/STL/EH families before assigning authored work;
- rank work by unlock impact, shared-call/type fan-out, and byte mass;
- show provenance, subsystem, semantic, source, exact, and giant-root metrics;
- schedule at least one hard-path packet per parallel wave.

Exit gate: agents receive non-overlapping address packets and the dashboard
distinguishes real source progress from library classification and inventory
cleanup.

### Phase 8: partial link, runtime validation, and full executable

In order:

1. link isolated authored islands against pinned VC8/runtime dependencies;
2. validate constructors, RTTI/vtables, EH, static initialization, and global
   service order;
3. validate scenes, input/replay, network, render/assets/audio, and gameplay
   at runtime;
4. run executable-wide reccmp;
5. close layout, relocation, TU/LTCG, section-order, and resource differences.

The original executable, databases, toolchains, generated reports, and game
data remain uncommitted.

## Near-term execution waves

### Wave A — origin fast path

- complete the mixed Boost/project island audit;
- identify interspersed VC8 STL/EH/thunk clone families;
- assign subsystems to high-byte review rows first;
- update census, ledger, and progress in audited batches.

Success measure: fewer review rows without misclassifying project adapters.

### Wave B — fighter `+0x28` breadth

- retain Alice, Youmu, and Yuyuko as the Hex-Rays baseline pilots;
- retain Marisa and Udonge as exact-instruction table-decoding pilots;
- retain Patchouli as the non-contiguous-boundary regression pilot;
- reconcile Sakuya's non-contiguous chunks before any comparator work;
- fan common `0..226` and `301..418` contracts across the roster;
- keep high-action tables character-local until clone evidence proves more.

Success measure: move roots from `identified` to `decompiled` only after each
root has complete numeric cases, direct callees, field effects, ABI, and
boundary evidence.  Source follows per bounded slice.

Capture each pilot with:

```bash
python3 scripts/character-root-survey.py --kind vslot28 \
  --fighter Alice --output build/alice-vslot28-survey.json
```

Use repeated `--fighter` flags for two or three bounded roots. Do not make a
single whole-roster Hex-Rays response a routine dependency.

### Wave C — second character pillar

- identify and vtable-anchor the fifteen likely owned-object/action roots;
- build the same structural manifest;
- join their spawn/object-manager dependencies to the existing eight clone
  families;
- prioritize shared helpers that unlock several characters.

### Wave D — gameplay systems

Continue breadth-first waves for spell-card data/runtime and battle simulation:

- complete PAT record/container helpers and `0x00460B50` source;
- shape hard spell parsers and roster 600-series fan-out;
- finish collision/hit/round/sync exact frontiers;
- expand to HUD, effects, weather, stage, and outer battle states.

### Wave E — whole-program breadth

Use RTTI/vtables and one-hop call graphs to establish scene, render/assets,
UI/profile, input/replay, network, audio, script/story, and platform trees.
Prefer central constructors/managers and resource ownership boundaries over
trivial accessors.

## Parallel agent contract

The coordinator:

- verifies target/backend and creates exact claims;
- owns manifests, ledgers, shared source, analysis DB writes, Git, commits,
  and pushes;
- integrates evidence and independently verifies status transitions.

Evidence workers:

- receive non-overlapping addresses and explicit exclusions;
- use verified IDA read-only or Ghidra with `program="th105.exe"`;
- label conclusions Observed, Inferred, or Hypothesized;
- return boundaries, instructions, callers/callees, fields, confidence,
  candidate ABI/source, comparison path, and unknowns;
- never write ledgers, claims, databases, shared source, or Git.

Exact workers additionally return target/object sizes, first mismatch,
relocation status, applicable matching-pattern IDs, minimal patch, and stop
condition.

## Prioritization rule

Choose work in this order:

1. a provenance/type/helper result that removes false authored work or
   unlocks several roots;
2. a central hard function whose structure releases a subsystem;
3. one representative of a proven roster/clone family;
4. exact fan-out after breadth establishes truthful contracts;
5. isolated trivial functions only when they close an ABI, relocation, or
   caller path.

This preserves the effective breadth-first plus exact-fill workflow: map most
of a system faithfully, then let parallel exact lanes close bounded compiler
differences without rediscovering the architecture.

## Handoff checklist

```bash
python3 scripts/verify-target.py
python3 scripts/function-origins.py --check
python3 scripts/validate-tracking.py
python3 scripts/build.py --check
python3 scripts/clone-families.py --check
python3 scripts/generate-synthetic-coff.py --check
python3 scripts/core-worklist.py --check
python3 scripts/progress.py --check
git diff --check
```

Every handoff states addresses, evidence, old/new statuses, files, exact
results, remaining blocker, and claim disposition.
