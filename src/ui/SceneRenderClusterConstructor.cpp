#include "battle/ScriptCommandRegistry.hpp"

#include <list>
#include <map>
#include <string>

namespace th105 {

struct SceneListRecord124 {
    unsigned char bytes[0x7C];
};

struct SceneMapValue20 {
    unsigned char bytes[20];
};

struct SceneRenderClusterConstructorLayout {
    SceneTimelineRegistry timeline_00;
    std::map<int, void *> objects_4c;
    std::list<SceneListRecord124> records_58;
    std::map<int, SceneMapValue20> values_64;
    std::string path_70;
    unsigned char tail_8c[7];

    SceneRenderClusterConstructorLayout();
};

SceneRenderClusterConstructorLayout::SceneRenderClusterConstructorLayout()
{
}

typedef char SceneRenderClusterConstructorLayout_size[
    sizeof(SceneRenderClusterConstructorLayout) == 0x94 ? 1 : -1];
typedef char SceneRenderClusterConstructorLayout_objects[
    offsetof(SceneRenderClusterConstructorLayout, objects_4c) == 0x4C ? 1 : -1];
typedef char SceneRenderClusterConstructorLayout_records[
    offsetof(SceneRenderClusterConstructorLayout, records_58) == 0x58 ? 1 : -1];
typedef char SceneRenderClusterConstructorLayout_values[
    offsetof(SceneRenderClusterConstructorLayout, values_64) == 0x64 ? 1 : -1];
typedef char SceneRenderClusterConstructorLayout_path[
    offsetof(SceneRenderClusterConstructorLayout, path_70) == 0x70 ? 1 : -1];

} // namespace th105
