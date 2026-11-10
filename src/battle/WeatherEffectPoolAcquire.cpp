#include "characters/TObjectManagerBase.hpp"
#include "battle/EffectObjectHierarchy.hpp"
#include "battle/EffectSprite.cpp"
#include "battle/FighterActionScratch.cpp"
#include <new>
#include <string.h>

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
class PoolLockGuard {
public:
    PoolLockGuard(th105::CriticalSectionWrapper *lock): lock_(lock) { lock_->enter(); }
    ~PoolLockGuard() { lock_->leave(); }
private: th105::CriticalSectionWrapper *lock_;
};
}


// Native x86 tokens store the slot in the low word and generation in the high
// word. Byte copies preserve those writes without aliasing the unsigned token.
template <>
WeatherEffectObject *CHandleManagerEx<WeatherEffectObject>::acquire(unsigned *handle_token)
{
    PoolLockGuard guard(&lock_34);
    unsigned char *handle_bytes = reinterpret_cast<unsigned char *>(handle_token);
    unsigned slot;
    if (free_slots_24.empty()) {
        slot = slots_04.size();
        if (++generation_counter_30 > 0xffff) generation_counter_30 = 1;
        memcpy(handle_bytes, &slot, sizeof(unsigned short));
        memcpy(handle_bytes + 2, &generation_counter_30, sizeof(unsigned short));
        WeatherEffectObject *object = new WeatherEffectObject;
        slots_04.push_back(object);
        generations_14.push_back(*handle_token >> 16);
    } else {
        slot = free_slots_24.back();
        if (++generation_counter_30 > 0xffff) generation_counter_30 = 1;
        memcpy(handle_bytes, &slot, sizeof(unsigned short));
        memcpy(handle_bytes + 2, &generation_counter_30, sizeof(unsigned short));
        free_slots_24.erase(--free_slots_24.end());
        unsigned generation = *handle_token >> 16;
        generations_14[slot] = generation;
        new (slots_04.at(slot)) WeatherEffectObject;
    }
    return slots_04.at(slot);
}
template <>
EffectObject *CHandleManagerEx<EffectObject>::acquire(unsigned *handle_token)
{
    PoolLockGuard guard(&lock_34);
    unsigned char *handle_bytes = reinterpret_cast<unsigned char *>(handle_token);
    unsigned slot;
    if (free_slots_24.empty()) {
        slot = slots_04.size();
        if (++generation_counter_30 > 0xffff) generation_counter_30 = 1;
        memcpy(handle_bytes, &slot, sizeof(unsigned short));
        memcpy(handle_bytes + 2, &generation_counter_30, sizeof(unsigned short));
        EffectObject *object = new EffectObject;
        slots_04.push_back(object);
        generations_14.push_back(*handle_token >> 16);
    } else {
        slot = free_slots_24.back();
        if (++generation_counter_30 > 0xffff) generation_counter_30 = 1;
        memcpy(handle_bytes, &slot, sizeof(unsigned short));
        memcpy(handle_bytes + 2, &generation_counter_30, sizeof(unsigned short));
        free_slots_24.erase(--free_slots_24.end());
        unsigned generation = *handle_token >> 16;
        generations_14[slot] = generation;
        new (slots_04.at(slot)) EffectObject;
    }
    return slots_04.at(slot);
}
