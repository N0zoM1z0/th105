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

// The binary reader is consumed only through vtable slot +0x04 here.  Its
// concrete CFileReader/CPackageFileReader ownership stays in assets.
struct FileReader {
    virtual ~FileReader();
    virtual bool read(void *destination, unsigned long size) = 0;
};

struct FixedSlotEnvelope {
    FixedBattleSetupSlot setup_00;
    SidePayload private_payload_3c;

    bool deserialize_fixed_slot_envelope(FileReader *reader);
};

bool FixedSlotEnvelope::deserialize_fixed_slot_envelope(FileReader *reader)
{
    unsigned payload_count;
    unsigned short serialized_value;

    for (int side = 0; side < 2; ++side) {
        reader->read(&setup_00.side_value_lo_00[side], 1);
        reader->read(&setup_00.side_byte_05_02[side], 1);
        reader->read(&payload_count, 4);
        if (payload_count > 0x14)
            return false;

        for (unsigned index = 0; index < payload_count; ++index) {
            reader->read(&serialized_value, 2);
            setup_00.payload_08[side].push_back(
                static_cast<short>(serialized_value));
        }

        reader->read(&setup_00.side_byte_04_06[side], 1);
        reader->read(&setup_00.side_byte_06_04[side], 1);
        reader->read(&setup_00.token_tag_30[side], 1);
    }

    reader->read(&setup_00.tail_32, 1);
    reader->read(&setup_00.tail_33, 1);
    reader->read(&setup_00.tail_34, 1);
    reader->read(&setup_00.tail_dword_38, 4);
    reader->read(&payload_count, 4);

    private_payload_3c.clear();
    if (payload_count > 0x40000000)
        return false;

    for (unsigned index = 0; index < payload_count; ++index) {
        reader->read(&serialized_value, 2);
        private_payload_3c.push_back(
            reinterpret_cast<short const &>(serialized_value));
    }
    return true;
}

} // namespace th105
