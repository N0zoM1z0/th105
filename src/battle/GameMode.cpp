#include "GameMode.hpp"

namespace th105 {

extern volatile GameMode g_game_mode;
extern MatchSetup g_match_setup;

GameMode get_game_mode()
{
    return g_game_mode;
}

MatchSetup *get_match_setup()
{
    return &g_match_setup;
}

} // namespace th105
