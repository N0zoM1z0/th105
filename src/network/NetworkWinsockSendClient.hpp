#pragma once

#include "NetworkUdpPacketPool.hpp"

namespace th105 {

struct NetworkSendPeerRecord20 {
    unsigned char endpoint_00[16];
    int slot_10;
    unsigned char unreviewed_14[12];
};

class NetworkWinsockSendClientView {
public:
    void send_loop();
    int send_client(const void *payload, unsigned int size,
                    unsigned int timeout_ms, unsigned int *result);
    void send_server(unsigned int index, const void *payload, unsigned int size,
                     unsigned int timeout_ms, unsigned int *result);

    unsigned char unreviewed_000[0x28];
    unsigned int socket_028;
    unsigned char unreviewed_02c[0x48];
    unsigned char running_074;
    unsigned char unreviewed_075[0x4b];
    unsigned char endpoint_0c0[16];
    unsigned char unreviewed_0d0[0x10];
    NetworkUdpPacketCriticalSectionView endpoint_lock_0e0;
    unsigned char unreviewed_0fc[0x0c];
    std::vector<NetworkSendPeerRecord20> records_108;
    unsigned char unreviewed_118[8];
    NetworkUdpPacketCriticalSectionView peer_lock_120;
    unsigned char unreviewed_13c[0x2c];
    std::deque<unsigned int> pending_tokens_168;
    NetworkUdpPacketHandleManager64 packet_pool_17c;
    void *event_1e0;
    NetworkUdpPacketCriticalSectionView queue_lock_1e4;
};

typedef char NetworkWinsockSendClientSize[
    sizeof(NetworkWinsockSendClientView) == 0x200 ? 1 : -1];

} // namespace th105
