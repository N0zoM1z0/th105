# Actual scenario-selection sprites, 2026-11-02

Target SHA-256: 56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

CSelectScenario now owns actual CSprite at +0x44, +0xDC and +0x21C,
and actual CTile at +0x174. The constructor uses actual virtual texture calls
instead of a partial six-slot class. Preview application uses the actual
set_texture_options call instead of reading and casting the vtable. Its complete
186-byte native body remains exact without preserving a manual table cache.
The constructor's CTile texture binding now names the already-qualified actual
provider at 0x4098B0; no call destination or compiler option changes.

All 13 accepted roots in 10 units remain exact in the 12-unit actual include
closure, including constructor 862, destructor 277, preview 186, update 247 and
scene entry 271 bytes. Seven other selected support/pending roots retain their
before/after hashes. Both affected scalar-origin gates pass, one 30-byte root
each. Whole constructor and destructor EH regions are 138 code + 108 metadata
bytes each, totaling 492 support bytes. The emitted vector cleanup at 0x435F90
matches all 42 bytes. Actual sprite RTTI covers 249 bytes and nine slots; tile
RTTI covers 247 bytes and four slots. These are separate graph extents with
shared ancestors, not additive authored credit.

The retained, unselected SelectScenarioRender.cpp also needed its tile call
adapted to the real signature. The raw native sequence at 0x424B83..0x424BB9
pushes the selected scenario as row, then zero as column, then y and x, before
calling 0x4099F0 at 0x424BB4. The source now calls render(x, y, 0, scenario).
The previous view declared render(int, int, float, float), which was not the
actual ABI. A private complete comparison now yields 757 source / 756 native
bytes, first mismatch at +125, and remains nonexact. No public match selector,
source-present ledger entry or new byte credit is added for that render body.
This does not resolve its loop scheduling and floating-point differences.

Private controls: .analysis/frontier-select-scenario-real-sprites-20261102/.
Receipts: build/frontier-select-scenario-real-sprites-20261102/.
Final CI passed all 962 tests in 110.932 seconds. Both diff checks gate the
local checkpoint. No target or generated
binary is committed. Counts remain 1426 exact / 443399 bytes, source 1636,
authored 1655, mapped 1826, excluded 2075, review 297 and units 813.
