#pragma once

#include <stddef.h>

namespace th105 {
// 0x28-byte application startup value copied by 0x00407DA0. The WinMain
// caller supplies HWND/HINSTANCE and two callback objects after construction.
// Unresolved option words and flag purposes keep offset-based names.
struct ApplicationStartupOptions {
    ApplicationStartupOptions();

    void *window_00;
    void *instance_04;
    unsigned graphics_option_08;
    unsigned graphics_option_0c;
    unsigned audio_option_10;
    void *application_callbacks_14;
    unsigned initial_state_18;
    void *secondary_callbacks_1c;
    bool graphics_enabled_20;
    bool input_enabled_21;
    bool audio_enabled_22;
    bool ime_enabled_23;
    bool cursor_visible_24;
    bool graphics_flag_25;
    bool flag_26;
    bool flag_27;
};

typedef char ApplicationStartupOptionsSize[
    sizeof(ApplicationStartupOptions) == 0x28 ? 1 : -1];
typedef char ApplicationStartupOptionsFlags[
    offsetof(ApplicationStartupOptions, graphics_enabled_20) == 0x20 ? 1 : -1];
} // namespace th105
