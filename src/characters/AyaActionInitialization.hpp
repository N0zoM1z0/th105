#pragma once

#include <stddef.h>
namespace th105 {
// Pointer-only views; never instantiate/embed complete Fighter owners.
struct AyaEntryScratchView { void reset(); };
class AyaActionEntryView {
public:
    virtual void slot00();
    virtual void slot04();
    virtual int set_action_and_finalize(short);
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
    unsigned char advance_frame_and_dispatch();
    void dispatch_character_wave_handle(unsigned int);
    void initialize_common_action_entry();

    unsigned char unknown_004[0xf0];
    float velocity_x_f4;
    float velocity_y_f8;
    unsigned char unknown_0fc[0x4];
    float acceleration_y_100;
    unsigned char unknown_104[0x4];
    float field_108;
    float field_10c;
    unsigned char unknown_110[0x2c];
    short action_id_13c;
    short field_13e;
    short frame_index_140;
    short frame_timer_142;
    int field_144;
    unsigned char unknown_148[0x34];
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
    float field_748;
    float field_74c;
    unsigned char field_750;
};

typedef char CheckAya_velocity_x_f4[
    offsetof(AyaActionEntryView, velocity_x_f4) == 0xf4 ? 1 : -1];
typedef char CheckAya_velocity_y_f8[
    offsetof(AyaActionEntryView, velocity_y_f8) == 0xf8 ? 1 : -1];
typedef char CheckAya_acceleration_y_100[
    offsetof(AyaActionEntryView, acceleration_y_100) == 0x100 ? 1 : -1];
typedef char CheckAya_field_108[
    offsetof(AyaActionEntryView, field_108) == 0x108 ? 1 : -1];
typedef char CheckAya_field_10c[
    offsetof(AyaActionEntryView, field_10c) == 0x10c ? 1 : -1];
typedef char CheckAya_action_id_13c[
    offsetof(AyaActionEntryView, action_id_13c) == 0x13c ? 1 : -1];
typedef char CheckAya_field_13e[
    offsetof(AyaActionEntryView, field_13e) == 0x13e ? 1 : -1];
typedef char CheckAya_frame_index_140[
    offsetof(AyaActionEntryView, frame_index_140) == 0x140 ? 1 : -1];
typedef char CheckAya_frame_timer_142[
    offsetof(AyaActionEntryView, frame_timer_142) == 0x142 ? 1 : -1];
typedef char CheckAya_field_144[
    offsetof(AyaActionEntryView, field_144) == 0x144 ? 1 : -1];
typedef char CheckAya_field_17c[
    offsetof(AyaActionEntryView, field_17c) == 0x17c ? 1 : -1];
typedef char CheckAya_phase_state_180[
    offsetof(AyaActionEntryView, phase_state_180) == 0x180 ? 1 : -1];
typedef char CheckAya_phase_index_184[
    offsetof(AyaActionEntryView, phase_index_184) == 0x184 ? 1 : -1];
typedef char CheckAya_field_47e[
    offsetof(AyaActionEntryView, field_47e) == 0x47e ? 1 : -1];
typedef char CheckAya_field_730[
    offsetof(AyaActionEntryView, field_730) == 0x730 ? 1 : -1];
typedef char CheckAya_field_732[
    offsetof(AyaActionEntryView, field_732) == 0x732 ? 1 : -1];
typedef char CheckAya_field_734[
    offsetof(AyaActionEntryView, field_734) == 0x734 ? 1 : -1];
typedef char CheckAya_field_736[
    offsetof(AyaActionEntryView, field_736) == 0x736 ? 1 : -1];
typedef char CheckAya_field_738[
    offsetof(AyaActionEntryView, field_738) == 0x738 ? 1 : -1];
typedef char CheckAya_field_73c[
    offsetof(AyaActionEntryView, field_73c) == 0x73c ? 1 : -1];
typedef char CheckAya_field_740[
    offsetof(AyaActionEntryView, field_740) == 0x740 ? 1 : -1];
typedef char CheckAya_field_744[
    offsetof(AyaActionEntryView, field_744) == 0x744 ? 1 : -1];
typedef char CheckAya_field_748[
    offsetof(AyaActionEntryView, field_748) == 0x748 ? 1 : -1];
typedef char CheckAya_field_74c[
    offsetof(AyaActionEntryView, field_74c) == 0x74c ? 1 : -1];
typedef char CheckAya_field_750[
    offsetof(AyaActionEntryView, field_750) == 0x750 ? 1 : -1];

}
