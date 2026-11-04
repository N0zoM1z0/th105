# Sprite rectangle render4070C0

Complete153/native153 strict-FP candidate remains nonexact at+16; no exact or
source-selection credit. Receipt build/frontier-4070c0-20261028/strict-fp.json.
Target SHA:1ae97c5fd56570a9684bcfde50d194a07e6b00e931a745ea4f918938452afb5f.

Current sprite/gauge virtual slot18 supplies four float rectangle edges. Source
writes the eight actual vertex X/Y fields with half-pixel subtraction, binds
resource04, sets FVF324 and draws a two-primitive triangle strip of28-byte
vertices. It reuses the actual CSpriteBase storage and existing D3D interface;
no manual virtual dispatch or geometry byte recipe is added.

Default O2 produces161 bytes, first+5, promoting the half-pixel constant to a
double and changing repeated x87 evaluation. The existing strict-FP profile,
already evidenced by adjacent gauge rendering, recovers native single-precision
half-pixel pooling and153-byte length. The remaining first residual is resource
handle load scheduling: fresh loads it before vertex writes while native loads
after them. No fake alias barrier, volatile handle, invented accessor or forced
register is used to delay the load. Equal length is not exactness.

The canonical render-manager device-base alias validates the genuine+4 device
cell; no global allowance is broadened. Complete CFG boundary is audited beside
the focused receipts. Shared headers and existing consumers remain unchanged.

## Source registration, 2026-11-04

The complete existing implementation is now source-present and authored.
The current CSprite RTTI table pins its `0x006C0680` virtual slot, the full
native body and the texture-binding call. A fresh strict-FP build reproduces
153/native153 with first difference +16, so no exact credit is claimed.
Receipt: `build/frontier-sprite-rectangle-register-20261104/formal.json`.
