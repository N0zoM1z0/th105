#include "audio/BgmStreamRuntime.cpp"
#include "assets/ResourceHandleLookupRuntime.cpp"
namespace th105 {
// Pointer-only wave service prefix; no construction or storage ownership.
struct WaveHandleGainView {
    unsigned char first_manager_000[0x64];
    CHandleManagerLookupView handles_064;
    unsigned char buffers_counters_0c8[0x388];
    float gain_450, gain_454;
    void set_handle_gain(unsigned handle, float gain);
};
typedef char WaveHandleGainOffset[offsetof(WaveHandleGainView,gain_450)==0x450?1:-1];
void WaveHandleGainView::set_handle_gain(unsigned handle, float gain)
{
    if (!handle) return;
    float effective = gain_450 * gain;
    long volume = effective <= bgm_minimum_gain ? -10000 : linear_gain_to_ds_volume(effective);
    BgmBufferRuntime *buffer = static_cast<BgmBufferRuntime *>(*handles_064.lookup_token_417800(handle));
    buffer->set_volume(volume);
}
}
