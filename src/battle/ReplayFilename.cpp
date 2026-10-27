#include <windows.h>
#include <string>
#include <ctime>

namespace th105 {
struct ConnectConfigIniView {
    char path_buffer_000[260];
    bool has_file_40f0b0(const char *path);
    unsigned int read_uint_40f100(const char *section, const char *key);
    unsigned long read_string_40f120(const char *section, const char *key, char *output, unsigned long size);
};
extern ConnectConfigIniView g_connect_config_ini;
const char *__cdecl character_key_to_name(int);
struct ReplayFilenameSlot { signed char character_00[2]; };
struct ReplayFilenameSlots { ReplayFilenameSlot *select_slot_4284c0(int index); };
class ReplayFilenameFile {
public:
    explicit ReplayFilenameFile(const char *path) {
        handle = CreateFileA(path, 1, 1, 0, 3, 0x80, 0);
        if (handle == INVALID_HANDLE_VALUE) handle = 0;
    }
    virtual ~ReplayFilenameFile() { if (handle) CloseHandle(handle); }
    virtual bool read(void *out, unsigned long count) { return ReadFile(handle, out, count, &last_count, 0) != 0; }
    virtual unsigned long last_read_size() const { return last_count; }
    virtual long seek(long offset, int origin) { return SetFilePointer(handle, offset, 0, origin); }
    virtual unsigned long size() const { return GetFileSize(handle, 0); }
    HANDLE handle;
    unsigned long last_count;
};
// Only the flag and slot-store receiver are accessed; never instantiate this view.
struct ReplayFilenameView {
    unsigned char unknown_000[0xec];
    unsigned char versus_ec;
    void expand_pattern_429b70(std::string *out, const char *key, const char *first, const char *second);
    int build_filename_42a560(char *out, const char *first, const char *second);
};

int ReplayFilenameView::build_filename_42a560(char *out, const char *first, const char *second)
{
    std::string directory("Replay");
    std::string name("");
    std::string suffix(".rep");
    bool use_default = true;
    char buffer[260];
    if (g_connect_config_ini.has_file_40f0b0("configex.ini")) {
        if (!versus_ec)
            expand_pattern_429b70(&name, "file_story", first, second);
        else
            expand_pattern_429b70(&name, "file_vs", first, second);
        if (!name.empty()) use_default = false;
        expand_pattern_429b70(&directory, "dir", first, second);
        if (directory.empty()) {
            directory = "Replay";
        } else {
            directory = "Replay/" + directory;
            CreateDirectoryA(directory.c_str(), 0);
        }
    }
    if (use_default) {
        __time64_t now;
        struct tm local;
        _time64(&now);
        _localtime64_s(&local, &now);
        if (!versus_ec) {
            wsprintfA(buffer, "replay/%02d%02d%02d_%02d%02d_%s_story", local.tm_year % 100,
                local.tm_mon + 1, local.tm_mday, local.tm_hour, local.tm_min,
                character_key_to_name(reinterpret_cast<ReplayFilenameSlots *>(reinterpret_cast<unsigned char *>(this) + 0xf4)->select_slot_4284c0(0)->character_00[0]));
        } else {
            ReplayFilenameSlot *slot = reinterpret_cast<ReplayFilenameSlots *>(reinterpret_cast<unsigned char *>(this) + 0xf4)->select_slot_4284c0(0);
            const char *other = character_key_to_name(reinterpret_cast<ReplayFilenameSlots *>(reinterpret_cast<unsigned char *>(this) + 0xf4)->select_slot_4284c0(0)->character_00[1]);
            wsprintfA(buffer, "replay/%02d%02d%02d_%02d%02d_%s_%s", local.tm_year % 100,
                local.tm_mon + 1, local.tm_mday, local.tm_hour, local.tm_min,
                character_key_to_name(slot->character_00[0]), other);
        }
        name = buffer;
    }
    name = directory + "/" + name;
    int index = 0;
    for (;;) {
        wsprintfA(out, "%s%s", name.c_str(), suffix.c_str());
        ReplayFilenameFile file(out);
        if (!file.handle) break;
        wsprintfA(buffer, "_%d.rep", index);
        suffix = buffer;
        ++index;
    }
    return 0;
}
} // namespace th105

#include <mbstring.h>
#include <vector>
namespace th105 {
// Read-only slot envelope view: 0x50 stride is independently established by
// the current fixed-slot selector. No object of this partial record is created.
struct ReplayPatternRecord80 {
    signed char character_00[2];
    unsigned char unknown_02[0x4e];
};
#define REPLAY_PATTERN_SLOT0 (*reinterpret_cast<std::vector<ReplayPatternRecord80> *>(reinterpret_cast<unsigned char *>(this) + 0xf4))[0]
void ReplayFilenameView::expand_pattern_429b70(
    std::string *out, const char *key, const char *first, const char *second)
{
    if (_mbschr(reinterpret_cast<const unsigned char *>(out->c_str()), '/') ||
        _mbschr(reinterpret_cast<const unsigned char *>(out->c_str()), '\\')) {
        *out = "";
        return;
    }
    __time64_t now;
    struct tm local;
    char buffer[260];
    _time64(&now);
    _localtime64_s(&local, &now);
    g_connect_config_ini.read_string_40f120("replay", key, buffer, 260);
    *out = buffer;
    std::string::size_type pos;
    while ((pos = out->find("%d1", 0, 3)) != std::string::npos) {
        wsprintfA(buffer, "%02d%02d%02d", local.tm_year % 100, local.tm_mon + 1, local.tm_mday);
        out->replace(pos, 3, buffer);
    }
    while ((pos = out->find("%d2", 0, 3)) != std::string::npos) {
        wsprintfA(buffer, "%02d%02d", local.tm_mon + 1, local.tm_mday);
        out->replace(pos, 3, buffer);
    }
    while ((pos = out->find("%t1", 0, 3)) != std::string::npos) {
        wsprintfA(buffer, "%02d%02d%02d", local.tm_hour, local.tm_min, local.tm_sec);
        out->replace(pos, 3, buffer);
    }
    while ((pos = out->find("%t2", 0, 3)) != std::string::npos) {
        wsprintfA(buffer, "%02d%02d", local.tm_hour, local.tm_min);
        out->replace(pos, 3, buffer);
    }
    if (first) {
        while ((pos = out->find("%p1", 0, 3)) != std::string::npos)
            out->replace(pos, 3, first);
    }
    if (second && versus_ec) {
        while ((pos = out->find("%p2", 0, 3)) != std::string::npos)
            out->replace(pos, 3, second);
    }
    while ((pos = out->find("%c1", 0, 3)) != std::string::npos) {
        if (!versus_ec) {
            wsprintfA(buffer, "%s_story", character_key_to_name(REPLAY_PATTERN_SLOT0.character_00[0]));
            out->replace(pos, 3, buffer);
        } else {
            out->replace(pos, 3, character_key_to_name(REPLAY_PATTERN_SLOT0.character_00[0]));
        }
    }
    if (versus_ec) {
        while ((pos = out->find("%c2", 0, 3)) != std::string::npos)
            out->replace(pos, 3, character_key_to_name(REPLAY_PATTERN_SLOT0.character_00[1]));
    }
}
#undef REPLAY_PATTERN_SLOT0
} // namespace th105
