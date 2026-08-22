#include "BattleScenes.hpp"

#include "GameMode.hpp"
#include "input/Input.hpp"
#include "input/InputSelection.hpp"
#include "ui/SceneTransitionState.hpp"

namespace th105 {

extern "C" bool __cdecl is_menu_initial_press(
    unsigned char, bool, bool, bool);
unsigned char __cdecl start_async_engine_scene_load(int scene);

struct LoadingPlayer2InputView {
    void configure_session_input_slots(signed char slot_count, signed char game_mode);
    void configure_watch_player_42bc40(signed char slot, MatchSetup *setup);
};

struct LoadingNetworkSessionView {
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual bool accept_match_setup(MatchSetup *setup);
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual bool disconnected();

    void pump_watch_44d880();
};

int CLoadingWatch::update()
{
    LoadingNetworkSessionView *session =
        reinterpret_cast<LoadingNetworkSessionView *>(get_network_session());
    ++timer_9c();
    session->pump_watch_44d880();

    int state = state_a0();
    if (state == 0) {
        if (session->disconnected() ||
            is_menu_initial_press(1, false, false, false) ||
            *reinterpret_cast<int *>(get_combined_menu_input_counters() + 0x0c) == 1)
            return 2;

        if (session->accept_match_setup(get_match_setup())) {
            reinterpret_cast<LoadingPlayer2InputView *>(get_player2_input())
                ->configure_session_input_slots(
                    1, static_cast<signed char>(get_game_mode()));
            reinterpret_cast<LoadingPlayer2InputView *>(get_player2_input())
                ->configure_watch_player_42bc40(0, get_match_setup());
            start_async_engine_scene_load(3);
            state_a0() = 1;
        }
        return 12;
    }

    if (state == 1) {
        if (get_async_scene_load_request() == 3)
            return 12;
    }
    return 15;
}

} // namespace th105
