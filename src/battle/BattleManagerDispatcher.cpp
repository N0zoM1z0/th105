#include "BattleManagerVirtuals.hpp"
#include "BattleController.hpp"
#include "GameMode.hpp"
#include "ui/UiSelectionState.hpp"

#include <new>

namespace th105 {

struct CNetworkBase;
CNetworkBase *get_network_session();

struct CMenuBattleDispatchView {
    unsigned char storage_00[0x78];
    explicit CMenuBattleDispatchView(CBattleManager *owner);
};

struct CMenuPracticeDispatchView {
    unsigned char storage_00[0x288];
    explicit CMenuPracticeDispatchView(CBattleManager *owner);
};

void __cdecl install_menu_object(void *object);
void __cdecl dispatch_indexed_event(unsigned event_id);
int CBattleManager::dispatch_battle_state_frame_472b20()
{
    if (has_ui_selection_state_changed())
        return *reinterpret_cast<int *>(
            reinterpret_cast<unsigned char *>(this) + 0x84);

    if (get_network_session() != 0) {
        if (is_menu_initial_press(1, false, false, false)) {
            dispatch_indexed_event(0x29);
            return 1;
        }
    } else if (is_menu_initial_press(1, false, false, false)) {
        dispatch_indexed_event(0x29);
        if (get_session_setup_option() == 2)
            return 2;

        void *menu;
        if (get_game_mode() == GAME_MODE_PRACTICE)
            menu = new CMenuPracticeDispatchView(this);
        else
            menu = new CMenuBattleDispatchView(this);
        install_menu_object(menu);
        return 0;
    }

    if (get_session_setup_option() == 2) {
        BattleInputGate *input = get_player2_input();
        if (input->poll_synchronized_input_4708b0())
            return 2;
        if (is_menu_initial_press(1, false, false, false))
            return 2;
    }

    ++frame_counter_04;
    switch (phase_88) {
    case 0: return run_pipeline_and_transition_472d80();
    case 1: return run_reset_pipeline_472dc0();
    case 2: return run_full_pipeline_471630();
    case 3: return run_120_frame_pipeline_472e10();
    case 4: return run_180_frame_pipeline_472ea0();
    case 5: return run_info_phase_pipeline_472f10();
    case 6: return constant_one_471920();
    default: return 0;
    }
}

} // namespace th105
