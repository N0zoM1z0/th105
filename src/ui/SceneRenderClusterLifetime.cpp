// JP1.06a 0x0041F1F0. Implicit destruction of the observed owned members.
// Trailing-byte ownership in containing scenes is not inferred by this view.
#include "battle/ScriptCommandRegistry.hpp"
#include "ui/RenderTimeline.hpp"
#include "ui/SceneTimelineEntries.hpp"
#include <map>
#include <list>
#include <string>
#include <stddef.h>
namespace th105 {
struct SceneClusterLifetimeView {
    SceneTimelineRegistry timeline_00;
    std::map<int,RenderTimelineEntry *> objects_4c;
    std::list<RenderTimelineEntry> records_58;
    SceneTimelineEntries events_64;
    std::string music_path_70;
    unsigned char tail_8c[7];
};
typedef char CheckObjectsOffset[offsetof(SceneClusterLifetimeView,objects_4c)==0x4c?1:-1];
typedef char CheckRecordsOffset[offsetof(SceneClusterLifetimeView,records_58)==0x58?1:-1];
typedef char CheckEventsOffset[offsetof(SceneClusterLifetimeView,events_64)==0x64?1:-1];
typedef char CheckPathOffset[offsetof(SceneClusterLifetimeView,music_path_70)==0x70?1:-1];
// Emission only: no native address/credit or target allocation is assigned.
void destroy_scene_cluster_emission_probe(SceneClusterLifetimeView *value)
{
    delete value;
}
}
