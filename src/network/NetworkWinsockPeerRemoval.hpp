#pragma once

#include "NetworkUdpEvent.hpp"
#include "../engine/CriticalSectionWrapper.hpp"

#include <map>
#include <vector>

namespace th105 {

struct NetworkPeerAddress16 {
    unsigned short family_00;
    unsigned short port_02;
    unsigned int address_04;
    unsigned char reserved_08[8];
};

struct NetworkPeerRecord20 {
    NetworkPeerAddress16 endpoint_00;
    int slot_10;
    unsigned int counter_14;
    unsigned int unknown_18;
    unsigned int unknown_1c;
};

typedef std::multimap<unsigned int, NetworkPeerRecord20 *> NetworkPeerMap;


// Prefix used by endpoint lookup and peer removal.
struct NetworkWinsockPeerRemovalView {
    NetworkPeerMap::iterator find_peer(const NetworkPeerAddress16 &address);
    void remove_peer(unsigned int slot);

    unsigned char unreviewed_000[0x28];
    unsigned int socket_028;
    unsigned char unreviewed_02c[0x54];
    INetworkUDPEventProc *callback_080;
    CriticalSectionWrapper callback_lock_084;
    unsigned char unreviewed_0a0[0x5c];
    NetworkPeerMap peers_0fc;
    std::vector<NetworkPeerRecord20> records_108;
    unsigned int active_count_118;
    unsigned char unreviewed_11c[4];
    CriticalSectionWrapper peer_lock_120;
};

} // namespace th105
