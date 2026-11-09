#pragma once

namespace th105 {

class CFade;
// Historical binding name: application +78 holds the shared fade pointer.
extern "C" CFade *g_active_scene_id;

class IScene {
public:
    virtual ~IScene()
    {
    }

    virtual int update();
    virtual bool render();
    virtual void unknown_scene_method();
    virtual void on_scene_enter(int previous_scene);
    virtual void on_scene_exit(int next_scene);
};

class CSceneBase : public IScene {
public:
    CSceneBase() : fade_04(g_active_scene_id) {}

    virtual int update();
    virtual bool render();
    virtual void unknown_scene_method();
    virtual void on_scene_enter(int previous_scene);
    virtual void on_scene_exit(int next_scene);

    int advance_battle_setup_state();
    int map_battle_setup_state_to_scene();

    CFade *fade_04;
};

} // namespace th105
