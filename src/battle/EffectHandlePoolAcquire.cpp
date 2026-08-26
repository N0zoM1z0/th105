#include "characters/TObjectManagerBase.hpp"

#include <new>


class CSelectObject {
public:
    CSelectObject();
    virtual ~CSelectObject();

    unsigned char storage_004[0x16c];
};


class InfoEffectObject {
public:
    InfoEffectObject();
    virtual ~InfoEffectObject();

    unsigned char storage_004[0x174];
};


typedef char CSelectObject_size_must_be_0x170[
    sizeof(CSelectObject) == 0x170 ? 1 : -1];
typedef char InfoEffectObject_size_must_be_0x178[
    sizeof(InfoEffectObject) == 0x178 ? 1 : -1];


namespace {

struct EffectObjectHandle {
    unsigned short slot;
    unsigned short generation;
};


class PoolLockGuard {
public:
    __forceinline PoolLockGuard(th105::CriticalSectionWrapper *lock)
        : lock_(lock)
    {
        lock_->enter();
    }

    __forceinline ~PoolLockGuard()
    {
        lock_->leave();
    }

private:
    th105::CriticalSectionWrapper *lock_;
};

} // namespace


#define TH105_DEFINE_EFFECT_POOL_ACQUIRE(ObjectType)                         \
template <>                                                                  \
ObjectType *CHandleManagerEx<ObjectType>::acquire(unsigned *handle_token)    \
{                                                                            \
    PoolLockGuard guard(&lock_34);                                            \
    EffectObjectHandle *handle =                                             \
        reinterpret_cast<EffectObjectHandle *>(handle_token);                \
    unsigned slot;                                                           \
                                                                             \
    if (free_slots_24.empty()) {                                             \
        slot = slots_04.size();                                              \
        if (++generation_counter_30 > 0xffff)                                \
            generation_counter_30 = 1;                                      \
        handle->slot = static_cast<unsigned short>(slot);                    \
        handle->generation =                                                 \
            static_cast<unsigned short>(generation_counter_30);              \
                                                                             \
        ObjectType *object = new ObjectType;                                 \
        slots_04.push_back(object);                                          \
        generations_14.push_back(handle->generation);                        \
    } else {                                                                 \
        slot = free_slots_24.back();                                         \
        if (++generation_counter_30 > 0xffff)                                \
            generation_counter_30 = 1;                                      \
        handle->slot = static_cast<unsigned short>(slot);                    \
        handle->generation =                                                 \
            static_cast<unsigned short>(generation_counter_30);              \
                                                                             \
        free_slots_24.erase(--free_slots_24.end());                          \
        unsigned generation = handle->generation;                            \
        generations_14[slot] = generation;                                  \
        new (slots_04.at(slot)) ObjectType;                                  \
    }                                                                        \
                                                                             \
    return slots_04.at(slot);                                                \
}

TH105_DEFINE_EFFECT_POOL_ACQUIRE(CSelectObject)
TH105_DEFINE_EFFECT_POOL_ACQUIRE(InfoEffectObject)

#undef TH105_DEFINE_EFFECT_POOL_ACQUIRE
