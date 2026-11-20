#pragma once

#include <stddef.h>
namespace th105 {
// Pointer-only receiver/returned-record views; no complete owner is instantiated.
// Original nominal class layout and source partition remain provisional.
struct PatchouliEntryScratchView { void reset(); };
class PatchouliActionEntryView {
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
    void emit_effect(short,float,float,unsigned char,int);
    void dispatch_sequence_window(signed char,int,int);
    void finalize_sequence_entry(int);
    void publish_texture_state(signed char,short);
    void copy_action_word_176_to_174();
    void dispatch_event(unsigned);
    void initialize_common_action_entry();

    unsigned char unknown_004[0xe8];
    float x_ec;
    float y_f0;
    float velocity_x_f4;
    float velocity_y_f8;
    unsigned char unknown_0fc[0x4];
    float acceleration_y_100;
    signed char facing_104;
    unsigned char unknown_105[0x37];
    short action_id_13c;
    unsigned char unknown_13e[0x3e];
    unsigned char field_17c;
    unsigned char unknown_17d[0x3];
    int phase_state_180;
    unsigned char phase_index_184;
    unsigned char unknown_185[0x2f9];
    unsigned char field_47e;
    unsigned char unknown_47f[0x1a5];
    signed char field_624;
    signed char field_625;
    signed char field_626;
    signed char field_627;
    signed char field_628;
    signed char field_629;
    signed char field_62a;
    signed char field_62b;
    signed char field_62c;
    signed char field_62d;
    signed char field_62e;
    signed char field_62f;
    signed char field_630;
    signed char field_631;
    signed char field_632;
    unsigned char unknown_633[0x22];
    unsigned char field_655;
    unsigned char unknown_656[0xda];
    short field_730;
    short field_732;
    unsigned char unknown_734[0x2];
    short field_736;
    short field_738;
    unsigned char unknown_73a[0x2];
    float field_73c;
    float field_740;
    float field_744;
    unsigned char unknown_748[0x4];
    float field_74c;
    unsigned char field_750;
    unsigned char unknown_751[0x13];
    short field_764;
    short field_766;
    short field_768;
    short field_76a;
    short field_76c;
};

typedef char CheckPatchouli_x_ec[
    offsetof(PatchouliActionEntryView, x_ec) == 0xec ? 1 : -1];
typedef char CheckPatchouli_y_f0[
    offsetof(PatchouliActionEntryView, y_f0) == 0xf0 ? 1 : -1];
typedef char CheckPatchouli_velocity_x_f4[
    offsetof(PatchouliActionEntryView, velocity_x_f4) == 0xf4 ? 1 : -1];
typedef char CheckPatchouli_velocity_y_f8[
    offsetof(PatchouliActionEntryView, velocity_y_f8) == 0xf8 ? 1 : -1];
typedef char CheckPatchouli_acceleration_y_100[
    offsetof(PatchouliActionEntryView, acceleration_y_100) == 0x100 ? 1 : -1];
typedef char CheckPatchouli_facing_104[
    offsetof(PatchouliActionEntryView, facing_104) == 0x104 ? 1 : -1];
typedef char CheckPatchouli_action_id_13c[
    offsetof(PatchouliActionEntryView, action_id_13c) == 0x13c ? 1 : -1];
typedef char CheckPatchouli_field_17c[
    offsetof(PatchouliActionEntryView, field_17c) == 0x17c ? 1 : -1];
typedef char CheckPatchouli_phase_state_180[
    offsetof(PatchouliActionEntryView, phase_state_180) == 0x180 ? 1 : -1];
typedef char CheckPatchouli_phase_index_184[
    offsetof(PatchouliActionEntryView, phase_index_184) == 0x184 ? 1 : -1];
typedef char CheckPatchouli_field_47e[
    offsetof(PatchouliActionEntryView, field_47e) == 0x47e ? 1 : -1];
typedef char CheckPatchouli_field_624[
    offsetof(PatchouliActionEntryView, field_624) == 0x624 ? 1 : -1];
typedef char CheckPatchouli_field_625[
    offsetof(PatchouliActionEntryView, field_625) == 0x625 ? 1 : -1];
typedef char CheckPatchouli_field_626[
    offsetof(PatchouliActionEntryView, field_626) == 0x626 ? 1 : -1];
typedef char CheckPatchouli_field_627[
    offsetof(PatchouliActionEntryView, field_627) == 0x627 ? 1 : -1];
typedef char CheckPatchouli_field_628[
    offsetof(PatchouliActionEntryView, field_628) == 0x628 ? 1 : -1];
typedef char CheckPatchouli_field_629[
    offsetof(PatchouliActionEntryView, field_629) == 0x629 ? 1 : -1];
typedef char CheckPatchouli_field_62a[
    offsetof(PatchouliActionEntryView, field_62a) == 0x62a ? 1 : -1];
typedef char CheckPatchouli_field_62b[
    offsetof(PatchouliActionEntryView, field_62b) == 0x62b ? 1 : -1];
typedef char CheckPatchouli_field_62c[
    offsetof(PatchouliActionEntryView, field_62c) == 0x62c ? 1 : -1];
typedef char CheckPatchouli_field_62d[
    offsetof(PatchouliActionEntryView, field_62d) == 0x62d ? 1 : -1];
typedef char CheckPatchouli_field_62e[
    offsetof(PatchouliActionEntryView, field_62e) == 0x62e ? 1 : -1];
typedef char CheckPatchouli_field_62f[
    offsetof(PatchouliActionEntryView, field_62f) == 0x62f ? 1 : -1];
typedef char CheckPatchouli_field_630[
    offsetof(PatchouliActionEntryView, field_630) == 0x630 ? 1 : -1];
typedef char CheckPatchouli_field_631[
    offsetof(PatchouliActionEntryView, field_631) == 0x631 ? 1 : -1];
typedef char CheckPatchouli_field_632[
    offsetof(PatchouliActionEntryView, field_632) == 0x632 ? 1 : -1];
typedef char CheckPatchouli_field_655[
    offsetof(PatchouliActionEntryView, field_655) == 0x655 ? 1 : -1];
typedef char CheckPatchouli_field_730[
    offsetof(PatchouliActionEntryView, field_730) == 0x730 ? 1 : -1];
typedef char CheckPatchouli_field_732[
    offsetof(PatchouliActionEntryView, field_732) == 0x732 ? 1 : -1];
typedef char CheckPatchouli_field_736[
    offsetof(PatchouliActionEntryView, field_736) == 0x736 ? 1 : -1];
typedef char CheckPatchouli_field_738[
    offsetof(PatchouliActionEntryView, field_738) == 0x738 ? 1 : -1];
typedef char CheckPatchouli_field_73c[
    offsetof(PatchouliActionEntryView, field_73c) == 0x73c ? 1 : -1];
typedef char CheckPatchouli_field_740[
    offsetof(PatchouliActionEntryView, field_740) == 0x740 ? 1 : -1];
typedef char CheckPatchouli_field_744[
    offsetof(PatchouliActionEntryView, field_744) == 0x744 ? 1 : -1];
typedef char CheckPatchouli_field_74c[
    offsetof(PatchouliActionEntryView, field_74c) == 0x74c ? 1 : -1];
typedef char CheckPatchouli_field_750[
    offsetof(PatchouliActionEntryView, field_750) == 0x750 ? 1 : -1];
typedef char CheckPatchouli_field_764[
    offsetof(PatchouliActionEntryView, field_764) == 0x764 ? 1 : -1];
typedef char CheckPatchouli_field_766[
    offsetof(PatchouliActionEntryView, field_766) == 0x766 ? 1 : -1];
typedef char CheckPatchouli_field_768[
    offsetof(PatchouliActionEntryView, field_768) == 0x768 ? 1 : -1];
typedef char CheckPatchouli_field_76a[
    offsetof(PatchouliActionEntryView, field_76a) == 0x76a ? 1 : -1];
typedef char CheckPatchouli_field_76c[
    offsetof(PatchouliActionEntryView, field_76c) == 0x76c ? 1 : -1];

float __fastcall stage_surface_height_at_x(PatchouliActionEntryView *);
}
