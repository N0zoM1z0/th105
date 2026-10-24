# Reverse-engineering workflow

The workflow copies TH08's conservative state machine while adapting its
mechanics to TH105's VC8/LTCG executable.

## Sources of truth

- `config/target.toml`: immutable target identity and PE facts.
- hash-attested target PE: byte, edge, and boundary evidence.
- verified IDA or target-attested Ghidra database: optional semantic working
  state, never committed; decompiler output remains a hypothesis.
- `config/functions.csv`: provisional function candidates and reviewed state.
- `config/function-origins.csv`: generated authored/compiler/library disposition.
- `config/function-origin-rules.toml`: fail-closed current-target origin/exclusion rules.
- `config/xiph-origin-anchors.toml`: relocation-free current 1.06a witnesses against the SHA-pinned official Xiph Win32 SDK; every anchor is revalidated for full-inventory uniqueness before exclusion.
- `config/xiph-relocated-origin-anchors.toml`: strict link-agnostic Xiph witnesses whose supported COFF relocation fields are masked only after boundary/form checks, minimum exact-byte coverage, alignment-tail checks, and full-inventory uniqueness.
- `config/reccmp-functions.csv`: durable address/name/category mappings.
- `config/implemented.csv`: mapped authored symbols whose source is present.
- `config/matches.csv`: accepted 100% exact functions only.
- `config/match-units.toml`: reproducible VC8 object/comparison graph.
- `config/known-symbols.csv`, `known-globals.csv`, and relocation ledgers:
  supported semantic and linker mappings.
- `docs/RE_HANDOFF.md`: current phase and blockers; ledgers override prose.

The analysis database is not the only durable record. Read back changes and
record accepted names, types, boundaries, and evidence in the repository.

## State layers

These transitions must remain separate:

1. **Candidate:** a disassembler or raw target edge suggests a function-like
   region; boundary is provisional.
2. **Identified/decompiled:** role, ABI, and control flow have target evidence.
3. **Mapped:** a durable name/category exists in `reccmp-functions.csv`.
4. **Source-present:** the authored name appears in `implemented.csv`.
5. **Compiles:** a configured VC8 unit builds, but may differ.
6. **Exact:** the canonical comparator reports 100%, recorded in
   `matches.csv` and as `matching` in `functions.csv`.
7. **Excluded:** compiler/runtime/third-party ownership has positive evidence.

No earlier layer implies a later one. In particular, retained old source and
IDA auto-names do not imply mappings or implementations.

## Bounded function loop

1. Read the handoff, inspect Git state, verify target, attest IDA, and run the
   status/ledger checks from `AGENTS.md`.
2. Select one bounded address or a tightly coupled group. Keep claims header-only.
   Prioritize complete large authored functions and accepted byte coverage.
3. Inspect exact disassembly plus callers, callees, xrefs, strings, globals,
   RTTI/vtables, access widths, cleanup, saved registers, and EH behavior.
4. Reconcile the full target control flow with the candidate extent. Record
   observations, inferences, and unknowns separately.
5. Apply supported names/types in an attested analysis database when available;
   read them back and update durable ledgers.
6. Recover the ABI, accessed storage widths, necessary layout constraints,
   lifetimes and complete control flow needed for truthful compiling source.
   Gameplay names and a complete nominal owner layout can remain unknown.
7. Select or adapt a natural implementation of the complete bounded body;
   compile and compare early. Add it to `implemented.csv` only when instruction
   semantics and complete behavior are supported. A partial receiver view must
   never be instantiated or embedded as a recovered complete owner.
8. Configure one reproducible unit, compile with the pinned VC8 environment,
   compare the smallest extent first, and audit floating relocations with
   `python3 scripts/check-match-literals.py --require-target`.
9. Add `matches.csv` only after strict zero-difference relocation replay against
   `resources/th105.exe`; update the candidate row at the same time.
10. Update the handoff, then run the mandatory final local `python3 scripts/ci.py`
    and `git diff --check` gate. Commit, push, or open a pull request only after
    both commands pass in the finished worktree.

GitHub Actions is a second check, not a substitute for the local gate. Any edit
after the final pass invalidates that pass and requires another local run.

## Exact-first priority from the TH075 review

