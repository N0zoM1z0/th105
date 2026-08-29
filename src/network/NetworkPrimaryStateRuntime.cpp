#include "../engine/CriticalSectionWrapper.hpp"

#include <deque>

namespace th105 {

struct NetworkPeerByte5 {
    unsigned char reserved_000[4];
    unsigned char byte_004;
};

class NetworkPrimaryPacket8 {
public:
    virtual unsigned int serialize(void *buffer);
    unsigned int result_004;
};

struct NetworkClientSend4View {
    int send_client(
        const void *buffer,
        unsigned int size,
        int option,
        unsigned int *result);
};

struct NetworkServerSend5View {
    int send_server(
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
    NetworkPrimaryPacket8 packet_064;
    unsigned char state_06c;
    unsigned char reserved_06d[3];
    NetworkPrimaryPacket8 packet_070;
    unsigned char state_078;
    unsigned char reserved_079[3];
    unsigned short current_07c;
    unsigned short previous_07e;
    signed char adaptive_080;
    signed char delay_081;
    unsigned char phase_082;
    unsigned char cooldown_083;
    unsigned int ahead_084;
    unsigned int behind_088;
    unsigned int combined_08c;
    NetworkPrimaryPacket8 packet_090;
    unsigned char state_098[4];
    unsigned char state_09c;
    unsigned char reserved_09d[3];
    std::deque<short> queue_0a0;
    unsigned char reserved_0b4[0x28];
    CriticalSectionWrapper critical_0dc;
    unsigned char reserved_0f8[0x78];
    unsigned int available_170;
    unsigned char reserved_174[0x8c];
    NetworkPeerByte5 *peer_200;
    unsigned char reserved_204[4];
    unsigned char *input_208;
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
    const bool same = state_06c == value;
    state_078 = value;
    if (!same) {
        NetworkPrimaryPacket8 *packet = &packet_070;
        unsigned char *buffer = buffer_5b4;
        send_3b4.send_client(
            buffer,
            packet->serialize(buffer),
            0x50,
            &packet->result_004);
        lock->leave();
        return 0;
    }

    if (state_09c != value) {
        reset_state();
        state_09c = state_078;
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
    if (queue_0a0.size() != 0) {
        unsigned short value = *reinterpret_cast<unsigned short *>(input_208 + 0x62);
        queue_0a0.at(0) = static_cast<short>(value & 0x3ff);
    } else {
        unsigned short value = *reinterpret_cast<unsigned short *>(input_208 + 0x62);
        queue_0a0.push_back(static_cast<short>(value & 0x3ff));
    }

    NetworkPrimaryPacket8 *packet = &packet_090;
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
    NetworkPrimaryPacket8 packet_064;
    unsigned char state_06c;
    unsigned char reserved_06d[3];
    NetworkPrimaryPacket8 packet_070;
    unsigned char state_078;
    unsigned char reserved_079[3];
    unsigned short current_07c;
    unsigned short previous_07e;
    signed char adaptive_080;
    signed char delay_081;
    unsigned char phase_082;
    unsigned char cooldown_083;
    unsigned int ahead_084;
    unsigned int behind_088;
    unsigned int combined_08c;
    NetworkPrimaryPacket8 packet_090;
    unsigned char state_098[4];
    unsigned char state_09c;
    unsigned char reserved_09d[0x33];
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
    const bool same = value == state_078;
    state_06c = value;
    if (!same) {
        NetworkPrimaryPacket8 *packet = &packet_064;
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

    if (state_09c != value) {
        reset_state();
        state_09c = state_06c;
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
