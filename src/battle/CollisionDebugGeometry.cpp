#include "battle/PatResourceContracts.hpp"
#include "engine/RenderModeManager.hpp"

namespace th105 {
extern float g_secondary_animation_x_offset;
extern float g_secondary_animation_y_origin;
extern float g_secondary_animation_scale;
struct DebugRect4 { int left, top, right, bottom; };
struct CollisionDebugLineView {
    int draw_line(float x1, float y1, float x2, float y2, unsigned color);
};
// Nonconstructing receiver; accessed offsets are pinned by the target.
struct CollisionDebugObjectView { void render_debug_geometry_45e950(); };
template<class T> static T &debug_field(void *object, unsigned offset)
{
    return *reinterpret_cast<T *>(static_cast<unsigned char *>(object) + offset);
}
#define DX(value) static_cast<float>(((value) + g_secondary_animation_x_offset) * g_secondary_animation_scale)
#define DY(value) static_cast<float>(((value) + g_secondary_animation_y_origin) * g_secondary_animation_scale)
#define LINE(x1,y1,x2,y2,color) reinterpret_cast<CollisionDebugLineView *>(&g_render_mode_manager)->draw_line(DX(x1), DY(y1), DX(x2), DY(y2), color)

void CollisionDebugObjectView::render_debug_geometry_45e950()
{
    const DebugRect4 *box = debug_field<DebugRect4 *>(this, 0x32C);
    if (box != 0) {
        LINE(box->left, box->top, box->right, box->top, 0xFF00FFFFu);
        LINE(box->right, box->top, box->right, box->bottom, 0xFF00FFFFu);
        LINE(box->right, box->bottom, box->left, box->bottom, 0xFF00FFFFu);
        LINE(box->left, box->bottom, box->left, box->top, 0xFF00FFFFu);
    }
    if (debug_field<PatRecord88 *>(this, 0x158)->raw16_vector_58.size() != 0) {
        for (int index = 0; index < debug_field<signed char>(this, 0x1B0); ++index) {
            const DebugRect4 *box = &debug_field<DebugRect4>(this, 0x1B4 + index * 16);
            if (box != 0) {
                const DebugRect4 *quad = debug_field<DebugRect4 *>(this, 0x318 + index * 4);
                if (quad != 0) {
                    const int ux = quad->left;
                    const int uy = quad->top;
                    const int vx = quad->right;
                    const int vy = quad->bottom;
                    LINE(box->left, box->top, box->left + ux, box->top + uy, 0xFF0000FFu);
                    LINE(box->left, box->top, box->left + vx, box->top + vy, 0xFF0000FFu);
                    LINE(box->right, box->bottom, box->right - ux, box->bottom - uy, 0xFF0000FFu);
                    LINE(box->right, box->bottom, box->right - vx, box->bottom - vy, 0xFF0000FFu);
                } else {
                    LINE(box->left, box->top, box->right, box->top, 0xFF0000FFu);
                    LINE(box->right, box->top, box->right, box->bottom, 0xFF0000FFu);
                    LINE(box->right, box->bottom, box->left, box->bottom, 0xFF0000FFu);
                    LINE(box->left, box->bottom, box->left, box->top, 0xFF0000FFu);
                }
            }
        }
    }
    if (debug_field<PatRecord88 *>(this, 0x158)->raw16_vector_68.size() +
            static_cast<unsigned>(debug_field<DebugRect4 *>(this, 0x194) != 0) != 0 &&
        debug_field<unsigned>(this, 0x180) == 0 &&
        debug_field<signed char>(this, 0x184) > 0) {
        for (int index = 0; index < debug_field<signed char>(this, 0x1AF); ++index) {
            const DebugRect4 *box = &debug_field<DebugRect4>(this, 0x204 + index * 16);
            if (box != 0) {
                const DebugRect4 *quad = debug_field<DebugRect4 *>(this, 0x304 + index * 4);
                if (quad != 0) {
                    const int ux = quad->left;
                    const int uy = quad->top;
                    const int vx = quad->right;
                    const int vy = quad->bottom;
                    LINE(box->left, box->top, box->left + ux, box->top + uy, 0xFFFF0000u);
                    LINE(box->left, box->top, box->left + vx, box->top + vy, 0xFFFF0000u);
                    LINE(box->right, box->bottom, box->right - ux, box->bottom - uy, 0xFFFF0000u);
                    LINE(box->right, box->bottom, box->right - vx, box->bottom - vy, 0xFFFF0000u);
                } else {
                    LINE(box->left, box->top, box->right, box->top, 0xFFFF0000u);
                    LINE(box->right, box->top, box->right, box->bottom, 0xFFFF0000u);
                    LINE(box->right, box->bottom, box->left, box->bottom, 0xFFFF0000u);
                    LINE(box->left, box->bottom, box->left, box->top, 0xFFFF0000u);
                }
            }
        }
    }
    void *const related = debug_field<void *>(this, 0x168);
    if (this == related) {
        int width = debug_field<short>(related, 0x49E) *
                    debug_field<signed char>(this, 0x104);
        if (width >= 300)
            width = 300;
        g_render_mode_manager.draw_rect(
            static_cast<float>((debug_field<float>(this, 0xEC) + g_secondary_animation_x_offset) * g_secondary_animation_scale),
            static_cast<float>((g_secondary_animation_y_origin - debug_field<float>(this, 0xF0)) * g_secondary_animation_scale),
            static_cast<float>((width + debug_field<float>(this, 0xEC) + g_secondary_animation_x_offset) * g_secondary_animation_scale),
            static_cast<float>((4.0 - debug_field<float>(this, 0xF0) + g_secondary_animation_y_origin) * g_secondary_animation_scale),
            0xFFFF0000u, 1);
    }
}
#undef LINE
#undef DX
#undef DY
} // namespace th105
