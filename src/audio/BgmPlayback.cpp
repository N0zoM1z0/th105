#include <cstring>

namespace th105 {

struct String28CallGate {
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
