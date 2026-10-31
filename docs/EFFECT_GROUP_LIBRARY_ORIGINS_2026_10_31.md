# Original effect-group deque library origins

The actual32-byte EffectResourceGroup declaration and original unmodified VC8
headers reproduce three complete target library implementations:

- 422770,341 bytes: deque map growth.
- 422E00,117 bytes: std placement construction using the implicit group copy.
- 4505A0,60 bytes: deque pop_front with actual virtual element destruction.

All three match complete canonical bytes in unit vc8-effect-group-deque-origin,
total518 bytes. The fresh compiler object contains no trailing alignment cuts
for these anchors. The provenance rule independently verifies full native body
hashes, minimum unmasked coverage and uniqueness across the entire inventory,
not merely among review rows. Unchanged existing census evidence is retained.

The growth implementation's real seven direct calls resolve to449940,439580,
four memmove_s calls and scalar delete6898EA. Placement construction binds the
actual group vtable and original117-byte body's handler, then invokes the
already-proven FrameData vector copy4228D0. The full pop_front witness has no
relocation fields to ignore.

These establish original standard-library/compiler implementation families.
The shared map-growth code and generic virtual-destruction pop_front pattern
do not prove that their original template argument was uniquely this nominal
element type. The placement-copy source is also implicitly generated, not a
new authored copy body. No hand-written copy loop or target machine bytes are
part of the source probe.

Public source: scripts/probes/EffectGroupDequeOrigin.cpp.
Anchors: config/vc8-effect-group-deque-origin-anchors.toml.
Rule: vc8-generated-effect-group-deque-106a.
Private receipts: build/frontier-effect-group-library-20261031/formal.json and
the focused rule validation under build/frontier-boost-library-20261031.

The census gains three exclusions/518 bytes only: excluded1658, review594,
units751. Authored exact1558/444502, source1755/authored1775/mapped1782 remain
unchanged. No helper inflation.
