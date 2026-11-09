#include "engine/CriticalSectionWrapper.hpp"
#include "battle/BattleController.hpp"
#include "network/NetworkBaseMembers.hpp"
#include "network/NetworkInputDelayQueue.hpp"
#include <stddef.h>
namespace th105 {
extern "C" unsigned int g_network_frame_tick;
class ClientPacingView {
public:
    virtual ~ClientPacingView();
    virtual void slot_04(); virtual void slot_08(); virtual void slot_0c();
    virtual void slot_10(); virtual void slot_14(); virtual void slot_18();
    virtual void slot_1c(); virtual void slot_20();
    virtual bool advance_frame();
    virtual void slot_28();
    virtual void set_state(unsigned char);
    unsigned char reserved_004[0x7d];
    signed char delay_081;
    signed char pacing_082;
    unsigned char wait_083;
    unsigned int ahead_count_084, behind_count_088, sampled_count_08c;
    unsigned char reserved_090[0x4c];
    CriticalSectionWrapper critical_0dc;
    NetworkInputEndpoint7C endpoints_0f8[2];
    unsigned char reserved_1f0[0x4c4];
    BattleInputGate *input_gate_6b4;
    unsigned char reserved_6b8[8];
    unsigned int limit_6c0, recovery_6c4;
    unsigned char reserved_6c8[0x10];
    unsigned int frame_6d8;
    unsigned char reserved_6dc[4];
    int mode_6e0;
};
typedef char ClientPacingSize[sizeof(ClientPacingView)==0x6e4?1:-1];
typedef char ClientPacingCrit[offsetof(ClientPacingView,critical_0dc)==0xdc?1:-1];
typedef char ClientPacingInputs[offsetof(ClientPacingView,endpoints_0f8)==0xf8?1:-1];
typedef char ClientPacingPeer[offsetof(ClientPacingView,input_gate_6b4)==0x6b4?1:-1];
typedef char ClientPacingMode[offsetof(ClientPacingView,mode_6e0)==0x6e0?1:-1];
bool ClientPacingView::advance_frame()
{
    if (wait_083) { --wait_083; return false; }
    if (mode_6e0 == 1) {
        critical_0dc.enter();
        unsigned int local_frame = frame_6d8;
        critical_0dc.leave();
        if (limit_6c0 > 0) {
            BattleInputGate *peer = input_gate_6b4;
            peer->lock_124.enter();
            unsigned int remote_count = peer->input_104->controls_3c.live_count_10;
            peer->lock_124.leave();
            if (local_frame - remote_count + 30 >= limit_6c0)
                set_state(3);
        }
        BattleInputGate *peer = input_gate_6b4;
        peer->lock_124.enter();
        unsigned int remote_count = peer->input_104->controls_3c.live_count_10;
        peer->lock_124.leave();
        if (remote_count > 2) {
            if (pacing_082) {
                if (remote_count > 64) { recovery_6c4 = 30; return true; }
                if (remote_count < 4) { ++wait_083; recovery_6c4 = 0; pacing_082 = 0; return false; }
                if (recovery_6c4) { --recovery_6c4; return true; }
            } else { pacing_082 = 1; return true; }
        } else if (!pacing_082) {
            wait_083 = 4; pacing_082 = 0; return false;
        }
        pacing_082 = 0;
        return false;
    }
    critical_0dc.enter();
    int queued = static_cast<int>(endpoints_0f8[0].queue_068.size());
    critical_0dc.leave();
    if (queued) {
        if (pacing_082) {
            if (queued >= delay_081 + 1) {
                ++ahead_count_084;
                if (pacing_082 > 1) { pacing_082 = 0; return false; }
            } else {
                pacing_082 = 0;
                if (queued < delay_081) { ++behind_count_088; ++wait_083; }
                return false;
            }
        }
        critical_0dc.enter();
        reinterpret_cast<NetworkInputDelayQueueView *>(&endpoints_0f8[0])->advance_delay_queue();
        reinterpret_cast<NetworkInputDelayQueueView *>(&endpoints_0f8[1])->advance_delay_queue();
        critical_0dc.leave();
        unsigned int tick = g_network_frame_tick;
        ++pacing_082;
        g_network_frame_tick = ++tick;
        if (tick == 60) {
            sampled_count_08c = behind_count_088 + ahead_count_084;
            behind_count_088 = 0; ahead_count_084 = 0; g_network_frame_tick = 0;
        }
        return true;
    }
    if (!pacing_082) { ++behind_count_088; wait_083 = delay_081; }
    pacing_082 = 0;
    return false;
}
}
