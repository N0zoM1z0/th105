#pragma once
#include "SceneTimelineEntries.hpp"
#include <list>
#include <map>
#include <string>
namespace th105 {
struct SceneTimeline40Update {
    unsigned int reserved_00;
    unsigned int start_tick_04;
    unsigned int elapsed_08;
    unsigned char reserved_0c[0x34];
};
typedef char SceneTimeline40Update_size[sizeof(SceneTimeline40Update)==0x40?1:-1];

struct SceneListRecord124Update {
    unsigned char reserved_00[0x74];
    unsigned int quotient_74;
    unsigned int divisor_78;
};

class SceneRenderClusterUpdateView {
public:
    bool update_451400();
    float apply_easing(int mode, float value);
    void interpolate_scene_byte_4501b0(
        unsigned char *output,
        unsigned char *current,
        const SceneInterpolationEntry24 *entry,
        unsigned int elapsed);
    void interpolate_scene_float_450290(
        float *output,
        float *current,
        const SceneInterpolationEntry24 *entry,
        unsigned int elapsed);

    SceneTimeline40Update timeline_00;
    unsigned int field_40;
    unsigned char flag_44;
    unsigned char reserved_45[7];
    std::map<int, void *> objects_4c;
    std::list<SceneListRecord124Update> records_58;
    SceneTimelineEntries values_64;
    std::string path_70;
    unsigned int field_8c;
    unsigned char flag_90;
    unsigned char flag_91;
    unsigned char flag_92;
    unsigned char flag_93;
};

} // namespace th105
