#include "DesignBaseLifetime.hpp"
#include "Title.hpp"

namespace th105 {

struct UiDesignObject : public DesignColorLifetimeView {
    virtual void render_offset(float x, float y);
    virtual void render();
};

void CDesignBase::virtual_cleanup()
{
    while (!objects_14.empty()) {
        delete objects_14.back();
        objects_14.pop_back();
    }
    for (unsigned int index = 0; index < texture_handles_04.size(); ++index)
        g_title_resource_manager.release_title_resource_handle(
            texture_handles_04.at(index));
    texture_handles_04.erase(texture_handles_04.begin(), texture_handles_04.end());
}

} // namespace th105
