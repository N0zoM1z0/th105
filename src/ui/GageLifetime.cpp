// JP1.06a lifetime/color view of CGage and its CDesignGage owner.
// Runtime virtuals outside the compared slots remain declarations only.
#include "Gage.hpp"
#include <new>

#include "GageConstructor.cpp"

namespace th105 {

class DesignObjectBaseLifetime : public IColor {
public:
    unsigned int value_04;
    DesignObjectBaseLifetime() : value_04(0), value_08(0.0f), enabled_14(true) {}
    virtual ~DesignObjectBaseLifetime() {}
    virtual void set_color(unsigned int color);
    virtual void set_vertex_colors(const unsigned int *colors);
    virtual void multiply_color(unsigned int color);
    virtual void render_offset(float x, float y);
    virtual void render();
    // Observed +18 empty entry40AE60 consumes three words (RET12).
    // Their original semantic types remain unproved.
    virtual void slot_18(unsigned int, unsigned int, unsigned int);
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
    CGage gage_18;
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

typedef char GageSpriteSize[sizeof(CSprite) == 0x94 ? 1 : -1];
typedef char GageUSpanOffset[offsetof(CGage, u_span_94) == 0x94 ? 1 : -1];
typedef char GageVSpanOffset[offsetof(CGage, v_span_98) == 0x98 ? 1 : -1];
typedef char GageFillModeOffset[offsetof(CGage, fill_mode_9c) == 0x9c ? 1 : -1];
typedef char GagePointerOffset[
    offsetof(CGage, value_a0) == 0xa0 ? 1 : -1];
typedef char GageSize[sizeof(CGage) == 0xa4 ? 1 : -1];
typedef char DesignObjectBaseSize[
    sizeof(DesignObjectBaseLifetime) == 0x18 ? 1 : -1];
typedef char DesignGageOffset[
    offsetof(CDesignGageLifetime, gage_18) == 0x18 ? 1 : -1];
typedef char DesignGageSize[sizeof(CDesignGageLifetime) == 0xbc ? 1 : -1];

} // namespace th105
