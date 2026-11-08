#include "EventEffectStateData.hpp"

namespace th105 {

void EventEffectStateData::update_background_entries_469b70()
{
    std::deque<BackgroundRenderEntry>::iterator entry =
        background_entries_28.begin();
    ++entry;

    while (entry != background_entries_28.end()) {
        if (entry->alpha != 0) {
            entry->alpha -= 15;
            ++entry;
        } else {
            entry = background_entries_28.erase(entry);
        }
    }

    emitter_48.update_effects();
}

} // namespace th105
