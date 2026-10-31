#include "engine/RenderModeManager.hpp"
#include "ui/Title.hpp"
namespace th105 {
// The actual four-byte texture token is passed by value. This view declares
// the established binder entry, without claiming another manager instance.
struct RenderTextureBindingView {
    void bind_texture(TextureHandleResult handle, int stage);
};
extern RenderTextureBindingView g_render_texture_binding;
void RenderModeManager::on_device_lost()
{
    g_render_texture_binding.bind_texture(TextureHandleResult(), 0);
}
}
