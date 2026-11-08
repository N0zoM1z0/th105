#include "../engine/CriticalSectionWrapper.hpp"
#include "../input/InputManager.hpp"
#include "NetworkInputPacket.hpp"
#include "NetworkBaseMembers.hpp"

#include <deque>

namespace th105 {

struct NetworkPeerByte5 {
    unsigned char reserved_000[4];
    unsigned char byte_004;
};

struct NetworkClientSend4View {
    int send_client(
        const void *buffer,
        unsigned int size,
        int option,
        unsigned int *result);
};

struct NetworkServerSend5View {
    // The caller discards the real sender result; the inactive path has none.
    void send_server(
        unsigned int channel,
        const void *buffer,
        unsigned int size,
        int option,
        unsigned int *result);
};

class NetworkPrimaryStateVirtualBase {
public:
    virtual ~NetworkPrimaryStateVirtualBase();
    virtual void reset_state();
    virtual void slot_02();
    virtual void slot_03();
    virtual void slot_04();
    virtual void slot_05();
    virtual void slot_06();
    virtual void slot_07();
};

class CNetworkClientPrimaryStateView : public NetworkPrimaryStateVirtualBase {
public:
    unsigned char sync_peer_state(unsigned char value);
    void publish_input_value();

    unsigned char reserved_004[0x44];
    CriticalSectionWrapper critical_048;
    ScenePacket0C packet_064;
    ScenePacket0C packet_070;
    unsigned short current_07c;
    unsigned short previous_07e;
    signed char adaptive_080;
    signed char delay_081;
    unsigned char phase_082;
    unsigned char cooldown_083;
    unsigned int ahead_084;
    unsigned int behind_088;
    unsigned int combined_08c;
    InputPacket24 input_packet_090;
    unsigned char reserved_0b4[0x28];
    CriticalSectionWrapper critical_0dc;
    unsigned char reserved_0f8[0x78];
    unsigned int available_170;
    unsigned char reserved_174[0x8c];
    NetworkPeerByte5 *peer_200;
    unsigned char reserved_204[4];
    CInputManagerEx *input_208;
    unsigned char reserved_20c[0x0e];
    unsigned char byte_21a;
    unsigned char reserved_21b[0x15];
    NetworkPeerByte5 *peer_230;
    unsigned char reserved_234[6];
    unsigned char byte_23a;
    unsigned char reserved_23b[0x15];
    NetworkPeerByte5 *peer_250;
    unsigned char reserved_254[8];
    CriticalSectionWrapper critical_25c;
    unsigned char reserved_278[0x12e];
    unsigned char pending_3a6;
    unsigned char reserved_3a7[0x0d];
    NetworkClientSend4View send_3b4;
    unsigned char reserved_3b5[0x1ff];
    unsigned char buffer_5b4[0x50];
};

unsigned char CNetworkClientPrimaryStateView::sync_peer_state(
    unsigned char value)
{
    CriticalSectionWrapper *lock = &critical_048;
    lock->enter();
    const bool same = packet_064.payload_008[0] == value;
    packet_070.payload_008[0] = value;
    if (!same) {
        ScenePacket0C *packet = &packet_070;
        unsigned char *buffer = buffer_5b4;
        send_3b4.send_client(
            buffer,
            packet->serialize(buffer),
            0x50,
            &packet->result_004);
        lock->leave();
        return 0;
    }

    if (input_packet_090.tag_00c != value) {
        reset_state();
        input_packet_090.tag_00c = packet_070.payload_008[0];
    }
    lock->leave();

    critical_0dc.enter();
    unsigned int available = available_170;
    critical_0dc.leave();
    if (!available) {
        slot_07();
        return 0;
    }
    return 1;
}

void CNetworkClientPrimaryStateView::publish_input_value()
{
    CriticalSectionWrapper *lock = &critical_048;
    lock->enter();
    if (input_packet_090.values_010.size() != 0) {
        unsigned short value = input_208->resolved_mask;
        input_packet_090.values_010.at(0) = static_cast<short>(value & 0x3ff);
    } else {
        unsigned short value = input_208->resolved_mask;
        input_packet_090.values_010.push_back(static_cast<short>(value & 0x3ff));
    }

    NetworkPacketBase8 *packet = &input_packet_090;
    unsigned char *buffer = buffer_5b4;
    send_3b4.send_client(
        buffer,
        packet->serialize(buffer),
        0x50,
        &packet->result_004);
    lock->leave();
}

class CNetworkServerPrimaryStateView : public NetworkPrimaryStateVirtualBase {
public:
    unsigned char sync_peer_state(unsigned char value);

    unsigned char reserved_004[0x44];
    CriticalSectionWrapper critical_048;
    ScenePacket0C packet_064;
    ScenePacket0C packet_070;
    unsigned short current_07c;
    unsigned short previous_07e;
    signed char adaptive_080;
    signed char delay_081;
    unsigned char phase_082;
    unsigned char cooldown_083;
    unsigned int ahead_084;
    unsigned int behind_088;
    unsigned int combined_08c;
    InputPacket24 input_packet_090;
    unsigned char reserved_0b4[0x1c];
    unsigned char reserved_0d0[0x0c];
    CriticalSectionWrapper critical_0dc;
    unsigned char reserved_0f8[0x78];
    unsigned int available_170;
    unsigned char reserved_174[0x240];
    NetworkServerSend5View send_3b4;
    unsigned char reserved_3b5[0x1ff];
    unsigned char buffer_5b4[0x50];
};

unsigned char CNetworkServerPrimaryStateView::sync_peer_state(
    unsigned char value)
{
    CriticalSectionWrapper *lock = &critical_048;
    lock->enter();
    const bool same = value == packet_070.payload_008[0];
    packet_064.payload_008[0] = value;
    if (!same) {
        ScenePacket0C *packet = &packet_064;
        unsigned char *buffer = buffer_5b4;
        send_3b4.send_server(
            0,
            buffer,
            packet->serialize(buffer),
            0x50,
            &packet->result_004);
        lock->leave();
        return 0;
    }

    if (input_packet_090.tag_00c != value) {
        reset_state();
        input_packet_090.tag_00c = packet_064.payload_008[0];
    }
    lock->leave();

    critical_0dc.enter();
    unsigned int available = available_170;
    critical_0dc.leave();
    if (available < static_cast<unsigned int>(adaptive_080)) {
        slot_07();
        return 0;
    }
    return 1;
}

} // namespace th105

typedef char NetworkResolvedInputMaskOffset[offsetof(th105::CInputManagerEx,resolved_mask)==0x62?1:-1];
typedef char NetworkClientInputPacketOffset[offsetof(th105::CNetworkClientPrimaryStateView,input_packet_090)==0x90?1:-1];
typedef char NetworkServerInputPacketOffset[offsetof(th105::CNetworkServerPrimaryStateView,input_packet_090)==0x90?1:-1];
typedef char NetworkClientPacketFollowingLockOffset[offsetof(th105::CNetworkClientPrimaryStateView,critical_0dc)==0xdc?1:-1];
typedef char NetworkServerPacketFollowingLockOffset[offsetof(th105::CNetworkServerPrimaryStateView,critical_0dc)==0xdc?1:-1];
typedef char NetworkClientScenePacketOffset[offsetof(th105::CNetworkClientPrimaryStateView,packet_064)==0x64?1:-1];
typedef char NetworkServerScenePacketOffset[offsetof(th105::CNetworkServerPrimaryStateView,packet_070)==0x70?1:-1];
