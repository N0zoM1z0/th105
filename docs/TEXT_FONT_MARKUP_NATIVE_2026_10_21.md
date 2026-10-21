# Native font markup: real private ABI and delimiter control flow

`TextFont_parse_text_markup @ 0x00411FA0` now naturally receives font in EDX
and height output in ECX, with cursor/width output on the stack and RET8.
The selected definition is a genuine file-local stdcall in its real render
caller TU. Positive delimiter control flow replaces the previous normal-member
hypothesis. No register facade, fabricated fastcall declaration, padding,
noinline annotation or fake provider is used.

This is **not exact**: complete source1720/460 versus target1744/463 still
first differs at411FB0/+16, reserving788 versus796 bytes. Source full canonical
SHA256 is `b36c554885b583b2d656742e8ddaec679da167cc2ea6f638094cee2a7a1ecc50`.
Target main-body SHA256 remains
`6343d2d6639459aaeadb9de2acd74ecbb0be02f8a908e4b84af385f1daeccebb`.
No exact function/byte, source-present or origin denominator count changes.

Only original Japanese TH10.5 v1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is analyzed. Target/status/tracking preflights pass. IDA again rejects its wrong
open image; all target observations use the hash-attested raw PE.

## Observed target and actual source caller

The full1744-byte main span decodes463 instructions and ends at41266D with
RET8. The reviewed incoming call at41276A explicitly loads height output into
ECX, pushes width/cursor and moves font from ESI to EDX. The callee copies EDX
to ESI and saves ECX before native deque/string/token operations. A normal
ECX/RET12 source member was therefore an unverified nominal model.

Target branches forward to the missing-terminator strlen path near its end.
Its populated-token branch remains the main fallthrough. The source now says
`if (close) { ... return length + 1; } return strlen(cursor);`, preserving all
observed tag behavior and automatic native object lifetimes. In this real
caller context VC8's ordinary private optimization selects the target ABI.
The previous early-return local-function control's shared ESI/RET4 result
does not generalize to this control-flow shape.

The complete source caller is now323/115, canonical
`99116ccce2f7b9baed5d9ffec75ea16a348fc408797e0590288b35588ff2d8f8`, still
nonexact+0 against target326. Its one real E8 is at canonical41275E, with the
same native parameter roles; the callsite address is not equal to target41276A.
Height output persists in EBX across the loop. The body is not merely the old
322-byte caller with one operand changed. A retained actual COFF call witness
pins its symbol, relocation, entry roles, full source hash and RET8.

The unused parser member declaration is removed from the shared owner header;
no field, offset, vtable or other public declaration changes. Original nominal
class/function spelling and TU ownership remain unknown.

## Bounded controls and rejected assumptions

All controls use the same real rendering/provider source and pinned compiler.
Ordinary COFF keeps the existing local O2/Ob1 profile and GS; GL controls link
genuine owner/render source with the already validated native libraries and
ABS data/IAT bindings, without code stubs.

| Source context | Complete markup | Result |
| --- | ---: | --- |
| Previous ordinary member/early return |1647/444|normal ECX/RET12, frame788|
| Member with per-tag returns |1644/444|wrong ABI/frame|
| Positive delimiter member |1720/460|normal ECX/RET12, frame788|
| Positive member plus per-tag returns |1712/458|wrong ABI/frame|
| **Positive file-local stdcall** |**1720/460**|**native EDX font/ECX height/RET8**, frame788|
| Unsigned length / named allocation size |1720/460|identical positive member bytes|
| Return inside ruby lifetime |1720/460|native ABI, different slots, frame788 persists|
| Commuted return / preincrement length |1720/460|identical selected native bytes|
| Genuine complete GL, baseline |1497/391|EDX cursor, stack font/width, ECX height/RET8|
| Genuine complete GL, positive branch |1572/408|same wrong parameter roles, frame788|

The fully resolved GL controls establish neither the target ABI nor a
universal LTCG blocker. They inline the surface helper and are private
diagnostics; the selected ordinary COFF retains the actual exact helper call.
Control inputs are phase-scoped to baseline06c08b5, whose source/header snapshot
is retained. Replaying those controls after public-header changes requires the
frozen original headers; their old wrappers are not current public build units.

The remaining24-byte size gap is not permission to insert a local or padding.
Stack-slot allocation, length/allocation-size lifetimes, arithmetic/return
placement, destructor-state writes and internal alignment still differ.
These are observations to explain, not an assertion that only frame size is
left. Source and target FuncInfo both describe four states with the graph
`[-1,0,1,0]` and flags1. The four cleanup roles agree, but handler/funclet
offsets and metadata remain unqualified for canonical or runtime EH acceptance.
Moving a return into ruby scope does not remove the residual state write.

## Actual execution and minimal affected replay

All **8,640/8,640** complete target/source parent cases pass again because this
change rearranges the whole function and its entry ABI. Both sides now use
the observed EDX/ECX/two-stack contract. Actual byte-identical hex45 and
setter45 execute inside parent; setter executes192 times per side. Other
CRT/STL/font/color calls remain explicit observers. Coverage includes all
previous tags, unknown/missing delimiters, SSO/heap/empty/short tokens, stored
ASCII/SJIS/nonlead/embedded-NUL ruby text, signed dimensions/spacing, ruby
flags and optional output null/alias modes, including first invalid-index stops.
Expected trace digest:
`ace84c52d6df5492bed5861d8bb4db958f9fc589e0a7de1d61b6e1535cfe3460`.

All **280/280** affected whole-render-caller cases pass with the actual complete
289-byte blend, executed140 times per side. They cover flat/outline modes,
output null/alias modes, destination reload, lead-range boundaries, repeated
markup and missing terminators. Begin/end/glyph/markup/CRT calls inside this
caller remain ABI-specific observers. Callback failures are caught and raised
outside ctypes. No actual GDI, parent EH unwinding, allocation failure,
arbitrary-alias or protected-page read coverage is claimed.

The other nine complete font bodies are byte-identical, including the full
433-byte accent tail. Existing exact setter45, hex45 and blend289 persist.
Both accepted header consumers cold-build: font render and font owner retain
all prior exacts, including owner138/210/439/config67 and compiler-only Tidy71.
The nonaccepted texture consumer retains complete110/264 hashes. No unrelated
accepted-unit source/definition/flag/relocation input changes or aggregate cold
exact replay is claimed. The origin evidence text changes, not classification.

## Reproduction and retained state

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

Font render still intentionally reports comparison_failed: eight roots remain
nonexact and all three accepted leaves remain exact. Owner reports ok; texture
has its existing two nonexact candidates, without resolver failures.

Current formal reports, selected COFF, complete canonical bodies, caller/EH
facts and execution receipts are in `build/font-markup-local-20261021/`.
Private source recipes and baseline snapshot are under
`.analysis/font-markup-local-20261021/`. Completed unselected controls are
compressed only after per-file SHA256 archive readback; selected evidence stays
available. No generated binary/report is committed.

Next: explain actual stack-value lifetimes, destructor-state scheduling and
the8-byte frame residual with the now recovered entry/caller context. Glyph
coordinate ordering and Reimu496540/+31 remain open.
