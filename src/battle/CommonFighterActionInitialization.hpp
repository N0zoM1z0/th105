#pragma once
#include <stddef.h>

namespace th105 {
class CommonActionEntryView {
public:
    virtual void slot00();
    virtual void slot04();
    virtual int set_action(short);
    void initialize_common_action_entry();
    void zero_motion();
    void advance_secondary_event_effect_cycle();
    void emit_effect(short,float,float,unsigned char,int);
    void publish_layout_scalar(float);
    void dispatch_event(unsigned);
    void dispatch_sequence_window(signed char,int,int);

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
    unsigned char unknown_110[0x1c];
    float field_12c;
    unsigned char unknown_130[0xc];
    short action_id_13c;
    unsigned char unknown_13e[0x42];
    int phase_state_180;
    unsigned char phase_index_184;
    unsigned char unknown_185[0x1];
    short field_186;
    unsigned char unknown_188[0x4];
    float field_18c;
    float field_190;
    unsigned char unknown_194[0x2ea];
    unsigned char field_47e;
    unsigned char field_47f;
    unsigned char unknown_480[0xa];
    short field_48a;
    unsigned char unknown_48c[0xce];
    signed char field_55a;
    unsigned char unknown_55b[0xc9];
    // Four card rows share the alternatives in each column.
    signed char skill_levels_624[4][4];
    unsigned char unknown_634[0x80];
    int field_6b4;
    int field_6b8;
    unsigned char unknown_6bc[0xc];
    unsigned field_6c8;
    unsigned char unknown_6cc[0x58];
    unsigned char field_724;
    unsigned char unknown_725[0xb];
    short field_730;
    short field_732;
    short field_734;
    short field_736;
    short field_738;
    unsigned char unknown_73a[0x2];
    float field_73c;
    float field_740;
    float field_744;
    float field_748;
    float field_74c;
    unsigned char unknown_750[0x28];
    float field_778;
    float field_77c;
    unsigned char unknown_780[0x20];
    short field_7a0;
    short field_7a2;
};

typedef char CheckCommonActionEntryView_x_ec[
    offsetof(CommonActionEntryView, x_ec) == 0xec ? 1 : -1];
typedef char CheckCommonActionEntryView_y_f0[
    offsetof(CommonActionEntryView, y_f0) == 0xf0 ? 1 : -1];
typedef char CheckCommonActionEntryView_velocity_x_f4[
    offsetof(CommonActionEntryView, velocity_x_f4) == 0xf4 ? 1 : -1];
typedef char CheckCommonActionEntryView_velocity_y_f8[
    offsetof(CommonActionEntryView, velocity_y_f8) == 0xf8 ? 1 : -1];
typedef char CheckCommonActionEntryView_acceleration_y_100[
    offsetof(CommonActionEntryView, acceleration_y_100) == 0x100 ? 1 : -1];
typedef char CheckCommonActionEntryView_facing_104[
    offsetof(CommonActionEntryView, facing_104) == 0x104 ? 1 : -1];
typedef char CheckCommonActionEntryView_field_108[
    offsetof(CommonActionEntryView, field_108) == 0x108 ? 1 : -1];
typedef char CheckCommonActionEntryView_field_10c[
    offsetof(CommonActionEntryView, field_10c) == 0x10c ? 1 : -1];
typedef char CheckCommonActionEntryView_field_12c[
    offsetof(CommonActionEntryView, field_12c) == 0x12c ? 1 : -1];
typedef char CheckCommonActionEntryView_action_id_13c[
    offsetof(CommonActionEntryView, action_id_13c) == 0x13c ? 1 : -1];
typedef char CheckCommonActionEntryView_phase_state_180[
    offsetof(CommonActionEntryView, phase_state_180) == 0x180 ? 1 : -1];
typedef char CheckCommonActionEntryView_phase_index_184[
    offsetof(CommonActionEntryView, phase_index_184) == 0x184 ? 1 : -1];
typedef char CheckCommonActionEntryView_field_186[
    offsetof(CommonActionEntryView, field_186) == 0x186 ? 1 : -1];
typedef char CheckCommonActionEntryView_field_18c[
    offsetof(CommonActionEntryView, field_18c) == 0x18c ? 1 : -1];
typedef char CheckCommonActionEntryView_field_190[
    offsetof(CommonActionEntryView, field_190) == 0x190 ? 1 : -1];
typedef char CheckCommonActionEntryView_field_47e[
    offsetof(CommonActionEntryView, field_47e) == 0x47e ? 1 : -1];
typedef char CheckCommonActionEntryView_field_47f[
    offsetof(CommonActionEntryView, field_47f) == 0x47f ? 1 : -1];
typedef char CheckCommonActionEntryView_field_48a[
    offsetof(CommonActionEntryView, field_48a) == 0x48a ? 1 : -1];
typedef char CheckCommonActionEntryView_field_55a[
    offsetof(CommonActionEntryView, field_55a) == 0x55a ? 1 : -1];
typedef char CheckCommonActionEntryView_skill_levels_624[
    offsetof(CommonActionEntryView, skill_levels_624) == 0x624 ? 1 : -1];
typedef char CheckCommonActionEntryView_field_6b4[
    offsetof(CommonActionEntryView, field_6b4) == 0x6b4 ? 1 : -1];
typedef char CheckCommonActionEntryView_field_6b8[
    offsetof(CommonActionEntryView, field_6b8) == 0x6b8 ? 1 : -1];
typedef char CheckCommonActionEntryView_field_6c8[
    offsetof(CommonActionEntryView, field_6c8) == 0x6c8 ? 1 : -1];
typedef char CheckCommonActionEntryView_field_724[
    offsetof(CommonActionEntryView, field_724) == 0x724 ? 1 : -1];
typedef char CheckCommonActionEntryView_field_730[
    offsetof(CommonActionEntryView, field_730) == 0x730 ? 1 : -1];
typedef char CheckCommonActionEntryView_field_732[
    offsetof(CommonActionEntryView, field_732) == 0x732 ? 1 : -1];
typedef char CheckCommonActionEntryView_field_734[
    offsetof(CommonActionEntryView, field_734) == 0x734 ? 1 : -1];
typedef char CheckCommonActionEntryView_field_736[
    offsetof(CommonActionEntryView, field_736) == 0x736 ? 1 : -1];
typedef char CheckCommonActionEntryView_field_738[
    offsetof(CommonActionEntryView, field_738) == 0x738 ? 1 : -1];
typedef char CheckCommonActionEntryView_field_73c[
    offsetof(CommonActionEntryView, field_73c) == 0x73c ? 1 : -1];
typedef char CheckCommonActionEntryView_field_740[
    offsetof(CommonActionEntryView, field_740) == 0x740 ? 1 : -1];
typedef char CheckCommonActionEntryView_field_744[
    offsetof(CommonActionEntryView, field_744) == 0x744 ? 1 : -1];
typedef char CheckCommonActionEntryView_field_748[
    offsetof(CommonActionEntryView, field_748) == 0x748 ? 1 : -1];
typedef char CheckCommonActionEntryView_field_74c[
    offsetof(CommonActionEntryView, field_74c) == 0x74c ? 1 : -1];
typedef char CheckCommonActionEntryView_field_778[
    offsetof(CommonActionEntryView, field_778) == 0x778 ? 1 : -1];
typedef char CheckCommonActionEntryView_field_77c[
    offsetof(CommonActionEntryView, field_77c) == 0x77c ? 1 : -1];
typedef char CheckCommonActionEntryView_field_7a0[
    offsetof(CommonActionEntryView, field_7a0) == 0x7a0 ? 1 : -1];
typedef char CheckCommonActionEntryView_field_7a2[
    offsetof(CommonActionEntryView, field_7a2) == 0x7a2 ? 1 : -1];

}
