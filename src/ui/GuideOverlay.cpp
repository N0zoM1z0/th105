#include "SelectScenario.hpp"
#include "engine/RenderModeManager.hpp"

extern "C" __declspec(dllimport) int __cdecl wsprintfA(
    char *buffer, const char *format, ...);
extern "C" const char guide_texture_path_format[];

namespace th105 {

GuideOverlay::GuideOverlay()
{
    texture_04 = 0;
    visible = false;
}

GuideOverlay::~GuideOverlay()
{
    if (texture_04 != 0)
        g_title_resource_manager.release_title_resource_handle(texture_04);
}

void GuideOverlay::load(int guide_id)
{
    char path[260];
    wsprintfA(path, guide_texture_path_format, guide_id);

    unsigned int handle;
    unsigned int width;
    unsigned int height;
    unsigned int loaded = *g_title_resource_manager.load_texture(
        &handle, path, &width, &height);
    const unsigned int *methods = sprite_08.vtable;
    texture_04 = loaded;
    reinterpret_cast<UiSprite94::SetTexture>(methods[5])(
        &sprite_08, texture_04, 0, 0, width, height);
    wrap_width_a0 = static_cast<float>(width);
    scroll_9c = 0.0f;
    alpha_a4 = 0;
    visible = false;
}

void GuideOverlay::update()
{
    scroll_9c += 0.5;
    if (scroll_9c > wrap_width_a0)
        scroll_9c -= wrap_width_a0;

    unsigned char alpha = alpha_a4;
    if (visible) {
        if (alpha >= 255)
            return;
        alpha += 15;
    } else {
        if (alpha == 0)
            return;
        alpha -= 15;
    }
    reinterpret_cast<UiSprite94::SetColor>(sprite_08.vtable[1])(
        &sprite_08,
        (static_cast<unsigned int>(alpha_a4 = alpha) << 24) |
            0xFFFFFF);
}

void GuideOverlay::render()
{
    if (alpha_a4 == 0)
        return;

    g_render_mode_manager.set_mode(2);
    sprite_08.render(-scroll_9c, 456.0f);
    sprite_08.render(wrap_width_a0 - scroll_9c, 456.0f);
    g_render_mode_manager.set_mode(1);
}

} // namespace th105
