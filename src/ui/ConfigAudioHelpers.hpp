#pragma once

namespace th105 {
struct BgmVolumeService {
    void set_volume(float value);
};
struct SoundVolumeService {
    void set_master_volume(float value);
    void set_handle_volume(unsigned handle, float value);
};

extern BgmVolumeService g_bgm_volume_service;
extern SoundVolumeService g_sound_volume_service;
extern unsigned g_indexed_event_handles[128];

void apply_bgm_percent(int value);
void apply_se_percent(int value);
} // namespace th105
