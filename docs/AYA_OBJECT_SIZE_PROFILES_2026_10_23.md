# AyaObject size-oriented compiler controls

Completed before the handoff cleanup: `/O2 /Os` and `/O1` produce identical
canonical payloads for the selected update source, but both disagree with the
target stack frame. Neither profile is selected. No game source, build profile,
relocation contract or exact ledger changes.

## Inputs and observed results

Only original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Target/status/tracking checks pass; IDA rejects its open database's
different hash. Target entry instructions are decoded directly from the
hash-attested PE.

The selected source is `src/characters/AyaObjectActionState.cpp`, SHA256
`4272f7f5d30499822931f9a70f7b52e179e6d99732e7d21962f58a6cfdef0472`
(game-source checkpoint `e24fb73`). A fresh configured SP1 `/O2` build remains
nonexact at `0x61A2B2`, `+0x22`, target `0F` / source `9B`. Its complete emitted
payload remains 20,132 bytes, canonical SHA256 `a5dc22f5...`.

Each private control compiles a frozen copy of that source with the same SP1
compiler, headers, `/GS- /GR /EHsc /MT` and explicit environment. The only flag
change is `/O2 /Os` or `/O1`. Builds run serially on CPU0/nice10. Both complete
the existing canonical address replay without adding literal or code bindings.

| Input | Emitted section-tail bytes | First target mismatch | Frame after `MOV EBP,ESP` |
| --- | ---: | --- | --- |
| Target | Callable ledger: 19,522 | — | `AND ESP,-8; SUB ESP,0x20` |
| Configured `/O2` | 20,132 | `+0x22` | Target entry frame retained |
| `/O2 /Os` | 18,180 | `+0x4`, target `E4` / source `EC` | `SUB ESP,0x18` |
| `/O1` | 18,180 | `+0x4`, target `E4` / source `EC` | `SUB ESP,0x18` |

Both size-oriented payloads have full canonical SHA256
`7619d56b2b0745c133841abf47ebcb22c8484a2c1aabaf89a05f2aa9087b125f`.
They also replace the target's initial indexed dispatch with a comparison tree.
The emitted tail includes metadata; its size is not a recovered callable boundary.

## Interpretation and recovery

These observations reject a direct global size-profile substitution for this
source/compiler context. A smaller payload does not improve canonical agreement.
No runtime equivalence matrix is claimed for either control, and these results
do not rule out other genuine TU, visibility or lifetime contexts. An older
Aya `/Os` experiment targeted initializer `0x61F0B0`, not this update root.

Private recipes: `.analysis/aya-size-profile-20261023/controls.py`.
Private scope: `build/aya-size-profile-20261023/`. `controls.json` records exact
commands, compiler/source/object pins, entry instructions and comparison
results; `inputs.json` pins 157 public build inputs. Frozen source, all three
objects and both canonical bodies remain loose. `handoff-verification.json`
records fresh target entry bytes and successful readback of all input hashes.
The controls script refuses existing output objects; inspect its receipts
before attempting to rerun it in the same directory.
