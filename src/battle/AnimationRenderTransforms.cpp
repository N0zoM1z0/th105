#include "battle/EffectSprite.hpp"

namespace th105 {

struct AnimationRenderFrame {
    unsigned char unknown_00[0x04];
    short pivot_x_04;
    short pivot_y_06;
    unsigned char unknown_08[0x80];
};

struct BattleBackgroundLayoutRenderView {
    unsigned char unknown_00[0x0c];
    float offset_x_0c;
    float offset_y_10;
    float scale_14;
    void transform_sprite(CSpriteEx *sprite);
};

struct BattleObjectManagerRenderView {
    void dispatch_render_sprite(CSpriteEx *sprite);
};

extern BattleBackgroundLayoutRenderView g_battle_background_layout;
extern BattleObjectManagerRenderView *g_battle_object_manager;

struct AnimationRenderObjectView {
    void **vtable_000;
    CEffectSprite sprite_004;
    unsigned owner_130;
    unsigned char layout_absolute_134;
    unsigned char render_to_battle_135;
    unsigned char unknown_136[2];
    float battle_y_offset_138;
    unsigned char unknown_13c[0x14];
    AnimationRenderFrame *frame_150;
    void *aux_renderer_154;

    void prepare_render_transform();
    void render_to_battle_scene();
};

void AnimationRenderObjectView::prepare_render_transform()
{
    AnimationRenderFrame *const frame = frame_150;
    float const pivot_x = static_cast<float>(frame->pivot_x_04);
    float const pivot_y = static_cast<float>(frame->pivot_y_06);

    sprite_004.reset_transform();
    sprite_004.scale_x(static_cast<float>(sprite_004.object_facing_100));

    sprite_004.scale_x(
        sprite_004.reset_one_118,
        (sprite_004.reset_zero_104 + pivot_x) *
            static_cast<float>(sprite_004.object_facing_100));

    sprite_004.scale_y(
        sprite_004.reset_one_11c,
        pivot_y - sprite_004.reset_zero_108);

    sprite_004.rotate_xyz(
        sprite_004.reset_zero_120,
        sprite_004.reset_zero_124,
        static_cast<float>(sprite_004.object_facing_100) * sprite_004.reset_zero_128,
        (sprite_004.reset_zero_104 + pivot_x) *
            static_cast<float>(sprite_004.object_facing_100),
        pivot_y - sprite_004.reset_zero_108,
        0.0f);

    sprite_004.translate(
        static_cast<float>(-sprite_004.object_facing_100) * pivot_x,
        -pivot_y,
        0.0f);

    if (layout_absolute_134) {
        sprite_004.translate(sprite_004.object_x_0e8, sprite_004.object_y_0ec, 0.0f);
    } else {
        sprite_004.translate(sprite_004.object_x_0e8, -sprite_004.object_y_0ec, 0.0f);
        g_battle_background_layout.transform_sprite(&sprite_004);
    }
}

void AnimationRenderObjectView::render_to_battle_scene()
{
    if (!render_to_battle_135)
        return;

    AnimationRenderFrame *const frame = frame_150;
    float const pivot_x = static_cast<float>(frame->pivot_x_04);
    float const pivot_y = static_cast<float>(frame->pivot_y_06);

    sprite_004.reset_transform();
    sprite_004.scale_x(static_cast<float>(sprite_004.object_facing_100));

    sprite_004.scale_x(
        sprite_004.reset_one_118,
        (sprite_004.reset_zero_104 + pivot_x) *
            static_cast<float>(sprite_004.object_facing_100));

    sprite_004.scale_y(
        sprite_004.reset_one_11c,
        pivot_y - sprite_004.reset_zero_108);

    sprite_004.rotate_xyz(
        sprite_004.reset_zero_120,
        sprite_004.reset_zero_124,
        static_cast<float>(sprite_004.object_facing_100) * sprite_004.reset_zero_128,
        (sprite_004.reset_zero_104 + pivot_x) *
            static_cast<float>(sprite_004.object_facing_100),
        pivot_y - sprite_004.reset_zero_108,
        0.0f);

    sprite_004.translate(
        static_cast<float>(-sprite_004.object_facing_100) * pivot_x,
        -pivot_y,
        0.0f);
    sprite_004.translate(
        sprite_004.object_x_0e8,
        -sprite_004.object_y_0ec - battle_y_offset_138,
        0.0f);

    g_battle_object_manager->dispatch_render_sprite(&sprite_004);
    g_battle_background_layout.transform_sprite(&sprite_004);
    sprite_004.finalize_render();
}

}
