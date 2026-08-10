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

struct MatchSetup;

GameMode get_game_mode();
MatchSetup *get_match_setup();

} // namespace th105
