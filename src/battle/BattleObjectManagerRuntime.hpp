#pragma once

#include "battle/BattleRenderHelpers.hpp"

#include <list>
#include <windows.h>
#include <stddef.h>

namespace th105 {

struct BattleRenderRequest {
    unsigned kind_00;
    float value_04;
};

struct BattleOwnedObject {
    virtual ~BattleOwnedObject();
};

struct BattleThreadHandle {
    HANDLE handle_00;
    unsigned thread_id_04;

    BattleThreadHandle();
    ~BattleThreadHandle();
    bool start(LPTHREAD_START_ROUTINE proc, void *argument);
    void wait_for_exit();
    int set_priority(int priority);
};

struct BattleBaseEffect {
    void *vptr_00;
    void *effect_04;

    BattleBaseEffect();
    ~BattleBaseEffect();
    bool initialize(const void *data, unsigned size);
    void shutdown();
};

struct BattleObjectManager {
    std::list<BattleRenderRequest> render_requests_00;
    unsigned char running_0c;
    unsigned char reserved_0d[3];
    BattleThreadHandle worker_a_10;
    BattleThreadHandle worker_b_18;
    HANDLE event_a_20;
    HANDLE event_b_24;
    std::list<BackgroundBase *> renderers_28;
    std::list<BackgroundBase *> owned_34;
    BattleBaseEffect effect_40;
    unsigned char render_state_48[0x90];
    unsigned texture_a_d8;
    unsigned texture_b_dc;
    float drift_e0;
    float drift_e4;
    float drift_e8;
    float drift_ec;
    unsigned char reserved_f0[0x08];
    unsigned char effect_level_f8;
    unsigned char reserved_f9[0x03];
    int effect_level_delta_fc;
    float background_x_100;
    float background_y_104;
    float background_z_108;
    float background_offset_x_10c;
    float background_offset_y_110;
    unsigned runtime_tick_114;

    BattleObjectManager();
    ~BattleObjectManager();

    void phase_466980();
    void phase_4669f0();
    void phase_466a50();
    void update_background_runtime_466f40();
    void manager_worker_loop_466c70();
    void render_worker_loop_4677b0();

    void render_tail_4666a0();
    void dispatch_request_467380(unsigned kind, float value);
    void publish_stage(int stage, int count, bool notify);
};

typedef char BattleObjectManager_size_must_be_0x118[
    sizeof(BattleObjectManager) == 0x118 ? 1 : -1];
typedef char BattleObjectManager_running_offset_must_be_0x0c[
    offsetof(BattleObjectManager, running_0c) == 0x0c ? 1 : -1];
typedef char BattleObjectManager_worker_a_offset_must_be_0x10[
    offsetof(BattleObjectManager, worker_a_10) == 0x10 ? 1 : -1];
typedef char BattleObjectManager_event_a_offset_must_be_0x20[
    offsetof(BattleObjectManager, event_a_20) == 0x20 ? 1 : -1];
typedef char BattleObjectManager_renderers_offset_must_be_0x28[
    offsetof(BattleObjectManager, renderers_28) == 0x28 ? 1 : -1];
typedef char BattleObjectManager_owned_offset_must_be_0x34[
    offsetof(BattleObjectManager, owned_34) == 0x34 ? 1 : -1];
typedef char BattleObjectManager_effect_offset_must_be_0x40[
    offsetof(BattleObjectManager, effect_40) == 0x40 ? 1 : -1];
typedef char BattleObjectManager_texture_a_offset_must_be_0xd8[
    offsetof(BattleObjectManager, texture_a_d8) == 0xd8 ? 1 : -1];

typedef char BattleObjectManager_drift_offset_must_be_0xe0[
    offsetof(BattleObjectManager, drift_e0) == 0xe0 ? 1 : -1];
typedef char BattleObjectManager_effect_level_offset_must_be_0xf8[
    offsetof(BattleObjectManager, effect_level_f8) == 0xf8 ? 1 : -1];
typedef char BattleObjectManager_background_x_offset_must_be_0x100[
    offsetof(BattleObjectManager, background_x_100) == 0x100 ? 1 : -1];
typedef char BattleObjectManager_runtime_tick_offset_must_be_0x114[
    offsetof(BattleObjectManager, runtime_tick_114) == 0x114 ? 1 : -1];

extern BattleObjectManager *g_battle_object_manager;
extern const unsigned char battle_object_effect_blob_6c2db8[];

DWORD WINAPI battle_object_render_worker_proc_4678d0(void *argument);
DWORD WINAPI battle_object_manager_worker_proc_466cf0(void *argument);

} // namespace th105
