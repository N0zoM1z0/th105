#include "battle/ScriptCommandRegistry.hpp"
#include <list>
#include <map>
#include <string>

namespace th105 {

struct SceneListRecord124Cleanup { unsigned char bytes[0x7C]; ~SceneListRecord124Cleanup(); };
struct SceneMapValue20Cleanup { unsigned char bytes[20]; };

struct SceneRenderClusterCleanupView {
    SceneTimelineRegistry timeline_00;
    std::map<int, void *> objects_4c;
    std::list<SceneListRecord124Cleanup> records_58;
    std::map<int, SceneMapValue20Cleanup> values_64;
    std::string path_70;
    unsigned char tail_8c[7];

    void cleanup_452e60();
};

void SceneRenderClusterCleanupView::cleanup_452e60()
{
    values_64.clear();
    records_58.clear();
    objects_4c.clear();
    timeline_00.script_18.clear_commands();
}

typedef char SceneRenderClusterCleanupView_size[
    sizeof(SceneRenderClusterCleanupView) == 0x94 ? 1 : -1];
typedef char SceneRenderClusterCleanupView_values[
    offsetof(SceneRenderClusterCleanupView, values_64) == 0x64 ? 1 : -1];
}
