#include "battle/SystemEffectObject.hpp"
typedef void (SystemEffectObjectBase::*SystemEffectMethod)();
SystemEffectMethod get_system_effect_update_method()
{
    return &SystemEffectObjectBase::update_state;
}
SystemEffectMethod get_system_effect_render_method()
{
    return &SystemEffectObjectBase::render_effect;
}
