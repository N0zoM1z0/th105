#ifndef TH105_REMILIA_OBJECT_UPDATE_HPP
#define TH105_REMILIA_OBJECT_UPDATE_HPP

#include <stddef.h>

namespace th105 {

class RemiliaUpdateMotionView {
public:
    void set_components(float angle, float magnitude);

    unsigned char opaque_000[0xe8];
};

struct RemiliaUpdateOwnerView {
    unsigned char pad_000[0xec];
    float x_ec;
    float y_f0;
    float velocity_x_f4;
    float velocity_y_f8;
    unsigned char pad_0fc[0x40];
    short action_id_13c;
    short sequence_index_13e;
    short frame_index_140;
    unsigned char pad_142[0x32];
    short word_174;
    unsigned char pad_176[0x10];
    short word_186;
    unsigned char pad_188[0x5a8];
    short word_730;
    unsigned char pad_732[0x1f];
    unsigned char byte_751;

    void dispatch_character_wave_handle(unsigned index);
};

// Matches CharacterObject's non-primary CObjectBase subobject at +0x330.
class RemiliaLifetimeBase {
public:
    __forceinline void retire() { --lifetime_330; }

    int lifetime_330;
    unsigned char pad_334[0x4];
};

// Matches CharacterObject's primary AttackObject base at +0x000..+0x330.
class RemiliaAttackBase {
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void select_sequence(short sequence);
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual void dispatch_slot20();
    virtual void slot24();
    virtual void update_action_state();

    RemiliaUpdateMotionView motion_004;
    float x_ec;
    float y_f0;
    float velocity_x_f4;
    float velocity_y_f8;
    unsigned char pad_0fc[0x8];
    signed char facing_104;
    unsigned char pad_105[0xb];
    unsigned char color_b_110;
    unsigned char color_g_111;
    unsigned char color_r_112;
    unsigned char color_a_113;
    unsigned char pad_114[0x8];
    float scale_x_11c;
    float scale_y_120;
    unsigned char pad_124[0x8];
    float rotation_12c;
    unsigned char pad_130[0xc];
    short action_id_13c;
    short sequence_index_13e;
    short frame_index_140;
    short frame_timer_142;
    int time_counter_144;
    unsigned char pad_148[0x28];
    RemiliaUpdateOwnerView *target_170;
    unsigned char pad_174[0xc];
    int field_180;
    signed char byte_184;
    unsigned char pad_185[0x1ab];
};

// Pointer-only primary call view: never construct or embed this receiver.
class RemiliaObjectUpdateView : public RemiliaLifetimeBase, public RemiliaAttackBase {
public:
    virtual void update_action_state();

    unsigned char emit_repeated(int mode, int count200, int count201);
    unsigned char advance_frame();
    unsigned char advance_phase(int limit);
    void replace_secondary(short key, float width, int subdivisions, int bands, int blend);
    void turn_heading(float bias, float max_step, float y_offset);
    void *position_relative(int x, int y);
    void *spawn_unparented(int action, float x, float y, unsigned char facing, int layer, const unsigned *words, int count);
    float stage_surface_height_at_x();
    void update_ping_pong_motion();

