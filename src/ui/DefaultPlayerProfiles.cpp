namespace th105 {

struct PlayerSlotProfileRuntimeView {
    unsigned char opaque_000[0x33c];

    bool reload_profile();
    bool load_profile(const char *path);
    void initialize_defaults();
    void save_to_profile(const char *path);
    void set_profile_color(
        unsigned char red,
        unsigned char green,
        unsigned char blue);
};

extern PlayerSlotProfileRuntimeView g_player_slot_records[2];

void __cdecl initialize_default_player_profiles()
{
    PlayerSlotProfileRuntimeView *player1 = &g_player_slot_records[0];
    if (!player1->reload_profile() && !player1->load_profile("Profile1P.dat")) {
        player1->initialize_defaults();
        player1->save_to_profile("Profile1P.dat");
    }

    PlayerSlotProfileRuntimeView *player2 = &g_player_slot_records[1];
    if (!player2->reload_profile() && !player2->load_profile("Profile2P.dat")) {
        player2->initialize_defaults();
        player2->save_to_profile("Profile2P.dat");
    }

    player1->set_profile_color(160, 160, 255);
    player2->set_profile_color(255, 128, 128);
}

} // namespace th105
