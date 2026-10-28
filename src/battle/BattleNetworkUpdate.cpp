#include "battle/BattleScenes.hpp"
#include "input/InputSelection.hpp"
#include "input/InputManager.hpp"
#include "ui/UiSelectionState.hpp"
#include "network/NetworkSession.hpp"

namespace th105 {
struct BattleNetworkUpdateSessionView {
    virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0c();
    virtual void slot10();virtual void slot14();virtual void slot18();
    virtual void advance();
    virtual void slot20();virtual bool continue_transition();
    virtual void slot28();virtual void slot2c();virtual int transition_mode();
    virtual void slot34();virtual void slot38();virtual bool disconnected();
    unsigned char unknown_004[0x6bc];
    void *sink_6c0;
    unsigned char unknown_6c4[0x14];
    void *pending_sink_6d8;
    void flush_replay_values_44d800();
};
struct BattleNetworkUpdatePeer {
    virtual void slot00();virtual void update();
};
struct BattleNetworkUpdateRenderer {
    virtual void slot00();virtual void slot04();virtual void slot08();
    virtual int scene_phase();
    unsigned char unknown_004[0x84];
    int phase_088;
};
extern BattleNetworkUpdateRenderer *g_scene_renderer;

int CBattleSV::update()
{
    BattleNetworkUpdateSessionView *session=reinterpret_cast<BattleNetworkUpdateSessionView *>(get_network_session());
    if(session->disconnected())return 2;
    if(!has_ui_selection_state_changed() && g_scene_renderer->phase_088!=5) {
        reinterpret_cast<BattleNetworkUpdatePeer *>(battle_peer_08())->update();
        session->advance();
        if(session->transition_mode()!=3) {
            while(session->continue_transition()) {
                switch(g_scene_renderer->scene_phase()) {
                case 1:
                    reinterpret_cast<NetworkSessionState *>(session)->copy_session_field_6c8_if_unset();
                    return 8;
                }
            }
            session->flush_replay_values_44d800();
            return 13;
        }
        if(!session->sink_6c0)session->sink_6c0=session->pending_sink_6d8;
        return 8;
    }
    if(!session->sink_6c0)session->sink_6c0=session->pending_sink_6d8;
    switch(g_scene_renderer->scene_phase()) {
    case 1:return 8;
    default:return 13;
    }
}

int CBattleCL::update()
{
    BattleNetworkUpdateSessionView *session=reinterpret_cast<BattleNetworkUpdateSessionView *>(get_network_session());
    if(session->disconnected())return 2;
    if(!has_ui_selection_state_changed() && g_scene_renderer->phase_088!=5) {
        reinterpret_cast<BattleNetworkUpdatePeer *>(battle_peer_08())->update();
        session->advance();
        if(session->transition_mode()!=3) {
            while(session->continue_transition()) {
                switch(g_scene_renderer->scene_phase()) {
                case 1:
                    reinterpret_cast<NetworkSessionState *>(session)->copy_session_field_6c8_if_unset();
                    return 9;
                }
            }
            session->flush_replay_values_44d800();
            return 14;
        }
        if(!session->sink_6c0)session->sink_6c0=session->pending_sink_6d8;
        return 9;
    }
    if(!session->sink_6c0)session->sink_6c0=session->pending_sink_6d8;
    switch(g_scene_renderer->scene_phase()) {
    case 1:
        reinterpret_cast<CInputManager *>(get_combined_menu_input())->reset_counters();
        return 8;
    default:return 14;
    }
}
}
