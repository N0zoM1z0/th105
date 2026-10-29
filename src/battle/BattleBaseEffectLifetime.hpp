#pragma once
#include "audio/DirectSound.hpp"

namespace th105 {

class BattleBaseEffectLifetimeView {
public:
    BattleBaseEffectLifetimeView();
    ~BattleBaseEffectLifetimeView();
    virtual void control_a();
    virtual void control_b();

    bool initialize(const void *data, unsigned size);
    void shutdown();

private:
    UnknownInterface *effect_04;
};

extern "C" void __stdcall remove_battle_base_effect(
    BattleBaseEffectLifetimeView *effect);

} // namespace th105
