#pragma once
#include <stddef.h>

namespace th105 {
class UdongeActionStateView;
extern int g_match_identifier;
unsigned __cdecl udonge_random(int);
unsigned __cdecl udonge_random_u32();
float __cdecl udonge_atan(float, float);
float __cdecl udonge_tangent(float);
float __cdecl udonge_sine(float);
float __cdecl udonge_cosine(float);
float __fastcall udonge_surface(UdongeActionStateView *);
unsigned char __fastcall udonge_on_surface(UdongeActionStateView *);
struct UdongeActionScratch { void reset(); };

// Partial receiver; never instantiate as a recovered complete Fighter.
class UdongeActionStateView {
public:
    virtual void scalar_delete_slot_00();
    virtual int set_action_sequence_and_finalize(short, int);
    virtual int set_action_and_finalize(short);
    virtual int select_sequence(int);
    virtual int reset_sequence();
    virtual unsigned char next_sequence_block();
    virtual int previous_sequence_block();
    virtual int set_sequence_frame(short);

    void dispatch_character_wave_handle(unsigned);
    void dispatch_action_state_vslot28();
    unsigned char landing();
    int crossed();
    unsigned char advance();
    void zero_motion();
    void event(unsigned);
    void flip();
    unsigned char directional(int);
    void layout(float);
    int spawn(int, float, float, signed char, int, const void *, int);
    void effect(int, float, float, unsigned char, int);
    void counter(short, int);
    int phase_counter(int);
    void texture(signed char, short);
    void finalize(int);
    void copy_health();
    void sequence_window(signed char, int, int);
    void secondary_cycle();
    void common_update();

