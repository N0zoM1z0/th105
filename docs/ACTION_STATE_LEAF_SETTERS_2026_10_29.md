# Action-state leaf setters

Both complete native bodies replay canonical exact in
`exact-first-action-state-leaf-setters`, using ordinary C++ pointer-only views
in `src/battle/ActionStateLeafSetters.cpp`. No shared header or accepted caller
changes. Target SHA256 remains
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.

## Fighter counter4776C0

All15 bytes are MOV AX,[ESP+4], MOV [ECX+48A],AX and RET4, followed by one INT3.
SHA256 `e8b377d97bc2eb752064aa91e131e78a1fe7866dcb432cba1f5b03317517163f`.
Reimu action root478FA0 calls at488670 with the current Fighter receiver and40;
Suika598990 does so at5A2DCF. Fresh RTTI readback closes the root ownership:
Reimu vtable6C412C slot28/cell6C4154 and Suika vtable6C5B8C slot28/cell6C5BB4.
These are game-state field writes, not inferred library ownership from size.
The setter stores the low16 input bits. Short signedness and nominal return type
are not uniquely recoverable from those instructions; observed callers discard
any residual return. The source uses a conventional void short setter and does
not claim the entire Fighter allocation or the precise gameplay timer name.

## Scenario result4547D0

All4 bytes set receiver byte+0 to1 and return, followed by12 INT3 bytes.
SHA256 `834ffb2105774a3033265ade794f37611ca4e42257511bcaba49fa784b52fcbe`.
The reviewed CScenarioData interpreter458440 calls it at459B8D. Native458966
forms receiver+390 and45896E retains that pointer in the local used at459B89.
This is the already established ScenarioResultResource member at+390, whose
state byte is+0, rather than a new polymorphic object or constructor inference.
Its existing update/hide/reset methods establish the surrounding state layout.
The narrow leaf source simply enables that state, without adding a phase reset
or counter write absent from the native function.

Focused proof: `build/frontier-4776c0-20261029/formal-build.json` compares both
full functions; `boundary.json` retains complete instructions, body hashes,
alignment and caller RTTI/field facts. Only19 newly exact authored bytes are
credited. Neither large caller becomes exact as a consequence.
