#include "Sakuya.hpp"

#include <new>


namespace th105 {

namespace {

struct RosterObjectHandle {
    unsigned short slot;
    unsigned short generation;
};


class PoolLockGuard {
public:
    __forceinline PoolLockGuard(CriticalSectionWrapper *lock) : lock_(lock)
    {
        lock_->enter();
    }

    __forceinline ~PoolLockGuard()
    {
        lock_->leave();
    }

private:
    CriticalSectionWrapper *lock_;
};

} // namespace


#define TH105_DEFINE_POOL_ACQUIRE(FighterName)                                \
::FighterName##Object *FighterName##ObjectPool::acquire(unsigned *handle_token) \
{                                                                             \
    FighterName##ObjectPoolStorage &storage = storage_00;                     \
    PoolLockGuard guard(&storage.lock_34);                                     \
    RosterObjectHandle *handle =                                              \
        reinterpret_cast<RosterObjectHandle *>(handle_token);                 \
    unsigned slot;                                                            \
                                                                              \
    if (storage.free_slots_24.empty()) {                                      \
        slot = storage.slots_04.size();                                       \
        if (++storage.generation_counter_30 > 0xffff) {                       \
            storage.generation_counter_30 = 1;                               \
        }                                                                     \
        handle->slot = static_cast<unsigned short>(slot);                     \
        handle->generation =                                                  \
            static_cast<unsigned short>(storage.generation_counter_30);       \
                                                                              \
        FighterName##Object *object = new FighterName##Object;                \
        storage.slots_04.push_back(object);                                   \
        storage.generations_14.push_back(handle->generation);                 \
    } else {                                                                  \
        slot = storage.free_slots_24.back();                                  \
        if (++storage.generation_counter_30 > 0xffff) {                       \
            storage.generation_counter_30 = 1;                               \
        }                                                                     \
        handle->slot = static_cast<unsigned short>(slot);                     \
        handle->generation =                                                  \
            static_cast<unsigned short>(storage.generation_counter_30);       \
                                                                              \
        storage.free_slots_24.erase(--storage.free_slots_24.end());           \
        storage.generations_14[slot] = handle->generation;                    \
        new (storage.slots_04.at(slot)) FighterName##Object;                  \
    }                                                                         \
                                                                              \
    return storage.slots_04.at(slot);                                         \
}

TH105_DEFINE_POOL_ACQUIRE(Reimu)
TH105_DEFINE_POOL_ACQUIRE(Marisa)
TH105_DEFINE_POOL_ACQUIRE(Sakuya)
TH105_DEFINE_POOL_ACQUIRE(Alice)
TH105_DEFINE_POOL_ACQUIRE(Patchouli)
TH105_DEFINE_POOL_ACQUIRE(Youmu)
TH105_DEFINE_POOL_ACQUIRE(Remilia)
TH105_DEFINE_POOL_ACQUIRE(Yuyuko)
TH105_DEFINE_POOL_ACQUIRE(Yukari)
TH105_DEFINE_POOL_ACQUIRE(Suika)
TH105_DEFINE_POOL_ACQUIRE(Udonge)
TH105_DEFINE_POOL_ACQUIRE(Komachi)
TH105_DEFINE_POOL_ACQUIRE(Aya)
TH105_DEFINE_POOL_ACQUIRE(Iku)
TH105_DEFINE_POOL_ACQUIRE(Tenshi)

#undef TH105_DEFINE_POOL_ACQUIRE

} // namespace th105
