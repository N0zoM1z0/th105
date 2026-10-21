#include "DesignBaseLifetime.hpp"

namespace th105 {

// The distinct 420B90 body uses the same native map and checked iterator ABI.
// Original method spelling and source partition remain unknown.
void CDesignBase::bind_object_alt(UiDesignObject **object, int object_id)
{
    std::map<unsigned int, UiDesignObject *>::iterator it =
        object_tree_20.find(object_id);
    if (it == object_tree_20.end())
        *object = 0;
    else
        *object = it->second;
}

} // namespace th105
