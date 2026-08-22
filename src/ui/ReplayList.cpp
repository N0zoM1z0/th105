#include "FileList.hpp"

namespace th105 {

extern const char replay_list_pattern[];
extern const char replay_extension_pattern[];
extern const char replay_directory_name[];

struct ReplayListStringAssignBytesView {
    std::string *assign_bytes(const char *source, unsigned int length);
};

struct ReplayListStringAssignCopyView {
    void assign_copy(
        const std::string &source,
        unsigned int offset,
        unsigned int count);
};

struct ReplayHeaderServiceView {
    int read_header_code(const char *path);
};

extern ReplayHeaderServiceView *get_replay_header_service();
extern int get_current_replay_header_code();
extern "C" __declspec(dllimport) int __cdecl wsprintfA(
    char *buffer, const char *format, ...);

CReplayList::CReplayList()
{
    reinterpret_cast<ReplayListStringAssignBytesView *>(&path_054)
        ->assign_bytes(replay_list_pattern, 12);
    reinterpret_cast<ReplayListStringAssignBytesView *>(&path_054)
        ->assign_bytes(replay_extension_pattern, 5);
    std::string *directory =
        reinterpret_cast<ReplayListStringAssignBytesView *>(&directory_08c)
            ->assign_bytes(replay_directory_name, 6);
    reinterpret_cast<ReplayListStringAssignCopyView *>(&filter_070)
        ->assign_copy(*directory, 0, static_cast<unsigned int>(-1));
    field_a8 = 96;
    field_b0 = 1;
}

unsigned int CReplayList::format_item(
    std::string *output,
    std::deque<std::string>::iterator current)
{
    std::string value = *current;
    unsigned int index = current - rows_004.begin();
    if (flags_018[index]) {
        output->append("<color 40FF40>", 14);
        output->append(value, 0, static_cast<unsigned int>(-1));
        output->append("</color>", 8);
    } else {
        char path[260];
        wsprintfA(path, "%s/%s", directory_08c.c_str(), value.c_str());
        if (get_replay_header_service()->read_header_code(path) !=
            get_current_replay_header_code()) {
            output->append("<color 404040>", 14);
            trim_item_text(&value);
            output->append(value, 0, static_cast<unsigned int>(-1));
            output->append("</color>", 8);
        } else {
            trim_item_text(&value);
            output->append(value, 0, static_cast<unsigned int>(-1));
        }
    }
    return value.size();
}

} // namespace th105
