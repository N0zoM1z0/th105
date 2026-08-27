#include "battle/BackgroundBase.hpp"
#include "ui/Title.hpp"

namespace th105 {

BackgroundBase::BackgroundBase()
    : handles_a_04(), sprites_a_14(), handles_b_24(), sprites_b_34()
{
    value_44 = value_48 = value_4c = value_50 = value_54 = value_58 = 0.0f;
}

BackgroundBase::~BackgroundBase()
{
    for (unsigned i = 0; i < handles_b_24.size(); ++i)
        g_title_resource_manager.release_title_resource_handle(handles_b_24[i]);
    for (unsigned i = 0; i < handles_a_04.size(); ++i)
        g_title_resource_manager.release_title_resource_handle(handles_a_04[i]);
}

} // namespace th105
