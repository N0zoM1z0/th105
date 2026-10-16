#include "engine/CriticalSectionWrapper.hpp"

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

class NetworkPeerRemovalCallbackView {
public:
    virtual void unreviewed_slot_00();
    virtual void unreviewed_slot_04();
    virtual void unreviewed_slot_08();
    virtual void unreviewed_slot_0c();
    virtual void unreviewed_slot_10();
    virtual void on_peer_removed(unsigned int slot);
};

class NetworkPeerRemovalLock {
public:
    explicit NetworkPeerRemovalLock(CriticalSectionWrapper *lock) : lock_(lock)
    {
        EnterCriticalSection(&lock_->critical_section_04);
    }

    ~NetworkPeerRemovalLock()
    {
        LeaveCriticalSection(&lock_->critical_section_04);
    }

private:
    CriticalSectionWrapper *lock_;
};

extern "C" __declspec(dllimport) int __stdcall sendto(
    unsigned int socket,
    const char *buffer,
    int size,
    int flags,
    const NetworkPeerAddress16 *destination,
    int destination_size);

struct NetworkWinsockPeerRemovalView {
    NetworkPeerMap::iterator find_peer(const NetworkPeerAddress16 &address);
    void remove_peer(unsigned int slot);

    unsigned char unreviewed_000[0x28];
    unsigned int socket_028;
    unsigned char unreviewed_02c[0x54];
    NetworkPeerRemovalCallbackView *callback_080;
    CriticalSectionWrapper callback_lock_084;
    unsigned char unreviewed_0a0[0x5c];
    NetworkPeerMap peers_0fc;
    std::vector<NetworkPeerRecord20> records_108;
    unsigned int active_count_118;
    unsigned char unreviewed_11c[4];
    CriticalSectionWrapper peer_lock_120;
};

NetworkPeerMap::iterator NetworkWinsockPeerRemovalView::find_peer(
    const NetworkPeerAddress16 &address)
{
    std::pair<NetworkPeerMap::iterator, NetworkPeerMap::iterator> range =
        peers_0fc.equal_range(address.address_04);
    for (NetworkPeerMap::iterator it = range.first; it != range.second; ++it) {
        if (it->second->endpoint_00.port_02 == address.port_02)
            return it;
    }
    return peers_0fc.end();
}

void NetworkWinsockPeerRemovalView::remove_peer(unsigned int slot)
{
    NetworkPeerRemovalLock peer_lock(&peer_lock_120);
    if (records_108[slot].slot_10 != -1) {
        // Only the transmitted opcode byte is established here. The target's
        // larger packet-storage/frame ownership remains an open source question.
        char packet = 11;
        sendto(socket_028, &packet, 1, 0,
               &records_108[slot].endpoint_00, sizeof(NetworkPeerAddress16));
        peers_0fc.erase(find_peer(records_108[slot].endpoint_00));
        records_108[slot].counter_14 = 10;
        records_108[slot].slot_10 = -1;

        NetworkPeerRemovalLock callback_lock(&callback_lock_084);
        if (callback_080)
            callback_080->on_peer_removed(slot);
        --active_count_118;
    }
}

typedef char NetworkPeerAddressSize[sizeof(NetworkPeerAddress16) == 16 ? 1 : -1];
typedef char NetworkPeerRecordSize[sizeof(NetworkPeerRecord20) == 32 ? 1 : -1];
typedef char NetworkPeerMapSize[sizeof(NetworkPeerMap) == 12 ? 1 : -1];
typedef char NetworkPeerVectorSize[
    sizeof(std::vector<NetworkPeerRecord20>) == 16 ? 1 : -1];
typedef char NetworkPeerMapOffset[
    offsetof(NetworkWinsockPeerRemovalView, peers_0fc) == 0xfc ? 1 : -1];
typedef char NetworkPeerRecordsOffset[
    offsetof(NetworkWinsockPeerRemovalView, records_108) == 0x108 ? 1 : -1];
typedef char NetworkPeerCountOffset[
    offsetof(NetworkWinsockPeerRemovalView, active_count_118) == 0x118 ? 1 : -1];
typedef char NetworkPeerLockOffset[
    offsetof(NetworkWinsockPeerRemovalView, peer_lock_120) == 0x120 ? 1 : -1];

} // namespace th105
