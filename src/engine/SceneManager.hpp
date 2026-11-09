#pragma once

namespace th105 {

struct ISceneManager {
    virtual void initialize();
    virtual void shutdown();
    virtual void update();
    virtual unsigned char render();
    virtual void *create_scene(int scene);
};

class CSceneManager : public ISceneManager {
public:
    virtual void initialize();
    virtual void shutdown();
    virtual void update();
    virtual unsigned char render();
    virtual void *create_scene(int scene);
};

typedef char SceneManagerInterfaceSize[sizeof(ISceneManager) == 4 ? 1 : -1];
typedef char SceneManagerAllocationSize[sizeof(CSceneManager) == 4 ? 1 : -1];

} // namespace th105
