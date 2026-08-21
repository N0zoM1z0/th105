#include "EffectSprite.hpp"

void CSpriteBase::set_color(unsigned int color)
{
    vertices_08[3].color = color;
    vertices_08[2].color = color;
    vertices_08[1].color = color;
    vertices_08[0].color = color;
}

void CSpriteBase::set_vertex_colors(const unsigned int *colors)
{
    vertices_08[0].color = colors[0];
    vertices_08[1].color = colors[1];
    vertices_08[2].color = colors[2];
    vertices_08[3].color = colors[3];
}

union SpritePackedColor {
    unsigned int value;
    unsigned char component[4];
};

void CSpriteBase::multiply_color(unsigned int color)
{
    SpritePackedColor current;
    SpritePackedColor input;
    SpritePackedColor result;
    current.value = vertices_08[0].color;
    input.value = color;
    result.component[0] = static_cast<unsigned char>(
        current.component[0] * input.component[0] / 255);
    result.component[1] = static_cast<unsigned char>(
        current.component[1] * input.component[1] / 255);
    result.component[2] = static_cast<unsigned char>(
        current.component[2] * input.component[2] / 255);
    result.component[3] = static_cast<unsigned char>(
        current.component[3] * input.component[3] / 255);
    vertices_08[3].color = result.value;
    vertices_08[2].color = result.value;
    vertices_08[1].color = result.value;
    vertices_08[0].color = result.value;
}
