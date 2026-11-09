#include "DesignBaseLifetime.hpp"

namespace th105 {

struct UiDesignObject : public DesignColorLifetimeView {
    virtual void render_offset(float x, float y);
    virtual void render();
};

void CDesignBase::set_color(unsigned int color)
{
    for (std::list<UiDesignObject *>::iterator it = objects_14.begin();
         it != objects_14.end(); ++it) {
        (*it)->set_color(color);
    }
}

} // namespace th105
