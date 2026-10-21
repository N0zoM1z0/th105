# Text rendering: restore the observed packed input read

The selected `TextTextureFontView::render_text @ 412670` source now loads a
32-bit packed word on its multibyte path, then exchanges the low two bytes.
The preceding source read the lead byte and trail byte separately. Both gave
the same character on padded input, but the old read footprint did not match
the executable at a readable-page boundary. This is a source correction, not
new exact-match credit: the complete caller remains nonexact at entry.

All observations use original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
IDA preflight rejects the wrong open image and contributes no semantics.

## Target observations and selection

The complete326-byte target contains a byte lead read at412713. Its
81..9F/E0..FE multibyte path then executes `mov eax,[edi+ebx]` at412726:
**four bytes are read from the current input address**, including bytes beyond
the two-byte character. `movzx ecx,ah; mov ch,al; mov eax,ecx` forms the
character code. The single-byte path still sign-extends AL. The new source
models this actual load and byte packing without an ABI facade, assembly,
copied instructions, padding or a comparison exception. The original nominal
C++ load type/expression remains unknown.

The new native source emits a DWORD read followed by the observed AH/AL packing
operations. It remains324 bytes /116 instructions, canonical SHA256
`1daa6415e2c57413e20351792f7df526c42849c7c20536a1bcc8d4714a61f25d`,
versus target326 /120, and still first differs at+0 on frame/register context.
The preceding selected caller was323 /115, canonical99116ccc. A private
two-byte packed-load control happens to be326 bytes but emits a WORD read;
it fails the page-boundary observations below and is not selected. Target size
alone would have selected the wrong read behavior.

Public source SHA256 after selection is
`76e86737670ca41893c2b1940ae77e9f4254e863ae2424971a273634be3f66ca`.
Only this caller changes in the12-function font-render unit. All other11
complete canonical hashes/extents remain identical, including glyph624/a1f0b4e5,
markup1728/a3c2e09c and accepted surface45/hex45/blend289. The byte-equal
checked-character33 still has origin review and no authored credit. No shared
header, public layout, compiler profile, relocation binding, accepted match
row or authored-byte total changes.

## New guarded input evidence

[The input audit](../scripts/audit-text-font-input.py) executes the actual
target and canonical source caller instructions through first glyph/end entry
or an input read fault. It uses a flat font, null output pointers, a single
readable input page and checked begin/leaf ABI boundaries. The begin provider
returns through its observed RET0 contract; glyph and GDI are not executed.
Hook failures are raised outside the emulator callback. Fresh fault engines
are collected after each execution.

There are57 cases: representative boundaries in both multibyte ranges,
three trails, five single-byte leads, a truncated pair and empty input, at
aligned, unaligned and page-ending positions. Target fixture outcomes are
asserted so that an observer accidentally skipping decoding cannot yield a
vacuous pass.

| Source | Value/stop differences | Input-read trace differences |
| --- | ---: | ---: |
| Pre-correction selected323-byte caller |13 /57|39 /57|
| Two-byte packed-load326-byte control |13 /57|39 /57|
| Selected DWORD-load324-byte caller |0 /57|0 /57|

For example, `81 40 00` occupies the last three readable bytes. Target observes
its one-byte lead read and a four-byte packed read, then encounters the unmapped
next page at412726. The new source does the same at its DWORD instruction.
The old source instead reads the second byte and reaches glyph with8140.
Target and selected source have13 matching read-fault cases. These are actual
x86 instruction observations under Unicorn, not a Windows exception/unwinding
or whole-game execution claim.

## Full caller replay and retained providers

A separate fresh replay runs13,100 complete caller cases per side: all256
leads with five trails, flat/outlined modes, optional/aliased output dimensions,
and explicit post-end destination changes, plus mixed/tag/empty/truncated
strings. All outputs, ordered observer events, font/surface bytes and normal
ABI restoration agree. Each side executes the actual289-byte blend6,550 times.
All normal inputs in this replay are padded; the guarded read evidence is the
separate57-case audit, not an extrapolation from final output equality.

Begin/end/glyph/markup/CRT remain explicit observers in the caller replay.
The current private markup contract is used on both sides. The missing-close
observer returns the remaining strlen, matching the independently observed
parent branch; actual markup, real GDI, allocation failure, EH and arbitrary
aliasing are not qualified by this caller replay. Previous160/280/13,100-case
receipts retain their own source epochs.

The fresh public build reproduces the tested candidate's complete12 canonical
bodies, including the new caller hash above. Its three previously accepted
leaves persist. The source/runtime bridge therefore uses full emitted-body
equality, not source resemblance or a selected instruction window.

## Reproduction and retained evidence

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-text-font-render --compare --json
# Expected mixed comparison: caller324/+0, glyph624/+89, markup1728/+16.
taskset -c 0 nice -n 10 python3 scripts/audit-text-font-input.py \
  build/match-units/GptWeb_TextFontRender.obj --output build/font-input.json
```

Receipts are under `build/font-markup-homes-20261022/`: `formal.json`,
`input-formal.json`, `input-negative-control.json`, `input-footprint.json` and
`packed-caller-replay.json`. The frozen pre-correction COFF is
`pre-packed-render.obj`; running the same input audit on it exits1 with13
value/stop and39 read differences. Private recipes, frozen old source and
unselected packed-load controls are in the matching `.analysis/` directory.
All compilation/execution is serial at CPU0/nice10. Only the affected font
unit is rebuilt; no aggregate cold replay is claimed.

The associated [markup stack/context audit](FONT_MARKUP_STACK_HOMES_2026_10_22.md)
retains the8-byte frame question. The input correction does not make glyph,
markup or the full caller exact, or establish an original TU/compiler profile.
