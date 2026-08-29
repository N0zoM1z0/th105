#include <deque>

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

// The binary writer is consumed only through vtable slot +0x04 here.  The
// concrete file owner and its handle lifetime stay in the replay save path.
struct FileWriter {
    virtual ~FileWriter();
    virtual bool write(const void *source, unsigned long size) = 0;
};

struct FixedSlotEnvelope {
    FixedBattleSetupSlot setup_00;
    SidePayload private_payload_3c;

    void serialize_fixed_slot_envelope(FileWriter *writer);
};

void FixedSlotEnvelope::serialize_fixed_slot_envelope(FileWriter *writer)
{
    unsigned payload_count;

    for (int side = 0; side < 2; ++side) {
        writer->write(&setup_00.side_value_lo_00[side], 1);
        writer->write(&setup_00.side_byte_05_02[side], 1);

        payload_count = setup_00.payload_08[side].size();
        writer->write(&payload_count, 4);
        SidePayload::iterator value = setup_00.payload_08[side].begin();
        SidePayload::iterator end = setup_00.payload_08[side].end();
        for (; value != end; ++value) {
            writer->write(&*value, 2);
        }

        writer->write(&setup_00.side_byte_04_06[side], 1);
        writer->write(&setup_00.side_byte_06_04[side], 1);
        writer->write(&setup_00.token_tag_30[side], 1);
    }

    writer->write(&setup_00.tail_32, 1);
    writer->write(&setup_00.tail_33, 1);
    writer->write(&setup_00.tail_34, 1);
    writer->write(&setup_00.tail_dword_38, 4);

    payload_count = private_payload_3c.size();
    writer->write(&payload_count, 4);
    SidePayload::iterator value = private_payload_3c.begin();
    SidePayload::iterator end = private_payload_3c.end();
    for (; value != end; ++value) {
        writer->write(&*value, 2);
    }
}

} // namespace th105
