#include "GameMode.hpp"

namespace th105 {

GameMode get_game_mode()
{
    return *reinterpret_cast<volatile GameMode *>(0x006e62ec);
}

MatchSetup *get_match_setup()
{
    return reinterpret_cast<MatchSetup *>(0x006e6fe8);
}

} // namespace th105
