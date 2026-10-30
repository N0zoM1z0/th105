#include "input/DirectInputMouseBootstrap.cpp"
#include "SystemUtilities.hpp"

#include <windows.h>
#include <objbase.h>
#include <string.h>
#include <stdlib.h>

namespace th105 {

int __stdcall split_path_components(
    char *full_path,
    char *directory,
    char *filename)
{
    char extension[256];
    if (filename != 0) {
        _splitpath_s(
            full_path, 0, 0, directory, 260, filename, 260,
            extension, sizeof(extension));
        return strcat_s(filename, 260, extension);
    }
    return _splitpath_s(
        full_path, 0, 0, directory, 260, 0, 0, extension, sizeof(extension));
}

void __stdcall read_clipboard_ansi(char *destination, unsigned int size)
{
    if (destination == 0 || size == 0)
        return;

    OpenClipboard(0);
    HANDLE data = GetClipboardData(CF_TEXT);
    if (data != 0) {
        const char *text = static_cast<const char *>(GlobalLock(data));
        strncpy_s(destination, size, text, size - 1);
        GlobalUnlock(data);
    } else {
        destination[0] = 0;
    }
    CloseClipboard();
}

unsigned char ModulePathTextView::extra_bytes(unsigned char value)
{
    if (value < 0x81)
        return 0;
    if (value < 0xA0)
        return 1;
    if (value < 0xE0)
        return 0;
    return value < 0xFF;
}

unsigned char __stdcall initialize_direct_input(void *window, void *instance)
{
    if (g_direct_input_interface != 0)
        return 1;

    g_direct_input_window = static_cast<HWND>(window);
    if (CoCreateInstance(
            direct_input_class_id,
            0,
            0x17,
            direct_input_interface_id,
            reinterpret_cast<void **>(&g_direct_input_interface)) < 0) {
        MessageBoxA(
            g_direct_input_window,
            direct_input_create_error,
            direct_input_error_title,
            0);
        return 0;
    }

    if (g_direct_input_interface->vtable->initialize(
            g_direct_input_interface, instance, 0x800) < 0) {
        MessageBoxA(
            g_direct_input_window,
            direct_input_initialize_error,
            direct_input_error_title,
            0);
        return 0;
    }
    return 1;
}

unsigned char initialize_keyboard_device()
{
    if (g_keyboard_device != 0)
        return 1;

    if (g_direct_input_interface->vtable->create_device(
            g_direct_input_interface,
            &keyboard_device_guid,
            &g_keyboard_device,
            0) < 0) {
        MessageBoxA(
            g_direct_input_window,
            direct_input_create_keyboard_error,
            direct_input_error_title,
            0);
        return 0;
    }

    if (g_keyboard_device->vtable->set_data_format(
            g_keyboard_device, keyboard_data_format) < 0) {
        MessageBoxA(
            g_direct_input_window,
            direct_input_set_format_error,
            direct_input_error_title,
            0);
        return 0;
    }

    if (g_keyboard_device->vtable->set_cooperative_level(
            g_keyboard_device, g_direct_input_window, 0x16) < 0) {
        MessageBoxA(
            g_direct_input_window,
            direct_input_cooperative_error,
            direct_input_error_title,
            0);
        return 0;
    }

    g_keyboard_device->vtable->acquire(g_keyboard_device);
    return 1;
}


} // namespace th105
