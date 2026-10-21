# Glyph arithmetic and compiler-context controls

Scope: `TextTextureFontView_draw_text_glyph @ 411B80`, original Japanese
TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Source selection, public types, compiler profiles, mappings and exact rows
remain unchanged. This checkpoint adds no exact or aggregate verification
claim. Fresh IDA preflight rejects the open image; only the attested PE is
used for target observations.

## Fresh complete baseline

The focused public font-render build reproduces all12 current canonical
hashes/extents. Glyph remains624 bytes, canonical SHA256
`a1f0b4e58a76926fa837cdd852256122752fea9e5c9226332fc02139a8ac7806`.
Current source SHA256 is
`b88ed013c517dc4dacdabe2a3089bc1dbc3ac256d939eddebb1f31c1733a4c13`.
The accepted surface45, hex45 and blend289 remain exact; the33-byte
checked-character operation remains byte-equal with origin review and no
authored credit. Other candidates remain nonexact.

Independent raw CFG inspection again closes the entire target624-byte span:
189 decoded instructions,187 reachable, RET12 at411DED, exclusive end411DF0.
The skipped7-byte LEA at411CD8 and one-byte NOP at411CDF remain in comparison.
Target SHA256 is
`3e67460ec4d76b1bdf2e30566a9dc74d44c3d34116e847e49ea78667bfb93630`.
Exactly14 bytes differ, all inside the16-byte window+88..103; the first is+89.
Target starts that calculation with ascent, subtracts originY, saves height
and adds cached cursorY. Source starts with cached cursorY, subtracts originY,
saves height and adds ascent. Every byte outside that window agrees.

## Isolated source and API controls

One earlier private `top.cpp` also reverted the two coverage loops to combined
postincrement expressions. That older file cannot by itself isolate the top
local's effect in the selected source. The current control therefore changes
only the real glyph-top calculation, leaving the current cursor/loop lifetimes
intact. This does not invalidate the separately recorded SDK/top-helper controls
at their own source epochs.

| Current-source control | Glyph result | Other11 complete bodies |
| --- | --- | --- |
| Real local `long glyph_top = ascent - originY`, used by bottom |624, identical canonical hash, nonexact+89|Identical hashes/extents|
| Cached ascent field uses signed long, consistent with TEXTMETRICA's ascent type |624, identical canonical hash, nonexact+89|Identical hashes/extents|
| Actual SDK GDI declarations, TEXTMETRICA, GLYPHMETRICS and MAT2, with typed handle conversions |624, identical canonical hash, nonexact+89|Identical hashes/extents|
| Pen-relative expression `cursorY + (ascent - originY) + height` |624, identical canonical hash, nonexact+89|Identical hashes/extents|

The long-ascent view is private; the external SDK type does not establish the
game's original cached member spelling. The SDK control replaces manual Win32
declarations rather than introducing a new ABI facade. Its native20-byte glyph
metrics,16-byte transform, origin8 and advance16 layouts are checked. Real COFF
transform symbols are read back and assigned the existing attested data roles;
no new game address or unknown executable target is mapped. All four controls
compile the complete current TU with the existing O2/Ob1/GS profile. None is
selected merely for equivalent behavior or type cleanliness.

## Compiler controls with explicit identities

Both compiler controls use the unchanged public source and fixed pinned SP1
CRT/SDK headers. They are private manual compilations, not public SP1-profile
build provenance. Commands, actual driver/front-end/back-end hashes, numeric
PE file versions, object hashes and all12 comparisons are recorded.

| Control | Glyph result | Whole font-unit observation |
| --- | --- | --- |
| SP1 O2/Ob1 plus `/Os` |579 bytes, nonexact at+0|All12 full-body comparison pairs change; private calling/frame behavior is unqualified|
| Driver, C1XX and C2 each report14.0.50727.42; same O2/Ob1/GS and SP1 headers |624, same canonical hash and+89|All12 hashes/extents unchanged|

The .42 binaries are independently distinguished from the selected
14.0.50727.762 tools. Driver SHA256 is
`3cbf4306526c06a07d09fd4785ac290c7ac7b52355944e7b377e08f5d8e7ece7`,
C1XX is `e4890058a1f928538b27246af1f5c6f95551fc0ad380639b1bf1d6b143b80d09`,
and C2 is `ebca6ef587d6e028b50cc79fe71dd6155230ecb51014295399e8f00e8865ff86`.
These establish which installed compiler binaries ran. They do not prove the
original game's exact compiler release, installation provenance, headers or
project settings. The installed directory name and old RTM-labelled reports
are not substituted for these fresh identities.

## Receipts and remaining work

All work is serial at CPU0/nice10. No runtime sweep is repeated for the
byte-identical source/backend controls. The size control is not selected or
presented as runtime equivalent. Prior glyph/GDI observer receipts retain
their actual source epochs and limits; real GDI, allocation failure, EH and
arbitrary aliasing remain unqualified.

Private recipes are `.analysis/font-glyph-arithmetic-20261022/capture.py`,
`probe.py`, `compiler_controls.py` and `archive_controls.py`. Complete receipts under the matching
`build/` directory are `baseline-formal.json`, `baseline-facts.json`,
`local-top.json`, `sdk-ascent.json`, `sdk-gdi.json`, `pen-first.json`,
`prefer-size.json` and `backend-50727-42.json`, plus compiler logs and objects.
The original [native ABI evidence](TEXT_FONT_GLYPH_NATIVE_2026_10_21.md) and
[SDK layout checkpoint](FONT_GLYPH_SDK_TYPES_2026_10_21.md) remain valid at
their recorded epochs.

After all comparisons, the six unselected private COFFs are losslessly archived
as `completed-control-objects.tar.gz`:501,853 bytes become122,830. Each archived
member is read back and checked against its build SHA256 before removing its
loose copy; `control-object-archive.json` records every hash. Current public
baseline COFF, sources/recipes, toolchains and all receipts remain loose.
Restore the private objects with:

```bash
tar -xzf build/font-glyph-arithmetic-20261022/completed-control-objects.tar.gz \
  -C build/font-glyph-arithmetic-20261022
```

These specific source/API/backend controls do not explain the residual. They
prove neither a general standalone-object impossibility nor an LTCG requirement.
Keep the current source. Further changes need an independent caller, lifetime
or original compilation-context lead rather than more equivalent-expression
enumeration. Glyph remains nonexact; markup411FA0 remains nonexact+16 with its
separate frame/lifetime question.