    unsigned char pad_338[0x8];
    float *params_340;
    unsigned char pad_344[0x4];
    RemiliaUpdateOwnerView *owner_348;
    RemiliaObjectUpdateView *related_34c;
    unsigned char pad_350[0x14];
    short word_364;
    unsigned char pad_366[0xa];
    float field_370;
    float field_374;
    float field_378;
    float field_37c;
    float field_380;
    short word_384;
};

#define REMILIA_UPD_CHECK(T, M, OFF) \
    typedef char Check_##T##_##M[offsetof(T, M) == (OFF) ? 1 : -1]

REMILIA_UPD_CHECK(RemiliaUpdateOwnerView, x_ec, 0x0ec);
REMILIA_UPD_CHECK(RemiliaUpdateOwnerView, y_f0, 0x0f0);
REMILIA_UPD_CHECK(RemiliaUpdateOwnerView, velocity_x_f4, 0x0f4);
REMILIA_UPD_CHECK(RemiliaUpdateOwnerView, velocity_y_f8, 0x0f8);
REMILIA_UPD_CHECK(RemiliaUpdateOwnerView, action_id_13c, 0x13c);
REMILIA_UPD_CHECK(RemiliaUpdateOwnerView, sequence_index_13e, 0x13e);
REMILIA_UPD_CHECK(RemiliaUpdateOwnerView, frame_index_140, 0x140);
REMILIA_UPD_CHECK(RemiliaUpdateOwnerView, word_174, 0x174);
REMILIA_UPD_CHECK(RemiliaUpdateOwnerView, word_186, 0x186);
REMILIA_UPD_CHECK(RemiliaUpdateOwnerView, word_730, 0x730);
REMILIA_UPD_CHECK(RemiliaUpdateOwnerView, byte_751, 0x751);

typedef char Check_RemiliaLifetimeBase_size[sizeof(RemiliaLifetimeBase) == 0x08 ? 1 : -1];
typedef char Check_RemiliaAttackBase_size[sizeof(RemiliaAttackBase) == 0x330 ? 1 : -1];

REMILIA_UPD_CHECK(RemiliaObjectUpdateView, motion_004, 0x004);
REMILIA_UPD_CHECK(RemiliaObjectUpdateView, x_ec, 0x0ec);
REMILIA_UPD_CHECK(RemiliaObjectUpdateView, y_f0, 0x0f0);
REMILIA_UPD_CHECK(RemiliaObjectUpdateView, velocity_x_f4, 0x0f4);
REMILIA_UPD_CHECK(RemiliaObjectUpdateView, velocity_y_f8, 0x0f8);
REMILIA_UPD_CHECK(RemiliaObjectUpdateView, facing_104, 0x104);
REMILIA_UPD_CHECK(RemiliaObjectUpdateView, color_b_110, 0x110);
REMILIA_UPD_CHECK(RemiliaObjectUpdateView, color_g_111, 0x111);
REMILIA_UPD_CHECK(RemiliaObjectUpdateView, color_r_112, 0x112);
REMILIA_UPD_CHECK(RemiliaObjectUpdateView, color_a_113, 0x113);
REMILIA_UPD_CHECK(RemiliaObjectUpdateView, scale_x_11c, 0x11c);
REMILIA_UPD_CHECK(RemiliaObjectUpdateView, scale_y_120, 0x120);
REMILIA_UPD_CHECK(RemiliaObjectUpdateView, rotation_12c, 0x12c);
REMILIA_UPD_CHECK(RemiliaObjectUpdateView, action_id_13c, 0x13c);
REMILIA_UPD_CHECK(RemiliaObjectUpdateView, sequence_index_13e, 0x13e);
REMILIA_UPD_CHECK(RemiliaObjectUpdateView, frame_index_140, 0x140);
REMILIA_UPD_CHECK(RemiliaObjectUpdateView, frame_timer_142, 0x142);
REMILIA_UPD_CHECK(RemiliaObjectUpdateView, time_counter_144, 0x144);
REMILIA_UPD_CHECK(RemiliaObjectUpdateView, target_170, 0x170);
REMILIA_UPD_CHECK(RemiliaObjectUpdateView, field_180, 0x180);
REMILIA_UPD_CHECK(RemiliaObjectUpdateView, byte_184, 0x184);
REMILIA_UPD_CHECK(RemiliaObjectUpdateView, lifetime_330, 0x330);
REMILIA_UPD_CHECK(RemiliaObjectUpdateView, params_340, 0x340);
REMILIA_UPD_CHECK(RemiliaObjectUpdateView, owner_348, 0x348);
REMILIA_UPD_CHECK(RemiliaObjectUpdateView, related_34c, 0x34c);
REMILIA_UPD_CHECK(RemiliaObjectUpdateView, word_364, 0x364);
REMILIA_UPD_CHECK(RemiliaObjectUpdateView, field_370, 0x370);
REMILIA_UPD_CHECK(RemiliaObjectUpdateView, field_374, 0x374);
REMILIA_UPD_CHECK(RemiliaObjectUpdateView, field_378, 0x378);
REMILIA_UPD_CHECK(RemiliaObjectUpdateView, field_37c, 0x37c);
REMILIA_UPD_CHECK(RemiliaObjectUpdateView, field_380, 0x380);
REMILIA_UPD_CHECK(RemiliaObjectUpdateView, word_384, 0x384);

#undef REMILIA_UPD_CHECK

int __cdecl selector_random_roll(int limit);
float __cdecl atan2_degrees(float y, float x);
float __cdecl lookup_orientation_sine_quantized_abs(float angle);
float __cdecl lookup_orientation_cosine_quantized_abs(float angle);

} // namespace th105

#endif
