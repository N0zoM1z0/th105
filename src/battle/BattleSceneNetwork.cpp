#include "BattleScenes.hpp"

#include "GameMode.hpp"
#include "engine/CriticalSectionWrapper.hpp"
#include "input/Input.hpp"
#include "input/InputSelection.hpp"
#include "ui/SceneTransitionState.hpp"

namespace th105 {

extern "C" __declspec(dllimport) void *__stdcall CreateEventA(void *, int, int, const char *);
extern "C" __declspec(dllimport) unsigned __stdcall WaitForSingleObject(void *, unsigned);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(void *);
extern "C" bool __cdecl is_menu_initial_press(unsigned char, bool, bool, bool);
extern "C" void __cdecl clear_menu_objects();

struct SceneEventWait {
    void *handle;
    unsigned wait_ms;
    SceneEventWait() : handle(CreateEventA(0, 0, 0, 0)), wait_ms(0x10) {}
    ~SceneEventWait() { CloseHandle(handle); }
    void wait() { WaitForSingleObject(handle, wait_ms); }
};

struct BattleSceneRendererView {
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual int scene_phase();
    int state_88() const {
        return *reinterpret_cast<const int *>(reinterpret_cast<const unsigned char *>(this) + 0x88);
    }
};
extern BattleSceneRendererView *g_scene_renderer;

struct BattleScenePeerView {
    virtual void slot0();
    virtual void advance();
};

struct BattleNetworkSessionView {
    virtual void slot0(); virtual void slot1(); virtual void slot2();
    virtual bool accept_match_setup(MatchSetup *setup);
    virtual void slot4(); virtual void slot5(); virtual void slot6();
    virtual void advance_session();
    virtual void slot8();
    virtual bool continue_transition();
    virtual bool reached_state(int state);
    virtual void slot11();
    virtual int transition_mode();
    virtual void slot13(); virtual void slot14();
    virtual bool disconnected();
    void pump_watch_44d880();
    void prepare_watch_transition_44e2c0();
};

struct PlayerSlotRecordView {
    void *battle_peer_138() const {
        return *reinterpret_cast<void * const *>(reinterpret_cast<const unsigned char *>(this) + 0x138);
    }
};

static unsigned read_watch_ready_state() {
    unsigned char *input = reinterpret_cast<unsigned char *>(get_player2_input());
    CriticalSectionWrapper *lock = reinterpret_cast<CriticalSectionWrapper *>(input + 0x124);
    lock->enter();
    unsigned char *state = *reinterpret_cast<unsigned char **>(input + 0x104);
    unsigned value = *reinterpret_cast<unsigned *>(state + 0x4c);
    lock->leave();
    return value;
}

int CBattle::update()
{
    switch (g_scene_renderer->scene_phase()) {
    case 1:
        if (get_session_setup_option() == 2)
            return 2;
        return get_game_mode() != 0 ? 3 : 16;
    case 2:
        return 2;
    case 3:
        return 20;
    default:
        return 5;
    }
}

void CBattle::on_scene_exit(int)
{
    clear_menu_objects();
    start_scene_fade_out(0, 0);
}

void CBattleSV::on_scene_enter(int)
{
    BattleNetworkSessionView *session =
        reinterpret_cast<BattleNetworkSessionView *>(get_network_session());
    SceneEventWait event;
    while (!session->reached_state(5)) {
        if (session->disconnected())
            break;
        event.wait();
    }
    battle_peer_08() =
        reinterpret_cast<PlayerSlotRecordView *>(get_player_slot_record(0))
            ->battle_peer_138();
}

void CBattleCL::on_scene_enter(int)
{
    BattleNetworkSessionView *session =
        reinterpret_cast<BattleNetworkSessionView *>(get_network_session());
    SceneEventWait event;
    while (!session->reached_state(5)) {
        if (session->disconnected())
            break;
        event.wait();
    }
    battle_peer_08() =
        reinterpret_cast<PlayerSlotRecordView *>(get_player_slot_record(0))
            ->battle_peer_138();
}

void CBattleWatch::on_scene_enter(int)
{
    BattleNetworkSessionView *session =
        reinterpret_cast<BattleNetworkSessionView *>(get_network_session());
    SceneEventWait event;
    unsigned state = read_watch_ready_state();
    if (state < 5) {
        do {
            session->pump_watch_44d880();
            if (session->disconnected())
                break;
            event.wait();
            state = read_watch_ready_state();
        } while (state < 5);
    }
}

int CBattleWatch::update()
{
    BattleNetworkSessionView *session =
        reinterpret_cast<BattleNetworkSessionView *>(get_network_session());
    if (session->disconnected() ||
        is_menu_initial_press(1, false, false, false) ||
        *reinterpret_cast<int *>(get_combined_menu_input_counters() + 0x0c) == 1)
        return 2;

    session->pump_watch_44d880();
    if (session->transition_mode() != 3) {
        while (session->continue_transition()) {
            int phase = g_scene_renderer->scene_phase();
            if (phase > 0 && phase <= 2)
                return 12;
            if (g_scene_renderer->state_88() == 5) {
                session->prepare_watch_transition_44e2c0();
                return 12;
            }
        }
        return 15;
    }
    session->prepare_watch_transition_44e2c0();
    return 12;
}

} // namespace th105
