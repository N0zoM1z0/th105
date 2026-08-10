#pragma once

namespace th105 {

class CLoadingWatch {
public:
    virtual ~CLoadingWatch();

    virtual void on_scene_enter(int previous_scene);
};

} // namespace th105
