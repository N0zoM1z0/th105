#include "Collision.hpp"

namespace th105 {

void CollisionContext::emit_effect_at_collision_center(
    int effect_code,
    int direction)
{
    EffectSink *sink = *reinterpret_cast<EffectSink **>(0x006e6250);
    sink->emit_effect(
        effect_code,
        static_cast<float>(extent_1c + extent_24) * 0.5,
        -static_cast<float>(extent_20 + extent_28) * 0.5,
        direction,
        1,
        0);
}

} // namespace th105
