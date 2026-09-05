#include <stddef.h>
#include "battle/Collision.hpp"
#include "battle/SpellRuntime.hpp"
#include "battle/PairEmbeddedMode.hpp"

namespace th105 {

int __cdecl selector_random_roll(int limit);
extern int g_fighter_state_4b8_default;
extern int g_secondary_event_effect_id;
extern short g_info_mode_value_6fa88c;

struct FighterActionScratchView { void reset(); };

class FighterCommonActionStateView {
public:
    virtual void slot_00();
    virtual void slot_04();
    virtual void set_action(int action);
    virtual void set_sequence(int sequence);
    virtual void slot_10();
    virtual void slot_14();

    unsigned char resolve_stage_surface_landing_transition();
    unsigned char advance_frame_and_dispatch();
    signed char classify_fighter_x_boundary();
    void publish_battle_layout_scalar(float value);
    void dispatch_indexed_event_member(unsigned index);
    void emit_fighter_effect_433cc0(int effect_code, float x, float y, int direction, int trailing_value);
    void dispatch_indexed_sequence_window_45c8b0(signed char relative_index, int outcome, int source_token);
    void zero_velocity_acceleration();
    int has_crossed_stage_surface_while_descending();
    void copy_action_word_176_to_174();
    void update_common_action_state();

