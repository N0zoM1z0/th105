#include "assets/ResourceHandleManagerLifetime.hpp"
#include "audio/BgmStreamAllocation.cpp"
namespace th105 {
struct WaveServiceLifetime {
    ResourceHandleManagerLifetime64<WaveBufferResource *> wave_handles_000;
    ResourceHandleManagerLifetime64<SoundBufferResource *> sound_handles_064;
    DirectSoundResourceBaseLifetime buffers_0c8[32];
    DirectSoundResourceLifetime spatial_buffers_248[32];
    unsigned next_448, next_44c;
    float gain_450, gain_454;
    WaveServiceLifetime();
    ~WaveServiceLifetime();
};
WaveServiceLifetime::WaveServiceLifetime() {}
WaveServiceLifetime::~WaveServiceLifetime() {}
WaveServiceLifetime g_wave_service_lifetime;
typedef char WaveServiceSize[sizeof(WaveServiceLifetime)==0x458?1:-1];
typedef char WaveServiceSecondManager[offsetof(WaveServiceLifetime,sound_handles_064)==0x64?1:-1];
typedef char WaveServiceBaseArray[offsetof(WaveServiceLifetime,buffers_0c8)==0xc8?1:-1];
typedef char WaveServiceSpatialArray[offsetof(WaveServiceLifetime,spatial_buffers_248)==0x248?1:-1];
typedef char WaveServiceCounter[offsetof(WaveServiceLifetime,next_448)==0x448?1:-1];
typedef char WaveServiceGain[offsetof(WaveServiceLifetime,gain_450)==0x450?1:-1];
}
