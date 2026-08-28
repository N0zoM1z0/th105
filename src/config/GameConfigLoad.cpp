#include "assets/FileReader.hpp"

#include <deque>
#include <string>
#include <string.h>

extern "C" __declspec(dllimport) int __stdcall ReadFile(
    void *file,
    void *buffer,
    unsigned long bytes_to_read,
    unsigned long *bytes_read,
    void *overlapped);
extern "C" __declspec(dllimport) unsigned long __stdcall SetFilePointer(
    void *file,
    long distance,
    long *distance_high,
    unsigned long origin);

namespace th105 {

// Call-site lifetime view of the current CFileReader object used by GameConfig.
// The vtable is canonical-mapped to CFileReader @ 0x006C0F34; keeping this
// local avoids changing CFileReader visibility in unrelated exact TUs.
struct GameConfigFileReaderView {
    explicit GameConfigFileReaderView(const char *path)
    {
        file = CreateFileA(path, 1, 1, 0, 3, 0x80, 0);
        if (file == reinterpret_cast<void *>(-1))
            file = 0;
    }

    virtual ~GameConfigFileReaderView()
    {
        if (file != 0)
            CloseHandle(file);
    }

    virtual bool read(void *destination, unsigned long size)
    {
        return ReadFile(file, destination, size, &bytes_read, 0) != 0;
    }

    virtual unsigned long last_read_size() const { return bytes_read; }
    virtual long seek(long offset, int origin)
    {
        return SetFilePointer(file, offset, 0, origin);
    }
    virtual unsigned long size() const { return 0; }

    void *file;
    unsigned long bytes_read;
};

struct GameConfigLoadView {
    std::string profile_paths_00[2];
    int timeout_38;
    unsigned short values_3c[4];
    int timeout_44;
    std::deque<std::string> recent_entries_48;
    unsigned char flag_5c;
    unsigned char flag_5d;
    unsigned char flag_5e;
    unsigned char reserved_5f;
    int mode_60;
    int default_game_type_64;
    int volume_bgm_68;
    int volume_se_6c;
    unsigned char flag_70;
    unsigned char continue_flag_71;
    unsigned char reserved_72[2];

    unsigned char load_config_427800();
};

unsigned char GameConfigLoadView::load_config_427800()
{
    GameConfigFileReaderView reader("config.dat");
    if (reader.file == 0)
        return 0;

    unsigned version;
    ReadFile(reader.file, &version, 4, &reader.bytes_read, 0);

    char buffer[1024];
    unsigned length;
    for (int i = 0; i < 2; ++i) {
        ReadFile(reader.file, &length, 4, &reader.bytes_read, 0);
        memset(buffer, 0, 260);
        if (length != 0) {
            ReadFile(reader.file, buffer, length, &reader.bytes_read, 0);
            profile_paths_00[i].assign(buffer, strlen(buffer));
        }
    }

    ReadFile(reader.file, &timeout_38, 4, &reader.bytes_read, 0);
    for (int i = 0; i < 4; ++i)
        ReadFile(reader.file, &values_3c[i], 2, &reader.bytes_read, 0);
    ReadFile(reader.file, &timeout_44, 4, &reader.bytes_read, 0);

    unsigned count;
    ReadFile(reader.file, &count, 4, &reader.bytes_read, 0);
    for (unsigned i = 0; i < count; ++i) {
        ReadFile(reader.file, &length, 4, &reader.bytes_read, 0);
        unsigned read_length = length;
        if (read_length > 1024) {
            read_length = 1024;
            length = 1024;
        }

        memset(buffer, 0, sizeof(buffer));
        if (read_length != 0) {
            ReadFile(reader.file, buffer, read_length, &reader.bytes_read, 0);
            recent_entries_48.push_back(std::string(buffer));
        }
    }

    ReadFile(reader.file, &flag_5c, 1, &reader.bytes_read, 0);
    ReadFile(reader.file, &flag_5d, 1, &reader.bytes_read, 0);
    ReadFile(reader.file, &flag_5e, 1, &reader.bytes_read, 0);
    ReadFile(reader.file, &mode_60, 4, &reader.bytes_read, 0);
    ReadFile(reader.file, &default_game_type_64, 4, &reader.bytes_read, 0);
    ReadFile(reader.file, &volume_bgm_68, 4, &reader.bytes_read, 0);
    ReadFile(reader.file, &volume_se_6c, 4, &reader.bytes_read, 0);
    ReadFile(reader.file, &flag_70, 1, &reader.bytes_read, 0);
    ReadFile(reader.file, &continue_flag_71, 1, &reader.bytes_read, 0);
    return 1;
}

typedef char GameConfigLoadView_size_must_be_0x74[
    sizeof(GameConfigLoadView) == 0x74 ? 1 : -1];
typedef char GameConfigLoadView_recent_offset_must_be_0x48[
    offsetof(GameConfigLoadView, recent_entries_48) == 0x48 ? 1 : -1];
typedef char GameConfigLoadView_game_type_offset_must_be_0x64[
    offsetof(GameConfigLoadView, default_game_type_64) == 0x64 ? 1 : -1];

} // namespace th105
