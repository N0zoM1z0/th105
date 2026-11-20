#ifndef TH105_IKU_OBJECT_ACTION_ENTRY_HPP
#define TH105_IKU_OBJECT_ACTION_ENTRY_HPP
#include <stddef.h>

namespace th105 {
// Pointer-only primary-vtable view. Never construct or embed this receiver.
// Slot names and complete owner layout remain provisional.
// Local slot0C call view uses a signed-WORD carrier in a four-byte slot.
// The existing shared selector implementation/prototype is not changed.
class IkuObjectEntryView {
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
    void replace_secondary(int key,float half_width,int subdivisions,int bands,int blend);
    float stage_height();
    void *spawn_parented(int action, float x, float y, unsigned char facing,
                         int layer, const unsigned *words, int count);
    void *spawn_unparented(int action, float x, float y, unsigned char facing,
                           int layer, const unsigned *words, int count);

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
    unsigned char unknown_130[0x4];
    unsigned char field_134;
    unsigned char unknown_135[0x7];
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

typedef char CheckIkuObjectEntryView_x_ec[
    offsetof(IkuObjectEntryView, x_ec) == 0xec ? 1 : -1];
typedef char CheckIkuObjectEntryView_y_f0[
    offsetof(IkuObjectEntryView, y_f0) == 0xf0 ? 1 : -1];
typedef char CheckIkuObjectEntryView_velocity_x_f4[
    offsetof(IkuObjectEntryView, velocity_x_f4) == 0xf4 ? 1 : -1];
typedef char CheckIkuObjectEntryView_velocity_y_f8[
    offsetof(IkuObjectEntryView, velocity_y_f8) == 0xf8 ? 1 : -1];
typedef char CheckIkuObjectEntryView_facing_104[
    offsetof(IkuObjectEntryView, facing_104) == 0x104 ? 1 : -1];
typedef char CheckIkuObjectEntryView_alpha_113[
    offsetof(IkuObjectEntryView, alpha_113) == 0x113 ? 1 : -1];
typedef char CheckIkuObjectEntryView_field_11c[
    offsetof(IkuObjectEntryView, field_11c) == 0x11c ? 1 : -1];
typedef char CheckIkuObjectEntryView_field_120[
    offsetof(IkuObjectEntryView, field_120) == 0x120 ? 1 : -1];
typedef char CheckIkuObjectEntryView_field_124[
    offsetof(IkuObjectEntryView, field_124) == 0x124 ? 1 : -1];
typedef char CheckIkuObjectEntryView_field_128[
    offsetof(IkuObjectEntryView, field_128) == 0x128 ? 1 : -1];
typedef char CheckIkuObjectEntryView_field_12c[
    offsetof(IkuObjectEntryView, field_12c) == 0x12c ? 1 : -1];
typedef char CheckIkuObjectEntryView_field_134[
    offsetof(IkuObjectEntryView, field_134) == 0x134 ? 1 : -1];
typedef char CheckIkuObjectEntryView_action_id_13c[
    offsetof(IkuObjectEntryView, action_id_13c) == 0x13c ? 1 : -1];
typedef char CheckIkuObjectEntryView_sequence_id_13e[
    offsetof(IkuObjectEntryView, sequence_id_13e) == 0x13e ? 1 : -1];
typedef char CheckIkuObjectEntryView_field_17c[
    offsetof(IkuObjectEntryView, field_17c) == 0x17c ? 1 : -1];
typedef char CheckIkuObjectEntryView_phase_state_180[
    offsetof(IkuObjectEntryView, phase_state_180) == 0x180 ? 1 : -1];
typedef char CheckIkuObjectEntryView_phase_index_184[
    offsetof(IkuObjectEntryView, phase_index_184) == 0x184 ? 1 : -1];
typedef char CheckIkuObjectEntryView_parameters_340[
    offsetof(IkuObjectEntryView, parameters_340) == 0x340 ? 1 : -1];
typedef char CheckIkuObjectEntryView_field_344[
    offsetof(IkuObjectEntryView, field_344) == 0x344 ? 1 : -1];
typedef char CheckIkuObjectEntryView_owner_348[
    offsetof(IkuObjectEntryView, owner_348) == 0x348 ? 1 : -1];
typedef char CheckIkuObjectEntryView_field_364[
    offsetof(IkuObjectEntryView, field_364) == 0x364 ? 1 : -1];
typedef char CheckIkuObjectEntryView_field_366[
    offsetof(IkuObjectEntryView, field_366) == 0x366 ? 1 : -1];
typedef char CheckIkuObjectEntryView_field_368[
    offsetof(IkuObjectEntryView, field_368) == 0x368 ? 1 : -1];
typedef char CheckIkuObjectEntryView_field_36a[
    offsetof(IkuObjectEntryView, field_36a) == 0x36a ? 1 : -1];
typedef char CheckIkuObjectEntryView_field_36c[
    offsetof(IkuObjectEntryView, field_36c) == 0x36c ? 1 : -1];
typedef char CheckIkuObjectEntryView_field_370[
    offsetof(IkuObjectEntryView, field_370) == 0x370 ? 1 : -1];
typedef char CheckIkuObjectEntryView_field_374[
    offsetof(IkuObjectEntryView, field_374) == 0x374 ? 1 : -1];
typedef char CheckIkuObjectEntryView_field_378[
    offsetof(IkuObjectEntryView, field_378) == 0x378 ? 1 : -1];
typedef char CheckIkuObjectEntryView_field_37c[
    offsetof(IkuObjectEntryView, field_37c) == 0x37c ? 1 : -1];
typedef char CheckIkuObjectEntryView_field_380[
    offsetof(IkuObjectEntryView, field_380) == 0x380 ? 1 : -1];
typedef char CheckIkuObjectEntryView_field_384[
    offsetof(IkuObjectEntryView, field_384) == 0x384 ? 1 : -1];
typedef char CheckIkuObjectEntryView_field_386[
    offsetof(IkuObjectEntryView, field_386) == 0x386 ? 1 : -1];

class IkuEntryMotionView {
public:
    void set_components(float angle, float magnitude);
};
int __cdecl selector_random_roll(int limit);
}
#endif
