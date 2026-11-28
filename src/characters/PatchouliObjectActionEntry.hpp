#ifndef TH105_PATCHOULI_OBJECT_ACTION_ENTRY_HPP
#define TH105_PATCHOULI_OBJECT_ACTION_ENTRY_HPP

#include <stddef.h>

namespace th105 {

class PatchouliEntryMotionView {
public:
    void set_components(float angle, float magnitude);

    unsigned char opaque_000[0xe8];
};

struct PatchouliAuxiliaryView {
    unsigned char unknown_000[0xe8];
    float x_e8;
    float y_ec;
    unsigned char unknown_0f0[0x8];
    float scale_x_f8;
    float scale_y_fc;
    unsigned char unknown_100[0x4];
    unsigned char facing_104;
};

struct PatchouliOwnerView {
    unsigned char unknown_000[0xec];
    float x_ec;
    float y_f0;
    unsigned char unknown_0f4[0x518];
    signed char byte_60c;
};

// Pointer-only partial primary call view. Never construct or embed this receiver.
class PatchouliObjectEntryView {
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
    void replace_secondary(short key, float half_width, int divisions, int bands, int blend);
    float stage_height();
    void *spawn_parented(int action, float x, float y, unsigned char facing, int layer, const unsigned *words, int count);
    void *spawn_unparented(int action, float x, float y, unsigned char facing, int layer, const unsigned *words, int count);

    PatchouliEntryMotionView motion_004;
    float x_ec;
    float y_f0;
    float velocity_x_f4;
    float velocity_y_f8;
    unsigned char unknown_0fc[0x8];
    signed char facing_104;
    unsigned char unknown_105[0xb];
    unsigned char color_110;
    unsigned char color_111;
    unsigned char color_112;
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
    unsigned char unknown_140[0x14];
    PatchouliAuxiliaryView *aux_154;
    unsigned char unknown_158[0x24];
    unsigned char byte_17c;
    unsigned char unknown_17d[0x3];
    int int_180;
    unsigned char byte_184;
    unsigned char unknown_185[0x1b7];
    unsigned char layer_33c;
    unsigned char unknown_33d[0x3];
    float *params_340;
    short word_344;
    unsigned char unknown_346[0x2];
    PatchouliOwnerView *owner_348;
    PatchouliObjectEntryView *target_34c;
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

typedef char CheckPatchouliAux_x_e8[offsetof(PatchouliAuxiliaryView, x_e8) == 0xe8 ? 1 : -1];
typedef char CheckPatchouliAux_scale_x_f8[offsetof(PatchouliAuxiliaryView, scale_x_f8) == 0xf8 ? 1 : -1];
typedef char CheckPatchouliAux_facing_104[offsetof(PatchouliAuxiliaryView, facing_104) == 0x104 ? 1 : -1];
typedef char CheckPatchouliOwner_x_ec[offsetof(PatchouliOwnerView, x_ec) == 0xec ? 1 : -1];
typedef char CheckPatchouliOwner_byte_60c[offsetof(PatchouliOwnerView, byte_60c) == 0x60c ? 1 : -1];
typedef char CheckPatchouliObj_motion_004[offsetof(PatchouliObjectEntryView, motion_004) == 0x004 ? 1 : -1];
typedef char CheckPatchouliObj_x_ec[offsetof(PatchouliObjectEntryView, x_ec) == 0x0ec ? 1 : -1];
typedef char CheckPatchouliObj_facing_104[offsetof(PatchouliObjectEntryView, facing_104) == 0x104 ? 1 : -1];
typedef char CheckPatchouliObj_color_110[offsetof(PatchouliObjectEntryView, color_110) == 0x110 ? 1 : -1];
typedef char CheckPatchouliObj_scale_x_11c[offsetof(PatchouliObjectEntryView, scale_x_11c) == 0x11c ? 1 : -1];
typedef char CheckPatchouliObj_action_id_13c[offsetof(PatchouliObjectEntryView, action_id_13c) == 0x13c ? 1 : -1];
typedef char CheckPatchouliObj_aux_154[offsetof(PatchouliObjectEntryView, aux_154) == 0x154 ? 1 : -1];
typedef char CheckPatchouliObj_byte_17c[offsetof(PatchouliObjectEntryView, byte_17c) == 0x17c ? 1 : -1];
typedef char CheckPatchouliObj_layer_33c[offsetof(PatchouliObjectEntryView, layer_33c) == 0x33c ? 1 : -1];
typedef char CheckPatchouliObj_params_340[offsetof(PatchouliObjectEntryView, params_340) == 0x340 ? 1 : -1];
typedef char CheckPatchouliObj_owner_348[offsetof(PatchouliObjectEntryView, owner_348) == 0x348 ? 1 : -1];
typedef char CheckPatchouliObj_word_364[offsetof(PatchouliObjectEntryView, word_364) == 0x364 ? 1 : -1];
typedef char CheckPatchouliObj_field_370[offsetof(PatchouliObjectEntryView, field_370) == 0x370 ? 1 : -1];
typedef char CheckPatchouliObj_word_386[offsetof(PatchouliObjectEntryView, word_386) == 0x386 ? 1 : -1];

int __cdecl selector_random_roll(int limit);
float __cdecl lookup_orientation_cosine_quantized_abs(float angle);
float __cdecl lookup_orientation_sine_quantized_abs(float angle);
extern int g_match_identifier;

} // namespace th105

#endif
