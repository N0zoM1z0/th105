#include "CNumberTileTextureOptions.cpp"

namespace th105 {
void CNumber::initialize(
    unsigned int texture,
    int left,
    int top,
    int right,
    int bottom,
    int columns,
    float spacing,
    int reserved_a,
    int reserved_b,
    int mode)
{
    columns_14 = columns;
    reserved_18 = reserved_a;
    reserved_1c = reserved_b;
    right -= left;
    glyph_width_04 = static_cast<float>(right);
    mode_20 = static_cast<unsigned char>(mode);
    spacing_08 = spacing;
    scale_0c = secondary_scale_10 = 1.0f;

    tile_28.set_texture_options(
        texture,
        left,
        top,
        right,
        bottom - top,
        0,
        0);
}


} // namespace th105

#include "CNumberIntegerRender.cpp"
