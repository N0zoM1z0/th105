#ifndef TH105_UDONGE_OBJECT_ACTION_ENTRY_HPP
#define TH105_UDONGE_OBJECT_ACTION_ENTRY_HPP
#include <stddef.h>

namespace th105 {
// Pointer-only partial primary call view. Never construct or embed this receiver.
class UdongeObjectEntryView {
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual int select_sequence(short sequence);
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual int set_sequence_frame(short frame);
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2c();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void initialize_action_entry();
    void continue_action_980();
    void dispatch_character_wave_handle(unsigned index);
    void *spawn_parented(int action,float x,float y,unsigned char facing,int layer,const unsigned *words,int count);
    void *spawn_unparented(int action,float x,float y,unsigned char facing,int layer,const unsigned *words,int count);

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
    unsigned char unknown_110[0x3];
    unsigned char alpha_113;
    unsigned char unknown_114[0x8];
    float field_11c;
    float field_120;
    float field_124;
    float field_128;
    float field_12c;
    unsigned char unknown_130[0xc];
    short action_id_13c;
    short sequence_id_13e;
    unsigned char unknown_140[0x30];
    UdongeObjectEntryView *peer_170;
    unsigned char unknown_174[0x8];
    unsigned char field_17c;
    unsigned char unknown_17d[0x7];
    unsigned char phase_index_184;
    unsigned char unknown_185[0x1bb];
    float *parameters_340;
    unsigned char unknown_344[0x4];
    UdongeObjectEntryView *owner_348;
    unsigned char unknown_34c[0x18];
    short field_364;
    short field_366;
    short field_368;
    short field_36a;
    short field_36c;
    unsigned char unknown_36e[0x2];
    float field_370;
    float field_374;
    float field_378;
    float field_37c;
    float field_380;
    short field_384;
    short field_386;
};

typedef char CheckUdongeObjectEntryView_x_ec[
    offsetof(UdongeObjectEntryView, x_ec) == 0xec ? 1 : -1];
typedef char CheckUdongeObjectEntryView_y_f0[
    offsetof(UdongeObjectEntryView, y_f0) == 0xf0 ? 1 : -1];
typedef char CheckUdongeObjectEntryView_velocity_x_f4[
    offsetof(UdongeObjectEntryView, velocity_x_f4) == 0xf4 ? 1 : -1];
typedef char CheckUdongeObjectEntryView_velocity_y_f8[
    offsetof(UdongeObjectEntryView, velocity_y_f8) == 0xf8 ? 1 : -1];
typedef char CheckUdongeObjectEntryView_acceleration_y_100[
    offsetof(UdongeObjectEntryView, acceleration_y_100) == 0x100 ? 1 : -1];
typedef char CheckUdongeObjectEntryView_facing_104[
    offsetof(UdongeObjectEntryView, facing_104) == 0x104 ? 1 : -1];
typedef char CheckUdongeObjectEntryView_field_108[
    offsetof(UdongeObjectEntryView, field_108) == 0x108 ? 1 : -1];
typedef char CheckUdongeObjectEntryView_field_10c[
    offsetof(UdongeObjectEntryView, field_10c) == 0x10c ? 1 : -1];
typedef char CheckUdongeObjectEntryView_alpha_113[
    offsetof(UdongeObjectEntryView, alpha_113) == 0x113 ? 1 : -1];
typedef char CheckUdongeObjectEntryView_field_11c[
    offsetof(UdongeObjectEntryView, field_11c) == 0x11c ? 1 : -1];
typedef char CheckUdongeObjectEntryView_field_120[
    offsetof(UdongeObjectEntryView, field_120) == 0x120 ? 1 : -1];
typedef char CheckUdongeObjectEntryView_field_124[
    offsetof(UdongeObjectEntryView, field_124) == 0x124 ? 1 : -1];
typedef char CheckUdongeObjectEntryView_field_128[
    offsetof(UdongeObjectEntryView, field_128) == 0x128 ? 1 : -1];
typedef char CheckUdongeObjectEntryView_field_12c[
    offsetof(UdongeObjectEntryView, field_12c) == 0x12c ? 1 : -1];
typedef char CheckUdongeObjectEntryView_action_id_13c[
    offsetof(UdongeObjectEntryView, action_id_13c) == 0x13c ? 1 : -1];
typedef char CheckUdongeObjectEntryView_sequence_id_13e[
    offsetof(UdongeObjectEntryView, sequence_id_13e) == 0x13e ? 1 : -1];
typedef char CheckUdongeObjectEntryView_peer_170[
    offsetof(UdongeObjectEntryView, peer_170) == 0x170 ? 1 : -1];
typedef char CheckUdongeObjectEntryView_field_17c[
    offsetof(UdongeObjectEntryView, field_17c) == 0x17c ? 1 : -1];
typedef char CheckUdongeObjectEntryView_phase_index_184[
    offsetof(UdongeObjectEntryView, phase_index_184) == 0x184 ? 1 : -1];
typedef char CheckUdongeObjectEntryView_parameters_340[
    offsetof(UdongeObjectEntryView, parameters_340) == 0x340 ? 1 : -1];
typedef char CheckUdongeObjectEntryView_owner_348[
    offsetof(UdongeObjectEntryView, owner_348) == 0x348 ? 1 : -1];
typedef char CheckUdongeObjectEntryView_field_364[
    offsetof(UdongeObjectEntryView, field_364) == 0x364 ? 1 : -1];
typedef char CheckUdongeObjectEntryView_field_366[
    offsetof(UdongeObjectEntryView, field_366) == 0x366 ? 1 : -1];
typedef char CheckUdongeObjectEntryView_field_368[
    offsetof(UdongeObjectEntryView, field_368) == 0x368 ? 1 : -1];
typedef char CheckUdongeObjectEntryView_field_36a[
    offsetof(UdongeObjectEntryView, field_36a) == 0x36a ? 1 : -1];
typedef char CheckUdongeObjectEntryView_field_36c[
    offsetof(UdongeObjectEntryView, field_36c) == 0x36c ? 1 : -1];
typedef char CheckUdongeObjectEntryView_field_370[
    offsetof(UdongeObjectEntryView, field_370) == 0x370 ? 1 : -1];
typedef char CheckUdongeObjectEntryView_field_374[
    offsetof(UdongeObjectEntryView, field_374) == 0x374 ? 1 : -1];
typedef char CheckUdongeObjectEntryView_field_378[
    offsetof(UdongeObjectEntryView, field_378) == 0x378 ? 1 : -1];
typedef char CheckUdongeObjectEntryView_field_37c[
    offsetof(UdongeObjectEntryView, field_37c) == 0x37c ? 1 : -1];
typedef char CheckUdongeObjectEntryView_field_380[
    offsetof(UdongeObjectEntryView, field_380) == 0x380 ? 1 : -1];
typedef char CheckUdongeObjectEntryView_field_384[
    offsetof(UdongeObjectEntryView, field_384) == 0x384 ? 1 : -1];
typedef char CheckUdongeObjectEntryView_field_386[
    offsetof(UdongeObjectEntryView, field_386) == 0x386 ? 1 : -1];

class UdongeEntryMotionView { public: void set_components(float angle,float magnitude); };
int __cdecl selector_random_roll(int limit);
float __cdecl atan2_degrees(float y,float x);
}
#endif
