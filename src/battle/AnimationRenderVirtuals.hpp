#pragma once

#include "battle/EffectSprite.hpp"

#include <stddef.h>

namespace th105 {

struct AuxiliarySpriteRenderView {
    void render_auxiliary();
    void finish_render_pass();
};

struct SecondaryAnimationRenderView {
    void render_secondary();
};

struct AnimationRenderFrameView {
    unsigned char unknown_00[0x14];
    signed char render_mode_14;
    unsigned char unknown_15[3];
    unsigned *mode_values_18;
    unsigned char unknown_1c[0x6c];
};

struct SpriteRenderEffectView : CSpriteEx {
    void render_rgb(float red, float green, float blue);
    void render_alpha_rgb(float alpha, float red, float green, float blue);
    void render_luma(float red, float green, float blue);
    void render_luma_alpha(
        float luma_red, float luma_green, float luma_blue,
        float alpha, float red, float green, float blue);
};

struct AnimationRenderObjectView {
    virtual void slot_00();
    virtual void slot_04();
    virtual void slot_08();
    virtual void slot_0c();
    virtual void slot_10();
    virtual void slot_14();
    virtual void slot_18();
    virtual void slot_1c();
    virtual void slot_20();
    virtual void slot_24();
    virtual void slot_28();
    virtual void render_main();
    virtual void render_to_battle_scene();
    virtual void prepare_render_transform();
    virtual void render_color_mode();

    void set_sprite_uv_size(float width, float height);
    void render_group_callback(signed char group);

    CEffectSprite sprite_004;
    unsigned char unknown_130[0x20];
    AnimationRenderFrameView *frame_150;
    AuxiliarySpriteRenderView *aux_renderer_154;
    unsigned char unknown_158[0x1e0];
    SecondaryAnimationRenderView *secondary_renderer_338;
    signed char render_group_33c;
};

typedef char AnimationRenderFrame_size_must_be_0x88[
    sizeof(AnimationRenderFrameView) == 0x88 ? 1 : -1];
typedef char AnimationRenderObject_sprite_offset_must_be_0x04[
    offsetof(AnimationRenderObjectView, sprite_004) == 0x04 ? 1 : -1];
typedef char AnimationRenderObject_frame_offset_must_be_0x150[
    offsetof(AnimationRenderObjectView, frame_150) == 0x150 ? 1 : -1];
typedef char AnimationRenderObject_aux_offset_must_be_0x154[
    offsetof(AnimationRenderObjectView, aux_renderer_154) == 0x154 ? 1 : -1];
typedef char AnimationRenderObject_secondary_offset_must_be_0x338[
    offsetof(AnimationRenderObjectView, secondary_renderer_338) == 0x338 ? 1 : -1];
typedef char AnimationRenderObject_group_offset_must_be_0x33c[
    offsetof(AnimationRenderObjectView, render_group_33c) == 0x33c ? 1 : -1];

extern unsigned char g_battle_render_pass;

} // namespace th105
