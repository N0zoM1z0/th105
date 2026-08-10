#include "GameConfig.hpp"

namespace th105 {

GameConfig *get_game_config()
{
    return reinterpret_cast<GameConfig *>(0x006e6b38);
}

} // namespace th105
