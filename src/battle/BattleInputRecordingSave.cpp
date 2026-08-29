#include "assets/FileReader.hpp"

#include <deque>
#include <time.h>
#include <vector>

namespace th105 {

typedef std::deque<short> ReplaySidePayload;

struct ReplayFixedBattleSetupSlot {
    unsigned char side_value_lo_00[2];
    unsigned char side_byte_05_02[2];
    unsigned char side_byte_06_04[2];
    unsigned char side_byte_04_06[2];
    ReplaySidePayload payload_08[2];
    unsigned char token_tag_30[2];
    unsigned char tail_32;
    unsigned char tail_33;
    unsigned char tail_34;
    unsigned char padding_35[3];
    unsigned tail_dword_38;
};

struct ReplayFileWriterView {
    virtual ~ReplayFileWriterView();
    virtual bool write(const void *source, unsigned long size) = 0;
};

struct ReplayFixedSlotEnvelope {
    ReplayFixedBattleSetupSlot setup_00;
    ReplaySidePayload private_payload_3c;

    void serialize_fixed_slot_envelope(ReplayFileWriterView *writer);
};

struct ReplayInputStorageSaveView {
    void *input_a_000;
    void *input_b_004;
    unsigned char unknown_008[0xe0];
    unsigned char recording_header_0e8[10];
    unsigned char unknown_0f2[2];
    std::vector<ReplayFixedSlotEnvelope> slots_0f4;
    void *selected_slot_104;
    unsigned char unknown_108[0x38];
    unsigned char displayed_slot_140;

    void save_replay_428d90(const char *path);
};

extern "C" int __cdecl get_current_replay_header_code();

typedef char ReplayFixedSlotEnvelope_size_must_be_0x50[
    sizeof(ReplayFixedSlotEnvelope) == 0x50 ? 1 : -1];
typedef char ReplayInputStorageSave_slots_offset_must_be_0xf4[
    offsetof(ReplayInputStorageSaveView, slots_0f4) == 0xf4 ? 1 : -1];
typedef char ReplayInputStorageSave_displayed_offset_must_be_0x140[
    offsetof(ReplayInputStorageSaveView, displayed_slot_140) == 0x140 ? 1 : -1];

void ReplayInputStorageSaveView::save_replay_428d90(const char *path)
{
    CFileWriter writer(path);

    int header_code = get_current_replay_header_code();
    writer.write(&header_code, sizeof(header_code));

    __time64_t current_time;
    struct tm local_time;
    _time64(&current_time);
    _localtime64_s(&local_time, &current_time);

    unsigned char month = static_cast<unsigned char>(local_time.tm_mon + 1);
    unsigned char slot_count = static_cast<unsigned char>(displayed_slot_140 + 1);
    recording_header_0e8[3] = static_cast<unsigned char>(local_time.tm_mday);
    recording_header_0e8[2] = month;
    recording_header_0e8[7] = slot_count;
    recording_header_0e8[8] = static_cast<unsigned char>(
        2 * (input_b_004 != 0) + (input_a_000 != 0));

    writer.write(recording_header_0e8, sizeof(recording_header_0e8));

    for (int slot = 0;
         slot < static_cast<signed char>(recording_header_0e8[7]);
         ++slot) {
        slots_0f4[slot].serialize_fixed_slot_envelope(
            reinterpret_cast<ReplayFileWriterView *>(&writer));
    }
}

} // namespace th105
