// Complete JP1.06a Alice Fighter update hypothesis; source selection and exactness remain open.
// See docs/ALICE_FIGHTER_UPDATE_2026_10_25.md.
#include "AliceFighterActionState.hpp"
namespace th105 {
#define AT(p,t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(p)+(o)))
#define F(o) AT(this,float,o)
#define S(o) AT(this,short,o)
#define U(o) AT(this,unsigned short,o)
#define I(o) AT(this,int,o)
#define W(o) AT(this,unsigned,o)
#define B(o) AT(this,unsigned char,o)
#define C(o) AT(this,signed char,o)
#define D(x) static_cast<double>(x)
#define RESOLVE() resolve_stage_surface_landing_transition()
#define FRAME() advance_frame_and_dispatch()
#define ZERO() zero_velocity_acceleration()
#define CROSSED() static_cast<unsigned char>(has_crossed_stage_surface_while_descending())
#define GROUND() alice_stage_surface_height_at_x(this)
#define ACTION(x) set_action_and_finalize(x)
#define SEQUENCE(x) select_sequence(x)
#define BLOCK() next_sequence_block()
#define GATE(x) try_dispatch_directional_action_208_210(x)
#define EVENT(x) dispatch_indexed_event_member(x)
#define WAVE(x) dispatch_character_wave_handle(x)
#define ADJUST(x,y) adjust_counter_482(x,y)
#define SCALE(x) add_phase_scaled_counter_558(x)
#define EFFECT(n,x,y,d,z) emit_fighter_effect_433cc0(n,x,y,d,z)
#define SPAWN(n,x,y,d,z,p,c) spawn_owned_object_via_manager(n,x,y,d,z,p,c)
void AliceFighterActionStateView::dispatch_action_state()
{
 unsigned char *raw=reinterpret_cast<unsigned char *>(this);
 float adjusted,zero;
 S(0x7A0)=0; S(0x7A2)=100;
 ++S(0x7AC); if(S(0x7AC)>=360) S(0x7AC)=0;
 if(S(0x174)<=0) I(0x7A4)=0;
 if(S(0x13C)>149 && S(0x13C)<159 && B(0x751)==0) {
  B(0x751)=1;
  if(S(0x13C)>149 && S(0x13C)<154)
   SPAWN(998,static_cast<float>(60*C(0x104)+F(0xEC)),static_cast<float>(F(0xF0)+110.0),B(0x104),1,0,0);
  if(S(0x13C)>153 && S(0x13C)<158)
   SPAWN(998,static_cast<float>(60*C(0x104)+F(0xEC)),static_cast<float>(F(0xF0)+60.0),B(0x104),1,0,0);
  if(S(0x13C)==158)
   SPAWN(998,static_cast<float>(60*C(0x104)+F(0xEC)),static_cast<float>(F(0xF0)+100.0),B(0x104),1,0,0);
 }
 if(S(0x186)!=0) return;
 if(AT(AT(this,void *,0x170),short,0x48C)!=0) return;
 switch(S(0x13C)) {
    case 0:
        resolve_stage_surface_landing_transition();
        if (!F(0xf4))
            B(0x47e) = 0;
        if (!B(0x47e)) {
            zero_velocity_acceleration();
            advance_frame_and_dispatch();
            return;
        }
        if (F(0xf4) > 0.0f) {
            adjusted = F(0xf4) - 0.5f;
            F(0xf4) = adjusted;
            if (adjusted < 0.0f) {
                zero_velocity_acceleration();
                B(0x47e) = 0;
            }
        }
        if (F(0xf4) < 0.0f) {
            adjusted = F(0xf4) + 0.5f;
            F(0xf4) = adjusted;
            if (adjusted > 0.0f) {
                zero_velocity_acceleration();
                B(0x47e) = 0;
            }
        }
        advance_frame_and_dispatch();
        return;

    case 1:
        resolve_stage_surface_landing_transition();
        if (B(0x47e)) {
            zero = 0.0f;
            if (F(0xf4) > zero) {
                adjusted = F(0xf4) - 0.5f;
                F(0xf4) = adjusted;
                if (adjusted < zero) {
                    zero_velocity_acceleration();
                    B(0x47e) = 0;
                }
            }
            if (zero > F(0xf4)) {
                adjusted = F(0xf4) + 0.5f;
                F(0xf4) = adjusted;
                if (adjusted > zero) {
                    zero_velocity_acceleration();
                    B(0x47e) = 0;
                }
            }
        } else {
            zero_velocity_acceleration();
        }
        if (advance_frame_and_dispatch() && !U(0x140))
            set_action_and_finalize(2);
        return;

    case 2:
        resolve_stage_surface_landing_transition();
        if (!B(0x47e)) {
            zero_velocity_acceleration();
            advance_frame_and_dispatch();
            return;
        }
        if (F(0xf4) > 0.0f) {
            adjusted = F(0xf4) - 0.5f;
            F(0xf4) = adjusted;
            if (adjusted < 0.0f) {
                zero_velocity_acceleration();
                B(0x47e) = 0;
            }
        }
        if (F(0xf4) < 0.0f) {
            adjusted = F(0xf4) + 0.5f;
            F(0xf4) = adjusted;
            if (adjusted > 0.0f) {
                zero_velocity_acceleration();
                B(0x47e) = 0;
            }
        }
        advance_frame_and_dispatch();
        return;

    case 3:
        resolve_stage_surface_landing_transition();
        if (B(0x47e)) {
            zero = 0.0f;
            if (F(0xf4) > zero) {
                adjusted = F(0xf4) - 0.5f;
                F(0xf4) = adjusted;
                if (adjusted < zero) {
                    zero_velocity_acceleration();
                    B(0x47e) = 0;
                }
            }
            if (zero > F(0xf4)) {
                adjusted = F(0xf4) + 0.5f;
                F(0xf4) = adjusted;
                if (adjusted > zero) {
                    zero_velocity_acceleration();
                    B(0x47e) = 0;
                }
            }
        } else {
            zero_velocity_acceleration();
        }
        if (!advance_frame_and_dispatch())
            return;
        if (U(0x140))
            return;
        set_action_and_finalize(0);
        return;

    case 4:
        resolve_stage_surface_landing_transition();
        F(0xf4) = 6.0f;
        advance_frame_and_dispatch();
        return;

    case 5:
        resolve_stage_surface_landing_transition();
        F(0xf4) = -6.0f;
        advance_frame_and_dispatch();
        return;

    case 6:
        if (!U(0x13e)) {
            resolve_stage_surface_landing_transition();
            if (!U(0x13e) && !B(0x47e))
                zero_velocity_acceleration();
        }
        if (*reinterpret_cast<__int16 *>(raw + 318) > 0) {
            F(0xf8) =
                F(0xf8) - F(0x100);
            if (has_crossed_stage_surface_while_descending()) {
                set_action_and_finalize(10);
                F(0xf0) = alice_stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                return;
            }
        }
        advance_frame_and_dispatch();
        if (W(0x144)
            || U(0x142)
            || U(0x140)
            || U(0x13e) != 1)
            return;
        F(0xf4) = 0.0f;
        F(0xf8) = 15.0f;
        F(0x100) = 0.65f;
        B(0x47e) = 0;
        return;

    case 7:
        if (!U(0x13e)) {
            resolve_stage_surface_landing_transition();
            if (!U(0x13e) && !B(0x47e))
                zero_velocity_acceleration();
        }
        if (*reinterpret_cast<__int16 *>(raw + 318) > 0) {
            F(0xf8) =
                F(0xf8) - F(0x100);
            if (has_crossed_stage_surface_while_descending()) {
                set_action_and_finalize(10);
                F(0xf0) = alice_stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                return;
            }
        }
        advance_frame_and_dispatch();
        if (W(0x144)
            || U(0x142)
            || U(0x140)
            || U(0x13e) != 1)
            return;
        F(0xf4) = 5.0f;
        F(0xf8) = 15.0f;
        F(0x100) = 0.65f;
        B(0x47e) = 0;
        return;

    case 8:
        if (!U(0x13e)) {
            resolve_stage_surface_landing_transition();
            if (!U(0x13e) && !B(0x47e))
                zero_velocity_acceleration();
        }
        if (*reinterpret_cast<__int16 *>(raw + 318) > 0) {
            F(0xf8) =
                F(0xf8) - F(0x100);
            if (has_crossed_stage_surface_while_descending()) {
                set_action_and_finalize(10);
                F(0xf0) = alice_stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                return;
            }
        }
        advance_frame_and_dispatch();
        if (W(0x144)
            || U(0x142)
            || U(0x140)
            || U(0x13e) != 1)
            return;
        F(0xf4) = -5.0f;
        F(0xf8) = 15.0f;
        F(0x100) = 0.65f;
        B(0x47e) = 0;
        return;


    case 9:
        if (!F(0x100))
            F(0x100) = 0.6000000238418579f;
        F(0xf8) =
            F(0xf8) - F(0x100);
        if (has_crossed_stage_surface_while_descending()) {
            set_action_and_finalize(10);
            F(0xf0) = alice_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        advance_frame_and_dispatch();
        return;

    case 10:
        resolve_stage_surface_landing_transition();
        zero_velocity_acceleration();
        if (advance_frame_and_dispatch()) {
            if (W(0x6b8))
                set_action_and_finalize(2);
            else
                set_action_and_finalize(0);
        }
        return;


    case 197: {
        unsigned char *peer;

        resolve_stage_surface_landing_transition();
        if (advance_frame_and_dispatch()) {
            if (B(0x72c) == 2) {
                set_action_and_finalize(700);
                U(0x4a8) = 3;
                U(0x4ac) = 3;
                return;
            }
            set_action_and_finalize(0);
            if (I(0x6b8) > 0)
                set_action_and_finalize(1);
        }
        if (!U(0x142) && U(0x140) == 8)
            zero_velocity_acceleration();
        if (!U(0x142) && U(0x140) == 13) {
            peer = reinterpret_cast<unsigned char *>(W(0x170));
            if (*reinterpret_cast<float *>(peer + 236) < F(0xec))
                C(0x104) = -1;
            if (*reinterpret_cast<float *>(peer + 236) > F(0xec))
                C(0x104) = 1;
        }
        return;
    }

    case 198: {
        unsigned char *peer;

        resolve_stage_surface_landing_transition();
        if (advance_frame_and_dispatch()) {
            if (B(0x72c) == 2) {
                set_action_and_finalize(700);
                U(0x4a8) = 3;
                U(0x4ac) = 3;
                return;
            }
            set_action_and_finalize(0);
            if (I(0x6b8) > 0)
                set_action_and_finalize(1);
        }
        if (!U(0x142) && U(0x140) == 8)
            zero_velocity_acceleration();
        if (!U(0x142) && U(0x140) == 13) {
            peer = reinterpret_cast<unsigned char *>(W(0x170));
            if (*reinterpret_cast<float *>(peer + 236) < F(0xec))
                C(0x104) = -1;
            if (*reinterpret_cast<float *>(peer + 236) > F(0xec))
                C(0x104) = 1;
        }
        return;
    }

    case 199: {
        unsigned char *peer;

        resolve_stage_surface_landing_transition();
        if (advance_frame_and_dispatch()) {
            if (B(0x72c) == 2) {
                set_action_and_finalize(700);
                U(0x4a8) = 3;
                U(0x4ac) = 3;
                return;
            }
            set_action_and_finalize(0);
            if (I(0x6b8) > 0)
                set_action_and_finalize(1);
        }
        if (!U(0x142) && U(0x140) == 5) {
            peer = reinterpret_cast<unsigned char *>(W(0x170));
            if (*reinterpret_cast<float *>(peer + 236) < F(0xec))
                C(0x104) = -1;
            if (*reinterpret_cast<float *>(peer + 236) > F(0xec))
                C(0x104) = 1;
        }
        return;
    }

    case 200: {
        int facing;
        int input_product;
        short counter;

        resolve_stage_surface_landing_transition();
        B(0x47e) = 1;
        if (F(0xf4) > 9.0f) {
            adjusted = static_cast<float>(F(0xf4) - 0.5);
            F(0xf4) = adjusted;
            if (adjusted < 9.0f)
                F(0xf4) = 9.0f;
        }
        advance_frame_and_dispatch();
        if (U(0x13e) == 1) {
            if (!(I(0x144) % 5)) {
                facing = B(0x104);
                emit_fighter_effect_433cc0(
                    124,
                    static_cast<float>((F(0xec) + 50.0)
                        - static_cast<float>(mt19937_next_u32() % 100)),
                    static_cast<float>(static_cast<float>(mt19937_next_u32() % 200)
                        + F(0xf0)),
                    facing,
                    1);
            }
            if (I(0x6b8) < 0) {
                input_product = static_cast<signed char>(B(0x104))
                    * I(0x6b4);
                if (input_product > 0)
                    set_action_and_finalize(212);
                else
                    set_action_and_finalize(211);
                return;
            }
            counter = static_cast<short>(++U(0x730));
            input_product = static_cast<signed char>(B(0x104))
                * I(0x6b4);
            if ((input_product > 0 && counter > 45) || (input_product <= 0 && counter > 5)) {
                set_action_and_finalize(204);
                return;
            }
        }
        if (!U(0x13e)
            && !U(0x142)
            && U(0x140) == 2) {
            F(0xf4) = 10.0f;
            facing = B(0x104);
            emit_fighter_effect_433cc0(
                125,
                F(0xec) + static_cast<float>(80 * static_cast<signed char>(facing)),
                static_cast<float>(F(0xf0) + 80.0),
                facing,
                1);
            emit_fighter_effect_433cc0(
                126,
                F(0xec),
                static_cast<float>(F(0xf0) + 80.0),
                facing,
                1);
            dispatch_indexed_event_member(0x1Fu);
        }
        return;
    }

    case 201: {
        int opposite_facing;

        if (!U(0x13e)
            && static_cast<__int16>(U(0x140)) <= 1)
            resolve_stage_surface_landing_transition();
        if (U(0x13e) == 3) {
            resolve_stage_surface_landing_transition();
            adjusted = static_cast<float>(F(0xf4) + 2.0);
            F(0xf4) = adjusted;
            if (adjusted > 0.0f)
                F(0xf4) = 0.0f;
        }
        if (!is_y_at_or_below_stage_surface(this) && !(I(0x144) % 5)) {
            opposite_facing = static_cast<unsigned char>(-C(0x104));
            emit_fighter_effect_433cc0(
                124,
                static_cast<float>((F(0xec) + 50.0)
                    - static_cast<float>(mt19937_next_u32() % 100)),
                static_cast<float>(static_cast<float>(mt19937_next_u32() % 200)
                    + F(0xf0)),
                opposite_facing,
                1);
        }
        if (static_cast<__int16>(U(0x13e)) < 3) {
            F(0xf8) =
                F(0xf8) - F(0x100);
            if (has_crossed_stage_surface_while_descending()) {
                F(0xf8) = 0.0f;
                F(0xf0) = alice_stage_surface_height_at_x(this);
                select_sequence(3);
                return;
            }
        }
        if (advance_frame_and_dispatch()) {
            set_action_and_finalize(0);
            F(0xf4) = 0.0f;
            return;
        }
        if (!U(0x13e)
            && !U(0x142)
            && U(0x140) == 2) {
            F(0xf4) = -10.0f;
            F(0xf8) = 4.5f;
            F(0x100) = 0.6000000238418579f;
            opposite_facing = static_cast<unsigned char>(-C(0x104));
            emit_fighter_effect_433cc0(
                125,
                F(0xec),
                static_cast<float>(F(0xf0) + 80.0),
                opposite_facing,
                1);
            emit_fighter_effect_433cc0(
                126,
                F(0xec),
                static_cast<float>(F(0xf0) + 80.0),
                opposite_facing,
                1);
            dispatch_indexed_event_member(0x1Fu);
        }
        return;
    }

    case 202: {
        int facing;

        F(0xf8) =
            F(0xf8) - F(0x100);
        if (has_crossed_stage_surface_while_descending()) {
            zero_velocity_acceleration();
            F(0xf0) = alice_stage_surface_height_at_x(this);
            set_action_and_finalize(10);
            return;
        }
        if ((U(0x13e) == 1 || U(0x13e) == 2)
            && !(I(0x144) % 5)) {
            facing = B(0x104);
            emit_fighter_effect_433cc0(
                124,
                static_cast<float>((F(0xec) + 50.0)
                    - static_cast<float>(mt19937_next_u32() % 100)),
                static_cast<float>(static_cast<float>(mt19937_next_u32() % 200)
                    + F(0xf0)),
                facing,
                1);
        }
        advance_frame_and_dispatch();
        if (!U(0x13e)
            && !U(0x142)
            && U(0x140) == 2) {
            U(0x730) = 0;
            F(0xf4) = 8.5f;
            F(0xf8) = 5.0f;
            F(0x100) = 0.6000000238418579f;
            facing = B(0x104);
            emit_fighter_effect_433cc0(
                125,
                F(0xec) + static_cast<float>(80 * static_cast<signed char>(facing)),
                static_cast<float>(F(0xf0) + 110.0),
                facing,
                1);
            emit_fighter_effect_433cc0(
                126,
                F(0xec),
                static_cast<float>(F(0xf0) + 110.0),
                facing,
                1);
            dispatch_indexed_event_member(0x1Fu);
        }
        if (!I(0x144)
            && !U(0x142)
            && !U(0x140)
            && U(0x13e) == 2)
            face_opponent_and_flip_horizontal_velocity();
        return;
    }

    case 203: {
        int opposite_facing;

        F(0xf8) =
            F(0xf8) - F(0x100);
        if (has_crossed_stage_surface_while_descending()) {
            zero_velocity_acceleration();
            F(0xf0) = alice_stage_surface_height_at_x(this);
            U(0x142) = 0;
            set_action_and_finalize(10);
            return;
        }
        if (static_cast<__int16>(U(0x13e)) < 3
            && !(I(0x144) % 5)) {
            opposite_facing = static_cast<unsigned char>(-C(0x104));
            emit_fighter_effect_433cc0(
                124,
                static_cast<float>((F(0xec) + 50.0)
                    - static_cast<float>(mt19937_next_u32() % 100)),
                static_cast<float>(static_cast<float>(mt19937_next_u32() % 200)
                    + F(0xf0)),
                opposite_facing,
                1);
        }
        advance_frame_and_dispatch();
        if (!U(0x13e)
            && !U(0x142)
            && U(0x140) == 1) {
            F(0xf4) = -8.5f;
            F(0xf8) = 5.0f;
            F(0x100) = 0.6000000238418579f;
            opposite_facing = static_cast<unsigned char>(-C(0x104));
            emit_fighter_effect_433cc0(
                125,
                F(0xec),
                static_cast<float>(F(0xf0) + 120.0),
                opposite_facing,
                1);
            emit_fighter_effect_433cc0(
                126,
                F(0xec),
                static_cast<float>(F(0xf0) + 120.0),
                opposite_facing,
                1);
            dispatch_indexed_event_member(0x1Fu);
        }
        if (!I(0x144)
            && !U(0x142)
            && !U(0x140)
            && U(0x13e) == 2)
            face_opponent_and_flip_horizontal_velocity();
        return;
    }

    case 204:
        resolve_stage_surface_landing_transition();
        adjusted = static_cast<float>(F(0xf4) - 0.5);
        F(0xf4) = adjusted;
        if (adjusted < 0.0f) {
            F(0xf4) = 0.0f;
            B(0x47e) = 0;
        }
        if (advance_frame_and_dispatch()) {
            set_action_and_finalize(0);
            B(0x47e) = 0;
        }
        return;


    case 208:
        if (!U(0x13e))
            resolve_stage_surface_landing_transition();
        if (has_crossed_stage_surface_while_descending()) {
            set_action_and_finalize(10);
            F(0xf0) = alice_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if (is_y_at_or_below_stage_surface(this) || F(0xf8) > 0.0f)
            U(0x4ae) = 2;
        if (static_cast<__int16>(U(0x13e)) > 0) {
            adjusted = F(0xf8) - F(0x100);
            F(0xf8) = adjusted;
            if (adjusted < -20.0f)
                F(0xf8) = -20.0f;
        }
        advance_frame_and_dispatch();
        if (!I(0x144)
            && !U(0x142)
            && !U(0x140)
            && U(0x13e) == 1) {
            F(0xf4) = 0.0f;
            F(0xf8) = 19.0f;
            F(0x100) = 0.65f;
            B(0x47e) = 0;
            emit_fighter_effect_433cc0(
                63,
                F(0xec),
                F(0xf0),
                B(0x104),
                1);
        }
        return;

    case 209:
    case 212:
    case 221:
        if (!U(0x13e))
            resolve_stage_surface_landing_transition();
        if (has_crossed_stage_surface_while_descending()) {
            set_action_and_finalize(10);
            F(0xf0) = alice_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if (is_y_at_or_below_stage_surface(this) || F(0xf8) > 0.0f)
            U(0x4ae) = 2;
        if (static_cast<__int16>(U(0x13e)) > 0) {
            adjusted = F(0xf8) - F(0x100);
            F(0xf8) = adjusted;
            if (adjusted < -20.0f)
                F(0xf8) = -20.0f;
        }
        advance_frame_and_dispatch();
        if (!I(0x144)
            && !U(0x142)
            && !U(0x140)
            && U(0x13e) == 1) {
            F(0xf4) = 9.0f;
            F(0xf8) = 15.0f;
            F(0x100) = 0.65f;
            B(0x47e) = 0;
            emit_fighter_effect_433cc0(
                63,
                F(0xec),
                F(0xf0),
                B(0x104),
                1);
        }
        return;

    case 210:
    case 222:
        if (!U(0x13e))
            resolve_stage_surface_landing_transition();
        if (has_crossed_stage_surface_while_descending()) {
            set_action_and_finalize(10);
            F(0xf0) = alice_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if (is_y_at_or_below_stage_surface(this) || F(0xf8) > 0.0f)
            U(0x4ae) = 2;
        if (static_cast<__int16>(U(0x13e)) > 0) {
            adjusted = F(0xf8) - F(0x100);
            F(0xf8) = adjusted;
            if (adjusted < -20.0f)
                F(0xf8) = -20.0f;
        }
        advance_frame_and_dispatch();
        if (!I(0x144)
            && !U(0x142)
            && !U(0x140)
            && U(0x13e) == 1) {
            F(0xf4) = -9.0f;
            F(0xf8) = 15.0f;
            F(0x100) = 0.65f;
            B(0x47e) = 0;
            emit_fighter_effect_433cc0(
                63,
                F(0xec),
                F(0xf0),
                B(0x104),
                1);
        }
        return;

    case 211:
        if (!U(0x13e))
            resolve_stage_surface_landing_transition();
        if (has_crossed_stage_surface_while_descending()) {
            set_action_and_finalize(10);
            F(0xf0) = alice_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if (is_y_at_or_below_stage_surface(this) || F(0xf8) > 0.0f)
            U(0x4ae) = 2;
        if (static_cast<__int16>(U(0x13e)) > 0) {
            adjusted = F(0xf8) - F(0x100);
            F(0xf8) = adjusted;
            if (adjusted < -20.0f)
                F(0xf8) = -20.0f;
        }
        advance_frame_and_dispatch();
        if (!I(0x144)
            && !U(0x142)
            && !U(0x140)
            && U(0x13e) == 1) {
            F(0xf4) = 2.0f;
            F(0xf8) = 19.0f;
            F(0x100) = 0.65f;
            B(0x47e) = 0;
            emit_fighter_effect_433cc0(
                63,
                F(0xec),
                F(0xf0),
                B(0x104),
                1);
        }
        return;


    case 214: {
        if (FRAME()) { ACTION(9); return; }
        if (I(0x144)==0) {
            if (S(0x142)==0 && S(0x140)==0 && S(0x13E)==1) EVENT(31);
            if (I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==6) { ACTION(9); return; }
        }
        int const vertical=I(0x6B8);
        int const horizontal=I(0x6B4);
        int const input_product=C(0x104)*horizontal;
        if (vertical>0) {
            if (input_product>0) S(0x732)=-45;
            else if (input_product<0) S(0x732)=-135;
            else S(0x732)=-90;
        } else if (vertical<0) {
            if (input_product>0) S(0x732)=45;
            else if (input_product<0) S(0x732)=135;
            else S(0x732)=90;
        } else {
            if (input_product>0) S(0x732)=0;
            else if (input_product<0) S(0x732)=180;
        }
        if (S(0x13E)==5 || S(0x13E)==6) F(0xF8)-=F(0x100);
        if (S(0x13E)>0 && S(0x13E)<5) {
            ++U(0x736);
            S(0x734)=static_cast<short>(S(0x732)-static_cast<int>(F(0x740)));
            if (S(0x734)>180) S(0x734)-=360;
            if (S(0x734)<-180) S(0x734)+=360;
            if (S(0x734)>0) F(0x740)+=W(0x4B8)?0.5:1.5;
            if (S(0x734)<0) F(0x740)-=W(0x4B8)?0.5:1.5;
            F(0xF4)=static_cast<float>(lookup_orientation_cosine_quantized_abs(F(0x740))*F(0x73C));
            F(0xF8)=static_cast<float>(lookup_orientation_sine_quantized_abs(F(0x740))*F(0x73C));
            if (F(0xF0)>680.0f && F(0xF8)>0.0f) F(0xF8)=0;
            F(0x73C)+=D(0.3f); if (F(0x73C)>12.0f) F(0x73C)=12;
            if (W(0x4B8)) ADJUST(10,1); else ADJUST(5,1);
            F(0x12C)=-F(0x740);
            if (F(0xF4)<0.0f) F(0x12C)=static_cast<float>(180.0-F(0x740));
            if (F(0xF4)<0.0f && S(0x13E)==1) SEQUENCE(3);
            if (F(0xF4)>=0.0f && S(0x13E)==3) SEQUENCE(1);
            if (F(0xF4)<0.0f && S(0x13E)==2) SEQUENCE(4);
            if (F(0xF4)>=0.0f && S(0x13E)==4) SEQUENCE(2);
            if (I(0x144)%5==1) {
                int const facing=B(0x104);
                EFFECT(125,static_cast<float>(lookup_orientation_cosine_quantized_abs(F(0x740))*100.0*C(0x104)+F(0xEC)),
                    static_cast<float>(lookup_orientation_sine_quantized_abs(F(0x740))*100.0+F(0xF0)+100.0),facing,1);
            }
            if (!((W(0x6C8) || S(0x736)<=10) && S(0x482)>0)) {
                reinterpret_cast<AliceFighterScratchView *>(raw+4)->reset();
                if (S(0x13E)==1 || S(0x13E)==2) {
                    signed char const facing=C(0x104);
                    if (facing==1) {
                        if (AT(AT(this,void *,0x170),float,0xEC)<F(0xEC)) {
                            C(0x104)=-1; F(0xF4)=-F(0xF4); SEQUENCE(6);
                        } else SEQUENCE(5);
                    } else if (AT(AT(this,void *,0x170),float,0xEC)>F(0xEC)) {
                        C(0x104)=static_cast<signed char>(-facing); F(0xF4)=-F(0xF4); SEQUENCE(6);
                    } else SEQUENCE(5);
                }
                if (S(0x13E)==3 || S(0x13E)==4) {
                    signed char const facing=C(0x104);
                    if (facing==1) {
                        if (AT(AT(this,void *,0x170),float,0xEC)<F(0xEC)) {
                            C(0x104)=-1; F(0xF4)=-F(0xF4); SEQUENCE(5);
                        } else SEQUENCE(6);
                    } else if (AT(AT(this,void *,0x170),float,0xEC)>F(0xEC)) {
                        C(0x104)=static_cast<signed char>(-facing); F(0xF4)=-F(0xF4); SEQUENCE(5);
                    } else SEQUENCE(6);
                }
                return;
            }
        }
        if (CROSSED()) {
            F(0xF0)=GROUND(); F(0x100)=0; F(0xF8)=0;
            if (S(0x13E)>=5) { ACTION(10); ZERO(); }
            else { reinterpret_cast<AliceFighterScratchView *>(raw+4)->reset(); ACTION(215); }
        }
        return;
    }

    case 215:
        resolve_stage_surface_landing_transition();
        if (F(0xf4) > 0.0f) {
            adjusted = static_cast<float>(F(0xf4) - 0.75);
            F(0xf4) = adjusted;
            if (adjusted < 0.0f)
                F(0xf4) = 0.0f;
        }
        if (F(0xf4) < 0.0f) {
            adjusted = static_cast<float>(F(0xf4) + 0.75);
            F(0xf4) = adjusted;
            if (adjusted > 0.0f)
                F(0xf4) = 0.0f;
        }
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        return;


    case 220:
        if (!U(0x13e))
            resolve_stage_surface_landing_transition();
        if (has_crossed_stage_surface_while_descending()) {
            set_action_and_finalize(10);
            F(0xf0) = alice_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if (is_y_at_or_below_stage_surface(this) || F(0xf8) > 0.0f)
            U(0x4ae) = 2;
        if (static_cast<__int16>(U(0x13e)) > 0) {
            adjusted = F(0xf8) - F(0x100);
            F(0xf8) = adjusted;
            if (adjusted < -20.0f)
                F(0xf8) = -20.0f;
        }
        advance_frame_and_dispatch();
        if (!I(0x144)
            && !U(0x142)
            && !U(0x140)
            && U(0x13e) == 1) {
            F(0xf4) = 0.0f;
            F(0xf8) = 19.0f;
            F(0x100) = 0.65f;
            B(0x47e) = 0;
            emit_fighter_effect_433cc0(
                63,
                F(0xec),
                F(0xf0),
                B(0x104),
                1);
        }
        return;

    case 223: {
        int facing;
        int input_product;
        short counter;

        resolve_stage_surface_landing_transition();
        B(0x47e) = 1;
        advance_frame_and_dispatch();
        if (U(0x13e) == 1) {
            if (!(I(0x144) % 5)) {
                facing = B(0x104);
                emit_fighter_effect_433cc0(
                    124,
                    static_cast<float>((F(0xec) + 50.0)
                        - static_cast<float>(mt19937_next_u32() % 100)),
                    static_cast<float>(static_cast<float>(mt19937_next_u32() % 200)
                        + F(0xf0)),
                    facing,
                    1);
            }
            counter = static_cast<short>(++U(0x730));
            input_product = I(0x6b4)
                * static_cast<signed char>(B(0x104));
            if ((input_product <= 0 && counter >= 13) || counter > 45) {
                set_action_and_finalize(204);
                return;
            }
        }
        if (!U(0x13e)
            && !U(0x142)
            && U(0x140) == 4) {
            F(0xf4) = 5.0f;
            facing = B(0x104);
            emit_fighter_effect_433cc0(
                125,
                F(0xec) + static_cast<float>(80 * static_cast<signed char>(facing)),
                static_cast<float>(F(0xf0) + 80.0),
                facing,
                1);
            emit_fighter_effect_433cc0(
                126,
                F(0xec),
                static_cast<float>(F(0xf0) + 80.0),
                facing,
                1);
            dispatch_indexed_event_member(0x1Fu);
        }
        return;
    }


    case 224: {
        int opposite_facing;

        if (!U(0x13e) && !U(0x140))
            resolve_stage_surface_landing_transition();
        if (U(0x13e) == 3) {
            resolve_stage_surface_landing_transition();
            adjusted = static_cast<float>(F(0xf4) + 2.0);
            F(0xf4) = adjusted;
            if (adjusted > 0.0f)
                F(0xf4) = 0.0f;
        }
        if (!is_y_at_or_below_stage_surface(this) && !(I(0x144) % 5)) {
            opposite_facing = static_cast<unsigned char>(-C(0x104));
            emit_fighter_effect_433cc0(
                124,
                static_cast<float>((F(0xec) + 50.0)
                    - static_cast<float>(mt19937_next_u32() % 100)),
                static_cast<float>(static_cast<float>(mt19937_next_u32() % 200)
                    + F(0xf0)),
                opposite_facing,
                1);
        }
        if (static_cast<short>(U(0x13e)) < 3) {
            F(0xf8) =
                F(0xf8) - F(0x100);
            if (has_crossed_stage_surface_while_descending()) {
                F(0xf8) = 0.0f;
                F(0xf0) = alice_stage_surface_height_at_x(this);
                select_sequence(3);
                return;
            }
        }
        if (advance_frame_and_dispatch()) {
            set_action_and_finalize(0);
            F(0xf4) = 0.0f;
            return;
        }
        if (!U(0x13e)
            && !U(0x142)
            && U(0x140) == 2) {
            F(0xf4) = -10.0f;
            F(0xf8) = 4.5f;
            F(0x100) = 0.6000000238418579f;
            opposite_facing = static_cast<unsigned char>(-C(0x104));
            emit_fighter_effect_433cc0(
                125,
                F(0xec),
                static_cast<float>(F(0xf0) + 80.0),
                opposite_facing,
                1);
            emit_fighter_effect_433cc0(
                126,
                F(0xec),
                static_cast<float>(F(0xf0) + 80.0),
                opposite_facing,
                1);
            dispatch_indexed_event_member(0x1Fu);
        }
        return;
    }

    case 225: {
        int opposite_facing;

        F(0xf8) =
            F(0xf8) - F(0x100);
        if (has_crossed_stage_surface_while_descending()) {
            zero_velocity_acceleration();
            F(0xf0) = alice_stage_surface_height_at_x(this);
            set_action_and_finalize(10);
            return;
        }
        if ((U(0x13e) == 1 || U(0x13e) == 2)
            && !(I(0x144) % 5)) {
            opposite_facing = static_cast<unsigned char>(-C(0x104));
            emit_fighter_effect_433cc0(
                124,
                static_cast<float>((F(0xec) + 50.0)
                    - static_cast<float>(mt19937_next_u32() % 100)),
                static_cast<float>(static_cast<float>(mt19937_next_u32() % 200)
                    + F(0xf0)),
                opposite_facing,
                1);
        }
        if (advance_frame_and_dispatch())
            set_action_and_finalize(9);
        if (!I(0x144)
            && !U(0x142)
            && !U(0x140)
            && U(0x13e) == 1) {
            F(0xf4) = -8.5f;
            F(0xf8) = 5.0f;
            F(0x100) = 0.6000000238418579f;
            opposite_facing = static_cast<unsigned char>(-C(0x104));
            emit_fighter_effect_433cc0(
                125,
                F(0xec),
                static_cast<float>(F(0xf0) + 120.0),
                opposite_facing,
                1);
            emit_fighter_effect_433cc0(
                126,
                F(0xec),
                static_cast<float>(F(0xf0) + 120.0),
                opposite_facing,
                1);
            dispatch_indexed_event_member(0x1Fu);
        }
        return;
    }

    case 226: {
        int facing;

        F(0xf8) =
            F(0xf8) - F(0x100);
        if (has_crossed_stage_surface_while_descending()) {
            zero_velocity_acceleration();
            F(0xf0) = alice_stage_surface_height_at_x(this);
            set_action_and_finalize(10);
            return;
        }
        if ((U(0x13e) == 1 || U(0x13e) == 2)
            && !(I(0x144) % 5)) {
            facing = B(0x104);
            emit_fighter_effect_433cc0(
                124,
                static_cast<float>((F(0xec) + 50.0)
                    - static_cast<float>(mt19937_next_u32() % 100)),
                static_cast<float>(static_cast<float>(mt19937_next_u32() % 200)
                    + F(0xf0)),
                facing,
                1);
        }
        if (advance_frame_and_dispatch())
            set_action_and_finalize(9);
        if (!I(0x144)
            && !U(0x142)
            && !U(0x140)
            && U(0x13e) == 1) {
            U(0x730) = 0;
            F(0xf4) = 8.5f;
            F(0xf8) = 5.0f;
            F(0x100) = 0.6000000238418579f;
            facing = B(0x104);
            emit_fighter_effect_433cc0(
                125,
                F(0xec) + static_cast<float>(80 * static_cast<signed char>(facing)),
                static_cast<float>(F(0xf0) + 110.0),
                facing,
                1);
            emit_fighter_effect_433cc0(
                126,
                F(0xec),
                static_cast<float>(F(0xf0) + 110.0),
                facing,
                1);
            dispatch_indexed_event_member(0x1Fu);
        }
        if (!I(0x144)
            && !U(0x142)
            && !U(0x140)
            && U(0x13e) == 3)
            face_opponent_and_flip_horizontal_velocity();
        return;
    }


    case 300:
        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(0))
            return;
        if (B(0x47e)) {
            adjusted = static_cast<float>(F(0xf4) - 0.5);
            F(0xf4) = adjusted;
            if (adjusted < 0.0f) {
                F(0xf4) = 0.0f;
                B(0x47e) = 0;
            }
        }
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        if (!U(0x142) && U(0x140) == 2) {
            dispatch_indexed_event_member(0x1Bu);
            B(0x47e) = 0;
        }
        return;

    case 301: {
        float spawn_payload[3];
        int facing;

        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(0))
            return;
        if (B(0x47e)) {
            adjusted = static_cast<float>(F(0xf4) - 0.5);
            F(0xf4) = adjusted;
            if (adjusted < 0.0f) {
                F(0xf4) = 0.0f;
                B(0x47e) = 0;
            }
        }
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        if (!U(0x142) && U(0x140) == 2) {
            spawn_payload[0] = 0.0f;
            spawn_payload[1] = 0.0f;
            spawn_payload[2] = 1.0f;
            facing = B(0x104);
            spawn_owned_object_via_manager(
                849,
                F(0xec) + static_cast<float>(30 * static_cast<signed char>(facing)),
                static_cast<float>(F(0xf0) + 100.0),
                facing,
                1,
                spawn_payload,
                3);
        }
        return;
    }

    case 302: {
        float spawn_payload[3];
        int facing;

        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(1))
            return;
        if (B(0x47e)) {
            adjusted = static_cast<float>(F(0xf4) - 0.5);
            F(0xf4) = adjusted;
            if (adjusted < 0.0f) {
                F(0xf4) = 0.0f;
                B(0x47e) = 0;
            }
        }
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        if (!U(0x142) && U(0x140) == 3) {
            dispatch_indexed_event_member(0x1Du);
            spawn_payload[0] = 0.0f;
            spawn_payload[1] = 0.0f;
            spawn_payload[2] = 8.0f;
            facing = B(0x104);
            spawn_owned_object_via_manager(
                849,
                F(0xec) + static_cast<float>(110 * static_cast<signed char>(facing)),
                static_cast<float>(F(0xf0) + 105.0),
                facing,
                1,
                spawn_payload,
                3);
        }
        return;
    }

    case 303:
        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(0))
            return;
        if (C(0x47e) > 0
            || F(0xf4) > 0.0f) {
            adjusted = static_cast<float>(F(0xf4) - 0.6000000238418579);
            F(0xf4) = adjusted;
            if (adjusted < 0.0f) {
                F(0xf4) = 0.0f;
                B(0x47e) = 0;
            }
        }
        if (advance_frame_and_dispatch())
            set_action_and_finalize(2);
        if (!U(0x142) && U(0x140) == 2)
            F(0xf4) = 6.0f;
        if (!U(0x142) && U(0x140) == 3)
            dispatch_indexed_event_member(0x1Cu);
        return;


    case 304: {
        float spawn_payload[3];
        int spawn_index;
        int facing;

        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(1))
            return;
        if (F(0xf4) > 0.0f) {
            adjusted = static_cast<float>(F(0xf4) - 1.0);
            F(0xf4) = adjusted;
            if (adjusted < 0.0f)
                F(0xf4) = 0.0f;
        }
        if (*reinterpret_cast<__int16 *>(raw + 320) >= 4
            && *reinterpret_cast<__int16 *>(raw + 320) <= 6) {
            if (static_cast<__int16>(U(0x730)) % 4 == 0
                && *reinterpret_cast<__int16 *>(raw + 1842) <= 4) {
                spawn_index = *reinterpret_cast<__int16 *>(raw + 1842);
                spawn_payload[0] = static_cast<float>(-10.0 - 13.0 * spawn_index);
                spawn_payload[1] = 30.0f;
                spawn_payload[2] = 11.0f;
                facing = B(0x104);
                spawn_owned_object_via_manager(
                    849,
                    static_cast<float>(F(0xec) + 30.0),
                    static_cast<float>(F(0xf0) + 100.0),
                    facing,
                    1,
                    spawn_payload,
                    3);
                ++U(0x732);
            }
            ++U(0x730);
        }
        if (advance_frame_and_dispatch())
            set_action_and_finalize(2);
        return;
    }

    case 305:
        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(1))
            return;
        if (*reinterpret_cast<__int16 *>(raw + 320) > 3) {
            adjusted = static_cast<float>(F(0xf4) - 0.75);
            F(0xf4) = adjusted;
            if (adjusted < 0.0f)
                F(0xf4) = 0.0f;
        }
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        if (!U(0x142) && U(0x140) == 2)
            dispatch_indexed_event_member(0x1Du);
        return;

    case 306:
        F(0xf8) =
            F(0xf8) - F(0x100);
        if (has_crossed_stage_surface_while_descending()) {
            set_action_and_finalize(10);
            F(0xf0) = alice_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if (advance_frame_and_dispatch())
            set_action_and_finalize(9);
        if (!U(0x142) && U(0x140) == 4)
            dispatch_indexed_event_member(0x1Bu);
        return;


    case 307: {
        float spawn_payload[3];
        int facing;

        if (*reinterpret_cast<__int16 *>(raw + 320) >= 11)
            F(0xf8) =
                F(0xf8) - F(0x100);
        if (has_crossed_stage_surface_while_descending()
            && *reinterpret_cast<__int16 *>(raw + 320) >= 11) {
            set_action_and_finalize(10);
            zero_velocity_acceleration();
            F(0xf0) = alice_stage_surface_height_at_x(this);
            return;
        }
        if (advance_frame_and_dispatch())
            set_action_and_finalize(9);
        if (!U(0x142) && U(0x140) == 3) {
            dispatch_indexed_event_member(0x1Du);
            spawn_payload[0] = 0.0f;
            spawn_payload[1] = 0.0f;
            spawn_payload[2] = 16.0f;
            facing = B(0x104);
            spawn_owned_object_via_manager(
                849,
                F(0xec) + static_cast<float>(50 * static_cast<signed char>(facing)),
                static_cast<float>(F(0xf0) + 140.0),
                facing,
                1,
                spawn_payload,
                3);
        }
        return;
    }

    case 308: {
        float spawn_payload[3];
        int facing;
        int i;

        F(0xf8) =
            F(0xf8) - F(0x100);
        if (has_crossed_stage_surface_while_descending()) {
            set_action_and_finalize(10);
            F(0xf0) = alice_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if (advance_frame_and_dispatch())
            set_action_and_finalize(9);
        if (!W(0x144)
            && !U(0x142)
            && !U(0x140)
            && U(0x13e) == 1)
            dispatch_indexed_event_member(0x1Du);
        if (!U(0x13e)) {
            if (!U(0x142) && U(0x140) == 4) {
                facing = B(0x104);
                for (i = 0; i < 6; ++i) {
                    spawn_payload[0] = static_cast<float>(-static_cast<double>(i) * 60.0);
                    spawn_payload[1] = 13.0f;
                    spawn_payload[2] = 17.0f;
                    spawn_owned_object_via_manager(
                        849,
                        F(0xec) + static_cast<float>(25 * static_cast<signed char>(facing)),
                        static_cast<float>(F(0xf0) + 95.0),
                        facing,
                        1,
                        spawn_payload,
                        3);
                    ++U(0x732);
                }
            }
            if (!U(0x142) && U(0x140) == 5) {
                F(0xf4) = -4.0f;
                F(0xf8) = 8.0f;
            }
        }
        if (!U(0x142) && U(0x13e) == 1)
            W(0x180) = 0;
        return;
    }

    case 309: {
        float spawn_payload[3];
        int facing;
        int i;

        F(0xf8) =
            F(0xf8) - F(0x100);
        if (has_crossed_stage_surface_while_descending()) {
            set_action_and_finalize(10);
            F(0xf0) = alice_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if (advance_frame_and_dispatch())
            set_action_and_finalize(9);
        if (!W(0x144)
            && !U(0x142)
            && !U(0x140)
            && U(0x13e) == 1)
            dispatch_indexed_event_member(0x1Du);
        if (!U(0x13e)
            && !U(0x142)
            && U(0x140) == 3) {
            facing = B(0x104);
            for (i = 0; i < 6; ++i) {
                spawn_payload[0] = static_cast<float>(-static_cast<double>(i) * 60.0);
                spawn_payload[1] = 13.0f;
                spawn_payload[2] = 24.0f;
                spawn_owned_object_via_manager(
                    849,
                    F(0xec) + static_cast<float>(30 * static_cast<signed char>(facing)),
                    static_cast<float>(F(0xf0) + 120.0),
                    facing,
                    1,
                    spawn_payload,
                    3);
                ++U(0x732);
            }
        }
        if (U(0x13e) == 2
            && !U(0x142)
            && U(0x140) == 4)
            F(0x100) = 0.5f;
        if (!U(0x142) && U(0x13e) == 1)
            W(0x180) = 0;
        return;
    }

    case 310: {
        double next_y;

        if (W(0x180)) {
            if (static_cast<__int16>(++U(0x730)) > 5) {
                W(0x180) = 0;
                U(0x730) = 0;
            }
        }
        if (U(0x13e) == 1) {
            if (!W(0x144))
                F(0xf4) = 15.0f;
            if (!(I(0x144) % 8))
                dispatch_indexed_event_member(0x1Bu);
            if (W(0x180)) {
                if (static_cast<__int16>(++U(0x730)) > 5) {
                    W(0x180) = 0;
                    U(0x730) = 0;
                }
            }
            if (I(0x144) > 30) {
                next_sequence_block();
                F(0xf8) = 6.0f;
                F(0xf4) =
                    static_cast<float>(F(0xf4) * 0.5);
            }
        }
        if (U(0x13e) == 2) {
            adjusted = F(0xf8) - F(0x100);
            F(0xf8) = adjusted;
            next_y = static_cast<double>(adjusted) + F(0xf0);
            if (alice_stage_surface_height_at_x(this) >= next_y) {
                F(0xf8) = 0.0f;
                F(0xf0) = alice_stage_surface_height_at_x(this);
                set_action_and_finalize(9);
                return;
            }
        }
        if (advance_frame_and_dispatch()) {
            set_action_and_finalize(9);
            return;
        }
        return;
    }

    case 320:
        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(0))
            return;
        if (*reinterpret_cast<__int16 *>(raw + 320) > 1) {
            adjusted = static_cast<float>(F(0xf4) - 2.0);
            F(0xf4) = adjusted;
            if (adjusted < 0.0f)
                F(0xf4) = 0.0f;
        }
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        if (!U(0x142) && U(0x140) == 2) {
            dispatch_indexed_event_member(0x1Cu);
            B(0x47e) = 0;
        }
        return;

    case 321:
        resolve_stage_surface_landing_transition();
        if (!try_dispatch_directional_action_208_210(1)) {
            if (*reinterpret_cast<__int16 *>(raw + 320) > 3) {
                adjusted = static_cast<float>(F(0xf4) - 0.5);
                F(0xf4) = adjusted;
                if (adjusted < 0.0f)
                    F(0xf4) = 0.0f;
            }
            if (advance_frame_and_dispatch())
                set_action_and_finalize(0);
            if (!U(0x142) && U(0x140) == 3) {
                dispatch_indexed_event_member(0x1Cu);
                F(0xf4) = 7.5f;
                B(0x47e) = 0;
            }
        }
        return;


    case 322: {
        int facing;

        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(1))
            return;
        adjusted = static_cast<float>(F(0xf4) - 1.5);
        F(0xf4) = adjusted;
        if (adjusted < 0.0f)
            F(0xf4) = 0.0f;
        if (!W(0x6bc))
            B(0x750) = 0;
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        if (!W(0x144)
            && !U(0x142)
            && !U(0x140)
            && U(0x13e) == 1) {
            set_action_and_finalize(0);
            return;
        }
        if (!U(0x13e)) {
            if (!U(0x142) && U(0x140) == 7) {
                if (B(0x750) == 1) {
                    next_sequence_block();
                    facing = B(0x104);
                    emit_fighter_effect_433cc0(
                        62,
                        F(0xec) - static_cast<float>(33 * static_cast<signed char>(facing)),
                        static_cast<float>(F(0xf0) + 112.0),
                        facing,
                        -1);
                    return;
                }
                F(0xf4) = 15.0f;
            }
            if (!U(0x142) && U(0x140) == 9) {
                dispatch_indexed_event_member(0x1Du);
                B(0x47e) = 0;
            }
        }
        if (U(0x13e) == 1) {
            if (!U(0x142) && U(0x140) == 11)
                F(0xf4) = 19.0f;
            if (!U(0x142) && U(0x140) == 12)
                dispatch_indexed_event_member(0x1Du);
        }
        return;
    }



 case 400: {
  RESOLVE(); if(I(0x6C0)==0) B(0x750)=0;
  if(FRAME()) ACTION(0);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==1) {
   if(C(0x750)==1) {
    SEQUENCE(4);
    EFFECT(62,static_cast<float>(25*C(0x104)+F(0xEC)),static_cast<float>(F(0xF0)+148.0),B(0x104),1);
    float packet[3]={-74,100,0};
    SPAWN(802,static_cast<float>(F(0xEC)-74*C(0x104)),static_cast<float>(F(0xF0)+104.0),B(0x104),1,packet,3);
    WAVE(2); ADJUST(200,45); I(0x180)=1; SCALE(30); return;
   }
   float packet[3]={-74,100,0};
   SPAWN(801,static_cast<float>(F(0xEC)-74*C(0x104)),static_cast<float>(F(0xF0)+104.0),B(0x104),1,packet,3);
   WAVE(2); ADJUST(200,45); I(0x180)=1; SCALE(30);
  }
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==4) { ACTION(0); return; }
  if(S(0x13E)==2 && I(0x144)>=20) BLOCK();
  if(S(0x13E)==4 && I(0x144)>=25) BLOCK();
  if(S(0x13E)==6 && I(0x144)>=40) BLOCK();
  return;
 }

    case 401: {
        float spawn_payload[3];
        int facing;
        resolve_stage_surface_landing_transition();
        if (!W(0x6c0))
            B(0x750) = 0;
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        if (!W(0x144)
            && !U(0x142)
            && !U(0x140)
            && U(0x13e) == 1) {
            spawn_payload[0] = -74.0f;
            spawn_payload[1] = 100.0f;
            spawn_payload[2] = 0.0f;
            facing = B(0x104);
            spawn_owned_object_via_manager(803,
                F(0xec) - static_cast<float>(74 * static_cast<signed char>(facing)),
                static_cast<float>(F(0xf0) + 104.0),
                facing, 1, spawn_payload, 3);
            dispatch_character_wave_handle(2);
            W(0x180) = 1;
            adjust_counter_482(200, 45);
            add_phase_scaled_counter_558(30);
        }
        if (!W(0x144)
            && !U(0x142)
            && !U(0x140)
            && U(0x13e) == 4) {
            set_action_and_finalize(0);
            return;
        }
        if (U(0x13e) == 2 && I(0x144) >= 30)
            next_sequence_block();
        if (U(0x13e) == 4 && I(0x144) >= 25)
            next_sequence_block();
        if (U(0x13e) == 6 && I(0x144) >= 45)
            next_sequence_block();
        return;
    }


    case 402: {
        float spawn_payload[3];
        int facing;
        resolve_stage_surface_landing_transition();
        if (advance_frame_and_dispatch())
            set_action_and_finalize(2);
        if (!U(0x142)
            && U(0x140) == 4) {
            spawn_payload[0] = 0.0f;
            spawn_payload[1] = 7.0f;
            spawn_payload[2] = 0.0f;
            facing = B(0x104);
            spawn_owned_object_via_manager(801,
                F(0xec) + static_cast<float>(20 * static_cast<signed char>(facing)),
                static_cast<float>(F(0xf0) + 90.0),
                facing, 1, spawn_payload, 3);
            dispatch_character_wave_handle(2);
            adjust_counter_482(200, 45);
            W(0x180) = 1;
            add_phase_scaled_counter_558(30);
        }
        return;
    }

    case 408: {
        float spawn_payload[3];
        int facing;

        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(1))
            return;
        adjusted = static_cast<float>(F(0xf4) - 0.25);
        F(0xf4) = adjusted;
        if (adjusted < 0.0f) {
            F(0xf4) = 0.0f;
            B(0x47e) = 0;
        }
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        if (!U(0x142) && U(0x140) == 2) {
            spawn_payload[0] = 0.0f;
            spawn_payload[1] = 0.0f;
            spawn_payload[2] = 19.0f;
            facing = B(0x104);
            spawn_owned_object_via_manager(
                849,
                F(0xec) + static_cast<float>(30 * static_cast<signed char>(facing)),
                static_cast<float>(F(0xf0) + 100.0),
                facing,
                1,
                spawn_payload,
                3);
        }
        return;
    }

