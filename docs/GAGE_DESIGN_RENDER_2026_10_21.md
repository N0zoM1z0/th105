# CDesignGage render entries: two complete exact functions

This page retains the original source/receipt epoch at58ccf96. The later
[CDesignSprite scale checkpoint](DESIGN_SPRITE_SCALE_2026_10_21.md) adds19/19
to the same source unit and freshly reconfirms these two60/68-byte bodies.
The original source/object hashes below describe the frozen earlier inputs.

`CDesignGage_render @40AEA0` and `CDesignGage_render_offset @40AF30` now
compare canonically exact in `gpt-web-gage-design-render`:60/60 and68/68,
128 bytes total. The containing CGage renderer41B3F0 remains nonexact;
exact callers do not confer acceptance on that indirect callee.

Only original Japanese TH10.5 v1.06a is used, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Fresh target, status and tracking checks pass. IDA still reports the wrong
10350095... target and is not used for semantics. All new observations come
from the hash-attested PE; no database or target instruction is modified.

## Observed identity, boundary and ABI

Vtable6D6AA0 has RTTI COL6DCB00, type descriptor6FA494 and the name
`.?AVCDesignGage@@`. Its+10 cell6D6AB0 points to40AF30 and its+14 cell6D6AB4
points to40AEA0. The independently exact destructor40BAC0 and
[the factory/lifetime evidence](GAGE_LIFETIME_2026_10_20.md) establish the
embedded CGage at+18, complete member extentA4 and complete object extentBC.
The member's actual vtable6D6A38 has render slot+1C at6D6A54 ->41B3F0.

| Address | Boundary | Reachable instructions | Return | Following alignment | Canonical SHA256 |
| --- | --- | ---: | --- | ---: | --- |
|40AEA0|[40AEA0,40AEDC)|21/21|RET at40AEDB|4 INT3|7421d84962faf205b709b163e6458008ed499e5a2936c4b78bfb2640e5f1ee27|
|40AF30|[40AF30,40AF74)|21/21|RET8 at40AF71|12 INT3|db211a01c6477864717e1428d58dfc22d09384823dc55428449baf540c953fc3|

Each complete local control-flow graph closes at its one return and has one
indirect CALL EAX, at40AED8/40AF6F. ECX is the receiver;40AEA0 consumes no
stack arguments and40AF30 consumes two float words. The plain render uses a
four-byte temporary; the offset entry reuses an incoming stack slot for its
float round trips. Neither body has a remote tail, jump table or EH region.
Void return declarations fit the observed rendering interface; their unique
original C++ spelling and return declaration are not independently recovered.

## Recovered behavior and field correction

Both entries first test byte+14. A zero value returns without calling the
member. Otherwise the target evaluates the Y argument first, then X, rounds
each result to float through a real memory home and invokes the member's
actual virtual render slot1C with ECX=this+18.

Plain render passes `x_0c + base_x_04` and `y_10 + base_y_08`. The offset
entry passes those same sums with incoming X/Y added last. The source retains
this association and the normal C++ virtual call. The body itself writes only
stack storage; subsequent member-render side effects remain an actual call.

The accesses at+04/+08 are FLD/FADD m32 floating-point operands. In particular,
the retained shared `IColor::value_04` unsigned declaration is not evidence
for an unsigned design-coordinate field. `GageDesignRender.cpp` uses a private
four-slot color interface and typed design fields at04/08/0C/10/14, with the
complete typed CGage member at18. This view reproduces observed storage and
slot order without a bitcast, manual function-pointer call or a shared-header
change. Assertions guard each consumed field and18/A4/BC extents. The
three bytes after the enabled bool are ordinary compiler object alignment.

Original base-versus-derived data ownership remains unknown: the four-byte
interface view is not a proof that the original IColor class had that size.
The sprite member uses+4 as its unsigned texture handle, a distinct observed
use. The source's position names and unused virtual declarations remain
layout/interface hypotheses; no constructor, RTTI-data or empty-slot body is
accepted here.

## Source, compiler and acceptance evidence

The selected profile is ordinary `vc8-sp1-probe-o2`, GS off. There are no
floating-point pragmas. The initial strict and ordinary pragma-bearing
controls, followed by the pragma-free ordinary source, all reproduce both
complete canonical bodies. This establishes a reproducible matching profile,
not the unique original compiler flag set.

The two COFF symbol extents are exactly60/68 bytes. There are no relocations
in either body, and no code/global/literal mappings are added. Full comparison
uses the normal canonical comparator with no masks, padding, fabricated
behavior, assembly or ABI facade. A native fixture replay is not substituted
for this complete byte comparison.

| Selected artifact | SHA256 |
| --- | --- |
|CRLF source|85bc09f8a69de247df74c7a5fa377578d04b1fe990c166b2415ad9cf5d51a2c6|
|Formal COFF|1c1551524531767d5fb9d206455798d476180e125e7178a7952682c853533ec6|

The formal build receipt pins the source, compiler, manifest and object before
comparison. Frozen `selected.cpp`/`selected.obj`, preflight logs, full target
packet, initial controls and `formal-build.json` are under
`build/gage-design-render-20261021/`. Private target and acceptance recipes are
under `.analysis/gage-design-render-20261021/`.

Both previously unclaimed review candidates receive durable names,
source-present entries and complete matching rows together. Origin updates
use the official `function-origins.py` baseline function for exactly these two
new matching rows. All196 explicit origin-rule selections are checked before
and after: their ordered selections are unchanged and neither address is
selected. The target and origin-rule file are unchanged. `acceptance-delta.json`
records that bounded update and its pins; no complete library-anchor replay
or new aggregate cold-replay claim is made.

No prior accepted source/header, object partition, flag or relocation changes.
The focused formal build therefore covers the affected new unit. Existing
lifetime/color functions and CGage41B3F0 retain their previous source bytes;
ReimuObject496540 remains nonexact at+31.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-gage-design-render --compare --json
python3 scripts/validate-tracking.py --require-target
python3 scripts/build.py --check
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

The first command must return zero with complete exact60/60 and68/68. The
current handoff and tracking ledgers supersede older statements that these
two runtime virtual bodies were unimplemented.
