#include "Collision.hpp"

namespace th105 {

struct GlobalBattlePairState {
    float source_00;
    float source_04;
    float source_08;
    unsigned char unknown_0c[0x08];
    float mirrored_14;
    float mirrored_18;
    float mirrored_1c;
    float scale_20;
    unsigned char unknown_24[0x08];
    unsigned char enabled_2c;
    unsigned char enabled_2d;
    unsigned char enabled_2e;
    unsigned char unknown_2f;
    float target_30;
    float target_34;
    float target_38;
    float target_3c;
    float target_40;
    float *first_x_44;
    float *second_x_48;
    float *first_y_4c;
    float *second_y_50;

    void update_first();
    void update_second();

    void copy_roster_metadata(
        float *first_x,
        float *first_y,
        float *second_x,
        float *second_y);
    void initialize_pair_metadata(
        float *first_x,
        float *first_y,
        float *second_x,
        float *second_y);
};

void GlobalBattlePairState::copy_roster_metadata(
    float *first_x,
    float *first_y,
    float *second_x,
    float *second_y)
{
    first_x_44 = first_x;
    first_y_4c = first_y;
    second_x_48 = second_x;
    second_y_50 = second_y;
}

void GlobalBattlePairState::initialize_pair_metadata(
    float *first_x,
    float *first_y,
    float *second_x,
    float *second_y)
{
    target_30 = 0.0f;
    target_34 = 0.0f;
    enabled_2c = 0;
    target_40 = 0.0f;
    enabled_2d = 0;
    target_38 = 0.0f;
    enabled_2e = 0;
    target_3c = 0.0f;
    mirrored_14 = 1.0f;
    first_x_44 = first_x;
    first_y_4c = first_y;
    second_x_48 = second_x;
    second_y_50 = second_y;

    update_first();
    mirrored_18 = source_00;
    mirrored_1c = source_04;
    mirrored_14 = source_08;
    update_first();
    update_second();
}

struct PairInputState {
    unsigned char enabled_00;
    unsigned char unknown_01[3];
    int value_04;
    int value_08;
    int value_0c;
    int value_10;
    int value_14;
    int value_18;
    int value_1c;
    int value_20;
    int value_24;
    int value_28;
    unsigned char flag_2c;
    unsigned char unknown_2d;
    unsigned char flag_2e;

    void reset();
};

void PairInputState::reset()
{
    flag_2c = 0;
    flag_2e = 0;
    value_04 = 0;
    value_08 = 0;
    value_0c = 0;
    value_10 = 0;
    value_18 = 0;
    enabled_00 = 1;
    value_14 = 5;
    value_1c = 3;
    value_20 = 1;
    value_24 = 1;
    value_28 = 3;
}

struct FighterPhaseContextSetupState {
    unsigned char unknown_00[0x28];
    Fighter *fighters_28[3];
    unsigned char active_34[3];

    void publish_slots();
    unsigned char finish_fighter_slot_setup(int slot);
};

unsigned char FighterPhaseContextSetupState::finish_fighter_slot_setup(
    int slot)
{
    if (active_34[slot])
        return 1;
    if (fighters_28[slot]) {
        active_34[slot] = 1;
        publish_slots();
        return 1;
    }
    return 0;
}

typedef char GlobalBattlePairState_size_must_be_0x54[
    sizeof(GlobalBattlePairState) == 0x54 ? 1 : -1];
typedef char PairInputState_prefix_must_be_0x30[
    sizeof(PairInputState) == 0x30 ? 1 : -1];

} // namespace th105
