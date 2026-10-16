#include "ApplicationStartupOptions.hpp"

namespace th105 {
ApplicationStartupOptions::ApplicationStartupOptions()
{
    window_00 = 0;
    instance_04 = 0;
    graphics_option_08 = 0;
    graphics_option_0c = 0;
    cursor_visible_24 = true;
    graphics_enabled_20 = true;
    input_enabled_21 = true;
    audio_enabled_22 = true;
    ime_enabled_23 = false;
    graphics_flag_25 = false;
    flag_26 = false;
    flag_27 = false;
    audio_option_10 = 0;
    initial_state_18 = 0;
    application_callbacks_14 = 0;
    secondary_callbacks_1c = 0;
}
} // namespace th105
