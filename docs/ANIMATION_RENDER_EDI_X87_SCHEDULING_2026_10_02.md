# Animation render x87/EDI scheduling, 2026-10-02

## Exact target and comparison evidence

The only target is original Japanese TH10.5 v1.06a, SHA-256 `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`. The two authored, source-present virtual roots are `AnimationObject_prepare_render_transform @ 0x00435360` (439 bytes) and `AnimationObject_render_to_battle_scene @ 0x00435740` (456 bytes). A fresh recursive raw-PE decode covers all 439/456 bytes with 117/119 instructions, no internal gaps, two/one `RET` sites and, in the second function, one terminal direct jump from `4358FE` to `CSpriteEx_finalize_render @ 407AD0`. Their target body SHA-256 values are `fba84339aeaacc35592a61bb85606bbd1bed986cad684b73db614705f514eec7` and `b4dcb23ecb5598042ee9dfb5ded2f6b5016f931efde0f1f0db806caed0bf7461`.

The focused pinned VC8 command `python3 scripts/build.py --unit gpt-web-animation-render-transforms --compare --json` still reports both functions **nonexact**, with full relocation closure and exact-sized 439/456-byte candidate extents. The compared object hashes are `5cd65ae2dcf74b026b88c2702ff2cc5c41df3d4f99ba0c0525175b9abd806de6` and `630b42b9a8fed55e9637ccf83bc4d233e01b2b3189c8a3cf874260965ac143c0`. After relocation replay, each candidate has exactly **five differing byte positions**, entirely at one instruction-order window; all later bytes align. The private comparison is reproducible with `.analysis/animation-render-20261002/diff-instructions.py` and `build/animation-render-20261002-baseline.json`.

| Target | Target order | Current candidate order |
| --- | --- | --- |
| `43537C` / `435380` | `FILD dword ptr [esp+8]`; `PUSH EDI` | `PUSH EDI`; `FILD dword ptr [esp+0C]` |
| `435769` / `43576D` | `FILD dword ptr [esp+8]`; `PUSH EDI` | `PUSH EDI`; `FILD dword ptr [esp+0C]` |

The following `LEA EDI,[ESI+4]`, second `FILD`, float stores and transform calls have the same instruction forms and bytes. The `FILD` reads the signed pivot-X stack home derived from frame `+0x04`. The offset change preserves which stack value is read across the `PUSH EDI`; this is a compiler scheduling mismatch, not an observed missing transform step. The target and candidate save the same nonvolatile registers and use the same 12-byte initial frame.

## Private source and compiler controls

Each variant was compiled separately with the pinned VC8 SP1 `/O2 /GS-` profile and compared through the configured unit's relocation contract. No variant is accepted as source:

| Control | Fresh result |
| --- | --- |
| Make the two pivot locals mutable | Byte-neutral: first differences remain `+0x1C` / `+0x29`. |
| Use implicit short-to-float conversions | Byte-neutral. |
| Read `frame_150` directly instead of a pointer local | Byte-neutral. |
| Use a pointer to const frame | Byte-neutral. |
| Declare pivot Y before pivot X | Regresses at `+0x0F` / `+0x1C` by reversing the target's two signed-short loads. |
| Use one long-lived sprite reference | Regresses at `+0x04` / `+0x03`, changing receiver register coloring and the prologue. |
| Local `#pragma fenv_access(on)` | Regresses at `+0x02`: candidate frame grows from `0x0C` to `0x10`; the exact neighboring sprite-rotation precedent does not transfer here. |

A separate single-TU `/GL` plus `/LTCG` export/include diagnostic retained the same `PUSH EDI; FILD [esp+0C]` opening in both forms. Its DLL contains forced unresolved externals and is **noncanonical**, so it cannot support byte acceptance or rule out a different original TU/link context. Logs and rejected source variants are private under `build/animation-render-20261002-*` and `.analysis/animation-render-20261002/`.

**Unknown:** the original source grouping, TU ownership, and scheduler context that places the first `FILD` before saving EDI. The retained natural C++ source, helper ABI, match unit and relocation ledgers remain unchanged. No exact credit is added; do not force the order with assembly, volatile state, dead locals or register constraints.
