#include "battle/EventEffectStateData.hpp"
#include "battle/EffectManager.hpp"
#include "battle/EffectSprite.hpp"
#include "battle/EventEffectState.hpp"

#include <deque>
#include <map>
#include <stddef.h>
#include <vector>

namespace th105 {

typedef char EventEffect_resources_off[(offsetof(EventEffectStateData,resources_08)==0x08)?1:-1];
typedef char EventEffect_sprites_off[(offsetof(EventEffectStateData,sprites_18)==0x18)?1:-1];
typedef char EventEffect_background_off[(offsetof(EventEffectStateData,background_entries_28)==0x28)?1:-1];
typedef char EventEffect_rows_off[(offsetof(EventEffectStateData,stage_rows_3c)==0x3c)?1:-1];
typedef char EventEffect_emitter_off[(offsetof(EventEffectStateData,emitter_48)==0x48)?1:-1];
typedef char EventEffect_x_off[(offsetof(EventEffectStateData,runtime_x_dc)==0xdc)?1:-1];
typedef char EventEffect_z_off[(offsetof(EventEffectStateData,runtime_z_e4)==0xe4)?1:-1];
typedef char EventEffect_size[(sizeof(EventEffectStateData)==0xe8)?1:-1];

extern EventEffectStateData *g_event_effect_state_lifetime;

EventEffectStateData::EventEffectStateData()
{
    g_event_effect_state_lifetime = this;
}

EventEffectStateData::~EventEffectStateData()
{
}

} // namespace th105
