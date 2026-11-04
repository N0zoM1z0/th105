#include "battle/SystemEffectManager.hpp"
#include "ui/Title.hpp"
namespace th105 {
template <>
SystemEffectObject *SystemEffectManager< ::SystemEffectObject>::spawn(const char *path, short mode, float x, float y)
{
    SystemEffectObject *object = acquire_and_link_object();
    unsigned int token, width, height;
    object->resource_handle_138 = *g_title_resource_manager.load_texture(&token, path, &width, &height);
    object->effect_000.sprite_000.set_texture_options(object->resource_handle_138, 0, 0, width, height, 0, 0);
    object->effect_000.object_x_0e8 = x;
    object->effect_000.object_y_0ec = y;
    object->mode_13c = mode;
    object->reset_state();
    return object;
}
}
