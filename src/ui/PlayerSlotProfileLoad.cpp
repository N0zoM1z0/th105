#include "ProfileMenu.hpp"

#include "assets/FileReader.cpp"

#include <string.h>

namespace th105 {

// Only the open-handle test needs a read-only layout view. Construction,
// reads, normal destruction and exception cleanup use the real CFileReader.
struct PlayerSlotProfileReaderHandleView {
    void *vtable_000;
    FileHandle file_004;
};

bool PlayerSlotRecord::load_profile(const char *path)
{
    ProfileMenuBaseData *data =
        reinterpret_cast<ProfileMenuBaseData *>(this);

    std::string profile_path(path);
    profile_path = "profile/" + profile_path;

    CFileReader reader(profile_path.c_str());
    if (reinterpret_cast<PlayerSlotProfileReaderHandleView *>(&reader)->file_004 == 0)
        return false;

    data->string_098.assign(path, strlen(path));
    data->normalize_profile_name();

    reader.read(data->block_140, 0x34);
    reader.read(data->block_174, 0x34);
    reader.read(&data->flag_13c, 1);
    reader.read(&data->flag_1a8, 1);

    for (int deck_index = 0; deck_index < 20; ++deck_index) {
        unsigned char count;
        reader.read(&count, 1);
        data->decks_1ac[deck_index].clear();
        for (int index = 0; index < count; ++index) {
            unsigned short value = 0;
            data->decks_1ac[deck_index].push_back(value);
            reader.read(&data->decks_1ac[deck_index].back(), 2);
        }
    }

    return true;
}

typedef char PlayerSlotProfileFileReader_size_must_be_0x0c[
    sizeof(CFileReader) == 0x0C ? 1 : -1];
typedef char ProfileMenuBaseData_size_must_be_0x33c[
    sizeof(ProfileMenuBaseData) == 0x33C ? 1 : -1];

typedef char PlayerSlotProfileReaderHandleOffset[
    offsetof(PlayerSlotProfileReaderHandleView, file_004) == 4 ? 1 : -1];

} // namespace th105
