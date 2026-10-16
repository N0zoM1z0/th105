#include "engine/CriticalSectionWrapper.hpp"
#include <map>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

namespace th105 {
extern "C" int __stdcall recvfrom(unsigned int socket, char *buffer, int size,
    int flags, void *sender, int *sender_size);
extern "C" int __stdcall sendto(unsigned int socket, const char *buffer, int size,
    int flags, const void *destination, int destination_size);
extern "C" unsigned short __stdcall ntohs(unsigned short port);
extern "C" unsigned short __stdcall htons(unsigned short port);
extern "C" unsigned long __stdcall htonl(unsigned long address);
extern "C" unsigned int __stdcall socket(int family, int type, int protocol);
extern "C" int __stdcall bind(unsigned int socket, const void *address, int size);
extern "C" int __stdcall closesocket(unsigned int socket);
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
extern "C" unsigned long __stdcall inet_addr(const char *address);
struct NetworkReceiveHostEntry {
    char *name_00;
    char **aliases_04;
    short address_type_08;
    short address_size_0a;
    char **addresses_0c;
};
extern "C" NetworkReceiveHostEntry *__stdcall gethostbyname(const char *name);
extern "C" __declspec(dllimport) int __stdcall GetExitCodeThread(
    void *thread, unsigned long *exit_code);
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
    void *handle, unsigned long milliseconds);

struct NetworkReceiveWorker8 {
    bool start(unsigned long (__stdcall *entry)(void *), void *parameter);
    bool is_running()
    {
        if (handle_00 != 0) {
            unsigned long exit_code;
            GetExitCodeThread(handle_00, &exit_code);
            return exit_code == 259;
        }
        return false;
    }
    void *handle_00;
    unsigned long thread_id_04;
};

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
    unsigned char unreviewed_075[3];
    void *request_data_078;
    unsigned short request_size_07c;
    unsigned char unreviewed_07e[2];
    NetworkReceiveCallbackView *callback_080;
    CriticalSectionWrapper callback_lock_084;
    NetworkReceiveAddress16 connection_endpoint_0a0;
    unsigned char unreviewed_0b0[0x10];
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
    NetworkReceiveWorker8 connection_worker_13c;
    unsigned int state_144;
    unsigned int marker_148;
    std::vector<NetworkReceiveAddress16> endpoints_14c;
};

struct NetworkConnectionHandoff10 {
    NetworkWinsockReceiveView *owner_00;
    unsigned short size_04;
    const void *data_08;
    int copied_0c;
};
extern "C" unsigned long __stdcall network_winsock_connection_thread(void *parameter);

#pragma pack(push, 1)
struct NetworkConnectionProbe25 {
    unsigned char opcode_00;
    NetworkReceiveAddress16 first_01;
    NetworkReceiveAddress16 second_11;
    unsigned short port_21;
    unsigned char unreviewed_23[2];
};
struct NetworkConnectionRequestHeader19 {
    unsigned char opcode_00;
    unsigned char key_01[16];
    unsigned short word_11;
    unsigned char peer_limit_13;
    unsigned char unreviewed_14;
    unsigned short size_15;
    unsigned char unreviewed_17[2];
};
// The only fresh-data caller supplies ConnectPacket40; the receive caller
// reuses it through FFFF. Original stack packet capacity remains unknown.
struct NetworkConnectionRequest41 {
    NetworkConnectionRequestHeader19 header_00;
    unsigned char payload_19[40];
};
#pragma pack(pop)

static void __stdcall clear_connection_endpoints(
    std::vector<NetworkReceiveAddress16> &endpoints)
{
    endpoints.clear();
}

char NetworkWinsockReceiveView::start_connection(const char *endpoint,
    unsigned short port, const void *packet, unsigned short size)
{
    if (connection_worker_13c.is_running())
        return 0;
    NetworkReceiveLock endpoint_lock(&endpoint_lock_0e0);
    if (state_144 == 2 || state_144 == 3)
        return 0;
    if (size < 0xffff) {
        if (request_data_078)
            free(request_data_078);
        request_size_07c = size;
        if (size) {
            request_data_078 = malloc(size);
            memcpy(request_data_078, packet, request_size_07c);
        } else {
            request_data_078 = 0;
        }
    }
    NetworkConnectionHandoff10 handoff;
    handoff.owner_00 = this;
    handoff.size_04 = request_size_07c;
    handoff.data_08 = request_data_078;
    handoff.copied_0c = 0;
    if (endpoint) {
        connection_endpoint_0a0.family_00 = 2;
        connection_endpoint_0a0.port_02 = htons(port);
        connection_endpoint_0a0.address_04 = inet_addr(endpoint);
        if (connection_endpoint_0a0.address_04 == 0xffffffffU) {
            NetworkReceiveHostEntry *host = gethostbyname(endpoint);
            if (!host || !host->addresses_0c[0])
                return 0;
            connection_endpoint_0a0.address_04 =
                *reinterpret_cast<const unsigned int *>(host->addresses_0c[0]);
        }
    }
    published_endpoint_03c = connection_endpoint_0a0;
    previous_endpoint_04c = connection_endpoint_0a0;
    clear_connection_endpoints(endpoints_14c);
    endpoints_14c.push_back(connection_endpoint_0a0);
    state_144 = 2;
    connection_worker_13c.start(network_winsock_connection_thread, &handoff);
    while (handoff.copied_0c == 0)
        WaitForSingleObject(connection_worker_13c.handle_00, 16);
    return 1;
}

