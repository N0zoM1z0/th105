#include "NetworkUdpPacketPool.hpp"
#include "assets/ResourceHandleManager.hpp"
#include <string.h>

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
