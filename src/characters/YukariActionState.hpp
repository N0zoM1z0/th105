#pragma once
#include <stddef.h>
#include <deque>
#include "battle/SpellRuntime.hpp"

namespace th105 {
class YukariActionStateView;
extern int g_match_identifier;
unsigned __cdecl yukari_random(int);
unsigned __cdecl yukari_random_u32();
float __cdecl yukari_atan(float, float);
float __cdecl sqrt_float_value(float);
float __cdecl absolute_scalar_float(float);
float __cdecl yukari_sine(float);
float __cdecl yukari_cosine(float);
float __fastcall yukari_surface(YukariActionStateView *);
unsigned char __fastcall yukari_on_surface(YukariActionStateView *);
struct YukariActionScratch { void reset(); };

// Partial receiver; never instantiate as a recovered complete Fighter.
class YukariActionStateView {
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

    unsigned char pad_004[0xe8];
    float x_ec;
    float y_f0;
    float velocity_x_f4;
    float velocity_y_f8;
    unsigned char pad_0fc[0x4];
    float acceleration_y_100;
    signed char facing_104;
    unsigned char pad_105[0x3];
    float field_108;
    float field_10c;
    unsigned char pad_110[0x3];
    unsigned char byte_113;
    unsigned char pad_114[0x8];
    float field_11c;
    unsigned char pad_120[0xc];
    float field_12c;
    unsigned char pad_130[0xc];
    short action_id_13c;
    short sequence_index_13e;
    short frame_index_140;
    short frame_timer_142;
    int time_counter_144;
    unsigned char pad_148[0x20];
    YukariActionStateView *owner_168;
    unsigned char pad_16c[0x4];
    YukariActionStateView *fighter_170;
    unsigned char pad_174[0x8];
    unsigned char byte_17c;
    unsigned char pad_17d[0x3];
    int field_180;
    unsigned char byte_184;
    unsigned char pad_185[0x1];
    short word_186;
    unsigned char pad_188[0x2f6];
    unsigned char byte_47e;
    unsigned char byte_47f;
    unsigned char pad_480[0x2];
    short word_482;
    unsigned char pad_484[0x6];
    short word_48a;
    short word_48c;
    unsigned char pad_48e[0x2];
    unsigned char byte_490;
    unsigned char pad_491[0x17];
    short word_4a8;
    unsigned char pad_4aa[0x2];
    short word_4ac;
    short word_4ae;
    unsigned char pad_4b0[0x8];
    int field_4b8;
    unsigned char pad_4bc[0x9e];
    signed char byte_55a;
    unsigned char pad_55b[0x1];
    std::deque<FighterSequenceSlot> cards_55c;
    unsigned char pad_570[0x95];
    signed char byte_605;
    unsigned char pad_606[0x3];
    signed char byte_609;
    unsigned char pad_60a[0x4b];
    unsigned char byte_655;
    unsigned char pad_656[0x56];
    float field_6ac;
    unsigned char pad_6b0[0x4];
    int field_6b4;
    int field_6b8;
    int field_6bc;
    int field_6c0;
    int field_6c4;
    int field_6c8;
    unsigned char pad_6cc[0x60];
    unsigned char byte_72c;
    unsigned char pad_72d[0x3];
    short word_730;
    short word_732;
    short word_734;
    short word_736;
    short word_738;
    unsigned char pad_73a[0x2];
    float field_73c;
    float field_740;
    float field_744;
    unsigned char pad_748[0x8];
    unsigned char byte_750;
    unsigned char byte_751;
    unsigned char pad_752[0x12];
    short word_764;
    short word_766;
    short word_768;
    short word_76a;
    short word_76c;
    unsigned char pad_76e[0x32];
    short word_7a0;
    short word_7a2;
    short word_7a4;
    unsigned char pad_7a6[0x16];
    short word_7bc;
    short word_7be;
    short word_7c0;
    unsigned char pad_7c2[0x2];
    short word_7c4;
    short word_7c6;

