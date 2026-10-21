#include "DesignBaseLifetime.hpp"

namespace th105 {

// The loader's list element interface shares the observed IColor prefix.
// Slot +10 renders with an offset; slot +14 renders at the stored position.
struct UiDesignObject : public DesignColorLifetimeView {
    virtual void render_offset(float x, float y);
    virtual void render();
};

void CDesignBase::set_vertex_colors(const unsigned int *colors)
{
    for (std::list<UiDesignObject *>::iterator it = objects_14.begin();
         it != objects_14.end(); ++it) {
        (*it)->set_vertex_colors(colors);
    }
}

void CDesignBase::multiply_color(unsigned int color)
{
    for (std::list<UiDesignObject *>::iterator it = objects_14.begin();
         it != objects_14.end(); ++it) {
        (*it)->multiply_color(color);
    }
}

void CDesignBase::render_offset(float x, float y)
{
    while (current_2c != objects_14.end()) {
        (*current_2c)->render_offset(x, y);
        ++current_2c;
    }
    current_2c = objects_14.begin();
}

void CDesignBase::render()
{
    while (current_2c != objects_14.end()) {
        (*current_2c)->render();
        ++current_2c;
    }
    current_2c = objects_14.begin();
}

void CDesignBase::find_object(UiDesignObject **object, int object_id)
{
    std::map<unsigned int, UiDesignObject *>::iterator it = object_tree_20.find(object_id);
    if (it == object_tree_20.end())
        *object = 0;
    else
        *object = it->second;
}

void CDesignBase::render_through(unsigned int object_id)
{
    UiDesignObject *last;
    find_object(&last, object_id);
    while (current_2c != objects_14.end()) {
        (*current_2c)->render();
        if (*current_2c == last) {
            ++current_2c;
            break;
        }
        ++current_2c;
    }
    if (current_2c == objects_14.end())
        current_2c = objects_14.begin();
}

void CDesignBase::render_offset_through(float x, float y, unsigned int object_id)
{
    UiDesignObject *last;
    find_object(&last, object_id);
    while (current_2c != objects_14.end()) {
        (*current_2c)->render_offset(x, y);
        if (*current_2c == last) {
            ++current_2c;
            break;
        }
        ++current_2c;
    }
    if (current_2c == objects_14.end())
        current_2c = objects_14.begin();
}

} // namespace th105
