#include <cstring>

namespace th105 {

struct String28CallGate {
    unsigned char allocator_00[4];
    union {
        char inline_buffer[16];
        const char *allocated_data;
    } storage_04;
    unsigned size_14;
    unsigned capacity_18;

    void assign(const char *source, unsigned source_size);
};

struct BgmHandleResult {
    unsigned value;
};

struct BgmPlaybackServiceView {
    BgmHandleResult allocate_handle();
    void play(unsigned handle, const char *path, bool queued, float gain);
    void schedule_or_start(unsigned handle, int delay);
    void fade(unsigned handle, int duration, int target, bool enabled);
};

struct ScoreDataBgmView {
    void publish_bgm_path(const char *path);
};

extern String28CallGate g_bgm_source_path;
extern BgmPlaybackServiceView g_bgm_service;
extern ScoreDataBgmView g_score_data;
extern int g_bgm_handle;

unsigned __cdecl case_insensitive_crc32(
    const unsigned char *bytes,
    int length);

unsigned __cdecl current_info_effect_key_43bb90()
{
    const unsigned char *source = reinterpret_cast<const unsigned char *>(
        g_bgm_source_path.storage_04.allocated_data);
    if (g_bgm_source_path.capacity_18 < 16)
        source = reinterpret_cast<const unsigned char *>(
            g_bgm_source_path.storage_04.inline_buffer);
    return case_insensitive_crc32(
        source,
        static_cast<int>(g_bgm_source_path.size_14));
}

extern "C" void __cdecl load_bgm_source(const char *path)
{
    const char *source = path;
    if (source != 0) {
        g_bgm_source_path.assign(source, std::strlen(source));
        if (g_bgm_handle != 0)
            g_bgm_service.fade(g_bgm_handle, 1000, 0, true);
        g_bgm_handle = g_bgm_service.allocate_handle().value;
        g_bgm_service.play(g_bgm_handle, source, false, 1.0f);
        g_score_data.publish_bgm_path(source);
    }
}

extern "C" void __cdecl play_bgm(const char *path)
{
    const char *source = path;
    if (source != 0) {
        g_bgm_source_path.assign(source, std::strlen(source));
        if (g_bgm_handle != 0)
            g_bgm_service.fade(g_bgm_handle, 1000, 0, true);
        g_bgm_handle = g_bgm_service.allocate_handle().value;
        g_bgm_service.play(g_bgm_handle, source, true, 1.0f);
        g_bgm_service.schedule_or_start(g_bgm_handle, 500);
        g_score_data.publish_bgm_path(source);
        return;
    }
    g_bgm_service.schedule_or_start(g_bgm_handle, 0);
}

} // namespace th105
