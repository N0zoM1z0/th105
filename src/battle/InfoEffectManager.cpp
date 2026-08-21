#include "InfoEffectManager.hpp"

namespace th105 {

InfoEffectObjectView *InfoEffectManagerSpawnView::spawn_effect_46f460(
    int effect_id,
    float x,
    float y,
    unsigned char facing,
    unsigned char spawn_flag,
    int spawn_context)
{
    InfoEffectObjectView *object = object_pool_04().allocate_46f370();
    object->spawn_context_164() = spawn_context;
    object->manager_anchor_130() = manager_anchor_64();
    object->manager_anchor_160() = manager_anchor_88();
    object->set_effect_id_08(effect_id);
    object->x_ec() = x;
    object->y_f0() = y;
    object->facing_104() = facing;
    object->spawn_flag_16c() = spawn_flag;
    object->finalize_3c();
    return object;
}

void InfoEffectManagerSpawnView::load_effect_resource_and_preallocate_46f900(
    const char *path, unsigned target_count)
{
    load_effect_resource_437ec0(path);
    object_pool_04().preallocate_46f3d0(target_count);
}

} // namespace th105
