#include <stddef.h>

namespace th105 {

int __cdecl selector_random_roll(int limit);
unsigned int __cdecl mt19937_next_u32(void);
float __cdecl lookup_orientation_sine_quantized_abs(float phase);
float __cdecl lookup_orientation_cosine_quantized_abs(float phase);

class YoumuActionStateView;
float __fastcall stage_surface_height_at_x(YoumuActionStateView *fighter);
int __fastcall is_y_at_or_below_stage_surface(void *fighter);

struct FighterActionScratchView { void reset(); void set_oriented_components_f0_f4(float, float); };

// Target-pinned Fighter prefix and sequence slots +8/+0C/+14/+1C.
// The opponent uses the same accessed layout; offsets below are checked by VC8.
class YoumuActionStateView {
public:
    virtual void scalar_delete_slot_00();
    virtual int set_action_sequence_and_finalize(short, int);
    virtual int set_action_and_finalize(short);
    virtual int select_sequence(int);
    virtual int reset_sequence();
    virtual unsigned char next_sequence_block();
    virtual int previous_sequence_block();
    virtual int set_sequence_frame(short);

    unsigned char resolve_stage_surface_landing_transition();
    unsigned char advance_frame_and_dispatch();
    int has_crossed_stage_surface_while_descending();
    void zero_velocity_acceleration();
    void set_oriented_components_f0_f4(float angle, float magnitude);
    void emit_fighter_effect_433cc0(int effect_code, float x, float y, unsigned char direction, int trailing_value);
    void publish_battle_layout_scalar(float value);
    void dispatch_indexed_event_member(unsigned index);
    void dispatch_character_wave_handle(unsigned index);
    void finalize_sequence_entry(int outcome);
    void dispatch_indexed_sequence_window_45c8b0(signed char relative_index, int outcome, int source_token);
    int configure_render_history(int countdown, signed char period, int color_mask);
    void publish_texture_state(signed char texture_index, short duration);
    int spawn_owned_object_via_manager(int object_id, float x, float y, signed char direction, signed char field_33c, const void *payload, int payload_count);
    void adjust_counter_482(short amount, int floor_value);
    void advance_secondary_event_effect_cycle();
    int add_phase_scaled_counter_558(int value);
    void face_opponent_and_flip_horizontal_velocity();
    unsigned char try_dispatch_directional_action_208_210(int option);
    void copy_action_word_176_to_174();
    void update_common_action_state();

    __forceinline void opening_brake(double amount, bool clear_motion) {
        if (velocity_x_f4 > 0.0f) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - amount);
            if (velocity_x_f4 < 0.0f) {
                if (clear_motion) zero_velocity_acceleration();
                else velocity_x_f4 = 0.0f;
                if (clear_motion) byte_47e = 0;
            }
        }
        // Keep this second independent test after the first possible store/call.
        if (velocity_x_f4 < 0.0f) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 + amount);
            if (velocity_x_f4 > 0.0f) {
                if (clear_motion) zero_velocity_acceleration();
                else velocity_x_f4 = 0.0f;
                if (clear_motion) byte_47e = 0;
            }
        }
    }

    __forceinline bool sequence_entry(short sequence) {
        return time_counter_144 == 0 && frame_timer_142 == 0
        && frame_index_140 == 0 && sequence_index_13e == sequence;
    }
    void dispatch_action_state_vslot28();

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
    unsigned char pad_110[0xc];
    float field_11c;
    float field_120;
    unsigned char pad_124[0x8];
    float field_12c;
    unsigned char pad_130[0xc];
    short action_id_13c;
    short sequence_index_13e;
    short frame_index_140;
    short frame_timer_142;
    int time_counter_144;
    unsigned char pad_148[0x28];
    YoumuActionStateView * related_170;
    short word_174;
    unsigned char pad_176[0x6];
    unsigned char byte_17c;
    unsigned char pad_17d[0x3];
    int field_180;
    signed char byte_184;
    unsigned char pad_185[0x1];
    short word_186;
    unsigned char pad_188[4];
    float field_18c;
    float field_190;
    unsigned char pad_194[0x2ea];
    unsigned char byte_47e;
    unsigned char byte_47f;
    unsigned char pad_480[0x2];
    short word_482;
    unsigned char pad_484[0x6];
    short word_48a;
    short word_48c;
    unsigned char pad_48e[0x1a];
    short word_4a8;
    unsigned char pad_4aa[0x2];
    short word_4ac;
    short word_4ae;
    unsigned char pad_4b0[0x8];
    int field_4b8;
    unsigned char pad_4bc[0x14];
    float field_4d0;
    unsigned char pad_4d4[0x134];
    signed char byte_608;
    unsigned char pad_609[0x4c];
    unsigned char byte_655;
    unsigned char pad_656[0x5e];
    int field_6b4;
    int field_6b8;
    unsigned int field_6bc;
    unsigned int field_6c0;
    unsigned int field_6c4;
    int field_6c8;
    unsigned char pad_6cc[0x60];
    unsigned char byte_72c;
    unsigned char pad_72d[0x3];
    short word_730;
    short word_732;
    short word_734;
    short word_736;
    unsigned char pad_738[0x4];
    float field_73c;
    float field_740;
    unsigned char pad_744[0xc];
    unsigned char byte_750;
    unsigned char pad_751[0x13];
    short word_764;
    short word_766;
    short word_768;
    short word_76a;
    short word_76c;
    unsigned char pad_76e[0x32];
    short word_7a0;
    short word_7a2;
    unsigned char pad_7a4[0x29];
    unsigned char byte_7cd;
    unsigned char pad_7ce[0x17];
    unsigned char byte_7e5;
    short word_7e6;
    short word_7e8;
    short word_7ea;
    short word_7ec;
};

#define YOUMU_OFFSET(type, member, offset) typedef char offset_##type##_##member[offsetof(type, member) == offset ? 1 : -1]
YOUMU_OFFSET(YoumuActionStateView, x_ec, 0xec);
YOUMU_OFFSET(YoumuActionStateView, y_f0, 0xf0);
YOUMU_OFFSET(YoumuActionStateView, velocity_x_f4, 0xf4);
YOUMU_OFFSET(YoumuActionStateView, velocity_y_f8, 0xf8);
YOUMU_OFFSET(YoumuActionStateView, acceleration_y_100, 0x100);
YOUMU_OFFSET(YoumuActionStateView, facing_104, 0x104);
YOUMU_OFFSET(YoumuActionStateView, field_108, 0x108);
YOUMU_OFFSET(YoumuActionStateView, field_10c, 0x10c);
YOUMU_OFFSET(YoumuActionStateView, field_11c, 0x11c);
YOUMU_OFFSET(YoumuActionStateView, field_120, 0x120);
YOUMU_OFFSET(YoumuActionStateView, field_12c, 0x12c);
YOUMU_OFFSET(YoumuActionStateView, action_id_13c, 0x13c);
YOUMU_OFFSET(YoumuActionStateView, sequence_index_13e, 0x13e);
YOUMU_OFFSET(YoumuActionStateView, frame_index_140, 0x140);
YOUMU_OFFSET(YoumuActionStateView, frame_timer_142, 0x142);
YOUMU_OFFSET(YoumuActionStateView, time_counter_144, 0x144);
YOUMU_OFFSET(YoumuActionStateView, related_170, 0x170);
YOUMU_OFFSET(YoumuActionStateView, word_174, 0x174);
YOUMU_OFFSET(YoumuActionStateView, byte_17c, 0x17c);
YOUMU_OFFSET(YoumuActionStateView, field_180, 0x180);
YOUMU_OFFSET(YoumuActionStateView, byte_184, 0x184);
YOUMU_OFFSET(YoumuActionStateView, word_186, 0x186);
YOUMU_OFFSET(YoumuActionStateView, field_18c, 0x18c);
YOUMU_OFFSET(YoumuActionStateView, field_190, 0x190);
YOUMU_OFFSET(YoumuActionStateView, word_48c, 0x48c);
YOUMU_OFFSET(YoumuActionStateView, byte_47e, 0x47e);
YOUMU_OFFSET(YoumuActionStateView, byte_47f, 0x47f);
YOUMU_OFFSET(YoumuActionStateView, word_482, 0x482);
YOUMU_OFFSET(YoumuActionStateView, word_48a, 0x48a);
YOUMU_OFFSET(YoumuActionStateView, word_4a8, 0x4a8);
YOUMU_OFFSET(YoumuActionStateView, word_4ac, 0x4ac);
YOUMU_OFFSET(YoumuActionStateView, word_4ae, 0x4ae);
YOUMU_OFFSET(YoumuActionStateView, field_4b8, 0x4b8);
YOUMU_OFFSET(YoumuActionStateView, field_4d0, 0x4d0);
YOUMU_OFFSET(YoumuActionStateView, byte_608, 0x608);
YOUMU_OFFSET(YoumuActionStateView, byte_655, 0x655);
YOUMU_OFFSET(YoumuActionStateView, field_6b4, 0x6b4);
YOUMU_OFFSET(YoumuActionStateView, field_6b8, 0x6b8);
YOUMU_OFFSET(YoumuActionStateView, field_6bc, 0x6bc);
YOUMU_OFFSET(YoumuActionStateView, field_6c0, 0x6c0);
YOUMU_OFFSET(YoumuActionStateView, field_6c4, 0x6c4);
YOUMU_OFFSET(YoumuActionStateView, field_6c8, 0x6c8);
YOUMU_OFFSET(YoumuActionStateView, byte_72c, 0x72c);
YOUMU_OFFSET(YoumuActionStateView, word_730, 0x730);
YOUMU_OFFSET(YoumuActionStateView, word_732, 0x732);
YOUMU_OFFSET(YoumuActionStateView, word_734, 0x734);
YOUMU_OFFSET(YoumuActionStateView, word_736, 0x736);
YOUMU_OFFSET(YoumuActionStateView, field_73c, 0x73c);
YOUMU_OFFSET(YoumuActionStateView, field_740, 0x740);
YOUMU_OFFSET(YoumuActionStateView, byte_750, 0x750);
YOUMU_OFFSET(YoumuActionStateView, word_764, 0x764);
YOUMU_OFFSET(YoumuActionStateView, word_766, 0x766);
YOUMU_OFFSET(YoumuActionStateView, word_768, 0x768);
YOUMU_OFFSET(YoumuActionStateView, word_76a, 0x76a);
YOUMU_OFFSET(YoumuActionStateView, word_76c, 0x76c);
YOUMU_OFFSET(YoumuActionStateView, word_7a0, 0x7a0);
YOUMU_OFFSET(YoumuActionStateView, word_7a2, 0x7a2);
YOUMU_OFFSET(YoumuActionStateView, byte_7cd, 0x7cd);
YOUMU_OFFSET(YoumuActionStateView, byte_7e5, 0x7e5);
YOUMU_OFFSET(YoumuActionStateView, word_7e6, 0x7e6);
YOUMU_OFFSET(YoumuActionStateView, word_7e8, 0x7e8);
YOUMU_OFFSET(YoumuActionStateView, word_7ea, 0x7ea);
YOUMU_OFFSET(YoumuActionStateView, word_7ec, 0x7ec);

extern int g_match_identifier;

