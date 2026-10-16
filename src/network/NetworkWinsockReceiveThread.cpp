#include "engine/CriticalSectionWrapper.hpp"
#include <map>
#include <vector>
#include <string.h>

namespace th105 {
extern "C" int __stdcall recvfrom(unsigned int socket, char *buffer, int size,
    int flags, void *sender, int *sender_size);
extern "C" int __stdcall sendto(unsigned int socket, const char *buffer, int size,
    int flags, const void *destination, int destination_size);
extern "C" unsigned short __stdcall ntohs(unsigned short port);
extern "C" unsigned short __stdcall htons(unsigned short port);

struct NetworkReceiveAddress16 {
    unsigned short family_00;
    unsigned short port_02;
    unsigned int address_04;
    unsigned char unreviewed_08[8];
};
struct NetworkReceivePeer20 {
    NetworkReceiveAddress16 endpoint_00;
    int slot_10;
    unsigned int probe_count_14;
    unsigned int unreviewed_18;
    unsigned int reported_value_1c;
};
typedef std::multimap<unsigned int, NetworkReceivePeer20 *> NetworkReceivePeerMap;

#pragma pack(push, 1)
struct NetworkReceiveProbe4 { unsigned int reported_value_00; };
struct NetworkReceiveReject4 { unsigned int code_00; };
struct NetworkReceiveRoute24 {
    NetworkReceiveAddress16 first_00;
    NetworkReceiveAddress16 second_10;
    unsigned int port_20;
};
struct NetworkReceiveEndpointList44 {
    int count_00;
    NetworkReceiveAddress16 endpoints_04[4];
};
struct NetworkReceiveRequest18 {
    unsigned char unreviewed_00[20];
    unsigned short size_14;
    unsigned char unreviewed_16[2];
};
struct NetworkReceiveAccept0C {
    unsigned char unreviewed_00[8];
    unsigned short size_08;
    unsigned char unreviewed_0a[2];
};
#pragma pack(pop)

class NetworkReceiveCallbackView {
public:
    virtual void on_accepted(unsigned int code, const void *payload, unsigned int size);
    virtual void on_rejected(unsigned int code);
    virtual void on_primary_data(const void *payload, int size);
    virtual void on_peer_data(unsigned int slot, const void *payload, int size);
};
class NetworkReceiveLock {
public:
    explicit NetworkReceiveLock(CriticalSectionWrapper *lock) : lock_(lock)
    { EnterCriticalSection(&lock_->critical_section_04); }
    ~NetworkReceiveLock()
    { LeaveCriticalSection(&lock_->critical_section_04); }
private:
    CriticalSectionWrapper *lock_;
};

class NetworkWinsockReceiveView {
public:
    void receive_loop();
    void remove_peer(unsigned int slot);
    char start_connection(const char *endpoint, unsigned short port,
                          const void *packet, unsigned short size);

