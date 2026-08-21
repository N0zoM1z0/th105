#pragma once

namespace th105 {

int get_async_scene_load_request();
void start_scene_fade_out(unsigned int color, int duration);
void start_scene_fade_in(unsigned int color, int duration);
int is_scene_fade_in_progress();

} // namespace th105
