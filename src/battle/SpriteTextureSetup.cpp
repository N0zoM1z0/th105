#include "EffectSprite.hpp"
#include "ui/Title.hpp"

namespace th105 {
// Local physical view of the target CSpriteEx prefix. No object of this
// view is constructed and no shared vtable or class declaration is changed.
class SpriteTextureSetupView : public CSpriteEx {
public:
    void set_texture_options(unsigned handle, int x, int y,
        int width, int height, int pivot_x, int pivot_y);
};

// This helper and every call to it belong to this TU. VC8 privately passes
// self in EAX and pops only the six float arguments; do not expose that
// generated ABI as an external stdcall/fastcall/member declaration.
static void __stdcall initialize_texture_rectangle(SpriteTextureSetupView *self, float x, float y,
    float width, float height, float pivot_x, float pivot_y);

#pragma float_control(except, off, push)
void SpriteTextureSetupView::set_texture_options(unsigned handle, int x, int y,
    int width, int height, int pivot_x, int pivot_y)
{
    value_04 = handle;
    if (handle) {
        unsigned texture_width;
        unsigned texture_height;
        g_title_resource_manager.get_texture_size(
            handle, &texture_width, &texture_height);
        texture_width_78 = static_cast<float>(texture_width);
        texture_height_7c = static_cast<float>(texture_height);
    } else {
        texture_width_78 = texture_height_7c = 0.0f;
    }
    source_quad_080[0].z = source_quad_080[1].z =
        source_quad_080[2].z = source_quad_080[3].z = 0.0f;
    vertices_08[0].color = vertices_08[1].color =
        vertices_08[2].color = vertices_08[3].color = ~0u;
    initialize_texture_rectangle(this, static_cast<float>(x), static_cast<float>(y),
        static_cast<float>(width), static_cast<float>(height),
        static_cast<float>(pivot_x), static_cast<float>(pivot_y));
}

static void __stdcall initialize_texture_rectangle(SpriteTextureSetupView *self, float x, float y,
    float width, float height, float pivot_x, float pivot_y)
{
    if (self->value_04) {
        float u = width / self->texture_width_78;
        self->extra_e0 = u;
        float v = height / self->texture_height_7c;
        self->extra_e4 = v;
        float left = x / self->texture_width_78;
        self->vertices_08[0].u = left;
        float top = y / self->texture_height_7c;
        self->vertices_08[0].v = top;
        float right = u + left;
        self->vertices_08[1].u = right;
        self->vertices_08[1].v = top;
        self->vertices_08[2].u = left;
        float bottom = v + top;
        self->vertices_08[2].v = bottom;
        self->vertices_08[3].v = bottom;
        self->vertices_08[3].u = right;
    } else {
        self->extra_e0 = self->extra_e4 = 0.0f;
    }
    float left = -pivot_x;
    self->source_quad_080[0].x = left;
    float top = -pivot_y;
    self->source_quad_080[0].y = top;
    float right = width - pivot_x;
    self->source_quad_080[1].x = right;
    self->source_quad_080[1].y = top;
    self->source_quad_080[2].x = left;
    float bottom = height - pivot_y;
    self->source_quad_080[2].y = bottom;
    self->source_quad_080[3].y = bottom;
    self->source_quad_080[3].x = right;
}
#pragma float_control(pop)

typedef char SpriteTextureSetupViewSize[
    sizeof(SpriteTextureSetupView) == sizeof(CSpriteEx) ? 1 : -1];
} // namespace th105