The 2026-10-24 user direction renews this priority with an explicit throughput
rule: choose a complete medium/large representative, compare the first complete
body early, and make each subsequent trial answer one target-backed question.
After repeated byte-neutral controls, retain a concise receipt and switch to
another bounded candidate unless new independent evidence changes the question.
After a representative succeeds, review and accept its family peers separately.
Large execution matrices must resolve concrete ambiguities; naming, readability
cleanup and abstraction follow stable exactness. Use serial CPU0/nice10 jobs,
monitor available memory and swap, and commit/push stable locally gated work.
The first new bounded checkpoint is
[RemiliaObject 0x55BE70](REMILIA_OBJECT_ENTRY_2026_10_24.md), still nonexact.

The 2026-10-23 user instruction prioritizes full-function exactness before
high-level semantic reconstruction. Keep provisional address/offset names,
numeric states and declaration-only callees where they express established
instruction and ABI facts. Defer gameplay naming, speculative class hierarchies
and broad source cleanup. They are not prerequisites for a canonical comparison.

Read-only peer evidence is refreshed at TH075 commit
`4aeea7acc76b1a7db67722aff88ce9d8f8293f5b` in
`/home/pentester/coding/codex_ida/th075-reconstruction/th075`.
Its ledgers record 153 exact functions /515551 code bytes; 45 functions of at
least 4096 bytes account for 481646 bytes. This supersedes the earlier 140/350848
snapshot at `c7bcad7`; neither corpus is rebuilt in this session.

F060 `0x005FAE30` accepts 31352 callable bytes and the complete 31777-byte payload
with 913 individually bound relocations. `src/CharacterAuxAction.cpp` retains
numeric states, typed offset accesses, independent repeated calls, ordinary
casts and the observed unusual conditions. Its 19-line declaration-only header
leaves original identity and full layout unknown. F059 `0x005F3D60` reuses a
reviewed sequence family, independently checks every changed path and accepts
the complete 12792-byte payload/451 relocations. Its first preview exposed an
incorrect fade threshold and missing exit; the corrected complete build then
matched. These examples support early full-function comparison and checked
family reuse. Declaration-only callees receive no implementation credit.
Neither result is a masked structural score or proof of original source names.

These peer units use VC7.1 build3077 with `/Od /Ob0 /Gy /GR- /GX- /Zi`.
TH105 uses VC8 and has 42 C++ LTCG Rich records; the current Aya root uses `/O2`.
Copy the compile/compare discipline and independently verified family reuse,
not addresses, fields, ABI declarations or compiler settings. The shared product
genre alone does not establish identical internals.

