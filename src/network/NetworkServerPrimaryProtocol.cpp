#include "NetworkWinsockSendClient.hpp"
#include "../engine/CriticalSectionWrapper.hpp"
#include "NetworkInputPacket.hpp"

#include <stddef.h>

namespace th105 {

struct NetworkSendStateView {
    bool check(int index);
    void process(int index);
};

struct NetworkTerminateBase4 {
    NetworkTerminateBase4() : result_004(0) {}
    unsigned int result_004;
};

class NetworkTerminatePacket8 : public NetworkTerminateBase4 {
public:
    NetworkTerminatePacket8() {}
    virtual unsigned int serialize(void *buffer);
};

class NetworkGenericPacket8 {
public:
    virtual unsigned int serialize(void *buffer);
    unsigned int result_004;
};

struct CNetworkServerPrimaryProtocolView {
    bool flush_send_state();
    void send_packet(
        unsigned int channel,
        NetworkGenericPacket8 *packet,
        int option);
    unsigned char send_state_or_terminate();

    unsigned char reserved_000[0x48];
    CriticalSectionWrapper critical_048;
    unsigned char reserved_064[0x2c];
    InputPacket24 input_packet_090;
    unsigned char reserved_0b4[0x300];
    NetworkWinsockSendClientView send_3b4;
    unsigned char buffer_5b4[0x134];
    unsigned int last_sequence_6e8;
};

bool CNetworkServerPrimaryProtocolView::flush_send_state()
{
    if (reinterpret_cast<NetworkSendStateView *>(&send_3b4)->check(0)) {
        reinterpret_cast<NetworkSendStateView *>(&send_3b4)->process(0);
        return true;
    }
    return false;
}

void CNetworkServerPrimaryProtocolView::send_packet(
    unsigned int channel,
    NetworkGenericPacket8 *packet,
    int option)
{
    send_3b4.send_server(
        channel,
        buffer_5b4,
        packet->serialize(buffer_5b4),
        option,
        &packet->result_004);
}

unsigned char CNetworkServerPrimaryProtocolView::send_state_or_terminate()
{
    CriticalSectionWrapper *critical = &critical_048;
    critical->enter();
    unsigned char *buffer = buffer_5b4;
    if (input_packet_090.sequence_008 != last_sequence_6e8) {
        NetworkPacketBase8 *packet = &input_packet_090;
        send_3b4.send_server(
            0,
            buffer,
            packet->serialize(buffer),
            0x50,
            &packet->result_004);
        critical->leave();
        return 0;
    }

    NetworkTerminatePacket8 packet;
    NetworkTerminatePacket8 *request = &packet;
    send_3b4.send_server(
        0,
        buffer,
        request->serialize(buffer),
        0x50,
        &request->result_004);
    const unsigned char pending =
        reinterpret_cast<unsigned char *>(this)[0x3a7];
    critical->leave();
    return pending;
}

typedef char NetworkTerminatePacket8_size[
    sizeof(NetworkTerminatePacket8) == 0x08 ? 1 : -1];
typedef char ServerCriticalOff[
    offsetof(CNetworkServerPrimaryProtocolView, critical_048) == 0x48 ? 1 : -1];
typedef char ServerPacketOff[
    offsetof(CNetworkServerPrimaryProtocolView, input_packet_090) == 0x90 ? 1 : -1];
typedef char ServerSendOff[
    offsetof(CNetworkServerPrimaryProtocolView, send_3b4) == 0x3b4 ? 1 : -1];
typedef char ServerBufferOff[
    offsetof(CNetworkServerPrimaryProtocolView, buffer_5b4) == 0x5b4 ? 1 : -1];
typedef char ServerLastOff[
    offsetof(CNetworkServerPrimaryProtocolView, last_sequence_6e8) == 0x6e8 ? 1 : -1];

} // namespace th105
