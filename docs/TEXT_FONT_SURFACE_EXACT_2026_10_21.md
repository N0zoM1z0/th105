# Native font surface value: complete45/45 exact with an actual caller

`TextFont_set_surface @ 0x00411760` is canonical **45/45 bytes**, all9
reachable instructions, under the explicit local
`vc8-sp1-probe-o2-ob1` profile. A genuine file-local typed stdcall takes font,
surface, an8-byte by-value dimension pair and signed pitch. VC8 naturally
passes font in EAX and surface in ECX, leaving size/pitch on the stack and
returning with RET12. The real source parent retains one E8 at canonical412359,
the same target callsite. No unused function copy is used as caller evidence.

Full target/source SHA256:
`04b792ad4009bbc903713029ed02d712df4599ebdad9a2cfc313458837d37b06`.
Only original Japanese TH10.5 v1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is analyzed. Required target/status/tracking preflights pass; IDA rejects its
wrong open executable, so observations use the attested raw PE.

## Boundary, data and the missing value type

The complete leaf ends in RET12 at41178A..8C. There are no relocations, callees,
EH metadata, internal skipped bytes, static storage or cropped extents.
It loads height from the second stack word, writes surface to cursor144 then
base140, writes width14C, height148 and pitch150 in order. It never dereferences
surface, converts pitch, validates dimensions or adds a null gate.

The binary's three stack words did not prove three independent scalar
parameters. The source's meaningful dimension value is:

```cpp
struct TextSurfaceSize {
    unsigned width;
    unsigned height;
};
```

Both DWORDs are used. It is a real size value, with no dummy field or padding.
The by-value argument remains on the stack while the two pointers receive the
compiler's private registers. This reproduces the target's height load and
RET12 rather than silently promoting height into EDX. The original type/name
and whether it was another ABI-compatible value type remain unknown; this is
a source model supported by complete native code and its genuine caller.

The selected caller creates this value from its actual width/height fields
and passes it to `set_font_surface(&ruby, surface, size, pitch)`. The body
performs only the observed chain assignment and three dimension/pitch stores.
The obsolete unused normal-member declaration is removed. No register facade,
fastcall wrapper, source noinline annotation, assembly or shaping local is used.

## Controlled source/profile evidence

| Source/control | Complete setter | Actual parent call |
| --- | ---: | --- |
| Ordinary scalar member, default COFF |49 bytes, normal ECX/RET16|one call, wrong private ABI|
| Scalar local stdcall, default COFF |41 bytes, height in EDX/RET8|inlined|
| Scalar cdecl/stdcall/fastcall, `/Ob1` |39/41/41 bytes|one call, wrong native ABI|
| Real scalar member, genuine GL `/Ob1` link |41 bytes|one call, wrong native ABI|
| By-value size, default `/O2` |45 bytes, all bytes equal|inlined; unused copy rejected as caller evidence|
| By-value size, `/O2 /Ob1` |**45 bytes, all bytes equal**|**one actual E8 at412359**|

The local profile explicitly selects `/Ob1`: only functions marked inline or
defined inline in a class are candidates for ordinary expansion. It retains
the observed call to this normal helper while allowing real inline STL
members. The default profiles keep their previous compiler arguments; no
project-wide option is changed. This reconstructs a reproducible native
function/caller configuration, not the original project's unknown options.
It does not override a proven original TU boundary or establish a reusable
instruction to add noinline controls elsewhere.

The manifest names the profile, the builder resets ambient inline mode per
unit and records it in provenance, and the shell accepts only default/explicit
modes. Origin-anchor compilation explicitly keeps default mode. Five regressions
check unchanged default flags, `/Ob1` ordering after `/O2`, rejecting an unknown
mode before compiler invocation, environment isolation/provenance and the
profile's local selection. There is no arbitrary extra-flags escape hatch.

## Actual instruction execution and affected replay

All **480/480** complete actual target/source leaf cases pass an independent
five-store/full194-byte font specification and real EAX/ECX/stack cleanup/saved
register checks. Opaque surface inputs include null, unaligned and font-interior
values; dimensions cover full-bit values and pitch covers signed/zero/max
values. No font/stack argument alias or actual surface dereference is claimed.

Only the **480 affected ruby-close parent cases** replay. All pass with actual
byte-identical hex45 and setter45 execution; setter runs192 times per side.
Other CRT/STL/font/color providers remain explicit ABI-specific observers,
without actual GDI, parent EH unwinding or allocation-failure coverage.

Parent shrinks1648/445->1647/444, canonical
`faadf3249a2ad039a3911d58b1a6178197e78d81c689676e6c018d35fbcd177d`.
Complete instruction/CFG alignment proves420 instruction pairs and37 internal
branch edges unchanged outside one ruby setter setup/adjacent SSO pointer
materialization window. That window changes25->24 instructions; it contains
the one real setter call and is exercised by the480 cases, including SSO/heap
strings and output pointer modes. The other tag/byte cases are not replayed.

The by-value size **does not** close the parent's frame gap: source is still
788 versus target796, first difference+16. Normal member/private target entry,
handler/FuncInfo/funclet ownership and actual runtime behavior remain open.
No parent exact or EH credit follows from the leaf result.

The other nine complete font bodies are unchanged under the local profile,
including exact hex45/blend289 and the current624-byte nonexact glyph.
Both accepted header consumers cold-build: font render retains all prior exact
leaves and font owner retains138/210/439/config67 plus compiler-only Tidy71.
The nonaccepted text-texture consumer retains its full110/264 candidate hashes.
New-mode tests and default-mode origin-anchor checks guard the shared tooling;
unrelated units keep the same definitions/default arguments and have no changed
source dependencies. No unrelated or aggregate cold exact replay is claimed.

## Acceptance and commands

One previously source-present authored function gains45 exact bytes.
Source/mapping/authored denominator counts are unchanged. Its old source-present
origin rule retires to canonical-exact-authored, retaining the ownership facts
above. The font unit's accepted subset is now setter411760, blend4127C0 and
hex4128F0. Its whole command still intentionally exits comparison_failed because
eight candidates remain nonexact.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-text-font-render --compare --json
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-text-font-owner --compare --json
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-text-texture-runtime --compare --json
python3 scripts/function-origins.py --check
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Selected source/COFF, complete45-byte/caller evidence and480/480 receipts are
retained in `build/font-setter-local-20261021/`; private controls/recipes are
in `.analysis/font-setter-local-20261021/`. The scalar member GL control is
phase-scoped to baseline commit ec7c0eb; its source input snapshot is preserved.
Unselected outputs are archived only after per-file SHA readback verification.

Next: recover the larger markup/private source context, its8-byte frame
residual and EH, alongside the remaining glyph coordinate ordering. Reimu496540
remains nonexact at49655F/+31.
