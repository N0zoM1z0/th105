# Common Fighter diagnostic refresh and TH08 x87 reference, 2026-10-02

## Canonical result and scope

**Observed:** `CharacterEx::update_common_action_state`, durably mapped as
`Fighter_update_common_action_state @ 0x004740C0`, remains nonexact. A fresh
pinned VC8 SP1 build of `gpt-web-fighter-common-action-state` reproduces
**53/66 instruction/edge-identical physical owners**, metadata at `+0x2838`,
and a 10,801-byte COFF section tail. These are diagnostics, not accepted
function or byte credit. No reconstruction source, compiler profile, layout,
relocation contract, or match ledger changed in this batch.

The full formal comparison first differs at `+0x14 / 0x004740D4`:
target `48`, candidate `95`, inside the high-dispatch branch displacement.
The compared candidate hash is
`99563500433bccf1f68e7c256b438595de9cdcf5b18aee4816f19e69e1cda835`.
The target callable is `[0x004740C0, 0x004768AB)`, 10,219 bytes, with hash
`7def23cf4826d7511260e7d9ea8db18848c43a7b77939bb42724a29af117a0c6`.
Fresh raw traversal reaches all 2,799 instructions and all callable bytes.
Eight register-indirect exits remain visible; their polymorphic owner sets
are outside this bounded traversal.

```bash
taskset -c 0 python3 scripts/build.py \
  --unit gpt-web-fighter-common-action-state --compare --json
python3 scripts/map-giant-action-switches.py fighter-common-action --json
python3 scripts/audit-giant-action-owners.py fighter-common-action \
  build/match-units/GptWeb_FighterCommonActionState.obj \
  --unit gpt-web-fighter-common-action-state --json
```

The first command returns exit 1 for the ordinary mismatch; a successful
owner audit does not imply a successful canonical comparison. Local reports
are `build/common-fighter-20261002-{baseline,target-map,baseline-owners}.json`.

## Remaining physical-owner differences

**Observed:** the thirteen nonidentical owners fall into three groups:

| Owners | Target and candidate difference |
| --- | --- |
| Entry, low 180 containing the high dispatcher | Target uses `sub eax,50` / `sub eax,691`; candidate uses addition of negative immediates. |
| Low 53/54/55/56 and 159/160/161/162 | Target consumers enter the action-50 clamp/drop/advance tails at `0x474122`, `0x474139`, and `0x474161`; candidate puts the shared copies in action 162. Short/near branch lengths and the expanded owner 162 follow from that placement. |
| Low 73/75/88 | Target puts the common sequence-2/3 selection in action 73; candidate puts it in action 88. The 344/310-byte spans exchange ownership, while action 75 remains 148 bytes with a different destination. |

These are instruction and edge observations. They do not establish that
floating semantics are fully recovered, that natural source recovery is
exhausted, or that LTCG caused the residual. In particular, replacing a few
x87 operations would not itself explain the integer dispatcher or shared
terminal placement.

## New private source probes

All probes compile serially on CPU 0 with the existing profile. They are
isolated under `.analysis/common-fighter-20261002/`, with objects under
`build/common-fighter-20261002/`. Existing-object comparison reuses the unit's
relocation contract but explicitly reports unverified build provenance; these
probes cannot be promoted as canonical acceptance evidence.

| Probe | Observation | Disposition |
| --- | --- | --- |
| `late-shared-step` | Reuse one real float rounding temporary across 159..166. Still 53/66; compared bytes have the same baseline hash. | Byte-neutral diagnostic; original declarations retained. |
| `whole-shared-step` | Also reuse the real early clamp lifetime. 51/66, metadata `+0x27E4`; loses owners 50 and 799 without gaining any. | Rejected. |
| `word-action-selector` | Cache the word action as `short`. 11/66, metadata `+0x28AC`; first difference `+6`. Candidate initially zero-extends, then later sign-extends the selector. | Rejected; a word field does not prove a short local after integer promotion. |
| `local-fenv` | Add only `fenv_access(on)` before this definition and restore it after the definition. Candidate begins `push ebp; mov ebp,esp; and esp,-8; sub esp,12`, unlike target `push ecx; push ebx; push esi`. | Rejected as a target profile explanation for this retained source. |

