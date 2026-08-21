#include "EffectManager.hpp"


struct EffectSpawnObjectView {
    virtual void slot_00();
    virtual void slot_04();
    virtual void set_effect_id_08(int effect_id);
    virtual void slot_0c();
    virtual void slot_10();
    virtual void slot_14();
    virtual void slot_18();
    virtual void slot_1c();
    virtual void slot_20();
    virtual void slot_24();
    virtual void slot_28();
    virtual void slot_2c();
    virtual void slot_30();
    virtual void slot_34();
    virtual void slot_38();
    virtual void finalize_3c();
};


template <typename ObjectType>
ObjectType *CEffectManager<ObjectType>::spawn_effect(
    int effect_id, float x, float y, unsigned char facing,
    unsigned char spawn_flag, int spawn_context)
{
    ObjectType *object =
        TObjectManagerBase<ObjectType, EffectObjectBase>::acquire_and_link_object();
    unsigned char *bytes = reinterpret_cast<unsigned char *>(object);
    EffectSpawnObjectView *view = reinterpret_cast<EffectSpawnObjectView *>(object);

    *reinterpret_cast<int *>(bytes + 0x164) = spawn_context;
    *reinterpret_cast<void **>(bytes + 0x130) =
        reinterpret_cast<unsigned char *>(this) + 0x64;
    *reinterpret_cast<void **>(bytes + 0x160) =
        reinterpret_cast<unsigned char *>(this) + 0x88;
    view->set_effect_id_08(effect_id);
    *reinterpret_cast<float *>(bytes + 0xec) = x;
    *reinterpret_cast<float *>(bytes + 0xf0) = y;
    bytes[0x104] = facing;
    bytes[0x16c] = spawn_flag;
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