    unsigned char reserved_004[0xe8];
    float x_ec;
    float y_f0;
    float velocity_x_f4;
    float velocity_y_f8;
    float acceleration_x_fc;
    float acceleration_y_100;
    signed char facing_104;
    unsigned char reserved_105[3];
    float float_108;
    float float_10c;
    unsigned char reserved_110[3];
    unsigned char byte_113;
    unsigned char reserved_114[0x18];
    float angle_12c;
    EventSubobject130 event_130;
    short action_13c;
    short sequence_13e;
    short frame_index_140;
    short frame_timer_142;
    int frame_counter_144;
    unsigned char reserved_148[0x336];
    unsigned char byte_47e;
    unsigned char reserved_47f[3];
    short counter_482;
    short word_484;
    unsigned char reserved_486[2];
    short word_488;
    unsigned char reserved_48a[6];
    unsigned char unknown_490;
    unsigned char reserved_491[0x23];
    short word_4b4;
    unsigned char byte_4b6;
    unsigned char reserved_4b7[0x32];
    unsigned char terminal_pending_4e9;
    unsigned char reserved_4ea;
    unsigned char terminal_finalize_4eb;
    unsigned char byte_4ec;
    unsigned char reserved_4ed[0x6b];
    short counter_558;
    signed char state_55a;
    signed char state_55b;
    FighterSequenceController sequence_controller_55c;
    unsigned char reserved_570[0x13c];
    float peer_component_6ac;
    unsigned char reserved_6b0[4];
    int field_6b4;
    int field_6b8;
    int field_6bc;
    int field_6c0;
    int field_6c4;
    int field_6c8;
    unsigned char reserved_6cc[0x60];
    unsigned char state_72c;
    unsigned char reserved_72d[3];
    short word_730;
    short word_732;
    unsigned char reserved_734[4];
    short word_738;
    unsigned char reserved_73a[2];
    float float_73c;
    unsigned char reserved_740[0x36];
    short flag_776;
    float motion_x_778;
    float motion_y_77c;
    float policy_x_780;
    float policy_y_784;
    float policy_scale_788;
    unsigned char reserved_78c[0x14];
    short word_7a0;
    short word_7a2;
};

#define OFFCHECK(field, off) typedef char FighterCommonActionState_##field[(offsetof(FighterCommonActionStateView, field)==off)?1:-1]
OFFCHECK(action_13c,0x13c); OFFCHECK(frame_counter_144,0x144); OFFCHECK(byte_47e,0x47e);
OFFCHECK(sequence_controller_55c,0x55c); OFFCHECK(peer_component_6ac,0x6ac); OFFCHECK(state_72c,0x72c);
OFFCHECK(word_730,0x730); OFFCHECK(flag_776,0x776); OFFCHECK(word_7a2,0x7a2);
typedef char FighterCommonActionState_size[(sizeof(FighterCommonActionStateView)==0x7a4)?1:-1];
#undef OFFCHECK

float __fastcall stage_surface_height_at_x(FighterCommonActionStateView *fighter);

void FighterCommonActionStateView::update_common_action_state()
{
  int v2; // eax
  double v3; // st7
  double v4; // st6
  double v5; // st7
  double v6; // st6
  double v12; // st7
  __int16 v15; // ax
  double v17; // st7
  double v19; // st7
  double v21; // st7
  double v23; // st7
  char v24; // cl
  char v25; // al
  double v26; // st7
  double v28; // st7
  double v30; // st7
  int v32; // eax
  int v33; // ecx
  int v34; // eax
  __int16 v35; // ax
  int v36; // eax
  unsigned __int8 v37; // al
  double v38; // st7
  __int16 v40; // ax
  __int16 v41; // ax
  char v42; // al
  int v45; // edx
  __int16 v46; // ax
  __int16 v47; // ax
  __int16 v48; // ax
  char v50; // al
  int v52; // eax
  double v53; // st7
  __int16 v54; // ax
  int v57; // ecx
  double v58; // st7
  __int16 v59; // ax
  int v62; // ecx
  double v63; // st7
  float v65; // [esp+8h] [ebp-1Ch]
  float v80; // [esp+20h] [ebp-4h]
  float v81; // [esp+20h] [ebp-4h]
  float v82; // [esp+20h] [ebp-4h]
  float v83; // [esp+20h] [ebp-4h]
  float v84; // [esp+20h] [ebp-4h]
  int v85; // [esp+20h] [ebp-4h]
  int v86; // [esp+20h] [ebp-4h]
  float v87; // [esp+20h] [ebp-4h]
  float v88; // [esp+20h] [ebp-4h]
  float v89; // [esp+20h] [ebp-4h]
  float v90; // [esp+20h] [ebp-4h]
  float v91; // [esp+20h] [ebp-4h]
  float v92; // [esp+20h] [ebp-4h]
  float v93; // [esp+20h] [ebp-4h]
  float v94; // [esp+20h] [ebp-4h]
  float v95; // [esp+20h] [ebp-4h]
  float v96; // [esp+20h] [ebp-4h]
  float v97; // [esp+20h] [ebp-4h]
  float v98; // [esp+20h] [ebp-4h]
  float v99; // [esp+20h] [ebp-4h]
  float v100; // [esp+20h] [ebp-4h]
  float v101; // [esp+20h] [ebp-4h]
  float v102; // [esp+20h] [ebp-4h]
  float v103; // [esp+20h] [ebp-4h]
  float v104; // [esp+20h] [ebp-4h]
  float v105; // [esp+20h] [ebp-4h]
  float v106; // [esp+20h] [ebp-4h]
  float v107; // [esp+20h] [ebp-4h]
  float v108; // [esp+20h] [ebp-4h]
  float v109; // [esp+20h] [ebp-4h]
  float v110; // [esp+20h] [ebp-4h]
  float v111; // [esp+20h] [ebp-4h]
  float v112; // [esp+20h] [ebp-4h]
  float v113; // [esp+20h] [ebp-4h]
  float v114; // [esp+20h] [ebp-4h]
  float v115; // [esp+20h] [ebp-4h]
  float v117; // [esp+20h] [ebp-4h]
  float v118; // [esp+20h] [ebp-4h]
  float v119; // [esp+20h] [ebp-4h]
  float v120; // [esp+20h] [ebp-4h]
  v2 = action_13c;
  if ( v2 <= 690 )
  {
    if (v2 == 690)
      goto ACTION_54_60_690;
    else
    {
    switch ( v2 )
    {
      case 50:
        resolve_stage_surface_landing_transition();
        if (velocity_x_f4 < 0.0) {
          if ((velocity_x_f4 = static_cast<float>(velocity_x_f4 + 3.0)) > 0.0f)
            velocity_x_f4 = 0.0f;
        }
        if (classify_fighter_x_boundary() && unknown_490)
          peer_component_6ac = static_cast<float>(velocity_x_f4 * 0.75);
LABEL_11:
        if (advance_frame_and_dispatch())
          set_action(0);
        return;

      case 51:
        resolve_stage_surface_landing_transition();
        if (velocity_x_f4 < 0.0) {
          const float adjusted = static_cast<float>(velocity_x_f4 + 3.0);
          velocity_x_f4 = adjusted;
          if (adjusted > 0.0f)
            velocity_x_f4 = 0.0f;
        }
        if (classify_fighter_x_boundary() && unknown_490)
          peer_component_6ac = static_cast<float>(velocity_x_f4 * 0.75);
        if (advance_frame_and_dispatch())
          set_action(0);
        return;

      case 52:
        resolve_stage_surface_landing_transition();
        if (velocity_x_f4 < 0.0) {
          float adjusted;
          adjusted = static_cast<float>(velocity_x_f4 + 3.0);
          velocity_x_f4 = adjusted;
          if (adjusted > 0.0f)
            velocity_x_f4 = 0.0f;
        }
        if (classify_fighter_x_boundary() && unknown_490)
          peer_component_6ac = static_cast<float>(velocity_x_f4 * 0.75);
        if (advance_frame_and_dispatch())
          set_action(0);
        return;

      case 53:
      case 59:
      case 65:
        resolve_stage_surface_landing_transition();
        if (velocity_x_f4 < 0.0 && word_732 == 0) {
          if ((velocity_x_f4 = static_cast<float>(velocity_x_f4 + 1.5)) > 0.0)
            velocity_x_f4 = 0.0f;
        }
        if (velocity_x_f4 > 0.0 && word_732 == 1) {
          if ((velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.75)) < 0.0)
            velocity_x_f4 = 0.0f;
        }
        if (classify_fighter_x_boundary() && velocity_x_f4 < -8.0f) {
          velocity_x_f4 = -velocity_x_f4;
          word_732 = 1;
          publish_battle_layout_scalar(2.0f);
          dispatch_indexed_event_member(0x16u);
        }
        if (advance_frame_and_dispatch())
          set_action(0);
        return;

      case 54:
      case 60:
ACTION_54_60_690:
        resolve_stage_surface_landing_transition();
        if (advance_frame_and_dispatch())
          set_action(0);
        return;

      case 55:
      case 61:
        resolve_stage_surface_landing_transition();
        if (velocity_x_f4 > 0.0) {
          if ((velocity_x_f4 = static_cast<float>(velocity_x_f4 - 1.5)) < 0.0)
            velocity_x_f4 = 0.0f;
        }
        if (classify_fighter_x_boundary() && unknown_490)
          peer_component_6ac = static_cast<float>(velocity_x_f4 * 0.75);
        if (advance_frame_and_dispatch())
          set_action(0);
        return;

      case 56:
      case 57:
      case 58:
        resolve_stage_surface_landing_transition();
        if (velocity_x_f4 < 0.0) {
          if ((velocity_x_f4 = static_cast<float>(velocity_x_f4 + 1.5)) > 0.0)
            velocity_x_f4 = 0.0f;
        }
        if (classify_fighter_x_boundary() && unknown_490)
          peer_component_6ac = static_cast<float>(velocity_x_f4 * 0.75);
        if (advance_frame_and_dispatch())
          set_action(0);
        return;

      case 62:
        resolve_stage_surface_landing_transition();
        if (velocity_x_f4 < 0.0f) {
          if ((velocity_x_f4 = static_cast<float>(velocity_x_f4 + 1.5)) > 0.0f)
            velocity_x_f4 = 0.0f;
        }
        goto ACTION_62_67_BOUNDARY;

      case 63:
        resolve_stage_surface_landing_transition();
        if (velocity_x_f4 < 0.0f) {
          const float adjusted = static_cast<float>(velocity_x_f4 + 1.5);
          velocity_x_f4 = adjusted;
          if (adjusted > 0.0f)
            velocity_x_f4 = 0.0f;
        }
        if (classify_fighter_x_boundary() && unknown_490)
          peer_component_6ac = static_cast<float>(velocity_x_f4 * 0.75);
        if (advance_frame_and_dispatch())
          set_action(2);
        return;

      case 64:
        resolve_stage_surface_landing_transition();
        if (velocity_x_f4 < 0.0f) {
          if ((velocity_x_f4 = static_cast<float>(velocity_x_f4 + 1.5)) > 0.0f)
            velocity_x_f4 = 0.0f;
        }
        if (classify_fighter_x_boundary() && unknown_490)
          peer_component_6ac = static_cast<float>(velocity_x_f4 * 0.75);
        if (advance_frame_and_dispatch())
          set_action(2);
        return;

      case 66:
        resolve_stage_surface_landing_transition();
        goto ACTION_62_67_ADVANCE;

      case 67:
        resolve_stage_surface_landing_transition();
        if (velocity_x_f4 > 0.0f) {
          if ((velocity_x_f4 = static_cast<float>(velocity_x_f4 - 1.5)) > 0.0f)
            velocity_x_f4 = 0.0f;
        }
ACTION_62_67_BOUNDARY:
        if (classify_fighter_x_boundary() && unknown_490)
          peer_component_6ac = static_cast<float>(velocity_x_f4 * 0.75);
ACTION_62_67_ADVANCE:
        if (advance_frame_and_dispatch())
          set_action(2);
        return;

      case 70: {
        const short direction = word_730;
        if (direction > 0) {
          if (velocity_x_f4 > 2.0f)
            velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.5);
          if (velocity_x_f4 < 2.0f)
            velocity_x_f4 = 2.0f;
        }
        if (direction < 0) {
          if (velocity_x_f4 < -2.0f)
            velocity_x_f4 = static_cast<float>(velocity_x_f4 + 0.5);
          if (velocity_x_f4 > -2.0f)
            velocity_x_f4 = -2.0f;
        }
        velocity_y_f8 -= acceleration_y_100;
        if (classify_fighter_x_boundary() && velocity_x_f4 < 0.0f) {
          if ((velocity_x_f4 = static_cast<float>(velocity_x_f4 + 1.0)) > 0.0f)
            velocity_x_f4 = 0.0f;
          if (unknown_490)
            peer_component_6ac = velocity_x_f4;
        }
        if (has_crossed_stage_surface_while_descending()) {
          zero_velocity_acceleration();
          y_f0 = 0.0f;
          set_action(10);
          return;
        }
        if (advance_frame_and_dispatch())
          set_action(9);
        return;
      }

      case 71:
        if (sequence_13e == 1 && velocity_y_f8 < 2.0) {
          slot_14();
          return;
        }
        v80 = velocity_y_f8 - acceleration_y_100;
        velocity_y_f8 = v80;
        if (v80 > 0.0)
          velocity_y_f8 = v80 - acceleration_y_100;
        if ((unsigned __int8)has_crossed_stage_surface_while_descending()) {
          word_730 = 100 * (int)velocity_x_f4;
          word_732 = 100 * (int)velocity_y_f8;
          zero_velocity_acceleration();
          y_f0 = 0.0;
          set_action(97);
          publish_battle_layout_scalar(2.0f);
          dispatch_indexed_event_member(0x16u);
          return;
        }
        if (word_730 > 0)
          --word_730;
        if (classify_fighter_x_boundary() && velocity_x_f4 < 0.0) {
          if ((velocity_x_f4 = static_cast<float>(velocity_x_f4 + 1.0)) > 0.0f)
            velocity_x_f4 = 0.0f;
          if (unknown_490)
            peer_component_6ac = static_cast<float>((double)word_730 * -2.0);
        }
        advance_frame_and_dispatch();
        return;

      case 72:
        if (sequence_13e == 1 && velocity_y_f8 < 2.0) {
          slot_14();
          return;
        }
        velocity_y_f8 -= acceleration_y_100;
        if ((unsigned __int8)has_crossed_stage_surface_while_descending()) {
          word_730 = 100 * (int)velocity_x_f4;
          word_732 = 100 * (int)velocity_y_f8;
          zero_velocity_acceleration();
          y_f0 = 0.0;
          set_action(97);
          publish_battle_layout_scalar(2.0f);
          dispatch_indexed_event_member(0x16u);
          return;
        }
        if (classify_fighter_x_boundary() && velocity_x_f4 < 0.0) {
          if ((velocity_x_f4 = static_cast<float>(velocity_x_f4 + 1.0)) > 0.0f)
            velocity_x_f4 = 0.0f;
          if (unknown_490)
            peer_component_6ac = velocity_x_f4;
        }
        advance_frame_and_dispatch();
        return;

      case 73:
        if ((unsigned __int8)has_crossed_stage_surface_while_descending()) {
          word_730 = 100 * (int)velocity_x_f4;
          word_732 = 100 * (int)velocity_y_f8;
          zero_velocity_acceleration();
          y_f0 = 0.0;
          set_action(97);
          publish_battle_layout_scalar(5.0f);
          dispatch_indexed_event_member(0x16u);
          return;
        }
        advance_frame_and_dispatch();
        if (!frame_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_13e == 1 && 0.0 != velocity_y_f8) {
          if (0.0 == velocity_x_f4)
            set_sequence(3);
          else
            set_sequence(2);
          return;
        }
        if (--word_730 < 0)
          word_730 = 0;
        if (classify_fighter_x_boundary() && velocity_x_f4 < 0.0) {
          if ((velocity_x_f4 = static_cast<float>(velocity_x_f4 + 2.5)) > 0.0f)
            velocity_x_f4 = 0.0f;
          if (unknown_490)
            peer_component_6ac = static_cast<float>((double)word_730 * -2.0);
        }
        return;

      case 74:
        if (sequence_13e == 1 && velocity_y_f8 < 2.0) {
          slot_14();
          return;
        }
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -25.0) {
          set_action(76);
          return;
        }
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -15.0) {
          set_action(78);
          return;
        }
        velocity_y_f8 -= acceleration_y_100;
        if ((unsigned __int8)has_crossed_stage_surface_while_descending()) {
          word_730 = 100 * (int)velocity_x_f4;
          word_732 = 100 * (int)velocity_y_f8;
          zero_velocity_acceleration();
          y_f0 = 0.0;
          set_action(97);
          publish_battle_layout_scalar(2.0f);
          dispatch_indexed_event_member(0x16u);
          return;
        }
        advance_frame_and_dispatch();
        return;

