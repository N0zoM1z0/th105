#include "battle/AnimationSpriteFrame.hpp"

namespace th105 {
struct SelectObjectTransformView : AnimationSpriteFrameView {
    void prepare_transform_41fad0();
};
void SelectObjectTransformView::prepare_transform_41fad0()
{
    const float pivot_x=static_cast<float>(frame_150->pivot_x_04);
    const float pivot_y=static_cast<float>(frame_150->pivot_y_06);
    sprite_004.sprite_000.reset_transform();
    sprite_004.sprite_000.translate(static_cast<float>(-sprite_004.object_facing_100)*pivot_x,-pivot_y,0.0f);
    sprite_004.sprite_000.translate(sprite_004.object_x_0e8,sprite_004.object_y_0ec,0.0f);
}
}