    case 409:
        F(0xf8) =
            F(0xf8) - F(0x100);
        if (has_crossed_stage_surface_while_descending()) {
            set_action_and_finalize(10);
            zero_velocity_acceleration();
            F(0xf0) = alice_stage_surface_height_at_x(this);
            return;
        }
        if (!advance_frame_and_dispatch())
            return;
        set_action_and_finalize(9);
        return;



    case 410: {
        float spawn_payload[3];
        int facing;
        resolve_stage_surface_landing_transition();
        if (!W(0x6c4))
            B(0x750) = 0;
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        if (!U(0x13e)
            && !U(0x142)
            && U(0x140) == 3) {
            spawn_payload[0] = -45.0f;
            spawn_payload[1] = 40.0f;
            spawn_payload[2] = 0.0f;
            facing = B(0x104);
            spawn_owned_object_via_manager(805,
                F(0xec) + static_cast<float>(5 * static_cast<signed char>(facing)),
                static_cast<float>(F(0xf0) + 108.0),
                facing, 1, spawn_payload, 3);
            dispatch_character_wave_handle(2);
            W(0x180) = 1;
            adjust_counter_482(200, 60);
            add_phase_scaled_counter_558(30);
            return;
        }
        if (!W(0x144)
            && !U(0x142)
            && !U(0x140)
            && U(0x13e) == 1) {
            if (!B(0x750)) {
                set_action_and_finalize(0);
                return;
            }
            facing = B(0x104);
            emit_fighter_effect_433cc0(62,
                F(0xec) - static_cast<float>(66 * static_cast<signed char>(facing)),
                static_cast<float>(F(0xf0) + 148.0), facing, 1);
            return;
        }
        return;
    }

