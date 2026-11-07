#include "CharacterObjectEffects.hpp"
#include "AnimationSequenceVirtuals.hpp"

#include <map>

namespace th105 {

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
    AnimationSequenceBlock *const block =
        sequence_tree_160->find(key)->second;
    AnimationSequenceFrame &frame = block->records_00[0];
    secondary_renderer_338->initialize(
        reinterpret_cast<SecondaryAnimationOwnerRuntimeView *>(this),
        reinterpret_cast<const SecondaryAnimationFrameRuntimeView *>(&frame),
        half_width, subdivision_count, band_count, blend_mode);
}

} // namespace th105
