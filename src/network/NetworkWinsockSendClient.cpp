#include "NetworkUdpPacketPool.hpp"
#include "assets/ResourceHandleManager.hpp"
#include <string.h>

namespace th105 {
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
extern "C" __declspec(dllimport) int __stdcall SetEvent(void *event);

class NetworkWinsockSendClientView {
public:
    int send_client(const void *payload, unsigned int size,
                    unsigned int options, unsigned int *result);

    unsigned char unreviewed_000[0x74];
    unsigned char running_074;
    unsigned char unreviewed_075[0x4b];
    unsigned char endpoint_0c0[16];
    unsigned char unreviewed_0d0[0x10];
    NetworkUdpPacketCriticalSectionView endpoint_lock_0e0;
    unsigned char unreviewed_0fc[0x6c];
    std::deque<unsigned int> pending_tokens_168;
    NetworkUdpPacketHandleManager64 packet_pool_17c;
    void *event_1e0;
    NetworkUdpPacketCriticalSectionView queue_lock_1e4;
};

int NetworkWinsockSendClientView::send_client(
    const void *payload, unsigned int size,
    unsigned int options, unsigned int *result)
{
    unsigned int token = 0;
    NetworkUdpPacketBuffer41C *packet = packet_pool_17c.acquire(
        *reinterpret_cast<ResourceHandleToken *>(&token));
    packet->payload_1c[0] = 0x0e;
    packet->options_14 = options;
    packet->timestamp_10 = timeGetTime();
    EnterCriticalSection(&endpoint_lock_0e0.critical_section_04);
    memcpy(packet->endpoint_00, endpoint_0c0, sizeof(endpoint_0c0));
    LeaveCriticalSection(&endpoint_lock_0e0.critical_section_04);
    memcpy(packet->payload_1c + 1, payload, size);
    packet->size_18 = size + 1;
    EnterCriticalSection(&queue_lock_1e4.critical_section_04);
    if (result != 0) {
        for (std::deque<unsigned int>::iterator it = pending_tokens_168.begin();
             it != pending_tokens_168.end(); ++it) {
            if (*it == *result) {
                packet_pool_17c.release(*it);
                pending_tokens_168.erase(it);
                break;
            }
            if (!running_074)
                break;
        }
        *result = token;
    }
    pending_tokens_168.push_back(token);
    LeaveCriticalSection(&queue_lock_1e4.critical_section_04);
    return SetEvent(event_1e0);
}

typedef char SendClientEndpointOffset[offsetof(NetworkWinsockSendClientView, endpoint_0c0)==0xc0?1:-1];
typedef char SendClientQueueOffset[offsetof(NetworkWinsockSendClientView, pending_tokens_168)==0x168?1:-1];
typedef char SendClientPoolOffset[offsetof(NetworkWinsockSendClientView, packet_pool_17c)==0x17c?1:-1];
typedef char SendClientEventOffset[offsetof(NetworkWinsockSendClientView, event_1e0)==0x1e0?1:-1];
typedef char SendClientQueueLockOffset[offsetof(NetworkWinsockSendClientView, queue_lock_1e4)==0x1e4?1:-1];

// Token recycling is shared by the manager's payload specializations.
void NetworkUdpPacketHandleManager64::release(unsigned int packed_token)
{
    const ResourceHandleToken &token =
        *reinterpret_cast<const ResourceHandleToken *>(&packed_token);
    EnterCriticalSection(&critical_48.critical_section_04);
    if (generations_28[token.slot_00] == token.generation_02) {
        generations_28[token.slot_00] = 0;
        free_slots_38.push_back(token.slot_00);
    }
    LeaveCriticalSection(&critical_48.critical_section_04);
}
} // namespace th105

namespace th105 {
class NetworkUdpPacketPoolLock {
public:
    explicit NetworkUdpPacketPoolLock(NetworkUdpPacketCriticalSectionView *lock)
        : lock_(lock) { EnterCriticalSection(&lock_->critical_section_04); }
    ~NetworkUdpPacketPoolLock() { LeaveCriticalSection(&lock_->critical_section_04); }
private:
    NetworkUdpPacketCriticalSectionView *lock_;
};

NetworkUdpPacketBuffer41C *NetworkUdpPacketHandleManager64::acquire(ResourceHandleToken &token)
{
    NetworkUdpPacketPoolLock scope(&critical_48);
    unsigned int slot;
    if (free_slots_38.empty()) {
        slot = packets_04.size();
        if (++generation_44 > 0xffff)
            generation_44 = 1;
        token.slot_00 = static_cast<unsigned short>(slot);
        token.generation_02 = static_cast<unsigned short>(generation_44);
        NetworkUdpPacketBuffer41C packet;
        memset(&packet, 0, sizeof(packet));
        packets_04.push_back(packet);
        slots_18.push_back(&packets_04.back());
        generations_28.push_back(token.generation_02);
    } else {
        // Reuse preserves packet contents; only its token generation changes.
        slot = free_slots_38.back();
        if (++generation_44 > 0xffff)
            generation_44 = 1;
        token.slot_00 = static_cast<unsigned short>(slot);
        token.generation_02 = static_cast<unsigned short>(generation_44);
        free_slots_38.pop_back();
        generations_28[slot] = token.generation_02;
    }
    return slots_18.at(slot);
}
} // namespace th105
