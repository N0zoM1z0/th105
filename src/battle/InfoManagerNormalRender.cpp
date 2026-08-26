#include "battle/Collision.hpp"
#include "battle/InfoManagerResources.hpp"
#include "engine/RenderModeManager.hpp"
#include "input/InputSelection.hpp"
#include "ui/UiPrimitives.hpp"

#include <string>
#include <string.h>

namespace th105 {

float __cdecl lookup_orientation_cosine(int angle);

struct InfoShortNormalRenderView { void render_46a800(); };
struct InfoLongNormalRenderView { void render_4325c0(); };
struct BattleInfoNormalRenderView { void render_470710(float shift); };
struct InfoEffectNormalRenderView {
    virtual void slot_00(); virtual void slot_04(); virtual void slot_08();
    virtual void slot_0c(); virtual void slot_10(); virtual void slot_14();
    virtual void set_phase(int phase);
};
struct Renderable2DNormalView {
    virtual void slot_00(); virtual void slot_04(); virtual void slot_08();
    virtual void slot_0c(); virtual void slot_10(); virtual void slot_14();
    virtual void slot_18(); virtual void render(float x, float y);
};
struct InfoDesignNormalRenderView {
    virtual void slot_00(); virtual void slot_04(); virtual void slot_08();
    virtual void slot_0c(); virtual void slot_10(); virtual void slot_14();
    virtual void render_object_18(float x, float y, int id);
    virtual void move_1c(float x, float y);
};
struct NormalSceneRendererProfileView {
    unsigned char reserved_000[0x0c];
    Fighter *fighter_0c;
    Fighter *fighter_10;
};
struct ProfileRenderSprite94 {
    virtual void slot_00(); virtual void slot_04(); virtual void slot_08();
    virtual void slot_0c(); virtual void slot_10(); virtual void slot_14();
    virtual void slot_18(); virtual void render(float x, float y);
    unsigned char reserved_004[0x90];
};
typedef char ProfileRenderSprite94_size_must_be_0x94[
    sizeof(ProfileRenderSprite94) == 0x94 ? 1 : -1];

struct NetworkProfileRenderView {
    unsigned char reserved_000[0x24];
    char profile_name_024[1];
};
struct PlayerSlotNormalRenderView {
    unsigned texture_000;
    ProfileRenderSprite94 sprite_004;
    std::string string_098;
    std::string string_0b4;
};
extern NormalSceneRendererProfileView *g_scene_renderer;

static __forceinline bool hide_profile(Fighter *fighter)
{
    return reinterpret_cast<unsigned char *>(fighter)[0x72c] != 0;
}
static __forceinline ProfileRenderSprite94 *network_profile_sprite(
    NetworkProfileRenderView *session, unsigned offset)
{
    return reinterpret_cast<ProfileRenderSprite94 *>(
        reinterpret_cast<unsigned char *>(session) + offset);
}
static __forceinline PlayerSlotNormalRenderView *player_slot(unsigned slot)
{
    return reinterpret_cast<PlayerSlotNormalRenderView *>(
        get_player_slot_record(slot));
}

struct CInfoManagerNormalRenderView {
    void render_normal_46e650();
};

void CInfoManagerNormalRenderView::render_normal_46e650()
{
    unsigned char *self = reinterpret_cast<unsigned char *>(this);
    g_render_mode_manager.set_state_22(1);
    g_render_mode_manager.set_blend_mode(1);

    const float shift = static_cast<float>(
        (1.0f - lookup_orientation_cosine(
            *reinterpret_cast<int *>(self + 0x494) * 3)) * 200.0);
    const float negative_shift = -shift;

    (*reinterpret_cast<Renderable2DNormalView **>(self + 0x47c))
        ->render(0.0f, negative_shift);
    (*reinterpret_cast<Renderable2DNormalView **>(self + 0x480))
        ->render(640.0f, negative_shift);

    if (!hide_profile(g_scene_renderer->fighter_0c)) {
        if (get_network_session() != 0) {
            unsigned name_length = strlen(
                reinterpret_cast<NetworkProfileRenderView *>(
                    get_network_session())->profile_name_024);
            network_profile_sprite(
                reinterpret_cast<NetworkProfileRenderView *>(
                    get_network_session()), 0x27c)
                ->render(
                    static_cast<float>(
                        212.0 - static_cast<float>(static_cast<float>(name_length) * 7.0)),
                    8.0f - shift);
        } else if (get_session_setup_option() != 2) {
            unsigned name_length = player_slot(0)->string_0b4.size();
            player_slot(0)->sprite_004.render(
                static_cast<float>(
                    212.0 - static_cast<float>(static_cast<float>(name_length) * 7.0)),
                8.0f - shift);
        }
    }

    if (!hide_profile(g_scene_renderer->fighter_10)) {
        if (get_network_session() != 0) {
            network_profile_sprite(
                reinterpret_cast<NetworkProfileRenderView *>(
                    get_network_session()), 0x310)
                ->render(428.0f, 8.0f - shift);
        } else if (get_session_setup_option() != 2) {
            player_slot(1)->sprite_004.render(428.0f, 8.0f - shift);
        }
    }

    reinterpret_cast<InfoDesignNormalRenderView *>(self + 0x98)
        ->render_object_18(0.0f, negative_shift, 26);
    reinterpret_cast<InfoDesignNormalRenderView *>(self + 0xcc)
        ->move_1c(0.0f, shift);

    InfoEffectNormalRenderView *effect =
        reinterpret_cast<InfoEffectNormalRenderView *>(self + 0x04);
    effect->set_phase(2);
    g_render_mode_manager.set_blend_mode(1);
    reinterpret_cast<InfoShortNormalRenderView *>(self + 0x16c)->render_46a800();
    reinterpret_cast<InfoShortNormalRenderView *>(self + 0x1a0)->render_46a800();
    reinterpret_cast<BattleInfoNormalRenderView *>(self + 0x498)->render_470710(shift);
    reinterpret_cast<BattleInfoNormalRenderView *>(self + 0x590)->render_470710(shift);
    reinterpret_cast<InfoLongNormalRenderView *>(self + 0x1d4)->render_4325c0();
    reinterpret_cast<InfoLongNormalRenderView *>(self + 0x328)->render_4325c0();
    effect->set_phase(1);
    g_render_mode_manager.set_blend_mode(1);
    reinterpret_cast<InfoDesignNormalRenderView *>(self + 0x98)
        ->move_1c(0.0f, negative_shift);
    effect->set_phase(0);
}

} // namespace th105
