#ifndef TH105_YUYUKO_OBJECT_ACTION_ENTRY_HPP
#define TH105_YUYUKO_OBJECT_ACTION_ENTRY_HPP

#include <stddef.h>

namespace th105 {

class YuyukoEntryMotionView {
public:
    void set_components(float angle, float magnitude);

    unsigned char opaque_000[0xe8];
};

struct YuyukoOwnerView {
    unsigned char unknown_000[0xec];
    float x_ec;
    float y_f0;
    unsigned char unknown_0f4[0x514];
    signed char byte_608;
};

// Pointer-only partial primary call view. Never construct or embed this receiver.
class YuyukoObjectEntryView {
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
    void replace_secondary(short key, float half_width, int divisions, int bands, int blend);
    void *spawn_parented(int action, float x, float y, unsigned char facing, int layer, const unsigned *words, int count);
    void *spawn_unparented(int action, float x, float y, unsigned char facing, int layer, const unsigned *words, int count);

    YuyukoEntryMotionView motion_004;
    float x_ec;
    float y_f0;
    float velocity_x_f4;
    float velocity_y_f8;
    unsigned char unknown_0fc[0x8];
    signed char facing_104;
    unsigned char unknown_105[0x3];
    float field_108;
    float field_10c;
    unsigned char unknown_110[0x3];
    unsigned char alpha_113;
    unsigned char unknown_114[0x8];
    float scale_x_11c;
    float scale_y_120;
    float field_124;
    float field_128;
    float rotation_12c;
    unsigned char unknown_130[0xc];
    short action_id_13c;
    short sequence_id_13e;
    unsigned char unknown_140[0x4];
    int int_144;
    unsigned char unknown_148[0x34];
    unsigned char byte_17c;
    unsigned char unknown_17d[0x7];
    unsigned char byte_184;
    unsigned char unknown_185[0x1bb];
    float *params_340;
    short word_344;
    unsigned char unknown_346[0x2];
    YuyukoOwnerView *owner_348;
    YuyukoObjectEntryView *target_34c;
    unsigned char unknown_350[0x14];
    short word_364;
    short word_366;
    short word_368;
    short word_36a;
    short word_36c;
    unsigned char unknown_36e[0x2];
    float field_370;
    float field_374;
    float field_378;
    float field_37c;
    float field_380;
    short word_384;
    short word_386;
};

typedef char CheckYuyukoOwner_x_ec[offsetof(YuyukoOwnerView, x_ec) == 0xec ? 1 : -1];
typedef char CheckYuyukoOwner_byte_608[offsetof(YuyukoOwnerView, byte_608) == 0x608 ? 1 : -1];
typedef char CheckYuyukoObj_motion_004[offsetof(YuyukoObjectEntryView, motion_004) == 0x004 ? 1 : -1];
typedef char CheckYuyukoObj_x_ec[offsetof(YuyukoObjectEntryView, x_ec) == 0x0ec ? 1 : -1];
typedef char CheckYuyukoObj_facing_104[offsetof(YuyukoObjectEntryView, facing_104) == 0x104 ? 1 : -1];
typedef char CheckYuyukoObj_field_108[offsetof(YuyukoObjectEntryView, field_108) == 0x108 ? 1 : -1];
typedef char CheckYuyukoObj_alpha_113[offsetof(YuyukoObjectEntryView, alpha_113) == 0x113 ? 1 : -1];
typedef char CheckYuyukoObj_scale_x_11c[offsetof(YuyukoObjectEntryView, scale_x_11c) == 0x11c ? 1 : -1];
typedef char CheckYuyukoObj_action_id_13c[offsetof(YuyukoObjectEntryView, action_id_13c) == 0x13c ? 1 : -1];
typedef char CheckYuyukoObj_int_144[offsetof(YuyukoObjectEntryView, int_144) == 0x144 ? 1 : -1];
typedef char CheckYuyukoObj_byte_17c[offsetof(YuyukoObjectEntryView, byte_17c) == 0x17c ? 1 : -1];
typedef char CheckYuyukoObj_params_340[offsetof(YuyukoObjectEntryView, params_340) == 0x340 ? 1 : -1];
typedef char CheckYuyukoObj_owner_348[offsetof(YuyukoObjectEntryView, owner_348) == 0x348 ? 1 : -1];
typedef char CheckYuyukoObj_word_364[offsetof(YuyukoObjectEntryView, word_364) == 0x364 ? 1 : -1];
typedef char CheckYuyukoObj_field_370[offsetof(YuyukoObjectEntryView, field_370) == 0x370 ? 1 : -1];
typedef char CheckYuyukoObj_word_386[offsetof(YuyukoObjectEntryView, word_386) == 0x386 ? 1 : -1];

int __cdecl selector_random_roll(int limit);
float __cdecl lookup_orientation_cosine_quantized_abs(float angle);
float __cdecl lookup_orientation_sine_quantized_abs(float angle);

} // namespace th105

#endif
