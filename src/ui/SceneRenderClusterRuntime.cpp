#include "SceneRenderClusterRuntime.hpp"
#include <list>
#include <map>
#include <set>
#include <string>
#include <stddef.h>

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
extern "C" void __cdecl begin_scene_timeline(const char *path);
extern "C" void __cdecl set_scene_timeline_mode(int mode);

namespace th105 {

struct SceneAnimatedObjectUpdateView {
    unsigned char reserved_00[0x28];
    float current_28;
    float current_2c;
    float current_30;
    float current_34;
    float current_38;
    float current_3c;
    float current_40;
    float output_44;
    float output_48;
    float output_4c;
    float output_50;
    unsigned char output_byte_54;
    unsigned char current_byte_55;
    unsigned char output_byte_56;
    unsigned char current_byte_57;
    unsigned char output_byte_58;
    unsigned char current_byte_59;
    unsigned char output_byte_5a;
    unsigned char current_byte_5b;
    float output_5c;
    float output_60;
    float output_64;
    unsigned char reserved_68[0x24];
    unsigned char active_8c;
};

typedef char SceneInterpolationEntry24_size[
    sizeof(SceneInterpolationEntry24) == 0x18 ? 1 : -1];
typedef char SceneListRecord124Update_size[
    sizeof(SceneListRecord124Update) == 0x7c ? 1 : -1];
typedef char SceneRenderClusterUpdateView_size[
    sizeof(SceneRenderClusterUpdateView) == 0x94 ? 1 : -1];

bool SceneRenderClusterUpdateView::update_451400()
{
    field_8c = 0;
    if (timeline_00.start_tick_04 == 0) {
        timeline_00.elapsed_08 = 0;
        begin_scene_timeline(path_70.c_str());
        set_scene_timeline_mode(0);
        timeline_00.start_tick_04 = timeGetTime();
    } else {
        unsigned int delta = timeGetTime() - timeline_00.start_tick_04;
        unsigned int elapsed = (delta + timeline_00.elapsed_08 + 16) >> 1;
        timeline_00.elapsed_08 = elapsed;
        if (elapsed >= *reinterpret_cast<unsigned int *>(
                reinterpret_cast<unsigned char *>(&timeline_00) + 0x0c))
            return false;
    }

    for (SceneTimelineEntries::iterator it = values_64.begin();
         it != values_64.end();) {
        if (timeline_00.elapsed_08 < it->start_04)
            break;

        if (it->type_14 == 16) {
            field_8c = 1;
        } else {
            SceneAnimatedObjectUpdateView *object =
                reinterpret_cast<SceneAnimatedObjectUpdateView *>(
                    objects_4c.find(it->object_id_00)->second);

            switch (it->type_14) {
            case 3:
                interpolate_scene_float_450290(
                    &object->current_28, &object->output_44,
                    &*it,
                    timeline_00.elapsed_08);
                break;
            case 4:
                interpolate_scene_float_450290(
                    &object->current_2c, &object->output_48,
                    &*it,
                    timeline_00.elapsed_08);
                break;
            case 7:
                interpolate_scene_byte_4501b0(
                    &object->output_byte_56, &object->current_byte_57,
                    &*it,
                    timeline_00.elapsed_08);
                break;
            case 8:
                interpolate_scene_byte_4501b0(
                    &object->output_byte_58, &object->current_byte_59,
                    &*it,
                    timeline_00.elapsed_08);
                break;
            case 9:
                interpolate_scene_byte_4501b0(
                    &object->output_byte_5a, &object->current_byte_5b,
                    &*it,
                    timeline_00.elapsed_08);
                break;
            case 5:
                interpolate_scene_float_450290(
                    &object->current_30, &object->output_4c,
                    &*it,
                    timeline_00.elapsed_08);
                break;
            case 6:
                interpolate_scene_float_450290(
                    &object->current_34, &object->output_50,
                    &*it,
                    timeline_00.elapsed_08);
                break;
            case 10:
                interpolate_scene_byte_4501b0(
                    &object->output_byte_54, &object->current_byte_55,
                    &*it,
                    timeline_00.elapsed_08);
                break;
            case 11:
                interpolate_scene_float_450290(
                    &object->current_38, &object->output_5c,
                    &*it,
                    timeline_00.elapsed_08);
                break;
            case 12:
                interpolate_scene_float_450290(
                    &object->current_3c, &object->output_60,
                    &*it,
                    timeline_00.elapsed_08);
                break;
            case 13:
                interpolate_scene_float_450290(
                    &object->current_40, &object->output_64,
                    &*it,
                    timeline_00.elapsed_08);
                break;
            default:
                break;
            }
        }

        if (timeline_00.elapsed_08 >= it->end_08)
            it = values_64.erase(it);
        else
            ++it;
    }

    for (std::list<SceneListRecord124Update>::iterator it = records_58.begin();
         it != records_58.end(); ++it)
        it->quotient_74 = timeline_00.elapsed_08 / it->divisor_78;

    return true;
}

} // namespace th105
