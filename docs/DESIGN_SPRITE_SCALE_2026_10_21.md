# CDesignSprite uniform scale: complete canonical exact

`CDesignSprite_set_uniform_scale @40AEE0` is **19/19 canonical exact** in
`gpt-web-gage-design-render`. Its ordinary typed definition is added to
`src/ui/GageDesignRender.cpp`. The same affected object also reproduces both
existing CDesignGage renderers,40AEA0/40AF30, at60/60 and68/68. Only the new
19-byte function receives new exact credit.

## Observed target identity, extent and behavior

All observations use the original Japanese TH10.5 v1.06a PE, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Target/tracking checks pass. IDA again fails attestation with10350095...;
no IDA semantics, Ghidra process or target modification is used.

RTTI COL6DCB50 identifies vtable6D6A80 as `CDesignSprite`; its+18 cell6D6A98
points to40AEE0. The actual descriptors name the zero-offset, nonvirtual
hierarchy `CDesignSprite`, `CDesignObjectBase`, `IColor`; the last descriptor
uses the struct spelling `.?AUIColor@@`. The constructor path at40B437
allocatesAC bytes, publishes the primary vptr at40B451 and the sprite vptr
6C0668 at whole-object+18 at40B463. This independently supports the18/94/AC
prefix/member/complete extents used by the source view.

The complete callable is `[40AEE0,40AEF3)`, with four instructions:

```text
40AEE0  fld  dword ptr [esp+0C]
40AEE4  fst  dword ptr [ecx+A0]
40AEEA  fstp dword ptr [ecx+A4]
40AEF0  ret  0C
```

All instructions are reachable; no call, branch, remote tail or EH region
belongs to the body. Four preceding and thirteen following INT3 bytes isolate
it. Its complete canonical SHA256 is
`057e8a478ee3a8c3d9ed37ec74e368816eca4da489e18d0fee61fe6605d32786`.
ECX supplies the receiver and RET12 consumes three stack words. Only the third
word is read, as float. It is published first toA0, thenA4. The independently
recovered sprite layout identifies these as member18's scale X/Y fields88/8C.

The durable uniform-scale name describes that observed policy. The source
uses `set_render_parameters(unsigned,unsigned,float)` as a normal virtual
slot18 definition. The first two semantic parameter types are unknown; the
unsigned word view is ABI-compatible and neither argument is evaluated by
the body. Exact callee bytes do not establish their unique original types,
the original setter name, return spelling, base data ownership or TU.

## Source and acceptance

Two explicit member assignments preserve the observed publication order.
Local layout assertions guard the completeAC-byte object, sprite+18 and
scale88/8C. The existing design receiver/typed sprite views are reused without
changing a shared header. Ordinary VC8 SP1 O2, GS off, emits the complete
19-byte symbol with no relocations. No assembly, padding, inert locals, manual
vtable dispatch, custom entry convention or manufactured return is used.

| Formal artifact | SHA256 |
| --- | --- |
|CRLF source|d725647a99627c6ac885b40f3abecd9001e42d8c9caf420c6a308578c4f9a543|
|COFF|8525cf03a4f05a817e544bdd16c22abdc57d332a415ceb710808733c1909453d|

`build/design-sprite-scale-20261021/` retains the raw target packet, initial
probe, final formal build receipt, frozen selected source/object and bounded
acceptance delta. Private recipes are in the corresponding `.analysis/`
directory. The formal receipt attests source/compiler/object provenance and
all three whole-function comparisons. Native fixture replay is unnecessary
for this complete zero-difference result and is not claimed.

The candidate, durable name, source selection and exact ledger are updated
together. The official origin `baseline()` supplies the newly exact row.
All196 explicit rule selections remain unchanged and exclude this address;
the origin-rule file itself is unchanged. No full library-anchor or aggregate
cold replay is claimed. No other selected source, compiler profile, object
partition or relocation changes; the three-function focused build covers the
affected source unit.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-gage-design-render --compare --json
python3 scripts/validate-tracking.py --require-target
python3 scripts/build.py --check
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

The focused build must report exact60/68/19. CGage41B3F0, texture binder404DF0
and ReimuObject496540 remain nonexact; this small entry supplies no acceptance
for them. The additional [CGage product controls](GAGE_RENDER_CONTEXT_2026_10_21.md#additional-product-and-inheritance-controls)
leave that selected source unchanged.
