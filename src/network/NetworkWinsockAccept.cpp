#include "engine/CriticalSectionWrapper.hpp"

namespace th105 {
struct NetworkAcceptAddress16 {
    unsigned int words[4];
};
#pragma pack(push, 1)
struct NetworkAcceptPacketHeader0C {
    unsigned int unreviewed_00;
    unsigned int code_04;
    unsigned short size_08;
    unsigned short unreviewed_0a;
};
#pragma pack(pop)
class NetworkAcceptCallbackView {
public:
    virtual void on_accepted(unsigned int code, const void *payload, unsigned int size);
};
class NetworkAcceptLock {
public:
    explicit NetworkAcceptLock(CriticalSectionWrapper *lock) : lock_(lock)
    {
        EnterCriticalSection(&lock_->critical_section_04);
    }
    ~NetworkAcceptLock()
    {
        LeaveCriticalSection(&lock_->critical_section_04);
    }
private:
    CriticalSectionWrapper *lock_;
};
struct NetworkUdpAcceptView {
    unsigned char unreviewed_000[0x80];
    NetworkAcceptCallbackView *callback_080;
    CriticalSectionWrapper callback_lock_084;
    unsigned char unreviewed_0a0[0x20];
    NetworkAcceptAddress16 endpoint_0c0;
    unsigned char unreviewed_0d0[4];
    unsigned int probe_count_0d4;
    unsigned char unreviewed_0d8[8];
    CriticalSectionWrapper endpoint_lock_0e0;
    unsigned char unreviewed_0fc[0x48];
    unsigned int state_144;
};

void __fastcall network_udp_accept(const NetworkAcceptAddress16 *sender,
    NetworkUdpAcceptView *owner, const NetworkAcceptPacketHeader0C *packet)
{
    if (owner->state_144 == 3) {
        NetworkAcceptLock endpoint_lock(&owner->endpoint_lock_0e0);
        owner->endpoint_0c0 = *sender;
        owner->probe_count_0d4 = 0;
        NetworkAcceptLock callback_lock(&owner->callback_lock_084);
        if (owner->callback_080)
            owner->callback_080->on_accepted(packet->code_04, packet + 1, packet->size_08);
        owner->state_144 = 0;
    }
}

typedef char AcceptHeaderSize[sizeof(NetworkAcceptPacketHeader0C) == 12 ? 1 : -1];
typedef char AcceptCallbackOffset[offsetof(NetworkUdpAcceptView, callback_080) == 0x80 ? 1 : -1];
typedef char AcceptCallbackLockOffset[offsetof(NetworkUdpAcceptView, callback_lock_084) == 0x84 ? 1 : -1];
typedef char AcceptEndpointOffset[offsetof(NetworkUdpAcceptView, endpoint_0c0) == 0xc0 ? 1 : -1];
typedef char AcceptProbeOffset[offsetof(NetworkUdpAcceptView, probe_count_0d4) == 0xd4 ? 1 : -1];
typedef char AcceptEndpointLockOffset[offsetof(NetworkUdpAcceptView, endpoint_lock_0e0) == 0xe0 ? 1 : -1];
typedef char AcceptStateOffset[offsetof(NetworkUdpAcceptView, state_144) == 0x144 ? 1 : -1];
} // namespace th105
