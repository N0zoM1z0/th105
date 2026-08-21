#include "BgmTransition.hpp"

namespace th105 {

struct BgmServiceView {
    void stop(int handle);
    void fade(int handle, int duration, int target, bool enabled);
    void set_level(int handle, int first, int unused, float value);
};

extern int g_bgm_handle;
extern BgmServiceView g_bgm_service;

void stop_bgm()
{
    g_bgm_service.stop(g_bgm_handle);
}

void fade_bgm(int duration, int target)
{
    g_bgm_service.fade(g_bgm_handle, duration, target, true);
    g_bgm_handle = 0;
}

void set_bgm_volume(int first, int percent)
{
    float value = static_cast<float>(percent / 100.0);
    g_bgm_service.set_level(g_bgm_handle, first, 0, value);
}

} // namespace th105
