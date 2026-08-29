#include "../battle/SpellData.hpp"
#include "../engine/CriticalSectionWrapper.hpp"

#include <stddef.h>

namespace th105 {

struct NetworkDelayBase8 {
    NetworkDelayBase8() : value_004(0) {}
    unsigned int value_004;
    unsigned char delay_008;
    unsigned char reserved_009[3];
};

class NetworkDelayPacket12 : public NetworkDelayBase8 {
public:
    NetworkDelayPacket12() {}
    virtual unsigned int serialize(void *buffer);
};

struct NetworkClientDelaySend4View {
    int send_client(
        const void *buffer,
        unsigned int size,
        int option,
        void *completion);
};

struct NetworkClientSend4View {
    int send_client(
        const void *buffer,
        unsigned int size,
        int option,
        unsigned int *result);
};

struct NetworkSendStateView {
    int status();
};

class NetworkClientPacket8View {
public:
    virtual unsigned int serialize(void *buffer);
    unsigned int result_004;
};

struct CNetworkClientPrimaryProtocolView {
    unsigned char send_state_ready();
    bool send_if_needed();
    int send_delay(unsigned char value);
    void advance_delay_queue();

    unsigned char reserved_000[0x48];
    CriticalSectionWrapper critical_048;
    unsigned char reserved_064[0x08];
    unsigned char state_06c;
    unsigned char reserved_06d[3];
    unsigned char reserved_070[0x08];
    unsigned char peer_state_078;
    unsigned char reserved_079[0x07];
    unsigned char reserved_080;
    unsigned char delay_081;
    unsigned char reserved_082[0x0e];
    NetworkClientPacket8View packet_090;
    unsigned char reserved_098[0x30f];
    unsigned char pending_3a7;
    unsigned char reserved_3a8[0x0c];
    NetworkClientSend4View send_3b4;
    unsigned char reserved_3b5[0x1ff];
    unsigned char buffer_5b4[0x50];
};

struct CNetworkClientDelayQueueView {
    void advance_delay_queue();
    unsigned char reserved_000[0x60];
    short current_060;
    unsigned char reserved_062[0x06];
    ShortDeque8 queue_068;
};

unsigned char CNetworkClientPrimaryProtocolView::send_state_ready()
{
    int state = reinterpret_cast<NetworkSendStateView *>(&send_3b4)->status();
    if (state == 0)
        return false;
    if (state == 2)
        return false;
    return state != 3;
}

bool CNetworkClientPrimaryProtocolView::send_if_needed()
{
    CriticalSectionWrapper *critical = &critical_048;
    critical->enter();
    const unsigned char pending = pending_3a7;
    critical->leave();
    if (pending)
        return true;

    critical->enter();
    NetworkClientPacket8View *packet = &packet_090;
    unsigned char *buffer = buffer_5b4;
    send_3b4.send_client(
        buffer, packet->serialize(buffer), 0x50, &packet->result_004);
    critical->leave();
    return false;
}

int CNetworkClientPrimaryProtocolView::send_delay(unsigned char value)
{
    delay_081 = value;
    NetworkDelayPacket12 packet;
    NetworkDelayPacket12 *request = &packet;
    request->delay_008 = value;
    return reinterpret_cast<NetworkClientDelaySend4View *>(&send_3b4)->send_client(
        buffer_5b4, request->serialize(buffer_5b4), 0, 0);
}

void CNetworkClientDelayQueueView::advance_delay_queue()
{
    if (queue_068.live_count_10 != 0) {
        ShortDeque8 *queue = &queue_068;
        current_060 = *queue->front_checked();
        if (queue->live_count_10 != 0) {
            ++queue->head_0c;
            if (queue->block_capacity_08 * 8 <= queue->head_0c)
                queue->head_0c = 0;
            --queue->live_count_10;
            if (queue->live_count_10 == 0)
                queue->head_0c = 0;
        }
    }
}

typedef char NetworkDelayPacket12_size[sizeof(NetworkDelayPacket12) == 0x0c ? 1 : -1];
typedef char ClientCriticalOff[
    offsetof(CNetworkClientPrimaryProtocolView, critical_048) == 0x48 ? 1 : -1];
typedef char ClientDelayOff[
    offsetof(CNetworkClientPrimaryProtocolView, delay_081) == 0x81 ? 1 : -1];
typedef char ClientSendOff[
    offsetof(CNetworkClientPrimaryProtocolView, send_3b4) == 0x3b4 ? 1 : -1];
typedef char ClientBufferOff[
    offsetof(CNetworkClientPrimaryProtocolView, buffer_5b4) == 0x5b4 ? 1 : -1];
typedef char ClientDelayQueueOff[
    offsetof(CNetworkClientDelayQueueView, queue_068) == 0x68 ? 1 : -1];

} // namespace th105