    case 411: {
        float spawn_payload[3];
        int facing;

        resolve_stage_surface_landing_transition();
        if (!W(0x6c4))
            B(0x750) = 0;
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        if (!U(0x13e)
            && !U(0x142)
            && U(0x140) == 3) {
            spawn_payload[0] = 0.0f;
            spawn_payload[1] = 40.0f;
            spawn_payload[2] = 0.0f;
            facing = B(0x104);
            spawn_owned_object_via_manager(
                805,
                F(0xec) + static_cast<float>(5 * static_cast<signed char>(facing)),
                static_cast<float>(F(0xf0) + 108.0),
                facing,
                1,
                spawn_payload,
                3);
            dispatch_character_wave_handle(2);
            W(0x180) = 1;
            adjust_counter_482(200, 60);
            add_phase_scaled_counter_558(30);
            return;
        }
        if (!W(0x144)
            && !U(0x142)
            && !U(0x140)
            && U(0x13e) == 1) {
            if (!B(0x750)) {
                set_action_and_finalize(0);
                return;
            }
            facing = B(0x104);
            emit_fighter_effect_433cc0(
                62,
                F(0xec) - static_cast<float>(66 * static_cast<signed char>(facing)),
                static_cast<float>(F(0xf0) + 148.0),
                facing,
                1);
            return;
        }
        return;
    }

