#include "battle/EffectManager.hpp"
#include "battle/EffectSprite.hpp"
#include "battle/EventEffectState.hpp"

#include <deque>
#include <map>
#include <stddef.h>
#include <vector>

namespace th105 {

struct EventEffectStateLifetime {
    int current_event_id_00;
    signed char current_stage_04;
    unsigned char reserved_05[3];
    std::vector<unsigned> resources_08;
    std::vector<CSpriteEx> sprites_18;
    std::deque<BackgroundRenderEntry> background_entries_28;
    std::map<signed char, std::vector<unsigned char> > stage_rows_3c;
    CEffectManager<WeatherEffectObject> emitter_48;
    unsigned char runtime_tail_dc[0x0c];

    EventEffectStateLifetime();
    ~EventEffectStateLifetime();
};

typedef char EventEffect_resources_off[(offsetof(EventEffectStateLifetime,resources_08)==0x08)?1:-1];
typedef char EventEffect_sprites_off[(offsetof(EventEffectStateLifetime,sprites_18)==0x18)?1:-1];
typedef char EventEffect_background_off[(offsetof(EventEffectStateLifetime,background_entries_28)==0x28)?1:-1];
typedef char EventEffect_rows_off[(offsetof(EventEffectStateLifetime,stage_rows_3c)==0x3c)?1:-1];
typedef char EventEffect_emitter_off[(offsetof(EventEffectStateLifetime,emitter_48)==0x48)?1:-1];
typedef char EventEffect_size[(sizeof(EventEffectStateLifetime)==0xe8)?1:-1];

extern EventEffectStateLifetime *g_event_effect_state_lifetime;

EventEffectStateLifetime::EventEffectStateLifetime()
{
    g_event_effect_state_lifetime = this;
}

EventEffectStateLifetime::~EventEffectStateLifetime()
{
}

} // namespace th105
