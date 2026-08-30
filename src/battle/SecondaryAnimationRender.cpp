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

    SecondaryAnimationPoint()
    {
    }

    SecondaryAnimationPoint(float x_value, float y_value)
        : x(x_value), y(y_value)
    {
    }

    SecondaryAnimationPoint operator+(const SecondaryAnimationPoint &other) const
    {
        return SecondaryAnimationPoint(x + other.x, y + other.y);
    }

    SecondaryAnimationPoint operator-(const SecondaryAnimationPoint &other) const
    {
        return SecondaryAnimationPoint(x - other.x, y - other.y);
    }

    SecondaryAnimationPoint operator*(float scale) const
    {
        return SecondaryAnimationPoint(x * scale, y * scale);
    }

    SecondaryAnimationPoint &operator+=(const SecondaryAnimationPoint &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    SecondaryAnimationPoint &operator-=(const SecondaryAnimationPoint &other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }
};

extern "C" SecondaryAnimationPoint *__stdcall D3DXVec2Hermite(
    SecondaryAnimationPoint *destination,
    const SecondaryAnimationPoint *point1,
    const SecondaryAnimationPoint *tangent1,
    const SecondaryAnimationPoint *point2,
    const SecondaryAnimationPoint *tangent2,
    float amount);
extern "C" SecondaryAnimationPoint *__stdcall D3DXVec2Normalize(
    SecondaryAnimationPoint *destination,
    const SecondaryAnimationPoint *source);

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
    void update_secondary();
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