    case 412: {
        float spawn_payload[3];
        int facing;

        resolve_stage_surface_landing_transition();
        if (!W(0x6c4))
            B(0x750) = 0;
        if (!U(0x13e)
            && !U(0x142)
            && U(0x140) == 10)
            F(0xf4) = 0.0f;
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        if (!U(0x13e) && !U(0x142)) {
            if (U(0x140) == 9) {
                spawn_payload[0] = -80.0f;
                spawn_payload[1] = 40.0f;
                spawn_payload[2] = 0.0f;
                facing = B(0x104);
                spawn_owned_object_via_manager(
                    805,
                    F(0xec) + static_cast<float>(5 * static_cast<signed char>(facing)),
                    static_cast<float>(F(0xf0) + 108.0),
                    facing,
                    1,
                    spawn_payload,
                    3);
                dispatch_character_wave_handle(2);
                W(0x180) = 1;
                adjust_counter_482(200, 60);
                add_phase_scaled_counter_558(30);
                return;
            }
            if (U(0x140) == 10)
                F(0xf4) = 34.0f;
        }
        if (!W(0x144)
            && !U(0x142)
            && !U(0x140)
            && U(0x13e) == 1) {
            if (!B(0x750)) {
                set_action_and_finalize(0);
                return;
            }
            facing = B(0x104);
            emit_fighter_effect_433cc0(
                62,
                F(0xec) - static_cast<float>(66 * static_cast<signed char>(facing)),
                static_cast<float>(F(0xf0) + 148.0),
                facing,
                1);
            return;
        }
        return;
    }


    case 500: {
        float spawn_payload[3];
        int facing;
        resolve_stage_surface_landing_transition();
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        if (!U(0x13e)
            && !U(0x142)
            && U(0x140) == 3) {
            spawn_payload[0] = 20.0f;
            spawn_payload[1] = 30.0f;
            spawn_payload[2] = 0.0f;
            W(0x180) = 1;
            facing = B(0x104);
            spawn_owned_object_via_manager(810,
                F(0xec) + static_cast<float>(8 * static_cast<signed char>(facing)),
                static_cast<float>(F(0xf0) + 100.0),
                facing, 1, spawn_payload, 3);
            dispatch_character_wave_handle(3);
            adjust_counter_482(200, 120);
            add_phase_scaled_counter_558(30);
        }
        return;
    }

    case 501: {
        float spawn_payload[3];
        int facing;
        resolve_stage_surface_landing_transition();
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        if (!U(0x13e)
            && !U(0x142)
            && U(0x140) == 3) {
            spawn_payload[0] = -25.0f;
            spawn_payload[1] = 30.0f;
            spawn_payload[2] = 0.0f;
            W(0x180) = 1;
            facing = B(0x104);
            spawn_owned_object_via_manager(810,
                F(0xec) + static_cast<float>(8 * static_cast<signed char>(facing)),
                static_cast<float>(F(0xf0) + 100.0),
                facing, 1, spawn_payload, 3);
            dispatch_character_wave_handle(3);
            adjust_counter_482(200, 120);
            add_phase_scaled_counter_558(30);
        }
        return;
    }


    case 505: {
        float spawn_payload[3];
        int facing;
        resolve_stage_surface_landing_transition();
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        if (!U(0x13e)
            && !U(0x142)
            && U(0x140) == 7) {
            spawn_payload[0] = 0.0f;
            spawn_payload[1] = 25.0f;
            spawn_payload[2] = 0.0f;
            W(0x180) = 1;
            facing = B(0x104);
            spawn_owned_object_via_manager(811,
                F(0xec) + static_cast<float>(8 * static_cast<signed char>(facing)),
                static_cast<float>(F(0xf0) + 100.0),
                facing, 1, spawn_payload, 3);
            dispatch_character_wave_handle(10);
            adjust_counter_482(200, 120);
            add_phase_scaled_counter_558(30);
        }
        return;
    }

    case 506: {
        float spawn_payload[3];
        int facing;
        resolve_stage_surface_landing_transition();
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        if (!U(0x13e)
            && !U(0x142)
            && U(0x140) == 7) {
            spawn_payload[0] = -45.0f;
            spawn_payload[1] = 25.0f;
            spawn_payload[2] = 0.0f;
            W(0x180) = 1;
            facing = B(0x104);
            spawn_owned_object_via_manager(811,
                F(0xec) + static_cast<float>(8 * static_cast<signed char>(facing)),
                static_cast<float>(F(0xf0) + 100.0),
                facing, 1, spawn_payload, 3);
            dispatch_character_wave_handle(10);
            adjust_counter_482(200, 120);
            add_phase_scaled_counter_558(30);
        }
        return;
    }


