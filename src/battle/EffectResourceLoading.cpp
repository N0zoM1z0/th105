#include "battle/PatResourceContracts.hpp"
#include "assets/FileReader.hpp"
#include "ui/Title.hpp"
#include "platform/SystemUtilities.hpp"
#include <deque>
#include <list>
#include <map>
#include <cstring>

extern "C" __declspec(dllimport) int __cdecl wsprintfA(char *, const char *, ...);
namespace th105 {
class EffectFrameData {
public:
    EffectFrameData() {
        // Native temporary clears all 28 bytes, including its just-published vptr.
        std::memset(this, 0, sizeof(*this));
        tag_14 = 0;
        optional_mode_payload_18 = 0;
    }
    virtual ~EffectFrameData() {
        if (optional_mode_payload_18 != 0)
            delete optional_mode_payload_18;
    }
    short field_04, field_06, field_08, field_0a;
    short field_0c, field_0e, field_10, field_12;
    unsigned char tag_14;
    PatOptionalModePayload20 *optional_mode_payload_18;
};
typedef char effect_frame_size[sizeof(EffectFrameData) == 0x1c ? 1 : -1];
struct EffectResourceGroup {
    EffectResourceGroup();
    virtual ~EffectResourceGroup();
    std::vector<EffectFrameData> frames_04;
    unsigned char flag_14;
    EffectResourceGroup *previous_18;
    EffectResourceGroup *next_1c;
};
typedef char effect_group_size[sizeof(EffectResourceGroup) == 0x20 ? 1 : -1];
struct PatFileReaderOwner {
    PatFileReaderOwner();
    ~PatFileReaderOwner();
    bool open(const char *path);
    CFileReader *reader;
};
struct EffectPathService { int split_path(char *, char *, char *); };
extern EffectPathService g_effect_path_service;
// Runtime-only receiver; this view is never constructed or embedded.
struct EffectResourceManagerView { void load_effect_resource(const char *path); };
template<class T> static T &effect_member(void *object, unsigned offset)
{
    return *reinterpret_cast<T *>(static_cast<unsigned char *>(object) + offset);
}
void EffectResourceManagerView::load_effect_resource(const char *path)
{
    PatFileReaderOwner file;
    if (!file.open(path))
        return;
    char directory[260];
    g_effect_path_service.split_path(const_cast<char *>(path), directory, 0);
    unsigned char version;
    short texture_count;
    file.reader->read(&version, 1);
    file.reader->read(&texture_count, 2);
    effect_member<std::vector<unsigned> >(this, 0x64).assign(texture_count, 0u);
    for (int index = 0; index < texture_count; ++index) {
        char filename[128];
        char resource_path[260];
        file.reader->read(filename, 128);
        wsprintfA(resource_path, "%s%s", directory, filename);
        unsigned handle;
        effect_member<std::vector<unsigned> >(this, 0x64).at(index) =
            *g_title_resource_manager.load_texture(&handle, resource_path, 0, 0);
    }
    std::list<int> alias_keys;
    std::list<int> alias_targets;
    int entry_count;
    file.reader->read(&entry_count, 4);
    EffectResourceGroup *chain_root;
    EffectResourceGroup *current;
    for (int entry = 0; entry < entry_count; ++entry) {
        int key;
        file.reader->read(&key, 4);
        switch (key) {
        case -2: {
            EffectResourceGroup *previous = &effect_member<std::deque<EffectResourceGroup> >(this, 0x74).back();
            effect_member<std::deque<EffectResourceGroup> >(this, 0x74).push_back(EffectResourceGroup());
            current = &effect_member<std::deque<EffectResourceGroup> >(this, 0x74).back();
            previous->next_1c = current;
            current->next_1c = chain_root;
            current->previous_18 = previous;
            break;
        }
        case -1: {
            int alias_key;
            int target_key;
            file.reader->read(&alias_key, 4);
            file.reader->read(&target_key, 4);
            alias_keys.push_back(alias_key);
            alias_targets.push_back(target_key);
            continue;
        }
        default: {
            std::map<int, EffectResourceGroup *>::iterator found = effect_member<std::map<int, EffectResourceGroup *> >(this, 0x88).find(key);
            if (found != effect_member<std::map<int, EffectResourceGroup *> >(this, 0x88).end())
                effect_member<std::map<int, EffectResourceGroup *> >(this, 0x88).erase(found);
            effect_member<std::deque<EffectResourceGroup> >(this, 0x74).push_back(EffectResourceGroup());
            current = &effect_member<std::deque<EffectResourceGroup> >(this, 0x74).back();
            current->previous_18 = 0;
            current->next_1c = current;
            chain_root = current;
            effect_member<std::map<int, EffectResourceGroup *> >(this, 0x88).insert(std::pair<int, EffectResourceGroup *>(key, current));
            break;
        }
        }
        file.reader->read(&current->flag_14, 1);
        int frame_count;
        file.reader->read(&frame_count, 4);
        current->frames_04.assign(frame_count, EffectFrameData());
        for (int frame_index = 0; frame_index < frame_count; ++frame_index) {
            EffectFrameData &frame = current->frames_04[frame_index];
            int texture_index;
            file.reader->read(&texture_index, 4);
            frame.field_0a = static_cast<short>(texture_index);
            file.reader->read(&frame.field_0c, 2);
            file.reader->read(&frame.field_0e, 2);
            file.reader->read(&frame.field_10, 2);
            file.reader->read(&frame.field_12, 2);
            file.reader->read(&frame.field_04, 2);
            file.reader->read(&frame.field_06, 2);
            file.reader->read(&frame.field_08, 2);
            file.reader->read(&frame.tag_14, 1);
            if (frame.tag_14 == 2) {
                frame.optional_mode_payload_18 = new PatOptionalModePayload20;
                short mode;
                file.reader->read(&mode, 2);
                switch (mode) {
                case 0: frame.optional_mode_payload_18->mode_00 = 1; break;
                case 1: frame.optional_mode_payload_18->mode_00 = 2; break;
                case 2: frame.optional_mode_payload_18->mode_00 = 3; break;
                }
                file.reader->read(&frame.optional_mode_payload_18->bytes_04[3], 1);
                file.reader->read(&frame.optional_mode_payload_18->bytes_04[2], 1);
                file.reader->read(&frame.optional_mode_payload_18->bytes_04[1], 1);
                file.reader->read(&frame.optional_mode_payload_18->bytes_04[0], 1);
                short value;
                file.reader->read(&value, 2);
                const float shared_scale = static_cast<float>(static_cast<double>(value) / 100.0);
                frame.optional_mode_payload_18->shared_scale_08 = shared_scale;
                frame.optional_mode_payload_18->shared_scale_0c = frame.optional_mode_payload_18->shared_scale_08;
                frame.optional_mode_payload_18->shared_scale_10 = frame.optional_mode_payload_18->shared_scale_0c;
                file.reader->read(&value, 2);
                frame.optional_mode_payload_18->scale_14 = static_cast<float>(value);
                file.reader->read(&value, 2);
                frame.optional_mode_payload_18->scale_18 = static_cast<float>(value);
                file.reader->read(&value, 2);
                frame.optional_mode_payload_18->scale_1c = static_cast<float>(value);
            }
        }
    }
    while (!alias_targets.empty()) {
        std::map<int, EffectResourceGroup *>::iterator found = effect_member<std::map<int, EffectResourceGroup *> >(this, 0x88).find(alias_targets.back());
        if (found != effect_member<std::map<int, EffectResourceGroup *> >(this, 0x88).end())
            effect_member<std::map<int, EffectResourceGroup *> >(this, 0x88).insert(std::pair<int, EffectResourceGroup *>(alias_keys.back(), found->second));
        alias_keys.pop_back();
        alias_targets.pop_back();
    }
}
} // namespace th105
