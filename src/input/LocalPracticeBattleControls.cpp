#include "battle/BattleController.hpp"
#include "battle/Collision.hpp"
#include "battle/GameMode.hpp"
#include "battle/PairEmbeddedMode.hpp"

namespace th105 {
struct CNetworkBase;
CNetworkBase *get_network_session();
struct LocalPracticeSettingsView {
    int unknown_00,restore_04,mode_lock_08;
};
struct LocalPracticeSceneView {
    unsigned char unknown_00[0x0c];
    Fighter *first_0c,*second_10;
};
extern LocalPracticeSceneView *g_scene_renderer;
extern short g_info_mode_value_6fa88c;
extern int g_fighter_state_4b8_default;

void BattleInputGate::update_local_practice_battle_controls_427190()
{
    if(get_network_session())return;
    LocalPracticeSettingsView *settings=reinterpret_cast<LocalPracticeSettingsView *>(this);
    if(get_game_mode()==GAME_MODE_VS_PLAYER || get_game_mode()==GAME_MODE_NETWORK_SERVER) {
        if(is_menu_initial_press(65,0,0,0)) {
            settings->mode_lock_08=0;
            g_info_mode_value_6fa88c=0;
            reinterpret_cast<PairEmbeddedModeView *>(this)->select_pair_mode_434780(16,1);
        }
        if(is_menu_initial_press(64,0,0,0)) {
            settings->mode_lock_08=1;
            reinterpret_cast<PairEmbeddedModeView *>(this)->select_pair_mode_434780((g_fighter_state_4b8_default+13)%14,1);
        }
        if(is_menu_initial_press(63,0,0,0)) {
            settings->mode_lock_08=1;
            reinterpret_cast<PairEmbeddedModeView *>(this)->select_pair_mode_434780((g_fighter_state_4b8_default+1)%14,1);
        }
        if(is_menu_initial_press(59,0,0,0))
            settings->restore_04=(settings->restore_04+1)%2;
    }
    if(get_game_mode()==GAME_MODE_VS_PLAYER ||
       get_game_mode()==GAME_MODE_NETWORK_SERVER ||
       get_game_mode()==GAME_MODE_PRACTICE) {
        if(is_state_13c_in_32_95(g_scene_renderer->first_0c) ||
           is_state_13c_in_32_95(g_scene_renderer->second_10))
            return;
        if(is_menu_initial_press(61,0,0,0)) {
            int count=5;
            do {
                g_scene_renderer->first_0c->advance_fighter_sequence_55c();
                g_scene_renderer->second_10->advance_fighter_sequence_55c();
            }while(--count!=0);
            reinterpret_cast<SpellDataOwner *>(g_scene_renderer->first_0c->spell_lookup_4f0)->set_sequence_mode(1);
            reinterpret_cast<SpellDataOwner *>(g_scene_renderer->second_10->spell_lookup_4f0)->set_sequence_mode(1);
        }
        if(is_menu_initial_press(60,0,0,0)) {
            int count=5;
            do {
                g_scene_renderer->first_0c->prepare_next_spell_sequence_entry();
                g_scene_renderer->second_10->prepare_next_spell_sequence_entry();
            }while(--count!=0);
        }
    }
}
}
