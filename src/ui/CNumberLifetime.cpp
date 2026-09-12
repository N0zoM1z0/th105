#include <new>
#include <stddef.h>

namespace th105 {

// RTTI for the target CNumber hierarchy proves a single zero-offset IColor
// base. Keep a narrow lifetime view here so the existing render/layout model
// does not need to manufacture vptr writes by hand.
class CNumberColorLifetime {
public:
    virtual ~CNumberColorLifetime() {}
    virtual void set_color(unsigned int color) = 0;
    virtual void set_vertex_colors(const unsigned int *colors) = 0;
    virtual void multiply_color(unsigned int color) = 0;
};

class CNumberTileLifetime : public CNumberColorLifetime {
public:
    virtual void set_color(unsigned int color);
    virtual void set_vertex_colors(const unsigned int *colors);
    virtual void multiply_color(unsigned int color);

private:
    unsigned char payload_04[0xA0];
};

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
    CNumberTileLifetime tile_28;
};

CNumberLifetime::CNumberLifetime() : number_value_24(0) {}

void CNumberLifetime::set_color(unsigned int color)
{
    tile_28.set_color(color);
}

void CNumberLifetime::set_vertex_colors(const unsigned int *colors)
{
    tile_28.set_vertex_colors(colors);
}

void CNumberLifetime::multiply_color(unsigned int color)
{
    tile_28.multiply_color(color);
}

typedef char CNumberColorLifetime_size_must_be_0x04[
    sizeof(CNumberColorLifetime) == 0x04 ? 1 : -1];
typedef char CNumberTileLifetime_size_must_be_0xa4[
    sizeof(CNumberTileLifetime) == 0xA4 ? 1 : -1];
typedef char CNumberLifetime_size_must_be_0xcc[
    sizeof(CNumberLifetime) == 0xCC ? 1 : -1];
typedef char CNumberLifetime_value_offset_must_be_0x24[
    offsetof(CNumberLifetime, number_value_24) == 0x24 ? 1 : -1];
typedef char CNumberLifetime_tile_offset_must_be_0x28[
    offsetof(CNumberLifetime, tile_28) == 0x28 ? 1 : -1];

} // namespace th105
