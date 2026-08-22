#pragma once

#include "engine/SceneBase.hpp"

namespace th105 {

class CBattle : public IScene {
public:
    CBattle();
    virtual ~CBattle();

    virtual int update();
    virtual bool render();
    virtual void unknown_scene_method();
    virtual void on_scene_enter(int previous_scene);
    virtual void on_scene_exit(int next_scene);

protected:
    void *&battle_peer_08()
    {
        return *reinterpret_cast<void **>(
            reinterpret_cast<unsigned char *>(this) + 0x08);
    }
};

class CBattleSV : public CBattle {
public:
    CBattleSV();
    virtual int update();
    virtual void on_scene_enter(int previous_scene);
};

class CBattleCL : public CBattle {
public:
    CBattleCL();
    virtual int update();
    virtual void on_scene_enter(int previous_scene);
};

class CBattleWatch : public CBattle {
public:
    CBattleWatch();
    virtual int update();
    virtual void on_scene_enter(int previous_scene);
};

class CLoadingWatch : public IScene {
public:
    virtual int update();
    virtual bool render();
    virtual void unknown_scene_method();
    virtual void on_scene_enter(int previous_scene);
    virtual void on_scene_exit(int next_scene);

private:
    unsigned short &timer_9c()
    {
        return *reinterpret_cast<unsigned short *>(
            reinterpret_cast<unsigned char *>(this) + 0x9c);
    }

    int &state_a0()
    {
        return *reinterpret_cast<int *>(
            reinterpret_cast<unsigned char *>(this) + 0xa0);
    }
};

} // namespace th105
