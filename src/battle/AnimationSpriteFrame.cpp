#include "AnimationSpriteFrame.hpp"
#include "SpriteTextureSetup.hpp"

namespace th105 {

void AnimationSpriteFrameView::apply_current_frame()
{
    int texture_height = frame_150->texture_height_12;
    int texture_width = frame_150->texture_width_10;
    int texture_y = frame_150->texture_y_0e;
    int texture_x = frame_150->texture_x_0c;
    unsigned texture = texture_handles_130->at(frame_150->texture_index_0a);
    SpriteTextureSetupView *sprite =
        reinterpret_cast<SpriteTextureSetupView *>(&sprite_004);
    sprite->set_texture_options(
        texture, texture_x, texture_y, texture_width, texture_height, 0, 0);
    sprite->reset_transform();

    switch (frame_150->render_mode_14) {
    case 0:
        sprite->scale_x(2.0f);
        sprite->scale_y(2.0f);
        break;

    case 2: {
        AnimationSpriteFrame *frame = frame_150;
        sprite->scale_xyz_pivots(
            frame->transform_18->scale_x_08,
            frame->transform_18->scale_y_0c,
            frame->transform_18->scale_z_10,
            frame_150->pivot_x_04, frame_150->pivot_y_06, 0.0f);
        sprite->rotate_xyz(
            frame->transform_18->angle_x_14,
            frame->transform_18->angle_y_18,
            frame->transform_18->angle_z_1c,
            frame_150->pivot_x_04, frame_150->pivot_y_06, 0.0f);
        break;
    }
    }

    sprite->commit_transform();
}

} // namespace th105
