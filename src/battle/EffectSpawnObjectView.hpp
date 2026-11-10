#pragma once
#include <stddef.h>
namespace th105 {
// Observed shared spawn protocol. Never allocated as a complete effect owner.
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

    unsigned char unknown_004[0xe8];
    float x_0ec, y_0f0;
    unsigned char unknown_0f4[0x10];
    unsigned char facing_104;
    unsigned char unknown_105[0x2b];
    void *manager_anchor_130;
    unsigned char unknown_134[0x2c];
    void *manager_anchor_160;
    int spawn_context_164;
    unsigned char unknown_168[4];
    unsigned char spawn_flag_16c;
};
typedef char EffectSpawn_x_0ec[offsetof(EffectSpawnObjectView,x_0ec)==0xec?1:-1];
typedef char EffectSpawn_y_0f0[offsetof(EffectSpawnObjectView,y_0f0)==0xf0?1:-1];
typedef char EffectSpawn_facing_104[offsetof(EffectSpawnObjectView,facing_104)==0x104?1:-1];
typedef char EffectSpawn_manager_anchor_130[offsetof(EffectSpawnObjectView,manager_anchor_130)==0x130?1:-1];
typedef char EffectSpawn_manager_anchor_160[offsetof(EffectSpawnObjectView,manager_anchor_160)==0x160?1:-1];
typedef char EffectSpawn_spawn_context_164[offsetof(EffectSpawnObjectView,spawn_context_164)==0x164?1:-1];
typedef char EffectSpawn_spawn_flag_16c[offsetof(EffectSpawnObjectView,spawn_flag_16c)==0x16c?1:-1];
} // namespace th105
