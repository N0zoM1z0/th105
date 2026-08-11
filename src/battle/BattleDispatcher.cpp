#include "BattleController.hpp"

#include <new>

namespace th105 {

int BattleController::dispatch_battle_state_frame_470940()
{
    if (has_ui_selection_state_changed()) {
        return result_84;
    }

    if (is_menu_initial_press(1, 0, 0, 0)) {
        if (get_session_setup_option() != 2) {
            dispatch_indexed_event(0x29);
            SceneExitTransition *transition = new SceneExitTransition(this);
            install_menu_object(transition);
            return 0;
        }
        return 2;
    }

    if (get_session_setup_option() == 2) {
        BattleInputGate *input = get_player2_input();
        if (!input->poll_synchronized_input_4708b0()) {
            do {
                if (phase_88 == 0) {
                    ++frame_counter_04;
                    run_phase_0_470940();
                } else if (phase_88 == 5) {
                    ++frame_counter_04;
                    run_phase_5_470940();
                } else {
                    goto dispatch_once;
                }
                input = get_player2_input();
            } while (!input->poll_synchronized_input_4708b0());
        }
        return 2;
    }

dispatch_once:
    int retries = 0;
    do {
        ++frame_counter_04;
        switch (phase_88) {
        case 0: return run_phase_0_470940();
        case 1: return run_phase_1_470940();
        case 2: return run_phase_2_470940();
        case 3: return run_phase_3_470940();
        case 4: return run_phase_4_470940();
        case 5: return run_phase_5_470940();
        case 6: return run_phase_6_470940();
        default: break;
        }
    } while (++retries < 1);
    return 0;
}

} // namespace th105
