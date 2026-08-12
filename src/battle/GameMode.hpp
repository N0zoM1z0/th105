#pragma once

namespace th105 {

enum GameMode {
    GAME_MODE_VS_COM = 1,
    GAME_MODE_VS_PLAYER = 2,
    GAME_MODE_NETWORK_SERVER = 3,
    GAME_MODE_NETWORK_CLIENT = 4,
    GAME_MODE_NETWORK_WATCH = 5,
    GAME_MODE_PRACTICE = 8,
};

struct MatchSetup {
    struct Side {
        int character_key_00;
        unsigned char fighter_option_04;
        unsigned char fighter_option_05;
        unsigned char fighter_category_06;
        unsigned char unknown_07;
        unsigned char input_payload_08[0x14];
        void *transition_link_1c;
    };

    int match_identifier_00;
    signed char stage_04;
    signed char bgm_id_05;
    unsigned char unknown_06[2];
    Side sides_08[2];
    unsigned seed_48;
};

typedef char MatchSetupSide_size_must_be_0x20[
    sizeof(MatchSetup::Side) == 0x20 ? 1 : -1];
typedef char MatchSetup_size_must_be_0x4c[
    sizeof(MatchSetup) == 0x4c ? 1 : -1];

GameMode get_game_mode();
MatchSetup *get_match_setup();

} // namespace th105
