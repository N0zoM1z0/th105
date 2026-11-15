# TH10.5 reconstruction handoff

Follow [AGENTS.md](../AGENTS.md). Reconstruct only the original Japanese
TH10.5 v1.06a executable with SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.

Read live status from the ledgers rather than from this note:

```bash
git status --short
scripts/repo-python scripts/report-reconstruction-status.py --summary
```

## How the recent gains were made

Read [VC8 source-shape patterns](VC8_SOURCE_SHAPE_PATTERNS.md) before retrying
any near-miss. It lists the source shapes that produced exact matches and every
parked residual with what was tried. The most productive rules:

- **Integer comparison constants are emitted as written** (`x < 1` is not
  `x <= 0` to VC8). A greedy respelling pass over the giant character
  functions removed hundreds of differing instructions; the target's `cmp`
  immediate gives the source literal. Float comparisons need the ordered form
  the target tests (`!(a > b)` is not `a <= b`).
- **Duplicate a shared tail in source** when one branch jumps into another
  branch's tail. VC8 then cross-jumps the copies the way the target does. This
  closed the scenario list fade 0x455850, the battle menu update 0x4407E0 and
  Komachi's initializer 0x5F6700.
- **Texture handles are the 4-byte class `DesignTextureHandle`**
  (`engine/TextureHandleValue.hpp`), taken by value by the binder 0x404DF0 and
  the release 0x404D70. Fields that callers pass to them are class-typed;
  vectors proven `vector<unsigned>` by native helpers keep `unsigned`.
- Use offset macros, not an inline `at<T>` accessor, in the giant switches.
  Re-read members per test instead of caching them in locals.
- A "remote chunk" reached by `jmp` after an epilogue is usually a tail call
  to a separate function (the scene frame update 0x43B4A0 tail-calls 0x4400D0).

Equal-size residuals have nearly always been source questions (statement order,
branch direction, scopes, literals), not compiler settings; RTM, LTCG, `/Z7`,
`/fp` and `/Os` variations were tried without effect.

## Open work

Smallest remaining character residuals, after the literal pass:
- Alice CPU policy 0x4F4B80 (about 40 differing instructions);
- the control-mode functions: Aya 0x616800, Patchouli 0x51CB40 (+8 bytes of
  frame), Suika, Yukari, Tenshi;
- the object-entry functions of Sakuya, Marisa, Patchouli and Yuyuko, and the
  Marisa CPU dispatch tails 0x4B4070;
- the initializers Reimu 0x491C40, Udonge 0x5D0E60 and Youmu 0x53A1D0 (one or
  two cross-jump regions each).

Other open leads:
- Scenario character install 0x456EB0 (one EH-state store) and the info
  effect update 0x65CB40 (14,783 bytes, two regions).
- LTCG context: `MenuCursorState::update` 0x41FA20 takes a propagated
  `int period` from its 35 callers, which explains its `idiv` by 6. The angle
  lookups 0x406360/0x4063D0 (`idiv` by 3600) and the menu callers' residuals may
  come from the same whole-program context.
- LTCG-private ABIs need linked units: `this` in ESI or EAX, 0x41B7F0, the PAT
  loader 0x461B70, and the shared `list::erase` 0x414DE0 behind 0x414D50 and
  0x419400.
- The text-texture pair 0x404D00/0x4097A0 differs only in LTCG promoting
  `width` into ECX. The gain conversion 0x418990 keeps two redundant float
  round-trips.
- The ACK-constructor CIL context lacks the IPacket base serialize/parse
  providers; recover them rather than inventing bodies.
- The CDesignBase loader links but differs in size (2666 against 2708) and
  frame (0x3E8 against 0x3F8); see
  [real gauge context](DESIGN_LOADER_REAL_GAGE_2026_11_02.md).
- The giant action roots of Reimu 0x478FA0 and Komachi 0x5E20E0 have no source
  yet. The [Reimu](REIMU_OBJECT_EVIDENCE.md) and [Aya](AYA_OBJECT_EVIDENCE.md)
  indexes collect the findings for those characters' object roots.

## Checking shared type changes

After changing a shared header type, build every unit whose include closure
names the changed type before and after, and compare per function. Then refresh
the scalar-wrapper receipts
(`scripts/repo-python scripts/scalar_wrapper_origins.py --unit <unit>`) and run
`scripts/function-origins.py --check` (about 10 minutes), which flags header
pins that need renewing.

## Session rules

Keep one writable reconstruction scope and run VC8/Ghidra serially. Attest an
analysis session before using its semantics. Source presence, semantic probes
and a successful link confer no exact credit. Run the focused comparisons and
`python3 scripts/ci.py` before each commit.
