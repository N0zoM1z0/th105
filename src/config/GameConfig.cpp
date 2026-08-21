#include "GameConfig.hpp"

namespace th105 {

extern GameConfig g_game_config;

GameConfig *get_game_config()
{
    return &g_game_config;
}

} // namespace th105
