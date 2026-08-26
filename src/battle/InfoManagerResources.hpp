#pragma once

#include <stddef.h>

namespace th105 {

struct Fighter;
struct UiDesignObject;

struct InfoEffectManagerSubobject {
    virtual void slot_00();
    virtual void load_resource(const char *path, int option);
    virtual int release_resource();
};

struct InfoDesignResourceSubobject {
    virtual void slot_00();
    virtual void slot_04();
    virtual void slot_08();
    virtual void slot_0c();
    virtual void load_design(const char *path);
    virtual int release_design();
};

struct BattleInfoRecordF8 {
    signed char mode_00;
    unsigned char align_01[3];
    float primary_height_04;
    float height_ratio_08;
    int gauge_0c;
    union {
        int gauge_10;
        float story_progress_10;
    };
    union {
        InfoEffectManagerSubobject *effect_manager_14;
        struct {
            unsigned char fade_alpha_14;
            unsigned char story_state_15[3];
        };
    };
    union {
        InfoEffectManagerSubobject *story_context_18;
        Fighter *fighter_18;
    };
    union {
        UiDesignObject *primary_1c;
        Fighter *story_fighter_1c;
    };
    UiDesignObject *secondary_20;
    UiDesignObject *group_24[5];
    UiDesignObject *group_38[5];
    UiDesignObject *group_4c[5];
    UiDesignObject *group_60[5];
    UiDesignObject *group_74[5];
    UiDesignObject *group_88[5];
    UiDesignObject *group_9c[5];
    UiDesignObject *group_b0[5];
    UiDesignObject *group_c4[5];
    void *owned_effect_d8[5];
    UiDesignObject *tail_ec;
    UiDesignObject *tail_f0;
    UiDesignObject *tail_f4;

    void initialize_46fd20(
        int index,
        InfoDesignResourceSubobject *upper,
        InfoDesignResourceSubobject *lower,
        InfoEffectManagerSubobject *effect_manager);
    void initialize_story_471c10(
        InfoDesignResourceSubobject *upper,
        InfoDesignResourceSubobject *lower,
        InfoEffectManagerSubobject *context);
    void attach_story_fighter_471be0(Fighter *fighter);
    void bind_story_values_471a80();
    void update_runtime_46ff30();
    void update_story_471930();
    void render_470710(float shift);
};

typedef char BattleInfoRecordF8_size_must_be_0xf8[
    sizeof(BattleInfoRecordF8) == 0xf8 ? 1 : -1];
typedef char BattleInfoRecordF8_group_24_offset_must_be_0x24[
    offsetof(BattleInfoRecordF8, group_24) == 0x24 ? 1 : -1];
typedef char BattleInfoRecordF8_owned_effect_offset_must_be_0xd8[
    offsetof(BattleInfoRecordF8, owned_effect_d8) == 0xd8 ? 1 : -1];

struct InfoComboResourceSubobject {
    int load_combo_resources_46a8c0();
    int release_combo_resources_46a610();
};

struct InfoManagerResourceView {
    __forceinline InfoEffectManagerSubobject &effect_manager_04()
    {
        return *reinterpret_cast<InfoEffectManagerSubobject *>(
            reinterpret_cast<unsigned char *>(this) + 0x04);
    }

    __forceinline InfoDesignResourceSubobject &upper_design_98()
    {
        return *reinterpret_cast<InfoDesignResourceSubobject *>(
            reinterpret_cast<unsigned char *>(this) + 0x98);
    }

    __forceinline InfoDesignResourceSubobject &lower_design_cc()
    {
        return *reinterpret_cast<InfoDesignResourceSubobject *>(
            reinterpret_cast<unsigned char *>(this) + 0xcc);
    }

    __forceinline InfoComboResourceSubobject &combo_design_100()
    {
        return *reinterpret_cast<InfoComboResourceSubobject *>(
            reinterpret_cast<unsigned char *>(this) + 0x100);
    }

    __forceinline BattleInfoRecordF8 *battle_records_498()
    {
        return reinterpret_cast<BattleInfoRecordF8 *>(
            reinterpret_cast<unsigned char *>(this) + 0x498);
    }

    int load_info_effect_resources_46e960();
    int release_info_effect_resources_46e990();
    void initialize_story_info_resources_471e50();
    void update_normal_46e5a0();
    void update_runtime_471c90();
    void bind_story_values_471d00();
    void render_runtime_471d10();
};

} // namespace th105
