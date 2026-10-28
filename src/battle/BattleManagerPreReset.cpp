#include "battle/BattleManagerVirtuals.hpp"
#include "battle/BattleController.hpp"
#include "battle/GameMode.hpp"
#include "ui/MenuPractice.hpp"
#include <new>

namespace th105 {
struct CNetworkBase;
CNetworkBase *get_network_session();
struct PreResetInputState {
    unsigned char unknown_00[0x58];
    int state_58;
};
struct PreResetInputLink {
    PreResetInputState *state_00;
};
extern BattleInputGate *g_battle_input_gate;

void CBattleManager::pre_reset_slot_40()
{
    if(get_session_setup_option()==2)
        get_player2_input()->publish_synchronized_control_bits_427ac0();
    fighter_0c->update_scripted_input_state_462e20();
    fighter_10->update_scripted_input_state_462e20();
    if(!get_network_session() && get_session_setup_option()!=2) {
        Fighter **fighter=&fighter_0c;
        int count=2;
        do {
            PreResetInputLink *link=reinterpret_cast<PreResetInputLink *>((*fighter)->field_6b0);
            if(link && link->state_00->state_58==1) {
                dispatch_indexed_event(0x29);
                void *menu;
                if(get_game_mode()==GAME_MODE_PRACTICE)
                    menu=new CMenuPractice(reinterpret_cast<PracticeOwnerView *>(this));
                else
                    menu=new SceneExitTransition(reinterpret_cast<BattleController *>(this));
                install_menu_object(menu);
            }
            ++fighter;
        }while(--count!=0);
    }
    g_battle_input_gate->update_local_practice_battle_controls_427190();
    if(get_session_setup_option()==1)
        get_player2_input()->collect_battle_control_bits_42a560();
}
}