    __forceinline bool entry(short seq) {
        return !time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e == seq;
    }
    __forceinline void reset_action_scratch() {
        reinterpret_cast<UdongeActionScratch *>(reinterpret_cast<unsigned char *>(this) + 4)->reset();
    }
    __forceinline void spawn_offset(int object, int xoff, double height, float *p, int count, int layer = 1) {
        spawn(
            object,
            xoff == 0 ? x_ec
                : xoff < 0 ? static_cast<float>(x_ec - (-xoff * facing_104))
                           : static_cast<float>(xoff * facing_104 + x_ec),
            height == 0.0 ? y_f0
                : height < 0.0 ? static_cast<float>(y_f0 - (-height))
                               : static_cast<float>(y_f0 + height),
            facing_104,
            layer,
            p,
            count);
    }
    __forceinline void idle_motion() {
        if (!byte_47e) {
            zero_motion();
        } else {
            if (velocity_x_f4 > 0.0f) {
                velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.5);
                if (velocity_x_f4 < 0.0f) {
                    zero_motion();
                    byte_47e = 0;
                }
            }
            if (velocity_x_f4 < 0.0f) {
                velocity_x_f4 = static_cast<float>(velocity_x_f4 + 0.5);
                if (velocity_x_f4 > 0.0f) {
                    zero_motion();
                    byte_47e = 0;
                }
            }
        }
    }
    __forceinline void face_without_velocity() {
        if (x_ec > fighter_170->x_ec) facing_104 = -1;
        if (x_ec < fighter_170->x_ec) facing_104 = 1;
    }
    __forceinline void dash_dust(bool reverse) {
        effect(
            124,
            static_cast<float>(x_ec + 50.0 - static_cast<float>(udonge_random_u32() % 100u)),
            static_cast<float>(static_cast<float>(udonge_random_u32() % 200u) + y_f0),
            reverse ? static_cast<unsigned char>(-facing_104) : static_cast<unsigned char>(facing_104),
            1);
    }
    __forceinline void dash_effects(bool reverse, double height, bool ahead) {
        effect(
            125,
            ahead ? static_cast<float>(80 * facing_104 + x_ec) : x_ec,
            static_cast<float>(y_f0 + height),
            reverse ? static_cast<unsigned char>(-facing_104) : static_cast<unsigned char>(facing_104),
            1);
        effect(
            126,
            x_ec,
            static_cast<float>(y_f0 + height),
            reverse ? static_cast<unsigned char>(-facing_104) : static_cast<unsigned char>(facing_104),
            1);
        event(31);
    }
    __forceinline void aim_to_peer() {
        float dx = static_cast<float>((fighter_170->x_ec - x_ec) * static_cast<signed char>(facing_104));
        field_744 = -udonge_atan(fighter_170->y_f0 - y_f0, dx);
    }
    __forceinline void fan800(int xoff, double height, bool aimed) {
        float p[3];
        if (aimed) field_744 = static_cast<float>((static_cast<float>(udonge_random(9)) - 4.0) + field_744);
        else field_744 = static_cast<float>(static_cast<float>(udonge_random(9)) - 4.0);
        p[0] = field_744; p[1] = 25.0f; p[2] = 0.0f; spawn_offset(800, xoff, height, p, 3);
        p[2] = 1.0f; spawn_offset(800, xoff, height, p, 3);
        p[0] = static_cast<float>(field_744 + 5.0); p[2] = 4.0f; spawn_offset(800, xoff, height, p, 3);
        p[0] = static_cast<float>(field_744 - 5.0); p[2] = 4.0f; spawn_offset(800, xoff, height, p, 3);
        p[0] = static_cast<float>(field_744 + 10.0); p[2] = 4.0f; spawn_offset(800, xoff, height, p, 3);
        p[0] = static_cast<float>(field_744 - 10.0); p[2] = 4.0f; spawn_offset(800, xoff, height, p, 3);
        phase_counter(10);
    }
    __forceinline void aim_short(short lo, short hi) {
        float dx = static_cast<float>((fighter_170->x_ec - x_ec) * static_cast<signed char>(facing_104));
        word_734 = static_cast<short>(-static_cast<short>(static_cast<int>(udonge_atan(fighter_170->y_f0 - y_f0, dx))));
        if (word_734 < lo) word_734 = lo;
        if (word_734 > hi) word_734 = hi;
    }
    __forceinline void fan801(int xoff, double height, bool charged, bool air = false) {
        float p[3]; p[0] = static_cast<float>(word_734); p[1] = 5.0f; p[2] = charged ? 7.0f : 0.0f;
        spawn_offset(801, xoff, height, p, 3); p[2] = 4.0f; spawn_offset(801, xoff, height, p, 3);
        p[0] = static_cast<float>(word_734 + (charged ? 45.0 : 15.0)); p[2] = charged ? 9.0f : 8.0f; spawn_offset(801, xoff, height, p, 3);
        p[0] = static_cast<float>(word_734 - (charged ? 45.0 : 15.0)); p[2] = charged ? 9.0f : 8.0f; spawn_offset(801, xoff, height, p, 3);
        if (air) { dispatch_character_wave_handle(3); velocity_x_f4 = -6.0f; velocity_y_f8 = 5.0f; acceleration_y_100 = 0.6f; phase_counter(50); }
        else { phase_counter(50); dispatch_character_wave_handle(3); }
    }
    __forceinline void expand_cone() {
        if (field_73c > 0.0f) {
            field_7b0 += field_73c;
            field_73c = static_cast<float>(field_73c - static_cast<double>(0.2f));
            if (field_73c < 0.25f) field_73c = 0.25f;
        }
    }
    __forceinline void spawn_at_peer(int object, float *p) {
        spawn(object, fighter_170->x_ec, static_cast<float>(fighter_170->y_f0 + 100.0), facing_104, 1, p, 3);
    }
    __forceinline bool peer_in_cone() {
        if (facing_104 == 1 && fighter_170->x_ec > x_ec &&
            fighter_170->y_f0 < udonge_tangent(field_7b0) * (fighter_170->x_ec - x_ec) + y_f0 &&
            fighter_170->y_f0 > udonge_tangent(-field_7b0) * (fighter_170->x_ec - x_ec) + y_f0)
            return true;
        if (facing_104 == -1 && fighter_170->x_ec < x_ec &&
            fighter_170->y_f0 < udonge_tangent(field_7b0) * (x_ec - fighter_170->x_ec) + y_f0 &&
            fighter_170->y_f0 > udonge_tangent(-field_7b0) * (x_ec - fighter_170->x_ec) + y_f0)
            return true;
        return false;
    }
    __forceinline void beam_pair826(float *p) {
        spawn(826, x_ec, y_f0, facing_104, 1, p, 3);
        spawn(826, x_ec, y_f0, static_cast<unsigned char>(-static_cast<signed char>(facing_104)), 1, p, 3);
    }
    __forceinline void begin_beams826(bool diagonal) {
        word_730 = 0; field_73c = 0.0f; field_740 = 40.0f;
        dispatch_character_wave_handle(19); counter(200, 120); phase_counter(50); field_180 = 1;
        float p[3];
        if (diagonal) {
            p[0] = -45.0f; p[1] = 0.0f; p[2] = 1.0f; beam_pair826(p);
            p[0] = 45.0f; p[1] = 0.0f; p[2] = 1.0f; beam_pair826(p);
            if (byte_60b >= 4) {
                p[1] = 0.0f; p[2] = 1.0f; p[0] = 90.0f; spawn_offset(826, 0, 0.0, p, 3);
                p[0] = 90.0f; spawn(826, x_ec, y_f0, static_cast<unsigned char>(-static_cast<signed char>(facing_104)), 1, p, 3);
            }
        } else {
            p[0] = 0.0f; p[1] = 0.0f; p[2] = 1.0f; beam_pair826(p);
            if (byte_60b >= 4) {
                p[0] = -45.0f; p[1] = 0.0f; p[2] = 1.0f; beam_pair826(p);
                p[0] = 45.0f; p[1] = 0.0f; p[2] = 1.0f; beam_pair826(p);
            }
        }
        p[2] = 5.0f; spawn_offset(826, 0, 100.0, p, 3);
    }
    __forceinline void spell_flash(int xoff, double height, int window) {
        word_48a = 40; event(23);
        effect(
            115,
            xoff < 0 ? static_cast<float>(x_ec - (-xoff * static_cast<signed char>(facing_104)))
                : xoff ? static_cast<float>(xoff * static_cast<signed char>(facing_104) + x_ec) : x_ec,
            static_cast<float>(y_f0 + height),
            facing_104,
            1);
        sequence_window(0, window, 60); secondary_cycle();
    }
    __forceinline void orbit900(float *p) {
        spawn(
            900,
            static_cast<float>(udonge_cosine(-p[0]) * 100.0 * static_cast<signed char>(facing_104) + x_ec),
            static_cast<float>(udonge_sine(-p[0]) * 100.0 + y_f0 + 85.0),
            facing_104,
            1,
            p,
            3);
    }
    __forceinline void orbit852(float *p) {
        spawn(
            852,
            static_cast<float>(udonge_cosine(-p[0]) * 100.0 * static_cast<signed char>(facing_104) + x_ec),
            static_cast<float>(udonge_sine(-p[0]) * 100.0 + (y_f0 + 130.0)),
            facing_104,
            1,
            p,
            4);
    }

