#include "engine/RenderModeManager.hpp"
#include "ui/Title.hpp"

namespace th105 {

void RenderModeManager::on_device_lost()
{
    g_title_resource_manager.bind_texture(0, 0);
}

} // namespace th105
