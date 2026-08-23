namespace th105 {

struct BgmVolumeService {
    int set_volume(float value);
};
struct SoundVolumeService {
    void set_master_volume(float value);
    int set_handle_volume(unsigned handle, float value);
};

extern BgmVolumeService g_bgm_volume_service;
extern SoundVolumeService g_sound_volume_service;
extern unsigned g_indexed_event_handles[128];

int apply_bgm_percent(int value)
{
    const float scaled = static_cast<float>(
        static_cast<double>(value) * 0.01f * 0.75);
    return g_bgm_volume_service.set_volume(scaled);
}

int apply_se_percent(int value)
{
    const float scaled = static_cast<float>(
        static_cast<double>(value) * 0.01f * 0.75);
    g_sound_volume_service.set_master_volume(scaled);
    unsigned *current = g_indexed_event_handles;
    int result;
    do {
        result = g_sound_volume_service.set_handle_volume(*current, 1.0f);
        ++current;
    } while (reinterpret_cast<int>(current) <
             reinterpret_cast<int>(g_indexed_event_handles + 128));
    return result;
}

} // namespace th105
