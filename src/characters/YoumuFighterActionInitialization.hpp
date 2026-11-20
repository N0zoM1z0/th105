#pragma once

#include <stddef.h>

namespace th105 {
// Pointer-only call view; never instantiate/embed a complete Fighter owner.
class YoumuFighterActionEntryView {
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual int select_sequence(short sequence);
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
    int spawn_owned_object(int,float,float,unsigned char,int,float *,int);
    void dispatch_event(unsigned int);
    void zero_motion();
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
    unsigned char unknown_13e[0x42];
    int phase_state_180;
    unsigned char phase_index_184;
    unsigned char unknown_185[0x2f9];
    unsigned char field_47e;
    unsigned char unknown_47f[0x18a];
    signed char field_609;
    unsigned char unknown_60a[0x126];
    short field_730;
    short field_732;
    short field_734;
    short field_736;
    short field_738;
    unsigned char unknown_73a[0x2];
    float field_73c;
    unsigned char unknown_740[0xc];
    float field_74c;
    unsigned char field_750;
    unsigned char unknown_751[0x7c];
    unsigned char field_7cd;
    unsigned char unknown_7ce[0x16];
    unsigned char spawned_899_7e4;
};

typedef char CheckYoumu_x_ec[
    offsetof(YoumuFighterActionEntryView, x_ec) == 0xec ? 1 : -1];
typedef char CheckYoumu_y_f0[
    offsetof(YoumuFighterActionEntryView, y_f0) == 0xf0 ? 1 : -1];
typedef char CheckYoumu_velocity_x_f4[
    offsetof(YoumuFighterActionEntryView, velocity_x_f4) == 0xf4 ? 1 : -1];
typedef char CheckYoumu_velocity_y_f8[
    offsetof(YoumuFighterActionEntryView, velocity_y_f8) == 0xf8 ? 1 : -1];
typedef char CheckYoumu_acceleration_y_100[
    offsetof(YoumuFighterActionEntryView, acceleration_y_100) == 0x100 ? 1 : -1];
typedef char CheckYoumu_facing_104[
    offsetof(YoumuFighterActionEntryView, facing_104) == 0x104 ? 1 : -1];
typedef char CheckYoumu_field_108[
    offsetof(YoumuFighterActionEntryView, field_108) == 0x108 ? 1 : -1];
typedef char CheckYoumu_field_10c[
    offsetof(YoumuFighterActionEntryView, field_10c) == 0x10c ? 1 : -1];
typedef char CheckYoumu_action_id_13c[
    offsetof(YoumuFighterActionEntryView, action_id_13c) == 0x13c ? 1 : -1];
typedef char CheckYoumu_phase_state_180[
    offsetof(YoumuFighterActionEntryView, phase_state_180) == 0x180 ? 1 : -1];
typedef char CheckYoumu_phase_index_184[
    offsetof(YoumuFighterActionEntryView, phase_index_184) == 0x184 ? 1 : -1];
typedef char CheckYoumu_field_47e[
    offsetof(YoumuFighterActionEntryView, field_47e) == 0x47e ? 1 : -1];
typedef char CheckYoumu_field_609[
    offsetof(YoumuFighterActionEntryView, field_609) == 0x609 ? 1 : -1];
typedef char CheckYoumu_field_730[
    offsetof(YoumuFighterActionEntryView, field_730) == 0x730 ? 1 : -1];
typedef char CheckYoumu_field_732[
    offsetof(YoumuFighterActionEntryView, field_732) == 0x732 ? 1 : -1];
typedef char CheckYoumu_field_734[
    offsetof(YoumuFighterActionEntryView, field_734) == 0x734 ? 1 : -1];
typedef char CheckYoumu_field_736[
    offsetof(YoumuFighterActionEntryView, field_736) == 0x736 ? 1 : -1];
typedef char CheckYoumu_field_738[
    offsetof(YoumuFighterActionEntryView, field_738) == 0x738 ? 1 : -1];
typedef char CheckYoumu_field_73c[
    offsetof(YoumuFighterActionEntryView, field_73c) == 0x73c ? 1 : -1];
typedef char CheckYoumu_field_74c[
    offsetof(YoumuFighterActionEntryView, field_74c) == 0x74c ? 1 : -1];
typedef char CheckYoumu_field_750[
    offsetof(YoumuFighterActionEntryView, field_750) == 0x750 ? 1 : -1];
typedef char CheckYoumu_field_7cd[
    offsetof(YoumuFighterActionEntryView, field_7cd) == 0x7cd ? 1 : -1];
typedef char CheckYoumu_spawned_899_7e4[
    offsetof(YoumuFighterActionEntryView, spawned_899_7e4) == 0x7e4 ? 1 : -1];

}
