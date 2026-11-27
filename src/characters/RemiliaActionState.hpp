#pragma once
#include <stddef.h>

namespace th105 {
class RemiliaActionStateView;
int __fastcall initialize_fighter_phase_631e0(RemiliaActionStateView *);
extern int g_match_identifier;
unsigned __cdecl remilia_random(int);
unsigned __cdecl remilia_random_u32();
float __cdecl remilia_atan(float, float);
float __cdecl remilia_sine(float);
float __cdecl remilia_cosine(float);
float __fastcall remilia_surface(RemiliaActionStateView *);
unsigned char __fastcall remilia_on_surface(RemiliaActionStateView *);
struct RemiliaActionScratch { void reset(); void oriented_components(float, float); };

// Partial receiver; never instantiate as a recovered complete Fighter.
class RemiliaActionStateView {
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
    signed char classify_fighter_x_boundary();
    unsigned char advance();
    void zero_motion();
    void event(unsigned);
    void flip();
    unsigned char directional(int);
    void layout(float);
    int spawn(int, float, float, signed char, signed char, const void *, int);
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
    unsigned char pad_114[0x18];
    float field_12c;
    unsigned char pad_130[0xc];
    short action_id_13c;
    short sequence_index_13e;
    short frame_index_140;
    short frame_timer_142;
    int time_counter_144;
    unsigned char pad_148[0x20];
    RemiliaActionStateView *owner_168;
    unsigned char pad_16c[0x4];
    RemiliaActionStateView *fighter_170;
    unsigned char pad_174[0x8];
    unsigned char byte_17c;
    unsigned char pad_17d[0x3];
    int field_180;
    signed char byte_184;
    unsigned char pad_185[0x1];
    short word_186;
    unsigned char pad_188[0x2f6];
    unsigned char byte_47e;
    unsigned char byte_47f;
    unsigned char pad_480[0xa];
    short word_48a;
    short word_48c;
    unsigned char pad_48e[0x1a];
    short word_4a8;
    unsigned char pad_4aa[0x2];
    short word_4ac;
    short word_4ae;
    unsigned char pad_4b0[0x8];
    int field_4b8;
    unsigned char pad_4bc[0x149];
    signed char byte_605;
    unsigned char pad_606[0x3];
    signed char byte_609;
    signed char byte_60a;
    signed char byte_60b;
    unsigned char pad_60c[0x1];
    signed char byte_60d;
    unsigned char pad_60e[0x47];
    unsigned char byte_655;
    unsigned char pad_656[0x5e];
    int field_6b4;
    int field_6b8;
    int field_6bc;
    int field_6c0;
    int field_6c4;
    unsigned char pad_6c8[0x60];
    int field_728;
    unsigned char byte_72c;
    unsigned char pad_72d[0x3];
    short word_730;
    short word_732;
    short word_734;
    unsigned char pad_736[0x6];
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

