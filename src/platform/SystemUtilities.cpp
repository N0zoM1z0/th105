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

struct DirectInput8View;
struct DirectInputDevice8View;
struct DirectInput8VtableView {
    void *slots_00[3];
    long (__stdcall *create_device)(
        DirectInput8View *, const GUID *, DirectInputDevice8View **, void *);
    void *slots_10[3];
    long (__stdcall *initialize)(DirectInput8View *, void *, unsigned long);
};
struct DirectInput8View {
    DirectInput8VtableView *vtable;
};

struct DirectInputDevice8VtableView {
    void *slots_00[6];
    long (__stdcall *set_property)(DirectInputDevice8View *, const GUID *, const void *);
    long (__stdcall *acquire)(DirectInputDevice8View *);
    void *slots_20[3];
    long (__stdcall *set_data_format)(DirectInputDevice8View *, const void *);
    void *slot_30;
    long (__stdcall *set_cooperative_level)(
        DirectInputDevice8View *, HWND, unsigned long);
};
struct DirectInputDevice8View {
    DirectInputDevice8VtableView *vtable;
};

extern HWND g_direct_input_window;
extern DirectInput8View *g_direct_input_interface;
extern DirectInputDevice8View *g_keyboard_device;
extern DirectInputDevice8View *g_mouse_device;
extern const GUID direct_input_class_id;
extern const GUID direct_input_interface_id;
extern const GUID keyboard_device_guid;
extern const GUID mouse_device_guid;
extern const unsigned char keyboard_data_format[];
extern const unsigned char mouse_data_format[];
extern const char direct_input_create_error[];
extern const char direct_input_initialize_error[];
extern const char direct_input_error_title[];
extern const char direct_input_create_keyboard_error[];
extern const char direct_input_set_format_error[];
extern const char direct_input_cooperative_error[];
extern const char direct_input_create_mouse_error[];

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
        return 0;
    }

    g_mouse_device->vtable->acquire(g_mouse_device);
    return 1;
}

} // namespace th105
