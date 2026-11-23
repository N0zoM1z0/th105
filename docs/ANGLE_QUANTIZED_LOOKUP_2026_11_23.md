# Quantized orientation lookup recovery — 2026-11-23

Target: Japanese TH10.5 1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.

## Recovered source shape

The two authored helpers at `0x00406360` and `0x004063D0` now have natural
C++ candidates that reproduce their complete target bodies. Both return
`float`, read the game-owned 3600-entry `g_orientation_cosine_table`, round
through the SDK float `abs` overload, and use the same checked index shape:

```cpp
float magnitude = phase * 10.0f - 900.0f; // sine; cosine omits the subtraction
magnitude = abs(magnitude);
__declspec(align(64)) int index = static_cast<int>(magnitude + 0.5f);
int divisor = 3600;
return g_orientation_cosine_table[index % divisor];
```

The non-const local divisor is important. With the constant expression
`index % 3600`, VC8 chooses a magic-constant remainder sequence. With the
ordinary local `int divisor = 3600`, the same compiler naturally emits the
target's `CDQ / MOV ECX, 0xE10 / IDIV ECX` sequence. The aligned integer local
naturally accounts for the target's 64-byte stack alignment; no assembly,
inline instruction bytes, padding, or artificial live-value use is present.

The unit uses the explicit `vc8-sp1-probe-o2-fp-strict-noexcept` profile
(`/fp:strict /fp:except-`) because the target calls `__ftol2_sse`, not the
exception-sensitive conversion helper. The source keeps the corresponding
local `float_control(except, off, push/pop)` scope.

## Focused comparison

`cross-v106a-angle-lookup` builds all four functions from one translation
unit. The fresh focused comparison reports:

| Target | Function | Result |
| --- | --- | ---: |
| `0x00406360` | `lookup_orientation_sine_quantized_abs` | 100/100 |
| `0x004063D0` | `lookup_orientation_cosine_quantized_abs` | 94/94 |
| `0x00406480` | `lookup_orientation_sine` | 34/34 |
| `0x004064B0` | `lookup_orientation_cosine` | 30/30 |

The separate `exact-first-angle-tangent` unit remains 69/69 after updating
its helper declarations to the recovered float return type.

A double-return candidate with otherwise corresponding source shape fails:
its scratch slot moves from `ESP+0x44` to `ESP+0x40` and the body grows by
eight bytes. The float return is therefore the supported source contract for
this VC8 reconstruction. This is not a claim that the original source used
this exact variable spelling or that the reason for its alignment attribute
has been uniquely recovered.

## Authored origin boundary

The existing target-pinned caller census independently classifies both
addresses as `authored_game`: the helpers are called directly by all fifteen
RTTI-owned roster Object `+0x28` action roots (295 sine and 205 cosine calls)
and index the game-owned orientation table at `0x006FE8B0`. This recovery
changes neither that origin classification nor the function extents. It
replaces the prior nonexact source hypotheses with a complete codegen match.

Canonical factory acceptance is tracked separately from this focused local
object comparison. The large callers remain independent reconstruction
scopes; this leaf result does not grant exactness to any caller root.
