# Battle effect device reset callbacks, 2026-10-28

Both complete callbacks are canonical exact21/21 in the original Japanese
TH1051.06a target: 418070 forwards OnLostDevice; 418090 forwards OnResetDevice.
The target executable SHA256 remains
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

## Ownership and boundary

The independently exact BattleBaseEffect constructor417FB0 publishes vtable
6D6CD0 and clears its sole resource pointer at+4. The two vtable cells contain
418070/418090. The exact BattleObjectManager owner contains this8-byte effect
member at+40; the existing initializer produces the resource via D3DXCreateEffect.
This is authored resource reset policy, not generic compiler-generated code.

Each root has eight reachable instructions covering all21 bytes, a null guard,
an ordinary COM call and RET0. Eleven following INT3 bytes separate the next
function. Body SHA256 values:

- 418070: c57bd857e4994dcec912cb2137f2fbdd8abba72595017fcb7861540d1151c8e2
- 418090: 23b3dc136db25a3669adb06a7596bb63956e5bc01d4f9cb2db013695de4f8a34

The non-null path loads the resource vptr and calls slot114/118, pushing the
resource receiver. The installed MinGW d3dx9effect.h independently places
ID3DXEffect OnLostDevice/OnResetDevice at zero-based slots69/70 and declares
HRESULT stdcall with no explicit parameters. The ordinary declaration-only
interface prefix records those actual API contracts; the target proves the
used slots and pointer lifetime. No full resource allocation or private ABI is
asserted. No target bytes, manual vtable loads or forced reloads are used.

## Focused replay

The two definitions are added to the existing
src/battle/BattleBaseEffectLifetime.cpp and its existing unit
`gpt-web-battle-base-effect-lifetime`. The original UnknownInterface resource
field, class size and constructor/destructor contracts remain unchanged.

Focused six-function comparison gives:

- constructor417FB0 exact16, destructor417FC0 exact33, shutdown418040 exact33,
  all unchanged accepted consumers;
- new reset callbacks418070/418090 exact21 each;
- initialize417FF0 retains its known first difference+17, ordinary ECX versus
  original-TU EAX listener-registration receiver. This pre-existing nonexact
  result prevents describing the entire unit as all-exact.

Receipts: build/frontier-418070-20261028/formal-build.json and boundary.json.
Only the two new complete callbacks add42 exact authored bytes; all other
accepted native receipts remain incremental. No aggregate cold build was run.