      case 75:
        if ((unsigned __int8)has_crossed_stage_surface_while_descending()) {
          word_730 = 100 * (int)velocity_x_f4;
          word_732 = 100 * (int)velocity_y_f8;
          zero_velocity_acceleration();
          y_f0 = 0.0;
          set_action(97);
          publish_battle_layout_scalar(5.0f);
          dispatch_indexed_event_member(0x16u);
          return;
        }
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -25.0) {
          set_action(76);
          return;
        }
        if (classify_fighter_x_boundary() && velocity_x_f4 <= -15.0) {
          set_action(78);
          return;
        }
        advance_frame_and_dispatch();
        if (!frame_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_13e == 1 && 0.0 != velocity_y_f8) {
          if (0.0 == velocity_x_f4)
            set_sequence(3);
          else
            set_sequence(2);
        }
        return;

      case 76:
        if (sequence_13e > 0)
          angle_12c -= 30.0f;
        velocity_y_f8 -= acceleration_y_100;
        if ((unsigned __int8)has_crossed_stage_surface_while_descending()) {
          dispatch_indexed_event_member(0x16u);
          word_730 = 100 * (int)velocity_x_f4;
          word_732 = 100 * (int)velocity_y_f8;
          zero_velocity_acceleration();
          y_f0 = 0.0;
          set_action(97);
          angle_12c = 0.0f;
          publish_battle_layout_scalar(2.0f);
          reinterpret_cast<FighterActionScratchView *>(reinterpret_cast<unsigned char *>(this) + 4)->reset();
          return;
        }
        advance_frame_and_dispatch();
        if (!frame_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_13e == 1) {
          velocity_x_f4 = -3.0f;
          velocity_y_f8 = 10.0f;
          acceleration_y_100 = 0.5f;
          facing_104 = -facing_104;
        }
        return;

      case 77:
        angle_12c -= 30.0f;
        velocity_y_f8 -= acceleration_y_100;
        if (!(unsigned __int8)has_crossed_stage_surface_while_descending()) {
          advance_frame_and_dispatch();
          return;
        }
        dispatch_indexed_event_member(0x16u);
        word_730 = 100 * (int)velocity_x_f4;
        word_732 = 100 * (int)velocity_y_f8;
        zero_velocity_acceleration();
        y_f0 = 0.0;
        set_action(97);
        angle_12c = 0.0f;
        publish_battle_layout_scalar(2.0f);
        reinterpret_cast<FighterActionScratchView *>(reinterpret_cast<unsigned char *>(this) + 4)->reset();
        return;

      case 78:
        velocity_y_f8 -= acceleration_y_100;
        if ((unsigned __int8)has_crossed_stage_surface_while_descending()) {
          dispatch_indexed_event_member(0x16u);
          word_730 = 100 * (int)velocity_x_f4;
          word_732 = 100 * (int)velocity_y_f8;
          zero_velocity_acceleration();
          y_f0 = 0.0;
          set_action(97);
          publish_battle_layout_scalar(2.0f);
          return;
        }
        advance_frame_and_dispatch();
        if (!frame_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_13e == 1) {
          velocity_x_f4 = -5.0f;
          velocity_y_f8 = 3.0f;
          acceleration_y_100 = 0.5f;
          facing_104 = -facing_104;
        }
        return;

      case 88:
        if ((unsigned __int8)has_crossed_stage_surface_while_descending()) {
          word_730 = 100 * (int)velocity_x_f4;
          word_732 = 100 * (int)velocity_y_f8;
          zero_velocity_acceleration();
          y_f0 = 0.0;
          set_action(89);
          publish_battle_layout_scalar(5.0f);
          dispatch_indexed_event_member(0x16u);
          return;
        }
        advance_frame_and_dispatch();
        if (!frame_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_13e == 1 && 0.0 != velocity_y_f8) {
          if (0.0 == velocity_x_f4)
            set_sequence(3);
          else
            set_sequence(2);
          return;
        }
        if (--word_730 < 0)
          word_730 = 0;
        if (classify_fighter_x_boundary() && velocity_x_f4 < 0.0) {
          if ((velocity_x_f4 = static_cast<float>(velocity_x_f4 + 2.5)) > 0.0f)
            velocity_x_f4 = 0.0f;
          if (unknown_490)
            peer_component_6ac = static_cast<float>((double)word_730 * -2.0);
        }
        return;
      case 89:
        if ( sequence_13e > 0
          && (angle_12c = angle_12c - 40.0,
              velocity_y_f8 = velocity_y_f8 - acceleration_y_100,
              (unsigned __int8)has_crossed_stage_surface_while_descending()) )
        {
          v30 = velocity_y_f8;
          word_730 = 100 * (int)velocity_x_f4;
          word_732 = 100 * (int)v30;
          zero_velocity_acceleration();y_f0 = 0.0;
          set_action(97);
          angle_12c = 0.0;
          publish_battle_layout_scalar(2.0);
          reinterpret_cast<FighterActionScratchView *>(reinterpret_cast<unsigned char *>(this) + 4)->reset();
          dispatch_indexed_event_member(0x16u);
        }
        else
        {
          advance_frame_and_dispatch();
          if ( !frame_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_13e == 1 )
          {
            v32 = word_7a0;
            v33 = word_7a2;
            v85 = -word_732;
            velocity_x_f4 = (double)word_730 * 0.0025f;
            velocity_y_f8 = 0.0025f * (double)v85;
            acceleration_y_100 = 0.25;
            float_108 = (float)v32;
            float_10c = (float)v33;
          }
        }
        return;
      case 97:
        if ( sequence_13e == 3 )
          resolve_stage_surface_landing_transition();
        v34 = field_6b4 * facing_104;
        if ( v34 > 0
          && (field_6bc || field_6c0 || field_6c4 || field_6c8) )
        {
          word_730 = 1;
        }
        if ( v34 < 0
          && (field_6bc || field_6c0 || field_6c4 || field_6c8) )
        {
          word_730 = 2;
        }
        v35 = sequence_13e;
        if ( (v35 == 1 || v35 == 2)
          && (velocity_y_f8 = velocity_y_f8 - acceleration_y_100, (unsigned __int8)has_crossed_stage_surface_while_descending()) )
        {
          y_f0 = 0.0;
          zero_velocity_acceleration();
          set_sequence(3);
        }
        else
        {
          if ( (unsigned __int8)advance_frame_and_dispatch() )
          {
            set_action(98);
            if ( terminal_pending_4e9 )
              set_action(99);
          }
          if ( !frame_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_13e == 1 )
          {
            v86 = -word_732;
            velocity_x_f4 = (double)word_730 * 0.005f;
            velocity_y_f8 = 0.005f * (double)v86;
            acceleration_y_100 = 2.0;
          }
        }
        return;
      case 98:
        resolve_stage_surface_landing_transition();
        v36 = field_6b4 * facing_104;
        if ( v36 > 0
          && (field_6bc || field_6c0 || field_6c4 || field_6c8) )
        {
          word_730 = 1;
        }
        if ( v36 < 0
          && (field_6bc || field_6c0 || field_6c4 || field_6c8) )
        {
          word_730 = 2;
        }
        if ( (unsigned __int8)advance_frame_and_dispatch() )
        {
          set_action(199);
          if ( word_730 == 1 )
            set_action(197);
          if ( word_730 == 2 )
            set_action(198);
        }
        return;
      case 99:
        resolve_stage_surface_landing_transition();
        if ( sequence_13e == 3 )
        {
          v37 = byte_113;
          event_130.storage_00[5] = 0;
          if ( v37 <= 3u )
            byte_113 = 0;
          else
            byte_113 = v37 - 3;
        }
        advance_frame_and_dispatch();
        if ( !frame_counter_144
          && !frame_timer_142
          && !frame_index_140
          && sequence_13e == 2
          && !terminal_finalize_4eb )
        {
          if ( state_55a > 0
            && state_72c == 2
            && sequence_controller_55c.entry_at_checked(0)->record_id_00 >= 248 )
          {
            copy_action_word_176_to_174();
          }
          set_action(199);
          terminal_pending_4e9 = 0;
          byte_4ec = 1;
        }
        return;
      case 140:
        resolve_stage_surface_landing_transition();
        if ( velocity_x_f4 < 0.0 )
        {
          v87 = velocity_x_f4 + 0.6000000238418579;
          velocity_x_f4 = v87;
          if ( v87 > 0.0 )
            velocity_x_f4 = 0.0;
        }
        if ( classify_fighter_x_boundary() && unknown_490 )
          peer_component_6ac = velocity_x_f4 * 0.75;
        if ((unsigned __int8)advance_frame_and_dispatch())
          set_action(0);
        return;
      case 143:
        resolve_stage_surface_landing_transition();
        if ( velocity_x_f4 < 0.0 )
        {
          v88 = velocity_x_f4 + 0.6000000238418579;
          velocity_x_f4 = v88;
          if ( v88 > 0.0 )
            velocity_x_f4 = 0.0;
        }
        if ( classify_fighter_x_boundary() && unknown_490 )
          peer_component_6ac = velocity_x_f4 * 0.75;
        if ((unsigned __int8)advance_frame_and_dispatch())
          set_action(0);
        return;
      case 144:
        resolve_stage_surface_landing_transition();
        if ( velocity_x_f4 < 0.0 )
        {
          v89 = velocity_x_f4 + 0.6000000238418579;
          velocity_x_f4 = v89;
          if ( v89 > 0.0 )
            velocity_x_f4 = 0.0;
        }
        if ( classify_fighter_x_boundary() && unknown_490 )
          peer_component_6ac = velocity_x_f4 * 0.75;
        if ((unsigned __int8)advance_frame_and_dispatch())
          set_action(0);
        return;
      case 145:
        if (sequence_13e == 1) {
          if (2.0f > velocity_y_f8)
            goto LABEL_291;
        }
        goto LABEL_285;
      case 149:
        if (sequence_13e == 1) {
          if (2.0f > velocity_y_f8) {
LABEL_291:
            slot_14();
            return;
          }
        }
