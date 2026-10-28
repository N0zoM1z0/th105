#include "battle/Collision.hpp"
#include "battle/BattleObjectManagerRuntime.hpp"
#include "battle/GameMode.hpp"
#include <stddef.h>

namespace th105 {
struct PresentationFighterView {
    unsigned char unknown_000[0x6a0];
    short texture_duration_6a0;
};
struct PresentationInputView {
    void update_428260();
};
struct BattlePresentationController {
    unsigned char unknown_00[0x0c];
    PresentationFighterView *first_0c;
    PresentationFighterView *second_10;
    void update_presentation_46b160();
};
extern PresentationInputView *g_battle_input_gate;
extern int g_pair_state;

void BattlePresentationController::update_presentation_46b160()
{
    if (first_0c->texture_duration_6a0 != 0 ||
        second_10->texture_duration_6a0 != 0)
        g_battle_object_manager->effect_level_delta_fc = -10;
    if (get_game_mode() != GAME_MODE_NETWORK_CLIENT &&
        get_game_mode() != GAME_MODE_NETWORK_WATCH)
        g_battle_input_gate->update_428260();
    g_effect_sink->unknown_14();
    g_battle_object_manager->update_background_runtime_466f40();
    ++g_pair_state;
}
}
