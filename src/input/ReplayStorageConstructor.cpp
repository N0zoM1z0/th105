#include "ui/ProfileMenuBaseDataLifetime.hpp"
#include "engine/CriticalSectionWrapper.hpp"
#include <deque>
#include <string>
#include <vector>

namespace th105 {
typedef ProfileInputManagerExLifetime ReplayInjectedInput;
struct ReplayStorageSlot {
    unsigned char side_fields_00[8];
    std::deque<short> side_payloads_08[2];
    unsigned char tags_30[5];
    unsigned tail_38;
    std::deque<short> private_payload_3c;
};
struct ReplayStorageLifetime {
    ProfileInputManagerLifetime *input_00;
    ProfileInputManagerLifetime *input_04;
    ReplayInjectedInput injected_08[2];
    ProfileInputManagerLifetime *selected_0d8;
    unsigned unknown_0dc;
    ProfileInputManagerLifetime *selected_0e0;
    unsigned unknown_0e4;
    unsigned char header_0e8[10];
    std::vector<ReplayStorageSlot> slots_0f4;
    ReplayStorageSlot *selected_slot_104;
    std::string filename_108;
    CriticalSectionWrapper lock_124;

    ReplayStorageLifetime();
};
typedef char ReplayInjectedInput_size[sizeof(ReplayInjectedInput)==0x68?1:-1];
typedef char ReplayStorageSlot_size[sizeof(ReplayStorageSlot)==0x50?1:-1];
typedef char ReplayStorage_slots_offset[offsetof(ReplayStorageLifetime,slots_0f4)==0xf4?1:-1];
typedef char ReplayStorage_lock_offset[offsetof(ReplayStorageLifetime,lock_124)==0x124?1:-1];
ReplayStorageLifetime::ReplayStorageLifetime()
{
    selected_0e0 = &injected_08[1];
    selected_0d8 = &injected_08[0];
}
}
