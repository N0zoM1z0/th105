#include "audio/BgmStreamRuntime.cpp"
#include "assets/ResourceHandleLookupRuntime.cpp"
namespace th105 {
struct WaveVolumeBuffer12 {
    unsigned char unused_00[4];
    DirectSoundBuffer8 *buffer_04;
    unsigned state_08;
};
struct WaveVolumeSpatial16 {
    WaveVolumeBuffer12 base;
    void *spatial_0c;
};
struct WaveMasterGainView {
    unsigned char managers_000[0xc8];
    WaveVolumeBuffer12 buffers_0c8[32];
    WaveVolumeSpatial16 spatial_248[32];
    unsigned next_448, next_44c;
    float gain_450, gain_454;
    void set_master_gain(float gain);
};
typedef char WaveVolumeBaseSize[sizeof(WaveVolumeBuffer12)==12?1:-1];
typedef char WaveVolumeSpatialSize[sizeof(WaveVolumeSpatial16)==16?1:-1];
typedef char WaveMasterGainOffset[offsetof(WaveMasterGainView,gain_450)==0x450?1:-1];
void WaveMasterGainView::set_master_gain(float gain)
{
    if (gain < 0.0f) gain = 0.0f;
    else if (gain > 1.0f) gain = 1.0f;
    gain_450 = gain;
    float effective = gain_454 * gain_450;
    long volume = effective <= bgm_minimum_gain ? -10000 : linear_gain_to_ds_volume(effective);
    for (int i = 0; i < 32; ++i) {
        if (buffers_0c8[i].buffer_04) buffers_0c8[i].buffer_04->set_volume(volume);
        if (spatial_248[i].base.buffer_04) spatial_248[i].base.buffer_04->set_volume(volume);
    }
}
}
