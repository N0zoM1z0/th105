#include "CharacterObjectEffects.hpp"
#include "AnimationSequenceVirtuals.hpp"

#include <map>

namespace th105 {

struct AnimationSequenceBlockVectorView {
    std::vector<AnimationSequenceFrame> frames_00;
    unsigned int unknown_10;
    unsigned char mode_14;
    unsigned char unknown_15[3];
    void *previous_18;
    void *next_1c;
};

typedef std::map<int, AnimationSequenceBlockVectorView *> SecondarySequenceMap;
typedef char CheckSecondarySequenceMapSize[sizeof(SecondarySequenceMap) == 0x0c ? 1 : -1];
typedef char CheckAnimationSequenceBlockVectorViewSize[
    sizeof(AnimationSequenceBlockVectorView) == 0x20 ? 1 : -1];

void CharacterObjectEffectEmitter::replace_secondary_animation(
    int key, float half_width, int subdivision_count,
    int band_count, int blend_mode)
{
    {
        if (secondary_renderer_338)
            delete secondary_renderer_338;
        secondary_renderer_338 = new SecondaryAnimationRenderRuntimeView;
    }

    key = static_cast<short>(key);
    // A real temporary checked iterator lets VC8 reuse the completed new
    // expression's cleanup slot. An explicit out-parameter facade does not.
    AnimationSequenceBlockVectorView *const block =
        reinterpret_cast<SecondarySequenceMap *>(sequence_tree_160)->find(key)->second;
    AnimationSequenceFrame &frame = block->frames_00[0];
    secondary_renderer_338->initialize(
        reinterpret_cast<SecondaryAnimationOwnerRuntimeView *>(this),
        reinterpret_cast<const SecondaryAnimationFrameRuntimeView *>(&frame),
        half_width, subdivision_count, band_count, blend_mode);
}

} // namespace th105
