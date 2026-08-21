#include "InfoEffectEmitter.hpp"

namespace th105 {

int InfoEffectEmitterView::emit_effect(
    int effect_id, float x, float y, int flag_a, int flag_b)
{
    return emitter_04.emit(effect_id, x, y, flag_a, flag_b, 0);
}

} // namespace th105