LABEL_285:
        {
          velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
          if ( (unsigned __int8)has_crossed_stage_surface_while_descending() )
          {
            v38 = velocity_y_f8;
            word_730 = 100 * (int)velocity_x_f4;
            word_732 = 100 * (int)v38;
            zero_velocity_acceleration();y_f0 = 0.0;
            set_action(97);
            publish_battle_layout_scalar(2.0f);
          }
          else if ( (unsigned __int8)advance_frame_and_dispatch() )
          {
            set_sequence(5);
          }
        }
        break;
      case 150:
        resolve_stage_surface_landing_transition();
        if ( velocity_x_f4 < 0.0 )
        {
          v90 = velocity_x_f4 + 0.6000000238418579;
          velocity_x_f4 = v90;
          if ( v90 > 0.0 )
            velocity_x_f4 = 0.0;
        }
        if ( classify_fighter_x_boundary() && unknown_490 )
          peer_component_6ac = velocity_x_f4 * 0.75;
        if ((unsigned __int8)advance_frame_and_dispatch())
          set_action(0);
        return;
      case 151:
        resolve_stage_surface_landing_transition();
        if ( velocity_x_f4 < 0.0 )
        {
          v91 = velocity_x_f4 + 0.6000000238418579;
          velocity_x_f4 = v91;
          if ( v91 > 0.0 )
            velocity_x_f4 = 0.0;
        }
        if ( classify_fighter_x_boundary() && unknown_490 )
          peer_component_6ac = velocity_x_f4 * 0.75;
        if ((unsigned __int8)advance_frame_and_dispatch())
          set_action(0);
        return;
      case 152:
        resolve_stage_surface_landing_transition();
        if ( velocity_x_f4 < 0.0 )
        {
          v92 = velocity_x_f4 + 0.6000000238418579;
          velocity_x_f4 = v92;
          if ( v92 > 0.0 )
            velocity_x_f4 = 0.0;
        }
        if ( classify_fighter_x_boundary() && unknown_490 )
          peer_component_6ac = velocity_x_f4 * 0.75;
        if ((unsigned __int8)advance_frame_and_dispatch())
          set_action(0);
        return;
      case 153:
        resolve_stage_surface_landing_transition();
        if ( velocity_x_f4 < 0.0 )
        {
          v93 = velocity_x_f4 + 0.6000000238418579;
          velocity_x_f4 = v93;
          if ( v93 > 0.0 )
            velocity_x_f4 = 0.0;
        }
        if ( classify_fighter_x_boundary() && unknown_490 )
          peer_component_6ac = velocity_x_f4 * 0.75;
        if ((unsigned __int8)advance_frame_and_dispatch())
          set_action(0);
        return;
      case 154:
        resolve_stage_surface_landing_transition();
        if ( velocity_x_f4 < 0.0 )
        {
          v94 = velocity_x_f4 + 0.6000000238418579;
          velocity_x_f4 = v94;
          if ( v94 > 0.0 )
            velocity_x_f4 = 0.0;
        }
        if ( classify_fighter_x_boundary() && unknown_490 )
          peer_component_6ac = velocity_x_f4 * 0.75;
        if ((unsigned __int8)advance_frame_and_dispatch())
          set_action(2);
        return;
      case 155:
        resolve_stage_surface_landing_transition();
        if ( velocity_x_f4 < 0.0 )
        {
          v95 = velocity_x_f4 + 0.6000000238418579;
          velocity_x_f4 = v95;
          if ( v95 > 0.0 )
            velocity_x_f4 = 0.0;
        }
        if ( classify_fighter_x_boundary() && unknown_490 )
          peer_component_6ac = velocity_x_f4 * 0.75;
        if ((unsigned __int8)advance_frame_and_dispatch())
          set_action(2);
        return;
      case 156:
        resolve_stage_surface_landing_transition();
        if ( velocity_x_f4 < 0.0 )
        {
          v96 = velocity_x_f4 + 0.6000000238418579;
          velocity_x_f4 = v96;
          if ( v96 > 0.0 )
            velocity_x_f4 = 0.0;
        }
        if ( classify_fighter_x_boundary() && unknown_490 )
          peer_component_6ac = velocity_x_f4 * 0.75;
        if ((unsigned __int8)advance_frame_and_dispatch())
          set_action(2);
        return;
      case 157:
        resolve_stage_surface_landing_transition();
        if ( velocity_x_f4 < 0.0 )
        {
          v97 = velocity_x_f4 + 0.6000000238418579;
          velocity_x_f4 = v97;
          if ( v97 > 0.0 )
            velocity_x_f4 = 0.0;
        }
        if ( classify_fighter_x_boundary() && unknown_490 )
          peer_component_6ac = velocity_x_f4 * 0.75;
        if ((unsigned __int8)advance_frame_and_dispatch())
          set_action(2);
        return;
      case 158:
        velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
        if ( (unsigned __int8)has_crossed_stage_surface_while_descending() )
          goto LABEL_357;
        v40 = word_730;
        if ( v40 > 0 )
          word_730 = v40 - 1;
        if ( classify_fighter_x_boundary() && velocity_x_f4 < 0.0 )
        {
          v98 = velocity_x_f4 + 1.0;
          velocity_x_f4 = v98;
          if ( v98 > 0.0 )
            velocity_x_f4 = 0.0;
          if ( unknown_490 )
            peer_component_6ac = (double)word_730 * -2.0;
        }
        goto LABEL_366;
      case 159:
        resolve_stage_surface_landing_transition();
        v3 = 0.0;
        if ( velocity_x_f4 >= 0.0 )
          goto LABEL_8;
        v99 = velocity_x_f4 + 0.6000000238418579;
        v100 = v99 + 0.6000000238418579;
        v4 = v100;
        goto LABEL_6;
      case 160:
        resolve_stage_surface_landing_transition();
        v3 = 0.0;
        if ( velocity_x_f4 >= 0.0 )
          goto LABEL_8;
        v101 = velocity_x_f4 + 0.6000000238418579;
        v102 = v101 + 0.6000000238418579;
        v4 = v102;
        goto LABEL_6;
      case 161:
        resolve_stage_surface_landing_transition();
        v3 = 0.0;
        if ( velocity_x_f4 >= 0.0 )
          goto LABEL_8;
        v103 = velocity_x_f4 + 0.6000000238418579;
        v104 = v103 + 0.6000000238418579;
        v4 = v104;
        goto LABEL_6;
      case 162:
        resolve_stage_surface_landing_transition();
        v3 = 0.0;
        if ( velocity_x_f4 >= 0.0 )
          goto LABEL_8;
        v105 = velocity_x_f4 + 0.6000000238418579;
        v106 = v105 + 0.6000000238418579;
        v4 = v106;