    unsigned char unknown_004[0xe8];
    float x_ec;
    float y_f0;
    float velocity_x_f4;
    float velocity_y_f8;
    unsigned char unknown_0fc[0x4];
    float acceleration_y_100;
    signed char facing_104;
    unsigned char unknown_105[0xe];
    unsigned char byte_113;
    unsigned char unknown_114[0x18];
    float field_12c;
    unsigned char unknown_130[0xc];
    short action_id_13c;
    short sequence_index_13e;
    short frame_index_140;
    short frame_timer_142;
    int time_counter_144;
    unsigned char unknown_148[0x28];
    UdongeActionStateView *fighter_170;
    short word_174;
    unsigned char unknown_176[0xa];
    int field_180;
    unsigned char byte_184;
    unsigned char unknown_185;
    short word_186;
    unsigned char unknown_188[0x2f6];
    signed char byte_47e;
    unsigned char byte_47f;
    unsigned char unknown_480[0x2];
    short word_482;
    unsigned char unknown_484[0x6];
    short word_48a;
    short word_48c;
    unsigned char unknown_48e[0x1a];
    short word_4a8;
    unsigned char unknown_4aa[0x2];
    short word_4ac;
    short word_4ae;
    unsigned char unknown_4b0[0x8];
    int field_4b8;
    float field_4bc;
    float field_4c0;
    unsigned char unknown_4c4[0x142];
    signed char byte_606;
    unsigned char unknown_607[0x3];
    signed char byte_60a;
    signed char byte_60b;
    unsigned char unknown_60c[0x49];
    unsigned char byte_655;
    unsigned char unknown_656[0x5e];
    int field_6b4;
    int field_6b8;
    int field_6bc;
    int field_6c0;
    int field_6c4;
    int field_6c8;
    unsigned char unknown_6cc[0x60];
    signed char byte_72c;
    unsigned char unknown_72d[0x3];
    short word_730;
    short word_732;
    short word_734;
    short word_736;
    unsigned char unknown_738[0x4];
    float field_73c;
    float field_740;
    float field_744;
    unsigned char unknown_748[0x8];
    unsigned char byte_750;
    unsigned char byte_751;
    unsigned char unknown_752[0x12];
    short word_764;
    short word_766;
    short word_768;
    short word_76a;
    short word_76c;
    unsigned char unknown_76e[0x32];
    short word_7a0;
    short word_7a2;
    unsigned char unknown_7a4[0x2];
    short word_7a6;
    float field_7a8;
    short word_7ac;
    short word_7ae;
    float field_7b0;
    float field_7b4;
    int field_7b8;
};

