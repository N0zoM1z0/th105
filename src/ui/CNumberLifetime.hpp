#pragma once

#include "Tile.hpp"
#include <new>
#include <stddef.h>

namespace th105 {


// Native CNumber, CTile and CSprite share the actual IColor interface.
// Keep the legacy alias spelling, not a second source interface identity.
typedef ::IColor CNumberColorLifetime;

class CNumberLifetime : public CNumberColorLifetime {
public:
    CNumberLifetime();
    virtual ~CNumberLifetime()
    {
        if (number_value_24 != 0)
            operator delete(number_value_24);
    }

    virtual void set_color(unsigned int color);
    virtual void set_vertex_colors(const unsigned int *colors);
    virtual void multiply_color(unsigned int color);

public:
    // Public only so this narrow reconstruction view can assert target offsets.
    float glyph_width_04;
    float spacing_08;
    float scale_0c;
    float secondary_scale_10;
    int columns_14;
    int reserved_18;
    int reserved_1c;
    unsigned char mode_20;
    unsigned char reserved_21[3];
    void *number_value_24;
    CTile tile_28;
};

typedef char CNumberColorLifetime_size_must_be_0x04[
    sizeof(CNumberColorLifetime) == 0x04 ? 1 : -1];
typedef char CNumber_tile_size_must_be_0xa4[
    sizeof(CTile) == 0xA4 ? 1 : -1];
typedef char CNumberLifetime_size_must_be_0xcc[
    sizeof(CNumberLifetime) == 0xCC ? 1 : -1];
typedef char CNumberLifetime_value_offset_must_be_0x24[
    offsetof(CNumberLifetime, number_value_24) == 0x24 ? 1 : -1];
typedef char CNumberLifetime_tile_offset_must_be_0x28[
    offsetof(CNumberLifetime, tile_28) == 0x28 ? 1 : -1];

} // namespace th105
