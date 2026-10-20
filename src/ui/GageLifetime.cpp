// JP1.06a lifetime/color view of CGage and its CDesignGage owner.
// Runtime virtuals outside the compared slots remain declarations only.
#include "battle/EffectSprite.hpp"
#include <new>

namespace th105 {

// Retain all nine observed sprite/gauge slots without expanding the shared
// sprite header's narrower interface. Original declaration ownership is open.
class GageSpriteLifetime : public CSpriteBase {
public:
    virtual ~GageSpriteLifetime() {}
    virtual void set_texture_options(unsigned int, int, int, unsigned int,
                                    unsigned int, int, int);
    virtual void set_texture(unsigned int, int, int, unsigned int, unsigned int);
    // Unused marker for the observed +18 slot; its source signature is unknown.
    virtual void slot_18();
    virtual void render(float x, float y);
    virtual void render_plain(float x, float y);
    unsigned char unmodeled_080[0x14];
};

class CGageLifetime : public GageSpriteLifetime {
public:
    CGageLifetime();
    virtual ~CGageLifetime()
    {
        if (value_a0 != 0)
            ::operator delete(value_a0);
    }
    virtual void render(float x, float y);
    virtual void render_plain(float x, float y);
    unsigned char unmodeled_094[0x0c];
    void *value_a0;
};

CGageLifetime::CGageLifetime() : value_a0(0) {}

class DesignObjectBaseLifetime : public IColor {
public:
    DesignObjectBaseLifetime() : value_08(0.0f), enabled_14(true) {}
    virtual ~DesignObjectBaseLifetime() {}
    virtual void set_color(unsigned int color);
    virtual void set_vertex_colors(const unsigned int *colors);
    virtual void multiply_color(unsigned int color);
    virtual void render_offset(float x, float y);
    virtual void render();
    // Unused marker for the observed +18 slot; its source signature is unknown.
    virtual void slot_18();
    float value_08;
    float x_0c;
    float y_10;
    bool enabled_14;
    unsigned char unmodeled_015[3];
};

class CDesignGageLifetime : public DesignObjectBaseLifetime {
public:
    CDesignGageLifetime();
    // Its implicit destructor destroys the member, then the outer base.
    virtual void set_color(unsigned int color);
    virtual void set_vertex_colors(const unsigned int *colors);
    virtual void multiply_color(unsigned int color);
    virtual void render_offset(float x, float y);
    virtual void render();
    CGageLifetime gage_18;
};

CDesignGageLifetime::CDesignGageLifetime() {}

void CDesignGageLifetime::set_color(unsigned int color)
{
    gage_18.set_color(color);
}

void CDesignGageLifetime::set_vertex_colors(const unsigned int *colors)
{
    gage_18.set_vertex_colors(colors);
}

void CDesignGageLifetime::multiply_color(unsigned int color)
{
    gage_18.multiply_color(color);
}

typedef char GageSpriteSize[sizeof(GageSpriteLifetime) == 0x94 ? 1 : -1];
typedef char GagePointerOffset[
    offsetof(CGageLifetime, value_a0) == 0xa0 ? 1 : -1];
typedef char GageSize[sizeof(CGageLifetime) == 0xa4 ? 1 : -1];
typedef char DesignObjectBaseSize[
    sizeof(DesignObjectBaseLifetime) == 0x18 ? 1 : -1];
typedef char DesignGageOffset[
    offsetof(CDesignGageLifetime, gage_18) == 0x18 ? 1 : -1];
typedef char DesignGageSize[sizeof(CDesignGageLifetime) == 0xbc ? 1 : -1];

} // namespace th105
