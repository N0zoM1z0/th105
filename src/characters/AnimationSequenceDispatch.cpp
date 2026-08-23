#include "AnimationSequenceVirtuals.hpp"

#include "battle/Collision.hpp"

namespace th105 {

struct OpaqueWaveHandleService {
    unsigned char opaque_00[0x68];
    void dispatch_wave_handle(unsigned handle);
};
struct SceneRendererView;
extern OpaqueWaveHandleService g_wave_handle_service;
extern SceneRendererView *g_scene_renderer;

void AnimationSequenceObjectView::dispatch_character_wave_handle(unsigned index)
{
    if (index <= 0x3f)
        g_wave_handle_service.dispatch_wave_handle(wave_handles_164[index]);
}

void AnimationSequenceObjectView::forward_hit_quantity(
    int quantity,
    int scalar_per_thousand,
    short forwarded_counter_delta,
    signed char use_dynamic_scalar)
{
    reinterpret_cast<CollisionContext *>(g_scene_renderer)->
        apply_forwarded_quantity_to_pair(
            reinterpret_cast<AttackCandidate *>(this),
            reinterpret_cast<Fighter *>(related_170),
            quantity,
            scalar_per_thousand,
            forwarded_counter_delta,
            use_dynamic_scalar);
}

} // namespace th105
