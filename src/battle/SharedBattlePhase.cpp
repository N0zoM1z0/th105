#include "Collision.hpp"
#include "FighterPhaseContext.hpp"
#include "BattleObjectManagerRuntime.hpp"

namespace th105 {


struct PhaseStaticService {
    void *vtable_00;

    void phase_010c0();
    void phase_04980(int value);
    void phase_04a10(int value);
};

struct InfoManagerPhaseView;
typedef void (__thiscall *InfoManagerPhaseCallback)(
    InfoManagerPhaseView *manager);

struct InfoManagerPhaseView {
    InfoManagerPhaseCallback *vtable_00;
};

struct SharedBattlePhaseController {
    void run_shared_battle_phase_sequence();
    void run_battle_phase_and_info_callback();
};

BattleObjectManager *g_battle_object_manager;
FighterPhaseContext *g_fighter_phase_context;
EffectSink *g_effect_sink;
PhaseStaticService g_battle_phase_static_service = {
    reinterpret_cast<void *>(0x006c09a8)
};

void Fighter::emit_fighter_effect_433cc0(
    int effect_code,
    float x,
    float y,
    int direction,
    int trailing_value)
{
    g_effect_sink->emit_effect(
        effect_code, x, y, direction, trailing_value, this);
}

void SharedBattlePhaseController::run_shared_battle_phase_sequence()
{
    g_battle_object_manager->phase_466980();
    g_battle_phase_static_service.phase_04a10(1);
    g_battle_phase_static_service.phase_04980(2);
    g_fighter_phase_context->phase_463970();
    g_battle_phase_static_service.phase_04980(1);
    g_battle_object_manager->phase_4669f0();
    g_fighter_phase_context->phase_463a00(-2);
    g_fighter_phase_context->phase_463ab0();
    g_fighter_phase_context->phase_463a60();
    g_effect_sink->phase_18(-1);
    g_fighter_phase_context->phase_463a00(-1);
    g_fighter_phase_context->phase_463820();
    g_fighter_phase_context->phase_463a00(1);
    g_fighter_phase_context->phase_463a00(2);
    g_effect_sink->phase_18(1);
    g_battle_object_manager->phase_466a50();
}

void SharedBattlePhaseController::run_battle_phase_and_info_callback()
{
    g_battle_phase_static_service.phase_010c0();
    run_shared_battle_phase_sequence();

    InfoManagerPhaseView *manager =
        reinterpret_cast<InfoManagerPhaseView *>(g_info_manager);
    manager->vtable_00[5](manager);
}

} // namespace th105
