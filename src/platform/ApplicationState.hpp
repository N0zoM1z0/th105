#pragma once

#include "platform/ApplicationStartupOptions.hpp"
#include "platform/BattleThreadHandle.hpp"
#include "engine/CriticalSectionWrapper.hpp"
#include <list>

namespace th105 {
class IScene;
class CSceneManager;
class CFade;

// Native application singleton at 702820. Its shutdown method is separate
// from the automatic member destruction registered with the CRT.
struct ApplicationState {
    ApplicationState();

    void *window_00, *instance_04;
    ApplicationStartupOptions options_08;
    int control_fps_030, control_count_034;
    unsigned long timestamp_038;
    int render_fps_03c, present_fps_040, render_count_044, present_count_048;
    bool running_04c;
    BattleThreadHandle control_050, graphics_058;
    void *event_060;
    BattleThreadHandle scene_creation_064, scene_disposal_06c;
    CSceneManager *manager_074;
    CFade *fade_078;
    IScene *previous_scene_07c, *pending_scene_080;
    std::list<IScene *> retired_scenes_084;
    void *retired_event_090;
    CriticalSectionWrapper scene_lock_094;
    int requested_state_0b0, active_state_0b4;
};

typedef char ApplicationStateSize[sizeof(ApplicationState) == 0xb8 ? 1 : -1];
typedef char ApplicationStateOptions[offsetof(ApplicationState, options_08) == 8 ? 1 : -1];
typedef char ApplicationStateThreads[offsetof(ApplicationState, control_050) == 0x50 ? 1 : -1];
typedef char ApplicationStateFade[offsetof(ApplicationState, fade_078) == 0x78 ? 1 : -1];
typedef char ApplicationStateList[offsetof(ApplicationState, retired_scenes_084) == 0x84 ? 1 : -1];
typedef char ApplicationStateLock[offsetof(ApplicationState, scene_lock_094) == 0x94 ? 1 : -1];
} // namespace th105