    case 507: {
        float spawn_payload[3];
        int facing;
        if (U(0x13e) == 3)
            resolve_stage_surface_landing_transition();
        if (static_cast<short>(U(0x13e)) < 3) {
            F(0xf8) =
                F(0xf8) - F(0x100);
            if (has_crossed_stage_surface_while_descending()) {
                zero_velocity_acceleration();
                F(0xf0) = alice_stage_surface_height_at_x(this);
                select_sequence(3);
                return;
            }
        }
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        if (!U(0x13e)
            && !U(0x142)) {
            if (U(0x140) == 5) {
                F(0xf4) = -5.0f;
                F(0xf8) = 5.0f;
                F(0x100) = 0.5f;
            }
            if (U(0x140) == 6) {
                spawn_payload[0] = 0.0f;
                spawn_payload[1] = 25.0f;
                spawn_payload[2] = 0.0f;
                W(0x180) = 1;
                facing = B(0x104);
                spawn_owned_object_via_manager(811,
                    F(0xec) + static_cast<float>(17 * static_cast<signed char>(facing)),
                    static_cast<float>(F(0xf0) + 104.0),
                    facing, 1, spawn_payload, 3);
                dispatch_character_wave_handle(10);
                adjust_counter_482(200, 120);
                add_phase_scaled_counter_558(30);
            }
        }
        if (!W(0x144)
            && !U(0x142)
            && !U(0x140)
            && U(0x13e) == 3)
            set_action_and_finalize(9);
        return;
    }

    case 695: {
        float effect_y0;
        float effect_y1;
        float effect_y2;
        float effect_y3;
        int facing;

        resolve_stage_surface_landing_transition();
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        if (!U(0x13e)
            && !U(0x142)
            && U(0x140) == 7) {
            dispatch_indexed_event_member(0x37u);
            facing = B(0x104);
            effect_y0 = F(0xf0) + 100.0f;
            emit_fighter_effect_433cc0(140, F(0xec), effect_y0, facing, 1);
            effect_y1 = F(0xf0) + 100.0f;
            emit_fighter_effect_433cc0(140, F(0xec), effect_y1, facing, 1);
            effect_y2 = F(0xf0) + 100.0f;
            emit_fighter_effect_433cc0(140, F(0xec), effect_y2, facing, 1);
            effect_y3 = F(0xf0) + 100.0f;
            emit_fighter_effect_433cc0(141, F(0xec), effect_y3, facing, -1);
            emit_fighter_effect_433cc0(142,
                F(0xec),
                F(0xf0),
                facing,
                -1);
        }
        return;
    }

    case 696:
        resolve_stage_surface_landing_transition();
        adjusted = static_cast<float>(F(0xf4) - 1.5);
        F(0xf4) = adjusted;
        if (adjusted < 0.0f)
            F(0xf4) = 0.0f;
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        if (U(0x13e))
            return;
        if (!U(0x142) && U(0x140) == 8)
            F(0xf4) = 15.0f;
        if (!U(0x142) && U(0x140) == 9) {
            dispatch_indexed_event_member(0x1Du);
            B(0x47e) = 0;
        }
        return;

