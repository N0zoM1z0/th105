#include "battle/SystemEffectManager.hpp"
#include <new>

namespace {

struct EffectObjectHandle {
    unsigned short slot;
    unsigned short generation;
};


class PoolLockGuard {
public:
    PoolLockGuard(th105::CriticalSectionWrapper *lock)
        : lock_(lock)
    {
        lock_->enter();
    }

    ~PoolLockGuard()
    {
        lock_->leave();
    }

private:
    th105::CriticalSectionWrapper *lock_;
};

} // namespace


template <>
SystemEffectObject *CHandleManagerEx<SystemEffectObject>::acquire(unsigned *handle_token)
{
    PoolLockGuard guard(&lock_34);
    EffectObjectHandle *handle =
        reinterpret_cast<EffectObjectHandle *>(handle_token);
    unsigned slot;

    if (free_slots_24.empty()) {
        slot = slots_04.size();
        if (++generation_counter_30 > 0xffff)
            generation_counter_30 = 1;
        handle->slot = static_cast<unsigned short>(slot);
        handle->generation =
            static_cast<unsigned short>(generation_counter_30);

        SystemEffectObject *object = new SystemEffectObject;
        slots_04.push_back(object);
        generations_14.push_back(handle->generation);
    } else {
        slot = free_slots_24.back();
        if (++generation_counter_30 > 0xffff)
            generation_counter_30 = 1;
        handle->slot = static_cast<unsigned short>(slot);
        handle->generation =
            static_cast<unsigned short>(generation_counter_30);

        free_slots_24.erase(--free_slots_24.end());
        unsigned generation = handle->generation;
        generations_14[slot] = generation;
        new (slots_04.at(slot)) SystemEffectObject;
    }

    return slots_04.at(slot);
}
