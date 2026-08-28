#include <string>

namespace th105 {

struct GameConfigProfileRuntimeView {
    std::string profile_paths_00[2];
    int timeout_38;
    unsigned short values_3c[4];
    int timeout_44;
    unsigned char reserved_48[0x1c];
    int default_game_type_64;

    unsigned char load_config_427800();
};

struct PlayerSlotProfileRuntimeView {
    unsigned char opaque_000[0x33c];

    bool load_profile(const char *path);
    void initialize_defaults();
    void save_to_profile(const char *path);
    void set_profile_color(
        unsigned char red,
        unsigned char green,
        unsigned char blue);
};

extern GameConfigProfileRuntimeView g_game_config;
extern PlayerSlotProfileRuntimeView g_player_slot_records[2];

void __cdecl initialize_player_profiles_from_game_config()
{
    g_game_config.load_config_427800();

    if (!g_player_slot_records[0].load_profile(
            g_game_config.profile_paths_00[0].c_str()) &&
        !g_player_slot_records[0].load_profile("Profile1P.dat")) {
        g_player_slot_records[0].initialize_defaults();
        g_player_slot_records[0].save_to_profile("Profile1P.dat");
    }

    if (!g_player_slot_records[1].load_profile(
            g_game_config.profile_paths_00[1].c_str()) &&
        !g_player_slot_records[1].load_profile("Profile2P.dat")) {
        g_player_slot_records[1].initialize_defaults();
        g_player_slot_records[1].save_to_profile("Profile2P.dat");
    }

    g_player_slot_records[0].set_profile_color(160, 160, 255);
    g_player_slot_records[1].set_profile_color(255, 128, 128);
}

} // namespace th105
