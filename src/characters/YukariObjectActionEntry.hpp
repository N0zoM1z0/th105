#ifndef TH105_YUKARI_OBJECT_ACTION_ENTRY_HPP
#define TH105_YUKARI_OBJECT_ACTION_ENTRY_HPP

#include <stddef.h>

namespace th105 {

class YukariEntryMotionView {
public:
    void set_components(float angle, float magnitude);
    int random_range(int lower, int upper);

    unsigned char opaque_000[0xe8];
};

struct YukariAuxiliaryView {
    unsigned char unknown_000[0xe8];
    float x_e8;
    float y_ec;
    unsigned char unknown_0f0[0x8];
    float scale_x_f8;
    float scale_y_fc;
    unsigned char unknown_100[0x4];
    unsigned char facing_104;
};

// Pointer-only primary-vtable view. Never construct or embed this receiver.
// Slot names and complete owner layout remain provisional.
// Local slot0C call view uses a signed-WORD carrier in a four-byte slot.
// The existing shared selector implementation/prototype is not changed.
class YukariObjectEntryView {
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
    void replace_auxiliary(short resource);
    float stage_height();
    void *spawn_parented(int action, float x, float y, unsigned char facing,
                         int layer, const unsigned *words, int count);
    void *spawn_unparented(int action, float x, float y, unsigned char facing,
                           int layer, const unsigned *words, int count);

    YukariEntryMotionView motion_004;
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
    unsigned char unknown_130[0x4];
    unsigned char byte_134;
    unsigned char byte_135;
    unsigned char unknown_136[0x6];
    short action_id_13c;
    short sequence_id_13e;
    unsigned char unknown_140[0x14];
    YukariAuxiliaryView *aux_154;
    unsigned char unknown_158[0x24];
    unsigned char byte_17c;
    unsigned char unknown_17d[0x3];
    int int_180;
    unsigned char byte_184;
    unsigned char unknown_185[0x1bb];
    float *params_340;
    short word_344;
    unsigned char unknown_346[0x2];
    YukariObjectEntryView *owner_348;
    unsigned char unknown_34c[0x18];
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
    unsigned char unknown_388[0x281];
    signed char byte_609;
};

typedef char CheckYukariAux_x_e8[offsetof(YukariAuxiliaryView, x_e8) == 0xe8 ? 1 : -1];
typedef char CheckYukariAux_scale_x_f8[offsetof(YukariAuxiliaryView, scale_x_f8) == 0xf8 ? 1 : -1];
typedef char CheckYukariAux_facing_104[offsetof(YukariAuxiliaryView, facing_104) == 0x104 ? 1 : -1];
typedef char CheckYukariObj_motion_004[offsetof(YukariObjectEntryView, motion_004) == 0x004 ? 1 : -1];
typedef char CheckYukariObj_x_ec[offsetof(YukariObjectEntryView, x_ec) == 0x0ec ? 1 : -1];
typedef char CheckYukariObj_facing_104[offsetof(YukariObjectEntryView, facing_104) == 0x104 ? 1 : -1];
typedef char CheckYukariObj_field_108[offsetof(YukariObjectEntryView, field_108) == 0x108 ? 1 : -1];
typedef char CheckYukariObj_alpha_113[offsetof(YukariObjectEntryView, alpha_113) == 0x113 ? 1 : -1];
typedef char CheckYukariObj_scale_x_11c[offsetof(YukariObjectEntryView, scale_x_11c) == 0x11c ? 1 : -1];
typedef char CheckYukariObj_byte_134[offsetof(YukariObjectEntryView, byte_134) == 0x134 ? 1 : -1];
typedef char CheckYukariObj_action_id_13c[offsetof(YukariObjectEntryView, action_id_13c) == 0x13c ? 1 : -1];
typedef char CheckYukariObj_aux_154[offsetof(YukariObjectEntryView, aux_154) == 0x154 ? 1 : -1];
typedef char CheckYukariObj_byte_17c[offsetof(YukariObjectEntryView, byte_17c) == 0x17c ? 1 : -1];
typedef char CheckYukariObj_params_340[offsetof(YukariObjectEntryView, params_340) == 0x340 ? 1 : -1];
typedef char CheckYukariObj_owner_348[offsetof(YukariObjectEntryView, owner_348) == 0x348 ? 1 : -1];
typedef char CheckYukariObj_word_364[offsetof(YukariObjectEntryView, word_364) == 0x364 ? 1 : -1];
typedef char CheckYukariObj_field_370[offsetof(YukariObjectEntryView, field_370) == 0x370 ? 1 : -1];
typedef char CheckYukariObj_word_386[offsetof(YukariObjectEntryView, word_386) == 0x386 ? 1 : -1];
typedef char CheckYukariObj_byte_609[offsetof(YukariObjectEntryView, byte_609) == 0x609 ? 1 : -1];

int __cdecl selector_random_roll(int limit);
float __cdecl lookup_orientation_sine_quantized_abs(float phase);
float __cdecl lookup_orientation_cosine_quantized_abs(float phase);

} // namespace th105

#endif
