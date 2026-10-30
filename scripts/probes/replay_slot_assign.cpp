// Library-origin evidence only: preserve the independently exact VC8 vector
// assignment fingerprint. The byte-wise serialized view is not the loader
// local aggregate, whose paired scalar fields are recovered separately.
#include <deque>
#include <vector>
namespace th105 {
struct FileReader;
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

    bool deserialize_fixed_slot_envelope(FileReader *reader);
};

void instantiate_replay_slot_assign(std::vector<FixedSlotEnvelope> &slots, unsigned count)
{
    FixedSlotEnvelope value = FixedSlotEnvelope();
    slots.assign(count, value);
}
}
