#pragma once
#include <stddef.h>

namespace th105 {
class SuikaActionStateView;
extern int g_match_identifier;
unsigned __cdecl suika_random(int);
unsigned __cdecl suika_random_u32();
float __cdecl suika_atan(float, float);
float __cdecl suika_square(float);
float __cdecl suika_sine_int(int);
float __cdecl suika_absolute(float);
float __cdecl suika_sine(float);
float __cdecl suika_cosine(float);
float __fastcall suika_surface(SuikaActionStateView *);
unsigned char __fastcall suika_on_surface(SuikaActionStateView *);
struct SuikaActionScratch { void reset(); void oriented_components(float, float); };

// Partial receiver; never instantiate as a recovered complete Fighter.
class SuikaActionStateView {
public:
    virtual void scalar_delete_slot_00();
    virtual int set_action_sequence_and_finalize(short, int);
    virtual int set_action_and_finalize(short);
    virtual int select_sequence(int);
    virtual int reset_sequence();
    virtual unsigned char next_sequence_block();
    virtual int previous_sequence_block();
    virtual int set_sequence_frame(short);
    virtual unsigned char next_sequence_frame();

    void dispatch_character_wave_handle(unsigned);
    void forward_hit_quantity(int, int, short, signed char);
    void dispatch_action_state_vslot28();
    unsigned char landing();
    int crossed();
    signed char classify_fighter_x_boundary();
    unsigned char advance();
    void zero_motion();
    void event(unsigned);
    void flip();
    unsigned char directional(int);
    void layout(float);
    void consume_steps(signed char);
    void set_counter_48a(short);
    signed char shared_first(signed char, float);
    signed char shared_second(signed char, float);
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
        reinterpret_cast<SuikaActionScratch *>(reinterpret_cast<unsigned char *>(this) + 4)->reset();
    }
    __forceinline void dash_dust(bool reverse) {
        effect(124,
            static_cast<float>(x_ec + 50.0 - static_cast<float>(suika_random_u32() % 100u)),
            static_cast<float>(static_cast<float>(suika_random_u32() % 200u) + y_f0),
            reverse ? static_cast<unsigned char>(-facing_104) : static_cast<unsigned char>(facing_104), 1);
    }
    __forceinline void dash_effects(bool reverse, double height, bool ahead) {
        effect(125,
            ahead ? static_cast<float>(80 * facing_104 + x_ec) : x_ec,
            static_cast<float>(y_f0 + height),
            reverse ? static_cast<unsigned char>(-facing_104) : static_cast<unsigned char>(facing_104), 1);
        effect(126, x_ec, static_cast<float>(y_f0 + height),
            reverse ? static_cast<unsigned char>(-facing_104) : static_cast<unsigned char>(facing_104), 1);
        event(31);
    }
    __forceinline void decelerate(double step, bool clear) {
        velocity_x_f4 = static_cast<float>(velocity_x_f4 - step);
        if (velocity_x_f4 < 0.0f) { velocity_x_f4 = 0.0f; if (clear) byte_47e = 0; }
    }
    __forceinline void spawn_offset(int object, int xoff, double height, float *p, int count, int layer = 1) {
        spawn(object,
            xoff == 0 ? x_ec : xoff < 0 ? static_cast<float>(x_ec - (-xoff * facing_104)) : static_cast<float>(xoff * facing_104 + x_ec),
            height == 0.0 ? y_f0 : height < 0.0 ? static_cast<float>(y_f0 - (-height)) : static_cast<float>(y_f0 + height),
            facing_104, layer, p, count);
    }
    __forceinline void idle_motion() {
        if (!byte_47e) {
            zero_motion();
        } else {
            if (velocity_x_f4 > 0.0f) {
                velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.5);
                if (velocity_x_f4 < 0.0f) { zero_motion(); byte_47e = 0; }
            }
            if (velocity_x_f4 < 0.0f) {
                velocity_x_f4 = static_cast<float>(velocity_x_f4 + 0.5);
                if (velocity_x_f4 > 0.0f) { zero_motion(); byte_47e = 0; }
            }
        }
    }
    __forceinline void ground_face() {
        if (x_ec > fighter_170->x_ec) facing_104 = -1;
        if (x_ec < fighter_170->x_ec) facing_104 = 1;
    }
    __forceinline void aim_short(short low, short high) {
        float dx = static_cast<float>((fighter_170->x_ec - x_ec) * facing_104);
        word_734 = static_cast<short>(-static_cast<short>(static_cast<int>(suika_atan(fighter_170->y_f0 - y_f0, dx))));
        if (word_734 < low) word_734 = low;
        if (word_734 > high) word_734 = high;
    }
    __forceinline void aim_float(float minimum, float maximum) {
        float dx = static_cast<float>((fighter_170->x_ec - x_ec) * facing_104);
        field_744 = -suika_atan(fighter_170->y_f0 - y_f0, dx);
        if (field_744 < minimum) field_744 = minimum;
        if (field_744 > maximum) field_744 = maximum;
    }
    __forceinline void release_fragments811() {
        word_732 = 1; float p[3]; p[2] = 1.0f; float n = 0.0f;
        do {
            p[0] = static_cast<float>((n * 60.0 - 20.0) + static_cast<float>(suika_random(40)));
            p[1] = static_cast<float>(static_cast<float>(suika_random(8)) + 30.0);
            if (p[0] < 0.0f || p[0] > 180.0f) word_730 = -1; else word_730 = 1;
            spawn_offset(811, 40, 0.0, p, 3, static_cast<unsigned char>(word_730));
            n = static_cast<float>(n + 1.0);
        } while (n < 6.0f);
    }
    __forceinline void impact_fragments811() {
        float p[3] = {0.0f, 0.0f, 0.0f}; spawn_offset(811, 40, 0.0, p, 3);
        p[2] = 2.0f; spawn_offset(811, 40, 0.0, p, 3, -1); p[2] = 1.0f; float n = 0.0f;
        do {
            p[0] = static_cast<float>((n * 60.0 - 20.0) + static_cast<float>(suika_random(40)));
            p[1] = static_cast<float>(static_cast<float>(suika_random(8)) + 30.0);
            if (p[0] < 0.0f || p[0] > 180.0f) word_730 = -1; else word_730 = 1;
            spawn_offset(811, 40, 0.0, p, 3, static_cast<unsigned char>(word_730));
            n = static_cast<float>(n + 1.0);
        } while (n < 6.0f);
    }
    __forceinline void mist817() {
        float p[3];
        p[0] = static_cast<float>(suika_random(360));
        p[1] = static_cast<float>(static_cast<float>(suika_random(5)) + 5.0);
        p[2] = 5.0f;
        spawn(817,
            static_cast<float>(static_cast<double>(static_cast<float>(suika_random(60))) + x_ec - 30.0),
            static_cast<float>(static_cast<double>(static_cast<float>(suika_random(60))) + y_f0 + 30.0),
            facing_104, 1, p, 3);
    }
    __forceinline void steer_cloud(double rate) {
        velocity_x_f4 = static_cast<float>(velocity_x_f4 + facing_104 * (field_6b4 * rate));
        velocity_y_f8 = static_cast<float>(velocity_y_f8 - field_6b8 * rate);
        if (velocity_x_f4 > 10.0f) velocity_x_f4 = 10.0f;
        if (velocity_x_f4 < -10.0f) velocity_x_f4 = -10.0f;
        if (velocity_y_f8 > 10.0f) velocity_y_f8 = 10.0f;
        if (velocity_y_f8 < -10.0f) velocity_y_f8 = -10.0f;
    }
    __forceinline void shot808_burst(bool air, bool phase) {
        if (word_730 > 0 && (sequence_index_13e == 2 || sequence_index_13e == 3)) {
            if (word_730 % 4 == 1) {
                if (phase) phase_counter(10);
                field_180 = 1; aim_short(-10, 10); dispatch_character_wave_handle(9);
                if (!air) effect(129, x_ec, y_f0, facing_104, -1);
                if (air ? word_738 == 1 : byte_750 == 1) {
                    double base = word_734 + 30.0;
                    float p[3]; p[0] = static_cast<float>(base - static_cast<float>(suika_random_u32() % 60u)); p[1] = 15.0f; p[2] = static_cast<float>(suika_random(4));
                    spawn_offset(808, 44, 85.0, p, 3);
                } else {
                    double base = word_734 + 30.0;
                    float p[3]; p[0] = static_cast<float>(base - static_cast<float>(suika_random_u32() % 60u)); p[1] = 15.0f; p[2] = static_cast<float>(suika_random(4));
                    spawn_offset(808, 44, 85.0, p, 3);
                }
            }
            ++word_730;
        }
    }
    __forceinline void spell_flash(int xoff, double height, int window) {
        set_counter_48a(40); event(23);
        effect(115,
            xoff < 0 ? static_cast<float>(x_ec - (-xoff * facing_104))
                : xoff ? static_cast<float>(xoff * facing_104 + x_ec) : x_ec,
            static_cast<float>(y_f0 + height), facing_104, 1);
        sequence_window(0, window, 60); secondary_cycle();
    }
    __forceinline void sync_grab_peer() {
        fighter_170->x_ec = static_cast<float>(facing_104 * (velocity_x_f4 + 45.0) + x_ec);
        fighter_170->y_f0 = static_cast<float>(y_f0 + 120.0 + velocity_y_f8);
    }
    __forceinline void pose_grab_peer(float rotation, int xoff, double height) {
        fighter_170->field_12c = rotation;
        fighter_170->x_ec = xoff < 0 ? static_cast<float>(x_ec - (-xoff * facing_104)) : static_cast<float>(xoff * facing_104 + x_ec);
        fighter_170->y_f0 = static_cast<float>(y_f0 + height);
    }
    __forceinline void ending_smoke999() {
        float p[3]; p[0] = static_cast<float>(suika_random(360));
        p[1] = static_cast<float>(static_cast<float>(static_cast<float>(suika_random(50)) * static_cast<double>(0.1f)) + 6.0);
        p[2] = 1.0f;
        spawn_offset(999, 0, 100.0, p, 3);
    }
    __forceinline void ending_fragments811() {
        float p[3]; float n = 0.0f;
        do {
            p[0] = static_cast<float>((n * 36.0 - 20.0) + static_cast<float>(suika_random(40)));
            p[1] = static_cast<float>(static_cast<float>(suika_random(8)) + 30.0);
            p[2] = 1.0f;
            if (p[0] < 0.0f || p[0] > 180.0f) word_730 = -1; else word_730 = 1;
            spawn_offset(811, 40, 0.0, p, 3, static_cast<unsigned char>(word_730));
            n = static_cast<float>(n + 1.0);
        } while (n < 10.0f);
    }
    __forceinline void burst999() {
        float n = 0.0f; float p[3];
        do {
            p[0] = static_cast<float>((n * 45.0 - 20.0) + static_cast<float>(suika_random(40)));
            p[1] = static_cast<float>(static_cast<float>(suika_random(13)) + 12.0);
            p[2] = 0.0f;
            spawn_offset(999, 0, 100.0, p, 3);
            n = static_cast<float>(n + 1.0);
        } while (n < 8.0f);
    }
    __forceinline void orbit_particle930() {
        float p[3]; p[0] = static_cast<float>(suika_random(360)); p[1] = static_cast<float>(suika_random(120)); p[2] = 1.0f;
        spawn(930,
            static_cast<float>(suika_cosine(-p[0]) * p[1] + x_ec),
            static_cast<float>(suika_sine(-p[0]) * p[1] + y_f0),
            facing_104, 1, p, 3);
    }
    __forceinline void shot_particle930() {
        float p[3]; p[0] = static_cast<float>(suika_random(360)); p[1] = 0.0f; p[2] = 4.0f;
        float radius = static_cast<float>(suika_random(120));
        spawn(930,
            static_cast<float>(suika_cosine(-p[0]) * radius + x_ec),
            static_cast<float>(suika_sine(-p[0]) * radius + y_f0),
            facing_104, 1, p, 3);
    }
    __forceinline void moving_grab_pose(float rotation, double xoff, double height) {
        fighter_170->field_12c = rotation;
        fighter_170->x_ec = static_cast<float>(facing_104 * (velocity_x_f4 + xoff) + x_ec);
        if (height == 0.0) fighter_170->y_f0 = static_cast<float>(velocity_y_f8 + y_f0);
        else fighter_170->y_f0 = static_cast<float>((y_f0 + height) + velocity_y_f8);
    }
    __forceinline void moving_grab_vertical() {
        fighter_170->field_12c = 0.0f;
        double offset = velocity_x_f4 * (-30.0);
        fighter_170->x_ec = static_cast<float>(offset * facing_104 + x_ec);
        fighter_170->y_f0 = static_cast<float>(y_f0 + 110.0 + velocity_y_f8);
        fighter_170->set_action_and_finalize(107);
    }
    __forceinline void grab_impact_effect(int object, int xoff) {
        effect(object, static_cast<float>(xoff * facing_104 + x_ec), static_cast<float>(y_f0 + 10.0), facing_104, 1);
    }
    __forceinline void giant_ring855(float *p, float count, double spacing, float speed, int xoff) {
        float n = 0.0f;
        do {
            p[0] = static_cast<float>((n * spacing - 20.0) + static_cast<float>(suika_random(40)));
            p[1] = speed; p[2] = 2.0f;
            if (p[0] < 0.0f || p[0] > 180.0f) word_730 = -1; else word_730 = 1;
            spawn_offset(855, xoff, 0.0, p, 3, static_cast<unsigned char>(word_730));
            n = static_cast<float>(n + 1.0);
        } while (n < count);
    }
    __forceinline void giant_ring920(int object, float *p, float count, double spacing, float speed, int xoff) {
        float n = 0.0f;
        do {
            p[0] = static_cast<float>((n * spacing - 20.0) + static_cast<float>(suika_random(40)));
            p[1] = speed; p[2] = 2.0f;
            if (p[0] < 0.0f || p[0] > 180.0f) word_730 = -1; else word_730 = 1;
            spawn_offset(object, xoff, 0.0, p, 3, static_cast<unsigned char>(word_730));
            n = static_cast<float>(n + 1.0);
        } while (n < count);
    }
    __forceinline void update_oriented_velocity() {
        reinterpret_cast<SuikaActionScratch *>(reinterpret_cast<unsigned char *>(this) + 4)->oriented_components(field_744, field_740);
    }

    unsigned char unknown_004[0xe8];
    float x_ec;
    float y_f0;
    float velocity_x_f4;
    float velocity_y_f8;
    unsigned char unknown_0fc[0x4];
    float acceleration_y_100;
    signed char facing_104;
    unsigned char unknown_105[0x3];
    float field_108;
    float field_10c;
    unsigned char unknown_110[0x3];
    unsigned char byte_113;
    unsigned char unknown_114[0x8];
    float scale_x_11c;
    float scale_y_120;
    unsigned char unknown_124[0x8];
    float field_12c;
    unsigned char unknown_130[0xc];
    short action_id_13c;
    short sequence_index_13e;
    short frame_index_140;
    short frame_timer_142;
    int time_counter_144;
    unsigned char unknown_148[0x20];
    SuikaActionStateView * owner_168;
    unsigned char unknown_16c[0x4];
    SuikaActionStateView * fighter_170;
    short word_174;
    unsigned char unknown_176[0x6];
    unsigned char byte_17c;
    unsigned char unknown_17d[0x3];
    int field_180;
    signed char byte_184;
    unsigned char unknown_185;
    short word_186;
    unsigned char unknown_188[0x4];
    float field_18c;
    float field_190;
    unsigned char unknown_194[0x2ea];
    signed char byte_47e;
    unsigned char byte_47f;
    unsigned char unknown_480[0x2];
    short word_482;
    unsigned char unknown_484[0x8];
    short word_48c;
    unsigned char unknown_48e[0x1a];
    short word_4a8;
    unsigned char unknown_4aa[0x2];
    short word_4ac;
    short word_4ae;
    unsigned char unknown_4b0[0x2];
    short word_4b2;
    unsigned char unknown_4b4[0x4];
    int field_4b8;
    unsigned char unknown_4bc[0x4];
    float field_4c0;
    unsigned char unknown_4c4[0x140];
    signed char byte_604;
    unsigned char unknown_605;
    signed char byte_606;
    unsigned char unknown_607[0x2];
    signed char byte_609;
    signed char byte_60a;
    unsigned char unknown_60b[0x4a];
    unsigned char byte_655;
    unsigned char unknown_656[0x56];
    float field_6ac;
    unsigned char unknown_6b0[0x4];
    int field_6b4;
    int field_6b8;
    int field_6bc;
    int field_6c0;
    int field_6c4;
    int field_6c8;
    unsigned char unknown_6cc[0x10];
    unsigned int uint_6dc;
    unsigned int uint_6e0;
    unsigned int uint_6e4;
    unsigned char unknown_6e8[0xc];
    unsigned int uint_6f4;
    unsigned int uint_6f8;
    unsigned int uint_6fc;
    unsigned char unknown_700[0x2c];
    unsigned char byte_72c;
    unsigned char unknown_72d[0x3];
    short word_730;
    short word_732;
    short word_734;
    short word_736;
    short word_738;
    unsigned char unknown_73a[0x2];
    float field_73c;
    float field_740;
    float field_744;
    float field_748;
    unsigned char unknown_74c[0x4];
    unsigned char byte_750;
    unsigned char unknown_751[0x13];
    short word_764;
    short word_766;
    short word_768;
    short word_76a;
    short word_76c;
    unsigned char unknown_76e[0x32];
    short word_7a0;
    short word_7a2;
    short word_7a4;
    short word_7a6;
};