The `local-fenv` formal comparator is **blocked**, rather than an ordinary
completed mismatch: it reports unknown DIR32 literal `__real@3b23d70a`.
The owner audit also fails to pair the low COFF switch table under its current
contract. Do not interpret that failure as absence of a candidate switch;
raw COFF disassembly contains its indexed dispatch. No owner score is assigned
to this probe, and no relocation ledger was broadened to make it comparable.
The different raw entry alone disproves full equality for this object.

## Direct Ghidra attestation and limits

**Observed:** one direct Ghidra 12.1 headless process at a time imported the
canonical PE. The private post-script independently checked raw and imported
executable SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`,
image base `0x400000`, actual external entry point `0x68B9D2`, language
`x86:LE:32:default`, Windows compiler specification, and every mapped `.text`
byte. The mapped `.text` hash is
`f5cb09ff0a54362356d8c4cce853cbcb14552499cce12cf7390d0868db9ebe97`.
The bounded function's extent and body hash agree with raw PE evidence.

An initial decompilation without helper declarations misinterpreted ordinary
calls as possible PIC branches and discarded blocks. The second run declared
fifteen helpers using existing ABI evidence, read back each signature,
calling convention and stack purge, and eliminated those PIC/unreachable
warnings. This metadata improves analysis; it does not prove the original
source declarations. The conversion runtime and indirect virtual calls still
need separate modeling. Inferred root `uint` return and flattened floating
expressions remain decompiler hypotheses and were not adopted into source.

Private script/output: `.analysis/common-fighter-20261002/ghidra-scripts/`
and `ghidra-typed-hypothesis.c`; log:
`build/common-fighter-20261002-ghidra-typed.log`. Ghidra rejected project paths
with dot-prefixed components, so the successful transient project lived below
`build/` and used `-deleteProject`. Script and hypothesis paths can remain
below `.analysis/`. No target bytes were patched. The mismatched IDA session
and factory adapter were not used.

## What the TH08 reference actually shows

**External source evidence:** inspected the local TH08 tree at HEAD
`d2a00f4acb4a13916e07a00bd13f714961714628`. This batch did not rebuild TH08 or
independently verify its target matches. Its source examples are useful
corroboration, not TH105 instruction or compiler provenance:

- `src/ZunMath.hpp:38` and `:57` use inline x87 `fsincos` in vector methods.
  The `sincos` macro at `:145` expands `fld; fsincos; fstp; fstp`.
- `src/AnmManager.cpp:1146` uses a local `frndint` island for four quad
  coordinates, followed by paired stores. The modern-port branch uses
  `nearbyintf`; that branch is not a claim of identical VC7 output.
- `src/Supervisor.cpp:427` retains a separate integer index-shaping asm island.
  It is not an x87 mechanism or evidence for reproducing TH105 dispatchers.
- `docs/BUILD_MATCHING.md:467` records that VC7 `sin`/`cos` intrinsics did not
  fuse into `fsincos`. TH08's current rules forbid adding new assembly merely
  to force comparisons; these retained islands are historical examples.

The inspected `ZunMath.hpp` SHA-256 is
`ba187178ec936c2492f3e311e8d6d634421c35bc5abd74ab4af77a4c81ddb3de`;
`AnmManager.cpp` is
`1c354795fa862d3da2d1164f567980bf813ede9fc1bb5aa1d37d7ee3cf17b24e`.

**Current TH105 evidence:** x87 alone does not imply an assembly requirement.
`CSpriteEx_rotate_xyz @ 0x407680` already matches 1,095/1,095 bytes through
ordinary C++ plus local environment control and real lifetimes; see
[the accepted rotation evidence](SPRITE_PIVOT_ROTATION_2026_10_02.md).
Its trig calls are quantized lookup helpers, not `fsincos`. The body-collision
root likewise matches through target-supported comparison orientation and
single-precision rounding boundaries. Neither result establishes a universal
source recipe for special x87 instructions.

**Unknown / next discriminator:** determine the original common-root source
structure and helper visibility without changing established ABI or numerical
boundaries. Any special-instruction island needs its own target evidence;
there is no demonstrated `fsincos`/`frndint` requirement in this root. Original
TU ownership, link-time transformation, and complete indirect owner sets
remain unresolved. Exact credit added by this batch: zero.
