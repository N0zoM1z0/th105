#include "../battle/EffectSprite.hpp"
#include "GuideOverlay.hpp"
namespace th105 {
// Typed color virtual of the existing CSprite object, without vptr writes.
class GuideSprite94 : public IColor {
public:
 virtual ~GuideSprite94();
 virtual void set_color(unsigned);
 virtual void set_vertex_colors(const unsigned *);
 virtual void multiply_color(unsigned);
 virtual void set_texture_options(unsigned,int,int,unsigned,unsigned,int,int);
 virtual void set_texture(unsigned,int,int,int,int);
 virtual void slot_18();
 virtual void render(float,float);
 SpriteVertex28 vertices_08[4];
 float width_78,height_7c,extension_80[5];
};
typedef char GuideSpriteSize[sizeof(GuideSprite94) == 0x94 ? 1 : -1];

void GuideOverlay::update()
{
    scroll_9c += 0.5;
    if(scroll_9c>wrap_width_a0)scroll_9c-=wrap_width_a0;
    if(visible) {
        if(alpha_a4>=255)return;
        reinterpret_cast<GuideSprite94 *>(&sprite_08)->set_color((static_cast<unsigned>(alpha_a4+=15)<<24)|0xffffff);
    } else {
        if(alpha_a4==0)return;
        reinterpret_cast<GuideSprite94 *>(&sprite_08)->set_color((static_cast<unsigned>(alpha_a4-=15)<<24)|0xffffff);
    }
}
}
