#include "audio/DirectSound.hpp"

namespace th105 {

class BattleBaseEffectLifetimeView {
public:
    BattleBaseEffectLifetimeView();
    ~BattleBaseEffectLifetimeView();
    virtual void control_a();
    virtual void control_b();

    void shutdown();

private:
    UnknownInterface *effect_04;
};

extern "C" void __stdcall remove_battle_base_effect(
    BattleBaseEffectLifetimeView *effect);

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

void BattleBaseEffectLifetimeView::shutdown()
{
    remove_battle_base_effect(this);
    if (effect_04 != 0) {
        effect_04->release();
        effect_04 = 0;
    }
}

} // namespace th105