typedef char check_suika_x_ec[offsetof(SuikaActionStateView, x_ec) == 0xec ? 1 : -1];
typedef char check_suika_y_f0[offsetof(SuikaActionStateView, y_f0) == 0xf0 ? 1 : -1];
typedef char check_suika_velocity_x_f4[offsetof(SuikaActionStateView, velocity_x_f4) == 0xf4 ? 1 : -1];
typedef char check_suika_velocity_y_f8[offsetof(SuikaActionStateView, velocity_y_f8) == 0xf8 ? 1 : -1];
typedef char check_suika_acceleration_y_100[offsetof(SuikaActionStateView, acceleration_y_100) == 0x100 ? 1 : -1];
typedef char check_suika_facing_104[offsetof(SuikaActionStateView, facing_104) == 0x104 ? 1 : -1];
typedef char check_suika_field_108[offsetof(SuikaActionStateView, field_108) == 0x108 ? 1 : -1];
typedef char check_suika_field_10c[offsetof(SuikaActionStateView, field_10c) == 0x10c ? 1 : -1];
typedef char check_suika_byte_113[offsetof(SuikaActionStateView, byte_113) == 0x113 ? 1 : -1];
typedef char check_suika_scale_x_11c[offsetof(SuikaActionStateView, scale_x_11c) == 0x11c ? 1 : -1];
typedef char check_suika_scale_y_120[offsetof(SuikaActionStateView, scale_y_120) == 0x120 ? 1 : -1];
typedef char check_suika_field_12c[offsetof(SuikaActionStateView, field_12c) == 0x12c ? 1 : -1];
typedef char check_suika_action_id_13c[offsetof(SuikaActionStateView, action_id_13c) == 0x13c ? 1 : -1];
typedef char check_suika_sequence_index_13e[offsetof(SuikaActionStateView, sequence_index_13e) == 0x13e ? 1 : -1];
typedef char check_suika_frame_index_140[offsetof(SuikaActionStateView, frame_index_140) == 0x140 ? 1 : -1];
typedef char check_suika_frame_timer_142[offsetof(SuikaActionStateView, frame_timer_142) == 0x142 ? 1 : -1];
typedef char check_suika_time_counter_144[offsetof(SuikaActionStateView, time_counter_144) == 0x144 ? 1 : -1];
typedef char check_suika_owner_168[offsetof(SuikaActionStateView, owner_168) == 0x168 ? 1 : -1];
typedef char check_suika_fighter_170[offsetof(SuikaActionStateView, fighter_170) == 0x170 ? 1 : -1];
typedef char check_suika_word_174[offsetof(SuikaActionStateView, word_174) == 0x174 ? 1 : -1];
typedef char check_suika_byte_17c[offsetof(SuikaActionStateView, byte_17c) == 0x17c ? 1 : -1];
typedef char check_suika_field_180[offsetof(SuikaActionStateView, field_180) == 0x180 ? 1 : -1];
typedef char check_suika_byte_184[offsetof(SuikaActionStateView, byte_184) == 0x184 ? 1 : -1];
typedef char check_suika_word_186[offsetof(SuikaActionStateView, word_186) == 0x186 ? 1 : -1];
typedef char check_suika_field_18c[offsetof(SuikaActionStateView, field_18c) == 0x18c ? 1 : -1];
typedef char check_suika_field_190[offsetof(SuikaActionStateView, field_190) == 0x190 ? 1 : -1];
typedef char check_suika_byte_47e[offsetof(SuikaActionStateView, byte_47e) == 0x47e ? 1 : -1];
typedef char check_suika_byte_47f[offsetof(SuikaActionStateView, byte_47f) == 0x47f ? 1 : -1];
typedef char check_suika_word_482[offsetof(SuikaActionStateView, word_482) == 0x482 ? 1 : -1];
typedef char check_suika_word_48c[offsetof(SuikaActionStateView, word_48c) == 0x48c ? 1 : -1];
typedef char check_suika_word_4a8[offsetof(SuikaActionStateView, word_4a8) == 0x4a8 ? 1 : -1];
typedef char check_suika_word_4ac[offsetof(SuikaActionStateView, word_4ac) == 0x4ac ? 1 : -1];
typedef char check_suika_word_4ae[offsetof(SuikaActionStateView, word_4ae) == 0x4ae ? 1 : -1];
typedef char check_suika_word_4b2[offsetof(SuikaActionStateView, word_4b2) == 0x4b2 ? 1 : -1];
typedef char check_suika_field_4b8[offsetof(SuikaActionStateView, field_4b8) == 0x4b8 ? 1 : -1];
typedef char check_suika_field_4c0[offsetof(SuikaActionStateView, field_4c0) == 0x4c0 ? 1 : -1];
typedef char check_suika_byte_604[offsetof(SuikaActionStateView, byte_604) == 0x604 ? 1 : -1];
typedef char check_suika_byte_606[offsetof(SuikaActionStateView, byte_606) == 0x606 ? 1 : -1];
typedef char check_suika_byte_609[offsetof(SuikaActionStateView, byte_609) == 0x609 ? 1 : -1];
typedef char check_suika_byte_60a[offsetof(SuikaActionStateView, byte_60a) == 0x60a ? 1 : -1];
typedef char check_suika_byte_655[offsetof(SuikaActionStateView, byte_655) == 0x655 ? 1 : -1];
typedef char check_suika_field_6ac[offsetof(SuikaActionStateView, field_6ac) == 0x6ac ? 1 : -1];
typedef char check_suika_field_6b4[offsetof(SuikaActionStateView, field_6b4) == 0x6b4 ? 1 : -1];
typedef char check_suika_field_6b8[offsetof(SuikaActionStateView, field_6b8) == 0x6b8 ? 1 : -1];
typedef char check_suika_field_6bc[offsetof(SuikaActionStateView, field_6bc) == 0x6bc ? 1 : -1];
typedef char check_suika_field_6c0[offsetof(SuikaActionStateView, field_6c0) == 0x6c0 ? 1 : -1];
typedef char check_suika_field_6c4[offsetof(SuikaActionStateView, field_6c4) == 0x6c4 ? 1 : -1];
typedef char check_suika_field_6c8[offsetof(SuikaActionStateView, field_6c8) == 0x6c8 ? 1 : -1];
typedef char check_suika_uint_6dc[offsetof(SuikaActionStateView, uint_6dc) == 0x6dc ? 1 : -1];
typedef char check_suika_uint_6e0[offsetof(SuikaActionStateView, uint_6e0) == 0x6e0 ? 1 : -1];
typedef char check_suika_uint_6e4[offsetof(SuikaActionStateView, uint_6e4) == 0x6e4 ? 1 : -1];
typedef char check_suika_uint_6f4[offsetof(SuikaActionStateView, uint_6f4) == 0x6f4 ? 1 : -1];
typedef char check_suika_uint_6f8[offsetof(SuikaActionStateView, uint_6f8) == 0x6f8 ? 1 : -1];
typedef char check_suika_uint_6fc[offsetof(SuikaActionStateView, uint_6fc) == 0x6fc ? 1 : -1];
typedef char check_suika_byte_72c[offsetof(SuikaActionStateView, byte_72c) == 0x72c ? 1 : -1];
typedef char check_suika_word_730[offsetof(SuikaActionStateView, word_730) == 0x730 ? 1 : -1];
typedef char check_suika_word_732[offsetof(SuikaActionStateView, word_732) == 0x732 ? 1 : -1];
typedef char check_suika_word_734[offsetof(SuikaActionStateView, word_734) == 0x734 ? 1 : -1];
typedef char check_suika_word_736[offsetof(SuikaActionStateView, word_736) == 0x736 ? 1 : -1];
typedef char check_suika_word_738[offsetof(SuikaActionStateView, word_738) == 0x738 ? 1 : -1];
typedef char check_suika_field_73c[offsetof(SuikaActionStateView, field_73c) == 0x73c ? 1 : -1];
typedef char check_suika_field_740[offsetof(SuikaActionStateView, field_740) == 0x740 ? 1 : -1];
typedef char check_suika_field_744[offsetof(SuikaActionStateView, field_744) == 0x744 ? 1 : -1];
typedef char check_suika_field_748[offsetof(SuikaActionStateView, field_748) == 0x748 ? 1 : -1];
typedef char check_suika_byte_750[offsetof(SuikaActionStateView, byte_750) == 0x750 ? 1 : -1];
typedef char check_suika_word_764[offsetof(SuikaActionStateView, word_764) == 0x764 ? 1 : -1];
typedef char check_suika_word_766[offsetof(SuikaActionStateView, word_766) == 0x766 ? 1 : -1];
typedef char check_suika_word_768[offsetof(SuikaActionStateView, word_768) == 0x768 ? 1 : -1];
typedef char check_suika_word_76a[offsetof(SuikaActionStateView, word_76a) == 0x76a ? 1 : -1];
typedef char check_suika_word_76c[offsetof(SuikaActionStateView, word_76c) == 0x76c ? 1 : -1];
typedef char check_suika_word_7a0[offsetof(SuikaActionStateView, word_7a0) == 0x7a0 ? 1 : -1];
typedef char check_suika_word_7a2[offsetof(SuikaActionStateView, word_7a2) == 0x7a2 ? 1 : -1];
typedef char check_suika_word_7a4[offsetof(SuikaActionStateView, word_7a4) == 0x7a4 ? 1 : -1];
typedef char check_suika_word_7a6[offsetof(SuikaActionStateView, word_7a6) == 0x7a6 ? 1 : -1];
}
