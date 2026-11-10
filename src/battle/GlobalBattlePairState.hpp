#pragma once
#include <stddef.h>

namespace th105 {

// Shared camera state retains live Fighter coordinate pointers.
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
typedef char BattlePair_first_x_44[offsetof(GlobalBattlePairState,first_x_44)==0x44?1:-1];
typedef char BattlePair_second_x_48[offsetof(GlobalBattlePairState,second_x_48)==0x48?1:-1];
typedef char BattlePair_first_y_4c[offsetof(GlobalBattlePairState,first_y_4c)==0x4c?1:-1];
typedef char BattlePair_second_y_50[offsetof(GlobalBattlePairState,second_y_50)==0x50?1:-1];
typedef char BattlePair_viewport_left_5c[offsetof(GlobalBattlePairState,viewport_left_5c)==0x5c?1:-1];
typedef char BattlePair_size[sizeof(GlobalBattlePairState)==0x6c?1:-1];

} // namespace th105
