#include "AnimationAuxiliarySprite.hpp"
#include "SpriteTextureSetup.hpp"

#include <map>

namespace th105 {

struct AuxiliarySpriteFrameView {
    unsigned char unknown_00[4];
    short frame_x_04;
    short frame_y_06;
    short duration_08;
    short texture_index_0a;
    short source_x_0c;
    short source_y_0e;
    short width_10;
    short height_12;
    unsigned char unknown_14[0x74];
};

struct AuxiliarySpriteSequenceBlockView {
    std::vector<AuxiliarySpriteFrameView> frames_00;
    unsigned char unknown_10[0x10];
};

typedef std::map<int, AuxiliarySpriteSequenceBlockView *> AuxiliarySpriteSequenceMap;
typedef char AuxiliarySpriteFrameView_size[
    sizeof(AuxiliarySpriteFrameView) == 0x88 ? 1 : -1];
typedef char AuxiliarySpriteSequenceBlockView_size[
    sizeof(AuxiliarySpriteSequenceBlockView) == 0x20 ? 1 : -1];

void AnimationAuxiliarySpriteOwnerView::replace_auxiliary_sprite(short resource_id)
{
    if (aux_renderer_154)
        delete aux_renderer_154;
    aux_renderer_154 = new AuxiliarySpriteRuntimeView;

    // The checked iterator remains alive through the frame access. Splitting
    // off a sequence pointer changes its lifetime and the target stack reuse.
    AuxiliarySpriteFrameView &frame =
        reinterpret_cast<AuxiliarySpriteSequenceMap *>(sequence_tree_160)->
            find(resource_id)->second->frames_00[0];
    int const height = frame.height_12;
    int const width = frame.width_10;
    int const y = frame.source_y_0e;
    int const x = frame.source_x_0c;
    unsigned const texture = texture_handles_130->at(frame.texture_index_0a);
    reinterpret_cast<SpriteTextureSetupView *>(
        &aux_renderer_154->sprite_000)->set_texture_options(
            texture, x, y, width, height, 0, 0);
    aux_renderer_154->frame_x_f0 = frame.frame_x_04;
    aux_renderer_154->frame_y_f4 = frame.frame_y_06;
    aux_renderer_154->field_fc = 1.0f;
    aux_renderer_154->field_f8 = 1.0f;
    aux_renderer_154->angle_100 = 0.0f;
}

} // namespace th105
