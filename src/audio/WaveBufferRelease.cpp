#include "audio/DirectSound.hpp"
#include <stddef.h>
namespace th105 {
struct WaveBufferSlot {
    virtual bool initialize(const void *,unsigned);
    virtual ~WaveBufferSlot();
    DirectSoundBuffer8 *buffer_04;
    unsigned size_08;
};
struct SpatialWaveBufferSlot : WaveBufferSlot {
    UnknownInterface *spatial_0c;
};
struct WaveBufferReleaseView {
    unsigned char prefix_000[0xc8];
    WaveBufferSlot ordinary_0c8[32];
    SpatialWaveBufferSlot spatial_248[32];
    void release_buffers();
};
typedef char WaveBufferSlot_size[sizeof(WaveBufferSlot)==12?1:-1];
typedef char SpatialWaveBufferSlot_size[sizeof(SpatialWaveBufferSlot)==16?1:-1];
typedef char WaveBufferRelease_spatial_offset[offsetof(WaveBufferReleaseView,spatial_248)==0x248?1:-1];
void WaveBufferReleaseView::release_buffers()
{
    for (int i=0; i<32; ++i) {
        if (ordinary_0c8[i].buffer_04 != 0) {
            ordinary_0c8[i].buffer_04->release();
            ordinary_0c8[i].buffer_04=0;
        }
        if (spatial_248[i].spatial_0c != 0) {
            spatial_248[i].spatial_0c->release();
            spatial_248[i].spatial_0c=0;
        }
        if (spatial_248[i].buffer_04 != 0) {
            spatial_248[i].buffer_04->release();
            spatial_248[i].buffer_04=0;
        }
    }
}
}
