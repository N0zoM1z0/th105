#include "ConfigAudioHelpers.hpp"

namespace th105 {

void apply_bgm_percent(int value)
{
    const float scaled = static_cast<float>(
        static_cast<double>(value) * 0.01f * 0.75);
    g_bgm_volume_service.set_volume(scaled);
}

void apply_se_percent(int value)
{
    const float scaled = static_cast<float>(
        static_cast<double>(value) * 0.01f * 0.75);
    g_sound_volume_service.set_master_volume(scaled);
    unsigned *current = g_indexed_event_handles;
    do {
        g_sound_volume_service.set_handle_volume(*current, 1.0f);
        ++current;
    } while (reinterpret_cast<int>(current) <
             reinterpret_cast<int>(g_indexed_event_handles + 128));
}

} // namespace th105