    __forceinline bool entry(short seq) {
        return !time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e == seq;
    }
    __forceinline void reset_action_scratch() {
        reinterpret_cast<RemiliaActionScratch *>(reinterpret_cast<unsigned char *>(this) + 4)->reset();
    }
    __forceinline void set_oriented_components_f0_f4(float angle, float speed) {
        reinterpret_cast<RemiliaActionScratch *>(reinterpret_cast<unsigned char *>(this) + 4)->oriented_components(angle, speed);
    }
    __forceinline void dash_dust(bool reverse) {
        double base = x_ec + 50.0;
        if (reverse) {
            effect(124, static_cast<float>(base - static_cast<float>(remilia_random_u32() % 100u)),
                   static_cast<float>(static_cast<float>(remilia_random_u32() % 200u) + y_f0),
                   static_cast<unsigned char>(-facing_104), 1);
        } else {
            effect(124, static_cast<float>(base - static_cast<float>(remilia_random_u32() % 100u)),
                   static_cast<float>(static_cast<float>(remilia_random_u32() % 200u) + y_f0),
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
    __forceinline void normal_jump(float vx, float vy) {
        if (!sequence_index_13e) {
            landing();
            if (!sequence_index_13e && !byte_47e) zero_motion();
        }
        if (sequence_index_13e > 0) {
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(crossed())) {
                set_action_and_finalize(10); y_f0 = remilia_surface(this); zero_motion(); return;
            }
        }
        advance();
        if (entry(1)) { velocity_x_f4 = vx; velocity_y_f8 = vy; acceleration_y_100 = 0.95f; byte_47e = 0; }
    }
    __forceinline void spawn_offset(int object, int xoff, double height, float *p, int count) {
        spawn(object,
            xoff == 0 ? x_ec : static_cast<float>(xoff * facing_104 + static_cast<double>(x_ec)),
            static_cast<float>(y_f0 + height),
            facing_104, 1, p, count);
    }
    __forceinline void recovery_jump(float vx, float vy) {
        if (!sequence_index_13e || sequence_index_13e == 3) landing();
        else { velocity_y_f8 -= acceleration_y_100; if (static_cast<unsigned char>(crossed())) { y_f0 = remilia_surface(this); zero_motion(); select_sequence(3); return; } }
        if (advance()) { if (byte_72c == 2) { set_action_and_finalize(700); word_4a8 = 3; word_4ac = 3; return; } set_action_and_finalize(0); if (field_6b8 > 0) set_action_and_finalize(1); }
        if (sequence_index_13e == 3 && frame_index_140 == 2 && !frame_timer_142) ground_face();
        if (entry(1)) { velocity_y_f8 = vy; velocity_x_f4 = vx; acceleration_y_100 = 0.75f; }
    }
    __forceinline void decelerate(double amount, bool clear) {
        velocity_x_f4 = static_cast<float>(velocity_x_f4 - amount);
        if (velocity_x_f4 < 0.0f) { velocity_x_f4 = 0.0f; if (clear) byte_47e = 0; }
    }
    __forceinline void packet848(float mode) {
        float p[3] = {0.0f, 0.0f, mode}; spawn(848, x_ec, y_f0, facing_104, 1, p, 3);
    }
    __forceinline void interval_clear() {
        if (field_180 && ++word_730 > 5) { field_180 = 0; word_730 = 0; }
    }
    __forceinline void aim800(float low, float high) {
        field_744 = -remilia_atan(fighter_170->y_f0 - y_f0, static_cast<float>((fighter_170->x_ec - x_ec) * static_cast<double>(facing_104)));
        if (field_744 < static_cast<double>(low)) field_744 = low;
        if (field_744 > high) field_744 = high;
    }
    __forceinline void charge(int xoff, double y) {
        effect(62,
            xoff == 0 ? x_ec : xoff < 0 ? static_cast<float>(x_ec - (-xoff) * facing_104) : static_cast<float>(xoff * facing_104 + static_cast<double>(x_ec)),
            static_cast<float>(y_f0 + y), static_cast<unsigned char>(facing_104), 1);
        next_sequence_block();
    }
    __forceinline void fan800(int count, int random_range, double bias, double speed, int x, double y) {
        float p[3];
        for (int n = 0; n < count; ++n) { p[0] = static_cast<float>(static_cast<double>(static_cast<float>(remilia_random(random_range))) + (field_744 - bias)); p[1] = static_cast<float>(n + speed); p[2] = 0.0f; spawn_offset(800, x, y, p, 3); }
    }
    __forceinline void shot800(float low, float high, int count, int range, double bias, double speed, int x, double y, bool air) {
        field_180 = 1; aim800(low, high); counter(200, 45);
        if (air) { velocity_x_f4 = -4.0f; velocity_y_f8 = 9.0f; acceleration_y_100 = 0.65f; }
        phase_counter(30); dispatch_character_wave_handle(0); fan800(count, range, bias, speed, x, y);
    }
    __forceinline void air800(float low, float high, int x, double y) {
        if (sequence_index_13e == 2) landing();
        if (!field_6c0) byte_750 = 0;
        velocity_y_f8 -= acceleration_y_100;
        if (static_cast<unsigned char>(crossed()) && sequence_index_13e < 2) { select_sequence(2); byte_47f = 0; y_f0 = remilia_surface(this); zero_motion(); return; }
        if (advance()) set_action_and_finalize(0);
        if (entry(1) || entry(2)) { set_action_and_finalize(9); return; }
        if (!sequence_index_13e) {
            if (!frame_timer_142 && frame_index_140 == 3 && byte_750 == 1) { charge(-22, 96.0); return; }
            if (!frame_timer_142 && frame_index_140 == 4) shot800(low, high, 6, 20, 10.0, 15.0, x, y, true);
        }
        if (sequence_index_13e == 1 && !frame_timer_142 && frame_index_140 == 2) shot800(low, high, 10, 30, 15.0, 10.0, x, y, true);
    }
    __forceinline void packet801(float angle, float speed, int x, double y) {
        float p[3] = {angle, speed, 0.0f}; spawn_offset(801, x, y, p, 3); dispatch_character_wave_handle(1);
    }
    __forceinline void start801(int x, double y, float angle) {
        field_180 = 1; counter(200, 60); phase_counter(50); packet801(angle, 12.0f, x, y);
    }
    __forceinline void ring810() {
        float p[3]; p[2] = 0.0f; p[1] = 30.0f;
        for (float n = 0.0f; n < 8.0f; n = static_cast<float>(n + 1.0)) { p[0] = static_cast<float>(static_cast<double>(static_cast<float>(remilia_random(25))) + n * 45.0); signed char layer = static_cast<signed char>(2 * (remilia_sine(p[0]) >= 0.0) - 1); spawn(810, x_ec, y_f0, facing_104, layer, p, 3); }
    }
    __forceinline void packet811(float mode) {
        float p[3] = {0.0f, 0.0f, mode}; spawn(811, x_ec, y_f0, facing_104, 1, p, 3);
    }
    __forceinline void ring815(float speed, bool charged) {
        dispatch_character_wave_handle(11); field_180 = 1; counter(200, 120); phase_counter(50);
        switch (byte_605) { case 0: field_740 = charged ? 5.0f : 3.0f; break; case 1: case 2: case 3: field_740 = charged ? 6.0f : 4.0f; break; case 4: field_740 = charged ? 7.0f : 5.0f; break; }
        float p[4]; for (float n = 0.0f; static_cast<double>(n) < field_740; n = static_cast<float>(n + 1.0)) { p[0] = static_cast<float>(360.0 * n / field_740); p[1] = speed; p[2] = 0.0f; p[3] = static_cast<float>(n * 5.0 + 60.0); spawn_offset(815, 40, 102.0, p, 4); }
        p[2] = 2.0f; spawn_offset(815, 40, 102.0, p, 3); p[2] = 3.0f; spawn_offset(815, 40, 102.0, p, 3);
    }
    __forceinline void ground815(int &control, float speed) {
        landing(); byte_17c = 1; if (!control) byte_750 = 0; if (advance()) set_action_and_finalize(0); if (entry(1)) { set_action_and_finalize(0); return; }
        if (!sequence_index_13e) {
            if (!frame_timer_142 && frame_index_140 == 3 && byte_750) { charge(0, 107.0); return; }
            if (!frame_timer_142 && frame_index_140 == 5) ring815(speed, false);
        }
        if (sequence_index_13e == 1 && !frame_timer_142 && frame_index_140 == 3) ring815(speed, true);
    }
    __forceinline void ground816(int &control) {
        landing(); byte_17c = 5; if (!control) byte_750 = 0;
        if (sequence_index_13e == 2 && (time_counter_144 >= 10 * (byte_609 + 1) || !byte_750)) { next_sequence_block(); return; }
        if (advance()) set_action_and_finalize(0); if (entry(1)) { float p[4] = {0.0f, 0.0f, 0.0f, 0.0f}; spawn_offset(816, 20, 100.0, p, 4); p[2] = 1.0f; spawn_offset(816, 20, 100.0, p, 4); dispatch_character_wave_handle(16); counter(200, 120); phase_counter(50); }
    }
    __forceinline void fan817(double offset, bool charged) {
        field_180 = 1; counter(200, 120); dispatch_character_wave_handle(20); phase_counter(50); aim800(-15.0f, 0.0f);
        float p[3];
        if (charged) {
            for (float n = 0.0f; n < 6.0f; n = static_cast<float>(n + 1.0)) {
                p[0] = offset == 0.0 ? static_cast<float>(field_744 - n * 6.0) : static_cast<float>(field_744 - n * 6.0 - offset); p[1] = 35.0f; p[2] = 0.0f;
                spawn(817,
                    static_cast<float>((remilia_cosine(-p[0]) * 200.0 - 120.0) * facing_104 + x_ec),
                    static_cast<float>(remilia_sine(-p[0]) * 200.0 + y_f0 + 100.0),
                    facing_104, 1, p, 4);
            }
        } else {
            for (float n = 0.0f; n < byte_60d + 1; n = static_cast<float>(n + 1.0)) {
                p[0] = offset == 0.0 ? static_cast<float>(field_744 - n * 6.0) : static_cast<float>(field_744 - n * 6.0 - offset); p[1] = 35.0f; p[2] = 0.0f;
                spawn(817,
                    static_cast<float>((remilia_cosine(-p[0]) * 200.0 - 120.0) * facing_104 + x_ec),
                    static_cast<float>(remilia_sine(-p[0]) * 200.0 + y_f0 + 100.0),
                    facing_104, 1, p, 4);
            }
        }
    }
    __forceinline void ground817(int &control, double offset) {
        landing(); byte_17c = 9; if (!control) byte_750 = 0; if (advance()) set_action_and_finalize(0); if (entry(1)) { set_action_and_finalize(0); return; }
        if (!sequence_index_13e) {
            if (!frame_timer_142 && frame_index_140 == 10 && byte_750) { charge(-140, 160.0); return; }
            if (!frame_timer_142 && frame_index_140 == 12) fan817(offset, false);
        }
        if (sequence_index_13e == 1 && !frame_timer_142 && frame_index_140 == 3) fan817(offset, true);
    }
    __forceinline void ground821(float angle) {
        landing(); byte_17c = 6; if (advance()) set_action_and_finalize(0);
        if (!sequence_index_13e && !frame_timer_142 && frame_index_140 == 2) { phase_counter(50); counter(200, 120); field_180 = 1; float p[3] = {angle, 20.0f, 4.0f}; if (byte_60a <= 3) p[2] = 3.0f; if (byte_60a <= 1) p[2] = 0.0f; spawn_offset(821, 110, 227.0, p, 3);
            p[0] = 0.0f; p[1] = 0.5f; p[2] = 2.0f; spawn(821, static_cast<float>(80 * facing_104 + static_cast<double>(x_ec)), y_f0, facing_104, -1, p, 3); dispatch_character_wave_handle(23); }
    }
    __forceinline void diving826(float vx) {
        if (sequence_index_13e == 6) landing();
        if (sequence_index_13e == 3) {
            if (!(time_counter_144 % 2)) { float p[3] = {0.0f, 0.0f, 3.0f}; spawn(826, x_ec, static_cast<float>(y_f0 + 100.0), facing_104, -1, p, 3); }
            if (static_cast<unsigned char>(crossed())) {
                next_sequence_block(); layout(8.0f); dispatch_character_wave_handle(18); y_f0 = remilia_surface(this);
                velocity_x_f4 = -15.0f; velocity_y_f8 = 12.5f; acceleration_y_100 = 0.5f;
                float p[3] = {0.0f, 0.0f, 0.0f}; spawn(826, x_ec, y_f0, facing_104, -1, p, 3);
                p[1] = 15.0f; p[2] = 1.0f;
                for (float n = 0.0f; n < 6.0f; n = static_cast<float>(n + 1.0)) {
                    p[0] = static_cast<float>(static_cast<double>(static_cast<float>(remilia_random(30))) + (n * 60.0 + 30.0));
                    if (p[0] >= 0.0f && p[0] <= 180.0f) spawn(826, x_ec, y_f0, facing_104, 1, p, 3);
                    else spawn(826, x_ec, y_f0, facing_104, -1, p, 3);
                }
                p[0] = 0.0f; p[1] = 50.0f; p[2] = 6.0f;
                if (byte_60b <= 3) { p[1] = 42.5f; p[2] = 4.0f; }
                if (byte_60b <= 1) { p[1] = 35.0f; p[2] = 4.0f; }
                spawn(826, static_cast<float>(50 * facing_104 + static_cast<double>(x_ec)), y_f0, facing_104, 1, p, 3);
                spawn(826, static_cast<float>(50 * facing_104 + static_cast<double>(x_ec)), y_f0, static_cast<signed char>(-facing_104), 1, p, 3);
            }
        }
        if (sequence_index_13e == 4 || sequence_index_13e == 5) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 + 0.5); if (velocity_x_f4 > 0.0f) velocity_x_f4 = 0.0f;
            velocity_y_f8 -= acceleration_y_100;
            if (static_cast<unsigned char>(crossed())) { zero_motion(); y_f0 = remilia_surface(this); select_sequence(6); return; }
        }
        byte_17c = 7; if (advance()) set_action_and_finalize(0);
        if (entry(1)) { counter(200, 120); dispatch_character_wave_handle(13); velocity_x_f4 = vx; velocity_y_f8 = static_cast<float>((700.0 - y_f0) * static_cast<double>(0.05f)); }
        if (entry(2)) zero_motion();
        if (entry(3)) { float p[3] = {0.0f, 0.0f, 2.0f}; spawn(826, x_ec, y_f0, facing_104, 1, p, 3); velocity_y_f8 = -50.0f; phase_counter(50); }
    }
    __forceinline void spell_flash(int xoff, double height, int outcome) {
        word_48a = 40; event(23);
        effect(115,
            xoff < 0 ? static_cast<float>(x_ec - (-xoff * facing_104))
                : xoff ? static_cast<float>(xoff * facing_104 + static_cast<double>(x_ec)) : x_ec,
            static_cast<float>(y_f0 + height), static_cast<unsigned char>(facing_104), 1);
        sequence_window(0, outcome, 60); secondary_cycle();
    }
    __forceinline void hover(double height) {
        y_f0 = static_cast<float>(remilia_surface(this) + height - field_73c);
        if (field_73c != 0.0f) field_73c = static_cast<float>(field_73c * static_cast<double>(0.95f));
        if (field_73c <= 1.0f) field_73c = 0.0f;
    }
    __forceinline void contact_interval() {
        if (field_180 && byte_184 > 0 && ++word_732 >= 3) { word_732 = 0; field_180 = 0; }
    }
    __forceinline void aim_unbounded() {
        field_744 = -remilia_atan(fighter_170->y_f0 - y_f0, static_cast<float>((fighter_170->x_ec - x_ec) * static_cast<double>(facing_104)));
    }
    __forceinline void random902(int range) {
        dispatch_character_wave_handle(58);
        float p[3]; p[0] = static_cast<float>(remilia_random(360)); p[1] = static_cast<float>(static_cast<double>(static_cast<float>(remilia_random(range))) * static_cast<double>(0.1f) + 4.0); p[2] = 0.0f; spawn_offset(902, 30, 90.0, p, 3);
    }
    __forceinline void ring902(float *p, int count) {
        for (float n = 0.0f; n < count; n = static_cast<float>(n + 1.0)) {
            p[0] = static_cast<float>(remilia_random(360)); p[1] = static_cast<float>(static_cast<double>(static_cast<float>(remilia_random(12))) + 18.0); p[2] = 1.0f;
            spawn(902,
                static_cast<float>(remilia_cosine(static_cast<float>(180.0 - p[0])) * (p[1] * 60.0) * facing_104 + x_ec),
                static_cast<float>(remilia_sine(static_cast<float>(180.0 - p[0])) * (p[1] * 60.0) + (static_cast<double>(y_f0) + 100.0)),
                facing_104, 1, p, 3);
        }
    }
    __forceinline void burst902(float *p, int count, double bias) {
        for (float n = 0.0f; n < count; n = static_cast<float>(n + 1.0)) { p[0] = static_cast<float>(remilia_random(360)); p[1] = static_cast<float>(static_cast<double>(static_cast<float>(remilia_random(10))) + bias); p[2] = 5.0f; spawn_offset(902, 0, 100.0, p, 3); }
    }
    __forceinline void teleport902(float vx, float vy) {
        if (sequence_index_13e == 1 || sequence_index_13e == 2) {
            if (time_counter_144 <= 60) {
                switch (g_match_identifier) {
                case 3: if (!(time_counter_144 % 3)) random902(100); break;
                case 2: if (!(time_counter_144 % 4)) random902(80); break;
                case 1: if (!(time_counter_144 % 6)) random902(60);
                case 0: if (!(time_counter_144 % 10)) random902(40); break;
                }
            }
            if (time_counter_144 >= 50) { if (byte_113 >= 10) byte_113 -= 10; else { select_sequence(3); byte_113 = 255; zero_motion(); return; } }
        }
        if (sequence_index_13e == 3) {
            if (time_counter_144 == 45) {
                x_ec = fighter_170->x_ec; y_f0 = fighter_170->y_f0; dispatch_character_wave_handle(59);
                float p[3]; switch (g_match_identifier) { case 3: ring902(p, 20); break; case 2: ring902(p, 15); break; case 1: ring902(p, 10); break; case 0: ring902(p, 10); break; }
            }
            if (time_counter_144 == 85) {
                dispatch_character_wave_handle(60); float p[3];
                switch (g_match_identifier) { case 3: burst902(p, 25, 1.0); break; case 2: burst902(p, 18, 2.0); break; case 1: burst902(p, 12, 2.0); break; }
                p[0] = 0.0f; p[1] = 0.0f; p[2] = 2.0f;
                spawn_offset(902, 0, 100.0, p, 3); spawn_offset(902, 0, 100.0, p, 3); spawn_offset(902, 0, 100.0, p, 3);
                p[2] = 4.0f; spawn_offset(902, 0, 100.0, p, 3); p[2] = 3.0f;
                for (float n = 0.0f; n < 8.0f; n = static_cast<float>(n + 1.0)) { p[0] = static_cast<float>(remilia_random(360)); p[1] = static_cast<float>(static_cast<double>(static_cast<float>(remilia_random(22))) + 8.0); spawn_offset(902, 0, 100.0, p, 3); }
                select_sequence(4); return;
            }
        }
        if (advance()) { if (static_cast<unsigned char>(crossed())) set_action_and_finalize(700); else { set_action_and_finalize(704); acceleration_y_100 = 0.3f; } }
        if (entry(1)) { velocity_x_f4 = vx; velocity_y_f8 = vy; }
    }
    __forceinline void spell_finish() {
        texture(2, -1); copy_health(); word_76c = 0; word_76a = 1; word_766 = 0; word_768 = 0; word_764 = 0; event(23);
    }
    __forceinline void ring903(float *p, int count, double step) {
        float angle = static_cast<float>(remilia_random(360));
        for (float n = 0.0f; n < count; n = static_cast<float>(n + 1.0)) { p[0] = static_cast<float>(n * step + angle); p[1] = 0.0f; p[2] = 0.0f; spawn_offset(903, 0, 230.0, p, 3); }
    }
    __forceinline void burst903(float *p, int count, double bias) {
        for (float n = 0.0f; n < count; n = static_cast<float>(n + 1.0)) { p[0] = static_cast<float>(remilia_random(360)); p[1] = static_cast<float>(static_cast<double>(static_cast<float>(remilia_random(40))) * static_cast<double>(0.1f) + bias); p[2] = 3.0f; spawn_offset(903, 0, 230.0, p, 3); }
    }
};

#define TH105_REMILIA_CHECK(field, off) typedef char remilia_check_##field[offsetof(RemiliaActionStateView, field) == (off) ? 1 : -1]
TH105_REMILIA_CHECK(x_ec, 0x0ec);
TH105_REMILIA_CHECK(y_f0, 0x0f0);
TH105_REMILIA_CHECK(velocity_x_f4, 0x0f4);
TH105_REMILIA_CHECK(velocity_y_f8, 0x0f8);
TH105_REMILIA_CHECK(acceleration_y_100, 0x100);
TH105_REMILIA_CHECK(facing_104, 0x104);
TH105_REMILIA_CHECK(field_108, 0x108);
TH105_REMILIA_CHECK(field_10c, 0x10c);
TH105_REMILIA_CHECK(byte_113, 0x113);
TH105_REMILIA_CHECK(field_12c, 0x12c);
TH105_REMILIA_CHECK(action_id_13c, 0x13c);
TH105_REMILIA_CHECK(sequence_index_13e, 0x13e);
TH105_REMILIA_CHECK(frame_index_140, 0x140);
TH105_REMILIA_CHECK(frame_timer_142, 0x142);
TH105_REMILIA_CHECK(time_counter_144, 0x144);
TH105_REMILIA_CHECK(owner_168, 0x168);
TH105_REMILIA_CHECK(fighter_170, 0x170);
TH105_REMILIA_CHECK(byte_17c, 0x17c);
TH105_REMILIA_CHECK(field_180, 0x180);
TH105_REMILIA_CHECK(byte_184, 0x184);
TH105_REMILIA_CHECK(word_186, 0x186);
TH105_REMILIA_CHECK(byte_47e, 0x47e);
TH105_REMILIA_CHECK(byte_47f, 0x47f);
TH105_REMILIA_CHECK(word_48a, 0x48a);
TH105_REMILIA_CHECK(word_48c, 0x48c);
TH105_REMILIA_CHECK(word_4a8, 0x4a8);
TH105_REMILIA_CHECK(word_4ac, 0x4ac);
TH105_REMILIA_CHECK(word_4ae, 0x4ae);
TH105_REMILIA_CHECK(field_4b8, 0x4b8);
TH105_REMILIA_CHECK(byte_605, 0x605);
TH105_REMILIA_CHECK(byte_609, 0x609);
TH105_REMILIA_CHECK(byte_60a, 0x60a);
TH105_REMILIA_CHECK(byte_60b, 0x60b);
TH105_REMILIA_CHECK(byte_60d, 0x60d);
TH105_REMILIA_CHECK(byte_655, 0x655);
TH105_REMILIA_CHECK(field_6b4, 0x6b4);
TH105_REMILIA_CHECK(field_6b8, 0x6b8);
TH105_REMILIA_CHECK(field_6bc, 0x6bc);
TH105_REMILIA_CHECK(field_6c0, 0x6c0);
TH105_REMILIA_CHECK(field_6c4, 0x6c4);
TH105_REMILIA_CHECK(field_728, 0x728);
TH105_REMILIA_CHECK(byte_72c, 0x72c);
TH105_REMILIA_CHECK(word_730, 0x730);
TH105_REMILIA_CHECK(word_732, 0x732);
TH105_REMILIA_CHECK(word_734, 0x734);
TH105_REMILIA_CHECK(field_73c, 0x73c);
TH105_REMILIA_CHECK(field_740, 0x740);
TH105_REMILIA_CHECK(field_744, 0x744);
TH105_REMILIA_CHECK(byte_750, 0x750);
TH105_REMILIA_CHECK(byte_751, 0x751);
TH105_REMILIA_CHECK(word_764, 0x764);
TH105_REMILIA_CHECK(word_766, 0x766);
TH105_REMILIA_CHECK(word_768, 0x768);
TH105_REMILIA_CHECK(word_76a, 0x76a);
TH105_REMILIA_CHECK(word_76c, 0x76c);
TH105_REMILIA_CHECK(word_7a0, 0x7a0);
TH105_REMILIA_CHECK(word_7a2, 0x7a2);
#undef TH105_REMILIA_CHECK
}
