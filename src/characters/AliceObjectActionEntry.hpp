#ifndef TH105_ALICE_OBJECT_ACTION_ENTRY_HPP
#define TH105_ALICE_OBJECT_ACTION_ENTRY_HPP
#include <stddef.h>

namespace th105 {
// Pointer-only primary call view. Never construct or embed this receiver.
class AliceObjectEntryView {
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
    void continue_action_980();
    void dispatch_character_wave_handle(unsigned handle);
    void *spawn_parented(int action,float x,float y,unsigned char facing,int layer,const unsigned *words,int count);
    void *spawn_unparented(int action,float x,float y,unsigned char facing,int layer,const unsigned *words,int count);

    unsigned char unknown_004[0xe8];
    float x_ec;
    float y_f0;
    float velocity_x_f4;
    float velocity_y_f8;
    unsigned char unknown_0fc[0x8];
    unsigned char facing_104;
    unsigned char unknown_105[0xe];
    unsigned char alpha_113;
    unsigned char unknown_114[0x8];
    float field_11c;
    float field_120;
    float field_124;
    float field_128;
    float field_12c;
    unsigned char unknown_130[0x5];
    unsigned char field_135;
    unsigned char unknown_136[0x6];
    short action_id_13c;
    short sequence_id_13e;
    unsigned char unknown_140[0x30];
    AliceObjectEntryView *peer_170;
    unsigned char unknown_174[0x8];
    unsigned char field_17c;
    unsigned char unknown_17d[0x3];
    int phase_state_180;
    unsigned char phase_index_184;
    unsigned char unknown_185[0x1bb];
    float *parameters_340;
    unsigned char unknown_344[0x4];
    AliceObjectEntryView *owner_348;
    AliceObjectEntryView *linked_object_34c;
    unsigned char unknown_350[0x14];
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

typedef char CheckAliceObjectEntryView_x_ec[
    offsetof(AliceObjectEntryView, x_ec) == 0xec ? 1 : -1];
typedef char CheckAliceObjectEntryView_y_f0[
    offsetof(AliceObjectEntryView, y_f0) == 0xf0 ? 1 : -1];
typedef char CheckAliceObjectEntryView_velocity_x_f4[
    offsetof(AliceObjectEntryView, velocity_x_f4) == 0xf4 ? 1 : -1];
typedef char CheckAliceObjectEntryView_velocity_y_f8[
    offsetof(AliceObjectEntryView, velocity_y_f8) == 0xf8 ? 1 : -1];
typedef char CheckAliceObjectEntryView_facing_104[
    offsetof(AliceObjectEntryView, facing_104) == 0x104 ? 1 : -1];
typedef char CheckAliceObjectEntryView_alpha_113[
    offsetof(AliceObjectEntryView, alpha_113) == 0x113 ? 1 : -1];
typedef char CheckAliceObjectEntryView_field_11c[
    offsetof(AliceObjectEntryView, field_11c) == 0x11c ? 1 : -1];
typedef char CheckAliceObjectEntryView_field_120[
    offsetof(AliceObjectEntryView, field_120) == 0x120 ? 1 : -1];
typedef char CheckAliceObjectEntryView_field_124[
    offsetof(AliceObjectEntryView, field_124) == 0x124 ? 1 : -1];
typedef char CheckAliceObjectEntryView_field_128[
    offsetof(AliceObjectEntryView, field_128) == 0x128 ? 1 : -1];
typedef char CheckAliceObjectEntryView_field_12c[
    offsetof(AliceObjectEntryView, field_12c) == 0x12c ? 1 : -1];
typedef char CheckAliceObjectEntryView_field_135[
    offsetof(AliceObjectEntryView, field_135) == 0x135 ? 1 : -1];
typedef char CheckAliceObjectEntryView_action_id_13c[
    offsetof(AliceObjectEntryView, action_id_13c) == 0x13c ? 1 : -1];
typedef char CheckAliceObjectEntryView_sequence_id_13e[
    offsetof(AliceObjectEntryView, sequence_id_13e) == 0x13e ? 1 : -1];
typedef char CheckAliceObjectEntryView_peer_170[
    offsetof(AliceObjectEntryView, peer_170) == 0x170 ? 1 : -1];
typedef char CheckAliceObjectEntryView_field_17c[
    offsetof(AliceObjectEntryView, field_17c) == 0x17c ? 1 : -1];
typedef char CheckAliceObjectEntryView_phase_state_180[
    offsetof(AliceObjectEntryView, phase_state_180) == 0x180 ? 1 : -1];
typedef char CheckAliceObjectEntryView_phase_index_184[
    offsetof(AliceObjectEntryView, phase_index_184) == 0x184 ? 1 : -1];
typedef char CheckAliceObjectEntryView_parameters_340[
    offsetof(AliceObjectEntryView, parameters_340) == 0x340 ? 1 : -1];
typedef char CheckAliceObjectEntryView_owner_348[
    offsetof(AliceObjectEntryView, owner_348) == 0x348 ? 1 : -1];
typedef char CheckAliceObjectEntryView_linked_object_34c[
    offsetof(AliceObjectEntryView, linked_object_34c) == 0x34c ? 1 : -1];
typedef char CheckAliceObjectEntryView_field_364[
    offsetof(AliceObjectEntryView, field_364) == 0x364 ? 1 : -1];
typedef char CheckAliceObjectEntryView_field_366[
    offsetof(AliceObjectEntryView, field_366) == 0x366 ? 1 : -1];
typedef char CheckAliceObjectEntryView_field_368[
    offsetof(AliceObjectEntryView, field_368) == 0x368 ? 1 : -1];
typedef char CheckAliceObjectEntryView_field_36a[
    offsetof(AliceObjectEntryView, field_36a) == 0x36a ? 1 : -1];
typedef char CheckAliceObjectEntryView_field_36c[
    offsetof(AliceObjectEntryView, field_36c) == 0x36c ? 1 : -1];
typedef char CheckAliceObjectEntryView_field_370[
    offsetof(AliceObjectEntryView, field_370) == 0x370 ? 1 : -1];
typedef char CheckAliceObjectEntryView_field_374[
    offsetof(AliceObjectEntryView, field_374) == 0x374 ? 1 : -1];
typedef char CheckAliceObjectEntryView_field_378[
    offsetof(AliceObjectEntryView, field_378) == 0x378 ? 1 : -1];
typedef char CheckAliceObjectEntryView_field_37c[
    offsetof(AliceObjectEntryView, field_37c) == 0x37c ? 1 : -1];
typedef char CheckAliceObjectEntryView_field_380[
    offsetof(AliceObjectEntryView, field_380) == 0x380 ? 1 : -1];
typedef char CheckAliceObjectEntryView_field_384[
    offsetof(AliceObjectEntryView, field_384) == 0x384 ? 1 : -1];
typedef char CheckAliceObjectEntryView_field_386[
    offsetof(AliceObjectEntryView, field_386) == 0x386 ? 1 : -1];

class AliceEntryMotionView { public: void set_components(float angle,float magnitude); };
int __cdecl selector_random_roll(int limit);
}
#endif
