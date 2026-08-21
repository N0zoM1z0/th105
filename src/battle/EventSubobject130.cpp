#include "EventSubobject130.hpp"
#include "EventEffectState.hpp"

namespace th105 {

struct InfoEffectEmitterView {
    int emit_effect(int effect_id, float x, float y, int flag_a, int flag_b);
};

extern int g_event_effect_id;
extern InfoEffectEmitterView *g_info_effect_emitter;
int __cdecl lookup_event_effect_record(int event_id);

struct BattleObjectManagerPairView {
    unsigned char reserved_00[0x10c];
    float shared_first_10c;
    float shared_second_110;
};

extern BattleObjectManagerPairView *g_battle_object_manager;

int EventSubobject130::trigger_global_effect(int value)
{
    g_event_effect_id = value;
    g_info_effect_emitter->emit_effect(
        lookup_event_effect_record(value), 320.0f, 42.0f, 1, 1);
    return g_event_effect_state->set_event_id(value);
}

void *EventSubobject130::set_global_pair(float first, float second)
{
    BattleObjectManagerPairView *const result = g_battle_object_manager;
    result->shared_first_10c = first;
    g_battle_object_manager->shared_second_110 = second;
    return result;
}

} // namespace th105
