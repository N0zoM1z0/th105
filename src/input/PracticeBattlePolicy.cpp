#include "battle/Collision.hpp"
#include "battle/GameMode.hpp"
#include "battle/PairEmbeddedMode.hpp"
#include "input/InputSelection.hpp"

namespace th105 {
bool __fastcall is_state_13c_below_32(void *);
struct PracticeSceneView {
    unsigned char unknown_00[0x0c];
    Fighter *fighters_0c[2];
};
struct PracticeBattlePolicyView {
    int unknown_00,restore_04,mode_lock_08,guard_0c;
    int mode_10,spirit_14,input_18,unknown_1c,guard_policy_20;
    void update_428260();
};
struct PracticePlayerSlotView {
    void select_deck(unsigned char source);
};
extern PracticeSceneView *g_scene_renderer;
extern PracticeBattlePolicyView *g_battle_input_gate;
extern short g_info_mode_value_6fa88c;
extern int g_fighter_state_4b8_default;

void PracticeBattlePolicyView::update_428260()
{
    Fighter *first=g_scene_renderer->fighters_0c[0];
    Fighter *second=g_scene_renderer->fighters_0c[1];
    Fighter *fighters[2] = {first,second};
    if (get_game_mode()==GAME_MODE_PRACTICE) {
        switch(guard_policy_20) {
        case 0: case 2: case 3: guard_0c=1; break;
        case 1: guard_0c=0; break;
        case 4:
            if(static_cast<unsigned char>(is_state_13c_in_96_c7(second)))
                guard_0c=0;
            else if(is_state_13c_in_32_95(second))
                guard_0c=1;
            else if(is_state_13c_below_32(first) && is_state_13c_below_32(second))
                guard_0c=0;
            break;
        }
        if(is_state_13c_below_32(first)) {
            first->value_174=first->maximum_176;
            first->unknown_484=1000;
            first->counter_482=1000;
            first->floor_486=0;
            *reinterpret_cast<short *>(first->unknown_488)=0;
        }
        if(is_state_13c_below_32(second)) {
            second->value_174=second->maximum_176;
            int spirit=g_battle_input_gate->spirit_14*1000/5;
            if(second->counter_482<spirit)spirit=second->counter_482;
            second->counter_482=static_cast<short>(spirit);
            second->unknown_484=1000;
            *reinterpret_cast<short *>(second->unknown_488)=0;
        }
        int mode;
        if(mode_10!=0) {
            mode=mode_10-1;
            g_info_mode_value_6fa88c=999;
        } else {
            mode=16;
            g_info_mode_value_6fa88c=0;
        }
        if(mode!=g_fighter_state_4b8_default)
            reinterpret_cast<PairEmbeddedModeView *>(this)->select_pair_mode_434780(mode,1);
        if(input_18==3) {
            if(second->field_6b0==0) {
                rebind_selected_input_43b640(1,1);
                if(get_selected_input(1)) {
                    reinterpret_cast<PracticePlayerSlotView *>(get_player_slot_record(1))
                        ->select_deck(static_cast<unsigned char>(get_selected_input_source(1)));
                    second->field_6b0=reinterpret_cast<unsigned char *>(get_player_slot_record(1))+0x138;
                }
            }
        } else second->field_6b0=0;
        return;
    }
    if(mode_lock_08!=0)g_info_mode_value_6fa88c=999;
    if(restore_04==1) {
        for(int i=0;i<2;++i) {
            Fighter *fighter=fighters[i];
            if(!is_state_13c_in_32_95(fighter))
                fighter->value_174=fighter->maximum_176;
            if(is_state_13c_below_32(fighter)) {
                fighter->unknown_484=1000;
                fighter->counter_482=1000;
                fighter->floor_486=0;
                *reinterpret_cast<short *>(fighter->unknown_488)=0;
            }
        }
    }
}
}
