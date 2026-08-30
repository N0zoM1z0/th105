#include "Collision.hpp"

#include <math.h>

namespace th105 {

struct GlobalBattlePairState {
    float source_00;
    float source_04;
    float source_08;
    float source_0c;
    float source_10;
    float mirrored_14;
    float mirrored_18;
    float mirrored_1c;
    float scale_20;
    float target_24;
    float target_28;
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
    float midpoint_x_54;
    float midpoint_y_58;
    float viewport_left_5c;
    float viewport_top_60;
    float viewport_right_64;
    float viewport_bottom_68;

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

double __cdecl battle_camera_wave_y(float phase);
double __cdecl battle_camera_wave_x(float phase);

void GlobalBattlePairState::update_first()
{
    float horizontal_span = *first_x_44 - *second_x_48;
    horizontal_span = static_cast<float>(fabs(horizontal_span));
    horizontal_span += 80.0;

    float vertical_span = *first_y_4c - *second_y_50;
    vertical_span = static_cast<float>(fabs(vertical_span));
    if (vertical_span < 0.0f)
        vertical_span = 0.0f;
    if (horizontal_span < 640.0f)
        horizontal_span = 640.0f;

    float diagonal_squared = static_cast<float>(
        vertical_span * vertical_span * 1.5 * 1.5
        + horizontal_span * horizontal_span);
    float diagonal = static_cast<float>(sqrt(diagonal_squared));
    if (diagonal <= 0.0f)
        source_08 = 1.0f;
    source_08 = static_cast<float>(640.0 / diagonal);
    if (enabled_2e)
        source_08 = target_28;
    if (source_08 < 0.5f)
        source_08 = 0.5f;
    else if (source_08 > 1.0f)
        source_08 = 1.0f;

    if (enabled_2c)
        source_00 = scale_20;
    else
        source_00 = static_cast<float>((*first_x_44 + *second_x_48) * 0.5);
    if (source_00 > 960.0)
        source_00 = 960.0f;

    double horizontal_limit = 640.0 / source_08 * 0.5;
    if (source_00 < horizontal_limit)
        source_00 = horizontal_limit;

    float scaled_height = (mirrored_14 - 0.5f) * 2.0;
    if (enabled_2d) {
        source_04 = -target_24 * scaled_height;
        if (source_04 < scaled_height * -420.0)
            source_04 = static_cast<float>(scaled_height * -420.0);
    } else {
        float upper_fighter = *first_y_4c < *second_y_50
            ? *first_y_4c : *second_y_50;
        float separation = *first_y_4c - *second_y_50;
        separation = static_cast<float>(fabs(separation));
        source_04 = static_cast<float>(
            -separation * 0.2f * scaled_height);
        if (upper_fighter > 270.0f)
            source_04 = -upper_fighter * scaled_height;
        if (source_04 < scaled_height * -420.0)
            source_04 = static_cast<float>(scaled_height * -420.0);
    }

    midpoint_x_54 = static_cast<float>((*first_x_44 + *second_x_48) * 0.5);
    midpoint_y_58 = (*first_y_4c + *second_y_50) * 0.5f;
}

void GlobalBattlePairState::update_second()
{
    if (mirrored_14 > source_08) {
        mirrored_14 = static_cast<float>(
            mirrored_14 - ((mirrored_14 - source_08) / 5.0 + 0.002f));
        if (source_08 > mirrored_14)
            mirrored_14 = source_08;
    } else if (mirrored_14 < source_08) {
        mirrored_14 = static_cast<float>(
            mirrored_14 - ((mirrored_14 - source_08) / 80.0 - 0.002f));
        if (source_08 < mirrored_14)
            mirrored_14 = source_08;
    }
    if (mirrored_14 > 1.0f)
        mirrored_14 = 1.0f;
    else if (mirrored_14 < 0.5f)
        mirrored_14 = 0.5f;

    if (mirrored_18 < source_00) {
        mirrored_18 = static_cast<float>(
            mirrored_18 - ((mirrored_18 - source_00) / 30.0 - 5.0));
        if (source_00 < mirrored_18)
            mirrored_18 = source_00;
    } else {
        mirrored_18 = static_cast<float>(
            mirrored_18 - ((mirrored_18 - source_00) / 30.0 + 5.0));
        if (source_00 > mirrored_18)
            mirrored_18 = source_00;
    }

    double horizontal_limit = 640.0 / mirrored_14 * 0.5;
    if (mirrored_18 > 1280.0 - horizontal_limit)
        mirrored_18 = static_cast<float>(1280.0 - horizontal_limit);
    if (mirrored_18 < horizontal_limit)
        mirrored_18 = horizontal_limit;

    float scaled_height = (mirrored_14 - 0.5f) * 2.0;
    if (enabled_2d) {
        if (!(source_04 > mirrored_1c)) {
            mirrored_1c = static_cast<float>(
                mirrored_1c - ((mirrored_1c - source_04) / 10.0 + 1.0));
            if (source_04 > mirrored_1c)
                mirrored_1c = source_04;
        } else {
            mirrored_1c = static_cast<float>(
                mirrored_1c - ((mirrored_1c - source_04) / 10.0 - 1.0));
            if (source_04 < mirrored_1c)
                mirrored_1c = source_04;
        }
    } else if (mirrored_1c < source_04) {
        mirrored_1c = static_cast<float>(
            mirrored_1c - ((mirrored_1c - source_04) / 20.0 - 1.0));
        if (source_04 < mirrored_1c)
            mirrored_1c = source_04;
    } else {
        float upper_fighter = *first_y_4c < *second_y_50
            ? *first_y_4c : *second_y_50;
        if (upper_fighter > 270.0f) {
            mirrored_1c = static_cast<float>(
                mirrored_1c - ((mirrored_1c - source_04) / 10.0 + 1.0));
        } else {
            mirrored_1c = static_cast<float>(
                mirrored_1c - ((mirrored_1c - source_04) / 30.0 + 1.0));
        }
        if (source_04 > mirrored_1c)
            mirrored_1c = source_04;
    }

    float vertical_limit = static_cast<float>(scaled_height * -420.0);
    if (mirrored_1c < vertical_limit)
        mirrored_1c = vertical_limit;
    else if (mirrored_1c > 0.0f)
        mirrored_1c = 0.0f;

    if (target_40 >= 1.0f) {
        target_30 = static_cast<float>(battle_camera_wave_x(target_38) * target_40);
        target_34 = static_cast<float>(battle_camera_wave_y(target_3c) * target_40);
        target_38 = static_cast<float>(target_38 + 83.0);
        if (target_38 >= 360.0f)
            target_38 = static_cast<float>(target_38 - 360.0);
        target_3c = static_cast<float>(target_3c + 107.0);
        if (target_3c >= 360.0f)
            target_3c = static_cast<float>(target_3c - 360.0);
        target_40 = static_cast<float>(target_40 * 0.949999988079071);
        if (target_40 < 1.0f) {
            target_40 = 0.0f;
            target_30 = 0.0f;
            target_34 = 0.0f;
        }
    }

    source_0c = static_cast<float>(
        320.0 / mirrored_14 - (target_30 + mirrored_18));
    source_10 = static_cast<float>(
        420.0 / mirrored_14 - (target_34 + mirrored_1c));
    viewport_left_5c = -source_0c;
    viewport_top_60 = source_10;
    viewport_right_64 = static_cast<float>(640.0 / mirrored_14 - source_0c);
    viewport_bottom_68 = static_cast<float>(source_10 - 480.0 / mirrored_14);
}

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

typedef char GlobalBattlePairState_size_must_be_0x6c[
    sizeof(GlobalBattlePairState) == 0x6c ? 1 : -1];
typedef char PairInputState_prefix_must_be_0x30[
    sizeof(PairInputState) == 0x30 ? 1 : -1];

} // namespace th105
