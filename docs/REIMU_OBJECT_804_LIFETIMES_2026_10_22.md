# ReimuObject action804 velocity lifetime, 2026-10-22

Action804 sequence2 retains its rounded velocity on the x87 stack across the
floor predicate. The current selected source reproduces that 77-byte window.
The private complete-owner root initially loses that lifetime despite equal
observable results in the finite matrix. Accessing the real float storage
through existing owner subobjects restores the window. The whole root remains
nonexact; no private owner change is selected and no exact credit is added.

## Target observations

All target observations use original Japanese1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
IDA preflight again rejects its unrelated `10350095...` image. This work uses
the attested PE and ordinary VC8 COFF builds, without decompiler authority.

The primary804 entry is `496C1E`. The physical interval before the next primary
entry ends at `497086`; this does not assign all bytes to804 or establish a
compiler boundary. Within it, `496F2F..496F7C` (exclusive end) is a complete
77-byte velocity/heading window:

1. Load float velocity at this+F8, subtract the double0.25 at6C33A8, store to
   the float stack temporary and reload. This explicitly rounds the new value
   before assigning this+F8 with nonpopping FST.
2. Load float Y at this+F0 and add the retained velocity with `FADD ST(1)`.
   `FCOMP` against the double zero at6CD148 consumes the sum, leaving velocity.
3. `FNSTSW AX; TEST AH,5; JP` selects the no-flip path, including unordered
   comparisons. The flip path uses FCHS/FSTP to this+F8; the other path pops
   the retained value with `FSTP ST(0)`.
4. Load this+12C, add the double40 at6C13D0 and store the heading as float.

Thus two logical x87 values are live immediately before FCOMP and one is
live immediately after it. The public source window at80091E has all77 bytes
equal, including its local branches and replayed literal addresses. The
private complete-owner root instead adds Y from memory, consumes its only
value at FCOMP and reloads velocity if the branch flips. Its window also has
77 bytes; equal length alone misses this difference.

## Real execution and compiled negative control

`scripts/audit-reimu-object-804-lifetimes.py` relocates the actual COFF source
through the configured real helper/data mappings. It executes original target
instructions and the real62-byte animation helper4351C0. It neither patches
instructions nor supplies opaque return values. Raw Y/velocity bit patterns
are installed in fixture storage at root entry, before its first instruction.

The fixed5,120-case matrix crosses ten Y patterns,16 velocity patterns, two
x87 precisions (53/64), four rounding modes and alpha0/4/5/200. Values include
signed zero,0.25 neighbours, subnormals, infinities, signed quiet NaN payloads
and signalling NaNs. Exceptions are masked. Sequence2, phase0, counter1 and
timer0 avoid the emitter/render/RNG paths and let the real animation helper
return without another callback or expiration. Every case returns through
the full root ABI; predicate entry/exit are each reached once. There are1,704
velocity flips and2,048 actual animation-helper calls.

Compare full fixture outputs as raw bytes, ordered owner writes, logical
x87 values/tags at both predicate sides and selected stores/helper entry, and
final FPSW. The inherited execution gate also checks callee-saved registers,
ESP/RET0, unchanged control word and empty final x87 stack.

| Compiled source | Outputs / ordered writes / final FPSW | Logical snapshots | Window |
| --- | --- | --- | --- |
| Selected public root | Equal in5,120 | Equal in5,120 | 77/77 |
| Complete owner with overlay float access | Equal in5,120 | Different in5,120 | Nonexact |
| Complete owner with typed self float access | Equal in5,120 | Equal in5,120 | 77/77 |

The middle row is a genuine compiled negative control, retaining the actual
root and real helper. It demonstrates why output-only tests cannot establish
the target's temporary lifetime. These are scoped x86 emulation observations,
not hardware validation, arbitrary object/alias/resource coverage, unmasked
exception coverage or whole-root semantic equivalence.

## Declaration and member-access isolation

First change only the private sequence selector formal from int to short,
through its existing void-return base/attack/sequence chain. All ten real
sequence bodies remain fully canonical, including27-byte base setter and
202-byte attack selector. The root remains45,712 bytes with unchanged
canonical SHA256 `85492a7eafaa3524982491875ef1eecf649c0370ee05918dcb45a0a6e6f854d0`,
still nonexact+31. Counter4963A0 remains66/66. Target low-word use does not
uniquely recover the original nominal formal; width alone does not explain804.

Next retain the original private int/void declarations and change only self
float access. Use existing effect position/scale/angle members and existing
owner float tail members. Expose observed velocity X/Y and acceleration Y in
the effect sprite's existing16-byte opaque storage, keeping the opaque union
alternative and the unused third word. Compile-time size/offset checks retain
the existing subobject layout; no constructor, vtable, value or padding is
invented. Other parent/scalar accesses remain unchanged overlay views.

This native diagnostic root is45,696 bytes, canonical SHA256
`b23be2ba4248277cf0a20f1b5a0df1b3535293237df051f850fa8f32173fec6f`,
still nonexact+31. Counter4963A0 remains66/66 with canonical SHA256
`ad12b782ed5fc99007456fc66a9615951cee34178850a308316409c5245bb156`.
The restored804 window and matrix justify investigating typed owner access;
they do not establish original member declarations or select the full model.
A coarse public-versus-typed instruction delta has15 regions, located in869,
902,904,907 and908.804 and822 scheduling differences seen in the earlier
complete-owner control disappear. Branch normalization is only a location
diagnostic; those remaining changes require their own target observations.

## Reproduction and acceptance

Build the unchanged selected public unit, retaining its expected root
comparison failure and accepted helper result:

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-reimu-object-action-state --compare --json
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-804-lifetimes.py \
  build/match-units/GptWeb_ReimuObjectActionState.obj
```

The optional `--contrast-object` / `--contrast-symbol` arguments add a compiled
negative control; the primary `--symbol` can select a private real owner.
The report pins its object, target, source, manifest/data ledgers, script
dependencies and engine versions before/after execution. It explicitly does
not independently attest a source-to-object build; retain the fresh build
receipt alongside it. A contrast mismatch is informational, while a primary
snapshot/output mismatch fails the command.

Private recipes are in `.analysis/reimu-object-804-lifetimes-20261022/`:
`facts.py`, `word_build.py`, `word_root.py`, `direct_float.py`, `direct_delta.py`.
Receipts under `build/reimu-object-804-lifetimes-20261022/` include
`facts.json`, `word-sequence-comparison.json`, `word-root-comparison.json`,
`direct-float-inputs.json`, `direct-float-comparison.json`, `direct-counter.json`,
`public-audit.json`, `direct-audit.json`, `direct-source-delta.json` and
`fresh-public-build.json`. Private headers, objects and reports are uncommitted.

Fresh public replay retains source SHA256
`3b9e4896c3645bb1228db3b432a832154870c5639a80df6c02cb67ce2dba12cc`,
45,700-byte canonical SHA256
`d0ff3d3259c823cc56e322c5e0ec238456d8b490c78b4a5336a249b45a405a58`,
first difference49655F/+31 and helper66/66. Source selection, shared public
headers/profile/layout, byte ownership and matches are unchanged. Current
ledgers stay1,379 exact/234,584 bytes; no new aggregate cold replay is claimed.
Next inspect869's remaining floating round trips before selecting owner access.