    unsigned char unreviewed_000[0x28];
    unsigned int socket_028;
    unsigned char unreviewed_02c[0x10];
    NetworkReceiveAddress16 published_endpoint_03c;
    NetworkReceiveAddress16 previous_endpoint_04c;
    unsigned char unreviewed_05c[0x18];
    unsigned char running_074;
    unsigned char unreviewed_075[0x0b];
    NetworkReceiveCallbackView *callback_080;
    CriticalSectionWrapper callback_lock_084;
    unsigned char unreviewed_0a0[0x20];
    NetworkReceiveAddress16 primary_endpoint_0c0;
    unsigned char unreviewed_0d0[4];
    unsigned int probe_count_0d4;
    unsigned char unreviewed_0d8[4];
    unsigned int reported_value_0dc;
    CriticalSectionWrapper endpoint_lock_0e0;
    NetworkReceivePeerMap peers_0fc;
    std::vector<NetworkReceivePeer20> peer_records_108;
    unsigned char unreviewed_118[8];
    CriticalSectionWrapper peer_lock_120;
    unsigned char unreviewed_13c[8];
    unsigned int state_144;
    unsigned int marker_148;
    std::vector<NetworkReceiveAddress16> endpoints_14c;
};

struct NetworkAcceptAddress16;
struct NetworkUdpAcceptView;
struct NetworkAcceptPacketHeader0C;
void __fastcall network_udp_accept(const NetworkAcceptAddress16 *sender,
    NetworkUdpAcceptView *owner, const NetworkAcceptPacketHeader0C *packet);
// The complete target preserves all other incoming registers and pops only
// its owner pointer: ECX sender, EDX request payload, stack owner.
void __fastcall network_udp_receive_request(const NetworkReceiveAddress16 *sender,
    const NetworkReceiveRequest18 *packet, NetworkWinsockReceiveView *owner);

static NetworkReceivePeerMap::iterator __stdcall find_receive_peer(
    NetworkWinsockReceiveView *owner, const NetworkReceiveAddress16 &sender)
{
    std::pair<NetworkReceivePeerMap::iterator, NetworkReceivePeerMap::iterator> range =
        owner->peers_0fc.equal_range(sender.address_04);
    for (NetworkReceivePeerMap::iterator it = range.first; it != range.second; ++it)
        if (it->second->endpoint_00.port_02 == sender.port_02)
            return it;
    return owner->peers_0fc.end();
}

static void __stdcall receive_rejection(NetworkWinsockReceiveView *owner,
                                        const NetworkReceiveReject4 *packet)
{
    NetworkReceiveLock lock(&owner->callback_lock_084);
    if (owner->callback_080)
        owner->callback_080->on_rejected(packet->code_00);
    owner->state_144 = 9;
}

static void __stdcall receive_endpoint_list(NetworkWinsockReceiveView *owner,
                                            const NetworkReceiveEndpointList44 *packet)
{
    NetworkReceiveLock lock(&owner->endpoint_lock_0e0);
    int count = packet->count_00;
    if (count > 4)
        count = 4;
    for (int index = 0; index < count; ++index) {
        if (owner->published_endpoint_03c.address_04 == packet->endpoints_04[index].address_04
            && owner->published_endpoint_03c.port_02 == packet->endpoints_04[index].port_02)
            return;
    }
    owner->previous_endpoint_04c = owner->published_endpoint_03c;
    owner->published_endpoint_03c = packet->endpoints_04[0];
    owner->marker_148 = 0xffffffffU;
    owner->endpoints_14c.clear();
    for (int index = 0; index < count; ++index)
        owner->endpoints_14c.push_back(packet->endpoints_04[index]);
    owner->state_144 = 2;
}

void NetworkWinsockReceiveView::receive_loop()
{
    unsigned char packet[1024];
    memset(packet, 0, sizeof(packet));
    NetworkReceiveAddress16 sender;
    int sender_size = 16;
    // Only the maximum transmitted reply extent is established. Its final
    // four bytes are not written on the forwarding path in the target.
    unsigned char reply[21];
    while (running_074) {
        int received = recvfrom(socket_028, reinterpret_cast<char *>(packet),
                                sizeof(packet), 0, &sender, &sender_size);
        if (static_cast<unsigned int>(received) > 1023)
            continue;
        int size = received - 1;
        const unsigned char *payload = packet + 1;
        switch (packet[0]) {
        case 1:
            if (size == 36) {
                const NetworkReceiveRoute24 *route =
                    reinterpret_cast<const NetworkReceiveRoute24 *>(payload);
                if (route->second_10.address_04 == route->first_00.address_04
                    && route->second_10.port_02 == route->first_00.port_02) {
                    reply[0] = 3;
                    sendto(socket_028, reinterpret_cast<const char *>(reply), 1, 0, &sender, 16);
                } else {
                    reply[0] = 2;
                    memcpy(reply + 1, &sender, sizeof(sender));
                    unsigned short port = static_cast<unsigned short>(route->port_20);
                    if (port < 1024)
                        port = static_cast<unsigned short>(ntohs(sender.port_02) + port);
                    port = htons(port);
                    memcpy(reply + 3, &port, sizeof(port));
                    sendto(socket_028, reinterpret_cast<const char *>(reply), 21, 0,
                           &route->second_10, 16);
                }
            }
            break;
        case 2:
            if (size == 20) {
                reply[0] = 3;
                sendto(socket_028, reinterpret_cast<const char *>(reply), 1, 0, payload, 16);
            }
            break;
        case 3:
            EnterCriticalSection(&endpoint_lock_0e0.critical_section_04);
            published_endpoint_03c = sender;
            if (state_144 == 2)
                state_144 = 3;
            LeaveCriticalSection(&endpoint_lock_0e0.critical_section_04);
            break;
        case 4:
            if (size == 4) {
                const NetworkReceiveProbe4 *probe = reinterpret_cast<const NetworkReceiveProbe4 *>(payload);
                EnterCriticalSection(&peer_lock_120.critical_section_04);
                NetworkReceivePeerMap::iterator it = find_receive_peer(this, sender);
                if (it != peers_0fc.end()) {
                    it->second->reported_value_1c = probe->reported_value_00;
                    it->second->probe_count_14 = 0;
                    LeaveCriticalSection(&peer_lock_120.critical_section_04);
                } else {
                    LeaveCriticalSection(&peer_lock_120.critical_section_04);
                    NetworkReceiveLock endpoint_lock(&endpoint_lock_0e0);
                    if (primary_endpoint_0c0.address_04 == sender.address_04
                        && primary_endpoint_0c0.port_02 == sender.port_02) {
                        reported_value_0dc = probe->reported_value_00;
                        probe_count_0d4 = 0;
                    }
                }
            }
            break;
        case 5: {
            const NetworkReceiveRequest18 *request = reinterpret_cast<const NetworkReceiveRequest18 *>(payload);
            if (size == request->size_14 + 24)
                network_udp_receive_request(&sender, request, this);
            break;
        }
        case 6: {
            const NetworkReceiveAccept0C *accepted = reinterpret_cast<const NetworkReceiveAccept0C *>(payload);
            if (size == accepted->size_08 + 12)
                network_udp_accept(reinterpret_cast<const NetworkAcceptAddress16 *>(&sender),
                    reinterpret_cast<NetworkUdpAcceptView *>(this),
                    reinterpret_cast<const NetworkAcceptPacketHeader0C *>(payload));
            break;
        }
        case 7:
            if (size == 4 && state_144 == 3)
                receive_rejection(this, reinterpret_cast<const NetworkReceiveReject4 *>(payload));
            break;
        case 8:
            if (size == 68)
                receive_endpoint_list(this, reinterpret_cast<const NetworkReceiveEndpointList44 *>(payload));
            break;
        case 11: {
            {
                NetworkReceiveLock peer_lock(&peer_lock_120);
                NetworkReceivePeerMap::iterator it = find_receive_peer(this, sender);
                if (it != peers_0fc.end()) {
                    remove_peer(it->second->slot_10);
                    break;
                }
            }
            NetworkReceiveLock endpoint_lock(&endpoint_lock_0e0);
            if (primary_endpoint_0c0.address_04 == sender.address_04
                && primary_endpoint_0c0.port_02 == sender.port_02)
                start_connection(0, 0, 0, 0xffff);
            break;
        }
        case 13:
            EnterCriticalSection(&endpoint_lock_0e0.critical_section_04);
            if (primary_endpoint_0c0.address_04 != sender.address_04
                || primary_endpoint_0c0.port_02 != sender.port_02) {
                LeaveCriticalSection(&endpoint_lock_0e0.critical_section_04);
                break;
            }
            probe_count_0d4 = 0;
            LeaveCriticalSection(&endpoint_lock_0e0.critical_section_04);
            {
                NetworkReceiveLock callback_lock(&callback_lock_084);
                if (callback_080)
                    callback_080->on_primary_data(payload, size);
            }
            break;
        case 14: {
            EnterCriticalSection(&peer_lock_120.critical_section_04);
            NetworkReceivePeerMap::iterator it = find_receive_peer(this, sender);
            if (it == peers_0fc.end()) {
                LeaveCriticalSection(&peer_lock_120.critical_section_04);
                break;
            }
            it->second->probe_count_14 = 0;
            unsigned int slot = it->second->slot_10;
            LeaveCriticalSection(&peer_lock_120.critical_section_04);
            NetworkReceiveLock callback_lock(&callback_lock_084);
            if (callback_080)
                callback_080->on_peer_data(slot, payload, size);
            break;
        }
        }
    }
}

extern "C" unsigned long __stdcall network_winsock_receive_thread(void *owner)
{
    static_cast<NetworkWinsockReceiveView *>(owner)->receive_loop();
    return 0;
}

typedef char ReceiveAddressSize[sizeof(NetworkReceiveAddress16) == 16 ? 1 : -1];
typedef char ReceivePeerSize[sizeof(NetworkReceivePeer20) == 32 ? 1 : -1];
typedef char ReceiveRouteSize[sizeof(NetworkReceiveRoute24) == 36 ? 1 : -1];
typedef char ReceiveListSize[sizeof(NetworkReceiveEndpointList44) == 68 ? 1 : -1];
typedef char ReceiveMapSize[sizeof(NetworkReceivePeerMap) == 12 ? 1 : -1];
typedef char ReceiveSocketOffset[offsetof(NetworkWinsockReceiveView, socket_028) == 0x28 ? 1 : -1];
typedef char ReceivePublishedOffset[offsetof(NetworkWinsockReceiveView, published_endpoint_03c) == 0x3c ? 1 : -1];
typedef char ReceiveRunningOffset[offsetof(NetworkWinsockReceiveView, running_074) == 0x74 ? 1 : -1];
typedef char ReceiveCallbackOffset[offsetof(NetworkWinsockReceiveView, callback_080) == 0x80 ? 1 : -1];
typedef char ReceiveEndpointOffset[offsetof(NetworkWinsockReceiveView, primary_endpoint_0c0) == 0xc0 ? 1 : -1];
typedef char ReceiveMapOffset[offsetof(NetworkWinsockReceiveView, peers_0fc) == 0xfc ? 1 : -1];
typedef char ReceiveVectorOffset[offsetof(NetworkWinsockReceiveView, peer_records_108) == 0x108 ? 1 : -1];
typedef char ReceivePeerLockOffset[offsetof(NetworkWinsockReceiveView, peer_lock_120) == 0x120 ? 1 : -1];
typedef char ReceiveStateOffset[offsetof(NetworkWinsockReceiveView, state_144) == 0x144 ? 1 : -1];
typedef char ReceiveListOffset[offsetof(NetworkWinsockReceiveView, endpoints_14c) == 0x14c ? 1 : -1];
} // namespace th105
