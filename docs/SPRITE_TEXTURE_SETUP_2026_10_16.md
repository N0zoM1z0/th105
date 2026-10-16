# Exact Sprite texture setup and its compiler-private helper

## Accepted result

The original Japanese TH10.5 v1.06a target remains SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
One ordinary VC8 TU now reproduces both complete authored callables:

| Address | Recovered operation | Canonical result | Target / relocated object SHA-256 |
| --- | --- | --- | --- |
| `00407160` | CSpriteEx texture options and source-quad initialization | **193/193** | `ff12481407a3f5e34a949c87db2943c48225bc0f5d048d643e217a504b9f6f40` |
| `00407230` | texture rectangle UVs and source-quad coordinates | **261/261** | `83f2b73423fee824bd7eb03bbe0daee895f74dfa6394843f8c03c9263e7f4ba3` |

```bash
python3 scripts/build.py --unit cross-v106a-sprite-texture-setup --compare --json
python3 scripts/audit-candidate-boundaries.py 0x00407160 0x00407230 --json
python3 scripts/check-match-literals.py --require-target
```

Fresh formal report: `build/sprite-texture-setup-formal.json`. The canonical
comparator validates complete COFF symbol ownership, both callable extents,
the real-valued literal, the manager data relocation, the external resource
size call and the caller's relocation to its same-TU helper. Source is
`src/battle/SpriteTextureSetup.cpp`; the unit uses the existing strict-FP
profile with local exception scheduling disabled, no new global flag.

## Observed target facts

Raw CFG traversal reaches all **59 instructions / 193 bytes** of
`[407160,407221)` and **73 instructions / 261 bytes** of
`[407230,407335)`. Both have one RET, no unreached bytes, no visible indirect
jump and no outgoing direct jump. INT3 separates and follows the callables.
The public entry uses ECX and seven integer arguments, with `RET 28`.
Its call at `407183` queries texture dimensions through the existing
normal-thiscall manager helper `404E60` on `702798`.

The current exact-backed five-argument CSpriteEx texture wrapper `41F640`
and CLogo constructor `41F780` independently establish this game-sprite
ownership and public seven-argument ABI. Their configured units
`gpt-web-sprite-texture-wrapper` and `gpt-web-scene-constructor-runtime`
were rebuilt and remained canonical exact. Authored identity does not come
from disassembler auto-naming or from the fact that a byte comparison passes.

The internal entry receives the sprite pointer in **EAX**, six floats on
the stack and pops **24 bytes**. The only raw E8 reference in `.text` is
`407217` in the public caller; no aligned `.rdata` or `.data` dword names
the helper. This is bounded incoming-edge evidence, not exhaustive proof
against every possible computed call. The caller/helper code proves the
pointer and float homes directly; an external normal-thiscall or fastcall
declaration would describe the wrong machine boundary.

For a nonzero texture handle the public entry obtains unsigned dimensions,
converts them to float with the target's signed-load/2^32 correction, and
stores dimensions at +78/+7C. Zero handle writes both dimensions to zero.
It clears the four source-quad z fields at +88/+94/+A0/+AC, sets all vertex
colors to `FFFFFFFF`, converts the six rectangle/pivot integers to float and
calls the internal entry. Real unsigned source locals naturally let VC8 reuse
the dead incoming handle slot for one dimension; source contains no argument
slot aliases or synthetic storage.

The internal entry, when a handle exists, writes width/height UV fractions
at +E0/+E4 and all four vertex UV pairs. Zero handle clears only those two
fractions and leaves vertex UVs intact. Both paths publish the source quad
at +80: left/top are negative pivots, right/bottom are width/height minus
pivots. It does not reset the working quad. Single-precision locals preserve
all observed rounding and reuse, including the shared right/bottom edges.

## Why a complete TU matters

The initial natural private C++ member has a normal ECX boundary in its
standalone object. A bounded `/GL + /LTCG` visibility experiment naturally
changed that helper to EAX with `RET 24`, proving that special-register source
or assembly was unnecessary. Its unresolved inspection DLL was never executed
or accepted as matching evidence; this was only a compiler-phase discriminator.

There is also a truthful standalone-object solution. Keep the complete helper
**file-local**, define it in the same TU as its only source caller, and retain
normal callee-cleanup source semantics through `static void __stdcall`.
VC8 then privately removes the pointer's stack argument, passes it in EAX,
and pops the six floats. Both emitted sides are compared together. Source
does not declare an external EAX ABI, force a register, introduce a shim,
or replace any operation with assembly. A local cdecl control likewise
privately uses EAX but leaves caller cleanup, so it does not reproduce the
target. This source contract is a reproducible reconstruction, not proof
of the original spelling or proof that the shipped TU did or did not use LTCG.

Three target-backed assignment relationships also matter: zero texture
dimensions store height before width, vertex colors store 3/2/1/0, and the
helper's zero fractions store +E4 before +E0. Ordinary chained assignments
express those lifetimes and give full equality without padding or fake work.

## Attested analysis and remaining limits

Direct Ghidra sessions independently checked executable hash, entry and
external-entry marker, x86 Windows language/compiler, full mapped `.text`
and bounded bytes before saving metadata. A fresh read-only process checked
both names, extents, return hypotheses and purge values, public ECX storage,
and custom helper storage: EAX plus six float stack parameters at +4..+24.
The helper's Ghidra convention is explicitly unknown/custom, not an invented
external standard ABI. Pseudocode remains a hypothesis. Processes used a
768 MiB heap and two active processors; no factory adapter or IDA analysis
was used. Private working state is under
`.analysis/sprite-texture-island-20261016/`.

This adds exactly **two authored functions / 454 exact bytes**. The selected
unit has no mixed nonexact member. Original TU partition, original local
variable names and source spelling remain nonunique. Keep the helper definition
and caller together when changing source ownership; replay both after any
visibility, convention, FP profile or layout change. This does not solve the
separate COM scheduling residuals in the basic Sprite/tile renderers.