    __forceinline bool entry(short seq) {
        return !time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e == seq;
    }
    __forceinline void reset_action_scratch() {
        reinterpret_cast<YukariActionScratch *>(reinterpret_cast<unsigned char *>(this) + 4)->reset();
    }
    __forceinline void dash_dust(bool reverse) {
        double base = x_ec + 50.0;
        if (reverse) {
            effect(124, static_cast<float>(base - static_cast<float>(yukari_random_u32() % 100u)),
                   static_cast<float>(static_cast<float>(yukari_random_u32() % 200u) + y_f0),
                   static_cast<unsigned char>(-facing_104), 1);
        } else {
            effect(124, static_cast<float>(base - static_cast<float>(yukari_random_u32() % 100u)),
                   static_cast<float>(static_cast<float>(yukari_random_u32() % 200u) + y_f0),
                   static_cast<unsigned char>(facing_104), 1);
        }
    }
    __forceinline void dash_effects(bool reverse, double height, bool ahead) {
        if (reverse) {
            effect(125, ahead ? static_cast<float>(80 * static_cast<signed char>(-facing_104) + static_cast<double>(x_ec)) : x_ec,
                   static_cast<float>(y_f0 + height), static_cast<unsigned char>(-facing_104), 1);
            effect(126, x_ec, static_cast<float>(y_f0 + height), static_cast<unsigned char>(-facing_104), 1);
        } else {
            effect(125, ahead ? static_cast<float>(80 * facing_104 + static_cast<double>(x_ec)) : x_ec,
                   static_cast<float>(y_f0 + height), static_cast<unsigned char>(facing_104), 1);
            effect(126, x_ec, static_cast<float>(y_f0 + height), static_cast<unsigned char>(facing_104), 1);
        }
        event(31);
    }
    __forceinline void idle_motion() {
        if (!byte_47e) { zero_motion(); return; }
        if (velocity_x_f4 > 0.0f) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.5);
            if (velocity_x_f4 < 0.0f) { zero_motion(); byte_47e = 0; }
        }
        if (velocity_x_f4 < 0.0f) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 + 0.5);
            if (velocity_x_f4 > 0.0f) { zero_motion(); byte_47e = 0; }
        }
    }
    __forceinline void ground_face() {
        if (x_ec > fighter_170->x_ec) facing_104 = -1;
        if (x_ec < fighter_170->x_ec) facing_104 = 1;
    }
    __forceinline void normal_jump(float vx) {
        if (!sequence_index_13e) {
            landing();
            if (!sequence_index_13e && !byte_47e) zero_motion();
        }
        if (sequence_index_13e > 0) {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(crossed())) {
                set_action_and_finalize(10); y_f0 = yukari_surface(this); zero_motion(); return;
            }
        }
        advance();
        if (entry(1)) { velocity_x_f4 = vx; velocity_y_f8 = 12.5f; acceleration_y_100 = 0.55f; byte_47e = 0; }
    }
    __forceinline void spawn_offset(int object, int xoff, double height, float *p, int count) {
        spawn(object,
            xoff == 0 ? x_ec : static_cast<float>(xoff * facing_104 + static_cast<double>(x_ec)),
            static_cast<float>(y_f0 + height), facing_104, 1, p, count);
    }
    __forceinline void ensure_recovery_object() {
        if (!word_7a4) { word_7a4 = 1; spawn(999, x_ec, y_f0, facing_104, -1, 0, 0); }
    }
    __forceinline void recovery_land(short action) {
        word_730 = static_cast<short>(100 * static_cast<int>(velocity_x_f4));
        word_732 = static_cast<short>(100 * static_cast<int>(velocity_y_f8));
        zero_motion(); y_f0 = yukari_surface(this); set_action_and_finalize(action);
    }
    __forceinline void recovery_slide(double step, bool counter_velocity) {
        if (classify_fighter_x_boundary() && velocity_x_f4 < 0.0f) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 + step);
            if (velocity_x_f4 > 0.0f) velocity_x_f4 = 0.0f;
            if (byte_490) field_6ac = counter_velocity ? static_cast<float>(word_730 * -2.0) : velocity_x_f4;
        }
    }
    __forceinline bool recovery_entry_sequence() {
        if (entry(1)) { ensure_recovery_object(); if (velocity_y_f8 != 0.0f) { if (velocity_x_f4 == 0.0f) select_sequence(3); else select_sequence(2); return true; } }
        return false;
    }
    __forceinline void packet981(float mode) {
        float p[3] = {0.0f, 0.0f, mode}; spawn(981, x_ec, y_f0, facing_104, -1, p, 3);
    }
    __forceinline void packet981_pair() {
        float p[3] = {0.0f, 0.0f, 0.0f}; spawn(981, x_ec, y_f0, facing_104, -1, p, 3);
        p[2] = 6.0f; spawn(981, x_ec, y_f0, facing_104, -1, p, 3);
    }
    __forceinline bool recover_action() {
        if (!advance()) return false;
        if (byte_72c == 2) { set_action_and_finalize(700); word_4a8 = 3; word_4ac = 3; return true; }
        set_action_and_finalize(0); if (field_6b8 > 0) set_action_and_finalize(1); return false;
    }
    __forceinline void decelerate(double amount, bool clear) {
        velocity_x_f4 = static_cast<float>(velocity_x_f4 - amount);
        if (velocity_x_f4 < 0.0f) { velocity_x_f4 = 0.0f; if (clear) byte_47e = 0; }
    }
    __forceinline void packet848(float mode, int layer) {
        float p[3] = {0.0f, 0.0f, mode}; spawn(848, x_ec, y_f0, facing_104, layer, p, 3);
    }
    __forceinline void aim800(float cap) {
        field_744 = -yukari_atan(fighter_170->y_f0 - y_f0, static_cast<float>((fighter_170->x_ec - x_ec) * static_cast<double>(facing_104)));
        if (field_744 < -cap) field_744 = -cap;
        if (field_744 > cap) field_744 = cap;
    }
    __forceinline void charge800() {
        next_sequence_block();
        effect(62, static_cast<float>(30 * facing_104 + static_cast<double>(x_ec)), static_cast<float>(y_f0 + 190.0), static_cast<unsigned char>(facing_104), 1);
    }
    __forceinline void fan800(double height, bool air) {
        if (word_730 != 1) return;
        if (!sequence_index_13e) {
            if (word_732 % 3 == 0 && word_734 < 5) {
                field_180 = 1; if (air && !word_734) counter(200, 45);
                float p[3]; for (int n = 0; n < 45; n += 15) { p[0] = static_cast<float>((field_744 - 20.0) + 10 * word_734 + n - 15.0); p[1] = 10.0f; p[2] = 0.0f; spawn_offset(800, 82, height, p, 3); }
                phase_counter(10); dispatch_character_wave_handle(2); ++word_734;
            }
        } else {
            if (word_732 % 3 == (air ? 1 : 0) && word_734 < 5) {
                field_180 = 1; if (air && !word_734) counter(200, 45);
                float p[3]; for (int n = 0; n < 75; n += 15) { p[0] = static_cast<float>((field_744 - 20.0) + 10 * word_734 + n - 30.0); p[1] = 10.0f; p[2] = 0.0f; spawn_offset(800, 82, height, p, 3); }
                phase_counter(10); dispatch_character_wave_handle(2); ++word_734;
            }
        }
        ++word_732;
    }
    __forceinline void ground800() {
        landing(); if (!field_6c0) byte_750 = 0; fan800(135.0, false);
        if (advance()) set_action_and_finalize(0); if (entry(1)) { set_action_and_finalize(0); return; }
        if (!sequence_index_13e) {
            if (!frame_timer_142 && frame_index_140 == 2 && byte_750) { charge800(); return; }
            if (!frame_timer_142 && frame_index_140 == 3) {
                word_730 = 1;
                field_744 = -yukari_atan(fighter_170->y_f0 - y_f0, static_cast<float>((fighter_170->x_ec - x_ec) * static_cast<double>(facing_104)));
                counter(200, 45);
                if (field_744 < -30.0f) field_744 = -30.0f; if (field_744 > 30.0f) field_744 = 30.0f;
            }
        }
        if (sequence_index_13e == 1 && !frame_timer_142 && frame_index_140 == 2) { word_730 = 1; counter(200, 45); aim800(30.0f); }
    }
    __forceinline void fan801(int x, double y, float angle) {
        float p[4];
        for (float n = 0.0f; n < 2.0f; n = static_cast<float>(n + 1.0)) { p[0] = angle; p[1] = 10.0f; p[2] = 0.0f; p[3] = static_cast<float>(5.0 + n * 5.0); spawn_offset(801, x, y, p, 4); }
        for (float n = 0.0f; n < 2.0f; n = static_cast<float>(n + 1.0)) { p[0] = angle; p[1] = -10.0f; p[2] = 0.0f; p[3] = static_cast<float>(n * 5.0 + 5.0); spawn_offset(801, x, y, p, 4); }
        p[0] = angle; p[1] = 0.0f; p[2] = 0.0f; p[3] = 0.0f; spawn_offset(801, x, y, p, 4);
    }
    __forceinline void split801(int x, double y) {
        float p[4];
        for (float n = 0.0f; n < 3.0f; n = static_cast<float>(n + 1.0)) { p[0] = -90.0f; p[1] = 10.0f; p[2] = 5.0f; p[3] = static_cast<float>(n * 5.0 + 10.0); spawn_offset(801, x, y, p, 4); }
        for (float n = 0.0f; n < 3.0f; n = static_cast<float>(n + 1.0)) { p[0] = 90.0f; p[1] = 10.0f; p[2] = 6.0f; p[3] = static_cast<float>(n * 5.0 + 10.0); spawn_offset(801, x, y, p, 4); }
    }
    __forceinline void ground810(int &control, int frame, int x) {
        landing(); byte_17c = 0; if (!control) byte_750 = 0;
        if (advance()) set_action_and_finalize(0); if (entry(1)) { set_action_and_finalize(0); return; }
        if (!sequence_index_13e && !frame_timer_142 && frame_index_140 == frame) { field_180 = 1; counter(200, 120); phase_counter(50); float p[3] = {0.0f, 0.0f, 0.0f}; spawn(810, static_cast<float>(x * facing_104 + static_cast<double>(x_ec)), 0.0f, facing_104, 1, p, 3); dispatch_character_wave_handle(10); }
    }
    __forceinline void air810(int &control, int x) {
        if (sequence_index_13e == 2) landing(); byte_17c = 0; if (!control) byte_750 = 0;
        if (advance()) set_action_and_finalize(0); if (entry(1) || entry(2)) { set_action_and_finalize(9); return; }
        if (!sequence_index_13e) { if (!frame_timer_142 && frame_index_140 == 4) { field_180 = 1; counter(200, 120); phase_counter(50); float p[3] = {0.0f, 0.0f, 0.0f}; spawn(810, static_cast<float>(x * facing_104 + static_cast<double>(x_ec)), 640.0f, facing_104, 1, p, 3); dispatch_character_wave_handle(10); } if (!frame_timer_142 && frame_index_140 == 7) acceleration_y_100 = 0.5f; }
    }
    __forceinline void ground811(int &control) {
        landing(); byte_17c = 4; if (!control) byte_750 = 0;
        if (advance()) set_action_and_finalize(0); if (entry(1)) { set_action_and_finalize(0); return; }
        if (!sequence_index_13e && !frame_timer_142 && frame_index_140 == 5) { counter(200, 120); phase_counter(50); float p[3] = {0.0f, 0.0f, 0.0f}; spawn_offset(811, 100, 145.0, p, 3); dispatch_character_wave_handle(17); }
    }
    __forceinline void ground812(int &control, int x, double y) {
        landing(); byte_17c = 8; if (!control) byte_750 = 0;
        if (advance()) set_action_and_finalize(0); if (entry(1)) { set_action_and_finalize(0); return; }
        if (!sequence_index_13e) {
            if (!frame_timer_142 && frame_index_140 == 4 && byte_750) { next_sequence_block(); effect(62, static_cast<float>(x_ec - 40 * facing_104), static_cast<float>(y_f0 + 158.0), static_cast<unsigned char>(facing_104), 1); return; }
            if (!frame_timer_142 && frame_index_140 == 5) { counter(200, 120); phase_counter(50); float p[3] = {0.0f, 0.0f, 0.0f}; spawn_offset(812, x, y, p, 3); dispatch_character_wave_handle(21); }
        }
        if (sequence_index_13e == 1 && !frame_timer_142 && frame_index_140 == 2) { counter(200, 120); phase_counter(50); float p[3] = {0.0f, 0.0f, 4.0f}; spawn_offset(812, x, y, p, 3); dispatch_character_wave_handle(21); }
    }
    __forceinline void air802(float speed, float first_x, float first_square, float second_x, float second_square) {
        if (sequence_index_13e == 5) landing(); byte_17c = 1;
        if (sequence_index_13e < 5) {
            if (sequence_index_13e == 4) { acceleration_y_100 = 0.6f; velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.6f)); }
            double y = y_f0 + static_cast<double>(velocity_y_f8);
            if (yukari_surface(this) >= y && velocity_y_f8 < 0.0f) { zero_motion(); y_f0 = yukari_surface(this); select_sequence(5); return; }
        }
        if (sequence_index_13e == 3 && !time_counter_144) {
            counter(200, 120); field_180 = 1; phase_counter(50); float p[3] = {0.0f, speed, 0.0f}; spawn_offset(802, 43, 107.0, p, 3);
            p[0] = yukari_atan(135.0f, first_x); float first_speed = static_cast<float>(sqrt_float_value(first_square) / 15.0); p[1] = first_speed; p[2] = 2.0f; spawn_offset(802, 43, 107.0, p, 3);
            p[0] = yukari_atan(-135.0f, first_x); p[1] = first_speed; spawn_offset(802, 43, 107.0, p, 3);
            p[0] = yukari_atan(-115.0f, second_x); float second_speed = static_cast<float>(sqrt_float_value(second_square) / 15.0); p[1] = second_speed; spawn_offset(802, 43, 107.0, p, 3);
            p[0] = yukari_atan(115.0f, second_x); p[1] = second_speed; spawn_offset(802, 43, 107.0, p, 3);
        }
        if (advance()) set_action_and_finalize(0); if (entry(5)) { set_action_and_finalize(9); return; } if (sequence_index_13e == 1 && time_counter_144 > 0) next_sequence_block();
    }
    __forceinline void hold816(int &control, float angle) {
        landing(); byte_17c = 5; if (!control) byte_750 = 0;
        if (sequence_index_13e == 1) { field_12c = static_cast<float>(field_12c - 40.0); if ((word_730 >= 15 && !byte_750) || word_730 >= 120) { next_sequence_block(); field_12c = 0.0f; return; } ++word_730; }
        if (advance()) set_action_and_finalize(0);
        if (entry(1) && !word_730) { counter(200, 120); phase_counter(50); float p[3] = {angle, 15.0f, 0.0f}; if (byte_609 >= 4) p[2] = 2.0f; spawn_offset(816, 0, 135.0, p, 3); field_108 = 0.0f; field_10c = 135.0f; dispatch_character_wave_handle(12); }
        if (sequence_index_13e == 2 && !frame_timer_142 && frame_index_140 == 8) { dispatch_character_wave_handle(18); field_180 = 1; }
    }
    __forceinline void projectile820(bool air, float mode, int wave) {
        if (!air || sequence_index_13e == 1) landing(); byte_17c = 2;
        if (air && !sequence_index_13e) { velocity_y_f8 -= acceleration_y_100; if (static_cast<unsigned char>(crossed())) { y_f0 = yukari_surface(this); next_sequence_block(); zero_motion(); return; } }
        if (advance()) set_action_and_finalize(0); if (air && entry(1)) { set_action_and_finalize(9); return; }
        if (!air || !sequence_index_13e) { if (!frame_timer_142 && frame_index_140 == 7) { field_180 = 1; counter(200, 120); phase_counter(25); float p[3] = {0.0f, 0.0f, mode}; spawn_offset(820, 65, 100.0, p, 3); dispatch_character_wave_handle(wave); } if (air && !frame_timer_142 && frame_index_140 == 14) acceleration_y_100 = 0.5f; }
    }
    __forceinline void projectile821(bool air) {
        if (!air || sequence_index_13e == 1) landing(); byte_17c = 6;
        if (air && !sequence_index_13e) { velocity_y_f8 -= acceleration_y_100; if (static_cast<unsigned char>(crossed())) { y_f0 = yukari_surface(this); next_sequence_block(); zero_motion(); return; } }
        if (advance()) set_action_and_finalize(0); if (air && entry(1)) { set_action_and_finalize(9); return; }
        if (!air || !sequence_index_13e) { if (!frame_timer_142 && frame_index_140 == 7) { field_180 = 1; counter(200, 120); phase_counter(50); ++word_7bc; float p[3] = {0.0f, static_cast<float>(word_7bc), 0.0f}; spawn_offset(821, 65, 100.0, p, 3); dispatch_character_wave_handle(19); } if (air && !frame_timer_142 && frame_index_140 == 14) acceleration_y_100 = 0.5f; }
    }
    __forceinline void vanish825() {
        field_108 = 0.0f; field_10c = 100.0f; field_11c = static_cast<float>(field_11c * static_cast<double>(0.8f));
    }
    __forceinline void opening825() {
        dispatch_character_wave_handle(15); float p[3] = {0.0f, 0.0f, 0.0f}; spawn(825, x_ec, static_cast<float>(y_f0 + 100.0), facing_104, -1, p, 3);
    }
    __forceinline void ground825() {
        if (sequence_index_13e > 0) landing(); byte_17c = 3;
        if (!sequence_index_13e) { if (frame_index_140 >= 5) vanish825(); } else decelerate(static_cast<double>(0.3f), false);
        if (sequence_index_13e == 1 && time_counter_144 >= 36) next_sequence_block(); if (advance()) set_action_and_finalize(0);
        if (!sequence_index_13e) {
            if (!frame_timer_142 && frame_index_140 == 2) opening825();
            {
                if (!frame_timer_142 && frame_index_140 == 5) { counter(200, 120); phase_counter(50); }
                if (!frame_timer_142 && frame_index_140 == 7) {
                    if (facing_104 * field_6b4 > 0) x_ec = static_cast<float>(450 * facing_104 + static_cast<double>(x_ec));
                    if (facing_104 * field_6b4 < 0) x_ec = static_cast<float>(x_ec - 300 * facing_104);
                    if (!field_6b4) x_ec = static_cast<float>(250 * facing_104 + static_cast<double>(x_ec));
                    if (x_ec > 980.0f && facing_104 == 1) x_ec = 980.0f;
                    if (x_ec < 200.0f && facing_104 == -1) x_ec = 200.0f;
                    y_f0 = yukari_surface(this);
                }
            }
        }
        if (sequence_index_13e == 1 && !frame_timer_142 && frame_index_140 == 3 && word_730 == 1) { byte_184 = 1; ++word_730; }
        if (entry(1)) { if (!word_730) { dispatch_character_wave_handle(16); float p[3] = {0.0f, 0.0f, 1.0f}; spawn(825, static_cast<float>(70 * facing_104 + static_cast<double>(x_ec)), static_cast<float>(y_f0 + 100.0), facing_104, -1, p, 3); time_counter_144 = 0; field_11c = 1.0f; velocity_x_f4 = 20.0f; word_4a8 = 6; word_4ac = 6; } ++word_730; }
    }
    __forceinline void diving825() {
        if (sequence_index_13e == 2) landing(); byte_17c = 3; if (!sequence_index_13e && frame_index_140 >= 5) vanish825();
        if (sequence_index_13e == 1) { field_108 = 0.0f; field_10c = 100.0f; field_12c = static_cast<float>(field_12c - 35.0); if (static_cast<unsigned char>(crossed())) { field_12c = 0.0f; y_f0 = yukari_surface(this); velocity_y_f8 = 0.0f; next_sequence_block(); } }
        if (sequence_index_13e == 2 && velocity_x_f4 != 0.0f) { velocity_x_f4 = static_cast<float>(velocity_x_f4 * static_cast<double>(0.8f)); if (absolute_scalar_float(velocity_x_f4) < 0.01f) velocity_x_f4 = 0.0f; }
        if (advance()) set_action_and_finalize(0);
        if (!sequence_index_13e) {
            if (!frame_timer_142 && frame_index_140 == 2) opening825();
            {
                if (!frame_timer_142 && frame_index_140 == 5) { counter(200, 120); phase_counter(50); }
                if (!frame_timer_142 && frame_index_140 == 7) { int input = field_6b4 * facing_104; if (input > 0) field_740 = 1.0f; else if (input < 0) field_740 = -1.0f; y_f0 = static_cast<float>(yukari_surface(this) + 600.0); }
            }
        }
        if (sequence_index_13e == 1 && time_counter_144 == 6) { byte_184 = 1; ++word_730; }
        if (entry(1)) { if (!word_730) { dispatch_character_wave_handle(16); float p[3] = {0.0f, 0.0f, 2.0f}; spawn(825, x_ec, y_f0, facing_104, -1, p, 3); time_counter_144 = 0; field_11c = 1.0f; velocity_x_f4 = 0.0f; velocity_y_f8 = -25.0f; velocity_x_f4 = static_cast<float>(field_740 * 25.0); word_4a8 = 6; word_4ac = 6; } ++word_730; }
    }
    __forceinline void opening826() {
        field_108 = 0.0f; field_10c = 135.0f; float p[3] = {0.0f, 0.0f, 1.0f}; spawn(826, x_ec, y_f0, facing_104, -1, p, 3);
        p[1] = 0.5f; p[2] = 4.0f; spawn(826, x_ec, y_f0, facing_104, -1, p, 3);
        p[2] = 4.0f; p[1] = 0.25f; spawn(826, x_ec, y_f0, facing_104, -1, p, 3); dispatch_character_wave_handle(1); counter(200, 120); phase_counter(50);
    }
    __forceinline void packet826(float mode) {
        float p[3] = {0.0f, 0.0f, mode}; spawn(826, x_ec, y_f0, facing_104, 1, p, 3);
    }
    __forceinline void launch826(float mode) {
        velocity_x_f4 = 6.0f; float p[3] = {0.0f, 0.5f, 4.0f}; spawn(826, x_ec, y_f0, facing_104, -1, p, 3);
        p[2] = 4.0f; p[1] = 0.25f; spawn(826, x_ec, y_f0, facing_104, -1, p, 3);
        p[2] = mode; spawn(826, x_ec, static_cast<float>(y_f0 - 250.0), facing_104, 1, p, 3); dispatch_character_wave_handle(1);
    }
    __forceinline void interval_clear() {
        if (field_180 && ++word_730 >= 6) { field_180 = 0; word_730 = 0; }
    }
    __forceinline void falling826() {
        velocity_y_f8 -= acceleration_y_100; if (time_counter_144 % 12 == 0) event(29); field_12c = static_cast<float>(field_12c - 40.0); interval_clear();
        if (static_cast<unsigned char>(crossed())) { reset_action_scratch(); y_f0 = yukari_surface(this); zero_motion(); next_sequence_block(); }
    }
    __forceinline void spell_flash(int xoff, double height, int outcome) {
        word_48a = 40; event(23);
        effect(115,
            xoff == 0 ? x_ec : xoff < 0 ? static_cast<float>(x_ec - (-xoff * facing_104)) : static_cast<float>(xoff * facing_104 + static_cast<double>(x_ec)),
            static_cast<float>(y_f0 + height), static_cast<unsigned char>(facing_104), 1);
        sequence_window(0, outcome, 60); secondary_cycle();
    }
    __forceinline void simple_spell(int object, int flash_frame, int flash_x, double flash_y, int window, int shot_frame, int shot_x, double shot_y, int wave) {
        landing(); texture(2, 2); if (advance()) set_action_and_finalize(0);
        if (!sequence_index_13e) {
            if (!frame_timer_142 && frame_index_140 == flash_frame) spell_flash(flash_x, flash_y, window);
            if (!frame_timer_142 && frame_index_140 == shot_frame) { float p[3] = {0.0f, 0.0f, 0.0f}; spawn_offset(object, shot_x, shot_y, p, 3); dispatch_character_wave_handle(wave); }
        }
    }
    __forceinline void shower856() {
        short tick = word_730; if (tick <= 0) return;
        if (tick % 2 == 0 && tick <= 60) {
            dispatch_character_wave_handle(21); float p[3] = {0.0f, field_73c, 0.0f};
            double base_y = y_f0 + 350.0;
            spawn(856,
                static_cast<float>((100.0 - static_cast<double>(static_cast<float>(yukari_random(300)))) * facing_104 + x_ec),
                static_cast<float>(base_y - static_cast<double>(static_cast<float>(yukari_random(400)))),
                facing_104, -1, p, 3);
            field_73c = static_cast<float>(field_73c + 1.0);
        }
        ++word_730;
    }
    __forceinline void difficulty900(int period, int extra_modulus) {
        if (word_732 % period) return; dispatch_character_wave_handle(2); float p[3]; p[1] = 0.0f; p[2] = 0.0f;
        for (float n = 0.0f; n < 12.0f; n = static_cast<float>(n + 1.0)) { p[0] = static_cast<float>(n * 30.0); if (word_734 % 2 == 0) spawn(900, x_ec, static_cast<float>(100.0 + y_f0), facing_104, 1, p, 3); else spawn(900, x_ec, static_cast<float>(100.0 + y_f0), static_cast<signed char>(-facing_104), 1, p, 3); }
        if (extra_modulus && word_734 % extra_modulus == 0) { p[2] = 1.0f; for (float n = 0.0f; n < 12.0f; n = static_cast<float>(n + 1.0)) { p[0] = static_cast<float>(n * 30.0); if (word_734 % 4 == 0) spawn(900, x_ec, static_cast<float>(y_f0 + 100.0), facing_104, 1, p, 3); else spawn(900, x_ec, static_cast<float>(y_f0 + 100.0), static_cast<signed char>(-facing_104), 1, p, 3); } }
        ++word_734;
    }
    __forceinline void opening910() {
        field_108 = 0.0f; field_10c = 135.0f; float p[3] = {0.0f, 0.0f, 1.0f}; spawn(910, x_ec, y_f0, facing_104, -1, p, 3);
        p[1] = 0.5f; p[2] = 4.0f; spawn(910, x_ec, y_f0, facing_104, -1, p, 3);
        p[2] = 4.0f; p[1] = 0.25f; spawn(910, x_ec, y_f0, facing_104, -1, p, 3); dispatch_character_wave_handle(1);
    }
    __forceinline void packet910(float mode) {
        float p[3] = {0.0f, 0.0f, mode}; spawn(910, x_ec, y_f0, facing_104, 1, p, 3);
    }
    __forceinline void launch910(float mode, float vx = 6.0f) {
        velocity_x_f4 = vx; float p[3] = {0.0f, 0.5f, 4.0f}; spawn(910, x_ec, y_f0, facing_104, -1, p, 3);
        p[2] = 4.0f; p[1] = 0.25f; spawn(910, x_ec, y_f0, facing_104, -1, p, 3);
        p[2] = mode; spawn(910, x_ec, static_cast<float>(y_f0 - 250.0), facing_104, 1, p, 3); dispatch_character_wave_handle(1);
    }
    __forceinline void burst910(float *p, int count, double angle, int range, int speed_range, double speed) {
        word_738 = 1;
        for (int i = 0; i < count; ++i) {
            p[0] = static_cast<float>(angle - static_cast<float>(yukari_random(range)));
            p[1] = static_cast<float>(static_cast<float>(yukari_random(speed_range)) * static_cast<double>(0.1f) + speed);
            p[2] = 12.0f;
            double base = x_ec + 100.0;
            spawn(910, static_cast<float>(base - static_cast<float>(yukari_random(200))), owner_168->y_f0, facing_104, 1, p, 3);
        }
    }
    __forceinline void finish_story_state() {
        byte_655 = 1; finalize(-1); texture(2, -1); copy_health();
        word_76c = 0; word_76a = 1; word_766 = 0; word_768 = 0; word_764 = 0; event(23);
    }
};

