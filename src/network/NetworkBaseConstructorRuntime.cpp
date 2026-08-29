#include "../engine/CriticalSectionWrapper.hpp"
#include "../input/InputManager.hpp"
#include "../ui/UiPrimitives.hpp"

#include <deque>
#include <stddef.h>

namespace th105 {

struct PacketResultBase4 {
    PacketResultBase4() : result_004() {}
    unsigned int result_004;
};

class ScenePacket0C : public PacketResultBase4 {
public:
    ScenePacket0C() {}
    virtual unsigned int serialize(void *buffer);

    unsigned char payload_008[4];
};

class InputPacket24ConstructorView : public PacketResultBase4 {
public:
    InputPacket24ConstructorView() {}
    virtual unsigned int serialize(void *buffer);

    unsigned int sequence_008;
    unsigned char tag_00c;
    unsigned char reserved_00d[3];
    std::deque<short> values_010;
};

struct NetworkInputEndpoint7C {
    CInputManagerEx input_000;
    std::deque<short> queue_068;
};

struct NetworkQueueSlot20 {
    unsigned int sequence_000;
    unsigned char side_004;
    unsigned char reserved_005[3];
    std::deque<short> queue_008;
    void *input_01c;
};

class NetworkWinsockState314 {
public:
    NetworkWinsockState314();
    virtual ~NetworkWinsockState314();

private:
    unsigned char reserved_004[0x310];
};

struct ScoreDataView {
    unsigned int reserved_000;
    unsigned int value_004;
};

ScoreDataView *__cdecl get_score_data();

class CNetworkBaseConstructorView {
public:
    CNetworkBaseConstructorView();
    virtual ~CNetworkBaseConstructorView();

public:
    unsigned char reserved_004[0x44];
    CriticalSectionWrapper critical_048;
    ScenePacket0C scene_packets_064[2];
    unsigned char reserved_07c[0x14];
    InputPacket24ConstructorView input_packet_090;
    std::deque<short> queues_0b4[2];
    CriticalSectionWrapper critical_0dc;
    NetworkInputEndpoint7C endpoints_0f8[2];
    unsigned char input_records_1f0[0x24];
    NetworkQueueSlot20 queue_slots_214[2];
    unsigned char reserved_254[0x08];
    CriticalSectionWrapper critical_25c;
    void *sprite_handle_278;
    UiSprite94 sprites_27c[2];
    unsigned char state_3a4;
    unsigned char reserved_3a5[7];
    unsigned int state_3ac;
    unsigned int score_value_3b0;
    NetworkWinsockState314 winsock_3b4;
    std::deque<short> replay_values_6c8;
};

CNetworkBaseConstructorView::CNetworkBaseConstructorView()
    : sprite_handle_278(0)
{
    state_3a4 = 0;
    state_3ac = 0;
    queue_slots_214[0].input_01c = input_records_1f0;
    queue_slots_214[1].input_01c = input_records_1f0 + 8;
    queue_slots_214[0].side_004 = 0;
    queue_slots_214[1].side_004 = 1;
    score_value_3b0 = get_score_data()->value_004;
}

typedef char ScenePacket0C_size[sizeof(ScenePacket0C) == 0x0c ? 1 : -1];
typedef char InputPacket24ConstructorView_size[
    sizeof(InputPacket24ConstructorView) == 0x24 ? 1 : -1];
typedef char NetworkInputEndpoint7C_size[
    sizeof(NetworkInputEndpoint7C) == 0x7c ? 1 : -1];
typedef char NetworkQueueSlot20_size[
    sizeof(NetworkQueueSlot20) == 0x20 ? 1 : -1];
typedef char NetworkWinsockState314_size[
    sizeof(NetworkWinsockState314) == 0x314 ? 1 : -1];
typedef char CNetworkBaseConstructorView_size[
    sizeof(CNetworkBaseConstructorView) == 0x6dc ? 1 : -1];
typedef char CNetworkBaseConstructorView_endpoint_offset[
    offsetof(CNetworkBaseConstructorView, endpoints_0f8) == 0x0f8 ? 1 : -1];
typedef char CNetworkBaseConstructorView_slot_offset[
    offsetof(CNetworkBaseConstructorView, queue_slots_214) == 0x214 ? 1 : -1];
typedef char CNetworkBaseConstructorView_winsock_offset[
    offsetof(CNetworkBaseConstructorView, winsock_3b4) == 0x3b4 ? 1 : -1];

} // namespace th105
