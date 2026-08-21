#pragma once

namespace th105 {

struct InfoEffectObjectView {
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

    __forceinline float &x_ec()
    {
        return *reinterpret_cast<float *>(
            reinterpret_cast<unsigned char *>(this) + 0xec);
    }

    __forceinline float &y_f0()
    {
        return *reinterpret_cast<float *>(
            reinterpret_cast<unsigned char *>(this) + 0xf0);
    }

    __forceinline unsigned char &facing_104()
    {
        return *(reinterpret_cast<unsigned char *>(this) + 0x104);
    }

    __forceinline void *&manager_anchor_130()
    {
        return *reinterpret_cast<void **>(
            reinterpret_cast<unsigned char *>(this) + 0x130);
    }

    __forceinline void *&manager_anchor_160()
    {
        return *reinterpret_cast<void **>(
            reinterpret_cast<unsigned char *>(this) + 0x160);
    }

    __forceinline int &spawn_context_164()
    {
        return *reinterpret_cast<int *>(
            reinterpret_cast<unsigned char *>(this) + 0x164);
    }

    __forceinline unsigned char &spawn_flag_16c()
    {
        return *(reinterpret_cast<unsigned char *>(this) + 0x16c);
    }
};

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

    InfoEffectObjectView *spawn_effect_46f460(
        int effect_id,
        float x,
        float y,
        unsigned char facing,
        unsigned char spawn_flag,
        int spawn_context);
    int load_effect_resource_437ec0(const char *path);
    void load_effect_resource_and_preallocate_46f900(
        const char *path, unsigned target_count);
};

} // namespace th105
