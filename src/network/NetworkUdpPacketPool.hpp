#pragma once

#include "engine/CriticalSectionWrapper.hpp"

#include <deque>
#include <list>
#include <vector>

namespace th105 {

struct ResourceHandleToken;

// RTTI names the original payload NET_PACKET_UDP_BUFFER. Slot allocation
// zeroes0x41C bytes; send paths write the opcode at+1C and payload at+1D.
struct NetworkUdpPacketBuffer41C {
    unsigned char endpoint_00[16];
    unsigned int timestamp_10;
    unsigned int options_14;
    unsigned int size_18;
    unsigned char payload_1c[1024];
};

class NetworkUdpPacketCriticalSectionView {
public:
    NetworkUdpPacketCriticalSectionView()
    {
        InitializeCriticalSection(&critical_section_04);
    }

    virtual ~NetworkUdpPacketCriticalSectionView()
    {
        DeleteCriticalSection(&critical_section_04);
    }

    Win32CriticalSection24 critical_section_04;
};

// Method-focused view of CHandleManager<NET_PACKET_UDP_BUFFER>.
// The owner's event at+1E0 follows this0x64-byte member at+17C.
class NetworkUdpPacketHandleManager64 {
public:
    NetworkUdpPacketHandleManager64();
    virtual ~NetworkUdpPacketHandleManager64();
    NetworkUdpPacketBuffer41C *acquire(ResourceHandleToken &token);
    void release(unsigned int packed_token);

    std::deque<NetworkUdpPacketBuffer41C> packets_04;
    std::vector<NetworkUdpPacketBuffer41C *> slots_18;
    std::vector<unsigned int> generations_28;
    std::list<unsigned int> free_slots_38;
    unsigned int generation_44;
    NetworkUdpPacketCriticalSectionView critical_48;
};

typedef char NetworkUdpPacketSize[
    sizeof(NetworkUdpPacketBuffer41C) == 0x41c ? 1 : -1];
typedef char NetworkUdpPacketPayloadOffset[
    offsetof(NetworkUdpPacketBuffer41C, payload_1c) == 0x1c ? 1 : -1];
typedef char NetworkUdpPacketPoolSize[
    sizeof(NetworkUdpPacketHandleManager64) == 0x64 ? 1 : -1];
typedef char NetworkUdpPacketPoolSlotsOffset[
    offsetof(NetworkUdpPacketHandleManager64, slots_18) == 0x18 ? 1 : -1];
typedef char NetworkUdpPacketPoolGenerationOffset[
    offsetof(NetworkUdpPacketHandleManager64, generations_28) == 0x28 ? 1 : -1];
typedef char NetworkUdpPacketPoolFreeSlotsOffset[
    offsetof(NetworkUdpPacketHandleManager64, free_slots_38) == 0x38 ? 1 : -1];
typedef char NetworkUdpPacketPoolLockOffset[
    offsetof(NetworkUdpPacketHandleManager64, critical_48) == 0x48 ? 1 : -1];

} // namespace th105
