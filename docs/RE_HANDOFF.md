# TH10.5 reconstruction handoff

Follow [AGENTS.md](../AGENTS.md). Reconstruct only the original Japanese
TH10.5 v1.06a executable with SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.

## Current work

The 2026-11-14 session (commit prefix `claude-opus-5.5-high:`) committed the
pending global-class Input refactor after replaying all 226 dependent units, and
moved VC8 compiles off the Factory runner: `scripts/compile-unit.sh` now calls the
system Wine directly with the same `.tools/wine-msvc8` prefix. A unit builds and
compares in about 2 s.

New exact functions: profile key capture 0x44B540, CMenuConfig constructor
0x441520, descriptor point test 0x46B8B0, file-list parent step 0x4398B0, Arcade
post pipeline 0x472F80, title render 0x425740, and three functions that were
already exact but never accepted (0x42CF70, 0x42D010, 0x432200). Reusable source-shape
findings and every parked residual tried this session are in
[VC8 source-shape patterns](VC8_SOURCE_SHAPE_PATTERNS.md). Read it before retrying
any of those functions.

The quickest discovery method was to rebuild every unit that holds a nonexact
authored function and rank the results by first-mismatch offset and size delta. A size
difference with a late first mismatch has usually been a real source-shape
error. Equal sizes have usually been register or scheduling noise.

The largest remaining nonexact clusters are VC8 optimizer choices that no
source spelling has moved so far: commutative operand order in checked-container
bounds, compare-in-memory then reload, register preference after calls, and
tail-merge or block placement. A real LTCG build of one of them is the next
untested lead; it needs genuine callee definitions, without stubs or `/FORCE`.
The giant Fighter/Object action roots remain far from exact; see their topic notes.

Read live status from the ledgers instead of copying totals into this document:

```bash
git status --short
scripts/repo-python scripts/report-reconstruction-status.py --summary
```

## Useful current results and blockers

- Battle setup, pair initialization and camera providers share
  `GlobalBattlePairState`; nine roots remain exact. See
  [battle-pair ownership](BATTLE_PAIR_CAMERA_OWNER_2026_11_10.md).
- Scenario runtime reset `0x457E40` is locally exact at 334 bytes after using
  real map-iterator and render-list operations. The interpreter remains blocked
  on its local string-constructor binding. Stand commands use the record's
  character resource name, with loader-returned texture tokens. See
  [runtime reset](SCENARIO_RUNTIME_RESET_SOURCE_2026_11_04.md),
  [Stand resources](SCENARIO_STAND_RESOURCE_2026_11_10.md) and
  [texture publication](SCENARIO_TEXTURE_PUBLICATION_2026_11_10.md).
- Application initialization `0x407CA0` is locally exact across the 255-byte
  root, cleanup EH and real inline exit callback. Factory's standalone COFF
  comparator cannot accept its linked DLL. See
  [application initialization](APPLICATION_INLINE_CLEANUP_2026_11_10.md).
- SystemEffect spawning `0x458340` is exact at 125 bytes with Factory acceptance.
  Spell selection shuffle `0x432420` is locally exact at 196 bytes using the
  genuine deque provider. See [SystemEffect spawning](SYSTEM_EFFECT_MANAGER_SPAWN_2026_11_04.md)
  and [spell shuffle](SPELL_SELECTION_SHUFFLE_SOURCE_2026_11_04.md).
- The real ACK-constructor CIL context lacks definitions for the IPacket base
  serialize/parse slots. Recover those providers before linking; do not invent
  bodies or change the base to pure virtual merely to satisfy the linker.
- The private CDesignBase loader context links, but remains nonexact: native
  callable size 2666 versus CIL 2708, frame 0x3E8 versus 0x3F8, with separate
  switch tables. The CGage initializer also has a genuine ABI difference
  (native ESI/RET12 versus CIL stack receiver/RET16). Preserve its real provider
  inputs; do not force registers or reopen spelling/flag grids without new
  evidence. See [real gauge context](DESIGN_LOADER_REAL_GAGE_2026_11_02.md).
- Large character and effect updates remain nonexact despite useful typed-owner
  and semantic corrections. Consult each topic note before repeating failed
  controls. The [Reimu](REIMU_OBJECT_EVIDENCE.md) and
  [Aya](AYA_OBJECT_EVIDENCE.md) indexes collect their relevant findings.

## Next reconstruction step

Review the pre-existing dirty source and manifest changes, select one bounded
scope, and run the target/status/tracking checks from AGENTS.md. Compile and
compare the complete affected extent, including owned metadata and relocations;
recheck directly affected accepted consumers when shared inputs change.

Keep one writable reconstruction scope and run VC8/Ghidra serially. Attest any
analysis session before using its semantics. Source presence, semantic probes
and a successful link confer no exact credit.

Retain a short finding and checkpoint stable work with the current commit prefix.
Run the applicable focused checks and `python3 scripts/ci.py` before committing.
Basic CI uses only the standard library for tracked-file syntax, whitespace,
portable ledger/build-graph consistency and private artifact checks. GitHub
Actions checks the PR/push commit range with `--base COMMIT`. Native contracts,
target-byte validation, tests and exact comparisons run separately when relevant.
Ordinary documentation maintenance needs no native build or broad replay.
