#include "battle/Collision.hpp"
#include "battle/PatResourceContracts.hpp"
#include "assets/FileReaderOperations.hpp"
#include "ui/Title.hpp"
#include <deque>
#include <list>
#include <map>
#include <vector>
#include "battle/PatGroup.cpp"

extern "C" __declspec(dllimport) int __cdecl wsprintfA(char *, const char *, ...);
extern "C" const unsigned char select_palette_6fa258[];

namespace th105 {

const char *__cdecl character_key_to_name(int character_key);

// Full four-byte owner; each declared operation has a target-observed provider.
struct PatFileReaderOwner {
    PatFileReaderOwner();
    ~PatFileReaderOwner();
    bool open(const char *path);
    CFileReader *reader;
};
typedef char pat_reader_size[sizeof(PatFileReaderOwner) == 4 ? 1 : -1];

struct PatPaletteService {
    void load_palette(const char *path, const unsigned char *config, int format);
};
extern PatPaletteService g_pat_palette_service;

template<class T> static T &pat_member(void *object, unsigned offset)
{
    return *reinterpret_cast<T *>(static_cast<unsigned char *>(object) + offset);
}

void Fighter::load_pat_data_and_palette_resources()
{
    const char *const character = character_key_to_name(record_key_330);
    PatFileReaderOwner file;
    char pat_path[260];
    char filename[128];
    wsprintfA(pat_path, "data/character/%s/%s.pat", character, character);
    if (!file.open(pat_path))
        return;

    unsigned char version;
    short texture_count;
    read_file_buffer(file.reader, &version, 1);
    read_file_buffer(file.reader, &texture_count, 2);
    pat_member<std::vector<unsigned> *>(this, 0x130)->assign(texture_count, 0u);
    wsprintfA(filename, "data/character/%s/palette%03d.bmp", character,
              static_cast<int>(pat_member<signed char>(this, 0x335)));
    g_pat_palette_service.load_palette(filename, select_palette_6fa258, 16);
    for (int index = 0; index < texture_count; ++index) {
        char resource_path[260];
        read_file_buffer(file.reader, filename, 128);
        wsprintfA(resource_path, "data/character/%s/%s", character, filename);
        unsigned handle;
        pat_member<std::vector<unsigned> *>(this, 0x130)->at(index) = *g_title_resource_manager.load_texture(
            &handle, resource_path, 0, 0);
    }

    std::list<int> alias_keys;
    std::list<int> alias_targets;
    int entry_count;
    read_file_buffer(file.reader, &entry_count, 4);
    PatGroup *chain_root;
    PatGroup *current;
    for (int entry = 0; entry < entry_count; ++entry) {
        int key;
        read_file_buffer(file.reader, &key, 4);
        switch (key) {
        case -2: {
            PatGroup *previous = &pat_member<std::deque<PatGroup> >(this, 0x65C).back();
            pat_member<std::deque<PatGroup> >(this, 0x65C).push_back(PatGroup());
            current = &pat_member<std::deque<PatGroup> >(this, 0x65C).back();
            previous->next_1c = current;
            current->next_1c = chain_root;
            current->previous_18 = previous;
            break;
        }
        case -1: {
            int alias_key;
            int target_key;
            read_file_buffer(file.reader, &alias_key, 4);
            read_file_buffer(file.reader, &target_key, 4);
            alias_keys.push_back(alias_key);
            alias_targets.push_back(target_key);
            continue;
        }
        default: {
            std::map<int, PatGroup *>::iterator found = pat_member<std::map<int, PatGroup *> *>(this, 0x160)->find(key);
            if (found != pat_member<std::map<int, PatGroup *> *>(this, 0x160)->end())
                pat_member<std::map<int, PatGroup *> *>(this, 0x160)->erase(found);
            pat_member<std::deque<PatGroup> >(this, 0x65C).push_back(PatGroup());
            current = &pat_member<std::deque<PatGroup> >(this, 0x65C).back();
            current->previous_18 = 0;
            current->next_1c = current;
            chain_root = current;
            pat_member<std::map<int, PatGroup *> *>(this, 0x160)->insert(std::pair<int, PatGroup *>(key, current));
            break;
        }
        }

        read_file_buffer(file.reader, &current->field_10, 2);
        read_file_buffer(file.reader, &current->field_12, 2);
        read_file_buffer(file.reader, &current->field_14, 1);
        int frame_count;
        read_file_buffer(file.reader, &frame_count, 4);
        current->records_00.assign(frame_count, PatRecord88());
        for (int frame_index = 0; frame_index < frame_count; ++frame_index) {
            PatRecord88 &frame = current->records_00[frame_index];
            int texture_index;
            read_file_buffer(file.reader, &texture_index, 4);
            frame.texture_index_bits_0a = static_cast<short>(texture_index);
            read_file_buffer(file.reader, &frame.texture_x_bits_0c, 2);
            read_file_buffer(file.reader, &frame.texture_y_bits_0e, 2);
            read_file_buffer(file.reader, &frame.texture_width_bits_10, 2);
            read_file_buffer(file.reader, &frame.texture_height_bits_12, 2);
            read_file_buffer(file.reader, &frame.pivot_x_bits_04, 2);
            read_file_buffer(file.reader, &frame.pivot_y_bits_06, 2);
            read_file_buffer(file.reader, &frame.duration_bits_08, 2);
            read_file_buffer(file.reader, &frame.tag_14, 1);
            short value;
            if (frame.tag_14 == 2) {
                frame.optional_mode_payload_18 = new PatOptionalModePayload20;
                short mode;
                read_file_buffer(file.reader, &mode, 2);
                switch (mode) {
                case 0: frame.optional_mode_payload_18->mode_00 = 1; break;
                case 1: frame.optional_mode_payload_18->mode_00 = 2; break;
                case 2: frame.optional_mode_payload_18->mode_00 = 3; break;
                }
                read_file_buffer(file.reader, &frame.optional_mode_payload_18->bytes_04[3], 1);
                read_file_buffer(file.reader, &frame.optional_mode_payload_18->bytes_04[2], 1);
                read_file_buffer(file.reader, &frame.optional_mode_payload_18->bytes_04[1], 1);
                read_file_buffer(file.reader, &frame.optional_mode_payload_18->bytes_04[0], 1);
                read_file_buffer(file.reader, &value, 2);
                const float shared_scale = static_cast<float>(static_cast<double>(value) / 100.0);
                frame.optional_mode_payload_18->shared_scale_08 = shared_scale;
                frame.optional_mode_payload_18->shared_scale_0c = frame.optional_mode_payload_18->shared_scale_08;
                frame.optional_mode_payload_18->shared_scale_10 = frame.optional_mode_payload_18->shared_scale_0c;
                read_file_buffer(file.reader, &value, 2);
                frame.optional_mode_payload_18->scale_14 = static_cast<float>(value);
                read_file_buffer(file.reader, &value, 2);
                frame.optional_mode_payload_18->scale_18 = static_cast<float>(value);
                read_file_buffer(file.reader, &value, 2);
                frame.optional_mode_payload_18->scale_1c = static_cast<float>(value);
            }
            read_file_buffer(file.reader, &frame.field_1c, 2);
            read_file_buffer(file.reader, &frame.field_1e, 2);
            read_file_buffer(file.reader, &frame.field_20, 2);
            read_file_buffer(file.reader, &frame.field_22, 2);
            read_file_buffer(file.reader, &frame.field_24, 2);
            read_file_buffer(file.reader, &frame.field_26, 2);
            read_file_buffer(file.reader, &frame.field_28, 2);
            read_file_buffer(file.reader, &frame.field_2a, 2);
            read_file_buffer(file.reader, &frame.field_2c, 2);
            read_file_buffer(file.reader, &frame.field_2e, 2);
            read_file_buffer(file.reader, &frame.field_30, 2);
            read_file_buffer(file.reader, &frame.field_32, 2);
            read_file_buffer(file.reader, &frame.field_34, 2);
            read_file_buffer(file.reader, &frame.field_36, 2);
            read_file_buffer(file.reader, &frame.field_38, 2);
            read_file_buffer(file.reader, &value, 2);
            frame.scaled_3c = static_cast<float>(static_cast<double>(value) / 100.0);
            read_file_buffer(file.reader, &value, 2);
            frame.scaled_40 = static_cast<float>(static_cast<double>(value) / 100.0);
            read_file_buffer(file.reader, &frame.field_44, 2);
            read_file_buffer(file.reader, &frame.field_46, 2);
            read_file_buffer(file.reader, &pat_member<unsigned short>(&frame, 0x48), 2);
            read_file_buffer(file.reader, &frame.field_49, 1);
            read_file_buffer(file.reader, &frame.flags_4c, 4);
            read_file_buffer(file.reader, &frame.field_50, 4);
            signed char count;
            read_file_buffer(file.reader, &count, 1);
            if (count != 0) {
                frame.primary_collision_box_54 = new PatRaw16;
                read_file_buffer(file.reader, frame.primary_collision_box_54, 16);
            }
            read_file_buffer(file.reader, &count, 1);
            frame.group_b_collision_boxes_58.assign(count, PatRaw16());
            for (int index = 0; index < count; ++index) {
                read_file_buffer(file.reader, &frame.group_b_collision_boxes_58[index], 16);
                // Preserve the observed second checked access after the reader callback.
                frame.group_b_collision_boxes_58[index];
            }
            read_file_buffer(file.reader, &count, 1);
            frame.group_a_collision_boxes_68.assign(count, PatRaw16());
            frame.group_a_descriptors_78.assign(count, static_cast<PatRaw16 *>(0));
            for (int index = 0; index < count; ++index) {
                read_file_buffer(file.reader, &frame.group_a_collision_boxes_68[index], 16);
                signed char has_pointer;
                read_file_buffer(file.reader, &has_pointer, 1);
                if (has_pointer != 0) {
                    frame.group_a_descriptors_78[index] = new PatRaw16;
                    read_file_buffer(file.reader, frame.group_a_descriptors_78[index], 16);
                }
            }
            if ((frame.flags_4c & 0x01000000u) != 0)
                frame.group_b_collision_boxes_58 = frame.group_a_collision_boxes_68;
        }
    }
    while (!alias_targets.empty()) {
        std::map<int, PatGroup *>::iterator found = pat_member<std::map<int, PatGroup *> *>(this, 0x160)->find(alias_targets.back());
        if (found != pat_member<std::map<int, PatGroup *> *>(this, 0x160)->end())
            pat_member<std::map<int, PatGroup *> *>(this, 0x160)->insert(std::pair<int, PatGroup *>(alias_keys.back(), found->second));
        alias_keys.pop_back();
        alias_targets.pop_back();
    }
}

} // namespace th105
