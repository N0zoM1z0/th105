# Actual title constructor sprites, 2026-11-02

Target SHA-256: 56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

TitleConstructorRuntime.cpp now uses the shared global CSprite / CTile classes.
The local SceneSpriteColorBase and incomplete sprite/tile classes are removed.
The false eight-slot tile declaration is replaced by the real four-slot class.
Texture option binding now names the existing actual CTile provider at 0x4098E0.
The constructor-facing outer Title view, resource view and texture locals are
unchanged; this does not claim unified outer CTitle linkage or original TU layout.

The one directly affected unit preserves the canonical 577-byte constructor at
0x425DF0, SHA-256
abd6cbfcdcaaf1fe5e19bb3719e72161339170f3a0400b54bac4304a6e731013.
The complete 616-byte owned section is also canonical: the callable body ends
with RET, followed by three bytes of alignment and a nine-entry / 36-byte switch
table. All nine targets resolve within the callable body. Those trailing data
bytes are not additional authored code credit.

Actual sprite RTTI 249 bytes / nine slots and tile RTTI 247 bytes / four slots
pass. Complete constructor EH is 88 code + 76 metadata bytes, also exact.
There are no manual vptr writes, copied instruction bodies, inert locals,
compiler flag changes or forced inlining boundaries. No origin/ledger changes.

Private controls and receipts: .analysis/frontier-title-real-sprites-20261102/
and build/frontier-title-real-sprites-20261102/. Final CI passed all 962 tests in
139.882 seconds. Both diff checks gate the local checkpoint. Totals remain 1426 exact / 443399 bytes, source 1636,
authored 1655, mapped 1826, excluded 2076, review 296 and units 813.
