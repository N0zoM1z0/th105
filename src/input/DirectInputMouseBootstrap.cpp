#include "input/DirectInputDeviceViews.hpp"

namespace th105 {

int report_direct_input_error(const char *message)
{
    return MessageBoxA(g_direct_input_window,message,direct_input_error_title,0);
}

unsigned char initialize_mouse_device()
{
    if (g_mouse_device != 0)
        return 1;

    if (g_direct_input_interface->vtable->create_device(
            g_direct_input_interface,
            &mouse_device_guid,
            &g_mouse_device,
            0) < 0) {
        MessageBoxA(
            g_direct_input_window,
            direct_input_create_mouse_error,
            direct_input_error_title,
            0);
        return 0;
    }

    if (g_mouse_device->vtable->set_data_format(
            g_mouse_device, mouse_data_format) < 0) {
        MessageBoxA(
            g_direct_input_window,
            direct_input_set_format_error,
            direct_input_error_title,
            0);
        return 0;
    }

    if (g_mouse_device->vtable->set_cooperative_level(
            g_mouse_device, g_direct_input_window, 6) < 0) {
        MessageBoxA(
            g_direct_input_window,
            direct_input_cooperative_error,
            direct_input_error_title,
            0);
        return 0;
    }

    unsigned int property[5];
    property[0] = 20;
    property[1] = 16;
    property[2] = 0;
    property[3] = 0;
    property[4] = 1;
    if (g_mouse_device->vtable->set_property(
            g_mouse_device, reinterpret_cast<const GUID *>(2), property) < 0) {
        report_direct_input_error(direct_input_property_error);
        return 0;
    }

    g_mouse_device->vtable->acquire(g_mouse_device);
    return 1;
}

} // namespace th105
