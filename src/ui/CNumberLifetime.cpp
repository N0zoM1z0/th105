#include "ui/CNumberLifetime.hpp"
#include "DesignObjects.hpp"

namespace th105 {

void CNumber::set_color(unsigned int color)
{
    tile_28.set_color(color);
}

void CNumber::set_vertex_colors(const unsigned int *colors)
{
    tile_28.set_vertex_colors(colors);
}

void CNumber::multiply_color(unsigned int color)
{
    tile_28.multiply_color(color);
}

} // namespace th105

#include "DesignNumberConstructor.cpp"
