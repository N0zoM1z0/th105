#include "InfoManagerResources.hpp"
#include "../engine/RenderModeManager.hpp"

namespace th105 {

float __cdecl lookup_orientation_cosine(int angle);

struct InfoShortRuntimeView {
    void update_46ac30();
    void render_46a800();
};

struct InfoLongRuntimeView {
    void update_4327c0();
    void render_4325c0();
};

struct InfoEffectRuntimeView {
    virtual void slot_00();
    virtual void slot_04();
    virtual void slot_08();
    virtual void slot_0c();
    virtual void slot_10();
    virtual void slot_14();
    virtual void set_phase(int phase);
};

struct Renderable2DView {
    virtual void slot_00();
    virtual void slot_04();
    virtual void slot_08();
    virtual void slot_0c();
    virtual void slot_10();
    virtual void slot_14();
    virtual void slot_18();
    virtual void render(float x, float y);
};

struct BattleInfoRenderView {
    void render_470710(float shift);
};

struct StoryInfoRenderView {
    void render_470720(float shift);
};

static __forceinline unsigned char *bytes(InfoManagerResourceView *manager)
{
    return reinterpret_cast<unsigned char *>(manager);
}

void InfoManagerResourceView::update_runtime_471c90()
{
    battle_records_498()[0].update_runtime_46ff30();
    battle_records_498()[1].update_story_471930();

    unsigned char *long_record = bytes(this) + 0x1d4;
    unsigned char *short_record = bytes(this) + 0x16c;
    for (int count = 2; count != 0; --count) {
        reinterpret_cast<InfoShortRuntimeView *>(short_record)->update_46ac30();
        reinterpret_cast<InfoLongRuntimeView *>(long_record)->update_4327c0();
        short_record += 0x34;
        long_record += 0x154;
    }

    reinterpret_cast<InfoEffectRuntimeView *>(bytes(this) + 0x04)->slot_14();
    ++*reinterpret_cast<int *>(bytes(this) + 0x484);
}

void InfoManagerResourceView::bind_story_values_471d00()
{
    battle_records_498()[1].bind_story_values_471a80();
}

void InfoManagerResourceView::render_runtime_471d10()
{
    g_render_mode_manager.set_state_22(1);
    g_render_mode_manager.set_blend_mode(1);

    const float shift = static_cast<float>(
        (1.0f - lookup_orientation_cosine(
            *reinterpret_cast<int *>(bytes(this) + 0x494) * 3)) * 200.0);
    const float negative_shift = -shift;

    (*reinterpret_cast<Renderable2DView **>(bytes(this) + 0x47c))
        ->render(0.0f, negative_shift);
    (*reinterpret_cast<Renderable2DView **>(bytes(this) + 0x480))
        ->render(640.0f, negative_shift);
    reinterpret_cast<Renderable2DView *>(bytes(this) + 0x98)
        ->render(0.0f, negative_shift);
    reinterpret_cast<Renderable2DView *>(bytes(this) + 0xcc)
        ->render(0.0f, shift);

    InfoEffectRuntimeView *effect =
        reinterpret_cast<InfoEffectRuntimeView *>(bytes(this) + 0x04);
    effect->set_phase(2);
    reinterpret_cast<InfoShortRuntimeView *>(bytes(this) + 0x16c)
        ->render_46a800();
    reinterpret_cast<InfoShortRuntimeView *>(bytes(this) + 0x1a0)
        ->render_46a800();
    reinterpret_cast<BattleInfoRenderView *>(bytes(this) + 0x498)
        ->render_470710(shift);
    reinterpret_cast<StoryInfoRenderView *>(bytes(this) + 0x590)
        ->render_470720(shift);
    reinterpret_cast<InfoLongRuntimeView *>(bytes(this) + 0x1d4)
        ->render_4325c0();
    reinterpret_cast<InfoLongRuntimeView *>(bytes(this) + 0x328)
        ->render_4325c0();
    effect->set_phase(1);
    effect->set_phase(0);
}

} // namespace th105
