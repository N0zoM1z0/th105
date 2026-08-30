#include "ProfileMenu.hpp"

#include "assets/FileReader.hpp"

#include <string.h>

extern "C" __declspec(dllimport) int __stdcall ReadFile(
    void *file,
    void *buffer,
    unsigned long bytes_to_read,
    unsigned long *bytes_read,
    void *overlapped);

namespace th105 {

// The profile loader owns a concrete CFileReader automatic object.  This
// call-site view keeps that lifetime visible to VC8 without changing the
// current shared FileReader header or its already-exact translation units.
struct PlayerSlotProfileFileReaderView {
    explicit PlayerSlotProfileFileReaderView(const char *path)
    {
        file = CreateFileA(path, 1, 1, 0, 3, 0x80, 0);
        if (file == reinterpret_cast<void *>(-1))
            file = 0;
    }

    virtual ~PlayerSlotProfileFileReaderView()
    {
        if (file != 0)
            CloseHandle(file);
    }

    virtual bool read(void *destination, unsigned long size)
    {
        return ReadFile(file, destination, size, &bytes_read, 0) != 0;
    }

    virtual unsigned long last_read_size() const { return bytes_read; }
    virtual long seek(long, int) { return 0; }
    virtual unsigned long size() const { return 0; }

    void *file;
    unsigned long bytes_read;
};

struct PlayerSlotProfileDataView {
    unsigned char reserved_000[0x98];
    std::string string_098;
    std::string string_0b4;
    unsigned char reserved_0d0[0x6C];
    unsigned char flag_13c;
    unsigned char reserved_13d[3];
    unsigned char block_140[0x34];
    unsigned char block_174[0x34];
    unsigned char flag_1a8;
    unsigned char reserved_1a9[3];
    std::deque<unsigned short> decks_1ac[20];

    void normalize_profile_name();
};

bool PlayerSlotRecord::load_profile(const char *path)
{
    PlayerSlotProfileDataView *data =
        reinterpret_cast<PlayerSlotProfileDataView *>(this);

    std::string profile_path(path);
    profile_path = "profile/" + profile_path;

    PlayerSlotProfileFileReaderView reader(profile_path.c_str());
    if (reader.file == 0)
        return false;

    data->string_098.assign(path, strlen(path));
    data->normalize_profile_name();

    ReadFile(reader.file, data->block_140, 0x34, &reader.bytes_read, 0);
    ReadFile(reader.file, data->block_174, 0x34, &reader.bytes_read, 0);
    ReadFile(reader.file, &data->flag_13c, 1, &reader.bytes_read, 0);
    ReadFile(reader.file, &data->flag_1a8, 1, &reader.bytes_read, 0);

    std::deque<unsigned short> *deck = data->decks_1ac;
    int remaining = 20;
    while (remaining != 0) {
        unsigned char count;
        ReadFile(reader.file, &count, 1, &reader.bytes_read, 0);
        deck->clear();
        for (int index = 0; index < count; ++index) {
            unsigned short value = 0;
            deck->push_back(value);
            ReadFile(
                reader.file,
                &deck->back(),
                2,
                &reader.bytes_read,
                0);
        }
        ++deck;
        --remaining;
    }

    return true;
}

typedef char PlayerSlotProfileFileReaderView_size_must_be_0x0c[
    sizeof(PlayerSlotProfileFileReaderView) == 0x0C ? 1 : -1];
typedef char PlayerSlotProfileDataView_size_must_be_0x33c[
    sizeof(PlayerSlotProfileDataView) == 0x33C ? 1 : -1];

} // namespace th105
