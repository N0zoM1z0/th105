#include "InfoManagerResources.hpp"
#include "Collision.hpp"
#include "../ui/Title.hpp"
#include "../ui/UiPrimitives.hpp"

namespace th105 {

extern "C" int __cdecl _ftol2_sse(double value);

static __forceinline void set_enabled(UiDesignObject *object)
{
    object->enabled = true;
}

static __forceinline float object_metric_90(UiDesignObject *object)
{
    return *reinterpret_cast<float *>(
        reinterpret_cast<unsigned char *>(object) + 0x90);
}

static __forceinline void release_reference_158(void *object)
{
    --*reinterpret_cast<int *>(
        reinterpret_cast<unsigned char *>(object) + 0x158);
}

void BattleInfoRecordF8::initialize_46fd20(
    int index,
    InfoDesignResourceSubobject *upper,
    InfoDesignResourceSubobject *lower,
    InfoEffectManagerSubobject *effect_manager)
{
    TitleDesignResource *upper_design =
        reinterpret_cast<TitleDesignResource *>(upper);
    TitleDesignResource *lower_design =
        reinterpret_cast<TitleDesignResource *>(lower);

    mode_00 = static_cast<signed char>(index);
    effect_manager_14 = effect_manager;

    upper_design->bind_object_alt(&primary_1c, mode_00 + 10);
    upper_design->bind_object_alt(&secondary_20, mode_00 + 15);
    set_enabled(primary_1c);
    set_enabled(secondary_20);

    upper_design->bind_object_alt(&tail_ec, 5 * (mode_00 + 4));
    upper_design->bind_object_alt(&tail_f0, 5 * mode_00 + 21);
    upper_design->bind_object_alt(&tail_f4, 5 * mode_00 + 22);

    for (int i = 0; i < 5; ++i) {
        lower_design->bind_object_alt(&group_24[i], i + 10 * (mode_00 + 2));
        set_enabled(group_24[i]);
        lower_design->bind_object_alt(&group_4c[i], i + 10 * (mode_00 + 4));
        lower_design->bind_object_alt(&group_60[i], i + 10 * (mode_00 + 6));
        set_enabled(group_60[i]);
        lower_design->bind_object_alt(&group_74[i], i + 10 * (mode_00 + 8));
        lower_design->bind_object_alt(&group_38[i], i + 10 * (mode_00 + 10));
    }

    for (int i = 0; i < 5; ++i) {
        lower_design->bind_object_alt(&group_88[i], i + 10 * (mode_00 + 12));
        lower_design->bind_object_alt(&group_9c[i], i + 10 * (mode_00 + 14));
        lower_design->bind_object_alt(&group_b0[i], i + 10 * (mode_00 + 20));
        lower_design->bind_object_alt(&group_c4[i], i + 10 * mode_00 + 205);
        set_enabled(group_b0[i]);
        if (owned_effect_d8[i] != 0) {
            release_reference_158(owned_effect_d8[i]);
            owned_effect_d8[i] = 0;
        }
    }

    primary_height_04 = static_cast<float>(
        static_cast<int>(object_metric_90(group_88[0])));
    height_ratio_08 = static_cast<float>(
        static_cast<int>(object_metric_90(group_88[1]))) / primary_height_04;
}

void BattleInfoRecordF8::initialize_story_471c10(
    InfoDesignResourceSubobject *upper,
    InfoDesignResourceSubobject *,
    InfoEffectManagerSubobject *context)
{
    TitleDesignResource *upper_design =
        reinterpret_cast<TitleDesignResource *>(upper);

    story_context_18 = context;
    upper_design->bind_object_alt(&secondary_20, 11);
    upper_design->bind_object_alt(&group_24[0], 16);
    set_enabled(secondary_20);
    set_enabled(group_24[0]);
    upper_design->bind_object_alt(&group_60[4], 110);
    upper_design->bind_object_alt(&group_74[0], 111);
    upper_design->bind_object_alt(&group_74[1], 120);
    upper_design->bind_object_alt(&group_74[2], 121);
}

void BattleInfoRecordF8::attach_story_fighter_471be0(Fighter *fighter)
{
    story_fighter_1c = fighter;
    bind_story_values_471a80();
    story_progress_10 = 0.0f;
    fade_alpha_14 = 0;
    group_60[4]->enabled = false;
    group_74[1]->enabled = false;
}

} // namespace th105
