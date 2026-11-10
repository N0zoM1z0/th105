# TH10.5 reconstruction handoff

Follow [AGENTS.md](../AGENTS.md). Reconstruct only the original Japanese
TH10.5 v1.06a executable with SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.

## Current work

The November 10 maintenance removes obsolete archives, diagnostic outputs and
cleanup history. Current source, exact ledgers, reproducible build scripts,
toolchains and analysis projects remain in place. Keep useful findings in the
existing topic notes; a file being cited is not a reason to retain it.
See [ARTIFACTS.md](ARTIFACTS.md) for the small set of private inputs to preserve.

The latest reconstruction checkpoint before maintenance is `ec2fbccf`, joining
battle setup to the live camera owner. The worktree also contains earlier
uncommitted Input ownership/source-pin changes, Scenario data/render/text
changes, MenuCursor layout work and an Alice action-214 audit change. Preserve
those edits and inspect their diffs before resuming reconstruction. This
maintenance does not reconcile or accept them.

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

Retain a short finding and checkpoint stable work with `gpt-dots: <summary>`.
Run the applicable focused checks and the local CI/diff gate before committing.
Ordinary documentation maintenance needs no native build or broad replay.
