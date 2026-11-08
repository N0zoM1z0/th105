#include "battle/InfoEffectEmitter.hpp"
#include "battle/EventEffectState.hpp"
#include "battle/EventEffectStateData.hpp"
namespace th105 {
struct EffectSceneStateView { unsigned unknown_00,unknown_04; int state_08; };
extern EffectSceneStateView *g_effect_scene_state;
// These info helpers are reached by member-compatible callers that prepare
// ECX, but the complete target bodies never consume the incoming receiver.
struct InfoEffectGlobalCalls {
    InfoEffectObject *emit(int,float,float,int,int);
    void set_scene_state(int);
};
InfoEffectObject *InfoEffectGlobalCalls::emit(int id,float x,float y,int a,int b)
{
    return g_info_effect_emitter->emit_effect(id,x,y,a,b);
}
void InfoEffectGlobalCalls::set_scene_state(int state)
{
    g_effect_scene_state->state_08=state;
}
WeatherEffectObject *__cdecl emit_weather_effect_665470(int id,float x,float y,int a,int b)
{
    return g_event_effect_state->emit_effect(id,x,y,a,b);
}
}
