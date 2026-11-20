#pragma once

#include <stddef.h>
namespace th105 {
// Pointer-only call view; never instantiate/embed a recovered full Fighter.
class YuyukoActionEntryView {
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
    void dispatch_character_wave_handle(unsigned int);
    void initialize_common_action_entry();

    unsigned char unknown_004[0xec];
    float y_f0;
    float velocity_x_f4;
    float velocity_y_f8;
    unsigned char unknown_0fc[0x4];
    float acceleration_y_100;
    unsigned char unknown_104[0x4];
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
    float field_740;
    float field_744;
    unsigned char unknown_748[0x4];
    float field_74c;
    unsigned char field_750;
};

typedef char CheckYuyuko_y_f0[
    offsetof(YuyukoActionEntryView, y_f0) == 0xf0 ? 1 : -1];
typedef char CheckYuyuko_velocity_x_f4[
    offsetof(YuyukoActionEntryView, velocity_x_f4) == 0xf4 ? 1 : -1];
typedef char CheckYuyuko_velocity_y_f8[
    offsetof(YuyukoActionEntryView, velocity_y_f8) == 0xf8 ? 1 : -1];
typedef char CheckYuyuko_acceleration_y_100[
    offsetof(YuyukoActionEntryView, acceleration_y_100) == 0x100 ? 1 : -1];
typedef char CheckYuyuko_field_108[
    offsetof(YuyukoActionEntryView, field_108) == 0x108 ? 1 : -1];
typedef char CheckYuyuko_field_10c[
    offsetof(YuyukoActionEntryView, field_10c) == 0x10c ? 1 : -1];
typedef char CheckYuyuko_action_id_13c[
    offsetof(YuyukoActionEntryView, action_id_13c) == 0x13c ? 1 : -1];
typedef char CheckYuyuko_field_17c[
    offsetof(YuyukoActionEntryView, field_17c) == 0x17c ? 1 : -1];
typedef char CheckYuyuko_phase_state_180[
    offsetof(YuyukoActionEntryView, phase_state_180) == 0x180 ? 1 : -1];
typedef char CheckYuyuko_phase_index_184[
    offsetof(YuyukoActionEntryView, phase_index_184) == 0x184 ? 1 : -1];
typedef char CheckYuyuko_field_47e[
    offsetof(YuyukoActionEntryView, field_47e) == 0x47e ? 1 : -1];
typedef char CheckYuyuko_field_730[
    offsetof(YuyukoActionEntryView, field_730) == 0x730 ? 1 : -1];
typedef char CheckYuyuko_field_732[
    offsetof(YuyukoActionEntryView, field_732) == 0x732 ? 1 : -1];
typedef char CheckYuyuko_field_734[
    offsetof(YuyukoActionEntryView, field_734) == 0x734 ? 1 : -1];
typedef char CheckYuyuko_field_736[
    offsetof(YuyukoActionEntryView, field_736) == 0x736 ? 1 : -1];
typedef char CheckYuyuko_field_738[
    offsetof(YuyukoActionEntryView, field_738) == 0x738 ? 1 : -1];
typedef char CheckYuyuko_field_73c[
    offsetof(YuyukoActionEntryView, field_73c) == 0x73c ? 1 : -1];
typedef char CheckYuyuko_field_740[
    offsetof(YuyukoActionEntryView, field_740) == 0x740 ? 1 : -1];
typedef char CheckYuyuko_field_744[
    offsetof(YuyukoActionEntryView, field_744) == 0x744 ? 1 : -1];
typedef char CheckYuyuko_field_74c[
    offsetof(YuyukoActionEntryView, field_74c) == 0x74c ? 1 : -1];
typedef char CheckYuyuko_field_750[
    offsetof(YuyukoActionEntryView, field_750) == 0x750 ? 1 : -1];

}
