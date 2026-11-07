#include "battle/Collision.hpp"
#include "battle/SpellRuntime.hpp"
#include "battle/InfoManagerResources.hpp"
#include "ui/UiPrimitives.hpp"
#include <deque>

namespace th105 {

extern "C" void __cdecl _invalid_parameter_noinfo(void);

struct InfoRuntimeEmitter {
    virtual void slot_00();
    virtual void slot_04();
    virtual void slot_08();
    virtual void *emit(
        int effect_id,
        float x,
        float y,
        unsigned char direction,
        int flag,
        int trailing_zero);
};


static inline void release_effect(void *&effect)
{
    if (effect != 0) {
        --*reinterpret_cast<int *>(
            reinterpret_cast<unsigned char *>(effect) + 0x158);
        effect = 0;
    }
}

// Pointer-only view: the native HUD update consumes the 0x534 dword as a
// signed count. It is not constructed or embedded here.
struct FighterGaugeCountView {
    unsigned char prefix_000[0x534];
    int count_534;
};
typedef char FighterGaugeCount_offset[offsetof(FighterGaugeCountView, count_534) == 0x534 ? 1 : -1];
typedef char NativeSequence_size[sizeof(std::deque<FighterSequenceSlot>) == sizeof(FighterSequenceController) ? 1 : -1];
void BattleInfoRecordF8::update_runtime_46ff30()
{
    Fighter *fighter = fighter_18;
    const signed char direction =
        static_cast<signed char>((fighter->player_index_334 == 0) * 2 - 1);

    const int upper_target = fighter->health_174;
    if (gauge_0c < upper_target) {
        int value = gauge_0c + fighter->max_health_176 / 120;
        if (value >= upper_target)
            value = upper_target;
        gauge_0c = value;
    } else {
        gauge_0c = upper_target;
    }

    const int lower_target = fighter->value_47c;
    if (gauge_10 > lower_target) {
        int value = gauge_10 - fighter->max_health_176 / 120;
        if (value <= lower_target)
            value = lower_target;
        gauge_10 = value;
    } else {
        gauge_10 = lower_target;
    }

    if (fighter->terminal_delay_4e8 > 0)
        tail_ec->enabled = true;
    else if (tail_ec != 0)
        tail_ec->enabled = false;

    if (fighter_18->terminal_delay_4e8 > 1)
        tail_f0->enabled = true;
    else if (tail_f0 != 0)
        tail_f0->enabled = false;

    if (fighter_18->terminal_delay_4e8 > 2)
        tail_f4->enabled = true;
    else if (tail_f4 != 0)
        tail_f4->enabled = false;

#define UPDATE_GAUGE_ROW(I, UPPER, LOWER)                                    \
    group_24[I]->enabled = fighter_18->counter_482 < (UPPER);                \
    group_4c[I]->enabled = !group_24[I]->enabled;                            \
    group_60[I]->enabled = fighter_18->unknown_484 > (LOWER);                \
    group_74[I]->enabled = !group_60[I]->enabled;                            \
    group_38[I]->enabled = fighter_18->unknown_484 == (LOWER)

    UPDATE_GAUGE_ROW(0, 200, 0);
    UPDATE_GAUGE_ROW(1, 400, 200);
    UPDATE_GAUGE_ROW(2, 600, 400);
    UPDATE_GAUGE_ROW(3, 800, 600);
    UPDATE_GAUGE_ROW(4, 1000, 800);
#undef UPDATE_GAUGE_ROW

    Fighter *status_fighter = fighter_18;
    const int state_index = status_fighter->state_55a;
    const int total = state_index +
        reinterpret_cast<FighterGaugeCountView *>(status_fighter)->count_534;

    if (status_fighter->unknown_4e7 != 0) {
#define RESET_ACTIVE_ROW(I)                                                  \
        group_9c[I]->enabled = true;                                         \
        group_b0[I]->enabled = true;                                         \
        group_c4[I]->enabled = false;                                        \
        release_effect(owned_effect_d8[I])
        RESET_ACTIVE_ROW(0);
        RESET_ACTIVE_ROW(1);
        RESET_ACTIVE_ROW(2);
        RESET_ACTIVE_ROW(3);
        RESET_ACTIVE_ROW(4);
#undef RESET_ACTIVE_ROW
        return;
    }

#define UPDATE_CURRENT_ROW(I)                                                \
    group_88[I]->enabled = fighter_18->state_55a == (I) && total > (I)
    group_88[0]->enabled = state_index == 0 && total > 0;
    UPDATE_CURRENT_ROW(1);
    UPDATE_CURRENT_ROW(2);
    UPDATE_CURRENT_ROW(3);
    UPDATE_CURRENT_ROW(4);
#undef UPDATE_CURRENT_ROW

    int visible_count = 0;
    if (fighter_18->state_55a != 0) {
        Fighter *sequence_fighter = fighter_18;
        typedef std::deque<FighterSequenceSlot> NativeSequenceDeque;
        NativeSequenceDeque *sequence = reinterpret_cast<NativeSequenceDeque *>(
            &sequence_fighter->sequence_controller_55c);
        FighterSequenceSlot &front = *sequence->begin();
        visible_count = front.field_02;
        if (fighter_18->state_4b8 == 2 && front.field_02 > 1)
            --visible_count;
    }
    if (visible_count > total)
        visible_count = 15;

#define UPDATE_EFFECT_ROW(I)                                                 \
    group_9c[I]->enabled = false;                                            \
    group_b0[I]->enabled = visible_count > (I) && total > (I);               \
    group_c4[I]->enabled = visible_count <= (I) && total > (I);              \
    if (visible_count <= (I))                                                \
        release_effect(owned_effect_d8[I])
    UPDATE_EFFECT_ROW(0);
    UPDATE_EFFECT_ROW(1);
    UPDATE_EFFECT_ROW(2);
    UPDATE_EFFECT_ROW(3);
    UPDATE_EFFECT_ROW(4);
#undef UPDATE_EFFECT_ROW

    if (visible_count > fighter_18->state_55a || visible_count <= 0) {
        release_effect(owned_effect_d8[0]);
        release_effect(owned_effect_d8[1]);
        release_effect(owned_effect_d8[2]);
        release_effect(owned_effect_d8[3]);
        release_effect(owned_effect_d8[4]);
        return;
    }

    for (int i = 0; i < visible_count; ++i) {
        if (owned_effect_d8[i] == 0) {
            const unsigned short effect_id = static_cast<unsigned short>(
                (i > 0) + 32);
            owned_effect_d8[i] = reinterpret_cast<InfoRuntimeEmitter *>(effect_manager_14)->emit(
                    effect_id,
                    group_88[i]->x,
                    group_88[i]->y,
                    direction,
                    1,
                    0);
        }
    }
}

} // namespace th105
