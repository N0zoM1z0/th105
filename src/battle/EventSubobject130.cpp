#include "EventSubobject130.hpp"

namespace th105 {

struct BattleObjectManagerPairView {
    unsigned char reserved_00[0x10c];
    float shared_first_10c;
    float shared_second_110;
};

extern BattleObjectManagerPairView *g_battle_object_manager;

void *EventSubobject130::set_global_pair(float first, float second)
{
    BattleObjectManagerPairView *const result = g_battle_object_manager;
    result->shared_first_10c = first;
    g_battle_object_manager->shared_second_110 = second;
    return result;
}

} // namespace th105
