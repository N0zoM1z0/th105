#pragma once

#include <stddef.h>
namespace th105 {
// Pointer-only views: neither the scratch prefix nor full Fighter is instantiated.
// Numeric states and original nominal class/TU details remain provisional.
struct YukariEntryScratchView { void reset(); };
class YukariActionEntryView {
public:
    virtual void slot00();
    virtual void slot04();
    virtual int set_action(short);
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
    void advance_secondary_event_effect_cycle();
    void emit_effect(short,float,float,unsigned char,int);
    int spawn_owned_object(int,float,float,unsigned char,int,float *,int);
    void publish_layout_scalar(float);
    void dispatch_event(unsigned);
    void zero_motion();
    unsigned char advance_frame_and_dispatch();
    void dispatch_character_wave_handle(unsigned);
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
    unsigned char unknown_110[0x1c];
    float field_12c;
    unsigned char unknown_130[0xc];
    short action_id_13c;
    unsigned char unknown_13e[0x2];
    short frame_index_140;
    short frame_timer_142;
    unsigned char unknown_144[0x38];
    unsigned char field_17c;
    unsigned char unknown_17d[0x3];
    int phase_state_180;
    unsigned char phase_index_184;
    unsigned char unknown_185[0x1];
    short field_186;
    unsigned char unknown_188[0x4];
    float field_18c;
    float field_190;
    unsigned char unknown_194[0x2ea];
    unsigned char field_47e;
    unsigned char unknown_47f[0x29];
    short field_4a8;
    unsigned char unknown_4aa[0x15b];
    signed char field_605;
    unsigned char unknown_606[0x12a];
    short field_730;
    short field_732;
    short field_734;
    short field_736;
    short field_738;
    unsigned char unknown_73a[0x2];
    float field_73c;
    float field_740;
    unsigned char unknown_744[0x8];
    float field_74c;
    unsigned char field_750;
    unsigned char unknown_751[0x4f];
    short field_7a0;
    short field_7a2;
    short field_7a4;
};

typedef char CheckYukari_x_ec[
    offsetof(YukariActionEntryView, x_ec) == 0xec ? 1 : -1];
typedef char CheckYukari_y_f0[
    offsetof(YukariActionEntryView, y_f0) == 0xf0 ? 1 : -1];
typedef char CheckYukari_velocity_x_f4[
    offsetof(YukariActionEntryView, velocity_x_f4) == 0xf4 ? 1 : -1];
typedef char CheckYukari_velocity_y_f8[
    offsetof(YukariActionEntryView, velocity_y_f8) == 0xf8 ? 1 : -1];
typedef char CheckYukari_acceleration_y_100[
    offsetof(YukariActionEntryView, acceleration_y_100) == 0x100 ? 1 : -1];
typedef char CheckYukari_facing_104[
    offsetof(YukariActionEntryView, facing_104) == 0x104 ? 1 : -1];
typedef char CheckYukari_field_108[
    offsetof(YukariActionEntryView, field_108) == 0x108 ? 1 : -1];
typedef char CheckYukari_field_10c[
    offsetof(YukariActionEntryView, field_10c) == 0x10c ? 1 : -1];
typedef char CheckYukari_field_12c[
    offsetof(YukariActionEntryView, field_12c) == 0x12c ? 1 : -1];
typedef char CheckYukari_action_id_13c[
    offsetof(YukariActionEntryView, action_id_13c) == 0x13c ? 1 : -1];
typedef char CheckYukari_frame_index_140[
    offsetof(YukariActionEntryView, frame_index_140) == 0x140 ? 1 : -1];
typedef char CheckYukari_frame_timer_142[
    offsetof(YukariActionEntryView, frame_timer_142) == 0x142 ? 1 : -1];
typedef char CheckYukari_field_17c[
    offsetof(YukariActionEntryView, field_17c) == 0x17c ? 1 : -1];
typedef char CheckYukari_phase_state_180[
    offsetof(YukariActionEntryView, phase_state_180) == 0x180 ? 1 : -1];
typedef char CheckYukari_phase_index_184[
    offsetof(YukariActionEntryView, phase_index_184) == 0x184 ? 1 : -1];
typedef char CheckYukari_field_186[
    offsetof(YukariActionEntryView, field_186) == 0x186 ? 1 : -1];
typedef char CheckYukari_field_18c[
    offsetof(YukariActionEntryView, field_18c) == 0x18c ? 1 : -1];
typedef char CheckYukari_field_190[
    offsetof(YukariActionEntryView, field_190) == 0x190 ? 1 : -1];
typedef char CheckYukari_field_47e[
    offsetof(YukariActionEntryView, field_47e) == 0x47e ? 1 : -1];
typedef char CheckYukari_field_4a8[
    offsetof(YukariActionEntryView, field_4a8) == 0x4a8 ? 1 : -1];
typedef char CheckYukari_field_605[
    offsetof(YukariActionEntryView, field_605) == 0x605 ? 1 : -1];
typedef char CheckYukari_field_730[
    offsetof(YukariActionEntryView, field_730) == 0x730 ? 1 : -1];
typedef char CheckYukari_field_732[
    offsetof(YukariActionEntryView, field_732) == 0x732 ? 1 : -1];
typedef char CheckYukari_field_734[
    offsetof(YukariActionEntryView, field_734) == 0x734 ? 1 : -1];
typedef char CheckYukari_field_736[
    offsetof(YukariActionEntryView, field_736) == 0x736 ? 1 : -1];
typedef char CheckYukari_field_738[
    offsetof(YukariActionEntryView, field_738) == 0x738 ? 1 : -1];
typedef char CheckYukari_field_73c[
    offsetof(YukariActionEntryView, field_73c) == 0x73c ? 1 : -1];
typedef char CheckYukari_field_740[
    offsetof(YukariActionEntryView, field_740) == 0x740 ? 1 : -1];
typedef char CheckYukari_field_74c[
    offsetof(YukariActionEntryView, field_74c) == 0x74c ? 1 : -1];
typedef char CheckYukari_field_750[
    offsetof(YukariActionEntryView, field_750) == 0x750 ? 1 : -1];
typedef char CheckYukari_field_7a0[
    offsetof(YukariActionEntryView, field_7a0) == 0x7a0 ? 1 : -1];
typedef char CheckYukari_field_7a2[
    offsetof(YukariActionEntryView, field_7a2) == 0x7a2 ? 1 : -1];
typedef char CheckYukari_field_7a4[
    offsetof(YukariActionEntryView, field_7a4) == 0x7a4 ? 1 : -1];

}
