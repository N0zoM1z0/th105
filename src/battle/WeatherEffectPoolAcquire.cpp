#include "characters/TObjectManagerBase.hpp"
#include "battle/EffectObjectHierarchy.hpp"
#include "battle/EffectSprite.cpp"
#include "battle/FighterActionScratch.cpp"
#include <new>

// Complete allocation extents observed at 437520/4379D0. The inherited
// hierarchy supplies the native primary vptr and +158/+15C handle state.
// Unknown tail storage is left uninitialized, as in the target.
class WeatherEffectObject : public EffectObjectBase {
public:
    unsigned char unknown_170[0x10];
};
class EffectObject : public EffectObjectBase {
public:
    unsigned char unknown_170[8];
};
typedef char WeatherSize[sizeof(WeatherEffectObject)==0x180?1:-1];
typedef char EffectSize[sizeof(EffectObject)==0x178?1:-1];
namespace {
struct EffectObjectHandle { unsigned short slot; unsigned short generation; };
class PoolLockGuard {
public:
    PoolLockGuard(th105::CriticalSectionWrapper *lock): lock_(lock) { lock_->enter(); }
    ~PoolLockGuard() { lock_->leave(); }
private: th105::CriticalSectionWrapper *lock_;
};
}


template <>
WeatherEffectObject *CHandleManagerEx<WeatherEffectObject>::acquire(unsigned *handle_token)
{
    PoolLockGuard guard(&lock_34);
    EffectObjectHandle *handle = reinterpret_cast<EffectObjectHandle *>(handle_token);
    unsigned slot;
    if (free_slots_24.empty()) {
        slot = slots_04.size();
        if (++generation_counter_30 > 0xffff) generation_counter_30 = 1;
        handle->slot = static_cast<unsigned short>(slot);
        handle->generation = static_cast<unsigned short>(generation_counter_30);
        WeatherEffectObject *object = new WeatherEffectObject;
        slots_04.push_back(object);
        generations_14.push_back(handle->generation);
    } else {
        slot = free_slots_24.back();
        if (++generation_counter_30 > 0xffff) generation_counter_30 = 1;
        handle->slot = static_cast<unsigned short>(slot);
        handle->generation = static_cast<unsigned short>(generation_counter_30);
        free_slots_24.erase(--free_slots_24.end());
        unsigned generation = handle->generation;
        generations_14[slot] = generation;
        new (slots_04.at(slot)) WeatherEffectObject;
    }
    return slots_04.at(slot);
}
template <>
EffectObject *CHandleManagerEx<EffectObject>::acquire(unsigned *handle_token)
{
    PoolLockGuard guard(&lock_34);
    EffectObjectHandle *handle = reinterpret_cast<EffectObjectHandle *>(handle_token);
    unsigned slot;
    if (free_slots_24.empty()) {
        slot = slots_04.size();
        if (++generation_counter_30 > 0xffff) generation_counter_30 = 1;
        handle->slot = static_cast<unsigned short>(slot);
        handle->generation = static_cast<unsigned short>(generation_counter_30);
        EffectObject *object = new EffectObject;
        slots_04.push_back(object);
        generations_14.push_back(handle->generation);
    } else {
        slot = free_slots_24.back();
        if (++generation_counter_30 > 0xffff) generation_counter_30 = 1;
        handle->slot = static_cast<unsigned short>(slot);
        handle->generation = static_cast<unsigned short>(generation_counter_30);
        free_slots_24.erase(--free_slots_24.end());
        unsigned generation = handle->generation;
        generations_14[slot] = generation;
        new (slots_04.at(slot)) EffectObject;
    }
    return slots_04.at(slot);
}
