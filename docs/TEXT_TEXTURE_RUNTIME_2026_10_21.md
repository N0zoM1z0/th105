# Text-texture wrapper and population source

`TextTextureRuntime.cpp` provides genuine C++ source for wrapper 404D00 and
backend 4097A0, with real native token acquire/recycle definitions in the same
TU. Both are source-present and **nonexact**. No match row or exact byte is added.

Only original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Target/status/tracking preflights pass. IDA rejects its wrong open
executable; raw canonical PE instructions and pinned VC8 builds supply the
new evidence. No database or target bytes are modified.

## Observed complete boundaries and calls

| Target | Bytes / reachable instructions | SHA256 |
| --- | --- | --- |
| 404D00 wrapper | 111 / 40 | `fc2a1d60bc6b46699dfaace27231d5e7135b47105b7493cd04ce864ea9f8ee0c` |
| 4097A0 population | 270 / 94 | `e630b34ff2c155e3cd7fc231b76fa1ff34e28afe2f0ddf6fb232e29035ab7e93` |

Independent CFG traversal reaches every instruction and closes the wrapper's
two RET28 paths and backend RET20. Existing exact UI/network callers establish
the wrapper's hidden four-byte class-result convention. The source uses the
existing `TextureHandleResult` view; original nominal API/class names remain
unknown.

The wrapper initializes the token, acquires its stable cell, writes null to
that cell and invokes 4097A0. A negative backend HRESULT recycles the token
through 405200 and returns handle0. Otherwise the class result contains the
acquired token. The source provides actual native deque/vector/list policy,
generation rollover and lock lifetime for acquisition/recycling. These support
the caller context without new helper credit; the existing 405200 acceptance
in the networking unit is unchanged.

Backend 4097A0 uses ESI for the mutable font state, EAX for unsigned height and
five stack words for cell/text/width/two output pointers. Its complete policy is:

- Test the backend caps byte at aggregate+64, before locking. Bit20 makes the
  unsigned dimensions square by enlarging the smaller one.
- Lock the backend and call D3DXCreateTexture with levels1, usage0, format21
  and pool1; unlock. Negative creation status returns immediately.
- Lock again and call texture vslot4C/LockRect. Exactly status0 enters the
  clear/render path; other statuses skip it and are returned after unlocking.
- Clear `4 * height * width` bytes with 32-bit unsigned multiplication. Publish
  font cursor144 before base140, signed pitch/4 at150, width14C and height148.
- Call normal ECX/RET12 font entry412670 with text and the two optional output pointers.
  Reload the texture through the original cell for vslot50/UnlockRect, whose
  result is discarded. Unlock the backend and return the saved LockRect status.

The fresh texture reload and ordered font publications are source-visible
lifetimes. Source uses a chained cursor/base assignment and ordinary COM
virtual calls. It retains explicit backend locks, matching the target's absence
of exception cleanup around text drawing. The acquire provider separately has
the target-observed RAII lock/unwind policy.

Raw412670 conditionally writes zero through each final argument before drawing,
then passes those pointers onward. They are optional output pointers. The public
wrapper declaration now passes them as typed pointers; its six existing caller
bindings use the compiler-confirmed decorated name, and existing calls supply
null outputs. The `const void *` font label remains a compatibility view; the
implementation accesses the observed mutable font prefix. Original signedness,
concrete font type, font constness and public declaration spelling need broader
caller/type recovery. No arbitrary-alias or runtime COM coverage is claimed.

## Strict comparisons and remaining context

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-text-texture-runtime --compare --json
# Expected exit1: both complete functions remain nonexact, with no blocked relocation.
```

| Complete source body | Bytes / instructions | First mismatch | Canonical SHA prefix |
| --- | --- | --- | --- |
| wrapper | 110 / 39 | 404D07 / +7 | 50731d79 |
| backend | 264 / 90 | 4097A0 / +0 | 15555b85 |

The source wrapper's release uses normal ECX while the original uses EAX.
The real file-local backend naturally receives font in ESI and height in EAX,
but additionally promotes width into ECX, yielding RET16 instead of target
RET20. It lacks the target's aligned EBP frame. No external private-register
prototype, forced frame, assembly, inert local or fabricated return is used.
These are concrete context differences; they do not prove that standalone
recovery is impossible.

The actual D3DX call at4097E3 reaches thunk68989C, whose FF25 target is IAT
6C02B0, identified as `d3dx9_33.dll!D3DXCreateTexture`. Source uses the matching
ordinary E8 import-thunk declaration. The earlier dllimport control emitted a
different call form. Complete comparisons include every instruction and named
call/data relocation; neither a smaller size nor partial agreement adds credit.

An honest linked experiment still needs the real normal font provider412670
and its begin/end/glyph/markup callees. This checkpoint keeps that open instead
of manufacturing a provider. Recover those bodies or another independently
supported TU/lifetime property before retesting CIL/private lowering.

## Binding scope, ledgers and verification

The sole shared mapping addition is offset100/0x64 on the existing
`g_d3d_backend` aggregate. The target test at4097A9 independently proves that
caps+3C access; no overlapping standalone flags global is invented. Existing
base bytes, previous offsets and validation rules stay in force.

Actual bindings, transitive source uses and native COFF symbol references select
87 affected accepted units, including all transitive `Title.hpp` consumers.
All **207 accepted functions** cold-build and compare exact after the mapping
and output-pointer declaration changes. No unrelated or aggregate replay is claimed.
The 270-byte game's font/D3D policy now has positive authored classification;
the wrapper retains its existing authored rule. Acquire405090 and font412670
remain outside the new source-present/credit rows.

```bash
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

The final focused receipt is `typed-formal.json`; typed-pointer source
SHA256 is `b76d0f5de78a80fa95193c3e2159868c01c092648c9ba6aa6165e8d8934c973a`.
Formal builds, full CFG/hash facts, independent import/member evidence, source
controls and affected replay receipts are under
`build/text-texture-context-20261021/`. Matching `.analysis/` recipes preserve
the experiments. Completed control files are compressed only after per-file
SHA256 readback: 300,427 bytes become 65,280 bytes in
`completed-controls.tar.gz`. The selected formal source/object/receipts remain
available.

## Font provider follow-up

[The font entry checkpoint](TEXT_FONT_RENDER_2026_10_21.md) selects actual
326-byte412670 source and a new bounded prefix declaration. The texture TU now
includes that header instead of deriving its view from the retained composite
facade. Fresh raw native-list/fallback-color evidence rejects that facade's
164 label and any complete-size168 assumption. This include/type-view change
leaves the complete wrapper/backend canonical candidates50731d79/15555b85
unchanged; current receipts are in `build/font-render-20261021/`. The earlier
typed-pointer source SHA above describes the frozen preceding checkpoint.
Real provider/TU closure remains open, with no new exact acceptance.
