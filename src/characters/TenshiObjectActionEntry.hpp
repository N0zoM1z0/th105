#ifndef TH105_TENSHI_OBJECT_ACTION_ENTRY_HPP
#define TH105_TENSHI_OBJECT_ACTION_ENTRY_HPP

#include <stddef.h>

namespace th105 {

class TenshiEntryMotionView {
public:
    void set_components(float angle, float magnitude);

    unsigned char opaque_000[0xe8];
};

struct TenshiAuxiliaryView {
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
class TenshiObjectEntryView {
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
    void dispatch_character_wave_handle(unsigned index);
    void *spawn_parented(int action, float x, float y, unsigned char facing,
                         int layer, const unsigned *words, int count);
    void *spawn_unparented(int action, float x, float y, unsigned char facing,
                           int layer, const unsigned *words, int count);

    TenshiEntryMotionView motion_004;
    float x_ec;
    float y_f0;
    float velocity_x_f4;
    float velocity_y_f8;
    unsigned char unknown_0fc[0x8];
    signed char facing_104;
    unsigned char unknown_105[0xc];
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
    unsigned char unknown_140[0x4];
    int int_144;
    unsigned char unknown_148[0xc];
    TenshiAuxiliaryView *aux_154;
    unsigned char unknown_158[0x24];
    unsigned char byte_17c;
    unsigned char unknown_17d[0x7];
    unsigned char byte_184;
    unsigned char unknown_185[0x1b7];
    unsigned char layer_33c;
    unsigned char unknown_33d[0x3];
    float *params_340;
    short word_344;
    unsigned char unknown_346[0x2];
    TenshiObjectEntryView *owner_348;
    TenshiObjectEntryView *target_34c;
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
    unsigned char unknown_388[0x4a0];
    float field_828;
};

typedef char CheckTenshiAux_x_e8[offsetof(TenshiAuxiliaryView, x_e8) == 0xe8 ? 1 : -1];
typedef char CheckTenshiAux_scale_x_f8[offsetof(TenshiAuxiliaryView, scale_x_f8) == 0xf8 ? 1 : -1];
typedef char CheckTenshiAux_facing_104[offsetof(TenshiAuxiliaryView, facing_104) == 0x104 ? 1 : -1];
typedef char CheckTenshiObj_motion_004[offsetof(TenshiObjectEntryView, motion_004) == 0x004 ? 1 : -1];
typedef char CheckTenshiObj_x_ec[offsetof(TenshiObjectEntryView, x_ec) == 0x0ec ? 1 : -1];
typedef char CheckTenshiObj_facing_104[offsetof(TenshiObjectEntryView, facing_104) == 0x104 ? 1 : -1];
typedef char CheckTenshiObj_color_111[offsetof(TenshiObjectEntryView, color_111) == 0x111 ? 1 : -1];
typedef char CheckTenshiObj_scale_x_11c[offsetof(TenshiObjectEntryView, scale_x_11c) == 0x11c ? 1 : -1];
typedef char CheckTenshiObj_action_id_13c[offsetof(TenshiObjectEntryView, action_id_13c) == 0x13c ? 1 : -1];
typedef char CheckTenshiObj_int_144[offsetof(TenshiObjectEntryView, int_144) == 0x144 ? 1 : -1];
typedef char CheckTenshiObj_aux_154[offsetof(TenshiObjectEntryView, aux_154) == 0x154 ? 1 : -1];
typedef char CheckTenshiObj_byte_17c[offsetof(TenshiObjectEntryView, byte_17c) == 0x17c ? 1 : -1];
typedef char CheckTenshiObj_layer_33c[offsetof(TenshiObjectEntryView, layer_33c) == 0x33c ? 1 : -1];
typedef char CheckTenshiObj_params_340[offsetof(TenshiObjectEntryView, params_340) == 0x340 ? 1 : -1];
typedef char CheckTenshiObj_owner_348[offsetof(TenshiObjectEntryView, owner_348) == 0x348 ? 1 : -1];
typedef char CheckTenshiObj_word_364[offsetof(TenshiObjectEntryView, word_364) == 0x364 ? 1 : -1];
typedef char CheckTenshiObj_field_370[offsetof(TenshiObjectEntryView, field_370) == 0x370 ? 1 : -1];
typedef char CheckTenshiObj_word_386[offsetof(TenshiObjectEntryView, word_386) == 0x386 ? 1 : -1];
typedef char CheckTenshiObj_field_828[offsetof(TenshiObjectEntryView, field_828) == 0x828 ? 1 : -1];

int __cdecl selector_random_roll(int limit);
extern int g_event_effect_id;
float __cdecl lookup_orientation_sine_quantized_abs(float phase);
float __cdecl lookup_orientation_cosine_quantized_abs(float phase);

} // namespace th105

#endif
