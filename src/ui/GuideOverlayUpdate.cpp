#include "../battle/EffectSprite.hpp"
#include "GuideOverlay.hpp"
namespace th105 {

void GuideOverlay::update()
{
    scroll_9c += 0.5;
    if(scroll_9c>wrap_width_a0)scroll_9c-=wrap_width_a0;
    if(visible) {
        if(alpha_a4>=255)return;
        sprite_08.set_color((static_cast<unsigned>(alpha_a4+=15)<<24)|0xffffff);
    } else {
        if(alpha_a4==0)return;
        sprite_08.set_color((static_cast<unsigned>(alpha_a4-=15)<<24)|0xffffff);
    }
}
}
