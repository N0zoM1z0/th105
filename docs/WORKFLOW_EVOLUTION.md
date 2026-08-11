# Workflow evolution decision

## Decision

The reconstruction will evolve in this order:

```text
ledger schema gate
→ structured strict comparator
→ match-unit object graph
→ lazy IDA-first work packets
→ known roster clone-family manifest/fan-out
→ one audited synthetic COFF island + objdiff
→ generic clone mining / WIP scheduler / dashboard
→ partial link → runtime validation → full executable
```

This sequence was accepted on 2026-08-11 after reviewing the current TH105
repository and the TH06-style build proposal in `/tmp/vc_sth.txt`. It keeps
exact function bytes as the acceptance criterion while separating facts about
the shipped executable from useful, but weaker, source/build hypotheses.

## Why this order

The function ledger previously admitted malformed CSV rows because comma-bearing
signatures were not quoted and the validator did not check physical row width.
That makes every downstream metric suspect, so schema correctness is the first
gate. A comparator must then report exact, mismatch, blocked, and error states
as structured data; a scheduler cannot safely infer those states from prose or
exit codes alone.

Focused VC8 probes already reproduce target functions, but they are not proof
of original translation-unit boundaries. `config/match-units.toml` therefore
models an explicit probe/object/function graph and records compiler inputs and
provenance without pretending that a probe is an original object. Work packets
join this local evidence with a fresh, exact-target IDA query. They remain
advisory because neither IDA MCP nor Ghidra MCP exposes a stable database
revision identity.

The fifteen-character object lifecycle is a known family supported by exact
target bytes. It is safer and more valuable to encode and validate those three
families before attempting generic similarity mining. Clone membership does not
change function status: template identity is not a source-byte match.

Objdiff is useful before an original COFF is recovered, but the evidence class
must remain explicit. An audited PE-derived synthetic island can normalize
linked relocations back into ordinary COFF relocations and provide a visual
diagnostic. It is not original object, translation-unit, or LTCG-boundary
evidence, and it cannot grant ledger status. Object/function comparison remains
the acceptance loop until a linked reconstruction exists; executable comparison
remains final authority, especially for the PE's LTCG code.

## Invariants

- `config/functions.csv` remains the authoritative function/status ledger.
- A physical CSV row must have exactly the canonical fifteen columns.
- `matching` requires a reproducible 100% strict comparison; clone hashes,
  decompiler similarity, and IDA names are not acceptance evidence.
- An IDA or Ghidra function boundary is advisory until reconciled with target
  instructions and the ledger.
- IDA packets require exact SHA-256 metadata before and after collection.
- Every Ghidra fallback call supplies `program="th105.exe"` and runs headless.
- Match units state whether they are probes, synthetic islands, or linked
  candidates. None silently claims an original translation unit.
- The comparator independently verifies the exact target SHA-256. Unknown
  relocations fail closed, and failures have stable categories.
- The coordinator owns semantic-database writes, shared ledgers, claims, and
  Git; parallel evidence workers use non-overlapping address ranges.
- The original executable, analysis databases, generated packets, compiler,
  and reports remain uncommitted.

## Implemented foundation

- `scripts/validate-tracking.py` enforces the canonical ledger header and row
  width, booleans, evidence, and source-file invariants.
- `scripts/compare-function.py --json` emits stable exact/mismatch/blocked/error
  records with the first differing byte and relocation failure category.
- `config/match-units.toml` and `scripts/build.py` build canonical VC8 probes,
  hash their inputs, save provenance, and run strict comparisons.
- `scripts/work-packet.py ADDRESS --refresh` performs a lazy IDA-first capture,
  preserves raw backend payloads, diagnoses boundary disagreement, and embeds
  only fresh canonical comparison results. `--backend ghidra` is the explicit
  headless fallback; `--cached` is visibly advisory.
- `config/clone-families.toml` and `scripts/clone-families.py --check` attest
  the 45 known roster lifecycle members against exact target bytes and explicit
  normalization fields.
- `config/synthetic-islands.toml` and
  `scripts/generate-synthetic-coff.py` define one audited PE-derived diagnostic
  island. The generator verifies the exact target hash and ledger boundary,
  replays both REL32 equations, emits ordinary unlinked COFF operands, and
  proves that linking them reproduces the 175 target bytes.
