#include "InputCluster.hpp"

#include <cstdlib>

namespace th105 {

void CInputManagerCluster::merge_menu_input_sources()
{
    counters[0] = 0;
    counters[1] = 0;
    counters[2] = 0;
    counters[3] = 0;
    counters[4] = 0;
    counters[5] = 0;
    counters[6] = 0;
    counters[7] = 0;
    counters[8] = 0;
    counters[9] = 0;

    for (unsigned i = 0; i < sources.size(); i++) {
        if (std::abs(hold.horizontal) <
            std::abs(sources.at(i)->hold.horizontal)) {
            hold.horizontal = sources.at(i)->hold.horizontal;
            active_source = sources.at(i)->bindings.source_id;
        }
        if (std::abs(hold.vertical) <
            std::abs(sources.at(i)->hold.vertical)) {
            hold.vertical = sources.at(i)->hold.vertical;
            active_source = sources.at(i)->bindings.source_id;
        }
        for (unsigned button = 0; button < 8; button++) {
            if (static_cast<unsigned>(hold.buttons[button]) <
                static_cast<unsigned>(sources.at(i)->hold.buttons[button])) {
                active_source = sources.at(i)->bindings.source_id;
                hold.buttons[button] = sources.at(i)->hold.buttons[button];
            }
        }
    }
}

} // namespace th105
