#include "SceneTransitionState.hpp"

namespace th105 {

extern int g_async_scene_load_request;
extern float g_scene_fade_value;
extern float g_scene_fade_delta;
extern unsigned int g_scene_fade_color;

int get_async_scene_load_request()
{
    return g_async_scene_load_request;
}

void start_scene_fade_out(unsigned int color, int duration)
{
    if (duration > 0) {
        g_scene_fade_color = color;
        g_scene_fade_delta = -1.0 / duration;
    } else {
        g_scene_fade_value = 0.0f;
        g_scene_fade_color = color;
        g_scene_fade_delta = 0.0f;
    }
}

void start_scene_fade_in(unsigned int color, int duration)
{
    if (duration > 0) {
        g_scene_fade_color = color;
        g_scene_fade_delta = 1.0 / duration;
    } else {
        g_scene_fade_value = 1.0f;
        g_scene_fade_color = color;
        g_scene_fade_delta = 0.0f;
    }
}

int is_scene_fade_in_progress()
{
    return g_scene_fade_delta > 0.0f;
}

} // namespace th105