LABEL_6:
        velocity_x_f4 = v4;
        if ( v4 > v3 )
          velocity_x_f4 = v3;
LABEL_8:
        if ( classify_fighter_x_boundary() )
        {
          if ( unknown_490 )
            peer_component_6ac = velocity_x_f4 * 0.75;
        }
        goto LABEL_11;
      case 163:
        resolve_stage_surface_landing_transition();
        v5 = 0.0;
        if ( velocity_x_f4 >= 0.0 )
          goto LABEL_49;
        v107 = velocity_x_f4 + 0.6000000238418579;
        v108 = v107 + 0.6000000238418579;
        v6 = v108;
        goto LABEL_47;
      case 164:
        resolve_stage_surface_landing_transition();
        v5 = 0.0;
        if ( velocity_x_f4 >= 0.0 )
          goto LABEL_49;
        v109 = velocity_x_f4 + 0.6000000238418579;
        v110 = v109 + 0.6000000238418579;
        v6 = v110;
        goto LABEL_47;
      case 165:
        resolve_stage_surface_landing_transition();
        v5 = 0.0;
        if ( velocity_x_f4 >= 0.0 )
          goto LABEL_49;
        v111 = velocity_x_f4 + 0.6000000238418579;
        v112 = v111 + 0.6000000238418579;
        v6 = v112;
        goto LABEL_47;
      case 166:
        resolve_stage_surface_landing_transition();
        v5 = 0.0;
        if ( velocity_x_f4 >= 0.0 )
          goto LABEL_49;
        v113 = velocity_x_f4 + 0.6000000238418579;
        v114 = v113 + 0.6000000238418579;
        v6 = v114;
