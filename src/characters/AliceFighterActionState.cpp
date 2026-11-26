#include <stddef.h>
namespace th105 {
unsigned __cdecl mt19937_next_u32();
// Pointer-only primary call view; the concrete owner is not recovered.
class AliceFighterActionStateView {
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
 unsigned char try_dispatch_directional_action_208_210(int);
 void dispatch_indexed_event_member(unsigned);
 void dispatch_character_wave_handle(unsigned);
 void emit_fighter_effect_433cc0(int,float,float,unsigned char,int);
 void adjust_counter_482(short,int);
 int add_phase_scaled_counter_558(int);
 void face_opponent_and_flip_horizontal_velocity();
 int spawn_owned_object_via_manager(int,float,float,signed char,int,const void *,int);
 void publish_texture_state(signed char,short);
 void dispatch_indexed_sequence_window_45c8b0(signed char,int,int);
 void advance_secondary_event_effect_cycle();
 void finalize_sequence_entry(int);
 void copy_action_word_176_to_174();
 void update_common_action_state();
 __forceinline void idle_motion() {
  if(!byte_47e)zero_velocity_acceleration();else {
   if(velocity_x_f4>0.0){velocity_x_f4-=0.5;if(velocity_x_f4<0.0){zero_velocity_acceleration();byte_47e=0;}}
   if(velocity_x_f4<0.0){velocity_x_f4+=0.5;if(velocity_x_f4>0.0){zero_velocity_acceleration();byte_47e=0;}}
  }
 }
 __forceinline void dash_dust(bool reverse) {
  double base=x_ec+50.0;
  emit_fighter_effect_433cc0(124,
   static_cast<float>(base-static_cast<float>(mt19937_next_u32()%100u)),
   static_cast<float>(static_cast<float>(mt19937_next_u32()%200u)+y_f0),
   reverse?static_cast<unsigned char>(-facing_104):static_cast<unsigned char>(facing_104),1);
 }
 void dispatch_action_state();
 unsigned char unknown_004[0xe8];
 float x_ec;
 float y_f0;
 float velocity_x_f4;
 float velocity_y_f8;
 unsigned char unknown_0fc[0x4];
 float acceleration_y_100;
 signed char facing_104;
 unsigned char unknown_105[0x27];
 float orientation_12c;
 unsigned char unknown_130[0xc];
 short action_id_13c;
 short sequence_index_13e;
 short frame_index_140;
 short frame_timer_142;
 int time_counter_144;
 unsigned char unknown_148[0x28];
 AliceFighterActionStateView * related_170;
 short word_174;
 unsigned char unknown_176[0xa];
 int field_180;
 unsigned char unknown_184[0x2];
 short word_186;
 unsigned char unknown_188[0x2f6];
 unsigned char byte_47e;
 unsigned char unknown_47f[0x3];
 short word_482;
 unsigned char unknown_484[0x6];
 short word_48a;
 short word_48c;
 unsigned char unknown_48e[0x1a];
 short word_4a8;
 unsigned char unknown_4aa[0x2];
 short word_4ac;
 unsigned short word_4ae;
 unsigned char unknown_4b0[0x8];
 unsigned field_4b8;
 unsigned char unknown_4bc[0x149];
 signed char byte_605;
 unsigned char unknown_606[0x3];
 signed char byte_609;
 unsigned char unknown_60a[0x5];
 signed char byte_60f;
 unsigned char unknown_610[0x45];
 unsigned char byte_655;
 unsigned char unknown_656[0x5e];
 int field_6b4;
 int field_6b8;
 unsigned field_6bc;
 int field_6c0;
 int field_6c4;
 int field_6c8;
 unsigned char unknown_6cc[0x60];
 unsigned char byte_72c;
 unsigned char unknown_72d[0x3];
 short word_730;
 union {short word_732; unsigned char byte_732;};
 short word_734;
 short word_736;
 unsigned char unknown_738[0x4];
 float field_73c;
 float field_740;
 unsigned char unknown_744[0xc];
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
 union {int field_7a4; struct {short word_7a4; short word_7a6;};};
 unsigned char unknown_7a8[0x4];
 short word_7ac;
 unsigned char unknown_7ae[0x2];
 float field_7b0[4];
 float field_7c0[4];
 unsigned char byte_7d0;
};
struct AliceFighterScratchView { void reset(); };
float __fastcall alice_stage_surface_height_at_x(AliceFighterActionStateView *);
int __fastcall is_y_at_or_below_stage_surface(void *);
extern int g_match_identifier;
unsigned __cdecl mt19937_next_u32();
int __cdecl selector_random_roll(int);
float __cdecl atan2_degrees(float,float);
float __cdecl lookup_orientation_sine_quantized_abs(float);
float __cdecl lookup_orientation_cosine_quantized_abs(float);
typedef char check_x_ec[offsetof(AliceFighterActionStateView,x_ec)==0xec?1:-1];
typedef char check_y_f0[offsetof(AliceFighterActionStateView,y_f0)==0xf0?1:-1];
typedef char check_velocity_x_f4[offsetof(AliceFighterActionStateView,velocity_x_f4)==0xf4?1:-1];
typedef char check_velocity_y_f8[offsetof(AliceFighterActionStateView,velocity_y_f8)==0xf8?1:-1];
typedef char check_acceleration_y_100[offsetof(AliceFighterActionStateView,acceleration_y_100)==0x100?1:-1];
typedef char check_facing_104[offsetof(AliceFighterActionStateView,facing_104)==0x104?1:-1];
typedef char check_orientation_12c[offsetof(AliceFighterActionStateView,orientation_12c)==0x12c?1:-1];
typedef char check_action_id_13c[offsetof(AliceFighterActionStateView,action_id_13c)==0x13c?1:-1];
typedef char check_sequence_index_13e[offsetof(AliceFighterActionStateView,sequence_index_13e)==0x13e?1:-1];
typedef char check_frame_index_140[offsetof(AliceFighterActionStateView,frame_index_140)==0x140?1:-1];
typedef char check_frame_timer_142[offsetof(AliceFighterActionStateView,frame_timer_142)==0x142?1:-1];
typedef char check_time_counter_144[offsetof(AliceFighterActionStateView,time_counter_144)==0x144?1:-1];
typedef char check_related_170[offsetof(AliceFighterActionStateView,related_170)==0x170?1:-1];
typedef char check_word_174[offsetof(AliceFighterActionStateView,word_174)==0x174?1:-1];
typedef char check_field_180[offsetof(AliceFighterActionStateView,field_180)==0x180?1:-1];
typedef char check_word_186[offsetof(AliceFighterActionStateView,word_186)==0x186?1:-1];
typedef char check_byte_47e[offsetof(AliceFighterActionStateView,byte_47e)==0x47e?1:-1];
typedef char check_word_482[offsetof(AliceFighterActionStateView,word_482)==0x482?1:-1];
typedef char check_word_48a[offsetof(AliceFighterActionStateView,word_48a)==0x48a?1:-1];
typedef char check_word_48c[offsetof(AliceFighterActionStateView,word_48c)==0x48c?1:-1];
typedef char check_word_4a8[offsetof(AliceFighterActionStateView,word_4a8)==0x4a8?1:-1];
typedef char check_word_4ac[offsetof(AliceFighterActionStateView,word_4ac)==0x4ac?1:-1];
typedef char check_word_4ae[offsetof(AliceFighterActionStateView,word_4ae)==0x4ae?1:-1];
typedef char check_field_4b8[offsetof(AliceFighterActionStateView,field_4b8)==0x4b8?1:-1];
typedef char check_byte_605[offsetof(AliceFighterActionStateView,byte_605)==0x605?1:-1];
typedef char check_byte_609[offsetof(AliceFighterActionStateView,byte_609)==0x609?1:-1];
typedef char check_byte_60f[offsetof(AliceFighterActionStateView,byte_60f)==0x60f?1:-1];
typedef char check_byte_655[offsetof(AliceFighterActionStateView,byte_655)==0x655?1:-1];
typedef char check_field_6b4[offsetof(AliceFighterActionStateView,field_6b4)==0x6b4?1:-1];
typedef char check_field_6b8[offsetof(AliceFighterActionStateView,field_6b8)==0x6b8?1:-1];
typedef char check_field_6bc[offsetof(AliceFighterActionStateView,field_6bc)==0x6bc?1:-1];
typedef char check_field_6c0[offsetof(AliceFighterActionStateView,field_6c0)==0x6c0?1:-1];
typedef char check_field_6c4[offsetof(AliceFighterActionStateView,field_6c4)==0x6c4?1:-1];
typedef char check_field_6c8[offsetof(AliceFighterActionStateView,field_6c8)==0x6c8?1:-1];
typedef char check_byte_72c[offsetof(AliceFighterActionStateView,byte_72c)==0x72c?1:-1];
typedef char check_word_730[offsetof(AliceFighterActionStateView,word_730)==0x730?1:-1];
typedef char check_byte_732[offsetof(AliceFighterActionStateView,byte_732)==0x732?1:-1];
typedef char check_word_732[offsetof(AliceFighterActionStateView,word_732)==0x732?1:-1];
typedef char check_word_734[offsetof(AliceFighterActionStateView,word_734)==0x734?1:-1];
typedef char check_word_736[offsetof(AliceFighterActionStateView,word_736)==0x736?1:-1];
typedef char check_field_73c[offsetof(AliceFighterActionStateView,field_73c)==0x73c?1:-1];
typedef char check_field_740[offsetof(AliceFighterActionStateView,field_740)==0x740?1:-1];
typedef char check_byte_750[offsetof(AliceFighterActionStateView,byte_750)==0x750?1:-1];
typedef char check_byte_751[offsetof(AliceFighterActionStateView,byte_751)==0x751?1:-1];
typedef char check_word_764[offsetof(AliceFighterActionStateView,word_764)==0x764?1:-1];
typedef char check_word_766[offsetof(AliceFighterActionStateView,word_766)==0x766?1:-1];
typedef char check_word_768[offsetof(AliceFighterActionStateView,word_768)==0x768?1:-1];
typedef char check_word_76a[offsetof(AliceFighterActionStateView,word_76a)==0x76a?1:-1];
typedef char check_word_76c[offsetof(AliceFighterActionStateView,word_76c)==0x76c?1:-1];
typedef char check_word_7a0[offsetof(AliceFighterActionStateView,word_7a0)==0x7a0?1:-1];
typedef char check_word_7a2[offsetof(AliceFighterActionStateView,word_7a2)==0x7a2?1:-1];
typedef char check_word_7a4[offsetof(AliceFighterActionStateView,word_7a4)==0x7a4?1:-1];
typedef char check_word_7a6[offsetof(AliceFighterActionStateView,word_7a6)==0x7a6?1:-1];
typedef char check_field_7a4[offsetof(AliceFighterActionStateView,field_7a4)==0x7a4?1:-1];
typedef char check_word_7ac[offsetof(AliceFighterActionStateView,word_7ac)==0x7ac?1:-1];
typedef char check_field_7b0[offsetof(AliceFighterActionStateView,field_7b0)==0x7b0?1:-1];
typedef char check_field_7c0[offsetof(AliceFighterActionStateView,field_7c0)==0x7c0?1:-1];
typedef char check_byte_7d0[offsetof(AliceFighterActionStateView,byte_7d0)==0x7d0?1:-1];
}
// JP1.06a Alice Fighter +0x28 root; offsets retain descriptive names where semantics are unknown.
// See docs/ALICE_FIGHTER_UPDATE_2026_10_25.md.

namespace th105 {
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


 word_7a0=0; word_7a2=100;
 ++word_7ac; if(word_7ac>=360) word_7ac=0;
 if(word_174<=0) field_7a4=0;
 if(action_id_13c>149 && action_id_13c<159 && byte_751==0) {
  byte_751=1;
  if(action_id_13c>149 && action_id_13c<154)
   SPAWN(998,static_cast<float>(60*facing_104+x_ec),static_cast<float>(y_f0+110.0),static_cast<unsigned char>(facing_104),1,0,0);
  if(action_id_13c>153 && action_id_13c<158)
   SPAWN(998,static_cast<float>(60*facing_104+x_ec),static_cast<float>(y_f0+60.0),static_cast<unsigned char>(facing_104),1,0,0);
  if(action_id_13c==158)
   SPAWN(998,static_cast<float>(60*facing_104+x_ec),static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1,0,0);
 }
 if(word_186!=0 || related_170->word_48c!=0) return;
 switch(action_id_13c) {
case 0: RESOLVE();if(velocity_x_f4==0.0)byte_47e=0;idle_motion();break;
case 1: RESOLVE();idle_motion();if(FRAME()&&!frame_index_140)ACTION(2);return;
case 2: RESOLVE();idle_motion();break;
case 3: RESOLVE();idle_motion();if(FRAME()&&!frame_index_140)ACTION(0);return;
case 4: RESOLVE();velocity_x_f4=6.0;break;
case 5: RESOLVE();velocity_x_f4=-6.0;break;

    case 6:
        if (!static_cast<unsigned short>(sequence_index_13e)) {
            resolve_stage_surface_landing_transition();
            if (!static_cast<unsigned short>(sequence_index_13e) && !byte_47e)
                zero_velocity_acceleration();
        }
        if (sequence_index_13e > 0) {
            velocity_y_f8 =
                velocity_y_f8 - acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                set_action_and_finalize(10);
                y_f0 = alice_stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                return;
            }
        }
        advance_frame_and_dispatch();
        if (static_cast<unsigned>(time_counter_144)
            || static_cast<unsigned short>(frame_timer_142)
            || static_cast<unsigned short>(frame_index_140)
            || static_cast<unsigned short>(sequence_index_13e) != 1)
            return;
        velocity_x_f4 = 0.0f;
        velocity_y_f8 = 15.0f;
        acceleration_y_100 = 0.65f;
        byte_47e = 0;
        return;

