#include <deque>
#include <vector>

namespace th105 {

typedef std::deque<short> SidePayload;

struct FixedBattleSetupSlot {
    unsigned short side_value_lo_00;
    unsigned short side_byte_05_02;
    unsigned short side_byte_06_04;
    unsigned short side_byte_04_06;
    SidePayload payload_08[2];
    unsigned short token_tag_30;
    unsigned char tail_32;
    unsigned char tail_33;
    unsigned tail_34_and_padding;
    unsigned tail_dword_38;
};

struct FixedSlotEnvelope {
    FixedBattleSetupSlot setup_00;
    SidePayload private_payload_3c;
};

struct BattleInputSlotConfigView {
    unsigned char unknown_000[0xec];
    signed char game_mode_0ec;
    unsigned char unknown_0ed[7];
    std::vector<FixedSlotEnvelope> slots_0f4;
    unsigned char unknown_104[0x3c];
    unsigned char published_140;

    void configure_session_input_slots(
        signed char slot_count,
        signed char game_mode);
};

typedef char FixedSlotEnvelope_size_must_be_0x50[
    sizeof(FixedSlotEnvelope) == 0x50 ? 1 : -1];
typedef char BattleInputSlotConfigView_slots_offset_must_be_0x0f4[
    offsetof(BattleInputSlotConfigView, slots_0f4) == 0x0f4 ? 1 : -1];
typedef char BattleInputSlotConfigView_published_offset_must_be_0x140[
    offsetof(BattleInputSlotConfigView, published_140) == 0x140 ? 1 : -1];

void BattleInputSlotConfigView::configure_session_input_slots(
    signed char slot_count,
    signed char game_mode)
{
    if (slot_count > 0) {
        game_mode_0ec = game_mode;
        published_140 = 0;
        slots_0f4.erase(slots_0f4.begin(), slots_0f4.end());

        FixedSlotEnvelope default_slot = FixedSlotEnvelope();
        slots_0f4.assign(slot_count, default_slot);
    }
}

} // namespace th105
