#include "audio/DirectSound.hpp"
#include "engine/D3DBackendListenerRuntime.hpp"

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

extern "C" long __stdcall D3DXCreateEffect(
    D3DDevice9 *device,
    const void *source_data,
    unsigned source_size,
    const void *defines,
    void *include_handler,
    unsigned flags,
    void *effect_pool,
    UnknownInterface **effect,
    void **errors);

bool BattleBaseEffectLifetimeView::initialize(const void *data, unsigned size)
{
    if (effect_04 != 0)
        return false;
    d3d_backend_listener_runtime()->register_reset_listener(
        reinterpret_cast<DeviceResetListener *>(this));
    return D3DXCreateEffect(
        g_d3d_backend.device_020, data, size, 0, 0, 0, 0, &effect_04, 0) == 0;
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
