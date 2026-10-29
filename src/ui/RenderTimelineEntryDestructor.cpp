// JP1.06a 0x0041EC10. Release owned texture handles before deque cleanup.
#include "RenderTimeline.hpp"
#include "ui/Title.hpp"
namespace th105 {
RenderTimelineEntry::~RenderTimelineEntry()
{
    while (texture_handles_00.size() != 0) {
        g_title_resource_manager.release_title_resource_handle(texture_handles_00.front());
        texture_handles_00.pop_front();
    }
}
}
