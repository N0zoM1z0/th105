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
    unsigned int response_code_18;
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
    unsigned char key_00[16];
    unsigned int unreviewed_10;
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
    virtual int route_payload(unsigned int slot, int *code, const unsigned char *payload,
                              int size, void **reply, unsigned short *reply_size);
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

    unsigned char unreviewed_000[4];
    unsigned char key_004[16];
    unsigned char key_014[16];
    unsigned short word_024;
    unsigned char unreviewed_026[2];
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
    unsigned int active_count_118;
    unsigned int peer_limit_11c;
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

static NetworkReceivePeer20 &__stdcall request_peer(
    std::vector<NetworkReceivePeer20> &peers, unsigned int slot)
{
    return peers[slot];
}

#pragma pack(push, 1)
struct NetworkRequestAcceptHeader0D {
    unsigned char opcode_00;
    unsigned char slot_01;
    unsigned char unreviewed_02;
    unsigned short word_03;
    unsigned int code_05;
    unsigned short size_09;
    unsigned char unreviewed_0b[2];
};
struct NetworkRequestRedirect45 {
    unsigned char opcode_00;
    unsigned int count_01;
    NetworkReceiveAddress16 endpoints_05[4];
};
struct NetworkRequestReject05 {
    unsigned char opcode_00;
    unsigned int code_01;
};
// Both canonical secondary route implementations return exactly0x44 bytes on
// success. This is minimum observed reply storage, not a recovered capacity.
union NetworkRequestReply51 {
    struct {
        NetworkRequestAcceptHeader0D header_00;
        unsigned char payload_0d[0x44];
    } accepted;
    NetworkRequestRedirect45 redirect;
    NetworkRequestReject05 rejected;
};
#pragma pack(pop)

// The SDK defines equivalent IsEqualGUID source. Ownership of4152A0
// remains in review despite its canonical byte equality; no authored credit.
static int __stdcall request_key_matches(const void *expected, const void *incoming)
{
    return memcmp(expected, incoming, 16) == 0;
}

void __fastcall network_udp_receive_request(const NetworkReceiveAddress16 *sender,
    const NetworkReceiveRequest18 *packet, NetworkWinsockReceiveView *owner)
{
    if (!owner->running_074 || owner->peer_limit_11c == 0)
        return;
    if (!request_key_matches(owner->key_004, packet->key_00)
        && !request_key_matches(owner->key_014, packet->key_00))
        return;

    void *reply_data = 0;
    unsigned short reply_size = 0;
    int response_code;
    NetworkReceiveLock peer_lock(&owner->peer_lock_120);
    NetworkReceivePeerMap::iterator it = find_receive_peer(owner, *sender);
    NetworkReceivePeer20 *peer = 0;
    NetworkRequestReply51 reply;
    if (it == owner->peers_0fc.end()) {
        if (owner->active_count_118 >= owner->peer_limit_11c) {
            unsigned int best = 0xffffffffU;
            unsigned int selected;
            for (unsigned int index = 0; index < owner->peer_records_108.size(); ++index) {
                if (request_peer(owner->peer_records_108, index).slot_10 != -1
                    && request_peer(owner->peer_records_108, index).reported_value_1c < best
                    && request_peer(owner->peer_records_108, index).reported_value_1c != 0) {
                    best = request_peer(owner->peer_records_108, index).reported_value_1c;
                    selected = index;
                }
            }
            if (best == 0xffffffffU)
                return;
            reply.redirect.opcode_00 = 8;
            unsigned int count = 0;
            for (unsigned int offset = 0;
                 offset < owner->peer_records_108.size() && offset < 4; ++offset) {
                unsigned int index = (selected + offset) % owner->peer_records_108.size();
                if (request_peer(owner->peer_records_108, index).slot_10 != -1
                    && request_peer(owner->peer_records_108, index).reported_value_1c != 0) {
                    reply.redirect.endpoints_05[count] = request_peer(owner->peer_records_108, index).endpoint_00;
                    ++count;
                }
            }
            reply.redirect.count_01 = count;
            sendto(owner->socket_028, reinterpret_cast<const char *>(&reply), 69, 0, sender, 16);
            return;
        }
        for (unsigned int slot = 0; slot < owner->peer_records_108.size(); ++slot) {
            if (request_peer(owner->peer_records_108, slot).slot_10 != -1)
                continue;
            NetworkReceiveLock callback_lock(&owner->callback_lock_084);
            if (owner->callback_080) {
                int result = owner->callback_080->route_payload(slot, &response_code,
                    reinterpret_cast<const unsigned char *>(packet + 1), packet->size_14,
                    &reply_data, &reply_size);
                if (result == 0) {
                    request_peer(owner->peer_records_108, slot).endpoint_00 = *sender;
                    request_peer(owner->peer_records_108, slot).slot_10 = slot;
                    request_peer(owner->peer_records_108, slot).probe_count_14 = 0;
                    request_peer(owner->peer_records_108, slot).response_code_18 = response_code;
                    // The target consumes .first from the native tree
                    // insertion result (iterator plus success byte).
                    it = static_cast<NetworkReceivePeerMap::_Mybase &>(owner->peers_0fc)
                        .insert(NetworkReceivePeerMap::value_type(sender->address_04,
                            &request_peer(owner->peer_records_108, slot))).first;
                    peer = &request_peer(owner->peer_records_108, slot);
                    ++owner->active_count_118;
                    break;
                }
                if (result == 9) {
                    reply.rejected.opcode_00 = 7;
                    reply.rejected.code_01 = response_code;
                    sendto(owner->socket_028, reinterpret_cast<const char *>(&reply), 5, 0, sender, 16);
                    return;
                }
            }
        }
    } else {
        peer = it->second;
    }
    if (peer != 0) {
        reply.accepted.header_00.opcode_00 = 6;
        reply.accepted.header_00.slot_01 = static_cast<unsigned char>(it->second->slot_10);
        reply.accepted.header_00.word_03 = owner->word_024;
        reply.accepted.header_00.code_05 = it->second->response_code_18;
        reply.accepted.header_00.size_09 = reply_size;
        if (reply_data != 0)
            memcpy(reply.accepted.payload_0d, reply_data, reply_size);
        sendto(owner->socket_028, reinterpret_cast<const char *>(&reply),
               reply_size + 13, 0, peer, 16);
    }
}

typedef char RequestHeaderSize[sizeof(NetworkReceiveRequest18) == 24 ? 1 : -1];
typedef char RequestAcceptSize[sizeof(NetworkRequestAcceptHeader0D) == 13 ? 1 : -1];
typedef char RequestRedirectSize[sizeof(NetworkRequestRedirect45) == 69 ? 1 : -1];
typedef char RequestReplySize[sizeof(NetworkRequestReply51) == 81 ? 1 : -1];

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