 case 404: {
  if(S(0x13E)==8) RESOLVE();
  if(S(0x13E)==3 || S(0x13E)==7) F(0xF8)-=F(0x100);
  if(CROSSED() && S(0x13E)<8) { SEQUENCE(8); F(0xF0)=GROUND(); ZERO(); return; }
  if(I(0x6C0)==0) B(0x750)=0;
  if(FRAME()) ACTION(0);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==1) {
   if(C(0x750)==1) {
    SEQUENCE(4); EFFECT(62,static_cast<float>(25*C(0x104)+F(0xEC)),static_cast<float>(F(0xF0)+148.0),B(0x104),1);
    float packet[3]={-74,100,0};
    SPAWN(802,static_cast<float>(F(0xEC)-74*C(0x104)),static_cast<float>(F(0xF0)+104.0),B(0x104),1,packet,3);
    WAVE(2); ADJUST(200,45); I(0x180)=1; SCALE(30); return;
   }
   float packet[3]={-74,100,0};
   SPAWN(801,static_cast<float>(F(0xEC)-74*C(0x104)),static_cast<float>(F(0xF0)+104.0),B(0x104),1,packet,3);
   WAVE(2); ADJUST(200,45); I(0x180)=1; SCALE(30);
  }
  if(I(0x144)==0) {
   if(S(0x142)==0 && S(0x140)==0 && S(0x13E)==4) { ACTION(9); return; }
   if(S(0x142)==0 && S(0x140)==0 && S(0x13E)==8) ACTION(9);
  }
  if(S(0x13E)==2 && I(0x144)>=20) BLOCK();
  if(S(0x13E)==4 && I(0x144)>=25) BLOCK();
  if(S(0x13E)==6 && I(0x144)>=40) BLOCK();
  return;
 }
 case 406: {
  if(S(0x13E)==8) RESOLVE();
  if(S(0x13E)==3 || S(0x13E)==7) F(0xF8)-=F(0x100);
  if(CROSSED() && S(0x13E)<8) { SEQUENCE(8); F(0xF0)=GROUND(); ZERO(); return; }
  if(I(0x6C0)==0) B(0x750)=0;
  if(FRAME()) ACTION(0);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==1) {
   if(C(0x750)==1) {
    SEQUENCE(4); EFFECT(62,static_cast<float>(25*C(0x104)+F(0xEC)),static_cast<float>(F(0xF0)+148.0),B(0x104),1);
    float packet[3]={-74,100,1};
    SPAWN(802,static_cast<float>(F(0xEC)-74*C(0x104)),static_cast<float>(F(0xF0)+104.0),B(0x104),1,packet,3);
    WAVE(2); ADJUST(200,45); I(0x180)=1; SCALE(30); return;
   }
   float packet[3]={-74,100,1};
   SPAWN(801,static_cast<float>(F(0xEC)-74*C(0x104)),static_cast<float>(F(0xF0)+104.0),B(0x104),1,packet,3);
   WAVE(2); ADJUST(200,45); I(0x180)=1; SCALE(30);
  }
  if(I(0x144)==0) {
   if(S(0x142)==0 && S(0x140)==0 && S(0x13E)==4) { ACTION(9); return; }
   if(S(0x142)==0 && S(0x140)==0 && S(0x13E)==8) ACTION(9);
  }
  if(S(0x13E)==2 && I(0x144)>=20) BLOCK();
  if(S(0x13E)==4 && I(0x144)>=25) BLOCK();
  if(S(0x13E)==6 && I(0x144)>=40) BLOCK();
  return;
 }
 case 414: {
  if(S(0x13E)==2) RESOLVE();
  if(I(0x6C4)==0) B(0x750)=0;
  if(S(0x13E)==1 && S(0x140)>=12) F(0xF8)-=F(0x100);
  if((S(0x13E)==0 || (S(0x13E)==1 && S(0x140)>=12)) && CROSSED()) {
   SEQUENCE(2); F(0xF0)=GROUND(); ZERO(); return;
  }
  if(FRAME()) ACTION(0);
  short const sequence=S(0x13E);
  if(sequence==0 && S(0x142)==0) {
   if(S(0x140)==6) {
    float packet[3]={45,40,0};
    SPAWN(805,static_cast<float>(20*C(0x104)+F(0xEC)),static_cast<float>(F(0xF0)+100.0),B(0x104),1,packet,3);
    WAVE(2); ADJUST(200,60); I(0x180)=1; SCALE(30); return;
   }
   if(S(0x140)==11 && C(0x750)==1) {
    EFFECT(62,static_cast<float>(F(0xEC)-47*C(0x104)),static_cast<float>(F(0xF0)+185.0),B(0x104),1); BLOCK(); return;
   }
  }
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && (sequence==1 || sequence==2)) ACTION(9);
  return;
 }
 case 415: {
  if(S(0x13E)==2) RESOLVE();
  if(I(0x6C4)==0) B(0x750)=0;
  if(S(0x13E)==1 && S(0x140)>=12) F(0xF8)-=F(0x100);
  if((S(0x13E)==0 || (S(0x13E)==1 && S(0x140)>=12)) && CROSSED()) {
   SEQUENCE(2); F(0xF0)=GROUND(); ZERO(); return;
  }
  if(FRAME()) ACTION(0);
  short const sequence=S(0x13E);
  if(sequence==0 && S(0x142)==0) {
   if(S(0x140)==6) {
    float packet[3]={0,40,0};
    SPAWN(805,static_cast<float>(20*C(0x104)+F(0xEC)),static_cast<float>(F(0xF0)+100.0),B(0x104),1,packet,3);
    WAVE(2); ADJUST(200,60); I(0x180)=1; SCALE(30); return;
   }
   if(S(0x140)==11 && C(0x750)==1) {
    EFFECT(62,static_cast<float>(F(0xEC)-47*C(0x104)),static_cast<float>(F(0xF0)+185.0),B(0x104),1); BLOCK(); return;
   }
  }
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && (sequence==1 || sequence==2)) ACTION(9);
  return;
 }
 case 416: {
  if(S(0x13E)==2) RESOLVE();
  if(I(0x6C4)==0) B(0x750)=0;
  if(S(0x13E)==1 && S(0x140)>=12) F(0xF8)-=F(0x100);
  if((S(0x13E)==0 || (S(0x13E)==1 && S(0x140)>=12)) && CROSSED()) {
   SEQUENCE(2); F(0xF0)=GROUND(); ZERO(); return;
  }
  if(FRAME()) ACTION(0);
  short const sequence=S(0x13E);
  if(sequence==0 && S(0x142)==0) {
   if(S(0x140)==5) {
    float packet[3]={80,40,0};
    SPAWN(805,static_cast<float>(20*C(0x104)+F(0xEC)),static_cast<float>(F(0xF0)+100.0),B(0x104),1,packet,3);
    WAVE(2); ADJUST(200,60); I(0x180)=1; SCALE(30); return;
   }
   if(S(0x140)==8 && C(0x750)==1) {
    EFFECT(62,static_cast<float>(F(0xEC)-47*C(0x104)),static_cast<float>(F(0xF0)+185.0),B(0x104),1); BLOCK(); return;
   }
  }
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && (sequence==1 || sequence==2)) ACTION(9);
  return;
 }
 case 418:
  RESOLVE(); if(GATE(1)) return;
  F(0xF4)-=D(0.35f); if(F(0xF4)<0.0f) { F(0xF4)=0; B(0x47E)=0; }
  if(FRAME()) ACTION(0);
  if(S(0x142)==0 && S(0x140)==2) {
   float packet[3]={0,0,21};
   SPAWN(849,static_cast<float>(F(0xEC)+0.0),static_cast<float>(F(0xF0)+50.0),B(0x104),255,packet,3); EVENT(29);
  }
  if(S(0x142)==0 && S(0x140)==3) {
   float packet[3]={0,0,23};
   SPAWN(849,static_cast<float>(F(0xEC)+0.0),static_cast<float>(F(0xF0)+50.0),B(0x104),1,packet,3); EVENT(29);
  }
  if(S(0x142)==0 && S(0x140)==4) {
   float packet[3]={0,0,21};
   SPAWN(849,static_cast<float>(F(0xEC)+0.0),static_cast<float>(F(0xF0)+50.0),B(0x104),255,packet,3); EVENT(29);
  }
  if(S(0x142)==0 && S(0x140)==5) {
   float packet[3]={0,0,23};
   SPAWN(849,static_cast<float>(F(0xEC)+0.0),static_cast<float>(F(0xF0)+50.0),B(0x104),1,packet,3); EVENT(29);
  }
  return;
    case 508: {
        float spawn_payload[3];
        int facing;
        if (U(0x13e) == 3)
            resolve_stage_surface_landing_transition();
        if (static_cast<short>(U(0x13e)) < 3) {
            F(0xf8) =
                F(0xf8) - F(0x100);
            if (has_crossed_stage_surface_while_descending()) {
                zero_velocity_acceleration();
                F(0xf0) = alice_stage_surface_height_at_x(this);
                select_sequence(3);
                return;
            }
        }
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        if (!U(0x13e)
            && !U(0x142)) {
            if (U(0x140) == 5) {
                F(0xf4) = -5.0f;
                F(0xf8) = 5.0f;
                F(0x100) = 0.5f;
            }
            if (U(0x140) == 6) {
                spawn_payload[0] = 45.0f;
                spawn_payload[1] = 25.0f;
                spawn_payload[2] = 0.0f;
                W(0x180) = 1;
                facing = B(0x104);
                spawn_owned_object_via_manager(811,
                    F(0xec) + static_cast<float>(17 * static_cast<signed char>(facing)),
                    static_cast<float>(F(0xf0) + 104.0),
                    facing, 1, spawn_payload, 3);
                dispatch_character_wave_handle(10);
                adjust_counter_482(200, 120);
                add_phase_scaled_counter_558(30);
            }
        }
        if (!W(0x144)
            && !U(0x142)
            && !U(0x140)
            && U(0x13e) == 3)
            set_action_and_finalize(9);
        return;
    }

 case 520: {
  if(S(0x13E)==0 || S(0x13E)==4 || S(0x13E)==8) RESOLVE();
  if(I(0x6C0)==0) B(0x750)=0;
  if((S(0x13E)==2 || S(0x13E)==3) && I(0x144)>=0) {
   switch(B(0x605)) { case 0: S(0x732)=3; break; case 1: case 2: S(0x732)=4; break; case 3: case 4: S(0x732)=5; break; }
   if(I(0x144)%6==0 && S(0x730)<S(0x732)) {
    I(0x180)=1; SCALE(10); ++S(0x730);
    float packet[3]; packet[0]=static_cast<float>(-25*S(0x730)+70); packet[1]=15; packet[2]=0;
    SPAWN(815,static_cast<float>(14*C(0x104)+F(0xEC)),static_cast<float>(F(0xF0)+111.0),B(0x104),1,packet,3);
    WAVE(5); if(S(0x730)==1) ADJUST(200,120);
   }
  }
  if((S(0x13E)==6 || S(0x13E)==7) && I(0x144)>=0) {
   switch(B(0x605)) { case 0: S(0x732)=5; break; case 1: case 2: S(0x732)=6; break; case 3: case 4: S(0x732)=7; break; }
   if(I(0x144)%3==0 && S(0x730)<S(0x732)) {
    I(0x180)=1; ++S(0x730); SCALE(10);
    float packet[3]; packet[0]=static_cast<float>((5-S(0x730))*15); packet[1]=15; packet[2]=0;
    SPAWN(815,static_cast<float>(14*C(0x104)+F(0xEC)),static_cast<float>(F(0xF0)+111.0),B(0x104),1,packet,3);
    WAVE(5); if(S(0x730)==1) ADJUST(200,120);
   }
  }
  short const sequence=S(0x13E);
  if(sequence==1 || sequence==2 || sequence==3 || sequence==5 || sequence==6 || sequence==7) {
   F(0xF8)-=F(0x100);
   if(CROSSED()) { F(0xF0)=GROUND(); ZERO(); SEQUENCE(8); return; }
  }
  if(FRAME()) ACTION(0);
  short const next_sequence=S(0x13E);
  if(next_sequence==0 && S(0x142)==0 && S(0x140)==3 && C(0x750)==1) {
   SEQUENCE(4); EFFECT(62,static_cast<float>(F(0xEC)-4*C(0x104)),static_cast<float>(F(0xF0)+116.0),B(0x104),-1); return;
  }
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && next_sequence==1) { F(0xF4)=-7.5f; F(0xF8)=12.5f; F(0x100)=0.7f; }
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==5) { F(0xF4)=-6; F(0xF8)=17.5f; F(0x100)=0.7f; }
  return;
 }
 case 521: {
  if(S(0x13E)==0 || S(0x13E)==4 || S(0x13E)==8) RESOLVE();
  if(I(0x6C0)==0) B(0x750)=0;
  if((S(0x13E)==2 || S(0x13E)==3) && I(0x144)>=0) {
   switch(B(0x605)) { case 0: S(0x732)=3; break; case 1: case 2: S(0x732)=4; break; case 3: case 4: S(0x732)=5; break; }
   if(I(0x144)%6==0 && S(0x730)<S(0x732)) {
    I(0x180)=1; SCALE(10); ++S(0x730);
    float packet[3]; packet[0]=static_cast<float>(-25*S(0x730)+40); packet[1]=15; packet[2]=0;
    SPAWN(815,static_cast<float>(14*C(0x104)+F(0xEC)),static_cast<float>(F(0xF0)+111.0),B(0x104),1,packet,3);
    WAVE(5); if(S(0x730)==1) ADJUST(200,120);
   }
  }
  if((S(0x13E)==6 || S(0x13E)==7) && I(0x144)>=0) {
   switch(B(0x605)) { case 0: S(0x732)=5; break; case 1: case 2: S(0x732)=6; break; case 3: case 4: S(0x732)=7; break; }
   if(I(0x144)%3==0 && S(0x730)<S(0x732)) {
    I(0x180)=1; ++S(0x730); SCALE(10);
    float packet[3]; packet[0]=static_cast<float>((5-S(0x730))*15); packet[1]=15; packet[2]=0;
    SPAWN(815,static_cast<float>(14*C(0x104)+F(0xEC)),static_cast<float>(F(0xF0)+111.0),B(0x104),1,packet,3);
    WAVE(5); if(S(0x730)==1) ADJUST(200,120);
   }
  }
  short const sequence=S(0x13E);
  if(sequence==1 || sequence==2 || sequence==3 || sequence==5 || sequence==6 || sequence==7) {
   F(0xF8)-=F(0x100);
   if(CROSSED()) { F(0xF0)=GROUND(); ZERO(); SEQUENCE(8); return; }
  }
  if(FRAME()) ACTION(0);
  short const next_sequence=S(0x13E);
  if(next_sequence==0 && S(0x142)==0 && S(0x140)==3 && C(0x750)==1) {
   SEQUENCE(4); EFFECT(62,static_cast<float>(F(0xEC)-4*C(0x104)),static_cast<float>(F(0xF0)+116.0),B(0x104),-1); return;
  }
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && next_sequence==1) { F(0xF4)=-7.5f; F(0xF8)=12.5f; F(0x100)=0.7f; }
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==5) { F(0xF4)=-6; F(0xF8)=17.5f; F(0x100)=0.7f; }
  return;
 }
 case 522: {
  if(S(0x13E)==8) RESOLVE();
  if(I(0x6C0)==0) B(0x750)=0;
  if((S(0x13E)==2 || S(0x13E)==3) && I(0x144)>=0) {
   switch(B(0x605)) { case 0: S(0x732)=3; break; case 1: case 2: S(0x732)=4; break; case 3: case 4: S(0x732)=5; break; }
   if(I(0x144)%6==0 && S(0x730)<S(0x732)) {
    I(0x180)=1; SCALE(10); ++S(0x730);
    float packet[3]; packet[0]=static_cast<float>(-25*S(0x730)+70); packet[1]=15; packet[2]=0;
    SPAWN(815,static_cast<float>(14*C(0x104)+F(0xEC)),static_cast<float>(F(0xF0)+111.0),B(0x104),1,packet,3);
    WAVE(5); if(S(0x730)==1) ADJUST(200,120);
   }
  }
  if((S(0x13E)==6 || S(0x13E)==7) && I(0x144)>=0) {
   switch(B(0x605)) { case 0: S(0x732)=5; break; case 1: case 2: S(0x732)=6; break; case 3: case 4: S(0x732)=7; break; }
   if(I(0x144)%3==0 && S(0x730)<S(0x732)) {
    I(0x180)=1; ++S(0x730); SCALE(10);
    float packet[3]; packet[0]=static_cast<float>((5-S(0x730))*15); packet[1]=15; packet[2]=0;
    SPAWN(815,static_cast<float>(14*C(0x104)+F(0xEC)),static_cast<float>(F(0xF0)+111.0),B(0x104),1,packet,3);
    WAVE(5); if(S(0x730)==1) ADJUST(200,120);
   }
  }
  short const sequence=S(0x13E);
  if(sequence==1 || sequence==2 || sequence==3 || sequence==5 || sequence==6 || sequence==7) {
   F(0xF8)-=F(0x100);
   if(CROSSED()) { F(0xF0)=GROUND(); ZERO(); SEQUENCE(8); return; }
  }
  if(FRAME()) ACTION(0);
  short const next_sequence=S(0x13E);
  if(next_sequence==0 && S(0x142)==0 && S(0x140)==3 && C(0x750)==1) {
   SEQUENCE(4); EFFECT(62,static_cast<float>(F(0xEC)-4*C(0x104)),static_cast<float>(F(0xF0)+116.0),B(0x104),-1); return;
  }
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && next_sequence==1) { F(0xF4)=-7.5f; F(0xF8)=12.5f; F(0x100)=0.7f; }
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==5) { F(0xF4)=-6; F(0xF8)=17.5f; F(0x100)=0.7f; }
  return;
 }
 case 523: {
  if(S(0x13E)==8) RESOLVE();
  if(I(0x6C0)==0) B(0x750)=0;
  if((S(0x13E)==2 || S(0x13E)==3) && I(0x144)>=0) {
   switch(B(0x605)) { case 0: S(0x732)=3; break; case 1: case 2: S(0x732)=4; break; case 3: case 4: S(0x732)=5; break; }
   if(I(0x144)%6==0 && S(0x730)<S(0x732)) {
    I(0x180)=1; SCALE(10); ++S(0x730);
    float packet[3]; packet[0]=static_cast<float>(-25*S(0x730)+40); packet[1]=15; packet[2]=0;
    SPAWN(815,static_cast<float>(14*C(0x104)+F(0xEC)),static_cast<float>(F(0xF0)+111.0),B(0x104),1,packet,3);
    WAVE(5); if(S(0x730)==1) ADJUST(200,120);
   }
  }
  if((S(0x13E)==6 || S(0x13E)==7) && I(0x144)>=0) {
   switch(B(0x605)) { case 0: S(0x732)=5; break; case 1: case 2: S(0x732)=6; break; case 3: case 4: S(0x732)=7; break; }
   if(I(0x144)%3==0 && S(0x730)<S(0x732)) {
    I(0x180)=1; ++S(0x730); SCALE(10);
    float packet[3]; packet[0]=static_cast<float>((5-S(0x730))*15); packet[1]=15; packet[2]=0;
    SPAWN(815,static_cast<float>(14*C(0x104)+F(0xEC)),static_cast<float>(F(0xF0)+111.0),B(0x104),1,packet,3);
    WAVE(5); if(S(0x730)==1) ADJUST(200,120);
   }
  }
  short const sequence=S(0x13E);
  if(sequence==1 || sequence==2 || sequence==3 || sequence==5 || sequence==6 || sequence==7) {
   F(0xF8)-=F(0x100);
   if(CROSSED()) { F(0xF0)=GROUND(); ZERO(); SEQUENCE(8); return; }
  }
  if(FRAME()) ACTION(0);
  short const next_sequence=S(0x13E);
  if(next_sequence==0 && S(0x142)==0 && S(0x140)==3 && C(0x750)==1) {
   SEQUENCE(4); EFFECT(62,static_cast<float>(F(0xEC)-4*C(0x104)),static_cast<float>(F(0xF0)+116.0),B(0x104),-1); return;
  }
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && next_sequence==1) { F(0xF4)=-7.5f; F(0xF8)=12.5f; F(0x100)=0.7f; }
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==5) { F(0xF4)=-6; F(0xF8)=17.5f; F(0x100)=0.7f; }
  return;
 }
 case 525: {
  RESOLVE(); if(I(0x6C0)==0) B(0x750)=0;
  if(S(0x13E)==1 && I(0x144)>=16) { BLOCK(); return; }
  if(FRAME()) ACTION(0);
  if(S(0x13E)==0 && S(0x142)==0) {
   if(S(0x140)==8 && C(0x750)==1) { BLOCK(); EFFECT(62,static_cast<float>(F(0xEC)-33*C(0x104)),static_cast<float>(F(0xF0)+112.0),B(0x104),-1); return; }
   if(S(0x140)==10) {
    for(float n=0;n<C(0x609)+1;n+=1.0) {
     float packet[3]; packet[1]=n*2.0; packet[0]=2.0+packet[1]; packet[1]+=21.0; packet[2]=0;
     SPAWN(816,static_cast<float>(124*C(0x104)+F(0xEC)),static_cast<float>(F(0xF0)+100.0),B(0x104),1,packet,3);
    }
    WAVE(3); I(0x180)=1; ADJUST(200,120); SCALE(50);
   }
  }
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==1) { ACTION(0); return; }
  if(S(0x13E)==2 && S(0x142)==0 && S(0x140)==2) {
   for(float n=0;n<C(0x609)+3;n+=1.0) {
    float packet[3]; packet[0]=n+n+1.0; packet[1]=n+n+21.0; packet[2]=0;
    SPAWN(816,static_cast<float>(124*C(0x104)+F(0xEC)),static_cast<float>(F(0xF0)+100.0),B(0x104),1,packet,3);
   }
   WAVE(3); I(0x180)=1; ADJUST(200,120); SCALE(50);
  }
  return;
 }
 case 526: {
  RESOLVE(); if(I(0x6C4)==0) B(0x750)=0;
  if(S(0x13E)==1 && I(0x144)>=16) { BLOCK(); return; }
  if(FRAME()) ACTION(0);
  if(S(0x13E)==0 && S(0x142)==0) {
   if(S(0x140)==8 && C(0x750)==1) { BLOCK(); EFFECT(62,static_cast<float>(F(0xEC)-33*C(0x104)),static_cast<float>(F(0xF0)+112.0),B(0x104),-1); return; }
   if(S(0x140)==10) {
    for(float n=0;n<C(0x609)+1;n+=1.0) {
     float packet[3]; packet[0]=10.0+n+n; packet[1]=n+n+21.0; packet[2]=0;
     SPAWN(816,static_cast<float>(124*C(0x104)+F(0xEC)),static_cast<float>(F(0xF0)+100.0),B(0x104),1,packet,3);
    }
    WAVE(3); I(0x180)=1; ADJUST(200,120); SCALE(50);
   }
  }
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==1) { ACTION(0); return; }
  if(S(0x13E)==2 && S(0x142)==0 && S(0x140)==2) {
   for(float n=0;n<C(0x609)+3;n+=1.0) {
    float packet[3]; packet[1]=n*2.0; packet[0]=2.0+packet[1]; packet[1]+=21.0; packet[2]=0;
    SPAWN(816,static_cast<float>(124*C(0x104)+F(0xEC)),static_cast<float>(F(0xF0)+100.0),B(0x104),1,packet,3);
   }
   WAVE(3); I(0x180)=1; ADJUST(200,120); SCALE(50);
  }
  return;
 }
 case 530: {
  RESOLVE(); if(I(0x6C0)==0) B(0x750)=0;
  if(FRAME()) ACTION(0);
  if(S(0x13E)==0 && S(0x142)==0 && S(0x140)==3) {
   float packet[3]={3,5,0}; SPAWN(817,F(0xEC),static_cast<float>(F(0xF0)+100.0),B(0x104),1,packet,3);
   WAVE(3); I(0x180)=1; ADJUST(200,120); SCALE(50);
  }
  return;
 }
 case 531: {
  RESOLVE(); if(I(0x6C4)==0) B(0x750)=0;
  if(FRAME()) ACTION(0);
  if(S(0x13E)==0 && S(0x142)==0 && S(0x140)==3) {
   float packet[3]={3,5,9}; SPAWN(817,F(0xEC),static_cast<float>(F(0xF0)+100.0),B(0x104),1,packet,3);
   WAVE(3); I(0x180)=1; ADJUST(200,120); SCALE(50);
  }
  return;
 }
 case 540: {
  RESOLVE(); if(S(0x13E)==2 && I(0x144)>=20) { BLOCK(); return; }
  if(FRAME()) ACTION(0);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==1) {
   WAVE(3); ADJUST(200,120); I(0x180)=1; SCALE(50);
   float packet[4]={4,15,0,30};
   SPAWN(820,static_cast<float>(F(0xEC)+0.0),static_cast<float>(F(0xF0)+120.0),B(0x104),255,packet,4);
   packet[0]=-4; packet[1]=15; packet[3]=15;
   SPAWN(820,static_cast<float>(F(0xEC)+0.0),static_cast<float>(F(0xF0)+120.0),B(0x104),255,packet,4);
   packet[0]=8; packet[1]=14; packet[3]=45;
   SPAWN(820,static_cast<float>(F(0xEC)+0.0),static_cast<float>(F(0xF0)+120.0),B(0x104),255,packet,4);
   packet[0]=-8; packet[1]=14; packet[3]=0;
   SPAWN(820,static_cast<float>(F(0xEC)+0.0),static_cast<float>(F(0xF0)+120.0),B(0x104),255,packet,4);
  }
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==4) ACTION(0);
  return;
 }
 case 541: {
  RESOLVE(); if(S(0x13E)==2 && I(0x144)>=10) { BLOCK(); return; }
  if(FRAME()) ACTION(0);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==1) {
   WAVE(3); ADJUST(200,120); I(0x180)=1; SCALE(50);
   float packet[4]={5,17,0,0};
   SPAWN(820,static_cast<float>(F(0xEC)+0.0),static_cast<float>(F(0xF0)+120.0),B(0x104),255,packet,4);
   packet[0]=10; packet[1]=17; packet[3]=5;
   SPAWN(820,static_cast<float>(F(0xEC)+0.0),static_cast<float>(F(0xF0)+120.0),B(0x104),255,packet,4);
   packet[0]=5; packet[1]=12; packet[3]=10;
   SPAWN(820,static_cast<float>(F(0xEC)+0.0),static_cast<float>(F(0xF0)+120.0),B(0x104),255,packet,4);
   packet[0]=10; packet[1]=12; packet[3]=15;
   SPAWN(820,static_cast<float>(F(0xEC)+0.0),static_cast<float>(F(0xF0)+120.0),B(0x104),255,packet,4);
  }
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==4) ACTION(0);
  return;
 }
 case 542: {
  if(S(0x13E)==8) RESOLVE();
  short const sequence=S(0x13E);
  if(sequence==2 && I(0x144)>=20) { F(0x100)=0.5f; BLOCK(); return; }
  if(sequence==3 || sequence==7) {
   F(0xF8)-=F(0x100); if(CROSSED()) { SEQUENCE(8); F(0xF0)=GROUND(); ZERO(); return; }
  }
  if(FRAME()) ACTION(0);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==1) {
   WAVE(3); ADJUST(200,120); I(0x180)=1; SCALE(50);
   float packet[4]={4,15,0,30};
   SPAWN(820,static_cast<float>(F(0xEC)+0.0),static_cast<float>(F(0xF0)+120.0),B(0x104),255,packet,4);
   packet[0]=-4; packet[1]=15; packet[3]=15;
   SPAWN(820,static_cast<float>(F(0xEC)+0.0),static_cast<float>(F(0xF0)+120.0),B(0x104),255,packet,4);
   packet[0]=8; packet[1]=14; packet[3]=45;
   SPAWN(820,static_cast<float>(F(0xEC)+0.0),static_cast<float>(F(0xF0)+120.0),B(0x104),255,packet,4);
   packet[0]=-8; packet[1]=14; packet[3]=0;
   SPAWN(820,static_cast<float>(F(0xEC)+0.0),static_cast<float>(F(0xF0)+120.0),B(0x104),255,packet,4);
  }
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && (S(0x13E)==4 || S(0x13E)==8)) ACTION(9);
  return;
 }
 case 543: {
  if(S(0x13E)==8) RESOLVE();
  short const sequence=S(0x13E);
  if(sequence==2 && I(0x144)>=20) { F(0x100)=0.5f; BLOCK(); return; }
  if(sequence==3 || sequence==7) {
   F(0xF8)-=F(0x100); if(CROSSED()) { SEQUENCE(8); F(0xF0)=GROUND(); ZERO(); return; }
  }
  if(FRAME()) ACTION(0);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==1) {
   WAVE(3); ADJUST(200,120); I(0x180)=1; SCALE(50);
   float packet[4]={5,17,0,0};
   SPAWN(820,static_cast<float>(F(0xEC)+0.0),static_cast<float>(F(0xF0)+120.0),B(0x104),255,packet,4);
   packet[0]=10; packet[1]=17; packet[3]=5;
   SPAWN(820,static_cast<float>(F(0xEC)+0.0),static_cast<float>(F(0xF0)+120.0),B(0x104),255,packet,4);
   packet[0]=5; packet[1]=12; packet[3]=10;
   SPAWN(820,static_cast<float>(F(0xEC)+0.0),static_cast<float>(F(0xF0)+120.0),B(0x104),255,packet,4);
   packet[0]=10; packet[1]=12; packet[3]=15;
   SPAWN(820,static_cast<float>(F(0xEC)+0.0),static_cast<float>(F(0xF0)+120.0),B(0x104),255,packet,4);
  }
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && (S(0x13E)==4 || S(0x13E)==8)) ACTION(9);
  return;
 }
 case 545: {
  RESOLVE();
  if((S(0x13E)==1 || S(0x13E)==2) && I(0x144)%7==0 && S(0x730)<7) {
   float packet[3]; packet[0]=static_cast<float>(static_cast<float>(mt19937_next_u32()%110)-60.0);
   packet[1]=static_cast<float>(static_cast<float>(mt19937_next_u32()%170)+10.0); packet[2]=0;
   if(static_cast<unsigned>(selector_random_roll(100))<51) S(0x732)=1; else S(0x732)=-1;
   SPAWN(821,static_cast<float>(C(0x104)*packet[0]+F(0xEC)),static_cast<float>(F(0xF0)+packet[1]),B(0x104),B(0x732),packet,3);
   ++S(0x730);
  }
  if(S(0x13E)==2 && I(0x144)>=40) { BLOCK(); return; }
  if(FRAME()) ACTION(0);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==1) { ADJUST(200,120); SCALE(50); }
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==4) ACTION(0);
  return;
 }
 case 546: {
  RESOLVE();
  if(S(0x13E)==1) {
   if(I(0x144)%7==0 && S(0x730)<8) {
    float packet[3]; packet[0]=static_cast<float>(static_cast<float>(mt19937_next_u32()%110)-60.0);
    packet[1]=static_cast<float>(static_cast<float>(mt19937_next_u32()%170)+10.0); packet[2]=0;
    if(static_cast<unsigned>(selector_random_roll(100))<51) S(0x732)=1; else S(0x732)=-1;
    SPAWN(821,static_cast<float>(C(0x104)*packet[0]+F(0xEC)),static_cast<float>(F(0xF0)+packet[1]),B(0x104),B(0x732),packet,3);
    ++S(0x730);
   }
   if(S(0x13E)==1 && I(0x144)>=60) { BLOCK(); F(0xF4)=0; return; }
  }
  if(FRAME()) ACTION(0);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==1) { F(0xF4)=5; ADJUST(200,120); SCALE(50); }
  return;
 }
 case 547: {
  if(S(0x13E)==4) RESOLVE();
  if((S(0x13E)==1 || S(0x13E)==2) && I(0x144)%7==0 && S(0x730)<7) {
   float packet[3]; packet[0]=static_cast<float>(static_cast<float>(mt19937_next_u32()%110)-60.0);
   packet[1]=static_cast<float>(static_cast<float>(mt19937_next_u32()%170)+10.0); packet[2]=0;
   if(static_cast<unsigned>(selector_random_roll(100))<51) S(0x732)=1; else S(0x732)=-1;
   SPAWN(821,static_cast<float>(C(0x104)*packet[0]+F(0xEC)),static_cast<float>(F(0xF0)+packet[1]),B(0x104),B(0x732),packet,3);
   ++S(0x730);
  }
  short const sequence=S(0x13E);
  if(sequence==2 && I(0x144)>=30) { BLOCK(); return; }
  if(sequence<=2) F(0xF8)-=D(0.1f);
  if(S(0x13E)==3) { F(0xF8)-=F(0x100); if(CROSSED()) { ZERO(); F(0xF0)=GROUND(); BLOCK(); return; } }
  if(FRAME()) ACTION(0);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==1) { ADJUST(200,120); SCALE(50); }
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==4) ACTION(9);
  return;
 }
 case 548: {
  if(S(0x13E)==4) RESOLVE();
  if((S(0x13E)==1 || S(0x13E)==2) && I(0x144)%7==0 && S(0x730)<11) {
   float packet[3]; packet[0]=static_cast<float>(static_cast<float>(mt19937_next_u32()%110)-60.0);
   packet[1]=static_cast<float>(static_cast<float>(mt19937_next_u32()%170)+10.0); packet[2]=0;
   if(static_cast<unsigned>(selector_random_roll(100))<51) S(0x732)=1; else S(0x732)=-1;
   SPAWN(821,static_cast<float>(C(0x104)*packet[0]+F(0xEC)),static_cast<float>(F(0xF0)+packet[1]),B(0x104),B(0x732),packet,3);
   ++S(0x730);
  }
  short const sequence=S(0x13E);
  if(sequence==2 && I(0x144)>=50) { BLOCK(); return; }
  if(sequence<=2) F(0xF8)-=D(0.1f);
  if(S(0x13E)==3) { F(0xF8)-=F(0x100); if(CROSSED()) { ZERO(); F(0xF0)=GROUND(); BLOCK(); return; } }
  if(FRAME()) ACTION(0);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==1) { ADJUST(200,120); SCALE(50); }
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==4) ACTION(9);
  return;
 }
 case 560:
  RESOLVE();
  if((S(0x13E)==1 && I(0x144)>=10) || (S(0x13E)==2 && I(0x144)>=10)) { BLOCK(); return; }
  if(FRAME()) ACTION(0);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==1) { WAVE(3); ADJUST(200,120); I(0x180)=1; SCALE(50); }
  return;
 case 565:
  RESOLVE();
  if(S(0x13E)==1 && I(0x144)>=13) BLOCK();
  if(S(0x13E)==2 && I(0x144)>=19) BLOCK();
  if(FRAME()) ACTION(0);
  if(S(0x13E)==0 && S(0x142)==0 && S(0x140)==6) { WAVE(3); I(0x180)=1; ADJUST(200,120); SCALE(50); }
  return;
 case 566:
  RESOLVE();
  if(S(0x13E)==0 && I(0x144)==1) B(0x7D0)=0;
  if(S(0x13E)==1 && I(0x144)>=13) BLOCK();
  if(S(0x13E)==2 && I(0x144)>=34) BLOCK();
  if(FRAME()) ACTION(0);
  if(S(0x13E)==0 && S(0x142)==0 && S(0x140)==6) { WAVE(3); I(0x180)=1; ADJUST(200,120); SCALE(50); }
  return;
 case 568:
  RESOLVE(); if(FRAME()) ACTION(0);
  if(S(0x142)==0 && S(0x140)==8) {
   WAVE(3); ADJUST(200,45); I(0x180)=1; SCALE(50);
   ++S(0x7A4); if(S(0x7A4)>=3) S(0x7A4)=3;
   float packet[3]; packet[0]=0; packet[1]=0; packet[2]=S(0x7A4);
   SPAWN(830,static_cast<float>(F(0xEC)+0.0),static_cast<float>(F(0xF0)+120.0),B(0x104),255,packet,3);
  }
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==4) ACTION(0);
  return;
 case 570: {
  RESOLVE(); if(S(0x13E)==2 && I(0x144)>=18) { BLOCK(); return; }
  if(FRAME()) ACTION(0);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==1) {
   WAVE(13); ADJUST(200,120); I(0x180)=1; SCALE(50);
   float packet[4]; short const index=S(0x7A6);
   // Native count is four; this arm has no store to packet[3].
   packet[0]=0;
   if(index>=1) packet[0]=-atan2_degrees(static_cast<float>(F(0x7BC+index*4)-F(0xF0)-115.0),static_cast<float>((F(0x7AC+index*4)-F(0xEC)-13*C(0x104))*C(0x104)));
   packet[1]=30; packet[2]=3; if(C(0x60F)<4) packet[2]=0;
   SPAWN(827,static_cast<float>(13*C(0x104)+F(0xEC)),static_cast<float>(F(0xF0)+115.0),B(0x104),255,packet,4);
   packet[0]=0; packet[1]=0; packet[2]=2;
   SPAWN(827,static_cast<float>(13*C(0x104)+F(0xEC)),static_cast<float>(F(0xF0)+115.0),B(0x104),255,packet,4);
  }
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==4) ACTION(0);
  return;
 }
 case 571: {
  RESOLVE(); if(S(0x13E)==2 && I(0x144)>=18) { BLOCK(); return; }
  if(FRAME()) ACTION(0);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==1) {
   WAVE(13); ADJUST(200,120); I(0x180)=1; SCALE(50);
   float packet[4]; short const index=S(0x7A6);
   // As in570, the fourth transmitted word is not assigned by this arm.
   packet[0]=0;
   if(index>=1) packet[0]=-atan2_degrees(static_cast<float>(F(0x7BC+index*4)-F(0xF0)-115.0),static_cast<float>((F(0x7AC+index*4)-F(0xEC)-13*C(0x104))*C(0x104)));
   packet[1]=30; packet[2]=5; if(C(0x60F)>3) packet[2]=6;
   SPAWN(827,static_cast<float>(13*C(0x104)+F(0xEC)),static_cast<float>(F(0xF0)+115.0),B(0x104),255,packet,4);
   packet[0]=0; packet[1]=0; packet[2]=2;
   SPAWN(827,static_cast<float>(13*C(0x104)+F(0xEC)),static_cast<float>(F(0xF0)+115.0),B(0x104),255,packet,4);
  }
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==4) ACTION(0);
  return;
 }
 case 600: {
  RESOLVE(); publish_texture_state(3,2);
  if(S(0x13E)==1 && I(0x144)>=39) { BLOCK(); return; }
  if(FRAME()) ACTION(0);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==1) {
   S(0x48A)=40; EVENT(23);
   EFFECT(115,static_cast<float>(F(0xEC)-34*C(0x104)),static_cast<float>(F(0xF0)+114.0),B(0x104),1);
   dispatch_indexed_sequence_window_45c8b0(0,1,60); advance_secondary_event_effect_cycle();
  }
  if(S(0x13E)==2 && S(0x140)==2 && S(0x142)==0) {
   WAVE(20); float packet[3]={0,0,0};
   SPAWN(850,static_cast<float>(125*C(0x104)+F(0xEC)),static_cast<float>(F(0xF0)+120.0),B(0x104),1,packet,3);
  }
  return;
 }
 case 603: {
  RESOLVE(); publish_texture_state(3,2);
  if(S(0x13E)==1 && I(0x144)>=39) { BLOCK(); return; }
  if(FRAME()) ACTION(0);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==1) {
   S(0x48A)=40; EVENT(23);
   EFFECT(115,static_cast<float>(F(0xEC)-34*C(0x104)),static_cast<float>(F(0xF0)+114.0),B(0x104),1);
   dispatch_indexed_sequence_window_45c8b0(0,3,60); advance_secondary_event_effect_cycle();
  }
  if(S(0x13E)==2 && S(0x140)==2 && S(0x142)==0) {
   WAVE(24); float packet[3]={0,0,0};
   SPAWN(853,static_cast<float>(125*C(0x104)+F(0xEC)),static_cast<float>(F(0xF0)+120.0),B(0x104),1,packet,3);
  }
  return;
 }
 case 601: {
  RESOLVE(); publish_texture_state(3,2);
  if(S(0x13E)==1 && I(0x144)>=39) { BLOCK(); return; }
  if(FRAME()) ACTION(0);
  if(S(0x142)==0 && S(0x140)==2) {
   S(0x48A)=40; EVENT(23);
   EFFECT(115,static_cast<float>(F(0xEC)-44*C(0x104)),static_cast<float>(F(0xF0)+100.0),B(0x104),1);
   dispatch_indexed_sequence_window_45c8b0(0,2,60); advance_secondary_event_effect_cycle();
  }
  if(S(0x142)==0 && S(0x140)==6) {
   WAVE(22);
   for(int n=0;n<360;n+=60) {
    float packet[4]; packet[0]=0; packet[1]=0; packet[2]=0; packet[3]=static_cast<float>(n);
    SPAWN(851,static_cast<float>(32*C(0x104)+F(0xEC)),static_cast<float>(F(0xF0)+104.0),B(0x104),255,packet,4);
   }
  }
  return;
 }
 case 604: {
  RESOLVE(); publish_texture_state(3,2);
  if(S(0x13E)==1 && I(0x144)>=39) { BLOCK(); return; }
  if(FRAME()) ACTION(0);
  if(S(0x142)==0 && S(0x140)==2) {
   S(0x48A)=40; EVENT(23);
   EFFECT(115,static_cast<float>(F(0xEC)-44*C(0x104)),static_cast<float>(F(0xF0)+100.0),B(0x104),1);
   dispatch_indexed_sequence_window_45c8b0(0,4,60); advance_secondary_event_effect_cycle();
  }
  if(S(0x142)==0 && S(0x140)==6) {
   WAVE(26);
   for(int n=0;n<720;n+=60) {
    float packet[4]; packet[0]=0; packet[1]=0; packet[2]=0; packet[3]=static_cast<float>(n);
    SPAWN(854,static_cast<float>(32*C(0x104)+F(0xEC)),static_cast<float>(F(0xF0)+104.0),B(0x104),255,packet,4);
   }
  }
  return;
 }
 case 602: {
  RESOLVE(); publish_texture_state(3,2);
  if(S(0x13E)==1 && I(0x144)>=61) BLOCK();
  if(S(0x13E)==2 && I(0x144)>=19) BLOCK();
  if(FRAME()) ACTION(0);
  if(S(0x13E)!=0) return;
  if(S(0x142)==0 && S(0x140)==3) {
   S(0x48A)=40; EVENT(23);
   EFFECT(115,static_cast<float>(F(0xEC)-60*C(0x104)),static_cast<float>(F(0xF0)+147.0),B(0x104),1);
   dispatch_indexed_sequence_window_45c8b0(0,2,60); advance_secondary_event_effect_cycle();
  }
  if(S(0x142)==0 && S(0x140)==4) {
   float packet[3]={0,0,0};
   SPAWN(852,static_cast<float>(F(0xEC)-50*C(0x104)),static_cast<float>(F(0xF0)+184.0),B(0x104),255,packet,3);
  }
  return;
 }
 case 605: {
  RESOLVE(); publish_texture_state(3,2);
  if(S(0x13E)==1 && I(0x144)>=81) BLOCK();
  if(S(0x13E)==2 && I(0x144)>=19) BLOCK();
  if(FRAME()) ACTION(0);
  if(S(0x13E)!=0) return;
  if(S(0x142)==0 && S(0x140)==3) {
   S(0x48A)=40; EVENT(23);
   EFFECT(115,static_cast<float>(F(0xEC)-60*C(0x104)),static_cast<float>(F(0xF0)+147.0),B(0x104),1);
   dispatch_indexed_sequence_window_45c8b0(0,4,60); advance_secondary_event_effect_cycle();
  }
  if(S(0x142)==0 && S(0x140)==4) {
   for(int n=0;n<6;++n) {
    float packet[4]; packet[0]=0; packet[1]=0; packet[2]=0; packet[3]=static_cast<float>(n);
    SPAWN(855,static_cast<float>(F(0xEC)-50*C(0x104)),static_cast<float>(F(0xF0)+184.0),B(0x104),255,packet,4);
   }
  }
  return;
 }
 case 606: {
  RESOLVE(); publish_texture_state(3,2);
  if(S(0x13E)==1) {
   if(I(0x144)%2==0 && S(0x730)<8) {
    WAVE(28);
    float packet[4]; packet[0]=static_cast<float>((S(0x730)%4)*6-60.0); packet[1]=S(0x730)*3.0+20.0;
    packet[2]=0; packet[3]=S(0x730);
    SPAWN(856,F(0xEC),static_cast<float>(F(0xF0)+110.0),B(0x104),255,packet,4); ++S(0x730);
   }
   if(I(0x144)>=20) BLOCK();
  }
  if(FRAME()) ACTION(0);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==1) WAVE(28);
  if(S(0x13E)==0 && S(0x142)==0 && S(0x140)==3) {
   S(0x48A)=40; EVENT(23);
   EFFECT(115,static_cast<float>(F(0xEC)-60*C(0x104)),static_cast<float>(F(0xF0)+147.0),B(0x104),1);
   dispatch_indexed_sequence_window_45c8b0(0,2,60); advance_secondary_event_effect_cycle();
  }
  return;
 }
 case 607: {
  RESOLVE(); publish_texture_state(3,2); if(FRAME()) ACTION(0);
  if(S(0x142)==0 && S(0x140)==4) {
   S(0x48A)=40; EVENT(23);
   EFFECT(115,static_cast<float>(F(0xEC)-63*C(0x104)),static_cast<float>(F(0xF0)+150.0),B(0x104),1);
   dispatch_indexed_sequence_window_45c8b0(0,4,60); advance_secondary_event_effect_cycle();
  }
  if(S(0x142)==0 && S(0x140)==9) {
   WAVE(5); float packet[3]={-30,30,0};
   SPAWN(857,static_cast<float>(20*C(0x104)+F(0xEC)),static_cast<float>(F(0xF0)+110.0),B(0x104),1,packet,3);
  }
  return;
 }
 case 608: {
  RESOLVE(); publish_texture_state(3,2);
  if(S(0x13E)==1 && (I(0x144)>=481 || I(0x6C8)!=0)) { BLOCK(); return; }
  if(FRAME()) ACTION(0);
  if(S(0x13E)==0 && S(0x142)==0 && S(0x140)==3) {
   S(0x48A)=40; EVENT(23);
   EFFECT(115,static_cast<float>(F(0xEC)-60*C(0x104)),static_cast<float>(F(0xF0)+147.0),B(0x104),1);
   dispatch_indexed_sequence_window_45c8b0(0,3,60); advance_secondary_event_effect_cycle();
  }
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==1) {
   float packet[3]={0,0,1};
   SPAWN(858,static_cast<float>(30*C(0x104)+F(0xEC)),static_cast<float>(F(0xF0)+130.0),B(0x104),1,packet,3);
  }
  return;
 }
 case 609:
  RESOLVE(); publish_texture_state(3,2); if(FRAME()) ACTION(0);
  if(S(0x13E)==0) {
   if(S(0x142)==0 && S(0x140)==2) {
    S(0x48A)=40; EVENT(23);
    EFFECT(115,static_cast<float>(13*C(0x104)+F(0xEC)),static_cast<float>(F(0xF0)+110.0),B(0x104),1);
    dispatch_indexed_sequence_window_45c8b0(0,2,60); advance_secondary_event_effect_cycle();
   }
   S(0x4A8)=6; S(0x4AC)=6;
  }
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==1) WAVE(35);
  publish_texture_state(3,2); publish_texture_state(3,2);
  if(S(0x13E)==2 && I(0x144)>=24) BLOCK();
  return;
 case 710: {
  RESOLVE();
  if(S(0x13E)==0 && S(0x140)==3 && I(0x144)%8==0 && S(0x730)>0) {
   float packet[3]; packet[0]=-100.0-static_cast<float>(static_cast<unsigned>(selector_random_roll(60)));
   packet[1]=static_cast<float>(static_cast<unsigned>(selector_random_roll(30)))+15.0; packet[2]=0;
   SPAWN(900,static_cast<float>(F(0xEC)-20*C(0x104)),static_cast<float>(F(0xF0)+105.0),B(0x104),255,packet,3);
   WAVE(31); --S(0x730);
  }
  if(S(0x13E)==1 && I(0x144)>=120) { BLOCK(); return; }
  if(FRAME()) ACTION(700);
  if(S(0x13E)==0 && S(0x142)==0 && S(0x140)==2) {
   switch(g_match_identifier) { case 0: S(0x730)=9; break; case 1: S(0x730)=11; break; case 2: S(0x730)=13; break; case 3: S(0x730)=15; break; }
  }
  return;
 }
 case 711: {
  if(S(0x13E)==0 || S(0x13E)==3) RESOLVE();
  if(S(0x13E)==2 && I(0x144)%8==0 && S(0x730)>0) {
   float packet[3]; packet[0]=-80.0-static_cast<float>(static_cast<unsigned>(selector_random_roll(60)));
   packet[1]=static_cast<float>(static_cast<unsigned>(selector_random_roll(30)))+15.0; packet[2]=0;
   SPAWN(900,static_cast<float>(F(0xEC)-45*C(0x104)),static_cast<float>(F(0xF0)+108.0),B(0x104),255,packet,3);
   WAVE(31); --S(0x730);
  }
  if(S(0x13E)==1 || S(0x13E)==2) {
   F(0xF8)-=F(0x100);
   if(S(0x730)>0) {
    if(F(0xF8)<-1.0f) F(0xF8)=-1;
    F(0xF4)+=D(0.2f); if(F(0xF4)>-1.0f) F(0xF4)=-1;
   }
   if(CROSSED()) { F(0xF0)=GROUND(); ZERO(); SEQUENCE(3); return; }
  }
  if(FRAME()) ACTION(0);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==1) {
   F(0xF4)=-7.5f; F(0xF8)=16.5f; F(0x100)=0.5f;
   switch(g_match_identifier) { case 0: S(0x730)=9; break; case 1: S(0x730)=11; break; case 2: S(0x730)=13; break; case 3: S(0x730)=15; break; }
  }
  return;
 }
 case 720:
  RESOLVE(); if(S(0x13E)==1 && I(0x144)>=120) { BLOCK(); return; }
  if(FRAME()) ACTION(700);
  if(I(0x144)!=0 || S(0x142)!=0 || S(0x140)!=0 || S(0x13E)!=1) return;
  F(0x73C)=static_cast<float>(static_cast<unsigned>(selector_random_roll(30)));
  switch(g_match_identifier) {
  case 0:
   for(float n=0;n<4;n+=1.0) {
    float packet[4]; packet[0]=n*90.0+F(0x73C); packet[1]=15; packet[2]=0; packet[3]=0;
    SPAWN(901,F(0xEC),static_cast<float>(F(0xF0)+105.0),B(0x104),255,packet,4); WAVE(32);
   }
   return;
  case 1:
   for(float n=0;n<6;n+=1.0) {
    float packet[4]; packet[0]=n*60.0+F(0x73C); packet[1]=15; packet[2]=0; packet[3]=0;
    SPAWN(901,F(0xEC),static_cast<float>(F(0xF0)+105.0),B(0x104),255,packet,4); WAVE(32);
   }
   return;
  case 2:
   for(float n=0;n<9;n+=1.0) {
    float packet[4]; packet[0]=n*40.0+F(0x73C); packet[1]=15; packet[2]=0; packet[3]=0;
    SPAWN(901,F(0xEC),static_cast<float>(F(0xF0)+105.0),B(0x104),255,packet,4); WAVE(32);
   }
   return;
  case 3:
   for(float n=0;n<12;n+=1.0) {
    float packet[4]; packet[0]=n*30.0+F(0x73C); packet[1]=15; packet[2]=0; packet[3]=0;
    SPAWN(901,F(0xEC),static_cast<float>(F(0xF0)+105.0),B(0x104),255,packet,4); WAVE(32);
   }
   return;
  default: return;
  }
 case 721:
  RESOLVE(); if(FRAME()) ACTION(700);
  if(S(0x142)!=0 || S(0x140)!=8) return;
  F(0x73C)=-atan2_degrees(static_cast<float>(AT(AT(this,void *,0x170),float,0xF0)+100.0-F(0xF0)),static_cast<float>(C(0x104)*(AT(AT(this,void *,0x170),float,0xEC)-F(0xEC))));
  switch(g_match_identifier) {
  case 0:
   for(float n=0;n<1;n+=1.0) {
    float packet[4]; packet[0]=F(0x73C); packet[1]=n*3.0+15.0; packet[2]=0; packet[3]=1;
    SPAWN(901,F(0xEC),static_cast<float>(F(0xF0)+110.0),B(0x104),255,packet,4); WAVE(32);
   }
   return;
  case 1:
   for(float n=0;n<2;n+=1.0) {
    float packet[4]; packet[0]=10.0*n+F(0x73C); packet[1]=n*3.0+15.0; packet[2]=0; packet[3]=1;
    SPAWN(901,F(0xEC),static_cast<float>(F(0xF0)+110.0),B(0x104),255,packet,4); WAVE(32);
   }
   return;
  case 2:
   for(float n=0;n<3;n+=1.0) {
    float packet[4]; packet[0]=n*10.0+(F(0x73C)-10.0); packet[1]=n*3.0+15.0; packet[2]=0; packet[3]=1;
    SPAWN(901,F(0xEC),static_cast<float>(F(0xF0)+110.0),B(0x104),255,packet,4); WAVE(32);
   }
   return;
  case 3:
   for(float n=0;n<4;n+=1.0) {
    float packet[4]; packet[0]=(F(0x73C)-15.0)+10.0*n; packet[1]=n*3.0+15.0; packet[2]=0; packet[3]=1;
    SPAWN(901,F(0xEC),static_cast<float>(F(0xF0)+110.0),B(0x104),255,packet,4); WAVE(32);
   }
   return;
  default: return;
  }
 case 730: {
  if(S(0x13E)==0 || S(0x13E)==7) RESOLVE();
  if(S(0x13E)==4 && I(0x144)>=210) { BLOCK(); F(0x100)=0.2f; }
  short const sequence=S(0x13E);
  if(sequence==1 || sequence==2 || sequence==3) {
   F(0xF8)-=F(0x100);
   if(CROSSED()) { SEQUENCE(7); ZERO(); F(0xF0)=GROUND(); return; }
  }
  if(S(0x13E)==5 || S(0x13E)==6) {
   F(0xF8)-=F(0x100);
   if(CROSSED()) { SEQUENCE(7); ZERO(); F(0xF0)=GROUND(); return; }
  }
  if(FRAME()) ACTION(700);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==1) {
   F(0xF4)=5; F(0xF8)=static_cast<float>(static_cast<unsigned>(selector_random_roll(35)))*D(0.1f)+11.5; F(0x100)=0.3f;
  }
  if(I(0x144)!=0 || S(0x142)!=0 || S(0x140)!=0 || S(0x13E)!=4) return;
  ZERO();
  float const heading=static_cast<float>(static_cast<unsigned>(selector_random_roll(360)));
  WAVE(33);
  switch(g_match_identifier) {
  case 0:
   for(float n=0;n<3;n+=1.0) {
    float packet[3]; packet[0]=n*120.0+heading; packet[1]=20; packet[2]=0;
    SPAWN(902,F(0xEC),static_cast<float>(F(0xF0)+110.0),S(0x76A)==4?1:-1,255,packet,3);
   }
   return;
  case 1:
   for(float n=0;n<4;n+=1.0) {
    float packet[3]; packet[0]=n*90.0+heading; packet[1]=20; packet[2]=0;
    SPAWN(902,F(0xEC),static_cast<float>(F(0xF0)+110.0),S(0x76A)==4?1:-1,255,packet,3);
   }
   return;
  case 2:
   for(float n=0;n<5;n+=1.0) {
    float packet[3]; packet[0]=n*72.0+heading; packet[1]=20; packet[2]=0;
    SPAWN(902,F(0xEC),static_cast<float>(F(0xF0)+110.0),S(0x76A)==4?1:-1,255,packet,3);
   }
   return;
  case 3:
   for(float n=0;n<6;n+=1.0) {
    float packet[3]; packet[0]=n*60.0+heading; packet[1]=20; packet[2]=0;
    SPAWN(902,F(0xEC),static_cast<float>(F(0xF0)+110.0),S(0x76A)==4?1:-1,255,packet,3);
   }
   return;
  default: return;
  }
 }
 case 770:
  if(FRAME()) ACTION(700);
  if(S(0x13E)!=0 || S(0x142)!=0 || S(0x140)!=6) return;
  B(0x655)=1; finalize_sequence_entry(-1); publish_texture_state(3,-1); copy_action_word_176_to_174();
  S(0x76C)=0; S(0x76A)=1; S(0x766)=0; S(0x768)=0; S(0x764)=0; EVENT(23); return;
 case 795:
  if(S(0x13E)==0) {
   F(0xF8)-=D(0.3f);
   if(CROSSED()) { EVENT(30); SEQUENCE(1); F(0xF0)=GROUND(); ZERO(); return; }
  }
  if(FRAME()) ACTION(700);
  return;
 case 797:
  if(S(0x13E)<3) {
   F(0xF8)-=F(0x100);
   if(CROSSED()) { EVENT(30); SEQUENCE(3); F(0xF0)=GROUND(); F(0xF8)=0; return; }
  }
  if(S(0x13E)==3) {
   F(0xF4)-=0.75;
   if(F(0xF4)<0.0f) { F(0xF4)=0; F(0xEC)=480; }
   if(F(0xEC)>480.0) F(0xEC)=480;
  }
  if(FRAME()) ACTION(0);
  return;
 case 798:
  if(S(0x13E)<3) {
   F(0xF8)-=F(0x100);
   if(CROSSED()) { EVENT(30); SEQUENCE(3); F(0xF0)=GROUND(); F(0xF8)=0; return; }
  }
  if(S(0x13E)==3) {
   F(0xF4)-=0.75;
   if(F(0xF4)<0.0f) { F(0xF4)=0; F(0xEC)=800; }
   if(F(0xEC)<800.0) F(0xEC)=800;
  }
  if(FRAME()) ACTION(700);
  return;
 default: update_common_action_state(); return;
 }
}
#undef AT
#undef F
#undef S
#undef U
#undef I
#undef W
#undef B
#undef C
#undef D
#undef RESOLVE
#undef FRAME
#undef ZERO
#undef CROSSED
#undef GROUND
#undef ACTION
#undef SEQUENCE
#undef BLOCK
#undef GATE
#undef EVENT
#undef WAVE
#undef ADJUST
#undef SCALE
#undef EFFECT
#undef SPAWN
} // namespace th105
