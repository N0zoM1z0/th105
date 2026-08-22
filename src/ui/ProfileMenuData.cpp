#include "ProfileMenu.hpp"
#include "../platform/SystemUtilities.hpp"
#include "../assets/FileReader.hpp"

#include <string.h>

extern "C" const char profile_name_empty[];

namespace th105 {


namespace {

struct StringAssignBytesView {
    std::string &assign_bytes(const char *source, unsigned int size);
};

} // namespace

void ProfileMenuBaseData::normalize_profile_name()
{
    string_0b4.assign(string_098, 0, ~0u);
    string_0b4.erase(string_098.size() - 4, 4);

    unsigned int position = 0;
    while (position < string_0b4.size()) {
        position += g_module_path_text.extra_bytes(
            static_cast<unsigned char>(string_098[position])) + 1;
        if (position >= 16)
            string_0b4.erase(position, string_0b4.size() - position);
    }
}

void ProfileMenuBaseData::initialize_defaults()
{
    reinterpret_cast<StringAssignBytesView *>(&string_098)
        ->assign_bytes(profile_name_empty, 0);
    reinterpret_cast<StringAssignBytesView *>(&string_0b4)
        ->assign_bytes(profile_name_empty, 0);

    memset(block_140, 0, sizeof(block_140));
    block_140[0] = 0xff;
    memset(block_174, 0, sizeof(block_174));

    unsigned int *primary = reinterpret_cast<unsigned int *>(block_140 + 4);
    primary[0] = 200;
    primary[1] = 208;
    primary[2] = 203;
    primary[3] = 205;
    primary[4] = 44;
    primary[5] = 45;
    primary[6] = 46;
    primary[7] = 30;
    primary[8] = 31;
    primary[9] = 32;
    primary[10] = 16;

    std::deque<unsigned short> *decks = decks_1ac;
    block_174[0] = 0;
    unsigned int *secondary = reinterpret_cast<unsigned int *>(block_174 + 0x14);
    secondary[0] = 0;
    secondary[1] = 1;
    secondary[2] = 2;
    secondary[3] = 3;
    secondary[4] = 4;
    secondary[5] = 5;
    secondary[6] = 6;

    flag_13c = 0;
    flag_1a8 = 0xff;

    for (int i = 0; i < 20; ++i)
        decks[i].clear();
    for (int i = 0; i < 15; ++i)
        initialize_default_deck(&decks[i], i);
}

} // namespace th105

extern "C" const char profile_directory_prefix[];

namespace th105 {

std::string __cdecl concatenate_profile_data_path(
    const char *prefix, const std::string &value);

bool ProfileMenuBaseData::save_to_profile(const char *path)
{
    std::string file_name;

    if (path != 0) {
        file_name.assign(path, strlen(path));
        string_098.assign(path, strlen(path));
    } else {
        if (string_098.compare(0, string_098.size(), profile_name_empty, 0) == 0)
            return false;
        file_name.assign(string_098, 0, ~0u);
    }

    normalize_profile_name();
    file_name.assign(
        concatenate_profile_data_path(profile_directory_prefix, file_name),
        0,
        ~0u);

    CFileWriter writer(file_name.c_str());
    if (!writer.is_open())
        return false;

    writer.write(block_140, sizeof(block_140));
    writer.write(block_174, sizeof(block_174));
    writer.write(&flag_13c, 1);
    writer.write(&flag_1a8, 1);

    std::deque<unsigned short> *deck = decks_1ac;
    int deck_index = 0;
    do {
        unsigned char count = static_cast<unsigned char>(deck->size());
        writer.write(&count, 1);

        int item_index = 0;
        if (count != 0) {
            do {
                writer.write(&(*deck)[item_index], sizeof(unsigned short));
                ++item_index;
            } while (item_index < count);
        }

        ++deck;
        ++deck_index;
    } while (deck_index < 20);

    return true;
}

} // namespace th105
