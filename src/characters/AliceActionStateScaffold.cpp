#include <stddef.h>

namespace th105 {

// Partial semantic reconstruction for Alice's primary-vtable +0x28 giant.
//
// This is deliberately NOT the target vslot28 root and is not referenced by
// config/functions.csv or a match unit.  It records only action cases whose
// current TH105 1.06a control/data flow has been checked against the Alice PE;
// shared-family cases also use the source-present Youmu root as a semantic
// reference.  Alice-specific cases are recovered from PE control/data flow and
// exact helper contracts.  Unknown actions return false.
// Keep this as a staging surface until the complete 42,721-byte root is
// recovered; never promote this helper as authored exact/source-present credit.

typedef unsigned char _BYTE;
typedef unsigned short _WORD;
typedef unsigned int _DWORD;

class AliceActionStateLowScaffoldView;
float __fastcall alice_stage_surface_height_at_x(AliceActionStateLowScaffoldView *fighter);
int __fastcall is_y_at_or_below_stage_surface(void *fighter);
unsigned int __cdecl mt19937_next_u32(void);
double __cdecl lookup_orientation_sine_quantized_abs(float phase);
double __cdecl lookup_orientation_cosine_quantized_abs(float phase);
struct FighterActionScratchView { void reset(); };

class AliceActionStateLowScaffoldView {
public:
    virtual void slot_00();
    virtual void slot_04();
    virtual void set_action(int action);
    virtual void set_sequence(int sequence);
    virtual void slot_10();
    virtual void slot_14();

    unsigned char resolve_stage_surface_landing_transition();
    unsigned char advance_frame_and_dispatch();
    int has_crossed_stage_surface_while_descending();
    unsigned char try_dispatch_directional_action_208_210(int mode);
    void dispatch_indexed_event_member(unsigned int event_code);
    void dispatch_character_wave_handle(unsigned int index);
    void emit_fighter_effect_433cc0(int effect_id, float x, float y, int facing, int arg5);
    void adjust_counter_482(short amount, int floor_value);
    int add_phase_scaled_counter_558(int value);
    void face_opponent_and_flip_horizontal_velocity();
    int spawn_owned_object_via_manager(
        int object_id, float x, float y, int direction, int arg5, int arg6, int arg7);
    void zero_velocity_acceleration();

