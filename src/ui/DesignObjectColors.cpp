#include "DesignObjects.hpp"

void CDesignSprite::set_color(unsigned int color)
{
    sprite_18.set_color(color);
}

void CDesignSprite::set_vertex_colors(const unsigned int * colors)
{
    sprite_18.set_vertex_colors(colors);
}

void CDesignSprite::multiply_color(unsigned int color)
{
    sprite_18.multiply_color(color);
}

void CDesignGage::set_color(unsigned int color)
{
    gage_18.set_color(color);
}

void CDesignGage::set_vertex_colors(const unsigned int * colors)
{
    gage_18.set_vertex_colors(colors);
}

void CDesignGage::multiply_color(unsigned int color)
{
    gage_18.multiply_color(color);
}

void CDesignNumber::set_color(unsigned int color)
{
    number_18.set_color(color);
}

void CDesignNumber::set_vertex_colors(const unsigned int * colors)
{
    number_18.set_vertex_colors(colors);
}

void CDesignNumber::multiply_color(unsigned int color)
{
    number_18.multiply_color(color);
}
