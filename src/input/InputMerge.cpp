#include "InputCluster.hpp"

#include <cstdlib>
#include <cstring>

namespace th105 {

void CInputManagerCluster::merge_menu_input_sources()
{
    std::memset(&hold, 0, sizeof(hold));

    for (int i = 0; i < sources.size(); i++) {
        if (std::abs(hold.horizontal) <
            std::abs(sources.begin()[i]->hold.horizontal)) {
            hold.horizontal = sources.begin()[i]->hold.horizontal;
            active_source = sources.begin()[i]->bindings.source_id;
        }
        if (std::abs(hold.vertical) <
            std::abs(sources.begin()[i]->hold.vertical)) {
            hold.vertical = sources.begin()[i]->hold.vertical;
            active_source = sources.begin()[i]->bindings.source_id;
        }
        for (int button = 0; button < 8; button++) {
            if (static_cast<unsigned>(hold.buttons[button]) <
                static_cast<unsigned>(
                    sources.begin()[i]->hold.buttons[button])) {
                active_source = sources.begin()[i]->bindings.source_id;
                hold.buttons[button] =
                    sources.begin()[i]->hold.buttons[button];
            }
        }
    }
}

} // namespace th105
