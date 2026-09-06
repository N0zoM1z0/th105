#include <stddef.h>

namespace th105 {

// Partial semantic reconstruction for Alice's primary-vtable +0x28 giant.
//
// This is deliberately NOT the target vslot28 root and is not referenced by
// config/functions.csv or a match unit.  It records only action cases whose
// current TH105 1.06a control/data flow has been checked against both the Alice
// PE and the source-present Youmu shared family.  Unknown actions return false.
// Keep this as a staging surface until the complete 42,721-byte root is
// recovered; never promote this helper as authored exact/source-present credit.

typedef unsigned char _BYTE;
typedef unsigned short _WORD;
typedef unsigned int _DWORD;

class AliceActionStateLowScaffoldView;
float __fastcall alice_stage_surface_height_at_x(AliceActionStateLowScaffoldView *fighter);

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
    void emit_fighter_effect_433cc0(int effect_id, float x, float y, int facing, int arg5);
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
