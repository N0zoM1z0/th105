#include "BattleBaseEffectLifetime.hpp"
#include "D3DXEffectInterface.hpp"
#include "engine/D3DBackendListenerRuntime.hpp"

namespace th105 {


BattleBaseEffectLifetimeView::BattleBaseEffectLifetimeView()
    : effect_04(0)
{
}

BattleBaseEffectLifetimeView::~BattleBaseEffectLifetimeView()
{
    if (effect_04 != 0) {
        effect_04->release();
        effect_04 = 0;
    }
}

void BattleBaseEffectLifetimeView::control_a()
{
    if (effect_04 != 0)
        static_cast<D3DXEffectInterface *>(effect_04)->OnLostDevice();
}

void BattleBaseEffectLifetimeView::control_b()
{
    if (effect_04 != 0)
        static_cast<D3DXEffectInterface *>(effect_04)->OnResetDevice();
}

void BattleBaseEffectLifetimeView::shutdown()
{
    remove_battle_base_effect(this);
    if (effect_04 != 0) {
        effect_04->release();
        effect_04 = 0;
    }
}

} // namespace th105
