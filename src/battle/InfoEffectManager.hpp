#pragma once
#include "EffectSpawnObjectView.hpp"

namespace th105 {

struct InfoEffectObjectView : EffectSpawnObjectView {};

struct InfoEffectObjectPoolView {
    InfoEffectObjectView *allocate_46f370();
    void preallocate_46f3d0(unsigned target_count);
};

struct InfoEffectManagerSpawnView {
    __forceinline InfoEffectObjectPoolView &object_pool_04()
    {
        return *reinterpret_cast<InfoEffectObjectPoolView *>(
            reinterpret_cast<unsigned char *>(this) + 0x04);
    }

    __forceinline void *manager_anchor_64()
    {
        return reinterpret_cast<unsigned char *>(this) + 0x64;
    }

    __forceinline void *manager_anchor_88()
    {
        return reinterpret_cast<unsigned char *>(this) + 0x88;
    }

    int load_effect_resource_437ec0(const char *path);
    void load_effect_resource_and_preallocate_46f900(
        const char *path, unsigned target_count);
};

} // namespace th105