A fresh TH105 control applies the pointer-only approach to Youmu 0x543670: remove
the local complete-owner storage declaration and replace 309 references to 23
used fields with typed offset accesses, keeping virtual order, operations and
all callees unchanged. Both complete 5492-byte objects normalize to the current
`d00f4fc4` payload and retain the same 21 callable differences. The control does
not justify replacing public source or solving original class identity first.
See [the bounded result](YOUMU_ENTRY_PHYSICAL_TAIL_2026_10_23.md#th075-offset-view-control).

For each trial, make one source-shape or compiler-context hypothesis, compile
the complete affected function serially, then inspect canonical mismatch,
relocations, frame/branch structure and size. Reuse a proven family body only
after checking the new target's complete extent and distinguishing branches.
Local matching windows and execution matrices diagnose specific uncertainties;
they do not replace the full comparison or require every gameplay meaning to
be settled first. Run a large matrix only when it resolves a concrete lifetime,
floating-point or side-effect question. Reject misleading improvements early;
retain a concise receipt and resume whole-function work. No assembly, copied
target arrays, ABI lies, inert locals, fake returns or padding are permitted.

## Giant-root owner diagnostics

For compiler behavior questions, consult [VC8_REFERENCE.md](VC8_REFERENCE.md)
and its SHA-pinned official Visual Studio 2005 text/Markdown library. Treat
official documentation and previous experiment notes as external corroboration,
not proof of source shape, compiler profile, or exactness; revalidate the
specific claim against the target and a fresh build.

For roots covered by `config/giant-action-switches.toml`, pair the target and
candidate span mapper with `scripts/audit-giant-action-owners.py ROOT OBJECT
--unit UNIT`. The latter preserves instruction encodings and compares internal
edges by physical owner plus intra-owner offset; it also traverses raw target
control flow to identify unledgered direct targets and visible indirect-exit
unknowns. A same-sized arm or a higher diagnostic count is never exact credit.
Run the strict full-function comparator independently. See
[GIANT_OWNER_AUDIT.md](GIANT_OWNER_AUDIT.md) for the common Fighter counterexample
and reproducible commands. Public CI dependencies are pinned in
`scripts/requirements-ci.txt`; install them before `scripts/ci.py` on a fresh
Python environment.

For roster Object giant roots, run `scripts/rank-roster-object-shared-callees.py` before decompiling another action family. It discovers direct external callees from raw canonical root bytes and only then annotates candidate/origin state, so missing IDA functions or stale classifications remain visible. Use the result as candidate/primitive evidence only; canonical exact acceptance still requires the normal match unit/comparator.

Candidate-boundary review must also cover indirect/data-driven call surfaces. Run `scripts/audit-roster-primary-vtable-coverage.py` to close the current Fighter/Object primary vtables against candidate starts, and use `scripts/rank-unledgered-rdata-text-pointers.py` to rank aligned canonical `.rdata` pointers that land outside all tracked main spans and reviewed remote chunks. Neither report assigns authored or exact credit. A raw pointer can name a compiler startup thunk, EH helper, deleting destructor, jump-table byte sequence or a real authored virtual/callback. Promote only after raw boundary isolation plus ownership/RTTI/caller evidence; then require the ordinary canonical comparator before exact acceptance. `CSceneManager::initialize @ 0x0041E070` is the current positive example: IDA had no containing function, but RTTI/vtable ownership plus a separately padded 162-byte body established the candidate and ordinary VC8 source subsequently matched 162/162.

## Shared-change replay

Headers, class layouts, inline functions, compiler flags, translation-unit
partition, global mappings, and relocation allowlists can invalidate several
accepted objects. Re-run every affected unit immediately. Before reporting
aggregate exact totals, run a cold single-job replay:

```bash
python3 scripts/function-origins.py --check
python3 scripts/verify-exact-units.py --all
```

Reusing prior build products is diagnostic only and cannot support aggregate
claims.

## Analysis lifecycle

- Audit direct branch targets that IDA represents only as remote tail chunks. If raw PE shows an independently isolated callable (for example INT3/alignment boundary plus its own return), do not inherit IDA ownership automatically. Split/add a candidate only after control-flow/xref review and an independently reproducible source/object comparison; a tail jump alone proves neither chunk nor separate-function ownership. Conversely, when IDA and target switch edges prove that a source function owns discontiguous executable chunks, record those chunks in `function-byte-ownership.toml` and hash any alignment excluded from the provisional main span. `functions.csv` span length is not authored-byte ownership.
- `.analysis/` contains private analysis state as well as regenerable exports.
  Preserve the primary databases, recipes and frozen inputs needed to reproduce
  evidence. Historical reports may be compressed after checking a lossless
  round trip; see [artifact retention and recovery](ARTIFACTS.md).
- `scripts/export-ida-inventory.py --write` deliberately replaces the entire
  candidate/origin baseline and never merges old status. Use it only for a
  target reset or an explicitly reviewed inventory refresh.
- A failed IDA preflight forbids using that IDA session. Raw PE instruction
  decoding remains available; a Ghidra database requires separate target-file,
  entry-point, and mapped-byte attestation before semantic use. Never treat
  auto-analysis boundaries, decompiler output, or an unverified project name
  as a target fact. Use at most one Ghidra process and keep private projects
  under `.analysis/`.
- Never patch the original image or commit private databases/logs.

## Target changes

A target hash change invalidates every address, boundary, name, origin rule,
match unit, exact report, and architecture note unless explicitly re-proven.
This rule is why all former 1.06 progress was reset when 1.06a was established.

### Writable callback-table boundary audit

Direct CALL/JMP closure and RTTI vtables do not cover mutable function-pointer tables. Periodically run `scripts/rank-unledgered-rdata-text-pointers.py --section .data` and inspect uncovered `.text` targets against raw padding, complete return closure, callers/consumers, and library/runtime provenance. Do not auto-promote a pointer target: compiler startup tables and runtime callbacks share the same surface. Conversely, when a writable table is copied into a known callback ABI and raw PE isolates the pointed body, treat that as first-class missed-candidate evidence even when IDA has no function object at the target.

### Qualifying raw code islands before candidate promotion

A padding-isolated, RET-terminated `.text` island is only a boundary lead. Before adding it to `functions.csv`, classify every incoming edge. EH/unwind tails that first derive a subobject from `EBP`/another live enclosing-frame register are remote cleanup chunks, even when the destination has padding on both sides. Strong independent-boundary evidence includes a normal call/thread/vtable/callback edge or an atexit wrapper that targets a complete prologue/epilogue body without inherited frame state. `0x00419000` is the positive atexit case; `0x00418A00`, `0x00426080`, and `0x004422E0` are current negative EH-funclet cases.

### Separate third-party provenance from authored call-site constants

A library fingerprint identifies the origin of the callee bytes, not the values an authored caller passed to that library. When reconstructing wrappers around third-party code, pin call-site literals from the canonical PE independently. The CBitmap PNG path is the current counterexample: the embedded implementation is classified as libpng 1.2.5, while the game caller at `0x0041A910` passes the literal `"1.5.2"` from `0x006D6E04`. Exact reconstruction follows the target-owned call-site bytes rather than normalizing them to the detected library version.

### Main body versus adjacent switch metadata

A source function may branch through compiler-emitted destination/index tables placed immediately after its RET. Do not extend the callable or authored-byte boundary solely to absorb those tables. Prove the main RET boundary independently, record adjacent metadata as structural/switch evidence, and compare callable bytes against that main boundary. `CBitmapData::load_bitmap 0x00419FF0` is the reference case: RET4 at `0x0041A8A3` ending exclusively at `0x0041A8A6`, alignment at `0x0041A8A6..A7`, destination table from `0x0041A8A8`, index table from `0x0041A8BC`.

### Preserve allocator provenance inside one object lifetime

Recover allocation and release independently; a `free` call does not prove a
`malloc` allocation. `PackageFileIndexNode` is the current counterexample:
constructor41B7F0 and the copies in41BCF0/41D320 allocate filename storage with
array `new` at665B8A, while the exact destructor41B850 releases it through CRT
`free`. Child nodes use scalar `new` and recursive `delete`. Preserve these
observed calls rather than normalizing the filename to `malloc`, `strdup` or
`delete[]`. Earlier wording inferred a CRT allocation from the destructor and
was incorrect. See [the constructor/lifetime evidence](PACKAGE_INDEX_UPDATE_2026_10_19.md).

### Same-size compiler-phase witnesses are still nonexact

A target-sized candidate is useful diagnostic evidence, never acceptance. `FileBufferView_load_plain @ 0x00419860` becomes 234/234 when the real FileReaderOwner destructor is visible, yet canonical comparison still first differs at +0x0E because the target owns a different frame lifetime. Record such witnesses as compiler/TU-phase evidence and keep the clean source nonexact; do not add dummy locals, fake cleanup CFG, custom calling conventions, or register forcing to convert a size coincidence into a byte claim.

- When a canonical candidate is exact-sized and differs only in the condition code after `test`, inspect whether the target branch is merely an equivalent flags spelling before rewriting source. For `InputPacket24_parse`, `test bl,bl; jbe` is semantically zero-only because TEST clears CF. Natural attempts to express unsigned `<=` or nested positive gates made VC8 range-fold the whole guard and worsened the function. Prefer the clean same-size source and record the backend provenance instead of adding fake data/control dependencies.
- A runtime ABI facade need not be reused for constructor recovery when target construction proves a more concrete physical member type. `ProfileEditor168_ctor` requires real polymorphic CTile members to obtain the target base-clear/vptr order, while runtime methods can continue using the lighter UiTile facade. Keep such constructor-only physical views isolated in their own TU and guard size/offsets with compile-time assertions.

- Treat negative A/B results as **phase-scoped evidence**. A truthful source change can be wrong in isolation yet become exact after another independently proved lifetime changes the allocator/scheduler phase. The reference case is `save_battle_setup_slot`: real vector-size visibility alone was 301/305, ternary max alone was 306/305, but the two target-backed changes together are 305/305 exact. Re-test only when there is new independent target evidence; do not perform combinatorial source searching.


### Source-owned globals in linked comparisons

The optional static-runtime linked contract uses real pinned VC8 DLL startup,
never synthetic constructor callers or forced private exports. An actually
included source file must provide an independent native COFF zero-storage
layout witness. Full initial storage, CRT initialization-table retention,
initializer/atexit helper bodies and private natural lifecycle identities are
attested before rebasing fields. Cleanup-only VC8 EH requires all parent,
handler, funclet, FuncInfo and unwind-map bytes, with typed operand roles and
exact HIGHLOW coverage. Unsupported metadata or edges block acceptance even
when parent instructions agree. Compiler witnesses confer no authored credit.
Quoted implementation includes are transitive provenance inputs. See
[archive lifecycle acceptance](PACKAGE_ARCHIVE_STORE_2026_10_19.md).
