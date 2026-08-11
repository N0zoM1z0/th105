#include <deque>
#include <vector>

namespace th105 {

typedef std::deque<short> SidePayload;

struct FixedBattleSetupSlot {
    unsigned char side_value_lo_00[2];
    unsigned char side_byte_05_02[2];
    unsigned char side_byte_06_04[2];
    unsigned char side_byte_04_06[2];
    SidePayload payload_08[2];
    unsigned char token_tag_30[2];
    unsigned char tail_32;
    unsigned char tail_33;
    unsigned char tail_34;
    unsigned char padding_35[3];
    unsigned tail_dword_38;
};

struct FixedSlotEnvelope {
    FixedBattleSetupSlot setup_00;
    SidePayload private_payload_3c;
};

} // namespace th105

// Force the native VC8 checked-vector specializations used by the battle
// setup/input fixed-slot owner. FixedSlotEnvelope is 0x50 bytes and owns three
// std::deque<short> members.
template class std::vector<th105::FixedSlotEnvelope>;
