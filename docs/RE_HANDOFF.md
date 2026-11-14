# TH10.5 reconstruction handoff

Follow [AGENTS.md](../AGENTS.md). Reconstruct only the original Japanese
TH10.5 v1.06a executable with SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.

## Current work

The 2026-11-14 sessions (commit prefix `claude-opus-5.5-high:`) moved VC8
compiles to the system Wine (`scripts/compile-unit.sh`, about 2 s per unit) and
raised exact coverage by roughly 30 functions. The recovered source-shape rules
and every parked residual are in
[VC8 source-shape patterns](VC8_SOURCE_SHAPE_PATTERNS.md); read it before retrying
any near-miss. Origin fixes are in
[origin corrections](ORIGIN_CORRECTIONS_2026_11_14.md).

The most productive finding: **texture handles are the 4-byte class
`DesignTextureHandle`** (`engine/TextureHandleValue.hpp`).
- The binder 0x404DF0 and the release 0x404D70 take it by value.
- The release has two linker-folded overloads, `unsigned` and
  `DesignTextureHandle`.
- `TextureHandleResult` aliases the class.
- Handle fields that callers pass to these functions are class-typed. Where a
  native helper proves `vector<unsigned>` (the background vectors and the scalar
  `_Assign_n` 0x40C2E0), the element stays `unsigned` and uses the `unsigned`
  overload.

Typing handles this way made about a dozen equal-size near-misses exact, including
`Character_dtor` 0x462CE0. A call site that builds an argument in place
(`push ecx; mov eax, esp; mov [eax], x`) is a literal converting to the class;
two pushes of a zeroed register are `DesignTextureHandle()`; a plain push is a
class object.

Other equal-size near-misses fell to small source causes:
- statement order (sum association, sequence publication);
- disjoint local scopes;
- short unrolled loops;
- the CRT `__min` macro;
- binding a copied handle local.

Treat equal-size residuals as source questions first.

### Latest change

The virtual `CSprite::set_texture` and `set_texture_options` setters also take
`DesignTextureHandle`. So do the spell record handles (`batch_texture_handle_40`,
`card_texture_handle_44`) and `g_common_spell_extra_handle`.
`SceneTextureHandle` is unified into `DesignTextureHandle`. This made 0x448B40
and 0x45DC90 exact, and kept 0x41FB80 and 0x4343A0 exact through natural
rewrites. A 389-unit replay against `matches.csv` showed no regressions.

The non-virtual `CSpriteEx`/`CTile` setters still take `unsigned`. Retyping them
is the next handle-typing step.

### Verifying shared type changes

After changing a shared header type, build a baseline and a new run for every
unit whose source include-closure mentions the changed names, then compare per
function. The session's scratch scripts did this in about 20 minutes per pass.
Then refresh the scalar-wrapper receipts:

    scripts/repo-python scripts/scalar_wrapper_origins.py --unit <unit> ...

Then run `scripts/function-origins.py --check`. It needs about 10 minutes, and
it flags header pins that need renewing; keep each pin's raw or LF hashing
convention.

### Open leads

- `CSprite::set_texture` callers and remaining handle fields: continue the
  handle typing.
- Text-texture pair 0x404D00/0x4097A0: a real LTCG build differs only in LTCG
  promoting `width` into ECX.
- The 64-byte-frame island (0x418990, 0x406360, 0x4063D0) matches code built
  with global optimizations disabled (`idiv` for `% 3600`). The setting that
  gives `and esp, -64` is unknown, and the three audio gain callers depend on
  0x418990. [Number frame audit](NUMBER_FRAME_AUDIT_2026_10_21.md) shows
  ordinary O2 emitting that alignment for a function with real `double` locals,
  and `#pragma optimize("y", off)` removing it.
- Linked units are needed for the LTCG-private ABIs: `this` in ESI or EAX,
  0x41B7F0, and the PAT loader 0x461B70.

### Parked clusters

These are documented in the patterns note:
- EH-state store placement (six functions);
- unmerged `return 0` epilogues;
- commutative operand order;
- register rotation in `release_all_tracked` and `update_and_prune`;
- the dead `push ecx` slot.

The giant character action roots (Reimu 0x478FA0, Komachi 0x5E20E0) have no
source yet.

The 2026-11-14 cleanup removed the single-function `audit-*`/`probe-*` scripts,
their tests and notes whose topics are now exact. Older notes still name some of
them; recover any from Git history (the parent of the cleanup commit) if a
reopened residual needs one.

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