LABEL_47:
        velocity_x_f4 = v6;
        if ( v6 > v5 )
          velocity_x_f4 = v5;
LABEL_49:
        if ( classify_fighter_x_boundary() && unknown_490 )
          peer_component_6ac = velocity_x_f4 * 0.75;
LABEL_52:
        if ( (unsigned __int8)advance_frame_and_dispatch() )
          set_action(2);
        return;
      case 167:
        velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
        if ( (unsigned __int8)has_crossed_stage_surface_while_descending() )
          goto LABEL_357;
        v41 = word_730;
        if ( v41 > 0 )
          word_730 = v41 - 1;
        if ( classify_fighter_x_boundary() && velocity_x_f4 < 0.0 )
        {
          v115 = velocity_x_f4 + 1.0;
          velocity_x_f4 = v115;
          if ( v115 > 0.0 )
            velocity_x_f4 = 0.0;
          if ( unknown_490 )
            peer_component_6ac = (double)word_730 * -2.0;
        }
LABEL_366:
LABEL_367:
        if ( (unsigned __int8)advance_frame_and_dispatch() )
          set_action(9);
        return;
      case 180:
      case 181:
        velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
        v42 = has_crossed_stage_surface_while_descending();
        if (!v42) {
          advance_frame_and_dispatch();
          return;
        }
