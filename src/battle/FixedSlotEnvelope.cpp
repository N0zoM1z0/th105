#include <deque>

namespace th105 {

struct FixedBattleSetupSlotView {
    unsigned char side_value_lo_00[2];
    unsigned char side_byte_05_02[2];
    unsigned char side_byte_06_04[2];
    unsigned char side_byte_04_06[2];
    std::deque<short> payload_08[2];
    unsigned char token_tag_30[2];
    unsigned char tail_32;
    unsigned char tail_33;
    unsigned char tail_34;
    unsigned char padding_35[3];
    unsigned tail_dword_38;
};

struct FixedSlotEnvelopeView {
    FixedBattleSetupSlotView setup_00;
    std::deque<short> private_payload_3c;

    FixedSlotEnvelopeView &operator=(const FixedSlotEnvelopeView &source);
};

FixedSlotEnvelopeView &FixedSlotEnvelopeView::operator=(
    const FixedSlotEnvelopeView &source)
{
    setup_00.side_value_lo_00[0] = source.setup_00.side_value_lo_00[0];
    setup_00.side_value_lo_00[1] = source.setup_00.side_value_lo_00[1];
    setup_00.side_byte_05_02[0] = source.setup_00.side_byte_05_02[0];
    setup_00.side_byte_05_02[1] = source.setup_00.side_byte_05_02[1];
    setup_00.side_byte_06_04[0] = source.setup_00.side_byte_06_04[0];
    setup_00.side_byte_06_04[1] = source.setup_00.side_byte_06_04[1];
    setup_00.side_byte_04_06[0] = source.setup_00.side_byte_04_06[0];
    setup_00.side_byte_04_06[1] = source.setup_00.side_byte_04_06[1];
    for (int side = 0; side < 2; ++side) {
        setup_00.payload_08[side] = source.setup_00.payload_08[side];
    }
    setup_00.token_tag_30[0] = source.setup_00.token_tag_30[0];
    setup_00.token_tag_30[1] = source.setup_00.token_tag_30[1];
    setup_00.tail_32 = source.setup_00.tail_32;
    setup_00.tail_33 = source.setup_00.tail_33;
    setup_00.tail_34 = source.setup_00.tail_34;
    setup_00.tail_dword_38 = source.setup_00.tail_dword_38;
    private_payload_3c = source.private_payload_3c;
    return *this;
}

} // namespace th105
