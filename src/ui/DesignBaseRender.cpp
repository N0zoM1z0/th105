#include "DesignBaseLifetime.hpp"

namespace th105 {

// The loader's list element interface shares the observed IColor prefix.
// Slot +10 renders with an offset; slot +14 renders at the stored position.
struct UiDesignObject : public DesignColorLifetimeView {
    virtual void render_offset(float x, float y);
    virtual void render();
};

void CDesignBase::render()
{
    while (current_2c != objects_14.end()) {
        (*current_2c)->render();
        ++current_2c;
    }
    current_2c = objects_14.begin();
}

} // namespace th105
