#include "AnimationAuxiliarySprite.hpp"
#include "SpriteTextureSetup.hpp"

#include <map>

namespace th105 {

void AnimationAuxiliarySpriteOwnerView::replace_auxiliary_sprite(short resource_id)
{
    if (aux_renderer_154)
        delete aux_renderer_154;
    aux_renderer_154 = new AuxiliarySpriteRuntimeView;

    // The checked iterator remains alive through the frame access. Splitting
    // off a sequence pointer changes its lifetime and the target stack reuse.
    PatRecord88 &frame =
        sequence_tree_160->find(resource_id)->second->records_00[0];
    int const height = static_cast<short>(frame.texture_height_bits_12);
    int const width = static_cast<short>(frame.texture_width_bits_10);
    int const y = static_cast<short>(frame.texture_y_bits_0e);
    int const x = static_cast<short>(frame.texture_x_bits_0c);
    unsigned const texture = texture_handles_130->at(static_cast<short>(frame.texture_index_bits_0a));
    aux_renderer_154->sprite_000.set_texture_options(
            texture, x, y, width, height, 0, 0);
    aux_renderer_154->frame_x_f0 = static_cast<short>(frame.pivot_x_bits_04);
    aux_renderer_154->frame_y_f4 = static_cast<short>(frame.pivot_y_bits_06);
    aux_renderer_154->field_fc = 1.0f;
    aux_renderer_154->field_f8 = 1.0f;
    aux_renderer_154->angle_100 = 0.0f;
}

} // namespace th105
