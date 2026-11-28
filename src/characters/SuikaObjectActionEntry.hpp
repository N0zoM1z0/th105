#ifndef TH105_SUIKA_OBJECT_ACTION_ENTRY_HPP
#define TH105_SUIKA_OBJECT_ACTION_ENTRY_HPP

#include <stddef.h>

namespace th105 {

class SuikaEntryMotionView {
public:
    void set_components(float angle, float magnitude);

    unsigned char opaque_000[0xe8];
};

// Pointer-only call view; never construct or embed this receiver.
// Complete owner size/identity remain unknown; local slot0C signed-WORD
// carrier occupies four stack bytes without changing the shared selector.
class SuikaObjectEntryView {
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
    void *spawn_unparented(int action, float x, float y, unsigned char facing,
                           int layer, const unsigned *words, int count);

    SuikaEntryMotionView motion_004;
    float x_ec;
    float y_f0;
    float velocity_x_f4;
    float velocity_y_f8;
    unsigned char unknown_0fc[0x8];
    unsigned char facing_104;
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
    unsigned char unknown_140[0x3c];
    unsigned char byte_17c;
    unsigned char unknown_17d[0x7];
    unsigned char byte_184;
    unsigned char unknown_185[0x1bb];
    float *params_340;
    short word_344;
    unsigned char unknown_346[0x6];
    SuikaObjectEntryView *target_34c;
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

typedef char CheckSuikaObj_motion_004[offsetof(SuikaObjectEntryView, motion_004) == 0x004 ? 1 : -1];
typedef char CheckSuikaObj_x_ec[offsetof(SuikaObjectEntryView, x_ec) == 0x0ec ? 1 : -1];
typedef char CheckSuikaObj_facing_104[offsetof(SuikaObjectEntryView, facing_104) == 0x104 ? 1 : -1];
typedef char CheckSuikaObj_color_111[offsetof(SuikaObjectEntryView, color_111) == 0x111 ? 1 : -1];
typedef char CheckSuikaObj_scale_x_11c[offsetof(SuikaObjectEntryView, scale_x_11c) == 0x11c ? 1 : -1];
typedef char CheckSuikaObj_action_id_13c[offsetof(SuikaObjectEntryView, action_id_13c) == 0x13c ? 1 : -1];
typedef char CheckSuikaObj_byte_17c[offsetof(SuikaObjectEntryView, byte_17c) == 0x17c ? 1 : -1];
typedef char CheckSuikaObj_params_340[offsetof(SuikaObjectEntryView, params_340) == 0x340 ? 1 : -1];
typedef char CheckSuikaObj_target_34c[offsetof(SuikaObjectEntryView, target_34c) == 0x34c ? 1 : -1];
typedef char CheckSuikaObj_word_364[offsetof(SuikaObjectEntryView, word_364) == 0x364 ? 1 : -1];
typedef char CheckSuikaObj_field_370[offsetof(SuikaObjectEntryView, field_370) == 0x370 ? 1 : -1];
typedef char CheckSuikaObj_word_386[offsetof(SuikaObjectEntryView, word_386) == 0x386 ? 1 : -1];

int __cdecl selector_random_roll(int limit);
float __cdecl lookup_orientation_cosine_quantized_abs(float phase);
float __cdecl lookup_orientation_sine_quantized_abs(float phase);

} // namespace th105

#endif
