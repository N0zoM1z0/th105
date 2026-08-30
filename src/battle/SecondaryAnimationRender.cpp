#include "AnimationRenderVirtuals.hpp"
#include "engine/RenderModeManager.hpp"
#include "ui/Title.hpp"

#include <deque>
#include <stddef.h>
#include <vector>

namespace th105 {

struct SecondaryAnimationPoint {
    float x;
    float y;
};

extern float g_secondary_animation_x_offset;
extern float g_secondary_animation_y_origin;
extern float g_secondary_animation_scale;

struct SecondaryAnimationOwnerRuntimeView {
    unsigned char reserved_000[0xec];
    float source_x_0ec;
    float source_y_0f0;
    unsigned char reserved_0f4[0x3c];
    std::vector<unsigned int> *texture_handles_130;
};

struct SecondaryAnimationFrameRuntimeView {
    unsigned char reserved_00[0x0a];
    short texture_index_0a;
    unsigned char reserved_0c[4];
    short texture_width_10;
    short texture_height_12;
};

class SecondaryAnimationRenderRuntimeView {
public:
    SecondaryAnimationRenderRuntimeView();
    ~SecondaryAnimationRenderRuntimeView();

    void initialize(
        SecondaryAnimationOwnerRuntimeView *owner,
        const SecondaryAnimationFrameRuntimeView *frame,
        float half_width,
        int subdivision_count,
        int band_count,
        int blend_mode);
    void render_secondary();

private:
    SecondaryAnimationOwnerRuntimeView *owner_00;
    int subdivision_count_04;
    int band_count_08;
    int elapsed_0c;
    float half_width_10;
    int blend_mode_14;
    float texture_u_extent_18;
    float texture_v_extent_1c;
    unsigned int texture_handle_20;
    unsigned char render_enabled_24;
    unsigned char update_step_25;
    unsigned char reserved_26[2];
    std::deque<SecondaryAnimationPoint> source_points_28;
    std::deque<SecondaryAnimationPoint> points_3c;
    SpriteVertex28 *vertices_50;
};

SecondaryAnimationRenderRuntimeView::SecondaryAnimationRenderRuntimeView()
    : texture_handle_20(0), vertices_50(0)
{
}

SecondaryAnimationRenderRuntimeView::~SecondaryAnimationRenderRuntimeView()
{
    if (vertices_50 != 0) {
        delete[] vertices_50;
        vertices_50 = 0;
    }
}

void SecondaryAnimationRenderRuntimeView::initialize(
    SecondaryAnimationOwnerRuntimeView *owner,
    const SecondaryAnimationFrameRuntimeView *frame,
    float half_width,
    int subdivision_count,
    int band_count,
    int blend_mode)
{
    owner_00 = owner;
    half_width_10 = half_width;
    subdivision_count_04 = subdivision_count;
    band_count_08 = band_count;
    blend_mode_14 = blend_mode;

    source_points_28.clear();
    points_3c.clear();

    SecondaryAnimationPoint source;
    source.x = owner_00->source_x_0ec;
    source.y = owner_00->source_y_0f0;
    source_points_28.push_back(source);
    points_3c.push_back(source_points_28.front());
    points_3c.push_back(source_points_28.front());

    elapsed_0c = -1;
    texture_handle_20 =
        owner_00->texture_handles_130->at(frame->texture_index_0a);
    unsigned int texture_width;
    unsigned int texture_height;
    g_title_resource_manager.get_texture_size(
        texture_handle_20, &texture_width, &texture_height);
    texture_u_extent_18 =
        static_cast<float>(frame->texture_width_10) / texture_width;
    texture_v_extent_1c =
        static_cast<float>(frame->texture_height_12) / texture_height;

    int vertex_count =
        2 * subdivision_count_04 * band_count_08 + 2;
    vertices_50 = new SpriteVertex28[vertex_count];
    for (int i = 0; i < vertex_count; ++i) {
        vertices_50[i].z = 0.0f;
        vertices_50[i].rhw = 1.0f;
        vertices_50[i].color = ~0u;
    }
    for (int i = 0; i < vertex_count; i += 2) {
        vertices_50[i].u = 0.0f;
        vertices_50[i + 1].u = texture_u_extent_18;
    }

    render_enabled_24 = 1;
    update_step_25 = 0;
}

/*
 * The target class is 0x54 bytes.  The two checked deques are native VC8
 * members; keeping them typed is what reproduces the shared at/push/tidy
 * helper family used by both initialize() and render_secondary().
 */
struct SecondaryAnimationRenderLayoutChecks {
    unsigned char reserved_00[0x14];
    int blend_mode_14;
    unsigned int reserved_18;
    float texture_v_extent_1c;
    unsigned int texture_handle_20;
    unsigned char reserved_24[0x18];
    std::deque<SecondaryAnimationPoint> points_3c;
    SpriteVertex28 *vertices_50;
};

void SecondaryAnimationRenderRuntimeView::render_secondary()
{
    unsigned int point_count = points_3c.size();
    if (point_count <= 2)
        return;

    float x_offset = g_secondary_animation_x_offset;
    float y_origin = g_secondary_animation_y_origin;
    float scale = g_secondary_animation_scale;
    for (unsigned int i = 0; i < point_count; ++i) {
        vertices_50[i].x = (points_3c[i].x + x_offset) * scale;
        vertices_50[i].y = (y_origin - points_3c[i].y) * scale;
    }

    for (unsigned int i = 0; i < point_count; i += 2) {
        float v = static_cast<float>(i) /
            static_cast<float>(point_count) * texture_v_extent_1c;
        vertices_50[i + 1].v = v;
        vertices_50[i].v = vertices_50[i + 1].v;
    }

    g_render_mode_manager.set_blend_mode(blend_mode_14);
    g_render_mode_manager.set_mode(2);
    g_render_mode_manager.submit_textured_primitive(
        texture_handle_20,
        5,
        point_count - 2,
        vertices_50,
        sizeof(SpriteVertex28),
        0x144);
    g_render_mode_manager.set_mode(1);
}

typedef char SecondaryAnimationPoint_size[
    sizeof(SecondaryAnimationPoint) == 0x08 ? 1 : -1];
typedef char SecondaryAnimationOwnerRuntimeView_texture_handles_offset[
    offsetof(SecondaryAnimationOwnerRuntimeView, texture_handles_130) == 0x130 ? 1 : -1];
typedef char SecondaryAnimationFrameRuntimeView_texture_index_offset[
    offsetof(SecondaryAnimationFrameRuntimeView, texture_index_0a) == 0x0a ? 1 : -1];
typedef char SecondaryAnimationRenderRuntimeView_size[
    sizeof(SecondaryAnimationRenderRuntimeView) == 0x54 ? 1 : -1];
typedef char SecondaryAnimationRenderRuntimeView_points_offset[
    offsetof(SecondaryAnimationRenderLayoutChecks, points_3c) == 0x3c ? 1 : -1];
typedef char SecondaryAnimationRenderRuntimeView_vertices_offset[
    offsetof(SecondaryAnimationRenderLayoutChecks, vertices_50) == 0x50 ? 1 : -1];

} // namespace th105