void SecondaryAnimationRenderRuntimeView::update_secondary()
{
    int expired_segments;
    if (source_points_28.size() > static_cast<unsigned int>(subdivision_count_04)) {
        if (static_cast<signed char>(update_step_25) < 1)
            expired_segments = 1;
        else
            expired_segments = static_cast<signed char>(update_step_25);
    } else {
        expired_segments = static_cast<signed char>(update_step_25);
    }

    if (expired_segments != 0) {
        if (static_cast<int>(source_points_28.size()) > expired_segments) {
            source_points_28.pop_back();
            points_3c.erase(
                points_3c.end() - 2 * band_count_08 * expired_segments,
                points_3c.end());
        } else {
            source_points_28.clear();
            points_3c.clear();
        }
    }

    if (render_enabled_24 == 0)
        return;

    source_points_28.push_back(SecondaryAnimationPoint(
        owner_00->source_x_0ec,
        owner_00->source_y_0f0));

    SecondaryAnimationPoint zero(0.0f, 0.0f);
    switch (source_points_28.size()) {
    case 0:
        return;

    case 1:
        points_3c.clear();
        points_3c.push_back(source_points_28.front());
        points_3c.push_back(source_points_28.front());
        return;

    case 2: {
        SecondaryAnimationPoint *point0 = &source_points_28[0];
        SecondaryAnimationPoint *point1 = &source_points_28[1];
        SecondaryAnimationPoint normal_source(
            source_points_28[0].y - source_points_28[1].y,
            source_points_28[1].x - source_points_28[0].x);
        SecondaryAnimationPoint normal;
        D3DXVec2Normalize(&normal, &normal_source);

        points_3c[0] += normal * half_width_10;
        points_3c[1] -= normal * half_width_10;

        SecondaryAnimationPoint previous(0.0f, 0.0f);
        SecondaryAnimationPoint end_tangent = previous;
        previous = *point1;
        for (int index = band_count_08 - 1; index >= 0; --index) {
            SecondaryAnimationPoint center;
            D3DXVec2Hermite(
                &center,
                point0,
                &zero,
                point1,
                &end_tangent,
                static_cast<float>(index) / band_count_08);
            SecondaryAnimationPoint perpendicular_source(
                previous.y - center.y,
                center.x - previous.x);
            D3DXVec2Normalize(&normal, &perpendicular_source);
            SecondaryAnimationPoint offset = normal * half_width_10;
            points_3c.push_back(center + offset);
            points_3c.push_back(center - offset);
            previous = center;
        }
        return;
    }

    case 3: {
        SecondaryAnimationPoint *point0 = &source_points_28[0];
        SecondaryAnimationPoint *point1 = &source_points_28[1];
        SecondaryAnimationPoint *point2 = &source_points_28[2];
        SecondaryAnimationPoint tangent(
            source_points_28[2].x - source_points_28[0].x,
            source_points_28[2].y - source_points_28[0].y);
        SecondaryAnimationPoint normal;

        points_3c.erase(
            points_3c.begin(),
            points_3c.begin() + 2 * band_count_08);

        SecondaryAnimationPoint previous(0.0f, 0.0f);
        SecondaryAnimationPoint end_tangent = previous;
        previous = *point2;
        for (int index = band_count_08 - 1; index >= 0; --index) {
            SecondaryAnimationPoint center;
            D3DXVec2Hermite(
                &center,
                point1,
                &tangent,
                point2,
                &end_tangent,
                static_cast<float>(index) / band_count_08);
            SecondaryAnimationPoint perpendicular_source(
                previous.y - center.y,
                center.x - previous.x);
            D3DXVec2Normalize(&normal, &perpendicular_source);
            SecondaryAnimationPoint offset = normal * half_width_10;
            points_3c.push_back(center + offset);
            points_3c.push_back(center - offset);
            previous = center;
        }

        for (int index = band_count_08 - 1; index >= 0; --index) {
            SecondaryAnimationPoint center;
            D3DXVec2Hermite(
                &center,
                point0,
                &zero,
                point1,
                &tangent,
                static_cast<float>(index) / band_count_08);
            SecondaryAnimationPoint perpendicular_source(
                previous.y - center.y,
                center.x - previous.x);
            D3DXVec2Normalize(&normal, &perpendicular_source);
            SecondaryAnimationPoint offset = normal * half_width_10;
            points_3c.push_back(center + offset);
            points_3c.push_back(center - offset);
            previous = center;
        }
        return;
    }

    default: {
        SecondaryAnimationPoint *point0 = &source_points_28[0];
        SecondaryAnimationPoint *point1 = &source_points_28[1];
        SecondaryAnimationPoint *point2 = &source_points_28[2];
        SecondaryAnimationPoint tangent1(
            source_points_28[2].x - source_points_28[0].x,
            source_points_28[2].y - source_points_28[0].y);
        SecondaryAnimationPoint tangent2(
            source_points_28[3].x - source_points_28[1].x,
            source_points_28[3].y - source_points_28[1].y);
        SecondaryAnimationPoint normal;

        points_3c.erase(
            points_3c.begin(),
            points_3c.begin() + 2 * band_count_08);

        SecondaryAnimationPoint previous = *point2;
        for (int index = band_count_08 - 1; index >= 0; --index) {
            SecondaryAnimationPoint center;
            D3DXVec2Hermite(
                &center,
                point1,
                &tangent1,
                point2,
                &tangent2,
                static_cast<float>(index) / band_count_08);
            SecondaryAnimationPoint perpendicular_source(
                previous.y - center.y,
                center.x - previous.x);
            D3DXVec2Normalize(&normal, &perpendicular_source);
            SecondaryAnimationPoint offset = normal * half_width_10;
            points_3c.push_back(center + offset);
            points_3c.push_back(center - offset);
            previous = center;
        }

        for (int index = band_count_08 - 1; index >= 0; --index) {
            SecondaryAnimationPoint center;
            D3DXVec2Hermite(
                &center,
                point0,
                &zero,
                point1,
                &tangent1,
                static_cast<float>(index) / band_count_08);
            SecondaryAnimationPoint perpendicular_source(
                previous.y - center.y,
                center.x - previous.x);
            D3DXVec2Normalize(&normal, &perpendicular_source);
            SecondaryAnimationPoint offset = normal * half_width_10;
            points_3c.push_back(center + offset);
            points_3c.push_back(center - offset);
            previous = center;
        }
        return;
    }
    }
}

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