#define TH105_YUKARI_CHECK(field, off) typedef char yukari_check_##field[offsetof(YukariActionStateView, field) == (off) ? 1 : -1]
TH105_YUKARI_CHECK(x_ec, 0x0ec);
TH105_YUKARI_CHECK(y_f0, 0x0f0);
TH105_YUKARI_CHECK(velocity_x_f4, 0x0f4);
TH105_YUKARI_CHECK(velocity_y_f8, 0x0f8);
TH105_YUKARI_CHECK(acceleration_y_100, 0x100);
TH105_YUKARI_CHECK(facing_104, 0x104);
TH105_YUKARI_CHECK(field_108, 0x108);
TH105_YUKARI_CHECK(field_10c, 0x10c);
TH105_YUKARI_CHECK(byte_113, 0x113);
TH105_YUKARI_CHECK(field_11c, 0x11c);
TH105_YUKARI_CHECK(field_12c, 0x12c);
TH105_YUKARI_CHECK(action_id_13c, 0x13c);
TH105_YUKARI_CHECK(sequence_index_13e, 0x13e);
TH105_YUKARI_CHECK(frame_index_140, 0x140);
TH105_YUKARI_CHECK(frame_timer_142, 0x142);
TH105_YUKARI_CHECK(time_counter_144, 0x144);
TH105_YUKARI_CHECK(owner_168, 0x168);
TH105_YUKARI_CHECK(fighter_170, 0x170);
TH105_YUKARI_CHECK(byte_17c, 0x17c);
TH105_YUKARI_CHECK(field_180, 0x180);
TH105_YUKARI_CHECK(byte_184, 0x184);
TH105_YUKARI_CHECK(word_186, 0x186);
TH105_YUKARI_CHECK(byte_47e, 0x47e);
TH105_YUKARI_CHECK(byte_47f, 0x47f);
TH105_YUKARI_CHECK(word_482, 0x482);
TH105_YUKARI_CHECK(word_48a, 0x48a);
TH105_YUKARI_CHECK(word_48c, 0x48c);
TH105_YUKARI_CHECK(byte_490, 0x490);
TH105_YUKARI_CHECK(word_4a8, 0x4a8);
TH105_YUKARI_CHECK(word_4ac, 0x4ac);
TH105_YUKARI_CHECK(word_4ae, 0x4ae);
TH105_YUKARI_CHECK(field_4b8, 0x4b8);
TH105_YUKARI_CHECK(byte_55a, 0x55a);
TH105_YUKARI_CHECK(cards_55c, 0x55c);
TH105_YUKARI_CHECK(byte_605, 0x605);
TH105_YUKARI_CHECK(byte_609, 0x609);
TH105_YUKARI_CHECK(byte_655, 0x655);
TH105_YUKARI_CHECK(field_6ac, 0x6ac);
TH105_YUKARI_CHECK(field_6b4, 0x6b4);
TH105_YUKARI_CHECK(field_6b8, 0x6b8);
TH105_YUKARI_CHECK(field_6bc, 0x6bc);
TH105_YUKARI_CHECK(field_6c0, 0x6c0);
TH105_YUKARI_CHECK(field_6c4, 0x6c4);
TH105_YUKARI_CHECK(field_6c8, 0x6c8);
TH105_YUKARI_CHECK(byte_72c, 0x72c);
TH105_YUKARI_CHECK(word_730, 0x730);
TH105_YUKARI_CHECK(word_732, 0x732);
TH105_YUKARI_CHECK(word_734, 0x734);
TH105_YUKARI_CHECK(word_736, 0x736);
TH105_YUKARI_CHECK(word_738, 0x738);
TH105_YUKARI_CHECK(field_73c, 0x73c);
TH105_YUKARI_CHECK(field_740, 0x740);
TH105_YUKARI_CHECK(field_744, 0x744);
TH105_YUKARI_CHECK(byte_750, 0x750);
TH105_YUKARI_CHECK(byte_751, 0x751);
TH105_YUKARI_CHECK(word_764, 0x764);
TH105_YUKARI_CHECK(word_766, 0x766);
TH105_YUKARI_CHECK(word_768, 0x768);
TH105_YUKARI_CHECK(word_76a, 0x76a);
TH105_YUKARI_CHECK(word_76c, 0x76c);
TH105_YUKARI_CHECK(word_7a0, 0x7a0);
TH105_YUKARI_CHECK(word_7a2, 0x7a2);
TH105_YUKARI_CHECK(word_7a4, 0x7a4);
TH105_YUKARI_CHECK(word_7bc, 0x7bc);
TH105_YUKARI_CHECK(word_7be, 0x7be);
TH105_YUKARI_CHECK(word_7c0, 0x7c0);
TH105_YUKARI_CHECK(word_7c4, 0x7c4);
TH105_YUKARI_CHECK(word_7c6, 0x7c6);
#undef TH105_YUKARI_CHECK
}
