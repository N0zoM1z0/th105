#pragma once

#include <stddef.h>
namespace th105 {
// Pointer-only call view; no complete Fighter is instantiated or embedded.
class TenshiActionEntryView {
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2c();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void initialize_action_entry();
    void zero_motion();
    void face_opponent_and_flip_horizontal_velocity();
    int spawn_owned_object(int,float,float,unsigned char,int,float *,int);
    void initialize_common_action_entry();

    unsigned char unknown_004[0xe8];
    float x_ec;
    float y_f0;
    float velocity_x_f4;
    float velocity_y_f8;
    unsigned char unknown_0fc[0x4];
    float acceleration_y_100;
    signed char facing_104;
    unsigned char unknown_105[0x3];
    float field_108;
    float field_10c;
    unsigned char unknown_110[0x2c];
    short action_id_13c;
    unsigned char unknown_13e[0x32];
    TenshiActionEntryView *other_fighter_170;
    unsigned char unknown_174[0x8];
    unsigned char field_17c;
    unsigned char unknown_17d[0x3];
    int phase_state_180;
    unsigned char phase_index_184;
    unsigned char unknown_185[0x2f9];
    unsigned char field_47e;
    unsigned char unknown_47f[0x2b1];
    short field_730;
    short field_732;
    short field_734;
    short field_736;
    short field_738;
    unsigned char unknown_73a[0x2];
    float field_73c;
    float field_740;
    float field_744;
    unsigned char unknown_748[0x4];
    float field_74c;
    unsigned char field_750;
    unsigned char unknown_751[0x2f];
    float field_780;
    float field_784;
    float field_788;
};

typedef char CheckTenshi_x_ec[
    offsetof(TenshiActionEntryView, x_ec) == 0xec ? 1 : -1];
typedef char CheckTenshi_y_f0[
    offsetof(TenshiActionEntryView, y_f0) == 0xf0 ? 1 : -1];
typedef char CheckTenshi_velocity_x_f4[
    offsetof(TenshiActionEntryView, velocity_x_f4) == 0xf4 ? 1 : -1];
typedef char CheckTenshi_velocity_y_f8[
    offsetof(TenshiActionEntryView, velocity_y_f8) == 0xf8 ? 1 : -1];
typedef char CheckTenshi_acceleration_y_100[
    offsetof(TenshiActionEntryView, acceleration_y_100) == 0x100 ? 1 : -1];
typedef char CheckTenshi_facing_104[
    offsetof(TenshiActionEntryView, facing_104) == 0x104 ? 1 : -1];
typedef char CheckTenshi_field_108[
    offsetof(TenshiActionEntryView, field_108) == 0x108 ? 1 : -1];
typedef char CheckTenshi_field_10c[
    offsetof(TenshiActionEntryView, field_10c) == 0x10c ? 1 : -1];
typedef char CheckTenshi_action_id_13c[
    offsetof(TenshiActionEntryView, action_id_13c) == 0x13c ? 1 : -1];
typedef char CheckTenshi_other_fighter_170[
    offsetof(TenshiActionEntryView, other_fighter_170) == 0x170 ? 1 : -1];
typedef char CheckTenshi_field_17c[
    offsetof(TenshiActionEntryView, field_17c) == 0x17c ? 1 : -1];
typedef char CheckTenshi_phase_state_180[
    offsetof(TenshiActionEntryView, phase_state_180) == 0x180 ? 1 : -1];
typedef char CheckTenshi_phase_index_184[
    offsetof(TenshiActionEntryView, phase_index_184) == 0x184 ? 1 : -1];
typedef char CheckTenshi_field_47e[
    offsetof(TenshiActionEntryView, field_47e) == 0x47e ? 1 : -1];
typedef char CheckTenshi_field_730[
    offsetof(TenshiActionEntryView, field_730) == 0x730 ? 1 : -1];
typedef char CheckTenshi_field_732[
    offsetof(TenshiActionEntryView, field_732) == 0x732 ? 1 : -1];
typedef char CheckTenshi_field_734[
    offsetof(TenshiActionEntryView, field_734) == 0x734 ? 1 : -1];
typedef char CheckTenshi_field_736[
    offsetof(TenshiActionEntryView, field_736) == 0x736 ? 1 : -1];
typedef char CheckTenshi_field_738[
    offsetof(TenshiActionEntryView, field_738) == 0x738 ? 1 : -1];
typedef char CheckTenshi_field_73c[
    offsetof(TenshiActionEntryView, field_73c) == 0x73c ? 1 : -1];
typedef char CheckTenshi_field_740[
    offsetof(TenshiActionEntryView, field_740) == 0x740 ? 1 : -1];
typedef char CheckTenshi_field_744[
    offsetof(TenshiActionEntryView, field_744) == 0x744 ? 1 : -1];
typedef char CheckTenshi_field_74c[
    offsetof(TenshiActionEntryView, field_74c) == 0x74c ? 1 : -1];
typedef char CheckTenshi_field_750[
    offsetof(TenshiActionEntryView, field_750) == 0x750 ? 1 : -1];
typedef char CheckTenshi_field_780[
    offsetof(TenshiActionEntryView, field_780) == 0x780 ? 1 : -1];
typedef char CheckTenshi_field_784[
    offsetof(TenshiActionEntryView, field_784) == 0x784 ? 1 : -1];
typedef char CheckTenshi_field_788[
    offsetof(TenshiActionEntryView, field_788) == 0x788 ? 1 : -1];

}