    case 7:
        if (!static_cast<unsigned short>(sequence_index_13e)) {
            resolve_stage_surface_landing_transition();
            if (!static_cast<unsigned short>(sequence_index_13e) && !byte_47e)
                zero_velocity_acceleration();
        }
        if (sequence_index_13e > 0) {
            velocity_y_f8 =
                velocity_y_f8 - acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                set_action_and_finalize(10);
                y_f0 = alice_stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                return;
            }
        }
        advance_frame_and_dispatch();
        if (static_cast<unsigned>(time_counter_144)
            || static_cast<unsigned short>(frame_timer_142)
            || static_cast<unsigned short>(frame_index_140)
            || static_cast<unsigned short>(sequence_index_13e) != 1)
            return;
        velocity_x_f4 = 5.0f;
        velocity_y_f8 = 15.0f;
        acceleration_y_100 = 0.65f;
        byte_47e = 0;
        return;

    case 8:
        if (!static_cast<unsigned short>(sequence_index_13e)) {
            resolve_stage_surface_landing_transition();
            if (!static_cast<unsigned short>(sequence_index_13e) && !byte_47e)
                zero_velocity_acceleration();
        }
        if (sequence_index_13e > 0) {
            velocity_y_f8 =
                velocity_y_f8 - acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                set_action_and_finalize(10);
                y_f0 = alice_stage_surface_height_at_x(this);
                zero_velocity_acceleration();
                return;
            }
        }
        advance_frame_and_dispatch();
        if (static_cast<unsigned>(time_counter_144)
            || static_cast<unsigned short>(frame_timer_142)
            || static_cast<unsigned short>(frame_index_140)
            || static_cast<unsigned short>(sequence_index_13e) != 1)
            return;
        velocity_x_f4 = -5.0f;
        velocity_y_f8 = 15.0f;
        acceleration_y_100 = 0.65f;
        byte_47e = 0;
        return;


    case 9:
        if (!acceleration_y_100)
            acceleration_y_100 = 0.6000000238418579f;
        velocity_y_f8 =
            velocity_y_f8 - acceleration_y_100;
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            set_action_and_finalize(10);
            y_f0 = alice_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        break;

    case 10:
        resolve_stage_surface_landing_transition();
        zero_velocity_acceleration();
        if (advance_frame_and_dispatch()) {
            if (!static_cast<unsigned>(field_6b8))
                set_action_and_finalize(0);
            else
                set_action_and_finalize(2);
        }
        return;


    case 197: {


        resolve_stage_surface_landing_transition();
        if (advance_frame_and_dispatch()) {
            if (byte_72c == 2) {
                set_action_and_finalize(700);
                word_4a8 = 3;
                word_4ac = 3;
                return;
            }
            set_action_and_finalize(0);
            if (field_6b8 > 0)
                set_action_and_finalize(1);
        }
        if (!static_cast<unsigned short>(frame_timer_142) && static_cast<unsigned short>(frame_index_140) == 8)
            zero_velocity_acceleration();
        if (!static_cast<unsigned short>(frame_timer_142) && static_cast<unsigned short>(frame_index_140) == 13) {
            if (x_ec > related_170->x_ec)
                facing_104 = -1;
            if (x_ec < related_170->x_ec)
                facing_104 = 1;
        }
        return;
    }

    case 198: {


        resolve_stage_surface_landing_transition();
        if (advance_frame_and_dispatch()) {
            if (byte_72c == 2) {
                set_action_and_finalize(700);
                word_4a8 = 3;
                word_4ac = 3;
                return;
            }
            set_action_and_finalize(0);
            if (field_6b8 > 0)
                set_action_and_finalize(1);
        }
        if (!static_cast<unsigned short>(frame_timer_142) && static_cast<unsigned short>(frame_index_140) == 8)
            zero_velocity_acceleration();
        if (!static_cast<unsigned short>(frame_timer_142) && static_cast<unsigned short>(frame_index_140) == 13) {
            if (x_ec > related_170->x_ec)
                facing_104 = -1;
            if (x_ec < related_170->x_ec)
                facing_104 = 1;
        }
        return;
    }

    case 199: {


        resolve_stage_surface_landing_transition();
        if (advance_frame_and_dispatch()) {
            if (byte_72c == 2) {
                set_action_and_finalize(700);
                word_4a8 = 3;
                word_4ac = 3;
                return;
            }
            set_action_and_finalize(0);
            if (field_6b8 > 0)
                set_action_and_finalize(1);
        }
        if (!static_cast<unsigned short>(frame_timer_142) && static_cast<unsigned short>(frame_index_140) == 5) {
            if (x_ec > related_170->x_ec)
                facing_104 = -1;
            if (x_ec < related_170->x_ec)
                facing_104 = 1;
        }
        return;
    }

    case 200: {

        int input_product;

        resolve_stage_surface_landing_transition();
        byte_47e = 1;
        if (velocity_x_f4 > 9.0f) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.5);
            if (velocity_x_f4 < 9.0f)
                velocity_x_f4 = 9.0f;
        }
        advance_frame_and_dispatch();
        if (static_cast<unsigned short>(sequence_index_13e) == 1) {
            if (!(time_counter_144 % 5)) {
                dash_dust(false);
            }
            if (field_6b8<0) {
                input_product = static_cast<signed char>(static_cast<unsigned char>(facing_104))
                    * field_6b4;
                if (input_product > 0)
                    set_action_and_finalize(212);
                else
                    set_action_and_finalize(211);
                return;
            }
            ++word_730;
            if ((facing_104*field_6b4<=0 && word_730>5) || word_730>45) {
                set_action_and_finalize(204);
                return;
            }
        }
        if (!static_cast<unsigned short>(sequence_index_13e)
            && static_cast<unsigned short>(frame_index_140) == 2
            && !static_cast<unsigned short>(frame_timer_142)) {
            velocity_x_f4 = 10.0f;
            emit_fighter_effect_433cc0(
                125,
                x_ec + static_cast<float>(80 * facing_104),
                static_cast<float>(y_f0 + 80.0),
                static_cast<unsigned char>(facing_104),
                1);
            emit_fighter_effect_433cc0(
                126,
                x_ec,
                static_cast<float>(y_f0 + 80.0),
                static_cast<unsigned char>(facing_104),
                1);
            dispatch_indexed_event_member(0x1Fu);
        }
        return;
    }

    case 201: {


        if (!static_cast<unsigned short>(sequence_index_13e)
            && static_cast<__int16>(static_cast<unsigned short>(frame_index_140)) <= 1)
            resolve_stage_surface_landing_transition();
        if (static_cast<unsigned short>(sequence_index_13e) == 3) {
            resolve_stage_surface_landing_transition();
            velocity_x_f4 = static_cast<float>(velocity_x_f4 + 2.0);
            if (velocity_x_f4 > 0.0f)
                velocity_x_f4 = 0.0f;
        }
        if (!static_cast<unsigned char>(is_y_at_or_below_stage_surface(this)) && !(time_counter_144 % 5)) {
            dash_dust(true);
        }
        if (static_cast<__int16>(static_cast<unsigned short>(sequence_index_13e)) < 3) {
            velocity_y_f8 =
                velocity_y_f8 - acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                velocity_y_f8 = 0.0f;
                y_f0 = alice_stage_surface_height_at_x(this);
                select_sequence(3);
                return;
            }
        }
        if (advance_frame_and_dispatch()) {
            set_action_and_finalize(0);
            velocity_x_f4 = 0.0f;
            return;
        }
        if (!static_cast<unsigned short>(sequence_index_13e)
            && !static_cast<unsigned short>(frame_timer_142)
            && static_cast<unsigned short>(frame_index_140) == 2) {
            velocity_x_f4 = -10.0f;
            velocity_y_f8 = 4.5f;
            acceleration_y_100 = 0.6000000238418579f;
            emit_fighter_effect_433cc0(
                125,
                x_ec,
                static_cast<float>(y_f0 + 80.0),
                static_cast<unsigned char>(-facing_104),
                1);
            emit_fighter_effect_433cc0(
                126,
                x_ec,
                static_cast<float>(y_f0 + 80.0),
                static_cast<unsigned char>(-facing_104),
                1);
            dispatch_indexed_event_member(0x1Fu);
        }
        return;
    }

    case 202: {


        velocity_y_f8 =
            velocity_y_f8 - acceleration_y_100;
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            zero_velocity_acceleration();
            y_f0 = alice_stage_surface_height_at_x(this);
            set_action_and_finalize(10);
            return;
        }
        if ((static_cast<unsigned short>(sequence_index_13e) == 1 || static_cast<unsigned short>(sequence_index_13e) == 2)
            && !(time_counter_144 % 5)) {
            dash_dust(false);
        }
        advance_frame_and_dispatch();
        if (!static_cast<unsigned short>(sequence_index_13e)
            && !static_cast<unsigned short>(frame_timer_142)
            && static_cast<unsigned short>(frame_index_140) == 2) {
            word_730 = 0;
            velocity_x_f4 = 8.5f;
            velocity_y_f8 = 5.0f;
            acceleration_y_100 = 0.6000000238418579f;
            emit_fighter_effect_433cc0(
                125,
                x_ec + static_cast<float>(80 * facing_104),
                static_cast<float>(y_f0 + 110.0),
                static_cast<unsigned char>(facing_104),
                1);
            emit_fighter_effect_433cc0(
                126,
                x_ec,
                static_cast<float>(y_f0 + 110.0),
                static_cast<unsigned char>(facing_104),
                1);
            dispatch_indexed_event_member(0x1Fu);
        }
        if (!time_counter_144
            && !static_cast<unsigned short>(frame_timer_142)
            && !static_cast<unsigned short>(frame_index_140)
            && static_cast<unsigned short>(sequence_index_13e) == 2)
            face_opponent_and_flip_horizontal_velocity();
        return;
    }

    case 203: {


        velocity_y_f8 =
            velocity_y_f8 - acceleration_y_100;
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            zero_velocity_acceleration();
            y_f0 = alice_stage_surface_height_at_x(this);
            frame_timer_142 = 0;
            set_action_and_finalize(10);
            return;
        }
        if (static_cast<__int16>(static_cast<unsigned short>(sequence_index_13e)) < 3
            && !(time_counter_144 % 5)) {
            dash_dust(true);
        }
        advance_frame_and_dispatch();
        if (!static_cast<unsigned short>(sequence_index_13e)
            && !static_cast<unsigned short>(frame_timer_142)
            && static_cast<unsigned short>(frame_index_140) == 1) {
            velocity_x_f4 = -8.5f;
            velocity_y_f8 = 5.0f;
            acceleration_y_100 = 0.6000000238418579f;
            emit_fighter_effect_433cc0(
                125,
                x_ec,
                static_cast<float>(y_f0 + 120.0),
                static_cast<unsigned char>(-facing_104),
                1);
            emit_fighter_effect_433cc0(
                126,
                x_ec,
                static_cast<float>(y_f0 + 120.0),
                static_cast<unsigned char>(-facing_104),
                1);
            dispatch_indexed_event_member(0x1Fu);
        }
        if (!time_counter_144
            && !static_cast<unsigned short>(frame_timer_142)
            && !static_cast<unsigned short>(frame_index_140)
            && static_cast<unsigned short>(sequence_index_13e) == 2)
            face_opponent_and_flip_horizontal_velocity();
        return;
    }

    case 204:
        resolve_stage_surface_landing_transition();
        velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.5);
            if (velocity_x_f4 < 0.0f) {
            velocity_x_f4 = 0.0f;
            byte_47e = 0;
        }
        if (advance_frame_and_dispatch()) {
            set_action_and_finalize(0);
            byte_47e = 0;
        }
        return;


    case 208:
        if (!static_cast<unsigned short>(sequence_index_13e))
            resolve_stage_surface_landing_transition();
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            set_action_and_finalize(10);
            y_f0 = alice_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if (static_cast<unsigned char>(is_y_at_or_below_stage_surface(this)) || velocity_y_f8 > 0.0f)
            word_4ae = 2;
        if (static_cast<__int16>(static_cast<unsigned short>(sequence_index_13e)) > 0) {
            velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
            if (velocity_y_f8 < -20.0f)
                velocity_y_f8 = -20.0f;
        }
        advance_frame_and_dispatch();
        if (!time_counter_144
            && !static_cast<unsigned short>(frame_timer_142)
            && !static_cast<unsigned short>(frame_index_140)
            && static_cast<unsigned short>(sequence_index_13e) == 1) {
            velocity_x_f4 = 0.0f;
            velocity_y_f8 = 19.0f;
            acceleration_y_100 = 0.65f;
            byte_47e = 0;
            emit_fighter_effect_433cc0(
                63,
                x_ec,
                y_f0,
                static_cast<unsigned char>(facing_104),
                1);
        }
        return;

    case 211:
        if (!static_cast<unsigned short>(sequence_index_13e))
            resolve_stage_surface_landing_transition();
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            set_action_and_finalize(10);
            y_f0 = alice_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if (static_cast<unsigned char>(is_y_at_or_below_stage_surface(this)) || velocity_y_f8 > 0.0f)
            word_4ae = 2;
        if (static_cast<__int16>(static_cast<unsigned short>(sequence_index_13e)) > 0) {
            velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
            if (velocity_y_f8 < -20.0f)
                velocity_y_f8 = -20.0f;
        }
        advance_frame_and_dispatch();
        if (!time_counter_144
            && !static_cast<unsigned short>(frame_timer_142)
            && !static_cast<unsigned short>(frame_index_140)
            && static_cast<unsigned short>(sequence_index_13e) == 1) {
            velocity_x_f4 = 2.0f;
            velocity_y_f8 = 19.0f;
            acceleration_y_100 = 0.65f;
            byte_47e = 0;
            emit_fighter_effect_433cc0(
                63,
                x_ec,
                y_f0,
                static_cast<unsigned char>(facing_104),
                1);
        }
        return;


    case 214: {
        if (FRAME()) { ACTION(9); return; }
        if (time_counter_144==0) {
            if (frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==1) EVENT(31);
            if (time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==6) { ACTION(9); return; }
        }
                if (field_6b8 > 0) {
                    if (facing_104 * field_6b4 > 0) word_732 = -45;
                    else if (facing_104 * field_6b4 < 0) word_732 = -135;
                    else word_732 = -90;
                }
                else if (field_6b8 < 0) {
                    if (facing_104 * field_6b4 > 0) word_732 = 45;
                    else if (facing_104 * field_6b4 < 0) word_732 = 135;
                    else word_732 = 90;
                }
                else {
                    if (facing_104 * field_6b4 > 0) word_732 = 0;
                    else if (facing_104 * field_6b4 < 0) word_732 = 180;
                }
                if (sequence_index_13e == 5 || sequence_index_13e == 6)                 velocity_y_f8 -= acceleration_y_100;
                if (sequence_index_13e > 0 && sequence_index_13e < 5) {
                    ++word_736;
                    word_734 = static_cast<short>(word_732 - static_cast<short>(static_cast<int>(field_740)));
                    if (word_734 > 180) word_734 -= 360;
                    if (word_734 < -180) word_734 += 360;
                    if (word_734 > 0) {
                        if (field_4b8 == 0) field_740 = static_cast<float>(field_740 + 1.5);
                        else field_740 = static_cast<float>(field_740 + 0.5);
                    }
                    if (word_734 < 0) {
                        if (field_4b8 == 0) field_740 = static_cast<float>(field_740 - 1.5);
                        else field_740 = static_cast<float>(field_740 - 0.5);
                    }
                    velocity_x_f4 = lookup_orientation_cosine_quantized_abs(field_740) * field_73c;
                    velocity_y_f8 = lookup_orientation_sine_quantized_abs(field_740) * field_73c;
                    if (y_f0 > 680.0 && velocity_y_f8 > 0.0) velocity_y_f8 = 0.0f;
                    field_73c = static_cast<float>(field_73c + static_cast<double>(0.3f));
                    if (field_73c > 12.0f) field_73c = 12.0f;
                    if (field_4b8 == 0) adjust_counter_482(5, 1);
                    else adjust_counter_482(10, 1);
                    orientation_12c = -field_740;
                    if (velocity_x_f4 < 0.0) orientation_12c = 180.0 - field_740;
                    if (velocity_x_f4 < 0.0 && sequence_index_13e == 1) select_sequence(3);
                    if (velocity_x_f4 >= 0.0 && sequence_index_13e == 3) select_sequence(1);
                    if (velocity_x_f4 < 0.0 && sequence_index_13e == 2) select_sequence(4);
                    if (velocity_x_f4 >= 0.0 && sequence_index_13e == 4) select_sequence(2);
                    if (time_counter_144 % 5 == 1) {
                        emit_fighter_effect_433cc0(125,                         lookup_orientation_cosine_quantized_abs(field_740) * 100.0 * facing_104 + x_ec,                         lookup_orientation_sine_quantized_abs(field_740) * 100.0 + y_f0 + 100.0,                         facing_104, 1);
                    }
                    if ((field_6c8 == 0 && word_736 > 10) || word_482 <= 0) {
                        if ((field_6c8 == 0 && word_736 > 10) || word_482 <= 0) {
                            reinterpret_cast<AliceFighterScratchView *>(reinterpret_cast<unsigned char *>(this)+4)->reset();
                            if (sequence_index_13e == 1 || sequence_index_13e == 2) {
                                if (facing_104 == 1) {
                                    if (x_ec > related_170->x_ec) {
                                        facing_104 = -1;
                                        velocity_x_f4 = -velocity_x_f4;
                                        select_sequence(6);
                                    }
                                    else select_sequence(5);
                                }
                                else {
                                    if (x_ec < related_170->x_ec) {
                                        facing_104 = -facing_104;
                                        velocity_x_f4 = -velocity_x_f4;
                                        select_sequence(6);
                                    }
                                    else select_sequence(5);
                                }
                            }
                            if (sequence_index_13e == 3 || sequence_index_13e == 4) {
                                if (facing_104 == 1) {
                                    if (x_ec > related_170->x_ec) {
                                        facing_104 = -1;
                                        velocity_x_f4 = -velocity_x_f4;
                                        select_sequence(5);
                                    }
                                    else select_sequence(6);
                                    return;
                                }
                                if (x_ec < related_170->x_ec) {
                                    facing_104 = -facing_104;
                                    velocity_x_f4 = -velocity_x_f4;
                                    select_sequence(5);
                                }
                                else select_sequence(6);
                            }
                            return;
                        }
                    }
                }
                if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                    y_f0 = alice_stage_surface_height_at_x(this);
                    velocity_y_f8 = 0.0f;
                    acceleration_y_100 = 0.0f;
                    if (sequence_index_13e < 5) {
                        reinterpret_cast<AliceFighterScratchView *>(reinterpret_cast<unsigned char *>(this)+4)->reset();
                        set_action_and_finalize(215);
                    }
                    else {
                        set_action_and_finalize(10);
                        zero_velocity_acceleration();
                    }
                }
                return;
            }
    case 215:
        resolve_stage_surface_landing_transition();
        if (velocity_x_f4 > 0.0f) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.75);
            if (velocity_x_f4 < 0.0f)
                velocity_x_f4 = 0.0f;
        }
        if (velocity_x_f4 < 0.0f) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 + 0.75);
            if (velocity_x_f4 > 0.0f)
                velocity_x_f4 = 0.0f;
        }
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        return;


    case 220:
        if (!static_cast<unsigned short>(sequence_index_13e))
            resolve_stage_surface_landing_transition();
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            set_action_and_finalize(10);
            y_f0 = alice_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if (static_cast<unsigned char>(is_y_at_or_below_stage_surface(this)) || velocity_y_f8 > 0.0f)
            word_4ae = 2;
        if (static_cast<__int16>(static_cast<unsigned short>(sequence_index_13e)) > 0) {
            velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
            if (velocity_y_f8 < -20.0f)
                velocity_y_f8 = -20.0f;
        }
        advance_frame_and_dispatch();
        if (!time_counter_144
            && !static_cast<unsigned short>(frame_timer_142)
            && !static_cast<unsigned short>(frame_index_140)
            && static_cast<unsigned short>(sequence_index_13e) == 1) {
            velocity_x_f4 = 0.0f;
            velocity_y_f8 = 19.0f;
            acceleration_y_100 = 0.65f;
            byte_47e = 0;
            emit_fighter_effect_433cc0(
                63,
                x_ec,
                y_f0,
                static_cast<unsigned char>(facing_104),
                1);
        }
        return;

    case 209:
    case 212:
    case 221:
        if (!static_cast<unsigned short>(sequence_index_13e))
            resolve_stage_surface_landing_transition();
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            set_action_and_finalize(10);
            y_f0 = alice_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if (static_cast<unsigned char>(is_y_at_or_below_stage_surface(this)) || velocity_y_f8 > 0.0f)
            word_4ae = 2;
        if (static_cast<__int16>(static_cast<unsigned short>(sequence_index_13e)) > 0) {
            velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
            if (velocity_y_f8 < -20.0f)
                velocity_y_f8 = -20.0f;
        }
        advance_frame_and_dispatch();
        if (!time_counter_144
            && !static_cast<unsigned short>(frame_timer_142)
            && !static_cast<unsigned short>(frame_index_140)
            && static_cast<unsigned short>(sequence_index_13e) == 1) {
            velocity_x_f4 = 9.0f;
            velocity_y_f8 = 15.0f;
            acceleration_y_100 = 0.65f;
            byte_47e = 0;
            emit_fighter_effect_433cc0(
                63,
                x_ec,
                y_f0,
                static_cast<unsigned char>(facing_104),
                1);
        }
        return;

    case 210:
    case 222:
        if (!static_cast<unsigned short>(sequence_index_13e))
            resolve_stage_surface_landing_transition();
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            set_action_and_finalize(10);
            y_f0 = alice_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if (static_cast<unsigned char>(is_y_at_or_below_stage_surface(this)) || velocity_y_f8 > 0.0f)
            word_4ae = 2;
        if (static_cast<__int16>(static_cast<unsigned short>(sequence_index_13e)) > 0) {
            velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
            if (velocity_y_f8 < -20.0f)
                velocity_y_f8 = -20.0f;
        }
        advance_frame_and_dispatch();
        if (!time_counter_144
            && !static_cast<unsigned short>(frame_timer_142)
            && !static_cast<unsigned short>(frame_index_140)
            && static_cast<unsigned short>(sequence_index_13e) == 1) {
            velocity_x_f4 = -9.0f;
            velocity_y_f8 = 15.0f;
            acceleration_y_100 = 0.65f;
            byte_47e = 0;
            emit_fighter_effect_433cc0(
                63,
                x_ec,
                y_f0,
                static_cast<unsigned char>(facing_104),
                1);
        }
        return;

    case 223: {


        resolve_stage_surface_landing_transition();
        byte_47e = 1;
        advance_frame_and_dispatch();
        if (static_cast<unsigned short>(sequence_index_13e) == 1) {
            if (!(time_counter_144 % 5)) {
                dash_dust(false);
            }
            ++word_730;
            if ((facing_104*field_6b4<=0 && word_730>=13) || word_730>45) {
                set_action_and_finalize(204);
                return;
            }
        }
        if (!static_cast<unsigned short>(sequence_index_13e)
            && static_cast<unsigned short>(frame_index_140) == 4
            && !static_cast<unsigned short>(frame_timer_142)) {
            velocity_x_f4 = 5.0f;
            emit_fighter_effect_433cc0(
                125,
                x_ec + static_cast<float>(80 * facing_104),
                static_cast<float>(y_f0 + 80.0),
                static_cast<unsigned char>(facing_104),
                1);
            emit_fighter_effect_433cc0(
                126,
                x_ec,
                static_cast<float>(y_f0 + 80.0),
                static_cast<unsigned char>(facing_104),
                1);
            dispatch_indexed_event_member(0x1Fu);
        }
        return;
    }


    case 224: {


        if (!sequence_index_13e && frame_index_140 <= 0)
            resolve_stage_surface_landing_transition();
        if (static_cast<unsigned short>(sequence_index_13e) == 3) {
            resolve_stage_surface_landing_transition();
            velocity_x_f4 = static_cast<float>(velocity_x_f4 + 2.0);
            if (velocity_x_f4 > 0.0f)
                velocity_x_f4 = 0.0f;
        }
        if (!static_cast<unsigned char>(is_y_at_or_below_stage_surface(this)) && !(time_counter_144 % 5)) {
            dash_dust(true);
        }
        if (static_cast<short>(static_cast<unsigned short>(sequence_index_13e)) < 3) {
            velocity_y_f8 =
                velocity_y_f8 - acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                velocity_y_f8 = 0.0f;
                y_f0 = alice_stage_surface_height_at_x(this);
                select_sequence(3);
                return;
            }
        }
        if (advance_frame_and_dispatch()) {
            set_action_and_finalize(0);
            velocity_x_f4 = 0.0f;
            return;
        }
        if (!static_cast<unsigned short>(sequence_index_13e)
            && !static_cast<unsigned short>(frame_timer_142)
            && static_cast<unsigned short>(frame_index_140) == 2) {
            velocity_x_f4 = -10.0f;
            velocity_y_f8 = 4.5f;
            acceleration_y_100 = 0.6000000238418579f;
            emit_fighter_effect_433cc0(
                125,
                x_ec,
                static_cast<float>(y_f0 + 80.0),
                static_cast<unsigned char>(-facing_104),
                1);
            emit_fighter_effect_433cc0(
                126,
                x_ec,
                static_cast<float>(y_f0 + 80.0),
                static_cast<unsigned char>(-facing_104),
                1);
            dispatch_indexed_event_member(0x1Fu);
        }
        return;
    }

    case 225: {


        velocity_y_f8 =
            velocity_y_f8 - acceleration_y_100;
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            zero_velocity_acceleration();
            y_f0 = alice_stage_surface_height_at_x(this);
            set_action_and_finalize(10);
            return;
        }
        if ((static_cast<unsigned short>(sequence_index_13e) == 1 || static_cast<unsigned short>(sequence_index_13e) == 2)
            && !(time_counter_144 % 5)) {
            dash_dust(true);
        }
        if (advance_frame_and_dispatch())
            set_action_and_finalize(9);
        if (!time_counter_144
            && !static_cast<unsigned short>(frame_timer_142)
            && !static_cast<unsigned short>(frame_index_140)
            && static_cast<unsigned short>(sequence_index_13e) == 1) {
            velocity_x_f4 = -8.5f;
            velocity_y_f8 = 5.0f;
            acceleration_y_100 = 0.6000000238418579f;
            emit_fighter_effect_433cc0(
                125,
                x_ec,
                static_cast<float>(y_f0 + 120.0),
                static_cast<unsigned char>(-facing_104),
                1);
            emit_fighter_effect_433cc0(
                126,
                x_ec,
                static_cast<float>(y_f0 + 120.0),
                static_cast<unsigned char>(-facing_104),
                1);
            dispatch_indexed_event_member(0x1Fu);
        }
        return;
    }

    case 226: {


        velocity_y_f8 =
            velocity_y_f8 - acceleration_y_100;
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            zero_velocity_acceleration();
            y_f0 = alice_stage_surface_height_at_x(this);
            set_action_and_finalize(10);
            return;
        }
        if ((static_cast<unsigned short>(sequence_index_13e) == 1 || static_cast<unsigned short>(sequence_index_13e) == 2)
            && !(time_counter_144 % 5)) {
            dash_dust(false);
        }
        if (advance_frame_and_dispatch())
            set_action_and_finalize(9);
        if (!time_counter_144
            && !static_cast<unsigned short>(frame_timer_142)
            && !static_cast<unsigned short>(frame_index_140)
            && static_cast<unsigned short>(sequence_index_13e) == 1) {
            word_730 = 0;
            velocity_x_f4 = 8.5f;
            velocity_y_f8 = 5.0f;
            acceleration_y_100 = 0.6000000238418579f;
            emit_fighter_effect_433cc0(
                125,
                x_ec + static_cast<float>(80 * facing_104),
                static_cast<float>(y_f0 + 110.0),
                static_cast<unsigned char>(facing_104),
                1);
            emit_fighter_effect_433cc0(
                126,
                x_ec,
                static_cast<float>(y_f0 + 110.0),
                static_cast<unsigned char>(facing_104),
                1);
            dispatch_indexed_event_member(0x1Fu);
        }
        if (!time_counter_144
            && !static_cast<unsigned short>(frame_timer_142)
            && !static_cast<unsigned short>(frame_index_140)
            && static_cast<unsigned short>(sequence_index_13e) == 3)
            face_opponent_and_flip_horizontal_velocity();
        return;
    }


    case 300:
        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(0))
            return;
        if (byte_47e) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.5);
            if (velocity_x_f4 < 0.0f) {
                velocity_x_f4 = 0.0f;
                byte_47e = 0;
            }
        }
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        if (!static_cast<unsigned short>(frame_timer_142) && static_cast<unsigned short>(frame_index_140) == 2) {
            dispatch_indexed_event_member(0x1Bu);
            byte_47e = 0;
        }
        return;

    case 301: {
        float spawn_payload[3];
        int facing;

        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(0))
            return;
        if (byte_47e) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.5);
            if (velocity_x_f4 < 0.0f) {
                velocity_x_f4 = 0.0f;
                byte_47e = 0;
            }
        }
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        if (!static_cast<unsigned short>(frame_timer_142) && static_cast<unsigned short>(frame_index_140) == 2) {
            spawn_payload[0] = 0.0f;
            spawn_payload[1] = 0.0f;
            spawn_payload[2] = 1.0f;
            facing = static_cast<unsigned char>(facing_104);
            spawn_owned_object_via_manager(
                849,
                x_ec + static_cast<float>(30 * static_cast<signed char>(facing)),
                static_cast<float>(y_f0 + 100.0),
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
        if (byte_47e) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.5);
            if (velocity_x_f4 < 0.0f) {
                velocity_x_f4 = 0.0f;
                byte_47e = 0;
            }
        }
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        if (!static_cast<unsigned short>(frame_timer_142) && static_cast<unsigned short>(frame_index_140) == 3) {
            dispatch_indexed_event_member(0x1Du);
            spawn_payload[0] = 0.0f;
            spawn_payload[1] = 0.0f;
            spawn_payload[2] = 8.0f;
            facing = static_cast<unsigned char>(facing_104);
            spawn_owned_object_via_manager(
                849,
                x_ec + static_cast<float>(110 * static_cast<signed char>(facing)),
                static_cast<float>(y_f0 + 105.0),
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
        if (static_cast<signed char>(byte_47e) > 0
            || velocity_x_f4 > 0.0f) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.6000000238418579);
            if (velocity_x_f4 < 0.0f) {
                velocity_x_f4 = 0.0f;
                byte_47e = 0;
            }
        }
        if (advance_frame_and_dispatch())
            set_action_and_finalize(2);
        if (!static_cast<unsigned short>(frame_timer_142) && static_cast<unsigned short>(frame_index_140) == 2)
            velocity_x_f4 = 6.0f;
        if (!static_cast<unsigned short>(frame_timer_142) && static_cast<unsigned short>(frame_index_140) == 3)
            dispatch_indexed_event_member(0x1Cu);
        return;


    case 304: {
        float spawn_payload[3];
        int spawn_index;
        int facing;

        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(1))
            return;
        if (velocity_x_f4 > 0.0f) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 1.0);
            if (velocity_x_f4 < 0.0f)
                velocity_x_f4 = 0.0f;
        }
        if (frame_index_140 >= 4
            && frame_index_140 <= 6) {
            if (static_cast<__int16>(static_cast<unsigned short>(word_730)) % 4 == 0
                && word_732 <= 4) {
                spawn_index = word_732;
                spawn_payload[0] = static_cast<float>(-10.0 - 13.0 * spawn_index);
                spawn_payload[1] = 30.0f;
                spawn_payload[2] = 11.0f;
                facing = static_cast<unsigned char>(facing_104);
                spawn_owned_object_via_manager(
                    849,
                    static_cast<float>(x_ec + 30.0),
                    static_cast<float>(y_f0 + 100.0),
                    facing,
                    1,
                    spawn_payload,
                    3);
                ++word_732;
            }
            ++word_730;
        }
        if (advance_frame_and_dispatch())
            set_action_and_finalize(2);
        return;
    }

    case 305:
        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(1))
            return;
        if (frame_index_140 > 3) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.75);
            if (velocity_x_f4 < 0.0f)
                velocity_x_f4 = 0.0f;
        }
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        if (!static_cast<unsigned short>(frame_timer_142) && static_cast<unsigned short>(frame_index_140) == 2)
            dispatch_indexed_event_member(0x1Du);
        return;

    case 306:
        velocity_y_f8 =
            velocity_y_f8 - acceleration_y_100;
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            set_action_and_finalize(10);
            y_f0 = alice_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if (advance_frame_and_dispatch())
            set_action_and_finalize(9);
        if (!static_cast<unsigned short>(frame_timer_142) && static_cast<unsigned short>(frame_index_140) == 4)
            dispatch_indexed_event_member(0x1Bu);
        return;


    case 307: {
        float spawn_payload[3];
        int facing;

        if (frame_index_140 >= 11)
            velocity_y_f8 =
                velocity_y_f8 - acceleration_y_100;
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())
            && frame_index_140 >= 11) {
            set_action_and_finalize(10);
            zero_velocity_acceleration();
            y_f0 = alice_stage_surface_height_at_x(this);
            return;
        }
        if (advance_frame_and_dispatch())
            set_action_and_finalize(9);
        if (!static_cast<unsigned short>(frame_timer_142) && static_cast<unsigned short>(frame_index_140) == 3) {
            dispatch_indexed_event_member(0x1Du);
            spawn_payload[0] = 0.0f;
            spawn_payload[1] = 0.0f;
            spawn_payload[2] = 16.0f;
            facing = static_cast<unsigned char>(facing_104);
            spawn_owned_object_via_manager(
                849,
                x_ec + static_cast<float>(50 * static_cast<signed char>(facing)),
                static_cast<float>(y_f0 + 140.0),
                facing,
                1,
                spawn_payload,
                3);
        }
        return;
    }

    case 308: {
        float spawn_payload[3];

        int i;

        velocity_y_f8 =
            velocity_y_f8 - acceleration_y_100;
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            set_action_and_finalize(10);
            y_f0 = alice_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if (advance_frame_and_dispatch())
            set_action_and_finalize(9);
        if (!static_cast<unsigned>(time_counter_144)
            && !static_cast<unsigned short>(frame_timer_142)
            && !static_cast<unsigned short>(frame_index_140)
            && static_cast<unsigned short>(sequence_index_13e) == 1)
            dispatch_indexed_event_member(0x1Du);
        if (!static_cast<unsigned short>(sequence_index_13e)) {
            if (!static_cast<unsigned short>(frame_timer_142) && static_cast<unsigned short>(frame_index_140) == 4) {

                for (i = 0; i < 6; ++i) {
                    spawn_payload[0] = static_cast<float>(-static_cast<float>(i) * 60.0);
                    spawn_payload[1] = 13.0f;
                    spawn_payload[2] = 17.0f;
                    spawn_owned_object_via_manager(
                        849,
                        x_ec + static_cast<float>(25 * facing_104),
                        static_cast<float>(y_f0 + 95.0),
                        static_cast<unsigned char>(facing_104),
                        1,
                        spawn_payload,
                        3);
                    ++word_732;
                }
            }
            if (!static_cast<unsigned short>(frame_timer_142) && static_cast<unsigned short>(frame_index_140) == 5) {
                velocity_x_f4 = -4.0f;
                velocity_y_f8 = 8.0f;
            }
        }
        if (!static_cast<unsigned short>(frame_timer_142) && static_cast<unsigned short>(sequence_index_13e) == 1)
            field_180 = 0;
        return;
    }

    case 309: {
        float spawn_payload[3];

        int i;

        velocity_y_f8 =
            velocity_y_f8 - acceleration_y_100;
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            set_action_and_finalize(10);
            y_f0 = alice_stage_surface_height_at_x(this);
            zero_velocity_acceleration();
            return;
        }
        if (advance_frame_and_dispatch())
            set_action_and_finalize(9);
        if (!static_cast<unsigned>(time_counter_144)
            && !static_cast<unsigned short>(frame_timer_142)
            && !static_cast<unsigned short>(frame_index_140)
            && static_cast<unsigned short>(sequence_index_13e) == 1)
            dispatch_indexed_event_member(0x1Du);
        if (!static_cast<unsigned short>(sequence_index_13e)
            && !static_cast<unsigned short>(frame_timer_142)
            && static_cast<unsigned short>(frame_index_140) == 3) {

            for (i = 0; i < 6; ++i) {
                spawn_payload[0] = static_cast<float>(-static_cast<float>(i) * 60.0);
                spawn_payload[1] = 13.0f;
                spawn_payload[2] = 24.0f;
                spawn_owned_object_via_manager(
                    849,
                    x_ec + static_cast<float>(30 * facing_104),
                    static_cast<float>(y_f0 + 120.0),
                    static_cast<unsigned char>(facing_104),
                    1,
                    spawn_payload,
                    3);
                ++word_732;
            }
        }
        if (static_cast<unsigned short>(sequence_index_13e) == 2
            && !static_cast<unsigned short>(frame_timer_142)
            && static_cast<unsigned short>(frame_index_140) == 4)
            acceleration_y_100 = 0.5f;
        if (!static_cast<unsigned short>(frame_timer_142) && static_cast<unsigned short>(sequence_index_13e) == 1)
            field_180 = 0;
        return;
    }

    case 310: {
        double next_y;

        if (static_cast<unsigned>(field_180)) {
            if (static_cast<__int16>(++word_730) > 5) {
                field_180 = 0;
                word_730 = 0;
            }
        }
        if (static_cast<unsigned short>(sequence_index_13e) == 1) {
            if (!static_cast<unsigned>(time_counter_144))
                velocity_x_f4 = 15.0f;
            if (!(time_counter_144 % 8))
                dispatch_indexed_event_member(0x1Bu);
            if (static_cast<unsigned>(field_180)) {
                if (static_cast<__int16>(++word_730) > 5) {
                    field_180 = 0;
                    word_730 = 0;
                }
            }
            if (time_counter_144 > 30) {
                next_sequence_block();
                velocity_y_f8 = 6.0f;
                velocity_x_f4 =
                    static_cast<float>(velocity_x_f4 * 0.5);
            }
        }
        if (static_cast<unsigned short>(sequence_index_13e) == 2) {
            velocity_y_f8 -= acceleration_y_100;
            next_y = static_cast<double>(velocity_y_f8) + y_f0;
            if (alice_stage_surface_height_at_x(this) >= next_y) {
                velocity_y_f8 = 0.0f;
                y_f0 = alice_stage_surface_height_at_x(this);
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
        if (frame_index_140 > 1) {
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 2.0);
            if (velocity_x_f4 < 0.0f)
                velocity_x_f4 = 0.0f;
        }
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        if (!static_cast<unsigned short>(frame_timer_142) && static_cast<unsigned short>(frame_index_140) == 2) {
            dispatch_indexed_event_member(0x1Cu);
            byte_47e = 0;
        }
        return;

    case 321:
        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(0))
            return;
            if (frame_index_140 > 3) {
                velocity_x_f4 = static_cast<float>(velocity_x_f4 - 1.0);
            if (velocity_x_f4 < 0.0f)
                    velocity_x_f4 = 0.0f;
            }
            if (advance_frame_and_dispatch())
                set_action_and_finalize(0);
            if (!static_cast<unsigned short>(frame_timer_142) && static_cast<unsigned short>(frame_index_140) == 3) {
                dispatch_indexed_event_member(0x1Cu);
                velocity_x_f4 = 10.0f;
                byte_47e = 0;
            }
        return;


    case 322: {
        int facing;

        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(1))
            return;
        velocity_x_f4 = static_cast<float>(velocity_x_f4 - 1.5);
            if (velocity_x_f4 < 0.0f)
            velocity_x_f4 = 0.0f;
        if (!field_6bc)
            byte_750 = 0;
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        if (!static_cast<unsigned>(time_counter_144)
            && !static_cast<unsigned short>(frame_timer_142)
            && !static_cast<unsigned short>(frame_index_140)
            && static_cast<unsigned short>(sequence_index_13e) == 1) {
            set_action_and_finalize(0);
            return;
        }
        if (!static_cast<unsigned short>(sequence_index_13e)) {
            if (!static_cast<unsigned short>(frame_timer_142) && static_cast<unsigned short>(frame_index_140) == 7) {
                if (byte_750 == 1) {
                    next_sequence_block();
                    facing = static_cast<unsigned char>(facing_104);
                    emit_fighter_effect_433cc0(
                        62,
                        x_ec - static_cast<float>(33 * static_cast<signed char>(facing)),
                        static_cast<float>(y_f0 + 112.0),
                        facing,
                        -1);
                    return;
                }
                velocity_x_f4 = 15.0f;
            }
            if (!static_cast<unsigned short>(frame_timer_142) && static_cast<unsigned short>(frame_index_140) == 9) {
                dispatch_indexed_event_member(0x1Du);
                byte_47e = 0;
            }
        }
        if (static_cast<unsigned short>(sequence_index_13e) == 1) {
            if (!static_cast<unsigned short>(frame_timer_142) && static_cast<unsigned short>(frame_index_140) == 11)
                velocity_x_f4 = 19.0f;
            if (!static_cast<unsigned short>(frame_timer_142) && static_cast<unsigned short>(frame_index_140) == 12)
                dispatch_indexed_event_member(0x1Du);
        }
        return;
    }



 case 400: {
  RESOLVE(); if(field_6c0==0) byte_750=0;
  if(FRAME()) ACTION(0);
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==1) {
   if(static_cast<signed char>(byte_750)==1) {
    SEQUENCE(4);
    EFFECT(62,static_cast<float>(25*facing_104+x_ec),static_cast<float>(y_f0+148.0),static_cast<unsigned char>(facing_104),1);
    float packet[3]={-74,100,0};
    SPAWN(802,static_cast<float>(x_ec-74*facing_104),static_cast<float>(y_f0+104.0),static_cast<unsigned char>(facing_104),1,packet,3);
    WAVE(2); ADJUST(200,45); field_180=1; SCALE(30); return;
   }
   float packet[3]={-74,100,0};
   SPAWN(801,static_cast<float>(x_ec-74*facing_104),static_cast<float>(y_f0+104.0),static_cast<unsigned char>(facing_104),1,packet,3);
   WAVE(2); ADJUST(200,45); field_180=1; SCALE(30);
  }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==4) { ACTION(0); return; }
  if(sequence_index_13e==2 && time_counter_144>=20) BLOCK();
  if(sequence_index_13e==4 && time_counter_144>=25) BLOCK();
  if(sequence_index_13e==6 && time_counter_144>=40) BLOCK();
  return;
 }

    case 401: {
        float spawn_payload[3];
        int facing;
        resolve_stage_surface_landing_transition();
        if (!static_cast<unsigned>(field_6c0))
            byte_750 = 0;
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        if (!static_cast<unsigned>(time_counter_144)
            && !static_cast<unsigned short>(frame_timer_142)
            && !static_cast<unsigned short>(frame_index_140)
            && static_cast<unsigned short>(sequence_index_13e) == 1) {
            spawn_payload[0] = -74.0f;
            spawn_payload[1] = 100.0f;
            spawn_payload[2] = 0.0f;
            facing = static_cast<unsigned char>(facing_104);
            spawn_owned_object_via_manager(803,
                x_ec - static_cast<float>(74 * static_cast<signed char>(facing)),
                static_cast<float>(y_f0 + 104.0),
                facing, 1, spawn_payload, 3);
            dispatch_character_wave_handle(2);
            field_180 = 1;
            adjust_counter_482(200, 45);
            add_phase_scaled_counter_558(30);
        }
        if (!static_cast<unsigned>(time_counter_144)
            && !static_cast<unsigned short>(frame_timer_142)
            && !static_cast<unsigned short>(frame_index_140)
            && static_cast<unsigned short>(sequence_index_13e) == 4) {
            set_action_and_finalize(0);
            return;
        }
        if (static_cast<unsigned short>(sequence_index_13e) == 2 && time_counter_144 >= 30)
            next_sequence_block();
        if (static_cast<unsigned short>(sequence_index_13e) == 4 && time_counter_144 >= 25)
            next_sequence_block();
        if (static_cast<unsigned short>(sequence_index_13e) == 6 && time_counter_144 >= 45)
            next_sequence_block();
        return;
    }


    case 402: {
        float spawn_payload[3];
        int facing;
        resolve_stage_surface_landing_transition();
        if (advance_frame_and_dispatch())
            set_action_and_finalize(2);
        if (!static_cast<unsigned short>(frame_timer_142)
            && static_cast<unsigned short>(frame_index_140) == 4) {
            spawn_payload[0] = 0.0f;
            spawn_payload[1] = 0.0f;
            spawn_payload[2] = 7.0f;
            facing = static_cast<unsigned char>(facing_104);
            spawn_owned_object_via_manager(801,
                x_ec + static_cast<float>(20 * static_cast<signed char>(facing)),
                static_cast<float>(y_f0 + 90.0),
                facing, 1, spawn_payload, 3);
            dispatch_character_wave_handle(2);
            adjust_counter_482(200, 45);
            field_180 = 1;
            add_phase_scaled_counter_558(30);
        }
        return;
    }

    case 404: {
  if(sequence_index_13e==8) RESOLVE();
  if(sequence_index_13e==3 || sequence_index_13e==7) velocity_y_f8-=acceleration_y_100;
  if(CROSSED() && sequence_index_13e<=7) { SEQUENCE(8); y_f0=GROUND(); ZERO(); return; }
  if(field_6c0==0) byte_750=0;
  if(FRAME()) ACTION(0);
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==1) {
   if(static_cast<signed char>(byte_750)==1) {
    SEQUENCE(4); EFFECT(62,static_cast<float>(25*facing_104+x_ec),static_cast<float>(y_f0+148.0),static_cast<unsigned char>(facing_104),1);
    float packet[3]={-74,100,0};
    SPAWN(802,static_cast<float>(x_ec-74*facing_104),static_cast<float>(y_f0+104.0),static_cast<unsigned char>(facing_104),1,packet,3);
    WAVE(2); ADJUST(200,45); field_180=1; SCALE(30); return;
   }
   float packet[3]={-74,100,0};
   SPAWN(801,static_cast<float>(x_ec-74*facing_104),static_cast<float>(y_f0+104.0),static_cast<unsigned char>(facing_104),1,packet,3);
   WAVE(2); ADJUST(200,45); field_180=1; SCALE(30);
  }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==4) { ACTION(9); return; }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==8) ACTION(9);
  if(sequence_index_13e==2 && time_counter_144>=20) BLOCK();
  if(sequence_index_13e==4 && time_counter_144>=25) BLOCK();
  if(sequence_index_13e==6 && time_counter_144>=40) BLOCK();
  return;
 }
 case 406: {
  if(sequence_index_13e==8) RESOLVE();
  if(sequence_index_13e==3 || sequence_index_13e==7) velocity_y_f8-=acceleration_y_100;
  if(CROSSED() && sequence_index_13e<=7) { SEQUENCE(8); y_f0=GROUND(); ZERO(); return; }
  if(field_6c0==0) byte_750=0;
  if(FRAME()) ACTION(0);
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==1) {
   if(static_cast<signed char>(byte_750)==1) {
    SEQUENCE(4); EFFECT(62,static_cast<float>(25*facing_104+x_ec),static_cast<float>(y_f0+148.0),static_cast<unsigned char>(facing_104),1);
    float packet[3]={-74,100,1};
    SPAWN(802,static_cast<float>(x_ec-74*facing_104),static_cast<float>(y_f0+104.0),static_cast<unsigned char>(facing_104),1,packet,3);
    WAVE(2); ADJUST(200,45); field_180=1; SCALE(30); return;
   }
   float packet[3]={-74,100,1};
   SPAWN(801,static_cast<float>(x_ec-74*facing_104),static_cast<float>(y_f0+104.0),static_cast<unsigned char>(facing_104),1,packet,3);
   WAVE(2); ADJUST(200,45); field_180=1; SCALE(30);
  }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==4) { ACTION(9); return; }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==8) ACTION(9);
  if(sequence_index_13e==2 && time_counter_144>=20) BLOCK();
  if(sequence_index_13e==4 && time_counter_144>=25) BLOCK();
  if(sequence_index_13e==6 && time_counter_144>=40) BLOCK();
  return;
 }
 case 408: {
        float spawn_payload[3];
        int facing;

        resolve_stage_surface_landing_transition();
        if (try_dispatch_directional_action_208_210(1))
            return;
        velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.25);
            if (velocity_x_f4 < 0.0f) {
            velocity_x_f4 = 0.0f;
            byte_47e = 0;
        }
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        if (!static_cast<unsigned short>(frame_timer_142) && static_cast<unsigned short>(frame_index_140) == 2) {
            spawn_payload[0] = 0.0f;
            spawn_payload[1] = 0.0f;
            spawn_payload[2] = 19.0f;
            facing = static_cast<unsigned char>(facing_104);
            spawn_owned_object_via_manager(
                849,
                x_ec + static_cast<float>(30 * static_cast<signed char>(facing)),
                static_cast<float>(y_f0 + 100.0),
                facing,
                1,
                spawn_payload,
                3);
        }
        return;
    }

    case 409:
        velocity_y_f8 =
            velocity_y_f8 - acceleration_y_100;
        if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
            set_action_and_finalize(10);
            zero_velocity_acceleration();
            y_f0 = alice_stage_surface_height_at_x(this);
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
        if (!static_cast<unsigned>(field_6c4))
            byte_750 = 0;
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        if (!static_cast<unsigned short>(sequence_index_13e)
            && !static_cast<unsigned short>(frame_timer_142)
            && static_cast<unsigned short>(frame_index_140) == 3) {
            spawn_payload[0] = -45.0f;
            spawn_payload[1] = 40.0f;
            spawn_payload[2] = 0.0f;
            facing = static_cast<unsigned char>(facing_104);
            spawn_owned_object_via_manager(805,
                x_ec + static_cast<float>(5 * static_cast<signed char>(facing)),
                static_cast<float>(y_f0 + 108.0),
                facing, 1, spawn_payload, 3);
            dispatch_character_wave_handle(2);
            adjust_counter_482(200, 60);
            add_phase_scaled_counter_558(30);
            field_180 = 1;
            return;
        }
        if (!static_cast<unsigned>(time_counter_144)
            && !static_cast<unsigned short>(frame_timer_142)
            && !static_cast<unsigned short>(frame_index_140)
            && static_cast<unsigned short>(sequence_index_13e) == 1) {
            if (!byte_750) {
                set_action_and_finalize(0);
                return;
            }
            facing = static_cast<unsigned char>(facing_104);
            emit_fighter_effect_433cc0(62,
                x_ec - static_cast<float>(66 * static_cast<signed char>(facing)),
                static_cast<float>(y_f0 + 148.0), facing, 1);
            return;
        }
        return;
    }

    case 411: {
        float spawn_payload[3];
        int facing;

        resolve_stage_surface_landing_transition();
        if (!static_cast<unsigned>(field_6c4))
            byte_750 = 0;
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        if (!static_cast<unsigned short>(sequence_index_13e)
            && !static_cast<unsigned short>(frame_timer_142)
            && static_cast<unsigned short>(frame_index_140) == 3) {
            spawn_payload[0] = 0.0f;
            spawn_payload[1] = 40.0f;
            spawn_payload[2] = 0.0f;
            facing = static_cast<unsigned char>(facing_104);
            spawn_owned_object_via_manager(
                805,
                x_ec + static_cast<float>(5 * static_cast<signed char>(facing)),
                static_cast<float>(y_f0 + 108.0),
                facing,
                1,
                spawn_payload,
                3);
            dispatch_character_wave_handle(2);
            field_180 = 1;
            adjust_counter_482(200, 60);
            add_phase_scaled_counter_558(30);
            return;
        }
        if (!static_cast<unsigned>(time_counter_144)
            && !static_cast<unsigned short>(frame_timer_142)
            && !static_cast<unsigned short>(frame_index_140)
            && static_cast<unsigned short>(sequence_index_13e) == 1) {
            if (!byte_750) {
                set_action_and_finalize(0);
                return;
            }
            facing = static_cast<unsigned char>(facing_104);
            emit_fighter_effect_433cc0(
                62,
                x_ec - static_cast<float>(66 * static_cast<signed char>(facing)),
                static_cast<float>(y_f0 + 148.0),
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
        if (!static_cast<unsigned>(field_6c4))
            byte_750 = 0;
        if (!static_cast<unsigned short>(sequence_index_13e)
            && !static_cast<unsigned short>(frame_timer_142)
            && static_cast<unsigned short>(frame_index_140) == 10)
            velocity_x_f4 = 0.0f;
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        if (!static_cast<unsigned short>(sequence_index_13e)) {
            if (!static_cast<unsigned short>(frame_timer_142) && static_cast<unsigned short>(frame_index_140) == 9) {
                spawn_payload[0] = -80.0f;
                spawn_payload[1] = 40.0f;
                spawn_payload[2] = 0.0f;
                facing = static_cast<unsigned char>(facing_104);
                spawn_owned_object_via_manager(
                    805,
                    x_ec + static_cast<float>(5 * static_cast<signed char>(facing)),
                    static_cast<float>(y_f0 + 108.0),
                    facing,
                    1,
                    spawn_payload,
                    3);
                dispatch_character_wave_handle(2);
                field_180 = 1;
                adjust_counter_482(200, 60);
                add_phase_scaled_counter_558(30);
                return;
            }
            if (!static_cast<unsigned short>(frame_timer_142) && static_cast<unsigned short>(frame_index_140) == 10)
                velocity_x_f4 = 34.0f;
        }
        if (!static_cast<unsigned>(time_counter_144)
            && !static_cast<unsigned short>(frame_timer_142)
            && !static_cast<unsigned short>(frame_index_140)
            && static_cast<unsigned short>(sequence_index_13e) == 1) {
            if (!byte_750) {
                set_action_and_finalize(0);
                return;
            }
            facing = static_cast<unsigned char>(facing_104);
            emit_fighter_effect_433cc0(
                62,
                x_ec - static_cast<float>(66 * static_cast<signed char>(facing)),
                static_cast<float>(y_f0 + 148.0),
                facing,
                1);
            return;
        }
        return;
    }


    case 414: {
  if(sequence_index_13e==2) RESOLVE();
  if(field_6c4==0) byte_750=0;
  if(sequence_index_13e==1 && frame_index_140>=12) velocity_y_f8-=acceleration_y_100;
  if((sequence_index_13e==0 || (sequence_index_13e==1 && frame_index_140>=12)) && CROSSED()) {
   SEQUENCE(2); y_f0=GROUND(); ZERO(); return;
  }
  if(FRAME()) ACTION(0);
  if(sequence_index_13e==0) {
   if(frame_timer_142==0 && frame_index_140==6) {
    float packet[3]={45,40,0};
    SPAWN(805,static_cast<float>(20*facing_104+x_ec),static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1,packet,3);
    WAVE(2); ADJUST(200,60); field_180=1; SCALE(30); return;
   }
   if(frame_timer_142==0 && frame_index_140==11 && static_cast<signed char>(byte_750)==1) {
    EFFECT(62,static_cast<float>(x_ec-47*facing_104),static_cast<float>(y_f0+185.0),static_cast<unsigned char>(facing_104),1); BLOCK(); return;
   }
  }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==1) { ACTION(9); return; }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==2) ACTION(9);
  return;
 }
 case 415: {
  if(sequence_index_13e==2) RESOLVE();
  if(field_6c4==0) byte_750=0;
  if(sequence_index_13e==1 && frame_index_140>=12) velocity_y_f8-=acceleration_y_100;
  if((sequence_index_13e==0 || (sequence_index_13e==1 && frame_index_140>=12)) && CROSSED()) {
   SEQUENCE(2); y_f0=GROUND(); ZERO(); return;
  }
  if(FRAME()) ACTION(0);
  if(sequence_index_13e==0) {
   if(frame_timer_142==0 && frame_index_140==6) {
    float packet[3]={0,40,0};
    SPAWN(805,static_cast<float>(20*facing_104+x_ec),static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1,packet,3);
    WAVE(2); field_180=1; ADJUST(200,60); SCALE(30); return;
   }
   if(frame_timer_142==0 && frame_index_140==11 && static_cast<signed char>(byte_750)==1) {
    EFFECT(62,static_cast<float>(x_ec-47*facing_104),static_cast<float>(y_f0+185.0),static_cast<unsigned char>(facing_104),1); BLOCK(); return;
   }
  }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==1) { ACTION(9); return; }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==2) ACTION(9);
  return;
 }
 case 416: {
  if(sequence_index_13e==2) RESOLVE();
  if(field_6c4==0) byte_750=0;
  if(sequence_index_13e==1 && frame_index_140>=12) velocity_y_f8-=acceleration_y_100;
  if((sequence_index_13e==0 || (sequence_index_13e==1 && frame_index_140>=12)) && CROSSED()) {
   SEQUENCE(2); y_f0=GROUND(); ZERO(); return;
  }
  if(FRAME()) ACTION(0);
  if(sequence_index_13e==0) {
   if(frame_timer_142==0 && frame_index_140==5) {
    float packet[3]={80,40,0};
    SPAWN(805,static_cast<float>(20*facing_104+x_ec),static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1,packet,3);
    WAVE(2); field_180=1; ADJUST(200,60); SCALE(30); return;
   }
   if(frame_timer_142==0 && frame_index_140==8 && static_cast<signed char>(byte_750)==1) {
    EFFECT(62,static_cast<float>(x_ec-47*facing_104),static_cast<float>(y_f0+185.0),static_cast<unsigned char>(facing_104),1); BLOCK(); return;
   }
  }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==1) { ACTION(9); return; }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==2) ACTION(9);
  return;
 }
 case 418:
  RESOLVE(); if(GATE(1)) return;
  velocity_x_f4-=D(0.35f); if(velocity_x_f4<0.0f) { velocity_x_f4=0; byte_47e=0; }
  if(FRAME()) ACTION(0);
  if(frame_timer_142==0 && frame_index_140==2) {
   float packet[3]={0,0,21};
   SPAWN(849,static_cast<float>(x_ec+0.0),static_cast<float>(y_f0+50.0),static_cast<unsigned char>(facing_104),-1,packet,3); EVENT(29);
  }
  if(frame_timer_142==0 && frame_index_140==3) {
   float packet[3]={0,0,23};
   SPAWN(849,static_cast<float>(x_ec+0.0),static_cast<float>(y_f0+50.0),static_cast<unsigned char>(facing_104),1,packet,3); EVENT(29);
  }
  if(frame_timer_142==0 && frame_index_140==4) {
   float packet[3]={0,0,21};
   SPAWN(849,static_cast<float>(x_ec+0.0),static_cast<float>(y_f0+50.0),static_cast<unsigned char>(facing_104),-1,packet,3); EVENT(29);
  }
  if(frame_timer_142==0 && frame_index_140==5) {
   float packet[3]={0,0,23};
   SPAWN(849,static_cast<float>(x_ec+0.0),static_cast<float>(y_f0+50.0),static_cast<unsigned char>(facing_104),1,packet,3); EVENT(29);
  }
  return;
    case 500: {
        float spawn_payload[3];
        int facing;
        resolve_stage_surface_landing_transition();
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        if (!static_cast<unsigned short>(sequence_index_13e)
            && !static_cast<unsigned short>(frame_timer_142)
            && static_cast<unsigned short>(frame_index_140) == 3) {
            spawn_payload[0] = 20.0f;
            spawn_payload[1] = 30.0f;
            spawn_payload[2] = 0.0f;
            field_180 = 1;
            facing = static_cast<unsigned char>(facing_104);
            spawn_owned_object_via_manager(810,
                x_ec + static_cast<float>(8 * static_cast<signed char>(facing)),
                static_cast<float>(y_f0 + 100.0),
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
        if (!static_cast<unsigned short>(sequence_index_13e)
            && !static_cast<unsigned short>(frame_timer_142)
            && static_cast<unsigned short>(frame_index_140) == 3) {
            spawn_payload[0] = -25.0f;
            spawn_payload[1] = 30.0f;
            spawn_payload[2] = 0.0f;
            field_180 = 1;
            facing = static_cast<unsigned char>(facing_104);
            spawn_owned_object_via_manager(810,
                x_ec + static_cast<float>(8 * static_cast<signed char>(facing)),
                static_cast<float>(y_f0 + 100.0),
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
        if (!static_cast<unsigned short>(sequence_index_13e)
            && !static_cast<unsigned short>(frame_timer_142)
            && static_cast<unsigned short>(frame_index_140) == 7) {
            spawn_payload[0] = 0.0f;
            spawn_payload[1] = 25.0f;
            spawn_payload[2] = 0.0f;
            field_180 = 1;
            facing = static_cast<unsigned char>(facing_104);
            spawn_owned_object_via_manager(811,
                x_ec + static_cast<float>(8 * static_cast<signed char>(facing)),
                static_cast<float>(y_f0 + 100.0),
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
        if (!static_cast<unsigned short>(sequence_index_13e)
            && !static_cast<unsigned short>(frame_timer_142)
            && static_cast<unsigned short>(frame_index_140) == 7) {
            spawn_payload[0] = -45.0f;
            spawn_payload[1] = 25.0f;
            spawn_payload[2] = 0.0f;
            field_180 = 1;
            facing = static_cast<unsigned char>(facing_104);
            spawn_owned_object_via_manager(811,
                x_ec + static_cast<float>(8 * static_cast<signed char>(facing)),
                static_cast<float>(y_f0 + 100.0),
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
        if (static_cast<unsigned short>(sequence_index_13e) == 3)
            resolve_stage_surface_landing_transition();
        if (static_cast<short>(static_cast<unsigned short>(sequence_index_13e)) < 3) {
            velocity_y_f8 =
                velocity_y_f8 - acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                zero_velocity_acceleration();
                y_f0 = alice_stage_surface_height_at_x(this);
                select_sequence(3);
                return;
            }
        }
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        if (!sequence_index_13e) {
            if (!frame_timer_142 && frame_index_140 == 5) {
                velocity_x_f4 = -5.0f;
                velocity_y_f8 = 5.0f;
                acceleration_y_100 = 0.5f;
            }
            if (!frame_timer_142 && frame_index_140 == 6) {
                spawn_payload[0] = 0.0f;
                spawn_payload[1] = 25.0f;
                spawn_payload[2] = 0.0f;
                field_180 = 1;
                facing = static_cast<unsigned char>(facing_104);
                spawn_owned_object_via_manager(811,
                    x_ec + static_cast<float>(17 * static_cast<signed char>(facing)),
                    static_cast<float>(y_f0 + 104.0),
                    facing, 1, spawn_payload, 3);
                dispatch_character_wave_handle(10);
                adjust_counter_482(200, 120);
                add_phase_scaled_counter_558(30);
            }
        }
        if (!static_cast<unsigned>(time_counter_144)
            && !static_cast<unsigned short>(frame_timer_142)
            && !static_cast<unsigned short>(frame_index_140)
            && static_cast<unsigned short>(sequence_index_13e) == 3)
            set_action_and_finalize(9);
        return;
    }

    case 508: {
        float spawn_payload[3];
        int facing;
        if (static_cast<unsigned short>(sequence_index_13e) == 3)
            resolve_stage_surface_landing_transition();
        if (static_cast<short>(static_cast<unsigned short>(sequence_index_13e)) < 3) {
            velocity_y_f8 =
                velocity_y_f8 - acceleration_y_100;
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                zero_velocity_acceleration();
                y_f0 = alice_stage_surface_height_at_x(this);
                select_sequence(3);
                return;
            }
        }
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        if (!sequence_index_13e) {
            if (!frame_timer_142 && frame_index_140 == 5) {
                velocity_x_f4 = -5.0f;
                velocity_y_f8 = 5.0f;
                acceleration_y_100 = 0.5f;
            }
            if (!frame_timer_142 && frame_index_140 == 6) {
                spawn_payload[0] = 45.0f;
                spawn_payload[1] = 25.0f;
                spawn_payload[2] = 0.0f;
                field_180 = 1;
                facing = static_cast<unsigned char>(facing_104);
                spawn_owned_object_via_manager(811,
                    x_ec + static_cast<float>(17 * static_cast<signed char>(facing)),
                    static_cast<float>(y_f0 + 104.0),
                    facing, 1, spawn_payload, 3);
                dispatch_character_wave_handle(10);
                adjust_counter_482(200, 120);
                add_phase_scaled_counter_558(30);
            }
        }
        if (!static_cast<unsigned>(time_counter_144)
            && !static_cast<unsigned short>(frame_timer_142)
            && !static_cast<unsigned short>(frame_index_140)
            && static_cast<unsigned short>(sequence_index_13e) == 3)
            set_action_and_finalize(9);
        return;
    }

 case 520: {
  if(sequence_index_13e==0 || sequence_index_13e==4 || sequence_index_13e==8) RESOLVE();
  if(field_6c0==0) byte_750=0;
  if((sequence_index_13e==2 || sequence_index_13e==3) && time_counter_144>=0) {
   switch(byte_605) { case 0: word_732=3; break; case 1: case 2: word_732=4; break; case 3: case 4: word_732=5; break; }
   if(time_counter_144%6==0 && word_730<word_732) {
    field_180=1; SCALE(10); ++word_730;
    float packet[3]; packet[0]=static_cast<float>(-25*word_730+70); packet[1]=15; packet[2]=0;
    SPAWN(815,static_cast<float>(14*facing_104+x_ec),static_cast<float>(y_f0+111.0),static_cast<unsigned char>(facing_104),1,packet,3);
    WAVE(5); if(word_730==1) ADJUST(200,120);
   }
  }
  if((sequence_index_13e==6 || sequence_index_13e==7) && time_counter_144>=0) {
   switch(byte_605) { case 0: word_732=5; break; case 1: case 2: word_732=6; break; case 3: case 4: word_732=7; break; }
   if(time_counter_144%3==0 && word_730<word_732) {
    field_180=1; ++word_730; SCALE(10);
    float packet[3]; packet[0]=static_cast<float>((5-word_730)*15); packet[1]=15; packet[2]=0;
    SPAWN(815,static_cast<float>(14*facing_104+x_ec),static_cast<float>(y_f0+111.0),static_cast<unsigned char>(facing_104),1,packet,3);
    WAVE(5); if(word_730==1) ADJUST(200,120);
   }
  }
  if(sequence_index_13e==1 || sequence_index_13e==2 || sequence_index_13e==3 || sequence_index_13e==5 || sequence_index_13e==6 || sequence_index_13e==7) {
   velocity_y_f8-=acceleration_y_100;
   if(CROSSED()) { y_f0=GROUND(); ZERO(); SEQUENCE(8); return; }
  }
  if(FRAME()) ACTION(0);
  if(sequence_index_13e==0 && frame_timer_142==0 && frame_index_140==3 && static_cast<signed char>(byte_750)==1) {
   SEQUENCE(4); EFFECT(62,static_cast<float>(x_ec-4*facing_104),static_cast<float>(y_f0+116.0),static_cast<unsigned char>(facing_104),-1); return;
  }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==1) { velocity_x_f4=-7.5f; velocity_y_f8=12.5f; acceleration_y_100=0.7f; }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==5) { velocity_x_f4=-6; velocity_y_f8=17.5f; acceleration_y_100=0.7f; }
  return;
 }
 case 521: {
  if(sequence_index_13e==0 || sequence_index_13e==4 || sequence_index_13e==8) RESOLVE();
  if(field_6c0==0) byte_750=0;
  if((sequence_index_13e==2 || sequence_index_13e==3) && time_counter_144>=0) {
   switch(byte_605) { case 0: word_732=3; break; case 1: case 2: word_732=4; break; case 3: case 4: word_732=5; break; }
   if(time_counter_144%6==0 && word_730<word_732) {
    field_180=1; SCALE(10); ++word_730;
    float packet[3]; packet[0]=static_cast<float>(-25*word_730+40); packet[1]=15; packet[2]=0;
    SPAWN(815,static_cast<float>(14*facing_104+x_ec),static_cast<float>(y_f0+111.0),static_cast<unsigned char>(facing_104),1,packet,3);
    WAVE(5); if(word_730==1) ADJUST(200,120);
   }
  }
  if((sequence_index_13e==6 || sequence_index_13e==7) && time_counter_144>=0) {
   switch(byte_605) { case 0: word_732=5; break; case 1: case 2: word_732=6; break; case 3: case 4: word_732=7; break; }
   if(time_counter_144%3==0 && word_730<word_732) {
    field_180=1; ++word_730; SCALE(10);
    float packet[3]; packet[0]=static_cast<float>((5-word_730)*15); packet[1]=15; packet[2]=0;
    SPAWN(815,static_cast<float>(14*facing_104+x_ec),static_cast<float>(y_f0+111.0),static_cast<unsigned char>(facing_104),1,packet,3);
    WAVE(5); if(word_730==1) ADJUST(200,120);
   }
  }
  if(sequence_index_13e==1 || sequence_index_13e==2 || sequence_index_13e==3 || sequence_index_13e==5 || sequence_index_13e==6 || sequence_index_13e==7) {
   velocity_y_f8-=acceleration_y_100;
   if(CROSSED()) { y_f0=GROUND(); ZERO(); SEQUENCE(8); return; }
  }
  if(FRAME()) ACTION(0);
  if(sequence_index_13e==0 && frame_timer_142==0 && frame_index_140==3 && static_cast<signed char>(byte_750)==1) {
   SEQUENCE(4); EFFECT(62,static_cast<float>(x_ec-4*facing_104),static_cast<float>(y_f0+116.0),static_cast<unsigned char>(facing_104),-1); return;
  }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==1) { velocity_x_f4=-7.5f; velocity_y_f8=12.5f; acceleration_y_100=0.7f; }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==5) { velocity_x_f4=-6; velocity_y_f8=17.5f; acceleration_y_100=0.7f; }
  return;
 }
 case 522: {
  if(sequence_index_13e==8) RESOLVE();
  if(field_6c0==0) byte_750=0;
  if((sequence_index_13e==2 || sequence_index_13e==3) && time_counter_144>=0) {
   switch(byte_605) { case 0: word_732=3; break; case 1: case 2: word_732=4; break; case 3: case 4: word_732=5; break; }
   if(time_counter_144%6==0 && word_730<word_732) {
    field_180=1; SCALE(10); ++word_730;
    float packet[3]; packet[0]=static_cast<float>(-25*word_730+70); packet[1]=15; packet[2]=0;
    SPAWN(815,static_cast<float>(14*facing_104+x_ec),static_cast<float>(y_f0+111.0),static_cast<unsigned char>(facing_104),1,packet,3);
    WAVE(5); if(word_730==1) ADJUST(200,120);
   }
  }
  if((sequence_index_13e==6 || sequence_index_13e==7) && time_counter_144>=0) {
   switch(byte_605) { case 0: word_732=5; break; case 1: case 2: word_732=6; break; case 3: case 4: word_732=7; break; }
   if(time_counter_144%3==0 && word_730<word_732) {
    field_180=1; ++word_730; SCALE(10);
    float packet[3]; packet[0]=static_cast<float>((5-word_730)*15); packet[1]=15; packet[2]=0;
    SPAWN(815,static_cast<float>(14*facing_104+x_ec),static_cast<float>(y_f0+111.0),static_cast<unsigned char>(facing_104),1,packet,3);
    WAVE(5); if(word_730==1) ADJUST(200,120);
   }
  }
  if(sequence_index_13e==1 || sequence_index_13e==2 || sequence_index_13e==3 || sequence_index_13e==5 || sequence_index_13e==6 || sequence_index_13e==7) {
   velocity_y_f8-=acceleration_y_100;
   if(CROSSED()) { y_f0=GROUND(); ZERO(); SEQUENCE(8); return; }
  }
  if(FRAME()) ACTION(0);
  if(sequence_index_13e==0 && frame_timer_142==0 && frame_index_140==3 && static_cast<signed char>(byte_750)==1) {
   SEQUENCE(4); EFFECT(62,static_cast<float>(x_ec-4*facing_104),static_cast<float>(y_f0+116.0),static_cast<unsigned char>(facing_104),-1); return;
  }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==1) { velocity_x_f4=-7.5f; velocity_y_f8=12.5f; acceleration_y_100=0.7f; }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==5) { velocity_x_f4=-6; velocity_y_f8=17.5f; acceleration_y_100=0.7f; }
  return;
 }
 case 523: {
  if(sequence_index_13e==8) RESOLVE();
  if(field_6c0==0) byte_750=0;
  if((sequence_index_13e==2 || sequence_index_13e==3) && time_counter_144>=0) {
   switch(byte_605) { case 0: word_732=3; break; case 1: case 2: word_732=4; break; case 3: case 4: word_732=5; break; }
   if(time_counter_144%6==0 && word_730<word_732) {
    field_180=1; SCALE(10); ++word_730;
    float packet[3]; packet[0]=static_cast<float>(-25*word_730+40); packet[1]=15; packet[2]=0;
    SPAWN(815,static_cast<float>(14*facing_104+x_ec),static_cast<float>(y_f0+111.0),static_cast<unsigned char>(facing_104),1,packet,3);
    WAVE(5); if(word_730==1) ADJUST(200,120);
   }
  }
  if((sequence_index_13e==6 || sequence_index_13e==7) && time_counter_144>=0) {
   switch(byte_605) { case 0: word_732=5; break; case 1: case 2: word_732=6; break; case 3: case 4: word_732=7; break; }
   if(time_counter_144%3==0 && word_730<word_732) {
    field_180=1; ++word_730; SCALE(10);
    float packet[3]; packet[0]=static_cast<float>((5-word_730)*15); packet[1]=15; packet[2]=0;
    SPAWN(815,static_cast<float>(14*facing_104+x_ec),static_cast<float>(y_f0+111.0),static_cast<unsigned char>(facing_104),1,packet,3);
    WAVE(5); if(word_730==1) ADJUST(200,120);
   }
  }
  if(sequence_index_13e==1 || sequence_index_13e==2 || sequence_index_13e==3 || sequence_index_13e==5 || sequence_index_13e==6 || sequence_index_13e==7) {
   velocity_y_f8-=acceleration_y_100;
   if(CROSSED()) { y_f0=GROUND(); ZERO(); SEQUENCE(8); return; }
  }
  if(FRAME()) ACTION(0);
  if(sequence_index_13e==0 && frame_timer_142==0 && frame_index_140==3 && static_cast<signed char>(byte_750)==1) {
   SEQUENCE(4); EFFECT(62,static_cast<float>(x_ec-4*facing_104),static_cast<float>(y_f0+116.0),static_cast<unsigned char>(facing_104),-1); return;
  }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==1) { velocity_x_f4=-7.5f; velocity_y_f8=12.5f; acceleration_y_100=0.7f; }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==5) { velocity_x_f4=-6; velocity_y_f8=17.5f; acceleration_y_100=0.7f; }
  return;
 }
 case 525: {
  RESOLVE(); if(field_6c0==0) byte_750=0;
  if(sequence_index_13e==1 && time_counter_144>15) { BLOCK(); return; }
  if(FRAME()) ACTION(0);
  if(sequence_index_13e==0) {
   if(frame_timer_142==0 && frame_index_140==8 && static_cast<signed char>(byte_750)==1) { BLOCK(); EFFECT(62,static_cast<float>(x_ec-33*facing_104),static_cast<float>(y_f0+112.0),static_cast<unsigned char>(facing_104),-1); return; }
   if(frame_timer_142==0 && frame_index_140==10) {
    for(float n=0;n<byte_609+1;n+=1.0) {
     float packet[3]; packet[0]=2.0+n*2.0; packet[1]=n*2.0+21.0; packet[2]=0;
     SPAWN(816,static_cast<float>(124*facing_104+x_ec),static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1,packet,3);
    }
    WAVE(3); field_180=1; ADJUST(200,120); SCALE(50);
   }
  }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==1) { ACTION(0); return; }
  if(sequence_index_13e==2 && frame_timer_142==0 && frame_index_140==2) {
   for(float n=0;n<byte_609+3;n+=1.0) {
    float packet[3]; packet[0]=1.0+n*2.0; packet[1]=n*2.0+21.0; packet[2]=0;
    SPAWN(816,static_cast<float>(124*facing_104+x_ec),static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1,packet,3);
   }
   WAVE(3); field_180=1; ADJUST(200,120); SCALE(50);
  }
  return;
 }
 case 526: {
  RESOLVE(); if(field_6c4==0) byte_750=0;
  if(sequence_index_13e==1 && time_counter_144>15) { BLOCK(); return; }
  if(FRAME()) ACTION(0);
  if(sequence_index_13e==0) {
   if(frame_timer_142==0 && frame_index_140==8 && static_cast<signed char>(byte_750)==1) { BLOCK(); EFFECT(62,static_cast<float>(x_ec-33*facing_104),static_cast<float>(y_f0+112.0),static_cast<unsigned char>(facing_104),-1); return; }
   if(frame_timer_142==0 && frame_index_140==10) {
    for(float n=0;n<byte_609+1;n+=1.0) {
     float packet[3]; packet[0]=10.0+n*2.0; packet[1]=n*2.0+21.0; packet[2]=0;
     SPAWN(816,static_cast<float>(124*facing_104+x_ec),static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1,packet,3);
    }
    WAVE(3); field_180=1; ADJUST(200,120); SCALE(50);
   }
  }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==1) { ACTION(0); return; }
  if(sequence_index_13e==2 && frame_timer_142==0 && frame_index_140==2) {
   for(float n=0;n<byte_609+3;n+=1.0) {
    float packet[3]; packet[0]=2.0+n*2.0; packet[1]=n*2.0+21.0; packet[2]=0;
    SPAWN(816,static_cast<float>(124*facing_104+x_ec),static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1,packet,3);
   }
   WAVE(3); field_180=1; ADJUST(200,120); SCALE(50);
  }
  return;
 }
 case 530: {
  RESOLVE(); if(field_6c0==0) byte_750=0;
  if(FRAME()) ACTION(0);
  if(sequence_index_13e==0 && frame_timer_142==0 && frame_index_140==3) {
   float packet[3]={3,5,0}; SPAWN(817,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1,packet,3);
   WAVE(3); field_180=1; ADJUST(200,120); SCALE(50);
  }
  return;
 }
 case 531: {
  RESOLVE(); if(field_6c4==0) byte_750=0;
  if(FRAME()) ACTION(0);
  if(sequence_index_13e==0 && frame_timer_142==0 && frame_index_140==3) {
   float packet[3]={3,5,9}; SPAWN(817,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1,packet,3);
   WAVE(3); field_180=1; ADJUST(200,120); SCALE(50);
  }
  return;
 }
 case 540: {
  RESOLVE(); if(sequence_index_13e==2 && time_counter_144>=20) { BLOCK(); return; }
  if(FRAME()) ACTION(0);
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==1) {
   WAVE(3); ADJUST(200,120); field_180=1; SCALE(50);
   float packet[4]={4,15,0,30};
   SPAWN(820,static_cast<float>(x_ec+0.0),static_cast<float>(y_f0+120.0),static_cast<unsigned char>(facing_104),-1,packet,4);
   packet[0]=-4; packet[1]=15; packet[3]=15;
   SPAWN(820,static_cast<float>(x_ec+0.0),static_cast<float>(y_f0+120.0),static_cast<unsigned char>(facing_104),-1,packet,4);
   packet[0]=8; packet[1]=14; packet[3]=45;
   SPAWN(820,static_cast<float>(x_ec+0.0),static_cast<float>(y_f0+120.0),static_cast<unsigned char>(facing_104),-1,packet,4);
   packet[0]=-8; packet[1]=14; packet[3]=0;
   SPAWN(820,static_cast<float>(x_ec+0.0),static_cast<float>(y_f0+120.0),static_cast<unsigned char>(facing_104),-1,packet,4);
  }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==4) ACTION(0);
  return;
 }
 case 541: {
  RESOLVE(); if(sequence_index_13e==2 && time_counter_144>=10) { BLOCK(); return; }
  if(FRAME()) ACTION(0);
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==1) {
   WAVE(3); ADJUST(200,120); field_180=1; SCALE(50);
   float packet[4]={5,17,0,0};
   SPAWN(820,static_cast<float>(x_ec+0.0),static_cast<float>(y_f0+120.0),static_cast<unsigned char>(facing_104),-1,packet,4);
   packet[0]=10; packet[1]=17; packet[3]=5;
   SPAWN(820,static_cast<float>(x_ec+0.0),static_cast<float>(y_f0+120.0),static_cast<unsigned char>(facing_104),-1,packet,4);
   packet[0]=5; packet[1]=12; packet[3]=10;
   SPAWN(820,static_cast<float>(x_ec+0.0),static_cast<float>(y_f0+120.0),static_cast<unsigned char>(facing_104),-1,packet,4);
   packet[0]=10; packet[1]=12; packet[3]=15;
   SPAWN(820,static_cast<float>(x_ec+0.0),static_cast<float>(y_f0+120.0),static_cast<unsigned char>(facing_104),-1,packet,4);
  }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==4) ACTION(0);
  return;
 }
 case 542: {
  if(sequence_index_13e==8) RESOLVE();
  if(sequence_index_13e==2 && time_counter_144>=20) { acceleration_y_100=0.5f; BLOCK(); return; }
  if(sequence_index_13e==3 || sequence_index_13e==7) {
   velocity_y_f8-=acceleration_y_100; if(CROSSED()) { SEQUENCE(8); y_f0=GROUND(); ZERO(); return; }
  }
  if(FRAME()) ACTION(0);
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==1) {
   WAVE(3); ADJUST(200,120); field_180=1; SCALE(50);
   float packet[4]={4,15,0,30};
   SPAWN(820,static_cast<float>(x_ec+0.0),static_cast<float>(y_f0+120.0),static_cast<unsigned char>(facing_104),-1,packet,4);
   packet[0]=-4; packet[1]=15; packet[3]=15;
   SPAWN(820,static_cast<float>(x_ec+0.0),static_cast<float>(y_f0+120.0),static_cast<unsigned char>(facing_104),-1,packet,4);
   packet[0]=8; packet[1]=14; packet[3]=45;
   SPAWN(820,static_cast<float>(x_ec+0.0),static_cast<float>(y_f0+120.0),static_cast<unsigned char>(facing_104),-1,packet,4);
   packet[0]=-8; packet[1]=14; packet[3]=0;
   SPAWN(820,static_cast<float>(x_ec+0.0),static_cast<float>(y_f0+120.0),static_cast<unsigned char>(facing_104),-1,packet,4);
  }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==4) { ACTION(9); return; }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==8) ACTION(9);
  return;
 }
 case 543: {
  if(sequence_index_13e==8) RESOLVE();
  if(sequence_index_13e==2 && time_counter_144>=20) { acceleration_y_100=0.5f; BLOCK(); return; }
  if(sequence_index_13e==3 || sequence_index_13e==7) {
   velocity_y_f8-=acceleration_y_100; if(CROSSED()) { SEQUENCE(8); y_f0=GROUND(); ZERO(); return; }
  }
  if(FRAME()) ACTION(0);
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==1) {
   WAVE(3); ADJUST(200,120); field_180=1; SCALE(50);
   float packet[4]={5,17,0,0};
   SPAWN(820,static_cast<float>(x_ec+0.0),static_cast<float>(y_f0+120.0),static_cast<unsigned char>(facing_104),-1,packet,4);
   packet[0]=10; packet[1]=17; packet[3]=5;
   SPAWN(820,static_cast<float>(x_ec+0.0),static_cast<float>(y_f0+120.0),static_cast<unsigned char>(facing_104),-1,packet,4);
   packet[0]=5; packet[1]=12; packet[3]=10;
   SPAWN(820,static_cast<float>(x_ec+0.0),static_cast<float>(y_f0+120.0),static_cast<unsigned char>(facing_104),-1,packet,4);
   packet[0]=10; packet[1]=12; packet[3]=15;
   SPAWN(820,static_cast<float>(x_ec+0.0),static_cast<float>(y_f0+120.0),static_cast<unsigned char>(facing_104),-1,packet,4);
  }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==4) { ACTION(9); return; }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==8) ACTION(9);
  return;
 }
 case 545: {
  RESOLVE();
  if((sequence_index_13e==1 || sequence_index_13e==2) && time_counter_144%7==0 && word_730<=6) {
   float packet[3]; packet[0]=static_cast<float>(static_cast<float>(mt19937_next_u32()%110)-60.0);
   packet[1]=static_cast<float>(static_cast<float>(mt19937_next_u32()%170)+10.0); packet[2]=0;
   if(static_cast<unsigned>(selector_random_roll(100))<=50) word_732=1; else word_732=-1;
   SPAWN(821,static_cast<float>(facing_104*packet[0]+x_ec),static_cast<float>(y_f0+packet[1]),static_cast<unsigned char>(facing_104),byte_732,packet,3);
   ++word_730;
  }
  if(sequence_index_13e==2 && time_counter_144>=40) { BLOCK(); return; }
  if(FRAME()) ACTION(0);
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==1) { ADJUST(200,120); SCALE(50); }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==4) ACTION(0);
  return;
 }
 case 546: {
  RESOLVE();
  if(sequence_index_13e==1) {
   if(time_counter_144%7==0 && word_730<=7) {
    float packet[3]; packet[0]=static_cast<float>(static_cast<float>(mt19937_next_u32()%110)-60.0);
    packet[1]=static_cast<float>(static_cast<float>(mt19937_next_u32()%170)+10.0); packet[2]=0;
    if(static_cast<unsigned>(selector_random_roll(100))<=50) word_732=1; else word_732=-1;
    SPAWN(821,static_cast<float>(facing_104*packet[0]+x_ec),static_cast<float>(y_f0+packet[1]),static_cast<unsigned char>(facing_104),byte_732,packet,3);
    ++word_730;
   }
   if(sequence_index_13e==1 && time_counter_144>=60) { BLOCK(); velocity_x_f4=0; return; }
  }
  if(FRAME()) ACTION(0);
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==1) { velocity_x_f4=5; ADJUST(200,120); SCALE(50); }
  return;
 }
 case 547: {
  if(sequence_index_13e==4) RESOLVE();
  if((sequence_index_13e==1 || sequence_index_13e==2) && time_counter_144%7==0 && word_730<=6) {
   float packet[3]; packet[0]=static_cast<float>(static_cast<float>(mt19937_next_u32()%110)-60.0);
   packet[1]=static_cast<float>(static_cast<float>(mt19937_next_u32()%170)+10.0); packet[2]=0;
   if(static_cast<unsigned>(selector_random_roll(100))<=50) word_732=1; else word_732=-1;
   SPAWN(821,static_cast<float>(facing_104*packet[0]+x_ec),static_cast<float>(y_f0+packet[1]),static_cast<unsigned char>(facing_104),byte_732,packet,3);
   ++word_730;
  }
  if(sequence_index_13e==2 && time_counter_144>=30) { BLOCK();return; }
  if(sequence_index_13e<=2) velocity_y_f8-=D(0.1f);
  if(sequence_index_13e==3) { velocity_y_f8-=acceleration_y_100; if(CROSSED()) { ZERO(); y_f0=GROUND(); BLOCK();return; } }
  if(FRAME()) ACTION(0);
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==1) { ADJUST(200,120); SCALE(50); }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==4) ACTION(9);
  return;
 }
 case 548: {
  if(sequence_index_13e==4) RESOLVE();
  if((sequence_index_13e==1 || sequence_index_13e==2) && time_counter_144%7==0 && word_730<=10) {
   float packet[3]; packet[0]=static_cast<float>(static_cast<float>(mt19937_next_u32()%110)-60.0);
   packet[1]=static_cast<float>(static_cast<float>(mt19937_next_u32()%170)+10.0); packet[2]=0;
   if(static_cast<unsigned>(selector_random_roll(100))<=50) word_732=1; else word_732=-1;
   SPAWN(821,static_cast<float>(facing_104*packet[0]+x_ec),static_cast<float>(y_f0+packet[1]),static_cast<unsigned char>(facing_104),byte_732,packet,3);
   ++word_730;
  }
  if(sequence_index_13e==2 && time_counter_144>=50) { BLOCK();return; }
  if(sequence_index_13e<=2) velocity_y_f8-=D(0.1f);
  if(sequence_index_13e==3) { velocity_y_f8-=acceleration_y_100; if(CROSSED()) { ZERO(); y_f0=GROUND(); BLOCK();return; } }
  if(FRAME()) ACTION(0);
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==1) { ADJUST(200,120); SCALE(50); }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==4) ACTION(9);
  return;
 }
 case 560:
  RESOLVE();
  if((sequence_index_13e==1 && time_counter_144>=10) || (sequence_index_13e==2 && time_counter_144>=10)) { BLOCK(); return; }
  if(FRAME()) ACTION(0);
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==1) { WAVE(3); ADJUST(200,120); field_180=1; SCALE(50); }
  return;
 case 565:
  RESOLVE();
  if(sequence_index_13e==1 && time_counter_144>12) BLOCK();
  if(sequence_index_13e==2 && time_counter_144>18) BLOCK();
  if(FRAME()) ACTION(0);
  if(sequence_index_13e==0 && frame_timer_142==0 && frame_index_140==6) { WAVE(3); field_180=1; ADJUST(200,120); SCALE(50); }
  return;
 case 566:
  RESOLVE();
  if(sequence_index_13e==0 && time_counter_144==1) byte_7d0=0;
  if(sequence_index_13e==1 && time_counter_144>12) BLOCK();
  if(sequence_index_13e==2 && time_counter_144>33) BLOCK();
  if(FRAME()) ACTION(0);
  if(sequence_index_13e==0 && frame_timer_142==0 && frame_index_140==6) { WAVE(3); field_180=1; ADJUST(200,120); SCALE(50); }
  return;
 case 568:
  RESOLVE(); if(FRAME()) ACTION(0);
  if(frame_timer_142==0 && frame_index_140==8) {
   WAVE(3); ADJUST(200,45); field_180=1; SCALE(50);
   ++word_7a4; if(word_7a4>=3) word_7a4=3;
   float packet[3]; packet[0]=0; packet[1]=0; packet[2]=word_7a4;
   SPAWN(830,static_cast<float>(x_ec+0.0),static_cast<float>(y_f0+120.0),static_cast<unsigned char>(facing_104),-1,packet,3);
  }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==4) ACTION(0);
  return;
 case 570: {
  RESOLVE(); if(sequence_index_13e==2 && time_counter_144>=18) { BLOCK(); return; }
  if(FRAME()) ACTION(0);
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==1) {
   WAVE(13); ADJUST(200,120); field_180=1; SCALE(50);
   float packet[3]; short const index=word_7a6;
   // Native count is four; this arm has no store to packet[3].
   if(index>0) packet[0]=-atan2_degrees(static_cast<float>(field_7c0[index-1]-y_f0-115.0),static_cast<float>((field_7b0[index-1]-x_ec-13*facing_104)*facing_104));
   else packet[0]=0;
   packet[1]=30; if(byte_60f>=4) packet[2]=3; else packet[2]=0;
   SPAWN(827,static_cast<float>(13*facing_104+x_ec),static_cast<float>(y_f0+115.0),static_cast<unsigned char>(facing_104),-1,packet,4);
   packet[0]=0; packet[1]=0; packet[2]=2;
   SPAWN(827,static_cast<float>(13*facing_104+x_ec),static_cast<float>(y_f0+115.0),static_cast<unsigned char>(facing_104),-1,packet,4);
  }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==4) ACTION(0);
  return;
 }
 case 571: {
  RESOLVE(); if(sequence_index_13e==2 && time_counter_144>=18) { BLOCK(); return; }
  if(FRAME()) ACTION(0);
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==1) {
   WAVE(13); ADJUST(200,120); field_180=1; SCALE(50);
   float packet[3]; short const index=word_7a6;
   // As in570, the fourth transmitted word is not assigned by this arm.
   if(index>0) packet[0]=-atan2_degrees(static_cast<float>(field_7c0[index-1]-y_f0-115.0),static_cast<float>((field_7b0[index-1]-x_ec-13*facing_104)*facing_104));
   else packet[0]=0;
   packet[1]=30; if(byte_60f>=4) packet[2]=6; else packet[2]=5;
   SPAWN(827,static_cast<float>(13*facing_104+x_ec),static_cast<float>(y_f0+115.0),static_cast<unsigned char>(facing_104),-1,packet,4);
   packet[0]=0; packet[1]=0; packet[2]=2;
   SPAWN(827,static_cast<float>(13*facing_104+x_ec),static_cast<float>(y_f0+115.0),static_cast<unsigned char>(facing_104),-1,packet,4);
  }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==4) ACTION(0);
  return;
 }
 case 600: {
  RESOLVE(); publish_texture_state(3,2);
  if(sequence_index_13e==1 && time_counter_144>=39) { BLOCK(); return; }
  if(FRAME()) ACTION(0);
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==1) {
   word_48a=40; EVENT(23);
   EFFECT(115,static_cast<float>(x_ec-34*facing_104),static_cast<float>(y_f0+114.0),static_cast<unsigned char>(facing_104),1);
   dispatch_indexed_sequence_window_45c8b0(0,1,60); advance_secondary_event_effect_cycle();
  }
  if(sequence_index_13e==2 && frame_index_140==2 && frame_timer_142==0) {
   WAVE(20); float packet[3]={0,0,0};
   SPAWN(850,static_cast<float>(125*facing_104+x_ec),static_cast<float>(y_f0+120.0),static_cast<unsigned char>(facing_104),1,packet,3);
  }
  return;
 }
 case 601: {
  RESOLVE(); publish_texture_state(3,2);
  if(sequence_index_13e==1 && time_counter_144>=39) { BLOCK(); return; }
  if(FRAME()) ACTION(0);
  if(frame_timer_142==0 && frame_index_140==2) {
   word_48a=40; EVENT(23);
   EFFECT(115,static_cast<float>(x_ec-44*facing_104),static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);
   dispatch_indexed_sequence_window_45c8b0(0,2,60); advance_secondary_event_effect_cycle();
  }
  if(frame_timer_142==0 && frame_index_140==6) {
   WAVE(22);
   for(int n=0;n<360;n+=60) {
    float packet[4]; packet[0]=0; packet[1]=0; packet[2]=0; packet[3]=static_cast<float>(n);
    SPAWN(851,static_cast<float>(32*facing_104+x_ec),static_cast<float>(y_f0+104.0),static_cast<unsigned char>(facing_104),-1,packet,4);
   }
  }
  return;
 }
 case 602: {
  RESOLVE(); publish_texture_state(3,2);
  if(sequence_index_13e==1 && time_counter_144>60) BLOCK();
  if(sequence_index_13e==2 && time_counter_144>18) BLOCK();
  if(FRAME()) ACTION(0);
  if(sequence_index_13e!=0) return;
  if(frame_timer_142==0 && frame_index_140==3) {
   word_48a=40; EVENT(23);
   EFFECT(115,static_cast<float>(x_ec-60*facing_104),static_cast<float>(y_f0+147.0),static_cast<unsigned char>(facing_104),1);
   dispatch_indexed_sequence_window_45c8b0(0,2,60); advance_secondary_event_effect_cycle();
  }
  if(frame_timer_142==0 && frame_index_140==4) {
   float packet[3]={0,0,0};
   SPAWN(852,static_cast<float>(x_ec-50*facing_104),static_cast<float>(y_f0+184.0),static_cast<unsigned char>(facing_104),-1,packet,3);
  }
  return;
 }
 case 603: {
  RESOLVE(); publish_texture_state(3,2);
  if(sequence_index_13e==1 && time_counter_144>=39) { BLOCK(); return; }
  if(FRAME()) ACTION(0);
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==1) {
   word_48a=40; EVENT(23);
   EFFECT(115,static_cast<float>(x_ec-34*facing_104),static_cast<float>(y_f0+114.0),static_cast<unsigned char>(facing_104),1);
   dispatch_indexed_sequence_window_45c8b0(0,3,60); advance_secondary_event_effect_cycle();
  }
  if(sequence_index_13e==2 && frame_index_140==2 && frame_timer_142==0) {
   WAVE(24); float packet[3]={0,0,0};
   SPAWN(853,static_cast<float>(125*facing_104+x_ec),static_cast<float>(y_f0+120.0),static_cast<unsigned char>(facing_104),1,packet,3);
  }
  return;
 }
 case 604: {
  RESOLVE(); publish_texture_state(3,2);
  if(sequence_index_13e==1 && time_counter_144>=39) { BLOCK(); return; }
  if(FRAME()) ACTION(0);
  if(frame_timer_142==0 && frame_index_140==2) {
   word_48a=40; EVENT(23);
   EFFECT(115,static_cast<float>(x_ec-44*facing_104),static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);
   dispatch_indexed_sequence_window_45c8b0(0,4,60); advance_secondary_event_effect_cycle();
  }
  if(frame_timer_142==0 && frame_index_140==6) {
   WAVE(26);
   for(int n=0;n<720;n+=60) {
    float packet[4]; packet[0]=0; packet[1]=0; packet[2]=0; packet[3]=static_cast<float>(n);
    SPAWN(854,static_cast<float>(32*facing_104+x_ec),static_cast<float>(y_f0+104.0),static_cast<unsigned char>(facing_104),-1,packet,4);
   }
  }
  return;
 }
 case 605: {
  RESOLVE(); publish_texture_state(3,2);
  if(sequence_index_13e==1 && time_counter_144>80) BLOCK();
  if(sequence_index_13e==2 && time_counter_144>18) BLOCK();
  if(FRAME()) ACTION(0);
  if(sequence_index_13e!=0) return;
  if(frame_timer_142==0 && frame_index_140==3) {
   word_48a=40; EVENT(23);
   EFFECT(115,static_cast<float>(x_ec-60*facing_104),static_cast<float>(y_f0+147.0),static_cast<unsigned char>(facing_104),1);
   dispatch_indexed_sequence_window_45c8b0(0,4,60); advance_secondary_event_effect_cycle();
  }
  if(frame_timer_142==0 && frame_index_140==4) {
   for(int n=0;n<6;++n) {
    float packet[4]; packet[0]=0; packet[1]=0; packet[2]=0; packet[3]=static_cast<float>(n);
    SPAWN(855,static_cast<float>(x_ec-50*facing_104),static_cast<float>(y_f0+184.0),static_cast<unsigned char>(facing_104),-1,packet,4);
   }
  }
  return;
 }
 case 606: {
  RESOLVE(); publish_texture_state(3,2);
  if(sequence_index_13e==1) {
   if(time_counter_144%2==0 && word_730<=7) {
    WAVE(28);
    float packet[4]; packet[0]=static_cast<float>((word_730%4)*6-60.0); packet[1]=word_730*3.0+20.0;
    packet[2]=0; packet[3]=word_730;
    SPAWN(856,x_ec,static_cast<float>(y_f0+110.0),static_cast<unsigned char>(facing_104),-1,packet,4); ++word_730;
   }
   if(time_counter_144>=20) BLOCK();
  }
  if(FRAME()) ACTION(0);
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==1) WAVE(28);
  if(sequence_index_13e==0 && frame_timer_142==0 && frame_index_140==3) {
   word_48a=40; EVENT(23);
   EFFECT(115,static_cast<float>(x_ec-60*facing_104),static_cast<float>(y_f0+147.0),static_cast<unsigned char>(facing_104),1);
   dispatch_indexed_sequence_window_45c8b0(0,2,60); advance_secondary_event_effect_cycle();
  }
  return;
 }
 case 607: {
  RESOLVE(); publish_texture_state(3,2); if(FRAME()) ACTION(0);
  if(frame_timer_142==0 && frame_index_140==4) {
   word_48a=40; EVENT(23);
   EFFECT(115,static_cast<float>(x_ec-63*facing_104),static_cast<float>(y_f0+150.0),static_cast<unsigned char>(facing_104),1);
   dispatch_indexed_sequence_window_45c8b0(0,4,60); advance_secondary_event_effect_cycle();
  }
  if(frame_timer_142==0 && frame_index_140==9) {
   WAVE(5); float packet[3]={-30,30,0};
   SPAWN(857,static_cast<float>(20*facing_104+x_ec),static_cast<float>(y_f0+110.0),static_cast<unsigned char>(facing_104),1,packet,3);
  }
  return;
 }
 case 608: {
  RESOLVE(); publish_texture_state(3,2);
  if(sequence_index_13e==1 && (time_counter_144>480 || static_cast<unsigned>(field_6c8)>0)) { BLOCK(); return; }
  if(FRAME()) ACTION(0);
  if(sequence_index_13e==0 && frame_timer_142==0 && frame_index_140==3) {
   word_48a=40; EVENT(23);
   EFFECT(115,static_cast<float>(x_ec-60*facing_104),static_cast<float>(y_f0+147.0),static_cast<unsigned char>(facing_104),1);
   dispatch_indexed_sequence_window_45c8b0(0,3,60); advance_secondary_event_effect_cycle();
  }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==1) {
   float packet[3]={0,0,1};
   SPAWN(858,static_cast<float>(30*facing_104+x_ec),static_cast<float>(y_f0+130.0),static_cast<unsigned char>(facing_104),1,packet,3);
  }
  return;
 }
 case 609:
  RESOLVE(); publish_texture_state(3,2); if(FRAME()) ACTION(0);
  if(sequence_index_13e==0) {
   if(frame_timer_142==0 && frame_index_140==2) {
    word_48a=40; EVENT(23);
    EFFECT(115,static_cast<float>(13*facing_104+x_ec),static_cast<float>(y_f0+110.0),static_cast<unsigned char>(facing_104),1);
    dispatch_indexed_sequence_window_45c8b0(0,2,60); advance_secondary_event_effect_cycle();
   }
   word_4a8=6; word_4ac=6;
  }
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==1) WAVE(35);
  publish_texture_state(3,2); publish_texture_state(3,2);
  if(sequence_index_13e==2 && time_counter_144>=24) BLOCK();
  return;
 case 695:
  RESOLVE(); if(FRAME()) ACTION(0);
  if(sequence_index_13e==0 && frame_timer_142==0 && frame_index_140==7) {
   EVENT(55);
   EFFECT(140,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);
   EFFECT(140,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);
   EFFECT(140,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);
   EFFECT(141,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),-1);
   EFFECT(142,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);
  }
  return;

    case 696:
        resolve_stage_surface_landing_transition();
        velocity_x_f4 = static_cast<float>(velocity_x_f4 - 1.5);
            if (velocity_x_f4 < 0.0f)
            velocity_x_f4 = 0.0f;
        if (advance_frame_and_dispatch())
            set_action_and_finalize(0);
        if (static_cast<unsigned short>(sequence_index_13e))
            return;
        if (!static_cast<unsigned short>(frame_timer_142) && static_cast<unsigned short>(frame_index_140) == 8)
            velocity_x_f4 = 15.0f;
        if (!static_cast<unsigned short>(frame_timer_142) && static_cast<unsigned short>(frame_index_140) == 9) {
            dispatch_indexed_event_member(0x1Du);
            byte_47e = 0;
        }
        return;

 case 710: {
  RESOLVE();
  if(sequence_index_13e==0 && frame_index_140==3 && time_counter_144%8==0 && word_730>0) {
   float packet[3]; packet[0]=-100.0-static_cast<float>(static_cast<unsigned>(selector_random_roll(60)));
   packet[1]=static_cast<float>(static_cast<unsigned>(selector_random_roll(30)))+15.0; packet[2]=0;
   SPAWN(900,static_cast<float>(x_ec-20*facing_104),static_cast<float>(y_f0+105.0),static_cast<unsigned char>(facing_104),-1,packet,3);
   WAVE(31); --word_730;
  }
  if(sequence_index_13e==1 && time_counter_144>=120) { BLOCK(); return; }
  if(FRAME()) ACTION(700);
  if(sequence_index_13e==0 && frame_timer_142==0 && frame_index_140==2) {
   switch(g_match_identifier) { case 3: word_730=15; break; case 2: word_730=13; break; case 1: word_730=11; break; case 0: word_730=9; break; }
  }
  return;
 }
 case 711: {
  if(sequence_index_13e==0 || sequence_index_13e==3) RESOLVE();
  if(sequence_index_13e==2 && time_counter_144%8==0 && word_730>0) {
   float packet[3]; packet[0]=-80.0-static_cast<float>(static_cast<unsigned>(selector_random_roll(60)));
   packet[1]=static_cast<float>(static_cast<unsigned>(selector_random_roll(30)))+15.0; packet[2]=0;
   SPAWN(900,static_cast<float>(x_ec-45*facing_104),static_cast<float>(y_f0+108.0),static_cast<unsigned char>(facing_104),-1,packet,3);
   WAVE(31); --word_730;
  }
  if(sequence_index_13e==1 || sequence_index_13e==2) {
   velocity_y_f8-=acceleration_y_100;
   if(word_730>0) {
    if(velocity_y_f8<-1.0f) velocity_y_f8=-1;
    velocity_x_f4+=D(0.2f); if(velocity_x_f4>-1.0f) velocity_x_f4=-1;
   }
   if(CROSSED()) { y_f0=GROUND(); ZERO(); SEQUENCE(3); return; }
  }
  if(FRAME()) ACTION(0);
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==1) {
   velocity_x_f4=-7.5f; velocity_y_f8=16.5f; acceleration_y_100=0.5f;
   switch(g_match_identifier) { case 3: word_730=15; break; case 2: word_730=13; break; case 1: word_730=11; break; case 0: word_730=9; break; }
  }
  return;
 }
 case 720:
  RESOLVE(); if(sequence_index_13e==1 && time_counter_144>=120) { BLOCK(); return; }
  if(FRAME()) ACTION(700);
  if(time_counter_144!=0 || frame_timer_142!=0 || frame_index_140!=0 || sequence_index_13e!=1) return;
  field_73c=static_cast<float>(static_cast<unsigned>(selector_random_roll(30)));
  switch(g_match_identifier) {
  case 3:
   for(float n=0;n<12;n+=1.0) {
    float packet[4]; packet[0]=n*30.0+field_73c; packet[1]=15; packet[2]=0; packet[3]=0;
    SPAWN(901,x_ec,static_cast<float>(y_f0+105.0),static_cast<unsigned char>(facing_104),-1,packet,4); WAVE(32);
   }
   return;
  case 2:
   for(float n=0;n<9;n+=1.0) {
    float packet[4]; packet[0]=n*40.0+field_73c; packet[1]=15; packet[2]=0; packet[3]=0;
    SPAWN(901,x_ec,static_cast<float>(y_f0+105.0),static_cast<unsigned char>(facing_104),-1,packet,4); WAVE(32);
   }
   return;
  case 1:
   for(float n=0;n<6;n+=1.0) {
    float packet[4]; packet[0]=n*60.0+field_73c; packet[1]=15; packet[2]=0; packet[3]=0;
    SPAWN(901,x_ec,static_cast<float>(y_f0+105.0),static_cast<unsigned char>(facing_104),-1,packet,4); WAVE(32);
   }
   return;
  case 0:
   for(float n=0;n<4;n+=1.0) {
    float packet[4]; packet[0]=n*90.0+field_73c; packet[1]=15; packet[2]=0; packet[3]=0;
    SPAWN(901,x_ec,static_cast<float>(y_f0+105.0),static_cast<unsigned char>(facing_104),-1,packet,4); WAVE(32);
   }
   return;
  default: return;
  }
 case 721:
  RESOLVE(); if(FRAME()) ACTION(700);
  if(frame_timer_142!=0 || frame_index_140!=8) return;
  field_73c=-atan2_degrees(static_cast<float>(related_170->y_f0+100.0-y_f0),static_cast<float>(facing_104*(related_170->x_ec-x_ec)));
  switch(g_match_identifier) {
  case 3:
   for(float n=0;n<4;n+=1.0) {
    double offset=n*10.0;
    float packet[4]; packet[0]=offset+(field_73c-15.0); packet[1]=n*3.0+15.0; packet[2]=0; packet[3]=1;
    SPAWN(901,x_ec,static_cast<float>(y_f0+110.0),static_cast<unsigned char>(facing_104),-1,packet,4); WAVE(32);
   }
   return;
  case 2:
   for(float n=0;n<3;n+=1.0) {
    double offset=n*10.0;
    float packet[4]; packet[0]=offset+(field_73c-10.0); packet[1]=n*3.0+15.0; packet[2]=0; packet[3]=1;
    SPAWN(901,x_ec,static_cast<float>(y_f0+110.0),static_cast<unsigned char>(facing_104),-1,packet,4); WAVE(32);
   }
   return;
  case 1:
   for(float n=0;n<2;n+=1.0) {
    float packet[4]; packet[0]=10.0*n+field_73c; packet[1]=n*3.0+15.0; packet[2]=0; packet[3]=1;
    SPAWN(901,x_ec,static_cast<float>(y_f0+110.0),static_cast<unsigned char>(facing_104),-1,packet,4); WAVE(32);
   }
   return;
  case 0:
   for(float n=0;n<1;n+=1.0) {
    float packet[4]; packet[0]=field_73c; packet[1]=n*3.0+15.0; packet[2]=0; packet[3]=1;
    SPAWN(901,x_ec,static_cast<float>(y_f0+110.0),static_cast<unsigned char>(facing_104),-1,packet,4); WAVE(32);
   }
   return;
  default: return;
  }
 case 730: {
  if(sequence_index_13e==0 || sequence_index_13e==7) RESOLVE();
  if(sequence_index_13e==4 && time_counter_144>=210) { BLOCK(); acceleration_y_100=0.2f; }
  if(sequence_index_13e==1 || sequence_index_13e==2 || sequence_index_13e==3) {
   velocity_y_f8-=acceleration_y_100;
   if(CROSSED()) { SEQUENCE(7); ZERO(); y_f0=GROUND(); return; }
  }
  if(sequence_index_13e==5 || sequence_index_13e==6) {
   velocity_y_f8-=acceleration_y_100;
   if(CROSSED()) { SEQUENCE(7); ZERO(); y_f0=GROUND(); return; }
  }
  if(FRAME()) ACTION(700);
  if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==1) {
   velocity_x_f4=5; velocity_y_f8=static_cast<float>(static_cast<unsigned>(selector_random_roll(35)))*D(0.1f)+11.5; acceleration_y_100=0.3f;
  }
  if(time_counter_144!=0 || frame_timer_142!=0 || frame_index_140!=0 || sequence_index_13e!=4) return;
  ZERO();
  float const heading=static_cast<float>(static_cast<unsigned>(selector_random_roll(360)));
  WAVE(33);
  switch(g_match_identifier) {
  case 3:
   for(float n=0;n<6;n+=1.0) {
    float packet[3]; packet[0]=n*60.0+heading; packet[1]=20; packet[2]=0;
    SPAWN(902,x_ec,static_cast<float>(y_f0+110.0),static_cast<signed char>(2*(word_76a==4)-1),-1,packet,3);
   }
   return;
  case 2:
   for(float n=0;n<5;n+=1.0) {
    float packet[3]; packet[0]=n*72.0+heading; packet[1]=20; packet[2]=0;
    SPAWN(902,x_ec,static_cast<float>(y_f0+110.0),static_cast<signed char>(2*(word_76a==4)-1),-1,packet,3);
   }
   return;
  case 1:
   for(float n=0;n<4;n+=1.0) {
    float packet[3]; packet[0]=n*90.0+heading; packet[1]=20; packet[2]=0;
    SPAWN(902,x_ec,static_cast<float>(y_f0+110.0),static_cast<signed char>(2*(word_76a==4)-1),-1,packet,3);
   }
   return;
  case 0:
   for(float n=0;n<3;n+=1.0) {
    float packet[3]; packet[0]=n*120.0+heading; packet[1]=20; packet[2]=0;
    SPAWN(902,x_ec,static_cast<float>(y_f0+110.0),static_cast<signed char>(2*(word_76a==4)-1),-1,packet,3);
   }
   return;
  default: return;
  }
 }
 case 770:
  if(FRAME()) ACTION(700);
  if(sequence_index_13e!=0 || frame_timer_142!=0 || frame_index_140!=6) return;
  byte_655=1; finalize_sequence_entry(-1); publish_texture_state(3,-1); copy_action_word_176_to_174();
  word_76c=0; word_76a=1; word_766=0; word_768=0; word_764=0; EVENT(23); return;
 case 795:
  if(sequence_index_13e==0) {
   velocity_y_f8-=D(0.3f);
   if(CROSSED()) { EVENT(30); SEQUENCE(1); y_f0=GROUND(); ZERO(); return; }
  }
  if(FRAME()) ACTION(700);
  return;
 case 797:
  if(sequence_index_13e<=2) {
   velocity_y_f8-=acceleration_y_100;
   if(CROSSED()) { EVENT(30); SEQUENCE(3); y_f0=GROUND(); velocity_y_f8=0; return; }
  }
  if(sequence_index_13e==3) {
   velocity_x_f4-=0.75;
   if(velocity_x_f4<0.0f) { velocity_x_f4=0; x_ec=480; }
   if(x_ec>480.0) x_ec=480;
  }
  if(FRAME()) ACTION(0);
  return;
 case 798:
  if(sequence_index_13e<=2) {
   velocity_y_f8-=acceleration_y_100;
   if(CROSSED()) { EVENT(30); SEQUENCE(3); y_f0=GROUND(); velocity_y_f8=0; return; }
  }
  if(sequence_index_13e==3) {
   velocity_x_f4-=0.75;
   if(velocity_x_f4<0.0f) { velocity_x_f4=0; x_ec=800; }
   if(x_ec<800.0) x_ec=800;
  }
  if(FRAME()) ACTION(700);
  return;
 default: update_common_action_state(); return;
 }
 FRAME();
}
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
