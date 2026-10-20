// JP1.06a CDesignGage render entries40AEA0/40AF30.
// Complete canonical matches; docs/GAGE_DESIGN_RENDER_2026_10_21.md.
#include <stddef.h>
namespace th105 {
// Four observed common virtual slots. Original base data ownership is open;
// the design receiver reads +4/+8 as floats, unlike its sprite member's handle+4.
class DesignGageColorView {
public:
    virtual ~DesignGageColorView();
    virtual void set_color(unsigned);
    virtual void set_vertex_colors(const unsigned *);
    virtual void multiply_color(unsigned);
};
struct DesignGageVertex28 { float x, y, z, rhw; unsigned color; float u, v; };
class DesignGageSpriteBaseView : public DesignGageColorView {
public:
    unsigned texture_handle_04;
    DesignGageVertex28 vertices_08[4];
    float width_78, height_7c;
};
class DesignGageSpriteView : public DesignGageSpriteBaseView {
public:
    virtual void set_texture_options(unsigned, int, int, unsigned, unsigned, int, int);
    virtual void set_texture(unsigned, int, int, unsigned, unsigned);
    virtual void render_rectangle(float, float, float, float);
    virtual void render(float, float);
    virtual void render_plain(float, float);
    float pivot_x_80, pivot_y_84;
    float scale_x_88, scale_y_8c;
    float angle_90;
};
class DesignGageMemberView : public DesignGageSpriteView {
public:
    virtual void render(float, float);
    virtual void render_plain(float, float);
    float u_span_94, v_span_98;
    int fill_mode_9c;
    void *value_a0;
};
class DesignGageObjectBaseView : public DesignGageColorView {
public:
    virtual void render_offset(float, float);
    virtual void render();
    virtual void slot_18(unsigned, unsigned, unsigned);
    // Target renderers add these to the local screen position before offsets.
    float base_x_04, base_y_08;
    float x_0c, y_10;
    bool enabled_14;
};
class CDesignGageRenderView : public DesignGageObjectBaseView {
public:
    virtual void render_offset(float x, float y);
    virtual void render();
    DesignGageMemberView gage_18;
};
void CDesignGageRenderView::render()
{
    if (enabled_14)
        gage_18.render(x_0c + base_x_04, y_10 + base_y_08);
}
void CDesignGageRenderView::render_offset(float x, float y)
{
    if (enabled_14)
        gage_18.render(x_0c + base_x_04 + x, y_10 + base_y_08 + y);
}
typedef char ColorViewSize[sizeof(DesignGageColorView) == 4 ? 1 : -1];
typedef char GageMemberSize[sizeof(DesignGageMemberView) == 0xa4 ? 1 : -1];
typedef char DesignBaseSize[sizeof(DesignGageObjectBaseView) == 0x18 ? 1 : -1];
typedef char DesignGageSize[sizeof(CDesignGageRenderView) == 0xbc ? 1 : -1];
typedef char GageMemberOffset[offsetof(CDesignGageRenderView, gage_18) == 0x18 ? 1 : -1];
typedef char BaseXOffset[offsetof(DesignGageObjectBaseView, base_x_04) == 4 ? 1 : -1];
typedef char BaseYOffset[offsetof(DesignGageObjectBaseView, base_y_08) == 8 ? 1 : -1];
typedef char XOffset[offsetof(DesignGageObjectBaseView, x_0c) == 0xc ? 1 : -1];
typedef char YOffset[offsetof(DesignGageObjectBaseView, y_10) == 0x10 ? 1 : -1];
typedef char EnabledOffset[offsetof(DesignGageObjectBaseView, enabled_14) == 0x14 ? 1 : -1];
} // namespace th105
