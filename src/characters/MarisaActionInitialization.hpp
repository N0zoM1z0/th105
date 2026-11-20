#pragma once

#include <stddef.h>
namespace th105 {
// Pointer-only receiver and scratch views; never instantiate/embed full owners.
struct MarisaEntryScratchView { void reset(); };
class MarisaActionEntryView {
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
    int has_crossed_stage_surface_while_descending();
    int spawn_owned_object(int,float,float,unsigned char,int,float *,int);
    void dispatch_character_wave_handle(unsigned);
    void initialize_common_action_entry();

    unsigned char unknown_004[0xe8];
    float x_ec;
    float y_f0;
    float velocity_x_f4;
    float velocity_y_f8;
    unsigned char unknown_0fc[0x4];
    float acceleration_y_100;
    unsigned char facing_104;
    unsigned char unknown_105[0x3];
    float field_108;
    float field_10c;
    unsigned char unknown_110[0x2c];
    short action_id_13c;
    unsigned char unknown_13e[0x3e];
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
    unsigned char unknown_740[0xc];
    float field_74c;
    unsigned char field_750;
    unsigned char unknown_751[0x53];
    short field_7a4;
    unsigned char unknown_7a6[0x2];
    short field_7a8;
};

typedef char CheckMarisa_x_ec[
    offsetof(MarisaActionEntryView, x_ec) == 0xec ? 1 : -1];
typedef char CheckMarisa_y_f0[
    offsetof(MarisaActionEntryView, y_f0) == 0xf0 ? 1 : -1];
typedef char CheckMarisa_velocity_x_f4[
    offsetof(MarisaActionEntryView, velocity_x_f4) == 0xf4 ? 1 : -1];
typedef char CheckMarisa_velocity_y_f8[
    offsetof(MarisaActionEntryView, velocity_y_f8) == 0xf8 ? 1 : -1];
typedef char CheckMarisa_acceleration_y_100[
    offsetof(MarisaActionEntryView, acceleration_y_100) == 0x100 ? 1 : -1];
typedef char CheckMarisa_facing_104[
    offsetof(MarisaActionEntryView, facing_104) == 0x104 ? 1 : -1];
typedef char CheckMarisa_field_108[
    offsetof(MarisaActionEntryView, field_108) == 0x108 ? 1 : -1];
typedef char CheckMarisa_field_10c[
    offsetof(MarisaActionEntryView, field_10c) == 0x10c ? 1 : -1];
typedef char CheckMarisa_action_id_13c[
    offsetof(MarisaActionEntryView, action_id_13c) == 0x13c ? 1 : -1];
typedef char CheckMarisa_field_17c[
    offsetof(MarisaActionEntryView, field_17c) == 0x17c ? 1 : -1];
typedef char CheckMarisa_phase_state_180[
    offsetof(MarisaActionEntryView, phase_state_180) == 0x180 ? 1 : -1];
typedef char CheckMarisa_phase_index_184[
    offsetof(MarisaActionEntryView, phase_index_184) == 0x184 ? 1 : -1];
typedef char CheckMarisa_field_47e[
    offsetof(MarisaActionEntryView, field_47e) == 0x47e ? 1 : -1];
typedef char CheckMarisa_field_730[
    offsetof(MarisaActionEntryView, field_730) == 0x730 ? 1 : -1];
typedef char CheckMarisa_field_732[
    offsetof(MarisaActionEntryView, field_732) == 0x732 ? 1 : -1];
typedef char CheckMarisa_field_734[
    offsetof(MarisaActionEntryView, field_734) == 0x734 ? 1 : -1];
typedef char CheckMarisa_field_736[
    offsetof(MarisaActionEntryView, field_736) == 0x736 ? 1 : -1];
typedef char CheckMarisa_field_738[
    offsetof(MarisaActionEntryView, field_738) == 0x738 ? 1 : -1];
typedef char CheckMarisa_field_73c[
    offsetof(MarisaActionEntryView, field_73c) == 0x73c ? 1 : -1];
typedef char CheckMarisa_field_74c[
    offsetof(MarisaActionEntryView, field_74c) == 0x74c ? 1 : -1];
typedef char CheckMarisa_field_750[
    offsetof(MarisaActionEntryView, field_750) == 0x750 ? 1 : -1];
typedef char CheckMarisa_field_7a4[
    offsetof(MarisaActionEntryView, field_7a4) == 0x7a4 ? 1 : -1];
typedef char CheckMarisa_field_7a8[
    offsetof(MarisaActionEntryView, field_7a8) == 0x7a8 ? 1 : -1];

}
