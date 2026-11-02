#include "ui/CNumberLifetime.hpp"

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

// RTTI-owned CDesignNumber contains the independently recovered CNumber
// lifetime at +18. Runtime virtuals and constructor bytes are not claimed.
class DesignNumberObjectBaseLifetime : public CNumberColorLifetime {
public:
    DesignNumberObjectBaseLifetime()
        : base_x_04(0.0f), base_y_08(0.0f), enabled_14(true) {}
    virtual ~DesignNumberObjectBaseLifetime() {}
    virtual void set_color(unsigned int);
    virtual void set_vertex_colors(const unsigned int *);
    virtual void multiply_color(unsigned int);
    virtual void render_offset(float, float);
    virtual void render();
    // Empty target slot consumes three words; semantic types remain open.
    virtual void slot_18(unsigned int, unsigned int, unsigned int);
    float base_x_04;
    float base_y_08;
    float x_0c;
    float y_10;
    bool enabled_14;
};

class CDesignNumberLifetime : public DesignNumberObjectBaseLifetime {
public:
    CDesignNumberLifetime();
    // The ordinary implicit destructor destroys number_18, then the base.
    CNumberLifetime number_18;
};

CDesignNumberLifetime::CDesignNumberLifetime() {}

typedef char DesignNumberBaseSize[
    sizeof(DesignNumberObjectBaseLifetime) == 0x18 ? 1 : -1];
typedef char DesignNumberMemberOffset[
    offsetof(CDesignNumberLifetime, number_18) == 0x18 ? 1 : -1];
typedef char DesignNumberSize[
    sizeof(CDesignNumberLifetime) == 0xe4 ? 1 : -1];

} // namespace th105
