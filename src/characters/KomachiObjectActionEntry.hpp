#ifndef TH105_KOMACHI_OBJECT_ACTION_ENTRY_HPP
#define TH105_KOMACHI_OBJECT_ACTION_ENTRY_HPP

#include <stddef.h>

namespace th105 {

struct KomachiEntryMotionView {
    unsigned char base_000;
    void set_components(float angle, float magnitude);
};

// Pointer-only primary-vtable view. Never construct or embed this receiver.
class KomachiObjectEntryView {
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
    void replace_secondary(int key, float half_width, int subdivisions, int bands, int blend);
    float stage_height();
    void *spawn_parented(int action, float x, float y, unsigned char facing,
                         int layer, const unsigned *words, int count);
    void *spawn_unparented(int action, float x, float y, unsigned char facing,
                           int layer, const unsigned *words, int count);

    KomachiEntryMotionView motion_004;
    unsigned char pad_005[0xe7];
    float x_ec;
    float y_f0;
    float velocity_x_f4;
    float velocity_y_f8;
    unsigned char pad_0fc[0x8];
    unsigned char facing_104;
    unsigned char pad_105[0xe];
    unsigned char alpha_113;
    unsigned char pad_114[0x8];
    float scale_x_11c;
    float scale_y_120;
    float field_124;
    float field_128;
    float rotation_12c;
    unsigned char pad_130[0xc];
    short action_id_13c;
    short sequence_id_13e;
    unsigned char pad_140[0x4];
    int time_counter_144;
    unsigned char pad_148[0x34];
    unsigned char byte_17c;
    unsigned char pad_17d[0x7];
    unsigned char byte_184;
    unsigned char pad_185[0x1bb];
    float *params_340;
    unsigned char pad_344[0x20];
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

typedef char CheckKomachiEntry_x_ec[offsetof(KomachiObjectEntryView, x_ec) == 0xec ? 1 : -1];
typedef char CheckKomachiEntry_facing_104[offsetof(KomachiObjectEntryView, facing_104) == 0x104 ? 1 : -1];
typedef char CheckKomachiEntry_alpha_113[offsetof(KomachiObjectEntryView, alpha_113) == 0x113 ? 1 : -1];
typedef char CheckKomachiEntry_rotation_12c[offsetof(KomachiObjectEntryView, rotation_12c) == 0x12c ? 1 : -1];
typedef char CheckKomachiEntry_action_id_13c[offsetof(KomachiObjectEntryView, action_id_13c) == 0x13c ? 1 : -1];
typedef char CheckKomachiEntry_time_counter_144[offsetof(KomachiObjectEntryView, time_counter_144) == 0x144 ? 1 : -1];
typedef char CheckKomachiEntry_byte_184[offsetof(KomachiObjectEntryView, byte_184) == 0x184 ? 1 : -1];
typedef char CheckKomachiEntry_params_340[offsetof(KomachiObjectEntryView, params_340) == 0x340 ? 1 : -1];
typedef char CheckKomachiEntry_word_364[offsetof(KomachiObjectEntryView, word_364) == 0x364 ? 1 : -1];
typedef char CheckKomachiEntry_field_370[offsetof(KomachiObjectEntryView, field_370) == 0x370 ? 1 : -1];
typedef char CheckKomachiEntry_word_386[offsetof(KomachiObjectEntryView, word_386) == 0x386 ? 1 : -1];

int __cdecl selector_random_roll(int limit);
unsigned __cdecl mt19937_next_u32();
extern int g_match_identifier;

} // namespace th105

#endif
