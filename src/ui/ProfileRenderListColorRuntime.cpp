#include <list>
#include <stddef.h>

namespace th105 {

struct ProfileRenderColorItem {
    virtual void slot_00();
    virtual void set_color(unsigned int color);
};

struct ProfileRenderListColorRuntimeView {
    unsigned char reserved_000[0x14];
    std::list<ProfileRenderColorItem *> objects_014;

    void set_color(unsigned int color);
};

void ProfileRenderListColorRuntimeView::set_color(unsigned int color)
{
    for (std::list<ProfileRenderColorItem *>::iterator it = objects_014.begin();
         it != objects_014.end(); ++it) {
        (*it)->set_color(color);
    }
}

typedef char ProfileRenderListObjectsOffset[
    offsetof(ProfileRenderListColorRuntimeView, objects_014) == 0x14 ? 1 : -1];

} // namespace th105
