#pragma once

// Native IColor is the four-byte interface. The texture handle at +4 belongs
// to CSpriteBase, as its constructor and implicit copy lifetimes establish.
// Native descriptor 6FA560 spells .?AUIColor@@ (struct tag).
struct IColor {
public:
    virtual ~IColor() {}
    virtual void set_color(unsigned int color) = 0;
    virtual void set_vertex_colors(const unsigned int *colors) = 0;
    virtual void multiply_color(unsigned int color) = 0;
};
