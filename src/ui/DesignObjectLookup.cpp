#include "DesignBaseLifetime.hpp"

namespace th105 {
void CDesignBase::find_object(UiDesignObject **object, int object_id)
{
    std::map<unsigned int, UiDesignObject *>::iterator it = object_tree_20.find(object_id);
    if (it == object_tree_20.end())
        *object = 0;
    else
        *object = it->second;
}

} // namespace th105