typedef char check_udonge_x_ec[offsetof(UdongeActionStateView, x_ec) == 0xec ? 1 : -1];
typedef char check_udonge_y_f0[offsetof(UdongeActionStateView, y_f0) == 0xf0 ? 1 : -1];
typedef char check_udonge_velocity_x_f4[offsetof(UdongeActionStateView, velocity_x_f4) == 0xf4 ? 1 : -1];
typedef char check_udonge_velocity_y_f8[offsetof(UdongeActionStateView, velocity_y_f8) == 0xf8 ? 1 : -1];
typedef char check_udonge_acceleration_y_100[offsetof(UdongeActionStateView, acceleration_y_100) == 0x100 ? 1 : -1];
typedef char check_udonge_facing_104[offsetof(UdongeActionStateView, facing_104) == 0x104 ? 1 : -1];
typedef char check_udonge_byte_113[offsetof(UdongeActionStateView, byte_113) == 0x113 ? 1 : -1];
typedef char check_udonge_field_12c[offsetof(UdongeActionStateView, field_12c) == 0x12c ? 1 : -1];
typedef char check_udonge_action_id_13c[offsetof(UdongeActionStateView, action_id_13c) == 0x13c ? 1 : -1];
typedef char check_udonge_sequence_index_13e[offsetof(UdongeActionStateView, sequence_index_13e) == 0x13e ? 1 : -1];
typedef char check_udonge_frame_index_140[offsetof(UdongeActionStateView, frame_index_140) == 0x140 ? 1 : -1];
typedef char check_udonge_frame_timer_142[offsetof(UdongeActionStateView, frame_timer_142) == 0x142 ? 1 : -1];
typedef char check_udonge_time_counter_144[offsetof(UdongeActionStateView, time_counter_144) == 0x144 ? 1 : -1];
typedef char check_udonge_fighter_170[offsetof(UdongeActionStateView, fighter_170) == 0x170 ? 1 : -1];
typedef char check_udonge_word_174[offsetof(UdongeActionStateView, word_174) == 0x174 ? 1 : -1];
typedef char check_udonge_field_180[offsetof(UdongeActionStateView, field_180) == 0x180 ? 1 : -1];
typedef char check_udonge_byte_184[offsetof(UdongeActionStateView, byte_184) == 0x184 ? 1 : -1];
typedef char check_udonge_word_186[offsetof(UdongeActionStateView, word_186) == 0x186 ? 1 : -1];
typedef char check_udonge_byte_47e[offsetof(UdongeActionStateView, byte_47e) == 0x47e ? 1 : -1];
typedef char check_udonge_byte_47f[offsetof(UdongeActionStateView, byte_47f) == 0x47f ? 1 : -1];
typedef char check_udonge_word_482[offsetof(UdongeActionStateView, word_482) == 0x482 ? 1 : -1];
typedef char check_udonge_word_48a[offsetof(UdongeActionStateView, word_48a) == 0x48a ? 1 : -1];
typedef char check_udonge_word_48c[offsetof(UdongeActionStateView, word_48c) == 0x48c ? 1 : -1];
typedef char check_udonge_word_4a8[offsetof(UdongeActionStateView, word_4a8) == 0x4a8 ? 1 : -1];
typedef char check_udonge_word_4ac[offsetof(UdongeActionStateView, word_4ac) == 0x4ac ? 1 : -1];
typedef char check_udonge_word_4ae[offsetof(UdongeActionStateView, word_4ae) == 0x4ae ? 1 : -1];
typedef char check_udonge_field_4b8[offsetof(UdongeActionStateView, field_4b8) == 0x4b8 ? 1 : -1];
typedef char check_udonge_field_4bc[offsetof(UdongeActionStateView, field_4bc) == 0x4bc ? 1 : -1];
typedef char check_udonge_field_4c0[offsetof(UdongeActionStateView, field_4c0) == 0x4c0 ? 1 : -1];
typedef char check_udonge_byte_606[offsetof(UdongeActionStateView, byte_606) == 0x606 ? 1 : -1];
typedef char check_udonge_byte_60a[offsetof(UdongeActionStateView, byte_60a) == 0x60a ? 1 : -1];
typedef char check_udonge_byte_60b[offsetof(UdongeActionStateView, byte_60b) == 0x60b ? 1 : -1];
typedef char check_udonge_byte_655[offsetof(UdongeActionStateView, byte_655) == 0x655 ? 1 : -1];
typedef char check_udonge_field_6b4[offsetof(UdongeActionStateView, field_6b4) == 0x6b4 ? 1 : -1];
typedef char check_udonge_field_6b8[offsetof(UdongeActionStateView, field_6b8) == 0x6b8 ? 1 : -1];
typedef char check_udonge_field_6bc[offsetof(UdongeActionStateView, field_6bc) == 0x6bc ? 1 : -1];
typedef char check_udonge_field_6c0[offsetof(UdongeActionStateView, field_6c0) == 0x6c0 ? 1 : -1];
typedef char check_udonge_field_6c4[offsetof(UdongeActionStateView, field_6c4) == 0x6c4 ? 1 : -1];
typedef char check_udonge_field_6c8[offsetof(UdongeActionStateView, field_6c8) == 0x6c8 ? 1 : -1];
typedef char check_udonge_byte_72c[offsetof(UdongeActionStateView, byte_72c) == 0x72c ? 1 : -1];
typedef char check_udonge_word_730[offsetof(UdongeActionStateView, word_730) == 0x730 ? 1 : -1];
typedef char check_udonge_word_732[offsetof(UdongeActionStateView, word_732) == 0x732 ? 1 : -1];
typedef char check_udonge_word_734[offsetof(UdongeActionStateView, word_734) == 0x734 ? 1 : -1];
typedef char check_udonge_word_736[offsetof(UdongeActionStateView, word_736) == 0x736 ? 1 : -1];
typedef char check_udonge_field_73c[offsetof(UdongeActionStateView, field_73c) == 0x73c ? 1 : -1];
typedef char check_udonge_field_740[offsetof(UdongeActionStateView, field_740) == 0x740 ? 1 : -1];
typedef char check_udonge_field_744[offsetof(UdongeActionStateView, field_744) == 0x744 ? 1 : -1];
typedef char check_udonge_byte_750[offsetof(UdongeActionStateView, byte_750) == 0x750 ? 1 : -1];
typedef char check_udonge_byte_751[offsetof(UdongeActionStateView, byte_751) == 0x751 ? 1 : -1];
typedef char check_udonge_word_764[offsetof(UdongeActionStateView, word_764) == 0x764 ? 1 : -1];
typedef char check_udonge_word_766[offsetof(UdongeActionStateView, word_766) == 0x766 ? 1 : -1];
typedef char check_udonge_word_768[offsetof(UdongeActionStateView, word_768) == 0x768 ? 1 : -1];
typedef char check_udonge_word_76a[offsetof(UdongeActionStateView, word_76a) == 0x76a ? 1 : -1];
typedef char check_udonge_word_76c[offsetof(UdongeActionStateView, word_76c) == 0x76c ? 1 : -1];
typedef char check_udonge_word_7a0[offsetof(UdongeActionStateView, word_7a0) == 0x7a0 ? 1 : -1];
typedef char check_udonge_word_7a2[offsetof(UdongeActionStateView, word_7a2) == 0x7a2 ? 1 : -1];
typedef char check_udonge_word_7a6[offsetof(UdongeActionStateView, word_7a6) == 0x7a6 ? 1 : -1];
typedef char check_udonge_field_7a8[offsetof(UdongeActionStateView, field_7a8) == 0x7a8 ? 1 : -1];
typedef char check_udonge_word_7ac[offsetof(UdongeActionStateView, word_7ac) == 0x7ac ? 1 : -1];
typedef char check_udonge_word_7ae[offsetof(UdongeActionStateView, word_7ae) == 0x7ae ? 1 : -1];
typedef char check_udonge_field_7b0[offsetof(UdongeActionStateView, field_7b0) == 0x7b0 ? 1 : -1];
typedef char check_udonge_field_7b4[offsetof(UdongeActionStateView, field_7b4) == 0x7b4 ? 1 : -1];
typedef char check_udonge_field_7b8[offsetof(UdongeActionStateView, field_7b8) == 0x7b8 ? 1 : -1];
}
