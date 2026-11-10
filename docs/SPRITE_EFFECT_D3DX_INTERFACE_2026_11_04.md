# Sprite effect calls through the shared D3DX interface

The RGB, alpha/RGB, luma and luma/alpha sprite effect bodies now use the shared
`D3DXEffectInterface` for their observed COM calls instead of a hand-declared
vtable structure. Their stable v4Arg0/v4Arg1 vector calls and effect-method
slot order agree with the D3DX-compatible interface already used by the exact
battle overlay. The concrete runtime service type and original source spelling
remain unknown.

The typed global pointer has a new C++ symbol spelling; each affected unit
maps it locally to the existing verified loader-zero service address `6FD398`.
The address, shared relocation allowlist, effect call order, vector lifetimes
and draw behavior are unchanged. No manual vtable writes or new implementation
of D3DX is introduced.

Fresh whole-body comparisons remain canonical exact for `6654D0` (199),
`6655A0` (173), `665650` (140) and `6656E0` (248). This is source/interface
cleanup, not four new matches or additional exact bytes. The exact
`435540` caller is also replayed. The existing `4666A0` overlay and five
reset/lifetime roots were separately rechecked against the shared interface;
no actual D3D or gameplay execution is claimed.

Reproduce with the `cross-v106a-sprite-render-effects`,
`cross-v106a-sprite-render-luma-alpha` and `cross-v106a-animation-render-color`
units.