LABEL_357:
        set_action(10);
        y_f0 = 0.0;
        zero_velocity_acceleration();
        return;
      default:
        return;
    }
      }
  }
  else
  {
    switch ( action_13c )
    {
      case 691:
        resolve_stage_surface_landing_transition();
        if ( (unsigned __int8)advance_frame_and_dispatch() )
          set_action(0);
        if ( frame_counter_144 == 20 )
        {
          emit_fighter_effect_433cc0(70, x_ec, y_f0, facing_104, 1);
          if ( g_fighter_state_4b8_default == 16 )
          {
            g_info_mode_value_6fa88c = 999;
            if ( g_secondary_event_effect_id != 16 )
              reinterpret_cast<PairEmbeddedModeView *>(&event_130)->select_pair_mode_434780(g_secondary_event_effect_id, 1);
          }
          else
          {
            byte_4b6 = 1;
          }
          dispatch_indexed_sequence_window_45c8b0(0, 1, 60);
        }
        if ( frame_counter_144 >= 20 && !(frame_counter_144 % 7) )
          emit_fighter_effect_433cc0(135, x_ec, y_f0, facing_104, -1);
        if ( frame_counter_144 >= 20 && !(frame_counter_144 % 5) )
          emit_fighter_effect_433cc0(
              136,
              static_cast<float>(static_cast<unsigned int>(selector_random_roll(200)))
                  + x_ec - 100.0,
              y_f0,
              facing_104,
              1);
        break;
      case 692:
        resolve_stage_surface_landing_transition();
        if ( sequence_13e == 1 )
        {
          v45 = frame_counter_144 % 15;
          counter_558 += 15;
          if ( !v45 )
            emit_fighter_effect_433cc0(153, x_ec, y_f0, facing_104, 1);
          if ( !(frame_counter_144 % 10) )
            emit_fighter_effect_433cc0(152, x_ec, y_f0, facing_104, -1);
          if (frame_counter_144 >= 67) {
            slot_14();
            return;
          }
        }
        if ( (unsigned __int8)advance_frame_and_dispatch() )
          set_action(0);
        if ( !frame_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_13e == 1 )
          dispatch_indexed_event_member(0x38u);
        break;
      case 693:
        resolve_stage_surface_landing_transition();
        if (sequence_13e == 1 && frame_counter_144 >= 40) {
          slot_14();
          return;
        }
        if ( (unsigned __int8)advance_frame_and_dispatch() )
          set_action(0);
        if ( !frame_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_13e == 1 )
        {
          word_4b4 = 250;
          dispatch_indexed_event_member(0x38u);
        }
        break;
      case 694:
        resolve_stage_surface_landing_transition();
        if ( sequence_13e != 1 )
          goto LABEL_522;
        if ( word_484 < 1000 )
        {
          v46 = word_488;
          if (v46 < 4800) {
            if ((word_488 += 240) >= 4800)
              word_488 = 4799;
          }
        }
        if ( !(frame_counter_144 % 15) )
          emit_fighter_effect_433cc0(155, x_ec, y_f0, facing_104, 1);
        if ( !(frame_counter_144 % 10) )
          emit_fighter_effect_433cc0(154, x_ec, y_f0, facing_104, -1);
        if ( frame_counter_144 >= 20 )
        {
LABEL_444:
          slot_14();
        }
        else
        {
LABEL_522:
          if ( (unsigned __int8)advance_frame_and_dispatch() )
            set_action(0);
          if ( !frame_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_13e == 1 )
          {
            dispatch_indexed_event_member(0x38u);
            counter_482 += 1000;
            v48 = word_484;
            if ( counter_482 >= v48 )
              counter_482 = v48;
          }
        }
        break;
      case 700:
        resolve_stage_surface_landing_transition();
        if (!velocity_x_f4)
          byte_47e = 0;
        if (!byte_47e) {
          zero_velocity_acceleration();
          advance_frame_and_dispatch();
          return;
        }
        if (velocity_x_f4 > 0.0) {
          v117 = velocity_x_f4 - 0.5;
          velocity_x_f4 = v117;
          if (v117 < 0.0) {
            zero_velocity_acceleration();
            byte_47e = 0;
          }
        }
        if (!(velocity_x_f4 < 0.0f)
          || (v118 = velocity_x_f4 + 0.5,
              velocity_x_f4 = v118,
              !(v118 > 0.0f))) {
          advance_frame_and_dispatch();
          return;
        }
        zero_velocity_acceleration();
        byte_47e = 0;
        advance_frame_and_dispatch();
        return;
      case 701:
      case 702:
      case 703:
        if (!sequence_13e) {
          resolve_stage_surface_landing_transition();
        if (sequence_13e == 1 && velocity_y_f8 < 4.0)
          slot_14();
        advance_frame_and_dispatch();
        if (!frame_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_13e == 1) {
          velocity_x_f4 = policy_x_780;
          velocity_y_f8 = policy_y_784;
          acceleration_y_100 = policy_scale_788;
        }
        return;
        }
        velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
        if ((unsigned __int8)has_crossed_stage_surface_while_descending()) {
          set_action(700);
          y_f0 = stage_surface_height_at_x(this);
          zero_velocity_acceleration();
          return;
        }
        if (sequence_13e == 1 && velocity_y_f8 < 4.0)
          slot_14();
        advance_frame_and_dispatch();
        if (!frame_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_13e == 1) {
          velocity_x_f4 = policy_x_780;
          velocity_y_f8 = policy_y_784;
          acceleration_y_100 = policy_scale_788;
        }
        return;
      case 704:
        velocity_y_f8 = velocity_y_f8 - acceleration_y_100;
        v50 = has_crossed_stage_surface_while_descending();
        if ( v50 )
        {
          set_action(709);
          zero_velocity_acceleration();
          y_f0 = stage_surface_height_at_x(this);
        }
        else
        {
          advance_frame_and_dispatch();
        }
        break;
      case 705:
        resolve_stage_surface_landing_transition();
        velocity_x_f4 = motion_x_778;
        advance_frame_and_dispatch();
        break;
      case 706:
        resolve_stage_surface_landing_transition();
        velocity_x_f4 = motion_y_77c;
        advance_frame_and_dispatch();
        break;
      case 709:
        resolve_stage_surface_landing_transition();
        if ((unsigned __int8)advance_frame_and_dispatch())
          set_action(700);
        return;
      case 789:
        zero_velocity_acceleration();
        advance_frame_and_dispatch();
        if ( !frame_index_140 && !frame_timer_142 && flag_776 )
        {
          set_action(0);
          flag_776 = 0;
        }
        break;
      case 790:
        if ( sequence_13e == 1 )
        {
          if ( y_f0 > 1580.0 )
          {
            velocity_y_f8 = 0.0;
            y_f0 = 1580.0;
          }
          if ( word_730 == 1 )
          {facing_104 = 1;
            slot_14();
          }
        }
        if ( sequence_13e == 2
          && (velocity_y_f8 = velocity_y_f8 - acceleration_y_100, (unsigned __int8)has_crossed_stage_surface_while_descending()) )
        {
          dispatch_indexed_event_member(0x1Eu);
          set_sequence(3);
          y_f0 = stage_surface_height_at_x(this);
          zero_velocity_acceleration();
        }
        else
        {
          if ((unsigned __int8)advance_frame_and_dispatch()) {
            set_action(0);
            return;
          }
          if ( !frame_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_13e == 1 )
          {
            v52 = facing_104;
            velocity_y_f8 = 25.0;
            v53 = y_f0;
            word_738 = 0;
            v65 = v53;
            emit_fighter_effect_433cc0(63, x_ec, v65, v52, 1);
          }
        }
        break;
      case 796:
        if (sequence_13e > 0
          && sequence_13e < 4
          && (velocity_y_f8 = velocity_y_f8 - acceleration_y_100, (unsigned __int8)has_crossed_stage_surface_while_descending()))
        {
          dispatch_indexed_event_member(0x1Eu);
          x_ec = 800.0;facing_104 = -1;
          set_sequence(4);
          y_f0 = stage_surface_height_at_x(this);
          zero_velocity_acceleration();
        }
        else if ( (unsigned __int8)advance_frame_and_dispatch() )
        {
          set_action(700);
        }
        else if ( !frame_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_13e == 1 )
        {
          v57 = facing_104;
          v58 = 800.0 - x_ec;
          byte_47e = 0;
          v119 = v58;
          float_73c = v119;
          velocity_x_f4 = v119 / 90.0 * (double)v57;
          velocity_y_f8 = 11.5;
          acceleration_y_100 = 0.25555557;
        }
        break;
      case 799:
        if (sequence_13e > 0
          && sequence_13e < 4
          && (velocity_y_f8 = velocity_y_f8 - acceleration_y_100, (unsigned __int8)has_crossed_stage_surface_while_descending()))
        {
          dispatch_indexed_event_member(0x1Eu);
          x_ec = 480.0;facing_104 = 1;
          set_sequence(4);
          y_f0 = stage_surface_height_at_x(this);
          zero_velocity_acceleration();
        }
        else if ( (unsigned __int8)advance_frame_and_dispatch() )
        {
          set_action(789);
        }
        else if ( !frame_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_13e == 1 )
        {
          v62 = facing_104;
          v63 = 480.0 - x_ec;
          byte_47e = 0;
          v120 = v63;
          float_73c = v120;
          velocity_x_f4 = v120 / 90.0 * (double)v62;
          velocity_y_f8 = 11.5;
          acceleration_y_100 = 0.25555557;
        }
        break;
      default:
        return;
    }
    }}

} // namespace th105
