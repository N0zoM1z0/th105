#include "EffectManager.hpp"
#include "EffectSpawnObjectView.hpp"


template <typename ObjectType>
ObjectType *CEffectManager<ObjectType>::spawn_effect(
    int effect_id, float x, float y, unsigned char facing,
    unsigned char spawn_flag, int spawn_context)
{
    ObjectType *object =
        TObjectManagerBase<ObjectType, EffectObjectBase>::acquire_and_link_object();
    th105::EffectSpawnObjectView *view = reinterpret_cast<th105::EffectSpawnObjectView *>(object);

    view->spawn_context_164 = spawn_context;
    view->manager_anchor_130 =
        reinterpret_cast<unsigned char *>(this) + 0x64;
    view->manager_anchor_160 =
        reinterpret_cast<unsigned char *>(this) + 0x88;
    view->set_effect_id_08(effect_id);
    view->x_0ec = x;
    view->y_0f0 = y;
    view->facing_104 = facing;
    view->spawn_flag_16c = spawn_flag;
    view->finalize_3c();
    return object;
}


#define TH105_INSTANTIATE_EFFECT_SPAWN(ObjectType) \
    template ObjectType *CEffectManager<ObjectType>::spawn_effect( \
        int, float, float, unsigned char, unsigned char, int)

TH105_INSTANTIATE_EFFECT_SPAWN(CSelectObject);
TH105_INSTANTIATE_EFFECT_SPAWN(WeatherEffectObject);
TH105_INSTANTIATE_EFFECT_SPAWN(EffectObject);

#undef TH105_INSTANTIATE_EFFECT_SPAWN
