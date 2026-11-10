#include "InfoEffectManager.hpp"
#include "EffectManager.hpp"

template <>
InfoEffectObject *CEffectManager<InfoEffectObject>::spawn_effect(
    int effect_id, float x, float y, unsigned char facing,
    unsigned char spawn_flag, int spawn_context)
{
    InfoEffectObject *object =
        TObjectManagerBase<InfoEffectObject, EffectObjectBase>::acquire_and_link_object();
    th105::InfoEffectObjectView *view =
        reinterpret_cast<th105::InfoEffectObjectView *>(object);
    view->spawn_context_164 = spawn_context;
    view->manager_anchor_130 = reinterpret_cast<unsigned char *>(this) + 0x64;
    view->manager_anchor_160 = reinterpret_cast<unsigned char *>(this) + 0x88;
    view->set_effect_id_08(effect_id);
    view->x_0ec = x;
    view->y_0f0 = y;
    view->facing_104 = facing;
    view->spawn_flag_16c = spawn_flag;
    view->finalize_3c();
    return object;
}

namespace th105 {

void InfoEffectManagerSpawnView::load_effect_resource_and_preallocate_46f900(
    const char *path, unsigned target_count)
{
    load_effect_resource_437ec0(path);
    object_pool_04().preallocate_46f3d0(target_count);
}

} // namespace th105
