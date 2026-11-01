// Complete original-JP1.06a configuration save; source-present, nonexact.
// See docs/GAME_CONFIG_SAVE_SOURCE_2026_11_01.md.
#include "assets/FileReader.hpp"
#include <string>
#include <deque>
#include <stddef.h>
namespace th105 {
int __cdecl get_current_replay_header_code();
struct GameConfigSaveView {
    std::string profile_paths_00[2];
    int timeout_38;
    unsigned short values_3c[4];
    int timeout_44;
    std::deque<std::string> recent_entries_48;
    unsigned char flag_5c, flag_5d, flag_5e, pad_5f;
    int mode_60, default_game_type_64, volume_bgm_68, volume_se_6c;
    unsigned char flag_70, continue_flag_71, pad_72[2];
    void save_427390();
};
// Read/write-format view only; the global constructor's separate string/EH
// topology is not claimed by this serializer.
typedef char SaveStringSize[sizeof(std::string)==0x1c?1:-1];
typedef char SaveDequeSize[sizeof(std::deque<std::string>)==0x14?1:-1];
typedef char SaveViewSize[sizeof(GameConfigSaveView)==0x74?1:-1];
typedef char SaveRecentOffset[offsetof(GameConfigSaveView,recent_entries_48)==0x48?1:-1];
typedef char SaveModeOffset[offsetof(GameConfigSaveView,default_game_type_64)==0x64?1:-1];
void GameConfigSaveView::save_427390()
{
    CFileWriter writer("config.dat");
    unsigned version = get_current_replay_header_code();
    writer.write(&version, sizeof(version));
    for (int i=0;i<2;++i) {
        unsigned length = profile_paths_00[i].size() > 260 ? 260 : profile_paths_00[i].size();
        writer.write(&length, sizeof(length));
        if (length != 0)
            writer.write(profile_paths_00[i].c_str(), length);
    }
    writer.write(&timeout_38, sizeof(timeout_38));
    for (int i=0;i<4;++i)
        writer.write(&values_3c[i], sizeof(values_3c[i]));
    writer.write(&timeout_44, sizeof(timeout_44));
    unsigned count = recent_entries_48.size() > 10 ? 10 : recent_entries_48.size();
    writer.write(&count, sizeof(count));
    for (unsigned i=0;i<count;++i) {
        unsigned length = recent_entries_48[i].size() > 1024 ? 1024 : recent_entries_48[i].size();
        writer.write(&length, sizeof(length));
        if (length != 0) {
            const char *data = recent_entries_48[i].c_str();
            writer.write(data, length);
        }
    }
    writer.write(&flag_5c,1);
    writer.write(&flag_5d,1);
    writer.write(&flag_5e,1);
    writer.write(&mode_60,4);
    writer.write(&default_game_type_64,4);
    writer.write(&volume_bgm_68,4);
    writer.write(&volume_se_6c,4);
    writer.write(&flag_70,1);
    writer.write(&continue_flag_71,1);
}
}
