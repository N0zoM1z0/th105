#ifndef TH105_SAKUYA_OBJECT_ACTION_ENTRY_HPP
#define TH105_SAKUYA_OBJECT_ACTION_ENTRY_HPP
#include <stddef.h>

namespace th105 {
// Pointer-only primary-vtable view. Never construct or embed this receiver.
// Slot names and complete owner layout remain provisional.
// Local slot0C call view uses a signed-WORD carrier in a four-byte slot.
// The existing shared selector implementation/prototype is not changed.
class SakuyaObjectEntryView {
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
    unsigned char unknown_130[0xc];
    short action_id_13c;
    short sequence_id_13e;
    unsigned char unknown_140[0x3c];
    unsigned char field_17c;
    unsigned char unknown_17d[0x3];
    int phase_state_180;
    unsigned char phase_index_184;
    unsigned char unknown_185[0x1bb];
    float *parameters_340;
    short field_344;
    unsigned char unknown_346[0x2];
    unsigned char *owner_348;
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

typedef char CheckSakuyaObject_x_ec[
    offsetof(SakuyaObjectEntryView, x_ec) == 0xec ? 1 : -1];
typedef char CheckSakuyaObject_y_f0[
    offsetof(SakuyaObjectEntryView, y_f0) == 0xf0 ? 1 : -1];
typedef char CheckSakuyaObject_velocity_x_f4[
    offsetof(SakuyaObjectEntryView, velocity_x_f4) == 0xf4 ? 1 : -1];
typedef char CheckSakuyaObject_velocity_y_f8[
    offsetof(SakuyaObjectEntryView, velocity_y_f8) == 0xf8 ? 1 : -1];
typedef char CheckSakuyaObject_facing_104[
    offsetof(SakuyaObjectEntryView, facing_104) == 0x104 ? 1 : -1];
typedef char CheckSakuyaObject_alpha_113[
    offsetof(SakuyaObjectEntryView, alpha_113) == 0x113 ? 1 : -1];
typedef char CheckSakuyaObject_field_11c[
    offsetof(SakuyaObjectEntryView, field_11c) == 0x11c ? 1 : -1];
typedef char CheckSakuyaObject_field_120[
    offsetof(SakuyaObjectEntryView, field_120) == 0x120 ? 1 : -1];
typedef char CheckSakuyaObject_field_124[
    offsetof(SakuyaObjectEntryView, field_124) == 0x124 ? 1 : -1];
typedef char CheckSakuyaObject_field_128[
    offsetof(SakuyaObjectEntryView, field_128) == 0x128 ? 1 : -1];
typedef char CheckSakuyaObject_field_12c[
    offsetof(SakuyaObjectEntryView, field_12c) == 0x12c ? 1 : -1];
typedef char CheckSakuyaObject_action_id_13c[
    offsetof(SakuyaObjectEntryView, action_id_13c) == 0x13c ? 1 : -1];
typedef char CheckSakuyaObject_sequence_id_13e[
    offsetof(SakuyaObjectEntryView, sequence_id_13e) == 0x13e ? 1 : -1];
typedef char CheckSakuyaObject_field_17c[
    offsetof(SakuyaObjectEntryView, field_17c) == 0x17c ? 1 : -1];
typedef char CheckSakuyaObject_phase_state_180[
    offsetof(SakuyaObjectEntryView, phase_state_180) == 0x180 ? 1 : -1];
typedef char CheckSakuyaObject_phase_index_184[
    offsetof(SakuyaObjectEntryView, phase_index_184) == 0x184 ? 1 : -1];
typedef char CheckSakuyaObject_parameters_340[
    offsetof(SakuyaObjectEntryView, parameters_340) == 0x340 ? 1 : -1];
typedef char CheckSakuyaObject_field_344[
    offsetof(SakuyaObjectEntryView, field_344) == 0x344 ? 1 : -1];
typedef char CheckSakuyaObject_owner_348[
    offsetof(SakuyaObjectEntryView, owner_348) == 0x348 ? 1 : -1];
typedef char CheckSakuyaObject_field_364[
    offsetof(SakuyaObjectEntryView, field_364) == 0x364 ? 1 : -1];
typedef char CheckSakuyaObject_field_366[
    offsetof(SakuyaObjectEntryView, field_366) == 0x366 ? 1 : -1];
typedef char CheckSakuyaObject_field_368[
    offsetof(SakuyaObjectEntryView, field_368) == 0x368 ? 1 : -1];
typedef char CheckSakuyaObject_field_36a[
    offsetof(SakuyaObjectEntryView, field_36a) == 0x36a ? 1 : -1];
typedef char CheckSakuyaObject_field_36c[
    offsetof(SakuyaObjectEntryView, field_36c) == 0x36c ? 1 : -1];
typedef char CheckSakuyaObject_field_370[
    offsetof(SakuyaObjectEntryView, field_370) == 0x370 ? 1 : -1];
typedef char CheckSakuyaObject_field_374[
    offsetof(SakuyaObjectEntryView, field_374) == 0x374 ? 1 : -1];
typedef char CheckSakuyaObject_field_378[
    offsetof(SakuyaObjectEntryView, field_378) == 0x378 ? 1 : -1];
typedef char CheckSakuyaObject_field_37c[
    offsetof(SakuyaObjectEntryView, field_37c) == 0x37c ? 1 : -1];
typedef char CheckSakuyaObject_field_380[
    offsetof(SakuyaObjectEntryView, field_380) == 0x380 ? 1 : -1];
typedef char CheckSakuyaObject_field_384[
    offsetof(SakuyaObjectEntryView, field_384) == 0x384 ? 1 : -1];
typedef char CheckSakuyaObject_field_386[
    offsetof(SakuyaObjectEntryView, field_386) == 0x386 ? 1 : -1];

int __cdecl selector_random_roll(int limit);
float __cdecl atan2_degrees(float y, float x);
}
#endif
