#include "FighterSequenceEffect.hpp"

namespace th105 {

void FighterSequenceEffectView::reset_and_set_color()
{
    reset_count_9c = 0;
    reset_y_a4 = -640.0f;
    reset_count_a0 = 0;
    reset_alpha_a8 = 0x80;
    sprite_04.set_color(0x80ffffff);
}

} // namespace th105
