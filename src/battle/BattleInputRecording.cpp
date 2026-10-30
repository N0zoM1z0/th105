#include "assets/FileReader.cpp"
#include "assets/FileReader.hpp"
#include "assets/String28.hpp"

#include <cstring>
#include <deque>
#include <vector>

namespace th105 {

struct FileReader {
    virtual ~FileReader();
    virtual bool read(void *destination, unsigned long size) = 0;
};

typedef std::deque<short> SidePayload;

// The current target retains string assign4021C0 out of line. The call view
// preserves that ordinary method boundary; String28 owns its real storage.
struct String28CallGate {
    void assign(const char *source, unsigned source_size);
};

static String28CallGate *string_gate(String28 *value)
{
    return reinterpret_cast<String28CallGate *>(value);
}

// Paired scalar words agree with BattleInputSlotConfig and slot-copy stores.
// The deserializer reads their component bytes; these are not C byte arrays.
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

    bool deserialize_fixed_slot_envelope(FileReader *reader);
};

// This value is deliberately a call rather than an inlined literal.  The
// target obtains the recording-format marker through a constant-return helper
// at 0x0043AA40.
unsigned __cdecl battle_input_recording_format_marker();

// The surrounding BattleInputGate ownership is still being recovered.  This
// view records only fields read or written by 0x0042C5C0; it agrees with the
// independently observed slot-vector and source-path offsets.
struct BattleInputRecordingView {
    unsigned char unknown_000[0x68];
    unsigned short sequence_068;
    unsigned char unknown_06a[2];
    unsigned char sequence_ready_06c;
    unsigned char unknown_06d[0x63];
    unsigned short frame_0d0;
    unsigned char unknown_0d2[2];
    unsigned char frame_ready_0d4;
    unsigned char unknown_0d5[0x13];
    unsigned char recording_header_0e8[10];
    unsigned char unknown_0f2[2];
    std::vector<FixedSlotEnvelope> slots_0f4;
    void *selected_slot_104;
    String28 source_path_108;
    unsigned char unknown_124[0x1c];
    unsigned char displayed_slot_140;

    bool load_battle_input_recording(const char *path);
};

typedef char BattleInputRecordingView_slots_offset_must_be_0x0f4[
    offsetof(BattleInputRecordingView, slots_0f4) == 0x0f4 ? 1 : -1];
typedef char BattleInputRecordingView_source_path_offset_must_be_0x108[
    offsetof(BattleInputRecordingView, source_path_108) == 0x108 ? 1 : -1];
typedef char BattleInputRecordingView_displayed_slot_offset_must_be_0x140[
    offsetof(BattleInputRecordingView, displayed_slot_140) == 0x140 ? 1 : -1];

// Read-only handle view for the concrete reader's open test. Construction,
// reads and all normal/exception cleanup belong to the real CFileReader.
struct CFileReaderAccess {
    void *vtable_00;
    FileHandle file_04;
    FileSize bytes_read_08;
};

typedef char FixedSlotEnvelope_size_must_be_0x50[sizeof(FixedSlotEnvelope)==0x50?1:-1];
typedef char CFileReader_size_must_be_0x0c[
    sizeof(CFileReader) == 0x0c ? 1 : -1];

bool BattleInputRecordingView::load_battle_input_recording(const char *path)
{
    String28 open_path("");
    open_path.append(path, std::strlen(path));
    CFileReader reader(open_path.c_str());
    if (reinterpret_cast<CFileReaderAccess *>(&reader)->file_04 == 0) {
        string_gate(&source_path_108)->assign("", 0u);
        return false;
    }
    string_gate(&source_path_108)->assign(path, std::strlen(path));
    unsigned marker;
    reader.read(&marker, 4);
    if (marker != battle_input_recording_format_marker()) {
        string_gate(&source_path_108)->assign("", 0u);
        return false;
    }
    reader.read(recording_header_0e8, 10);
    displayed_slot_140 = static_cast<unsigned char>(recording_header_0e8[7] - 1);
    slots_0f4.clear();
    {
        FixedSlotEnvelope default_slot;
        slots_0f4.assign(static_cast<signed char>(recording_header_0e8[7]), default_slot);
    }
    for (int slot = 0; slot < static_cast<signed char>(recording_header_0e8[7]); ++slot) {
        if (!slots_0f4[slot].deserialize_fixed_slot_envelope(reinterpret_cast<FileReader *>(&reader)))
            return false;
    }
    sequence_ready_06c = 1;
    sequence_068 = 0;
    frame_ready_0d4 = 1;
    frame_0d0 = 0;
    return true;
}
} // namespace th105
