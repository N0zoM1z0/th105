#include "battle/BattleObjectManagerRuntime.hpp"
#include "battle/EventEffectState.hpp"

#include <objbase.h>

namespace th105 {

BattleObjectManager::BattleObjectManager()
    : render_requests_00(),
      worker_a_10(),
      worker_b_18(),
      renderers_28(),
      owned_34(),
      effect_40()
{
    texture_a_d8 = 0;
    texture_b_dc = 0;
    effect_40.initialize(battle_object_effect_blob_6c2db8, 0x4d0);

    running_0c = 1;
    event_a_20 = CreateEventA(0, FALSE, FALSE, 0);
    event_b_24 = CreateEventA(0, FALSE, FALSE, 0);
    worker_a_10.start(battle_object_render_worker_proc_4678d0, this);
    worker_b_18.start(battle_object_manager_worker_proc_466cf0, this);
    worker_b_18.set_priority(-15);
}

BattleObjectManager::~BattleObjectManager()
{
    running_0c = 0;
    SetEvent(event_a_20);
    SetEvent(event_b_24);
    worker_a_10.wait_for_exit();
    worker_b_18.wait_for_exit();
    CloseHandle(event_a_20);
    CloseHandle(event_b_24);

    while (owned_34.size() != 0) {
        delete owned_34.front();
        owned_34.pop_front();
    }
    while (!renderers_28.empty()) {
        delete renderers_28.front();
        renderers_28.pop_front();
    }
    effect_40.shutdown();
}

void BattleObjectManager::phase_466980()
{
    g_event_effect_state->render_background_effects();
    g_event_effect_state->dispatch_emitter_state(-2);
    for (std::list<BackgroundBase *>::iterator it = renderers_28.begin();
         it != renderers_28.end(); ++it)
        (*it)->slot_10();
    render_tail_4666a0();
}

void BattleObjectManager::phase_4669f0()
{
    for (std::list<BackgroundBase *>::iterator it = renderers_28.begin();
         it != renderers_28.end(); ++it)
        (*it)->slot_0c();
    g_event_effect_state->dispatch_emitter_state(-1);
}

void BattleObjectManager::phase_466a50()
{
    for (std::list<BackgroundBase *>::iterator it = renderers_28.begin();
         it != renderers_28.end(); ++it)
        (*it)->slot_08();
    g_event_effect_state->dispatch_emitter_state(1);
}

void BattleObjectManager::manager_worker_loop_466c70()
{
    while (running_0c) {
        WaitForSingleObject(event_b_24, INFINITE);
        while (!owned_34.empty()) {
            delete owned_34.front();
            owned_34.pop_front();
        }
    }
}

void BattleObjectManager::render_worker_loop_4677b0()
{
    while (running_0c) {
        WaitForSingleObject(event_a_20, INFINITE);
        while (!render_requests_00.empty()) {
            dispatch_request_467380(
                render_requests_00.front().kind_00,
                render_requests_00.front().value_04);
            render_requests_00.pop_front();
        }
    }
}

DWORD WINAPI battle_object_render_worker_proc_4678d0(void *argument)
{
    if (CoInitialize(0) >= 0) {
        static_cast<BattleObjectManager *>(argument)->render_worker_loop_4677b0();
        CoUninitialize();
    }
    return 0;
}

DWORD WINAPI battle_object_manager_worker_proc_466cf0(void *argument)
{
    if (CoInitialize(0) >= 0) {
        static_cast<BattleObjectManager *>(argument)->manager_worker_loop_466c70();
        CoUninitialize();
    }
    return 0;
}

} // namespace th105

namespace th105 {

void __cdecl update_background_pattern_660b30(int background_id);

void BattleObjectManager::update_background_runtime_466f40()
{
    if (effect_level_delta_fc != 0) {
        if ((int)effect_level_f8 + effect_level_delta_fc > 255) {
            effect_level_f8 = 255;
            effect_level_delta_fc = 0;
            update_background_pattern_660b30(16);
        } else if ((int)effect_level_f8 + effect_level_delta_fc < 60) {
            effect_level_f8 = 60;
            effect_level_delta_fc = 0;
            update_background_pattern_660b30(16);
        } else {
            effect_level_f8 = static_cast<unsigned char>((int)effect_level_f8 + effect_level_delta_fc);
            effect_level_delta_fc = 0;
            update_background_pattern_660b30(16);
        }
    } else {
        if (effect_level_f8 < 245)
            effect_level_f8 += 10;
        else
            effect_level_f8 = 255;
        update_background_pattern_660b30(g_event_effect_state->current_event_id);
    }

    drift_e0 += 0.005f;
    drift_e8 += 0.005f;
    drift_e4 += 0.005f;
    drift_ec += 0.005f;

    if (background_x_100 < g_event_effect_state->background_target_x_dc()) {
        const double next = background_x_100 + 0.01f;
        background_x_100 = static_cast<float>(
            next < g_event_effect_state->background_target_x_dc()
                ? next
                : g_event_effect_state->background_target_x_dc());
    } else if (background_x_100 > g_event_effect_state->background_target_x_dc()) {
        const double next = background_x_100 - 0.01f;
        background_x_100 = static_cast<float>(
            next > g_event_effect_state->background_target_x_dc()
                ? next
                : g_event_effect_state->background_target_x_dc());
    }

    if (background_y_104 < g_event_effect_state->background_target_y_e0()) {
        const double next = background_y_104 + 0.01f;
        background_y_104 = static_cast<float>(
            next < g_event_effect_state->background_target_y_e0()
                ? next
                : g_event_effect_state->background_target_y_e0());
    } else if (background_y_104 > g_event_effect_state->background_target_y_e0()) {
        const double next = background_y_104 - 0.01f;
        background_y_104 = static_cast<float>(
            next > g_event_effect_state->background_target_y_e0()
                ? next
                : g_event_effect_state->background_target_y_e0());
    }

    if (background_z_108 < g_event_effect_state->background_target_z_e4()) {
        const double next = background_z_108 + 0.01f;
        background_z_108 = static_cast<float>(
            next < g_event_effect_state->background_target_z_e4()
                ? next
                : g_event_effect_state->background_target_z_e4());
    } else if (background_z_108 > g_event_effect_state->background_target_z_e4()) {
        const double next = background_z_108 - 0.01f;
        background_z_108 = static_cast<float>(
            next > g_event_effect_state->background_target_z_e4()
                ? next
                : g_event_effect_state->background_target_z_e4());
    }

    g_event_effect_state->update_background_entries_469b70();

    if (!renderers_28.empty()) {
        if (renderers_28.size() > 1) {
            std::list<BackgroundBase *>::iterator it = renderers_28.begin();
            while (it != renderers_28.end()) {
                {
                    BackgroundBase *background = *it;
                    background->set_runtime_position(
                        background_x_100, background_y_104, background_z_108);
                }
                {
                    BackgroundBase *background = *it;
                    background->set_runtime_offset(
                        background_offset_x_10c, background_offset_y_110);
                }
                (*it)->step_transition_4656a0();

                if ((*it)->transition_state_5c == 3) {
                    owned_34.push_back(*it);
                    SetEvent(event_b_24);
                    it = renderers_28.erase(it);
                } else {
                    (*it)->slot_04();
                    ++it;
                }
            }
        } else {
            renderers_28.front()->set_runtime_position(
                background_x_100, background_y_104, background_z_108);
            renderers_28.front()->set_runtime_offset(
                background_offset_x_10c, background_offset_y_110);
            renderers_28.front()->step_transition_4656a0();
            renderers_28.front()->slot_04();
        }
    }

    ++runtime_tick_114;
}

} // namespace th105