    bool try_dispatch_verified_action(int action);
};

bool AliceActionStateLowScaffoldView::try_dispatch_verified_action(int action)
{
    unsigned char *raw = reinterpret_cast<unsigned char *>(this);
    float adjusted;
    float zero;

    switch (action) {
    case 0:
        resolve_stage_surface_landing_transition();
        if (!*reinterpret_cast<float *>(raw + 244))
            *reinterpret_cast<_BYTE *>(raw + 1150) = 0;
        if (!*reinterpret_cast<_BYTE *>(raw + 1150)) {
            zero_velocity_acceleration();
            advance_frame_and_dispatch();
            return true;
        }
        if (*reinterpret_cast<float *>(raw + 244) > 0.0f) {
            adjusted = *reinterpret_cast<float *>(raw + 244) - 0.5f;
            *reinterpret_cast<float *>(raw + 244) = adjusted;
            if (adjusted < 0.0f) {
                zero_velocity_acceleration();
                *reinterpret_cast<_BYTE *>(raw + 1150) = 0;
            }
        }
        if (*reinterpret_cast<float *>(raw + 244) < 0.0f) {
            adjusted = *reinterpret_cast<float *>(raw + 244) + 0.5f;
            *reinterpret_cast<float *>(raw + 244) = adjusted;
            if (adjusted > 0.0f) {
                zero_velocity_acceleration();
                *reinterpret_cast<_BYTE *>(raw + 1150) = 0;
            }
        }
        advance_frame_and_dispatch();
        return true;

    case 1:
        resolve_stage_surface_landing_transition();
        if (*reinterpret_cast<_BYTE *>(raw + 1150)) {
            zero = 0.0f;
            if (*reinterpret_cast<float *>(raw + 244) > zero) {
                adjusted = *reinterpret_cast<float *>(raw + 244) - 0.5f;
                *reinterpret_cast<float *>(raw + 244) = adjusted;
                if (adjusted < zero) {
                    zero_velocity_acceleration();
                    *reinterpret_cast<_BYTE *>(raw + 1150) = 0;
                }
            }
            if (zero > *reinterpret_cast<float *>(raw + 244)) {
                adjusted = *reinterpret_cast<float *>(raw + 244) + 0.5f;
                *reinterpret_cast<float *>(raw + 244) = adjusted;
                if (adjusted > zero) {
                    zero_velocity_acceleration();
                    *reinterpret_cast<_BYTE *>(raw + 1150) = 0;
                }
            }
        } else {
            zero_velocity_acceleration();
        }
        if (advance_frame_and_dispatch() && !*reinterpret_cast<_WORD *>(raw + 320))
            set_action(2);
        return true;

    case 2:
        resolve_stage_surface_landing_transition();
        if (!*reinterpret_cast<_BYTE *>(raw + 1150)) {
            zero_velocity_acceleration();
            advance_frame_and_dispatch();
            return true;
        }
        if (*reinterpret_cast<float *>(raw + 244) > 0.0f) {
            adjusted = *reinterpret_cast<float *>(raw + 244) - 0.5f;
            *reinterpret_cast<float *>(raw + 244) = adjusted;
            if (adjusted < 0.0f) {
                zero_velocity_acceleration();
                *reinterpret_cast<_BYTE *>(raw + 1150) = 0;
            }
        }
        if (*reinterpret_cast<float *>(raw + 244) < 0.0f) {
            adjusted = *reinterpret_cast<float *>(raw + 244) + 0.5f;
            *reinterpret_cast<float *>(raw + 244) = adjusted;
            if (adjusted > 0.0f) {
                zero_velocity_acceleration();
                *reinterpret_cast<_BYTE *>(raw + 1150) = 0;
            }
        }
        advance_frame_and_dispatch();
        return true;

    case 3:
        resolve_stage_surface_landing_transition();
        if (*reinterpret_cast<_BYTE *>(raw + 1150)) {
            zero = 0.0f;
            if (*reinterpret_cast<float *>(raw + 244) > zero) {
                adjusted = *reinterpret_cast<float *>(raw + 244) - 0.5f;
                *reinterpret_cast<float *>(raw + 244) = adjusted;
                if (adjusted < zero) {
                    zero_velocity_acceleration();
                    *reinterpret_cast<_BYTE *>(raw + 1150) = 0;
                }
            }
            if (zero > *reinterpret_cast<float *>(raw + 244)) {
                adjusted = *reinterpret_cast<float *>(raw + 244) + 0.5f;
                *reinterpret_cast<float *>(raw + 244) = adjusted;
                if (adjusted > zero) {
                    zero_velocity_acceleration();
                    *reinterpret_cast<_BYTE *>(raw + 1150) = 0;
                }
            }
        } else {
            zero_velocity_acceleration();
        }
        if (!advance_frame_and_dispatch())
            return true;
        if (*reinterpret_cast<_WORD *>(raw + 320))
            return true;
        set_action(0);
        return true;

    case 4:
        resolve_stage_surface_landing_transition();
        *reinterpret_cast<float *>(raw + 244) = 6.0f;
        advance_frame_and_dispatch();
        return true;

    case 5:
        resolve_stage_surface_landing_transition();
        *reinterpret_cast<float *>(raw + 244) = -6.0f;
        advance_frame_and_dispatch();
        return true;

    case 6:
        if (!*reinterpret_cast<_WORD *>(raw + 318)) {
            resolve_stage_surface_landing_transition();
            if (!*reinterpret_cast<_WORD *>(raw + 318) && !*reinterpret_cast<_BYTE *>(raw + 1150))
                zero_velocity_acceleration();
        }
        if (*reinterpret_cast<__int16 *>(raw + 318) > 0) {
            *reinterpret_cast<float *>(raw + 248) =
                *reinterpret_cast<float *>(raw + 248) - *reinterpret_cast<float *>(raw + 256);
            if (has_crossed_stage_surface_while_descending()) {
                set_action(10);
                *reinterpret_cast<float *>(raw + 240) = alice_stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                return true;
            }
        }
        advance_frame_and_dispatch();
        if (*reinterpret_cast<_DWORD *>(raw + 324)
            || *reinterpret_cast<_WORD *>(raw + 322)
            || *reinterpret_cast<_WORD *>(raw + 320)
            || *reinterpret_cast<_WORD *>(raw + 318) != 1)
            return true;
        *reinterpret_cast<float *>(raw + 244) = 0.0f;
        *reinterpret_cast<float *>(raw + 248) = 15.0f;
        *reinterpret_cast<float *>(raw + 256) = 0.65f;
        *reinterpret_cast<_BYTE *>(raw + 1150) = 0;
        return true;

    case 7:
        if (!*reinterpret_cast<_WORD *>(raw + 318)) {
            resolve_stage_surface_landing_transition();
            if (!*reinterpret_cast<_WORD *>(raw + 318) && !*reinterpret_cast<_BYTE *>(raw + 1150))
                zero_velocity_acceleration();
        }
        if (*reinterpret_cast<__int16 *>(raw + 318) > 0) {
            *reinterpret_cast<float *>(raw + 248) =
                *reinterpret_cast<float *>(raw + 248) - *reinterpret_cast<float *>(raw + 256);
            if (has_crossed_stage_surface_while_descending()) {
                set_action(10);
                *reinterpret_cast<float *>(raw + 240) = alice_stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                return true;
            }
        }
        advance_frame_and_dispatch();
        if (*reinterpret_cast<_DWORD *>(raw + 324)
            || *reinterpret_cast<_WORD *>(raw + 322)
            || *reinterpret_cast<_WORD *>(raw + 320)
            || *reinterpret_cast<_WORD *>(raw + 318) != 1)
            return true;
        *reinterpret_cast<float *>(raw + 244) = 5.0f;
        *reinterpret_cast<float *>(raw + 248) = 15.0f;
        *reinterpret_cast<float *>(raw + 256) = 0.65f;
        *reinterpret_cast<_BYTE *>(raw + 1150) = 0;
        return true;

    case 8:
        if (!*reinterpret_cast<_WORD *>(raw + 318)) {
            resolve_stage_surface_landing_transition();
            if (!*reinterpret_cast<_WORD *>(raw + 318) && !*reinterpret_cast<_BYTE *>(raw + 1150))
                zero_velocity_acceleration();
        }
        if (*reinterpret_cast<__int16 *>(raw + 318) > 0) {
            *reinterpret_cast<float *>(raw + 248) =
                *reinterpret_cast<float *>(raw + 248) - *reinterpret_cast<float *>(raw + 256);
            if (has_crossed_stage_surface_while_descending()) {
                set_action(10);
                *reinterpret_cast<float *>(raw + 240) = alice_stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                return true;
            }
        }
        advance_frame_and_dispatch();
        if (*reinterpret_cast<_DWORD *>(raw + 324)
            || *reinterpret_cast<_WORD *>(raw + 322)
            || *reinterpret_cast<_WORD *>(raw + 320)
            || *reinterpret_cast<_WORD *>(raw + 318) != 1)
            return true;
        *reinterpret_cast<float *>(raw + 244) = -5.0f;
        *reinterpret_cast<float *>(raw + 248) = 15.0f;
        *reinterpret_cast<float *>(raw + 256) = 0.65f;
        *reinterpret_cast<_BYTE *>(raw + 1150) = 0;
        return true;

    case 10:
        resolve_stage_surface_landing_transition();
        zero_velocity_acceleration();
        if (advance_frame_and_dispatch()) {
            if (*reinterpret_cast<_DWORD *>(raw + 1720))
                set_action(2);
            else
                set_action(0);
        }
        return true;


    case 197: {
        unsigned char *peer;

        resolve_stage_surface_landing_transition();
        if (advance_frame_and_dispatch()) {
            if (*reinterpret_cast<_BYTE *>(raw + 1836) == 2) {
                set_action(700);
                *reinterpret_cast<_WORD *>(raw + 1192) = 3;
                *reinterpret_cast<_WORD *>(raw + 1196) = 3;
                return true;
            }
            set_action(0);
            if (*reinterpret_cast<int *>(raw + 1720) > 0)
                set_action(1);
        }
        if (!*reinterpret_cast<_WORD *>(raw + 322) && *reinterpret_cast<_WORD *>(raw + 320) == 8)
            zero_velocity_acceleration();
        if (!*reinterpret_cast<_WORD *>(raw + 322) && *reinterpret_cast<_WORD *>(raw + 320) == 13) {
            peer = reinterpret_cast<unsigned char *>(*reinterpret_cast<_DWORD *>(raw + 368));
            if (*reinterpret_cast<float *>(peer + 236) < *reinterpret_cast<float *>(raw + 236))
                *reinterpret_cast<signed char *>(raw + 260) = -1;
            if (*reinterpret_cast<float *>(peer + 236) > *reinterpret_cast<float *>(raw + 236))
                *reinterpret_cast<signed char *>(raw + 260) = 1;
        }
        return true;
    }

    case 198: {
        unsigned char *peer;

        resolve_stage_surface_landing_transition();
        if (advance_frame_and_dispatch()) {
            if (*reinterpret_cast<_BYTE *>(raw + 1836) == 2) {
                set_action(700);
                *reinterpret_cast<_WORD *>(raw + 1192) = 3;
                *reinterpret_cast<_WORD *>(raw + 1196) = 3;
                return true;
            }
            set_action(0);
            if (*reinterpret_cast<int *>(raw + 1720) > 0)
                set_action(1);
        }
        if (!*reinterpret_cast<_WORD *>(raw + 322) && *reinterpret_cast<_WORD *>(raw + 320) == 8)
            zero_velocity_acceleration();
        if (!*reinterpret_cast<_WORD *>(raw + 322) && *reinterpret_cast<_WORD *>(raw + 320) == 13) {
            peer = reinterpret_cast<unsigned char *>(*reinterpret_cast<_DWORD *>(raw + 368));
            if (*reinterpret_cast<float *>(peer + 236) < *reinterpret_cast<float *>(raw + 236))
                *reinterpret_cast<signed char *>(raw + 260) = -1;
            if (*reinterpret_cast<float *>(peer + 236) > *reinterpret_cast<float *>(raw + 236))
                *reinterpret_cast<signed char *>(raw + 260) = 1;
        }
        return true;
    }

    case 199: {
        unsigned char *peer;

        resolve_stage_surface_landing_transition();
        if (advance_frame_and_dispatch()) {
            if (*reinterpret_cast<_BYTE *>(raw + 1836) == 2) {
                set_action(700);
                *reinterpret_cast<_WORD *>(raw + 1192) = 3;
                *reinterpret_cast<_WORD *>(raw + 1196) = 3;
                return true;
            }
            set_action(0);
            if (*reinterpret_cast<int *>(raw + 1720) > 0)
                set_action(1);
        }
        if (!*reinterpret_cast<_WORD *>(raw + 322) && *reinterpret_cast<_WORD *>(raw + 320) == 5) {
            peer = reinterpret_cast<unsigned char *>(*reinterpret_cast<_DWORD *>(raw + 368));
            if (*reinterpret_cast<float *>(peer + 236) < *reinterpret_cast<float *>(raw + 236))
                *reinterpret_cast<signed char *>(raw + 260) = -1;
            if (*reinterpret_cast<float *>(peer + 236) > *reinterpret_cast<float *>(raw + 236))
                *reinterpret_cast<signed char *>(raw + 260) = 1;
        }
        return true;
    }

    case 200: {
        int facing;
        int input_product;
        short counter;

        resolve_stage_surface_landing_transition();
        *reinterpret_cast<_BYTE *>(raw + 1150) = 1;
        if (*reinterpret_cast<float *>(raw + 244) > 9.0f) {
            adjusted = static_cast<float>(*reinterpret_cast<float *>(raw + 244) - 0.5);
            *reinterpret_cast<float *>(raw + 244) = adjusted;
            if (adjusted < 9.0f)
                *reinterpret_cast<float *>(raw + 244) = 9.0f;
        }
        advance_frame_and_dispatch();
        if (*reinterpret_cast<_WORD *>(raw + 318) == 1) {
            if (!(*reinterpret_cast<int *>(raw + 324) % 5)) {
                facing = *reinterpret_cast<unsigned char *>(raw + 260);
                emit_fighter_effect_433cc0(
                    124,
                    static_cast<float>((*reinterpret_cast<float *>(raw + 236) + 50.0)
                        - static_cast<float>(mt19937_next_u32() % 100)),
                    static_cast<float>(static_cast<float>(mt19937_next_u32() % 200)
                        + *reinterpret_cast<float *>(raw + 240)),
                    facing,
                    1);
            }
            if (*reinterpret_cast<int *>(raw + 1720) < 0) {
                input_product = static_cast<signed char>(*reinterpret_cast<_BYTE *>(raw + 260))
                    * *reinterpret_cast<int *>(raw + 1716);
                if (input_product > 0)
                    set_action(212);
                else
                    set_action(211);
                return true;
            }
            counter = static_cast<short>(++*reinterpret_cast<_WORD *>(raw + 1840));
            input_product = static_cast<signed char>(*reinterpret_cast<_BYTE *>(raw + 260))
                * *reinterpret_cast<int *>(raw + 1716);
            if ((input_product > 0 && counter > 45) || (input_product <= 0 && counter > 5)) {
                set_action(204);
                return true;
            }
        }
        if (!*reinterpret_cast<_WORD *>(raw + 318)
            && !*reinterpret_cast<_WORD *>(raw + 322)
            && *reinterpret_cast<_WORD *>(raw + 320) == 2) {
            *reinterpret_cast<float *>(raw + 244) = 10.0f;
            facing = *reinterpret_cast<unsigned char *>(raw + 260);
            emit_fighter_effect_433cc0(
                125,
                *reinterpret_cast<float *>(raw + 236) + static_cast<float>(80 * static_cast<signed char>(facing)),
                static_cast<float>(*reinterpret_cast<float *>(raw + 240) + 80.0),
                facing,
                1);
            emit_fighter_effect_433cc0(
                126,
                *reinterpret_cast<float *>(raw + 236),
                static_cast<float>(*reinterpret_cast<float *>(raw + 240) + 80.0),
                facing,
                1);
            dispatch_indexed_event_member(0x1Fu);
        }
        return true;
    }

    case 201: {
        int opposite_facing;

        if (!*reinterpret_cast<_WORD *>(raw + 318)
            && static_cast<__int16>(*reinterpret_cast<_WORD *>(raw + 320)) <= 1)
            resolve_stage_surface_landing_transition();
        if (*reinterpret_cast<_WORD *>(raw + 318) == 3) {
            resolve_stage_surface_landing_transition();
            adjusted = static_cast<float>(*reinterpret_cast<float *>(raw + 244) + 2.0);
            *reinterpret_cast<float *>(raw + 244) = adjusted;
            if (adjusted > 0.0f)
                *reinterpret_cast<float *>(raw + 244) = 0.0f;
        }
        if (!is_y_at_or_below_stage_surface(this) && !(*reinterpret_cast<int *>(raw + 324) % 5)) {
            opposite_facing = static_cast<unsigned char>(-*reinterpret_cast<signed char *>(raw + 260));
            emit_fighter_effect_433cc0(
                124,
                static_cast<float>((*reinterpret_cast<float *>(raw + 236) + 50.0)
                    - static_cast<float>(mt19937_next_u32() % 100)),
                static_cast<float>(static_cast<float>(mt19937_next_u32() % 200)
                    + *reinterpret_cast<float *>(raw + 240)),
                opposite_facing,
                1);
        }
        if (static_cast<__int16>(*reinterpret_cast<_WORD *>(raw + 318)) < 3) {
            *reinterpret_cast<float *>(raw + 248) =
                *reinterpret_cast<float *>(raw + 248) - *reinterpret_cast<float *>(raw + 256);
            if (has_crossed_stage_surface_while_descending()) {
                *reinterpret_cast<float *>(raw + 248) = 0.0f;
                *reinterpret_cast<float *>(raw + 240) = alice_stage_surface_height_at_x(this);
                set_sequence(3);
                return true;
            }
        }
        if (advance_frame_and_dispatch()) {
            set_action(0);
            *reinterpret_cast<float *>(raw + 244) = 0.0f;
            return true;
        }
        if (!*reinterpret_cast<_WORD *>(raw + 318)
            && !*reinterpret_cast<_WORD *>(raw + 322)
            && *reinterpret_cast<_WORD *>(raw + 320) == 2) {
            *reinterpret_cast<float *>(raw + 244) = -10.0f;
            *reinterpret_cast<float *>(raw + 248) = 4.5f;
            *reinterpret_cast<float *>(raw + 256) = 0.6000000238418579f;
            opposite_facing = static_cast<unsigned char>(-*reinterpret_cast<signed char *>(raw + 260));
            emit_fighter_effect_433cc0(
                125,
                *reinterpret_cast<float *>(raw + 236),
                static_cast<float>(*reinterpret_cast<float *>(raw + 240) + 80.0),
                opposite_facing,
                1);
            emit_fighter_effect_433cc0(
                126,
                *reinterpret_cast<float *>(raw + 236),
                static_cast<float>(*reinterpret_cast<float *>(raw + 240) + 80.0),
                opposite_facing,
                1);
            dispatch_indexed_event_member(0x1Fu);
        }
        return true;
    }

    case 202: {
        int facing;

        *reinterpret_cast<float *>(raw + 248) =
            *reinterpret_cast<float *>(raw + 248) - *reinterpret_cast<float *>(raw + 256);
        if (has_crossed_stage_surface_while_descending()) {
            zero_velocity_acceleration();
            *reinterpret_cast<float *>(raw + 240) = alice_stage_surface_height_at_x(this);
            set_action(10);
            return true;
        }
        if ((*reinterpret_cast<_WORD *>(raw + 318) == 1 || *reinterpret_cast<_WORD *>(raw + 318) == 2)
            && !(*reinterpret_cast<int *>(raw + 324) % 5)) {
            facing = *reinterpret_cast<unsigned char *>(raw + 260);
            emit_fighter_effect_433cc0(
                124,
                static_cast<float>((*reinterpret_cast<float *>(raw + 236) + 50.0)
                    - static_cast<float>(mt19937_next_u32() % 100)),
                static_cast<float>(static_cast<float>(mt19937_next_u32() % 200)
                    + *reinterpret_cast<float *>(raw + 240)),
                facing,
                1);
        }
        advance_frame_and_dispatch();
        if (!*reinterpret_cast<_WORD *>(raw + 318)
            && !*reinterpret_cast<_WORD *>(raw + 322)
            && *reinterpret_cast<_WORD *>(raw + 320) == 2) {
            *reinterpret_cast<_WORD *>(raw + 1840) = 0;
            *reinterpret_cast<float *>(raw + 244) = 8.5f;
            *reinterpret_cast<float *>(raw + 248) = 5.0f;
            *reinterpret_cast<float *>(raw + 256) = 0.6000000238418579f;
            facing = *reinterpret_cast<unsigned char *>(raw + 260);
            emit_fighter_effect_433cc0(
                125,
                *reinterpret_cast<float *>(raw + 236) + static_cast<float>(80 * static_cast<signed char>(facing)),
                static_cast<float>(*reinterpret_cast<float *>(raw + 240) + 110.0),
                facing,
                1);
            emit_fighter_effect_433cc0(
                126,
                *reinterpret_cast<float *>(raw + 236),
                static_cast<float>(*reinterpret_cast<float *>(raw + 240) + 110.0),
                facing,
                1);
            dispatch_indexed_event_member(0x1Fu);
        }
        if (!*reinterpret_cast<int *>(raw + 324)
            && !*reinterpret_cast<_WORD *>(raw + 322)
            && !*reinterpret_cast<_WORD *>(raw + 320)
            && *reinterpret_cast<_WORD *>(raw + 318) == 2)
            face_opponent_and_flip_horizontal_velocity();
        return true;
    }

    case 203: {
        int opposite_facing;

        *reinterpret_cast<float *>(raw + 248) =
            *reinterpret_cast<float *>(raw + 248) - *reinterpret_cast<float *>(raw + 256);
        if (has_crossed_stage_surface_while_descending()) {
            zero_velocity_acceleration();
            *reinterpret_cast<float *>(raw + 240) = alice_stage_surface_height_at_x(this);
            *reinterpret_cast<_WORD *>(raw + 322) = 0;
            set_action(10);
            return true;
        }
        if (static_cast<__int16>(*reinterpret_cast<_WORD *>(raw + 318)) < 3
            && !(*reinterpret_cast<int *>(raw + 324) % 5)) {
            opposite_facing = static_cast<unsigned char>(-*reinterpret_cast<signed char *>(raw + 260));
            emit_fighter_effect_433cc0(
                124,
                static_cast<float>((*reinterpret_cast<float *>(raw + 236) + 50.0)
                    - static_cast<float>(mt19937_next_u32() % 100)),
                static_cast<float>(static_cast<float>(mt19937_next_u32() % 200)
                    + *reinterpret_cast<float *>(raw + 240)),
                opposite_facing,
                1);
        }
        advance_frame_and_dispatch();
        if (!*reinterpret_cast<_WORD *>(raw + 318)
            && !*reinterpret_cast<_WORD *>(raw + 322)
            && *reinterpret_cast<_WORD *>(raw + 320) == 1) {
            *reinterpret_cast<float *>(raw + 244) = -8.5f;
            *reinterpret_cast<float *>(raw + 248) = 5.0f;
            *reinterpret_cast<float *>(raw + 256) = 0.6000000238418579f;
            opposite_facing = static_cast<unsigned char>(-*reinterpret_cast<signed char *>(raw + 260));
            emit_fighter_effect_433cc0(
                125,
                *reinterpret_cast<float *>(raw + 236),
                static_cast<float>(*reinterpret_cast<float *>(raw + 240) + 120.0),
                opposite_facing,
                1);
            emit_fighter_effect_433cc0(
                126,
                *reinterpret_cast<float *>(raw + 236),
                static_cast<float>(*reinterpret_cast<float *>(raw + 240) + 120.0),
                opposite_facing,
                1);
            dispatch_indexed_event_member(0x1Fu);
        }
        if (!*reinterpret_cast<int *>(raw + 324)
            && !*reinterpret_cast<_WORD *>(raw + 322)
            && !*reinterpret_cast<_WORD *>(raw + 320)
            && *reinterpret_cast<_WORD *>(raw + 318) == 2)
            face_opponent_and_flip_horizontal_velocity();
        return true;
    }

    case 204:
        resolve_stage_surface_landing_transition();
        adjusted = static_cast<float>(*reinterpret_cast<float *>(raw + 244) - 0.5);
        *reinterpret_cast<float *>(raw + 244) = adjusted;
        if (adjusted < 0.0f) {
            *reinterpret_cast<float *>(raw + 244) = 0.0f;
            *reinterpret_cast<_BYTE *>(raw + 1150) = 0;
        }
        if (advance_frame_and_dispatch()) {
            set_action(0);
            *reinterpret_cast<_BYTE *>(raw + 1150) = 0;
        }
        return true;


    case 208:
        if (!*reinterpret_cast<_WORD *>(raw + 318))
            resolve_stage_surface_landing_transition();
        if (has_crossed_stage_surface_while_descending()) {
            set_action(10);
            *reinterpret_cast<float *>(raw + 240) = alice_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return true;
        }
        if (is_y_at_or_below_stage_surface(this) || *reinterpret_cast<float *>(raw + 248) > 0.0f)
            *reinterpret_cast<_WORD *>(raw + 1198) = 2;
        if (static_cast<__int16>(*reinterpret_cast<_WORD *>(raw + 318)) > 0) {
            adjusted = *reinterpret_cast<float *>(raw + 248) - *reinterpret_cast<float *>(raw + 256);
            *reinterpret_cast<float *>(raw + 248) = adjusted;
            if (adjusted < -20.0f)
                *reinterpret_cast<float *>(raw + 248) = -20.0f;
        }
        advance_frame_and_dispatch();
        if (!*reinterpret_cast<int *>(raw + 324)
            && !*reinterpret_cast<_WORD *>(raw + 322)
            && !*reinterpret_cast<_WORD *>(raw + 320)
            && *reinterpret_cast<_WORD *>(raw + 318) == 1) {
            *reinterpret_cast<float *>(raw + 244) = 0.0f;
            *reinterpret_cast<float *>(raw + 248) = 19.0f;
            *reinterpret_cast<float *>(raw + 256) = 0.65f;
            *reinterpret_cast<_BYTE *>(raw + 1150) = 0;
            emit_fighter_effect_433cc0(
                63,
                *reinterpret_cast<float *>(raw + 236),
                *reinterpret_cast<float *>(raw + 240),
                *reinterpret_cast<unsigned char *>(raw + 260),
                1);
        }
        return true;

    case 209:
    case 212:
    case 221:
        if (!*reinterpret_cast<_WORD *>(raw + 318))
            resolve_stage_surface_landing_transition();
        if (has_crossed_stage_surface_while_descending()) {
            set_action(10);
            *reinterpret_cast<float *>(raw + 240) = alice_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return true;
        }
        if (is_y_at_or_below_stage_surface(this) || *reinterpret_cast<float *>(raw + 248) > 0.0f)
            *reinterpret_cast<_WORD *>(raw + 1198) = 2;
        if (static_cast<__int16>(*reinterpret_cast<_WORD *>(raw + 318)) > 0) {
            adjusted = *reinterpret_cast<float *>(raw + 248) - *reinterpret_cast<float *>(raw + 256);
            *reinterpret_cast<float *>(raw + 248) = adjusted;
            if (adjusted < -20.0f)
                *reinterpret_cast<float *>(raw + 248) = -20.0f;
        }
        advance_frame_and_dispatch();
        if (!*reinterpret_cast<int *>(raw + 324)
            && !*reinterpret_cast<_WORD *>(raw + 322)
            && !*reinterpret_cast<_WORD *>(raw + 320)
            && *reinterpret_cast<_WORD *>(raw + 318) == 1) {
            *reinterpret_cast<float *>(raw + 244) = 9.0f;
            *reinterpret_cast<float *>(raw + 248) = 15.0f;
            *reinterpret_cast<float *>(raw + 256) = 0.65f;
            *reinterpret_cast<_BYTE *>(raw + 1150) = 0;
            emit_fighter_effect_433cc0(
                63,
                *reinterpret_cast<float *>(raw + 236),
                *reinterpret_cast<float *>(raw + 240),
                *reinterpret_cast<unsigned char *>(raw + 260),
                1);
        }
        return true;

    case 210:
    case 222:
        if (!*reinterpret_cast<_WORD *>(raw + 318))
            resolve_stage_surface_landing_transition();
        if (has_crossed_stage_surface_while_descending()) {
            set_action(10);
            *reinterpret_cast<float *>(raw + 240) = alice_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return true;
        }
        if (is_y_at_or_below_stage_surface(this) || *reinterpret_cast<float *>(raw + 248) > 0.0f)
            *reinterpret_cast<_WORD *>(raw + 1198) = 2;
        if (static_cast<__int16>(*reinterpret_cast<_WORD *>(raw + 318)) > 0) {
            adjusted = *reinterpret_cast<float *>(raw + 248) - *reinterpret_cast<float *>(raw + 256);
            *reinterpret_cast<float *>(raw + 248) = adjusted;
            if (adjusted < -20.0f)
                *reinterpret_cast<float *>(raw + 248) = -20.0f;
        }
        advance_frame_and_dispatch();
        if (!*reinterpret_cast<int *>(raw + 324)
            && !*reinterpret_cast<_WORD *>(raw + 322)
            && !*reinterpret_cast<_WORD *>(raw + 320)
            && *reinterpret_cast<_WORD *>(raw + 318) == 1) {
            *reinterpret_cast<float *>(raw + 244) = -9.0f;
            *reinterpret_cast<float *>(raw + 248) = 15.0f;
            *reinterpret_cast<float *>(raw + 256) = 0.65f;
            *reinterpret_cast<_BYTE *>(raw + 1150) = 0;
            emit_fighter_effect_433cc0(
                63,
                *reinterpret_cast<float *>(raw + 236),
                *reinterpret_cast<float *>(raw + 240),
                *reinterpret_cast<unsigned char *>(raw + 260),
                1);
        }
        return true;

    case 211:
        if (!*reinterpret_cast<_WORD *>(raw + 318))
            resolve_stage_surface_landing_transition();
        if (has_crossed_stage_surface_while_descending()) {
            set_action(10);
            *reinterpret_cast<float *>(raw + 240) = alice_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return true;
        }
        if (is_y_at_or_below_stage_surface(this) || *reinterpret_cast<float *>(raw + 248) > 0.0f)
            *reinterpret_cast<_WORD *>(raw + 1198) = 2;
        if (static_cast<__int16>(*reinterpret_cast<_WORD *>(raw + 318)) > 0) {
            adjusted = *reinterpret_cast<float *>(raw + 248) - *reinterpret_cast<float *>(raw + 256);
            *reinterpret_cast<float *>(raw + 248) = adjusted;
            if (adjusted < -20.0f)
                *reinterpret_cast<float *>(raw + 248) = -20.0f;
        }
        advance_frame_and_dispatch();
        if (!*reinterpret_cast<int *>(raw + 324)
            && !*reinterpret_cast<_WORD *>(raw + 322)
            && !*reinterpret_cast<_WORD *>(raw + 320)
            && *reinterpret_cast<_WORD *>(raw + 318) == 1) {
            *reinterpret_cast<float *>(raw + 244) = 2.0f;
            *reinterpret_cast<float *>(raw + 248) = 19.0f;
            *reinterpret_cast<float *>(raw + 256) = 0.65f;
            *reinterpret_cast<_BYTE *>(raw + 1150) = 0;
            emit_fighter_effect_433cc0(
                63,
                *reinterpret_cast<float *>(raw + 236),
                *reinterpret_cast<float *>(raw + 240),
                *reinterpret_cast<unsigned char *>(raw + 260),
                1);
        }
        return true;


    case 214: {
        int vertical_input;
        int horizontal_input;
        int input_product;
        int facing;
        int sequence;
        short target_angle;
        short angle_delta;
        float phase;
        float magnitude;
        float velocity_x;
        float velocity_y;
        unsigned char *peer;

        if (advance_frame_and_dispatch()) {
            set_action(9);
            return true;
        }
        if (!*reinterpret_cast<_DWORD *>(raw + 324)) {
            if (!*reinterpret_cast<_WORD *>(raw + 322)
                && !*reinterpret_cast<_WORD *>(raw + 320)
                && *reinterpret_cast<_WORD *>(raw + 318) == 1)
                dispatch_indexed_event_member(0x1Fu);
            if (!*reinterpret_cast<_WORD *>(raw + 322)
                && !*reinterpret_cast<_WORD *>(raw + 320)
                && *reinterpret_cast<_WORD *>(raw + 318) == 6) {
                set_action(9);
                return true;
            }
        }

        vertical_input = *reinterpret_cast<int *>(raw + 1720);
        horizontal_input = *reinterpret_cast<int *>(raw + 1716);
        facing = *reinterpret_cast<signed char *>(raw + 260);
        input_product = facing * horizontal_input;
        if (vertical_input > 0) {
            if (input_product > 0)
                *reinterpret_cast<_WORD *>(raw + 1842) = static_cast<_WORD>(-45);
            else if (input_product < 0)
                *reinterpret_cast<_WORD *>(raw + 1842) = static_cast<_WORD>(-135);
            else
                *reinterpret_cast<_WORD *>(raw + 1842) = static_cast<_WORD>(-90);
        } else if (vertical_input < 0) {
            if (input_product > 0)
                *reinterpret_cast<_WORD *>(raw + 1842) = 45;
            else if (input_product < 0)
                *reinterpret_cast<_WORD *>(raw + 1842) = 135;
            else
                *reinterpret_cast<_WORD *>(raw + 1842) = 90;
        } else {
            if (input_product > 0)
                *reinterpret_cast<_WORD *>(raw + 1842) = 0;
            else if (input_product < 0)
                *reinterpret_cast<_WORD *>(raw + 1842) = 180;
        }

        sequence = *reinterpret_cast<_WORD *>(raw + 318);
        if (sequence == 5 || sequence == 6)
            *reinterpret_cast<float *>(raw + 248) =
                *reinterpret_cast<float *>(raw + 248) - *reinterpret_cast<float *>(raw + 256);

        if (sequence > 0 && sequence < 5) {
            ++*reinterpret_cast<_WORD *>(raw + 1846);
            target_angle = *reinterpret_cast<short *>(raw + 1842);
            phase = *reinterpret_cast<float *>(raw + 1856);
            angle_delta = static_cast<short>(target_angle - static_cast<int>(phase));
            *reinterpret_cast<_WORD *>(raw + 1844) = static_cast<_WORD>(angle_delta);
            if (angle_delta > 180) {
                angle_delta = static_cast<short>(angle_delta - 360);
                *reinterpret_cast<_WORD *>(raw + 1844) = static_cast<_WORD>(angle_delta);
            }
            if (angle_delta < -180) {
                angle_delta = static_cast<short>(angle_delta + 360);
                *reinterpret_cast<_WORD *>(raw + 1844) = static_cast<_WORD>(angle_delta);
            }

            if (angle_delta > 0) {
                phase = static_cast<float>(phase + (*reinterpret_cast<_DWORD *>(raw + 1208) ? 0.5 : 1.5));
                *reinterpret_cast<float *>(raw + 1856) = phase;
            }
            if (angle_delta < 0) {
                phase = static_cast<float>(phase - (*reinterpret_cast<_DWORD *>(raw + 1208) ? 0.5 : 1.5));
                *reinterpret_cast<float *>(raw + 1856) = phase;
            }

            phase = *reinterpret_cast<float *>(raw + 1856);
            magnitude = *reinterpret_cast<float *>(raw + 1852);
            velocity_x = static_cast<float>(lookup_orientation_cosine_quantized_abs(phase) * magnitude);
            *reinterpret_cast<float *>(raw + 244) = velocity_x;
            velocity_y = static_cast<float>(lookup_orientation_sine_quantized_abs(phase) * magnitude);
            *reinterpret_cast<float *>(raw + 248) = velocity_y;
            if (*reinterpret_cast<float *>(raw + 240) > 680.0f && velocity_y > 0.0f)
                *reinterpret_cast<float *>(raw + 248) = 0.0f;

            magnitude = static_cast<float>(magnitude + 0.30000001192092896);
            *reinterpret_cast<float *>(raw + 1852) = magnitude;
            if (magnitude > 12.0f)
                *reinterpret_cast<float *>(raw + 1852) = 12.0f;

            if (*reinterpret_cast<_DWORD *>(raw + 1208))
                adjust_counter_482(10, 1);
            else
                adjust_counter_482(5, 1);

            *reinterpret_cast<float *>(raw + 300) = -phase;
            if (*reinterpret_cast<float *>(raw + 244) < 0.0f)
                *reinterpret_cast<float *>(raw + 300) = static_cast<float>(180.0 - phase);

            velocity_x = *reinterpret_cast<float *>(raw + 244);
            sequence = *reinterpret_cast<_WORD *>(raw + 318);
            if (velocity_x < 0.0f && sequence == 1)
                set_sequence(3);
            if (velocity_x >= 0.0f && sequence == 3)
                set_sequence(1);
            if (velocity_x < 0.0f && sequence == 2)
                set_sequence(4);
            if (velocity_x >= 0.0f && sequence == 4)
                set_sequence(2);

            if (*reinterpret_cast<int *>(raw + 324) % 5 == 1) {
                facing = *reinterpret_cast<unsigned char *>(raw + 260);
                emit_fighter_effect_433cc0(
                    125,
                    static_cast<float>(lookup_orientation_cosine_quantized_abs(phase)
                        * 100.0 * static_cast<signed char>(facing)
                        + *reinterpret_cast<float *>(raw + 236)),
                    static_cast<float>(lookup_orientation_sine_quantized_abs(phase)
                        * 100.0 + *reinterpret_cast<float *>(raw + 240) + 100.0),
                    facing,
                    1);
            }
        }

        if ((*reinterpret_cast<_DWORD *>(raw + 1736)
                || *reinterpret_cast<short *>(raw + 1846) <= 10)
            && *reinterpret_cast<short *>(raw + 1154) > 0) {
            if (has_crossed_stage_surface_while_descending()) {
                *reinterpret_cast<float *>(raw + 240) = alice_stage_surface_height_at_x(this);
                *reinterpret_cast<float *>(raw + 256) = 0.0f;
                *reinterpret_cast<float *>(raw + 248) = 0.0f;
                if (*reinterpret_cast<short *>(raw + 318) >= 5) {
                    set_action(10);
                    zero_velocity_acceleration();
                } else {
                    reinterpret_cast<FighterActionScratchView *>(raw + 4)->reset();
                    set_action(215);
                }
            }
            return true;
        }

        reinterpret_cast<FighterActionScratchView *>(raw + 4)->reset();
        sequence = *reinterpret_cast<_WORD *>(raw + 318);
        peer = reinterpret_cast<unsigned char *>(*reinterpret_cast<_DWORD *>(raw + 368));
        if (sequence == 1 || sequence == 2) {
            facing = *reinterpret_cast<signed char *>(raw + 260);
            if (facing == 1) {
                if (*reinterpret_cast<float *>(peer + 236) < *reinterpret_cast<float *>(raw + 236)) {
                    *reinterpret_cast<signed char *>(raw + 260) = -1;
                    *reinterpret_cast<float *>(raw + 244) = -*reinterpret_cast<float *>(raw + 244);
                    set_sequence(6);
                } else {
                    set_sequence(5);
                }
            } else if (*reinterpret_cast<float *>(peer + 236) > *reinterpret_cast<float *>(raw + 236)) {
                *reinterpret_cast<signed char *>(raw + 260) = static_cast<signed char>(-facing);
                *reinterpret_cast<float *>(raw + 244) = -*reinterpret_cast<float *>(raw + 244);
                set_sequence(6);
            } else {
                set_sequence(5);
            }
        }

        sequence = *reinterpret_cast<_WORD *>(raw + 318);
        if (sequence == 3 || sequence == 4) {
            facing = *reinterpret_cast<signed char *>(raw + 260);
            if (facing == 1) {
                if (*reinterpret_cast<float *>(peer + 236) < *reinterpret_cast<float *>(raw + 236)) {
                    *reinterpret_cast<signed char *>(raw + 260) = -1;
                    *reinterpret_cast<float *>(raw + 244) = -*reinterpret_cast<float *>(raw + 244);
                    set_sequence(5);
                } else {
                    set_sequence(6);
                }
            } else if (*reinterpret_cast<float *>(peer + 236) > *reinterpret_cast<float *>(raw + 236)) {
                *reinterpret_cast<signed char *>(raw + 260) = static_cast<signed char>(-facing);
                *reinterpret_cast<float *>(raw + 244) = -*reinterpret_cast<float *>(raw + 244);
                set_sequence(5);
            } else {
                set_sequence(6);
            }
        }
        return true;
    }

    case 215:
        resolve_stage_surface_landing_transition();
        if (*reinterpret_cast<float *>(raw + 244) > 0.0f) {
            adjusted = static_cast<float>(*reinterpret_cast<float *>(raw + 244) - 0.75);
            *reinterpret_cast<float *>(raw + 244) = adjusted;
            if (adjusted < 0.0f)
                *reinterpret_cast<float *>(raw + 244) = 0.0f;
        }
        if (*reinterpret_cast<float *>(raw + 244) < 0.0f) {
            adjusted = static_cast<float>(*reinterpret_cast<float *>(raw + 244) + 0.75);
            *reinterpret_cast<float *>(raw + 244) = adjusted;
            if (adjusted > 0.0f)
                *reinterpret_cast<float *>(raw + 244) = 0.0f;
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        return true;


    case 220:
        if (!*reinterpret_cast<_WORD *>(raw + 318))
            resolve_stage_surface_landing_transition();
        if (has_crossed_stage_surface_while_descending()) {
            set_action(10);
            *reinterpret_cast<float *>(raw + 240) = alice_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return true;
        }
        if (is_y_at_or_below_stage_surface(this) || *reinterpret_cast<float *>(raw + 248) > 0.0f)
            *reinterpret_cast<_WORD *>(raw + 1198) = 2;
        if (static_cast<__int16>(*reinterpret_cast<_WORD *>(raw + 318)) > 0) {
            adjusted = *reinterpret_cast<float *>(raw + 248) - *reinterpret_cast<float *>(raw + 256);
            *reinterpret_cast<float *>(raw + 248) = adjusted;
            if (adjusted < -20.0f)
                *reinterpret_cast<float *>(raw + 248) = -20.0f;
        }
        advance_frame_and_dispatch();
        if (!*reinterpret_cast<int *>(raw + 324)
            && !*reinterpret_cast<_WORD *>(raw + 322)
            && !*reinterpret_cast<_WORD *>(raw + 320)
            && *reinterpret_cast<_WORD *>(raw + 318) == 1) {
            *reinterpret_cast<float *>(raw + 244) = 0.0f;
            *reinterpret_cast<float *>(raw + 248) = 19.0f;
            *reinterpret_cast<float *>(raw + 256) = 0.65f;
            *reinterpret_cast<_BYTE *>(raw + 1150) = 0;
            emit_fighter_effect_433cc0(
                63,
                *reinterpret_cast<float *>(raw + 236),
                *reinterpret_cast<float *>(raw + 240),
                *reinterpret_cast<unsigned char *>(raw + 260),
                1);
        }
        return true;

    case 223: {
        int facing;
        int input_product;
        short counter;

        resolve_stage_surface_landing_transition();
        *reinterpret_cast<_BYTE *>(raw + 1150) = 1;
        advance_frame_and_dispatch();
        if (*reinterpret_cast<_WORD *>(raw + 318) == 1) {
            if (!(*reinterpret_cast<int *>(raw + 324) % 5)) {
                facing = *reinterpret_cast<unsigned char *>(raw + 260);
                emit_fighter_effect_433cc0(
                    124,
                    static_cast<float>((*reinterpret_cast<float *>(raw + 236) + 50.0)
                        - static_cast<float>(mt19937_next_u32() % 100)),
                    static_cast<float>(static_cast<float>(mt19937_next_u32() % 200)
                        + *reinterpret_cast<float *>(raw + 240)),
                    facing,
                    1);
            }
            counter = static_cast<short>(++*reinterpret_cast<_WORD *>(raw + 1840));
            input_product = *reinterpret_cast<int *>(raw + 1716)
                * static_cast<signed char>(*reinterpret_cast<_BYTE *>(raw + 260));
            if ((input_product <= 0 && counter >= 13) || counter > 45) {
                set_action(204);
                return true;
            }
        }
        if (!*reinterpret_cast<_WORD *>(raw + 318)
            && !*reinterpret_cast<_WORD *>(raw + 322)
            && *reinterpret_cast<_WORD *>(raw + 320) == 4) {
            *reinterpret_cast<float *>(raw + 244) = 5.0f;
            facing = *reinterpret_cast<unsigned char *>(raw + 260);
            emit_fighter_effect_433cc0(
                125,
                *reinterpret_cast<float *>(raw + 236) + static_cast<float>(80 * static_cast<signed char>(facing)),
                static_cast<float>(*reinterpret_cast<float *>(raw + 240) + 80.0),
                facing,
                1);
            emit_fighter_effect_433cc0(
                126,
                *reinterpret_cast<float *>(raw + 236),
                static_cast<float>(*reinterpret_cast<float *>(raw + 240) + 80.0),
                facing,
                1);
            dispatch_indexed_event_member(0x1Fu);
        }
        return true;
    }


    case 300:
        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(0))
            return true;
        if (*reinterpret_cast<_BYTE *>(raw + 1150)) {
            adjusted = static_cast<float>(*reinterpret_cast<float *>(raw + 244) - 0.5);
            *reinterpret_cast<float *>(raw + 244) = adjusted;
            if (adjusted < 0.0f) {
                *reinterpret_cast<float *>(raw + 244) = 0.0f;
                *reinterpret_cast<_BYTE *>(raw + 1150) = 0;
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (!*reinterpret_cast<_WORD *>(raw + 322) && *reinterpret_cast<_WORD *>(raw + 320) == 2) {
            dispatch_indexed_event_member(0x1Bu);
            *reinterpret_cast<_BYTE *>(raw + 1150) = 0;
        }
        return true;

    case 301: {
        float spawn_payload[3];
        int facing;

        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(0))
            return true;
        if (*reinterpret_cast<_BYTE *>(raw + 1150)) {
            adjusted = static_cast<float>(*reinterpret_cast<float *>(raw + 244) - 0.5);
            *reinterpret_cast<float *>(raw + 244) = adjusted;
            if (adjusted < 0.0f) {
                *reinterpret_cast<float *>(raw + 244) = 0.0f;
                *reinterpret_cast<_BYTE *>(raw + 1150) = 0;
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (!*reinterpret_cast<_WORD *>(raw + 322) && *reinterpret_cast<_WORD *>(raw + 320) == 2) {
            spawn_payload[0] = 0.0f;
            spawn_payload[1] = 0.0f;
            spawn_payload[2] = 1.0f;
            facing = *reinterpret_cast<unsigned char *>(raw + 260);
            spawn_owned_object_via_manager(
                849,
                *reinterpret_cast<float *>(raw + 236) + static_cast<float>(30 * static_cast<signed char>(facing)),
                static_cast<float>(*reinterpret_cast<float *>(raw + 240) + 100.0),
                facing,
                1,
                reinterpret_cast<int>(spawn_payload),
                3);
        }
        return true;
    }

    case 302: {
        float spawn_payload[3];
        int facing;

        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(1))
            return true;
        if (*reinterpret_cast<_BYTE *>(raw + 1150)) {
            adjusted = static_cast<float>(*reinterpret_cast<float *>(raw + 244) - 0.5);
            *reinterpret_cast<float *>(raw + 244) = adjusted;
            if (adjusted < 0.0f) {
                *reinterpret_cast<float *>(raw + 244) = 0.0f;
                *reinterpret_cast<_BYTE *>(raw + 1150) = 0;
            }
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (!*reinterpret_cast<_WORD *>(raw + 322) && *reinterpret_cast<_WORD *>(raw + 320) == 3) {
            dispatch_indexed_event_member(0x1Du);
            spawn_payload[0] = 0.0f;
            spawn_payload[1] = 0.0f;
            spawn_payload[2] = 8.0f;
            facing = *reinterpret_cast<unsigned char *>(raw + 260);
            spawn_owned_object_via_manager(
                849,
                *reinterpret_cast<float *>(raw + 236) + static_cast<float>(110 * static_cast<signed char>(facing)),
                static_cast<float>(*reinterpret_cast<float *>(raw + 240) + 105.0),
                facing,
                1,
                reinterpret_cast<int>(spawn_payload),
                3);
        }
        return true;
    }

    case 303:
        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(0))
            return true;
        if (*reinterpret_cast<signed char *>(raw + 1150) > 0
            || *reinterpret_cast<float *>(raw + 244) > 0.0f) {
            adjusted = static_cast<float>(*reinterpret_cast<float *>(raw + 244) - 0.6000000238418579);
            *reinterpret_cast<float *>(raw + 244) = adjusted;
            if (adjusted < 0.0f) {
                *reinterpret_cast<float *>(raw + 244) = 0.0f;
                *reinterpret_cast<_BYTE *>(raw + 1150) = 0;
            }
        }
        if (advance_frame_and_dispatch())
            set_action(2);
        if (!*reinterpret_cast<_WORD *>(raw + 322) && *reinterpret_cast<_WORD *>(raw + 320) == 2)
            *reinterpret_cast<float *>(raw + 244) = 6.0f;
        if (!*reinterpret_cast<_WORD *>(raw + 322) && *reinterpret_cast<_WORD *>(raw + 320) == 3)
            dispatch_indexed_event_member(0x1Cu);
        return true;


    case 304: {
        float spawn_payload[3];
        int spawn_index;
        int facing;

        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(1))
            return true;
        if (*reinterpret_cast<float *>(raw + 244) > 0.0f) {
            adjusted = static_cast<float>(*reinterpret_cast<float *>(raw + 244) - 1.0);
            *reinterpret_cast<float *>(raw + 244) = adjusted;
            if (adjusted < 0.0f)
                *reinterpret_cast<float *>(raw + 244) = 0.0f;
        }
        if (*reinterpret_cast<__int16 *>(raw + 320) >= 4
            && *reinterpret_cast<__int16 *>(raw + 320) <= 6) {
            if (static_cast<__int16>(*reinterpret_cast<_WORD *>(raw + 1840)) % 4 == 0
                && *reinterpret_cast<__int16 *>(raw + 1842) <= 4) {
                spawn_index = *reinterpret_cast<__int16 *>(raw + 1842);
                spawn_payload[0] = static_cast<float>(-10.0 - 13.0 * spawn_index);
                spawn_payload[1] = 30.0f;
                spawn_payload[2] = 11.0f;
                facing = *reinterpret_cast<unsigned char *>(raw + 260);
                spawn_owned_object_via_manager(
                    849,
                    static_cast<float>(*reinterpret_cast<float *>(raw + 236) + 30.0),
                    static_cast<float>(*reinterpret_cast<float *>(raw + 240) + 100.0),
                    facing,
                    1,
                    reinterpret_cast<int>(spawn_payload),
                    3);
                ++*reinterpret_cast<_WORD *>(raw + 1842);
            }
            ++*reinterpret_cast<_WORD *>(raw + 1840);
        }
        if (advance_frame_and_dispatch())
            set_action(2);
        return true;
    }

    case 305:
        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(1))
            return true;
        if (*reinterpret_cast<__int16 *>(raw + 320) > 3) {
            adjusted = static_cast<float>(*reinterpret_cast<float *>(raw + 244) - 0.75);
            *reinterpret_cast<float *>(raw + 244) = adjusted;
            if (adjusted < 0.0f)
                *reinterpret_cast<float *>(raw + 244) = 0.0f;
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (!*reinterpret_cast<_WORD *>(raw + 322) && *reinterpret_cast<_WORD *>(raw + 320) == 2)
            dispatch_indexed_event_member(0x1Du);
        return true;

    case 306:
        *reinterpret_cast<float *>(raw + 248) =
            *reinterpret_cast<float *>(raw + 248) - *reinterpret_cast<float *>(raw + 256);
        if (has_crossed_stage_surface_while_descending()) {
            set_action(10);
            *reinterpret_cast<float *>(raw + 240) = alice_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return true;
        }
        if (advance_frame_and_dispatch())
            set_action(9);
        if (!*reinterpret_cast<_WORD *>(raw + 322) && *reinterpret_cast<_WORD *>(raw + 320) == 4)
            dispatch_indexed_event_member(0x1Bu);
        return true;


    case 307: {
        float spawn_payload[3];
        int facing;

        if (*reinterpret_cast<__int16 *>(raw + 320) >= 11)
            *reinterpret_cast<float *>(raw + 248) =
                *reinterpret_cast<float *>(raw + 248) - *reinterpret_cast<float *>(raw + 256);
        if (has_crossed_stage_surface_while_descending()
            && *reinterpret_cast<__int16 *>(raw + 320) >= 11) {
            set_action(10);
            zero_velocity_acceleration();
            *reinterpret_cast<float *>(raw + 240) = alice_stage_surface_height_at_x(this);
            return true;
        }
        if (advance_frame_and_dispatch())
            set_action(9);
        if (!*reinterpret_cast<_WORD *>(raw + 322) && *reinterpret_cast<_WORD *>(raw + 320) == 3) {
            dispatch_indexed_event_member(0x1Du);
            spawn_payload[0] = 0.0f;
            spawn_payload[1] = 0.0f;
            spawn_payload[2] = 16.0f;
            facing = *reinterpret_cast<unsigned char *>(raw + 260);
            spawn_owned_object_via_manager(
                849,
                *reinterpret_cast<float *>(raw + 236) + static_cast<float>(50 * static_cast<signed char>(facing)),
                static_cast<float>(*reinterpret_cast<float *>(raw + 240) + 140.0),
                facing,
                1,
                reinterpret_cast<int>(spawn_payload),
                3);
        }
        return true;
    }

    case 308: {
        float spawn_payload[3];
        int facing;
        int i;

        *reinterpret_cast<float *>(raw + 248) =
            *reinterpret_cast<float *>(raw + 248) - *reinterpret_cast<float *>(raw + 256);
        if (has_crossed_stage_surface_while_descending()) {
            set_action(10);
            *reinterpret_cast<float *>(raw + 240) = alice_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return true;
        }
        if (advance_frame_and_dispatch())
            set_action(9);
        if (!*reinterpret_cast<_DWORD *>(raw + 324)
            && !*reinterpret_cast<_WORD *>(raw + 322)
            && !*reinterpret_cast<_WORD *>(raw + 320)
            && *reinterpret_cast<_WORD *>(raw + 318) == 1)
            dispatch_indexed_event_member(0x1Du);
        if (!*reinterpret_cast<_WORD *>(raw + 318)) {
            if (!*reinterpret_cast<_WORD *>(raw + 322) && *reinterpret_cast<_WORD *>(raw + 320) == 4) {
                facing = *reinterpret_cast<unsigned char *>(raw + 260);
                for (i = 0; i < 6; ++i) {
                    spawn_payload[0] = static_cast<float>(-static_cast<double>(i) * 60.0);
                    spawn_payload[1] = 13.0f;
                    spawn_payload[2] = 17.0f;
                    spawn_owned_object_via_manager(
                        849,
                        *reinterpret_cast<float *>(raw + 236) + static_cast<float>(25 * static_cast<signed char>(facing)),
                        static_cast<float>(*reinterpret_cast<float *>(raw + 240) + 95.0),
                        facing,
                        1,
                        reinterpret_cast<int>(spawn_payload),
                        3);
                    ++*reinterpret_cast<_WORD *>(raw + 1842);
                }
            }
            if (!*reinterpret_cast<_WORD *>(raw + 322) && *reinterpret_cast<_WORD *>(raw + 320) == 5) {
                *reinterpret_cast<float *>(raw + 244) = -4.0f;
                *reinterpret_cast<float *>(raw + 248) = 8.0f;
            }
        }
        if (!*reinterpret_cast<_WORD *>(raw + 322) && *reinterpret_cast<_WORD *>(raw + 318) == 1)
            *reinterpret_cast<_DWORD *>(raw + 384) = 0;
        return true;
    }

    case 309: {
        float spawn_payload[3];
        int facing;
        int i;

        *reinterpret_cast<float *>(raw + 248) =
            *reinterpret_cast<float *>(raw + 248) - *reinterpret_cast<float *>(raw + 256);
        if (has_crossed_stage_surface_while_descending()) {
            set_action(10);
            *reinterpret_cast<float *>(raw + 240) = alice_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return true;
        }
        if (advance_frame_and_dispatch())
            set_action(9);
        if (!*reinterpret_cast<_DWORD *>(raw + 324)
            && !*reinterpret_cast<_WORD *>(raw + 322)
            && !*reinterpret_cast<_WORD *>(raw + 320)
            && *reinterpret_cast<_WORD *>(raw + 318) == 1)
            dispatch_indexed_event_member(0x1Du);
        if (!*reinterpret_cast<_WORD *>(raw + 318)
            && !*reinterpret_cast<_WORD *>(raw + 322)
            && *reinterpret_cast<_WORD *>(raw + 320) == 3) {
            facing = *reinterpret_cast<unsigned char *>(raw + 260);
            for (i = 0; i < 6; ++i) {
                spawn_payload[0] = static_cast<float>(-static_cast<double>(i) * 60.0);
                spawn_payload[1] = 13.0f;
                spawn_payload[2] = 24.0f;
                spawn_owned_object_via_manager(
                    849,
                    *reinterpret_cast<float *>(raw + 236) + static_cast<float>(30 * static_cast<signed char>(facing)),
                    static_cast<float>(*reinterpret_cast<float *>(raw + 240) + 120.0),
                    facing,
                    1,
                    reinterpret_cast<int>(spawn_payload),
                    3);
                ++*reinterpret_cast<_WORD *>(raw + 1842);
            }
        }
        if (*reinterpret_cast<_WORD *>(raw + 318) == 2
            && !*reinterpret_cast<_WORD *>(raw + 322)
            && *reinterpret_cast<_WORD *>(raw + 320) == 4)
            *reinterpret_cast<float *>(raw + 256) = 0.5f;
        if (!*reinterpret_cast<_WORD *>(raw + 322) && *reinterpret_cast<_WORD *>(raw + 318) == 1)
            *reinterpret_cast<_DWORD *>(raw + 384) = 0;
        return true;
    }

    case 310: {
        double next_y;

        if (*reinterpret_cast<_DWORD *>(raw + 384)) {
            if (static_cast<__int16>(++*reinterpret_cast<_WORD *>(raw + 1840)) > 5) {
                *reinterpret_cast<_DWORD *>(raw + 384) = 0;
                *reinterpret_cast<_WORD *>(raw + 1840) = 0;
            }
        }
        if (*reinterpret_cast<_WORD *>(raw + 318) == 1) {
            if (!*reinterpret_cast<_DWORD *>(raw + 324))
                *reinterpret_cast<float *>(raw + 244) = 15.0f;
            if (!(*reinterpret_cast<int *>(raw + 324) % 8))
                dispatch_indexed_event_member(0x1Bu);
            if (*reinterpret_cast<_DWORD *>(raw + 384)) {
                if (static_cast<__int16>(++*reinterpret_cast<_WORD *>(raw + 1840)) > 5) {
                    *reinterpret_cast<_DWORD *>(raw + 384) = 0;
                    *reinterpret_cast<_WORD *>(raw + 1840) = 0;
                }
            }
            if (*reinterpret_cast<int *>(raw + 324) > 30) {
                slot_14();
                *reinterpret_cast<float *>(raw + 248) = 6.0f;
                *reinterpret_cast<float *>(raw + 244) =
                    static_cast<float>(*reinterpret_cast<float *>(raw + 244) * 0.5);
            }
        }
        if (*reinterpret_cast<_WORD *>(raw + 318) == 2) {
            adjusted = *reinterpret_cast<float *>(raw + 248) - *reinterpret_cast<float *>(raw + 256);
            *reinterpret_cast<float *>(raw + 248) = adjusted;
            next_y = static_cast<double>(adjusted) + *reinterpret_cast<float *>(raw + 240);
            if (alice_stage_surface_height_at_x(this) >= next_y) {
                *reinterpret_cast<float *>(raw + 248) = 0.0f;
                *reinterpret_cast<float *>(raw + 240) = alice_stage_surface_height_at_x(this);
                set_action(9);
                return true;
            }
        }
        if (advance_frame_and_dispatch()) {
            set_action(9);
            return true;
        }
        return true;
    }

    case 320:
        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(0))
            return true;
        if (*reinterpret_cast<__int16 *>(raw + 320) > 1) {
            adjusted = static_cast<float>(*reinterpret_cast<float *>(raw + 244) - 2.0);
            *reinterpret_cast<float *>(raw + 244) = adjusted;
            if (adjusted < 0.0f)
                *reinterpret_cast<float *>(raw + 244) = 0.0f;
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (!*reinterpret_cast<_WORD *>(raw + 322) && *reinterpret_cast<_WORD *>(raw + 320) == 2) {
            dispatch_indexed_event_member(0x1Cu);
            *reinterpret_cast<_BYTE *>(raw + 1150) = 0;
        }
        return true;

    case 321:
        resolve_stage_surface_landing_transition();
        if (!try_dispatch_directional_action_208_210(1)) {
            if (*reinterpret_cast<__int16 *>(raw + 320) > 3) {
                adjusted = static_cast<float>(*reinterpret_cast<float *>(raw + 244) - 0.5);
                *reinterpret_cast<float *>(raw + 244) = adjusted;
                if (adjusted < 0.0f)
                    *reinterpret_cast<float *>(raw + 244) = 0.0f;
            }
            if (advance_frame_and_dispatch())
                set_action(0);
            if (!*reinterpret_cast<_WORD *>(raw + 322) && *reinterpret_cast<_WORD *>(raw + 320) == 3) {
                dispatch_indexed_event_member(0x1Cu);
                *reinterpret_cast<float *>(raw + 244) = 7.5f;
                *reinterpret_cast<_BYTE *>(raw + 1150) = 0;
            }
        }
        return true;


    case 322: {
        int facing;

        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(1))
            return true;
        adjusted = static_cast<float>(*reinterpret_cast<float *>(raw + 244) - 1.5);
        *reinterpret_cast<float *>(raw + 244) = adjusted;
        if (adjusted < 0.0f)
            *reinterpret_cast<float *>(raw + 244) = 0.0f;
        if (!*reinterpret_cast<_DWORD *>(raw + 1724))
            *reinterpret_cast<_BYTE *>(raw + 1872) = 0;
        if (advance_frame_and_dispatch())
            set_action(0);
        if (!*reinterpret_cast<_DWORD *>(raw + 324)
            && !*reinterpret_cast<_WORD *>(raw + 322)
            && !*reinterpret_cast<_WORD *>(raw + 320)
            && *reinterpret_cast<_WORD *>(raw + 318) == 1) {
            set_action(0);
            return true;
        }
        if (!*reinterpret_cast<_WORD *>(raw + 318)) {
            if (!*reinterpret_cast<_WORD *>(raw + 322) && *reinterpret_cast<_WORD *>(raw + 320) == 7) {
                if (*reinterpret_cast<_BYTE *>(raw + 1872) == 1) {
                    slot_14();
                    facing = *reinterpret_cast<unsigned char *>(raw + 260);
                    emit_fighter_effect_433cc0(
                        62,
                        *reinterpret_cast<float *>(raw + 236) - static_cast<float>(33 * static_cast<signed char>(facing)),
                        static_cast<float>(*reinterpret_cast<float *>(raw + 240) + 112.0),
                        facing,
                        -1);
                    return true;
                }
                *reinterpret_cast<float *>(raw + 244) = 15.0f;
            }
            if (!*reinterpret_cast<_WORD *>(raw + 322) && *reinterpret_cast<_WORD *>(raw + 320) == 9) {
                dispatch_indexed_event_member(0x1Du);
                *reinterpret_cast<_BYTE *>(raw + 1150) = 0;
            }
        }
        if (*reinterpret_cast<_WORD *>(raw + 318) == 1) {
            if (!*reinterpret_cast<_WORD *>(raw + 322) && *reinterpret_cast<_WORD *>(raw + 320) == 11)
                *reinterpret_cast<float *>(raw + 244) = 19.0f;
            if (!*reinterpret_cast<_WORD *>(raw + 322) && *reinterpret_cast<_WORD *>(raw + 320) == 12)
                dispatch_indexed_event_member(0x1Du);
        }
        return true;
    }


    case 408: {
        float spawn_payload[3];
        int facing;

        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(1))
            return true;
        adjusted = static_cast<float>(*reinterpret_cast<float *>(raw + 244) - 0.25);
        *reinterpret_cast<float *>(raw + 244) = adjusted;
        if (adjusted < 0.0f) {
            *reinterpret_cast<float *>(raw + 244) = 0.0f;
            *reinterpret_cast<_BYTE *>(raw + 1150) = 0;
        }
        if (advance_frame_and_dispatch())
            set_action(0);
        if (!*reinterpret_cast<_WORD *>(raw + 322) && *reinterpret_cast<_WORD *>(raw + 320) == 2) {
            spawn_payload[0] = 0.0f;
            spawn_payload[1] = 0.0f;
            spawn_payload[2] = 19.0f;
            facing = *reinterpret_cast<unsigned char *>(raw + 260);
            spawn_owned_object_via_manager(
                849,
                *reinterpret_cast<float *>(raw + 236) + static_cast<float>(30 * static_cast<signed char>(facing)),
                static_cast<float>(*reinterpret_cast<float *>(raw + 240) + 100.0),
                facing,
                1,
                reinterpret_cast<int>(spawn_payload),
                3);
        }
        return true;
    }

    case 409:
        *reinterpret_cast<float *>(raw + 248) =
            *reinterpret_cast<float *>(raw + 248) - *reinterpret_cast<float *>(raw + 256);
        if (has_crossed_stage_surface_while_descending()) {
            set_action(10);
            zero_velocity_acceleration();
            *reinterpret_cast<float *>(raw + 240) = alice_stage_surface_height_at_x(this);
            return true;
        }
        if (!advance_frame_and_dispatch())
            return true;
        set_action(9);
        return true;


    case 411: {
        float spawn_payload[3];
        int facing;

        resolve_stage_surface_landing_transition();
        if (!*reinterpret_cast<_DWORD *>(raw + 1732))
            *reinterpret_cast<_BYTE *>(raw + 1872) = 0;
        if (advance_frame_and_dispatch())
            set_action(0);
        if (!*reinterpret_cast<_WORD *>(raw + 318)
            && !*reinterpret_cast<_WORD *>(raw + 322)
            && *reinterpret_cast<_WORD *>(raw + 320) == 3) {
            spawn_payload[0] = 0.0f;
            spawn_payload[1] = 40.0f;
            spawn_payload[2] = 0.0f;
            facing = *reinterpret_cast<unsigned char *>(raw + 260);
            spawn_owned_object_via_manager(
                805,
                *reinterpret_cast<float *>(raw + 236) + static_cast<float>(5 * static_cast<signed char>(facing)),
                static_cast<float>(*reinterpret_cast<float *>(raw + 240) + 108.0),
                facing,
                1,
                reinterpret_cast<int>(spawn_payload),
                3);
            dispatch_character_wave_handle(2);
            *reinterpret_cast<_DWORD *>(raw + 384) = 1;
            adjust_counter_482(200, 60);
            add_phase_scaled_counter_558(30);
            return true;
        }
        if (!*reinterpret_cast<_DWORD *>(raw + 324)
            && !*reinterpret_cast<_WORD *>(raw + 322)
            && !*reinterpret_cast<_WORD *>(raw + 320)
            && *reinterpret_cast<_WORD *>(raw + 318) == 1) {
            if (!*reinterpret_cast<_BYTE *>(raw + 1872)) {
                set_action(0);
                return true;
            }
            facing = *reinterpret_cast<unsigned char *>(raw + 260);
            emit_fighter_effect_433cc0(
                62,
                *reinterpret_cast<float *>(raw + 236) - static_cast<float>(66 * static_cast<signed char>(facing)),
                static_cast<float>(*reinterpret_cast<float *>(raw + 240) + 148.0),
                facing,
                1);
            return true;
        }
        return true;
    }

    case 412: {
        float spawn_payload[3];
        int facing;

        resolve_stage_surface_landing_transition();
        if (!*reinterpret_cast<_DWORD *>(raw + 1732))
            *reinterpret_cast<_BYTE *>(raw + 1872) = 0;
        if (!*reinterpret_cast<_WORD *>(raw + 318)
            && !*reinterpret_cast<_WORD *>(raw + 322)
            && *reinterpret_cast<_WORD *>(raw + 320) == 10)
            *reinterpret_cast<float *>(raw + 244) = 0.0f;
        if (advance_frame_and_dispatch())
            set_action(0);
        if (!*reinterpret_cast<_WORD *>(raw + 318) && !*reinterpret_cast<_WORD *>(raw + 322)) {
            if (*reinterpret_cast<_WORD *>(raw + 320) == 9) {
                spawn_payload[0] = -80.0f;
                spawn_payload[1] = 40.0f;
                spawn_payload[2] = 0.0f;
                facing = *reinterpret_cast<unsigned char *>(raw + 260);
                spawn_owned_object_via_manager(
                    805,
                    *reinterpret_cast<float *>(raw + 236) + static_cast<float>(5 * static_cast<signed char>(facing)),
                    static_cast<float>(*reinterpret_cast<float *>(raw + 240) + 108.0),
                    facing,
                    1,
                    reinterpret_cast<int>(spawn_payload),
                    3);
                dispatch_character_wave_handle(2);
                *reinterpret_cast<_DWORD *>(raw + 384) = 1;
                adjust_counter_482(200, 60);
                add_phase_scaled_counter_558(30);
                return true;
            }
            if (*reinterpret_cast<_WORD *>(raw + 320) == 10)
                *reinterpret_cast<float *>(raw + 244) = 34.0f;
        }
        if (!*reinterpret_cast<_DWORD *>(raw + 324)
            && !*reinterpret_cast<_WORD *>(raw + 322)
            && !*reinterpret_cast<_WORD *>(raw + 320)
            && *reinterpret_cast<_WORD *>(raw + 318) == 1) {
            if (!*reinterpret_cast<_BYTE *>(raw + 1872)) {
                set_action(0);
                return true;
            }
            facing = *reinterpret_cast<unsigned char *>(raw + 260);
            emit_fighter_effect_433cc0(
                62,
                *reinterpret_cast<float *>(raw + 236) - static_cast<float>(66 * static_cast<signed char>(facing)),
                static_cast<float>(*reinterpret_cast<float *>(raw + 240) + 148.0),
                facing,
                1);
            return true;
        }
        return true;
    }

    case 695: {
        float effect_y0;
        float effect_y1;
        float effect_y2;
        float effect_y3;
        int facing;

        resolve_stage_surface_landing_transition();
        if (advance_frame_and_dispatch())
            set_action(0);
        if (!*reinterpret_cast<_WORD *>(raw + 318)
            && !*reinterpret_cast<_WORD *>(raw + 322)
            && *reinterpret_cast<_WORD *>(raw + 320) == 7) {
            dispatch_indexed_event_member(0x37u);
            facing = *reinterpret_cast<unsigned char *>(raw + 260);
            effect_y0 = *reinterpret_cast<float *>(raw + 240) + 100.0f;
            emit_fighter_effect_433cc0(140, *reinterpret_cast<float *>(raw + 236), effect_y0, facing, 1);
            effect_y1 = *reinterpret_cast<float *>(raw + 240) + 100.0f;
            emit_fighter_effect_433cc0(140, *reinterpret_cast<float *>(raw + 236), effect_y1, facing, 1);
            effect_y2 = *reinterpret_cast<float *>(raw + 240) + 100.0f;
            emit_fighter_effect_433cc0(140, *reinterpret_cast<float *>(raw + 236), effect_y2, facing, 1);
            effect_y3 = *reinterpret_cast<float *>(raw + 240) + 100.0f;
            emit_fighter_effect_433cc0(141, *reinterpret_cast<float *>(raw + 236), effect_y3, facing, -1);
            emit_fighter_effect_433cc0(142,
                *reinterpret_cast<float *>(raw + 236),
                *reinterpret_cast<float *>(raw + 240),
                facing,
                -1);
        }
        return true;
    }

    case 696:
        resolve_stage_surface_landing_transition();
        adjusted = static_cast<float>(*reinterpret_cast<float *>(raw + 244) - 1.5);
        *reinterpret_cast<float *>(raw + 244) = adjusted;
        if (adjusted < 0.0f)
            *reinterpret_cast<float *>(raw + 244) = 0.0f;
        if (advance_frame_and_dispatch())
            set_action(0);
        if (*reinterpret_cast<_WORD *>(raw + 318))
            return true;
        if (!*reinterpret_cast<_WORD *>(raw + 322) && *reinterpret_cast<_WORD *>(raw + 320) == 8)
            *reinterpret_cast<float *>(raw + 244) = 15.0f;
        if (!*reinterpret_cast<_WORD *>(raw + 322) && *reinterpret_cast<_WORD *>(raw + 320) == 9) {
            dispatch_indexed_event_member(0x1Du);
            *reinterpret_cast<_BYTE *>(raw + 1150) = 0;
        }
        return true;

    default:
        return false;
    }
}

} // namespace th105
