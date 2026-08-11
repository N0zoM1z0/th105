#include "BattleController.hpp"

#include "Collision.hpp"

#include <new>

namespace th105 {

struct CNetworkBase;
CNetworkBase *__cdecl get_network_session();

struct FighterRoundTransitionState {
    unsigned char unknown_00[0x58];
    int state_58;
};

struct FighterRoundTransitionLink {
    FighterRoundTransitionState *state_00;
};

extern BattleInputGate *g_battle_input_gate;

void BattleController::initialize_round_state_4701c0()
{
    if (get_session_setup_option() == 2) {
        get_player2_input()->publish_synchronized_control_bits_427ac0();
    }

    fighter_0c->update_scripted_input_state_462e20();
    fighter_10->update_scripted_input_state_462e20();

    if (!get_network_session() && get_session_setup_option() != 2) {
        Fighter **fighter = &fighter_0c;
        int count = 2;
        do {
            FighterRoundTransitionLink *link =
                reinterpret_cast<FighterRoundTransitionLink *>(
                    (*fighter)->field_6b0);
            if (link && link->state_00->state_58 == 1) {
                dispatch_indexed_event(0x29);
                SceneExitTransition *transition =
                    new SceneExitTransition(this);
                install_menu_object(transition);
            }
            ++fighter;
        } while (--count != 0);
    }

    g_battle_input_gate->update_local_practice_battle_controls_427190();

    if (get_session_setup_option() == 1) {
        get_player2_input()->collect_battle_control_bits_42a560();
    }

    if (phase_88 == 2 || phase_88 == 3) {
        return;
    }
    if (phase_88 != 1) {
        reset_fighter_fields_6bc_728(
            reinterpret_cast<CollisionContext *>(this));
        return;
    }
    reset_fighter_fields_6b4_728(reinterpret_cast<CollisionContext *>(this));
}

} // namespace th105
