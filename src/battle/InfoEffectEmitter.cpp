#include "InfoEffectEmitter.hpp"

namespace th105 {

InfoEffectObject *InfoEffectEmitterView::emit_effect(
    int effect_id, float x, float y, int flag_a, int flag_b)
{
    return emitter_04.spawn_effect(effect_id, x, y,
        static_cast<unsigned char>(flag_a), static_cast<unsigned char>(flag_b), 0);
}

} // namespace th105