void YoumuActionStateView::dispatch_action_state_vslot28()
{
    unsigned char *raw = reinterpret_cast<unsigned char *>(this);
    short v2;
    int v5;
    float v17; // target loads/stores single-precision field values
    int v59;
    int v63;
    int v67;
    int v68;
    int v69;
    int v70;
    int v71;
    int v73;
    double v76;
    double v77;
    int v80;
    int v85;
    int v95;
    int v101;
    int v102;
    int v104;
    int v110;
    short v114;
    int v116;
    short v120;
    short v121;
    short v122;
    short v123;
    short v124;
    short v125;
    short v126;
    short v127;
    int v129;
    int v134;
    int v135;
    int v141;
    float v147;
    float v148;
    float v153;
    float v154;
    float v155;
    float v156;
    float v157;
    float v158;
    float v159;
    float v160;
    float v161;
    float v168;
    float v173;
    int v174;
    int v175;
    int v176;
    int v177;
    int v182;
    int v185;
    float v187;
    float v190;
    float v194;
    float v197;
    float v199;
    float v200;
    float v201;
    float v202;
    float v204;
    float v205;
    float v208;
    int v211;
    int v214;
    int v216;
    int v219;
    int v222;
    int *v224;
    int *v225;
    int v226;
    float v237;
    float v238;
    float v242;
    float v243;
    float v247;
    float v248;
    float v251;
    float v252;
    float v269;
    float v270;
    float v274;
    float v275;
    float v279;
    float v280;
    float v283;
    float v284;
    float v291;
    float v297;
    float v311;
    float v313;
    float v315;
    float v317;
    float v319;
    float v323;
    float v325;
    float v326;
    float v327;
    float v329;
    float v331;
    float v334;
    float v335;
    float v336;
    float v337;
    float v338;
    float v339;
    float v340;
    float v341;
    float v342;
    float v343;
    float v344;
    float v345;
    float v348;
    float v350;
    float v352;
    float v353;
    float v358;
    float v359;
    float v360;
    float v365;
    float v366;
    float v380;
    float v381;
    float v382;
    float v383;
    float v386;
    float v387;
    float v389;
    float v390;
    float v399;
    float v402;
    float v403;
    float v404;
    float v405;
    float v406;
    float v410;
    float v411;
    float v412;
    float v414;
    float v415;
    float v416;
    float v417;
    float v418;
    float v425;
    float v428;
    float v429;
    float v431;
    float v432;
    double v441;
    double v443;
    float payload_444[3]; // target contiguous three-float object-853 payload
    float payload_446[3]; // target contiguous +54/+58/+5C BYREF
    float payload_455[3]; // target contiguous +78/+7C/+80 BYREF
    float v458[3];
    float v459[3];
    float v461;
    int v462;
    float payload_463[3]; // target contiguous +B0/+B4/+B8 BYREF
    float payload_465[3]; // target contiguous +BC/+C0/+C4 BYREF
    float v467[3];
    float v468[3];
    float v469[3];
    float v470[3];
    float v471[3];
    float v472[3];
    float v473[3];
    float v474[3];
    float v475[3];
    float v476[3];
    float v477[3];
    float v478[3];
    float v479[3];
    float v480[3];
    float v481[3];
    float v482[3];
    float v483[3];
    float v484[3];
    float v485[3];
    float v486[3];
    float v487[3];
    float v488[3];
    float v489[3];
    float v490[4];
    float v491[4];
    float v492[5];
    float v493[5];
    float v494[5];
    float v495[5];
    float v496[5];

    word_7a0 = 0;
    word_7a2 = 90;
    v2 = word_7e8;
    if (v2 >= 1)
        word_7e8 = v2 - 1;
    if (word_7ea > 0)
    {
        if (word_7ec > 0)
            field_4d0 = 0.0;
        --word_7ea;
        if (word_174 <= 0 || related_170->word_174 <= 0)
            word_7ea = 0;
        if (action_id_13c >= 600)
        {
            if (action_id_13c <= 699)
            {
                if (action_id_13c == 602 || action_id_13c == 605)
                {
                    if (!sequence_index_13e)
                        word_7ea = 0;
                }
                else
                {
                    word_7ea = 0;
                }
            }
        }
    }
    else
    {
        word_7ec = 0;
    }
    if (word_186 || related_170->word_48c) return;
    v5 = action_id_13c;
    switch (v5)
    {
    case 0:
        resolve_stage_surface_landing_transition();
        if (velocity_x_f4 == 0.0f) byte_47e = 0;
        if (!byte_47e) zero_velocity_acceleration();
        else opening_brake(0.5, true);
        break;
    case 1:
        resolve_stage_surface_landing_transition();
        if (!byte_47e) zero_velocity_acceleration();
        else opening_brake(0.5, true);
        if (advance_frame_and_dispatch() && frame_index_140 == 0) set_action_and_finalize(2);
        return;
    case 2:
        resolve_stage_surface_landing_transition();
        if (!byte_47e) zero_velocity_acceleration();
        else opening_brake(0.5, true);
        break;
    case 3:
        resolve_stage_surface_landing_transition();
        if (!byte_47e) zero_velocity_acceleration();
        else opening_brake(0.5, true);
        if (advance_frame_and_dispatch() && frame_index_140 == 0) set_action_and_finalize(0);
        return;
    case 4:
        resolve_stage_surface_landing_transition();
        velocity_x_f4 = 4.0;
        break;
    case 5:
        resolve_stage_surface_landing_transition();
        velocity_x_f4 = -4.0;
        break;
    case 6:
        if ( !sequence_index_13e )
        {
            resolve_stage_surface_landing_transition();
            if ( !sequence_index_13e && !byte_47e )
                zero_velocity_acceleration();
        }
        if ( sequence_index_13e > 0 )
        {
            velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
            if ( (unsigned char)has_crossed_stage_surface_while_descending() )
            {
                set_action_and_finalize(10);
                y_f0 = stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                return;
            }
        }
        advance_frame_and_dispatch();
        if ( time_counter_144 || frame_timer_142 || frame_index_140 || sequence_index_13e != 1 )
            return;
        velocity_x_f4 = 0.0f;
        velocity_y_f8 = 16.0;
        acceleration_y_100 = 0.8f;
        byte_47e = 0;
        return;
    case 7:
        if ( !sequence_index_13e )
        {
            resolve_stage_surface_landing_transition();
            if ( !sequence_index_13e && !byte_47e )
                zero_velocity_acceleration();
        }
        if ( sequence_index_13e > 0 )
        {
            velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
            if ( (unsigned char)has_crossed_stage_surface_while_descending() )
            {
                set_action_and_finalize(10);
                y_f0 = stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                return;
            }
        }
        advance_frame_and_dispatch();
        if ( time_counter_144 || frame_timer_142 || frame_index_140 || sequence_index_13e != 1 )
            return;
        velocity_x_f4 = 6.5f;
        velocity_y_f8 = 16.0;
        acceleration_y_100 = 0.8f;
        byte_47e = 0;
        return;
    case 8:
        if ( !sequence_index_13e )
        {
            resolve_stage_surface_landing_transition();
            if ( !sequence_index_13e && !byte_47e )
                zero_velocity_acceleration();
        }
        if ( sequence_index_13e > 0 )
        {
            velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
            if ( (unsigned char)has_crossed_stage_surface_while_descending() )
            {
                set_action_and_finalize(10);
                y_f0 = stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                return;
            }
        }
        advance_frame_and_dispatch();
        if ( time_counter_144 || frame_timer_142 || frame_index_140 || sequence_index_13e != 1 )
            return;
        velocity_x_f4 = -6.5f;
        velocity_y_f8 = 16.0;
        acceleration_y_100 = 0.8f;
        byte_47e = 0;
        return;
    case 9:
        if ( !acceleration_y_100 )
            acceleration_y_100 = 0.60000002;
        velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
        if ( (unsigned char)has_crossed_stage_surface_while_descending() )
        {
            set_action_and_finalize(10);
            y_f0 = stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        break;
    case 10:
        resolve_stage_surface_landing_transition();
        zero_velocity_acceleration();
        if ( (unsigned char)advance_frame_and_dispatch() )
        {
            if ( !field_6b8 )
                set_action_and_finalize(0);
            else
                set_action_and_finalize(2);
        }
        return;
    case 197:
        if ( !sequence_index_13e || sequence_index_13e == 3 )
            resolve_stage_surface_landing_transition();
        if ( sequence_index_13e < 3 )
        {
            velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
            if ( (unsigned char)has_crossed_stage_surface_while_descending() )
            {
                y_f0 = stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                select_sequence(3);
                return;
            }
        }
        if ( !(unsigned char)advance_frame_and_dispatch() )
            goto LABEL_117;
        if ( byte_72c == 2 )
        {
            set_action_and_finalize(700);
            word_4a8 = 3;
            word_4ac = 3;
            return;
        }
        set_action_and_finalize(0);
        if ( field_6b8 > 0 )
            set_action_and_finalize(1);
    LABEL_117:
        if ( sequence_index_13e == 3 && frame_index_140 == 2 && !frame_timer_142 )
        {
            if ( x_ec > (double)related_170->x_ec )
                facing_104 = -1;
            if ( x_ec < (double)related_170->x_ec )
                facing_104 = 1;
        }
        if ( time_counter_144
            || frame_timer_142
            || frame_index_140
            || sequence_index_13e != 1 )
        {
            return;
        }
        velocity_y_f8 = 8.0;
        v17 = 13.5f;
        velocity_x_f4 = v17;
        acceleration_y_100 = 0.5;
        return;
    case 198:
        if ( !sequence_index_13e || sequence_index_13e == 3 )
            resolve_stage_surface_landing_transition();
        if ( sequence_index_13e < 3 )
        {
            velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
            if ( (unsigned char)has_crossed_stage_surface_while_descending() )
            {
                y_f0 = stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                select_sequence(3);
                return;
            }
        }
        if ( !(unsigned char)advance_frame_and_dispatch() )
            goto LABEL_140;
        if ( byte_72c == 2 )
        {
            set_action_and_finalize(700);
            word_4a8 = 3;
            word_4ac = 3;
            return;
        }
        else
        {
            set_action_and_finalize(0);
            if ( field_6b8 > 0 )
                set_action_and_finalize(1);
        LABEL_140:
            if ( sequence_index_13e == 3 && frame_index_140 == 2 && !frame_timer_142 )
            {
                if ( x_ec > (double)related_170->x_ec )
                    facing_104 = -1;
                if ( x_ec < (double)related_170->x_ec )
                    facing_104 = 1;
            }
            if ( sequence_entry(1) )
            {
                velocity_y_f8 = 8.0;
                v17 = -13.5f;
                velocity_x_f4 = v17;
                acceleration_y_100 = 0.5;
            }
        }
        return;
    case 199:
        resolve_stage_surface_landing_transition();
        if ( !(unsigned char)advance_frame_and_dispatch() )
            goto LABEL_156;
        if ( byte_72c == 2 )
        {
            set_action_and_finalize(700);
            word_4a8 = 3;
            word_4ac = 3;
        }
        else
        {
            set_action_and_finalize(0);
            if ( field_6b8 > 0 )
                set_action_and_finalize(1);
        LABEL_156:
            if ( !sequence_index_13e && frame_index_140 == 6 && !frame_timer_142 )
            {
                if ( x_ec > (double)related_170->x_ec )
                    facing_104 = -1;
                if ( x_ec < (double)related_170->x_ec )
                    facing_104 = 1;
            }
        }
        return;
    case 200:
        resolve_stage_surface_landing_transition();
        byte_47e = 1;
        configure_render_history(3, 4, 16776960);
        advance_frame_and_dispatch();
        if ( sequence_index_13e != 1 )
            goto LABEL_174;
        if ( !(time_counter_144 % 5) )
        {
            emit_fighter_effect_433cc0(
                124,
                (x_ec + 50.0) - (float)(mt19937_next_u32() % 0x64),
                (float)(mt19937_next_u32() % 0xC8) + y_f0,
                (unsigned char)facing_104,
                1);
        }
        if ( field_6b8 < 0 )
        {
            if ( field_6b4 * facing_104 > 0 )
                set_action_and_finalize(212);
            else
                set_action_and_finalize(211);
            return;
        }
        ++word_730;
        if ((field_6b4 * facing_104 <= 0 && word_730 > 5) || word_730 > 60)
        {
            set_action_and_finalize(204);
            return;
        }
    LABEL_174:
        if ( sequence_entry(1) )
        {
            velocity_x_f4 = 15.0;
            v211 = (unsigned char)facing_104;
            v187 = y_f0 + 80.0;
            v237 = (double)(30 * (char)v211) + x_ec;
            emit_fighter_effect_433cc0(125, v237, v187, v211, 1);
            v238 = y_f0 + 80.0;
            emit_fighter_effect_433cc0(126, x_ec, v238, facing_104, 1);
            dispatch_indexed_event_member(0x1Fu);
        }
        return;
    case 201:
        resolve_stage_surface_landing_transition();
        velocity_x_f4 = velocity_x_f4 + 1.75;
        if ( velocity_x_f4 > 0.0 )
            velocity_x_f4 = 0.0;
        if ( !(time_counter_144 % 5) )
        {
            emit_fighter_effect_433cc0(124,
                (x_ec + 50.0) - (float)(mt19937_next_u32() % 100U),
                (float)(mt19937_next_u32() % 200U) + y_f0,
                (unsigned char)-facing_104, 1);
        }
        if ( (unsigned char)advance_frame_and_dispatch() )
        {
            set_action_and_finalize(0);
            velocity_x_f4 = 0.0;
            return;
        }
        if ( !frame_timer_142 && frame_index_140 == 1 )
        {
            velocity_x_f4 = -25.0;
            v242 = y_f0 + 80.0;
            emit_fighter_effect_433cc0(125, x_ec, v242, (unsigned char)-(unsigned char)facing_104, 1);
            v243 = y_f0 + 80.0;
            emit_fighter_effect_433cc0(126, x_ec, v243, (unsigned char)-(unsigned char)facing_104, 1);
            dispatch_indexed_event_member(0x1Fu);
        }
        return;
    case 202:
        velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
        if ( (unsigned char)has_crossed_stage_surface_while_descending() )
        {
            zero_velocity_acceleration();
            y_f0 = stage_surface_height_at_x(this);
            set_action_and_finalize(10);
            return;
        }
        if ( (sequence_index_13e == 1 || sequence_index_13e == 2) && !(time_counter_144 % 5) )
        {
            emit_fighter_effect_433cc0(
                124,
                (x_ec + 50.0) - (float)(mt19937_next_u32() % 0x64),
                (float)(mt19937_next_u32() % 0xC8) + y_f0,
                (unsigned char)facing_104,
                1);
        }
        advance_frame_and_dispatch();
        if ( !sequence_index_13e && !frame_timer_142 && frame_index_140 == 1 )
        {
            velocity_x_f4 = 10.0;
            velocity_y_f8 = 5.0;
            acceleration_y_100 = 0.5;
            v214 = (unsigned char)facing_104;
            v190 = y_f0 + 110.0;
            v247 = (double)(80 * (char)v214) + x_ec;
            emit_fighter_effect_433cc0(125, v247, v190, v214, 1);
            v248 = y_f0 + 110.0;
            emit_fighter_effect_433cc0(126, x_ec, v248, facing_104, 1);
            dispatch_indexed_event_member(0x1Fu);
        }
        if ( sequence_entry(2) )
        {
            face_opponent_and_flip_horizontal_velocity();
        }
        return;
    case 203:
        velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
        if ( (unsigned char)has_crossed_stage_surface_while_descending() )
        {
            zero_velocity_acceleration();
            y_f0 = stage_surface_height_at_x(this);
            set_action_and_finalize(10);
            return;
        }
        if ( sequence_index_13e < 3 && !(time_counter_144 % 5) )
        {
            emit_fighter_effect_433cc0(
                124,
                (x_ec + 50.0) - (float)(mt19937_next_u32() % 0x64),
                (float)(mt19937_next_u32() % 0xC8) + y_f0,
                (unsigned char)-(unsigned char)facing_104,
                1);
        }
        advance_frame_and_dispatch();
        if ( !time_counter_144 )
        {
            if ( !frame_timer_142 && !frame_index_140 && sequence_index_13e == 1 )
            {
                velocity_x_f4 = -10.0;
                velocity_y_f8 = 5.0;
                acceleration_y_100 = 0.5;
                v251 = y_f0 + 120.0;
                emit_fighter_effect_433cc0(125, x_ec, v251, (unsigned char)-(unsigned char)facing_104, 1);
                v252 = y_f0 + 120.0;
                emit_fighter_effect_433cc0(126, x_ec, v252, (unsigned char)-(unsigned char)facing_104, 1);
                dispatch_indexed_event_member(0x1Fu);
            }
            if ( sequence_entry(2) )
            {
                face_opponent_and_flip_horizontal_velocity();
            }
        }
        return;
    case 204:
        resolve_stage_surface_landing_transition();
        velocity_x_f4 = velocity_x_f4 - 0.75;
        if ( velocity_x_f4 < 0.0 )
        {
            velocity_x_f4 = 0.0;
            byte_47e = 0;
        }
        if ( (unsigned char)advance_frame_and_dispatch() )
        {
            set_action_and_finalize(0);
            byte_47e = 0;
        }
        return;
    case 208:
        if ( !sequence_index_13e )
            resolve_stage_surface_landing_transition();
        if ( (unsigned char)has_crossed_stage_surface_while_descending() )
        {
            set_action_and_finalize(10);
            y_f0 = stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if ( (unsigned char)is_y_at_or_below_stage_surface(this) || velocity_y_f8 > 0.0 )
            word_4ae = 2;
        if ( sequence_index_13e > 0 )
        {
            velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
            if ( velocity_y_f8 < -20.0 )
                velocity_y_f8 = -20.0;
        }
        if ( sequence_index_13e == 1 && velocity_y_f8 < 4.0 )
            select_sequence(2);
        advance_frame_and_dispatch();
        if ( time_counter_144
            || frame_timer_142
            || frame_index_140
            || sequence_index_13e != 1 )
        {
            return;
        }
        velocity_x_f4 = 0.0f;
        velocity_y_f8 = 23.0f;
        acceleration_y_100 = 0.75f;
        byte_47e = 0;
        emit_fighter_effect_433cc0(63, x_ec, y_f0, facing_104, 1);
        return;
    case 209:
        if ( !sequence_index_13e )
            resolve_stage_surface_landing_transition();
        if ( (unsigned char)has_crossed_stage_surface_while_descending() )
        {
            set_action_and_finalize(10);
            y_f0 = stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if ( (unsigned char)is_y_at_or_below_stage_surface(this) || velocity_y_f8 > 0.0 )
            word_4ae = 2;
        if ( sequence_index_13e > 0 )
        {
            velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
            if ( velocity_y_f8 < -20.0 )
                velocity_y_f8 = -20.0;
        }
        if ( sequence_index_13e == 1 && velocity_y_f8 < 4.0 )
            select_sequence(2);
        advance_frame_and_dispatch();
        if ( time_counter_144
            || frame_timer_142
            || frame_index_140
            || sequence_index_13e != 1 )
        {
            return;
        }
        velocity_x_f4 = 11.0f;
        velocity_y_f8 = 17.5f;
        acceleration_y_100 = 0.8f;
        byte_47e = 0;
        emit_fighter_effect_433cc0(63, x_ec, y_f0, facing_104, 1);
        return;
    case 210:
        if ( !sequence_index_13e )
            resolve_stage_surface_landing_transition();
        if ( (unsigned char)has_crossed_stage_surface_while_descending() )
        {
            set_action_and_finalize(10);
            y_f0 = stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if ( (unsigned char)is_y_at_or_below_stage_surface(this) || velocity_y_f8 > 0.0 )
            word_4ae = 2;
        if ( sequence_index_13e > 0 )
        {
            velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
            if ( velocity_y_f8 < -20.0 )
                velocity_y_f8 = -20.0;
        }
        if ( sequence_index_13e == 1 && velocity_y_f8 < 4.0 )
            select_sequence(2);
        advance_frame_and_dispatch();
        if ( time_counter_144
            || frame_timer_142
            || frame_index_140
            || sequence_index_13e != 1 )
        {
            return;
        }
        velocity_x_f4 = -11.0f;
        {
            velocity_y_f8 = 17.5f;
            acceleration_y_100 = 0.8f;
            {
                byte_47e = 0;
                emit_fighter_effect_433cc0(63, x_ec, y_f0, facing_104, 1);
                return;
            }
        }
    case 211:
        if ( !sequence_index_13e )
            resolve_stage_surface_landing_transition();
        if ( (unsigned char)has_crossed_stage_surface_while_descending() )
        {
            set_action_and_finalize(10);
            y_f0 = stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if ( (unsigned char)is_y_at_or_below_stage_surface(this) || velocity_y_f8 > 0.0 )
            word_4ae = 2;
        if ( sequence_index_13e > 0 )
        {
            velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
            if ( velocity_y_f8 < -20.0 )
                velocity_y_f8 = -20.0;
        }
        if ( sequence_index_13e == 1 && velocity_y_f8 < 4.0 )
            select_sequence(2);
        advance_frame_and_dispatch();
        if ( time_counter_144
            || frame_timer_142
            || frame_index_140
            || sequence_index_13e != 1 )
        {
            return;
        }
        velocity_x_f4 = 3.0f;
        {
            velocity_y_f8 = 23.0f;
            acceleration_y_100 = 0.75f;
            {
                byte_47e = 0;
                emit_fighter_effect_433cc0(63, x_ec, y_f0, facing_104, 1);
                return;
            }
        }
    case 212:
    case 221:
        if ( !sequence_index_13e )
            resolve_stage_surface_landing_transition();
        if ( (unsigned char)has_crossed_stage_surface_while_descending() )
        {
            set_action_and_finalize(10);
            y_f0 = stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if ( (unsigned char)is_y_at_or_below_stage_surface(this) || velocity_y_f8 > 0.0 )
            word_4ae = 2;
        if ( sequence_index_13e > 0 )
        {
            velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
            if ( velocity_y_f8 < -20.0 )
                velocity_y_f8 = -20.0;
        }
        if ( sequence_index_13e == 1 && velocity_y_f8 < 4.0 )
            select_sequence(2);
        advance_frame_and_dispatch();
        if ( time_counter_144
            || frame_timer_142
            || frame_index_140
            || sequence_index_13e != 1 )
        {
            return;
        }
        velocity_x_f4 = 11.0f;
        velocity_y_f8 = 17.5f;
        acceleration_y_100 = 0.8f;
        {
            byte_47e = 0;
            emit_fighter_effect_433cc0(63, x_ec, y_f0, facing_104, 1);
            return;
        }
    case 214: {
            if (advance_frame_and_dispatch()) { set_action_and_finalize(9); return; }
            if (!time_counter_144) {
                if (!frame_timer_142 && !frame_index_140 && sequence_index_13e == 1)
                    dispatch_indexed_event_member(31);
                if (sequence_entry(6)) {
                    set_action_and_finalize(9); return;
                }
            }
            if (field_6b8 > 0) {
                if (facing_104 * field_6b4 > 0) word_732 = -45;
                else if (facing_104 * field_6b4 < 0) word_732 = -135;
                else word_732 = -90;
            } else if (field_6b8 < 0) {
                if (facing_104 * field_6b4 > 0) word_732 = 45;
                else if (facing_104 * field_6b4 < 0) word_732 = 135;
                else word_732 = 90;
            } else {
                if (facing_104 * field_6b4 > 0) word_732 = 0;
                else if (facing_104 * field_6b4 < 0) word_732 = 180;
            }
            if (sequence_index_13e == 5 || sequence_index_13e == 6)
                velocity_y_f8 -= acceleration_y_100;
            if (sequence_index_13e > 0 && sequence_index_13e < 5) {
                ++word_736;
                word_734 = static_cast<short>(word_732 - static_cast<short>(static_cast<int>(field_740)));
                if (word_734 > 180) word_734 -= 360;
                if (word_734 < -180) word_734 += 360;
                if (word_734 > 0) {
                    if (field_4b8 == 0) field_740 = static_cast<float>(field_740 + 1.0);
                    else field_740 = static_cast<float>(field_740 + 0.25);
                }
                if (word_734 < 0) {
                    if (field_4b8 == 0) field_740 = static_cast<float>(field_740 - 1.0);
                    else field_740 = static_cast<float>(field_740 - 0.25);
                }
                velocity_x_f4 = lookup_orientation_cosine_quantized_abs(field_740) * field_73c;
                velocity_y_f8 = lookup_orientation_sine_quantized_abs(field_740) * field_73c;
                if (y_f0 > 680.0 && velocity_y_f8 > 0.0) velocity_y_f8 = 0.0f;
                if (field_4b8 == 0) adjust_counter_482(6, 1);
                else adjust_counter_482(12, 1);
                field_12c = -field_740;
                if (velocity_x_f4 < 0.0) field_12c = 180.0 - field_740;
                if (velocity_x_f4 < 0.0 && sequence_index_13e == 1) select_sequence(3);
                if (velocity_x_f4 >= 0.0 && sequence_index_13e == 3) select_sequence(1);
                if (velocity_x_f4 < 0.0 && sequence_index_13e == 2) select_sequence(4);
                if (velocity_x_f4 >= 0.0 && sequence_index_13e == 4) select_sequence(2);
                if (time_counter_144 % 5 == 1) {
                    emit_fighter_effect_433cc0(125,
                        lookup_orientation_cosine_quantized_abs(field_740) * 100.0 * facing_104 + x_ec,
                        lookup_orientation_sine_quantized_abs(field_740) * 100.0 + y_f0 + 100.0,
                        facing_104, 1);
                }
                if ((field_6c8 == 0 && word_736 > 10) || word_482 <= 0) {
                    if ((field_6c8 == 0 && word_736 > 10) || word_482 <= 0) {
                        reinterpret_cast<FighterActionScratchView *>(raw + 4)->reset();
                        if (sequence_index_13e == 1 || sequence_index_13e == 2) {
                            if (facing_104 == 1) {
                                if (x_ec > related_170->x_ec) {
                                    facing_104 = -1;
                                    velocity_x_f4 = -velocity_x_f4;
                                    select_sequence(6);
                                } else select_sequence(5);
                            } else {
                                if (x_ec < related_170->x_ec) {
                                    facing_104 = -facing_104;
                                    velocity_x_f4 = -velocity_x_f4;
                                    select_sequence(6);
                                } else select_sequence(5);
                            }
                        }
                        if (sequence_index_13e == 3 || sequence_index_13e == 4) {
                            if (facing_104 == 1) {
                                if (x_ec > related_170->x_ec) {
                                    facing_104 = -1;
                                    velocity_x_f4 = -velocity_x_f4;
                                    select_sequence(5);
                                } else select_sequence(6);
                                return;
                            }
                            if (x_ec < related_170->x_ec) {
                                facing_104 = -facing_104;
                                velocity_x_f4 = -velocity_x_f4;
                                select_sequence(5);
                            } else select_sequence(6);
                        }
                        return;
                    }
                }
            }
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                y_f0 = stage_surface_height_at_x(this);
                acceleration_y_100 = 0.0f;
                velocity_y_f8 = 0.0f;
                if (sequence_index_13e < 5) {
                    reinterpret_cast<FighterActionScratchView *>(raw + 4)->reset();
                    set_action_and_finalize(215);
                } else {
                    set_action_and_finalize(10);
                    zero_velocity_acceleration();
                }
            }
            return;
        }
    case 215:
        resolve_stage_surface_landing_transition();
        if ( velocity_x_f4 > 0.0 )
        {
            velocity_x_f4 = velocity_x_f4 - 0.75;
            if ( velocity_x_f4 < 0.0 )
                velocity_x_f4 = 0.0;
        }
        if ( velocity_x_f4 < 0.0 )
        {
            velocity_x_f4 = velocity_x_f4 + 0.75;
            if ( velocity_x_f4 > 0.0 )
                velocity_x_f4 = 0.0;
        }
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        return;
    case 220:
        if ( !sequence_index_13e )
            resolve_stage_surface_landing_transition();
        if ( (unsigned char)has_crossed_stage_surface_while_descending() )
        {
        LABEL_99:
            set_action_and_finalize(10);
            {
                y_f0 = stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                return;
            }
        }
        if ( (unsigned char)is_y_at_or_below_stage_surface(this) || velocity_y_f8 > 0.0 )
            word_4ae = 2;
        if ( sequence_index_13e > 0 )
        {
            velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
            if ( velocity_y_f8 < -20.0 )
                velocity_y_f8 = -20.0;
        }
        if ( sequence_index_13e == 1 && velocity_y_f8 < 4.0 )
            select_sequence(2);
        advance_frame_and_dispatch();
        if ( sequence_entry(1) )
        {
            velocity_x_f4 = 0.0;
            velocity_y_f8 = 23.0;
            acceleration_y_100 = 0.75;
            byte_47e = 0;
            v216 = (unsigned char)facing_104;
            emit_fighter_effect_433cc0(63, x_ec, y_f0, v216, 1);
        }
        return;
    case 222:
        if ( !sequence_index_13e )
            resolve_stage_surface_landing_transition();
        if ( (unsigned char)has_crossed_stage_surface_while_descending() )
        {
            set_action_and_finalize(10);
            y_f0 = stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if ( (unsigned char)is_y_at_or_below_stage_surface(this) || velocity_y_f8 > 0.0 )
            word_4ae = 2;
        if ( sequence_index_13e > 0 )
        {
            velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
            if ( velocity_y_f8 < -20.0 )
                velocity_y_f8 = -20.0;
        }
        if ( sequence_index_13e == 1 && velocity_y_f8 < 4.0 )
            select_sequence(2);
        advance_frame_and_dispatch();
        if ( time_counter_144
            || frame_timer_142
            || frame_index_140
            || sequence_index_13e != 1 )
        {
            return;
        }
        velocity_x_f4 = -11.0f;
        {
            velocity_y_f8 = 17.5f;
            acceleration_y_100 = 0.8f;
            {
                byte_47e = 0;
                emit_fighter_effect_433cc0(63, x_ec, y_f0, facing_104, 1);
                return;
            }
        }
    case 223:
        resolve_stage_surface_landing_transition();
        byte_47e = 1;
        advance_frame_and_dispatch();
        if ( sequence_index_13e == 1 )
        {
            if ( !(time_counter_144 % 5) )
            {
                emit_fighter_effect_433cc0(
                    124,
                    (x_ec + 50.0) - (float)(mt19937_next_u32() % 0x64),
                    (float)(mt19937_next_u32() % 0xC8) + y_f0,
                    (unsigned char)facing_104,
                    1);
            }
            ++word_730;
            if ( (field_6b4 * facing_104 <= 0
                && word_730 > 15)
                || word_730 > 60 )
            {
                set_action_and_finalize(204);
                return;
            }
        }
        if ( sequence_entry(1) )
        {
            velocity_x_f4 = 7.5;
            v219 = (unsigned char)facing_104;
            v194 = y_f0 + 80.0;
            v269 = (double)(30 * (char)v219) + x_ec;
            emit_fighter_effect_433cc0(125, v269, v194, v219, 1);
            v270 = y_f0 + 80.0;
            emit_fighter_effect_433cc0(126, x_ec, v270, facing_104, 1);
            dispatch_indexed_event_member(0x1Fu);
        }
        return;
    case 224:
        if ( !sequence_index_13e || sequence_index_13e == 3 )
        {
            resolve_stage_surface_landing_transition();
        }
        if ( sequence_index_13e == 3 )
        {
            velocity_x_f4 = velocity_x_f4 + 2.0;
            if ( velocity_x_f4 > 0.0 )
                velocity_x_f4 = 0.0;
        }
        if ( !(unsigned char)is_y_at_or_below_stage_surface(this) && !(time_counter_144 % 5) )
        {
            emit_fighter_effect_433cc0(
                124,
                (x_ec + 50.0) - (float)(mt19937_next_u32() % 0x64),
                (float)(mt19937_next_u32() % 0xC8) + y_f0,
                (unsigned char)-(unsigned char)facing_104,
                1);
        }
        if ( sequence_index_13e < 3
            && (velocity_y_f8 = velocity_y_f8 - acceleration_y_100, (unsigned char)has_crossed_stage_surface_while_descending()) )
        {
            velocity_y_f8 = 0.0;
            acceleration_y_100 = 0.0;
            y_f0 = stage_surface_height_at_x(this);
            select_sequence(3);
        }
        else if ( (unsigned char)advance_frame_and_dispatch() )
        {
            set_action_and_finalize(0);
            velocity_x_f4 = 0.0;
        }
        else if ( sequence_entry(1) )
        {
            velocity_x_f4 = -15.0;
            velocity_y_f8 = 5.0;
            acceleration_y_100 = 0.75;
            v274 = y_f0 + 80.0;
            emit_fighter_effect_433cc0(125, x_ec, v274, (unsigned char)-(unsigned char)facing_104, 1);
            v275 = y_f0 + 80.0;
            emit_fighter_effect_433cc0(126, x_ec, v275, (unsigned char)-(unsigned char)facing_104, 1);
            dispatch_indexed_event_member(0x1Fu);
        }
        return;
    case 226:
        velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
        if ( (unsigned char)has_crossed_stage_surface_while_descending() )
        {
            zero_velocity_acceleration();
            y_f0 = stage_surface_height_at_x(this);
            set_action_and_finalize(10);
            return;
        }
        else
        {
            if ( (sequence_index_13e == 1 || sequence_index_13e == 2) && !(time_counter_144 % 5) )
            {
                emit_fighter_effect_433cc0(
                    124,
                    (x_ec + 50.0) - (float)(mt19937_next_u32() % 0x64),
                    (float)(mt19937_next_u32() % 0xC8) + y_f0,
                    (unsigned char)facing_104,
                    1);
            }
            if ( (unsigned char)advance_frame_and_dispatch() )
                set_action_and_finalize(9);
            if ( !sequence_index_13e && !frame_timer_142 && frame_index_140 == 1 )
            {
                word_730 = 0;
                velocity_x_f4 = 10.0;
                velocity_y_f8 = 5.0;
                acceleration_y_100 = 0.5;
                v222 = (unsigned char)facing_104;
                v197 = y_f0 + 110.0;
                v279 = (double)(80 * (char)v222) + x_ec;
                emit_fighter_effect_433cc0(125, v279, v197, v222, 1);
                v280 = y_f0 + 110.0;
                emit_fighter_effect_433cc0(126, x_ec, v280, facing_104, 1);
                dispatch_indexed_event_member(0x1Fu);
            }
            if ( sequence_entry(2) )
            {
                face_opponent_and_flip_horizontal_velocity();
            }
        }
        return;
    case 225:
        velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
        if ( !(unsigned char)has_crossed_stage_surface_while_descending() )
        {
            if ( sequence_index_13e < 3 && !(time_counter_144 % 5) )
            {
                emit_fighter_effect_433cc0(
                    124,
                    (x_ec + 50.0) - (float)(mt19937_next_u32() % 0x64),
                    (float)(mt19937_next_u32() % 0xC8) + y_f0,
                    (unsigned char)-(unsigned char)facing_104,
                    1);
            }
            if ( (unsigned char)advance_frame_and_dispatch() )
                set_action_and_finalize(9);
            if ( !time_counter_144 )
            {
                if ( !frame_timer_142 && !frame_index_140 && sequence_index_13e == 1 )
                {
                    velocity_x_f4 = -10.0;
                    velocity_y_f8 = 5.0;
                    acceleration_y_100 = 0.5;
                    v283 = y_f0 + 120.0;
                    emit_fighter_effect_433cc0(125, x_ec, v283, (unsigned char)-(unsigned char)facing_104, 1);
                    v284 = y_f0 + 120.0;
                    emit_fighter_effect_433cc0(126, x_ec, v284, (unsigned char)-(unsigned char)facing_104, 1);
                    dispatch_indexed_event_member(0x1Fu);
                }
                if ( sequence_entry(2) )
                {
                    face_opponent_and_flip_horizontal_velocity();
                }
            }
            return;
        }
        else
        {
            zero_velocity_acceleration();
            y_f0 = stage_surface_height_at_x(this);
            set_action_and_finalize(10);
            return;
        }
    case 300:
        resolve_stage_surface_landing_transition();
        if ( !(unsigned char)try_dispatch_directional_action_208_210(0) )
        {
            if ( byte_47e )
            {
                velocity_x_f4 = velocity_x_f4 - 0.5;
                if ( velocity_x_f4 < 0.0 )
                {
                    velocity_x_f4 = 0.0;
                    byte_47e = 0;
                }
            }
            if ( (unsigned char)advance_frame_and_dispatch() )
                set_action_and_finalize(0);
            if ( !frame_timer_142 && frame_index_140 == 2 )
            {
                dispatch_indexed_event_member(0x1Cu);
                byte_47e = 0;
            }
        }
        return;

    case 301:
        resolve_stage_surface_landing_transition();
        if ( (unsigned char)try_dispatch_directional_action_208_210(0) )
            return;
        if ( byte_47e )
        {
            velocity_x_f4 = velocity_x_f4 - 0.5;
            if ( velocity_x_f4 < 0.0 )
            {
                velocity_x_f4 = 0.0;
                byte_47e = 0;
            }
        }
        else
        {
        }
        if ( frame_index_140 >= 4 )
        {
            velocity_x_f4 = velocity_x_f4 - 1.5;
            if ( velocity_x_f4 < 0.0 )
                velocity_x_f4 = 0.0;
        }
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        if ( !frame_timer_142 && frame_index_140 == 4 )
            velocity_x_f4 = 5.0;
        if ( !frame_timer_142 && frame_index_140 == 3 )
        {
            velocity_x_f4 = 10.0;
            dispatch_indexed_event_member(0x1Bu);
            byte_47e = 0;
        }
        if ( frame_index_140 <= 3 )
            return;
        velocity_x_f4 = velocity_x_f4 - 1.0;
        if ( velocity_x_f4 < 0.0 )
            velocity_x_f4 = 0.0;
        return;
    case 302:
        resolve_stage_surface_landing_transition();
        if ( (unsigned char)try_dispatch_directional_action_208_210(1) )
            return;
        if ( !field_6bc )
            byte_750 = 0;
        if ( byte_47e )
        {
            velocity_x_f4 = velocity_x_f4 - 0.5;
            if ( velocity_x_f4 < 0.0 )
            {
                velocity_x_f4 = 0.0;
                byte_47e = 0;
            }
        }
        if (advance_frame_and_dispatch()) { set_action_and_finalize(0); return; }
        if (sequence_entry(1)) { set_action_and_finalize(0); return; }
        if ( !sequence_index_13e )
        {
            if ( !frame_timer_142 && frame_index_140 == 4 )
            {
                if ( byte_750 == 1 )
                {
                    next_sequence_block();
                    v59 = (unsigned char)facing_104;
                    v199 = y_f0 + 106.0;
                    v291 = (double)(70 * (char)v59) + x_ec;
                    emit_fighter_effect_433cc0(62, v291, v199, v59, 1);
                }
                else
                {
                    velocity_x_f4 = 20.0;
                    byte_47e = 0;
                }
            }
            if ( !frame_timer_142 && frame_index_140 == 5 )
            {
                dispatch_indexed_event_member(0x1Du);
                v475[0] = 0.0;
                v475[1] = 0.0;
                v475[2] = 0.0;
                spawn_owned_object_via_manager(848,
                    x_ec,
                    y_f0,
                    (unsigned char)facing_104,
                    1,
                    v475,
                    3);
            }
            if ( frame_index_140 >= 5 )
            {
                velocity_x_f4 = velocity_x_f4 - 2.0;
                if ( velocity_x_f4 < 0.0 )
                    velocity_x_f4 = 0.0;
            }
        }
        if ( sequence_index_13e != 1 )
            return;
        if ( !frame_timer_142 && frame_index_140 == 2 )
        {
            velocity_x_f4 = 30.0;
            byte_47e = 0;
            dispatch_indexed_event_member(0x1Du);
            v469[0] = 0.0;
            v469[1] = 0.0;
            v469[2] = 0.0;
            spawn_owned_object_via_manager(848,
                x_ec,
                y_f0,
                (unsigned char)facing_104,
                1,
                v469,
                3);
        }
        if ( frame_index_140 >= 2 )
        {
            velocity_x_f4 = velocity_x_f4 - 2.0;
            if ( velocity_x_f4 < 0.0 )
                velocity_x_f4 = 0.0;
        }
        return;
    case 303:
        resolve_stage_surface_landing_transition();
        if ( !(unsigned char)try_dispatch_directional_action_208_210(0) )
        {
            if ( (signed char)byte_47e > 0 )
            {
                velocity_x_f4 = velocity_x_f4 - 0.6000000238418579;
                if ( velocity_x_f4 < 0.0 )
                {
                    velocity_x_f4 = 0.0;
                    byte_47e = 0;
                }
            }
            if ( (unsigned char)advance_frame_and_dispatch() )
                set_action_and_finalize(2);
            if ( !frame_timer_142 && frame_index_140 == 1 )
                dispatch_indexed_event_member(0x1Cu);
        }
        return;
    case 304:
        resolve_stage_surface_landing_transition();
        if ( (unsigned char)try_dispatch_directional_action_208_210(1) )
            return;
        if ( !field_6bc )
            byte_750 = 0;
        if ( byte_47e )
        {
            velocity_x_f4 = velocity_x_f4 - 0.5;
            if ( velocity_x_f4 < 0.0 )
            {
                velocity_x_f4 = 0.0;
                byte_47e = 0;
            }
        }
        if ( (unsigned char)advance_frame_and_dispatch() )
        {
            set_action_and_finalize(0);
            return;
        }
        if ( sequence_entry(1) )
        {
            set_action_and_finalize(0);
            return;
        }
        if ( !sequence_index_13e )
        {
            if ( !frame_timer_142 && frame_index_140 == 5 )
            {
                if ( byte_750 == 1 )
                {
                    next_sequence_block();
                    v63 = (unsigned char)facing_104;
                    v200 = y_f0 + 118.0;
                    v297 = x_ec - 95 * (char)v63;
                    emit_fighter_effect_433cc0(62, v297, v200, v63, 1);
                }
                else
                {
                    velocity_x_f4 = 10.0;
                    byte_47e = 0;
                }
            }
            if ( !frame_timer_142 && frame_index_140 == 6 )
            {
                dispatch_indexed_event_member(0x1Du);
                v483[0] = 0.0;
                v483[1] = 0.0;
                v483[2] = 1.0;
                spawn_owned_object_via_manager(848,
                    x_ec,
                    y_f0,
                    (unsigned char)facing_104,
                    1,
                    v483,
                    3);
            }
            if ( frame_index_140 >= 5 )
            {
                velocity_x_f4 = velocity_x_f4 - 2.0;
                if ( velocity_x_f4 < 0.0 )
                    velocity_x_f4 = 0.0;
            }
        }
        if ( sequence_index_13e != 1 )
            return;
        if ( !frame_timer_142 && frame_index_140 == 1 )
        {
            velocity_x_f4 = 15.0;
            byte_47e = 0;
            dispatch_indexed_event_member(0x1Du);
        }
        if ( !frame_timer_142 && frame_index_140 == 2 )
        {
            v471[0] = 0.0;
            v471[1] = 0.0;
            v471[2] = 1.0;
            spawn_owned_object_via_manager(848,
                x_ec,
                y_f0,
                (unsigned char)facing_104,
                1,
                v471,
                3);
        }
        if ( frame_index_140 >= 2 )
        {
            velocity_x_f4 = velocity_x_f4 - 2.0;
            if ( velocity_x_f4 < 0.0 )
                velocity_x_f4 = 0.0;
        }
        return;
    case 305:
        resolve_stage_surface_landing_transition();
        if ( (unsigned char)try_dispatch_directional_action_208_210(1) )
            return;
        if ( !time_counter_144
            && !frame_timer_142
            && !frame_index_140
            && !sequence_index_13e )
        {
            velocity_y_f8 = 0.0;
            velocity_x_f4 = 12.5;
            acceleration_y_100 = 0.0;
            byte_47e = 0;
        }
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        if ( sequence_entry(1) )
        {
            {
                set_action_and_finalize(0);
                return;
            }
        }
        if ( sequence_index_13e )
            goto LABEL_636;
        if ( !frame_timer_142 && frame_index_140 == 3 )
            dispatch_indexed_event_member(0x1Cu);
        if ( frame_index_140 < 4 )
        {
        LABEL_636:
            ;
        }
        else
        {
            velocity_x_f4 = velocity_x_f4 - 1.0;
            if ( velocity_x_f4 < 0.0 )
                velocity_x_f4 = 0.0;
        }
        if ( sequence_index_13e == 1 )
        {
            velocity_x_f4 = velocity_x_f4 - 1.0;
            if ( velocity_x_f4 < 0.0 )
                velocity_x_f4 = 0.0;
            if ( !frame_timer_142 && frame_index_140 == 4 )
            {
                velocity_x_f4 = 20.0;
                dispatch_indexed_event_member(0x1Bu);
            }
        }
        return;
    case 306:
        velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
        if ( (unsigned char)has_crossed_stage_surface_while_descending() )
        {
            set_action_and_finalize(10);
            y_f0 = stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(9);
        if ( !frame_timer_142 && frame_index_140 == 3 )
            dispatch_indexed_event_member(0x1Bu);
        return;
    case 307:
        if ( sequence_index_13e == 1 )
        {
            resolve_stage_surface_landing_transition();
            velocity_x_f4 = velocity_x_f4 - 0.699999988079071;
            if ( velocity_x_f4 < 0.0 )
                velocity_x_f4 = 0.0;
        }
        if ( sequence_index_13e
            || (velocity_y_f8 = velocity_y_f8 - acceleration_y_100, !(unsigned char)has_crossed_stage_surface_while_descending()) )
        {
            if ( (unsigned char)advance_frame_and_dispatch() )
                set_action_and_finalize(0);
            if ( sequence_entry(1) )
            {
                set_action_and_finalize(9);
            }
            if ( !sequence_index_13e )
            {
                if ( frame_index_140 >= 3 && frame_index_140 <= 5 )
                {
                    reinterpret_cast<FighterActionScratchView *>(raw + 4)->set_oriented_components_f0_f4(15.0, field_73c);
                    field_73c = field_73c - 2.5;
                    if ( field_73c <= 2.0 )
                        field_73c = 2.0;
                }
                if ( !frame_timer_142 )
                {
                    if ( frame_index_140 == 3 )
                    {
                        dispatch_indexed_event_member(0x1Du);
                        field_73c = 30.0;
                    }
                    if ( !frame_timer_142 && frame_index_140 == 6 )
                        acceleration_y_100 = 0.40000001;
                }
            }
        }
        else
        {
            select_sequence(1);
            y_f0 = stage_surface_height_at_x(this);
            velocity_y_f8 = 0.0;
            acceleration_y_100 = 0.0;
            velocity_x_f4 = velocity_x_f4 * 0.5;
        }
        return;
    case 308:
        if ( !sequence_index_13e )
        {
            velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
            if ( (unsigned char)has_crossed_stage_surface_while_descending() )
            {
                set_action_and_finalize(10);
                {
                    y_f0 = stage_surface_height_at_x(this);
                    zero_velocity_acceleration();
                    return;
                }
            }
        }
        if ( sequence_index_13e == 1 && (unsigned char)has_crossed_stage_surface_while_descending() )
        {
            select_sequence(2);
            {
                y_f0 = stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                return;
            }
        }
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        if ( !sequence_index_13e && !frame_timer_142 && frame_index_140 == 4 )
        {
            dispatch_indexed_event_member(0x1Du);
            velocity_y_f8 = -40.0;
            velocity_x_f4 = 0.0;
        }
        return;
    case 309:
        velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
        if ( (unsigned char)has_crossed_stage_surface_while_descending() )
        {
            set_action_and_finalize(10);
            y_f0 = stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(9);
        if ( !frame_timer_142 && frame_index_140 == 3 )
        {
            dispatch_indexed_event_member(0x1Du);
            velocity_y_f8 = 16.0;
            velocity_x_f4 = 3.0;
            acceleration_y_100 = 0.75;
        }
        if ( sequence_index_13e == 1 && time_counter_144 >= 15 )
        {
            set_action_and_finalize(9);
            return;
        }
        return;
    case 310:
        if ( !time_counter_144
            && !frame_timer_142
            && !frame_index_140
            && !sequence_index_13e )
        {
            velocity_x_f4 = 0.0;
            velocity_y_f8 = 0.0;
            acceleration_y_100 = 0.5;
            word_730 = 0;
            byte_184 = 99;
            field_180 = 0;
        }
        if ( field_180 )
        {
            if ( (short)++word_730 > 5 )
            {
                field_180 = 0;
                word_730 = 0;
            }
        }
        if ( sequence_index_13e == 1 )
        {
            if ( !time_counter_144 )
                velocity_x_f4 = 17.5;
            if ( !(time_counter_144 % 8) )
                dispatch_indexed_event_member(0x1Bu);
            if ( field_180 )
            {
                if ( (short)++word_730 > 5 )
                {
                    field_180 = 0;
                    word_730 = 0;
                }
            }
            if ( time_counter_144 > 30 )
            {
                next_sequence_block();
                velocity_y_f8 = 6.0;
                velocity_x_f4 = velocity_x_f4 * 0.5;
            }
        }
        if ( sequence_index_13e == 2 )
        {
            velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
            v441 = velocity_y_f8 + y_f0;
            if ( stage_surface_height_at_x(this) >= v441 )
            {
                velocity_y_f8 = 0.0;
                y_f0 = stage_surface_height_at_x(this);
                set_action_and_finalize(9);
                return;
            }
        }
        if ( (unsigned char)advance_frame_and_dispatch() )
        {
            set_action_and_finalize(9);
            return;
        }
        return;
    case 311:
        resolve_stage_surface_landing_transition();
        if ( (unsigned char)try_dispatch_directional_action_208_210(0) )
            return;
        if ( (signed char)byte_47e > 0 )
        {
            velocity_x_f4 = velocity_x_f4 - 0.6000000238418579;
            if ( velocity_x_f4 < 0.0 )
            {
                velocity_x_f4 = 0.0;
                byte_47e = 0;
            }
        }
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(2);
        if ( !frame_timer_142 && frame_index_140 == 2 )
        {
            dispatch_indexed_event_member(0x1Du);
            velocity_x_f4 = 10.0;
        }
        if ( frame_index_140 >= 3 )
        {
            velocity_x_f4 = velocity_x_f4 - 2.0;
            if ( velocity_x_f4 < 0.0 )
                velocity_x_f4 = 0.0;
        }
        return;
    case 320:
        resolve_stage_surface_landing_transition();
        if ( (unsigned char)try_dispatch_directional_action_208_210(0) )
            return;
        if ( frame_index_140 > 1 )
        {
            velocity_x_f4 = velocity_x_f4 - 2.0;
            if ( velocity_x_f4 < 0.0 )
                velocity_x_f4 = 0.0;
        }
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        if ( !frame_timer_142 && frame_index_140 == 2 )
        {
            dispatch_indexed_event_member(0x1Cu);
            byte_47e = 0;
        }
        return;
    case 321:
        resolve_stage_surface_landing_transition();
        if ( !(unsigned char)try_dispatch_directional_action_208_210(1) )
        {
            if ( frame_index_140 > 3 )
            {
                velocity_x_f4 = velocity_x_f4 - 0.5;
                if ( velocity_x_f4 < 0.0 )
                    velocity_x_f4 = 0.0;
            }
            if ( (unsigned char)advance_frame_and_dispatch() )
                set_action_and_finalize(0);
            if ( !frame_timer_142 && frame_index_140 == 3 )
            {
                dispatch_indexed_event_member(0x1Cu);
                velocity_x_f4 = 7.5;
                byte_47e = 0;
            }
        }
        return;
    case 322:
        resolve_stage_surface_landing_transition();
        if ( !(unsigned char)try_dispatch_directional_action_208_210(1) )
        {
            if ( frame_index_140 > 5 )
            {
                velocity_x_f4 = velocity_x_f4 - 3.0;
                if ( velocity_x_f4 < 0.0 )
                    velocity_x_f4 = 0.0;
            }
            if ( (unsigned char)advance_frame_and_dispatch() )
                set_action_and_finalize(0);
            if ( !frame_timer_142 )
            {
                if ( frame_index_140 == 5 )
                    velocity_x_f4 = 15.0;
                if ( !frame_timer_142 && frame_index_140 == 6 )
                {
                    dispatch_indexed_event_member(0x1Du);
                    byte_47e = 0;
                }
            }
        }
        return;
    case 323:
        resolve_stage_surface_landing_transition();
        if ( (unsigned char)try_dispatch_directional_action_208_210(1) )
            return;
        if ( frame_index_140 > 3 )
        {
            velocity_x_f4 = velocity_x_f4 - 3.0;
            if ( velocity_x_f4 < 0.0 )
                velocity_x_f4 = 0.0;
        }
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        if ( frame_timer_142 )
            return;
        if ( frame_index_140 == 3 )
            velocity_x_f4 = 15.0;
        if ( frame_timer_142 || frame_index_140 != 2 )
            return;
        dispatch_indexed_event_member(0x1Du);
        byte_47e = 0;
        return;
    case 400:
        resolve_stage_surface_landing_transition();
        if ( sequence_index_13e < 2 && !field_6c0 )
            byte_750 = 0;
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        if ( time_counter_144 )
            goto LABEL_778;
        if ( frame_timer_142 )
            return;
        if ( !frame_index_140 && sequence_index_13e == 1 )
        {
            set_action_and_finalize(0);
            return;
        }
    LABEL_778:
        if ( !frame_timer_142 && frame_index_140 == 3 )
        {
            adjust_counter_482(200, 45);
            add_phase_scaled_counter_558(50);
            v495[0] = 35.0;
            v495[1] = 40.0;
            v495[2] = 0.0;
            v495[3] = 5.0;
            v495[4] = 0.0;
            v174 = (unsigned char)facing_104;
            v153 = y_f0 + 210.0;
            v311 = x_ec - 80 * (char)v174;
            spawn_owned_object_via_manager(800, v311, v153, v174, 1, v495, 5);
        }
        return;
    case 401:
        resolve_stage_surface_landing_transition();
        if ( sequence_index_13e < 2 && !field_6c0 )
            byte_750 = 0;
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        if ( time_counter_144 )
            goto LABEL_790;
        if ( frame_timer_142 )
            return;
        if ( !frame_index_140 && sequence_index_13e == 1 )
        {
            set_action_and_finalize(0);
            return;
        }
    LABEL_790:
        if ( !frame_timer_142 && frame_index_140 == 4 )
        {
            adjust_counter_482(200, 45);
            add_phase_scaled_counter_558(50);
            v492[0] = -35.0;
            v492[1] = 40.0;
            v492[2] = 0.0;
            v492[3] = 5.0;
            v492[4] = 0.0;
            v67 = (unsigned char)facing_104;
            v154 = y_f0 + 25.0;
            v313 = x_ec - 150 * (char)v67;
            spawn_owned_object_via_manager(800, v313, v154, v67, 1, v492, 5);
        }
        return;
    case 402:
        resolve_stage_surface_landing_transition();
        if ( sequence_index_13e < 2 && !field_6c0 )
            byte_750 = 0;
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(2);
        if ( time_counter_144 )
            goto LABEL_802;
        if ( frame_timer_142 )
            return;
        if ( !frame_index_140 && sequence_index_13e == 1 )
        {
            set_action_and_finalize(0);
            return;
        }
    LABEL_802:
        if ( !frame_timer_142 && frame_index_140 == 4 )
        {
            adjust_counter_482(200, 45);
            add_phase_scaled_counter_558(50);
            v493[0] = -120.0;
            v493[1] = 30.0;
            v493[2] = 0.0;
            v493[3] = 5.0;
            v493[4] = -25.0;
            v68 = (unsigned char)facing_104;
            v155 = y_f0 + 25.0;
            v315 = (double)(170 * (char)v68) + x_ec;
            spawn_owned_object_via_manager(800, v315, v155, v68, 1, v493, 5);
        }
        return;
    case 404:
        if ( sequence_index_13e == 1 )
            resolve_stage_surface_landing_transition();
        if ( !sequence_index_13e )
        {
            velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
            if ( (unsigned char)has_crossed_stage_surface_while_descending() )
            {
                next_sequence_block();
                byte_47f = 0;
                y_f0 = stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                return;
            }
        }
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        if ( sequence_entry(1) )
        {
            {
                set_action_and_finalize(9);
                return;
            }
        }
        if ( !sequence_index_13e && !frame_timer_142 && frame_index_140 == 4 )
        {
            adjust_counter_482(200, 45);
            add_phase_scaled_counter_558(50);
            v494[0] = 70.0;
            v494[1] = 30.0;
            v494[2] = 0.0;
            v494[3] = 5.0;
            v494[4] = 10.0;
            v69 = (unsigned char)facing_104;
            v156 = y_f0 + 225.0;
            v317 = x_ec - 45 * (char)v69;
            spawn_owned_object_via_manager(800, v317, v156, v69, 1, v494, 5);
        }
        return;
    case 406:
        if ( sequence_index_13e == 1 )
            resolve_stage_surface_landing_transition();
        if ( !sequence_index_13e )
        {
            velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
            if ( (unsigned char)has_crossed_stage_surface_while_descending() )
            {
                next_sequence_block();
                byte_47f = 0;
                {
                    y_f0 = stage_surface_height_at_x(this);
                    zero_velocity_acceleration();
                    return;
                }
            }
        }
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        if ( sequence_entry(1) )
        {
            {
                set_action_and_finalize(9);
                return;
            }
        }
        if ( !sequence_index_13e && !frame_timer_142 && frame_index_140 == 4 )
        {
            adjust_counter_482(200, 45);
            add_phase_scaled_counter_558(50);
            v496[0] = 70.0;
            v496[1] = 30.0;
            v496[2] = 0.0;
            v496[3] = 5.0;
            v496[4] = 60.0;
            v70 = (unsigned char)facing_104;
            v157 = y_f0 + 225.0;
            v319 = x_ec - 45 * (char)v70;
            spawn_owned_object_via_manager(800, v319, v157, v70, 1, v496, 5);
        }
        return;
    case 408:
        resolve_stage_surface_landing_transition();
        velocity_x_f4 = velocity_x_f4 - 0.75;
        if ( velocity_x_f4 < 0.0 )
            velocity_x_f4 = 0.0;
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        if ( !frame_timer_142 )
        {
            if ( frame_index_140 == 4 )
                velocity_x_f4 = 25.5;
            if ( !frame_timer_142 && frame_index_140 == 5 )
                dispatch_indexed_event_member(0x1Du);
        }
        return;
    case 409:
        velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
        if ( (unsigned char)has_crossed_stage_surface_while_descending() )
        {
            set_action_and_finalize(10);
            zero_velocity_acceleration();
            y_f0 = stage_surface_height_at_x(this);
            return;
        }
        if ( !(unsigned char)advance_frame_and_dispatch() )
            return;
        set_action_and_finalize(9);
        return;
    case 410:
        resolve_stage_surface_landing_transition();
        if ( sequence_index_13e == 2 && time_counter_144 >= 24 )
        { next_sequence_block(); return; }
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        if ( sequence_entry(1) )
        {
            add_phase_scaled_counter_558(50);
            byte_7e5 = 1;
            word_7e6 = 1;
            adjust_counter_482(200, 60);
        }
        return;
    case 411:
        resolve_stage_surface_landing_transition();
        if ( sequence_index_13e == 1 && time_counter_144 >= 15 )
        { next_sequence_block(); return; }
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        if ( !sequence_index_13e && !frame_timer_142 && frame_index_140 == 5 )
        {
            add_phase_scaled_counter_558(50);
            byte_7e5 = 1;
            word_7e6 = 2;
            adjust_counter_482(200, 60);
        }
        return;
    case 412:
        resolve_stage_surface_landing_transition();
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        if ( !sequence_index_13e && !frame_timer_142 && frame_index_140 == 5 )
        {
            add_phase_scaled_counter_558(50);
            byte_7e5 = 1;
            word_7e6 = 3;
            adjust_counter_482(200, 60);
        }
        return;
    case 414:
        v71 = 4;
        if ( sequence_index_13e == v71 )
            resolve_stage_surface_landing_transition();
        if ( sequence_index_13e < v71 )
        {
            velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
            if ( (unsigned char)has_crossed_stage_surface_while_descending() )
            {
                select_sequence(v71);
                byte_47f = 0;
                y_f0 = stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                return;
            }
        }
        if ( sequence_index_13e < 2 && !field_6c4 )
            byte_750 = 0;
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        if ( sequence_entry(1) )
        {
            add_phase_scaled_counter_558(50);
            byte_7e5 = 1;
            word_7e6 = 1;
            adjust_counter_482(200, 60);
        }
        v73 = time_counter_144;
        if ( v73 || frame_timer_142 || frame_index_140 || sequence_index_13e != 4 )
        {
            if ( sequence_index_13e == 2 && v73 >= 24 )
            {
                next_sequence_block();
                acceleration_y_100 = 0.60000002;
            }
            return;
        }
        {
            set_action_and_finalize(9);
            return;
        }
    case 415:
        v71 = 3;
        if ( sequence_index_13e == 3 )
            resolve_stage_surface_landing_transition();
        if ( sequence_index_13e == 1 && time_counter_144 >= 15 )
        {
            acceleration_y_100 = 0.60000002;
            { next_sequence_block(); return; }
        }
        if ( sequence_index_13e < 3 )
        {
            velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
            if ( (unsigned char)has_crossed_stage_surface_while_descending() )
            {
                select_sequence(v71);
                byte_47f = 0;
                {
                    y_f0 = stage_surface_height_at_x(this);
                    zero_velocity_acceleration();
                    return;
                }
            }
        }
        if ( sequence_index_13e < 2 && !field_6c4 )
            byte_750 = 0;
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        if ( !sequence_index_13e && !frame_timer_142 && frame_index_140 == 4 )
        {
            add_phase_scaled_counter_558(50);
            byte_7e5 = 1;
            word_7e6 = 2;
            adjust_counter_482(200, 60);
        }
        if ( time_counter_144
            || frame_timer_142
            || frame_index_140
            || sequence_index_13e != 3 )
        {
            return;
        }
        {
            set_action_and_finalize(9);
            return;
        }
    case 416:
        v71 = 4;
        if ( sequence_index_13e == v71 )
            resolve_stage_surface_landing_transition();
        if ( sequence_index_13e < v71 )
        {
            velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
            if ( (unsigned char)has_crossed_stage_surface_while_descending() )
            {
                select_sequence(v71);
                byte_47f = 0;
                y_f0 = stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                return;
            }
        }
        if ( sequence_index_13e < 2 && !field_6c4 )
            byte_750 = 0;
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        if ( sequence_entry(1) )
        {
            add_phase_scaled_counter_558(50);
            byte_7e5 = 1;
            word_7e6 = 3;
            adjust_counter_482(200, 60);
        }
        v73 = time_counter_144;
        if ( !v73 && !frame_timer_142 && !frame_index_140 && sequence_index_13e == 4 )
        {
            set_action_and_finalize(9);
            return;
        }
        if ( sequence_index_13e == 2 && v73 >= 24 )
        {
            next_sequence_block();
            acceleration_y_100 = 0.60000002;
        }
        return;
    case 418:
        resolve_stage_surface_landing_transition();
        if ( frame_index_140 >= 8 )
        {
            velocity_x_f4 = velocity_x_f4 - 1.0;
            if ( velocity_x_f4 < 0.0 )
                velocity_x_f4 = 0.0;
        }
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        if ( !frame_timer_142 && frame_index_140 == 6 )
    LABEL_843:
        dispatch_indexed_event_member(0x1Du);
        return;
    case 500:
        resolve_stage_surface_landing_transition();
        byte_17c = 0;
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        if ( frame_timer_142 || frame_index_140 != 3 )
            return;
        *(float *)&v462 = 0.0;
        v224 = &v462;
        v175 = (unsigned char)facing_104;
        v158 = y_f0 + 150.0;
        v323 = (double)(30 * (char)v175) + x_ec;
        v76 = v323;
        v147 = v76;
        spawn_owned_object_via_manager(810, v147, v158, v175, 1, v224, 1);
        field_180 = 1;
        dispatch_character_wave_handle(3);
        emit_fighter_effect_433cc0(127,
            x_ec,
            y_f0,
            (unsigned char)facing_104,
            -1);
        adjust_counter_482(200, 120);
        add_phase_scaled_counter_558(50);
        return;
    case 501:
        resolve_stage_surface_landing_transition();
        byte_17c = 0;
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        if ( frame_timer_142 || frame_index_140 != 3 )
            return;
        v461 = 0.0;
        v224 = (int *)&v461;
        v175 = (unsigned char)facing_104;
        v158 = y_f0 + 150.0;
        v325 = (double)(30 * (char)v175) + x_ec;
        v76 = v325;
        v147 = v76;
        spawn_owned_object_via_manager(810, v147, v158, v175, 1, v224, 1);
        field_180 = 1;
        dispatch_character_wave_handle(3);
        emit_fighter_effect_433cc0(127,
            x_ec,
            y_f0,
            (unsigned char)facing_104,
            -1);
        adjust_counter_482(200, 120);
        add_phase_scaled_counter_558(50);
        return;
    case 505:
        resolve_stage_surface_landing_transition();
        byte_17c = 4;
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        if ( frame_timer_142 || frame_index_140 != 6 )
            return;
        payload_463[0] = 15.0;
        payload_463[1] = 0.0;
        payload_463[2] = 0.0;
        if ( byte_608 >= 2 )
            payload_463[2] = 3.0;
        v225 = (int *)payload_463;
        v176 = (unsigned char)facing_104;
        v159 = y_f0;
        v326 = (double)(80 * (char)v176) + x_ec;
        v77 = v326;
        v148 = v77;
        spawn_owned_object_via_manager(815, v148, v159, v176, 1, v225, 3);
        field_180 = 1;
        dispatch_character_wave_handle(7);
        emit_fighter_effect_433cc0(127,
            x_ec,
            y_f0,
            (unsigned char)facing_104,
            -1);
        adjust_counter_482(200, 120);
        add_phase_scaled_counter_558(50);
        return;
    case 506:
        resolve_stage_surface_landing_transition();
        byte_17c = 4;
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        if ( frame_timer_142 || frame_index_140 != 6 )
            return;
        payload_465[0] = 25.0;
        payload_465[1] = 0.0;
        payload_465[2] = 0.0;
        if ( byte_608 >= 2 )
            payload_465[2] = 3.0;
        v225 = (int *)payload_465;
        v176 = (unsigned char)facing_104;
        v159 = y_f0;
        v327 = (double)(80 * (char)v176) + x_ec;
        v77 = v327;
        v148 = v77;
        spawn_owned_object_via_manager(815, v148, v159, v176, 1, v225, 3);
        field_180 = 1;
        dispatch_character_wave_handle(7);
        emit_fighter_effect_433cc0(127,
            x_ec,
            y_f0,
            (unsigned char)facing_104,
            -1);
        adjust_counter_482(200, 120);
        add_phase_scaled_counter_558(50);
        return;
    case 510:
    case 511:
        resolve_stage_surface_landing_transition();
        byte_17c = 8;
        if ( sequence_index_13e == 1 || sequence_index_13e == 2 )
        {
            if ( !word_730 )
                adjust_counter_482(200, 120);
            if ( word_730 % 4 == 0 )
            {
                dispatch_character_wave_handle(0xDu);
                v489[0] = 0.0;
                v489[1] = (double)word_730 + 30.0;
                v489[2] = 0.0;
                v80 = (unsigned char)facing_104;
                v160 = y_f0 + 74.0;
                v329 = (double)(170 * (char)v80) + x_ec;
                spawn_owned_object_via_manager(820, v329, v160, v80, 1, v489, 2);
            }
            ++word_730;
        }
        if ( sequence_index_13e == 1 && time_counter_144 >= 16 || sequence_index_13e == 2 && time_counter_144 >= 16 )
        { next_sequence_block(); return; }
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        if ( sequence_entry(4) )
        {
            set_action_and_finalize(0);
            return;
        }
        return;
    case 520:
        if ( !sequence_index_13e || sequence_index_13e == 3 )
        {
            resolve_stage_surface_landing_transition();
        }
        byte_17c = 1;
        if ( !field_6c0 )
            byte_750 = 0;
        if ( sequence_index_13e == 1 || sequence_index_13e == 2 )
        {
            velocity_x_f4 = velocity_x_f4 - 0.4000000059604645;
            if ( velocity_x_f4 < 0.0 )
                velocity_x_f4 = 0.0;
            velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
            if ( (unsigned char)has_crossed_stage_surface_while_descending() )
            {
                zero_velocity_acceleration();
                y_f0 = stage_surface_height_at_x(this);
                select_sequence(3);
                return;
            }
        }
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        if ( !sequence_index_13e && !frame_timer_142 && frame_index_140 == 3 )
        {
            v473[0] = 0.0;
            v473[1] = 0.0;
            v473[2] = 0.0;
            spawn_owned_object_via_manager(811,
                x_ec,
                y_f0,
                (unsigned char)facing_104,
                1,
                v473,
                3);
        }
        if ( sequence_entry(1) )
        {
            adjust_counter_482(200, 120);
            add_phase_scaled_counter_558(50);
            dispatch_character_wave_handle(4u);
            velocity_x_f4 = 15.0;
            velocity_y_f8 = 15.0;
            acceleration_y_100 = 0.75;
            emit_fighter_effect_433cc0(127,
                x_ec,
                y_f0,
                (unsigned char)facing_104,
                -1);
        }
        return;
    case 521:
        if ( !sequence_index_13e || sequence_index_13e == 3 )
        {
            resolve_stage_surface_landing_transition();
        }
        byte_17c = 1;
        if ( !field_6c0 )
            byte_750 = 0;
        if ( time_counter_144 || frame_timer_142 || frame_index_140 )
            goto LABEL_1020;
        if ( !sequence_index_13e )
        {
            adjust_counter_482(200, 120);
            add_phase_scaled_counter_558(50);
            velocity_x_f4 = 15.0;
            v85 = (unsigned char)facing_104;
            v331 = (double)(200 * (char)v85) + x_ec;
            emit_fighter_effect_433cc0(128, v331, y_f0, v85, -1);
        LABEL_1020:
            if ( !sequence_index_13e )
            {
                velocity_x_f4 = velocity_x_f4 - 0.75;
                if ( velocity_x_f4 < 0.0 )
                    velocity_x_f4 = 0.0;
            }
        }
        if ( sequence_index_13e != 1 && sequence_index_13e != 2 )
            goto LABEL_1770;
        velocity_x_f4 = velocity_x_f4 - 0.4000000059604645;
        if ( velocity_x_f4 < 0.0 )
            velocity_x_f4 = 0.0;
        velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
        if ( (unsigned char)has_crossed_stage_surface_while_descending() )
        {
            zero_velocity_acceleration();
            y_f0 = stage_surface_height_at_x(this);
            select_sequence(3);
        }
        else
        {
        LABEL_1770:
            if ( (unsigned char)advance_frame_and_dispatch() )
                set_action_and_finalize(0);
            if ( !sequence_index_13e && !frame_timer_142 )
            {
                if ( frame_index_140 == 3 )
                {
                    dispatch_character_wave_handle(4u);
                    v488[0] = 0.0;
                    v488[1] = 0.0;
                    v488[2] = 1.0;
                    spawn_owned_object_via_manager(811,
                        x_ec,
                        y_f0,
                        (unsigned char)facing_104,
                        1,
                        v488,
                        3);
                }
                if ( !frame_timer_142 && frame_index_140 == 14 )
                {
                    v467[0] = 0.0;
                    v467[1] = 0.0;
                    v467[2] = 0.0;
                    spawn_owned_object_via_manager(811,
                        x_ec,
                        y_f0,
                        (unsigned char)facing_104,
                        1,
                        v467,
                        3);
                }
            }
            if ( sequence_entry(1) )
            {
                dispatch_character_wave_handle(4u);
                field_180 = 0;
                byte_184 = 1;
                byte_7cd = 1;
                velocity_x_f4 = 15.0;
                velocity_y_f8 = 17.5;
                acceleration_y_100 = 0.75;
                emit_fighter_effect_433cc0(127,
                    x_ec,
                    y_f0,
                    (unsigned char)facing_104,
                    -1);
            }
        }
        return;
    case 525:
        if ( !sequence_index_13e || sequence_index_13e == 2 || sequence_index_13e == 3 || sequence_index_13e == 4 || sequence_index_13e == 1 && frame_index_140 >= 6 )
            resolve_stage_surface_landing_transition();
        byte_17c = 5;
        if ( !field_6c0 )
            byte_750 = 0;
        if ( (unsigned char)advance_frame_and_dispatch() )
        {
            set_action_and_finalize(0);
            return;
        }
        if ( sequence_entry(1) )
        {
            set_action_and_finalize(0);
            return;
        }
        if ( sequence_entry(2) )
        {
            set_action_and_finalize(0);
            return;
        }
        if ( sequence_entry(3) )
        {
            set_action_and_finalize(0);
            return;
        }
        if ( sequence_entry(4) )
        {
            set_action_and_finalize(0);
            return;
        }
        if ( !sequence_index_13e || sequence_index_13e == 2 || sequence_index_13e == 3 || sequence_index_13e == 4 )
        {
            if ( !frame_timer_142 && frame_index_140 == 2 )
            {
                adjust_counter_482(200, 120);
                add_phase_scaled_counter_558(25);
                if ( !(unsigned char)is_y_at_or_below_stage_surface(reinterpret_cast<void *>(related_170)) )
                    byte_184 = 0;
            }
            if ( field_180 == 1 )
            {
                next_sequence_block();
                related_170->set_action_and_finalize(100);
                related_170->zero_velocity_acceleration();
                related_170->facing_104 = -facing_104;
                v334 = (double)(95 * facing_104) + x_ec;
                related_170->x_ec = v334;
                related_170->y_f0 = y_f0;
            }
        }
        if ( sequence_index_13e == 1 && !frame_timer_142 )
        {
            if ( frame_index_140 == 1 )
            {
                related_170->set_action_and_finalize(102);
                v335 = (double)(55 * facing_104) + x_ec;
                related_170->x_ec = v335;
            }
            if ( !frame_timer_142 )
            {
                if ( frame_index_140 == 2 )
                {
                    v336 = (double)(25 * facing_104) + x_ec;
                    related_170->x_ec = v336;
                }
                if ( !frame_timer_142 )
                {
                    if ( frame_index_140 == 3 )
                    {
                        v337 = (double)(20 * facing_104) + x_ec;
                        related_170->x_ec = v337;
                    }
                    if ( !frame_timer_142 )
                    {
                        if ( frame_index_140 == 4 )
                        {
                            related_170->set_action_and_finalize(100);
                            v338 = (double)(25 * facing_104) + x_ec;
                            related_170->x_ec = v338;
                        }
                        if ( !frame_timer_142 )
                        {
                            if ( frame_index_140 == 5 )
                            {
                                if ( related_170->word_174 <= 0 )
                                {
                                    related_170->x_ec = (double)(45 * facing_104) + x_ec;
                                    related_170->field_18c = -10.0;
                                    related_170->field_190 = 7.5;
                                    related_170->set_action_and_finalize(71);
                                    related_170->facing_104 = -facing_104;
                                }
                                else
                                {
                                    related_170->set_action_and_finalize(53);
                                    v339 = (double)(45 * facing_104) + x_ec;
                                    related_170->x_ec = v339;
                                }
                            }
                            if ( !frame_timer_142 && frame_index_140 == 7 && byte_750 )
                            {
                                face_opponent_and_flip_horizontal_velocity();
                                set_action_and_finalize(529);
                            }
                        }
                    }
                }
            }
        }
        return;
    case 526:
        if ( !sequence_index_13e || sequence_index_13e == 1 && frame_index_140 >= 6 )
            resolve_stage_surface_landing_transition();
        byte_17c = 5;
        if ( !field_6c4 )
            byte_750 = 0;
        if ( (unsigned char)advance_frame_and_dispatch() )
        {
            set_action_and_finalize(0);
            return;
        }

        if ( sequence_entry(1) )
        {
            set_action_and_finalize(0);
            return;
        }
        if ( sequence_entry(2) )
        {
            set_action_and_finalize(0);
            return;
        }
        if (sequence_entry(3)) { set_action_and_finalize(0); return; }
        if (sequence_entry(4)) { set_action_and_finalize(0); return; }
        if ( !sequence_index_13e || sequence_index_13e == 2 || sequence_index_13e == 3 || sequence_index_13e == 4 )
        {
            if ( !frame_timer_142 && frame_index_140 == 2 )
            {
                adjust_counter_482(200, 120);
                add_phase_scaled_counter_558(25);
                if ( !(unsigned char)is_y_at_or_below_stage_surface(reinterpret_cast<void *>(related_170)) )
                    byte_184 = 0;
            }
            if ( field_180 == 1 )
            {
                next_sequence_block();
                related_170->set_action_and_finalize(100);
                related_170->zero_velocity_acceleration();
                related_170->facing_104 = -facing_104;
                v340 = (double)(95 * facing_104) + x_ec;
                related_170->x_ec = v340;
                related_170->y_f0 = y_f0;
            }
        }
        if ( sequence_index_13e == 1 && !frame_timer_142 )
        {
            if ( frame_index_140 == 1 )
            {
                related_170->set_action_and_finalize(102);
                v341 = (double)(55 * facing_104) + x_ec;
                related_170->x_ec = v341;
            }
            if ( !frame_timer_142 )
            {
                if ( frame_index_140 == 2 )
                {
                    v342 = (double)(25 * facing_104) + x_ec;
                    related_170->x_ec = v342;
                }
                if ( !frame_timer_142 )
                {
                    if ( frame_index_140 == 3 )
                    {
                        v343 = (double)(20 * facing_104) + x_ec;
                        related_170->x_ec = v343;
                    }
                    if ( !frame_timer_142 )
                    {
                        if ( frame_index_140 == 4 )
                        {
                            // Target keeps the signed facing product as an integer FISUB operand.
                            v344 = x_ec - (5 * facing_104);
                            related_170->x_ec = v344;
                            related_170->facing_104 = facing_104;
                        }
                        if ( !frame_timer_142 )
                        {
                            if ( frame_index_140 == 5 )
                            {
                                if ( related_170->word_174 <= 0 )
                                {
                                    related_170->x_ec = x_ec - (25 * facing_104);
                                    related_170->field_18c = -10.0;
                                    related_170->field_190 = 7.5;
                                    related_170->set_action_and_finalize(71);
                                    related_170->facing_104 = facing_104;
                                }
                                else
                                {
                                    related_170->set_action_and_finalize(53);
                                    v345 = x_ec - (25 * facing_104);
                                    related_170->x_ec = v345;
                                }
                            }
                            if ( !frame_timer_142 && frame_index_140 == 7 && byte_750 )
                            {
                                face_opponent_and_flip_horizontal_velocity();
                                set_action_and_finalize(529);
                            }
                        }
                    }
                }
            }
        }
        return;
    case 529:
        if ( !sequence_index_13e || sequence_index_13e == 2 )
        {
            resolve_stage_surface_landing_transition();
        }
        if ( velocity_x_f4 > 0.0 )
        {
            velocity_x_f4 = velocity_x_f4 - 1.0;
            if ( velocity_x_f4 < 0.0 )
                velocity_x_f4 = 0.0;
        }
        if ( sequence_index_13e == 1 )
        {
            velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
            if ( (unsigned char)has_crossed_stage_surface_while_descending() )
            {
                y_f0 = stage_surface_height_at_x(this);
                velocity_x_f4 = velocity_x_f4 * 0.5;
                velocity_y_f8 = 0.0;
                { next_sequence_block(); return; }
            }
        }
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        if ( time_counter_144 )
            goto LABEL_1174;
        if ( !frame_timer_142 && !frame_index_140 && sequence_index_13e == 1 )
        {
            velocity_x_f4 = 25.0;
            velocity_y_f8 = 8.5;
            acceleration_y_100 = 0.85000002;
            dispatch_indexed_event_member(0x1Du);
        }
        if ( time_counter_144 )
            goto LABEL_1174;
        if ( !frame_timer_142 )
        {
            if ( !frame_index_140 && sequence_index_13e == 2 )
            {
                set_action_and_finalize(9);
                return;
            }
        LABEL_1174:
            if ( !frame_timer_142 && frame_index_140 == 4 )
                dispatch_indexed_event_member(0x1Cu);
        }
        return;
    case 530:
    case 531:
        resolve_stage_surface_landing_transition();
        byte_17c = 9;
        if ( !sequence_index_13e )
        {
            if ( !frame_timer_142 && frame_index_140 == 2 )
            {
                adjust_counter_482(200, 120);
                add_phase_scaled_counter_558(30);
                dispatch_character_wave_handle(0xAu);
            }
            if ( field_180 == 3 )
            {
                byte_184 = 1;
                field_180 = 0;
                next_sequence_block();
                dispatch_character_wave_handle(0xBu);
                return;
            }
        }
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        if ( time_counter_144 || frame_timer_142 || frame_index_140 )
        {
            if ( sequence_index_13e == 1 && !frame_timer_142 )
            {
                if ( frame_index_140 == 10 )
                    velocity_x_f4 = 20.0;
                if ( !frame_timer_142 )
                {
                    if ( frame_index_140 == 11 )
                    {
                        velocity_x_f4 = 0.0;
                        dispatch_character_wave_handle(0xCu);
                        field_180 = 0;
                        byte_184 = 1;
                        byte_7cd = 1;
                    }
                    if ( !frame_timer_142 && frame_index_140 == 12 )
                    {
                        v486[0] = 60.0;
                        v486[1] = 0.0;
                        v486[2] = 0.0;
                        v95 = (unsigned char)facing_104;
                        v161 = y_f0 + 115.0;
                        v348 = (double)(150 * (char)v95) + x_ec;
                        spawn_owned_object_via_manager(821, v348, v161, v95, 1, v486, 3);
                    }
                }
            }
            return;
        }
        if ( sequence_index_13e != 1 )
            return;
        {
            set_action_and_finalize(0);
            return;
        }
    case 540: {
            if (sequence_index_13e == 0 || sequence_index_13e == 1 ||
                (sequence_index_13e == 2 && frame_index_140 <= 2) || sequence_index_13e == 4)
            resolve_stage_surface_landing_transition();
            byte_17c = 2;
            if (!field_6c0) byte_750 = 0;
            if (advance_frame_and_dispatch()) set_action_and_finalize(0);
            if (sequence_entry(1) || sequence_entry(2) || sequence_entry(5)) {
                set_action_and_finalize(0); return;
            }
            if (sequence_index_13e == 0) {
                if (frame_index_140 >= 6) velocity_x_f4 -= 0.5;
                if (velocity_x_f4 < 0.0f) velocity_x_f4 = 0.0f;
                if (!frame_timer_142 && frame_index_140 == 4) {
                    adjust_counter_482(200, 120);
                    add_phase_scaled_counter_558(25);
                    v477[0] = 0.0f; v477[1] = 0.0f; v477[2] = 0.0f;
                    spawn_owned_object_via_manager(812, x_ec, y_f0, facing_104, 1, v477, 3);
                    velocity_x_f4 = 12.5f;
                    emit_fighter_effect_433cc0(128,
                        static_cast<float>(100 * facing_104) + x_ec, y_f0, facing_104, -1);
                    dispatch_character_wave_handle(5);
                }
            }
            if (sequence_index_13e == 1) {
                if (frame_index_140 >= 3) velocity_x_f4 -= 1.0;
                if (velocity_x_f4 < 0.0f) velocity_x_f4 = 0.0f;
                if (!frame_timer_142 && frame_index_140 == 3) {
                    v484[0] = 0.0f; v484[1] = 0.0f; v484[2] = 1.0f;
                    spawn_owned_object_via_manager(812, x_ec, y_f0, facing_104, 1, v484, 3);
                    velocity_x_f4 = 12.5f;
                    emit_fighter_effect_433cc0(127, x_ec, y_f0, facing_104, -1);
                    add_phase_scaled_counter_558(25);
                    dispatch_character_wave_handle(5);
                }
            }
            if (sequence_index_13e == 2 || sequence_index_13e == 3 || sequence_index_13e == 4) {
                if (sequence_index_13e < 4) velocity_y_f8 -= acceleration_y_100;
                if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                    select_sequence(4);
                    y_f0 = stage_surface_height_at_x(this);
                    zero_velocity_acceleration();
                    return;
                }
                if (sequence_index_13e == 2 && !frame_timer_142) {
                    if (frame_index_140 == 3) {
                        velocity_x_f4 = 12.5f; velocity_y_f8 = 10.0f; acceleration_y_100 = 0.75f;
                        emit_fighter_effect_433cc0(127, x_ec, y_f0, facing_104, -1);
                    }
                    if (!frame_timer_142 && frame_index_140 == 7) {
                        dispatch_character_wave_handle(6);
                        add_phase_scaled_counter_558(25);
                        v479[0] = 0.0f; v479[1] = 0.0f; v479[2] = 2.0f;
                        spawn_owned_object_via_manager(812, x_ec, y_f0, facing_104, 1, v479, 3);
                    }
                }
            }
            if (sequence_index_13e == 6 || sequence_index_13e == 7 || sequence_index_13e == 8) {
                if (sequence_index_13e == 6 || sequence_index_13e == 7)
                    velocity_y_f8 -= acceleration_y_100;
                if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                    select_sequence(8);
                    y_f0 = stage_surface_height_at_x(this);
                    zero_velocity_acceleration();
                    return;
                }
                if (sequence_index_13e == 6 && !frame_timer_142) {
                    if (frame_index_140 == 3) {
                        velocity_x_f4 = 5.0f; velocity_y_f8 = 21.0f; acceleration_y_100 = 1.5f;
                        emit_fighter_effect_433cc0(127, x_ec, y_f0, facing_104, -1);
                    }
                    if (!frame_timer_142 && frame_index_140 == 7) {
                        dispatch_character_wave_handle(6);
                        add_phase_scaled_counter_558(25);
                        v485[0] = 0.0f; v485[1] = 0.0f; v485[2] = 2.0f;
                        spawn_owned_object_via_manager(812, x_ec, y_f0, facing_104, 1, v485, 3);
                    }
                }
            }
            return;
        }
    case 545:
        resolve_stage_surface_landing_transition();
        byte_17c = 6;
        if ( !field_6c0 )
            byte_750 = 0;
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        v101 = time_counter_144;
        if ( !v101 && !frame_timer_142 && !frame_index_140 && sequence_index_13e == 1 )
        {
            set_action_and_finalize(0);
            return;
        }
        if ( !sequence_index_13e )
        {
            if ( frame_index_140 <= 7 && !(time_counter_144 % 5) && velocity_x_f4 > 0.0 )
                emit_fighter_effect_433cc0(127,
                x_ec,
                y_f0,
                (unsigned char)facing_104,
                -1);
            if ( frame_index_140 > 6 )
                velocity_x_f4 = velocity_x_f4 - 1.0;
            if ( velocity_x_f4 < 0.0 )
                velocity_x_f4 = 0.0;
            if ( !frame_timer_142 )
            {
                if ( frame_index_140 == 5 )
                {
                    adjust_counter_482(200, 120);
                    add_phase_scaled_counter_558(50);
                    velocity_x_f4 = 30.0;
                    dispatch_character_wave_handle(9u);
                    v490[0] = 0.0;
                    v490[1] = 0.0;
                    v490[2] = 0.0;
                    v490[3] = 1.0;
                    spawn_owned_object_via_manager(817,
                        x_ec,
                        y_f0,
                        (unsigned char)facing_104,
                        1,
                        v490,
                        4);
                }
                if ( !frame_timer_142 && frame_index_140 == 7 )
                    velocity_x_f4 = velocity_x_f4 * 0.5;
            }
        }
        return;
    case 546:
        resolve_stage_surface_landing_transition();
        byte_17c = 6;
        if ( frame_index_140 == 6 )
        {
            if ( field_180 )
            {
                if ( byte_184 > 0 && (short)++word_730 >= 6 )
                {
                    field_180 = 0;
                    word_730 = 0;
                }
            }
        }
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        v102 = time_counter_144;
        if ( !v102 && !frame_timer_142 && !frame_index_140 && sequence_index_13e == 1 )
        {
            set_action_and_finalize(0);
            return;
        }
        if ( !sequence_index_13e )
        {
            if ( frame_index_140 <= 7 && !(time_counter_144 % 5) && velocity_x_f4 > 0.0 )
                emit_fighter_effect_433cc0(127,
                x_ec,
                y_f0,
                (unsigned char)facing_104,
                -1);
            if ( frame_index_140 > 6 )
                velocity_x_f4 = velocity_x_f4 - 1.0;
            if ( velocity_x_f4 < 0.0 )
                velocity_x_f4 = 0.0;
            if ( !frame_timer_142 )
            {
                if ( frame_index_140 == 5 )
                {
                    adjust_counter_482(200, 120);
                    add_phase_scaled_counter_558(50);
                    velocity_x_f4 = 30.0;
                    dispatch_character_wave_handle(9u);
                    v491[0] = 0.0;
                    v491[1] = 0.0;
                    v491[2] = 0.0;
                    v491[3] = 1.5;
                    spawn_owned_object_via_manager(817,
                        x_ec,
                        y_f0,
                        (unsigned char)facing_104,
                        1,
                        v491,
                        4);
                }
                if ( !frame_timer_142 && frame_index_140 == 7 )
                    velocity_x_f4 = velocity_x_f4 * 0.5;
            }
        }
        return;
    case 560:
    case 561:
        resolve_stage_surface_landing_transition();
        if ( sequence_index_13e == 1 && time_counter_144 >= 15 )
        {
            next_sequence_block();
        }
        else
        {
            if ( (unsigned char)advance_frame_and_dispatch() )
                set_action_and_finalize(0);
            if ( !sequence_index_13e && !frame_timer_142 && frame_index_140 == 5 )
            {
                byte_7e5 = 1;
                word_7e6 = 4;
                adjust_counter_482(200, 120);
                field_180 = 1;
                add_phase_scaled_counter_558(50);
            }
        }
        return;

    case 565:
    case 566:
        resolve_stage_surface_landing_transition();
        if ( sequence_index_13e == 2 && time_counter_144 >= 24 )
        { next_sequence_block(); return; }
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        if ( sequence_entry(1) )
        {
            byte_7e5 = 1;
            word_7e6 = 5;
            adjust_counter_482(200, 120);
            field_180 = 1;
            add_phase_scaled_counter_558(50);
        }
        return;
    case 570:
    case 571:
        resolve_stage_surface_landing_transition();
        if ( sequence_index_13e == 2 && time_counter_144 >= 24 )
        { next_sequence_block(); return; }
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        if ( sequence_entry(1) )
        {
            byte_7e5 = 1;
            word_7e6 = 6;
            adjust_counter_482(200, 120);
            field_180 = 1;
            add_phase_scaled_counter_558(50);
        }
        return;
    case 600:
        if ( frame_index_140 <= 6 || frame_index_140 >= 11 )
            resolve_stage_surface_landing_transition();
        publish_texture_state(3, 2);
        if ( word_730 )
            goto LABEL_1769;
        if ( field_180 == 1 )
        {
            word_730 = 1;
            v481[0] = 0.0;
            v481[1] = 0.0;
            v481[2] = 0.0;
            v350 = y_f0 + 100.0;
            spawn_owned_object_via_manager(850,
                x_ec,
                v350,
                (unsigned char)facing_104,
                1,
                v481,
                3);
            dispatch_character_wave_handle(0x33u);
        }
        if ( word_730 || !field_180 )
        {
        LABEL_1769:
            if ( (unsigned char)advance_frame_and_dispatch() )
                set_action_and_finalize(0);
            if ( !sequence_index_13e )
            {
                if ( !frame_timer_142 && frame_index_140 == 5 )
                {
                    word_48a = 40;
                    dispatch_indexed_event_member(0x17u);
                    v104 = (unsigned char)facing_104;
                    v201 = y_f0 + 107.0;
                    v352 = (double)(20 * (char)v104) + x_ec;
                    emit_fighter_effect_433cc0(115, v352, v201, v104, 1);
                    dispatch_indexed_sequence_window_45c8b0(0, 2, 0x3C);
                    advance_secondary_event_effect_cycle();
                }
                if ( !frame_timer_142 && frame_index_140 == 7 )
                {
                    velocity_x_f4 = 30.0;
                    int facing_600 = (unsigned char)facing_104;
                    v353 = (double)(200 * (char)facing_600) + x_ec;
                    emit_fighter_effect_433cc0(128, v353, y_f0, facing_600, -1);
                    field_108 = 35.0;
                    field_10c = 70.0;
                    dispatch_character_wave_handle(0x32u);
                }
                if ( !frame_timer_142 && frame_index_140 == 9 )
                    velocity_x_f4 = 25.0;
                ;
                if ( frame_index_140 == 7 )
                {
                    field_11c = field_11c + 0.2f;
                    field_120 = field_120 - 0.2f;
                    if ( field_120 < 0.0 )
                        field_120 = 0.0;
                    if ( field_11c > 3.0 )
                        field_11c = 3.0;
                }
                else
                {
                }
                if ( frame_index_140 == 9 )
                {
                    field_11c = field_11c - static_cast<double>(0.2f);
                    field_120 = static_cast<double>(0.2f) + field_120;
                    if ( field_120 > 1.0 )
                        field_120 = 1.0;
                    if ( field_11c < 1.0 )
                        field_11c = 1.0;
                }
                else
                {
                }
                if ( frame_index_140 >= 9 )
                {
                    velocity_x_f4 = velocity_x_f4 - 1.0;
                    if ( velocity_x_f4 < 0.0 )
                        velocity_x_f4 = 0.0;
                }
                if ( !frame_timer_142 && frame_index_140 == 10 )
                    reinterpret_cast<FighterActionScratchView *>(raw + 4)->reset();
            }
        }
        else
        {
            word_730 = 1;
            set_sequence_frame(9);
            velocity_x_f4 = 25.0;
        }
        return;
    case 601:
        resolve_stage_surface_landing_transition();
        publish_texture_state(3, 2);
        if ( field_180 )
        {
            if ( byte_184 > 0 && (short)++word_730 >= 2 )
            {
                word_730 = 0;
                field_180 = 0;
            }
        }
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        if ( !sequence_index_13e && !frame_timer_142 )
        {
            if ( frame_index_140 == 2 )
            {
                word_48a = 40;
                dispatch_indexed_event_member(0x17u);
                v110 = (unsigned char)facing_104;
                v202 = y_f0 + 87.0;
                v358 = (double)(63 * (char)v110) + x_ec;
                emit_fighter_effect_433cc0(115, v358, v202, v110, 1);
                dispatch_indexed_sequence_window_45c8b0(0, 3, 0x3C);
                advance_secondary_event_effect_cycle();
            }
            if ( !frame_timer_142 )
            {
                if ( frame_index_140 == 3 )
                {
                    v487[0] = 0.0;
                    v487[1] = 0.0;
                    v487[2] = 0.0;
                    spawn_owned_object_via_manager(851,
                        x_ec,
                        y_f0,
                        (unsigned char)facing_104,
                        1,
                        v487,
                        3);
                }
                if ( !frame_timer_142 )
                {
                    if ( frame_index_140 == 10 )
                        dispatch_character_wave_handle(0x34u);
                    if ( !frame_timer_142 && frame_index_140 == 11 )
                    {
                        v359 = 0.0;
                        do
                        {
                            // Target adds 22.5 to index*45 before adding the unsigned random roll.
                            v458[0] = (float)(unsigned int)selector_random_roll(0x12u) + (v359 * 45.0 + 22.5);
                            v458[1] = 20.0;
                            v458[2] = 2.0;
                            // The target sends unordered angles to the outside path as well.
                            if ( !(v458[0] >= 0.0 && v458[0] <= 180.0) )
                            {
                                v177 = (unsigned char)facing_104;
                                spawn_owned_object_via_manager(821,
                                    (float)((double)(175 * (char)v177) + x_ec),
                                    y_f0,
                                    v177, -1, v458, 3);
                            }
                            else
                            {
                                v177 = (unsigned char)facing_104;
                                spawn_owned_object_via_manager(821,
                                    (float)((double)(150 * (char)v177) + x_ec),
                                    y_f0,
                                    v177, 1, v458, 3);
                            }
                            v359 = v359 + 1.0;
                        }
                        while ( v359 < 8.0 );
                    }
                }
            }
        }
        return;
    case 602:
        // Target action602 shares the sequence-advance return with action415.
        resolve_stage_surface_landing_transition();
        publish_texture_state(3, 2);
        if ( sequence_index_13e == 1 && time_counter_144 >= 40 )
        {
            { next_sequence_block(); return; }
        }
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        if ( !time_counter_144 )
        {
            if ( !frame_timer_142 && !frame_index_140 && sequence_index_13e == 1 )
            {
                time_counter_144 = 0;
                word_48a = 40;
                dispatch_indexed_event_member(0x17u);
                v380 = y_f0 + 100.0;
                emit_fighter_effect_433cc0(115, x_ec, v380, facing_104, 1);
                dispatch_indexed_sequence_window_45c8b0(0, 2, 0x3C);
                advance_secondary_event_effect_cycle();
                dispatch_character_wave_handle(0x36u);
            }
            if ( sequence_entry(3) )
            {
                word_7ea = 240;
                word_7ec = 1;
                payload_446[0] = 0.0;
                payload_446[1] = 0.0;
                payload_446[2] = 0.0;
                v381 = y_f0 + 100.0;
                spawn_owned_object_via_manager(852,
                    x_ec,
                    v381,
                    (unsigned char)facing_104,
                    1,
                    payload_446,
                    3);
                // Target converts each roll as unsigned before the float payload store.
                payload_446[0] = (float)(unsigned int)selector_random_roll(0x168u);
                payload_446[2] = 1.0;
                v382 = y_f0 + 100.0;
                spawn_owned_object_via_manager(852,
                    x_ec,
                    v382,
                    (unsigned char)facing_104,
                    1,
                    payload_446,
                    3);
                payload_446[0] = (float)(unsigned int)selector_random_roll(0x168u);
                v383 = y_f0 + 100.0;
                spawn_owned_object_via_manager(852,
                    x_ec,
                    v383,
                    (unsigned char)-(unsigned char)facing_104,
                    1,
                    payload_446,
                    3);
                // Target keeps one rounded float counter through this six-step loop.
                v360 = 0.0;
                do
                {
                    payload_446[0] = v360 * 60.0 + 30.0;
                    payload_446[1] = 15.0;
                    payload_446[2] = 2.0;
                    // The target sends unordered angles to the outside path as well.
                    if ( !(payload_446[0] >= 0.0 && payload_446[0] <= 180.0) )
                        spawn_owned_object_via_manager(821,
                        x_ec,
                        y_f0,
                        (unsigned char)facing_104,
                        -1,
                        payload_446,
                        3);
                    else
                        spawn_owned_object_via_manager(821,
                        x_ec,
                        y_f0,
                        (unsigned char)facing_104,
                        1,
                        payload_446,
                        3);
                    v360 = v360 + 1.0;
                }
                while ( v360 < 6.0 );
            }
        }
        return;
    case 603: {
            publish_texture_state(3, 2);
            if ( sequence_index_13e == 5 || !sequence_index_13e && ((v114 = frame_index_140, v114 <= 6) || v114 >= 10) )
                resolve_stage_surface_landing_transition();
            if (advance_frame_and_dispatch()) { set_action_and_finalize(0); return; }
            if (sequence_entry(1)) { set_action_and_finalize(0); return; }
            if (sequence_index_13e == 0) {

                if ( field_180 == 1 )
                {
                    v468[0] = 0.0;
                    v468[1] = 0.0;
                    v468[2] = 0.0;
                    spawn_owned_object_via_manager(853,
                        x_ec,
                        static_cast<float>(y_f0 + 100.0),
                        facing_104,
                        1,
                        v468,
                        3);
                    zero_velocity_acceleration();
                    next_sequence_block();
                    x_ec = related_170->x_ec;
                    reinterpret_cast<FighterActionScratchView *>(raw + 4)->reset();
                    field_180 = 0;
                }
                if ( frame_index_140 <= 8 && field_180 )
                {
                    set_sequence_frame(9);
                    velocity_x_f4 = 25.0;
                    return;
                }
                if ( frame_index_140 <= 6 || frame_index_140 >= 11 )
                    resolve_stage_surface_landing_transition();
                if ( !frame_timer_142 )
                {
                    if ( frame_index_140 == 5 )
                    {
                        word_48a = 40;
                        dispatch_indexed_event_member(0x17u);
                        v116 = (unsigned char)facing_104;
                        v204 = y_f0 + 107.0;
                        v386 = (double)(20 * (char)v116) + x_ec;
                        emit_fighter_effect_433cc0(115, v386, v204, v116, 1);
                        dispatch_indexed_sequence_window_45c8b0(0, 5, 0x3C);
                        advance_secondary_event_effect_cycle();
                    }
                    if ( !frame_timer_142 )
                    {
                        if ( frame_index_140 == 7 )
                        {
                            velocity_x_f4 = 40.0;
                            v387 = (double)(200 * facing_104) + x_ec;
                            emit_fighter_effect_433cc0(128, v387, y_f0, facing_104, -1);
                            field_108 = 35.0;
                            field_10c = 70.0;
                        }
                        if ( !frame_timer_142 && frame_index_140 == 9 )
                            velocity_x_f4 = 25.0;
                    }
                }
                if ( frame_index_140 == 7 )
                {
                    field_11c = field_11c + 0.2f;
                    field_120 = field_120 - 0.2f;
                    if ( field_120 < 0.0 )
                        field_120 = 0.0;
                    if ( field_11c > 3.0 )
                        field_11c = 3.0;
                }
                else
                {
                }
                if ( frame_index_140 == 9 )
                {
                    field_11c = field_11c - 0.2f;
                    field_120 = field_120 + 0.2f;
                    if ( field_120 > 1.0 )
                        field_120 = 1.0;
                    if ( field_11c < 1.0 )
                        field_11c = 1.0;
                }
                else
                {
                }
                if ( frame_index_140 >= 9 )
                {
                    velocity_x_f4 = velocity_x_f4 - 1.0;
                    if ( velocity_x_f4 < 0.0 )
                        velocity_x_f4 = 0.0;
                }
                if ( !frame_timer_142 && frame_index_140 == 10 )
                {
                    reinterpret_cast<FighterActionScratchView *>(raw + 4)->reset();
                }
            }
            if (sequence_index_13e == 2) {
                if (time_counter_144 % 5 == 0) {
                    if (word_730 < 16) {
                        payload_444[0] = 0.0;
                        payload_444[1] = 0.0;
                        payload_444[2] = 2.0;
                        spawn_owned_object_via_manager(853,
                            related_170->x_ec,
                            static_cast<float>(related_170->y_f0 + 100.0),
                            (unsigned char)facing_104,
                            1,
                            payload_444,
                            3);
                        payload_444[2] = 1.0;
                        v120 = word_730;
                        if ( !v120 || v120 == 8 )
                            payload_444[0] = 0.0;
                        v121 = word_730;
                        if ( v121 == 1 || v121 == 9 )
                            payload_444[0] = 180.0;
                        v122 = word_730;
                        if ( v122 == 2 || v122 == 10 )
                            payload_444[0] = 90.0;
                        v123 = word_730;
                        if ( v123 == 3 || v123 == 11 )
                            payload_444[0] = 270.0;
                        v124 = word_730;
                        if ( v124 == 4 || v124 == 12 )
                            payload_444[0] = 45.0;
                        v125 = word_730;
                        if ( v125 == 5 || v125 == 13 )
                            payload_444[0] = 225.0;
                        v126 = word_730;
                        if ( v126 == 6 || v126 == 14 )
                            payload_444[0] = 135.0;
                        v127 = word_730;
                        if ( v127 == 7 || v127 == 15 )
                            payload_444[0] = 315.0;
                        v389 = 90.0 - payload_444[0];
                        // Target adds peerY+100 before adding the sine contribution.
                        double v442 = lookup_orientation_sine_quantized_abs(v389) * 200.0 + (related_170->y_f0 + 100.0);
                        v390 = 90.0 - payload_444[0];
                        double v364 = lookup_orientation_cosine_quantized_abs(v390) * 200.0;
                        // Target prepares trailing spawn arguments before the remaining sine-Y/cosine-X calls.
                        spawn_owned_object_via_manager(853,
                            (v364 - lookup_orientation_cosine_quantized_abs(-payload_444[0]) * 150.0) * (double)facing_104
                            + related_170->x_ec,
                            v442 - lookup_orientation_sine_quantized_abs(-payload_444[0]) * 150.0,
                            facing_104, 1, payload_444, 3);
                        payload_444[2] = 3.0;
                        // Target computes these coordinates within the spawn argument schedule.
                        spawn_owned_object_via_manager(853,
                            lookup_orientation_cosine_quantized_abs((float)(90.0 - payload_444[0])) * 250.0 * (double)facing_104
                            + related_170->x_ec,
                            lookup_orientation_sine_quantized_abs((float)(90.0 - payload_444[0])) * 250.0
                            + (related_170->y_f0 + 100.0),
                            facing_104, 1, payload_444, 3);
                        ++word_730;
                    }
                }
                if (word_730 >= 16) next_sequence_block();
            }
            if ( sequence_index_13e == 3 )
            {
                if ( !frame_timer_142 && frame_index_140 == 1 )
                {
                    byte_184 = 1;
                    field_180 = 0;
                    velocity_x_f4 = 0.0;
                    velocity_y_f8 = 60.0;
                }
                if ( field_180 == 1 )
                {
                    v470[0] = -90.0;
                    v470[1] = 0.0;
                    v470[2] = 0.0;
                    spawn_owned_object_via_manager(853,
                        x_ec,
                        static_cast<float>(y_f0 + 100.0),
                        (unsigned char)facing_104,
                        1,
                        v470,
                        3);
                    field_180 = 0;
                    byte_184 = 0;
                }
                if ( frame_index_140 >= 3 )
                    velocity_y_f8 = velocity_y_f8 - 1.0;
            }
            if ( sequence_index_13e == 4 )
                velocity_y_f8 = velocity_y_f8 - 1.0;
            if ( (sequence_index_13e == 3 || sequence_index_13e == 4) && (unsigned char)has_crossed_stage_surface_while_descending() )
            {
                zero_velocity_acceleration();
                y_f0 = stage_surface_height_at_x(this);
                select_sequence(5);
            }
            return;
        }
    case 604:
        resolve_stage_surface_landing_transition();
        publish_texture_state(3, 2);
        if ( field_180 )
        {
            if ( byte_184 > 0 && (short)++word_730 >= 2 )
            {
                word_730 = 0;
                field_180 = 0;
            }
        }
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        if ( !sequence_index_13e && !frame_timer_142 )
        {
            if ( frame_index_140 == 2 )
            {
                word_48a = 40;
                dispatch_indexed_event_member(0x17u);
                v129 = (unsigned char)facing_104;
                v205 = y_f0 + 87.0;
                v399 = (double)(63 * (char)v129) + x_ec;
                emit_fighter_effect_433cc0(115, v399, v205, v129, 1);
                dispatch_indexed_sequence_window_45c8b0(0, 4, 0x3C);
                advance_secondary_event_effect_cycle();
            }
            if ( !frame_timer_142 )
            {
                if ( frame_index_140 == 3 )
                {
                    v472[0] = 0.0;
                    v472[1] = 0.0;
                    v472[2] = 0.0;
                    spawn_owned_object_via_manager(854,
                        x_ec,
                        y_f0,
                        (unsigned char)facing_104,
                        1,
                        v472,
                        3);
                }
                if ( !frame_timer_142 )
                {
                    if ( frame_index_140 == 10 )
                        dispatch_character_wave_handle(0x35u);
                    if ( !frame_timer_142 && frame_index_140 == 11 )
                    {
                        v365 = 0.0;
                        do
                        {
                            // Target adds 22.5 to index*45 before adding the unsigned random roll.
                            v459[0] = (float)(unsigned int)selector_random_roll(0x12u) + (v365 * 45.0 + 22.5);
                            v459[1] = 20.0;
                            v459[2] = 2.0;
                            // The target sends unordered angles to the outside path as well.
                            if ( !(v459[0] >= 0.0 && v459[0] <= 180.0) )
                            {
                                spawn_owned_object_via_manager(821,
                                    (double)(175 * (char)facing_104) + x_ec,
                                    y_f0,
                                    (unsigned char)facing_104,
                                    -1,
                                    v459,
                                    3);
                            }
                            else
                            {
                                spawn_owned_object_via_manager(821,
                                    (double)(150 * (char)facing_104) + x_ec,
                                    y_f0,
                                    (unsigned char)facing_104,
                                    1,
                                    v459,
                                    3);
                            }
                            v365 = v365 + 1.0;
                        }
                        while ( v365 < 8.0 );
                    }
                }
            }
        }
        return;
    case 605: {
            float payload_452[3];
            resolve_stage_surface_landing_transition();
            publish_texture_state(3, 2);
            if ( sequence_index_13e == 1 && time_counter_144 >= 16 )
            {
                next_sequence_block();
            }
            else
            {
                if ( (unsigned char)advance_frame_and_dispatch() )
                    set_action_and_finalize(0);
                if ( !time_counter_144 )
                {
                    if ( !frame_timer_142 && !frame_index_140 && sequence_index_13e == 1 )
                    {
                        time_counter_144 = 0;
                        word_48a = 40;
                        dispatch_indexed_event_member(0x17u);
                        v402 = y_f0 + 100.0;
                        emit_fighter_effect_433cc0(115, x_ec, v402, facing_104, 1);
                        dispatch_indexed_sequence_window_45c8b0(0, 2, 0x3C);
                        advance_secondary_event_effect_cycle();
                        dispatch_character_wave_handle(0x36u);
                    }
                    if ( sequence_entry(3) )
                    {
                        word_7ea = 600;
                        payload_452[0] = 0.0;
                        payload_452[1] = 0.0;
                        payload_452[2] = 0.0;
                        v403 = y_f0 + 100.0;
                        spawn_owned_object_via_manager(855,
                            x_ec,
                            v403,
                            (unsigned char)facing_104,
                            1,
                            payload_452,
                            3);
                        payload_452[0] = (float)(unsigned int)selector_random_roll(0x258u);
                        payload_452[2] = 1.0;
                        v404 = y_f0 + 100.0;
                        spawn_owned_object_via_manager(855,
                            x_ec,
                            v404,
                            (unsigned char)facing_104,
                            1,
                            payload_452,
                            3);
                        payload_452[0] = (float)(unsigned int)selector_random_roll(0x168u);
                        v405 = y_f0 + 100.0;
                        spawn_owned_object_via_manager(855,
                            x_ec,
                            v405,
                            (unsigned char)-(unsigned char)facing_104,
                            1,
                            payload_452,
                            3);
                        v366 = 0.0;
                        do
                        {
                            payload_452[0] = (float)(unsigned int)selector_random_roll(0x168u);
                            payload_452[1] = 0.0;
                            payload_452[2] = 2.0;
                            v406 = y_f0 + 100.0;
                            spawn_owned_object_via_manager(855,
                                x_ec,
                                v406,
                                (unsigned char)facing_104,
                                1,
                                payload_452,
                                3);
                            v366 = v366 + 1.0;
                        }
                        while ( v366 < 6.0 );
                    }
                }
            }
            return;
        }
    case 606:
        if ( frame_index_140 <= 6 || frame_index_140 >= 11 )
            resolve_stage_surface_landing_transition();
        publish_texture_state(3, 2);
        if ( frame_index_140 >= 7 && frame_index_140 <= 10 )
        {
            if ( word_730 % 2 == 0 )
            {
                payload_455[0] = 10.0 - (float)(unsigned int)selector_random_roll(0x2Du);
                payload_455[1] = 0.0;
                payload_455[2] = 2.0;
                v443 = y_f0 + 20.0;
                field_73c = v443 - (float)(unsigned int)selector_random_roll(0x28u);
                spawn_owned_object_via_manager(856,
                    (float)(unsigned int)selector_random_roll(100) + x_ec - 50.0,
                    field_73c,
                    facing_104,
                    (unsigned char)(2 * (y_f0 >= field_73c) - 1),
                    payload_455, 3);
                payload_455[0] = 0.0;
                payload_455[1] = (double)word_730 * 0.0 + 45.0;
                payload_455[2] = 5.0;
                spawn_owned_object_via_manager(856,
                    x_ec,
                    y_f0,
                    (unsigned char)facing_104,
                    1,
                    payload_455,
                    3);
            }
            ++word_730;
        }
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        if ( !sequence_index_13e )
        {
            if ( !frame_timer_142 && frame_index_140 == 5 )
            {
                word_48a = 40;
                dispatch_indexed_event_member(0x17u);
                v134 = (unsigned char)facing_104;
                v208 = y_f0 + 107.0;
                v410 = (double)(20 * (char)v134) + x_ec;
                emit_fighter_effect_433cc0(115, v410, v208, v134, 1);
                dispatch_indexed_sequence_window_45c8b0(0, 3, 0x3C);
                advance_secondary_event_effect_cycle();
            }
            if ( !frame_timer_142 )
            {
                if ( frame_index_140 == 7 )
                {
                    dispatch_character_wave_handle(9u);
                    velocity_x_f4 = 30.0;
                    v135 = (unsigned char)facing_104;
                    v411 = (double)(200 * (char)v135) + x_ec;
                    emit_fighter_effect_433cc0(128, v411, y_f0, v135, -1);
                    field_108 = 35.0;
                    field_10c = 70.0;
                }
                if ( !frame_timer_142 && frame_index_140 == 9 )
                    velocity_x_f4 = 25.0;
            }
            ;
            if ( frame_index_140 == 7 )
            {
                field_11c = field_11c + 0.2f;
                field_120 = field_120 - 0.2f;
                if ( field_120 < 0.0 )
                    field_120 = 0.0;
                if ( field_11c > 3.0 )
                    field_11c = 3.0;
            }
            else
            {
            }
            if ( frame_index_140 == 9 )
            {
                field_11c = field_11c - static_cast<double>(0.2f);
                field_120 = static_cast<double>(0.2f) + field_120;
                if ( field_120 > 1.0 )
                    field_120 = 1.0;
                if ( field_11c < 1.0 )
                    field_11c = 1.0;
            }
            else
            {
            }
            if ( frame_index_140 >= 9 )
            {
                velocity_x_f4 = velocity_x_f4 - 1.0;
                if ( velocity_x_f4 < 0.0 )
                    velocity_x_f4 = 0.0;
            }
            if ( !frame_timer_142 && frame_index_140 == 10 )
                reinterpret_cast<FighterActionScratchView *>(raw + 4)->reset();
        }
        return;
    case 607:
        resolve_stage_surface_landing_transition();
        publish_texture_state(3, 2);
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        if ( !sequence_index_13e && !frame_timer_142 )
        {
            if ( frame_index_140 == 3 )
            {
                word_48a = 40;
                dispatch_indexed_event_member(0x17u);
                v412 = y_f0 + 90.0;
                emit_fighter_effect_433cc0(115, x_ec, v412, facing_104, 1);
                dispatch_indexed_sequence_window_45c8b0(0, 4, 0x3C);
                advance_secondary_event_effect_cycle();
            }
            if ( !frame_timer_142 && frame_index_140 == 6 )
            {
                v474[0] = 0.0;
                v474[1] = 0.0;
                v474[2] = 0.0;
                v182 = (unsigned char)facing_104;
                v168 = y_f0 - 20.0;
                v414 = (double)(50 * (char)v182) + x_ec;
                spawn_owned_object_via_manager(857, v414, v168, v182, 1, v474, 3);
                dispatch_character_wave_handle(0x37u);
                publish_battle_layout_scalar(10.0);
            }
        }
        return;
    case 695:
        resolve_stage_surface_landing_transition();
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        if ( !sequence_index_13e && !frame_timer_142 && frame_index_140 == 5 )
        {
            dispatch_indexed_event_member(0x37u);
            v415 = y_f0 + 100.0;
            emit_fighter_effect_433cc0(140, x_ec, v415, facing_104, 1);
            v416 = y_f0 + 100.0;
            emit_fighter_effect_433cc0(140, x_ec, v416, facing_104, 1);
            v417 = y_f0 + 100.0;
            emit_fighter_effect_433cc0(140, x_ec, v417, facing_104, 1);
            v418 = y_f0 + 100.0;
            emit_fighter_effect_433cc0(141, x_ec, v418, facing_104, -1);
            emit_fighter_effect_433cc0(142,
                x_ec,
                y_f0,
                (unsigned char)facing_104,
                -1);
        }
        return;
    case 696:
        resolve_stage_surface_landing_transition();
        if ( (unsigned char)advance_frame_and_dispatch()
            || sequence_entry(1) )
        {

            set_action_and_finalize(0);
            return;
        }
        if ( sequence_index_13e )
            return;
        if ( !frame_timer_142 && frame_index_140 == 4 )
            velocity_x_f4 = 20.0;
        if ( !frame_timer_142 && frame_index_140 == 5 )
            dispatch_indexed_event_member(0x1Du);
        if ( frame_index_140 >= 5 )
        {
            // Target rounds the decrement to a dword before the sign comparison.
            velocity_x_f4 = velocity_x_f4 - 2.0;
            if ( velocity_x_f4 < 0.0 )
                velocity_x_f4 = 0.0;
        }
        return;
    case 710: {
            float payload_449[3];
            resolve_stage_surface_landing_transition();
            if (advance_frame_and_dispatch()) set_action_and_finalize(700);
            if (!sequence_index_13e && !frame_timer_142 && frame_index_140 == 7) {
                payload_449[0] = -120.0f;
                payload_449[1] = 0.0f;
                payload_449[2] = 0.0f;
                spawn_owned_object_via_manager(900,
                    static_cast<float>(140 * facing_104) + x_ec,
                    static_cast<float>(y_f0 + 20.0), facing_104, 1, payload_449, 3);
                if (g_match_identifier == 3) {
                    payload_449[0] = -95.0f;
                    payload_449[1] = 0.0f;
                    payload_449[2] = 0.0f;
                    spawn_owned_object_via_manager(900,
                        static_cast<float>(140 * facing_104) + x_ec,
                        static_cast<float>(y_f0 + 20.0), facing_104, 1, payload_449, 3);
                }
                dispatch_character_wave_handle(12);
                for (float ray = 0.0f; ray < 8.0f; ray += 1.0f) {
                    payload_449[0] = static_cast<float>(static_cast<float>(static_cast<unsigned>(selector_random_roll(18))) + (ray * 45.0 + 22.5));
                    payload_449[1] = 20.0f;
                    payload_449[2] = 5.0f;
                    if (payload_449[0] >= 0.0f && payload_449[0] <= 180.0f) {
                        spawn_owned_object_via_manager(900,
                            static_cast<float>(140 * facing_104) + x_ec,
                            y_f0, facing_104, 1, payload_449, 3);
                    } else {
                        spawn_owned_object_via_manager(900,
                            static_cast<float>(140 * facing_104) + x_ec,
                            y_f0, facing_104, -1, payload_449, 3);
                    }
                }
            }
            if (sequence_index_13e == 1 && !frame_timer_142 && frame_index_140 == 5) {
                float v460[3];
                word_730 = 1;
                dispatch_character_wave_handle(15);
                for (float ray = 0.0f; ray < 8.0f; ray += 1.0f) {
                    v460[0] = static_cast<float>(static_cast<float>(static_cast<unsigned>(selector_random_roll(18))) + (ray * 45.0 + 22.5));
                    v460[1] = 20.0f;
                    v460[2] = 5.0f;
                    if (v460[0] >= 0.0f && v460[0] <= 180.0f)
                        spawn_owned_object_via_manager(900, x_ec, y_f0, facing_104, 1, v460, 3);
                    else
                        spawn_owned_object_via_manager(900, x_ec, y_f0, facing_104, -1, v460, 3);
                }
            }
            return;
        }
    case 720:
        if ( !sequence_index_13e && frame_index_140 <= 6 || sequence_index_13e == 3 && frame_index_140 >= 1 )
        {
            resolve_stage_surface_landing_transition();
        }
        if ( sequence_index_13e == 1 )
        {
            if ( time_counter_144 == 30 )
            {
                v476[0] = 0.0;
                v476[1] = 20.0;
                v476[2] = 6.0;
                v425 = related_170->y_f0 + 100.0;
                spawn_owned_object_via_manager(901,
                    related_170->x_ec,
                    v425,
                    (unsigned char)facing_104,
                    1,
                    v476,
                    3);
            }
            velocity_x_f4 = velocity_x_f4 - 1.0;
            if ( velocity_x_f4 < 0.0 )
                velocity_x_f4 = 0.0;
            if ( time_counter_144 >= 270 )
            {
                select_sequence(3);
                facing_104 = -facing_104;
                velocity_x_f4 = 25.0;
            }
        }
        if ( sequence_index_13e == 2 )
        {
            v141 = time_counter_144;
            // The target consumes +0x730/+0x734 as signed words (JGE at 0x538AD1).
            if ( v141 >= 60
                && !(v141 % word_732)
                && word_730 < word_734 )
            {
                v478[0] = (float)(unsigned int)selector_random_roll(0x168u);
                v478[1] = 20.0;
                v478[2] = 8.0;
                spawn_owned_object_via_manager(
                    901,
                    (float)(unsigned int)selector_random_roll(0x4B0u) + 40.0,
                    (float)(unsigned int)selector_random_roll(0x280u) + 100.0,
                    (unsigned char)facing_104,
                    1,
                    v478,
                    3);
                ++word_730;
            }
            velocity_x_f4 = velocity_x_f4 - 1.0;
            if ( velocity_x_f4 < 0.0 )
                velocity_x_f4 = 0.0;
            if ( time_counter_144 >= 270 )
            {
                select_sequence(3);
                facing_104 = -facing_104;
                velocity_x_f4 = 25.0;
            }
        }
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(700);
        if ( time_counter_144 )
            goto LABEL_1674;
        if ( !frame_timer_142
            && !frame_index_140
            && sequence_index_13e == 1
            && (unsigned int)selector_random_roll(0x64u) <= 0x32u )
        {
            // Target physical branch order is 3, 2, 1, 0.
            switch ( g_match_identifier )
            {
            case 3:
                word_732 = 10;
                word_734 = 20;
                break;
            case 2:
                word_732 = 13;
                word_734 = 15;
                break;
            case 1:
                word_732 = 16;
                word_734 = 12;
                break;
            case 0:
                word_732 = 20;
                word_734 = 10;
                break;
            default:
                break;
            }
            word_732 = 10;
            word_734 = 20;
            select_sequence(2);
            return;
        }
        if ( sequence_entry(4) )
        {
            {
                set_action_and_finalize(700);
                return;
            }
        }
    LABEL_1674:
        ;
        if ( sequence_index_13e )
            goto LABEL_1683;
        if ( frame_timer_142 )
            goto LABEL_1678;
        if ( frame_index_140 != 7 )
            goto LABEL_1683;
        velocity_x_f4 = 30.0;
        v428 = (double)(200 * facing_104) + x_ec;
        emit_fighter_effect_433cc0(128, v428, y_f0, facing_104, -1);
        field_108 = 35.0;
        field_10c = 70.0;
        dispatch_character_wave_handle(0x32u);
        ;
    LABEL_1678:
        if ( frame_index_140 == 7 )
        {
            field_11c = field_11c + static_cast<double>(0.2f);
            field_120 = field_120 - static_cast<double>(0.2f);
            if ( field_120 < 0.0 )
                field_120 = 0.0;
            if ( field_11c > 3.0 )
                field_11c = 3.0;
        }
        else
        {
        LABEL_1683:
            ;
        }
        if ( sequence_index_13e == 3 )
        {
            if ( frame_index_140 )
            {
            }
            else
            {
                field_11c = field_11c - static_cast<double>(0.2f);
                field_120 = static_cast<double>(0.2f) + field_120;
                if ( field_120 > 1.0 )
                    field_120 = 1.0;
                if ( field_11c < 1.0 )
                    field_11c = 1.0;
            }
            if ( frame_index_140 >= 2 )
            {
                velocity_x_f4 = velocity_x_f4 - 0.5;
                if ( velocity_x_f4 < 0.0 )
                    velocity_x_f4 = 0.0;
            }
            if ( !frame_timer_142 && frame_index_140 == 1 )
                reinterpret_cast<FighterActionScratchView *>(raw + 4)->reset();
        }
        return;
    case 730:
        resolve_stage_surface_landing_transition();
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(700);
        if ( !sequence_index_13e && !frame_timer_142 && frame_index_140 == 11 )
        {
            v480[0] = 0.0;
            v480[1] = 10.0;
            v480[2] = 5.0;
            int facing = (unsigned char)facing_104;
            v429 = (double)(100 * (char)facing) + x_ec;
            spawn_owned_object_via_manager(902,
                v429,
                y_f0,
                facing,
                1,
                v480,
                3);
            dispatch_character_wave_handle(0x34u);
            goto LABEL_1593;
        }
        return;
    case 731:
        resolve_stage_surface_landing_transition();
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(700);
        if ( !sequence_index_13e && !frame_timer_142 && frame_index_140 == 6 )
        {
            v482[0] = 0.0;
            v482[1] = 120.0;
            v482[2] = 6.0;
            v185 = (unsigned char)facing_104;
            v173 = y_f0 - 20.0;
            v431 = (double)(100 * (char)v185) + x_ec;
            spawn_owned_object_via_manager(902, v431, v173, v185, 1, v482, 3);
            dispatch_character_wave_handle(0x37u);
        LABEL_1593:
            publish_battle_layout_scalar(10.0);
        }
        return;
    case 740:
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        if ( sequence_index_13e )
            goto LABEL_1720;
        if ( frame_timer_142 )
            goto LABEL_1715;
        if ( frame_index_140 == 7 )
        {
            velocity_x_f4 = 30.0;
            v226 = (unsigned char)facing_104;
            v432 = (double)(200 * (char)v226) + x_ec;
            emit_fighter_effect_433cc0(128, v432, y_f0, v226, -1);
            field_108 = 35.0;
            field_10c = 70.0;
            dispatch_character_wave_handle(0x32u);
            word_7e6 = 10;
        LABEL_1715:
            if ( frame_index_140 == 7 )
            {
                field_11c = field_11c + 0.2f;
                field_120 = field_120 - 0.2f;
                if ( field_120 < 0.0 )
                    field_120 = 0.0;
                if ( field_11c > 3.0 )
                    field_11c = 3.0;
            }
        }
    LABEL_1720:
        if ( sequence_index_13e == 1 )
        {
            if ( !time_counter_144 && !frame_timer_142 && !frame_index_140 )
                reinterpret_cast<FighterActionScratchView *>(raw + 4)->reset();
            velocity_x_f4 = (640.0 - x_ec) / 30.0 * (double)facing_104;
            velocity_y_f8 = (350.0 - y_f0) / 30.0;
            if ( velocity_x_f4 > 30.0 )
                velocity_x_f4 = 30.0;
            if ( velocity_x_f4 < -30.0 )
                velocity_x_f4 = -30.0;
            if ( velocity_y_f8 > 30.0 )
                velocity_y_f8 = 30.0;
            if ( velocity_y_f8 < -30.0 )
                velocity_y_f8 = -30.0;
            if ( time_counter_144 >= 120 )
            { next_sequence_block(); return; }
        }
        if ( sequence_index_13e == 2 )
        {
            x_ec = 640.0;
            y_f0 = 350.0;
        }
        return;
    case 770:
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(700);
        if ( !sequence_index_13e && !frame_timer_142 && frame_index_140 == 7 )
        {
            byte_655 = 1;
            finalize_sequence_entry(-1);
            publish_texture_state(2, -1);
            copy_action_word_176_to_174();
            word_76c = 0;
            word_76a = 1;
            word_766 = 0;
            word_768 = 0;
            word_764 = 0;
            dispatch_indexed_event_member(0x17u);
        }
        return;
    case 795:
        if (sequence_index_13e == 0) {
            velocity_y_f8 -= 0.3f;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                select_sequence(1);
                y_f0 = stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                dispatch_indexed_event_member(30);
                return;
            }
        }
        if (advance_frame_and_dispatch()) set_action_and_finalize(700);
        return;
    case 797:
        if ( !sequence_index_13e )
        {
            velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
            if ( (unsigned char)has_crossed_stage_surface_while_descending() )
            {
                dispatch_indexed_event_member(0x1Eu);
                select_sequence(1);
                y_f0 = stage_surface_height_at_x(this);
                velocity_y_f8 = 0.0;
                return;
            }
        }
        if ( sequence_index_13e == 1 )
        {
            velocity_x_f4 = velocity_x_f4 - 0.2f;
            if ( velocity_x_f4 < 0.0 )
                velocity_x_f4 = 0.0;
            if ( x_ec > 480.0 )
            {
                x_ec = 480.0;
                velocity_x_f4 = 0.0;
            }
        }
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(0);
        return;
    case 798:
        if ( !sequence_index_13e )
        {
            velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
            if ( (unsigned char)has_crossed_stage_surface_while_descending() )
            {
                dispatch_indexed_event_member(0x1Eu);
                select_sequence(1);
                y_f0 = stage_surface_height_at_x(this);
                velocity_y_f8 = 0.0;
                return;
            }
        }
        if ( sequence_index_13e == 1 )
        {
            velocity_x_f4 = velocity_x_f4 - 0.2f;
            if ( velocity_x_f4 < 0.0 )
                velocity_x_f4 = 0.0;
            if ( x_ec < 800.0 )
            {
                x_ec = 800.0;
                velocity_x_f4 = 0.0;
            }
        }
        if ( (unsigned char)advance_frame_and_dispatch() )
            set_action_and_finalize(700);
        return;
    default:
        update_common_action_state();
        return;
    }
    advance_frame_and_dispatch();
}

} // namespace th105
