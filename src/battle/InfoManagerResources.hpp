#pragma once

namespace th105 {

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
    unsigned char storage_000[0xf8];

    void initialize_46fd20(
        int index,
        InfoDesignResourceSubobject *upper,
        InfoDesignResourceSubobject *lower,
        InfoEffectManagerSubobject *effect_manager);
    void initialize_story_471c10(
        InfoDesignResourceSubobject *upper,
        InfoDesignResourceSubobject *lower,
        InfoEffectManagerSubobject *effect_manager);
};

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
};

} // namespace th105
