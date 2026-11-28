#ifndef TH105_REMILIA_OBJECT_ACTION_ENTRY_HPP
#define TH105_REMILIA_OBJECT_ACTION_ENTRY_HPP

#include <stddef.h>

namespace th105 {

class RemiliaEntryMotionView {
public:
    void set_components(float angle, float magnitude);

    unsigned char opaque_000[0xe8];
};

struct RemiliaAuxiliaryView {
    unsigned char unknown_000[0xe8];
    float x_e8;
    float y_ec;
    unsigned char unknown_0f0[0x8];
    float scale_x_f8;
    float scale_y_fc;
    unsigned char unknown_100[0x4];
    signed char facing_104;
};

// Pointer-only primary-vtable view. Never construct or embed this receiver.
// Slot names and complete owner layout remain provisional.
class RemiliaObjectEntryView {
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void select_sequence(short sequence);
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
    void *spawn_parented(int action, float x, float y, signed char facing,
                         int layer, const unsigned *words, int count);
    void replace_secondary(int key, float half_width, int subdivisions,
                           int bands, int blend);
    void replace_auxiliary(short resource);

    RemiliaEntryMotionView motion_004;
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
    unsigned char unknown_140[0x14];
    RemiliaAuxiliaryView *aux_154;
    unsigned char unknown_158[0x24];
    unsigned char byte_17c;
    unsigned char unknown_17d[0x7];
    unsigned char byte_184;
    unsigned char unknown_185[0x1bb];
    float *params_340;
    short word_344;
    unsigned char unknown_346[0x1e];
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

typedef char CheckRemiliaAux_x_e8[offsetof(RemiliaAuxiliaryView, x_e8) == 0xe8 ? 1 : -1];
typedef char CheckRemiliaAux_scale_x_f8[offsetof(RemiliaAuxiliaryView, scale_x_f8) == 0xf8 ? 1 : -1];
typedef char CheckRemiliaAux_facing_104[offsetof(RemiliaAuxiliaryView, facing_104) == 0x104 ? 1 : -1];
typedef char CheckRemiliaObj_motion_004[offsetof(RemiliaObjectEntryView, motion_004) == 0x004 ? 1 : -1];
typedef char CheckRemiliaObj_x_ec[offsetof(RemiliaObjectEntryView, x_ec) == 0x0ec ? 1 : -1];
typedef char CheckRemiliaObj_facing_104[offsetof(RemiliaObjectEntryView, facing_104) == 0x104 ? 1 : -1];
typedef char CheckRemiliaObj_field_108[offsetof(RemiliaObjectEntryView, field_108) == 0x108 ? 1 : -1];
typedef char CheckRemiliaObj_alpha_113[offsetof(RemiliaObjectEntryView, alpha_113) == 0x113 ? 1 : -1];
typedef char CheckRemiliaObj_scale_x_11c[offsetof(RemiliaObjectEntryView, scale_x_11c) == 0x11c ? 1 : -1];
typedef char CheckRemiliaObj_action_id_13c[offsetof(RemiliaObjectEntryView, action_id_13c) == 0x13c ? 1 : -1];
typedef char CheckRemiliaObj_aux_154[offsetof(RemiliaObjectEntryView, aux_154) == 0x154 ? 1 : -1];
typedef char CheckRemiliaObj_byte_17c[offsetof(RemiliaObjectEntryView, byte_17c) == 0x17c ? 1 : -1];
typedef char CheckRemiliaObj_params_340[offsetof(RemiliaObjectEntryView, params_340) == 0x340 ? 1 : -1];
typedef char CheckRemiliaObj_word_364[offsetof(RemiliaObjectEntryView, word_364) == 0x364 ? 1 : -1];
typedef char CheckRemiliaObj_field_370[offsetof(RemiliaObjectEntryView, field_370) == 0x370 ? 1 : -1];
typedef char CheckRemiliaObj_word_386[offsetof(RemiliaObjectEntryView, word_386) == 0x386 ? 1 : -1];

int __cdecl selector_random_roll(int limit);

} // namespace th105

#endif