- The pinned objdiff 3.8.0 unit `synthetic-youmu-owner-record` compares the
  synthetic island with the rebuilt `YoumuObjectRecords.obj`; its `.text` and
  `apply_owner_record` symbol report 100.0%. This closes the diagnostic objdiff
  gate without claiming recovery of an original COFF object.

The first match-unit audit covers `0x0053CA40` and `0x0053CAA0`; both rebuild
and compare exactly. They prove the focused-probe pipeline, not an extracted
original COFF boundary. Generic mining, scheduling, and dashboard work is the
next workflow gate, but it should now consume the structured comparator,
match-unit graph, lazy packets, known-family manifest, and the audited objdiff
diagnostic rather than inventing a second source of truth.

Applying these gates to the high-value shared object chain produced four new
exact implementations: `IColor::~IColor` at `0x0041EAA0`, the CEffectSprite
scalar deleting destructor at `0x0041EB30`, `AttackObject::AttackObject` at
`0x0045E3A0`, and `CharacterObject::CharacterObject` at `0x004927D0`.
`CEffectSprite::CEffectSprite` at `0x00421310` is source-complete but remains
`implemented`: the standalone VC8 object reverses the target's final derived
vptr/EH-state store order, a linked-LTCG island question rather than a semantic
gap.

The next canonical packet, Reimu pool acquire `0x00492BA0`, also validates the
workflow.  Exact decorated REL32 names are now preferred over legacy short
aliases, so distinct VC8 template specializations such as the pointer-vector
and unsigned-vector `push_back` calls remain fail-closed and unambiguous.  The
resulting probe matches all relocated target bytes through the complete fresh
allocation path.  Modeling the object tail as a second non-polymorphic base
was the decisive structural correction: VC8 then emits base construction,
tail initialization, and the derived vptr store in target order.  The only
remaining delta is a five-byte checked-list iterator spill/register schedule
in the reuse path, suitable for the linked-LTCG island rather than fake source
code.  The verified roster clone manifest then safely fans this implementation
out to all fourteen non-Sakuya object pools.

The same canonical-first rule then advanced the 237-byte roster spawn family.
The clone audit corrected an important trait assumption: only acquire-and-link
is character-specific; deque append, array allocation, and `memcpy` are shared
targets whose raw REL32 operands differ only by caller address.  Giving the
owner `+0x160` field a direct typed assignment and using the real virtual
action method moved the first mismatch from `+0x0D` to the parent block at
`+0x3E`; the target and object are both 237 bytes and the complete tail from
`+0x57` is exact.  A tempting single-expression parent append introduced
C++03 evaluation-order ambiguity and was rejected.  The safe source keeps the
same parent/deque operations with only a standalone/LTCG scheduling delta, and
the audited manifest fans it out to fourteen non-Sakuya managers.

The work-packet boundary gate also prevented a false partial comparison at
`0x004B9540`: its stored `size=112` disagreed with `span_end=0x004B95B9`.
Fresh IDA instructions prove a contiguous 122-byte body through the final
`retn`, with the next function at `0x004B95C0`. Correcting the boundary before
adding a match unit exposed the full result: the genuine checked-list release
and clear source emits 122 bytes and matches 120, differing only in the token
load/push register. A comparator run against the stale 112 bytes would have
silently omitted the node-freeing tail.

## Operational loop

```bash
python3 scripts/verify-target.py
python3 scripts/validate-tracking.py
python3 scripts/build.py --check
python3 scripts/clone-families.py --check
python3 scripts/generate-synthetic-coff.py --check
python3 scripts/core-worklist.py --ready

# Coordinator or single-agent fresh capture.
python3 scripts/work-packet.py 0x00421310 --refresh

# Rebuild and compare a canonical focused unit.
python3 scripts/build.py --unit youmu-object-records --compare --json

# Regenerate the audited diagnostic island and inspect it with pinned objdiff.
python3 scripts/generate-synthetic-coff.py --island youmu-owner-record
.tools/objdiff/objdiff-cli diff -p . -u synthetic-youmu-owner-record \
  -o build/objdiff/youmu-owner-record.json --format json-pretty

# Evidence workers consume an existing packet without touching IDA/Ghidra.
python3 scripts/work-packet.py 0x00421310 --cached
```

The current high-value path remains the shared character-owned-object chain:
`CEffectSprite` → `AttackObject` → `CharacterObject` → fifteen pool acquire
functions → acquire/link and spawn families → character dispatchers, skills,
and spell-card pilots. Work should follow this unlock graph instead of raising
the function count with unrelated trivial accessors.