extern "C" unsigned long __stdcall network_winsock_connection_thread(void *parameter)
{
    NetworkConnectionHandoff10 *handoff =
        static_cast<NetworkConnectionHandoff10 *>(parameter);
    NetworkWinsockReceiveView *owner = handoff->owner_00;
    void *pacing_handle = owner->connection_worker_13c.handle_00;
    NetworkConnectionProbe25 probe;
    probe.opcode_00 = 1;
    NetworkConnectionRequest41 request;
    request.header_00.opcode_00 = 5;
    memcpy(request.header_00.key_01, owner->key_004, 16);
    request.header_00.word_11 = owner->word_024;
    request.header_00.peer_limit_13 = static_cast<unsigned char>(owner->peer_limit_11c);
    request.header_00.size_15 = handoff->size_04;
    if (handoff->size_04)
        memcpy(request.payload_19, handoff->data_08, handoff->size_04);
    unsigned int request_size = request.header_00.size_15 + 25;
    int probe_count = 0;
    int request_count = 0;
    handoff->copied_0c = 1;

    NetworkReceiveAddress16 local = {};
    local.family_00 = 2;
    local.address_04 = htonl(0);
    local.port_02 = htons(static_cast<unsigned short>(timeGetTime()) % 1000 + 11000);
    unsigned int auxiliary = socket(2, 2, 0);
    bool auxiliary_bound = false;
    if (auxiliary != 0xffffffffU) {
        if (bind(auxiliary, &local, 16) >= 0)
            auxiliary_bound = true;
        else
            closesocket(auxiliary);
    }

    owner->marker_148 = 0;
    bool running = true;
    if (owner->endpoints_14c.size() != 0) {
        owner->published_endpoint_03c = owner->endpoints_14c[0];
        do {
            EnterCriticalSection(&owner->endpoint_lock_0e0.critical_section_04);
            if (owner->state_144 == 2) {
                probe.second_11 = owner->published_endpoint_03c;
                probe.first_01 = owner->published_endpoint_03c;
                probe.port_21 = 0;
                sendto(owner->socket_028, reinterpret_cast<const char *>(&probe),
                    37, 0, &owner->published_endpoint_03c, 16);
                if (auxiliary_bound)
                    sendto(auxiliary, reinterpret_cast<const char *>(&probe),
                        37, 0, &owner->published_endpoint_03c, 16);
                probe.first_01 = owner->previous_endpoint_04c;
                probe.port_21 = 0;
                sendto(owner->socket_028, reinterpret_cast<const char *>(&probe),
                    37, 0, &owner->previous_endpoint_04c, 16);
                probe.port_21 = owner->word_024 + probe_count;
                sendto(owner->socket_028, reinterpret_cast<const char *>(&probe),
                    37, 0, &owner->previous_endpoint_04c, 16);
                if (auxiliary_bound) {
                    probe.port_21 = ntohs(local.port_02) + probe_count;
                    sendto(owner->socket_028, reinterpret_cast<const char *>(&probe),
                        37, 0, &owner->previous_endpoint_04c, 16);
                }
                if (probe_count++ > 32) {
                    ++owner->marker_148;
                    if (owner->marker_148 >= owner->endpoints_14c.size())
                        owner->state_144 = 6;
                    else {
                        probe_count = 0;
                        owner->published_endpoint_03c =
                            owner->endpoints_14c[owner->marker_148];
                    }
                }
                request_count = 0;
            } else if (owner->state_144 == 3) {
                sendto(owner->socket_028, reinterpret_cast<const char *>(&request),
                    request_size, 0, &owner->published_endpoint_03c, 16);
                if (request_count++ > 100)
                    owner->state_144 = 6;
                probe_count = 0;
            } else {
                running = false;
            }
            if (!owner->running_074)
                owner->state_144 = 6;
            LeaveCriticalSection(&owner->endpoint_lock_0e0.critical_section_04);
            WaitForSingleObject(pacing_handle, 128);
        } while (running);
    }
    if (auxiliary_bound)
        closesocket(auxiliary);
    return 0;
}

typedef char ReceiveWorkerSize[sizeof(NetworkReceiveWorker8) == 8 ? 1 : -1];
typedef char ConnectionHandoffSize[sizeof(NetworkConnectionHandoff10) == 16 ? 1 : -1];
typedef char ConnectionProbeSize[sizeof(NetworkConnectionProbe25) == 37 ? 1 : -1];
typedef char ConnectionRequestHeaderSize[sizeof(NetworkConnectionRequestHeader19) == 25 ? 1 : -1];
typedef char ReceiveOwnerSize[sizeof(NetworkWinsockReceiveView) == 0x15c ? 1 : -1];
typedef char ReceiveRequestOffset[offsetof(NetworkWinsockReceiveView, request_data_078) == 0x78 ? 1 : -1];
typedef char ReceiveConnectionOffset[offsetof(NetworkWinsockReceiveView, connection_endpoint_0a0) == 0xa0 ? 1 : -1];
typedef char ReceiveWorkerOffset[offsetof(NetworkWinsockReceiveView, connection_worker_13c) == 0x13c ? 1 : -1];

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
