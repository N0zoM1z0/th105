#include "assets/FileReader.hpp"
#include "assets/String28.hpp"

#include <cstring>
#include <deque>
#include <new>
#include <vector>

extern "C" __declspec(dllimport) int __stdcall CloseHandle(void *handle);
extern "C" __declspec(dllimport) int __stdcall ReadFile(
    void *file,
    void *buffer,
    unsigned long bytes_to_read,
    unsigned long *bytes_read,
    void *overlapped);
extern "C" __declspec(dllimport) void *__stdcall CreateFileA(
    const char *path,
    unsigned long access,
    unsigned long share_mode,
    void *security_attributes,
    unsigned long creation_disposition,
    unsigned long flags,
    void *template_file);

namespace th105 {

struct FileReader {
    virtual ~FileReader();
    virtual bool read(void *destination, unsigned long size) = 0;
};

typedef std::deque<short> SidePayload;

// The target keeps these two checked-string operations out of line at
// 0x004021C0 and 0x00408950.  The gate preserves their __thiscall ABI while
// String28 itself retains the real VC8 owning layout and destructor.
struct String28CallGate {
    void assign(const char *source, unsigned source_size);
    void append(const char *source, unsigned source_size);
};

static String28CallGate *string_gate(String28 *value)
{
    return reinterpret_cast<String28CallGate *>(value);
}

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

// This value is deliberately a call rather than an inlined literal.  The
// target obtains the recording-format marker through a one-instruction helper
// at 0x00439660.
unsigned __cdecl battle_input_recording_format_marker();

// The surrounding BattleInputGate ownership is still being recovered.  This
// view records only fields read or written by 0x0042B6C0; it agrees with the
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

// CFileReader has the target's three-word polymorphic layout.  The local is
// deliberately placement-constructed so the compiler emits its authentic
// vtable initialization while this routine retains the target's explicit
// CloseHandle ownership paths.
struct CFileReaderAccess {
    void *vtable_00;
    FileHandle file_04;
    FileSize bytes_read_08;
};

typedef char CFileReader_size_must_be_0x0c[
    sizeof(CFileReader) == 0x0c ? 1 : -1];

bool BattleInputRecordingView::load_battle_input_recording(const char *path)
{
    String28 open_path;
    string_gate(&open_path)->assign("", 0);
    string_gate(&open_path)->append(path, std::strlen(path));
    BattleInputRecordingView *recording = this;

    unsigned char reader_storage[sizeof(CFileReader)];
    CFileReader *reader = new (reader_storage) CFileReader;
    CFileReaderAccess *reader_access =
        reinterpret_cast<CFileReaderAccess *>(reader);
    reader_access->file_04 = CreateFileA(
        open_path.c_str(),
        0x80000000,
        1,
        0,
        3,
        0x80,
        0);
    if (reader_access->file_04 == reinterpret_cast<FileHandle>(-1))
        reader_access->file_04 = 0;

    if (reader_access->file_04 == 0) {
        string_gate(&recording->source_path_108)->assign("", 0);
        return false;
    }

    string_gate(&recording->source_path_108)->assign(path, std::strlen(path));

    unsigned recording_format_marker;
    ReadFile(
        reader_access->file_04,
        &recording_format_marker,
        sizeof(recording_format_marker),
        &reader_access->bytes_read_08,
        0);
    if (recording_format_marker != battle_input_recording_format_marker()) {
        string_gate(&recording->source_path_108)->assign("", 0);
        CloseHandle(reader_access->file_04);
        return false;
    }

    ReadFile(
        reader_access->file_04,
        recording->recording_header_0e8,
        sizeof(recording->recording_header_0e8),
        &reader_access->bytes_read_08,
        0);
    recording->displayed_slot_140 =
        static_cast<unsigned char>(recording->recording_header_0e8[7] - 1);

    recording->slots_0f4.clear();
    FixedSlotEnvelope default_slot = FixedSlotEnvelope();
    recording->slots_0f4.assign(
        static_cast<signed char>(recording->recording_header_0e8[7]),
        default_slot);

    for (int slot = 0;
         slot < static_cast<signed char>(recording->recording_header_0e8[7]);
         ++slot) {
        if (!recording->slots_0f4[slot].deserialize_fixed_slot_envelope(
                reinterpret_cast<FileReader *>(reader))) {
            CloseHandle(reader_access->file_04);
            return false;
        }
    }

    recording->sequence_ready_06c = 1;
    recording->sequence_068 = 0;
    recording->frame_ready_0d4 = 1;
    recording->frame_0d0 = 0;
    CloseHandle(reader_access->file_04);
    return true;
}

} // namespace th105
