#ifndef TH105_MARISA_OBJECT_ACTION_ENTRY_HPP
#define TH105_MARISA_OBJECT_ACTION_ENTRY_HPP

#include <stddef.h>

namespace th105 {

struct MarisaEntryMotionView {
    unsigned char base_000;
    void set_components(float angle, float magnitude);
};

struct MarisaAuxiliaryView {
    unsigned char pad_000[0xe8];
    float field_e8;
    float field_ec;
    unsigned char pad_0f0[0x8];
    float field_f8;
    float field_fc;
    unsigned char pad_100[0x4];
    unsigned char facing_104;
};

struct MarisaOwnerView {
    unsigned char pad_000[0xec];
    float x_ec;
    float y_f0;
    unsigned char pad_0f4[0x7c];
    MarisaOwnerView *target_170;
    unsigned char pad_174[0x638];
    float field_7ac;

    int spawn_owned(int action, float x, float y, unsigned char facing, int layer, const unsigned *words, int count);
};

// Pointer-only primary call view. Never construct or embed this receiver.
class MarisaObjectEntryView {
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual int select_sequence(short sequence);
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual int select_frame(short frame);
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
    void replace_auxiliary(short resource);
    void *spawn_parented(int action, float x, float y, unsigned char facing, int layer, const unsigned *words, int count);
    void *spawn_unparented(int action, float x, float y, unsigned char facing, int layer, const unsigned *words, int count);

    MarisaEntryMotionView motion_004;
    unsigned char pad_005[0xe7];
    float x_ec;
    float y_f0;
    float velocity_x_f4;
    float velocity_y_f8;
    unsigned char pad_0fc[0x8];
    signed char facing_104;
    unsigned char pad_105[0x3];
    float field_108;
    float field_10c;
    unsigned char color_b_110;
    unsigned char color_g_111;
    unsigned char color_r_112;
    unsigned char color_a_113;
    unsigned char pad_114[0x8];
    float scale_x_11c;
    float scale_y_120;
    float field_124;
    float field_128;
    float rotation_12c;
    unsigned char pad_130[0x4];
    unsigned char byte_134;
    unsigned char pad_135[0x7];
    short action_id_13c;
    short sequence_id_13e;
    short frame_id_140;
    unsigned char pad_142[0x2];
    int time_counter_144;
    unsigned char pad_148[0xc];
    MarisaAuxiliaryView *aux_154;
    unsigned char pad_158[0x18];
    MarisaOwnerView *target_170;
    unsigned char pad_174[0x8];
    unsigned char byte_17c;
    unsigned char pad_17d[0x3];
    int field_180;
    unsigned char byte_184;
    unsigned char pad_185[0x1bb];
    float *params_340;
    short word_344;
    unsigned char pad_346[0x2];
    MarisaOwnerView *owner_348;
    MarisaObjectEntryView *related_34c;
    unsigned char pad_350[0x14];
    short word_364;
    short word_366;
    short word_368;
    short word_36a;
    short word_36c;
    unsigned char pad_36e[0x2];
    float field_370;
    float field_374;
    float field_378;
    float field_37c;
    float field_380;
    short word_384;
    short word_386;
};

typedef char CheckMarisaAux_facing_104[offsetof(MarisaAuxiliaryView, facing_104) == 0x104 ? 1 : -1];
typedef char CheckMarisaOwner_target_170[offsetof(MarisaOwnerView, target_170) == 0x170 ? 1 : -1];
typedef char CheckMarisaOwner_field_7ac[offsetof(MarisaOwnerView, field_7ac) == 0x7ac ? 1 : -1];
typedef char CheckMarisaEntry_x_ec[offsetof(MarisaObjectEntryView, x_ec) == 0xec ? 1 : -1];
typedef char CheckMarisaEntry_facing_104[offsetof(MarisaObjectEntryView, facing_104) == 0x104 ? 1 : -1];
typedef char CheckMarisaEntry_color_a_113[offsetof(MarisaObjectEntryView, color_a_113) == 0x113 ? 1 : -1];
typedef char CheckMarisaEntry_rotation_12c[offsetof(MarisaObjectEntryView, rotation_12c) == 0x12c ? 1 : -1];
typedef char CheckMarisaEntry_action_id_13c[offsetof(MarisaObjectEntryView, action_id_13c) == 0x13c ? 1 : -1];
typedef char CheckMarisaEntry_aux_154[offsetof(MarisaObjectEntryView, aux_154) == 0x154 ? 1 : -1];
typedef char CheckMarisaEntry_target_170[offsetof(MarisaObjectEntryView, target_170) == 0x170 ? 1 : -1];
typedef char CheckMarisaEntry_byte_184[offsetof(MarisaObjectEntryView, byte_184) == 0x184 ? 1 : -1];
typedef char CheckMarisaEntry_params_340[offsetof(MarisaObjectEntryView, params_340) == 0x340 ? 1 : -1];
typedef char CheckMarisaEntry_owner_348[offsetof(MarisaObjectEntryView, owner_348) == 0x348 ? 1 : -1];
typedef char CheckMarisaEntry_word_364[offsetof(MarisaObjectEntryView, word_364) == 0x364 ? 1 : -1];
typedef char CheckMarisaEntry_field_370[offsetof(MarisaObjectEntryView, field_370) == 0x370 ? 1 : -1];
typedef char CheckMarisaEntry_word_386[offsetof(MarisaObjectEntryView, word_386) == 0x386 ? 1 : -1];

int __cdecl selector_random_roll(int limit);
unsigned __cdecl mt19937_next_u32();
float __cdecl lookup_orientation_sine_quantized_abs(float phase);
extern int g_match_identifier;

} // namespace th105

#endif
